/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : TIM_Launch.c 																	*/
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
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void TIM_Launch(void)
{
	UBYTE i;

	for (i=0;i<end_of_table_cnt_decnt;i++)
	{
		if (TIM_TableOfCntAndDecnt[i].activate == TRUE) 
		{
			if (TIM_TableOfCntAndDecnt[i].type == DECOUNT) 
			{
				if (TIM_TableOfCntAndDecnt[i].value >= cTIM_TimePeriodMs)
				{
					TIM_TableOfCntAndDecnt[i].value -= cTIM_TimePeriodMs;
				}
				else
				{
					TIM_TableOfCntAndDecnt[i].value = 0;
				}
			}
			else
			{
				TIM_TableOfCntAndDecnt[i].value += cTIM_TimePeriodMs;
			}
		}
	}

	for (i=0;i<end_of_minute_table_cnt_decnt;i++)
	{
		if (TIM_MinuteTableOfCntAndDecnt[i].activate == TRUE) 
		{
			if (TIM_MinuteTableOfCntAndDecnt[i].type == DECOUNT) 
			{
				if (TIM_MinuteTableOfCntAndDecnt[i].value >= cTIM_TimePeriodMs)
				{
					TIM_MinuteTableOfCntAndDecnt[i].value -= cTIM_TimePeriodMs;
				}
				else
				{
					TIM_MinuteTableOfCntAndDecnt[i].value = 0;
				}
			}
			else
			{
				TIM_MinuteTableOfCntAndDecnt[i].value += cTIM_TimePeriodMs;
			}
		}
	}
}

