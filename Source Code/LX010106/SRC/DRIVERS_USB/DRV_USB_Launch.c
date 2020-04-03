/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505																		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Launch.c 																*/
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

/*%C Mesure des temps de tâches */

/*%C Temps au repos sans clef */
/* Maximum = 39,2 µs */

/*%C Temps au repos (sans action IHM) avec clé */
/* Maximum = 42 µs */

/*%C Temps avec commande d'effacement total */
/* Maximum = 17 µs */

/*%C Temps avec commande d'écriture de réglage sur cle */
/* Maximum = 45 µs */

/*%C Temps avec commande de lecture de réglages sur cle */
/* Maximum = 75 µs */

/*%C Temps avec commande de transfert en continu */
/* Maximum = 97 µs */

/*%C Temps avec commande de monitorage detaillé */
/* Maximum = 434 µs */


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#ifndef _TASKING
	#include "LH_ST10F276.h"
	#include <intrins.h>
#else	    
 		#include "regf276e.h"
#endif 	
#include "io_declare.h"
#include "enum.h"
#include "define.h"
#include "typedef.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "Flash_Monit_data.h"
#include "DB_Config.h"
#include "DRV_NAND_ReadID.h"
#include "DB_Usb.h"
#include "DB_Event.h"										  
	#define DECLARATION_DRIVER_USB_DATA_H
#include "Driver_USB_Data.h"
#include "DRV_USB_Launch.h"

static void USB_BipRequest(e_VALIDATION_BIP bip);
static void USB_WriteEvent(UWORD16 value);
/******************************************************************************/
/*                             #DEFINE		                        				*/
/******************************************************************************/


/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/

void DRV_USB_Launch(void)
{

/******************************************************************************/
/*%C Variables 																					*/
/******************************************************************************/
	
	UWORD16 UsbCommandSent 		= DB_UsbRead(USB_COMMAND_SENT_U16);
	UWORD16 UsbMsnbOneDetected = DB_UsbRead(USB_MSNB_ONE_DETECTED_U16);
	UWORD16 UsbMsnbTwoDetected = DB_UsbRead(USB_MSNB_TWO_DETECTED_U16);
	UWORD16 UsbNewKeyDetected 	= DB_UsbRead(USB_NEW_KEY_CONNECTED_U16);
	UWORD16 UsbEraseKey		 	= DB_UsbRead(USB_ERASE_KEY_U16);
	UWORD16 UsbTransferApply 	= DB_UsbRead(USB_TRANSFER_APPLY_U16);
	UWORD16 UsbStopCommandSent = DB_UsbRead(USB_STOP_COMMAND_SENT_U16);


	UWORD16 UsbMsbFreeSpaceKeyOne
										= DB_UsbRead(USB_MSB_FREE_SPACE_KEY_ONE);
	UWORD16 UsbLsbFreeSpaceKeyOne
										= DB_UsbRead(USB_LSB_FREE_SPACE_KEY_ONE);
	UWORD16 UsbMsbFreeSpaceKeyTwo
										= DB_UsbRead(USB_MSB_FREE_SPACE_KEY_TWO);
	UWORD16 UsbLsbFreeSpaceKeyTwo
										= DB_UsbRead(USB_LSB_FREE_SPACE_KEY_TWO);

	UWORD16 UsbMonitorTransferSelect
										= DB_UsbRead(USB_MONITOR_TRANSFER_SELECT_U16);
	UWORD16 UsbMonitorTransfert 
										= DB_UsbRead(USB_MONITOR_TRANSFER_U16);			


	UWORD16 UsbTrendTransferSelect 
										= DB_UsbRead(USB_TREND_TRANSFER_SELECT_U16);
	UWORD16 UsbTrendTransfert 
										= DB_UsbRead(USB_TREND_TRANSFER_U16);


	UWORD16 UsbEventsTransfer 
										= DB_UsbRead(USB_EVENTS_TRANSFER_U16);


	UWORD16 UsbContinuousRecording 
										= DB_UsbRead(USB_CONTINUOUS_RECORDING_U16);


	UWORD16 UsbKey1DetectedAfterpowerOn 
						=DB_UsbRead(USB_KEY1_DETECTED_AFTER_POWER_ON_U16);

	UWORD16 UsbKey2DetectedAfterpowerOn 
						=DB_UsbRead(USB_KEY2_DETECTED_AFTER_POWER_ON_U16);
	
	UWORD16 AdjustControlR = DB_CurrentRead(ADJUST_CONTROL_R_U16);
	UWORD16 AdjustBackupR = DB_CurrentRead(ADJUST_BACKUP_R_U16);
	UWORD16 Currentmode = DB_ControlRead(CURRENT_MODE_U16);
	UWORD16 ControlR = 0;
	
	UWORD32 CurrentMsNumberFreeSpace = 0 ;
	UWORD32 TamponContinuousBytesWritten = 0 ;
	UWORD32 UsbTransfertRemainingTime = 0 ;
	UWORD32 NbMonitoringBytesToWrite = 0 ;
	UWORD32 NbTrensdsBytesToWrite = 0 ;	

	UWORD16 TimerState = 0 ; 
	UWORD16 SizeFrameMinute = 0 ;

	UWORD16 idx = 0;

	SWORD32 MaxOfContinuousFreeSpace = 64454400;

	static UWORD16 KeyNumber = 0 ; 
	static UWORD16 FirstRun = TRUE ;
	static UWORD16 PreviousNoKeyConnected = TRUE ;
	static UWORD16 ContinuousTransferEndDateFrameAndEventSent = FALSE ;
	static UWORD16 UsbContinuousRecordingMemo = FALSE;


/*%C Flag to detect any USB action */	
	if ( (UsbCommandSent == TRUE) 
	  || (UsbNewKeyDetected == TRUE) )
	{
		USB_CommandInProgress = TRUE;
	}

/******************************************************************************/
/*%C On First run or when a reset bridge is detected,									*/
/*%C Initialize USB data, RAZ interrupt flag and initialize PECC register 		*/
/*%C Init the SPI Bus and start timer to wait bridge ready							*/
/******************************************************************************/
 	if(FirstRun == TRUE)
	{
		/*%C Lock the frist Run Flag															*/
		FirstRun = FALSE ;
				  
		/*%C Update USB command IHM  */
		DB_UsbWrite(USB_COMMAND_SENT_U16 , FALSE);
		DB_UsbWrite(USB_STOP_COMMAND_SENT_U16 , FALSE);
		DB_UsbWrite(USB_TRANSFER_APPLY_U16 , FALSE);
		DB_UsbWrite(USB_ERASE_KEY_U16 , FALSE);
		DB_UsbWrite(USB_CONTINUOUS_RECORDING_U16 , FALSE);
		DB_UsbWrite(USB_MONITOR_TRANSFER_SELECT_U16 , FALSE);
		DB_UsbWrite(USB_MONITOR_TRANSFER_U16 , FALSE);
		DB_UsbWrite(USB_TREND_TRANSFER_SELECT_U16 , FALSE);
		DB_UsbWrite(USB_TREND_TRANSFER_U16 , FALSE);
		DB_UsbWrite(USB_EVENTS_TRANSFER_U16 , FALSE);
		DB_UsbWrite(USB_KEY1_DETECTED_AFTER_POWER_ON_U16,FALSE);
		DB_UsbWrite(USB_KEY2_DETECTED_AFTER_POWER_ON_U16,FALSE);
		
		/*%C Udpate Events Authorization Flag */
		EventsAuthorizationFlag = FALSE ;

		/*%C Re Init the step  */
		Step_UsbTransferApply = Usb_FirstStep ;
		Step_FileSetting = FileSettingNext ;				

		/*%C Compute Flash Monit Size */
		NandFlashMonitoringCapacity 	= (	
									((UWORD32)DRV_NAND_First_Partition_Block_End 
								-  (UWORD32)DRV_NAND_First_Partition_Block_Start)
								*	MONITORING_FLASH_PAGE_SIZE
								*	NAND_FLASH_PAGE_NUMBER) ;

		NandFlashTrendCapacity 		= (
									((UWORD32)DRV_NAND_Second_Partition_Block_End 
								-  (UWORD32)DRV_NAND_Second_Partition_Block_Start)
								*	TREND_FLASH_PAGE_SIZE
								*	NAND_FLASH_PAGE_NUMBER) ;

		/*%C SPI Bus and bridge Initialization */				
		DRV_USB_Init();

		/*%C Start Timer to wait busy hight */
		TIM_StartDecounter(WAIT_USB_BUSY,TIME_WAIT_USB_BUSY_AFTER_RESET);
		/*%C Start Timer to check a busy too long */
		TIM_StartMinuteDecounter(TimerUsbCommandTooLong,
	                               TIME_WAIT_USB_BUSY_LONG_COMMAND,
	                               FALSE);
	}	

	/*%C Check Busy Hight	*/
	TimerState = DRV_USB_WaitBusy(1);

	FrameReadyToSend = TRUE ;


   /*%C Write in continuous recording buffer */
	if ((UsbContinuousRecording == TRUE)
		&& (UsbCommandSent == TRUE) 
		&& (WriteBufferAuthorisation == TRUE))
	{ 
			DRV_USB_WriteInContinuousRecordBuffer();
	}

/******************************************************************************/
/*%C When bridge is ready 																		*/
/******************************************************************************/
	if (	(TIM_ReadDecounterValue(WAIT_USB_BUSY) == 0)
	  	&& (TimerState == 0))
	{

/******************************************************************************/
/*%C Upgrade Current Usb Key number 														*/
/******************************************************************************/
		if(	(UsbMsnbOneDetected == TRUE)
			&&	(UsbMsnbTwoDetected == FALSE))
		{
			CurrentUsbKey = KEY_1 ;
		}
		else if(		(UsbMsnbTwoDetected == TRUE)
					&&	(UsbMsnbOneDetected == FALSE))
		{
			CurrentUsbKey = KEY_2 ;
		}
		else
		{
			/*%C No Function */
		}

/******************************************************************************/
/*%C When IHM Send Command																		*/
/******************************************************************************/
		if(UsbCommandSent == TRUE)
		{
			/*%C Update Error Detected Flag */ 
			DisplayErrorCodeFlag = TRUE ;
			UsbErrorDetectedFlag = FALSE ;

			/*%C Compute the free space with datas already write */
			if(CurrentUsbKey == KEY_1)
			{
				CurrentMsNumberFreeSpace = 
					((((UWORD32)(UsbMsbFreeSpaceKeyOne ) << 16 ) & 0xFFFF0000)
				|	((UWORD32)(UsbLsbFreeSpaceKeyOne & 0x0000FFFF))) ;
			}
			if(CurrentUsbKey == KEY_2)
			{
				CurrentMsNumberFreeSpace = 
					((((UWORD32)(UsbMsbFreeSpaceKeyTwo ) << 16 ) & 0xFFFF0000)
				|	((UWORD32)(UsbLsbFreeSpaceKeyTwo & 0x0000FFFF))) ;
			}
			else
			{
				/*No Function */
			}

			CurrentMsNumberFreeSpace = CurrentMsNumberFreeSpace - UsbNbBytesWriteOnKey ;
			MaxOfContinuousFreeSpace = MaxOfContinuousFreeSpace - UsbNbBytesWriteOnKey ;
			if (MaxOfContinuousFreeSpace < 0)
			{
				MaxOfContinuousFreeSpace = 0;
			}

/******************************************************************************/
/*%C Case Key Full detected when a continuous transfer is asked						*/
/******************************************************************************/
			/*%C If free Space is less than 1Mo */
			/*%C and the command is a Continus Recording */
			/*%C Stop the transfer and close the file */
			if(	( (CurrentMsNumberFreeSpace <= 1048576)
			   || (MaxOfContinuousFreeSpace <= 0) )
			 && ( (UsbContinuousRecording == TRUE)
			   || (UsbContinuousRecordingMemo == TRUE) ) )
			{
				/*%C Don't Display the error code  */
				UsbErrorDetectedFlag = TRUE ;

 				if (USB_FileOpened == TRUE)
				{
					UsbContinuousRecordingMemo = TRUE;

					/*%C We avoid any more writtings in continuous buffer */
					DB_UsbWrite(USB_CONTINUOUS_RECORDING_U16 , FALSE);

					/*%C Continuous transfer end date frame and event are sent to buffer */
					if (ContinuousTransferEndDateFrameAndEventSent == FALSE)
					{
						ContinuousTransferEndDateFrameAndEventSent = TRUE;

						/*%C Write EVENT_USB_CONTINUOUS_TRANSFER_STOP event */
						USB_WriteEvent (EVENT_USB_CONTINUOUS_TRANSFER_STOP);

						/*%C Read Monitoring Datas (Horodatage)*/
						DRV_USB_Transmit_Monitoring(DETAILLED_HORODATAGE_TYPE);
			
						/*%C Write to the buffer */
						for (idx = 0;idx<(USB_End_Of_Continuous_Frame + End_Of_Table_Detailled_Monitoring - 1);idx++)  
						{
							DRV_USB_Continuous_Record_Buffer[DRV_USB_Idx_Write]=DataMonitoring[idx];
							DRV_USB_Idx_Write ++ ;
							DRV_USB_Idx_Write = (UWORD16)(DRV_USB_Idx_Write % DRV_USB_CONTINUOUS_RECORD_BUFFER_SIZE);
						}

						/*%C Read Event Datas */
						DRV_USB_Transmit_Events(FALSE);

						/*%C Write to the buffer */
						for (idx = 0;idx<(USB_End_Of_Continuous_Frame + EVENT_Last_Event_Parameter - 1);idx++)  
						{
							DRV_USB_Continuous_Record_Buffer[DRV_USB_Idx_Write]=DataEvents[idx];
							DRV_USB_Idx_Write ++ ;
							DRV_USB_Idx_Write = (UWORD16)(DRV_USB_Idx_Write % DRV_USB_CONTINUOUS_RECORD_BUFFER_SIZE);
						}
					}

					/*%C Flush buffer */
					if (DRV_USB_Idx_Write != DRV_USB_Idx_Read)
					{
						DRV_USB_WriteContinuousRecording();
					}
					/*%C When buffer is empty we close the file */
					else
					{
						ContinuousTransferEndDateFrameAndEventSent = FALSE;
						UsbContinuousRecordingMemo = FALSE;

						/*%C  Start Events transfer */
						DB_UsbWrite(USB_EVENTS_TRANSFER_U16 , TRUE);
				
						/*%C Udpate Events Authorization Flag */
						EventsAuthorizationFlag = FALSE ;

						if (CurrentMsNumberFreeSpace <= 1048576)
						{
							/*%C Write Event usb KEY FULL in flash*/
							USB_WriteEvent(EVENT_USB_KEY_FULL);
						}
		
						/*%C Close the file  */
						DRV_USB_CloseFile(CurrentUsbKey) ;
		
						/*%C Re Init the step  */
						Step_UsbTransferApply = Usb_FirstStep ;
						Step_FileSetting = FileSettingNext ;
						WriteBufferAuthorisation = FALSE ;

						/*%C Re Init this flag to the next transfert */
						FirstRemaningTimeApproximation = TRUE ;

						UsbFlashTrasnferRunning = USB_NAND_TRANSFER_IDLE;
					}
				}
				else 
				{
					DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_NOT_ENOUGH_KEY_SPACE);
					DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);
				
					/*%C Re Init the step  */
					Step_UsbTransferApply = Usb_FirstStep ;
					Step_FileSetting = FileSettingNext ;
					WriteBufferAuthorisation = FALSE ;

					DB_UsbWrite(USB_COMMAND_SENT_U16 , FALSE);
					DB_UsbWrite(USB_CONTINUOUS_RECORDING_U16 , FALSE);
				}

			}

/******************************************************************************/
/*%C Case user Stop action during a transfer, close the file				*/
/******************************************************************************/
			else if ( (UsbStopCommandSent == TRUE)
			  && (USB_FileOpened == TRUE)
			  && (UsbEventsTransfer==FALSE)
			  && (UsbTransferApply == FALSE))
				{
				    /*%C When continuous recording is stopped, we have to do some */
					/*%C actions before	closing the file */
					if ( (UsbContinuousRecording == TRUE)
					  || (UsbContinuousRecordingMemo == TRUE) )
					{
						UsbContinuousRecordingMemo = TRUE;
	
						/*%C We avoid any more writtings in continuous buffer */
						DB_UsbWrite(USB_CONTINUOUS_RECORDING_U16 , FALSE);
	
						/*%C Continuous transfer end date frame and event are sent to buffer */
						if (ContinuousTransferEndDateFrameAndEventSent == FALSE)
						{
							ContinuousTransferEndDateFrameAndEventSent = TRUE;
						
							/*%C Write EVENT_USB_CONTINUOUS_TRANSFER_STOP event */
							USB_WriteEvent (EVENT_USB_CONTINUOUS_TRANSFER_STOP);
	
							/*%C Read Monitoring Datas (Horodatage)*/
							DRV_USB_Transmit_Monitoring(DETAILLED_HORODATAGE_TYPE);
				
							/*%C Write to the buffer */
							for (idx = 0;idx<(USB_End_Of_Continuous_Frame + End_Of_Table_Detailled_Monitoring - 1);idx++)  
							{
								DRV_USB_Continuous_Record_Buffer[DRV_USB_Idx_Write]=DataMonitoring[idx];
								DRV_USB_Idx_Write ++ ;
								DRV_USB_Idx_Write = (UWORD16)(DRV_USB_Idx_Write % DRV_USB_CONTINUOUS_RECORD_BUFFER_SIZE);
							}
	
							/*%C Read Event Datas */
							DRV_USB_Transmit_Events(FALSE);
	
							/*%C Write to the buffer */
							for (idx = 0;idx<(USB_End_Of_Continuous_Frame + EVENT_Last_Event_Parameter - 1);idx++)  
							{
								DRV_USB_Continuous_Record_Buffer[DRV_USB_Idx_Write]=DataEvents[idx];
								DRV_USB_Idx_Write ++ ;
								DRV_USB_Idx_Write = (UWORD16)(DRV_USB_Idx_Write % DRV_USB_CONTINUOUS_RECORD_BUFFER_SIZE);
							}
						}
	
						/*%C Flush buffer */
						if (DRV_USB_Idx_Write != DRV_USB_Idx_Read)
						{
							DRV_USB_WriteContinuousRecording();
						}
						/*%C When buffer is empty we close the file */
						else
						{
							ContinuousTransferEndDateFrameAndEventSent = FALSE;
							UsbContinuousRecordingMemo = FALSE;
	
							/*%C  Start Events transfer */
							DB_UsbWrite(USB_COMMAND_SENT_U16 , TRUE);
							DB_UsbWrite(USB_EVENTS_TRANSFER_U16 , TRUE);
							DB_UsbWrite(USB_STOP_COMMAND_SENT_U16 , FALSE);
							DB_UsbWrite(USB_TRANSFER_APPLY_U16 , FALSE);
							DB_UsbWrite(USB_ERASE_KEY_U16 , FALSE);
							DB_UsbWrite(USB_MONITOR_TRANSFER_SELECT_U16 , FALSE);
							DB_UsbWrite(USB_MONITOR_TRANSFER_U16 , FALSE);
							DB_UsbWrite(USB_TREND_TRANSFER_SELECT_U16 , FALSE);
							DB_UsbWrite(USB_TREND_TRANSFER_U16 , FALSE);
	
							/*%C Udpate Events Authorization Flag */
							EventsAuthorizationFlag = FALSE ;
			
							/*%C Close the file  */
							DRV_USB_CloseFile(CurrentUsbKey) ;
			
							/*%C Re Init the step  */
							Step_UsbTransferApply = Usb_FirstStep ;
							Step_FileSetting = FileSettingNext ;
							WriteBufferAuthorisation = FALSE ;
							/*%C Re Init this flag to the next transfert */
							FirstRemaningTimeApproximation = TRUE ;
						}
					}
					else
					{
						/*%C Update USB DataBase  */
						DB_UsbWrite(USB_COMMAND_SENT_U16 , FALSE);
						DB_UsbWrite(USB_STOP_COMMAND_SENT_U16 , FALSE);
					DB_UsbWrite(USB_TRANSFER_APPLY_U16 , FALSE);
						DB_UsbWrite(USB_ERASE_KEY_U16 , FALSE);
						DB_UsbWrite(USB_CONTINUOUS_RECORDING_U16 , FALSE);
						DB_UsbWrite(USB_MONITOR_TRANSFER_SELECT_U16 , FALSE);
						DB_UsbWrite(USB_MONITOR_TRANSFER_U16 , FALSE);
						DB_UsbWrite(USB_TREND_TRANSFER_SELECT_U16 , FALSE);
						DB_UsbWrite(USB_TREND_TRANSFER_U16 , FALSE);
					DB_UsbWrite(USB_EVENTS_TRANSFER_U16 , FALSE);
					
				 	if  (UsbEventsTransfer == TRUE)
					{
						/*%C  Start Events and Settings transfer */
						DB_UsbWrite(USB_COMMAND_SENT_U16 , TRUE);
						DB_UsbWrite(USB_TRANSFER_APPLY_U16 , TRUE);
					}
					else
					{
					UsbWriteSettingsApply = TRUE ;
					}
						
						/*%C  Reset event counter for event transfer */
						UsbEventNumber = 1 ;			
				
						/*%C When Flash Transfer is running Stop request */
						if(	(UsbFlashTrasnferRunning == USB_NAND_MONIT_TRANSFER_RUNNING)
							||	(UsbFlashTrasnferRunning == USB_NAND_TREND_TRANSFER_RUNNING))
						{
							UsbFlashTrasnferRunning = USB_NAND_TRANSFER_IDLE;
						
							DRV_MONIT_Read_Request = ENDED ;
							DRV_TREND_Read_Request = ENDED ;
						
							DRV_TREND_New_Data = FALSE;
							DRV_MONIT_New_Data = FALSE;
						}		
		
						/*%C Udpate Events Authorization Flag */
						EventsAuthorizationFlag = FALSE ;
		
						/*%C Close the file  */
						DRV_USB_CloseFile(CurrentUsbKey) ;
		
						/*%C Re Init the step  */
						Step_UsbTransferApply = Usb_FirstStep ;
						Step_FileSetting = FileSettingNext ;
						WriteBufferAuthorisation = FALSE ;
						/*%C Re Init this flag to the next transfert */
						FirstRemaningTimeApproximation = TRUE ;
					}
			}

/******************************************************************************/
/*%C When erase key is asked 																	*/
/******************************************************************************/
		 	else if(UsbEraseKey == TRUE)
			{
				/*%C Build the erase Key frame */
				DRV_USB_EntireEraseMemoryStick(CurrentUsbKey);
 			
 				/*%C Update USB DataBase */
				DB_UsbWrite(USB_COMMAND_SENT_U16 , FALSE);
				DB_UsbWrite(USB_ERASE_KEY_U16 , FALSE);
				
				/*%C Indicate the remaining time */
				DB_UsbWrite(USB_PROGRESS_MINUTES_U16, 0x01);
				DB_UsbWrite(USB_PROGRESS_HOURS_U16, 0x00);
			}

/******************************************************************************/
/*%C When transfer setting is asked 														*/
/******************************************************************************/
			else if (UsbTransferApply == TRUE)
			{
				/*%C Transfer on key, check the frre space */
				if (CurrentMsNumberFreeSpace < 200000)
				{
					DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_NOT_ENOUGH_KEY_SPACE);
					DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);

					/*%C Write Event usb KEY FULL in flash*/
					USB_WriteEvent(EVENT_USB_KEY_FULL);

					/*%C Update USB DataBase  */
					DB_UsbWrite(USB_COMMAND_SENT_U16 , FALSE);
					DB_UsbWrite(USB_TRANSFER_APPLY_U16 , FALSE);
						
					/*%C Frame isn't ready to be Send */ 
					FrameReadyToSend = FALSE ;
				}
				else
				{
					/*%C Read or Write Settings */
					DRV_USB_ReadWriteSettings();
	
					/*%C Indicate the remaining time */
					DB_UsbWrite(USB_PROGRESS_MINUTES_U16, 0x01);
					DB_UsbWrite(USB_PROGRESS_HOURS_U16, 0x00);
				}
			}

/******************************************************************************/
/*%C When Continuous records, write the Continus Recording on the key 			*/
/******************************************************************************/
			else if (UsbContinuousRecording == TRUE)
			{	
				/*%C Records Monitoring, Trends and Events in continuous */
				DRV_USB_WriteContinuousRecording();

				TamponContinuousBytesWritten = CurrentMsNumberFreeSpace - 1048576;

				if (TamponContinuousBytesWritten > (UWORD32)MaxOfContinuousFreeSpace)
				{
					TamponContinuousBytesWritten = MaxOfContinuousFreeSpace;
				}
				else
				{
				 	/*%C No function*/
				}
				if (Currentmode == CPAP)
				{
					ControlR = 60;
				}
				else if (AdjustControlR == 0xAAAA)
				{
					ControlR = AdjustBackupR;
				}
				else
				{
					ControlR = AdjustControlR;
				}

				/*%C Monitoring Size and trends Size to evaluate remaining time */
				SizeFrameMinute
								=	(
									(60 * 
									((End_Of_Table_Detailled_Monitoring
										 +	USB_End_Of_Continuous_Frame -	1)
										  * 	DETAILLED_MONITORING_PERIOD))
									+	
									((End_Of_Table_Trends
										 +	USB_End_Of_Continuous_Frame -	1)
										 	*	ControlR));

				/*%C Transfert Time remaning */
				UsbTransfertRemainingTime = 
													(	TamponContinuousBytesWritten 
													/	SizeFrameMinute) ;
				
				/*%C Saturation Time 															*/
				if(UsbTransfertRemainingTime < 1) 
				{
					UsbTransfertRemainingTime = 1;
				}
				else
				{
				 	/*%C No function*/
				}

				/*%C Indicate the remaining time */
				DB_UsbWrite	(USB_PROGRESS_HOURS_U16,
								(UWORD16)(UsbTransfertRemainingTime / 60));
				DB_UsbWrite	(USB_PROGRESS_MINUTES_U16, 
								(UWORD16)(UsbTransfertRemainingTime) % 60 ) ;
		   	}

/******************************************************************************/
/*%C When write Flash monitoring, write the Flash monitoring on the key 		*/
/******************************************************************************/
			else if (UsbMonitorTransferSelect == TRUE)
			{
				if(FirstRemaningTimeApproximation == TRUE)
				{
					FirstRemaningTimeApproximation = FALSE ;
					/*%C Extract Monitoring Time transfert to bytes */
					/*%C Monitoring frame every 40ms */
					/*%C So 25 frame/s - 1500 frame/min - 90000 frame/h */
					/*%C 9 bytes represente the monitoring frame */
					/*%C 810000 bytes/h */
					NbBytesMonitoringFlashMonitToWrite = (UWORD32)UsbMonitorTransfert * 810000 ;
					/*%C Secure maximum data to transfer */
					if(NbBytesMonitoringFlashMonitToWrite > NandFlashMonitoringCapacity)
					{
						NbBytesMonitoringFlashMonitToWrite = NandFlashMonitoringCapacity ;
					}
					/*%C Check if the key have enough free space */
					/*%C to transfer the Monitoring */
					if (CurrentMsNumberFreeSpace < NbBytesMonitoringFlashMonitToWrite + 1048576)
					{
						FirstRemaningTimeApproximation = TRUE ;

						DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_NOT_ENOUGH_KEY_SPACE);
						DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);

						/*%C Write Event usb KEY FULL in flash*/
						USB_WriteEvent(EVENT_USB_KEY_FULL);

						/*%C Update USB DataBase  */
						DB_UsbWrite(USB_COMMAND_SENT_U16 , FALSE);
						DB_UsbWrite(USB_MONITOR_TRANSFER_SELECT_U16 , FALSE);
						DB_UsbWrite(USB_MONITOR_TRANSFER_U16 , FALSE);
						
						/*%C Frame isn't ready to be Send */ 
						FrameReadyToSend = FALSE ;
					}
					else
					{
						/*%C Records Flash Monitoring */
						DRV_USB_WriteMonitoringFlashMonit();
						/*%C Soustract bytes transfered to bytes to transfer */
						NbMonitoringBytesToWrite 	= 	NbBytesMonitoringFlashMonitToWrite
														-	NbBytesUsbWrittenFlashMonit ;
						/*%C Theorical transfer is eight time 240 bytes, and one time 128 bytes every 45ms */
						/*%C This transfer is truncated by the write flash time (every 2.275s) and by the spi usb bus wait */ 
						/*%C So a 10% marge is troncated */
						/*%C So 2400000 bytes every minutes */
						NbMonitoringBytesToWrite = NbMonitoringBytesToWrite / 2400000 ;
						/*%C Troncated by 1 increment */
						NbMonitoringBytesToWrite = NbMonitoringBytesToWrite + 1 ;
	
						/*%C Indicate the remaining time */
						DB_UsbWrite(USB_PROGRESS_MINUTES_U16, 
											(UWORD16)(NbMonitoringBytesToWrite));
						DB_UsbWrite(USB_PROGRESS_HOURS_U16 , 0x00);
					}
				}
				else
				{
				 	/*%C Records Flash Monitoring */
					DRV_USB_WriteMonitoringFlashMonit();
					/*%C Soustract bytes transfered to bytes to transfer */
					NbMonitoringBytesToWrite 	= 	NbBytesMonitoringFlashMonitToWrite
													-	NbBytesUsbWrittenFlashMonit ;
					/*%C Theorical transfer is eight time 240 bytes, and one time 128 bytes every 45ms */
					/*%C This transfer is truncated by the write flash time (every 2.275s) and by the spi usb bus wait */ 
					/*%C So a 10% marge is troncated */
					/*%C So 2400000 bytes every minutes */
					NbMonitoringBytesToWrite = NbMonitoringBytesToWrite / 2400000 ;
					/*%C Troncated by 1 increment */
					NbMonitoringBytesToWrite = NbMonitoringBytesToWrite + 1 ;

					/*%C Indicate the remaining time */
					DB_UsbWrite(USB_PROGRESS_MINUTES_U16, 
										(UWORD16)(NbMonitoringBytesToWrite));
					DB_UsbWrite(USB_PROGRESS_HOURS_U16 , 0x00);
				}			
			}

/******************************************************************************/
/*%C When write Flash Trends, write the Flash trends on the key 					*/
/*										and after write the Falsh events on the key 		*/
/******************************************************************************/
			else if (UsbTrendTransferSelect == TRUE)
			{
				if(FirstRemaningTimeApproximation == TRUE)
				{
					FirstRemaningTimeApproximation = FALSE ;

					if (UsbTrendTransfert == 3)
					{
						/*%C Extract Trends duration transfert */
						NbBytesMonitoringFlashTrendToWrite = (3312000);
					}
					else if	(UsbTrendTransfert == 6)
					{
						/*%C Extract Trends duration transfert */
						NbBytesMonitoringFlashTrendToWrite = (6624000);
					}
					else if	(UsbTrendTransfert == 9)
					{
						/*%C Extract Trends duration transfert */
						NbBytesMonitoringFlashTrendToWrite = (9936000);
					}
					else if	(UsbTrendTransfert == 12)
					{
						/*%C Extract Trends duration transfert */
						NbBytesMonitoringFlashTrendToWrite = (13176000);
					}
					else
					{
					 /*%C error code */
					}
						
					/*%C Secure maximum data to transfer */
					if(NbBytesMonitoringFlashTrendToWrite > NandFlashTrendCapacity)
					{
						NbBytesMonitoringFlashTrendToWrite = NandFlashTrendCapacity ;
					}
					/*%C Check if the key have enough free space to transfer */
					/*%C Trends and Events (1 048 576 octects)  */
					if (CurrentMsNumberFreeSpace < NbBytesMonitoringFlashTrendToWrite 
																+ 1048576)
					{
						FirstRemaningTimeApproximation = TRUE ;
						DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_NOT_ENOUGH_KEY_SPACE);
						DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);

						/*%C Write Event usb KEY FULL in flash*/
						USB_WriteEvent(EVENT_USB_KEY_FULL);

						/*%C Update USB DataBase  */
						DB_UsbWrite(USB_COMMAND_SENT_U16 , FALSE);
						DB_UsbWrite(USB_TREND_TRANSFER_SELECT_U16 , FALSE);
						DB_UsbWrite(USB_TREND_TRANSFER_U16 , FALSE);

						/*%C Frame isn't ready to be Send */ 
						FrameReadyToSend = FALSE ;
					}
					else
					{
						/*%C Records Flash Trends and Flash Events */
						DRV_USB_WriteTrendsFlashMonit();
						/*%C Soustract bytes transfered to bytes to transfer */
						NbTrensdsBytesToWrite 	= 	NbBytesMonitoringFlashTrendToWrite
														-	NbBytesUsbWrittenFlashMonit ;
						/*%C Theorical transfer is eight time 240 bytes, and one time 128 bytes every 45ms */
						/*%C This transfer is truncated by the write flash time (every 20.48s) and by the spi usb bus wait */ 
						/*%C So a 5% marge is troncated */
						/*%C So 2568000 bytes every minutes */
						NbTrensdsBytesToWrite = NbTrensdsBytesToWrite / 2568000 ;
						/*%C Troncated by 1 increment */
						NbTrensdsBytesToWrite = NbTrensdsBytesToWrite + 1 ;
		
						DB_UsbWrite(USB_PROGRESS_MINUTES_U16,
											 (UWORD16)(NbTrensdsBytesToWrite));
						DB_UsbWrite(USB_PROGRESS_HOURS_U16 , 0);
					}
				}
				else
				{
					/*%C Records Flash Trends and Flash Events */
					DRV_USB_WriteTrendsFlashMonit();
					/*%C Soustract bytes transfered to bytes to transfer */
					NbTrensdsBytesToWrite 	= 	NbBytesMonitoringFlashTrendToWrite
													-	NbBytesUsbWrittenFlashMonit ;
					/*%C Theorical transfer is eight time 240 bytes, and one time 128 bytes every 45ms */
					/*%C This transfer is truncated by the write flash time (every 20.48s) and by the spi usb bus wait */ 
					/*%C So a 5% marge is troncated */
					/*%C So 2568000 bytes every minutes */
					NbTrensdsBytesToWrite = NbTrensdsBytesToWrite / 2568000 ;
					/*%C Troncated by 1 increment */
					NbTrensdsBytesToWrite = NbTrensdsBytesToWrite + 1 ;
	
					DB_UsbWrite(USB_PROGRESS_MINUTES_U16,
										 (UWORD16)(NbTrensdsBytesToWrite));
					DB_UsbWrite(USB_PROGRESS_HOURS_U16 , 0);
				}
			}

/******************************************************************************/
/*%C When write Flash evenements, Write the Flash evenements on the key 		*/
/******************************************************************************/
			else if (UsbEventsTransfer == TRUE)
			{
				if(FirstRemaningTimeApproximation == TRUE)
				{
					FirstRemaningTimeApproximation = FALSE ;
					/*%C Check if the key have enough free space to transfer Events*/
					if (CurrentMsNumberFreeSpace < 600000)
					{
						FirstRemaningTimeApproximation = TRUE ;
						DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_NOT_ENOUGH_KEY_SPACE);
						DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);
	
						/*%C Write Event usb KEY FULL in flash*/
						USB_WriteEvent(EVENT_USB_KEY_FULL);
	
						/*%C Update USB DataBase  */
						DB_UsbWrite(USB_COMMAND_SENT_U16 , FALSE);
						DB_UsbWrite(USB_EVENTS_TRANSFER_U16 , FALSE);
							
						/*%C Frame isn't ready to be Send */ 
						FrameReadyToSend = FALSE ;
					}
					else
					{
						/*%C Records Flash Events */
						DRV_USB_WriteEventFlash();
		
						/*%C Transfert Entire Memory */
						/*%C 6000 events in flash and we transfer 1 event every 5ms => 30s*/
						DB_UsbWrite(USB_PROGRESS_MINUTES_U16, 0x01);
						DB_UsbWrite(USB_PROGRESS_HOURS_U16, 0x00);
					}
				}
				else
				{
					/*%C Records Flash Events */
					DRV_USB_WriteEventFlash();
		
					/*%C Transfert Entire Memory */
					/*%C 6000 events in flash and we transfer 1 event every 5ms => 30s*/
					DB_UsbWrite(USB_PROGRESS_MINUTES_U16, 0x01);
					DB_UsbWrite(USB_PROGRESS_HOURS_U16, 0x00);
				}
			}

/******************************************************************************/
/*%C No other IHM action 																		*/
/******************************************************************************/
			/*If we have more than 1Mo on the key */
			else if (UsbCommandSent == TRUE)
			{
				/*%C Frame isn't ready to be Send */
				FrameReadyToSend = FALSE ;
			}
			/*If we have less than 1Mo on the key */
			else
			{
			 	/*%C No Action */
			}
		}



/******************************************************************************/
/*%C When no any IHM command asked															*/
/*%C Search if a key connected																*/
/*%C If a key is connected and only one key, compute free space					*/
/******************************************************************************/
		else
		{
			/*%C Select MsNb */
			if(KeyNumber == KEY_1)
			{
				KeyNumber = KEY_2;
			}
			else
			{
				KeyNumber = KEY_1;
			}
			/*%C Build the frame	*/
			DRV_USB_AskKeyConnected(KeyNumber);

			/*%C Test if two keys are connected */
			if		((UsbMsnbOneDetected == TRUE)
				&&	 (UsbMsnbTwoDetected == TRUE))
			{
				if(UsbDetectedTwoManyKey == TRUE) 
				{
					/*%C To write the flag only one time */
					UsbDetectedTwoManyKey = FALSE ;
					/*%C To compute free space when only one key will still connected */
					UsbDetectedAKey = TRUE ;
					UsbPreviousTwoKeyConnected = TRUE ;
					/*%C Update USB DataBase */
					DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_TOO_MANY_KEY_CONNECTED);
					DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);
					/* Play Sounds on Usb Key Dectection only */
					/*if the key is detected after a power on*/
					if (	UsbKey1DetectedAfterpowerOn == TRUE 
						&& UsbKey2DetectedAfterpowerOn == TRUE)
					{						
						USB_BipRequest(BIP_USB_CONNECT);
					}
					/*%C Write Event too many keys connected in flash*/
					USB_WriteEvent(EVENT_USB_TOO_MANY_KEYS_CONNECTED);
				}
			}
			/*%C Test if only one key is connected */
			else if(((UsbMsnbOneDetected == TRUE)
					&&	 (UsbMsnbTwoDetected == FALSE))
					||	((UsbMsnbOneDetected == FALSE) 
					&&	 (UsbMsnbTwoDetected == TRUE))	)
			{
				if(UsbDetectedAKey == TRUE)
				{
					/*%C To write the flag only one time */
					UsbDetectedTwoManyKey = TRUE ;
					UsbDetectedAKey = FALSE ;
					/*%C Update USB DataBase */
					DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_ONE_KEY_CONNECTED);
					DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);
						
					/* Play Sounds on Usb Key Dectection only */
					/*if the key is detected after a power on*/
					if (	UsbKey1DetectedAfterpowerOn == TRUE 
						&& UsbKey2DetectedAfterpowerOn == TRUE)
					{						
						USB_BipRequest(BIP_USB_CONNECT);			
					}	
				}

				/*%C If a new key is connected */
				if		((UsbNewKeyDetected == TRUE)
					||	(UsbEndOfCommand == TRUE)
					||	(UsbEraseCommand == TRUE)
					|| (UsbPreviousTwoKeyConnected == TRUE))
				{
					
					/*%C Update Error Detected Flag */ 
					DisplayErrorCodeFlag = TRUE ;
					UsbErrorDetectedFlag = FALSE ;

					/*%C Update Flag */
					PreviousNoKeyConnected = FALSE ;

					/*%C Re-Init the UsbNbBytesWriteOnKey */
					UsbNbBytesWriteOnKey = 0 ;

					/*%C Update flag */
					UsbEndOfCommand = FALSE ;
					UsbEraseCommand = FALSE ;
					UsbPreviousTwoKeyConnected = FALSE ;
					/* Compute Free Space */
					if(UsbMsnbOneDetected == TRUE)
					{
						/*%C Compute Key_One Free Space */
						DRV_USB_GetFreeSpace(KEY_1) ;
					}
					else if(UsbMsnbTwoDetected == TRUE)
					{
						/*%C Compute Key_Two Free Space */
					  	DRV_USB_GetFreeSpace(KEY_2) ;
					}
					else
					{
						/*%C Frame isn't ready to be Send */
						FrameReadyToSend = FALSE ;
					}
				}
			}
			else
			{
			  	if(PreviousNoKeyConnected == FALSE)
				{
					/*%C Update USB DataBase */
					DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_KEY_DISCONNECTED);
					DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);
					/* Play Sounds on Usb Key Dectection */					
					USB_BipRequest(BIP_USB_DISCONNECT);

					/*%C Update Flag */
					PreviousNoKeyConnected = TRUE ;
				}
				else
				{
					/*%C No Function */
				}
				UsbDetectedTwoManyKey = TRUE ;
				UsbDetectedAKey = TRUE ;
			}
		}

/******************************************************************************/
/*%C Check the Reply and update USB DataBase												*/
/*%C Send the next frame 																		*/
/******************************************************************************/
		if (FrameReadyToSend == TRUE)
		{
			/*%C Start Timer to check a busy too long when */
			/*%C a other command is asked (300 sec) */
			TIM_StartMinuteDecounter(TimerUsbCommandTooLong,
                               TIME_WAIT_USB_BUSY_VERY_LONG_COMMAND,
                               FALSE);

			DRV_USB_CheckReplyFrame();

			DRV_USB_Send_Frame();
		}
		else
		{
			/*%C No function	*/
		}
	}

/******************************************************************************/
/*%C Check if the busy is low during a time too long	(Reset the bridge)		*/
/******************************************************************************/
	else if (TIM_ReadMinuteDecounterValue(TimerUsbCommandTooLong) == 0)
	{

/******************************************************************************/
/*%C DeSelect the bridge 																		*/
/******************************************************************************/
  		DRV_OutputPort(CE_SPI_USB,1) ;

/******************************************************************************/
/*%C Reset the bridge 																			*/
/******************************************************************************/
		/*%C Reset the bridge during 1.6µs minimum (Using T2)*/
		RESET_USB = 0;
		/*%C Raz flag underflow timer 2 														*/
		T2IR = 0 ;
		/*%C 16 * 200ns, duree du timer 2 = 3.2 µs 				*/
		T2 = 16 ;
		/*%C count down, fc=fcpu/8, start timer 											*/
		T2CON = 0x00C0 ;
		/*%C Waiting for end bridge busy or TimeOut */
		while (T2IR == 0);
		/*%C Stop Timer 4 																		*/
		T2CON = 0x0000; 
	
		RESET_USB = 1;

/******************************************************************************/
/*%C Reload timer, init datas and SPI port												*/
/******************************************************************************/
		FirstRun = TRUE ;

		/*%C Update Error Detected Flag */ 
		DisplayErrorCodeFlag = TRUE ;
		UsbErrorDetectedFlag = FALSE ;
	}

/******************************************************************************/
/*%C When bridge is busy 																		*/
/******************************************************************************/
	else
	{
		/*%C No function */
	}

/******************************************************************************/
/*%C Gestion de la pile des messages USB pour l'IHM							*/
/******************************************************************************/
	/*%C Permet d'envoyer le message contenu dans la pile à l'IHM			*/
	DRV_USB_ReadFifo();
	
	/*%C Permet de mettre le message en pile si l'IHM n'est pas prete		*/
	DRV_USB_WriteFifo();
}

static void USB_BipRequest(e_VALIDATION_BIP bip)
{
#ifdef CONFIG_USB
	DB_ControlWrite(VALIDATION_BIP_U16, bip);
#else
	bip = bip;
#endif
}

static void USB_WriteEvent(UWORD16 value)
{
#ifdef CONFIG_USB
	DB_EventMngt(value);
#else
	value = value;
#endif
}