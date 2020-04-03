/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckRemoteAlarm.c                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C             Management of alarm check remote alarm                       */
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
#include "Structure.h"
#include "io_declare.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_KeyboardEvent.h"
#include "SEC_CheckRemoteAlarm.h"
#include "Security_Datas.h"
#include "Driver_datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckRemoteAlarm(void)
{
/* Alarm check remote state recovery from alarm status base                   */
	UWORD16 AlarmCheckRemoteAlarm = DB_AlarmStatusRead(ALARM_CHECK_REMOTE_ALARM_U16);
/* Buzzer command state recovery from control base                            */
	UWORD16 Buzzer_Cmd = DB_ControlRead(BUZZER_CMD_U16);	
/* Cancel request recovery from keyboard event base                           */
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
/* Uncancel recovery from control base                                        */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

/*%C Check ALARM_CHECK_REMOTE_ALARM_U16 state								  */
switch(AlarmCheckRemoteAlarm)
{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C  If ALARM_REMOTE_STATE <> BUZZER_CMD_U16 or ALARM_CheckRemoteFlag = TRUE */
		if ( (ALARM_REMOTE_STATE != Buzzer_Cmd) 
		  || (ALARM_CheckRemoteFlag == TRUE) ) 
		{
/*%C		Then 	ALARM_CHECK_REMOTE_ALARM_U16 = ALARM_DETECTED  			  */
			DB_AlarmStatusWrite(ALARM_CHECK_REMOTE_ALARM_U16,
			 						  ALARM_DETECTED);
/*%C	   Timer delay launch  	            								  */
			TIM_StartDecounter(SEC_CHECK_REMOTE,
									 TIME_CHECK_REMOTE);
		}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL												  */ 
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C  If ALARM_REMOTE_STATE = BUZZER_CMD_U16 and ALARM_CheckRemoteFlag = FALSE*/
		if ( (ALARM_REMOTE_STATE == Buzzer_Cmd) 
		  && (ALARM_CheckRemoteFlag == FALSE) )
		{
/*%C	 Then ALARM_CHECK_REMOTE_ALARM_U16 = ALARM_FALSE 					  */
			DB_AlarmStatusWrite(ALARM_CHECK_REMOTE_ALARM_U16,
			 						  ALARM_FALSE);
		}
		else
		{
/*%C  Else 																	  */
/*%C		if timer reached delay, then 									  */
			if (TIM_ReadDecounterValue(SEC_CHECK_REMOTE) == 0)
			{
/*%C			ALARM_CHECK_REMOTE_ALARM_U16 = ALARM_TRUE           		  */
				DB_AlarmStatusWrite(ALARM_CHECK_REMOTE_ALARM_U16,
				 						ALARM_TRUE);
/*%C			Associated event is stored									  */
				DB_EventMngt(EVENT_AL_CHECK_REMOTE_ALARM);
/*%C			Updating priority register									  */
				SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0010;		  
			}
/*%C		End if 															  */
		}
/*%C	End if 																  */
/*%C Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 		  */
/*%C So there is no action to do.											  */
/*%C Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C No auto cancelation available for this alarm, only manual cancelation 	  */
/*%C If KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE, then 					  */
	 	if (KeyboardDoublePulseInhibEvent == TRUE ) 
 		{
/*%C	  ALARM_CHECK_REMOTE_ALARM_U16 = ALARM_CANCELED						  */
			DB_AlarmStatusWrite(ALARM_CHECK_REMOTE_ALARM_U16,
									ALARM_CANCELED);
/*%C     Priority register updating for buzzer and leds command 			  */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 & 0xFFEF;
		}
/*%C	End if 																  */
/*%C Alarm_Error = NO_ERR_AL												  */
	 	Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :

/*%C 	If UNCANCEL_CMD_U16 = TRUE 											  */
		if(UncancelCmd == TRUE)
		{
/*%C 	 ALARM_CHECK_REMOTE_ALARM_U16 = ALARM_TRUE							  */
/*%C	Priority register updating for buzzer and leds command 				  */
			DB_AlarmStatusWrite(ALARM_CHECK_REMOTE_ALARM_U16,
									ALARM_TRUE);
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0010;
		}
/*%C	End if 																  */
/*%C Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C Alarm_Error = ERR_AL_CHECK_REMOTE_ALARM								  */
		Alarm_Error = ERR_AL_CHECK_REMOTE_ALARM;
		break;
	}
/*%C End check alarm stae													  */
	return(Alarm_Error);
}
