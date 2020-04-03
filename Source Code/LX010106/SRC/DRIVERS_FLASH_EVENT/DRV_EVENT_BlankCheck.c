/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EVENT_BlankCheck.c                                     		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
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
#include "io_declare.h"
#include "enum.h"
#include "define.h"
#include "DB_AlarmStatus.h"
#include "DRV_EVENT_BlankCheck.h"
#include "Flash_Event_Data.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_EVENT_BlankCheck(void)
{

UWORD16 xhuge *PtrStartFlash;
UWORD16 xhuge *EndFlash;
UWORD16 xhuge *InitOfFor;
UWORD16 xhuge *EndOfFor;
UWORD16 xhuge *i;

e_BOOL NoBlank = TRUE;

/*%C Stall again the flash pointer in the event begin */
	Ptr_Flash = (UWORD16 xhuge *)((UWORD32)(((UWORD32)Ptr_Flash / EVENT_Last_Event_Parameter) * EVENT_Last_Event_Parameter));
	PtrStartFlash = (UWORD16 xhuge *) ((UWORD32)Ptr_Flash + EVENT_FLASH_START_ADDRESS);
	/*%C Flash end calcul to do a complete tour */
	if ( PtrStartFlash < (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS + EVENT_Last_Event_Parameter) )
		{
		EndFlash	= (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS + End_Of_Event_Flash);
		}
	else
		{
		EndFlash	= (UWORD16 xhuge *)(PtrStartFlash - (EVENT_Last_Event_Parameter/2)); 
		}
	/*%C End of Flash test */
	if ( PtrStartFlash >= (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS + End_Of_Event_Flash) )
		{
		PtrStartFlash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS);
		}

/*%C "for" Init calcul */
	InitOfFor = PtrStartFlash;
/*%C "for" End calcul */
	EndOfFor = PtrStartFlash + EVENT_Last_Event_Parameter/2;

/*%C Complete test of flash */	
	while(NoBlank == TRUE)
	 {
	 NoBlank = FALSE;
	 /*%C Call Watchdog in case of flash totaly empty */
	 It_watchdog();
	 for (i = InitOfFor;i <= EndOfFor; i++)
	 	{
		if (*i  != 0x0FFFF)
			{
			NoBlank = TRUE;
			/*%C Next event test */
			PtrStartFlash += EVENT_Last_Event_Parameter/2;
			/*%C Total scrutation flash test - End of test */
			if ( PtrStartFlash == EndFlash )
				{
				NoBlank = FALSE;
				}
			/*%C End of Flash test */
			if ( PtrStartFlash >= (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS + End_Of_Event_Flash) )
				{
				PtrStartFlash = (UWORD16 xhuge *)(EVENT_FLASH_START_ADDRESS);
				}
			/*%C Alarm detection */
			DB_AlarmStatusWrite(TECH_ALARM_LOOSE_FLASH_POINTER, ALARM_DETECTED);
			/*%C New "i" affectation to go out the FOR loof */ 
			i = EndOfFor + 1;
			}
		}
	/*%C Total scrutation flash test - End of test */
	if ( PtrStartFlash == EndFlash )
		{
		NoBlank = FALSE;
		}
 	 }

/*%C Calcul again the flash pointer */	
	Ptr_Flash = (UWORD16 xhuge *) ((UWORD32)PtrStartFlash - EVENT_FLASH_START_ADDRESS);
}
