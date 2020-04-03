/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_KeyboardDefault.c                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Keyboard default (too long push on key(s)                      */
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
#include "DB_Event.h"
#include "enum.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "SEC_KeyboardDefault.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_KeyboardDefault(void)
{
/* Alarm keyboard recovery from base				 						  */
UWORD16 Alarm_Keyboard_Default
								 = DB_AlarmStatusRead(ALARM_KEYBOARD_DEFAULT_U16);
/* Keyboard Anomalie recovery from base				 						  */
UWORD16 KeyboardAnomalie = DB_ControlRead(KEYBOARD_ANOMALIE_U16);

/*%C If KEYBOARD_ANOMALIE_U16 = TRUE and 					 				  */
/*%C ALARM_KEYBOARD_DEFAULT_U16 <> ALARM_TRUE and 			 				  */
/*%C ALARM_KEYBOARD_DEFAULT_U16 <> ALARM_DISPLAYED		 	 				  */
   if ( (KeyboardAnomalie == TRUE)
     && (Alarm_Keyboard_Default != ALARM_TRUE) 
     && (Alarm_Keyboard_Default != ALARM_DISPLAYED) ) 
   {
/*%C 	Then ALARM_KEYBOARD_DEFAULT_U16 = ALARM_TRUE, associated event stored    */
      	DB_AlarmStatusWrite(ALARM_KEYBOARD_DEFAULT_U16,
                          ALARM_TRUE);
     	DB_EventMngt(EVENT_AL_KEYBOARD );
/*%C  Priority register update 												  */
      	SEC_High_Priority_1= SEC_High_Priority_1| 0x0200;
   }
/*%C End if												 	 				  */
/*%C If KEYBOARD_ANOMALIE_U16 = FALSE and 					 				  */
/*%C (ALARM_KEYBOARD_DEFAULT_U16 = ALARM_TRUE or 			 				  */
/*%C ALARM_KEYBOARD_DEFAULT_U16 = ALARM_DISPLAYED )		 	 				  */
	if ( (KeyboardAnomalie == FALSE) 
	  && ( (Alarm_Keyboard_Default == ALARM_TRUE)
	    || (Alarm_Keyboard_Default == ALARM_DISPLAYED) ) ) 
/*%C  Then	ALARM_KEYBOARD_DEFAULT_U16 = ALARM_FALSE, associated event stored 	  */
	{
      	DB_AlarmStatusWrite(ALARM_KEYBOARD_DEFAULT_U16,
      	                 ALARM_FALSE);		
     	DB_EventMngt(EVENT_AL_END_KEYBOARD );
/*%C  Priority register update 												  */
		SEC_High_Priority_1= SEC_High_Priority_1& 0xFDFF;
   }
/*%C End if																	  */
}   