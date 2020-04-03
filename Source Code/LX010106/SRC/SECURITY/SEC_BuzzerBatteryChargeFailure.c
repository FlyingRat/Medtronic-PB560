/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_SEC_BuzzerBatteryChargeFailure.c	   			              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C    management of the alarm buzzer battery charge failure                 */
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
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"	
#include "SEC_BuzzerBatteryChargeFailure.h"
#include "security_datas.h"
#include "Driver_datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
 e_ALARM_ERROR SEC_BuzzerBatteryChargeFailure(void)
{

/* Alarm error declaration						                              */
   e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

/* Alarm buzzer battery charge failure recovery from base                     */
   UWORD16 AlarmBuzzerBatteryChargeFailure = DB_AlarmStatusRead(ALARM_BUZZER_BATTERY_CHARGE_FAILURE_U16);

/* Measure buzzer voltage recovery from base                                  */
   UWORD16 MeasureBatteryBuzzerVoltage = DB_ComputeRead(MEASURE_BATTERY_BUZZER_VOLTAGE_U16);
/*%C	Check ALARM_BUZZER_BATTERY_CHARGE_FAILURE_U16 state 				  */	
	switch(AlarmBuzzerBatteryChargeFailure)			
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
		if( (MeasureBatteryBuzzerVoltage < BATTERY_BUZZER_LOW_VOLTAGE_THRESHOLD) )
		{
	      	DB_AlarmStatusWrite(ALARM_BUZZER_BATTERY_CHARGE_FAILURE_U16, ALARM_DETECTED);
/*%C 		Associated timer is launched 									  */
			TIM_StartMinuteDecounter(SEC_BATTERY_FAILURE_CHARGE_BUZ_READ,
								 TIME_BATTERY_BUZ_READ_LONG,
								 FALSE);
		}
		Alarm_Error = NO_ERR_AL;			   
		break;									  
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
		if ( (MeasureBatteryBuzzerVoltage >= (BATTERY_BUZZER_LOW_VOLTAGE_THRESHOLD + HYSTERESIS_BATTERY_BUZZER_VOLTAGE)) )
		{
			DB_AlarmStatusWrite(ALARM_BUZZER_BATTERY_CHARGE_FAILURE_U16 , ALARM_FALSE);
		}
		
/*%C 	Else if delay of default reached, then 								  */
		else if (TIM_ReadMinuteDecounterValue(SEC_BATTERY_FAILURE_CHARGE_BUZ_READ) == 0)
		{
			DB_AlarmStatusWrite(ALARM_BUZZER_BATTERY_CHARGE_FAILURE_U16 , ALARM_TRUE);
			DB_EventMngt(EVENT_AL_BUZZER_BATTERY_CHARGE_FAILURE);
/*%C 		Priority register updating for buzzer and leds command 			  */
			SEC_High_Priority_2 = SEC_High_Priority_2 | 0x0002;
		}
/*%C	End if 																  */
/*%C	Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 		  */
/*%C So there is no action to do.											  */
/*%C	Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
		if ( (MeasureBatteryBuzzerVoltage >= (BATTERY_BUZZER_LOW_VOLTAGE_THRESHOLD + HYSTERESIS_BATTERY_BUZZER_VOLTAGE)) )
		{
			DB_AlarmStatusWrite(ALARM_BUZZER_BATTERY_CHARGE_FAILURE_U16 , ALARM_FALSE);
			DB_EventMngt(EVENT_AL_END_BUZZER_BATTERY_CHARGE_FAILURE);	
/*%C 		Priority register updating for buzzer and leds command 			  */
			SEC_High_Priority_2 = SEC_High_Priority_2 & 0xFFFD;
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
		Alarm_Error = ERR_AL_BUZZER_BATTERY_CHARGE_FAILURE;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
	  	Alarm_Error = ERR_AL_BUZZER_BATTERY_CHARGE_FAILURE;
		break;
	}
/*%C End of check alarm state 												  */
	return(Alarm_Error);
}

