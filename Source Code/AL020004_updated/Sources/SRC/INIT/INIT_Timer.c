/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INIT_Timer.c                                             		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "p18f6622.h"
#include "typedef.h"
#include "enum.h"
#include "structure.h"
	#define DECLARATION_TIMER_DATA
#include "Timer_Data.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void INIT_Timer(void)
{
	UBYTE Idx = 0;
	for( Idx = 0; Idx < end_of_table_cnt_decnt_16 ;Idx++)
	{
		TIM_TableOfCntAndDecnt16[Idx].value = 0;
		TIM_TableOfCntAndDecnt16[Idx].type  = DECOUNT;
	}
	for( Idx = 0; Idx < end_of_table_cnt_decnt_32 ;Idx++)
	{
		TIM_TableOfCntAndDecnt32[Idx].value = 0;
		TIM_TableOfCntAndDecnt32[Idx].type = DECOUNT;
	}
	/*%C Run WatchDog */
	ClrWdt();
}
