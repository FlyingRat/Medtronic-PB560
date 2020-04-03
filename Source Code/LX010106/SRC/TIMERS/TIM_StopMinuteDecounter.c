/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : TIM_StopMinuteDecounter.c */
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

void TIM_StopMinuteDecounter(e_TIM_MINUTE_TABLE_ID offset_table)
{
	TIM_MinuteTableOfCntAndDecnt[offset_table].type = DECOUNT;
	TIM_MinuteTableOfCntAndDecnt[offset_table].value = 0;
	TIM_MinuteTableOfCntAndDecnt[offset_table].activate = FALSE;
	TIM_MinuteTableOfCntAndDecnt[offset_table].autoreload = FALSE;
}