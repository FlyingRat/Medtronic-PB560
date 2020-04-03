/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EEP_ReadWord.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   */
/******************************************************************************/
/*%I Input Parameter :  UWORD16 adresse                                       */
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
#include "io_declare.h"
#include "DRV_EEP_ReadWord.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


UWORD16 DRV_EEP_ReadWord(UWORD16 adresse)
{
	UWORD16 CurrentData;
	DRV_OutputPort(CE_EEP, 0); // Activation chip enable EEPROM
	SSCTB  = 0x0003;    			/*%C Sending instruction for reading on SPI     */        	
	DRV_EEP_WaitEndTransmit();	/*%C  waiting end of transmission on  SPI				  */
	SSCTB  =  adresse >> 8;  	/*%C Sending of the Most significative Byte of the adress	  */
 	DRV_EEP_WaitEndTransmit();	/*%C  waiting end of transmission on  SPI					  */
	SSCTB  =  adresse & 0x00FF;/*%C Sending of the Less significative Byte of the adress						  */
	DRV_EEP_WaitEndTransmit(); /*%C  waiting end of transmission on  SPI					  */
	SSCTB  = 0x0000;          	/*%C generation SCLK_SPI_CPU to read EEPROM					  */
	DRV_EEP_WaitEndTransmit();	  /*%C  waiting end of transmission on  SPI				  */
	/*%CReading of the receipt register wich contains the most significative byte of data */
	CurrentData = SSCRB; 	
	CurrentData = CurrentData << 8;
	SSCTB  = 0x0000;          	/*%C generation SCLK_SPI_CPU pour lecture EEPROM					 */
	DRV_EEP_WaitEndTransmit();	/*%C  waiting end of transmission on  SPI				 */
	/*%CReading of the receipt register wich contains the less significative byte of data			 */
	CurrentData |= (UWORD16)SSCRB; 
	DRV_OutputPort(CE_EEP, 1); // Desctivation chip enable EEPROM
	DRV_EEP_tempo_CE();			/*%C tempo Chip select disable									 */
	return (CurrentData);
}
