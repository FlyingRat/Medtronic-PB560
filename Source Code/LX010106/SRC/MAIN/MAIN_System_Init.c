/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_System_Init.c                                   		  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           			  Init of system data			                      	*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES	                             */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Control.h"
#include "DB_RTC.h"
#include "System_Datas.h"
#include "MAIN_System_Init.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void MAIN_System_Init(void)
{
/*%C RTC declaration for Read/write operation */
	t_RTC_TIME_DATE RtcValue;

/*%C Read the machine and patient counters in the control base */
	SYS_CounterMachineMin  = DB_ControlRead(CURRENT_MACHINE_COUNTER_MIN_U16);
   SYS_CounterMachineHour = DB_ControlRead(CURRENT_MACHINE_COUNTER_HOUR_U16);
	SYS_CounterPatientMin  = DB_ControlRead(CURRENT_PATIENT_COUNTER_MIN_U16);
	SYS_CounterPatientHour = DB_ControlRead(CURRENT_PATIENT_COUNTER_HOUR_U16);

/*%C Read the RTC value */
	RtcValue = DRV_RTC_ReadTimeAndDate();
/*%C RTC storage in RTC base */
	DB_RTCWrite(DB_RTC_YEAR_U16,   RtcValue.Year);
	DB_RTCWrite(DB_RTC_MONTH_U16,  RtcValue.Month);
	DB_RTCWrite(DB_RTC_DAY_U16,   RtcValue.Day);
	DB_RTCWrite(DB_RTC_HOUR_U16,   RtcValue.Hour);
	DB_RTCWrite(DB_RTC_MINUTE_U16, RtcValue.Minute);
	DB_RTCWrite(DB_RTC_SECOND_U16, RtcValue.Second);

/*%C Start Backlight Decounter */
	TIM_StartDecounter(SYS_TIME_BACKLIGHT, TIME_BACKLIGHT);

}
