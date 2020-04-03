/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INIT_RS232_Driver.c															*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          Microcontroler UART Registers Configuration     				      */
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
	#define DECLARATION_RS232_DATA
#include "DRV_RS232_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void INIT_RS232_Driver(void)
{
	/*%C Configuration des registres du microcontroleur 								*/
	
	/*%C TXSTA: TRANSMIT STATUS AND CONTROL REGISTER 									*/
	/*%C bit 7 CSRC: Clock Source Select bit : Asynchronous = 0						*/
	/*%C bit 6 TX9: 9-bit Transmit Enable bit :8-bit transmission = 0				*/
	/*%C bit 5 TXEN: Transmit Enable bit : enabled = 1									*/
	/*%C bit 4 SYNC: EUSART Mode Select bit : Asynchronous mode	=0					*/
	/*%C bit 3 SENDB: Send Break Character bit : transmission completed = 0		*/
	/*%C bit 2 BRGH: High Baud Rate Select bit : High speed = 1						*/
	/*%C bit 1 TRMT: Transmit Shift Register Status bit : TSR empty = 1			*/
	/*%C bit 0 TX9D: 9th bit of Transmit Data : =0										*/
	/*%C TXSTA = 0b0010 0110																	*/		
	TXSTA2 = 0x06;

	/*%C RECEIVE STATUS AND CONTROL REGISTER			  */
	/*%C bit 7 SPEN: Serial Port Enable bit : enabled = 1 							*/
	/*%C bit 6 RX9: 9-bit Receive Enable bit : 8 bits recpetion	= 0				*/
	/*%C bit 5 SREN: Single Receive Enable bit :0										*/
	/*%C bit 4 CREN: Continuous Receive Enable bit : enabled = 1					*/
	/*%C bit 3 ADDEN: Address Detect Enable bit : disabled = 0						*/
	/*%C bit 2 FERR: Framing Error bit : No error = 0									*/
	/*%C bit 1 OERR: Overrun Error bit : No error = 0									*/
	/*%C bit 0 RX9D: 9th bit of Received Data												*/
	/*%C RCSTA = 0b1001 0000																	*/
	RCSTA2 = 0x90;

	/*%C BAUDCON: BAUD RATE CONTROL REGISTER		 */
   /*%C bit 7 ABDOVF: Auto-Baud Acquisition Rollover Status bit : none = 0 	*/
	/*%C bit 6 RCIDL: Receive Operation Idle Status bit : active = 0				*/
	/*%C bit 5 Unimplemented: Read as 0														*/
	/*%C bit 4 SCKP: Synchronous Clock Polarity Select bit : low level = 0		*/
	/*%C bit 3 BRG16: 16-bit Baud Rate Register Enable bit : 8 bit					*/
	/*%C bit 2 Unimplemented: Read as 0														*/
	/*%C bit 1 WUE: Wake-up Enable bit : unused = 0										*/
	/*%C bit 0 ABDEN: Auto-Baud Detect Enable bit : disabled = 0					*/
	/*%C BAUDCON = 0b0000000																	*/
	BAUDCON2 = 0x00;
	
	/*%C BRG Baud Rate Generator																*/
	/*%C Baud Rate = FOSC/[16 (n + 1)] if BRGH of TXSTA = 1							*/
	/*%C BRG = 103 ,Fosc 32.256 MHz --> BR = 19200 bauds								*/
	SPBRG2 = 103;
	
	PtrReadBufferRx = 0;
 	PtrWriteBufferRx = 0;
	Rs232_State = DRV_RS232_TRANSMIT_STOP;
	/*%C Init frame transmit value remote 	*/
	/*%C MSB Header		  */		
	ArrayTxData[MSB_START_FRAME] = MSB_START_FRAME_VALUE;	
	/*%C MSB Header																				*/
	ArrayTxData[LSB_START_FRAME] = LSB_START_FRAME_VALUE;			
	/*%C End of frame character																*/
	ArrayTxData[END_FRAME]       = (UWORD16)END_FRAME_VALUE;
	EndOfTransmit = TRUE;
	/*%C RS232 Recept Interrupt enabled 													*/
	PIE3bits.RC2IE = 1;

	/*%C Run WatchDog */
	ClrWdt();
}
