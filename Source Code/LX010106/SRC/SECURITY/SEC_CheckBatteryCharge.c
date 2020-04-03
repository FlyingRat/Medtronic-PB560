/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckBatteryCharge.c 		                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C    management of the alarm Check battery charge		                  */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Alarm_Error                                           */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "DB_KeyboardEvent.h"
#include "DB_Control.h"
#include "DB_PowerSupply.h"
#include "SEC_CheckBatteryCharge.h"	  
#include "security_datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
 e_ALARM_ERROR SEC_CheckBatteryCharge(void)
{
/* Alarm check supply recovery from base	                                  */
	e_DB_ALARMS_STATE AlarmCheckSupply 
									= DB_AlarmStatusRead(ALARM_CHECK_SUPPLY_U16);
/* Alarm check battery charge recovery from base	                          */
   UWORD16 AlarmCheckBatteryCharge 	
   								= DB_AlarmStatusRead(ALARM_CHECK_BATTERY_CHARGE_U16);
/* Charge OK state recovery from base	                           			  */
 	UWORD16 ChargeKo 			= DB_PowerSupplyRead(CHARGE_KO_U16);	
/* Alarm error declaration									                  */
 	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/* Uncancel recovery from control base                                        */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);


switch(AlarmCheckBatteryCharge)			
{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C If ALARM_CHECK_SUPPLY_U16 = ALARM_FALSE and CHARGE_KO_U16 = TRUE, then   */
	if ( (AlarmCheckSupply == ALARM_FALSE)
	  && (ChargeKo == TRUE) )
	{
/*%C  ALARM_CHECK_BATTERY_CHARGE_U16 = ALARM_TRUE 							  */	
		DB_AlarmStatusWrite(ALARM_CHECK_BATTERY_CHARGE_U16, ALARM_TRUE);
/*%C  Associated event is stored											  */	
		DB_EventMngt(EVENT_AL_CHECK_BATTERY_CHARGE);

/*%C  Priority register updating for buzzer and leds command 				  */
		SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0040;
	}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL											  	  */
	Alarm_Error = NO_ERR_AL;			   
	break;									  
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C Alarm_Error = ERR_AL_CHECK_BATTERY_CHARGE							  	  */
	Alarm_Error = ERR_AL_CHECK_BATTERY_CHARGE;
	break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 		  */
/*%C So there is no action to do.											  */
/*%C Alarm_Error = NO_ERR_AL											  	  */
	Alarm_Error = NO_ERR_AL;
	break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C If ALARM_CHECK_SUPPLY_U16 <> ALARM_FALSE or CHARGE_KO_U16 = FALSE, then  */
	if ( (AlarmCheckSupply != ALARM_FALSE)
	  || (ChargeKo == FALSE) )
	{
/*%C  ALARM_CHECK_BATTERY_CHARGE_U16 = ALARM_FALSE 							  */	
		DB_AlarmStatusWrite(ALARM_CHECK_BATTERY_CHARGE_U16, ALARM_FALSE);
/*%C  Associated event is stored 											  */
		DB_EventMngt(EVENT_AL_END_OF_CHECK_BATTERY_CHARGE);
/*%C  Priority register updating for buzzer and leds command 				  */
		SEC_Medium_Priority_2 = SEC_Medium_Priority_2 & 0xFFBF;
 	}
/*%C Else if KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE, then 			  */
	else if (KeyboardDoublePulseInhibEvent == TRUE)
	{
/*%C	ALARM_CHECK_BATTERY_CHARGE_U16 = ALARM_CANCELED						  */
		DB_AlarmStatusWrite(ALARM_CHECK_BATTERY_CHARGE_U16, ALARM_CANCELED);

/*%C  Priority register updating for buzzer and leds command 				  */
		SEC_Medium_Priority_2 = SEC_Medium_Priority_2 & 0xFFBF;
	}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL											  	  */
	Alarm_Error = NO_ERR_AL;
	break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C If ALARM_CHECK_SUPPLY_U16 <> ALARM_FALSE or CHARGE_KO_U16 = FALSE, then  */
	if ( (AlarmCheckSupply != ALARM_FALSE)
     || (ChargeKo == FALSE) )
	{
/*%C  ALARM_CHECK_BATTERY_CHARGE_U16 = ALARM_FALSE 							  */	
		DB_AlarmStatusWrite(ALARM_CHECK_BATTERY_CHARGE_U16, ALARM_FALSE);
/*%C  Associated event is stored 											  */	
		DB_EventMngt(EVENT_AL_END_OF_CHECK_BATTERY_CHARGE);
 	}
		/******************************************************************/
		/*		 				Reset of the "CANCELED" State             */
		/******************************************************************/
			 
/*%C Else if UNCANCEL_CMD_U16 = TRUE, then  								  */
	else if(UncancelCmd == TRUE)
	{
/*%C  ALARM_CHECK_BATTERY_CHARGE_U16 = ALARM_TRUE 							  */
		DB_AlarmStatusWrite(ALARM_CHECK_BATTERY_CHARGE_U16,
   							  ALARM_TRUE);
/*%C  Priority register updating for buzzer and leds command 				  */
		SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0040;
	}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL							  	  			 	  */
	Alarm_Error = NO_ERR_AL;
	break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C Alarm_Error = ERR_AL_CHECK_BATTERY_CHARGE							  	  */
  	Alarm_Error = ERR_AL_CHECK_BATTERY_CHARGE;
	break;
}
/*%C End of check alarm 													  */
	return(Alarm_Error);
}

