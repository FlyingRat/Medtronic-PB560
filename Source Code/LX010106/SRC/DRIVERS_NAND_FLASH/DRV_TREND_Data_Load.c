/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505													  */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_TREND_Data_Load.c  										  */
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
#include "enum.h"
#include "io_declare.h"
#include "typedef.h"
#include "define.h"
#include "Structure.h"
#include "DB_Config.h"
#include "Flash_Monit_data.h"
#include "DRV_TREND_Data_Load.h"

			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_TREND_Data_Load(void)
{
/* Monitoring Flash pointer declaration */
	UBYTE *MONITFLASH_Data = (UBYTE *)MONITORING_FLASH_POINTER_ADDRESS;
  	UWORD16 Loop_Number = 0;
	UBYTE Number_Bad_Block = 0;
	static UBYTE Trend_Element_Frame_Counter = 0;


	 
  	while ((Loop_Number < 32)
	   && (DRV_TREND_Address_Write_Flash.Column < MONITORING_FLASH_PAGE_SIZE )
	   &&  (DRV_TREND_Idx_Frame < NAND_PAGE_CLUSTER_SIZE))
	{

				/***********************************************/
		*MONITFLASH_Data = DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Read_Frame]
  									  			[DRV_TREND_Idx_Frame] ;
		DRV_TREND_Idx_Frame = DRV_TREND_Idx_Frame + 1;
/*%C the column index is increased. */
	  	DRV_TREND_Address_Write_Flash.Column = 
						DRV_TREND_Address_Write_Flash.Column + 1;
	
		Trend_Element_Frame_Counter = Trend_Element_Frame_Counter + 1;
	   	if(Trend_Element_Frame_Counter >= End_Of_Table_Trends)
		{		
/*%C Save the last write address into config database */
	 	  	DRV_TREND_Address_Write_Flash_Recording.Block =
						  DRV_TREND_Address_Write_Flash.Block;
		  	DRV_TREND_Address_Write_Flash_Recording.Page =
						  DRV_TREND_Address_Write_Flash.Page;
			DRV_TREND_Address_Write_Flash_Recording.Column =
						  DRV_TREND_Address_Write_Flash.Column;
			Trend_Element_Frame_Counter = 0;
															
		}
		Loop_Number = Loop_Number + 1;
  	}


	if(DRV_TREND_Idx_Frame >= NAND_PAGE_CLUSTER_SIZE)
	{
		DRV_TREND_Idx_Frame = 0;
		DRV_TREND_Idx_Read_Frame = DRV_TREND_Idx_Read_Frame + 1;
		if(DRV_TREND_Idx_Read_Frame >= TREND_BUFFER_SIZE)
		{
			DRV_TREND_Idx_Read_Frame = 0;	
		}

		/*%C   Write second Command */
		DRV_NAND_CommandInput(0x10) ;
		
		CMD_ME1 = 0; 

		DRV_TREND_Step = 0;
		DRV_NAND_Flash_State = NAND_FREE;
/* record the address for the beginninf of a read operation */
 	  	DRV_TREND_Address_Start_Read_Flash_Recording.Block =
					  DRV_TREND_Address_Write_Flash_Recording.Block;
	  	DRV_TREND_Address_Start_Read_Flash_Recording.Page =
					  DRV_TREND_Address_Write_Flash_Recording.Page;
		DRV_TREND_Address_Start_Read_Flash_Recording.Column =
					  DRV_TREND_Address_Write_Flash_Recording.Column;
	}

	if(DRV_TREND_Address_Write_Flash.Column >= MONITORING_FLASH_PAGE_SIZE )
	{
		/*%C   Write second Command */
		DRV_NAND_CommandInput(0x10) ;
		
		CMD_ME1 = 0; 

/* record the address for the beginninf of a read operation */
 	  	DRV_TREND_Address_Start_Read_Flash_Recording.Block =
					  DRV_TREND_Address_Write_Flash_Recording.Block;
	  	DRV_TREND_Address_Start_Read_Flash_Recording.Page =
					  DRV_TREND_Address_Write_Flash_Recording.Page;
		DRV_TREND_Address_Start_Read_Flash_Recording.Column =
					  DRV_TREND_Address_Write_Flash_Recording.Column;

/*%C Now we must control the page,block changing and the end of   */
/*%C Trend partition. */
			   	if (DRV_TREND_Address_Write_Flash.Page >= LAST_PAGE_IN_BLOCK)
				{
				   	if (DRV_TREND_Address_Write_Flash.Block >= 
										  DRV_NAND_Second_Partition_Block_End)
					{
						
					   	DRV_TREND_Address_Write_Flash.Block 
									= DRV_NAND_Second_Partition_Block_Start;
						DRV_TREND_Partition_Full = TRUE;
/*%C We must test if the next block is a Bad block */
						while((DRV_NAND_Bad_Block_Map[
								DRV_TREND_Address_Write_Flash.Block] 
								== 0)
							&&(Number_Bad_Block <= DRV_NAND_Maximum_Bad_Block))
						{
					 		DRV_TREND_Address_Write_Flash.Block = 
					 					  DRV_TREND_Address_Write_Flash.Block
					 					  + 1;
							Number_Bad_Block = Number_Bad_Block + 1;
				  		}
						Number_Bad_Block = 0;  
					}
					else
					{
/*%C We must test if the next block is a Bad block */
						do
						{
					 		DRV_TREND_Address_Write_Flash.Block = 
					 					  DRV_TREND_Address_Write_Flash.Block + 1;
							Number_Bad_Block = Number_Bad_Block + 1;
						}
						while((DRV_NAND_Bad_Block_Map[
								DRV_TREND_Address_Write_Flash.Block] 
								== 0)
								&&(Number_Bad_Block 
									<= DRV_NAND_Maximum_Bad_Block));
						Number_Bad_Block = 0;
					}
					DRV_TREND_Address_Write_Flash.Page = 0;
				}
				else
				{
				   	DRV_TREND_Address_Write_Flash.Page = 
			   						DRV_TREND_Address_Write_Flash.Page + 1;
			   	}	
			  	DRV_TREND_Address_Write_Flash.Column = 0;
		

	   	DRV_TREND_Step = 0;
/*%C The index is tested when it is upper than NAND_PAGE_CLUSTER_SIZE, but in fact*/
/*%C it is already done upper, and the index is put to 0. */
		if((DRV_TREND_Idx_Frame >= NAND_PAGE_CLUSTER_SIZE)
		 ||(DRV_TREND_Idx_Frame == 0))
		{
			DRV_NAND_Flash_State = NAND_FREE;
   		}
		else
		{
			DRV_NAND_Flash_State = NAND_TREND_WRITE;
		}
   	}	
 
/*EOF*/	 
}