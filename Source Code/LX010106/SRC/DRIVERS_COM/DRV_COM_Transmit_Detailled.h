/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Detailled.h  									  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                           			*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE       															*/
/******************************************************************************/


#ifndef DRV_COM_TRANSMIT_DETAILLED_H
#define DRV_COM_TRANSMIT_DETAILLED_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/

/*%C Transmit detailled	monitoring data storage */
	/* Keil  */
#ifndef _TASKING
UBYTE sdata Array_Detailled_Monit[MONIT_BUFFER_SIZE_READ + End_Of_Table_Com_TX_Remote -1];
	/* Tasking  */
#else
UBYTE near Array_Detailled_Monit[MONIT_BUFFER_SIZE_READ + End_Of_Table_Com_TX_Remote -1];
#endif

extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
										UWORD16 StopIndex,
										UBYTE* TransmitArray,
										UWORD16 Compute_CRC);



#endif
