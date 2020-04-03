/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Init.c 																*/
/*																										*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C         																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#ifndef _TASKING
	#include "LH_ST10F276.h"
	#include <intrins.h>
#else	    
 		#include "regf276e.h"
#endif 	
#include "io_declare.h"

/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/
void DRV_USB_Init(void)
{


/******************************************************************************/
/*%C SPI Bus configuration 																	*/
/******************************************************************************/
	/*%C Clear XSSCCON to configure after	*/
	XSSCCONCLR = 0xFFFF;

/*%C (Acces to control bit) */
/*
		- Tranfer 16 bits
		- MSB first
		- Transition sur SSCPO = 1 et SSCPH = 0
		- Enable error flag
		- Master mode
*/
	XSSCCONSET = 0x4F57;

/*%C (Acces to status flag) */
/*
		- Transmission and reception enabled.
*/
	XSSCCONSET = 0xC000;


/******************************************************************************/
/*%C Speed configuration : 2MHz																*/
/******************************************************************************/

	XSSCBR = 0x0A;


/******************************************************************************/
/*%C Configuration of SPI interrupt */
/******************************************************************************/
		
	/*%C Clear Interrupt Flag Receive : Interrput_2 */
	XIR2CLR = 0x0010 ;
	
	/*%C SPI Receive GLVL = 15 ILVL = 3 (Use PEC 7)  */
	XP2IC = 0x3F ;

 	/*%C Clear Interrupt Flag Transmit : Interrput_1 */
	XIR1CLR = 0x0008 ;
	
	/*%C SPI Transmit GLVL = 15 ILVL = 2 (Use PEC 6)  */
	XP1IC = 0x3E ;

	/*%C Clear Interrupt Flag  SPI Error*/
	XIR3CLR = 0x0008 ;
	
	/*%C SPI Error Interrupt*/
	/*%IR = 0 ,IE = 1; ILVL  = 12 ,GLVL = 1 	 */
	XP3IC = 0x71 ;
	
	/*%C Enable Interrupt SPI Error*/
	XIR3SET = 0x0800 ;

/******************************************************************************/
/*%C Configuration of externel interrupt 2 (P2.10) : USB_BUSY on Faling edge	*/
/******************************************************************************/

	/*%C No capture compare, interrput on falling edge on P2_10  */				  
	CCM2 &= 0xF2FF ;
	CCM2 |= 0x0200 ;

	/*%C Config priority interrupt, P2_10 : CC10 */
	/*%IR = 0 ,IE = 0; ILVL  = 13 ,GLVL = 2 	 */
	CC10IC = 0x0036 ;
	
}