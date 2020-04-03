/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Transmit_Trend.h  									  				*/
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

#ifndef DRV_USB_TRANSMIT_TREND_H
#define DRV_USB_TRANSMIT_TREND_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/

	extern UWORD16 DB_RTCRead(e_DB_RTC Id);
	extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
	extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
	extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
	extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
													UWORD16 StopIndex,
													UBYTE* TransmitArray, 
													UWORD16 Compute_CRC);


#endif
