/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : ACT_BrakePower.c																*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   Brake power command  	  											*/
/******************************************************************************/
/*%I Input Parameter :  UWORD16 percentage                    						*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE																	*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#ifndef _TASKING
	#include "LH_ST10F276.h"
	#include <intrins.h>
#else
	#ifdef _TESTRT
		#include "IO_TestRT.h"
	#else
		#include "regf276e.h"
	#endif
#endif 
#include "io_declare.h"
#include "typedef.h"
#include "Ventilation_Constants.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void ACT_BrakePower(UWORD16 percentage)
{
/*%C if the percentage is equal to 0, then												*/
	if (percentage == 0)
	{
/*%C  Timer 0 Stop																				*/
		T0R = 0;	 
		CCM0 &= 0xFF0F;
		BRAKE_BLOWER = 1;
	}
/*%C else if the percentage is equal to 100, then										*/
	else if (percentage == 100)
	{
/*%C  Blower Stop */
		BLOWER_CMD = cBLOWER_CMD_OFF;
/*%C  Timer 0 Stop																				*/
		T0R = 0;	
		CCM0 &= 0xFF0F;
 		BRAKE_BLOWER = 0;
	}
/*%C else, for a value include between 0 => 100% 										*/
	else
	{
/*%C  Blower Stop */
		BLOWER_CMD = cBLOWER_CMD_OFF;
		CCM0 &= 0xFF7F;
		CCM0 |= 0x0070;
		CC1 = (UWORD16)(BRAKE_PERIOD + ((NB_TIMER0_VALUE*percentage)/100));
/*%C 	Starting of Timer 0 */
  		T0R = 1; 
  	}
}
