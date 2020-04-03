/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_InternalPressureOffsetDefault.c                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Internal pressure Offset Default		                      		*/
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
#include "Security_Datas.h"
#include "SET_InternalPressureOffsetDefault.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SET_InternalPressureOffsetDefault(void)
{
/*Internal pressure offset default recovery from base									*/
UWORD16 TechAlarmInternalPressureOffsetDefault = 
				DB_AlarmStatusRead(TECH_ALARM_INTERNAL_PRESSURE_OFFSET_DEFAULT_U16);
 
/*%C Detection of Anomaly Default Offset internal Pressure :*/
/*%C The value DETECTED is written if the calibration has failed					*/

/*%C When the TRUE state is read, the alarm is set to the FALSE state			*/
	if (TechAlarmInternalPressureOffsetDefault >= ALARM_TRUE)
	{
	   DB_AlarmStatusWrite(TECH_ALARM_INTERNAL_PRESSURE_OFFSET_DEFAULT_U16,
	                       ALARM_FALSE);
	}
/*%C When the DETECTED state is read, an event is sent and the alarm is set to*/
/*%C the TRUE state*/

	if (TechAlarmInternalPressureOffsetDefault == ALARM_DETECTED) 
	{
	   DB_EventMngt(EVENT_ALT_INT_PRESS_OFSSET);
	   DB_AlarmStatusWrite(TECH_ALARM_INTERNAL_PRESSURE_OFFSET_DEFAULT_U16,
	                       ALARM_TRUE);
	}
}