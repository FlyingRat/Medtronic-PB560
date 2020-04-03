/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_DIS_grString.c */
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

#include "typedef.h"
#include "Driver_Display_Data.h"
#include "DRV_DIS_grString.h"						 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void DRV_DIS_grString ( UBYTE font, UWORD16 posx, UBYTE posy, 
							  UBYTE *st, UBYTE printon )
{
UWORD16 i ;
	DRV_DIS_grWriteDisplay(grESC);
	DRV_DIS_grWriteDisplay('S');
	DRV_DIS_grWriteDisplay( printon);
	DRV_DIS_grWriteDisplay(font);
	DRV_DIS_grWriteDisplay(posx>>8);
	DRV_DIS_grWriteDisplay((UBYTE) posx);
	DRV_DIS_grWriteDisplay( posy);

	for ( i=0; i<99; i++ )
	{
		DRV_DIS_grWriteDisplay(*st);
		
		if ( *st != grNULL )
			st++ ;
		else
			break;
	}
}