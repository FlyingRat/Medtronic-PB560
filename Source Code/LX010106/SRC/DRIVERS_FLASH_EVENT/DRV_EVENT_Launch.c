/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EVENT_Launch.c                                     */
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
#include "Structure.h"
#include "io_declare.h"
#include "define.h"
#include "DB_Rtc.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_Current.h"
#include "DB_Config.h"
#include "DB_PowerSupply.h"

#include "DB_EventMngt.h"
#include "Main_Data.h"
#include "DRV_EVENT_Launch.h"
#include "Flash_Event_Data.h"
#include "Driver_Datas.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_EVENT_Launch(void)
{
#ifndef _BORLAND
UWORD16 Concaten16bit; 

/*%C Test to know if memory flash is free   */
if ((BUSY_MEM2 == 1) && (Flash_State != DRV_EVENT_FREE))
/*%C realeasing the memory flash state if its value is = 1 (after a writing) */
	Flash_State = DRV_EVENT_FREE;


/*%C Reading the adress in Eeprom and exclusion		  */
if (Mutex_Read_Adresse == FALSE)
	{
	if (Flash_State == DRV_EVENT_FREE)
		{
/*%C	Identification of the kind of memory flash: top boot or bottom boot	  */
		type_memoire = DRV_EVENT_Identification();
		if (type_memoire == TOP_BOOT)
			{
/*%C		 Sector search */
			if ((UWORD32)Ptr_Flash < adresse_secteur_top[7])			// 0x70000
				Num_Sector = (UBYTE)(((UWORD32)Ptr_Flash) / 0x10000); 
			else if ((UWORD32)Ptr_Flash < adresse_secteur_top[8])		// 0x78000 	
				Num_Sector = 7;
			else if ((UWORD32)Ptr_Flash < adresse_secteur_top[9])		// 0x7A000
				Num_Sector = 8;
			else if ((UWORD32)Ptr_Flash < adresse_secteur_top[10])	// 0x7C000
				Num_Sector = 9;
			else
				Num_Sector = 10;
			}
		else if  (type_memoire == BOTTOM_BOOT)
			{
/*%C		 Sector search */
			if ((UWORD32)Ptr_Flash < adresse_secteur_bottom[1]) 		// 0x04000
				Num_Sector = 0; 
			else if ((UWORD32)Ptr_Flash < adresse_secteur_bottom[2]) // 0x06000
				Num_Sector = 1;
			else if ((UWORD32)Ptr_Flash < adresse_secteur_bottom[3]) // 0x08000
				Num_Sector = 2;
			else if ((UWORD32)Ptr_Flash < adresse_secteur_bottom[4]) // 0x10000
				Num_Sector = 3;
			else
				Num_Sector = (UBYTE)(((UWORD32)Ptr_Flash / 0x10000) + 3); 
			}
		Mutex_Read_Adresse = TRUE;
		}
	}
else
	{
/*%C		 Sector erazing */
	if ((Ptr_Evenement == 0) && (Mutex_Flag_Erase == FALSE)) 
		{
		if (type_memoire == BOTTOM_BOOT)
			{
			if (adresse_secteur_bottom[Num_Sector+1] <= (UWORD32)Ptr_Flash + (10*EVENT_Last_Event_Parameter))
				{
/*%C		 	Erazing sequence */
				DRV_EVENT_Erase_Sector((Num_Sector+1)%11);
				Mutex_Flag_Erase = TRUE;
				}
			}
		else if (type_memoire == TOP_BOOT)
			{
			if (adresse_secteur_top[Num_Sector+1] <= (UWORD32)Ptr_Flash + (10*EVENT_Last_Event_Parameter))
				{
/*%C		 	Erazing sequence */
				DRV_EVENT_Erase_Sector((Num_Sector+1)%11);
				Mutex_Flag_Erase = TRUE;
				}
			}
		}

/*%C	 Test to detect an event presence */
	if (EventEnvironment[Ptr_Num_evenement_Read][EVENT_STATE_ID] == TRUE)
		{
		if (Flash_State == DRV_EVENT_FREE)
			{
/*%C	Left Shift one byte  to obtain the most significative byte */
			Concaten16bit = (UWORD16)EventEnvironment[Ptr_Num_evenement_Read][Ptr_Evenement+1] << 8;
/*%C		Logical OR between the first and the second event with a shift of a byte to obtain the result on a word	 */
			Concaten16bit = Concaten16bit | (UWORD16)EventEnvironment[Ptr_Num_evenement_Read][Ptr_Evenement];
/*%C		Data Programation						 */
			DRV_EVENT_Program_Flash(Concaten16bit, (UWORD16 xhuge *)((UWORD32)Ptr_Flash + EVENT_FLASH_START_ADDRESS));
/*%C		Increasing of the writing index adress	*/
			Ptr_Flash++;
/*%C		Increasing of the event index, modulo 2 */
			Ptr_Evenement += 2;
/*%C		 If it s the end of the event record 		 */
			if (Ptr_Evenement >= EVENT_Last_Event_Parameter-1) 
				{
/*%C			Test to ensure to treat a full size event 		 */
				if ((UWORD32)Ptr_Flash + EVENT_Last_Event_Parameter >= adresse_secteur_top[11]) 
					{
					Ptr_Flash = 0;
					Num_Sector = 0;
					Mutex_Flag_Erase = FALSE;
					}
/*%C			Erazing of the Event index	 */
				Ptr_Evenement = 0; 
				EventEnvironment[Ptr_Num_evenement_Read][EVENT_STATE_ID] = FALSE;
/*%C			Increasing of the writing index		 */
				Ptr_Num_evenement_Read++;
/*%C			Verification to ensure the reading index is no longer than the buffer  */
				if (Ptr_Num_evenement_Read >= TAILLE_BUFFER) Ptr_Num_evenement_Read = 0;
				}

/*%C		Sector  increasing										*/
			if (type_memoire == BOTTOM_BOOT)
				{
/*%C 			Sector détermination 						*/

				if ((UWORD32)Ptr_Flash == adresse_secteur_bottom[(Num_Sector+1)])
					{
					Num_Sector++;
					if (Num_Sector == 11) Num_Sector = 0;
/*%C 				erazing flag Initialisation 							*/
					Mutex_Flag_Erase = FALSE;
					}
				}
			else if (type_memoire == TOP_BOOT)
				{
				if ((UWORD32)Ptr_Flash == adresse_secteur_top[(Num_Sector+1)])
					{
					Num_Sector++;
					if (Num_Sector == 11) Num_Sector = 0;
/*%C				erazing flag Initialisation			 */
 					Mutex_Flag_Erase = FALSE;
					}
				}
			}
		}
	}
#endif
}
