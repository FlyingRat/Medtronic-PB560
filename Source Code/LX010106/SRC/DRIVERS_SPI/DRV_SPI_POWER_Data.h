/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_SPI_POWER_Data.h                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Global variables of "RTC DRIVER"                    */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*                                                                            */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#define SPI_POWER_START_FRAME_MSB_VALUE				0xEB
#define SPI_POWER_START_FRAME_LSB_VALUE				0x90
#define SPI_POWER_END_FRAME_VALUE					0xFA
#define SPI_POWER_MAX_BYTES_WITHOUT_START_FRAME		0xFF
#define SPI_POWER_MAX_BAD_FRAMES					0x02


#ifdef DECLARATION_DRV_SPI_POWER_DATA

	#ifndef DRV_SPI_POWER_DATA_H
	#define DRV_SPI_POWER_DATA_H

/************************************************************************/
/*                        VARIABLE DECLARATION		                		*/
/************************************************************************/

/*%C 16 bytes array data rs232 transmit													*/
UBYTE SpiArrayTransmitData[] = 	{		SPI_POWER_START_FRAME_MSB_VALUE,
													SPI_POWER_START_FRAME_LSB_VALUE,
													0,
													0,
													0,
													0,
													SPI_POWER_END_FRAME_VALUE
											};
/*%C Frame reception buffer																	*/
UBYTE	SpiBufferOfReceipt[SPI_POWER_RECEIVE_BufferSize];
UBYTE	SpiPtrReadBufferRx = SPI_POWER_RECEIVE_MSB_START_FRAME;
UBYTE	SpiPtrWriteBufferRx = SPI_POWER_RECEIVE_MSB_START_FRAME;
/*%C Index of Transmit array data															*/
UBYTE	SpiArrayTransmitDataId = SPI_POWER_TRANSMIT_START_FRAME_MSB; 
/*%C Return the frame status */
UBYTE PowerSupplyFrame = FALSE ;

/*%C driver State						*/
e_DRV_SPI_POWER_ERROR DRV_SPI_POWER_Status = DRV_SPI_POWER_NO_ERROR;

//// Uncomment to debug spi_power
UWORD16	compteurAff = 0;
UWORD16	testAff = 0;
////

	#endif
#else
	#ifndef DRV_SPI_POWER_DATA_H
	#define DRV_SPI_POWER_DATA_H


/************************************************************************/
/*                        VARIABLE DECLARATION		                		*/
/************************************************************************/

/*%C 16 bytes array data rs232 transmit													*/
extern UBYTE	SpiArrayTransmitData[SPI_POWER_TRANSMIT_EndOfFrame];
/*%C Frame reception buffer																	*/
extern UBYTE	SpiBufferOfReceipt[SPI_POWER_RECEIVE_BufferSize];
extern UBYTE	SpiPtrReadBufferRx;
extern UBYTE	SpiPtrWriteBufferRx;
/*%C Index of Transmit array data															*/
extern UBYTE	SpiArrayTransmitDataId; 

/*%C RTC driver State						*/
extern e_DRV_SPI_POWER_ERROR DRV_SPI_POWER_Status;
extern UWORD16	SpiNbBytesWithoutStartFrame;
extern UBYTE	SpiNbBadFrames;

/*%C Return the frame status */
extern UBYTE PowerSupplyFrame ;

//// Uncomment to debug spi_power
extern UWORD16	compteurAff;
extern UWORD16	testAff;
////
	#endif
#endif
