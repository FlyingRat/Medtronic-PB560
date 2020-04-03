/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INIT_EEPROM_BAT_Driver.c													*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          Microcontroler UART Registers Configuration     				      */
/*%C 						Initialization of the DS2480B										*/
/*%C Initialization of the two memories array (Ram_Read_Bat and Ram_Write_Bat)*/
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
#include "DRV_EEPROM_BAT_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void INIT_EEPROM_BAT_Driver(void)
{	
	/*%C************************************************************************/
	/*%C Configuration des registres du microcontroleur 								*/
	/*%C************************************************************************/

	/*%C RECEIVE STATUS AND CONTROL REGISTER		 */
	/*%C bit 7 SPEN: Serial Port Enable bit : enabled = 1 							*/
	/*%C bit 6 RX9: 9-bit Receive Enable bit : 8 bits recpetion	= 0				*/
	/*%C bit 5 SREN: Single Receive Enable bit :0										*/
	/*%C bit 4 CREN: Continuous Receive Enable bit : enabled = 1					*/
	/*%C bit 3 ADDEN: Address Detect Enable bit : disabled = 0						*/
	/*%C bit 2 FERR: Framing Error bit : No error = 0									*/
	/*%C bit 1 OERR: Overrun Error bit : No error = 0									*/
	/*%C bit 0 RX9D: 9th bit of Received Data												*/
	/*%C RCSTA = 0b1001 0000																	*/
	RCSTA1 = 0x90;

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
	TXSTA1 = 0x26;

	/*%C BAUDCON: BAUD RATE CONTROL REGISTER	   */
   /*%C bit 7 ABDOVF: Auto-Baud Acquisition Rollover Status bit : none = 0 	*/
	/*%C bit 6 RCIDL: Receive Operation Idle Status bit : active = 0				*/
	/*%C bit 5 Unimplemented: Read as 0														*/
	/*%C bit 4 SCKP: Synchronous Clock Polarity Select bit : low level = 0		*/
	/*%C bit 3 BRG16: 16-bit Baud Rate Register Enable bit : 8 bit					*/
	/*%C bit 2 Unimplemented: Read as 0														*/
	/*%C bit 1 WUE: Wake-up Enable bit : unused = 0										*/
	/*%C bit 0 ABDEN: Auto-Baud Detect Enable bit : disabled = 0					*/
	/*%C BAUDCON = 0b0000000																	*/
	BAUDCON1 = 0x00;
	
	/*%C BRG Baud Rate Generator																*/
	/*%C Baud Rate = FOSC/[16 (n + 1)] if BRGH of TXSTA = 1							*/
	/*%C BRG = CF ,Fosc 32.256 MHz --> BR = 9600 bauds									*/
	SPBRG1= 0xCF;

	/*%C EUSART1 Receive Interrupt Enable bit												*/
	PIE1bits.RC1IE = 1;


	/*%C************************************************************************/
	/*%C Send break to reset the the DS2480B												*/
	/*%C************************************************************************/
	TXSTA1 = 0x00;    	/* TX off															*/
	TMR3H = 0xC1;			/* Temporasation 2ms												*/
	TMR3L = 0x7F;
	PIR2bits.TMR3IF = 0;
	while (PIR2bits.TMR3IF == 0);	/* End of tempo										*/

	TXSTA1 = 0x26; 		/* TX on																*/
	TMR3H = 0xC1;			/* Temporasation 2ms												*/
	TMR3L = 0x7F;
	PIR2bits.TMR3IF = 0;
	while (PIR2bits.TMR3IF == 0);	/* End of tempo										*/
	
	/*%C************************************************************************/
	/*%C Initialization of the DS2480B														*/
	/*%C************************************************************************/
	Flag_Answer_EEPROM_BAT = FALSE;

	TXREG1=0xC1;	/* Send timing byte														*/
	
	/* Set the Flex configuration parameters												*/
	TXREG1=0x17;	/* PDSRC=1.37V/µs.	Answer 0x16 is waited.						*/
	TMR3H = 0x63;	/* Temporasation 5ms														*/
	TMR3L = 0xBF;
	PIR2bits.TMR3IF = 0;
	while(Flag_Answer_EEPROM_BAT == FALSE && PIR2bits.TMR3IF ==0);
	Flag_Answer_EEPROM_BAT=FALSE;
	
	TXREG1=0x45;	/* W1LD=10µs.	Answer 0x44 is waited.								*/
	TMR3H = 0x63;	/* Temporasation 5ms														*/
	TMR3L = 0xBF;
	PIR2bits.TMR3IF = 0;
	while(Flag_Answer_EEPROM_BAT == FALSE && PIR2bits.TMR3IF ==0);
	Flag_Answer_EEPROM_BAT=FALSE;

	TXREG1=0x5B;	/* DSO/WORT=8µs.	Answer 0x5A is waited.							*/
	TMR3H = 0x63;	/* Temporasation 5ms														*/
	TMR3L = 0xBF;
	PIR2bits.TMR3IF = 0;
	while(Flag_Answer_EEPROM_BAT == FALSE && PIR2bits.TMR3IF ==0);
	Flag_Answer_EEPROM_BAT=FALSE;
	
	TXREG1=0x0F;	/* Read Baud Rate (RBR).Answer 0x00 is waited  (-> 9600)		*/
	TMR3H = 0x63;	/* Temporasation 5ms														*/
	TMR3L = 0xBF;
	PIR2bits.TMR3IF = 0;
	while(Flag_Answer_EEPROM_BAT == FALSE && PIR2bits.TMR3IF ==0);
	Flag_Answer_EEPROM_BAT=FALSE;
	
	TXREG1=0x91;	/*Send a 1-Wire bit to test 1-Wire block.	Answer 0x93 is waited.*/
	TMR3H = 0x63;	/* Temporasation 5ms														*/
	TMR3L = 0xBF;
	PIR2bits.TMR3IF = 0;
	while(Flag_Answer_EEPROM_BAT == FALSE && PIR2bits.TMR3IF ==0);
	Flag_Answer_EEPROM_BAT=FALSE;

	/*%C Run WatchDog */
	ClrWdt();
}
