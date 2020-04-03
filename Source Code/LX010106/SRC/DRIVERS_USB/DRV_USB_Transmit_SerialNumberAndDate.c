/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Transmit_SerialNumberAndDate.c                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/

#include "define.h"
#include "typedef.h"
#include "enum.h"
#include "DB_RTC.h"
#include "Driver_USB_Data.h"
#include "DRV_USB_Transmit_SerialNumberAndDate.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_USB_Transmit_SerialNumberAndDate(void)
{

/******************************************************************************/
/*%C Variables 																					*/
/******************************************************************************/

	UWORD16 Compute_U16 = 0 ;
	
	/*%C Reset the CRC Compute */
	UsbComputeCRC = 0 ;
	
	/*%C Serial Number */


	Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_1);
	SerialNumberAndDate[USB_SETTING_SERIAL_NUMBER_1] = (UBYTE)(Compute_U16 >>8) ;
	SerialNumberAndDate[USB_SETTING_SERIAL_NUMBER_2] = (UBYTE)(Compute_U16) ;

	Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_2); 
	SerialNumberAndDate[USB_SETTING_SERIAL_NUMBER_3] = (UBYTE)(Compute_U16 >>8) ;
	SerialNumberAndDate[USB_SETTING_SERIAL_NUMBER_4] = (UBYTE)(Compute_U16) ;

	Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_3);
	SerialNumberAndDate[USB_SETTING_SERIAL_NUMBER_5] = (UBYTE)(Compute_U16 >>8) ;
	SerialNumberAndDate[USB_SETTING_SERIAL_NUMBER_6] = (UBYTE)(Compute_U16) ;

	Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_4);
	SerialNumberAndDate[USB_SETTING_SERIAL_NUMBER_7] = (UBYTE)(Compute_U16 >>8) ;
	SerialNumberAndDate[USB_SETTING_SERIAL_NUMBER_8] = (UBYTE)(Compute_U16) ;

	Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_5);
	SerialNumberAndDate[USB_SETTING_SERIAL_NUMBER_9] = (UBYTE)(Compute_U16 >>8) ;
	SerialNumberAndDate[USB_SETTING_SERIAL_NUMBER_10] = (UBYTE)(Compute_U16) ;

	Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_6);
	SerialNumberAndDate[USB_SETTING_SERIAL_NUMBER_11] = (UBYTE)(Compute_U16 >>8);
	SerialNumberAndDate[USB_SETTING_SERIAL_NUMBER_12] = (UBYTE)(Compute_U16) ;


	/*%C Insert Date */
	SerialNumberAndDate[USB_SETTING_DATE_YEAR]
							= (UBYTE)DB_RTCRead(DB_RTC_YEAR_U16) ;
	SerialNumberAndDate[USB_SETTING_DATE_MONTH]
							= (UBYTE)DB_RTCRead(DB_RTC_MONTH_U16) ;
	SerialNumberAndDate[USB_SETTING_DATE_DAY]
							= (UBYTE)DB_RTCRead(DB_RTC_DAY_U16) ;
	SerialNumberAndDate[USB_SETTING_DATE_HOUR]
							= (UBYTE)DB_RTCRead(DB_RTC_HOUR_U16) ;	 
	SerialNumberAndDate[USB_SETTING_DATE_MINUTE]
							= (UBYTE)DB_RTCRead(DB_RTC_MINUTE_U16) ;
	SerialNumberAndDate[USB_SETTING_DATE_SECOND]
							= (UBYTE)DB_RTCRead(DB_RTC_SECOND_U16) ;
	/*%C CRC16 Compute */
	UsbComputeCRC =  CRC16_TableCompute
					(
					(UWORD16)USB_SETTING_SERIAL_NUMBER_1,
					(UWORD16)End_of_e_usb_frame_serialNumberAndDate,
					SerialNumberAndDate,
					UsbComputeCRC );

}