/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_SPI_ST10_Data.h                                                    */
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


#define SPI_ST10_MAX_BYTES_WITHOUT_START_FRAME		0xFF
#define SPI_ST10_MAX_BAD_FRAMES						0x02

#ifdef DECLARATION_SPI_ST10_DATA
	#ifndef SPI_ST10_DATA_H
	#define SPI_ST10_DATA_H


/*%C 16 bytes array data rs232 transmit													*/
UBYTE SpiArrayTransmitData[SPI_ST10_EndOfTableTransmit];
/*%C Frame reception buffer																	*/
UBYTE SpiBufferOfReceipt[SPI_ST10_RECEIVE_BufferSize];
UBYTE SpiPtrReadBufferRx;
UBYTE SpiPtrWriteBufferRx;
/*%C Index of Transmit array data															*/
UBYTE SpiArrayTransmitDataId; 
e_BOOL SpiEndOfTransmit;

/*%C driver State						*/
e_DRV_SPI_ST10_ERROR DRV_SPI_ST10_Status = DRV_SPI_ST10_NO_ERROR;
UWORD16 SpiNbBytesWithoutStartFrame = 0;
UBYTE	SpiNbBadFrames = 0;

	
	#endif
#else
	#ifndef SPI_ST10_DATA_H
	#define SPI_ST10_DATA_H


/*%C 16 bytes array data rs232 transmit													*/
extern UBYTE SpiArrayTransmitData[SPI_ST10_EndOfTableTransmit];
/*%C Frame reception buffer																	*/
extern UBYTE SpiBufferOfReceipt[SPI_ST10_RECEIVE_BufferSize];
extern UBYTE SpiPtrReadBufferRx;
extern UBYTE SpiPtrWriteBufferRx;
/*%C Index of Transmit array data															*/
extern UBYTE SpiArrayTransmitDataId; 
extern e_BOOL SpiEndOfTransmit;	

/*%C driver State						*/
extern e_DRV_SPI_ST10_ERROR DRV_SPI_ST10_Status;
extern UWORD16 SpiNbBytesWithoutStartFrame;
extern UBYTE	SpiNbBadFrames;
	
	#endif
#endif


