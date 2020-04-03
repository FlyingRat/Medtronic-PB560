/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Transmit_Events.c                         					*/
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

#include "define.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "DB_AlarmStatus.h"
#include "DB_KeyboardEvent.h"
#include "DB_Config.h"
#include "SEC_AlarmIndication.h"
#include "Driver_USB_Data.h"
#include "DRV_USB_Transmit_Events.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_USB_Transmit_Events(UBYTE EntireEventsMemoryTransfer)
{

/******************************************************************************/
/*%C Variables 																					*/
/******************************************************************************/

	UWORD16 LoopEvent = 0 ;

/******************************************************************************/
/*%C Case One Event Transfer 																	*/
/******************************************************************************/
	if(EntireEventsMemoryTransfer == FALSE)
	{
		/*%C Store Event Identifiant */
		DataEvents [USB_ID_FRAME] = USB_EVENTS_IDENTIFIANT;
		
		/*%C Test if a event is present */
	 	if (USB_EventsBuffer		[PtrUsbNumEventsRead]
										[EVENT_STATE_ID]
										== TRUE)
		{
			for(	LoopEvent = EVENT_NB_ID ;
					LoopEvent < EVENT_Last_Event_Parameter ;
					LoopEvent ++ )
			{
				DataEvents[LoopEvent + 1] = USB_EventsBuffer
														[PtrUsbNumEventsRead]
														[LoopEvent] ;
			}
		}

		/*%C Update Event Id state */
		USB_EventsBuffer[PtrUsbNumEventsRead][EVENT_STATE_ID]  = FALSE ;

		/*%C Increment Read Pointer */
		PtrUsbNumEventsRead = PtrUsbNumEventsRead + 1 ;
																										
		/*%C Protect Usb Buffer */
   	if (PtrUsbNumEventsRead >= USB_EVENTS_BUFFER_SIZE)
	   {
   	   PtrUsbNumEventsRead = 0;
		}
	}

/******************************************************************************/
/*%C Case Entire Events Memory Transfer 													*/
/******************************************************************************/
  	else if(EntireEventsMemoryTransfer == TRUE)
  	{
		/*%C Read all events write in Events Flash */
		if (UsbEventNumber	<= 	(((EVENT_FLASH_END_ADDRESS
											- EVENT_FLASH_START_ADDRESS)
											/ EVENT_Last_Event_Parameter )
											- 1))
		{

			DataEvents[EVENT_NB_ID] = DRV_EVENT_Read_Event(
																UsbEventNumber,
																EVENT_NB_ID,
																UsbAdressFlashEvent);

		 	if (DataEvents[EVENT_NB_ID] != 0xFF)
		  	{		  
	  			for(LoopEvent = EVENT_NB_ID ;
	  			    LoopEvent < EVENT_Last_Event_Parameter;
	  			    LoopEvent ++)
			   {
					DataEvents[LoopEvent]
								=  DRV_EVENT_Read_Event(	UsbEventNumber,
															   LoopEvent,
															   UsbAdressFlashEvent);
				}

				/*%C CRC16 Compute */
				UsbComputeCRC =  CRC16_TableCompute
								(
								(UWORD16)EVENT_NB_ID,
								(UWORD16)EVENT_Last_Event_Parameter,
								DataEvents,
								UsbComputeCRC
								);
				
				UsbEventNumber++;
		  	}
			else
			{
				/*%C Frame isn't ready to be Send */
		 		FrameReadyToSend = FALSE ;
				/*%C Udpate Flash state Flag */
				EndReadFlashEventFlag = TRUE ;
				UsbEventNumber = 1 ;
			}
		}
		else
		{
			/*%C Udpate Flash state Flag */
			EndReadFlashEventFlag = TRUE ;
			UsbEventNumber = 1 ;
		}
	}
	else
	{
		/*%C No Function */
	}
}