/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_CheckPageAndRetransmitAddress.c                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  EEPROM memory page check and address transmission if page change        */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   NONE                                                */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
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
#include "io_declare.h"
#include "enum.h"
#include "DRV_CheckPageAndRetransmitAddress.h"

void	DRV_CheckPageAndRetransmitAddress(UWORD16 Address)
{
	//Vérification si début de page mémoire eeprom	 (page de 32 octets)
	if (Address % 32 == 0) 
		{
    	DRV_EEP_tempo_CE();	  	// tempo Chip select disable
		DRV_OutputPort(CE_EEP, 1); // Desactivation chip enable EEPROM
		DRV_EEP_tempo_CE();     // tempo Chip select disable
		DRV_OutputPort(CE_EEP, 0); // Activation chip enable EEPROM
		do
			{
			//Contrôle mémoire eeprom libre (pas d'écriture en cours)
			DRV_OutputPort(CE_EEP, 0); // Activation chip enable EEPROM
			SSCTB  = 0x0005;          // Envoi de l'instruction RDSR	 activation de l'écriture eeprom
			DRV_EEP_WaitEndTransmit();// attente de fin de transmission sur le SPI
			SSCTB  = 0x0000;	        // generation horloge SCLK_SPI_CPU pour la lecture du status EEPROM
			DRV_EEP_WaitEndTransmit();// attente de fin de transmission sur le SPI
			DRV_OutputPort(CE_EEP, 1); // Desactivation chip enable EEPROM
			DRV_EEP_tempo_CE();		  // activation chip enable EEPROM
			}
		while ((SSCRB & 0x0001)  != 0x00); 	  //vérification si écriture en cours
		//Transmission de l'adresse ( page mémoire suivante)
		DRV_OutputPort(CE_EEP, 0); // Activation chip enable EEPROM
		SSCTB   = 0x0006;         // Envoi de l'instruction WREN
		DRV_EEP_WaitEndTransmit();// attente de fin de transmission sur le SPI
		DRV_OutputPort(CE_EEP, 1); // Desactivation chip enable EEPROM
		DRV_EEP_tempo_CE();       // tempo Chip select disable
		DRV_OutputPort(CE_EEP, 0); // Activation chip enable EEPROM
		SSCTB  = 0x0002;     	  //Envoie de l'instruction WRITE
	 	DRV_EEP_WaitEndTransmit();// attente de fin de transmission sur le SPI
 		SSCTB  = Address >> 8; 	  // envoie de la valeur Haute de l'adresse 
		DRV_EEP_WaitEndTransmit();// attente de fin de transmission sur le SPI
		SSCTB  = Address & 0x00FF;// envoie de la valeur basse de l'adresse 
		DRV_EEP_WaitEndTransmit();// attente de fin de transmission sur le SPI
		}
}
