/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_ResetOnReturnSupply.h                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  Data declaration for DRV_ResetOnReturnSupply.c	                        */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   NONE                                                */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

#ifndef DRV_RESET_ON_RETURN_SUPPLY_H
#define DRV_RESET_ON_RETURN_SUPPLY_H

/************************************************************************/
/*                   EXTERNAL CONSTANT DECLARATION	                     */
/************************************************************************/

extern const UBYTE *const huge cMSG_Alarm[Mark_Displayed_Alarm][NB_LANGUAGE];

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern void DRV_EEP_WaitEndTransmit(void);
extern void DRV_EEP_tempo_CE(void);
extern void	CheckPageAndRetransmitAddress(UWORD16 Address);
extern void DRV_DIS_HostRequest( bit etat );
extern void It_watchdog(void);
extern void DIS_ErasePage( UBYTE page ) ;
extern void DIS_DisplayPage( UBYTE page
									, UBYTE mode ) ;

extern void DIS_String( UBYTE *str
							 , UBYTE font
							 , SWORD16 line
							 , UWORD16 column
							 ,	UBYTE printon
							 , UBYTE page ) ;

#endif

