/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INIT_SPI_ST10_Driver.c                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          Microcontroler SPI Registers Configuration     				      */
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
	#define DECLARATION_SPI_ST10_DATA
#include "DRV_SPI_ST10_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void INIT_SPI_ST10_Driver(void)
{
	/*%C Configuration des registres du microcontroleur 								*/
	/*%C SPI Slave Mode																			*/
	SSP1STAT = 0x00;  /* mode slave ; sck sur front montant 							*/
	SSP1CON1 = 0x34;
		
	SpiPtrReadBufferRx = 0;
 	SpiPtrWriteBufferRx = 0;
	
	/*%C Init frame transmit value remote 		   */
	/*%C MSB Header																				*/
	SpiArrayTransmitData[SPI_ST10_MSB_START_FRAME] = MSB_START_FRAME_VALUE;	
	/*%C MSB Header																				*/
	SpiArrayTransmitData[SPI_ST10_LSB_START_FRAME] = LSB_START_FRAME_VALUE;			
	/*%C End of frame character																*/
	SpiArrayTransmitData[SPI_ST10_END_FRAME]       = (UWORD16)END_FRAME_VALUE;
	SpiEndOfTransmit = TRUE;

	PIR1bits.SSP1IF = 0;
	PIE1bits.SSP1IE = 1;

	/*%C Run WatchDog */
	ClrWdt();
}
