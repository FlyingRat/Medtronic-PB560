/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Security_Init.c                           		  		  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           			  Init of security function     		                 	*/
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
#include "define.h"
#include "Structure.h"
#include "DB_Event.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "DB_Config.h"
#include "DB_Rtc.h"
#include "DB_AlarmStatus.h"
#include "Security_Datas.h"
#include "MAIN_Security_Init.h"
#include "DB_IhmAccessParaDataBase.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void MAIN_Security_Init(void)
{
	UWORD16 i = 0;
	UWORD16 Id = 0;
/*%C Alarm base reset (except check settings alarm) */
	for(i = 0; i < end_of_alarms_table; i++)
	{
      if (i != ALARM_CHECK_SETTINGS_U16)
      {
		   DB_AlarmStatusWrite(i, ALARM_FALSE);
      }
	}
/*%C Power on event */
	DB_EventMngt(EVENT_START);

/*%C If a new version is detected:												         */
	if (NewVersionDetected == TRUE)
	{
/*%C  The check settings alarm is detected and the new version event is stored*/
/*%C  in flash   																					*/
      DB_AlarmStatus[ALARM_CHECK_SETTINGS_U16] |= ALARM_TRUE;
  		DB_EventMngt(EVENT_AL_NEW_VERSION );
		SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x4000;
/*%C Re-Initialize the TrendEvent and the DB_Trend */
		for(Id = DB_TREND_VENTIL_HOUR ; Id < end_of_db_trend_table ; Id ++)
		{
			DB_TrendWrite(Id,0);
		}

	}

/*%C If a bad parameter is detected:														*/
	if (BadParameter == TRUE)
   {
/*%C  The check settings alarm is detected and the bad parameter event is  	*/
/*%C	stored in flash   																		*/
      DB_AlarmStatus[ALARM_CHECK_SETTINGS_U16] |= ALARM_TRUE;
  		DB_EventMngt(EVENT_AL_EEPROM_OUT_OF_RANGE );
		SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x2000;
	}

/*%C If a config parameter is lost:	 												      */
	if (LoosePara == TRUE)
   {		  
/*%C  the check settings alarm is detected and the loose parameter event is   */
/*%C	stored in flash   																		*/
      DB_AlarmStatus[ALARM_CHECK_SETTINGS_U16] |= ALARM_TRUE;
  		DB_EventMngt(EVENT_AL_EEPROM_LOOSING_PARAM);
		SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x1000;
	}
/*%C Update Info for alarms with double messages */
	for(i = 0; i < end_of_alarms_table; i++)
	{      
	  switch(i)
	  {
		case ALARM_DISCONNECTION_U16:
		case ALARM_PROXI_DISCONNECTION_U16:
		case ALARM_NO_PROXIMAL_U16:
		case ALARM_CHECK_VALVE_U16:
		case ALARM_CHECK_VOLUME_U16:
		case ALARM_KEYBOARD_DEFAULT_U16:
		case ALARM_AMBIENT_TEMP_U16:
		case ALARM_BAT_TEMP_U16:
		case ALARM_OCCLUSION_U16:
			DB_AlarmInfoWrite(i, INFO_ALARM_TWO_MESSAGES);
		break;
        case ALARM_DELAYED_MESSAGE_U16:
			DB_AlarmInfoWrite(i, INFO_ALARM_DELAYED_MESSAGE);
		break;

		default:
		break;
	  }
	}
}
