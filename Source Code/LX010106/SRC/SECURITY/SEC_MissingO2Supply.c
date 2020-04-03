/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0306                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_MissingO2Supply.c                                        	  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            Management of the alarm missing O2 supply                       */
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
#include "define.h"
#include "DB_AlarmStatus.h"
#include "DB_Compute.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Event.h"
#include "SEC_MissingO2Supply.h"
#include "Security_Datas.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_MissingO2Supply(void)
{
	e_DB_ALARMS_STATE AlarmMissingO2Supply =
								DB_AlarmStatusRead(ALARM_MISSING_O2_SUPPLY_U16);
	SWORD16 MeasurePressureO2 = (SWORD16)DB_ComputeRead(MEASURE_PRESSURE_O2_S16);
	e_DB_ALARMS_STATE AlarmNoFio2Sensor =
   								DB_AlarmStatusRead(ALARM_NO_FIO2_SENSOR_U16);
	UWORD16 Adjust_FIO2= DB_ConfigRead(ADJUST_FIO2);
	UWORD16 FIO2_100_Active= DB_ControlRead(FIO2_100_ACTIVE);
  	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

	switch(AlarmMissingO2Supply)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C If the measure O2 pressure is lower than 0.1 bar and, Fio2 is adjusted or*/
/*%C 100%O2 is in progress. */
	    if	((MeasurePressureO2 < cO2_MISSING_SUPPLY_THRESHOLD)
			&&	((Adjust_FIO2 > cFIO2_MIN_ADJUST)
		 	||	(FIO2_100_Active == TRUE))
			&& (AlarmNoFio2Sensor == ALARM_FALSE)
			&&	(TIM_ReadDecounterValue(VEN_TIME_CALIB_FIO2) ==0))
		{
/*%C		Alarm is turned to Detected  */
			DB_AlarmStatusWrite(ALARM_MISSING_O2_SUPPLY_U16, ALARM_TRUE);
/*%C  	The Alarm event is sent */
			DB_EventMngt(EVENT_AL_MISSING_O2_SUPPLY);
/*%C		Priority register updating for buzzer and leds command */
			SEC_High_Priority_2	= SEC_High_Priority_2| 0x0020;
		}
	
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :


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
/*%C If the measure O2 pressure is upper or equal to 0.1 bar or, Fio2 is not */
/*%C adjusted or 100%O2 is not in progress, */
/*%C or the calib FIO2 is in progress. */
	   if		(((MeasurePressureO2 >= cO2_MISSING_SUPPLY_THRESHOLD)
	    	||	((Adjust_FIO2 <= cFIO2_MIN_ADJUST)
		 	&&	(FIO2_100_Active == FALSE)))
			|| (AlarmNoFio2Sensor != ALARM_FALSE)
			||	(TIM_ReadDecounterValue(VEN_TIME_CALIB_FIO2) !=0))
	   { 
/*%C		Alarm is turned to False and the associated event is sent*/
			DB_AlarmStatusWrite(ALARM_MISSING_O2_SUPPLY_U16,ALARM_FALSE);
/*%C  	The end of alarm event is sent */
			DB_EventMngt(EVENT_AL_END_MISSING_O2_SUPPLY);
/*%C		Priority register updating for buzzer and leds command */
			SEC_High_Priority_2= SEC_High_Priority_2& 0xFFDF;
	   }		
	   Alarm_Error = NO_ERR_AL;

		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :
		Alarm_Error = ERR_AL_MISSING_O2_SUPPLY;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
	  	Alarm_Error = ERR_AL_MISSING_O2_SUPPLY;
		break;
	}
	return(Alarm_Error);
}