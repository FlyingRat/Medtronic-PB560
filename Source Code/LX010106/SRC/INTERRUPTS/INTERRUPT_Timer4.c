/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INTERRUPT_Timer4.c */
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
#include "io_declare.h" 	
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Driver_Datas.h"

extern void DRV_OutputPort(e_OUTPUT_NAME _Port, UWORD16 _Value);
					 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

#ifndef _TASKING
void INTERRUPT_Timer4(void) interrupt 0x24
#else
interrupt (0x24)
 void INTERRUPT_Timer4(void)
#endif
{
// Tempo de 1s pour la Led Orange
CounterBlink++;
// Chargement du timer - 0.25s
// T4 = seconde / 25.6µs;
T4 = 9766;

// Clignottement Led Red - 2Hz - 1/2 période = 0.25 s
if (Id_Led_Red == TRUE)
	{
	// Activation des Buzzers
	LED_ALARME_ROUGE = !LED_ALARME_ROUGE;
	}

// Clignottement Led Orange - 0.5Hz - 1/2 période = 1 s
if ((Id_Led_Orange == TRUE) && (CounterBlink == 4))
	{
	// Activation des Buzzers
	LED_ALARME_ORANGE = !LED_ALARME_ORANGE;
	}	

#ifdef CONFIG_REGUL_O2
// Clignottement Led White - 0.5Hz - 1/2 période = 1 s
if ((Id_Led_White == TRUE) && (CounterBlink == 4))
	{
	   Led_White_On = !Led_White_On;
	   DRV_OutputPort(OUT_LED_O2, (UWORD16) Led_White_On);	
	}
#endif

// RAZ compteur
if (CounterBlink == 4) CounterBlink = 0;
}
