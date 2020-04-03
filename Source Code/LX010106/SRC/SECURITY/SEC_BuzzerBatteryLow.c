/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_BuzzerBatteryLow.c                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C    		  Management of buzzer low battery alarm                      */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Alarm_Error                 						  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "DB_AlarmStatus.h"	
#include "DB_KeyboardEvent.h"
#include "SEC_BuzzerBatteryLow.h"
#include "security_datas.h"
#include "Driver_datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_BuzzerBatteryLow(void)
{
/* Alarm error declaration						                              */
   e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/* Measure buzzer voltage recovery from base                                  */
   UWORD16 MeasureBatteryBuzzerVoltage = DB_ComputeRead(MEASURE_BATTERY_BUZZER_VOLTAGE_U16);
/* Alarm buzzer battery low recovery from base                                */
   UWORD16 AlarmBuzzerBatteryLow = DB_AlarmStatusRead(ALARM_BUZZER_BATTERY_LOW_U16);

/* Cancel request recovery from keyboard event base                           */
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
/* Uncancel command recovery from base                   					  */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);

	UWORD16 AlarmBuzzerBatteryChargeFailure = DB_AlarmStatusRead(ALARM_BUZZER_BATTERY_CHARGE_FAILURE_U16);
/*%C Check ALARM_BUZZER_BATTERY_LOW_U16 state 								  */
switch(AlarmBuzzerBatteryLow)
{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :				  
		if((MeasureBatteryBuzzerVoltage < BATTERY_BUZZER_LOW_VOLTAGE_THRESHOLD)
			&& (AlarmBuzzerBatteryChargeFailure == ALARM_FALSE))
	   {
	  		DB_AlarmStatusWrite(ALARM_BUZZER_BATTERY_LOW_U16 , ALARM_DETECTED);
/*%C 		Associated timer launched										  */
            TIM_StartMinuteDecounter(SEC_LOW_BATTERY_BUZ_READ,
                               TIME_BATTERY_BUZ_READ_MEDIUM,
                               FALSE);
	   }
	Alarm_Error = NO_ERR_AL;
	break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
		if ((MeasureBatteryBuzzerVoltage >= (BATTERY_BUZZER_LOW_VOLTAGE_THRESHOLD + HYSTERESIS_BATTERY_BUZZER_VOLTAGE))
			|| (AlarmBuzzerBatteryChargeFailure >= ALARM_TRUE))
		{
			DB_AlarmStatusWrite(ALARM_BUZZER_BATTERY_LOW_U16 , ALARM_FALSE);
		}
/*%C Else if delay of default is reached 									  */
		else if (TIM_ReadMinuteDecounterValue(SEC_LOW_BATTERY_BUZ_READ) == 0)
		{
			DB_AlarmStatusWrite(ALARM_BUZZER_BATTERY_LOW_U16 , ALARM_TRUE);
/*%C		Associated event is stored 										  */
			DB_EventMngt(EVENT_AL_LOW_BUZZER_BATTERY);
/*%C Priority register updating for buzzer and leds command 				  */
			SEC_Medium_Priority_3 = SEC_Medium_Priority_3 | 0x0400;
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C  The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  */
/*%C  So there is no action to do.											  */
			Alarm_Error = NO_ERR_AL;
			break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
		if ((MeasureBatteryBuzzerVoltage >= (BATTERY_BUZZER_LOW_VOLTAGE_THRESHOLD + HYSTERESIS_BATTERY_BUZZER_VOLTAGE))
			|| (AlarmBuzzerBatteryChargeFailure >= ALARM_TRUE))
		{
			DB_AlarmStatusWrite(ALARM_BUZZER_BATTERY_LOW_U16 , ALARM_FALSE);
/*%C		Associated event is stored 										  */
			DB_EventMngt(EVENT_AL_END_LOW_BUZZER_BATTERY);	
/*%C  		Priority register updating for buzzer and leds command 			  */
			SEC_Medium_Priority_3 = SEC_Medium_Priority_3 & 0xFBFF;
		}

/*%C 	Manual cancelation */
	 	else if (KeyboardDoublePulseInhibEvent == TRUE)
	 	{
/*%C  		ALARM_BUZZER_BATTERY_LOW_U16 = ALARM_CANCELED 					  */
			DB_AlarmStatusWrite(ALARM_BUZZER_BATTERY_LOW_U16 , ALARM_CANCELED);
/*%C  		Priority register updating for buzzer and leds command 			  */
			SEC_Medium_Priority_3 = SEC_Medium_Priority_3 & 0xFBFF; 
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
		if ((MeasureBatteryBuzzerVoltage >= (BATTERY_BUZZER_LOW_VOLTAGE_THRESHOLD + HYSTERESIS_BATTERY_BUZZER_VOLTAGE))
			|| (AlarmBuzzerBatteryChargeFailure >= ALARM_TRUE))
		{
			DB_AlarmStatusWrite(ALARM_BUZZER_BATTERY_LOW_U16 , ALARM_FALSE);
/*%C		Associated event is stored 										  */
			DB_EventMngt(EVENT_AL_END_LOW_BUZZER_BATTERY);	
/*%C  		Priority register updating for buzzer and leds command 			  */
			SEC_Medium_Priority_3 = SEC_Medium_Priority_3 & 0xFBFF;
		}
		else if (UncancelCmd == TRUE)
		{
			DB_AlarmStatusWrite(ALARM_BUZZER_BATTERY_LOW_U16 , ALARM_TRUE);
/*%C  		Priority register updating for buzzer and leds command 			  */
			SEC_Medium_Priority_3 = SEC_Medium_Priority_3 | 0x0400;
		}
/*%C	End if 																  */
/*%C Alarm_Error = NO_ERR_AL												  */		
		Alarm_Error = NO_ERR_AL;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
  	Alarm_Error = ERR_AL_BUZZER_BATTERY_LOW; 
	break;
}
/*%C End of check alarm state												  */
	return(Alarm_Error);
}
