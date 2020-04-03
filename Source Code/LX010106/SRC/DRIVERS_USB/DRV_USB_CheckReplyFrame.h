/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_CheckReplyFrame.h 													*/
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

#ifndef DRV_USB_CHECKREPLYFRAME_H
#define DRV_USB_CHECKREPLYFRAME_H


/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                    			*/
/******************************************************************************/

	extern void DRV_USB_CloseFile(UBYTE MsNb);
	extern void DRV_USB_GetDelayedStatus(UBYTE MsNb) ;
	extern void DRV_USB_Transmit_Settings(UWORD16 UsbTransferOn);
	extern UWORD16 DRV_USB_VerifyCompatibility(void);


	/*%C Usb Acces to DataBase */
	extern void DB_UsbWrite(e_DB_USB Id, UWORD16 Value);
	extern UWORD16 DB_UsbRead(e_DB_USB Id);


	/*%C Acces to DataBase */
	extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
	extern UWORD16 DB_ConfigWrite(e_DB_CONFIG Id , UWORD16 Value);
			  
	extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
	extern void DB_ControlWrite(e_DB_CONTROL Id , UWORD16 Value);



	extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
											UWORD16 StopIndex,
											UBYTE* TransmitArray,
											UWORD16 Compute_CRC);

   	/*%C Event Management */
	extern void DB_EventMngt (UWORD16 Value);
 #endif