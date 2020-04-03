/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505													  */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_NAND_BadBlock_Check.c  									  */
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
#include "DRV_NAND_BadBlock_Check.h"

			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UBYTE DRV_NAND_BadBlock_Check(UWORD16 Block)
{
	
	UBYTE *MONITFLASH_Data = (UBYTE *)MONITORING_FLASH_POINTER_ADDRESS;
	UBYTE Bad_Block1 = 0xFF;
	UBYTE Bad_Block2 = 0xFF;

	UBYTE result = 0;
 
	DRV_NAND_CommandInput(0x00) ;
	CMD_ME1 = 0 ;
   	/*the right address is sent */
   	DRV_NAND_AddressInput(Block,
   						   0,
   						   2048);
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

	result = *MONITFLASH_Data;
	if (result != 0xFF)
	{
		Bad_Block1 = 0x00;
	}
	else
	{
		Bad_Block1 = 0xFF;
	}


	DRV_NAND_CommandInput(0x00) ;
	CMD_ME1 = 0 ;
	   	/*the right address is sent */
   	DRV_NAND_AddressInput(Block,
   						   1,
   						   2048);
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

	result = *MONITFLASH_Data;
	if (result != 0xFF)
	{
		Bad_Block2 = 0x00;
	}
	else
	{
		Bad_Block2 = 0xFF;
	}

	if((Bad_Block1 == 0x00) || (Bad_Block2 == 0x00))	
	{
		result = 0x00;
	}
	else
	{
		result = 0xFF;
	}
	
	return(result);
}