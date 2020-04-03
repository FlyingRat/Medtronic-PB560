/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EEP_StartWriteWord.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   */
/******************************************************************************/
/*%I Input Parameter :  UWORD16 donnee, UWORD16 adresse                       */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE       */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif	
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "io_declare.h"
#include "Driver_Eeprom_Data.h"
#include "DRV_EEP_StartWriteWord.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/



void DRV_EEP_StartWriteWord(UWORD16 donnee, UWORD16 adresse)
{
	DRV_OutputPort(CE_EEP, 0); 	// Activation chip enable EEPROM
  	SSCTB   = 0x0006;         		// Envoi de l'instruction WREN
  	DRV_EEP_WaitEndTransmit();		// Attente de fin de transmission sur le SPI
	DRV_OutputPort(CE_EEP, 1); 	// Desactivation chip enable EEPROM
  	DRV_EEP_tempo_CE(); 				// Tempo Chip select disable
	DRV_OutputPort(CE_EEP, 0); 	// Activation chip enable EEPROM
	SSCTB  = 0x0002;     			// Envoi de l'instruction WRITE
	DRV_EEP_WaitEndTransmit();		// attente de fin de transmission sur le SPI
	SSCTB  = adresse >> 8; 			// envoie de la valeur Haute de l'adresse 
	DRV_EEP_WaitEndTransmit();		// attente de fin de transmission sur le SPI
	SSCTB  = adresse & 0x00FF; 	// envoie de la valeur basse de l'adresse 
	DRV_EEP_WaitEndTransmit();		// attente de fin de transmission sur le SPI
  	SSCTB  =(UBYTE)(donnee >> 8);	// Envoi du MSB de la donnée
	DRV_EEP_WaitEndTransmit();	 	// attente de fin de transmission sur le SPI
	SSCTB  =(UBYTE)(donnee & 0x00FF);//Envoi du LSB de la donnée
	DRV_EEP_WaitEndTransmit();	   // attente de fin de transmission sur le SPI

	donnee =~donnee;
  	SSCTB  =(UBYTE)(donnee >> 8);	// Envoi du MSB de la donnée
	DRV_EEP_WaitEndTransmit();	 	// attente de fin de transmission sur le SPI
	SSCTB  =(UBYTE)(donnee & 0x00FF);//Envoi du LSB de la donnée
	DRV_EEP_WaitEndTransmit();	   // attente de fin de transmission sur le SPI

	DRV_OutputPort(CE_EEP, 1); 	// Desactivation chip enable EEPROM
	DRV_EEP_tempo_CE();           // tempo Chip select disable
	DRV_EEP_StateEepDriver = DRV_EEP_WRITE_PENDING;
}