/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505													  */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_MONIT_PageRead.c											  */
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
#include "Flash_Monit_data.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_RTC.h"
#include "Driver_USB_Data.h"
#include "DRV_MONIT_PageRead.h"

			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_MONIT_PageRead(void)
{
  /* Monitoring Flash pointer declaration */
	UBYTE *MONITFLASH_Data = (UBYTE *)MONITORING_FLASH_POINTER_ADDRESS;

 	UBYTE i = 0;
	UBYTE Number_Bad_Block = 0;
	UWORD16 Column = 0;
	UWORD32 Written_Data_Number = 0;
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
	static t_FlashParam  Monit_Address_Read_Flash;
	static UWORD16  Previous_Column = 0;
	static UBYTE Mutex = FALSE;

											


/******************************************************************************/
/*%C When the computer requests a monitoring data transfert, it must start  */
/*%C at the last flash writing adress */
	if (DRV_MONIT_Read_Request == REQUEST)
	{
/*%C Init of special variables */
		DRV_NAND_End_Of_Read = FALSE;
		DRV_MONIT_Received_Data = 0;
		DRV_MONIT_New_Data = FALSE;
		Mutex = FALSE;

/*%C The last writing address is loaded into the flash reading adress .*/

		Monit_Address_Read_Flash.Column = 
							DRV_MONIT_Address_Start_Read_Flash_Recording.Column;
		Monit_Address_Read_Flash.Page =	
						   	DRV_MONIT_Address_Start_Read_Flash_Recording.Page;
 		Monit_Address_Read_Flash.Block = 
 						  	DRV_MONIT_Address_Start_Read_Flash_Recording.Block;


							
/*%C Now the reading processus can start. */
/*%C This is set to "RUNNING" here, because due to the conditions of the  */
/*%C block, page, column address, it can be set to "ENDED". */
		DRV_MONIT_Read_Request = RUNNING;

/*%C In the case of first start, stop the read */
		if((Monit_Address_Read_Flash.Column == 0)
		 &&(Monit_Address_Read_Flash.Page == 0)
		 &&(Monit_Address_Read_Flash.Block == DRV_NAND_First_Partition_Block_Start))
		{
			DRV_MONIT_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}
 

/*%C 					Control of the index validity 					*/
		if(Monit_Address_Read_Flash.Block 
				< DRV_NAND_First_Partition_Block_Start)
		{
			Monit_Address_Read_Flash.Block 
				= DRV_NAND_First_Partition_Block_Start;
			DRV_MONIT_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}
		else if(Monit_Address_Read_Flash.Block 
				> DRV_NAND_First_Partition_Block_End)
		{
			Monit_Address_Read_Flash.Block 
				= DRV_NAND_First_Partition_Block_End;
			DRV_MONIT_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}
	
		if(Monit_Address_Read_Flash.Page < 0)
		{
			Monit_Address_Read_Flash.Page = 0;
			DRV_MONIT_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}
		else if(Monit_Address_Read_Flash.Page > LAST_PAGE_IN_BLOCK)
		{
			Monit_Address_Read_Flash.Page = LAST_PAGE_IN_BLOCK;
			DRV_MONIT_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}
	
		if(Monit_Address_Read_Flash.Column < 0)
		{
			Monit_Address_Read_Flash.Column = 0;
			DRV_MONIT_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}
		else if(Monit_Address_Read_Flash.Column >= MONITORING_FLASH_PAGE_SIZE)
		{
			Monit_Address_Read_Flash.Column = MONITORING_FLASH_PAGE_SIZE - 1;
			DRV_MONIT_Read_Request = ENDED;
			DRV_NAND_End_Of_Read = TRUE;
		}





/*%C - If the column is lower than the output buffer size (the column is  */
/*%C   situated at the start of the page),  the*/
/*%C   next column is Zero, and we store the last column adress. */
 
  		   	if((Monit_Address_Read_Flash.Column <= MONIT_BUFFER_SIZE_READ)
			&&(Monit_Address_Read_Flash.Column > 0))
			{
				Previous_Column = Monit_Address_Read_Flash.Column;
				Monit_Address_Read_Flash.Column = 0;
			 }	  
/*%C  - If the column is between the conditions written before (default case)*/
/*%C    then the output buffer is completely loaded .*/	 	

 			else if (Monit_Address_Read_Flash.Column == 0) 
			{
				Monit_Address_Read_Flash.Column
					= MONITORING_FLASH_PAGE_SIZE
					- MONIT_BUFFER_SIZE_READ;
					
				if (Monit_Address_Read_Flash.Page <= 0)
				{
					if (Monit_Address_Read_Flash.Block <= 
											DRV_NAND_First_Partition_Block_Start)
					{
/*%C WARNING : the block number 0 is reserved for "Bad block map", */
/*%C so it can't be used!  */
						Monit_Address_Read_Flash.Block = 
											DRV_NAND_First_Partition_Block_End;
					 	while((DRV_NAND_Bad_Block_Map[
									Monit_Address_Read_Flash.Block] 
									== 0)
							&&(Number_Bad_Block <= DRV_NAND_Maximum_Bad_Block))
						{
							Monit_Address_Read_Flash.Block = 
										Monit_Address_Read_Flash.Block - 1;
							Number_Bad_Block = Number_Bad_Block + 1;
						}
						Number_Bad_Block = 0;
					}
					else
					{
						do
						{
						 	Monit_Address_Read_Flash.Block = 
								Monit_Address_Read_Flash.Block - 1;
							Number_Bad_Block = Number_Bad_Block + 1;	
						}
						while((DRV_NAND_Bad_Block_Map[
								Monit_Address_Read_Flash.Block] 
								== 0)
   						   &&(Number_Bad_Block <= DRV_NAND_Maximum_Bad_Block));
   						Number_Bad_Block = 0;	
					}
					Monit_Address_Read_Flash.Page = LAST_PAGE_IN_BLOCK;
					if(Monit_Address_Read_Flash.Block 
						== (DRV_MONIT_Address_Write_Flash.Block + 1))
					{
					 	DRV_MONIT_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Monit_Address_Read_Flash.Block 
							==  DRV_NAND_First_Partition_Block_Start)
					&&(DRV_MONIT_Address_Write_Flash.Block 
						>= (DRV_NAND_First_Partition_Block_End -1)))
					{
					 	DRV_MONIT_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Monit_Address_Read_Flash.Block 
						==  DRV_NAND_First_Partition_Block_End)
				   	&&(DRV_MONIT_Partition_Full	== FALSE))
					{
						 	DRV_MONIT_Read_Request = ENDED;
							DRV_NAND_End_Of_Read = TRUE;
					}

					else
					{
					}
				}
				else
				{
					Monit_Address_Read_Flash.Page = 
						Monit_Address_Read_Flash.Page - 1;
					if(Monit_Address_Read_Flash.Block 
						== (DRV_MONIT_Address_Write_Flash.Block + 1))
					{
					 	DRV_MONIT_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Monit_Address_Read_Flash.Block 
							==  DRV_NAND_First_Partition_Block_Start)
					&&(DRV_MONIT_Address_Write_Flash.Block 
						>= (DRV_NAND_First_Partition_Block_End -1)))
					{
					 	DRV_MONIT_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Monit_Address_Read_Flash.Block 
						==  DRV_NAND_First_Partition_Block_End)
				   	&&(DRV_MONIT_Partition_Full	== FALSE))
					{
						 	DRV_MONIT_Read_Request = ENDED;
							DRV_NAND_End_Of_Read = TRUE;
					}

					else
					{
					}
				}
				  
 		 	}
 		 	else
			{
				Monit_Address_Read_Flash.Column
					= Monit_Address_Read_Flash.Column 
					- MONIT_BUFFER_SIZE_READ;
			}

				   
 		if(DRV_MONIT_Partition_Full == FALSE)
		{
 			Written_Data_Number = (UWORD32)((Monit_Address_Read_Flash.Block
										- DRV_NAND_First_Partition_Block_Start) 
							 				* NAND_FLASH_BLOCK_SIZE);
 			
			Written_Data_Number = Written_Data_Number
							 +((UWORD32)(Monit_Address_Read_Flash.Page)
							 				* MONITORING_FLASH_PAGE_SIZE);

			Written_Data_Number = Written_Data_Number
							 + (UWORD32)Monit_Address_Read_Flash.Column;
			
			if(Written_Data_Number < NbBytesMonitoringFlashMonitToWrite)
			{
				if(Written_Data_Number < MONIT_BUFFER_SIZE_READ)
				{
					NbBytesMonitoringFlashMonitToWrite = 0;
				}
				else
				{
					NbBytesMonitoringFlashMonitToWrite = Written_Data_Number
												   + MONIT_BUFFER_SIZE_READ;
				}
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
	else if(DRV_MONIT_Read_Request == RUNNING)
	{

		Column = (UWORD16)Monit_Address_Read_Flash.Column;
	   /* Page Read  first command*/
		DRV_NAND_CommandInput(0x00) ;
		CMD_ME1 = 0 ;
  	   	/*the right address is sent */
	   	DRV_NAND_AddressInput(Monit_Address_Read_Flash.Block,
	   						   Monit_Address_Read_Flash.Page,
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
		if (DRV_MONIT_New_Data == FALSE)
		{
			DRV_MONIT_Received_Data = 0 ;

/*%C If the ventilation is ON we must send the current date */
			if((VentilState != VEN_VENTIL_DISABLE)
			&&(Mutex == FALSE))
			{
				DRV_MONIT_UART_Buffer_Var[0]
					= (UBYTE)HORODATAGE;
				DRV_MONIT_UART_Buffer_Var[1] 
					= (UBYTE)DB_RTCRead(DB_RTC_DAY_U16);
				DRV_MONIT_UART_Buffer_Var[2] 
					= (UBYTE)DB_RTCRead(DB_RTC_MONTH_U16);
				DRV_MONIT_UART_Buffer_Var[3] 
					= (UBYTE)DB_RTCRead(DB_RTC_YEAR_U16);
				DRV_MONIT_UART_Buffer_Var[4] 
					= (UBYTE)DB_RTCRead(DB_RTC_HOUR_U16);
				DRV_MONIT_UART_Buffer_Var[5] 
					= (UBYTE)DB_RTCRead(DB_RTC_MINUTE_U16);
				DRV_MONIT_UART_Buffer_Var[6] 
					= (UBYTE)DB_RTCRead(DB_RTC_SECOND_U16);
				DRV_MONIT_UART_Buffer_Var[7] 
					= 0x55;
				DRV_MONIT_UART_Buffer_Var[8] 
					= 0x55;

				DRV_MONIT_Received_Data = 9;
				DRV_MONIT_New_Data = TRUE;
				Mutex = TRUE;
			}
/*%C After sending the date when the ventilation is ON, or if the ventilation is OFF*/
/*%C we read the NAND Flash*/
			else if((Mutex == TRUE)
				  ||(VentilState == VEN_VENTIL_DISABLE))	
			{

/*%C The way to load of the ouptput buffer depends on where the column index */
/*%C is pointing into a page :         */

/*%C - If the column is lower than the output buffer size (the column is  */
/*%C   situated at the start of the page), we load all the buffer size,but the*/
/*%C   next column is Zero, and we store the last column adress. */
 
			   	if((Column <= MONIT_BUFFER_SIZE_READ)
				&&(Column > 0))
				{
					for(i=0;i<MONIT_BUFFER_SIZE_READ;i++)
					{
						DRV_MONIT_UART_Buffer_Var[(MONIT_BUFFER_SIZE_READ - 1)- i]
			   							= *MONITFLASH_Data;
						DRV_MONIT_Received_Data += 1;
					}
		            Monit_Address_Read_Flash.Column = 0;	
					Previous_Column = (UBYTE)Column;
					DRV_MONIT_New_Data = TRUE;
				 } 	   			 

/*%C - If the column is Zero, and as we know the last colum adress (     */
/*%C   "Previous_Column" variable), we can load the output buffer not */
/*%C   completely but with the remaining data. */

			  	 else if(Column == 0)
				 {
					for(i = 0;i < Previous_Column ;i++)
					{
				   		DRV_MONIT_UART_Buffer_Var[(Previous_Column - 1) - i]
								= *MONITFLASH_Data;
					   	DRV_MONIT_Received_Data += 1;
	
					}
				   	Monit_Address_Read_Flash.Column = 
							Monit_Address_Read_Flash.Column - 1;
					DRV_MONIT_New_Data = TRUE;
				 }
		 	
				
/*%C - If the column is upper than the end of page minus the output    */
/*%C   buffer size (the column point at the end of the page but there is not */
/*%C   enough data to send ), then the column goes to the end of page minus */
/*%C   the output buffer size. So at the next step, the output buffer */
/*%C   will be totally loaded .             */

			   	else if(Column > 
						(MONITORING_FLASH_PAGE_SIZE - MONIT_BUFFER_SIZE_READ))
				{
					Monit_Address_Read_Flash.Column = 
							MONITORING_FLASH_PAGE_SIZE - MONIT_BUFFER_SIZE_READ;
				   	DRV_MONIT_Received_Data = 0 ;
					DRV_MONIT_New_Data = FALSE;
				}  	  

/*%C  - If the column is between the conditions written before (default case)*/
/*%C    then the output buffer is completely loaded .*/	 	

			   else
				{  		
					for(i=0;i<MONIT_BUFFER_SIZE_READ;i++)
					{
				   		DRV_MONIT_UART_Buffer_Var[(MONIT_BUFFER_SIZE_READ-1)-i]
								= *MONITFLASH_Data;
						Monit_Address_Read_Flash.Column = 
							Monit_Address_Read_Flash.Column - 1;
						DRV_MONIT_Received_Data += 1;
					}
					DRV_MONIT_New_Data = TRUE;
			   	}
			}
					
		 		

/******************************************************************************/
/*%C Now, we must control the column, pages and blocks changes.    */
/*%C Each blocks changes, the validity of the next blocks must be test   */
/*%C with the "bad block map".    */
	   	   
	   	   
	   	   if(Monit_Address_Read_Flash.Column < 0)
			{
				if (Monit_Address_Read_Flash.Page <= 0)
				{
					if (Monit_Address_Read_Flash.Block <= 
										DRV_NAND_First_Partition_Block_Start)
					{
/*%C WARNING : the block number 0 is reserved for "Bad block map", */
/*%C so it can't be used!  */
						Monit_Address_Read_Flash.Block = 
											DRV_NAND_First_Partition_Block_End;
					 	while((DRV_NAND_Bad_Block_Map[
									Monit_Address_Read_Flash.Block] 
									== 0)
							&&(Number_Bad_Block <= DRV_NAND_Maximum_Bad_Block))
						{
							Monit_Address_Read_Flash.Block = 
										Monit_Address_Read_Flash.Block - 1;
							Number_Bad_Block = Number_Bad_Block + 1;
						}
						Number_Bad_Block = 0;
					}
					else
					{
						do
						{
						 	Monit_Address_Read_Flash.Block = 
								Monit_Address_Read_Flash.Block - 1;
							Number_Bad_Block = Number_Bad_Block + 1;	
						}
						while((DRV_NAND_Bad_Block_Map[
								Monit_Address_Read_Flash.Block] 
								== 0)
   						   &&(Number_Bad_Block <= DRV_NAND_Maximum_Bad_Block));
   						Number_Bad_Block = 0;	
					}
					Monit_Address_Read_Flash.Page = LAST_PAGE_IN_BLOCK;
					if(Monit_Address_Read_Flash.Block 
						== (DRV_MONIT_Address_Write_Flash.Block + 1))
					{
					 	DRV_MONIT_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Monit_Address_Read_Flash.Block 
							==  DRV_NAND_First_Partition_Block_Start)
					&&(DRV_MONIT_Address_Write_Flash.Block 
						>= (DRV_NAND_First_Partition_Block_End -1)))
					{
					 	DRV_MONIT_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Monit_Address_Read_Flash.Block 
						==  DRV_NAND_First_Partition_Block_End)
				   	&&(DRV_MONIT_Partition_Full	== FALSE))
					{
						 	DRV_MONIT_Read_Request = ENDED;
							DRV_NAND_End_Of_Read = TRUE;
					}
					else
					{
					}				
				}
				else
				{
					Monit_Address_Read_Flash.Page = 
						Monit_Address_Read_Flash.Page - 1;
					if(Monit_Address_Read_Flash.Block 
						== (DRV_MONIT_Address_Write_Flash.Block + 1))
					{
					 	DRV_MONIT_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Monit_Address_Read_Flash.Block 
							==  DRV_NAND_First_Partition_Block_Start)
					&&(DRV_MONIT_Address_Write_Flash.Block 
						>= (DRV_NAND_First_Partition_Block_End -1)))
					{
					 	DRV_MONIT_Read_Request = ENDED;
						DRV_NAND_End_Of_Read = TRUE;
					}
					else if((Monit_Address_Read_Flash.Block 
						==  DRV_NAND_First_Partition_Block_End)
				   	&&(DRV_MONIT_Partition_Full	== FALSE))
					{
						 	DRV_MONIT_Read_Request = ENDED;
							DRV_NAND_End_Of_Read = TRUE;
					}
					else
					{
					}
				}	
				Monit_Address_Read_Flash.Column = MONITORING_FLASH_PAGE_SIZE
													- MONIT_BUFFER_SIZE_READ;
			}
		}
	}

	
}
