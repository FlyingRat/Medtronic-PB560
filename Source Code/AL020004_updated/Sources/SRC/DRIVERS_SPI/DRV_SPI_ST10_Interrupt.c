/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_SPI_ST10_Interrupt.c                                	 		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        			  SPI Interrupt routine      					      			*/
/*%C          				max duration = 70 us (12/09/2006)	 		   	  		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/

#include "p18f6622.h"
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "DRV_SPI_ST10_Data.h"
#include "DRV_SPI_ST10_Interrupt.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_SPI_ST10_Interrupt(void) 
{ 
	/*C Receive a byte 																			*/
	SpiBufferOfReceipt[SpiPtrWriteBufferRx] = SSP1BUF;

	/*%C Increasing writing index 															*/
	SpiPtrWriteBufferRx ++;
	/*%C Modulo to re init writing Index 													*/
	/*%C when the maxi size of buffer is reached 										*/
	SpiPtrWriteBufferRx = SpiPtrWriteBufferRx % SPI_ST10_RECEIVE_BufferSize;

	/*%C send a byte */
	SSP1BUF = SpiArrayTransmitData[SpiArrayTransmitDataId];

	SpiArrayTransmitDataId ++;
	/*%C Check if it is the end of transmited data 										*/
	if (SpiArrayTransmitDataId == SPI_ST10_EndOfTableTransmit)
	{
		SpiArrayTransmitDataId = SPI_ST10_MSB_START_FRAME;
		DRV_SPI_ST10_Transmit();
	}

	PIR1bits.SSP1IF = 0;
}				
