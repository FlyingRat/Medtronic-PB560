/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_AlarmManager.cpp                                    			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Detection et Gestion des Alarmes			 					                  */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		     	         		   */
/******************************************************************************/

#include "HMI_AlarmManager.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Controller.hpp"

extern "C"
{
#include "enum.h"
#include "define.h"
#include "DB_AlarmStatus.h"
#include "DB_Rtc.h"
}



/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
AlarmManager::AlarmManager()
{
   RefreshActif = FALSE;
   DoubleAlarm = AMANAGER_DOUBLE_INACTIVE;
}

/******************************************************************************/
/*                           ACCESSEURS				                   			*/
/******************************************************************************/
e_BOOL AlarmManager::IsAlarmValid(AlarmEvent* _alarm)
{
	UWORD16 Info;
    UWORD16 i = _alarm->id + Mark_Begin_Alarm;
	DataBaseAccess::ReadInfo(&Info,i,ALARMS);
    if (Info & INFO_ALARM_DELAYED_MESSAGE)
        return FALSE;
    else
        return TRUE;
}
/******************************************************************************/
/*                           METHODES                			      				*/
/******************************************************************************/
/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C                                                                          */
/*%C Renvoie la prsence ou non d'une alarme sur double message			   */
/*%C                                                                          */
/*%I Input Parameter : 														  */
/*%I 		NONE															  */
/*%IO Input/Output : 														  */
/*%IO		NONE															  */
/*%O Output Parameter : 													  */
/*%O 		True: prsente ; False: Absente 							  	   */
/******************************************************************************/
e_BOOL AlarmManager::IsDoubleAlarmActive()
{
    if (this->DoubleAlarm == AMANAGER_DOUBLE_ACTIVE)
        return TRUE;
    else
        return FALSE;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Empeche un appel de REFRESH si un REFRESH et deja en cour						*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Index : Indice de la prochaine Alarme  							  			*/
/******************************************************************************/
void AlarmManager::CallRefresh()
{
   if(RefreshActif == FALSE)
   {
		Refresh();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Appelle la detection des alarmes dans la DB										*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Index : Indice de la prochaine Alarme  							  			*/
/******************************************************************************/
void AlarmManager::Refresh()
{
	UWORD16 Value,Status,Action, Info;
	static UWORD16 PreviousAlarmState[Mark_Displayed_Alarm+1];
	static UWORD16 RefreshFirstUse = TRUE;
	AlarmEvent Alarm;
 	/*%C Initialisation */
	Alarm.id = 0;
	Alarm.action = 0;
	Alarm.day = 0;
	Alarm.month = 0;
	Alarm.year = 0;
	Alarm.hour = 0;
	Alarm.min = 0;
	
	if (RefreshFirstUse == TRUE)
		{
		for(UWORD16 j = Mark_Begin_Alarm + 1; j<Mark_Displayed_Alarm; j++)
		PreviousAlarmState[j] = ALARM_FALSE;
		RefreshFirstUse = FALSE;
		}
	
	this->RefreshActif = TRUE;
    this->DoubleAlarm = AMANAGER_DOUBLE_INACTIVE;
	for(UWORD16 i = Mark_Begin_Alarm + 1; i<Mark_Displayed_Alarm; i++)
   	{
		
			DataBaseAccess::ReadValue(&Value,i,ALARMS);
			DataBaseAccess::ReadInfo(&Info,i,ALARMS);
			Status = Value & 0x000F;
			Action = Info;        

            // Update the alarm status of an alarm when there is a detection of change
            // from the previous captured alarm state.  Also, if any alarms listed below 
            // are ALARM_TRUE, always force their alarm's statuses to ALARM_DISPLAYED.
			if (    (PreviousAlarmState[i] != Status) 
                 || ((i == ALARM_LOW_BATTERY_U16) && (Status == ALARM_TRUE))
                 || ((i == ALARM_END_OF_BATTERY_U16) && (Status == ALARM_TRUE))
               )
			{        
				switch(Status)
				{
					case ALARM_TRUE:
					/*%C Determine la date */
					DataBaseAccess::ReadValue(&Alarm.hour,DB_RTC_HOUR_U16,RTC);
					DataBaseAccess::ReadValue(&Alarm.min,DB_RTC_MINUTE_U16,RTC);
					DataBaseAccess::ReadValue(&Alarm.day,DB_RTC_DAY_U16,RTC);
					DataBaseAccess::ReadValue(&Alarm.month,DB_RTC_MONTH_U16,RTC);
					DataBaseAccess::ReadValue(&Alarm.year,DB_RTC_YEAR_U16,RTC);
	
					Alarm.id = i - Mark_Begin_Alarm ;
					Alarm.action = Action;
					if (i != ALARM_APNEA_FLAG_U16)
					{	
						Controller::GetInstance()->AlarmDetect(TRUE,&Alarm);
					}
					Value &= 0xFFF0;
					Value += ALARM_DISPLAYED;
					DataBaseAccess::WriteValue(&Value,i,ALARMS);
				break;
	
				case ALARM_FALSE:   
				case ALARM_CANCELED:
				case ALARM_DETECTED:
					Alarm.id = i - Mark_Begin_Alarm ;
					Alarm.action = Action;
					if (i != ALARM_APNEA_FLAG_U16)
					{
						Controller::GetInstance()->AlarmDetect(FALSE,&Alarm);
					}
				break;		
				default:
	/*%C 			No operation */
				break;
				}
				PreviousAlarmState[i] = Status;
		        if ((Status == ALARM_TRUE) || (Status == ALARM_DISPLAYED)) {
		
		            if (Info & INFO_ALARM_TWO_MESSAGES)
		                {
						this->DoubleAlarm = AMANAGER_DOUBLE_ACTIVE;
						PreviousAlarmState[i] = end_of_alarms_state_table;
						}
		        }
			
			}
	}
	this->RefreshActif = FALSE;
}



