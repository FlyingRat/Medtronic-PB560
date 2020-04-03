/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                           				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Driver_USB_Data.h 															*/
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
/*                             #DEFINE		                        				*/
/******************************************************************************/



/*%C  Continuous record buffer size (5s)														*/

#define DRV_USB_CONTINUOUS_RECORD_BUFFER_SIZE 1375


/*%C Send command to Bridge 																	*/

#define CMD_OPEN_FILE	 						0x00
#define CMD_CLOSE_FILE	 						0x01
#define CMD_READ_FILE 							0x02
#define CMD_WRITE_AT_THE_END_OF_THE_FILE 	0x03
#define CMD_CREATE_FILE			 				0x04
#define CMD_RE_INITIALIZE_FILE_READING 	0x06
#define CMD_READ_CURRENT_DIRECTORY		 	0x07
#define CMD_ASK_KEY_CONNECTED			 		0x08
#define CMD_OPEN_DIRECTORY				 		0x09
#define CMD_GO_BACK_PARENT_DIRECTORY 		0x0A
#define CMD_CHANGE_FILE_DATA_TIME	 		0x0B
#define CMD_READ_FILE_INFORMATION	 		0x0C
#define CMD_GET_FREE_SPACE						0x0D
#define CMD_CREATE_DIRECTORY			 		0x0E
#define CMD_READ_FILE_AT_INDEX		 		0x12
#define CMD_WRITE_FILE_AT_INDEX		 		0x13
#define CMD_ERASE_ENTIRE_MEMORY		 		0x14

#define CMD_REPAIR_A_FILE				 		0x20

#define CMD_IDENTIFY_CURRENT_FIRMWARE 		0x30
#define CMD_IDENTIFY_OPEN_FIRMWARE	 		0x31
#define CMD_UPDATE_FIRWARE 					0x32

#define CMD_GET_DELAYED_STATUS		 		0x70


/*%C Rep bridge to CPU Board																	*/

#define REP_OPEN_FILE	 						0x80
#define REP_CLOSE_FILE	 						0x81
#define REP_READ_THE_FILE 						0x82
#define REP_WRITE_AT_THE_END_OF_THE_FILE	0x83
#define REP_CREATE_FILE			 				0x84
#define REP_RE_INITIALIZE_FILE_READING 	0x86
#define REP_READ_CURRENT_DIRECTORY		 	0x87
#define REP_ASK_KEY_CONNECTED			 		0x88
#define REP_OPEN_DIRECTORY				 		0x89
#define REP_GO_BACK_PARENT_DIRECTORY 		0x8A
#define REP_CHANGE_FILE_DATA_TIME	 		0x8B
#define REP_READ_FILE_INFORMATION	 		0x8C
#define REP_GET_FREE_SPACE_PARTITION 		0x8D
#define REP_CREATE_DIRECTORY			 		0x8E
#define REP_READ_FILE_AT_INDEX		 		0x92
#define REP_WRITE_FILE_AT_INDEX		 		0x93
#define REP_ERASE_ENTIRE_MEMORY		 		0x94

#define REP_REPAIR_A_FILE				 		0xA0

#define REP_IDENTIFY_CURRENT_FIRMWARE 		0xB0
#define REP_IDENTIFY_OPEN_FIRMWARE	 		0xB1
#define REP_UPDATE_FIRWARE 					0xB2

#define REP_GET_DELAYED_STATUS		 		0xF0

#define REP_TOO_LONG_COMMAND			 		0xFF

																							  	
/*%C List of Status Code																		*/

/*%C Generic Error Code 																		*/
#define POSITIVE_REPONSE 						0x00
#define INVALID_COMMAND 						0x09
#define KEY_NOT_CONNECTED 						0x0C
#define TOO_SHORT_COMMAND_ARGUMENTS 		0x40
#define DELAYED_COMMANDS_FORBIDDEN			0x41

/*%C Error Codes related to USB MS State													*/
#define USB_MS_NOT_CONNECTED	 				0x0C
#define INVALID_USB_MS_NUMBER	 				0x16
#define USB_MS_DISCONNECTED_DURING_CMD 	0x17
#define USB_MS_COMMUNICATION_ERROR		 	0x15

/*%C Error Codes related to File / deirectory operations 							*/
#define FILE_DIRECTORY_NOT_EXIST		 		0x01
#define FILE_OPEN						 			0x02
#define USB_MS_FULL						 		0x03
#define FILE_IS_NOT_OPEN	 					0x05
#define FILE_IS_WRITE_PROTECTED				0x06
#define FILE_DIRECTORY_ALREADY_EXIST 		0x0B
#define TOO_MANY_DIRECTORIS_OPEN				0x0D
#define DIRECTORIES_IS_NOT_EMPTY		 		0x0E
#define ILLEGAL_FILE_DIRECTORY_NAME	 		0x0F
#define FILE_ALLOCATION_EEROR			 		0x10
#define INVALID_NAVIGATION_TYPE		 		0x12
#define TOO_MANY_BYTES_TO_READ		 		0x13
#define ROOT_FAT16_DIRECTORY_FULL	 		0x14
#define FILE_CORRUPTED_NOT_BE_REPAIRED		0x11
#define FILE_CORRUPTED_BE_REPAIRED			0x18
#define FILE_REPAIR_FAILED						0x19
#define INVALID_INDEX							0x1A
#define END_OF_FILE_OVERRUN					0x1B
#define NO_DIRECTORY_READING_IN_PROGRESS	0x1C
#define INVALID_READ_DIRECTORY_ARGUMENT	0x1D

/*%C Error codes related to firmware update 												*/
#define INVALID_FIRMWARE_UPDATE				0x20
#define FIRMWARE_UPDATE_FATAL_ERROR			0x21

/*%C Error internal to the bridge subsystem												*/
#define INTERNAL_ERROR							0x30

/*%C Status code not related to an error													*/
#define END_OF_FILE_REACHED					0x04
#define NO_MORE_ENTRY_TO_READ_DIRECTORY	0x0A

/*%C Size Request and Reply 																	*/
#define CMD_SIZE									0x01
#define MSNB_SIZE									0x01
#define FIRST_OR_NEXT							0x01
#define CREATION_TIME							0x02
#define CREATION_DATE							0x02
#define MODIFICATION_TIME						0x02
#define MODIFICATION_DATE						0x02
#define NB_BYTES_INDEX							0x04
#define NO_DATAFIELD								0x00
#define HEADER_SIZE								0x02
#define CHECKSUM_SIZE							0x02
#define NB_BYTES_TO_READ_SIZE					0x02

#define FIRST										0x00
#define NEXT										0x01

#define ENTRY_TYPE_DIRECTORTY					0x00
#define ENTRY_TYPE_FILE							0x01

#define KEY_1										0x01
#define KEY_2										0x02


#define USB_MONITORING_IDENTIFIANT			0x01
#define USB_TREND_IDENTIFIANT					0x02
#define USB_EVENTS_IDENTIFIANT				0x03

#define USB_EVENTS_BUFFER_SIZE				0x0A
#define USB_NB_DATA_CRC16						0x02

#define DETAILLED_MONITORING_TYPE			0x00
#define DETAILLED_HORODATAGE_TYPE			0x01

#define DETAILLED_MONITORING_PERIOD			25
#define TRENDS_PERIODE							1

#define JUMPER_ON									0
#define JUMPER_OFF								1

/*%C Relative to JUMP CPU Card */
#define XL2_IDENTIFIANT							0
#define S2_IDENTIFIANT							1
#define M2_IDENTIFIANT							2
#define ERROR_IDENTIFIANT						3

#define FIFO_ERROR_CODE_TO_IHM_SIZE				10

/*%C NAND Flash State Running */ 
typedef enum
{
	USB_NAND_TRANSFER_IDLE = 0,
	USB_NAND_MONIT_TRANSFER_RUNNING,
	USB_NAND_TREND_TRANSFER_RUNNING
} e_USB_NAND_RUNNING ;


/******************************************************************************/
/*                   		EXTERNAL DECLARATION  			           				*/
/******************************************************************************/


#ifdef DECLARATION_DRIVER_USB_DATA_H

	#ifndef DRIVER_USB_DATA_H
	#define DRIVER_USB_DATA_H


 /* USB continuous record buffer definition with indexes */
  	UBYTE DRV_USB_Continuous_Record_Buffer[DRV_USB_CONTINUOUS_RECORD_BUFFER_SIZE];
	UWORD16 DRV_USB_Idx_Write = 0;
	UWORD16 DRV_USB_Idx_Read = 0;
	UWORD16 WriteBufferAuthorisation = FALSE ;


	e_USB_File_Settings Step_FileSetting = FileSettingNext ;
	e_USB_Transfer_Apply Step_UsbTransferApply 
												= Usb_FirstStep ;

	e_VentilState UsbMemoVentilState ;

	UBYTE USB_EventsPtrNumEventWrite = 0 ;

	UBYTE FifoErrorCodeToIHM	[FIFO_ERROR_CODE_TO_IHM_SIZE] ;
	UBYTE UsbPtrReadFifoErrorCodeToIHM = 0 ;
	UBYTE UsbPtrWriteFifoErrorCodeToIHM = 0 ;

 	UBYTE Tab_FileName 			[40] ;

	UBYTE SerialNumberAndDate	[End_of_e_usb_frame_serialNumberAndDate] ;

	UBYTE SerialNumber			[End_of_e_usb_frame_serialNumber] ;

	UBYTE DataSettings 			[End_Of_Table_Settings 
										+ End_of_e_usb_frame_setting
										- 1] ;

	UBYTE DataMonitoring			[End_Of_Table_Detailled_Monitoring
										+ USB_End_Of_Continuous_Frame
										- 1] ;

	UBYTE DataTrends				[End_Of_Table_Trends
										+ USB_End_Of_Continuous_Frame
										- 1] ;

	UBYTE DataEvents				[End_Of_Table_Events
										+ USB_End_Of_Continuous_Frame
										- 1] ;

	UBYTE DataCRC[USB_NB_DATA_CRC16];



	UBYTE PtrUsbNumEventsWrite = 0 ;
	UBYTE PtrUsbNumEventsRead = 0 ;
	UBYTE UsbBufferEmpty = FALSE ;

	UBYTE USB_EventsBuffer		[USB_EVENTS_BUFFER_SIZE]
										[End_Of_Table_Events];

	UWORD16 ReqNbBytes;
	UWORD16 FrameReadyToSend = TRUE ;
	UWORD16 DisplayErrorCodeFlag = FALSE ;
	UWORD16 UsbDetectedAKey = TRUE ;
	UWORD16 UsbDetectedTwoManyKey = TRUE ;
	UWORD16 UsbErrorDetectedFlag = FALSE ;
	UWORD16 UsbEventNumber = 1 ;
	UWORD16 UsbPreviousTwoKeyConnected = FALSE ;
	UWORD16 UsbEndOfCommand = FALSE ;
	UWORD16 UsbEraseCommand = FALSE ;
	UWORD16 EventsAuthorizationFlag = FALSE ;
	UWORD16 EndReadFlashEventFlag = FALSE ;
	UWORD16 UsbWriteSettingsApply = FALSE ;
	UWORD16 UsbFlashTrasnferRunning = 0 ;
	UWORD16 UsbFlashInUse = FALSE;
	UWORD16 UsbComputeCRC = 0 ;
	UWORD16 FirstRemaningTimeApproximation = TRUE ;
	
	UBYTE CurrentUsbKey = FALSE ;
	
	/*%C Adresse in EEP zone */
	UWORD16 *PtrAdresseSettingTable = 0 ;

	/*%C  Reading of Memory flash Writing index */
	UWORD16 xhuge *UsbAdressFlashEvent;
				 
	/*%C To previous Usb Key Full */
	UWORD32 UsbNbBytesWriteOnKey = 0 ;

	UWORD16 USB_CommandInProgress = FALSE;

	UWORD16 USB_ContinuousKeyFull = FALSE;

	UWORD16 USB_FileOpened = FALSE;

	UWORD16 USB_FileHour 	= 0;
	UWORD16 USB_FileMinute 	= 0;
	UWORD16 USB_FileSecond 	= 0;
	UWORD16 USB_FileYear 	= 0;
	UWORD16 USB_FileMonth	= 0;
	UWORD16 USB_FileDay		= 0;

/*********************************************************/
/*%C NAND Flash Interfacing 										*/
/*********************************************************/
	/*%C To Control Nand Flash Capacity*/
	UWORD32 NandFlashMonitoringCapacity = 0 ;
	UWORD32 NandFlashTrendCapacity = 0 ;

	/*%C To Control Bytes Write on Key to the Nand */
	UWORD32 NbBytesUsbWrittenFlashMonit = 0 ;

	/*%C Nb bytes to write on key */
	UWORD32 NbBytesMonitoringFlashMonitToWrite = 0 ;
	UWORD32 NbBytesMonitoringFlashTrendToWrite = 0 ;

/*********************************************************/



	/*Déclaration des 2 tableaux en XRAM1 */
	/* Keil  */
#ifndef _TASKING
   UBYTE sdata PEC_Emission 		[255];
	UBYTE sdata PEC_Reception 		[255];
	/* Tasking  */
#else
   UBYTE near PEC_Emission 		[255];
	UBYTE near PEC_Reception 		[255];
#endif

	#endif

#else

	#ifndef DRIVER_USB_DATA_H
	#define DRIVER_USB_DATA_H

 	/* USB continuous record buffer definition with indexes */
  	extern UBYTE DRV_USB_Continuous_Record_Buffer[];
	extern UWORD16 DRV_USB_Idx_Write ;
	extern UWORD16 DRV_USB_Idx_Read ;
	extern UWORD16 WriteBufferAuthorisation ;

	extern e_USB_File_Settings Step_FileSetting ;

	extern e_USB_Transfer_Apply Step_UsbTransferApply ;

	extern e_VentilState UsbMemoVentilState ;

	extern UBYTE USB_EventsPtrNumEventWrite ;

	extern UBYTE FifoErrorCodeToIHM		[] ;
	extern UBYTE UsbPtrReadFifoErrorCodeToIHM ;
	extern UBYTE UsbPtrWriteFifoErrorCodeToIHM ;

							 
	extern UBYTE Tab_FileName			[] ;

	extern UBYTE SerialNumberAndDate	[] ;

	extern UBYTE SerialNumber			[] ;

	extern UBYTE DataSettings 			[] ;

	extern UBYTE DataMonitoring		[] ;

	extern UBYTE DataTrends				[] ;

	extern UBYTE DataEvents				[] ;

	extern UBYTE DataCRC					[];
	
	extern UBYTE PtrUsbNumEventsWrite ;
	extern UBYTE PtrUsbNumEventsRead ;
	extern UBYTE EntireEventsMemoryTransfer ;
	extern UBYTE UsbBufferEmpty ;

	extern UBYTE USB_EventsBuffer	[USB_EVENTS_BUFFER_SIZE]
											[End_Of_Table_Events];

	extern UWORD16 ReqNbBytes;
	extern UWORD16 FrameReadyToSend ;
	extern UWORD16 DisplayErrorCodeFlag ;
	extern UWORD16 UsbDetectedAKey ;
	extern UWORD16 UsbDetectedTwoManyKey ;
	extern UWORD16 UsbErrorDetectedFlag ;
	extern UWORD16 UsbEventNumber ;
	extern UWORD16 UsbPreviousTwoKeyConnected ;
	extern UWORD16 UsbEndOfCommand ;
	extern UWORD16 UsbEraseCommand ;
	extern UWORD16 EventsAuthorizationFlag ;
	extern UWORD16 EndReadFlashEventFlag ;
	extern UWORD16 UsbComputeCRC ;
	extern UWORD16 UsbWriteSettingsApply ;
	extern UWORD16 UsbFlashInUse;
	extern UWORD16 UsbFlashTrasnferRunning ;
	extern UWORD16 FirstRemaningTimeApproximation ;
	
	extern UBYTE CurrentUsbKey ;

	/*%C Adresse in EEP zone */
	extern UWORD16 *PtrAdresseSettingTable ;

	/*%C  Reading of Memory flash Writing index */
	extern UWORD16 xhuge *UsbAdressFlashEvent;

	/*%C To previous Usb Key Full */
	extern UWORD32 UsbNbBytesWriteOnKey ;

	extern UWORD16 USB_CommandInProgress;

	extern UWORD16 USB_ContinuousKeyFull;

	extern UWORD16 USB_FileOpened;

	extern UWORD16 USB_FileHour 	;
	extern UWORD16 USB_FileMinute 	;
	extern UWORD16 USB_FileSecond 	;
	extern UWORD16 USB_FileYear 	;
	extern UWORD16 USB_FileMonth	;
	extern UWORD16 USB_FileDay		;

/*********************************************************/
/*%C NAND Flash Interfacing 										*/
/*********************************************************/
	/*%C To Control Nand Flash Capacity*/
	extern UWORD32 NandFlashMonitoringCapacity ;
	extern UWORD32 NandFlashTrendCapacity ;

	/*%C To Control Bytes Write on Key to the Nand */
	extern UWORD32 NbBytesUsbWrittenFlashMonit ;

	/*%C Nb bytes to write on key */
	extern UWORD32 NbBytesMonitoringFlashMonitToWrite ;
	extern UWORD32 NbBytesMonitoringFlashTrendToWrite ;

/*********************************************************/



	/* Keil  */
#ifndef _TASKING
	extern UBYTE sdata  PEC_Emission 	[];
	extern UBYTE sdata  PEC_Reception 	[];
	/* Tasking  */
#else
	extern UBYTE near PEC_Emission 		[];
	extern UBYTE near PEC_Reception 		[];
#endif


	#endif

#endif
