/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_ValvePressureOffsetDefault.c                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Valve pressure Offset Default			                     		*/
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
#include "SET_ValvePressureOffsetDefault.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SET_ValvePressureOffsetDefault(void)
{	 
/* Technical alarm valve pressure offset													*/
UWORD16 TechAlarmValvePressOffset = 
						DB_AlarmStatusRead(TECH_ALARM_VALVE_PRESS_OFFSET_DEFAULT_U16);
 
/*%C Detection of Anomaly Default Offset Pressure Valve  :*/
/*%C The values  DETECTED are written By SETUP	  */
/*%C erasing the alarm */
	if(DB_AlarmStatusRead(TECH_ALARM_VALVE_PRESS_OFFSET_DEFAULT_U16)
																					>= ALARM_TRUE)
	{
		DB_AlarmStatusWrite(TECH_ALARM_VALVE_PRESS_OFFSET_DEFAULT_U16,
								  ALARM_FALSE);
	}

	if (TechAlarmValvePressOffset == ALARM_DETECTED) 
	{
	   DB_EventMngt(EVENT_ALT_VALVE_PRESSURE_OFFSET);
      DB_AlarmStatusWrite(TECH_ALARM_VALVE_PRESS_OFFSET_DEFAULT_U16,
      						  ALARM_TRUE);
	}
}