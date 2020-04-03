/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505													  */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_NAND_Flash_Init.c 									  */
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


#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Config.h"
#include "Flash_Monit_data.h"
#include "DRV_NAND_Flash_Init.h"


			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_NAND_Flash_Init(void)
{
/*%C At the start of the device, we must reload the last write index. */
	DRV_MONIT_Address_Write_Flash.Block = 
						(SWORD16)DB_ConfigRead(FLASH_MONIT_WRITE_BLOCK_U16);
	DRV_MONIT_Address_Write_Flash.Page =  
						(SWORD16)DB_ConfigRead(FLASH_MONIT_WRITE_PAGE_U16);
	DRV_MONIT_Address_Write_Flash.Column = 
						(SWORD16)DB_ConfigRead(FLASH_MONIT_WRITE_COLUMN_U16);
/*%C At the start of the device, we must reload the last write index. */
	DRV_MONIT_Address_Write_Flash_Recording.Block = 
						(SWORD16)DB_ConfigRead(FLASH_MONIT_WRITE_BLOCK_U16);
	DRV_MONIT_Address_Write_Flash_Recording.Page =  
						(SWORD16)DB_ConfigRead(FLASH_MONIT_WRITE_PAGE_U16);
	DRV_MONIT_Address_Write_Flash_Recording.Column = 
						(SWORD16)DB_ConfigRead(FLASH_MONIT_WRITE_COLUMN_U16);

/*%C At the start of the device, we must reload the last write index. */
	DRV_MONIT_Address_Start_Read_Flash_Recording.Block = 
						(SWORD16)DB_ConfigRead(FLASH_MONIT_WRITE_BLOCK_U16);
	DRV_MONIT_Address_Start_Read_Flash_Recording.Page =  
						(SWORD16)DB_ConfigRead(FLASH_MONIT_WRITE_PAGE_U16);
	DRV_MONIT_Address_Start_Read_Flash_Recording.Column = 
						(SWORD16)DB_ConfigRead(FLASH_MONIT_WRITE_COLUMN_U16);

/*%C At the start of the device, we must reload the last write index. */
	DRV_TREND_Address_Write_Flash.Block = 
						(SWORD16)DB_ConfigRead(FLASH_TREND_WRITE_BLOCK_U16);
	DRV_TREND_Address_Write_Flash.Page =  
						(SWORD16)DB_ConfigRead(FLASH_TREND_WRITE_PAGE_U16);
	DRV_TREND_Address_Write_Flash.Column = 
						(SWORD16)DB_ConfigRead(FLASH_TREND_WRITE_COLUMN_U16);
/*%C At the start of the device, we must reload the last write index. */
	DRV_TREND_Address_Write_Flash_Recording.Block = 
						(SWORD16)DB_ConfigRead(FLASH_TREND_WRITE_BLOCK_U16);
	DRV_TREND_Address_Write_Flash_Recording.Page =  
						(SWORD16)DB_ConfigRead(FLASH_TREND_WRITE_PAGE_U16);
	DRV_TREND_Address_Write_Flash_Recording.Column = 
						(SWORD16)DB_ConfigRead(FLASH_TREND_WRITE_COLUMN_U16);
/*%C At the start of the device, we must reload the last write index. */
	DRV_TREND_Address_Start_Read_Flash_Recording.Block = 
						(SWORD16)DB_ConfigRead(FLASH_TREND_WRITE_BLOCK_U16);
	DRV_TREND_Address_Start_Read_Flash_Recording.Page =  
						(SWORD16)DB_ConfigRead(FLASH_TREND_WRITE_PAGE_U16);
	DRV_TREND_Address_Start_Read_Flash_Recording.Column = 
						(SWORD16)DB_ConfigRead(FLASH_TREND_WRITE_COLUMN_U16);
}