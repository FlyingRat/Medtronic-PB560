/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505																		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Send_Frame.c 														*/
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
#include "enum.h"
#include "typedef.h"
#include "Driver_USB_Data.h"
#include "DRV_USB_Send_Frame.h"


/******************************************************************************/
/*                             #DEFINE		                        				*/
/******************************************************************************/


/******************************************************************************/
/*                   INTERNAL FUNCTION DECLARATION                    			*/
/******************************************************************************/
void DRV_USB_Send_Frame(void)
{
		/* Select the bridge */
		DRV_OutputPort(CE_SPI_USB,0) ;

/******************************************************************************/
/*%C USB Busy Inhibition interrupt	(CC10)	*/
/******************************************************************************/

		/*%C Reset the interrupt request flag (CC010 = USB_BUSY)	*/
		CC10IR = 0 ;
		/*%C Interrupt CC10 enable (USB BUSY)	*/
		CC10IE = 1 ;

/******************************************************************************/
/*%C  Reception PEC 7 Configuration	*/
/******************************************************************************/

		/*%C Upadate an UnReadyFlag*/

		/*%C Initialisation of source pointer, SPI_1 aderesse */
 		SRCP7	  = (UWORD16) (&XSSCRB)	;

		/*%C Initialisation of destination pointer, Tab */
		DSTP7 =	_sof_(PEC_Reception);

		/*%C Config PEC */
		/*%C 5 octets reserved */
		/*%C 2 octets INC : increment de l'@d dest */
		/*%C 1 octet BWT : envoie octet par octet */
		/*%C 8 octets COUNT : reception de 3 octets (2 octets du header + 1 pour*/
		/*%C ne pas passer dans l'interruption*/
		PECC7 = 0x0303 ;
												 
/******************************************************************************/
/*%C Emission PEC 6 Configuration	*/
/******************************************************************************/

		/*%C Initialisation of source pointer, Tab */
		SRCP6 = (UWORD16)(PEC_Emission);
					 
		/*%C Initialisation of destination pointer, SPI_1 aderesse */
	 	DSTP6	  = (UWORD16) (&XSSCTB) ;

		/*%C Config PEC */
		/*%C 5 octets reserved */
		/*%C 2 octets INC : increment de l'@d src */
		/*%C 1 octet BWT : envoie octet par octet */
		/*%C 8 octets COUNT : envoi de 1 octets (le 1er envoie est manuel)*/
		PECC6 = 0x0502;

/******************************************************************************/
/*%C PEC Inhibition interrupt	*/
/******************************************************************************/

		/*%C Authorization interrupt de X1, receive */	  
		XIR1SET = 0x0800 ;

		/*%C Authorization interrupt de X2, transmit */	  
		XIR2SET = 0x1000 ;

		/*%C Reset the interrupt request flag (XP2IR -> Receive)	*/
		XP2IR = 0 ;
		/*%C Interrupt XP2 enable (XP2IC)	*/
		XP2IE = 1 ;

		/*%C Reset the interrupt request flag (XP1IR -> Transmit)	*/
		XP1IR = 0 ;
		/*%C Interrupt XP1 enable (XP1IC)	*/
		XP1IE = 1 ;


/******************************************************************************/
/*%C Start data transmission */
/******************************************************************************/

		XP1IR = 1 ;
		
}