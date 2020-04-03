/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_HighPressure.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           High Pressure alarm Management                                 */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : PressureCompareValue									  */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Alarm_Error                                        	  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Event.h"
#include "DB_KeyboardEvent.h"
#include "Security_Datas.h"
#include "Timer_Data.h"
#include "SEC_HighPressure.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_HighPressure(UWORD16 PressureCompareValue)
{ 
/*%C Read all the input values from the appropriates data bases.  			  */

	UWORD16 AlarmHighPressure = DB_AlarmStatusRead(ALARM_HIGH_PRESSURE_U16);
	UWORD16 AlarmCheckPressure = DB_AlarmStatusRead(ALARM_CHECK_PRESSURE_U16);
	UWORD16 AlarmCheckProximal = DB_AlarmStatusRead(ALARM_CHECK_PROXIMAL_U16);
    SWORD16 Measure_Patient_Pressure = 
        (SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);
	SWORD16 Measure_Prox_Pressure = 
        (SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_PROXI_S16);
	SWORD16 MeasureValvePressure = 
						(SWORD16)DB_ComputeRead(MEASURE_VALVE_PRESSURE_S16);

	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
	UWORD16 Ventil_State = DB_ControlRead(VENTIL_STATE_U16);
	UWORD16 High_Pressure_Detected = DB_ControlRead(HIGH_PRESSURE_DETECTED_U16);
	UWORD16 High_Pressure_Exhal_Detected = DB_ControlRead(HIGH_PRESSURE_EXHALATION_DETECTED_U16);
    UWORD16 High_Pressure_Filter_Window = DB_ControlRead(HIGH_PRESSURE_FILTER_WINDOW_U16);

    // HIGH PRESSURE ALARM
	UWORD16 SimvCycles = DB_ControlRead(SIMV_CYCLES_U16);
	UWORD16 CurrentMode = DB_ControlRead(CURRENT_MODE_U16);

	static UWORD16 SIMV_HighPressureCycleCounter = 0;
	static UWORD16 HighPressureCycleCounter = 0;
	static UWORD16 HighPresExhCycleCounter = 0; 
	static UWORD16 Previous_Ventil_State = VEN_EXHALATION;
   	static UWORD16 flag = FALSE;

    // Filter out high pressure signals less than 100ms in duration.
    // This filters out patient-generated transient pressures caused by 
    // the glottis closing.
    // Once the high pressure duration exceeds 100 ms, a high pressure 
    // condition is declared and the vent has 100 ms to relieve pressure within
    // the 200ms time required by ISO 10651-2. 

    // The 100 ms filter time was derived by testing the worst-case conditions of
    // high compliance (C50) and high resistance (R50) with the most aggresive
    // rise time in VC ventilation.  With these conditions, the vent relieves
    // pressure within 90 ms after high pressure detection. Therefore a filter
    // delay of 100 ms is within the 110 ms maximum detection time that allows
    // the vent to relieve pressure within the 200 ms.

    e_BOOL HighPressureCondition = FALSE;

    if ((Measure_Patient_Pressure >= (SWORD16)PressureCompareValue)
        || ((Measure_Prox_Pressure >= (SWORD16)PressureCompareValue)
            && (AlarmCheckProximal < ALARM_DETECTED)) )
    {
        if (High_Pressure_Filter_Window == FALSE)
        {
            TIM_StartDecounter(SEC_HIGH_PRESSURE_DETECT,TIME_HIGH_PRESSURE_DETECT);
            High_Pressure_Filter_Window = TRUE;
            DB_ControlWrite(HIGH_PRESSURE_FILTER_WINDOW_U16,High_Pressure_Filter_Window);
        }
        if (TIM_ReadDecounterValue(SEC_HIGH_PRESSURE_DETECT) == 0)
        {
            HighPressureCondition = TRUE;
        }
    }
    else
    {
        DB_ControlWrite(HIGH_PRESSURE_FILTER_WINDOW_U16,FALSE);
    }

    // Override time-filtered high pressure condition for P >= cHIGH_PRESSURE cmH2O
    if ((Measure_Patient_Pressure >= (SWORD16)cHIGH_PRESSURE)
        || ((Measure_Prox_Pressure >= (SWORD16)cHIGH_PRESSURE)
            && (AlarmCheckProximal < ALARM_DETECTED)) )
    {
        HighPressureCondition = TRUE;
    }

    // override filtered high pressure condition if both internal and 
    // proximal sensors have failed and valve pressure exceeds limit
    if ( (MeasureValvePressure > (SWORD16)PressureCompareValue)
         && (AlarmCheckPressure >= ALARM_DETECTED)
         && (AlarmCheckProximal >= ALARM_DETECTED) )
    {
        HighPressureCondition = TRUE;
    }

    // If outside the high pressure detection window or
    // a high pressure condition exists then update
    // the displayed low-pass filtered pressure data.
    if ( (HighPressureCondition == TRUE) 
         || (High_Pressure_Filter_Window == FALSE) )
    {
        DB_ComputeWrite(LPF_PATIENT_PRESSURE_S16,Measure_Patient_Pressure);
    }

	switch(AlarmHighPressure)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
		HighPresExhCycleCounter = 0;
		HighPressureCycleCounter = 0;
		SIMV_HighPressureCycleCounter = 0;
		flag = FALSE;

		if ( (Ventil_State == VEN_EXHALATION)
		  && (Previous_Ventil_State != VEN_EXHALATION))
		{
			TIM_StartDecounter(SEC_HIGH_PRESSURE,TIME_HIGH_PRESSURE);
		}
        if ( HighPressureCondition == TRUE )
		{
			DB_AlarmStatusWrite(ALARM_HIGH_PRESSURE_U16, ALARM_DETECTED);
			
			if ( (Ventil_State == VEN_INSPIRATION_CONTROLED)
			  || (Ventil_State == VEN_INSPIRATION_TRIGGERED) )
			{
			DB_AlarmStatusWrite(ALARM_HIGH_PRESSURE_U16, ALARM_DETECTED);
				DB_ControlWrite(HIGH_PRESSURE_DETECTED_U16,
									 TRUE);
			}
			else if ( (Ventil_State == VEN_EXHALATION)
				   && (TIM_ReadDecounterValue(SEC_HIGH_PRESSURE) == 0)
				   ) 
			{
				DB_AlarmStatusWrite(ALARM_HIGH_PRESSURE_U16, ALARM_DETECTED);
				DB_ControlWrite(HIGH_PRESSURE_EXHALATION_DETECTED_U16,
										 TRUE);
			}
		}
	   else
	   {
	   		if (KeyboardDoublePulseInhibEvent == TRUE)
		   	{
		      	DB_ControlWrite(HIGH_PRESSURE_LED_REMINDER_U16, FALSE);
		   	}
			DB_ControlWrite(HIGH_PRESSURE_DETECTED_U16,
								 FALSE);
			DB_ControlWrite(HIGH_PRESSURE_EXHALATION_DETECTED_U16,
								 FALSE);
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 				          */
/******************************************************************************/
	case ALARM_DETECTED :
		if ((Ventil_State == VEN_EXHALATION)
		   &&(Previous_Ventil_State != VEN_EXHALATION))
		{
			TIM_StartDecounter(SEC_HIGH_PRESSURE,TIME_HIGH_PRESSURE);
		}
        if ( HighPressureCondition == TRUE )
		{
			if ( (Ventil_State == VEN_INSPIRATION_CONTROLED)
			    || (Ventil_State == VEN_INSPIRATION_TRIGGERED) )
			{
				DB_ControlWrite(HIGH_PRESSURE_DETECTED_U16,
									 TRUE);
			}
			else if ( (Ventil_State == VEN_EXHALATION)
				   && (TIM_ReadDecounterValue(SEC_HIGH_PRESSURE) == 0) 
				    )
			{	
				DB_ControlWrite(HIGH_PRESSURE_EXHALATION_DETECTED_U16,
										 TRUE);
			}
		}
		if ((Ventil_State == VEN_EXHALATION)
		   &&((Previous_Ventil_State == VEN_INSPIRATION_CONTROLED)
		     ||(Previous_Ventil_State == VEN_INSPIRATION_TRIGGERED)))
		{
			flag = FALSE;
			if (High_Pressure_Detected == TRUE)
			{
			  	if ( ( (CurrentMode != VSIMV)
				  && (CurrentMode!=PSIMV) )
				  || (SimvCycles == PSV_Cycle) )
				{
					HighPressureCycleCounter = HighPressureCycleCounter +1;
				}
				else  
				{
					SIMV_HighPressureCycleCounter = 
					SIMV_HighPressureCycleCounter + 1;
				}
			}
			else
			{
				if ( ( (CurrentMode != VSIMV)
				  && (CurrentMode!=PSIMV) )
				  || (SimvCycles == PSV_Cycle) )
				{
					HighPressureCycleCounter = 0;
				}
				else
				{
					SIMV_HighPressureCycleCounter = 0;
				}
			
			}
			DB_ControlWrite(HIGH_PRESSURE_DETECTED_U16,
								 FALSE);
		}
/////////////////////////////////////////////////////////////////////

		if ( (Ventil_State == VEN_EXHALATION)
		  && (TIM_ReadDecounterValue(SEC_HIGH_PRESSURE) == 0)
		  && (flag == FALSE) )	
		{
			if (High_Pressure_Exhal_Detected == TRUE)
			{
				flag = TRUE;
				HighPresExhCycleCounter = HighPresExhCycleCounter +1;
			}
		}
		if ( (Previous_Ventil_State == VEN_EXHALATION)
		  	&& ( (Ventil_State == VEN_INSPIRATION_CONTROLED)
		    || (Ventil_State == VEN_INSPIRATION_TRIGGERED) ) )
			{
				if (High_Pressure_Exhal_Detected == FALSE) 
				{
					HighPresExhCycleCounter = 0;
				}
				DB_ControlWrite(HIGH_PRESSURE_EXHALATION_DETECTED_U16,
								 FALSE);
			}
		if( (HighPresExhCycleCounter == 0)
			&& (HighPressureCycleCounter == 0)	
			&& (SIMV_HighPressureCycleCounter == 0) )
		{
			DB_AlarmStatusWrite(ALARM_HIGH_PRESSURE_U16, ALARM_FALSE);
			SEC_High_Priority_1= SEC_High_Priority_1& 0xFFFD;
		}		
		else if ((HighPressureCycleCounter >= 3)	 
			||(SIMV_HighPressureCycleCounter >= 3)
			||(HighPresExhCycleCounter >= 3))
		{
			DB_AlarmStatusWrite(ALARM_HIGH_PRESSURE_U16, ALARM_TRUE);
			DB_ControlWrite(HIGH_PRESSURE_LED_REMINDER_U16, TRUE);
			DB_EventMngt(EVENT_AL_HIGH_PRESS);
			SEC_High_Priority_1= SEC_High_Priority_1| 0x0002;
		}
		else
		{
		   	if (KeyboardDoublePulseInhibEvent == TRUE)
			   {
			      DB_ControlWrite(HIGH_PRESSURE_LED_REMINDER_U16, FALSE);
			   }
		}

		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State					 		  */
/******************************************************************************/
	case ALARM_TRUE :
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
		if ( (Ventil_State == VEN_EXHALATION)
		  && (Previous_Ventil_State != VEN_EXHALATION))
		{
			TIM_StartDecounter(SEC_HIGH_PRESSURE,TIME_HIGH_PRESSURE);
		}

        if ( HighPressureCondition == TRUE )
		{
			if ( (Ventil_State == VEN_INSPIRATION_CONTROLED)
			  || (Ventil_State == VEN_INSPIRATION_TRIGGERED) )
			{	
				DB_ControlWrite(HIGH_PRESSURE_DETECTED_U16,
									 TRUE);
			}
			else if ((Ventil_State == VEN_EXHALATION)
					&&(TIM_ReadDecounterValue(SEC_HIGH_PRESSURE) == 0))
			{
				DB_ControlWrite(HIGH_PRESSURE_EXHALATION_DETECTED_U16,
										 TRUE);
			}
		}
		else
		{
			if ( (Previous_Ventil_State == VEN_EXHALATION)
			  && ( (Ventil_State == VEN_INSPIRATION_CONTROLED)
			    || (Ventil_State == VEN_INSPIRATION_TRIGGERED) ) )	
			{
				if (High_Pressure_Exhal_Detected == FALSE)
				{
					HighPresExhCycleCounter = 0;
				}
				DB_ControlWrite(HIGH_PRESSURE_EXHALATION_DETECTED_U16,
							 	 FALSE);											
			}
			if ( (Ventil_State == VEN_EXHALATION)
			  && ( (Previous_Ventil_State == VEN_INSPIRATION_CONTROLED)
			    || (Previous_Ventil_State == VEN_INSPIRATION_TRIGGERED) ) )	
			{
				if (High_Pressure_Detected == FALSE)
				{
					if ( ( (CurrentMode != VSIMV)
				  	  && (CurrentMode!=PSIMV) )
				  	  || (SimvCycles == PSV_Cycle) )
					{													 
						HighPressureCycleCounter = 0;
				 	}
					else
					{
						SIMV_HighPressureCycleCounter = 0;
					}
				}
				DB_ControlWrite(HIGH_PRESSURE_DETECTED_U16,
								 FALSE);
			}
		}

																  
			if ( (HighPresExhCycleCounter == 0)
				&& (HighPressureCycleCounter == 0)	
				&& (SIMV_HighPressureCycleCounter == 0) )
			{
				DB_AlarmStatusWrite(ALARM_HIGH_PRESSURE_U16, ALARM_FALSE);
				DB_EventMngt(EVENT_AL_END_OF_HIGH_PRESSURE);
				SEC_High_Priority_1= SEC_High_Priority_1& 0xFFFD;
			}
			else if ( (HighPresExhCycleCounter < 3)
				&& (HighPressureCycleCounter < 3)	
				&& (SIMV_HighPressureCycleCounter < 3) )
			{
				DB_AlarmStatusWrite(ALARM_HIGH_PRESSURE_U16, ALARM_DETECTED);
				DB_EventMngt(EVENT_AL_END_OF_HIGH_PRESSURE);
				SEC_High_Priority_1= SEC_High_Priority_1& 0xFFFD;
			}

		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
		Alarm_Error = ERR_AL_HIGH_PRESSURE;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
		Alarm_Error = ERR_AL_HIGH_PRESSURE;
		break;
	}
	Previous_Ventil_State = Ventil_State;

	return (Alarm_Error);

}


