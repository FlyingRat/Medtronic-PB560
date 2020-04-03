/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INIT_Sample.c																	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   Gestion des interruptions basse priorité   				*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES											*/
/******************************************************************************/

#include "p18f6622.h"
#include "define.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void INIT_Sample(void)
{
	/* %C Configuration du registre de controle 0 du convertisseur A/N			*/
		
	/*%C bit 7-6 Unimplemented: Read as ‘0’												*/
	/*%C bit 5-2 CHS3:CHS0: Analog Channel Select bits									*/
	/*%C 0001 = Channel 1 (AN1)																*/
	/*%C bit 1 GO/DONE: A/D Conversion Status bit										*/
	/*%C 0 = A/D Idle																				*/
	/*%C bit 0 ADON: A/D On bit																*/
	/*%C 1 = A/D converter module is enabled												*/
	/*%C ADCON0 = 0b0000 0001																	*/
	ADCON0 = 0x01;
	
	/*%C Configuration du registre de controle 1  du convertisseur A/N 			*/
	/*%C bit 7-6 Unimplemented: Read as ‘0’												*/
	/*%C bit 5-4 PCFG3:PCFG0: A/D Port Configuration Control bits:) 				*/
	/*%C 		AVDD / AVSS  : 00  																*/
	/*%C bit 3-0 PCFG3:PCFG0: A/D Port Configuration Control bits: 				*/
	/*%C 		AN11 Analog Input 0011 															*/
	/*%C 		ADCON1 =0b0000 0011 																*/
	ADCON1 = 0x13;
	
	/*%C Configuration du registre de controle 1  du convertisseur A/N 			*/
	/*%C bit 7 ADFM: A/D Result Format Select bit 										*/
	/*%C 		//1 = Right justified 															*/
	/*%C bit 6 Unimplemented: Read as ‘0’ 													*/
	/*%C bit 5-3 ACQT2:ACQT0: A/D Acquisition Time Select bits 						*/
	/*%C 						111 = 20 TAD 														*/
	/*%C bit 2-0 ADCS2:ADCS0: A/D Conversion Clock Select bits 						*/
	/*%C						110 = FOSC/64	 													*/
	/*%C 	ADCON2 = 0b1011 1110 																*/
	ADCON2 = 0xBE;
	
	/* Demande de conversion 																	*/
	ADCON0bits.GO = 1;

	/*%C Demande de conversion de la voie Measure DC */
	ADCON0 = MEASURE_VDC_CHANNEL ;

	/*%C Run WatchDog */
	ClrWdt();

}
