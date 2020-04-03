
/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_HighPressureDetection.c                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C  High Pressure detection Management for pressure modes (PRES, PSV)       */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : PressureCompareValue												*/
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Alarm_Error                                        	*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "Timer_Data.h"
#include "SEC_HighPressureDetection.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_HighPressureDetection(UWORD16 PressureCompareValue)
{ 
/*%C Read all the input values from the appropriates data bases.  */
	SWORD16 MeasureValvePressure = 
						(SWORD16)DB_ComputeRead(MEASURE_VALVE_PRESSURE_S16);
   SWORD16 Measure_Internal_Pressure = 
   						  (SWORD16)DB_ComputeRead(MEASURE_INTERNAL_PRESSURE_S16);
   SWORD16 Measure_Proximal_Pressure = 
   					  (SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_PROXI_S16);
	UWORD16 Ventil_State = DB_ControlRead(VENTIL_STATE_U16);
	static UWORD16 Previous_Ventil_State = VEN_EXHALATION;
	static UWORD16 MutexHighPressure = FALSE;

/*%C High pressure flags initialization at each new inspiration */
	if ( (Previous_Ventil_State == VEN_EXHALATION)
	  && ( (Ventil_State == VEN_INSPIRATION_CONTROLED)
	    || (Ventil_State == VEN_INSPIRATION_TRIGGERED) ) )	
	{
		DB_ControlWrite(HIGH_PRESSURE_DETECTED_PRESSURE_MODE_U16,
							 FALSE);
		DB_ControlWrite(HIGH_PRESSURE_EXHALATION_DETECTED_PRESSURE_MODE_U16,
							 FALSE);
		MutexHighPressure = FALSE;
	}
/*%C Ventil state memorization */
	Previous_Ventil_State = Ventil_State;

/*%C 	HIGH PRESSURE DETECTION              											*/
/*%C 	if the patient pressure measure or the              						*/
/*%C 	proximal patient pressure is upper than the "compare" value then:		*/
/*%C	- the timer for the 100ms delay is launched.						*/
/*%C	- the Alarm status becomes ALARM_DETECTED and is written	in database	*/
	if ( (Measure_Internal_Pressure > (SWORD16)PressureCompareValue)
	  || (Measure_Proximal_Pressure > (SWORD16)PressureCompareValue)
     || (MeasureValvePressure > (SWORD16)PressureCompareValue) )
	{
/*%C	Timer launch at the first high pressure detection	*/
		if (MutexHighPressure == FALSE)
		{ 
			TIM_StartDecounter(SEC_HIGH_PRESSURE,cTIME_HIGH_PRESSURE);
			MutexHighPressure = TRUE;
		}
/*%C	else, if the delay is reached, the high pressure flag is set	*/
		else
		{
			if (TIM_ReadDecounterValue(SEC_HIGH_PRESSURE)==0)
			{
/*%C			High pressure flag (during inspiration) writing	*/
				if ( (Ventil_State == VEN_INSPIRATION_CONTROLED)
				  || (Ventil_State == VEN_INSPIRATION_TRIGGERED) )
				{	  	
					DB_ControlWrite(HIGH_PRESSURE_DETECTED_PRESSURE_MODE_U16,
										 TRUE);
				}
/*%C			High pressure flag (during exhalation) writing	*/
				else if (Ventil_State == VEN_EXHALATION)
				{
					DB_ControlWrite(HIGH_PRESSURE_EXHALATION_DETECTED_PRESSURE_MODE_U16,
										 TRUE);
				}
			}
		}	  
	}
/*%C else, no high pressure detection, mutex initialization	*/
	else
	{
		MutexHighPressure = FALSE;
	}
}

