/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckBattery.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Management of check battery alarm   				                  	  */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter :	Alarm_Error 										  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "DB_PowerSupply.h"
#include "SEC_CheckBattery.h"
#include "security_datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckBattery(void)
{
	e_DB_ALARMS_STATE AlarmCheckBattery =
								DB_AlarmStatusRead(ALARM_CHECK_BATTERY_U16);
	e_DB_ALARMS_STATE AlarmCheckSupply =
								DB_AlarmStatusRead(ALARM_CHECK_SUPPLY_U16);

 	UWORD16 BatKo = DB_PowerSupplyRead(BAT_KO_U16);	

 	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

switch(AlarmCheckBattery)
{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C If BAT_KO_U16 = TRUE and ALARM_CHECK_SUPPLY_U16 = FALSE, then 			  */
		if ( (BatKo == TRUE)
		  && (AlarmCheckSupply == FALSE) )
		{
/*%C  ALARM_CHECK_BATTERY_U16 = ALARM_TRUE									  */		
			DB_AlarmStatusWrite(ALARM_CHECK_BATTERY_U16, ALARM_TRUE);
/*%C  The associated event is stored 										  */		
			DB_EventMngt(EVENT_AL_CHECK_BATTERY);
/*%C  Priority register updating for buzzer and leds command 				  */
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | 0x0400;
		}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 									  			  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C Alarm_Error = ERR_AL_CHECK_BATTERY 									  */
		Alarm_Error = ERR_AL_CHECK_BATTERY;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 		  */
/*%C So there is no action to do.											  */
/*%C Alarm_Error = NO_ERR_AL 									  			  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C If BAT_KO_U16 = FALSE or ALARM_CHECK_SUPPLY_U16 >= TRUE, then 			  */
		if ( (BatKo == FALSE)
		  || (AlarmCheckSupply >= TRUE) )
		{
/*%C  ALARM_CHECK_BATTERY_U16 = ALARM_FALSE 								  */	
			DB_AlarmStatusWrite(ALARM_CHECK_BATTERY_U16, ALARM_FALSE);
/*%C	Associated event is stored											  */
			DB_EventMngt(EVENT_AL_END_OF_CHECK_BATTERY);	
/*%C  Priority register updating for buzzer and leds command 				  */
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xFBFF;
		}
/*%C End if 															 	  */
/*%C Alarm_Error = NO_ERR_AL 									  			  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C Alarm_Error = ERR_AL_CHECK_BATTERY 									  */
		Alarm_Error = ERR_AL_CHECK_BATTERY;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C Alarm_Error = ERR_AL_CHECK_BATTERY 									  */
		Alarm_Error = ERR_AL_CHECK_BATTERY;
		break;
}
/*%C End of check alarm state 												  */
	return(Alarm_Error);
}
