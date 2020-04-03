/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_InspFlowOffsetDefault.c                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Inspiratory Flow Offset Default		                     		*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES	                              */
/******************************************************************************/
#include "typedef.h"
#include "DB_Event.h"
#include "enum.h"
#include "DB_AlarmStatus.h"
#include "Security_Datas.h"
#include "SET_InspFlowOffsetDefault.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SET_InspFlowOffsetDefault(void)
{
/* Technical alarm inspiration flow recovery from base */
UWORD16 TechAlarmInspFlowOffset = 
						DB_AlarmStatusRead(TECH_ALARM_INSP_FLOW_OFFSET_DEFAULT_U16);
						 
/*%C Detection of Anomaly Default Offset internal Pressure :*/
/*%C The value DETECTED is written if the calibration has failed					*/

/*%C When the TRUE state is read, the alarm is set to the FALSE state			*/
	if(TechAlarmInspFlowOffset >= ALARM_TRUE)
	{
		DB_AlarmStatusWrite(TECH_ALARM_INSP_FLOW_OFFSET_DEFAULT_U16,
		                    ALARM_FALSE);
	}
/*%C When the DETECTED state is read, an event is sent and the alarm is set to*/
/*%C the TRUE state*/
	if (TechAlarmInspFlowOffset == ALARM_DETECTED) 
	{
	   DB_EventMngt(EVENT_ALT_INSP_FLOW_OFFSET);
      DB_AlarmStatusWrite(TECH_ALARM_INSP_FLOW_OFFSET_DEFAULT_U16,
                          ALARM_TRUE);
	}
}