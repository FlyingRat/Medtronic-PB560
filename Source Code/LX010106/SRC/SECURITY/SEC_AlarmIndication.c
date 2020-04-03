/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_AlarmIndication.c                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  This function manages the alarm indication function of priority "flags".*/
/*%C  These flags give the alarm's level (high, medium or low) and the        */
/*%C  associated command for buzzer and leds.                                 */
/*%C  The buzzer command can be inhibited by a short push on the inhibition   */
/*%C  key, and this during 60s or until a new alarm occurs.                   */
/*%C  The alarm End_Of_Battery has priority on the inhibition.                */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   NONE                                                */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "Driver_Datas.h"
#include "Security_Datas.h"
#include "DB_Event.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_AlarmStatus.h"
#include "DB_KeyboardEvent.h"
#include "DB_Current.h"
#include "DB_IhmAccessParaDataBase.h "
	#define DECLARATION_ALARM_INDICATION
#include "SEC_AlarmIndication.h"

#include "DB_Compute.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void  SEC_AlarmIndication(void)
{

/* Alarm detection flag declaration */
   UWORD16 Alarm_Detected = FALSE; 

/* New alarm detection flag declaration */
   UWORD16 New_Alarm_Detected = FALSE; 

/* Alarm mask  */
   static UWORD16 Mask_High_Priority_1 = 0xFFFF; 
   static UWORD16 Mask_High_Priority_2 = 0xFFFF;
   static UWORD16 Mask_High_Priority_3 = 0xFFFF; 
   static UWORD16 Mask_Medium_Priority_1 = 0xFFFF; 
   static UWORD16 Mask_Medium_Priority_2 = 0xFFFF; 
   static UWORD16 Mask_Medium_Priority_3 = 0xFFFF; 
   static UWORD16 Mask_Low_Priority = 0xFFFF; 

	static UWORD16 MutexMinuteBuzzer = FALSE;


/* High Pressure LED reminder on */
    UWORD16 HighPressureLEDReminder = DB_ControlRead(HIGH_PRESSURE_LED_REMINDER_U16);

/* Keys declaration */
   UWORD16 Cancel_Alarm_Asked = DB_ControlRead(CANCEL_ALARM_ASKED);

/* Buzzer inhibition declaration */
   UWORD16 Inhibition_Buzzer = FALSE;
   static UWORD16 Previous_Inhibition_Buzzer = FALSE;

/* Timer flag running declaration */
   UWORD16 Inhibition_Running = FALSE;

/* Alarm indication state declaration */
   static e_DB_ALARMS_INDICATION_STATE Alarms_Indication_State =
   													ALARM_FALSE_STATE;
/* Alarm end of battery recovery */
   UWORD16 Alarm_End_Of_Battery = DB_AlarmStatusRead(ALARM_END_OF_BATTERY_U16);

/* Uncancel command declaration  */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);

/* Keyboard Anomalie recovery from base				 									*/
   UWORD16 KeyboardAnomalie = DB_ControlRead(KEYBOARD_ANOMALIE_U16);

/* Start/Stop buzzer sequence state	(associated timer read value)					*/
   UWORD16 StartStopBuzzerRunning = FALSE ;

/* Start/Stop buzzer timer value					*/
   UWORD16 StartStopBuzzerTimer = TIM_ReadDecounterValue(VEN_VENTILATION_BIP) ;

/* Keys declaration */
   UWORD16 Cancelled_Alarm = DB_ControlRead(CANCELLED_ALARM_U16);
	UWORD16 Inhibited_Buzzer =	DB_ControlRead(INHIBITED_BUZZER_U16);

/* Previous sound select */
	UWORD16 SoundLevelSelect = DB_ConfigRead(SOUND_LEVEL_SELECT_U16);
	UWORD16 PreviousSoundLevelSelect =
										 DB_ConfigRead(PREVIOUS_SOUND_LEVEL_SELECT_U16);
	UWORD16 New_Alarm_Hp_Detected = FALSE;
	
	UWORD16 Alarm_Keyboard_Default =
								 DB_AlarmStatusRead(ALARM_KEYBOARD_DEFAULT_U16);
	UWORD16 Alarm_Turbine_Overheat =
								 DB_AlarmStatusRead(ALARM_TURBINE_OVERHEAT_U16);
/* Change mode declaration */
   UWORD16 Change_Mode = FALSE;
   UWORD16 Current_Mode = DB_ControlRead(CURRENT_MODE_U16);
   static UWORD16 Previous_Mode = VOL;
   static UWORD16 Init_Mode = FALSE;
	static UWORD16 PreviousAlarmLevel = WP;

	
/*%C Mode initialization at device start	                                    */
	if (Init_Mode == FALSE)
	{
		Previous_Mode = Current_Mode;
		Init_Mode = TRUE;
	}

/*%C***************************************************************************/
/*%C                       ALARM DETECTION                                    */
/*%C***************************************************************************/

/*%C Alarm detection */
/*%C High level detection */
   if ((SEC_High_Priority_1 != 0)
   	  || (SEC_High_Priority_2 != 0)
	  || (SEC_High_Priority_3 != 0))

	{
/*%C  Alarm detection and level writing */
	   	Alarm_Level	= HP;
		Alarm_Detected = TRUE;
	}
	else
	{
/*%C 	If 85 db active with no high priority alarm, sound setting is set */
		if ( (SoundLevelSelect == cDB_TEST_CONFIG_DB[SOUND_LEVEL_SELECT_U16].maxi)
   	  && (PreviousAlarmLevel == HP) )
		{
			DB_ConfigWrite(SOUND_LEVEL_SELECT_U16, PreviousSoundLevelSelect);		
		  	DRV_BuzInit();	
		}
/*%C 	Medium level detection (Word N°1, N°2 et N°3) */
	   if ( (SEC_Medium_Priority_1 != 0)
	    ||  (SEC_Medium_Priority_2 != 0)
	    ||  (SEC_Medium_Priority_3 != 0) )
		{
/*%C  	Alarm detection and level writing */
		    Alarm_Level	= MPR;
			Alarm_Detected = TRUE;
            if (HighPressureLEDReminder) 
            {
                DB_ControlWrite(HIGH_PRESSURE_LED_REMINDER_U16, FALSE);
            }
		}
/*%C 	Low level detection */
	   else if (SEC_Low_Priority != 0)
		{
/*%C  	Alarm detection and level writing */
		    Alarm_Level	= LP;
			Alarm_Detected = TRUE;
            if (HighPressureLEDReminder) 
            {
                DB_ControlWrite(HIGH_PRESSURE_LED_REMINDER_U16, FALSE);
            }
		}
/*%C 	No alarm detected */
	   else 
		{
/*%C  	Without Priority level*/
		   Alarm_Level	= WP;
			Alarm_Detected = FALSE;
		}
	}
/*%C Alarm detected flag writing */
   DB_ControlWrite(ALARM_DETECTED_U16,
                   Alarm_Detected);


/*%C***************************************************************************/
/*%C                      NEW ALARM DETECTION                                 */
/*%C***************************************************************************/
/* Principal (example on high priority word)	                                 */
/* 														                                 */
/* Init state: 															                  */
/* - SEC_High_Priority_1  = 0000 0000 0000 0000 				                  	*/
/* - Mask_High_Priority = 1111 1111 1111 1111					                  */
/* 2 alarms occur: 											                           */
/*  - SEC_High_Priority_1  = 0000 0000 0001 0010                						*/
/*  - Mask_High_Priority = 1111 1111 1111 1111                  					*/
/*  - SEC_High_Priority_1 & Mask_High_Priority = 0000 0000 0001 0010				*/
/*  => New alarm is detected 				                         					*/
/*  => Mask_High_Priority = 1111 1111 1110 1101                  					*/
/* 1 alarm disapears:								                                 */
/*  - SEC_High_Priority_1 =  0000 0000 0000 0010                						*/
/*  - Mask_High_Priority = 1111 1111 1110 1101                  					*/
/*  - SEC_High_Priority_1 & Mask_High_Priority = 0000 0000 0000 0000				*/
/*  => No new alarm detected		 		                         					*/
/*  => Mask_High_Priority = 1111 1111 1111 1101                  					*/
/* The last alarm disapears, another occurs:	                                 */
/*  - SEC_High_Priority_1  = 1000 0000 0000 0000                						*/
/*  - Mask_High_Priority = 1111 1111 1111 1101                  					*/
/*  - SEC_High_Priority_1 & Mask_High_Priority = 1000 0000 0000 0000				*/
/*  => New alarm is detected 				                         					*/
/*  => Mask_High_Priority = 0111 1111 1111 1111                  					*/


/*%C New alarm detection */
   if (( (Mask_High_Priority_1 & SEC_High_Priority_1) != 0)
   		|| ( (Mask_High_Priority_2 & SEC_High_Priority_2) != 0)
		|| ( (Mask_High_Priority_3 & SEC_High_Priority_3) != 0))

	{
/*%C 	New high priority alarm detected */
		DB_ControlWrite(NEW_ALARM_HP_DETECTED_U16,
							TRUE);

		New_Alarm_Hp_Detected = TRUE;
/*%C  New alarm is detected, cancel and inhibition flags initialization */
		New_Alarm_Detected = TRUE;
		DB_ControlWrite(INHIBITED_BUZZER_U16,FALSE);
		DB_ControlWrite(INHIBITION_AUTHORIZATION_U16,TRUE);
	}
	else if ( ( (Mask_Medium_Priority_1 & SEC_Medium_Priority_1) != 0)
	  	    || ( (Mask_Medium_Priority_2 & SEC_Medium_Priority_2) != 0)
	       || ( (Mask_Medium_Priority_3 & SEC_Medium_Priority_3) != 0)
	       || ( (Mask_Low_Priority & SEC_Low_Priority) != 0) )
	{
/*%C  New alarm is detected, cancel and inhibition flags initialization */
		New_Alarm_Detected = TRUE;
		DB_ControlWrite(INHIBITED_BUZZER_U16,FALSE);
		DB_ControlWrite(INHIBITION_AUTHORIZATION_U16,TRUE);
	}
	else
	{
/*%C  New alarm is not detected */
		New_Alarm_Detected = FALSE;
	}
/*%C Mask update */
	Mask_High_Priority_1 = ~SEC_High_Priority_1;
	Mask_High_Priority_2 = ~SEC_High_Priority_2;
	Mask_High_Priority_3 = ~SEC_High_Priority_3;
	Mask_Medium_Priority_1 = ~SEC_Medium_Priority_1;
	Mask_Medium_Priority_2 = ~SEC_Medium_Priority_2;
	Mask_Medium_Priority_3 = ~SEC_Medium_Priority_3;
	Mask_Low_Priority = ~SEC_Low_Priority;
    
   

/*%C***************************************************************************/
/*%C                     INHIBITION DETECTION                                 */
/*%C***************************************************************************/

/*%C Inhibition buzzer detection if no keyboard anomaly detected */
   if ( (Cancel_Alarm_Asked == TRUE)
	  && (Alarm_Keyboard_Default == ALARM_FALSE) )
	{
/*%C  If an alarm is detected */
		if ( (Alarm_Detected == TRUE)
		  && (Alarm_End_Of_Battery <= ALARM_FALSE)
		  && (Alarm_Turbine_Overheat <= ALARM_FALSE) )
		{
/*%C  	Inhibition buzzer writing */
      	Inhibition_Buzzer = TRUE;
/*%C  	Inhibition writing in the control base for HMI display */
			DB_ControlWrite(INHIBITED_BUZZER_U16,TRUE);
/*%C  	Inhibition event sending */
			DB_EventMngt(EVENT_ALARM_INHIBITION);
/*%C  	Sound buzzer is set to its previous setting (before max setting) */
			DB_ConfigWrite(SOUND_LEVEL_SELECT_U16,
								PreviousSoundLevelSelect); 

		}
/*%C  The inhibition request is initialized even if no alarm detected*/
		DB_ControlWrite(CANCEL_ALARM_ASKED,FALSE);
	}
   else
	{
/*%C  Inhibition buzzer writing */
      Inhibition_Buzzer = FALSE;
/*%C  If no alarm running, the inhibition symbol disapears */
		if (Alarm_Detected == FALSE)
		{
			DB_ControlWrite(INHIBITED_BUZZER_U16,FALSE);
		}		
   }
/*%C***************************************************************************/
/*%C                     Buzzer sound max management                          */
/*%C***************************************************************************/
/*%C Change mode test */
	if (Previous_Mode != Current_Mode)
	{
		Change_Mode = TRUE;
	}
/*%C Mode updating */
	Previous_Mode = Current_Mode;

/*%C If a new high priority alarm is detected the sound max timer is launched */
/*%C and if the "Sound buzzer" is reset (value = 0) or stopped (value = 1)*/
	if ((New_Alarm_Hp_Detected == TRUE)
	&&((TIM_ReadDecounterValue(SEC_BUZZER_SOUND_MAX) == 0)
		||(TIM_ReadDecounterValue(SEC_BUZZER_SOUND_MAX) == 1)))
	{
/*%C  One minute buzzer launch */
		TIM_StartDecounter(SEC_BUZZER_SOUND_MAX,
								TIME_ONE_MINUTE_BUZZER);
/*%C  Inhibition buzzer mutex */
		MutexMinuteBuzzer = FALSE;
	}
/*%C else, 																*/
/*%C if the alarm level is not high priority (and was), 	*/
/*%C or if the current mode has changed 					 	*/
/*%C the timer is stopped 											*/
/*%C and sound buzzer is set to its previous setting     */
	else if ( ( (Alarm_Level != HP)
				&& (PreviousAlarmLevel == HP) )
			 || (Change_Mode == TRUE) )

	{
		TIM_StopDecounter(SEC_BUZZER_SOUND_MAX);
		DB_ConfigWrite(SOUND_LEVEL_SELECT_U16,
							PreviousSoundLevelSelect); 
		DRV_BuzInit();	
	}
/*%C If there is no inhibition during one minute with a high priority alarm 	*/
/*%C detected and no inhibition buzzer, the sound is set to the max			 	*/
/*%C power							 													*/
	else if ( (TIM_ReadDecounterValue(SEC_BUZZER_SOUND_MAX) == 0)
	  && (Alarm_Level == HP)
     && (Inhibition_Buzzer == FALSE)
     && (MutexMinuteBuzzer == FALSE) )
	{
/*%C 	Previous sound value is saved in order to get it back after an  */
/*%C  inhibition following the sound max sequence			 	*/
		DB_ConfigWrite(PREVIOUS_SOUND_LEVEL_SELECT_U16,
							SoundLevelSelect); 
		DB_ConfigWrite(SOUND_LEVEL_SELECT_U16,
						cDB_TEST_CONFIG_DB[SOUND_LEVEL_SELECT_U16].maxi);

/*%C  Buzzer command with the new volume and rate (stop buzzer command,  */
/*%C  the new volume will be applied at the next function scheduling	 */
	   SEC_BuzzerCmd(WP);
		DRV_BuzInit();	
/*%C  Mutex minute buzzer in order to set the sound level once and to keep the*/
/*%C  previous one */
		MutexMinuteBuzzer = TRUE;
	}	
	  		
 /*%C  Previous alarm level updating   */
	PreviousAlarmLevel = Alarm_Level;
/*%C***************************************************************************/
/*%C                     LEDS AND BUZZERS MANAGEMENT                          */
/*%C***************************************************************************/

   switch(Alarms_Indication_State)
	{
/*%C************************************************/
/*%C              FALSE STATE                      */
/*%C************************************************/
/*%C  If no alarm detected */
	   case ALARM_FALSE_STATE:
		{
/*%C     If an alarm is detected, switch to the "Detected State" */
		   if (Alarm_Detected == TRUE)
			{
			   Alarms_Indication_State = ALARM_DETECTED_STATE;
			}
/*%C     else, buzzers and leds are stopped */
			else
			{
			   SEC_BuzzerCmd(WP);
			   SEC_LedCmd(WP);
			}
			break;
		}
/*%C************************************************/
/*%C              DETECTED STATE                   */
/*%C************************************************/
	   case ALARM_DETECTED_STATE:
		{
/*%C     Buzzer and leds command */
	      SEC_BuzzerCmd(Alarm_Level);
	      SEC_LedCmd(Alarm_Level);

/*%C     If no alarm detected, return to the false state */
		   if (Alarm_Detected == FALSE)
			{
			   Alarms_Indication_State = ALARM_FALSE_STATE;
			}
/*%C     If inhibition detected and no end of battery alarm */
	      else if (Inhibition_Buzzer == TRUE)
			{
/*%C        Switch to the "Inhibited state" */
			   Alarms_Indication_State = ALARM_INHIBITED_STATE;
/*%C        Timer launch for inhibition buzzer */
            TIM_StartDecounter(SEC_INHIB_BUZZER,
                               TIME_INHIB_BUZZER);
			}
			break;
		}
/*%C************************************************/
/*%C          INHIBITED STATE                      */
/*%C************************************************/
	   case ALARM_INHIBITED_STATE:
		{
/*%C     Inhibition buzzer command */
	      SEC_BuzzerCmd(IA);
/*%C     The led is shut down when a cancel request is detected without 		*/
/*%C     any uncancellable alarms															*/
			if ( (Cancelled_Alarm == TRUE)
			  && (Inhibited_Buzzer == FALSE) )	
			{
                /*%C     	if no alarms Led command cancelled */
                if (Alarm_Detected == FALSE)
                    SEC_LedCmd(WP);
			}
			else
			{
/*%C     	Led command with the alarm level */
	      	SEC_LedCmd(Alarm_Level);
			}
/*%C     If no alarm detected, return to the "False state" */
		   	if (Alarm_Detected == FALSE)
			{
			   Alarms_Indication_State = ALARM_FALSE_STATE;
			}
/*%C     If a new alarm is detected or inhibition delay is reached */
			else if ((New_Alarm_Detected == TRUE)
					 ||(TIM_ReadDecounterValue(SEC_INHIB_BUZZER) == 0)
			  		 || (UncancelCmd == TRUE) )
			{
/*%C        returns to the "Dectected state" */
			   Alarms_Indication_State = ALARM_DETECTED_STATE;
/*%C        End of inhibition display */
				DB_ControlWrite(INHIBITED_BUZZER_U16,FALSE);
/*%C        At the end of inhibition, if the alarm level is high priority */
/*%C        the max sound buzzer timer is launched */
				if (Alarm_Level == HP)
				{
/*%C  			One minute buzzer launch */
					TIM_StartDecounter(SEC_BUZZER_SOUND_MAX,
											TIME_ONE_MINUTE_BUZZER);
/*%C  			Inhibition buzzer mutex */
					MutexMinuteBuzzer = FALSE;
				}
 					DRV_BuzInit();	
/*%C  	Sound buzzer is set to its previous setting (before max setting) */
			DB_ConfigWrite(SOUND_LEVEL_SELECT_U16,
								PreviousSoundLevelSelect); 
			}
   
			break;
		}
		default:
		{
/*%C     This case should not be reached */
			break;
  		}
	}

/*%C***************************************************************************/
/*%C         				 START/STOP BUZZER SEQUENCE           						*/
/*%C***************************************************************************/

/*%C If the buzzer is running in start or stop sequence, the alarm sequence is*/
/*%C stopped																	               */
   if (StartStopBuzzerTimer != 0)
   {
/*%C	Stop buzzer command																		*/
		SEC_BuzzerCmd(IA);
   }

 /*%C Reset of uncancel request flag 	*/
	DB_ControlWrite(UNCANCEL_CMD_U16, FALSE);
}
