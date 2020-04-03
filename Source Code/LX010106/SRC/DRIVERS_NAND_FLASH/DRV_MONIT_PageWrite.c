/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505													  */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_MONIT_PageWrite.c  										  */
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
#include "DRV_MONIT_PageWrite.h"

			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_MONIT_PageWrite(void)
{

/* Monitoring Flash pointer declaration */
UBYTE *MONITFLASH_Data = (UBYTE *)MONITORING_FLASH_POINTER_ADDRESS;
static UBYTE First_Start = TRUE;

   			
 	DRV_MONIT_Step = DRV_MONIT_Step + 1;

	
	if(DRV_MONIT_Step == 1)
	{
 	 
 
                 /**********************************************/
/*%C Writing command is launched :*/
/*%C   Write first Command */
		   	DRV_NAND_CommandInput(0x80) ;
			CMD_ME1 = 0 ; 

/*%C the right address is sent */
			DRV_NAND_AddressInput( DRV_MONIT_Address_Write_Flash.Block
								 , DRV_MONIT_Address_Write_Flash.Page
								 , DRV_MONIT_Address_Write_Flash.Column) ;
			ALE_ME1 =  0 ; 

		 
		 
			DRV_MONIT_Data_Load();

	}
	else if((DRV_MONIT_Step > 1) && (DRV_MONIT_Step <= 16))
	{
			DRV_MONIT_Data_Load();
	}
	else
	{
	}

/*EOF*/
}