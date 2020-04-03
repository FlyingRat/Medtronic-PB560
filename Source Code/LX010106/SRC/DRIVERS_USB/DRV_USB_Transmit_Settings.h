/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Transmit_Settings.h												*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  																			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE																	*/
/*%O Output Parameter : NONE       															*/
/******************************************************************************/

#ifndef DRV_USB_TRANSMIT_SETTINGS_H
#define DRV_USB_TRANSMIT_SETTINGS_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/

	extern void DB_UsbWrite(e_DB_USB Id, UWORD16 Value);
	extern UWORD16 DB_UsbRead(e_DB_USB Id);

	extern UWORD16 DB_RTCRead(e_DB_RTC Id);
	extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
	extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
	extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

	extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
	extern void DB_CurrentWrite(e_DB_ADJUST_CURRENT Id, UWORD16 Value);
	extern UWORD16 DB_ConfigWrite(e_DB_CONFIG Id, UWORD16 Value);
	
	extern void DB_WriteDataInEepAndRam(UWORD16 xhuge *data_address,
													UWORD16 value);

	extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
													UWORD16 StopIndex,
													UBYTE* TransmitArray,
													UWORD16 Compute_CRC);


#endif
