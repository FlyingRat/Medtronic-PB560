/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Read_Eeprom.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          																						*/
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
#else
#include "regf276e.h"
#endif	 
#include "typedef.h"
//#include "enum.h"
#include "DRV_COM_Data.h"

void DRV_COM_Read_Eeprom(void)
{
	 
	if (DRV_COM_End_of_Transmit == TRUE)
		{
		PECC2 = 0x0000; //Interruption générée à chaque envoi
		//autorisation  de transmission
		DRV_COM_End_of_Transmit = FALSE;
		S0TBIE = 1;
		S0TBUF = *EepromDataRead;
		EepromDataRead = EepromDataRead + 1;
		if (EepromDataRead >= (UBYTE xhuge *)(&EepromData) + (2 * COM_EEPROM_BUFFER_SIZE))
			{
			Communication_State = COM_TRANSMIT_STOP;	
			}
		}
}