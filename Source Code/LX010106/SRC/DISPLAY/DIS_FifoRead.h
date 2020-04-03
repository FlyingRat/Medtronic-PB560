/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DIS_FifoRead.h */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C              Data declaration for DIS_FifoRead.c									*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE       															*/
/******************************************************************************/


#ifndef DIS_FIFOREAD_H
#define DIS_FIFOREAD_H

/******************************************************************************/
/*                         EXTERNAL FUCNTION DECLARATION                      */
/******************************************************************************/

extern void DRV_DIS_HostRequest ( bit etat );
extern void DRV_DIS_Delay_us ( UWORD16 delay_us) ;
extern void DRV_DIS_grSetContrast ( UBYTE level );
extern void DRV_DIS_grNegative ( UBYTE etat );
extern void DIS_DisplayPage( UBYTE page
									, UBYTE mode ) ;
extern void DIS_String( UBYTE *str
							 , UBYTE font
							 , SWORD16 line
							 , UWORD16 column
							 ,	UBYTE printon
							 , UBYTE page ) ;
extern void DIS_Number( SWORD32 value
							 , UBYTE nature
							 , SWORD16 line
							 , UWORD16 column
							 , UBYTE font
							 , UBYTE nbdigit
							 , UBYTE zero
							 , UBYTE printon
							 , UBYTE page ) ;
extern void DIS_Symbol( UBYTE symbol
							 , UBYTE line
							 , UWORD16 column
							 , UBYTE page );
extern void DIS_Pixel( UBYTE line
							, UWORD16 column
							, UBYTE printon
							, UBYTE page );
extern void DIS_Line ( UBYTE startline
							, UWORD16 startcolumn
							, UBYTE endline
							, UWORD16 endcolumn
							, UBYTE printon
							, UBYTE page  );
extern void DIS_Box( UBYTE color
						 , UBYTE startline
						 , UWORD16 startcolumn
						 , UBYTE endline
						 , UWORD16 endcolumn
						 ,	UBYTE printon
						 , UBYTE page );
extern void DIS_EraseZone( UBYTE startline
								 , UWORD16 startcolumn
								 , UBYTE endline
								 , UWORD16 endcolumn
								 ,	UBYTE printon
								 , UBYTE page ) ;
extern void DIS_ErasePage( UBYTE page ) ;
extern void DRV_DIS_grBackLight ( UWORD16 _Level );





#endif