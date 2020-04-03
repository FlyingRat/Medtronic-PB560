/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : TIM_Launch.c                                             	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          																  						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "structure.h"
#include "Timer_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void TIM_Launch(void)
{
	UBYTE i = 0;

	for (i=0;i<end_of_table_cnt_decnt_16;i++)
	{
		if (TIM_TableOfCntAndDecnt16[i].type == DECOUNT) 
		{
			if (TIM_TableOfCntAndDecnt16[i].value >= PERIOD_OF_TIM_LAUNCH_CALL)
			{
				TIM_TableOfCntAndDecnt16[i].value -= PERIOD_OF_TIM_LAUNCH_CALL;
			}
			else
			{
				TIM_TableOfCntAndDecnt16[i].value = 0;
			}
		}
		else
		{
			if (TIM_TableOfCntAndDecnt16[i].value >= PERIOD_OF_TIM_LAUNCH_CALL)
			{
				TIM_TableOfCntAndDecnt16[i].value += PERIOD_OF_TIM_LAUNCH_CALL;
			}
			else
			{
				TIM_TableOfCntAndDecnt16[i].value = 0;
			}
		}
	}

	for (i=0;i<end_of_table_cnt_decnt_32;i++)
	{
		if (TIM_TableOfCntAndDecnt32[i].type == DECOUNT) 
		{
			if (TIM_TableOfCntAndDecnt32[i].value >= PERIOD_OF_TIM_LAUNCH_CALL)
			{
				TIM_TableOfCntAndDecnt32[i].value -= PERIOD_OF_TIM_LAUNCH_CALL;
			}
			else
			{
				TIM_TableOfCntAndDecnt32[i].value = 0;
			}
		}
		else
		{
			if (TIM_TableOfCntAndDecnt32[i].value >= PERIOD_OF_TIM_LAUNCH_CALL)
			{
				TIM_TableOfCntAndDecnt32[i].value += PERIOD_OF_TIM_LAUNCH_CALL;
			}
			else
			{
				TIM_TableOfCntAndDecnt32[i].value = 0;
			}
		}
	}
}
