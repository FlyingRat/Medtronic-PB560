/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_ID.h  									  */
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


#ifndef DRV_COM_TRANSMIT_ID_H
#define DRV_COM_TRANSMIT_ID_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/

/*%C Transmit ID Device */
	/* Keil  */
#ifndef _TASKING
UBYTE sdata Array_ID[End_Of_Table_Com_ID_Device + End_Of_Table_Com_TX_Remote - 1];
	/* Tasking  */
#else
UBYTE near Array_ID[End_Of_Table_Com_ID_Device + End_Of_Table_Com_TX_Remote - 1];
#endif


extern UWORD16 DB_VersionRead(e_DB_VERSION Id);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
										UWORD16 StopIndex,
										UBYTE* TransmitArray,
										UWORD16 Compute_CRC);
 #endif
