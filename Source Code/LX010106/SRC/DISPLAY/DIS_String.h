/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DIS_String.h */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  																			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                             	*/
/*%O Output Parameter : NONE       															*/
/******************************************************************************/


#ifndef DIS_STRING_H
#define DIS_STRING_H



/******************************************************************************/
/*                         EXTERNAL FUCNTION DECLARATION                      */
/******************************************************************************/

extern void DRV_DIS_grSetPage ( UBYTE page );
extern void DRV_DIS_grNegative ( UBYTE etat );
extern void DRV_DIS_grSetColor ( UBYTE color );
extern void DRV_DIS_grString ( UBYTE font
									  , UWORD16 posx
									  , UBYTE posy
									  , UBYTE *st
									  , UBYTE printon );
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

#endif