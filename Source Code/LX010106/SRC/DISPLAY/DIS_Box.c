/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DIS_Box.c */
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
#include "DIS_Box.h"
			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DIS_Box( UBYTE color
				, UBYTE startline
				, UWORD16 startcolumn
				, UBYTE endline
				, UWORD16 endcolumn
				, UBYTE printon
				, UBYTE page )
{


	DRV_DIS_grSetPage ( page-1 ) ;

	DRV_DIS_grSetColor ( printon ) ;

	if ( color == BLACK )
	{
		DRV_DIS_grFullRect ( startcolumn
								 , startline
								 , endcolumn
								 , endline ) ;
	}
	else
	{
		DRV_DIS_grRect ( startcolumn
							, startline
							, endcolumn
							, endline ) ;
	}
}
