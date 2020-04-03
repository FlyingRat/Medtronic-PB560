/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505																		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_WriteContinuousRecording.c	 									*/
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
#include "Structure.h"
#include "DB_Control.h" 
#include "Timer_Data.h" 
#include "DB_Usb.h"
#include "DB_RTC.h"
#include "DB_Event.h"										  
#include "Driver_USB_Data.h"
#include "DRV_USB_WriteContinuousRecording.h"

/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/

void DRV_USB_WriteContinuousRecording(void)
{

	e_VentilState UsbVentilState = DB_ControlRead(VENTIL_STATE_U16);
	

/******************************************************************************/
/*%C Write the Continus Recording on the key */
/******************************************************************************/

	/*%C Start the transfer */
	switch(Step_UsbTransferApply)
	{


		/*%C First step is create the continious Monitoring, Trends, */
		/*%C Events	file */
		case Usb_FirstStep :
		{
			/*%C Write continuous transfer start event */
			DB_EventMngt(EVENT_USB_CONTINUOUS_TRANSFER_START);
			/*%C The next monitoring transfer will be a horodatage */
			UsbMemoVentilState = VEN_VENTIL_DISABLE;
			/*%C Update files time and date for files name */
			USB_FileHour 	= (UBYTE)DB_RTCRead(DB_RTC_HOUR_U16) ;
			USB_FileMinute 	= (UBYTE)DB_RTCRead(DB_RTC_MINUTE_U16) ;
			USB_FileSecond 	= (UBYTE)DB_RTCRead(DB_RTC_SECOND_U16) ;
			USB_FileYear 	= (UBYTE)DB_RTCRead(DB_RTC_YEAR_U16) ;
			USB_FileMonth	= (UBYTE)DB_RTCRead(DB_RTC_MONTH_U16) ;
		 	USB_FileDay		= (UBYTE)DB_RTCRead(DB_RTC_DAY_U16) ;
			/*%C Build File name */
			DRV_USB_CreateFileName(ContinuousRecordingType);
			/*%C Build the frame */
			DRV_USB_CreateFile(CurrentUsbKey , Tab_FileName) ;
			/*%C Next Step */
			Step_UsbTransferApply = Usb_WriteSerialNumberAtEndOfFile ;
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
			/*%C Start Monitoring Decounter */
			TIM_StartDecounter(TIM_USB_RECORDING_MONIT
										,TIME_RECORDING_MONIT);
			/*%C Udpate Events Authorization Flag */
			EventsAuthorizationFlag = TRUE ;
			/*%C Start recording on buffer */
			DRV_USB_Idx_Write = 0 ;
			DRV_USB_Idx_Read = 0 ;
			WriteBufferAuthorisation = TRUE ;
			/*%C Next Step */
			Step_UsbTransferApply = Usb_WriteAtTheEndOfFile;
			break ;
		}



		/*%C Next Step is Write at the end of File */
		case Usb_WriteAtTheEndOfFile :
		{
			/*%C Read Buffer and send datas */
			if(DRV_USB_Idx_Write != DRV_USB_Idx_Read)
			{
				/*%C When write pointer is lower than read pointer */
				/*%C and read pointer is nearer than 240 bytes from the end of the buffer */
				if ((DRV_USB_Idx_Write < DRV_USB_Idx_Read)
					&&(DRV_USB_CONTINUOUS_RECORD_BUFFER_SIZE - DRV_USB_Idx_Read < 240))
				{
					/*%C Write buffer content in file from read pointer to the end of the buffer */
				 	DRV_USB_WriteAtTheEndOfFile(
			  							CurrentUsbKey,
				 						&DRV_USB_Continuous_Record_Buffer[DRV_USB_Idx_Read],
						 				DRV_USB_CONTINUOUS_RECORD_BUFFER_SIZE - DRV_USB_Idx_Read );
					/*%C Set read pointer at 0 */
					DRV_USB_Idx_Read = 0;
				}
				/*%C When write pointer is lower than read pointer */
				/*%C and read pointer is not nearer than 240 bytes from the end of the buffer */
				else if	(DRV_USB_Idx_Write < DRV_USB_Idx_Read)
				{
					/*%C Write buffer content in file from read pointer to read pointer + 240 bytes */
				  	DRV_USB_WriteAtTheEndOfFile(
			  							CurrentUsbKey,
				 						&DRV_USB_Continuous_Record_Buffer[DRV_USB_Idx_Read],
						 				240 );
					/*%C Increase read pointer by 240 bytes */
					DRV_USB_Idx_Read = DRV_USB_Idx_Read + 240;
				}
				/*%C When write pointer is not lower than read pointer */
				/*%C and the difference between write and read pointer is over 240 bytes */
				else if (DRV_USB_Idx_Write - DRV_USB_Idx_Read > 240)
				{
					/*%C Write buffer content in file from read pointer to read pointer + 240 bytes */
					DRV_USB_WriteAtTheEndOfFile(
			  							CurrentUsbKey,
				 						&DRV_USB_Continuous_Record_Buffer[DRV_USB_Idx_Read],
						 				240 );
					/*%C Increase read pointer by 240 bytes */
					DRV_USB_Idx_Read = DRV_USB_Idx_Read + 240;
				}
				/*%C When write pointer is not lower than read pointer */
				/*%C and the difference between write and read pointer is not over 240 bytes */
				else 
				{
					/*%C Write buffer content in file from read pointer to write pointer */
					DRV_USB_WriteAtTheEndOfFile(
			  							CurrentUsbKey,
				 						&DRV_USB_Continuous_Record_Buffer[DRV_USB_Idx_Read],
						 				DRV_USB_Idx_Write - DRV_USB_Idx_Read );
				 	DRV_USB_Idx_Read = DRV_USB_Idx_Write;
					/*%C Increase read pointer up to write pointer */
				}
			}
			/*%C No Records */
			else
			{
				/*%C Permet d'avoir l'alarme de déconnexion pendant ce transfert*/
				/*%C si on arrache la key alors qu'il n'y a pas de transfert */
				/*%C de données vers le CYPRESS*/
				DRV_USB_AskKeyConnected(CurrentUsbKey);
			}
			break ;
		}



		default:
		{
			/*%C Frame isn't ready to be Send */ 
			FrameReadyToSend =	FALSE ;
			break ;
		}
	}
}


