/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_BuzzerCmd.c                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  This function commands the buzzer, function of level alarm              */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   Buzzer_Cmd_Type                                     */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Control.h"
#include "SEC_BuzzerCmd.h"


void SEC_BuzzerCmd(e_DB_ALARM_LEVEL_PRIORITY Buzzer_Command_Type)
{
   static e_DB_ALARM_LEVEL_PRIORITY Buzzer_Command_Type_Memo = WP;
   UWORD16 Bip_Running = DB_ControlRead(BIP_RUNNING_U16);

/*%C Buzzer command flag inialization:  													*/
/*%C - If a bip is running, no alarm buzzer command  		  							*/
/*%C - else, if an alarm was running before a bip occurs, this alarm is			*/
/*%C 	 reactivated																				*/
   if (Bip_Running == TRUE)
   {
      Buzzer_Command_Type_Memo = WP;
   }
   else
   {
/*%C  Buzzer command, function of alarm level 											*/
      switch (Buzzer_Command_Type)
      {
/*%C  	High priority buzzer command   													*/
      case HP:
         {
             if ((TIM_ReadDecounterValue(SEC_MEDIUM_PRIORITY_BURST) == 0)
                 && (TIM_ReadDecounterValue(SEC_LOW_PRIORITY_BURST) == 0))
            {
    /*%C     	If the previous buzzer command was not HP, the high priority 		*/
    /*%C     	sequence is commanded                                             */
                if (Buzzer_Command_Type_Memo != HP)
                {
                   DRV_Buz_Sound(FAST_SOUND,
                                 BUZ_ALL);
    /*%C        	Buzzer command memorization  												*/
                   Buzzer_Command_Type_Memo = Buzzer_Command_Type;
                   /*%C     	High priority timer launch (in order to respect a half burst)     */
                   TIM_StartDecounter(SEC_HIGH_PRIORITY_BURST,
                                      TIME_HIGH_PRIORITY_BURST);
                }
            }
/*%C     	else, the priority is already HP, the buzzer is already activated */
            break;
         }
/*%C  	Medium priority buzzer command  	 												*/
      case MPR:
         {
/*%C     	End of high priority burst delay test    									*/
             if ((TIM_ReadDecounterValue(SEC_HIGH_PRIORITY_BURST) == 0)
                 && (TIM_ReadDecounterValue(SEC_LOW_PRIORITY_BURST) == 0))
            {
/*%C        	If the priority was not MPR, the medium priority sequence      */
/*%C        	is commanded .                       			 						*/
               if (Buzzer_Command_Type_Memo != MPR)
               {
                  DRV_Buz_Sound(SLOW_SOUND,
                                BUZ_ALL);
/*%C           	Buzzer command memorization  	  										*/
                  Buzzer_Command_Type_Memo = Buzzer_Command_Type;
/*%C        	Timer launch for medium priority burst                         */
/*%C        	(in order to respect a burst)                                  */
               TIM_StartDecounter(SEC_MEDIUM_PRIORITY_BURST,
                                  TIME_MEDIUM_PRIORITY_BURST);

               }
/*%C        	else, the priority is already MPR, the buzzer is already			*/
/*%C				activated																		*/
            }
/*%C     	else, the buzzer finishes to buzz in HP before buzzing in MPR  */
            break;
         }
/*%C  	Low priority buzzer command  */
      case LP:
         {
/*%C     	End of high or medium priority burst delay test  */
            if ((TIM_ReadDecounterValue(SEC_HIGH_PRIORITY_BURST) == 0)
                && (TIM_ReadDecounterValue(SEC_MEDIUM_PRIORITY_BURST) == 0))
            {
/*%C        	If the priority was not LP, the low priority sequence   	      */
/*%C        	is commanded .                      */
               if (Buzzer_Command_Type_Memo != LP)
               {
                  DRV_Buz_Sound(VERY_SLOW_SOUND,
                                BUZ_ALL);
/*%C           	Buzzer command memorization  */
                  Buzzer_Command_Type_Memo = Buzzer_Command_Type;
/*%C        	Timer launch for low priority burst                            */
/*%C        	(in order to respect a burst)			  		                     */
               TIM_StartDecounter(SEC_LOW_PRIORITY_BURST,
                                  TIME_LOW_PRIORITY_BURST);

               }
/*%C        	else, the priority is already LP, the buzzer is already 			*/
/*%C				activated */
            }
/*%C     	else the buzzer finishes to buzz in HP or MPR before buzzing in LP*/
            break;
         }
/*%C  	Without priority case:  the buzzer stops after the medium, high	   */
/*%C  	or low priority burst                                                */
      case WP:
         {
/*%C     	End of bursts delay test  */
            if ((TIM_ReadDecounterValue(SEC_HIGH_PRIORITY_BURST) == 0)
                && (TIM_ReadDecounterValue(SEC_MEDIUM_PRIORITY_BURST) == 0)
                && (TIM_ReadDecounterValue(SEC_LOW_PRIORITY_BURST) == 0))
            {
/*%C     		if an alarm sequence was running  */
               if (Buzzer_Command_Type_Memo != WP)
               {
/*%C           	Stop buzzer command  */
                  DRV_Buz_Sound(NO_SOUND,
                                BUZ_ALL);
/*%C             	Buzzer command memorization  */
                  Buzzer_Command_Type_Memo = Buzzer_Command_Type;
               }
            }
            break;
         }
/*%C  	Inhibition buzzer command  */
      case IA:
         {
/*%C     	The buzzer is inhibited intantaneously  */
            DRV_Buz_Sound(NO_SOUND,
                          BUZ_ALL);
/*%C     	Buzzer command memorization  */
            Buzzer_Command_Type_Memo = Buzzer_Command_Type;
            break;
         }

      default:
         {
/*%C     	nothing is done  */
            break;
         }
      }
   }
}
