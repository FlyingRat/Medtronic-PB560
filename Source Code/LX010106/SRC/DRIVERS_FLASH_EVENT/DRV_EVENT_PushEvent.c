/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EVENT_PushEvent.c                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function stores the different events in memory                    */
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
#include "Structure.h"
#include "DB_Rtc.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_Current.h"
#include "DB_Config.h"
#include "DB_PowerSupply.h"
#include "DB_EventMngt.h"
#include "Driver_Datas.h"
#include "Driver_Usb_Data.h"
#include "Flash_Event_Data.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_EVENT_PushEvent(	e_EVENT_PARAMETERS Id_Event,
                         	UBYTE value)
{

#ifndef _BORLAND

/******************************************************************************/
/*%C Push Events in Memory Event Flash Buffer */
/******************************************************************************/
   /*%C Push Events in flash events memory */
   if (Buffer_Empty == FALSE)
   {
		/*%C Write events in Flash buffer for storage */
      EventEnvironment[Ptr_Num_evenement_Write][Id_Event] = value ;
   }

	/*%C Increasing the writing index */
	if (Id_Event == EVENT_STATE_ID)
	{ 
	   if (EventEnvironment[(Ptr_Num_evenement_Write+1) 
	                                    %TAILLE_BUFFER][EVENT_STATE_ID] == FALSE)
		{
		   Ptr_Num_evenement_Write ++ ;
		   Buffer_Empty = FALSE;
		}
	   else
		{
			Buffer_Empty = TRUE;
		}
	}

	/*%C Protect Flash event Buffer */
   if (Ptr_Num_evenement_Write >= TAILLE_BUFFER)
   {
      Ptr_Num_evenement_Write = 0;
	}


/******************************************************************************/
/*%C Push Events in Usb Buffer */
/******************************************************************************/
	/*%C Push Events in Usb Buffer when Continuous recording mode is running */
	if(EventsAuthorizationFlag == TRUE)
	{
   	if(UsbBufferEmpty == FALSE)
	   {
			/*%C Write events in SPI Buffer for transfer */
	 		USB_EventsBuffer[PtrUsbNumEventsWrite][Id_Event] = value ;
	   }

		/*%C Increasing the writing index */
		if (Id_Event == EVENT_STATE_ID)
		{
		 /*%C Check Usb Buffer Empty */
		  if (USB_EventsBuffer		[(PtrUsbNumEventsWrite+1)
											%USB_EVENTS_BUFFER_SIZE]
											[EVENT_STATE_ID] == FALSE)
			{
			   PtrUsbNumEventsWrite ++ ;
			   UsbBufferEmpty = FALSE;
			}
		   else
			{
				UsbBufferEmpty = TRUE;
			}
		}

		/*%C Protect Usb Buffer */
   	if (PtrUsbNumEventsWrite >= USB_EVENTS_BUFFER_SIZE)
	   {
   	   PtrUsbNumEventsWrite = 0;
		}
	}

#endif

}