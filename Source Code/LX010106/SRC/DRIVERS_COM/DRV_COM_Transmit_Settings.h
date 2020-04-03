/*                                                                            */
/* Project N�  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Settings.h  									  */
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


#ifndef DRV_COM_TRANSMIT_SETTINGS_H
#define DRV_COM_TRANSMIT_SETTINGS_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/

/*%C Transmit Settings */
	/* Keil  */
#ifndef _TASKING
UBYTE sdata Array_Settings[End_Of_Table_TX_Settings + End_Of_Table_Com_TX_Remote - 1];
	/* Tasking  */
#else
UBYTE near Array_Settings[End_Of_Table_TX_Settings + End_Of_Table_Com_TX_Remote - 1];
#endif


extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
										UWORD16 StopIndex,
										UBYTE* TransmitArray,
										UWORD16 Compute_CRC);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
 #endif
