/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_RTC_Launch.c                         */
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
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "define.h"
#include "DRV_RTC_Launch.h"
#include "RTC_Driver_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_RTC_Launch(void)
{
	static UBYTE RTC_Nb_Step = 100;	
/*%CConfiguration of the SPI bus speed 1,8Mhz					 */
/*Adapter le time out du WaitEndTransmit si modification de SSCBR			*/
  	SSCBR  = 0x000A;     
/*%C management of RTC hardware										 */
	DRV_RTC_ReadWriteHardwareRTC();

/*%C if the delay of 200ms is over										 */
	if (RTC_Nb_Step >= 100)
		{
/*%C eraze of compteur														 */
		RTC_Nb_Step = 0;

/*%C Copy of the value at the storage adress					 */
/*%C A mettre toujours avant la lecture car le premier coup la lecture 		 */
/*%C n'est pas disponible, elle ne l'est qu'au second								 */
		RTC_Value = RTC_TempValue;

/*%C Renouvellement de la lecture 														 */
	  	DRV_RTC_FIFO_PushOneData(&RTC_TempValue.Second, RTC_SECOND, READ_RTC);
		DRV_RTC_FIFO_PushOneData(&RTC_TempValue.Minute, RTC_MINUTE, READ_RTC);
		DRV_RTC_FIFO_PushOneData(&RTC_TempValue.Hour,   RTC_HOUR,   READ_RTC);
		DRV_RTC_FIFO_PushOneData(&RTC_TempValue.Day,    RTC_DATE,	  READ_RTC);
		DRV_RTC_FIFO_PushOneData(&RTC_TempValue.Month,  RTC_MONTH,  READ_RTC);
		DRV_RTC_FIFO_PushOneData(&RTC_TempValue.Year,   RTC_YEAR,   READ_RTC); 
		}
	else   
		RTC_Nb_Step++;
}


