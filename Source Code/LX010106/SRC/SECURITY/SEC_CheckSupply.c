/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckSupply.c                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   				Management of check supply alarm 			              */
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
#include "DB_Control.h"
#include "DB_KeyboardEvent.h"
#include "SEC_CheckSupply.h"
#include "security_datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckSupply(void)
{
	e_DB_ALARMS_STATE AlarmCheckSupply =
								DB_AlarmStatusRead(ALARM_CHECK_SUPPLY_U16);
 	UWORD16 SupplyBusFailure = DB_ControlRead(SUPPLY_BUS_FAILURE_U16);
/*%C Cancel request recovery from keyboard event base                         */
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
 	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/*%C Uncancel recovery from control base                                      */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
/*%C Check 	ALARM_CHECK_SUPPLY_U16 state 									  */
	switch(AlarmCheckSupply)			
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C 	if SUPPLY_BUS_FAILURE_U16 = TRUE, then 								  */
		if (SupplyBusFailure == TRUE)
		{
/*%C 		ALARM_CHECK_SUPPLY_U16 = ALARM_TRUE, associated event is stored   */
			DB_AlarmStatusWrite(ALARM_CHECK_SUPPLY_U16, ALARM_TRUE);
			DB_EventMngt(EVENT_AL_CHECK_SUPPLY);
/*%C		Priority register updating for buzzer and leds command 			  */
		 	SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | 0x0200;
		}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
	Alarm_Error = ERR_AL_CHECK_SUPPLY;
/*%C Alarm_Error = ERR_AL_CHECK_SUPPLY 										  */
	break;
/******************************************************************************/
/*%C	         					 "TRUE" State					   		  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  	  */
/*%C  So there is no action to do .											  */
/*%C Alarm_Error = NO_ERR_AL 												  */
	Alarm_Error = NO_ERR_AL;
	break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C 	if SUPPLY_BUS_FAILURE_U16 = FALSE, then 							  */
	if (SupplyBusFailure == FALSE)
	{
/*%C 	Alarm ALARM_CHECK_SUPPLY_U16 = ALARM_FALSE, associated event is sent  */
	    DB_AlarmStatusWrite(ALARM_CHECK_SUPPLY_U16, ALARM_FALSE);
	  	DB_EventMngt(EVENT_AL_END_OF_CHECK_SUPPLY);
/*%C	Priority register updating for buzzer and leds command 				  */
	 	SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xFDFF;
	}
/*%C Else if KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE 					  */
	else if (KeyboardDoublePulseInhibEvent == TRUE )
 	{
/*%C 	then ALARM_CHECK_SUPPLY_U16 =  ALARM_CANCELED 						  */
		DB_AlarmStatusWrite(ALARM_CHECK_SUPPLY_U16, ALARM_CANCELED);
/*%C	Priority register updating for buzzer and leds command 				  */
	 	SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xFDFF;
	}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
	Alarm_Error = NO_ERR_AL;
	break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C 	if SUPPLY_BUS_FAILURE_U16 = FALSE, then 							  */
		if (SupplyBusFailure == FALSE)
		{
/*%C 	 Then ALARM_CHECK_SUPPLY_U16 = ALARM_FALSE, associated event stored   */
		  	DB_AlarmStatusWrite(ALARM_CHECK_SUPPLY_U16, ALARM_FALSE);
		  	DB_EventMngt(EVENT_AL_END_OF_CHECK_SUPPLY);
		}

		/******************************************************************/
		/*		 				Reset of the "CANCELED" State             */
		/******************************************************************/
			 
/*%C  Else If UNCANCEL_CMD_U16 = TRUE 										  */
/*%C  then 								   									  */
		else if (UncancelCmd == TRUE)
		{
/*%C 		ALARM_CHECK_SUPPLY_U16 = ALARM_TRUE								  */
/*%C		Priority register updating for buzzer and leds command 			  */
	   	    DB_AlarmStatusWrite(ALARM_CHECK_SUPPLY_U16,
	   							  ALARM_TRUE);
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | 0x0200;
		}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
	  	Alarm_Error = ERR_AL_CHECK_SUPPLY;
/*%C Alarm_Error = ERR_AL_CHECK_SUPPLY 										  */
		break;
	}
/*%C End of Check Alarm state												  */
	return(Alarm_Error);
}


