/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505																		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_WriteEventFlash.c													*/
/*																										*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C         																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "enum.h"
#include "define.h"
#include "typedef.h"
#include "DB_Usb.h"
#include "Driver_USB_Data.h"
#include "Flash_Event_Data.h"
#include "DRV_USB_WriteEventFlash.h"

/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/

void DRV_USB_WriteEventFlash(void)
{
	static UWORD16 MutexPtrFlashEvent = TRUE;

/******************************************************************************/
/*%C Write the Flash evenements on the key												*/
/******************************************************************************/
	switch(Step_UsbTransferApply)
	{



		/*%C First step is create the monitoring file */
		case Usb_FirstStep :
		{
			DRV_USB_CreateFileName(EventsTransferType);
			MutexPtrFlashEvent = TRUE;
			/*%C Build the frame */
			DRV_USB_CreateFile(CurrentUsbKey , Tab_FileName) ;
			/*%C Next Step */
			Step_UsbTransferApply = Usb_WriteSerialNumberAtEndOfFile ;
			UsbAdressFlashEvent = DRV_EVENT_TransPtrMemory();
			break ;
		}





		/*%C Next Step is Write at the end of File */
		case Usb_WriteSerialNumberAtEndOfFile :
		{
			/*%C Updates parameters */
			DRV_USB_Transmit_SerialNumber();
			/*%C Build the frame */
			DRV_USB_WriteAtTheEndOfFile(CurrentUsbKey,
										SerialNumber ,
										End_of_e_usb_frame_serialNumber) ;
			/*%C Next Step */
			Step_UsbTransferApply = Usb_WriteAtTheEndOfFile;
			break ;
		}





		/*%C Next Step is Write at the end of File */
		case Usb_WriteAtTheEndOfFile :
		{
			if(Ptr_Num_evenement_Read == Ptr_Num_evenement_Write)
			{
			    if (MutexPtrFlashEvent == TRUE) 
			    { 
			    	MutexPtrFlashEvent = FALSE; 
			    	UsbAdressFlashEvent = DRV_EVENT_TransPtrMemory(); 
			    } 
				EndReadFlashEventFlag = FALSE ;
				/*%C Read Flash Events */
				DRV_USB_Transmit_Events(TRUE);
				/*%C Read Flash Events */
				if(EndReadFlashEventFlag == FALSE)
				{
					/*%C Build the frame */
			  		DRV_USB_WriteAtTheEndOfFile(	CurrentUsbKey,
															DataEvents,
															EVENT_Last_Event_Parameter
															) ;
				}
				else
				{
					/*%C Frame isn't ready to be Send */
					FrameReadyToSend = FALSE ;
					Step_UsbTransferApply = Usb_WriteCRC ;
				}
			}
			else
			{
				/*%C Frame isn't ready to be Send */
				FrameReadyToSend = FALSE ;
			}
			break ;
		}




		/*%C Next Step is Write the CRC at the end of File */
		case Usb_WriteCRC :
		{
			/*%C Read Flash Events */
			DataCRC[0] = (UBYTE) (UsbComputeCRC >> 8);
			DataCRC[1] = (UBYTE) (UsbComputeCRC & 0x00FF);

			/*%C Build the frame */
		  	DRV_USB_WriteAtTheEndOfFile(	CurrentUsbKey,
													DataCRC,
													USB_NB_DATA_CRC16) ;

			Step_UsbTransferApply = Usb_CloseFile ;
			break ;
	
		}




		/*%C Next Step is close the File */
		case Usb_CloseFile :
		{
			/*%C Update USB DataBase */
			DB_UsbWrite(USB_TRANSFER_APPLY_U16 , TRUE);
			DB_UsbWrite(USB_EVENTS_TRANSFER_U16 , FALSE);
			/*%C Re Init this flag to the next transfert */
			FirstRemaningTimeApproximation = TRUE ;
			/*%C Build the frame */
			DRV_USB_CloseFile(CurrentUsbKey) ;
			/*%C Re Init the step */
			Step_UsbTransferApply = Usb_FirstStep ;
			break ;
		}



		default:
		{
			/*%C Frame isn't ready to be Send */ 
			FrameReadyToSend = FALSE ;
			break ;
		}
	}
}
