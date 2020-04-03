/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_RS232_Data.h                                                    */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     Timer Global Data declaration                        */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifdef DECLARATION_RS232_DATA
	#ifndef RS232_DATA_H
	#define RS232_DATA_H

e_DRV_RS232_STATE Rs232_State;
/*%C 16 bytes array data rs232 transmit													*/
UBYTE ArrayTxData[EndOfTableTx];
/*%C Frame reception buffer																	*/
UBYTE BufferOfReceipt[RX_BufferSize];
UBYTE PtrReadBufferRx;
UBYTE PtrWriteBufferRx;
/*%C Index of Transmit array data															*/
UBYTE ArrayTxDataId; 
e_BOOL EndOfTransmit;	
	
	#endif
#else
	#ifndef RS232_DATA_H
	#define RS232_DATA_H

extern e_DRV_RS232_STATE Rs232_State;
/*%C 16 bytes array data rs232 transmit													*/
extern UBYTE ArrayTxData[EndOfTableTx];
/*%C Frame reception buffer																	*/
extern UBYTE BufferOfReceipt[RX_BufferSize];
extern UBYTE PtrReadBufferRx;
extern UBYTE PtrWriteBufferRx;
/*%C Index of Transmit array data															*/
extern UBYTE ArrayTxDataId; 
extern e_BOOL EndOfTransmit;	
	
	#endif
#endif


