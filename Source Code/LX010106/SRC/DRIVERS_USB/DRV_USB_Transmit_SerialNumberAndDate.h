/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Transmit_SerialNumberAndDate.h									*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  																			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE       															*/
/******************************************************************************/


#ifndef DRV_USB_TRANSMIT_SERIALNUMBERANDDATE_H
#define DRV_USB_TRANSMIT_SERIALNUMBERANDDATE_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/

extern UWORD16 DB_RTCRead(e_DB_RTC Id);
extern UWORD16 DB_VersionRead(e_DB_VERSION Id);
extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
										UWORD16 StopIndex,
										UBYTE* TransmitArray,
										UWORD16 Compute_CRC);


#endif