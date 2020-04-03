/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_WriteMonitoringFlashMonit.h	 									*/
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

#ifndef DRV_USB_WRITEMONITORINGFLASHMONIT_H
#define DRV_USB_WRITEMONITORINGFLASHMONIT_H


/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                    			*/
/******************************************************************************/

	/*%C Usb Function */
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

 	extern UWORD16 DB_RTCRead(e_DB_RTC Id);

 #endif