/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_RTC_WriteTimeAndDate.c                         */
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
#include "DRV_RTC_WriteTimeAndDate.h"
#include "RTC_Driver_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_RTC_WriteTimeAndDate(t_RTC_TIME_DATE RTC_NewValue)
{
/*%C Storage in global datas of the values to be writen */
	RTC_WriteValue = RTC_NewValue;

/*%C Safe keeping of RTC value*/
	DRV_RTC_FIFO_PushOneData(&RTC_WriteValue.Day,    RTC_DATE,   WRITE_RTC);
	DRV_RTC_FIFO_PushOneData(&RTC_WriteValue.Month,  RTC_MONTH,  WRITE_RTC);
	DRV_RTC_FIFO_PushOneData(&RTC_WriteValue.Year,   RTC_YEAR,   WRITE_RTC);
	DRV_RTC_FIFO_PushOneData(&RTC_WriteValue.Hour,   RTC_HOUR,   WRITE_RTC);
	DRV_RTC_FIFO_PushOneData(&RTC_WriteValue.Minute, RTC_MINUTE, WRITE_RTC);
	DRV_RTC_FIFO_PushOneData(&RTC_WriteValue.Second, RTC_SECOND, WRITE_RTC);
}
