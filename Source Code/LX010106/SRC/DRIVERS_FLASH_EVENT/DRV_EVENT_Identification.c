/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EVENT_Identification.c                                     */
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
#include "typedef.h"
#include "enum.h"
#include "define.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DRV_EVENT_Identification(void)
{           
#ifndef _BORLAND
	UWORD16 xhuge *adr_flash; 
	UWORD16 type_memory;

	// identification of the kind of memeory: flash toop boot or bottom boot

/*%C 1st cycle identification séquence 		  */
	adr_flash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS +0xAAA);
	*adr_flash = 0x00AA;
/*%C 2d cycle identification séquence			  */
	adr_flash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS +0x554);
	*adr_flash = 0x0055;
/*%C 3d cycle identification séquence			  */
	adr_flash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS + 0xAAA);
	*adr_flash = 0x0090;
/*%C 4th cycle identification séquence			  */
	adr_flash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS +0x02);
	type_memory = *adr_flash;
	*adr_flash = 0xF0; // commande reset to leave the autoselect mode
/*%C type de mémoire par defaut bottom boot	  */
	if ((type_memory != BOTTOM_BOOT) && (type_memory != TOP_BOOT))  type_memory = BOTTOM_BOOT ; 
/*%C =BOTTOM_BOOT for a bottom boot, =TOP_BOOT for a top boot	 */
	return(type_memory);	
#endif
}
