/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INTERRUPT_Capture_CC0.c */
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
#include "io_declare.h"
#include "Driver_Datas.h"
					 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

#ifndef _TASKING
void INTERRUPT_Capture_CC0 (void) interrupt 0x10
#else
interrupt (0x10)
 void INTERRUPT_Capture_CC0 (void)
#endif
{
	UBYTE Loop;
	//Attente de 2us avant de tester s'il s'agit bien d'un front montant
	for (Loop =0;Loop <= 10;Loop++)
	{
		_nop_();
	}
	if (SPEED_BLOWER_PIN == 1)
	{ 
		if (CaptureNumber == 0)
		{
			Timer1Measure[0] = (UWORD32) CC0 + ((UWORD32)Cpt_Timer1_Overflow * 65535);
			CaptureNumber = CaptureNumber + 1;
		}
		else 
		{
		 	Timer1Measure[1] = (UWORD32)CC0 + ((UWORD32)Cpt_Timer1_Overflow * 65535);
			SpeedBlowerDigit = Timer1Measure[1] - Timer1Measure[0];
								   
			if (SpeedBlowerDigit > 4918) //Saturation à 61000 tr/min
			{ 
 				CaptureNumber = 0;
				CC0IE = 0; 
				T1R = 0  ;
				T1IE = 0 ;
				AvailableSpeedBlowerDigit = TRUE;
		  	}
  		}
	}
}
