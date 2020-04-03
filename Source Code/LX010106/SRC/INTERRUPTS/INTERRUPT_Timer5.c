/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INTERRUPT_Timer5.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE       */
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
#include "DB_Config.h"
#include "io_declare.h"
#include "INTERRUPT_Timer5.h"
#include "Driver_Datas.h"
#include "Timer_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

#ifndef _TASKING
void INTERRUPT_Timer5(void) interrupt 0x25
#else
interrupt(0x25)
void INTERRUPT_Timer5(void)
#endif
{
#define HIGH_PRIORITY_START_OF_SECOND_BURST_INDEX (SEQUENCE_FAST/2)


   e_BOOL ramp = FALSE;
   UWORD32 PW3Load = 0;
   UWORD16 SoundLevel = 0;

/* Max sequence buzzer */
   UWORD16 Sequence_Max = SEQUENCE_MAX;

   // Incrémentation du nombre de boucle
   // Increasing the number of loops
   CounterOfTurn++;

   // if skip, we are ramping signal
   if (cDRV_IHM_SIGNAL_BUZ[SoundActive - 1][Id_StatusSignal] == SKIP)
   {
      Id_StatusSignal++;
      EndOfOverflow = FALSE;
      StartOfOverflow = FALSE;
      CounterOfTurn = 0;
      Active = FALSE;

      // Stop Timer 5 interrupt authorization
      T5IE = 0;
      // Set the Timer 5 interrupt
      T5 = 0;
      // Timer 5 interrupt authorization
      T5IE = 1;
      return;
   }


   // limitation of the index
   if (Id_StatusSignal >= Sequence_Max)
   {
      Id_StatusSignal = 0;

      // If the sound is repeating back to the first index
      // reset the lock out timers for High, Med, and Low priority alarms.
      if (SoundActive == FAST_SOUND)
      {
         TIM_StartDecounter(SEC_HIGH_PRIORITY_BURST,
                            TIME_HIGH_PRIORITY_BURST);
      }
      else if (SoundActive == SLOW_SOUND)
      {
         TIM_StartDecounter(SEC_MEDIUM_PRIORITY_BURST,
                            TIME_MEDIUM_PRIORITY_BURST);
      }
      else if (SoundActive == VERY_SLOW_SOUND)
      {
         TIM_StartDecounter(SEC_LOW_PRIORITY_BURST,
                            TIME_LOW_PRIORITY_BURST);
      }

   }
   else
   {
      // If the high priority alarm index has reached half way, reset the alarm timers.
      if ((SoundActive == FAST_SOUND) && (Id_StatusSignal == HIGH_PRIORITY_START_OF_SECOND_BURST_INDEX))
      {
         TIM_StartDecounter(SEC_HIGH_PRIORITY_BURST,
                            TIME_HIGH_PRIORITY_BURST);
      }

   }

   // NumberOfTurn = (mseconde*1000 / (((65535 * 512) / FCPU)));
   NumberOfTurn = (UWORD32)cDRV_IHM_SIGNAL_BUZ[SoundActive - 1][Id_StatusSignal] * 1000 / 838848;

   // Dernier chargement de timer pour terminer la temporisation
   // Last timer load to complete the timer
   // Turns off the last tone in sequence
   if ((NumberOfTurn > 0) && (StartOfOverflow == FALSE))
   {
      // LastLoad = (mseconde*1000*FCPU)/512 - (65535 * NumberOfTurn)
      LastLoad = ((UWORD32)cDRV_IHM_SIGNAL_BUZ[SoundActive - 1][Id_StatusSignal] * 40000 / 512) - (NumberOfTurn * 65535);
      // Initialisation
      // Initialization
      EndOfOverflow = TRUE;
      StartOfOverflow = TRUE;
      CounterOfTurn = 0;
      // Inversion du signal à chaque passage
      // Inversion of the signal at each pass
      Active = !Active;
      T5IE = 0;
      rampdex = 0;
      DRV_PwmBuzzerInt(Active, 0);
      T5IE = 1;
   }

   if (CounterOfTurn == NumberOfTurn)
   {
      // Chargement du timer
      // Loading the timer
      T5 = (UWORD16)LastLoad;
      // Increasing the index of the signal table
      Id_StatusSignal++;
      // Initialisation
      // Initialization
      EndOfOverflow = FALSE;
      StartOfOverflow = FALSE;
      CounterOfTurn = 0;
   }
   // turns on and off most tones in sequence
   else if (EndOfOverflow == FALSE)
   {
      T5IE = 0;
      // Chargement du timer
      // Loading the timer
      T5 = (UWORD16)(((UWORD32)cDRV_IHM_SIGNAL_BUZ[SoundActive - 1][Id_StatusSignal] * 10000) / 128);

      // Inversion du signal à chaque passage
      // Inversion of the signal at each pass
      Active = !Active;
      if (Active)
      {
         if ((UWORD32)cDRV_IHM_SIGNAL_BUZ[SoundActive - 1][Id_StatusSignal] == RAMP_TIME) 
         {
             ramp = TRUE;
         }
         else 
         {
             ramp = FALSE;
         }
      }
      // when driving ramp signal first ramp is set to zero percent; this prevents spikes when 
      // signal is then driven on the second ramp which is 50 percent of the volume setting.
      if (ramp)
      {
         rampdex++;
         if (rampdex == 1)
         {
            DRV_PwmBuzzerInt(TRUE, 0);
         }
         else
         {
            DRV_PwmBuzzerInt(TRUE, 50);
         }
      }
      else
      {
         rampdex = 0;
         if (Active)
         {
            DRV_PwmBuzzerInt(Active, 100);
         }
         else
         {
            DRV_PwmBuzzerInt(Active, 0);
         }
      }
      T5IE = 1;
      // Incrémentation de l'index du tableau de signal
      // Increasing the index of the signal table
      Id_StatusSignal++;
      // Initialisation
      // Initialization
      CounterOfTurn = 0;
   }
}

