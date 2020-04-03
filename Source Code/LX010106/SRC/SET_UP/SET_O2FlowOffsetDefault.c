/******************************************************************************/
/*                                                                            */
/* Project N°  :  RC0306                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_O2FlowOffsetDefault.c                                    	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           			O2 Flow Offset Default		                     		*/
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
#include "SET_O2FlowOffsetDefault.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SET_O2FlowOffsetDefault(void)
{
/* Technical alarm inspiration flow recovery from base */
UWORD16 TechAlarmO2FlowOffset = 
						DB_AlarmStatusRead(TECH_ALARM_OFFSET_O2_FLOW);
						 
/*%C Detection of Anomaly Default O2 Flow offset :*/
/*%C The value DETECTED is written if the calibration has failed					*/

/*%C When the TRUE state is read, the alarm is set to the FALSE state			*/
	if(TechAlarmO2FlowOffset >= ALARM_TRUE)
	{
		DB_AlarmStatusWrite(TECH_ALARM_OFFSET_O2_FLOW,
		                    ALARM_FALSE);
	}
/*%C When the DETECTED state is read, an event is sent and the alarm is set to*/
/*%C the TRUE state*/
	if (TechAlarmO2FlowOffset == ALARM_DETECTED) 
	{
	   DB_EventMngt(EVENT_ALT_O2_FLOW_OFFSET);
      DB_AlarmStatusWrite(TECH_ALARM_OFFSET_O2_FLOW,
                          ALARM_TRUE);
	}
}