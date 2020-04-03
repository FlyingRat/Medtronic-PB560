/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Failure24V.c	                       								*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   					Management of 24v supply alarm			                  */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter :	Alarm_Error  														*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Event.h"
#include "DB_Control.h"
#include "DB_AlarmStatus.h"
#include "DB_PowerSupply.h"
#include "security_datas.h"
#include "SEC_Failure24V.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_Failure24V(void)
{
/* Alarm failure 24V state recovery from base      			                  */
	e_DB_ALARMS_STATE Alarm_Failure_24V =
								DB_AlarmStatusRead(ALARM_FAILURE_24V_U16);
/* Failure 24V flag flag information from power supply base  			         */
	UWORD16 Failure_24V_Flag =
								DB_PowerSupplyRead(FAILURE_24V_FLAG_U16);
/* Alarm error declaration					                  		               */
 	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;


switch(Alarm_Failure_24V)
{
/******************************************************************************/
/*%C	         					 "FALSE" State                                  */
/******************************************************************************/
	case ALARM_FALSE :
/*%C  The 24V alarm is detected if the corresponding flag in the power supply	*/
/*%C  base is set 											      		               */
		if (Failure_24V_Flag == TRUE)
		{
			DB_AlarmStatusWrite(ALARM_FAILURE_24V_U16, ALARM_DETECTED);
		}
	   Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					               */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C  The alarm is set to TRUE immediatly  */
      DB_AlarmStatusWrite(ALARM_FAILURE_24V_U16, ALARM_TRUE);
/*%C  Associated event management                                 */
      DB_EventMngt(EVENT_AL_FAILURE_24V);
/*%C	Priority register updating for buzzer and leds command */
       SEC_High_Priority_1= SEC_High_Priority_1| 0x0400;
	   Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "TRUE" State												*/
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
/*%C 	The 24V alarm is cancelled if the corresponding flag in the power supply*/
/*%C 	base is not set 									           		               */
		if (Failure_24V_Flag == FALSE)
		{
/*%C  	The alarm is set to TRUE immediatly  */
			DB_AlarmStatusWrite(ALARM_FAILURE_24V_U16, ALARM_FALSE);
/*%C  	Associated end event management                                 */
	      DB_EventMngt(EVENT_AL_END_FAILURE_24V);
/*%C		Priority register updating for buzzer and leds command */
      	  SEC_High_Priority_1= SEC_High_Priority_1& 0xFBFF;
		}
	   Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C 	No canceled state possible*/
		Alarm_Error = ERR_AL_FAILURE_24V;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
/*%C 	function return = error	*/
	  	Alarm_Error = ERR_AL_FAILURE_24V;
		break;
	}
	return(Alarm_Error);
}
