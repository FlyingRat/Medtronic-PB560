/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EVENT_Erase_Sector.c                                     */
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
#include "structure.h"
#include "define.h"
#include "Main_Data.h"
#include "Flash_Event_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UBYTE DRV_EVENT_Erase_Sector(UBYTE secteur)
{  
#ifndef _BORLAND
 	UWORD16 xhuge *adr_flash; 

/*%C  1st cycle erazing séquence			  */
	adr_flash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS +0xAAA);
	*adr_flash = 0x00AA;
/*%C 2d  cycle erazing séquence			  */
	adr_flash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS +0x554);
	*adr_flash = 0x0055;
/*%C 3d cycle erazing séquence			  */
	adr_flash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS +0xAAA);
	*adr_flash = 0x0080;
/*%C 4th cycle erazing séquence			  */
	adr_flash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS + 0xAAA);
	*adr_flash = 0x00AA;
/*%C 5th cycle erazing séquence			  */
	adr_flash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS + 0x554);
	*adr_flash = 0x0055; 
/*%C 6th cycle erazing séquence			  */
/*%C  Loading the adress of sector to eraze, depending of the kind of memory		*/
	if (type_memoire == BOTTOM_BOOT)
		adr_flash =  (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS + adresse_secteur_bottom[secteur]);
	else if  (type_memoire == TOP_BOOT)
		adr_flash =  (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS + adresse_secteur_top[secteur]);
	else return(1); /*%C return an error of memory identification 	*/
 	
/*%C storage of the erazig adress ( for a possible stand by )	*/
	Erase_Adress = adr_flash;

/*%C vérify the memory flash disponibility   */
	*adr_flash = 0x30; 

	Flash_State = DRV_EVENT_ERASE;
	return(0);											
#endif
}
