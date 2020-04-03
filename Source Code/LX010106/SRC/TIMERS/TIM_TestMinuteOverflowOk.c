/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : TIM_TestMinuteOverflowOk.c */
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
#ifndef _BORLAND
   #ifndef _TASKING
      #include "LH_ST10F276.h"
      #include <intrins.h>
   #else
      #include "regf276e.h"
   #endif
#endif
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

BIT TIM_TestMinuteOverflowOk(e_TIM_MINUTE_TABLE_ID offset_table)
{
	if ( (TIM_MinuteTableOfCntAndDecnt[offset_table].value == 0)
	  && (TIM_MinuteTableOfCntAndDecnt[offset_table].activate == TRUE) )
	{
		if (TIM_MinuteTableOfCntAndDecnt[offset_table].autoreload == TRUE)
		{
			TIM_MinuteTableOfCntAndDecnt[offset_table].value = 
								TIM_MinuteTableOfCntAndDecnt[offset_table].autovalue;
		}
		else
		{
			TIM_MinuteTableOfCntAndDecnt[offset_table].activate = FALSE;
		}
  		return (TRUE);
	}
	else
	{
		return (FALSE);
	}
}
