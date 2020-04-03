/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_NAND_Flash_Bad_Block_Detection.c                          */
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
#include "MAIN_NAND_Flash_Bad_Block_Detection.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void MAIN_NAND_Flash_Bad_Block_Detection(void)
{
UBYTE *MONITFLASH_Data = (UBYTE *)MONITORING_FLASH_POINTER_ADDRESS;
UWORD16 i = 0;
UBYTE Bad_Block_Test_Done = FALSE;

/******************************************************************************/
/*%C First we must read the "Bad_Block_Test_Done" flag into the first adress */
/*%C of the nand flash memory.   */
/*%C It allow to make the bad block detection one time, at the first start */
/*%C of the device. */
/*%C after, we will no longer do that.*/

   /* Page Read  first command*/
	DRV_NAND_CommandInput(0x00) ;
	CMD_ME1 = 0 ;
	   	/*the right address is sent */
   	DRV_NAND_AddressInput(0, 0, 0);
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
	
	Bad_Block_Test_Done	= *MONITFLASH_Data;

/******************************************************************************/
/*%C If the bad block detection has never been  done (device first start), */
/*%C we call "DRV_NAND_BadBlock_Check" modul which check all the memory block */
/*%C and test all of then to know if they are valid . */

	if(Bad_Block_Test_Done == 0xFF)
	{
   	 	for(i = 0; i<DRV_NAND_Block_Number; i++)
		{
			DRV_NAND_Bad_Block_Map[i] = DRV_NAND_BadBlock_Check(i);
		}
/*%C After knowing which block are wrong, we build a map into the second page */
/*%C of the first block : we store the result into this page. */
	if (DRV_NAND_Block_Number <= MONITORING_FLASH_PAGE_SIZE)
	{ 
	/*   Write first Command */
	   	DRV_NAND_CommandInput(0x80) ;
		CMD_ME1 = 0 ;
	/*the right address is sent */
		DRV_NAND_AddressInput(0, 1, 0) ;
		ALE_ME1 =  0 ;
	/* 2048 data are sent */
		for(i = 0; i<DRV_NAND_Block_Number; i++)
		{
			*MONITFLASH_Data = DRV_NAND_Bad_Block_Map[i]; 
		}
	/*   Write second Command */
		DRV_NAND_CommandInput(0x10) ;
		CMD_ME1 = 0 ;

	/* Attente du BUSY ou de 200ns x 50000 = 10ms */
		T3IR  = 0;
 		T3    = 50000;
 		T3CON = 0x00C0;	 
		while((BUSY_MEM1 == 0) && (T3IR == 0)); 
		/*%C stop Timer3	 */
		T3CON = 0x0000;   
		}

/* !!!!!!!!!!!!!!!!!!!!!!!!! BEWARE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*%C This part of code is not used because "DRV_NAND_Block_Number" is    */
/*%C limited to 256 Mo(2048 Blocks). Bute is written for an eventually  */
/*%C futur version with Nand flash size up to 512 Mo. */
	else if(DRV_NAND_Block_Number > MONITORING_FLASH_PAGE_SIZE)
	{
		/*   Write first Command */
	   DRV_NAND_CommandInput(0x80) ;
		CMD_ME1 = 0 ;
	/*the right address is sent */
		DRV_NAND_AddressInput(0, 1, 0) ;
		ALE_ME1 =  0 ;
	/* 2048 data are sent */
		for(i = 0; i<MONITORING_FLASH_PAGE_SIZE; i++)
		{
			*MONITFLASH_Data = DRV_NAND_Bad_Block_Map[i]; 
		}
	/*   Write second Command */
		DRV_NAND_CommandInput(0x10) ;
		CMD_ME1 = 0 ;

	/* Attente du BUSY ou de 200ns x 50000 = 10ms */
		T3IR  = 0;
 		T3    = 50000;
 		T3CON = 0x00C0;	 
		while((BUSY_MEM1 == 0) && (T3IR == 0)); 
		/*%C stop Timer3	 */
		T3CON = 0x0000;   

	/*   Write first Command */
	   	DRV_NAND_CommandInput(0x80) ;
		CMD_ME1 = 0 ;
	/*the right address is sent */
		DRV_NAND_AddressInput(0, 2, 0) ;
		ALE_ME1 =  0 ;
	/* 2048 data are sent */
		for(i = 0; i<MONITORING_FLASH_PAGE_SIZE; i++)
		{
			*MONITFLASH_Data = DRV_NAND_Bad_Block_Map
									[MONITORING_FLASH_PAGE_SIZE + i]; 
		}
	/*   Write second Command */
		DRV_NAND_CommandInput(0x10) ;
		CMD_ME1 = 0 ;

	/* Attente du BUSY ou de 200ns x 50000 = 10ms */
		T3IR  = 0;
 		T3    = 50000;
 		T3CON = 0x00C0;	 
		while((BUSY_MEM1 == 0) && (T3IR == 0)); 
		/*%C stop Timer3	 */
		T3CON = 0x0000;   
	}
	else
	{
	}

					/********************************/
/*%C When the detection is done, we must set the flash adress of     */
/*%C "Bad_Block_Test_Done" flag	 (col = 0 ,page = 0, block = 0 ).*/
	
		Bad_Block_Test_Done = 0x00;			
	/*   Write first Command */
	   DRV_NAND_CommandInput(0x80) ;
		CMD_ME1 = 0 ;

	/*the right address is sent */
		DRV_NAND_AddressInput(0, 0, 0) ;
		ALE_ME1 =  0 ;
		 
	/* 2048 data are sent */
		*MONITFLASH_Data = Bad_Block_Test_Done; 
		

	/*   Write second Command */
		DRV_NAND_CommandInput(0x10) ;
		
		CMD_ME1 = 0 ;
		
	/* Attente du BUSY ou de 200ns x 50000 = 10ms */
		T3IR  = 0;
 		T3    = 50000;
 		T3CON = 0x00C0;	 
		while((BUSY_MEM1 == 0) && (T3IR == 0)); 
		/*%C stop Timer3	 */
		T3CON = 0x0000;   
	}
/*EOF*/	
}