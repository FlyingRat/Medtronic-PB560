/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_RTC_control.c                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
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
#include "define.h"
#include "DRV_RTC_control.h"
#include "RTC_Driver_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_RTC_control (UBYTE data_control)
{
	DRV_OutputPort(CE_RTC1, 1); /*%C activation chip enable RTC																*/
	SSCTB  = 0x008F;          /*%C loading buffer with writing adressof the RTC control register */
	DRV_RTC_WaitEndTransmit();
	SSCTB  = (UWORD16) data_control;          /*%C loading buffer with writing adressof the control register 	  */
	DRV_RTC_WaitEndTransmit(); 
	DRV_OutputPort(CE_RTC1, 0); /*%C Desactivation chip enable RTC																*/
	DRV_RTC_tempo_CE();      	  /*%C tempo 1,5 µs ( /CS disable time minimum tcwh de 1 µs )}}						*/
}
