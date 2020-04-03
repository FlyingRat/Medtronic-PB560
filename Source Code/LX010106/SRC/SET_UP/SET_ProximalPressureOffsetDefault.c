/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_ProximalPressureOffsetDefault.c                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           proximal pressure Offset Default		                      		*/
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
#include "SET_ProximalPressureOffsetDefault.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SET_ProximalPressureOffsetDefault(void)
{
/* Technical alarm proximal pressure recovery from base :*/
UWORD16 TechAlarmProximalPressOffset = 
				DB_AlarmStatusRead(TECH_ALARM_PROXIMAL_PRESSURE_OFFSET_DEFAULT_U16);
 
/*%C Detection of Anomaly Default Offset proximal Pressure :*/
/*%C The values  DETECTED are written By SYSTEM		*/
/*%C erasing the alarm 	  */
	if(TechAlarmProximalPressOffset >= ALARM_TRUE)
	{
	   DB_AlarmStatusWrite(TECH_ALARM_PROXIMAL_PRESSURE_OFFSET_DEFAULT_U16,
	                       ALARM_FALSE);
	}
	if (TechAlarmProximalPressOffset == ALARM_DETECTED) 
	{
	   DB_EventMngt(EVENT_ALT_PROXI_PRESS_OFSSET);
	   DB_AlarmStatusWrite(TECH_ALARM_PROXIMAL_PRESSURE_OFFSET_DEFAULT_U16,
	                       ALARM_TRUE);
   }
}