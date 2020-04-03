/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_SPIU_ST10_Read_Buffer.c												*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                      max duration = 250 us (12/09/2006)				  		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "p18f6622.h"
#include "define.h"
#include "enum.h"
#include "IO_Declare.h"
#include "typedef.h"
#include "DB_PowerSupply.h"
#include "DRV_SPI_ST10_Data.h"
#include "DRV_SPI_ST10_ReadBuffer.h"

#include "define.h"

UWORD16 Idx;
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_SPI_ST10_ReadBuffer(void)
{
	UBYTE Ventil = 0;
	UWORD16 i;
	UBYTE  ComputeCRC = 0;
	

	/*%C Quit the function when the buffer is empty										*/
	if (SpiPtrReadBufferRx == SpiPtrWriteBufferRx) 
	{
		return;
	}


	/*%C Check for the MSB */
	while (	(SpiBufferOfReceipt[SpiPtrReadBufferRx ]!= MSB_START_FRAME_VALUE) 
			&&	(SpiPtrReadBufferRx != SpiPtrWriteBufferRx ))
	{
		/*%C Increase and modulo on the buffer size for an automatic re-init 	*/
		SpiPtrReadBufferRx = ((SpiPtrReadBufferRx + 1) % SPI_ST10_RECEIVE_BufferSize);
	}



	/*%C When the commad frame is complete													*/
	/*%C When Size of receiving buffer - Index on read buffer						*/
	/*%C + Index on writting buffer modulo Size of receiving buffer				*/
	/*%C is higher or equal to 6																*/
	if (((SPI_ST10_RECEIVE_BufferSize - SpiPtrReadBufferRx + SpiPtrWriteBufferRx) % SPI_ST10_RECEIVE_BufferSize) >= SPI_ST10_RECEIVE_EndOfFrame)
	{
	
		/*%C Received frames CRC computing													*/
		/*%C initializing  computed CRC														*/
		ComputeCRC = 0;
		for (Idx = (UWORD16)SpiPtrReadBufferRx ; Idx != ((UWORD16)SpiPtrReadBufferRx + SPI_ST10_RECEIVE_CRC)%SPI_ST10_RECEIVE_BufferSize ; Idx = (Idx + 1) % SPI_ST10_RECEIVE_BufferSize)
		{
			/*%C Update of Computed CRC														*/
			ComputeCRC ^= (UBYTE)SpiBufferOfReceipt[Idx];
		}
		
		/*%C	Check the CRC value and the end of frame									*/
		if (	(SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_ST10_RECEIVE_CRC) %SPI_ST10_RECEIVE_BufferSize] 					== ComputeCRC) 
			&& (SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_ST10_RECEIVE_END_FRAME) %SPI_ST10_RECEIVE_BufferSize] 			== END_FRAME_VALUE)
			&& (SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_ST10_RECEIVE_START_FRAME_MSB) %SPI_ST10_RECEIVE_BufferSize] 	== MSB_START_FRAME_VALUE)
			&& (SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_ST10_RECEIVE_START_FRAME_LSB) %SPI_ST10_RECEIVE_BufferSize] 	== LSB_START_FRAME_VALUE) )

		{
			/*C Update the VENTIL_AUTHORIZATION flag in data bases  					*/
				DB_PowerSupply_Write(VENTIL_AUTHORIZATION,
										SpiBufferOfReceipt[(SpiPtrReadBufferRx 
										+ SPI_ST10_RECEIVE_VENTIL_AUTHORIZATION)
										%SPI_ST10_RECEIVE_BufferSize]
										);
		
			/*C Update the MAINTENANCE_MODE flag in data bases  						*/
				DB_PowerSupply_Write(MAINTENANCE_MODE,
										SpiBufferOfReceipt[(SpiPtrReadBufferRx 
										+ SPI_ST10_RECEIVE_MAINTENANCE_FLAG)
										%SPI_ST10_RECEIVE_BufferSize]
										);
		
			/*C Update the CALIBRATION_MODE flag in data bases  						*/
				DB_PowerSupply_Write(CALIBRATION_MODE,
										SpiBufferOfReceipt[(SpiPtrReadBufferRx 
										+ SPI_ST10_RECEIVE_CALIBRATION_FLAG)
										%SPI_ST10_RECEIVE_BufferSize]
										);

				/*C  Increasing reading Index to acces to the next frame  			*/
				SpiPtrReadBufferRx = (SpiPtrReadBufferRx + SPI_ST10_RECEIVE_EndOfFrame) % SPI_ST10_RECEIVE_BufferSize ;
		
				/*C  Start decounter when the frame is correct							*/
				TIM_StartDecounter16(TIM_SPI_WRONG_FRAME,TIME_TWO_FRAMES_SPI_RECEIVE);
				/*C  Update the frame status flag											*/
				DRV_SPI_ST10_Status = DRV_SPI_ST10_NO_ERROR;
		}
		/*C Error case 																			*/
		else
		/*C increasing Reading Index 															*/
		{
			SpiPtrReadBufferRx = (SpiPtrReadBufferRx + 1) % SPI_ST10_RECEIVE_BufferSize ;

			/* Check for too much consecutive bad frames 								*/
			if(TIM_ReadValue16(TIM_SPI_WRONG_FRAME)== 0)
			{
			/*C Indication of consecutives frame errors 									*/
			/*%C in the SPI status word 														*/
				DRV_SPI_ST10_Status = DRV_SPI_ST10_BAD_FRAME;
			}
			else
			{
				/*%C No Function */
			}
		}	
	}
}

