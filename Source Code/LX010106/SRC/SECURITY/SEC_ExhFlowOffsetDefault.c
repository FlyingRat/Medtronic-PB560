/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ExhFlowOffsetDefault.c                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Exhalatory Flow Offset Default		     	           		  		*/
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
#include "SEC_ExhFlowOffsetDefault.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_ExhFlowOffsetDefault(void)
{
	UWORD16 TechAlarmExhFlowOffset = 
						DB_AlarmStatusRead(TECH_ALARM_EXHAL_FLOW_OFFSET_DEFAULT_U16);
 
/*%C Detection of Anomaly Default Offset exhalated flow :*/
/*%C The value DETECTED is written if the calibration has failed					*/

/*%C When the TRUE state is read, the alarm is set to the FALSE state			*/
	if(TechAlarmExhFlowOffset >= ALARM_TRUE)
	{
		DB_AlarmStatusWrite(TECH_ALARM_EXHAL_FLOW_OFFSET_DEFAULT_U16,
		                    ALARM_FALSE);
	}
/*%C When the DETECTED state is read, an event is sent and the alarm is set to*/
/*%C the TRUE state*/
	if (TechAlarmExhFlowOffset == ALARM_DETECTED) 
   {
	   DB_EventMngt(EVENT_ALT_EXH_FLOW_OFFSET);
      DB_AlarmStatusWrite(TECH_ALARM_EXHAL_FLOW_OFFSET_DEFAULT_U16,
                          ALARM_TRUE);
	}
}