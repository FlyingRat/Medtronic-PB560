/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EVENT_Program_Flash.c                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif	
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "io_declare.h"
#include "structure.h"
#include "Main_Data.h"
#include "Flash_Event_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UBYTE DRV_EVENT_Program_Flash( UWORD16 data_prog
									  , UWORD16 xhuge *adr_prog)
{           
#ifndef _BORLAND
	UWORD16 xhuge *adr_flash; 
	
/*%CVérification of the adress			  */
	if (((long)adr_prog < EVENT_FLASH_START_ADDRESS) 
	|| ((long)adr_prog > EVENT_FLASH_END_ADDRESS))
		{
/*%C	Adress out of memory flash domain			  */
		return(1); 	
		}
	if ((((long)adr_prog % 2) != 0)) return(2); /*%C odd adress */
/*%C Vérification : is the flash memory free									  */
	if (BUSY_MEM2 == 0)
		{ 
		return (3);
		}
/*%C vérification : is the writting adress free		  */
	if ( *adr_prog != 0xFFFF)
		{
		return(4);
		}

/*%C 1st cycle programing séquence 			  */
	adr_flash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS + 0xAAA);
	*adr_flash = 0xAA;
	
/*%C 2d cycle programing séquence		  */
	adr_flash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS + 0x554);
	*adr_flash = 0x55;
	
/*%C 3d cycle programing séquence			  */
	adr_flash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS + 0xAAA);
	*adr_flash = 0xA0;
/*%C 4th cycle programing séquence			  */
/*%C Loading of data to program */
	*adr_prog = data_prog; 
/*%C Vérification : is the flash acces free				  */
	Flash_State = DRV_EVENT_WRITE; // waiting to detect an Uo changing on BUZY_MEM
/*%C writing process succed									  */

	return(0);						 
	#endif
}
