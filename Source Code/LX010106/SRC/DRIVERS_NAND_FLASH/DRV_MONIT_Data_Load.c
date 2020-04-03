/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505													  */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_MONIT_Data_Load.c  										  */
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
#include "DRV_MONIT_Data_Load.h"

			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_MONIT_Data_Load(void)
{
/* Monitoring Flash pointer declaration */
	UBYTE *MONITFLASH_Data = (UBYTE *)MONITORING_FLASH_POINTER_ADDRESS;
  	UWORD16 Loop_Number = 0;
	UBYTE Number_Bad_Block = 0;
   	static UBYTE Monit_Element_Frame_Counter = 0;


   		 

	while ((Loop_Number < 32)
   && (DRV_MONIT_Address_Write_Flash.Column < MONITORING_FLASH_PAGE_SIZE )
   &&  (DRV_MONIT_Idx_Frame < NAND_PAGE_CLUSTER_SIZE))
	{

				/***********************************************/
		*MONITFLASH_Data = DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Read_Frame]
  									  			[DRV_MONIT_Idx_Frame] ;
		DRV_MONIT_Idx_Frame = DRV_MONIT_Idx_Frame + 1;
/*%C the column index is increased. */
	  	DRV_MONIT_Address_Write_Flash.Column = 
						DRV_MONIT_Address_Write_Flash.Column + 1;
		Monit_Element_Frame_Counter = Monit_Element_Frame_Counter + 1;
	   	if(Monit_Element_Frame_Counter >= End_Of_Table_Detailled_Monitoring)
		{		
/*%C Save the last write address into config database */
	 	  	DRV_MONIT_Address_Write_Flash_Recording.Block =
						  DRV_MONIT_Address_Write_Flash.Block;
		  	DRV_MONIT_Address_Write_Flash_Recording.Page =
						  DRV_MONIT_Address_Write_Flash.Page;
			DRV_MONIT_Address_Write_Flash_Recording.Column =
						  DRV_MONIT_Address_Write_Flash.Column;
			Monit_Element_Frame_Counter = 0;
		}
	
		Loop_Number = Loop_Number + 1;
	}


	if(DRV_MONIT_Idx_Frame >= NAND_PAGE_CLUSTER_SIZE)
	{
		DRV_MONIT_Idx_Frame = 0;
		DRV_MONIT_Idx_Read_Frame = DRV_MONIT_Idx_Read_Frame + 1;
		if(DRV_MONIT_Idx_Read_Frame >= MONIT_BUFFER_SIZE)
		{
			DRV_MONIT_Idx_Read_Frame = 0;	
		}

		/*%C   Write second Command */
		DRV_NAND_CommandInput(0x10) ;
		
		CMD_ME1 = 0; 

		DRV_MONIT_Step = 0;
		DRV_NAND_Flash_State = NAND_FREE;

/* record the address for the beginninf of a read operation */

 	  	DRV_MONIT_Address_Start_Read_Flash_Recording.Block =
					  DRV_MONIT_Address_Write_Flash_Recording.Block;
	  	DRV_MONIT_Address_Start_Read_Flash_Recording.Page =
					  DRV_MONIT_Address_Write_Flash_Recording.Page;
		DRV_MONIT_Address_Start_Read_Flash_Recording.Column =
					  DRV_MONIT_Address_Write_Flash_Recording.Column;

	}

	if(DRV_MONIT_Address_Write_Flash.Column >= MONITORING_FLASH_PAGE_SIZE )
	{
		/*%C   Write second Command */
		DRV_NAND_CommandInput(0x10) ;
		
		CMD_ME1 = 0; 

/* record the address for the beginninf of a read operation */

 	  	DRV_MONIT_Address_Start_Read_Flash_Recording.Block =
					  DRV_MONIT_Address_Write_Flash_Recording.Block;
	  	DRV_MONIT_Address_Start_Read_Flash_Recording.Page =
					  DRV_MONIT_Address_Write_Flash_Recording.Page;
		DRV_MONIT_Address_Start_Read_Flash_Recording.Column =
					  DRV_MONIT_Address_Write_Flash_Recording.Column;


/*%C Now we must control the page,block changing and the end of detailled  */
/*%C monitoring partition. */
			   	if (DRV_MONIT_Address_Write_Flash.Page >= LAST_PAGE_IN_BLOCK)
				{
				   	if (DRV_MONIT_Address_Write_Flash.Block >= 
										  DRV_NAND_First_Partition_Block_End)
					{
						DRV_MONIT_Address_Write_Flash.Block 
									= DRV_NAND_First_Partition_Block_Start;
						DRV_MONIT_Partition_Full = TRUE;
					
/*%C We must test if the next block is a Bad block */
						while((DRV_NAND_Bad_Block_Map[
								DRV_MONIT_Address_Write_Flash.Block] 
								== 0)
							&&(Number_Bad_Block <= DRV_NAND_Maximum_Bad_Block))
						{
					 		DRV_MONIT_Address_Write_Flash.Block = 
					 					  DRV_MONIT_Address_Write_Flash.Block
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
					 		DRV_MONIT_Address_Write_Flash.Block = 
					 					  DRV_MONIT_Address_Write_Flash.Block + 1;
							Number_Bad_Block = Number_Bad_Block + 1;
						}
						while((DRV_NAND_Bad_Block_Map[
								DRV_MONIT_Address_Write_Flash.Block] 
								== 0)
								&&(Number_Bad_Block 
									<= DRV_NAND_Maximum_Bad_Block));
						Number_Bad_Block = 0;
					}
					DRV_MONIT_Address_Write_Flash.Page = 0;
				}
				else
				{
				   	DRV_MONIT_Address_Write_Flash.Page = 
			   						DRV_MONIT_Address_Write_Flash.Page + 1;
			   	}	
			  	DRV_MONIT_Address_Write_Flash.Column = 0;
		

	   	DRV_MONIT_Step = 0;
/*%C The index is tested when it is upper than NAND_PAGE_CLUSTER_SIZE, but in fact*/
/*%C it is already done upper, and the index is put to 0. */
		if((DRV_MONIT_Idx_Frame >= NAND_PAGE_CLUSTER_SIZE)
		 ||(DRV_MONIT_Idx_Frame == 0))
		{
			DRV_NAND_Flash_State = NAND_FREE;
   		}
		else
		{
			DRV_NAND_Flash_State = NAND_MONIT_WRITE;
		}
   	}	
 
/*EOF*/	 
}