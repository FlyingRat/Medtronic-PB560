/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EVENT_Read_Event.c                                     		*/
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
#ifndef _BORLAND
   #ifndef _TASKING
      #include "LH_ST10F276.h"
      #include <intrins.h>
   #else
      #include "regf276e.h"
   #endif
#endif
#include "typedef.h"
#include "io_declare.h"
#include "enum.h"
#include "Structure.h"
#include "define.h"
#include "DB_Rtc.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_Current.h"
#include "DB_Config.h"
#include "DB_PowerSupply.h"
#include "DB_EventMngt.h"
#include "Main_Data.h"
#include "Flash_Event_Data.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UBYTE DRV_EVENT_Read_Event( UWORD16 num_event
								  , e_EVENT_PARAMETERS id_event
								  , UWORD16 xhuge *Ptr_retrieval)
{
#ifndef _BORLAND
UWORD16 xhuge *adr_Read; 
UWORD16 xhuge *adr_Suspend; 
UWORD16 xhuge *Start_Last_Event; 
UWORD16 value,i;
/*%Cif index = NULL,reading the memory flash from the writing index */
if (Ptr_retrieval == NULL)
	{
/*%C Compute of the first adress of the last event	*/
	Start_Last_Event = (UWORD16 xhuge *)((UWORD32)(EVENT_FLASH_START_ADDRESS + ((UWORD32)Ptr_Flash / EVENT_Last_Event_Parameter) * EVENT_Last_Event_Parameter));
	}
/*%Cif index = NULL,reading the memory flash from the writing index memorized at the begening of retrieval  */
else
	{
/*%C Compute of the first adress of the last event	*/
	Start_Last_Event = (UWORD16 xhuge *)((UWORD32)(EVENT_FLASH_START_ADDRESS + ((UWORD32)Ptr_retrieval / EVENT_Last_Event_Parameter) * EVENT_Last_Event_Parameter));
	}

while ((BUSY_MEM2 == 0) && (Flash_State == DRV_EVENT_WRITE));
/*%C starting adress ( for a possible eraze stand by )	*/
adr_Suspend = (UWORD16 xhuge*)EVENT_FLASH_START_ADDRESS;
/*%C Si effacement alors interruption d'effacement		 ???????????????????????????????		  */
if (Flash_State == DRV_EVENT_ERASE)
	{
/*%C Interruption of erazing sequence					 */
	*Erase_Adress = 0x00B0;
	Flash_State = DRV_EVENT_FREE;
	Suspend_Erase = TRUE;
/*%C Tempo 24.8µs  waiting validation of erazing				 */
/*%C Tempo vérified with oscilloscope								 */
	for (i=0;i<165;i++) 
		{
		_nop_();
		}
	}

/*%C Reading of data in array 0  [0 : Start_Last_Event]			 */
if ((UWORD32)Start_Last_Event >= (UWORD32)((UWORD32)EVENT_FLASH_START_ADDRESS + (UWORD32)((UWORD32)num_event * (UWORD32)EVENT_Last_Event_Parameter)))
	{
/*%C if ID event is EVEN												 */
	if (id_event%2 == 0)
		{
/*%CComputing of reading adress							 */
		adr_Read = (UWORD16 xhuge *)((UWORD32)((UWORD32)Start_Last_Event
					 - ((UWORD32)num_event * (UWORD32)EVENT_Last_Event_Parameter) + id_event));
		value = *adr_Read;
		value &= 0xFF;
		}
/*%C if ID event is ODD											*/
	else
		{
/*%C Computing of reading adress										*/
		adr_Read = (UWORD16 xhuge *)((UWORD32)((UWORD32)Start_Last_Event 
					 - ((UWORD32)num_event * (UWORD32)EVENT_Last_Event_Parameter) + id_event - 1));
		value = *adr_Read;
/*%C Rigth shifft 8 bit to obtain the less significative byte	*/
		value = value >> 8;
		}
	}
/*%C reading data [Start_Last_Event : EVENT_FLASH_END_ADDRESS]	*/
else
	{
/*%C if ID event is EVEN																		*/
	if (id_event%2 == 0)
		{
/*%C Computing of reading adress															*/
		adr_Read = (UWORD16 xhuge *)((UWORD32)((UWORD32)End_Of_Event_Flash
					- ((UWORD32)num_event * (UWORD32)EVENT_Last_Event_Parameter) 
					+ (UWORD32)Start_Last_Event + id_event));
		value = *adr_Read;
		}																							
/*%C  if ID event is ODD																				*/
	else
		{
/*%C Computing of reading adress															 */
		adr_Read = (UWORD16 xhuge *)((UWORD32)((UWORD32)End_Of_Event_Flash 
					- ((UWORD32)num_event * (UWORD32)EVENT_Last_Event_Parameter) + (UWORD32)Start_Last_Event + id_event - 1));
		value = *adr_Read;
/*%C Rigth shifft 8 bit to obtain the less significative byte		*/
		value = value >> 8;
		}
	}

/*%C  if erazing is suspended start again erazing	*/
if ((Suspend_Erase == TRUE) && (Flash_State == DRV_EVENT_FREE))
	{
/*%C Running erazing sequence 												*/
	*Erase_Adress = 0x0030;
	Flash_State = DRV_EVENT_ERASE;
	Suspend_Erase = FALSE;
	}

if(adr_Read == Ptr_Flash)
{
	value = 0xFFFF;	
}
/*%C return thre value																	*/
return((UBYTE)value);
#endif
}
