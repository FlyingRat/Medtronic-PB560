/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_NAND_ReadID.c											  */
/* 																			  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  														  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            	  */
/*%IO Input/Output :    NONE	                                             */
/*%O Output Parameter : NONE       											  */
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
#include "DRV_NAND_ReadID.h"
			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_NAND_ReadID(void)

{
	/* Déclaration du pointeur d'adresse en local */
	UBYTE *MONITFLASH_Data = (UBYTE *)MONITORING_FLASH_POINTER_ADDRESS;
 	UBYTE Cycle_Lecture = 0;
	UBYTE Compterror = 0 ;
	UBYTE Memory_ID[3];
	UBYTE Five_Addressing_Cycles = FALSE;
	UWORD16 Result = 0;
 	UBYTE Device_First_Use = FALSE;

	ALE_ME1 = 0 ;
	CMD_ME1 = 1 ;

  	*MONITFLASH_Data = 0x90 ; /* Passage de la commande */

	_nop_() ;
	_nop_() ;
	_nop_() ;
	_nop_() ;
	_nop_() ;
	_nop_() ;

	CMD_ME1 = 0 ;

	ALE_ME1 = 1 ;

	*MONITFLASH_Data = 0x00 ;

	_nop_() ;
	_nop_() ;
	_nop_() ;
	_nop_() ;
	_nop_() ;
	_nop_() ;


	ALE_ME1 = 0 ;

	/* Attente du BUSY ou de 200 ns (25*8*2) */
	T3IR  = 0;
 	T3    = 2500;
 	T3CON = 0x00C0;	 
	while((BUSY_MEM1 == 0) && (T3IR == 0)); 
	/*%C stop Timer3	 */
	T3CON = 0x0000;   

	for (Cycle_Lecture = 0 ; Cycle_Lecture < 4 ; Cycle_Lecture ++)
	{
	  	Memory_ID[Cycle_Lecture] = *MONITFLASH_Data ;
	}
	switch(Memory_ID[1])
	{
		case 0xF1 :    /* 128Mo */
		{
			Five_Addressing_Cycles = FALSE;
			DRV_NAND_Block_Number = 1024;
			DRV_NAND_First_Partition_Block_Start = 1;
			DRV_NAND_First_Partition_Block_End =341;
			DRV_NAND_Second_Partition_Block_Start = 342;
			DRV_NAND_Second_Partition_Block_End =1023;	
			DRV_NAND_Maximum_Bad_Block = 20;

		    break;
		}
		case 0xDA :    /* 256Mo */
		{
			Five_Addressing_Cycles = TRUE;
		    DRV_NAND_Block_Number = 2048;
			DRV_NAND_First_Partition_Block_Start = 1;
			DRV_NAND_First_Partition_Block_End =546;
			DRV_NAND_Second_Partition_Block_Start = 547;
			DRV_NAND_Second_Partition_Block_End =2047;	
			DRV_NAND_Maximum_Bad_Block = 40;
		    break;
		}
		case 0xDC :   /* 512Mo */
		{
			Five_Addressing_Cycles = TRUE;
			DRV_NAND_Block_Number = 2048;
			DRV_NAND_First_Partition_Block_Start = 1;
			DRV_NAND_First_Partition_Block_End =546;
			DRV_NAND_Second_Partition_Block_Start = 547;
			DRV_NAND_Second_Partition_Block_End =2047;	
			DRV_NAND_Maximum_Bad_Block = 40;	
		    break;
		}
		default :
		{
			Five_Addressing_Cycles = FALSE;
			DRV_NAND_Block_Number = 1024;
			DRV_NAND_First_Partition_Block_Start = 1;
			DRV_NAND_First_Partition_Block_End =341;
			DRV_NAND_Second_Partition_Block_Start = 342;
			DRV_NAND_Second_Partition_Block_End =1023;	
			DRV_NAND_Maximum_Bad_Block = 20;
		    break;
		}	
	}
	Result = DB_ConfigWrite(FLASH_MEMORY_MANUFACTURER,(UWORD16)Memory_ID[0]);
	Result = DB_ConfigWrite(FLASH_MEMORY_DEVICE,(UWORD16)Memory_ID[1]);
	Result = DB_ConfigWrite(FLASH_MEMORY_FIVE_ADDRESS_CYCLES
				  ,(UWORD16)Five_Addressing_Cycles);



/******************************************************************************/
/*%C First we must read the "Bad_Block_Test_Done" flag into the first adress */
/*%C of the nand flash memory.   */

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

	Device_First_Use = *MONITFLASH_Data;

/******************************************************************************/
/*%C If it is device first use, */
/*%C we store into "config" database the default partition size. */

	if(Device_First_Use == 0xFF)
	{
		Result = DB_ConfigWrite(FLASH_TREND_WRITE_BLOCK_U16
					  			,DRV_NAND_Second_Partition_Block_Start);
  	}
 

}