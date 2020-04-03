/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_WriteAtTheEndOfFile.c 											*/
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
#include "DRV_USB_WriteAtTheEndOfFile.h"


/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/
void DRV_USB_WriteAtTheEndOfFile(UBYTE MsNb , 
											UBYTE* Adr_DataToWrite ,
											UWORD16 NbDataToWrite)
{

/******************************************************************************/
/*%C Local variables																				*/
/******************************************************************************/

	UWORD16 HeaderCheck = 0 ;
	UWORD16 RequestHeader = 0 ;
	UWORD16 CheckSum = 0 ;
	UWORD16 Loop_CKS = 0 ; 
	UWORD16 Loop_Data = 0 ;
	UBYTE* CurrentByte =	Adr_DataToWrite;

/******************************************************************************/
/*%C Compute the request header 																*/
/******************************************************************************/

	/*%C Compute the number of bytes in frame 											*/
	/*%C Req_NbBytes field holds the total length of the Request Frame 			*/
	/*%C in bytes, header included.															*/
	ReqNbBytes = 		HEADER_SIZE
						+	CMD_SIZE
						+	MSNB_SIZE
						+ 	NbDataToWrite
						+	CHECKSUM_SIZE ;

	/*%C Compute the bytes was write in key */
	/*%C to previous the Key Full */
	UsbNbBytesWriteOnKey = UsbNbBytesWriteOnKey + NbDataToWrite ;

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

	for (Loop_CKS = 0 ; Loop_CKS < NbDataToWrite ; Loop_CKS ++ )
	{
		CheckSum = CheckSum + (UBYTE)(*CurrentByte);
		CurrentByte = CurrentByte + 1 ;
	}

	CheckSum =		CheckSum
					+	((RequestHeader >> 8) & 0x00FF)
					+ 	((RequestHeader ) & 0x00FF)
					+ 	CMD_WRITE_AT_THE_END_OF_THE_FILE
					+	MsNb ;



/******************************************************************************/
/*%C Build buffer																					*/
/******************************************************************************/

	/*%C First bytes is the Request Header 												*/
	PEC_Emission[0] = (UBYTE)(RequestHeader >> 8) ;
	PEC_Emission[1] = (UBYTE)RequestHeader ;
							
	/*%C Next Byte is the Command	and the memory stick number						*/
	PEC_Emission[2] = CMD_WRITE_AT_THE_END_OF_THE_FILE ;
	PEC_Emission[3] = MsNb;

	/*%C Next bytes is the data field														*/
	CurrentByte = Adr_DataToWrite;
	for(Loop_Data = 4 ; Loop_Data < (4 + NbDataToWrite); Loop_Data++)
	{
	 	PEC_Emission[Loop_Data] = (UBYTE)(*CurrentByte);
	 	CurrentByte = CurrentByte + 1 ;
	}

	/*%C Next byte is the CRC																	*/
	PEC_Emission[NbDataToWrite + 4] = (UBYTE) (CheckSum >> 8) ;
	PEC_Emission[NbDataToWrite + 5] = (UBYTE) CheckSum ;

}
