/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : TIM_Temporize.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  																			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE       															*/
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
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "TIM_Temporize.h"
			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void TIM_Temporize(UWORD32 useconde)
{
/*%C Init Clock Counter */
	cpt_de_debordement_timer = 0;
/*%C Init	signal of end of delay */
	temporisation_terminee = 0;
/*%C Check of the possibles min & max delay limits: 25 > delay > 100 000000 */
	if (useconde > 100000000)
	{
		useconde = 100000000;
	}
	if (useconde < 25)
	{
		useconde = 25;
	}
/*%C Compute of Timer loops to realise */
	nbre_de_debordement_timer = (useconde / (((65535 * 8) / FCPU)));
/*%C Timer 2 configuration  */
/*%C timer T2	control register  */
/*%C Prédivideur = 8 T2I = 000  */
/*%C Mode timer 	   T2M = 000	*/
/*%C running Timer T2R = 1		*/
/*%C select countdown function without T2 Input T2EUD = 01
/*%C Output Control of T2OUT P31 	not used.T6OE = 0	 */
/*%C latch of the output T2OL = 0	 */
/*%C Bit 9 10 11 12  13 14 15 non utilisés = 0000000		*/
/*%C Controle reload mode, No reload from CAPREL	 T2SR = 0  */
/*%C T2CON =  00000 0 0 01 1 000 000 = 0000000011000000 b = 0xC0	  */
/*%C Computing of delay loading value */
	if (nbre_de_debordement_timer == 0 )
	{ 
		T2 = (UWORD16)(((useconde*FCPU) / 8) - 50);
	}
	else 
	{
		T2 = 65484;
		dernier_chargement_T2 =  (useconde * FCPU) / 8
												 - (65535 * nbre_de_debordement_timer);
	}


	T2CON = 0xC0;
/*%C Interrupt control register */
		/* Revoir sa localisation dans le projet voir peut etre pour un 	 */
		/* module de gestion des niveaux de priorité des interruptions 	 */
		/* et de gestion des PEC														 */
		/* Priorité  des interruptions T2											 */
	/*%IR = 0 ,IE = 1; ILVL  = 13 ,GLVL = 0 	 */
	T2IC = 0x74;

/*%C waiting end of delay */ 
	do
	{
		It_watchdog();
	}
	while(temporisation_terminee == 0);	
/*%C Timer unactivation */ 
	T2R = 0;
/*%C timer 2 interruption not allowed */
	T2IE =0;
}

