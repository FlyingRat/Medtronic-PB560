/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Init_CPU.c                                               		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          It is the entry point, the "main", of the software :            */
/*%C          It initializes the processor target (registers and variables)   */
/*%C          and launch the scheduler.                                       */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "io_declare.h"
#include "p18f6622.h"

/******************************************************************************/
/*                                		                          					*/
/******************************************************************************/

#pragma romdata CONFIG 
/*%C Ecriture d'ans l'espace de configuration du micro.*/
	/*%C Config1L. Non utilisé																	*/
	/*%C Config1H. Gestion oscillateur : oscillateur interne							*/
	/*%C Config2L. Brown out reset et power up timer : par défaut					*/
	/*%C Config2H. Gestion watchdog : watchdog activé periode = 131.6 ms			*/
	/*%C Postscaler = 1:32 ; Frequency = 31.125 kHz ; Counter = 128				*/
	/*%C Config3L. Non utilisé																	*/
	/*%C Config3H. Options MCLR pin, low power timer1 oscillator, PORTB A/D		*/
	/*%C 				et CCP2 mux : PORTB digital											*/
	/*%C Config4L. Options background debugger, extended instruction set,		*/
	/*%C 				single-supply ICSP, stack full/underflow reset : LVP activé	*/
	/*%C Config4H. Non utilisé																	*/
	/*%C Config5L. Protection du code : none												*/
	/*%C Config5H. Protection du code : none												*/	
	/*%C Config6L. Protection du code : none												*/	
	/*%C Config6H. Protection du code : none												*/	
	/*%C Config7L. Protection du code : none												*/
	/*%C Config7H. Protection du code : none												*/	
	const rom unsigned char configuration[14] = {0x00,
                                                 0x09,
                                                 0x0F,
                                                 0x0A,
                                                 0xF3,
                                                 0x82,	 
												 0xC1,
                                                 0x00,
                                                 0x0F,
                                                 0xC0,
                                                 0x0F,
                                                 0xA0,
                                                 0x0F,
                                                 0x40 };
#pragma romdata

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void INIT_CPU(void)
{
	/*%C CPU Clock programing  32Mhz															*/
 	/*%C Internal oscilator frequency 8MHz													*/
 	/*%C PLL *4 activé																			*/
 	OSCCON  = 0x70  ;
 	OSCTUNE = 0x40;
 	 
	/*%C Input / output configuration														*/

	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;
	PORTF = 0x00;
	PORTG = 0x00; 
	
	/*%C Input / Output control registers programing									*/
	/*%C 0 -> Output 1 -> Input																*/

	TRISA = 0xFF;
	TRISB = 0xAB; 
	TRISC = 0x9F; 
	TRISD = 0x00; 
	TRISE = 0x03; 
	TRISF = 0xFF; 
	TRISG = 0x05;

	/* TIMER_0 : UTILISATION POUR LE SCHEDULER 											*/	
	/* bit7 TMR0ON: Timer0 On/Off Control bit = 1										*/
	/* bit 6 T08BIT: Timer0 8-bit/16-bit Control bit = 1								*/
	/* bit 5 T0CS: Timer0 Clock Source Select bit = 0 									*/
	/* bit 4 T0SE: Timer0 Source Edge Select bit = 1 									*/
	/* bit 3 PSA: Timer0 Prescaler Assignment bit = 0									*/
	/* bit 2-0 T0PS2:T0PS0: Timer0 Prescaler Select bits = 101 						*/
			/* 111 = 1:256 Prescale value														*/
			/* 110 = 1:128 Prescale value 													*/
			/* 101 = 1:64 Prescale value														*/
			/* 100 = 1:32 Prescale value														*/
			/* 011 = 1:16 Prescale value														*/
			/* 010 = 1:8 Prescale value														*/
			/* 001 = 1:4 Prescale value														*/
			/* 000 = 1:2 Prescale value														*/
 	T0CON = 0xD5;
	
	/* TIMER_1 : UTILISATION POUR LA CAPTURE VENTILATEUR 								*/
	/*%C TIMER1 Control Register																*/
	/*%C bit 7 RD16: 16-bit Read/Write Mode Enable bit = 1 							*/
	/*%C bit 6 T1RUN: Timer1 System Clock Status bit = 1 								*/
	/*%C bit 5-4 T1CKPS1:T1CKPS0: Timer1 Input Clock Prescale Select bits = 10 */
	/*%C bit 3 T1OSCEN: Timer1 Oscillator Enable bit = 0 								*/
	/*%C bit 2 T1SYNC: Timer1 External Clock Input Synch Select bit = 0 			*/
	/*%C bit 1 TMR1CS: Timer1 Clock Source Select bit = 0 							*/
	/*%C bit 0 TMR1ON: Timer1 On bit = 1 													*/
	/*%C Timer clock 1uS																			*/
	T1CON = 0xF1; 

	/* TIMER_2 : NOT USE																			*/
	/*%C TIMER2 Control Register																*/
	/*%C bit 7 Unimplemented '0' 																*/	
	/*%C bit 6-3 Timer 2 Output Postcale 													*/
	/*%C bit 2 Timer 2 is OFF																	*/
	/*%C bit 1-0 Timer 2 Post Prescale 														*/
	T2CON = 0x01; 

	/* TIMER_3 : UTILISATION POUR TEMPO DE COMMUT 										*/
	/*%C Configuration du timer 3  															*/
	/*%C Configuration  des interruptions Registre INTCON2							*/	
	/*%C bit 7 Read Write mode enable bit= 0												*/
	/*%C bit 6 & 3	Timer 3 et timer 1 to CCPx enable bit =	0, 1					*/
	/*%C bit 5 - 4 Timer 3 prescale value = 00											*/
	/*%C bit 2 Timer 3 external clock synchro = 0										*/
	/*%C bit 1 Timer 3 clock source = 0														*/
	/*%C bit 0 Timer 3 ON bit = 1																*/
	T3CON = 0x09;								
	
	/* TIMER_4 : UTILISATION POUR LES COMMANDES PWM										*/
	/*%C TIMER4 Control Register																*/
	/*%C bit 7 Unimplemented '0' 																*/	
	/*%C bit 6-3 Timer 4 Output Postcale 													*/
	/*%C bit 2 Timer 4 is ON																	*/
	/*%C bit 1-0 Timer 4 Post Prescale 														*/
	T4CON = 0x04; 

	/* Timer 4 Period Register 																*/
	PR4 = 0x3F;

	/*%C Configuration  des interruptions Registre INTCON								*/
	/*%C bit 7 GIE/GIEH: Global Interrupt Enable bit (IPEN = 1) = 1				*/
	/*%C bit 6 PEIE/GIEL: Peripheral Interrupt Enable bit (IPEN = 1) = 1			*/
	/*%C bit 5 TMR0IE: TMR0 Overflow Interrupt Enable bit = 1 						*/
	/*%C bit 4 INT0IE: INT0 External Interrupt Enable bit = 0						*/
	/*%C bit 3 RBIE: RB Port Change Interrupt Enable bit = 0							*/
	/*%C bit 2 TMR0IF: TMR0 Overflow Interrupt Flag bit = 0							*/
	/*%C bit 1 INT0IF: INT0 External Interrupt Flag bit = 0							*/
	/*%C bit 0 RBIF: RB Port Change Interrupt Flag bit = 0							*/
	INTCON = 0xD0;
	
	/*%C Configuration  des interruptions Registre INTCON2							*/	
	/*%C bit 7 RBPU: PORTB Pull-up Enable bit	= 0										*/
	/*%C bit 6 INTEDG0: External Interrupt 0 Edge Select bit = 1					*/
	/*%C bit 5 INTEDG1: External Interrupt 1 Edge Select bit	= 1					*/
	/*%C bit 4 INTEDG2: External Interrupt 2 Edge Select bit = 0					*/
	/*%C bit 3 INTEDG3: External Interrupt 3 Edge Select bit = 0					*/
	/*%C bit 2 TMR0IP: TMR0 Overflow Interrupt Priority bit = 1						*/
	/*%C bit 1 INT3IP: INT3 External Interrupt Priority bit = 0						*/
	/*%C bit 0 RBIP: RB Port Change Interrupt Priority bit =	0						*/
	INTCON2 = 0x64;
	
	/*%C Configuration  des interruptions Registre INTCON3							*/	
	/*%C bit 7 INT2IP: INT2 External Interrupt Priority bit = 0						*/
	/*%C bit 6 INT1IP: INT1 External Interrupt Priority bit = 1						*/
	/*%C bit 5 INT3IE: INT3 External Interrupt Enable bit = 0						*/
	/*%C bit 4 INT2IE: INT2 External Interrupt Enable bit = 0						*/
	/*%C bit 3 INT1IE: INT1 External Interrupt Enable bit = 0						*/
	/*%C bit 2 INT3IF: INT3 External Interrupt Flag bit = 0 							*/
	/*%C bit 1 INT2IF: INT2 External Interrupt Flag bit = 0							*/
	/*%C bit 0 INT1IF: INT1 External Interrupt Flag bit = 0							*/				
	INTCON3 = 0x40;

	/*%C Interruption	flags reset																*/
	PIR1 = 0x10;	
	PIR2 = 0x00;
	PIR3 = 0x10;
	
	/*%C bit 7 PSPIE: Parallel Slave Port Read/Write Interrupt Enable = 0 		*/
	/*%C bit 6 ADIE: A/D Converter Interrupt Enable bit = 0 							*/
	/*%C bit 5 RC1IE: EUSART1 Receive Interrupt Enable bit = 1 						*/
	/*%C bit 4 TX1IE: EUSART1 Transmit Interrupt Enable bit = 1 					*/
	/*%C bit 3 SSP1IE: MSSP1 Interrupt Enable bit = 1 									*/	
	/*%C bit 2 CCP1IE: ECCP1 Interrupt Enable bit = 1 									*/
	/*%C bit 1 TMR2IE: TMR2 to PR2 Match Interrupt Enable bit = 0 					*/
	/*%C bit 0 TMR1IE: TMR1 Overflow Interrupt Enable bit = 0						*/ 
	PIE1 = 0x00;

	/*%C bit 7 OSCFIE: Oscillator Fail Interrupt Enable bit = 0 					*/
	/*%C bit 6 CMIE: Comparator Interrupt Enable bit = 0 								*/	
	/*%C bit 5 Unimplemented: Read as ‘0’ = 0 											*/
	/*%C bit 4 EEIE: Interrupt Enable bit = 0 											*/
	/*%C bit 3 BCL1IE: MSSP1 Bus Collision Interrupt Enable bit = 0 				*/
	/*%C bit 2 HLVDIE: High/Low-Voltage Detect Interrupt Enable bit = 0 			*/
	/*%C bit 1 TMR3IE: TMR3 Overflow Interrupt Enable bit = 0 						*/
	/*%C bit 0 CCP2IE: ECCP2 Interrupt Enable bit = 0 									*/
	PIE2 = 0x00;

	/*%C bit 7 SSP2IE: MSSP2 Interrupt Enable bit = 0 									*/
	/*%C bit 6 BCL2IE: MSSP2 Bus Collision Interrupt Enable bit = 0 				*/
	/*%C bit 5 RC2IE: EUSART2 Receive Interrupt Enable bit = 0 						*/
	/*%C bit 4 TX2IE: EUSART2 Transmit Interrupt Enable bit = 0 					*/
	/*%C bit 3 TMR4IE: TMR4 to PR4 Match Interrupt Enable bit = 0 					*/
	/*%C bit 2 CCP5IE: CCP5 Interrupt Enable bit = 1 									*/ 
	/*%C bit 1 CCP4IE: CCP4 Interrupt Enable bit = 1 									*/
	/*%C bit 0 CCP3IE: ECCP3 Interrupt Enable bit = 0 									*/
	PIE3 = 0x00;
	
	/*%C Interupt priority level																*/
	/*%C bit 7 PSPIP: Parallel Slave Port R/W Interrupt Priority bit = 0 		*/
	/*%C bit 6 ADIP: A/D Converter Interrupt Priority bit	= 0 						*/
	/*%C bit 5 RC1IP: EUSART1 Receive Interrupt Priority bit = 0 					*/
	/*%C bit 4 TX1IP: EUSART1 Transmit Interrupt Priority bit = 0 					*/
	/*%C bit 3 SSP1IP: MSSP1 Interrupt Priority bit = 0 								*/
	/*%C bit 2 CCP1IP: ECCP1 Interrupt Priority bit = 0 								*/
	/*%C bit 1 TMR2IP: TMR2 to PR2 Match Interrupt Priority bit = 0 				*/
	/*%C bit 0 TMR1IP: TMR1 Overflow Interrupt Priority bit = 0 					*/
	IPR1 = 0xFF;
	
	/*%C Interupt priority level																*/
	/*%C bit 7 OSCFIP: Oscillator Fail Interrupt Priority bit = 0 					*/
	/*%C bit 6 CMIP: Comparator Interrupt Priority bit = 0 							*/
	/*%C bit 5 Unimplemented: Read as ‘0’ = 0 											*/
	/*%C bit 4 EEIP: Interrupt Priority bit = 0 											*/
	/*%C bit 3 BCL1IP: MSSP1 Bus Collision Interrupt Priority bit = 0 			*/
	/*%C bit 2 HLVDIP: High/Low-Voltage Detect Interrupt Priority bit = 0 		*/
	/*%C bit 1 TMR3IP: TMR3 Overflow Interrupt Priority bit = 0 					*/
	/*%C bit 0 CCP2IP: ECCP2 Interrupt Priority bit = 0 								*/
	IPR2 = 0xFF;

	/*%C Interupt priority level																*/
	/*%C bit 7 SSP2IP: MSSP2 Interrupt Priority bit = 0								*/
	/*%C bit 6 BCL2IP: MSSP2 Bus Collision Interrupt Priority bit = 0 			*/
	/*%C bit 5 RC2IP: EUSART2 Receive Interrupt Priority bit = 0 					*/
	/*%C bit 4 TX2IP: EUSART2 Transmit Interrupt Priority bit = 0 					*/
	/*%C bit 3 TMR4IP: TMR4 to PR4 Match Interrupt Priority bit = 0 				*/
	/*%C bit 2 CCP5IP: CCP5 Interrupt Priority bit = 0 								*/
 	/*%C bit 1 CCP4IP: CCP4 Interrupt Priority bit = 0 								*/
	/*%C bit 0 CCP3IP: ECCP3 Interrupt Priority bit = 0 								*/
	IPR3 = 0xFF;
	
	/*%C Configuration Reset Control Register RCON 										*/
	/*%C bit 7 IPEN: Interrupt Priority Enable bit = 1 								*/
	/*%C bit 6 SBOREN: Software BOR Enable bit = 										*/
	/*%C bit 5 Unimplemented: Read as ‘0’ =  												*/
	/*%C bit 4 RI: RESET Instruction Flag bit = 											*/
	/*%C bit 3 TO: Watchdog Timer Time-out Flag bit = 									*/
	/*%C bit 2 PD: Power-Down Detection Flag bit = 										*/
	/*%C bit 1 POR: Power-on Reset Status bit = 											*/
	/*%C bit 0 BOR: Brown-out Reset Status bit = 										*/
	RCON = 0x80;

	/* Configuration  PWM registrer 															*/
	/*%C bit 7-6 Unimplemented: Read as ‘0’ 												*/
	/*%C bit 5-4 DCxB1:DCxB0: PWM Duty Cycle bit 1 and bit 0 for CCP Module x 	*/
		/*%C Capture mode: Unused.																*/
		/*%C Compare mode: Unused.																*/
		/*%C PWM mode: two Least Significant bits of the 10-bit PWM duty cycle	*/
	/*%C bit 3-0 CCPxM3:CCPxM0: CCP Module x Mode Select bits 						*/
		/*%C 0000 = Capture/Compare/PWM disabled; resets CCPx module 				*/
		/*%C 0001 = Reserved 																	*/
		/*%C 0010 = Compare mode, toggle output on match; CCPxIF bit is set 		*/
		/*%C 0011 = Reserved 																	*/
		/*%C 0100 = Capture mode, every falling edge 									*/
		/*%C 0101 = Capture mode, every rising edge 										*/
		/*%C 0110 = Capture mode, every 4th rising edge 								*/
		/*%C 0111 = Capture mode, every 16th rising edge 								*/
		/*%C 1000 = Compare mode, initialize CCPx pin low								*/
		/*%C 1001 = Compare mode, initialize CCPx pin high								*/
		/*%C 1010 = Compare mode, generate software interrupt on compare match	*/
		/*%C 1011 = Compare mode, trigger special event									*/
	CCP1CON = 0x05;
	CCP2CON = 0x0C;
	CCP4CON = 0x0C;
	CCP5CON = 0x0C; 

	/*%C Configuration Duty Cycle CCPRxL:CCPxCON<5:4>									*/
	/* 8 MSB : CCPRxL and 2 LSB CCPxCON<5:4> 												*/
	PWM_CMD_VENTIL = 0x00;
	PWM_VCHARGE 	= 0x00;
	PWM_ICHARGE 	= 0x00;

	/*%C Run WatchDog																				*/
	ClrWdt();
	/*%C Activation du WatchDog																*/
	WDTCON = 1;

}
