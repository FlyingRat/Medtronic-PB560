/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INTERRUPT_Timer2.c */
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
#include "Timer_Data.h"
					 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

#ifndef _TASKING
void INTERRUPT_Timer2(void) interrupt 0x22
#else
interrupt (0x22)
 void INTERRUPT_Timer2(void)
#endif
{
	cpt_de_debordement_timer = cpt_de_debordement_timer +1;
  	if (cpt_de_debordement_timer == nbre_de_debordement_timer)
		{
		T2 = (UWORD16)dernier_chargement_T2;
		}
	if (cpt_de_debordement_timer > nbre_de_debordement_timer)
		{
		temporisation_terminee = 1;
		}
	
}