/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Launch.h 																*/
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

#ifndef DRV_USB_LAUNCH_H
#define DRV_USB_LAUNCH_H


/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                    			*/
/******************************************************************************/

	/*%C Select the bridge	*/
	extern void DRV_OutputPort(e_OUTPUT_NAME _Port, UWORD16 _Value);
	
	/*%C Usb Init Function */
	extern void DRV_USB_Init(void);


	/*%C Usb Function */
	extern void DRV_USB_AskKeyConnected(UBYTE MsNb);
	extern void DRV_USB_GetFreeSpace(UBYTE MsNb);
	extern void DRV_USB_EntireEraseMemoryStick(UBYTE MsNb);
	extern void DRV_USB_CloseFile(UBYTE MsNb);
	extern void DRV_USB_Send_Frame(void);
	extern void DRV_USB_CheckReplyFrame(void);
	extern void DRV_USB_WriteAtTheEndOfFile(UBYTE MsNb , UBYTE* Adr_DataToWrite
															, UWORD16 NbDataToWrite);


	/*%C Usb Read Continuous Frames */
	extern void DRV_USB_ReadWriteSettings(void);
	extern void DRV_USB_WriteContinuousRecording(void);
	extern void DRV_USB_WriteEventFlash(void);
 	extern void DRV_USB_WriteMonitoringFlashMonit(void);
	extern void DRV_USB_WriteTrendsFlashMonit(void);
	extern void DRV_USB_WriteInContinuousRecordBuffer(void);
	extern void DRV_USB_Transmit_Monitoring(UWORD16 DetailledDataType);
	extern void DRV_USB_Transmit_Monitoring(UWORD16 DetailledDataType);




	/*%C Usb Busy Function */
	extern UBYTE DRV_USB_WaitBusy(UBYTE State);


	/*%C Usb Acces to DataBase */
	extern void DB_UsbWrite(e_DB_USB Id, UWORD16 Value);
	extern UWORD16 DB_UsbRead(e_DB_USB Id);
	extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
	extern void DB_ControlWrite(e_DB_CONTROL Id , UWORD16 Value);
	extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);


	/*%C Usb Timer Function */
	extern void TIM_StartDecounter(e_TIM_TABLE_ID,UWORD16);
	extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table); 
	extern void TIM_StartMinuteDecounter(e_TIM_MINUTE_TABLE_ID offset_table,UWORD32 value,e_BOOL autoreload);
	extern UWORD32 TIM_ReadMinuteDecounterValue(e_TIM_MINUTE_TABLE_ID offset_table);

	/*%C Buzzer Sound */
	extern void DRV_Buz_Sound(e_TYPE_SOUND sound , e_NUMBER_BUZ NumBuzzer);

	/*%C Event Management */
	extern void DB_EventMngt (UWORD16 Value);
	extern void DRV_USB_Transmit_Events(UBYTE EntireEventsMemoryTransfer);

	
	/*%C FIFO error code management */
	extern void DRV_USB_ReadFifo(void);
	extern void DRV_USB_WriteFifo(void);


 #endif