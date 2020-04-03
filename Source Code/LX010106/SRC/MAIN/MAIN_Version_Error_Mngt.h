/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Version_Error.h                                   			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                               															*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef MAIN_VERSION_ERROR_H
#define MAIN_VERSION_ERROR_H


extern UWORD16 DB_ConfigWrite(e_DB_CONFIG Id,
										UWORD16 Value);
extern void DRV_DIS_HostRequest ( bit etat );
extern void DIS_ErasePage( UBYTE page );
extern void DIS_String( UBYTE *str
							 , UBYTE font
							 , SWORD16 line
							 , UWORD16 column
							 ,	UBYTE printon
							 , UBYTE page ) ;
extern void DIS_DisplayPage( UBYTE page
									, UBYTE mode ) ;

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern const UBYTE *const huge cMSG_Alarm[Mark_Displayed_Alarm][NB_LANGUAGE];
extern void DB_EventMngt(UWORD16 Value);

#endif
