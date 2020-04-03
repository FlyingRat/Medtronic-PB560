/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_RTC_ReadWriteHardwareRTC.c                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif
#include "io_declare.h"	
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "define.h"
#include "DRV_RTC_ReadWriteHardwareRTC.h"
#include "RTC_Driver_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_RTC_ReadWriteHardwareRTC(void)
{
	UBYTE bcd;
	UWORD16 receive;

	/* Prépositionement des niveaux des lignes SCLK et TSR  sur le bus SPI */
	SPI_PORT |= 0x2200;

/*%C If a data is present into RTC Fifo */	
	if (DRV_RTC_FIFO_ReadNbDataStored() > 0) 
		{
/*%C Reading of fifo */		
		DRV_RTC_CurrentDataPull = DRV_RTC_FIFO_PullFirstData();
/*%C If there's a request of RTC writing  */
		if (DRV_RTC_CurrentDataPull.state == WRITE_RTC)
			{
/*%C      Stop RTC					*/
/*%C      writing autorization & stop RTC 		*/
			DRV_RTC_control(0x0080);
			DRV_OutputPort(CE_RTC1, 1); /*%C activation chip enable RTC																*/
/*%C     Computing & sending of the adress of register to program	*/
			SSCTB = (UWORD16) (DRV_RTC_CurrentDataPull.regist + 0x0080);
/*%C      waiting end of transmition					*/
			DRV_RTC_WaitEndTransmit();

/*%C     Translation Interger to BCD				  */
			if (DRV_RTC_CurrentDataPull.regist < RTC_CONTROL)
				{				
				bcd = (UBYTE)((*DRV_RTC_CurrentDataPull.ptr_data / 10)*16 + (*DRV_RTC_CurrentDataPull.ptr_data % 10)); 
				SSCTB = (UWORD16) bcd;
 				}
			else
				{
				SSCTB = *DRV_RTC_CurrentDataPull.ptr_data;
				}

/*%C     waiting end of transmition		 */
			DRV_RTC_WaitEndTransmit();

/*%C     freiing of the current chanel buffer		 */
			DRV_OutputPort(CE_RTC1, 0); /*%C Desactivation chip enable RTC																*/
/*%C     Writing not allowed & RTC start		  */
			DRV_RTC_control(0x0070);
 			DRV_RTC_FIFO_FreeFirstData();
			}
/*%C   If there is a request of reading			*/
		else if (DRV_RTC_CurrentDataPull.state == READ_RTC)
			{
			DRV_OutputPort(CE_RTC1, 1); /*%C activation chip enable RTC																*/
/*%C     Sending the adress of register to be read					*/
			SSCTB = (UWORD16) (DRV_RTC_CurrentDataPull.regist);
/*%C     waiting end of transmition									*/
			DRV_RTC_WaitEndTransmit();
/*%C     Clock generation for the reading of datas		*/
			SSCTB = 0x0000; 
			/*%C     Waiting receiving, generate by a send  */
			DRV_RTC_WaitEndTransmit();
			receive = (UWORD16) SSCRB;
			if (DRV_RTC_CurrentDataPull.regist < RTC_CONTROL)
				{				
				*DRV_RTC_CurrentDataPull.ptr_data = (receive  / 16)*10 + (receive % 16);  /*%C Translation  BCD to Interger 		 */
				}
			else
				{
				*DRV_RTC_CurrentDataPull.ptr_data = receive  ;  
				}
		
			DRV_OutputPort(CE_RTC1, 0); /*%C Desactivation chip enable RTC																*/
			DRV_RTC_FIFO_FreeFirstData();
			}
		}
}

