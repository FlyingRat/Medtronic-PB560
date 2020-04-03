/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505													  */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_NAND_EraseBlock.c  										  */
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
#include "DRV_NAND_EraseBlock.h"


			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_NAND_EraseBlock(UWORD16 Block)
{
/*%C is the flash device is a five or four addressing cycles. */
/*%C It depends of the flash id .*/
   	UBYTE Five_Addressing_Cycles = 
						(UBYTE)DB_ConfigRead(FLASH_MEMORY_FIVE_ADDRESS_CYCLES);

  	UBYTE *MONITFLASH_Data = (UBYTE *)MONITORING_FLASH_POINTER_ADDRESS;
   
/*%C The input block adress is decoded. */
	UBYTE CycleAdr1 = 0;
	UBYTE CycleAdr2 = 0;
	UBYTE CycleAdr3 = 0;
	UBYTE CycleAdr1Temp = 0;

	if(Block > (DRV_NAND_Second_Partition_Block_End))
	{
		Block = (DRV_NAND_Second_Partition_Block_End);
	}


	CycleAdr1 =	0x00;
	CycleAdr1Temp =  (UBYTE)(Block << 6);
	CycleAdr1Temp =  CycleAdr1Temp & 0xC0;
	CycleAdr1 = CycleAdr1 | CycleAdr1Temp;
	
	CycleAdr2=	(UBYTE)(Block>>2);

	CycleAdr3 =	(UBYTE)(Block>>10);
	CycleAdr3 = CycleAdr3 & 0x01;


/* first erase  command*/

	DRV_NAND_CommandInput(0x60) ;

	CMD_ME1 = 0 ;

	ALE_ME1 = 1 ;

	*MONITFLASH_Data = CycleAdr1 ;
	*MONITFLASH_Data = CycleAdr2 ;
	if(Five_Addressing_Cycles == TRUE)
	{
		*MONITFLASH_Data = CycleAdr3 ;
	}

	_nop_() ;

	ALE_ME1 = 0 ;

/* second erase command */
	DRV_NAND_CommandInput(0xD0) ;

	CMD_ME1 = 0 ;

/*%C waiting for BUSY signal or a time out of 3.5 ms (the read operation  */
/*%C should be less than 3 ms). */
/*	  	T3IR  = 0;
		T3    = 0x46;
		T3CON = 0x00C7;
		while((BUSY_MEM1 == 0) && (T3IR == 0));	   */	  
/*EOF*/

}
