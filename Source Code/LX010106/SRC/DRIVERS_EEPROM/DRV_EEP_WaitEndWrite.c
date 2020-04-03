/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EEP_WaitEndWrite.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
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
#include "DRV_EEP_WaitEndWrite.h"

						 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_EEP_WaitEndWrite(void)
{
	DRV_EEP_CounterTimeOutWrite++; 	//incrémentation de la mesure du temps d'écriture
	DRV_OutputPort(CE_EEP, 0); 		// Activation chip enable EEPROM
 	SSCTB  = 0x0005;          		  	// Envoi de l'instruction RDSR lecture du status de l'eeprom
 	DRV_EEP_WaitEndTransmit();			// attente de fin de transmission sur le SPI
	SSCTB  = 0x0000;	        			// generation horloge SCLK_SPI_CPU pour la lecture du status EEPROM
	DRV_EEP_WaitEndTransmit();			// attente de fin de transmission sur le SPI
	DRV_OutputPort(CE_EEP, 1); 		// Desactivation chip enable EEPROM
	DRV_EEP_tempo_CE();		    		// tempo Chip select disable

	//Surveillance du temps d'écriture de l'eeprom 5ms max
	if (DRV_EEP_CounterTimeOutWrite < cDRV_EEP_TIME_OUT_10MS)
		{
		// Vérification de la fin d'écriture par test du registre de réception 
		// du bus SPI contenant le status de l'eeprom
		if ((SSCRB & 0x0001) == 0x00)
			{
			DRV_OutputPort(CE_EEP, 0); // Activation chip enable EEPROM
			SSCTB   = 0x0004;         	//Envoi de l'instruction WRDI disable write
			DRV_EEP_WaitEndTransmit();	// attente de fin de transmission sur le SPI
			DRV_OutputPort(CE_EEP, 1); // Desactivation chip enable EEPROM
 			DRV_EEP_tempo_CE();       	// tempo Chip select disable
			DRV_EEP_CounterTimeOutWrite =0;	//Raz du temps de surveillance d'écriture
			DRV_EEP_StateEepDriver = DRV_EEP_FREE;	//Libération d'accés eeprom
			DRV_EEP_WriteStatus = DRV_EEP_NO_ERROR;//Gestion d'erreur de l'eeprom pas d'erreur
			}
		}
	//Ecriture non réalisée dans le délais de 10ms
	else
		{
		DRV_EEP_CounterTimeOutWrite =0; 						//Raz du temps de surveillance de l'eeprom
		DRV_EEP_StateEepDriver = DRV_EEP_FREE;				//Libération de l'accès eeprom
  		DRV_EEP_WriteStatus    = DRV_EEP_TIME_OUT_WRITE;//Gestion d'erreur de de l'eeprom écriture non réalisée
		}
}
