/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_ReadWriteSettings.h 												*/
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

#ifndef DRV_USB_READWRITESETTINGS_H
#define DRV_USB_READWRITESETTINGS_H


/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                    			*/
/******************************************************************************/


	/*%C Usb Function */
	extern void DRV_USB_OpenFile(UBYTE MsNb , UBYTE* Adr_FileName );
	extern void DRV_USB_CloseFile(UBYTE MsNb);
	extern void DRV_USB_ReadTheFile(UBYTE MsNb, UWORD16 NbBytesToRead);
	extern void DRV_USB_Transmit_SerialNumberAndDate(void);
	extern void DRV_USB_CreateFile(UBYTE MsNb , UBYTE* Adr_FileName) ;
	extern void DRV_USB_ReadCurrentDirectory(UBYTE MsNb , UBYTE FirstOrNext) ;
	extern void DRV_USB_ChangeFileModificationDateAndTime(UBYTE MsNb);
	extern void DRV_USB_CreateFileName(UBYTE FileType);
	extern void DRV_USB_WriteAtTheEndOfFile(UBYTE MsNb , UBYTE* Adr_DataToWrite
															, UWORD16 NbDataToWrite);
	extern void DRV_USB_WriteStartAtAnIndex(	UBYTE MsNb ,
															UBYTE* Adr_DataToWrite ,
															UWORD16 NbDataToWrite ,
															UWORD32 Index) ;



	/*%C Usb build Settings Frames */
	extern void DRV_USB_Transmit_Settings(UWORD16 UsbTransferOn);

	/*%C Usb Acces to DataBase */
	extern void DB_UsbWrite(e_DB_USB Id, UWORD16 Value);
	extern UWORD16 DB_UsbRead(e_DB_USB Id); 

  	/*%C Event Management */
	extern void DB_EventMngt (UWORD16 Value);

 #endif