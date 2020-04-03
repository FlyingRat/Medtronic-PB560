/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EVENT_RazPointerSector.c                                   */
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
#include "DB_Config.h"
#include "DB_Control.h"
#include "structure.h"
#include "Main_Data.h"
#include "DRV_EVENT_RazPointerSector.h"
#include "Flash_Event_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_EVENT_RazPointerSector(void)
{
#ifndef _BORLAND
	DRV_EVENT_Erase_Flash();
/*%C Flash ptr reset																				*/
	Ptr_Flash = 0;
/*%C Flash ptr save and reset in Eeprom													*/
// Raz et Sauvegarde dans l'e2prom du pointeur Flash
	DB_ConfigWrite(RETRIEVAL_EVENT_ADRESS_MSB_U16,0);
	DB_ConfigWrite(RETRIEVAL_EVENT_ADRESS_LSB_U16,0);
/*%C Falsh sector reset																			*/
	Num_Sector = 0;
/*%C Short beep request																			*/
	DB_ControlWrite(VALIDATION_BIP_U16,
						 BIP_VERY_LONG);

#endif
}