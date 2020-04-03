/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckSettings.c                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C  			Management of alarm check settings                            */
/*     								 	                                      */
/*																		  	  */
/*																			  */
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
#include "DB_KeyboardEvent.h"
#include "DB_Event.h"
#include "DB_Control.h"
#include "DB_AlarmStatus.h"
#include "SEC_CheckSettings.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_CheckSettings(void) 
{
/* Alarm check settings recovery from base 									  */
	UWORD16 AlarmCheckSettings = DB_AlarmStatusRead(ALARM_CHECK_SETTINGS_U16);
/* Cancel request recovery from keyboard event base                           */
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
/* Uncancel recovery from control base                                        */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);

/*%C If KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE, then 	  			  	  */
	if (KeyboardDoublePulseInhibEvent == TRUE )
	{ 
/*%C	if ALARM_CHECK_SETTINGS_U16 = ALARM_DISPLAYED						  */
		if (AlarmCheckSettings == ALARM_DISPLAYED)
		{
/*%C 	 Then ALARM_CHECK_SETTINGS_U16 = ALARM_CANCELED 					  */
			DB_AlarmStatusWrite(ALARM_CHECK_SETTINGS_U16,
	      						  ALARM_CANCELED);
/*%C		Priority register updating for buzzer and leds command 			  */
/*%C		Bit 12, 13 and 14 of the medium priority 2 word 				  */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 & 0x8FFF;
		}
/*%C   End if				  												  */
	}
/*%C End if																	  */
	/******************************************************************/
	/*		 				Reset of the "CANCELED" State             */
	/******************************************************************/
			 
/*%C If UNCANCEL_CMD_U16 = TRUE and ALARM_CHECK_SETTINGS_U16 = ALARM_CANCELED */
	if ( (UncancelCmd == TRUE)
	  && (AlarmCheckSettings == ALARM_CANCELED) )
	{
/*%C 	Then ALARM_CHECK_SETTINGS_U16 = ALARM_TRUE							  */
/*%C	Priority register updating for buzzer and leds command 				  */
   		DB_AlarmStatusWrite(ALARM_CHECK_SETTINGS_U16,
   							  ALARM_TRUE);
		SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x7000;
	}
/*%C End if																	  */
}