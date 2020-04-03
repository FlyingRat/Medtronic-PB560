/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_SPI_POWER_Launch.c                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     Send a byte to the PIC and receive a byte from it	  */
/*%C         			 Duration = 17 us (04/09/06)						  */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif	
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "io_declare.h"
#include "DB_Control.h"
#include "DRV_SPI_POWER_Launch.h"
#include "DRV_SPI_POWER_Data.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_SPI_POWER_Launch(void)
{		
	UBYTE ComputeCRC;
	UBYTE Idx;

	/*%CConfiguration of the SPI bus speed 1.8Mhz								*/
	/*						SSCBR = FOSC / ( 2 . BAUD ) - 1						*/
	/*Adapter le time out du WaitEndTransmit si modification de SSCBR			*/
	SSCBR  = 0x000A;		/* 1.8MHz	*/

	SPI_PORT |= 0x2200;

	/*%C enable chip enable Power board											*/
	DRV_OutputPort(CE_SPI_PIC_IC44, 1);
	DRV_OutputPort(CE_SPI_PIC, 0);	 
 	/*%C management of Power board hardware										*/
	if (SpiArrayTransmitDataId == SPI_POWER_TRANSMIT_START_FRAME_MSB)
	{
		/*%C get and copy the VENTIL_AUTHORIZATION value 						*/
		SpiArrayTransmitData[SPI_POWER_TRANSMIT_VENTIL_AUTHORIZATION] 
										= (UBYTE)DB_ControlRead(VENTIL_AUTHORIZATION_U16);
		SpiArrayTransmitData[SPI_POWER_TRANSMIT_MAINTENANCE_MODE]
										= (UBYTE)DB_ControlRead(MAINTENANCE_MODE_U16);

		SpiArrayTransmitData[SPI_POWER_TRANSMIT_CALIBRATION_MODE]
										= (UBYTE)DB_ControlRead(CALIBRATION_MODE_U16);

		/*%C Compute CRC														*/
		ComputeCRC = 0;
		for (	Idx = SPI_POWER_TRANSMIT_START_FRAME_MSB; 
				Idx != SPI_POWER_TRANSMIT_CRC; 
				Idx++)
		{
			ComputeCRC ^= SpiArrayTransmitData[Idx];
		}
		SpiArrayTransmitData[SPI_POWER_TRANSMIT_CRC] = ComputeCRC;
	}

	
	/*%C send a byte of the transmit frame										*/
	SSCTB = SpiArrayTransmitData[SpiArrayTransmitDataId];
	SpiArrayTransmitDataId ++;
	if	(SpiArrayTransmitDataId >= SPI_POWER_TRANSMIT_EndOfFrame)
		SpiArrayTransmitDataId = SPI_POWER_TRANSMIT_START_FRAME_MSB;

	/*%C waiting the end of transmission 										*/
	DRV_SPI_POWER_WaitEndTransmit();
	/*%C read a byte from the reception buffer									*/
	SpiBufferOfReceipt[SpiPtrWriteBufferRx] = (UBYTE)SSCRB;
 	SpiPtrWriteBufferRx ++;
	SpiPtrWriteBufferRx = (UBYTE)(SpiPtrWriteBufferRx % SPI_POWER_RECEIVE_BufferSize);
	/*%C disable chip enable Power board										*/
	DRV_OutputPort(CE_SPI_PIC, 1);
	DRV_OutputPort(CE_SPI_PIC_IC44, 0);
	
}


