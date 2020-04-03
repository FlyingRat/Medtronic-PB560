/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ClockDefault.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Speed blower default on starting                               */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "DB_Event.h"
#include "enum.h"
#include "DB_AlarmStatus.h"
#include "DB_Rtc.h"
#include "SEC_ClockDefault.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_ClockDefault(void)
{
UWORD16 ClockDef = 0;
static UWORD16 AckRtcControl = 0;
static UWORD16 PreviousRtcTime = 60;
UWORD16 TechAlarmClockDefault= DB_AlarmStatusRead(TECH_ALARM_CLOCK_DEFAULT_U16);
UWORD16 ActualRtcTime = DB_RTCRead(DB_RTC_SECOND_U16);

	AckRtcControl = AckRtcControl + 1;
/*%C Clock test, 15s when starting  */
/*%C then each 5s (Base scheduler = 2 x 5ms = 10 ms) */
	if ( AckRtcControl >= cFIFTEEN_SECONDS ) 
	{
/*%C 	Initialization of clock default Flag */
		ClockDef = FALSE;
/*%C 	Do the following test if seconds are < 59 */
		if (PreviousRtcTime < cFIFTY_NINE_SECONDS) 
		{
/*%C 		Check if there's stagnation */
/*%C 		Or if the delta between actual time and previous is higher than 10sec*/
		  	if ( (ActualRtcTime == PreviousRtcTime) 
			  || (ActualRtcTime > PreviousRtcTime + 10) )  
			{
/*%C 			Clock default flag is set */
				ClockDef = TRUE;
		   }
		}
/*%C 	when the memorized seconds is equal or higher than 59 */
	 	if (PreviousRtcTime >= cFIFTY_NINE_SECONDS) 
		{
/*%C 		if acquired seconds equals 59 => no evolution after 10 sec. */
			if (ActualRtcTime == cFIFTY_NINE_SECONDS) 
			{
/*%C 			default flag is set */
            ClockDef = TRUE;
         }
		}
/*%C  if default flag is true and alarm yet false */
		if ( (ClockDef == TRUE) 
		  && (TechAlarmClockDefault == ALARM_FALSE) )
   	{
/*%C 		Alarm is turned to true and stored with associated event */
   		DB_EventMngt(EVENT_ALT_CLOCK );
         DB_AlarmStatusWrite(TECH_ALARM_CLOCK_DEFAULT_U16,
                             ALARM_TRUE);
   	}
/*%C	initialization to 10 seconds	   */
		AckRtcControl = cTEN_SECONDS;
   }
/*%C Memo each 5s	   */
	if ((AckRtcControl % cFIVE_SECONDS) == 0) 
	{
/*%C  Seconds memorizing	 */
		PreviousRtcTime = ActualRtcTime;
	}
}   