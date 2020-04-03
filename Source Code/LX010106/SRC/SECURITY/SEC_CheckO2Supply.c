/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0306                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckO2Supply.c                                        	  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            Management of the alarm check O2 supply                       */
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
#include "define.h"
#include "Structure.h"
#include "DB_AlarmStatus.h"
#include "DB_Compute.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Event.h"
#include "SEC_CheckO2Supply.h"
#include "Security_Datas.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckO2Supply(void)
{
	e_DB_ALARMS_STATE AlarmCheckO2Supply =
								DB_AlarmStatusRead(ALARM_CHECK_O2_SUPPLY_U16);
    e_DB_ALARMS_STATE AlarmMissingO2Supply =
   								DB_AlarmStatusRead(ALARM_MISSING_O2_SUPPLY_U16);
    e_DB_ALARMS_STATE AlarmNoFio2Sensor =
   								DB_AlarmStatusRead(ALARM_NO_FIO2_SENSOR_U16);
	SWORD16 FilterPressureO2 = (SWORD16)DB_ComputeRead(FILTER_PRESSURE_O2_S16);
	UWORD16 Adjust_FIO2= DB_ConfigRead(ADJUST_FIO2);
	UWORD16 FIO2_100_Active= DB_ControlRead(FIO2_100_ACTIVE);

  	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

	switch(AlarmCheckO2Supply)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C If the filtered O2 pressure is lower than 2.8 bar and, Fio2 is adjusted or*/
/*%C 100%O2 is in progress. */
	    if(	(FilterPressureO2 < cO2_CHECK_SUPPLY_THRESHOLD)
			&&	((Adjust_FIO2 > cFIO2_MIN_ADJUST)
		 	||	(FIO2_100_Active == TRUE))
			&&	(AlarmMissingO2Supply == ALARM_FALSE)
		 	&& (AlarmNoFio2Sensor == ALARM_FALSE)
			&&	(TIM_ReadDecounterValue(VEN_TIME_CALIB_FIO2) == 0))
		{
/*%C 		The Alarm is turned to DETECTED, and the corresponding decounter is launched*/
		  	DB_AlarmStatusWrite(ALARM_CHECK_O2_SUPPLY_U16, ALARM_DETECTED);
			TIM_StartDecounter(SEC_CHECK_O2_SUPPLY, cTEN_SECOND); 
		}
	   	Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C If the filtered O2 pressure is upper or equal to 2.8 bar or, Fio2 is not */
/*%C adjusted or 100%O2 is not in progress, */
/*%C or the alarm "missing O2 supply" is detected or activated,
/*%C or the calib FIO2 is in progress. */
	   if(	(FilterPressureO2 >= cO2_CHECK_SUPPLY_THRESHOLD)
	    	||	((Adjust_FIO2 <= cFIO2_MIN_ADJUST)
		 	&&	(FIO2_100_Active == FALSE))
			||	(AlarmMissingO2Supply != ALARM_FALSE)
			|| (AlarmNoFio2Sensor != ALARM_FALSE)
	   	||	(TIM_ReadDecounterValue(VEN_TIME_CALIB_FIO2) !=0))
	   { 
/*%C		Alarm is turned to False and the associated event is sent*/
			DB_AlarmStatusWrite(ALARM_CHECK_O2_SUPPLY_U16,ALARM_FALSE);
	   }
/*%C	When the Alarm is detected and the delay is over */
	   else if (TIM_ReadDecounterValue(SEC_CHECK_O2_SUPPLY) == 0)
	   { 
/*%C 		The Alarm is turned to TRUE, and the corresponding event is recorded*/
		  	DB_AlarmStatusWrite(ALARM_CHECK_O2_SUPPLY_U16, ALARM_TRUE);
			DB_EventMngt(EVENT_AL_CHECK_O2_SUPPLY);
/*%C		Priority register updating for buzzer and leds command */
			SEC_High_Priority_2	= SEC_High_Priority_2| 0x0010;
	   }
	   Alarm_Error = NO_ERR_AL;
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
/*%C If the filtered O2 pressure is upper or equal to 2.8 bar or, Fio2 is not */
/*%C adjusted or 100%O2 is not in progress, */
/*%C or the alarm "missing O2 supply" is detected or activated,
/*%C or the calib FIO2 is in progress. */
	   if(	((FilterPressureO2 >= cO2_CHECK_SUPPLY_THRESHOLD)
	    	||	((Adjust_FIO2 <= cFIO2_MIN_ADJUST)
		 	&&	(FIO2_100_Active == FALSE)))
			||	(AlarmMissingO2Supply != ALARM_FALSE)
			||	(AlarmNoFio2Sensor != ALARM_FALSE)
	   	||	(TIM_ReadDecounterValue(VEN_TIME_CALIB_FIO2) !=0))
	   { 
/*%C		Alarm is turned to False and the associated event is sent*/
			DB_AlarmStatusWrite(ALARM_CHECK_O2_SUPPLY_U16,ALARM_FALSE);
/*%C  The end of alarm event is sent */
			DB_EventMngt(EVENT_AL_END_OF_CHECK_O2_SUPPLY);
/*%C		Priority register updating for buzzer and leds command */
			SEC_High_Priority_2= SEC_High_Priority_2& 0xFFEF;
	   }

		Alarm_Error = NO_ERR_AL;

		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :
		Alarm_Error = ERR_AL_CHECK_O2_SUPPLY;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
	  	Alarm_Error = ERR_AL_CHECK_O2_SUPPLY;
		break;
	}
	return(Alarm_Error);
}

