/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505													  */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_NAND_CommandInput.c 									  */
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

						  
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_NAND_CommandInput(UBYTE Flash_Command)
{
/* Monitoring Flash pointer declaration */
	UBYTE *MONITFLASH_Data = (UBYTE *)MONITORING_FLASH_POINTER_ADDRESS;
/* Address Lacth is enabled */
	ALE_ME1 = 0 ;
/* Command Latch is disabled */
	CMD_ME1 = 1 ;
	
	/* Command is sent */
	*MONITFLASH_Data = Flash_Command ;

/* small delay to let the µc sending the command onto the bus */
	_nop_() ;

}
