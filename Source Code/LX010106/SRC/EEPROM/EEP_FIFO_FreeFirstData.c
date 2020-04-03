/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : EEP_FIFO_FreeFirstData.c */
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

BIT EEP_FIFO_FreeFirstData(void)
{
	if (EEP_FIFO_NbDataInFifo <= 0)
	{	
		return(FALSE);
	} else
	{
		EEP_FIFO_NbDataInFifo--;
	}

	EEP_FIFO_AccessDriver[EEP_FIFO_IdxPull].state = FREE_EEP;
	EEP_FIFO_AccessDriver[EEP_FIFO_IdxPull].ptr_DataRam = NULL;	

	if (EEP_FIFO_IdxPull < (SIZE_OF_FIFO_EEP_ACCESS-1))
	{
		EEP_FIFO_IdxPull++;		
	}else 
	{
		EEP_FIFO_IdxPull=0;		
	}
	return (TRUE);
}