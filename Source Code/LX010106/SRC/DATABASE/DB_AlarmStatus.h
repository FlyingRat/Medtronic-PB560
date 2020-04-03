/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_AlarmStatus.h			   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : 	datas declaration for alarm status base		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 	 		None			      	                       	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None				            				  		*/
/******************************************************************************/
#ifndef ALARMSTATUS_H
#define ALARMSTATUS_H
/******************************************************************************/
/*                     ENUM DECLARATION				                         	*/
/******************************************************************************/
/* Alarm base */
typedef enum {
	Mark_Begin_Alarm=0,
	ALARM_DISCONNECTION_U16,
	ALARM_HIGH_PRESSURE_U16,
	ALARM_APNEA_U16,
	ALARM_HIGH_VTI_U16,
	ALARM_LOW_VTI_U16,
	ALARM_LOW_VTE_U16,
	ALARM_HIGH_RATE_U16,
	ALARM_AC_POWER_FAIL_U16,
	ALARM_DC_POWER_FAIL_U16,
	ALARM_CHECK_SUPPLY_U16,
	ALARM_LOW_BATTERY_U16,
	ALARM_END_OF_BATTERY_U16,
	ALARM_CHECK_BATTERY_U16,
	ALARM_NO_BATTERY_U16,
	ALARM_CHECK_BUZZER_U16,	
	ALARM_BUZZER_BATTERY_LOW_U16,
	ALARM_BUZZER_BATTERY_CHARGE_FAILURE_U16,
	ALARM_RESERVED_18,
	ALARM_TECHNICAL_PROBLEM_U16,
	ALARM_CHECK_SETTINGS_U16,
	ALARM_CHECK_PRESSURE_U16,
	ALARM_CHECK_PROXIMAL_U16,
	ALARM_PROXI_DISCONNECTION_U16,
	ALARM_NO_PROXIMAL_U16,
	ALARM_CHECK_VALVE_U16,
	ALARM_CHECK_VOLUME_U16,
	ALARM_VALVE_LEAKAGE_U16,
	ALARM_CHECK_REMOTE_ALARM_U16,
	ALARM_UNKNOWN_BATTERY_U16,
	ALARM_CHECK_BATTERY_CHARGE_U16,
	ALARM_HIGH_VTE_U16,
	ALARM_CALIBRATION_FAIL_U16,
	ALARM_KEYBOARD_DEFAULT_U16,
	ALARM_AMBIENT_TEMP_U16,
	ALARM_BAT_TEMP_U16,
	ALARM_FAILURE_24V_U16,
	ALARM_COOLING_FAN_U16,
	ALARM_SUPPLY_MEASURE_U16,
	ALARM_TURBINE_OVERHEAT_U16,
	ALARM_RESERVED_40,
	ALARM_CONTROLLED_CYCLES_U16,
	ALARM_OCCLUSION_U16,
	ALARM_CPU_REFERENCE_U16,
	ALARM_BREATH_TIME_CYCLED_U16,
	ALARM_INSP_FLOW_FAILURE_U16,
	ALARM_CHECK_VALVE_PRESSURE_U16,
	ALARM_UTILISER_VALVE_CHANGER_PE_PI_1_U16,
	ALARM_UTILISER_VALVE_CHANGER_PE_PI_2_U16,
	ALARM_ENLEVER_VALVE_CHANGER_PE_PI_1_U16,
	ALARM_ENLEVER_VALVE_CHANGER_PE_PI_2_U16,
	ALARM_UTILISER_VALVE_1_U16,
	ALARM_UTILISER_VALVE_2_U16,
	ALARM_ENLEVER_VALVE_1_U16,
	ALARM_ENLEVER_VALVE_2_U16,
	ALARM_LEAKAGE_U16,
	ALARM_CHECK_FIO2_U16,
	ALARM_LOW_FIO2_U16,
	ALARM_HIGH_FIO2_U16,
	ALARM_NO_FIO2_SENSOR_U16,
	ALARM_CALIB_FIO2_U16,
	ALARM_CHECK_O2_SUPPLY_U16,
	ALARM_MISSING_O2_SUPPLY_U16,
	ALARM_CHECK_O2_U16,
	ALARM_O2_LEAKAGE_U16,
	ALARM_HIGH_SPO2_U16,
	ALARM_LOW_SPO2_U16,
	ALARM_SPO2_SENSOR_DISCONNECTED_U16,
	ALARM_100_PER_CENT_O2_U16,
    ALARM_DELAYED_MESSAGE_U16,
	ALARM_LEAK_OCCLUSION_U16,
	ALARM_VOLUNTARY_STOP_U16,
	ALARM_NEEDED_FIO2_CALIB_U16,
	ALARM_APNEA_FLAG_U16,
	Mark_Displayed_Alarm,
	Mark_Begin_Technical_Alarm,
	TECH_ALARM_RESERVED_1,
	TECH_ALARM_INSP_FLOW_OFFSET_DEFAULT_U16,
	TECH_ALARM_EXHAL_FLOW_OFFSET_DEFAULT_U16,
	TECH_ALARM_VALVE_PRESS_OFFSET_DEFAULT_U16,
	TECH_ALARM_INTERNAL_PRESSURE_OFFSET_DEFAULT_U16,
	TECH_ALARM_SPEED_DEFAULT_U16,
	TECH_ALARM_CLOCK_DEFAULT_U16,
	TECH_ALARM_PROXIMAL_PRESSURE_OFFSET_DEFAULT_U16,
	TECH_ALARM_VERY_LOW_PROXIMAL_PRESS_U16,
	TECH_ALARM_VERY_LOW_INTERNAL_PRESS_U16,
	TECH_ALARM_VERY_LOW_VALVE_PRESS_U16,
	TECH_ALARM_LOOSE_FLASH_POINTER,
	TECH_ALARM_FIO2_OFFSET_DEFAULT,
	TECH_ALARM_OFFSET_O2_FLOW,
	TECH_ALARM_O2_PRESSURE_OFFSET_DEFAULT,
	TECH_ALARM_RESERVED_16,
	TECH_ALARM_RESERVED_17,
	TECH_ALARM_RESERVED_18,
	TECH_ALARM_RESERVED_19,
	TECH_ALARM_RESERVED_20,
	end_of_alarms_table,
	NO_ALARM
	} e_DB_ALARMS;

#ifdef DECLARATION_ALARM_STATUS_BASE

/******************************************************************************/
/*                     CONSTANT DECLARATION			                         	*/
/******************************************************************************/
/* Base AlarmStatus array */
UWORD16 DB_AlarmStatus[end_of_alarms_table];
#else
/******************************************************************************/
/*                     CONSTANT DECLARATION			                         	*/
/******************************************************************************/
/* Base AlarmStatus array */
extern UWORD16 DB_AlarmStatus[end_of_alarms_table];

#endif
#endif
