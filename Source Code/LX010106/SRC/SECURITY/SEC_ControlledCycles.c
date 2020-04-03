/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ControlledCycles.c                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C    Controlled cycles alarm management                                    */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O *%O Output Parameter : Alarm_Error                                       */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "DB_Event.h"
#include "enum.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "Ventilation_compute_data.h"
#include "SEC_ControlledCycles.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR  SEC_ControlledCycles(void)
{
/* Alarm ControlledCycles recovery from alarm status base                     */
	e_DB_ALARMS_STATE ControlledCycles 
							= DB_AlarmStatusRead(ALARM_CONTROLLED_CYCLES_U16);
/* Ventilation state recovery from control base                               */
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
	UWORD16 SimvControlledInsp = DB_ControlRead(SIMV_CONTROLLED_INSP_U16);
	UWORD16 CurrentMode = DB_ControlRead(CURRENT_MODE_U16);
/* Alarm error declaration							                          */
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/* Temporary variable														  */
	UWORD32 TempApneaTime = 0;
/* Reset ControlledCycles patient breath counter							  */
	static UWORD16 ControlledCyclesCpt = 0;
/* ControlledCycles previous cycle					                          */
	static e_VentilState ControlledCyclesPreviousCycle = VEN_VENTIL_DISABLE;
/* Previous Alarm Controlled cycle state */
	static e_DB_ALARMS_STATE PreviousAlarmControlledCycle;

/*%C 	ControlledCycles alarm management          							  */
		switch(ControlledCycles)
		{
/******************************************************************************/
/*%C	         					 "FALSE" State                             */
/******************************************************************************/
		case ALARM_FALSE :
			 if((CurrentMode == PSIMV)
			 ||(CurrentMode == VSIMV))	
			 {
			  	if(SimvControlledInsp == TRUE)
				{
/*%C  		Storage of the true ControlledCycles alarm state in alarm base*/
/*%C  		Storage of the associated event*/
/*%C  		Up dating of priority register for leds & buzzer */
		   	
					DB_AlarmStatusWrite(ALARM_CONTROLLED_CYCLES_U16,
		   							  ALARM_TRUE);
					DB_EventMngt(EVENT_AL_CONTROLLED_CYCLES );
/*%C   		Reset of ControlledCycles counter */
		    		ControlledCyclesCpt = 0;
				}
 		 	}
			else
			{
			 	if (VentilState == VEN_INSPIRATION_CONTROLED)
			 	{
/*%C  		Storage of the true ControlledCycles alarm state in alarm base*/
/*%C  		Storage of the associated event*/
/*%C  		Up dating of priority register for leds & buzzer */
		   	
					DB_AlarmStatusWrite(ALARM_CONTROLLED_CYCLES_U16,
		   							  ALARM_TRUE);
					DB_EventMngt(EVENT_AL_CONTROLLED_CYCLES );
/*%C   		Reset of ControlledCycles counter */
		    		ControlledCyclesCpt = 0;
				}

			}

			Alarm_Error = NO_ERR_AL;
			PreviousAlarmControlledCycle = ALARM_FALSE ; 
		    break;

/******************************************************************************/
/*%C	         					 "DETECTED" State 					       */
/******************************************************************************/
/*%C 		The following state ,"ALARM_DETECTED", is not used. */
		case ALARM_DETECTED :
			Alarm_Error = ERR_AL_CONTROLLED_CYCLES;
		   break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
		case ALARM_TRUE :
/*%C 		The following state ,"ALARM_DISPLAYED", is written by HMI module. */
/*%C 		So there is no action to do .*/
			
			/*%C Start counter time (ventilation report*/
			if(PreviousAlarmControlledCycle == ALARM_FALSE) 
			{
				/*%C Counter number Apnea incrementation */			
				CMP_VentilReport_Array[DB_TREND_NB_APNEA] = 
					CMP_VentilReport_Array[DB_TREND_NB_APNEA] + 1;
				/*%C Compute the apnea time */
				TIM_StartMinuteCounter(TimerVenRecordingApnea);
			}

			Alarm_Error = NO_ERR_AL;
			PreviousAlarmControlledCycle = ALARM_TRUE ;  
			break;

/******************************************************************************/
/*%C	         					 "DISPLAYED" State                         */
/******************************************************************************/
		case ALARM_DISPLAYED	:
/*%C 		Increase of patient breathing counter  */
		    if((ControlledCyclesPreviousCycle == VEN_EXHALATION)
			  && (ControlledCyclesCpt < 3))
		     {
			  	if (VentilState == VEN_INSPIRATION_TRIGGERED)
				{
				 	ControlledCyclesCpt = ControlledCyclesCpt +1;
				}
				else if (VentilState == VEN_INSPIRATION_CONTROLED)
				{
				    ControlledCyclesCpt = 0;
				}
			 }
/*%C 		When Alarm is present and counter equals 3					 */	
			if (ControlledCyclesCpt == 3)
			{
/*%C 			The alarm is turned to False, associated event is stored */
				DB_AlarmStatusWrite(ALARM_CONTROLLED_CYCLES_U16,
			   						  ALARM_FALSE );
				DB_EventMngt(EVENT_AL_END_CONTROLLED_CYCLES );
/*%C 			End of previous apnea */
/*%C 			Read value of apnea time counter (s)*/
				TempApneaTime = (UWORD32)CMP_VentilReport_Array[DB_TREND_APNEA_TIME] +
				(TIM_ReadMinuteCounterValue(TimerVenRecordingApnea)/1000);
/*%C 			We have to check the robustness as	 TempApneaTime is an UWORD32 and*/
/*%C 			CMP_VentilReport_Array[DB_TREND_APNEA_TIME] is an UWORD16           */
				if(TempApneaTime >= 0x0000ffff)
				{
					CMP_VentilReport_Array[DB_TREND_APNEA_TIME] = 0xffff;
				}
				else
				{
					CMP_VentilReport_Array[DB_TREND_APNEA_TIME] = (UWORD16)TempApneaTime;
				}
			}
			Alarm_Error = NO_ERR_AL;
			PreviousAlarmControlledCycle = ALARM_DISPLAYED ; 
			break;

/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
		case ALARM_CANCELED :
		/******************************************************************/
		/*		 				Reset of the "CANCELED" State                   */
		/******************************************************************/
				 
		Alarm_Error = ERR_AL_CONTROLLED_CYCLES;
		PreviousAlarmControlledCycle = ALARM_CANCELED ;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                   */
/******************************************************************************/
		default:
		Alarm_Error = ERR_AL_CONTROLLED_CYCLES;
		break;
		
	 	}
/*%C Up dating the previous ventil state memory, the current mode and the  */
/*%C ventilation authorization                                               */
  	ControlledCyclesPreviousCycle =  VentilState;
	return (Alarm_Error);
}
