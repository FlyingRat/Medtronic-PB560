/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Trend.h  									  */
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


#ifndef DRV_COM_TRANSMIT_TREND_H
#define DRV_COM_TRANSMIT_TREND_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/
/*%C Transmit trend	monitoring data storage */
	/* Keil  */
#ifndef _TASKING
UBYTE sdata Array_Trend_Monit[TREND_BUFFER_SIZE_READ + End_Of_Table_Com_TX_Remote - 1];
	/* Tasking  */
#else
UBYTE near Array_Trend_Monit[TREND_BUFFER_SIZE_READ + End_Of_Table_Com_TX_Remote - 1];
#endif

/******************************************************************************/
extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
										UWORD16 StopIndex,
										UBYTE* TransmitArray,
										UWORD16 Compute_CRC);


#endif
