/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckBuzzer.c                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                 Management of check buzzer alarm                         */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Alarm_Error											  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_config.h"
#include "DB_AlarmStatus.h"				  
#include "DB_Control.h"
#include "DB_KeyboardEvent.h"
#include "SEC_CheckBuzzer.h"
#include "security_datas.h"
#include "Driver_datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckBuzzer(void)
{
/* fudge factor used when driving both alarms the measured values are now 
   15 percent lower */
#define FUDGE_FACTOR	(15/100)

/* Alarm error declaration						                              */
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL ;
/* Alarm check buzzer 					                                      */
	UWORD16 AlarmCheckBuzzer = DB_AlarmStatusRead(ALARM_CHECK_BUZZER_U16);
/* Control buzzer recovery from base                   		                  */
	UWORD16 ControlBuzzer = DB_ControlRead(CONTROL_BUZZER_U16);
/* Measure buzzer voltage 													  */
	SWORD16 MeasureBuzzerVoltage = (SWORD16)(DB_ComputeRead(MEASURE_BUZZER_VOLTAGE_U16));
/*%C  Sound level recovery from config base									  */
	UWORD16	SoundLevel = DB_ConfigRead(SOUND_LEVEL_SELECT_U16);
//#define TRESHOLD_DETECTION_ACCORDING_TO_SELECTED_LEVEL
/* (((sound setting - sound mini (20%)) * 6.2) +offset mini (100))	  */
	SWORD16 BuzzerLowVoltageThreshold = ((((SoundLevel- 20 )*62)/10)+ 100);
	BuzzerLowVoltageThreshold = BuzzerLowVoltageThreshold - (BuzzerLowVoltageThreshold * FUDGE_FACTOR); 
/*%C Check ALARM_CHECK_BUZZER_U16 state 						   			  */	
	switch(AlarmCheckBuzzer)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
		case ALARM_FALSE :				  
/*%C  If  MEASURE_BUZZER_VOLTAGE_U16 < BuzzerLowVoltageThreshold 			  */
/*%C  and CONTROL_BUZZER_U16 = TRUE or ALARM_CheckBuzzerFlag = TRUE, 		  */
/*%C  then									  	  						 	  */
			if ( (MeasureBuzzerVoltage < BuzzerLowVoltageThreshold)
		 	  && (ControlBuzzer == TRUE)
			  || ALARM_CheckBuzzerFlag == TRUE )
		   	{
/*%C 			ALARM_CHECK_BUZZER_U16 = ALARM_DETECTED						  */
		  		DB_AlarmStatusWrite(ALARM_CHECK_BUZZER_U16 , ALARM_DETECTED);
/*%C 			Associated timer is launched 								  */
				TIM_StartDecounter(SEC_BUZ_READ , TIME_BATTERY_BUZ_READ_SHORT);
		  	}
/*%C		End if 															  */
/*%C Alarm_Error = NO_ERR_AL												  */
		   	Alarm_Error = NO_ERR_AL;
		   	break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
		case ALARM_DETECTED :
/*%C  If MEASURE_BUZZER_VOLTAGE_U16 >= BuzzerLowVoltageThreshold + 			  */
/*%C  HYSTERESIS_BUZZER_VOLTAGE and ALARM_CheckBuzzerFlag = FALSE, then  	  */
			if ( (MeasureBuzzerVoltage >= BuzzerLowVoltageThreshold + HYSTERESIS_BUZZER_VOLTAGE)
		 	  && (ALARM_CheckBuzzerFlag == FALSE ))
			{
/*%C 			ALARM_CHECK_BUZZER_U16 = ALARM_FALSE						  */
				DB_AlarmStatusWrite(ALARM_CHECK_BUZZER_U16 , ALARM_FALSE);
			}
/*%C Else if timer reached delay, then 										  */
			else if (TIM_ReadDecounterValue(SEC_BUZ_READ) == 0)
			{
/*%C 			ALARM_CHECK_BUZZER_U16 = ALARM_TRUE 						  */
				DB_AlarmStatusWrite(ALARM_CHECK_BUZZER_U16 , ALARM_TRUE);
/*%C			Associated event is stored 									  */
				DB_EventMngt(EVENT_AL_CHECK_BUZZER);
/*%C 			Priority register updating for buzzer and leds command 		  */
				SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | 0x1000;
			}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL												  */
			Alarm_Error = NO_ERR_AL;
			break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
		case ALARM_TRUE :
/*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  	  */
/*%C So there is no action to do.											  */
/*%C Alarm_Error = NO_ERR_AL												  */
			Alarm_Error = NO_ERR_AL;
			break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
		case ALARM_DISPLAYED	:
/*%C Alarm_Error = NO_ERR_AL												  */		
			Alarm_Error = NO_ERR_AL;
			break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
		case ALARM_CANCELED :
/*%C Alarm_Error = ERR_AL_CHECK_BUZZER										  */
			Alarm_Error = ERR_AL_CHECK_BUZZER;
			break;
	
/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
		default:
/*%C Alarm_Error = ERR_AL_CHECK_BUZZER 										  */
		  	Alarm_Error = ERR_AL_CHECK_BUZZER; 
			break;
	}
/*%C End of check alarm state 												  */
	return(Alarm_Error);
}
