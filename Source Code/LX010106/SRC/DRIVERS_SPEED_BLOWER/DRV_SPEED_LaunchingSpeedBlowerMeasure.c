/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_SPEED_LaunchingSpeedBlowerMeasure.c */
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
#include "Driver_Datas.h"
					 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_SPEED_LaunchingSpeedBlowerMeasure(void)
{
	/*%CSpeed acquisition not avaible					  */
	AvailableSpeedBlowerDigit  = FALSE;
	Cpt_Timer1_Overflow = 0;
	CaptureNumber = 0;
	/*%C Reset timer1 Value	*/
	T1	= 0;
	/*%C Reset Interrupt request timer1 overflow  flag*/
	T1IR = 0;
	/*%C Enable Interrupt timer 1 */
	T1IE = 1;
	/*%C Launch Timer T1*/
	T1R = 1;
  	/*%C Reset interrupt request capture 0 */
	CC0IR = 0; 
	/*%C Enable Interrupt capture 0 */
	CC0IE = 1;    
}
