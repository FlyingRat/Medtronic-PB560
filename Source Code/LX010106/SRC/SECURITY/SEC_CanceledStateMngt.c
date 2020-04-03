/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CanceledStateMngt.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  This function manages the canceled flag for HMI.								*/
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
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Event.h"
#include "DB_KeyboardEvent.h"
#include "SEC_CanceledStateMngt.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void  SEC_CanceledStateMngt(void)
{

/* Cancellable alarms recovery from base */
   e_DB_ALARMS_STATE Alarm_Check_Buzzer = 
                     DB_AlarmStatusRead(ALARM_CHECK_BUZZER_U16);
	e_DB_ALARMS_STATE Alarm_Buzzer_Battery_Low =  
                     DB_AlarmStatusRead(ALARM_BUZZER_BATTERY_LOW_U16);
	e_DB_ALARMS_STATE Alarm_BuzzerBatteryChargeFailure =  
                     DB_AlarmStatusRead(ALARM_BUZZER_BATTERY_CHARGE_FAILURE_U16);
   e_DB_ALARMS_STATE Alarm_Check_Proximal =  
                     DB_AlarmStatusRead(ALARM_CHECK_PROXIMAL_U16);
   e_DB_ALARMS_STATE Alarm_Check_Supply =  
                     DB_AlarmStatusRead(ALARM_CHECK_SUPPLY_U16);
   e_DB_ALARMS_STATE Alarm_AC_Power_Fail =  
                     DB_AlarmStatusRead(ALARM_AC_POWER_FAIL_U16);
   e_DB_ALARMS_STATE Alarm_DC_Power_Fail =  
                     DB_AlarmStatusRead(ALARM_DC_POWER_FAIL_U16);
   e_DB_ALARMS_STATE Alarm_Apnea =  
                     DB_AlarmStatusRead(ALARM_APNEA_U16);
   e_DB_ALARMS_STATE Alarm_Check_Settings =  
                     DB_AlarmStatusRead(ALARM_CHECK_SETTINGS_U16);
   e_DB_ALARMS_STATE Alarm_Technical_Problem =
							DB_AlarmStatusRead(ALARM_TECHNICAL_PROBLEM_U16);
   e_DB_ALARMS_STATE Alarm_Calibration_Fail =
							DB_AlarmStatusRead(ALARM_CALIBRATION_FAIL_U16);
   e_DB_ALARMS_STATE Alarm_Check_Remote_Alarm =
							DB_AlarmStatusRead(ALARM_CHECK_REMOTE_ALARM_U16);
   e_DB_ALARMS_STATE Alarm_Check_Battery_Charge =
							DB_AlarmStatusRead(ALARM_CHECK_BATTERY_CHARGE_U16);
	e_DB_ALARMS_STATE Alarm_Ambient_Temp =
							DB_AlarmStatusRead(ALARM_AMBIENT_TEMP_U16);
	e_DB_ALARMS_STATE Alarm_Bat_Temp =
							DB_AlarmStatusRead(ALARM_BAT_TEMP_U16);
	e_DB_ALARMS_STATE Alarm_Cooling_Fan =
							DB_AlarmStatusRead(ALARM_COOLING_FAN_U16);
	e_DB_ALARMS_STATE Alarm_Supply_Measure =
							DB_AlarmStatusRead(ALARM_SUPPLY_MEASURE_U16);
	e_DB_ALARMS_STATE Alarm_Turbine_Overheat =
							DB_AlarmStatusRead(ALARM_TURBINE_OVERHEAT_U16);

/* Audio paused alarms recovery from base */
   e_DB_ALARMS_STATE Alarm_Disconnection =  
                     DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);
   e_DB_ALARMS_STATE Alarm_High_Pressure =  
                     DB_AlarmStatusRead(ALARM_HIGH_PRESSURE_U16);
   e_DB_ALARMS_STATE Alarm_High_Vti = DB_AlarmStatusRead(ALARM_HIGH_VTI_U16);
   e_DB_ALARMS_STATE Alarm_Low_Vti = DB_AlarmStatusRead(ALARM_LOW_VTI_U16);
   e_DB_ALARMS_STATE Alarm_High_Vte = DB_AlarmStatusRead(ALARM_HIGH_VTE_U16);
   e_DB_ALARMS_STATE Alarm_Low_Vte = DB_AlarmStatusRead(ALARM_LOW_VTE_U16);
   e_DB_ALARMS_STATE Alarm_High_Rate = DB_AlarmStatusRead(ALARM_HIGH_RATE_U16);
   e_DB_ALARMS_STATE Alarm_Check_Pressure =  
                     DB_AlarmStatusRead(ALARM_CHECK_PRESSURE_U16);
   e_DB_ALARMS_STATE Alarm_Proxi_Disconnection =
   						DB_AlarmStatusRead(ALARM_PROXI_DISCONNECTION_U16);
   e_DB_ALARMS_STATE Alarm_No_Proximal =  
                     DB_AlarmStatusRead(ALARM_NO_PROXIMAL_U16);
   e_DB_ALARMS_STATE Alarm_Check_Valve = 
   						DB_AlarmStatusRead(ALARM_CHECK_VALVE_U16);
   e_DB_ALARMS_STATE Alarm_Check_Volume = 
   						DB_AlarmStatusRead(ALARM_CHECK_VOLUME_U16);
   e_DB_ALARMS_STATE Alarm_Valve_Leakage = 
   						DB_AlarmStatusRead(ALARM_VALVE_LEAKAGE_U16);
   e_DB_ALARMS_STATE Alarm_Keyboard_Default =
   						DB_AlarmStatusRead(ALARM_KEYBOARD_DEFAULT_U16);
	e_DB_ALARMS_STATE Alarm_Low_Battery =
   			  			DB_AlarmStatusRead(ALARM_LOW_BATTERY_U16);
	e_DB_ALARMS_STATE Alarm_Check_Battery =
   			  			DB_AlarmStatusRead(ALARM_CHECK_BATTERY_U16);
	e_DB_ALARMS_STATE Alarm_No_Battery =
   			  			DB_AlarmStatusRead(ALARM_NO_BATTERY_U16);
	e_DB_ALARMS_STATE Alarm_Unknown_Battery =
   			  			DB_AlarmStatusRead(ALARM_UNKNOWN_BATTERY_U16);
	e_DB_ALARMS_STATE Alarm_Failure_24V =
   			  			DB_AlarmStatusRead(ALARM_FAILURE_24V_U16);	
	e_DB_ALARMS_STATE Alarm_Breath_Time_Cycled =
   			  			DB_AlarmStatusRead(ALARM_BREATH_TIME_CYCLED_U16);
	e_DB_ALARMS_STATE Alarm_Occlusion =
   			  			DB_AlarmStatusRead(ALARM_OCCLUSION_U16);
  	e_DB_ALARMS_STATE Alarm_Insp_Flow_Failure =
   			  			DB_AlarmStatusRead(ALARM_INSP_FLOW_FAILURE_U16);
  	e_DB_ALARMS_STATE Alarm_Leak_Occlusion =
   			  			DB_AlarmStatusRead(ALARM_LEAK_OCCLUSION_U16);	
	e_DB_ALARMS_STATE AlarmLeakage =
						DB_AlarmStatusRead(ALARM_LEAKAGE_U16);
	e_DB_ALARMS_STATE AlarmNoFio2Sensor = 
						DB_AlarmStatusRead(ALARM_NO_FIO2_SENSOR_U16);
	e_DB_ALARMS_STATE AlarmVoluntaryStop =
						DB_AlarmStatusRead(ALARM_VOLUNTARY_STOP_U16);
	e_DB_ALARMS_STATE AlarmNeededFio2Calib =
						DB_AlarmStatusRead(ALARM_NEEDED_FIO2_CALIB_U16);
	e_DB_ALARMS_STATE AlarmConnectValveChangePress =
						DB_AlarmStatusRead(ALARM_UTILISER_VALVE_CHANGER_PE_PI_1_U16);
	e_DB_ALARMS_STATE AlarmConnectValve =
						DB_AlarmStatusRead(ALARM_UTILISER_VALVE_1_U16);
	e_DB_ALARMS_STATE AlarmDisconnectValveChangePress =
						DB_AlarmStatusRead(ALARM_ENLEVER_VALVE_CHANGER_PE_PI_1_U16);
	e_DB_ALARMS_STATE AlarmDisconnectValve =
						DB_AlarmStatusRead(ALARM_ENLEVER_VALVE_1_U16);

/* Cancel request recovery from keyboard event base                           */
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
/* Uncancel recovery from control base                                        */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
/* Inhibition authorization recovery from control base                        */
	UWORD16 Inhibition_Authorization =
										 DB_ControlRead(INHIBITION_AUTHORIZATION_U16);



/*%C Canceled state is TRUE if one of the alarm status is canceled				*/
	if ( (Alarm_Buzzer_Battery_Low == ALARM_CANCELED)
		|| (Alarm_Check_Supply == ALARM_CANCELED)
		|| (Alarm_AC_Power_Fail == ALARM_CANCELED)
		|| (Alarm_DC_Power_Fail == ALARM_CANCELED)
		|| (Alarm_Apnea == ALARM_CANCELED)
		|| (Alarm_Check_Settings == ALARM_CANCELED)
		|| (Alarm_Technical_Problem == ALARM_CANCELED)
		|| (Alarm_Calibration_Fail == ALARM_CANCELED)
		|| (Alarm_Check_Remote_Alarm == ALARM_CANCELED)
		|| (Alarm_Check_Battery_Charge == ALARM_CANCELED)
		|| (Alarm_Ambient_Temp == ALARM_CANCELED)
		|| (Alarm_Bat_Temp == ALARM_CANCELED)
		|| (Alarm_Cooling_Fan == ALARM_CANCELED)
		|| (Alarm_Supply_Measure == ALARM_CANCELED)
		|| (Alarm_Turbine_Overheat == ALARM_CANCELED)
		|| (AlarmNoFio2Sensor == ALARM_CANCELED)
		|| (AlarmVoluntaryStop == ALARM_CANCELED)
		|| (AlarmNeededFio2Calib == ALARM_CANCELED)
		   )
	{
/*%C  The cancel flag and its associated event are written once for each  		*/
/*%C	cancel request																				*/
		if (KeyboardDoublePulseInhibEvent == TRUE)
		{
			DB_ControlWrite(CANCELLED_ALARM_U16, TRUE);
			DB_ControlWrite(INHIBITION_AUTHORIZATION_U16,FALSE);
			DB_EventMngt(EVENT_ALARM_CANCELLATION);
			DB_KeyboardEventWrite(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16,FALSE);
		}
/*%C  else, the cancel request is already treated 			*/

/*%C  Inhibition symbol	desactivation if no other inhibited alarm is detected */
/*%C  (if only cancellable alarms are detected, the inhibition symbol should  */
/*%C	disapear)																					*/
		if ( (Alarm_Disconnection != ALARM_DISPLAYED)
		  && (Alarm_High_Pressure != ALARM_DISPLAYED)
		  && (Alarm_Apnea != ALARM_DISPLAYED)
		  && (Alarm_High_Vti != ALARM_DISPLAYED)
		  && (Alarm_Low_Vti != ALARM_DISPLAYED)
		  && (Alarm_Low_Vte != ALARM_DISPLAYED)
		  && (Alarm_High_Vte != ALARM_DISPLAYED)
		  && (Alarm_High_Rate != ALARM_DISPLAYED)
		  && (Alarm_Check_Pressure != ALARM_DISPLAYED)
		  && (Alarm_Check_Proximal != ALARM_DISPLAYED)
		  && (Alarm_Proxi_Disconnection != ALARM_DISPLAYED)
		  && (Alarm_No_Proximal != ALARM_DISPLAYED)
		  && (Alarm_Check_Valve != ALARM_DISPLAYED)
		  && (Alarm_Check_Volume != ALARM_DISPLAYED)
		  && (Alarm_Valve_Leakage != ALARM_DISPLAYED)
		  && (Alarm_Keyboard_Default != ALARM_DISPLAYED)
		  && (Alarm_Low_Battery != ALARM_DISPLAYED)
		  && (Alarm_Check_Battery != ALARM_DISPLAYED)
		  && (Alarm_No_Battery != ALARM_DISPLAYED)
		  && (Alarm_Unknown_Battery != ALARM_DISPLAYED)
		  && (Alarm_Failure_24V != ALARM_DISPLAYED)
		  && (Alarm_Breath_Time_Cycled != ALARM_DISPLAYED)
		  && (Alarm_BuzzerBatteryChargeFailure == FALSE)
		  && (Alarm_Occlusion != ALARM_DISPLAYED)
		  && (Alarm_Insp_Flow_Failure != ALARM_DISPLAYED)
		  && (Alarm_Check_Buzzer != ALARM_DISPLAYED)
		  && (Alarm_Leak_Occlusion != ALARM_DISPLAYED)
		  && (AlarmLeakage != ALARM_DISPLAYED)
		  && (AlarmConnectValveChangePress != ALARM_DISPLAYED)
		  && (AlarmConnectValve != ALARM_DISPLAYED)
		  && (AlarmDisconnectValveChangePress != ALARM_DISPLAYED)
		  && (AlarmDisconnectValve != ALARM_DISPLAYED)
		  && (Inhibition_Authorization == FALSE) )
		{
			DB_ControlWrite(INHIBITED_BUZZER_U16, FALSE);
		}
	}
/*%C else, canceled state is FALSE the cancel flag is initialized					*/
	else
	{
		DB_ControlWrite(CANCELLED_ALARM_U16, FALSE);
	} 	
/*%C When the uncancel request is detected, the cancel and inhibition flags 	*/
/*%C are initialized                                        						*/
/*%C The cancel request is initialized too                    						*/
	if (UncancelCmd == TRUE)
	{
		DB_ControlWrite(CANCELLED_ALARM_U16, FALSE);
		DB_ControlWrite(INHIBITED_BUZZER_U16, FALSE);
	}
}
