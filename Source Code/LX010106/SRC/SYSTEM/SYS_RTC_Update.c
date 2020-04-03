/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_RTC_Update.c                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                 Real Time Clock Update		                              */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES                               */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Rtc.h"
#include "SYS_RTC_Update.h"	



/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void SYS_RTC_Update(void)
{
/*%C Is it a reading or writting of RTC */
   t_RTC_TIME_DATE RtcValue = {0,
                               0,
                               0,
                               0,
                               0,
                               0};

/*%C Reading the current value of RTC	*/
	RtcValue = DRV_RTC_ReadTimeAndDate();

/*%C Storage in DataBase (Year, month, day, hour, minute, second)	*/
	DB_RTCWrite(DB_RTC_YEAR_U16,   RtcValue.Year);
	DB_RTCWrite(DB_RTC_MONTH_U16,  RtcValue.Month);
	DB_RTCWrite(DB_RTC_DAY_U16,   RtcValue.Day);
	DB_RTCWrite(DB_RTC_HOUR_U16,   RtcValue.Hour);
	DB_RTCWrite(DB_RTC_MINUTE_U16, RtcValue.Minute);
	DB_RTCWrite(DB_RTC_SECOND_U16, RtcValue.Second);
}