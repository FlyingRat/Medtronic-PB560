/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Airox_Symbol_Diplay.c                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C       It displays the "AIROX" symbol                     						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef MAIN_AIROX_SYMBOL_DISPLAY_H
#define MAIN_AIROX_SYMBOL_DISPLAY_H


extern void DRV_DIS_HostRequest ( bit etat );
extern void DIS_ErasePage( UBYTE page ) ;
extern void DIS_DisplayPage( UBYTE page, UBYTE mode ) ;
extern void DIS_Symbol( UBYTE symbol, UBYTE line, UWORD16 column, UBYTE page );
extern void TIM_Temporize(UWORD32 useconde);
#endif 