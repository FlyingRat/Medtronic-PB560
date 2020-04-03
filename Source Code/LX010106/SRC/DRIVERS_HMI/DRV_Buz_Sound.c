/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_Buz_Sound.c                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :   Buzzer command function  */
/*%C                                                                          */
/*%C This function commands the different priority bursts function of sound   */
/*%C type. The command is applicated to the buzzer card, to the security      */
/*%C buzzer, or twice                                                         */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  sound                                                 */
/*%I Input Parameter :  NumBuzzer                                             */
/*%IO Input/Output :    NONE                                                  */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#ifndef _TASKING         
#include "LH_ST10F276.h" 
#include <intrins.h>     
#else                    
#include "regf276e.h"    
#endif                   	
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "io_declare.h"
#include "DB_Control.h"
#include "DRV_Buz_Sound.h"
#include "Driver_Datas.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_Buz_Sound(e_TYPE_SOUND sound,
                   e_NUMBER_BUZ NumBuzzer)
{
/* Timer 5 declaration  */
   UWORD32 TIMER_T5 = 0;

   /* Configuration du timer 5 */
   /* Registre de controle du timer T5	*/
	/* Prédiviseur = 24 T5I = 111	*/  
	/* Mode timer 	   T5M = 000	*/
	/* Timer en marche T5R = 1	*/
	/* Direction "décomptage" sans tenir compte de l'entrée T5 T8EUD = 01	*/
	/* Contrôle de la sortie T8OUT P31 	non utilisée.T5OE = 0	*/
	/* latch de la sortie T5OL = 0	*/
	/* Bit 11 12  13 14 15 non utilisés = 00000	*/
	/* Controle du mode reload pas de reload à partir de CAPREL	 T5SR = 0	*/
	/* T5CON =  00000 0 0 01 1 000 000 = 0000000011000111 b = 0xC7	*/
   T5CON = 0xC7;

   /* Registre de contrôle de l'interruption	*/
	/* Revoir sa localisation dans le projet voir peut etre pour un	*/ 
	/* module de gestion des niveaux de priorité des interruptions	*/ 
	/* et de gestion des PEC	*/
	/* Priorité  des interruptions T5	*/
   /*%IR = 0 ,IE = 0; ILVL  = 12 ,GLVL = 2 	 */
   T5IC = 0x32;

/* Init variable	*/
   CounterOfTurn = 0;
   EndOfOverflow = FALSE;
   StartOfOverflow = FALSE;
   Id_StatusSignal = 0;

/*%C Sound memorization	*/
   SoundActive = sound;

/*%C Continuous buzzer command 	*/
   if (sound == CONTINU_SOUND)
	{
/*%C  Timer 5 stop	*/
	   T5R = 0;
/*%C  No timer 5 interrupt */
	   T5IE = 0;
	   Active = TRUE;
/*%C  Buzzer activation	*/
	   DRV_PwmBuzzer(Active);
/*%C  Buzzer activation	*/
	   if (NumBuzzer != BUZ_VOLUME) 
		{
		   RAPPEL_ALARM = TRUE;
/*%C     Alarm check remote flag 	*/
		   DB_ControlWrite(BUZZER_CMD_U16,
		   					 TRUE);
		}
	}
   else if (sound == NO_SOUND)
	{
/*%C  Timer 5 stop 	*/
	   T5R = 0;
/*%C  No timer 5 interrupt */
	   T5IE = 0;
	   Active = FALSE;
/*%C  Buzzer desactivation	*/
	   DRV_PwmBuzzer(Active);
	   if (NumBuzzer != BUZ_VOLUME)
		{
		   RAPPEL_ALARM = FALSE;
/*%C     Alarm check remote flag 	*/
		   DB_ControlWrite(BUZZER_CMD_U16,
		   					 FALSE );
		}
	}
   else
	{

/*%C  No timer 5 interrupt */
	   T5IE = 0;
/*%C  Buzzer counter sequence reset */
   	Id_StatusSignal = 0;

    Active = TRUE;
    rampdex = 1;

/*%C  Use ramping feature (DRV_PwmBuzzerInt) on alarm tones */
    if ( (sound == VERY_SLOW_SOUND) || 
             (sound == SLOW_SOUND) || 
	         (sound == FAST_SOUND)
           )
	{
       DRV_PwmBuzzerInt(Active, 0);
    }
    else
    {
       DRV_PwmBuzzer(Active);
    }
		
/*%C  Timer T5 loading and saturation (16bits => 65535)    	*/
 	   TIMER_T5 = (cDRV_IHM_SIGNAL_BUZ[sound-1][Id_StatusSignal] * 10000) / 128;
 	   if (TIMER_T5 > 65535)
 	   {
/*%C  Timer 5 affectation to its maximum 	*/
 		   T5 = 65535;
 	   }			
	   else
	   {
/*%C  Timer 5 affectation by the buzzer sequence value 	*/
		   T5 = (UWORD16)TIMER_T5;
	   }   				
      Id_StatusSignal++;
/*%C  Timer 5 interrupt authorization    	*/
	   T5IE = 1;
  
      if (NumBuzzer != BUZ_VOLUME)
      {
         RAPPEL_ALARM = TRUE;
/*%C     Alarm check remote flag 	*/
         DB_ControlWrite(BUZZER_CMD_U16,TRUE);
		}
	}
}
