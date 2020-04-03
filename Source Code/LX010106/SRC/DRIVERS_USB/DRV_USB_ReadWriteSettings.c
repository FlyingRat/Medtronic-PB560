/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505																		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_ReadWriteSettings.c 												*/
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
#include "typedef.h"
#include "Driver_USB_Data.h"
#include "DB_Usb.h"
#include "DB_Event.h"
#include "DRV_USB_ReadWriteSettings.h"


/******************************************************************************/
/*                             #DEFINE		                        				*/
/******************************************************************************/


/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/

void DRV_USB_ReadWriteSettings(void)
{

/******************************************************************************/
/*%C Variables 																					*/
/******************************************************************************/

	UWORD16 ComputeCRC = 0 ;
							

	/*%C Start the transfer */
	switch(Step_UsbTransferApply)
	{

		/*%C First step is create the settings file */
		case Usb_FirstStep :
		{
			DRV_USB_CreateFileName(SettingsType);

			/*%C Build the frame */
			DRV_USB_CreateFile(CurrentUsbKey , Tab_FileName) ;
			/*%C Next Step */
			Step_UsbTransferApply = Usb_WriteSerialNumberAndDateAtEndOfFile ;
			break ;
		}


		/*%C Next Step is Write at the end of File */
		case Usb_WriteSerialNumberAndDateAtEndOfFile :
		{
			/*%C Updates parameters */
			DRV_USB_Transmit_SerialNumberAndDate();
			/*%C Build the frame */
			DRV_USB_WriteAtTheEndOfFile(CurrentUsbKey,
										SerialNumberAndDate ,
										End_of_e_usb_frame_serialNumberAndDate) ;
			/*%C Next Step */
			Step_UsbTransferApply = Usb_WriteAtTheEndOfFile;
			break ;
		}



		/*%C Next Step is Write at the end of File */
		case Usb_WriteAtTheEndOfFile :
		{
			/*%C Updates parameters */
			DRV_USB_Transmit_Settings(FALSE);
			/*%C Build the frame */
			DRV_USB_WriteAtTheEndOfFile(CurrentUsbKey,
												DataSettings ,
												(End_Of_Table_Settings
											+ 	End_of_e_usb_frame_setting
											-	1 )) ;
			/*%C Next Step */
			Step_UsbTransferApply = Usb_CloseFile ;
			break ;
		}



		/*%C Next Step is close the File */
		case Usb_CloseFile :
		{
			/*%C Update USB DataBase */
			DB_UsbWrite(USB_COMMAND_SENT_U16 , FALSE);
			DB_UsbWrite(USB_TRANSFER_APPLY_U16 , FALSE);
			/*%C Build the frame */
			UsbWriteSettingsApply = TRUE ;
			DRV_USB_CloseFile(CurrentUsbKey) ;
			/*%C Re Init the step */
			Step_UsbTransferApply = Usb_FirstStep ;
			Step_FileSetting = FileSettingNext ;
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