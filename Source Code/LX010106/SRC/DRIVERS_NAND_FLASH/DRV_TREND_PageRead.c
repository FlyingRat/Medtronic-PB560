/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505													  */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_TREND_PageRead.c											  */
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
#include "DB_Control.h"
#include "DB_Config.h"
#include "Flash_Monit_data.h"
#include "Driver_USB_Data.h"
#include "DRV_TREND_PageRead.h"

			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_TREND_PageRead(void)
{
  /* Monitoring Flash pointer declaration */
	UBYTE *MONITFLASH_Data = (UBYTE *)MONITORING_FLASH_POINTER_ADDRESS;

 	UBYTE i =0;
	UBYTE Number_Bad_Block = 0;
    UWORD16 Column = 0;
    UWORD32 Written_Data_Number = 0;
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
   	static t_FlashParam  Trend_Address_Read_Flash;
	static UWORD16 Previous_Column = 0;




/******************************************************************************/
/*%C When the computer requests a monitoring data transfert, it must start  */
/*%C at the last flash writing adress */
	if (DRV_TREND_Read_Request == REQUEST)
	{

		DRV_NAND_End_Of_Read = FALSE;
		DRV_TREND_Received_Data = 0;
		DRV_TREND_New_Data = FALSE;


/*%C  the last writing address is loaded into the flash reading adress .*/
		
		Trend_Address_Read_Flash.Column = 
							DRV_TREND_Address_Start_Read_Flash_Recording.Column;
		Trend_Address_Read_Flash.Page =	
						   	DRV_TREND_Address_Start_Read_Flash_Recording.Page;
 		Trend_Address_Read_Flash.Block = 
 						  	DRV_TREND_Address_Start_Read_Flash_Recording.Block;

/*%C Now the reading processus can start. */
/*%C This is set to "RUNNING" here, because due to the conditions of the  */
/*%C block, page, column address, it can be set to "ENDED". */
		DRV_TREND_Read_Request = RUNNING;

/*%C In the case of first start, stop the read */
		if((Trend_Address_Read_Flash.Column == 0)
		 &&(Trend_Address_Read_Flash.Page == 0)
		 &&(Trend_Address_Read_Flash.Block == DRV_NAND_Second_Partition_Block_Start))
		{
			DRV_TREND_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}

/*%C 					Control of the index validity 					*/
		if(Trend_Address_Read_Flash.Block 
				< DRV_NAND_Second_Partition_Block_Start)
		{
			Trend_Address_Read_Flash.Block 
				= DRV_NAND_Second_Partition_Block_Start;
			DRV_TREND_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}
		else if(Trend_Address_Read_Flash.Block 
				> DRV_NAND_Second_Partition_Block_End)
		{
			Trend_Address_Read_Flash.Block 
				= DRV_NAND_Second_Partition_Block_End;
			DRV_TREND_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}
	
		if(Trend_Address_Read_Flash.Page < 0)
		{
			Trend_Address_Read_Flash.Page = 0;
			DRV_TREND_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}
		else if(Trend_Address_Read_Flash.Page > LAST_PAGE_IN_BLOCK)
		{
			Trend_Address_Read_Flash.Page = LAST_PAGE_IN_BLOCK;
			DRV_TREND_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}
	
		if(Trend_Address_Read_Flash.Column < 0)
		{
			Trend_Address_Read_Flash.Column = 0;
			DRV_TREND_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}
		else if(Trend_Address_Read_Flash.Column >= TREND_FLASH_PAGE_SIZE)
		{
			Trend_Address_Read_Flash.Column = TREND_FLASH_PAGE_SIZE - 1;
			DRV_TREND_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}



		
/*%C - If the column is lower than the output buffer size (the column is  */
/*%C   situated at the start of the page),  the*/
/*%C   next column is Zero, and we store the last column adress. */
 
  		   	if((Trend_Address_Read_Flash.Column <= TREND_BUFFER_SIZE_READ)
			&&(Trend_Address_Read_Flash.Column > 0))
			{
				Previous_Column = Trend_Address_Read_Flash.Column;
				Trend_Address_Read_Flash.Column = 0;
			}	  
/*%C  - If the column is between the conditions written before (default case)*/
/*%C    then the output buffer is completely loaded .*/	 	

 			else if (Trend_Address_Read_Flash.Column == 0) 
			{
				Trend_Address_Read_Flash.Column
					= TREND_FLASH_PAGE_SIZE
					 -TREND_BUFFER_SIZE_READ;
					
				if (Trend_Address_Read_Flash.Page <= 0)
				{
					if (Trend_Address_Read_Flash.Block <= 
											DRV_NAND_First_Partition_Block_Start)
					{
/*%C WARNING : the block number 0 is reserved for "Bad block map", */
/*%C so it can't be used!  */
						Trend_Address_Read_Flash.Block = 
											DRV_NAND_Second_Partition_Block_End;
					 	while((DRV_NAND_Bad_Block_Map[
									Trend_Address_Read_Flash.Block] 
									== 0)
							&&(Number_Bad_Block <= DRV_NAND_Maximum_Bad_Block))
						{
							Trend_Address_Read_Flash.Block = 
										Trend_Address_Read_Flash.Block - 1;
							Number_Bad_Block = Number_Bad_Block + 1;
						}
						Number_Bad_Block = 0;
					}
					else
					{
						do
						{
						 	Trend_Address_Read_Flash.Block = 
								Trend_Address_Read_Flash.Block - 1;
							Number_Bad_Block = Number_Bad_Block + 1;	
						}
						while((DRV_NAND_Bad_Block_Map[
								Trend_Address_Read_Flash.Block] 
								== 0)
   						   &&(Number_Bad_Block <= DRV_NAND_Maximum_Bad_Block));
   						Number_Bad_Block = 0;	
					}
					Trend_Address_Read_Flash.Page = LAST_PAGE_IN_BLOCK;
					if(Trend_Address_Read_Flash.Block 
						== (DRV_TREND_Address_Write_Flash.Block + 1))
					{
					   	DRV_TREND_Read_Request = ENDED;
					  	DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Trend_Address_Read_Flash.Block 
							==  DRV_NAND_Second_Partition_Block_Start)
					&&(DRV_TREND_Address_Write_Flash.Block 
						>= (DRV_NAND_Second_Partition_Block_End -1)))
					{
					  	DRV_TREND_Read_Request = ENDED;
					  	DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Trend_Address_Read_Flash.Block 
						==  DRV_NAND_Second_Partition_Block_End)
				   	&&(DRV_TREND_Partition_Full == FALSE))
					{
					 	DRV_TREND_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}

					else
					{
					}

				}
				else
				{
					Trend_Address_Read_Flash.Page = 
						Trend_Address_Read_Flash.Page - 1;
					if(Trend_Address_Read_Flash.Block 
						== (DRV_TREND_Address_Write_Flash.Block + 1))
					{
					  	DRV_TREND_Read_Request = ENDED;
					  	DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Trend_Address_Read_Flash.Block 
							==  DRV_NAND_Second_Partition_Block_Start)
					&&(DRV_TREND_Address_Write_Flash.Block 
						>= (DRV_NAND_Second_Partition_Block_End -1)))
					{
					  	DRV_TREND_Read_Request = ENDED;
					   	DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Trend_Address_Read_Flash.Block 
						==  DRV_NAND_Second_Partition_Block_End)
				   	&&(DRV_TREND_Partition_Full == FALSE))
					{
					 	DRV_TREND_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}

					else
					{
					}
				}
				  
 		 	}
 		 	else
			{
				Trend_Address_Read_Flash.Column
					= Trend_Address_Read_Flash.Column 
					- TREND_BUFFER_SIZE_READ;
			}		   

	  	if(DRV_TREND_Partition_Full == FALSE)
		{
 			Written_Data_Number = (UWORD32)((Trend_Address_Read_Flash.Block
										- DRV_NAND_Second_Partition_Block_Start)
										 * NAND_FLASH_BLOCK_SIZE);
 			
			Written_Data_Number = Written_Data_Number
							 +((UWORD32)(Trend_Address_Read_Flash.Page)
							 				* MONITORING_FLASH_PAGE_SIZE);

			Written_Data_Number = Written_Data_Number
							 + (UWORD32)Trend_Address_Read_Flash.Column;
			
			if(Written_Data_Number < NbBytesMonitoringFlashTrendToWrite)
			{

					NbBytesMonitoringFlashTrendToWrite = Written_Data_Number 
													   + TREND_BUFFER_SIZE_READ;
			}
			else
			{
			}
 
		}
		else
		{
		}
	}

/******************************************************************************/
/*%C After a request from the host computer, the read must run .*/
	else if(DRV_TREND_Read_Request == RUNNING)
	{

		Column = (UWORD16)Trend_Address_Read_Flash.Column;
	   /* Page Read  first command*/
		DRV_NAND_CommandInput(0x00) ;
		CMD_ME1 = 0 ;
  	   	/*the right address is sent */
	   	DRV_NAND_AddressInput(Trend_Address_Read_Flash.Block,
	   						   Trend_Address_Read_Flash.Page,
	   						   (UWORD16)Column);
		ALE_ME1 = 0 ;
		/* Page Read Second command */
		DRV_NAND_CommandInput(0x30);
		CMD_ME1 = 0 ;
/*%C waiting for BUSY signal or a time out of 50 µs (the read operation  */
/*%C should be less than 25 µs). */
 	  	T2IR  = 0;
		T2    = 0x01;
		T2CON = 0x00C7;
		while((BUSY_MEM1 == 0) && (T2IR == 0));
			
				/*****************************************/
/*%C if the UART buffer is empty, then it can be reloaded.*/
		if (DRV_TREND_New_Data == FALSE)
		{
			DRV_TREND_Received_Data = 0 ;

/*%C The way to load of the ouptput buffer depends on where the column index */
/*%C is pointing into a page :         */

/*%C - If the column is lower than the output buffer size (the column is  */
/*%C   situated at the start of the page), we load all the buffer size,but the*/
/*%C   next column is Zero, and we store the last column adress. */
 
		   	if((Column <= MONIT_BUFFER_SIZE_READ)
			&&(Column > 0))
			{
				for(i=0;i<TREND_BUFFER_SIZE_READ;i++)
				{
			   		DRV_TREND_UART_Buffer_Var[(TREND_BUFFER_SIZE_READ - 1) - i]
							= *MONITFLASH_Data;
					DRV_TREND_Received_Data += 1;
				}
	            Trend_Address_Read_Flash.Column = 0;	
				Previous_Column = (UBYTE)Column;
				DRV_TREND_New_Data = TRUE;
			 }

/*%C - If the column is Zero, and as we know the last colum adress (     */
/*%C   "Previous_Column" variable), we can load the output buffer not */
/*%C   completely but with the remaining data. */

			 else if(Column == 0)
			 {
				for(i=0;i<Previous_Column;i++)
				{
			   		DRV_TREND_UART_Buffer_Var[(Previous_Column - 1) - i]
							= *MONITFLASH_Data;
				   	DRV_TREND_Received_Data += 1;

				}
			   	Trend_Address_Read_Flash.Column = 
						Trend_Address_Read_Flash.Column - 1;
				DRV_TREND_New_Data = TRUE;
			 }

				
/*%C - If the column is upper than the end of page minus the output    */
/*%C   buffer size (the column point at the end of the page but there is not */
/*%C   enough data to send ), then the column goes to the end of page minus */
/*%C   the output buffer size. So at the next step, the ooutput buffer */
/*%C   will be totally loaded .             */

		   	else if(Column > 
					(TREND_FLASH_PAGE_SIZE - TREND_BUFFER_SIZE_READ))
			{
				Trend_Address_Read_Flash.Column = 
						TREND_FLASH_PAGE_SIZE - TREND_BUFFER_SIZE_READ;
			   	DRV_TREND_Received_Data = 0 ;
				DRV_TREND_New_Data = FALSE;
			}

/*%C  - If the column is between the conditions written before (default case)*/
/*%C    then the output buffer is completely loaded .*/	 	
 	
			else
			{  
				for(i=0;i<TREND_BUFFER_SIZE_READ;i++)
				{
			   		DRV_TREND_UART_Buffer_Var[(TREND_BUFFER_SIZE_READ-1)-i]
							= *MONITFLASH_Data;
					Trend_Address_Read_Flash.Column = 
						Trend_Address_Read_Flash.Column - 1;
					DRV_TREND_Received_Data += 1;
				}
				DRV_TREND_New_Data = TRUE;
		 	}
					   

/******************************************************************************/
/*%C Now, we must control the column, pages and blocks changes.    */
/*%C Each blocks changes, the validity of the next blocks must be test   */
/*%C with the "bad block map".    */	   	   

	   	   
	   	   if(Trend_Address_Read_Flash.Column < 0)
			{
				if (Trend_Address_Read_Flash.Page <= 0)
				{
					if (Trend_Address_Read_Flash.Block <= 
									  	(DRV_NAND_Second_Partition_Block_Start))
					{
						Trend_Address_Read_Flash.Block = 
										DRV_NAND_Second_Partition_Block_End;
					 	while((DRV_NAND_Bad_Block_Map[
									Trend_Address_Read_Flash.Block] 
									== 0)
						&&(Number_Bad_Block <= DRV_NAND_Maximum_Bad_Block))
						{
							Trend_Address_Read_Flash.Block = 
										Trend_Address_Read_Flash.Block - 1;
							Number_Bad_Block = Number_Bad_Block + 1;
						}
						Number_Bad_Block = 0;
					}
					else
					{
						do
						{
					 	Trend_Address_Read_Flash.Block = 
							Trend_Address_Read_Flash.Block - 1;	
							Number_Bad_Block = Number_Bad_Block + 1;	
						}
						while((DRV_NAND_Bad_Block_Map[
								Trend_Address_Read_Flash.Block] 
								== 0)
   						   &&(Number_Bad_Block <= DRV_NAND_Maximum_Bad_Block));
   						Number_Bad_Block = 0;			
					}
					Trend_Address_Read_Flash.Page = LAST_PAGE_IN_BLOCK;
					if(Trend_Address_Read_Flash.Block 
						== (DRV_TREND_Address_Write_Flash.Block + 1))
					{
					 	DRV_TREND_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Trend_Address_Read_Flash.Block 
							==  DRV_NAND_Second_Partition_Block_Start)
					&&(DRV_TREND_Address_Write_Flash.Block 
						>= (DRV_NAND_Second_Partition_Block_End -1)))
					{
					 	DRV_TREND_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Trend_Address_Read_Flash.Block 
						==  DRV_NAND_Second_Partition_Block_End)
				   	&&(DRV_TREND_Partition_Full == FALSE))
					{
						 	DRV_TREND_Read_Request = ENDED;
							DRV_NAND_End_Of_Read = TRUE;
					}

					else
					{
					}	
				}
				else
				{
					Trend_Address_Read_Flash.Page = 
						Trend_Address_Read_Flash.Page - 1;
					if(Trend_Address_Read_Flash.Block 
						== (DRV_TREND_Address_Write_Flash.Block + 1))
					{
					 	DRV_TREND_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Trend_Address_Read_Flash.Block 
							==  DRV_NAND_Second_Partition_Block_Start)
					&&(DRV_TREND_Address_Write_Flash.Block 
						>= (DRV_NAND_Second_Partition_Block_End -1)))
					{
					 	DRV_TREND_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Trend_Address_Read_Flash.Block 
						==  DRV_NAND_Second_Partition_Block_End)
				   	&&(DRV_TREND_Partition_Full == FALSE))
					{
						 	DRV_TREND_Read_Request = ENDED;
							DRV_NAND_End_Of_Read = TRUE;
					}
					else
					{
					}
				}	
				Trend_Address_Read_Flash.Column = TREND_FLASH_PAGE_SIZE
													-TREND_BUFFER_SIZE_READ;
			}
		}
	}
}