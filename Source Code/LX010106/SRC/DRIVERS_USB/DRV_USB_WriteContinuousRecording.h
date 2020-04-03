/******************************************************************************/
/*                                                                            */
/* Project N�  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_WriteContinuousRecording.h	 									*/
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

#ifndef DRV_USB_WRITECONTINUOUSRECORDING_H
#define DRV_USB_WRITECONTINUOUSRECORDING_H


/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                    			*/
/******************************************************************************/

	extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

	/*%C Usb Function */
	extern void DRV_USB_AskKeyConnected(UBYTE MsNb);
	extern void DRV_USB_CloseFile(UBYTE MsNb);
	extern void DRV_USB_WriteAtTheEndOfFile(UBYTE MsNb , UBYTE* Adr_DataToWrite
															, UWORD16 NbDataToWrite);
	extern void DRV_USB_CreateFile(UBYTE MsNb , UBYTE* Adr_FileName) ;
	extern void DRV_USB_CreateFileName(UBYTE FileType);
	extern void DRV_USB_Transmit_SerialNumber(void);


	/*%C Usb Read Continuous Frames */
	extern void DRV_USB_Transmit_Monitoring(UWORD16 DetailledDataType);
	extern void DRV_USB_Transmit_Trend(void);
	extern void DRV_USB_Transmit_Events(UBYTE EntireEventsMemoryTransfer);

	/*%C Usb Acces to DataBase */
	extern void DB_UsbWrite(e_DB_USB Id, UWORD16 Value);
	extern UWORD16 DB_UsbRead(e_DB_USB Id);


	/*%C Usb Timer Function */
	extern void TIM_StartDecounter(e_TIM_TABLE_ID,UWORD16);
	extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table); 
	extern void TIM_StartMinuteDecounter(e_TIM_MINUTE_TABLE_ID offset_table,UWORD32 value,e_BOOL autoreload);
	extern UWORD32 TIM_ReadMinuteDecounterValue(e_TIM_MINUTE_TABLE_ID offset_table);

	/*%C Event Management */
	extern void DB_EventMngt (UWORD16 Value);

	extern UWORD16 DB_RTCRead(e_DB_RTC Id);
	


 #endif