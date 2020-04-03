/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_CheckReplyFrame.c 													*/
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
#ifndef _BORLAND
   #ifndef _TASKING
      #include "LH_ST10F276.h"
      #include <intrins.h>
   #else
      #include "regf276e.h"
   #endif
#endif

#ifdef _BORLAND
   /* Attention, conserver cette inclusion _après_ l'inclucion du io_declare.h
      car redéfinition des valeurs de JUMPER pour chaque produit */
      #include "io_declare.h"
      #include "HMI_Product.hpp"
#else
   #include "io_declare.h"
#endif

#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "Structure.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Usb.h"
#include "DB_Event.h"
#include "Driver_USB_Data.h"
#include "CRC16_Table.h"
#include "Flash_Monit_Data.h"
#include "DRV_USB_CheckReplyFrame.h"

											
/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/
void DRV_USB_CheckReplyFrame(void)
{

/******************************************************************************/
/*%C Local variables 																			*/
/******************************************************************************/

	UBYTE ComputeReplyHeaderCheck = 0 ;
	UWORD16 ReplyNbBytes = 0 ;

	UWORD16 EntryType = 0 ;
	UWORD16 ReplyHeaderCheck = 0 ;
	UWORD16 ReplyCommand = 0 ;
	UWORD16 ReplyMsNb = 0 ;
	UWORD16 ReplyStatus = 0 ;

	UWORD16 LoopCKS = 0 ;
	UWORD16 LoopFileName = 0 ;

	UWORD16 Compute_CRC = 0 ;
	UWORD16 Compteur = 0 ;

	UWORD16 VentilMode = 0 ;

	UWORD16 CheckSumReply = 0 ;

	UWORD16 FreeSpaceKey = 0 ;

	UWORD16 ParamCompatibility = 0 ;									
	UWORD16 SettingsCompatible = 0 ;

	UWORD16 UsbErrorCode = E_USB_OK ;
	UWORD16 UsbEventCode = 0 ;

	UWORD16 UsbMsnbOneDetected 
								= DB_UsbRead(USB_MSNB_ONE_DETECTED_U16);
	UWORD16 UsbMsnbTwoDetected 
								= DB_UsbRead(USB_MSNB_TWO_DETECTED_U16);
	UWORD16 UsbMonitorTransferSelect 
								= DB_UsbRead(USB_MONITOR_TRANSFER_SELECT_U16);
	UWORD16 UsbTrendTransfertSelect 
								= DB_UsbRead(USB_TREND_TRANSFER_SELECT_U16);
	UWORD16 UsbEventsTransfertSelect 
								= DB_UsbRead(USB_EVENTS_TRANSFER_U16);	
	UWORD16 UsbContinuousRecording 
								= DB_UsbRead(USB_CONTINUOUS_RECORDING_U16);


	static UWORD16 PreviousKeyOneConnected = FALSE ;
	static UWORD16 PreviousKeyTwoConnected = FALSE ;
	


/******************************************************************************/
/*%C Verify the header check																	*/
/******************************************************************************/

	/*%C Compute the reply header check */
	ComputeReplyHeaderCheck = 	(UBYTE)
										((PEC_Reception[1]  	& 0x0F)
									^ 	((PEC_Reception[1] 	& 0xF0) >> 4)
									^ 	(PEC_Reception[0]  	& 0x0F));



	ComputeReplyHeaderCheck = ~ ComputeReplyHeaderCheck ;
	ComputeReplyHeaderCheck &= 0x0F;

	/*%C Extract the reply header check */
	ReplyHeaderCheck = ((PEC_Reception[0] & 0xF0) >> 4);

	/*%C Compare the reply header chack with the compute header check */
	if(ReplyHeaderCheck == ComputeReplyHeaderCheck)
	{
		/*%C Search the reply nb bytes */
		ReplyNbBytes = (PEC_Reception[0] << 8 ) | PEC_Reception[1] ;
		
		/*%C ReplyNbBytes is extract */
		ReplyNbBytes = ReplyNbBytes & 0x0FFF ;

		if ( ReplyNbBytes > 2)
		{
			/*%C Compute CRC frame */
			for(LoopCKS = 0 ; LoopCKS < ReplyNbBytes - 2 ; LoopCKS ++)
			{
				CheckSumReply = CheckSumReply + (UWORD16)PEC_Reception[LoopCKS] ;
			}
		}

		/*%C Verify CheckSum */
		if(	(PEC_Reception[ReplyNbBytes - 2] == (UBYTE)(CheckSumReply	>> 8))
			&&	(PEC_Reception[ReplyNbBytes - 1] == (UBYTE)CheckSumReply))
		{
			/*%C Extract Reply Command */
			ReplyCommand = PEC_Reception[2] - 0x80 ;

			/*%C Extract Reply Command */
			ReplyMsNb = PEC_Reception[3] ;

			/*%C Extract Status */
			ReplyStatus = PEC_Reception[4] ;

			/*%C Build Frame to read the status delayed	*/
			if(ReplyStatus > 0x79)
			{
					DRV_USB_GetDelayedStatus(ReplyMsNb);
					return ;
			}

			switch(ReplyCommand)
			{
/******************************************************************************/
/*%C Case Command Get Delayed Status														*/
/******************************************************************************/
				case CMD_GET_DELAYED_STATUS :
				{
					/*%C No Function */
					break ;
				}
/******************************************************************************/
/*%C Case Command Open File																	*/
/******************************************************************************/
				case CMD_OPEN_FILE :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}	
					/*%C Test if the file is open */
					else if		((ReplyStatus == POSITIVE_REPONSE)
								||	(ReplyStatus == FILE_OPEN))  
					{
				 		UsbErrorCode = E_USB_OK ;
					}
					else
					{
			 			UsbErrorCode = E_USB_FILE_OPEN_FAILED ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_TRANSFER_ERROR ;
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Close File																	*/
/******************************************************************************/
				case CMD_CLOSE_FILE :
				{
			
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}	
					/*%C Test if the file is close */
					else if(ReplyStatus == POSITIVE_REPONSE)
					{
						if ( (UsbErrorDetectedFlag == FALSE)
						  && (UsbWriteSettingsApply == TRUE) )
						{
							/*%C Ask free space memory after a action */
							UsbEndOfCommand = TRUE ;
							DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_OK);
							DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);
							
							/*%C Update Error Code Flag */ 
							DisplayErrorCodeFlag = FALSE ;

							/*%C Update Write Settings Flag */
							UsbWriteSettingsApply = FALSE ;


						}
						else
						{
							/*%C We don't display the message end of transfert */
							/*%C No Function */							
						}
					}
					else if(UsbErrorDetectedFlag == FALSE)
					{
						/*%C Ask free space memory after a action */
						UsbEndOfCommand = TRUE ;

						DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_FILE_CLOSE_FAILED);
					 	DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);

						/*%C Write Event USB transfer error in flash*/
						DB_EventMngt(EVENT_USB_TRANSFER_ERROR);

						/*%C Update Error Code Flag */ 
						DisplayErrorCodeFlag = FALSE ;

						/*%C Update USB DataBase */
						DB_UsbWrite(USB_COMMAND_SENT_U16 , FALSE);
						DB_UsbWrite(USB_TRANSFER_APPLY_U16 , FALSE);
						DB_UsbWrite(USB_ERASE_KEY_U16 , FALSE);
						DB_UsbWrite(USB_CONTINUOUS_RECORDING_U16 , FALSE);
						DB_UsbWrite(USB_MONITOR_TRANSFER_SELECT_U16 , FALSE);
						DB_UsbWrite(USB_MONITOR_TRANSFER_U16 , FALSE);
						DB_UsbWrite(USB_TREND_TRANSFER_SELECT_U16 , FALSE);
						DB_UsbWrite(USB_TREND_TRANSFER_U16 , FALSE);
						DB_UsbWrite(USB_EVENTS_TRANSFER_U16 , FALSE);				

						if (USB_FileOpened == TRUE)
						{
							DRV_USB_CloseFile(CurrentUsbKey) ;
						}

						/*%C Udpate Events Authorization Flag */
						EventsAuthorizationFlag = FALSE ;

						/*%C Update Write Settings Flag */
						UsbWriteSettingsApply = FALSE ;
						
						/*%C Re Init this flag to the next transfert */
						FirstRemaningTimeApproximation = TRUE ;
						
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

						/*%C Re Init the Step */
						Step_UsbTransferApply = Usb_FirstStep ;
						Step_FileSetting = FileSettingNext ;
					}
					else
					{
						/*%C Ask free space memory after a action */
						UsbEndOfCommand = TRUE ;

						/*%C Update Write Settings Flag */
						UsbWriteSettingsApply = FALSE ;
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Create File																	*/
/******************************************************************************/
				case CMD_CREATE_FILE :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}	
					/*%C Test if the file is close */
					else if(ReplyStatus == POSITIVE_REPONSE)
					{
				 		UsbErrorCode = E_USB_OK ;
					}
					else
					{
				 		UsbErrorCode = E_USB_CREATE_FAILED ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_TRANSFER_ERROR ;
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Re-Initilainf File Reading		 										*/
/******************************************************************************/
				case CMD_RE_INITIALIZE_FILE_READING :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}	
					break ;
				}
/******************************************************************************/
/*%C Case Command Ask Key Connected															*/
/******************************************************************************/
				case CMD_ASK_KEY_CONNECTED :
				{
					/*%C Test if key one is connected */
					if(ReplyMsNb == KEY_1)
					{
						if(ReplyStatus == POSITIVE_REPONSE)
						{
							/*%C Test if is a new connection */
							if(PreviousKeyOneConnected == TRUE)
							{
								DB_UsbWrite(USB_MSNB_ONE_DETECTED_U16, TRUE);
								DB_UsbWrite(USB_NEW_KEY_CONNECTED_U16, FALSE);
							}
							else
							{
								DB_UsbWrite(USB_MSNB_ONE_DETECTED_U16, TRUE);
								DB_UsbWrite(USB_NEW_KEY_CONNECTED_U16, TRUE);
								PreviousKeyOneConnected = TRUE ;
							}
						}
						else
						{
							/*%C Key Disconnected during Continuous Recording */
					 		if ((UsbContinuousRecording == TRUE)
								&& (CurrentUsbKey == KEY_1))
							{
								UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
								/*%C Write Event USB transfer error in flash*/
								UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;
								/*%C Stop buffering datas */
								WriteBufferAuthorisation = FALSE ;
							}
							/*%C Key one is not connected */
							DB_UsbWrite(USB_MSNB_ONE_DETECTED_U16, FALSE);
							DB_UsbWrite(USB_NEW_KEY_CONNECTED_U16, FALSE);
							DB_UsbWrite(USB_KEY1_DETECTED_AFTER_POWER_ON_U16,TRUE);
							PreviousKeyOneConnected = FALSE ;
						}
					}
					/*%C Test if key two is connected */
					else if(ReplyMsNb == KEY_2)
					{
						if(ReplyStatus == POSITIVE_REPONSE)
						{
							/*%C Test if is a new connection */
							if(PreviousKeyTwoConnected == TRUE)
							{
								DB_UsbWrite(USB_MSNB_TWO_DETECTED_U16, TRUE);
								DB_UsbWrite(USB_NEW_KEY_CONNECTED_U16, FALSE);
							}
							else
							{
								DB_UsbWrite(USB_MSNB_TWO_DETECTED_U16, TRUE);
								DB_UsbWrite(USB_NEW_KEY_CONNECTED_U16, TRUE);
								PreviousKeyTwoConnected = TRUE ;
							}
						}
						else
						{
							/*%C Key Disconnected during Continuous Recording */
					 		if ((UsbContinuousRecording == TRUE)
							&& (CurrentUsbKey == KEY_2))
							{
								UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
								/*%C Write Event USB transfer error in flash*/
								UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;
								/*%C Stop buffering datas */
								WriteBufferAuthorisation = FALSE ;
							}
							/*%C Key two is not connected */
							DB_UsbWrite(USB_MSNB_TWO_DETECTED_U16, FALSE);
							DB_UsbWrite(USB_NEW_KEY_CONNECTED_U16, FALSE);
							DB_UsbWrite(USB_KEY2_DETECTED_AFTER_POWER_ON_U16,TRUE);
							PreviousKeyTwoConnected = FALSE ;
						}
					}
					else
					{
						/*%C No Function */
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Open Directory 															*/
/******************************************************************************/
				case CMD_OPEN_DIRECTORY :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Go Back to Parent Directory	 										*/
/******************************************************************************/
				case CMD_GO_BACK_PARENT_DIRECTORY :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Change file date and time 												*/
/******************************************************************************/
				case CMD_CHANGE_FILE_DATA_TIME :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					/*%C Test if the file modification date and time is ok */
					else if(ReplyStatus == POSITIVE_REPONSE)
					{
				 		UsbErrorCode = E_USB_OK ;
					}
					else
					{
			 			UsbErrorCode = E_USB_CREATE_FAILED ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_TRANSFER_ERROR ;
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Create Directory															*/
/******************************************************************************/
				case CMD_CREATE_DIRECTORY :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Erase Entite Memory														*/
/******************************************************************************/
				case CMD_ERASE_ENTIRE_MEMORY :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					/*%C Test if entire erase is ok */
					else if(ReplyStatus == POSITIVE_REPONSE)
					{
						/*%C Ask free space memory after a erase action */
						UsbEraseCommand = TRUE ;

						DB_UsbWrite(USB_STOP_COMMAND_SENT_U16 , FALSE);
						DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_OK);
						DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);
						/*%C Update Error Code Flag */
						DisplayErrorCodeFlag = FALSE ;
					}
					else
					{
						/*%C Ask free space memory after a erase action */
						UsbEraseCommand = TRUE ;						
						
						DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_ENTIRE_ERASE_FAILED);
						DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);

						/*%C Write Event usb error erase key in flash*/
						DB_EventMngt(EVENT_USB_ERASE_KEY_ERROR);

						/*%C Update Error Code Flag */ 
						DisplayErrorCodeFlag = FALSE ;
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Repair a File																*/
/******************************************************************************/
				case CMD_REPAIR_A_FILE :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Read File																	*/
/******************************************************************************/
				case CMD_READ_FILE :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					else if		((ReplyStatus == POSITIVE_REPONSE)
								||	(ReplyStatus == END_OF_FILE_REACHED))
					{
						/*%C CRC16 Compute */
						UsbComputeCRC =  CRC16_TableCompute
						(
							(UWORD16)(USB_SETTING_SERIAL_NUMBER_1 + 5),
							(UWORD16)(		USB_SETTINGS_DATA 
											+ 	End_of_e_usb_frame_serialNumberAndDate
											+ 	End_Of_Table_Settings
											+ 	5
											),
							PEC_Reception, 
							0
						);



						/*%C CrC is ok */
						if(	(((UBYTE)(UsbComputeCRC >> 8)) ==
													(PEC_Reception[
													End_of_e_usb_frame_serialNumberAndDate
												+ 	End_Of_Table_Settings
												+	USB_SETTINGS_MSB_CRC_FRAME
												+	5
												-	1]))
							&&
								(((UBYTE)(UsbComputeCRC & 0x00FF)) ==
													(PEC_Reception[
													End_of_e_usb_frame_serialNumberAndDate
												+ 	End_Of_Table_Settings
												+	USB_SETTINGS_LSB_CRC_FRAME
												+	5
												-	1])))
						{
							/*%C Extract the ventilator Identifiant to verify */
							/*C% compatibility */
							if(	(JUMPER_JP7 == JUMPER_OFF)
								&&	(JUMPER_JP8 == JUMPER_OFF))
							{
								/*%C This is a Legend@ir XL2 */
								ParamCompatibility = XL2_IDENTIFIANT ;
							}
							else if	(	(JUMPER_JP7 == JUMPER_ON) 
										&&	(JUMPER_JP8 == JUMPER_OFF))
							{
								/*%C This is a Smart@ir S2 */
								ParamCompatibility = S2_IDENTIFIANT ;
							}
							else if	(	(JUMPER_JP7 == JUMPER_OFF) 
										&&	(JUMPER_JP8 == JUMPER_ON))
							{
								/*%C This is a Support@ir M2 */
								ParamCompatibility = M2_IDENTIFIANT ;
							}
							else
							{
								/*%C This is a invalid device */
								ParamCompatibility = ERROR_IDENTIFIANT ;
							}

							DB_ConfigWrite(PARAM_COMPATIBILITY, ParamCompatibility);

							SettingsCompatible = DRV_USB_VerifyCompatibility();

							/*%C The settings are compatible */
							if(SettingsCompatible == TRUE)
							{
								/*%C This is the same ventilateur */
								DRV_USB_Transmit_Settings(TRUE);
							}
							/*%C Settings are not compatible */
							else
							{
				 				UsbErrorCode = E_USB_INCOMPATIBLE_SETTINGS ;
								/*%C Write Event usb settings incompatibles key in flash*/
								UsbEventCode = EVENT_USB_SETTINGS_INCOMPATIBLES ;
							}
						}
						/*%C CrC false */
						else
						{
				 			UsbErrorCode = E_USB_SETTING_FILE_CORRUPTED ;						
							/*%C Write Event usb setting file corrupted in flash*/
							UsbEventCode = EVENT_USB_SETTINGS_FILE_ERROR ;
						}
					}
					else
					{
				 		UsbErrorCode = E_USB_FILE_READ_FAILED ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_TRANSFER_ERROR ;
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Write At The End Of File												*/
/******************************************************************************/
				case CMD_WRITE_AT_THE_END_OF_THE_FILE :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_NOT_CONNECTED)
						||(ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD))
					{
						/*%C Key Disconnected during Continuous Recording */
				 		if (UsbContinuousRecording == TRUE)
						{
							/*%C Stop buffering datas */
							WriteBufferAuthorisation = FALSE ;
						}
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					/*%C Test if file is written */
					else if(ReplyStatus == POSITIVE_REPONSE)
					{
				 		UsbErrorCode = E_USB_OK ;
					}
					else if(ReplyStatus == USB_MS_FULL)
					{
						/*%C USB transfer error during Continuous Recording */
				 		if (UsbContinuousRecording == TRUE)
						{
							/*%C Stop buffering datas */
							WriteBufferAuthorisation = FALSE ;
						}

				 		UsbErrorCode = E_USB_NO_FREE_SPACE ;
						/*%C Write Event usb setting file corrupted in flash*/
						UsbEventCode = EVENT_USB_KEY_FULL ;
					}
					else
					{
						/*%C USB transfer error during Continuous Recording */
				 		if (UsbContinuousRecording == TRUE)
						{
							/*%C Stop buffering datas */
							WriteBufferAuthorisation = FALSE ;
						}
				 		UsbErrorCode = E_USB_FILE_WRITE_FAILED ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_TRANSFER_ERROR ; 
					}
					break ;
				}

/******************************************************************************/
/*%C Case Command Read File Information													*/
/******************************************************************************/
				case CMD_READ_FILE_INFORMATION :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Get Free Space																*/
/******************************************************************************/
				case CMD_GET_FREE_SPACE :
				{
					if(ReplyMsNb == KEY_1)
					{
						/*%C Key Disconnected during this operation */
				 		if (ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						{
							UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
							/*%C Write Event USB transfer error in flash*/
							UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
						}	
						else if(ReplyStatus == POSITIVE_REPONSE)
						{
							/*%C Extract free Space in Bytes */
							FreeSpaceKey = PEC_Reception[5];
							FreeSpaceKey = FreeSpaceKey << 8;
							FreeSpaceKey |= (PEC_Reception[6] & 0x00FF);
							DB_UsbWrite(	USB_MSB_FREE_SPACE_KEY_ONE,
												(UWORD16)(FreeSpaceKey));

							FreeSpaceKey = PEC_Reception[7];
							FreeSpaceKey = FreeSpaceKey << 8;
							FreeSpaceKey |= (PEC_Reception[8] & 0x00FF);
							DB_UsbWrite(	USB_LSB_FREE_SPACE_KEY_ONE,
												(UWORD16)(FreeSpaceKey));

							/*%C Check if we have two key connected, 
							/*%C we don't unlock the Frame USB */
							if	((UsbMsnbOneDetected == FALSE)
								|| (UsbMsnbTwoDetected == FALSE))
						  	{
								
								DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_READY_ACCESS);
								DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);
								USB_CommandInProgress = FALSE;	
								//DB_UsbWrite(USB_KEY1_DETECTED_AFTER_POWER_ON_U16,TRUE);								
								
								/*%C Update Error Code Flag */ 
								DisplayErrorCodeFlag = FALSE ;
							}
						}
						else
						{
							/*%C Check if we have two key connected, 
							/*%C we don't display this message */
							if ( ( (UsbMsnbOneDetected == FALSE)
							    || (UsbMsnbTwoDetected == FALSE) )
							  && ( (UsbMsnbOneDetected == TRUE)
							    || (UsbMsnbTwoDetected == TRUE) ) )
						  	{
								DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_FILE_SYSTEM_FAILED);
								DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);
	
								/*%C Write Event USB transfer error in flash*/
								DB_EventMngt(EVENT_USB_TRANSFER_ERROR);
	
								/*%C Update Error Code Flag */ 
								DisplayErrorCodeFlag = FALSE ;
							}
						}
					}
					if(ReplyMsNb == KEY_2)
					{
						/*%C Key Disconnected during this operation */
				 		if (ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						{
							UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
							/*%C Write Event USB transfer error in flash*/
							UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
						}	
						else if(ReplyStatus == POSITIVE_REPONSE)
						{
							/*%C Extract free Space in Bytes */
							FreeSpaceKey = PEC_Reception[5];
							FreeSpaceKey = FreeSpaceKey << 8;
							FreeSpaceKey |= (PEC_Reception[6] & 0x00FF);
							DB_UsbWrite(	USB_MSB_FREE_SPACE_KEY_TWO,
												(UWORD16)(FreeSpaceKey));

							FreeSpaceKey = PEC_Reception[7];
							FreeSpaceKey = FreeSpaceKey << 8;
							FreeSpaceKey |= (PEC_Reception[8] & 0x00FF);
							DB_UsbWrite(	USB_LSB_FREE_SPACE_KEY_TWO,
												(UWORD16)(FreeSpaceKey));
							
							/*%C Check if we have two key connected, 
							/*%C we don't unlock the Frame USB */
							if	((UsbMsnbOneDetected == FALSE)
								|| (UsbMsnbTwoDetected == FALSE))
						  	{
								DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_READY_ACCESS);
								DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);
								USB_CommandInProgress = FALSE;	
								//DB_UsbWrite(USB_KEY2_DETECTED_AFTER_POWER_ON_U16,TRUE);

								/*%C Update Error Code Flag */
								DisplayErrorCodeFlag = FALSE ;
							}
						}
						else
						{
							/*%C Check if we have two key connected, 
							/*%C we don't display this message */
							if ( ( (UsbMsnbOneDetected == FALSE)
							    || (UsbMsnbTwoDetected == FALSE) )
							  && ( (UsbMsnbOneDetected == TRUE)
							    || (UsbMsnbTwoDetected == TRUE) ) )
						  	{
								DB_UsbWrite(USB_ERROR_CODE_U16 , E_USB_FILE_SYSTEM_FAILED);
								DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);
							
								/*%C Write Event USB transfer error in flash*/
								DB_EventMngt(EVENT_USB_TRANSFER_ERROR);

								/*%C Update Error Code Flag */
								DisplayErrorCodeFlag = FALSE ;
							}
						}
					}
					else
					{
						/*%C No Function */
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Read File at Index														*/
/******************************************************************************/
				case CMD_READ_FILE_AT_INDEX :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					/*%C Test if file is written */
					else if(ReplyStatus == POSITIVE_REPONSE)
					{
				 		UsbErrorCode = E_USB_OK ;
					}
					else
					{
				 		UsbErrorCode = E_USB_FILE_READ_FAILED ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_TRANSFER_ERROR ; 
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Write File At Index														*/
/******************************************************************************/
				case CMD_WRITE_FILE_AT_INDEX :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					/*%C Test if file is written at index */
					else if(ReplyStatus == POSITIVE_REPONSE)
					{
				 		UsbErrorCode = E_USB_OK ;
					}
					else if(ReplyStatus == USB_MS_FULL)
					{
				 		UsbErrorCode = E_USB_NO_FREE_SPACE ;
						/*%C Write Event usb setting file corrupted in flash*/
						UsbEventCode = EVENT_USB_KEY_FULL ;

					}
					else
					{
				 		UsbErrorCode = E_USB_SETTING_FILE_CORRUPTED ;
						/*%C Write Event usb setting file corrupted in flash*/
						UsbEventCode = EVENT_USB_SETTINGS_FILE_ERROR ;
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Identify Current Firmware												*/
/******************************************************************************/
				case CMD_IDENTIFY_CURRENT_FIRMWARE :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Identify Open Firmware													*/
/******************************************************************************/
				case CMD_IDENTIFY_OPEN_FIRMWARE :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;							
					}
					break ;
				}
/******************************************************************************/
/*%C Case Command Update Firmware															*/
/******************************************************************************/
				case CMD_UPDATE_FIRWARE :
				{
					/*%C Key Disconnected during this operation */
			 		if ((ReplyStatus == USB_MS_DISCONNECTED_DURING_CMD)
						||(ReplyStatus == USB_MS_NOT_CONNECTED))
					{
						UsbErrorCode = E_USB_DISCONNECTION_KEY_DURING_OPERATION ;
						/*%C Write Event USB transfer error in flash*/
						UsbEventCode = EVENT_USB_KEY_DISCONNECTED_DURING_OPERATION;																				
					}
					break ;
				}
/******************************************************************************/
/*%C Case Default																					*/
/******************************************************************************/
				default :
				{ 
					/*%C No Function */ 
					break ; 
				}
			}
/******************************************************************************/
/*%C End of the switch, update USB_ERROR_CODE_U16 										*/
/******************************************************************************/
			if		((UsbErrorCode != E_USB_OK)
				&& (DisplayErrorCodeFlag == TRUE))
			{
				/*%C Update Error Code Flag */
				DisplayErrorCodeFlag = FALSE ;

				/*%C Update Usb Error Code */
				DB_UsbWrite(USB_ERROR_CODE_U16 , UsbErrorCode);
				DB_UsbWrite(USB_ERROR_CODE_READY_U16 , FLAG_ERROR_CODE_READY);
				/*%C Write Event USB transfer error in flash*/
				DB_EventMngt(UsbEventCode);

				/*%C Close the file in error case expected a disconnection key */
				/*%C On Key One */
				if(	(UsbMsnbOneDetected == TRUE)
					&&	(UsbMsnbTwoDetected == FALSE)
					&& (UsbErrorCode != E_USB_DISCONNECTION_KEY_DURING_OPERATION))
				{
					/*%C Build the frame */
					DRV_USB_CloseFile(KEY_1) ;
				}
				/*%C On Key Two */
				else if(		(UsbMsnbTwoDetected == TRUE)
							&&	(UsbMsnbOneDetected == FALSE)
							&& (UsbErrorCode != E_USB_DISCONNECTION_KEY_DURING_OPERATION))
				{
					/*%C Build the frame */
					DRV_USB_CloseFile(KEY_2) ;
				}
				else
				{
					/*%C No Function */
				}

				/*%C Update USB DataBase */
				DB_UsbWrite(USB_COMMAND_SENT_U16 , FALSE);
				DB_UsbWrite(USB_TRANSFER_APPLY_U16 , FALSE);
				DB_UsbWrite(USB_ERASE_KEY_U16 , FALSE);
				DB_UsbWrite(USB_CONTINUOUS_RECORDING_U16 , FALSE);
				DB_UsbWrite(USB_MONITOR_TRANSFER_SELECT_U16 , FALSE);
				DB_UsbWrite(USB_MONITOR_TRANSFER_U16 , FALSE);
				DB_UsbWrite(USB_TREND_TRANSFER_SELECT_U16 , FALSE);
				DB_UsbWrite(USB_TREND_TRANSFER_U16 , FALSE);
				DB_UsbWrite(USB_EVENTS_TRANSFER_U16 , FALSE);				

				/*%C Udpate Events Authorization Flag */
				EventsAuthorizationFlag = FALSE ;

				/*%C Re Init this flag to the next transfert */
				FirstRemaningTimeApproximation = TRUE ;
				
				/*%C Re Init the Step */
				Step_UsbTransferApply = Usb_FirstStep ;
				Step_FileSetting = FileSettingNext ;

				/*%C Update a flag to indicate the error */
				UsbErrorDetectedFlag = TRUE ;
				UsbFlashTrasnferRunning = USB_NAND_TRANSFER_IDLE;

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
			}
			else
			{
				/*%C No Function */
			}
		}
/******************************************************************************/
/*%C Incorrect frame																				*/
/******************************************************************************/
		else
		{
			/*%C Reply CheckSum is incorrect  */
		}
	}
/******************************************************************************/
/*%C Incorrect header																			*/
/******************************************************************************/
	else
	{ 
		/*%C Reply Header is incorrect  */
	}
}