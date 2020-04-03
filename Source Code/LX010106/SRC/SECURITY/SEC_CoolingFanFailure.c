/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CoolingFanFailure.c                                		  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   					Management of cooling fan alarm		                  */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter :	Alarm_Error  										  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Event.h"
#include "DB_Control.h"
#include "DB_KeyboardEvent.h"
#include "DB_AlarmStatus.h"
#include "DB_PowerSupply.h"
#include "security_datas.h"
#include "SEC_CoolingFanFailure.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CoolingFanFailure(void)
{
/*%C Alarm cooling fan state recovery from base                               */
	e_DB_ALARMS_STATE Alarm_Cooling_Fan =
								DB_AlarmStatusRead(ALARM_COOLING_FAN_U16);
/*%C Cooling fan failure information from power supply base                   */
	UWORD16 Cooling_Fan_Failure_Flag =
								DB_PowerSupplyRead(COOLING_FAN_FAILURE_FLAG_U16);
/*%C Cancel request recovery from keyboard event base                         */
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
/*%C Uncancel command recovery from base                             	      */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);					  
/*%C Alarm error declaration					                  		      */
 	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

/*%C Check ALARM_COOLING_FAN_U16 state					   					  */
switch(Alarm_Cooling_Fan)
{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C  If COOLING_FAN_FAILURE_FLAG_U16 = TRUE, then 							  */
		if (Cooling_Fan_Failure_Flag == TRUE)
		{
/*%C	  ALARM_COOLING_FAN_U16 = ALARM_DETECTED 							  */	
			DB_AlarmStatusWrite(ALARM_COOLING_FAN_U16, ALARM_DETECTED);
		}
/*%C	End if 																  */
/*%C  Alarm_Error = NO_ERR_AL												  */
	   Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C  The alarm is set to TRUE immediatly  									  */
/*%C  ALARM_COOLING_FAN_U16 = ALARM_DETECTED 							  	  */
      DB_AlarmStatusWrite(ALARM_COOLING_FAN_U16, ALARM_TRUE);
/*%C  Associated event management                                 			  */
      DB_EventMngt(EVENT_AL_COOLING_FAN);
/*%C  Priority register updating for buzzer and leds command 				  */
      SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0200;
/*%C  Alarm_Error = NO_ERR_AL												  */
	   Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C  The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  */
/*%C  So there is no action to do.											  */
/*%C  Alarm_Error = NO_ERR_AL												  */
	   Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED :

/*%C  If COOLING_FAN_FAILURE_FLAG_U16 = FALSE, then 						  */
		if (Cooling_Fan_Failure_Flag == FALSE)
		{
/*%C  	ALARM_COOLING_FAN_U16 = ALARM_FALSE									  */
			DB_AlarmStatusWrite(ALARM_COOLING_FAN_U16, ALARM_FALSE);
/*%C	Priority register updating for buzzer and leds command 				  */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 & 0xFDFF;
/*%C  	Associated end event management                                 	  */
      	    DB_EventMngt(EVENT_AL_END_COOLING_FAN);
		}
/*%C   End if 																  */

/*%C  If KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 =  TRUE, then 				  */
	   if (KeyboardDoublePulseInhibEvent == TRUE )
 	   {
/*%C	ALARM_COOLING_FAN_U16 = ALARM_CANCELED								  */
		    DB_AlarmStatusWrite(ALARM_COOLING_FAN_U16, ALARM_CANCELED);
/*%C	Priority register updating for buzzer and leds command 			  */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 & 0xFDFF;
	   }
/*%C	End if 																  */
/*%C  Alarm_Error = NO_ERR_AL												  */
       Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :

/*%C  If COOLING_FAN_FAILURE_FLAG_U16 = FALSE, then 						  */
		if (Cooling_Fan_Failure_Flag == FALSE)
		{
/*%C		ALARM_COOLING_FAN_U16 = ALARM_FALSE								  */
			DB_AlarmStatusWrite(ALARM_COOLING_FAN_U16, ALARM_FALSE);
/*%C  		Associated end event management                                   */
  	    	DB_EventMngt(EVENT_AL_END_COOLING_FAN);
		}
/*%C	End if 																  */
		/******************************************************************/
		/*		 				Reset of the "CANCELED" State             */
		/******************************************************************/

/*%C  If an uncancel command is detected, the alarm goes back to the TRUE */
/*%C  state */
		if (UncancelCmd == TRUE)
		{
/*%C 		Storage of True state of the alarm*/
	   	    DB_AlarmStatusWrite(ALARM_COOLING_FAN_U16, ALARM_TRUE);
/*%C		Priority register updating for buzzer and leds command */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0200;
		}
/*%C	End if 																  */ 
/*%C  Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C  function return = error												  */
/*%C  Alarm_Error = ERR_AL_COOLING_FAN										  */
	  	Alarm_Error = ERR_AL_COOLING_FAN;
		break;
	}
/*%C	End of check alarm 													  */
	return(Alarm_Error);
}
