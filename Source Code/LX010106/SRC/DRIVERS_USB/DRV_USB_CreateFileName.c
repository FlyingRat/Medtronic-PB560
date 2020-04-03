/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_CreateFileName.c	 												*/
/* 																									*/
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
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Driver_USB_Data.h"
#include "DRV_USB_CreateFileName.h"

/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/
void DRV_USB_CreateFileName(UBYTE FileType)
{
/******************************************************************************/
/*%C Local variables 																			*/
/******************************************************************************/
	
	UWORD16 Compute_U16 = 0 ;

	UWORD16 SeriaNumberData_1 = 0;
	UWORD16 SeriaNumberData_2 = 0;
	UWORD16 SeriaNumberData_3 = 0;
	UWORD16 SeriaNumberData_4 = 0;
	UWORD16 SeriaNumberData_5 = 0;
	UWORD16 SeriaNumberData_6 = 0;
	UWORD16 SeriaNumberData_7 = 0;
	UWORD16 SeriaNumberData_8 = 0;
	UWORD16 SeriaNumberData_9 = 0;
	UWORD16 SeriaNumberData_10 = 0;
	UWORD16 SeriaNumberData_11 = 0;
	UWORD16 SeriaNumberData_12 = 0;

	UWORD16 Second = 0 ;
	UWORD16 Minute = 0 ;
	UWORD16 Hour = 0 ;
	UWORD16 Day = 0 ;
	UWORD16 Month = 0 ;
	UWORD16 Year = 0 ;

	UWORD16 Hour_Msb = 0 ;
	UWORD16 Hour_Lsb = 0 ;

	UWORD16 Minute_Msb = 0 ;
	UWORD16 Minute_Lsb = 0 ;

	UWORD16 Second_Msb = 0 ;
	UWORD16 Second_Lsb = 0 ;

	UWORD16 Year_Msb = 0 ;
	UWORD16 Year_Lsb = 0 ;

	UWORD16 Month_Msb = 0 ;
	UWORD16 Month_Lsb = 0 ;

	UWORD16 Day_Msb = 0 ;
	UWORD16 Day_Lsb = 0 ;

/******************************************************************************/
/*%C Read the Serial Number base value*/
/******************************************************************************/
	Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_1);
	SeriaNumberData_1 = (UBYTE)(Compute_U16 >>8) ;
	SeriaNumberData_2 = (UBYTE)(Compute_U16) ;

	Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_2); 
	SeriaNumberData_3 = (UBYTE)(Compute_U16 >>8) ;
	SeriaNumberData_4 = (UBYTE)(Compute_U16) ;

	Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_3);
	SeriaNumberData_5 = (UBYTE)(Compute_U16 >>8) ;
	SeriaNumberData_6 = (UBYTE)(Compute_U16) ;

	Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_4);
	SeriaNumberData_7 = (UBYTE)(Compute_U16 >>8) ;
	SeriaNumberData_8 = (UBYTE)(Compute_U16) ;

	Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_5);
	SeriaNumberData_9 = (UBYTE)(Compute_U16 >>8) ;
	SeriaNumberData_10 = (UBYTE)(Compute_U16) ;

	Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_6);
	SeriaNumberData_11 = (UBYTE)(Compute_U16 >>8) ;
	SeriaNumberData_12 = (UBYTE)(Compute_U16) ;

/******************************************************************************/
/*%C Read the RTC base value  																*/
/******************************************************************************/
	Hour_Msb = (USB_FileHour / 10) + 0x30 ;
	Hour_Lsb = (USB_FileHour % 10) + 0x30 ;


	Minute_Msb = (USB_FileMinute / 10) + 0x30 ;
	Minute_Lsb = (USB_FileMinute % 10) + 0x30 ;


	Second_Msb = (USB_FileSecond / 10) + 0x30 ;
	Second_Lsb = (USB_FileSecond % 10) + 0x30 ;


	Year_Msb = (USB_FileYear / 10) + 0x30 ;
	Year_Lsb = (USB_FileYear % 10) + 0x30 ;


	Month_Msb = (USB_FileMonth / 10) + 0x30 ;
	Month_Lsb = (USB_FileMonth % 10) + 0x30 ;


	Day_Msb = (USB_FileDay / 10) + 0x30 ;
	Day_Lsb = (USB_FileDay % 10) + 0x30 ;


/******************************************************************************/
/*%C Select File type to build the file Name												*/
/******************************************************************************/
	switch(FileType)
	{
		case SettingsType :
		{
			Tab_FileName[0] = 'S' ;
			Tab_FileName[1] = 'P' ;
			Tab_FileName[2] = 'R' ;
			Tab_FileName[3] = '_' ;
			Tab_FileName[4] 	= (UBYTE)SeriaNumberData_1 ;
			Tab_FileName[5] 	= (UBYTE)SeriaNumberData_2 ;
			Tab_FileName[6] 	= (UBYTE)SeriaNumberData_3 ;
			Tab_FileName[7] 	= (UBYTE)SeriaNumberData_4 ;
			Tab_FileName[8] 	= (UBYTE)SeriaNumberData_5 ;
			Tab_FileName[9] 	= (UBYTE)SeriaNumberData_6 ;
			Tab_FileName[10] 	= (UBYTE)SeriaNumberData_7 ;
			Tab_FileName[11] 	= (UBYTE)SeriaNumberData_8 ;
			Tab_FileName[12] 	= (UBYTE)SeriaNumberData_9 ;
			Tab_FileName[13] 	= (UBYTE)SeriaNumberData_10 ;
			Tab_FileName[14] 	= (UBYTE)SeriaNumberData_11 ;
			Tab_FileName[15] 	= (UBYTE)SeriaNumberData_12 ;
			Tab_FileName[16] = '_' ;
			Tab_FileName[17] = (UBYTE)Year_Msb ;
			Tab_FileName[18] = (UBYTE)Year_Lsb ;
			Tab_FileName[19] = (UBYTE)Month_Msb ;
			Tab_FileName[20] = (UBYTE)Month_Lsb ;
			Tab_FileName[21] = (UBYTE)Day_Msb ;
			Tab_FileName[22] = (UBYTE)Day_Lsb ;
			Tab_FileName[23] = '_' ;
			Tab_FileName[24] = (UBYTE)Hour_Msb ;
			Tab_FileName[25] = (UBYTE)Hour_Lsb ;
			Tab_FileName[26] = (UBYTE)Minute_Msb ;
			Tab_FileName[27] = (UBYTE)Minute_Lsb ;
			Tab_FileName[28] = (UBYTE)Second_Msb ;
			Tab_FileName[29] = (UBYTE)Second_Lsb ;
			Tab_FileName[30] = '.' ;
			Tab_FileName[31] = 's' ;
			Tab_FileName[32] = 'p' ;
			Tab_FileName[33] = 'r' ;
			Tab_FileName[34] = '\0';
			break;
		}
 		case ContinuousRecordingType :
		{
			Tab_FileName[0] = 'M' ;
			Tab_FileName[1] = 'T' ;
			Tab_FileName[2] = 'C' ;
			Tab_FileName[3] = '_' ;
			Tab_FileName[4] 	= (UBYTE)SeriaNumberData_1 ;
			Tab_FileName[5] 	= (UBYTE)SeriaNumberData_2 ;
			Tab_FileName[6] 	= (UBYTE)SeriaNumberData_3 ;
			Tab_FileName[7] 	= (UBYTE)SeriaNumberData_4 ;
			Tab_FileName[8] 	= (UBYTE)SeriaNumberData_5 ;
			Tab_FileName[9] 	= (UBYTE)SeriaNumberData_6 ;
			Tab_FileName[10] 	= (UBYTE)SeriaNumberData_7 ;
			Tab_FileName[11] 	= (UBYTE)SeriaNumberData_8 ;
			Tab_FileName[12] 	= (UBYTE)SeriaNumberData_9 ;
			Tab_FileName[13] 	= (UBYTE)SeriaNumberData_10 ;
			Tab_FileName[14] 	= (UBYTE)SeriaNumberData_11 ;
			Tab_FileName[15] 	= (UBYTE)SeriaNumberData_12 ;
			Tab_FileName[16] = '_' ;
			Tab_FileName[17] = (UBYTE)Year_Msb ;
			Tab_FileName[18] = (UBYTE)Year_Lsb ;
			Tab_FileName[19] = (UBYTE)Month_Msb ;
			Tab_FileName[20] = (UBYTE)Month_Lsb ;
			Tab_FileName[21] = (UBYTE)Day_Msb ;
			Tab_FileName[22] = (UBYTE)Day_Lsb ;
			Tab_FileName[23] = '_' ;
			Tab_FileName[24] = (UBYTE)Hour_Msb ;
			Tab_FileName[25] = (UBYTE)Hour_Lsb ;
			Tab_FileName[26] = (UBYTE)Minute_Msb ;
			Tab_FileName[27] = (UBYTE)Minute_Lsb ;
			Tab_FileName[28] = (UBYTE)Second_Msb ;
			Tab_FileName[29] = (UBYTE)Second_Lsb ;
			Tab_FileName[30] = '.' ;
			Tab_FileName[31] = 'm' ;
			Tab_FileName[32] = 't' ;
			Tab_FileName[33] = 'c' ;
			Tab_FileName[34] = '\0';
			break;
		}

		case MonitoringTransferType :
		{
			Tab_FileName[0] = 'D' ;
			Tab_FileName[1] = 'T' ;
			Tab_FileName[2] = 'S' ;
			Tab_FileName[3] = '_' ;
			Tab_FileName[4] 	= (UBYTE)SeriaNumberData_1 ;
			Tab_FileName[5] 	= (UBYTE)SeriaNumberData_2 ;
			Tab_FileName[6] 	= (UBYTE)SeriaNumberData_3 ;
			Tab_FileName[7] 	= (UBYTE)SeriaNumberData_4 ;
			Tab_FileName[8] 	= (UBYTE)SeriaNumberData_5 ;
			Tab_FileName[9] 	= (UBYTE)SeriaNumberData_6 ;
			Tab_FileName[10] 	= (UBYTE)SeriaNumberData_7 ;
			Tab_FileName[11] 	= (UBYTE)SeriaNumberData_8 ;
			Tab_FileName[12] 	= (UBYTE)SeriaNumberData_9 ;
			Tab_FileName[13] 	= (UBYTE)SeriaNumberData_10 ;
			Tab_FileName[14] 	= (UBYTE)SeriaNumberData_11 ;
			Tab_FileName[15] 	= (UBYTE)SeriaNumberData_12 ;
			Tab_FileName[16] = '_' ;
			Tab_FileName[17] = (UBYTE)Year_Msb ;
			Tab_FileName[18] = (UBYTE)Year_Lsb ;
			Tab_FileName[19] = (UBYTE)Month_Msb ;
			Tab_FileName[20] = (UBYTE)Month_Lsb ;
			Tab_FileName[21] = (UBYTE)Day_Msb ;
			Tab_FileName[22] = (UBYTE)Day_Lsb ;
			Tab_FileName[23] = '_' ;
			Tab_FileName[24] = (UBYTE)Hour_Msb ;
			Tab_FileName[25] = (UBYTE)Hour_Lsb ;
			Tab_FileName[26] = (UBYTE)Minute_Msb ;
			Tab_FileName[27] = (UBYTE)Minute_Lsb ;
			Tab_FileName[28] = (UBYTE)Second_Msb ;
			Tab_FileName[29] = (UBYTE)Second_Lsb ;
			Tab_FileName[30] = '.' ;
			Tab_FileName[31] = 'd' ;
			Tab_FileName[32] = 't' ;
			Tab_FileName[33] = 's' ;
			Tab_FileName[34] = '\0';
			break;
		}
		case TrendsTransferType :
		{
			Tab_FileName[0] = 'T' ;
			Tab_FileName[1] = 'N' ;
			Tab_FileName[2] = 'D' ;
			Tab_FileName[3] = '_' ;
			Tab_FileName[4] 	= (UBYTE)SeriaNumberData_1 ;
			Tab_FileName[5] 	= (UBYTE)SeriaNumberData_2 ;
			Tab_FileName[6] 	= (UBYTE)SeriaNumberData_3 ;
			Tab_FileName[7] 	= (UBYTE)SeriaNumberData_4 ;
			Tab_FileName[8] 	= (UBYTE)SeriaNumberData_5 ;
			Tab_FileName[9] 	= (UBYTE)SeriaNumberData_6 ;
			Tab_FileName[10] 	= (UBYTE)SeriaNumberData_7 ;
			Tab_FileName[11] 	= (UBYTE)SeriaNumberData_8 ;
			Tab_FileName[12] 	= (UBYTE)SeriaNumberData_9 ;
			Tab_FileName[13] 	= (UBYTE)SeriaNumberData_10 ;
			Tab_FileName[14] 	= (UBYTE)SeriaNumberData_11 ;
			Tab_FileName[15] 	= (UBYTE)SeriaNumberData_12 ;
			Tab_FileName[16] = '_' ;
			Tab_FileName[17] = (UBYTE)Year_Msb ;
			Tab_FileName[18] = (UBYTE)Year_Lsb ;
			Tab_FileName[19] = (UBYTE)Month_Msb ;
			Tab_FileName[20] = (UBYTE)Month_Lsb ;
			Tab_FileName[21] = (UBYTE)Day_Msb ;
			Tab_FileName[22] = (UBYTE)Day_Lsb ;
			Tab_FileName[23] = '_' ;
			Tab_FileName[24] = (UBYTE)Hour_Msb ;
			Tab_FileName[25] = (UBYTE)Hour_Lsb ;
			Tab_FileName[26] = (UBYTE)Minute_Msb ;
			Tab_FileName[27] = (UBYTE)Minute_Lsb ;
			Tab_FileName[28] = (UBYTE)Second_Msb ;
			Tab_FileName[29] = (UBYTE)Second_Lsb ;
			Tab_FileName[30] = '.' ;
			Tab_FileName[31] = 't' ;
			Tab_FileName[32] = 'n' ;
			Tab_FileName[33] = 'd' ;
			Tab_FileName[34] = '\0';
			break;
		}
		case EventsTransferType :
		{
			Tab_FileName[0] = 'E' ;
			Tab_FileName[1] = 'V' ;
			Tab_FileName[2] = 'N' ;
			Tab_FileName[3] = '_' ;
			Tab_FileName[4] 	= (UBYTE)SeriaNumberData_1 ;
			Tab_FileName[5] 	= (UBYTE)SeriaNumberData_2 ;
			Tab_FileName[6] 	= (UBYTE)SeriaNumberData_3 ;
			Tab_FileName[7] 	= (UBYTE)SeriaNumberData_4 ;
			Tab_FileName[8] 	= (UBYTE)SeriaNumberData_5 ;
			Tab_FileName[9] 	= (UBYTE)SeriaNumberData_6 ;
			Tab_FileName[10] 	= (UBYTE)SeriaNumberData_7 ;
			Tab_FileName[11] 	= (UBYTE)SeriaNumberData_8 ;
			Tab_FileName[12] 	= (UBYTE)SeriaNumberData_9 ;
			Tab_FileName[13] 	= (UBYTE)SeriaNumberData_10 ;
			Tab_FileName[14] 	= (UBYTE)SeriaNumberData_11 ;
			Tab_FileName[15] 	= (UBYTE)SeriaNumberData_12 ;
			Tab_FileName[16] = '_' ;
			Tab_FileName[17] = (UBYTE)Year_Msb ;
			Tab_FileName[18] = (UBYTE)Year_Lsb ;
			Tab_FileName[19] = (UBYTE)Month_Msb ;
			Tab_FileName[20] = (UBYTE)Month_Lsb ;
			Tab_FileName[21] = (UBYTE)Day_Msb ;
			Tab_FileName[22] = (UBYTE)Day_Lsb ;
			Tab_FileName[23] = '_' ;
			Tab_FileName[24] = (UBYTE)Hour_Msb ;
			Tab_FileName[25] = (UBYTE)Hour_Lsb ;
			Tab_FileName[26] = (UBYTE)Minute_Msb ;
			Tab_FileName[27] = (UBYTE)Minute_Lsb ;
			Tab_FileName[28] = (UBYTE)Second_Msb ;
			Tab_FileName[29] = (UBYTE)Second_Lsb ;
			Tab_FileName[30] = '.' ;
			Tab_FileName[31] = 'e' ;
			Tab_FileName[32] = 'v' ;
			Tab_FileName[33] = 'n' ;
			Tab_FileName[34] = '\0';
			break;
		}

		default : 
		{ 
			break; 
		}
	}
}