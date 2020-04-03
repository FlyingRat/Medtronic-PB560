/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : TIM_StartMinuteDecounter.c */
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
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void TIM_StartMinuteDecounter(e_TIM_MINUTE_TABLE_ID offset_table,
										UWORD32 value,e_BOOL autoreload)
{
	TIM_MinuteTableOfCntAndDecnt[offset_table].type = DECOUNT;
	TIM_MinuteTableOfCntAndDecnt[offset_table].value = value;
	TIM_MinuteTableOfCntAndDecnt[offset_table].activate = TRUE;
	TIM_MinuteTableOfCntAndDecnt[offset_table].autoreload = autoreload;
	if (autoreload == TRUE)
	{
		TIM_MinuteTableOfCntAndDecnt[offset_table].autovalue = value;
	}
	else
	{
	 TIM_MinuteTableOfCntAndDecnt[offset_table].autovalue = 0;
	}
}