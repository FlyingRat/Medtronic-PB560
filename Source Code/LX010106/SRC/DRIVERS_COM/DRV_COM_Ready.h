/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Ready.h  											  */
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


#ifndef DRV_COM_READY_H 
#define DRV_COM_READY_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/
/*%C Transmit ID Device */
	/* Keil  */
#ifndef _TASKING
UBYTE sdata Array_Ready[End_Of_Table_Com_TX_Remote];
	/* Tasking  */
#else
UBYTE near Array_Ready[End_Of_Table_Com_TX_Remote];
#endif


extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
										UWORD16 StopIndex,
										UBYTE* TransmitArray,
										UWORD16 Compute_CRC);

#endif
