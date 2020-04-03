/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_RTC_Mngt.c                                               	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                 Real Time Clock Management                               */
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
#include "DB_Event.h"
#include "SET_RTC_Mngt.h"	



/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void SET_RTC_Mngt(void)
{
/*%C Is it a reading or writting of RTC */
   t_RTC_TIME_DATE RtcValue = {0,
                               0,
                               0,
                               0,
                               0,
                               0};

/*%C Step counter (initialized to 200ms) */
   static UWORD16 Nb_Step = 20;
/*%C RTC Update request from HMI	*/
   UWORD16 Adjust_rtc_req = DB_RTCRead(ADJUST_RTC_REQ_U16);

/*%C When HMI request a date RTC Update */
	if (Adjust_rtc_req == ADJUST_DATE)
	{
/*%C  Reading the current value of RTC Date */
		RtcValue = DRV_RTC_ReadTimeAndDate();

/*%C  Reading the adjusted values to Update (year, month, Day) */
		RtcValue.Year   =  DB_RTCRead(ADJUST_RTC_YEAR_U16);
		RtcValue.Month  =  DB_RTCRead(ADJUST_RTC_MONTH_U16);
		RtcValue.Day    =  DB_RTCRead(ADJUST_RTC_DAY_U16);

/*%C  Writting the new values to the hardware	  */
		DRV_RTC_WriteTimeAndDate(RtcValue);

/*%C  Date modification event with the actual settings	   */
		DB_EventMngt(EVENT_MODIF_DATE);

/*%C  Erazing the request	*/
		DB_RTCWrite(ADJUST_RTC_REQ_U16, NO_REQUEST);

/*%C  Writting the new values in database (for IHM : Year,month, day) */
		DB_RTCWrite(DB_RTC_YEAR_U16,   RtcValue.Year);
		DB_RTCWrite(DB_RTC_MONTH_U16,  RtcValue.Month);
		DB_RTCWrite(DB_RTC_DAY_U16,   RtcValue.Day);
										
/*%C  Init of Step counter (400ms)	 */
		Nb_Step = 0;
	}
/*%C End of job for a request to Update RTC Date	*/

/*%C When HMI request an Update of RTC Hour parameters do the following  */
	else if (Adjust_rtc_req == ADJUST_HOUR)
	{
/*%C  Reading the current value of RTC 	Hour		   */
		RtcValue = DRV_RTC_ReadTimeAndDate();
/*%C  Time modification event	with the previous settings	   */
		DB_EventMngt(EVENT_MODIF_TIME);
/*%C  Reading the adjusted values to Update (hour, minute, second)	 */
		RtcValue.Hour   =  DB_RTCRead(ADJUST_RTC_HOUR_U16);
		RtcValue.Minute =  DB_RTCRead(ADJUST_RTC_MINUTE_U16);
		RtcValue.Second =  DB_RTCRead(ADJUST_RTC_SECOND_U16);

/*%C  Writing the new values to the hardware		*/
		DRV_RTC_WriteTimeAndDate(RtcValue);

/*%C  Time modification event	with the actual settings	   */
		DB_EventMngt(EVENT_MODIF_TIME);

/*%C  Erazing the request					 */
		DB_RTCWrite(ADJUST_RTC_REQ_U16, NO_REQUEST);

/*%C  Writing the new values in database (for IHM : hour, minute, second)*/
		DB_RTCWrite(DB_RTC_HOUR_U16,   RtcValue.Hour);
		DB_RTCWrite(DB_RTC_MINUTE_U16, RtcValue.Minute);
		DB_RTCWrite(DB_RTC_SECOND_U16, RtcValue.Second);

/*%C  Init of Step counter (400ms)	*/
		Nb_Step = 0;
	}						  
/*%C End of job for a request to Update RTC hour */
/*%C After 400ms, DataBase is Updated	*/
	else if (Nb_Step >= 40)
	{
/*%C  Reading the current value of RTC	*/
		RtcValue = DRV_RTC_ReadTimeAndDate();
/*%C  Storage in DataBase (Year, month, day, hour, minute, second)	*/
		DB_RTCWrite(DB_RTC_YEAR_U16,   RtcValue.Year);
		DB_RTCWrite(DB_RTC_MONTH_U16,  RtcValue.Month);
		DB_RTCWrite(DB_RTC_DAY_U16,   RtcValue.Day);
		DB_RTCWrite(DB_RTC_HOUR_U16,   RtcValue.Hour);
		DB_RTCWrite(DB_RTC_MINUTE_U16, RtcValue.Minute);
		DB_RTCWrite(DB_RTC_SECOND_U16, RtcValue.Second);
/*%C  Erazing Step counter (400ms)	  */
		Nb_Step = 0;
	}
/*%C Increasing Step counter  */
	Nb_Step++;
}