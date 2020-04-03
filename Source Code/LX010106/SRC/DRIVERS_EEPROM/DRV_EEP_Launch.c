/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EEP_Launch.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
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
#include "DRV_EEP_Launch.h"

						 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_EEP_Launch(void)
{
	UWORD16 EepIndex;
	UWORD16 Data16Bits;
	//Configuration de la visse du bus SPI 1.8Mhz
	/*Adapter le time out du WaitEndTransmit si modification de SSCBR			*/
	SSCBR = 0x000A;
	// Si Ecriture en cours
	if ( DRV_EEP_StateEepDriver == DRV_EEP_WRITE_PENDING)
		{
		//test de fin d'écriture
		DRV_EEP_WaitEndWrite();
		// si fin d'écriture eeprom libre
		if ( DRV_EEP_StateEepDriver == DRV_EEP_FREE)
			{
			EEP_FIFO_FreeFirstData();
			}
		}
	// Si pas d'écriture en cours
	else
		{
		//si donnée présente dans la FIFO EEPROM
		if (EEP_FIFO_ReadNbDataStored() > 0) 
			{
			//Lecture de la FIFO
		 	DRV_EEP_CurrentDataPull = EEP_FIFO_PullFirstData();
/* ---------------------------------------------------------------------------*/
/*		 /\																							*/	
/*    /!!\		ATTENTION, Bien VERIFIER l'adresse de début EEPROM dans eprom.h*/
/*   /____\																							*/
/* ---------------------------------------------------------------------------*/
			//Calcul de l'adresse dans l'eeprom
			EepIndex = (UWORD16)((UWORD32)(DRV_EEP_CurrentDataPull.ptr_DataRam - BEGIN_RAM_ADRESS_OF_EEP_DATA)*2);
			// Si demande de lecture 
  			if (DRV_EEP_CurrentDataPull.state == READ_EEP)
				{
				// ------------------------------------
				// ACCES EN LECTURE D'UNE DATA 16bits
				*DRV_EEP_CurrentDataPull.ptr_DataRam = DRV_EEP_ReadWord(EepIndex);
				EEP_FIFO_FreeFirstData();
				}
			// Si demande d'écriture 
			else if (DRV_EEP_CurrentDataPull.state == WRITE_EEP)
				{
				Data16Bits = *DRV_EEP_CurrentDataPull.ptr_DataRam;
				DRV_EEP_StartWriteWord(Data16Bits,EepIndex);
				}
			}
		}
}
