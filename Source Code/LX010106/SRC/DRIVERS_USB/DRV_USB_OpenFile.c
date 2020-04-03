/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_OpenFile.c 															*/
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

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Driver_USB_Data.h"
#include "DRV_USB_OpenFile.h"


/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/
void DRV_USB_OpenFile(UBYTE MsNb , UBYTE* Adr_FileName)
{

/*%C Local variables 																			*/
	UWORD16 Size_Tab_FileName ;
	UWORD16 HeaderCheck = 0 ;
	UWORD16 RequestHeader = 0 ;
	UWORD16 CheckSum = 0 ;
	UWORD16 Loop_CKS = 0 ;
	UWORD16 Loop_Data = 0 ;
	UBYTE* CurrentByte = Adr_FileName ;


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
/*%C Compute the request header 																*/
/******************************************************************************/

	/*%C Compute the number of bytes in frame 											*/
	/*%C Req_NbBytes field holds the total length of the Request Frame 			*/
	/*%C in bytes, header included.															*/
	ReqNbBytes = 		HEADER_SIZE
						+	CMD_SIZE
						+	MSNB_SIZE
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



/******************************************************************************/
/*%C Compute the checksum 																		*/
/******************************************************************************/

	/*%C For both frames, the checksum is the sum of all preceding bytes 		*/
	/*%C of the	frame, header included. Bytes are considered as unsigned			*/
	/*%C integers. The sum is truncated to 2 bytes. 									*/
	CurrentByte = Adr_FileName ;
	for (Loop_CKS = 0 ; Loop_CKS < Size_Tab_FileName ; Loop_CKS ++ )
	{
		CheckSum = CheckSum + (UBYTE)(*CurrentByte);
		CurrentByte = CurrentByte + 1 ;
	}

	CheckSum = 		((RequestHeader >> 8) & 0x00FF)
					+ 	((RequestHeader ) & 0x00FF)
					+ 	CMD_OPEN_FILE
					+	MsNb 
					+ 	CheckSum ;

/******************************************************************************/



/******************************************************************************/
/*%C Build buffer																					*/
/******************************************************************************/
	
	/*%C First bytes is the Request Header 												*/
	PEC_Emission[0] = (UBYTE)(RequestHeader >> 8) ;
	PEC_Emission[1] = (UBYTE)RequestHeader ;

	/*%C Next Byte is the Command	and the memory stick number 						*/
	PEC_Emission[2] = CMD_OPEN_FILE ;
	PEC_Emission[3] = MsNb;

	/*%C Next bytes is the data field 														*/
	CurrentByte = Adr_FileName;
	for(Loop_Data = 4 ; Loop_Data < (4 + Size_Tab_FileName); Loop_Data++)
	{
	 	PEC_Emission[Loop_Data] = (UBYTE)(*CurrentByte);
	 	CurrentByte = CurrentByte + 1 ;
	}

	/*%C Next byte is the CRC																	*/
	PEC_Emission[4 + Size_Tab_FileName] =	(UBYTE) (CheckSum >> 8) ;
	PEC_Emission[4 + Size_Tab_FileName + 1] = (UBYTE) CheckSum ;
}