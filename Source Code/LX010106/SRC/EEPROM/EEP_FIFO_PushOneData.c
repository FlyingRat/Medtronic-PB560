/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : EEP_FIFO_PushOneData.c */
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
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "define.h"
#include "Eeprom_Data.h"
			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void EEP_FIFO_PushOneData(UWORD16 xhuge *ptr_data,
										e_EEP_ACCESS_STATE access_type)
{
// Attente de libération d'une case dans la FIFO
while (EEP_FIFO_NbDataInFifo == SIZE_OF_FIFO_EEP_ACCESS);	// ATTENTION : BOUCLE INFINI quand NbDataInFifo = 16


EEP_FIFO_AccessDriver[EEP_FIFO_IdxPush].state = access_type;
EEP_FIFO_AccessDriver[EEP_FIFO_IdxPush].ptr_DataRam = ptr_data;

// Incrémentation du pointeur du FIFO
EEP_FIFO_NbDataInFifo++;

 // Si accès en lecture attente de la fin de lecture de l'e2prom
while ((access_type == READ_EEP) && (EEP_FIFO_AccessDriver[EEP_FIFO_IdxPush].ptr_DataRam == ptr_data));

// Limitation du pointeur de la FIFO
if (EEP_FIFO_IdxPush < (SIZE_OF_FIFO_EEP_ACCESS-1))
	EEP_FIFO_IdxPush++;	
else 
	EEP_FIFO_IdxPush=0;
}