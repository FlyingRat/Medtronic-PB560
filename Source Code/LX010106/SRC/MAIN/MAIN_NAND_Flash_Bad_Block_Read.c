/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_NAND_Flash_Bad_Block_Read.c                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*											                                  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE                                                  */
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
#include "io_declare.h"
#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "Structure.h"
#include "Flash_Monit_data.h"
#include "MAIN_NAND_Flash_Bad_Block_Read.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void MAIN_NAND_Flash_Bad_Block_Read(void)
{
	UBYTE *MONITFLASH_Data = (UBYTE *)MONITORING_FLASH_POINTER_ADDRESS;
	UWORD16 i = 0;
	UBYTE ReadStatus = 0;

	DRV_NAND_CommandInput(0x00) ;
	CMD_ME1 = 0 ;
   	/*the right address is sent */
   	DRV_NAND_AddressInput(0,
   						   1,
   						   0);
	ALE_ME1 = 0 ;
	/* Page Read Second command */
	DRV_NAND_CommandInput(0x30);
	CMD_ME1 = 0 ;

	/* Attente du BUSY ou de 200ns x 50000 = 10ms */
	T3IR  = 0;
 	T3    = 50000;
 	T3CON = 0x00C0;	 
	while((BUSY_MEM1 == 0) && (T3IR == 0)); 
	/*%C stop Timer3	 */
	T3CON = 0x0000;   

	for(i = 0 ; i<NAND_FLASH_BLOCK_NUMBER_LIMIT/*DRV_NAND_Block_Number*/ ; i++)
	{
		DRV_NAND_Bad_Block_Map[i] = *MONITFLASH_Data;
	}

	
}