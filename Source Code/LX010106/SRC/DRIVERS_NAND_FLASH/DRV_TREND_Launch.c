/******************************************************************************/
/*                                                                            */
/* Project N�  :  RB0505													  */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_TREND_Launch.c  				   						      */
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
#include "DB_Config.h"
#include "Structure.h"
	#define DECLARATION_TRENDFLASH_DATA
#include "Flash_Monit_data.h"
#include "DRV_TREND_Launch.h"
						  


			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_TREND_Launch(void)
{
static UBYTE Trend_First_Start = TRUE;
static UBYTE Trend_Erase_Flag = FALSE;
UWORD16 BlockToErase = 0;
UBYTE CurrentPage = 0;
UBYTE Number_Bad_Block = 0;
UBYTE Remaining_Space = 0;
UWORD32 Nbr_Written_Data = 0;
UWORD16 Temp_Compute = 0;

 
 /*%C New read, write or erase operation can only be authorized if the  */
/*%C nand flash chip is not in used. So Busy signal is tested. */
if(BUSY_MEM1 == 1)
{

	if (Trend_First_Start == TRUE)
	{

/*%C 					Control of the index validity 					*/
	if(DRV_TREND_Address_Write_Flash.Block 
			< DRV_NAND_Second_Partition_Block_Start)
	{
		DRV_TREND_Address_Write_Flash.Block 
			= DRV_NAND_Second_Partition_Block_Start;
	}
	else if(DRV_TREND_Address_Write_Flash.Block 
			> DRV_NAND_Second_Partition_Block_End)
	{
		DRV_TREND_Address_Write_Flash.Block 
			= DRV_NAND_Second_Partition_Block_End;
	}

	if(DRV_TREND_Address_Write_Flash.Page < 0)
	{
		DRV_TREND_Address_Write_Flash.Page = 0;
	}
	else if(DRV_TREND_Address_Write_Flash.Page > LAST_PAGE_IN_BLOCK)
	{
		DRV_TREND_Address_Write_Flash.Page = LAST_PAGE_IN_BLOCK;
	}

	if(DRV_TREND_Address_Write_Flash.Column < 0)
	{
		DRV_TREND_Address_Write_Flash.Column = 0;
	}
	else if(DRV_TREND_Address_Write_Flash.Column >= TREND_FLASH_PAGE_SIZE)
	{
		DRV_TREND_Address_Write_Flash.Column = TREND_FLASH_PAGE_SIZE - 1;
	}


	



/*%C At the first start of the device, we must erase the first partition */
/*%C Block. */	
	if((DRV_TREND_Address_Write_Flash.Block 
					== DRV_NAND_Second_Partition_Block_Start)
	&& (DRV_TREND_Address_Write_Flash.Page == 0)
	&& (DRV_TREND_Address_Write_Flash.Column == 0))
	{
/*%C We must test if the block is valid. */
		  	BlockToErase = DRV_TREND_Address_Write_Flash.Block;

		   	while((DRV_NAND_Bad_Block_Map[BlockToErase] == 0)
				  &&(Number_Bad_Block <= DRV_NAND_Maximum_Bad_Block))
			{
		 		BlockToErase = BlockToErase + 1;
		 		Number_Bad_Block = Number_Bad_Block + 1;
				if(BlockToErase > DRV_NAND_Second_Partition_Block_End)
				{
					BlockToErase = DRV_NAND_Second_Partition_Block_Start;	
				}

			}
			 
			Number_Bad_Block = 0;
			DRV_NAND_EraseBlock(BlockToErase);	
	}	
	else
	{

			
	}
	   	

	DRV_TREND_Partition_Full = DB_ConfigRead(FLASH_SECOND_PARTITION_FULL_U16);   	
	
	Trend_First_Start = FALSE;
	}
	else
	{
	


/*%C if the current page number is 62, we must erase the next block before */
/*%C a write operation. */	   
   		if((DRV_TREND_Address_Write_Flash.Page == LAST_PAGE_TO_ERASE) 
	   	&&(Trend_Erase_Flag == FALSE)
		&&(DRV_NAND_Flash_State == NAND_FREE))
		{	  
			DRV_NAND_Flash_State = NAND_ERASE;	
/*%C We must test if the block is valid. */
		  	BlockToErase = DRV_TREND_Address_Write_Flash.Block;
		   	do
			{
		 		BlockToErase = BlockToErase + 1;
		 		Number_Bad_Block = Number_Bad_Block + 1;
				if(BlockToErase > DRV_NAND_Second_Partition_Block_End)
				{
					BlockToErase = DRV_NAND_Second_Partition_Block_Start;	
				}

			}
			while((DRV_NAND_Bad_Block_Map[BlockToErase] == 0)
				  &&(Number_Bad_Block <= DRV_NAND_Maximum_Bad_Block)); 
			Number_Bad_Block = 0;
			DRV_NAND_EraseBlock(BlockToErase);
			Trend_Erase_Flag = TRUE;
			DRV_NAND_Flash_State = NAND_FREE;
			
  		}	  
/*%C else if the write and read index into input buffer are different, */
/*%C then a write operation is authorized .*/
 	   	else if((DRV_TREND_Idx_Write_Frame != DRV_TREND_Idx_Read_Frame)
		&&(DRV_NAND_Flash_State != NAND_MONIT_WRITE))
		{
		  	DRV_NAND_Flash_State = NAND_TREND_WRITE;
		   	DRV_TREND_PageWrite();
		  
		 	if(DRV_TREND_Address_Write_Flash.Page == LAST_PAGE_IN_BLOCK) 
			{
				Trend_Erase_Flag = FALSE;
			}
		}
   		else if (DRV_NAND_Flash_State == NAND_FREE)
		{ 
				DRV_NAND_Flash_State = NAND_TREND_READ; 	  
/*%C else a read operation is authorized . */
		   		DRV_TREND_PageRead();
				DRV_NAND_Flash_State = NAND_FREE;
			
		}
	  /*	else
		{
		}	 */			  
/*%C  NOTA : As the input buffer is written all the 40 ms,then the write */
/*%C       index is increased all the 40 ms. But this modul "DRV_TREND_Launch"*/
/*%C       is launched all the 10 ms, so all the 40 ms, 1 write operation is */
/*%C       done, and 3 read operation is done. */

	}
}
}





