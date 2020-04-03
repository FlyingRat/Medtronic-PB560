/******************************************************************************/
/*                                                                            */
/* Project N°  :  RC0306                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_O2PressureOffsetDefault.c                                 	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           			O2 pressure Offset Default	    	                 		*/
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
#include "SET_O2PressureOffsetDefault.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SET_O2PressureOffsetDefault(void)
{
/* Technical alarm inspiration flow recovery from base */
UWORD16 TechAlarmO2PressureOffsetDefault = 
						DB_AlarmStatusRead(TECH_ALARM_O2_PRESSURE_OFFSET_DEFAULT);
						 
/*%C Detection of Anomaly Default O2 Flow offset :*/
/*%C The value DETECTED is written if the calibration has failed				*/

/*%C When the TRUE state is read, the alarm is set to the FALSE state  		*/
	if(TechAlarmO2PressureOffsetDefault >= ALARM_TRUE)
	{
		DB_AlarmStatusWrite(TECH_ALARM_O2_PRESSURE_OFFSET_DEFAULT,
		                    ALARM_FALSE);
	}
/*%C When the DETECTED state is read, an event is sent and the alarm is set to*/
/*%C the TRUE state*/
	if (TechAlarmO2PressureOffsetDefault == ALARM_DETECTED) 
	{
	   DB_EventMngt(EVENT_ALT_O2_PRESSURE_OFFSET);
      DB_AlarmStatusWrite(TECH_ALARM_O2_PRESSURE_OFFSET_DEFAULT,
                          ALARM_TRUE);
	}
}