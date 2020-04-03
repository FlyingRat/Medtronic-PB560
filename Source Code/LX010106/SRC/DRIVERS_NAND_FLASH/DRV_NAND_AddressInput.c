/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505													  */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_NAND_AddressInput.c 									  */
/* 																			  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  */
/******************************************************************************/
/*%I Input Parameter :  NONE												  */
/*%IO Input/Output :    NONE												  */
/*%O Output Parameter : NONE												  */
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
#include "io_declare.h"
#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "Structure.h"
#include "Flash_Monit_data.h"
#include "DB_Config.h"
#include "DRV_NAND_AddressInput.h"
						  
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_NAND_AddressInput(UWORD16 Block_Number,
							UBYTE	Page_Number,
							UWORD16 Column_Number )
{
	UBYTE Five_Addressing_Cycles = 
						(UBYTE)DB_ConfigRead(FLASH_MEMORY_FIVE_ADDRESS_CYCLES);
	
   	/* Déclaration du pointeur d'adresse en local */
   	UBYTE *MONITFLASH_Data = (UBYTE *)MONITORING_FLASH_POINTER_ADDRESS;

	/* Déclaration des variables pour le passage des adresses sur quelques Cycles)*/
	 
	UBYTE CycleAdr1 = 0;
	UBYTE CycleAdr2 = 0;
	UBYTE CycleAdr3 = 0;
	UBYTE CycleAdr4 = 0;
	UBYTE CycleAdr5 = 0;
	UBYTE CycleAdr3Temp = 0;

   			
	if(Block_Number > (DRV_NAND_Second_Partition_Block_End))
	{
		Block_Number = (DRV_NAND_Second_Partition_Block_End);
	}
	if(Block_Number < 0)
	{
		Block_Number = 0;
	}

	if(Page_Number > (NAND_FLASH_PAGE_NUMBER - 1))
	{
		Page_Number = (NAND_FLASH_PAGE_NUMBER - 1);
	}
	if(Page_Number < 0)
	{
		Page_Number = 0;
	}

	if(Column_Number > (NAND_FLASH_COLUMN_NUMBER - 1))
	{
		Column_Number = (NAND_FLASH_COLUMN_NUMBER - 1);
	}
	if(Column_Number < 0)
	{
		Column_Number = 0;
	}


	CycleAdr1 = (UBYTE)Column_Number;
	CycleAdr1 = CycleAdr1 & 0xFF;
	
	CycleAdr2 = (UBYTE)(Column_Number>>8);
	CycleAdr2 = CycleAdr2 & 0x0F;

	CycleAdr3 =	Page_Number & 0x3F ;
	CycleAdr3Temp =  (UBYTE)(Block_Number << 6);
	CycleAdr3Temp =  CycleAdr3Temp & 0xC0;
	CycleAdr3 = CycleAdr3 | CycleAdr3Temp;
	
	CycleAdr4 =	(UBYTE)(Block_Number>>2);

	CycleAdr5 =	(UBYTE)(Block_Number>>10);
	CycleAdr5 = CycleAdr5 & 0x01;

	/* Mise à niveau signaux de commande */
	ALE_ME1 = 1 ;
	CMD_ME1 = 0 ;

	/* Envoie de 4 octets pour une adresse de block, page et colonne */
	*MONITFLASH_Data = CycleAdr1 ; /* Octet 1 */ 
	*MONITFLASH_Data = CycleAdr2 ; /* Octet 2 */ 
	*MONITFLASH_Data = CycleAdr3 ; /* Octet 3 */
	*MONITFLASH_Data = CycleAdr4 ; /* Octet 4 */
	if(Five_Addressing_Cycles == TRUE)
	{
		*MONITFLASH_Data = CycleAdr5 ; /* Octet 5 */
	}
	                                                                      
  
	/* Laisser le temps au µc d'envoyer la commande sur le bus*/
	_nop_() ;

}

