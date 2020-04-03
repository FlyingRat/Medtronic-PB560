/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0306                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckO2.c                                        	      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            Management of the alarm check O2                              */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Compute.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "SEC_CheckO2.h"
#include "Security_Datas.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckO2(void)
{
	e_DB_ALARMS_STATE AlarmCheckO2 =
								DB_AlarmStatusRead(ALARM_CHECK_O2_U16);
	e_DB_ALARMS_STATE AlarmCheckO2Supply =
								DB_AlarmStatusRead(ALARM_CHECK_O2_SUPPLY_U16);
	e_DB_ALARMS_STATE AlarmMissingO2Supply =
								DB_AlarmStatusRead(ALARM_MISSING_O2_SUPPLY_U16);
    e_DB_ALARMS_STATE AlarmNoFio2Sensor =
   								DB_AlarmStatusRead(ALARM_NO_FIO2_SENSOR_U16);
						
	SWORD16 Measure_QO2 = (SWORD16)DB_ComputeRead(MEASURE_QO2_S16);
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
	UWORD16 Adjust_FIO2= DB_ConfigRead(ADJUST_FIO2);
	UWORD16 FIO2_100_Active= DB_ControlRead(FIO2_100_ACTIVE);
  	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

	static e_VentilState MemoVentilState = VEN_VENTIL_DISABLE;
	static UBYTE Respiratory_Cycle_Counter = 0;
	static SWORD16 Mini = 0;
	static SWORD16 Maxi = 0;

/*%C We must compute the variation of the QO2 each respiratory cycles. */

	if((VentilState == VEN_INSPIRATION_CONTROLED)
	 ||(VentilState == VEN_INSPIRATION_TRIGGERED))
	{
		if(Maxi <Measure_QO2)
		{
			Maxi = Measure_QO2;
		}
	}
	if(VentilState == VEN_EXHALATION)
	{
		if(Mini > Measure_QO2)
		{
			Mini = Measure_QO2;
		}
		if(Mini < 0)
		{
			Mini = 0; 
		}
	}


	switch(AlarmCheckO2)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
		if(((MemoVentilState == VEN_INSPIRATION_CONTROLED)
		  ||(MemoVentilState == VEN_INSPIRATION_TRIGGERED))
		 &&(VentilState == VEN_EXHALATION))
		 {
		 	if((Maxi-Mini <= 1)
			&&((Adjust_FIO2 > cFIO2_MIN_ADJUST)
		 	 ||(FIO2_100_Active == TRUE))
			 &&(AlarmCheckO2Supply == ALARM_FALSE)
			 &&(AlarmMissingO2Supply == ALARM_FALSE)
			 &&(TIM_ReadDecounterValue(VEN_TIME_CALIB_FIO2) == 0))
			{
			 	if(Respiratory_Cycle_Counter <= cTHREE_CYCLES)
				{
					Respiratory_Cycle_Counter += 1;
				}
 			}
			else
			{
				Respiratory_Cycle_Counter = 0;
			}
			Mini =Maxi;
			Maxi = 0;
		 }

		if(Respiratory_Cycle_Counter == cTHREE_CYCLES)
		{
			Respiratory_Cycle_Counter = 0;
			/*%C Alarm is turned to True  */
			DB_AlarmStatusWrite(ALARM_CHECK_O2_U16, ALARM_TRUE);
			DB_EventMngt(EVENT_AL_CHECK_O2);
/*%C		Priority register updating for buzzer and leds command */
			SEC_High_Priority_2	= SEC_High_Priority_2| 0x0040;		
		}  	

		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :


		Alarm_Error = ERR_AL_CHECK_O2;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C 	The following state ,"ALARM_DISPLAYED", is written by HMI module. */
/*%C  So there is no action to do .*/
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                              */
/******************************************************************************/
	case ALARM_DISPLAYED	:
	 	if((Maxi-Mini > 1)
		||((Adjust_FIO2 <= cFIO2_MIN_ADJUST)
	 	 &&(FIO2_100_Active == FALSE))
		 || (AlarmCheckO2Supply >= ALARM_TRUE)
		 ||(AlarmMissingO2Supply >= ALARM_TRUE)
   	 ||(TIM_ReadDecounterValue(VEN_TIME_CALIB_FIO2) !=0))	
		{
/*%C		Alarm is turned to False and the associated event is sent*/
			DB_AlarmStatusWrite(ALARM_CHECK_O2_U16,ALARM_FALSE);
/*%C  The end of alarm event is sent */
			DB_EventMngt(EVENT_AL_END_OF_CHECK_O2);
/*%C		Priority register updating for buzzer and leds command */
			SEC_High_Priority_2= SEC_High_Priority_2& 0xFFBF;

		}	
		Alarm_Error = NO_ERR_AL;

		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :
		Alarm_Error = ERR_AL_CHECK_O2;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
	  	Alarm_Error = ERR_AL_CHECK_O2;
		break;
	}
	MemoVentilState = VentilState;
	return(Alarm_Error);
}