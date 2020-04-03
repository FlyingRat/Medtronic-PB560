/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_LedCmd.c                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  This function commands the leds, function of level alarm                */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   Led_Cmd_Type                                        */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Control.h"
#include "SEC_LedCmd.h"
void SEC_LedCmd(e_DB_ALARM_LEVEL_PRIORITY Led_Command_Type)
{
   static e_DB_ALARM_LEVEL_PRIORITY Led_Command_Type_Memo = WP;
   UWORD16 High_Pressure_Led_Reminder = 
                              DB_ControlRead(HIGH_PRESSURE_LED_REMINDER_U16);
   static UWORD16 Previous_High_Pressure_Led_Reminder = FALSE;
/*%C If no high pressure alarm detected, led command function of command type */
   if (High_Pressure_Led_Reminder != TRUE)
   {
/*%C 	Previous high pressure led reminder initialization */
		Previous_High_Pressure_Led_Reminder = FALSE;
/*%C 	Led command, function of alarm level */
      switch(Led_Command_Type)
	   {
/*%C  	High priority Led command  */
         case HP:
		   {
/*%C     	If it's the first time in HP alarm, leds are commanded  */
/*%C     	in order to launch the sequence once.   */
/*%C     	After this launch the leds activation is autonomous and follow the*/
/*%C     	associated burst trough the driver function call                  */
            if (Led_Command_Type_Memo != 	Led_Command_Type)
			   {
/*%C           Red led blinking  */
               DRV_Led_Red(BLINK_LED);
/*%C           Orange led off  */
               DRV_Led_Orange(NO_LED);
/*%C 			   Led command memorization  */
				   Led_Command_Type_Memo = Led_Command_Type;
			   }
/*%C        else the leds are already activated in HP command */
            break;
		   }
/*%C     Medium priority Led command  */
         case MPR:
		   {
/*%C        If it's the first time in MPR alarm, leds are commanded  */
/*%C        in order to launch the sequence once.   */
/*%C        After this launch the leds activation is autonomous and follow the*/
/*%C        associated burst trough the driver function call                  */
/*%C        The MPR alarm led command is made if the high alarm burst is over */
	         if (TIM_ReadDecounterValue(SEC_HIGH_PRIORITY_BURST) == 0)
			   {
         	   if (Led_Command_Type_Memo != 	Led_Command_Type)
         	   {
/*%C        	   Orange led blinking  */
            	   DRV_Led_Orange(BLINK_LED);
/*%C        	   Red led off  */
            	   DRV_Led_Red(NO_LED);
/*%C 				   Led command memorization  */
					   Led_Command_Type_Memo = Led_Command_Type;
				   }
			   }
            break;
		   }
/*%C  Low priority Led command  */
         case LP:
		   {
/*%C        If it's the first time in LP alarm, leds are commanded  */
/*%C        in order to launch the sequence once.   */
/*%C        After this launch the leds activation is autonomous and follow the*/
/*%C        associated burst trough the driver function call                  */
/*%C       	The LP alarm led command is made if the high & medium alarm burst */
/*%C        are over 																			*/
	         if ( (TIM_ReadDecounterValue(SEC_HIGH_PRIORITY_BURST) == 0)
			     && (TIM_ReadDecounterValue(SEC_MEDIUM_PRIORITY_BURST) == 0) )
			   {
				   if (Led_Command_Type_Memo != 	Led_Command_Type)
         	   {
/*%C        	   Orange led continuous command  */
            	   DRV_Led_Orange(CONTINU_LED);
/*%C        	   Red led off  */
            	   DRV_Led_Red(NO_LED);
/*%C 				   Led command memorization  */
					   Led_Command_Type_Memo = Led_Command_Type;
				   }
			   }
            break;
		   }
/*%C     Without priority Led command  */
         case WP:
		   {
/*%C        If it's the first time in WP alarm, leds are commanded  */
/*%C        in order to launch the sequence once.   */
/*%C        In this state the led are set off   */
/*%C        Orange led off  */
            DRV_Led_Orange(NO_LED);
/*%C        Red led off  */
            DRV_Led_Red(NO_LED);
/*%C        Memo led command initialization to WP state  */
				Led_Command_Type_Memo = WP;
            break;
		   }
         default:
		   {
/*%C        Orange led off  */
            DRV_Led_Orange(NO_LED);
/*%C        Red led off  */
            DRV_Led_Red(NO_LED);
/*%C        Memo led command initialization to WP state  */
				Led_Command_Type_Memo = WP;
            break;
		   }
	   }
   }
/*%C else, the red led is blinking         */
   else
   {
/*%C  the red led is launched once         */
      if (High_Pressure_Led_Reminder != Previous_High_Pressure_Led_Reminder)
      {
/*%C     Red led blinking  */
         DRV_Led_Red(BLINK_LED);
/*%C     Orange led off  */
         DRV_Led_Orange(NO_LED);
/*%C     Previous led reminder update  */
         Previous_High_Pressure_Led_Reminder = High_Pressure_Led_Reminder;
/*%C     Memo led command initialization to WP state  */
			Led_Command_Type_Memo = WP;
      }
   }
}