/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_CreateFile.c															*/
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
#include "DB_RTC.h"
#include "Driver_USB_Data.h"
#include "DRV_USB_CreateFile.h"

/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/
void DRV_USB_CreateFile(UBYTE MsNb , UBYTE* Adr_FileName)
{
/******************************************************************************/
/*%C Local variables 																			*/
/******************************************************************************/

	UWORD16 Size_Tab_FileName ;
	UWORD16 HeaderCheck = 0 ;
	UWORD16 RequestHeader = 0 ;
	UWORD16 CheckSum = 0 ;
	UBYTE* CurrentByte = Adr_FileName;
	UWORD16 Loop_CKS = 0 ;
	UWORD16 Loop_Data = 0 ;

	UWORD16 Second = 0 ;
	UWORD16 Minute = 0 ;
	UWORD16 Hour = 0 ;
	UWORD16 Day = 0 ;
	UWORD16 Month = 0 ;
	UWORD16 Year = 0 ;

	UWORD16 CreateFile_Date = 0;
	UWORD16 CreateFile_Time = 0;

	USB_FileOpened = TRUE;

/******************************************************************************/
/*%C Read the RTC base value  																*/
/******************************************************************************/
	Hour 		= (UBYTE)DB_RTCRead(DB_RTC_HOUR_U16) ;
	Minute 	= (UBYTE)DB_RTCRead(DB_RTC_MINUTE_U16) ;
	Second 	= (UBYTE)DB_RTCRead(DB_RTC_SECOND_U16) ;

	Year 		= (UBYTE)DB_RTCRead(DB_RTC_YEAR_U16) ;
	Month		= (UBYTE)DB_RTCRead(DB_RTC_MONTH_U16) ;
 	Day		= (UBYTE)DB_RTCRead(DB_RTC_DAY_U16) ;


/******************************************************************************/
/*%C Compute the file name size 																*/
/******************************************************************************/
	Size_Tab_FileName = 0;

	while((*CurrentByte) != '\0' && Size_Tab_FileName < 40)
	{
		Size_Tab_FileName = Size_Tab_FileName + 1 ;
		CurrentByte = CurrentByte + 1 ;
	}

/******************************************************************************/
/*%C Build the time and date creation file 												*/
/******************************************************************************/
	CreateFile_Time = 	((Hour << 11) & 0xF800)
							|	((Minute << 5) & 0x07E0) 
							|	((Second >> 2 ) & 0x001F) ;

	CreateFile_Date = 	(((Year + 20) << 9) & 0xFE00)
							|	((Month << 5) & 0x01E0)
							|	((Day) & 0x001F) ;



/******************************************************************************/
/*%C Compute the request header 																*/
/******************************************************************************/

	/*%C Compute the number of bytes in frame 											*/
	/*%C Req_NbBytes field holds the total length of the Request Frame 			*/
	/*%C in bytes, header included.															*/
	ReqNbBytes = 		HEADER_SIZE
						+	CMD_SIZE
						+	MSNB_SIZE
						+	CREATION_TIME
						+ 	CREATION_DATE
						+	Size_Tab_FileName
						+	CHECKSUM_SIZE ;

	/*%C Compute Header Check 																	*/
	/*%C Computing Header_Check field involves splitting Req_NbBytes field 		*/
	/*%C into three 4-bit nibbles ReqNbBytes[11:8], ReqNbBytes[7:4] and			*/
	/*%C ReqNbBytes[3:0] : 																		*/
	HeaderCheck = 		((ReqNbBytes & 0x000F)
						^ 	((ReqNbBytes & 0x00F0) >> 4))
						^ 	((ReqNbBytes & 0x0F00) >> 8) ;
	HeaderCheck = ~ HeaderCheck ;

	/*%C Build the Request Header frame 													*/
	RequestHeader = ((HeaderCheck << 12) | (ReqNbBytes & 0x0FFF)) ;
										

/******************************************************************************/
/*%C Compute the checksum 																		*/
/******************************************************************************/

	/*%C For both frames, the checksum is the sum of all preceding bytes 		*/
	/*%C of the	frame, header included. Bytes are considered as unsigned			*/
	/*%C integers. The sum is truncated to 2 bytes. 									*/
	CurrentByte = Adr_FileName;
	for (Loop_CKS = 0 ; Loop_CKS < Size_Tab_FileName ; Loop_CKS ++ )
	{
		CheckSum = CheckSum + (UBYTE)(*CurrentByte);
		CurrentByte = CurrentByte + 1 ;
	}

	CheckSum =		CheckSum
				 	+	((RequestHeader >> 8) & 0x00FF)
					+ 	((RequestHeader) & 0x00FF)
					+ 	((CreateFile_Time >> 8) & 0x00FF)
					+	((CreateFile_Time) & 0x00FF)
					+ 	((CreateFile_Date >> 8) & 0x00FF)
					+	((CreateFile_Date) & 0x00FF)
					+ 	CMD_CREATE_FILE
					+	MsNb ;


/******************************************************************************/
/*%C Build buffer																					*/
/******************************************************************************/

	/*%C First bytes is the Request Header 												*/
	PEC_Emission[0] = (UBYTE)(RequestHeader >> 8) ;
	PEC_Emission[1] = (UBYTE)RequestHeader ;

	/*%C Next Byte is the Command	and the memory stick number 						*/
	PEC_Emission[2] = CMD_CREATE_FILE ;
	PEC_Emission[3] = MsNb;

	/*%C Next bytes is the RTC Time 															*/
	PEC_Emission[4] = (UBYTE)(CreateFile_Time >> 8) ;
	PEC_Emission[5] = (UBYTE)CreateFile_Time ;

	/*%C Next bytes is the RTC Time 															*/
	PEC_Emission[6] = (UBYTE)(CreateFile_Date >> 8) ;
	PEC_Emission[7] = (UBYTE)CreateFile_Date ;

	/*%C Next bytes is the data field 														*/
	CurrentByte = Adr_FileName;
	for(Loop_Data = 8 ; Loop_Data < (8 + Size_Tab_FileName); Loop_Data++)
	{
	 	PEC_Emission[Loop_Data] = (UBYTE)(*CurrentByte);
	 	CurrentByte = CurrentByte + 1 ;
	}

	/*%C Next byte is the CRC																	*/
	PEC_Emission[8 + Size_Tab_FileName] =	(UBYTE) (CheckSum >> 8) ;
	PEC_Emission[8 + Size_Tab_FileName + 1] = (UBYTE) CheckSum ;

}