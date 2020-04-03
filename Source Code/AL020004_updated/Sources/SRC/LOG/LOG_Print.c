/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : LOG_Print.c                                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

#include "p18f6622.h"
#include "LOG_Config.h"
#include "LOG_Print.h"
#include "stdio.h"

static unsigned long print_activated_modules = 0;
static unsigned int print_current_level = CFG_LOG_LVL_DEBUG;
static void init_hardware(void);

int LOG_Print(auto FILE *f, unsigned long module, unsigned int level, auto const MEM_MODEL rom char *fmt, ...)
{
	va_list args; 	

	if (module & print_activated_modules)
	{ 
		if (level <= print_current_level)
		{
			va_start (args, fmt);
			vfprintf (f, fmt, args);
			va_end (args);
		}
	}
	ClrWdt(); /* clear watchdog */
}

int LOG_Print_Init(void)
{
	init_hardware();

	LOG_Print_Set_Activated_Modules(CFG_LOG_ACTIVATED_MODS);
	LOG_Print_Set_level(CFG_LOG_CURRENT_LEVEL);
}

int LOG_Print_Set_Activated_Modules(unsigned long modules)
{
	print_activated_modules = modules;
}

int LOG_Print_Set_level(unsigned int level)
{
	print_current_level = level;
}

int _user_putc(char c)
{	
	/* polling mode */
	while((TXSTA2 & 0x02) == 0); 	/* TRMT bit : while shift register not empty, wait */
	TXREG2 = c;
	TXSTA2 |= 0x20; /* TXEN = 1 to start transmitting */
}

void init_hardware(void)
{
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

	/* Forbid tx interrupt cause we're in polling mode ! */
	PIE3bits.TX2IE = 0;
}
