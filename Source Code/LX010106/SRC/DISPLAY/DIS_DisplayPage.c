/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DIS_DisplayPage.c */
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
#include "DIS_DisplayPage.h"
			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DIS_DisplayPage( UBYTE page, UBYTE mode )
{
	if (page == PAGE1)
		{
		DRV_DIS_grControlPage ( 0, 1 ) ;
		DRV_DIS_grControlPage ( 0, 2 ) ;
		DRV_DIS_grControlPage ( mode, page-1 ) ;
		}
	else if (page == PAGE2)
		{
		DRV_DIS_grControlPage ( 0, 0 ) ;
		DRV_DIS_grControlPage ( 0, 2 ) ;
		DRV_DIS_grControlPage ( mode, page-1 ) ;
		}
	else
		{
		DRV_DIS_grControlPage ( 0, 0 ) ;
		DRV_DIS_grControlPage ( 0, 1 ) ;
		DRV_DIS_grControlPage ( mode, page-1 ) ;
		}
}