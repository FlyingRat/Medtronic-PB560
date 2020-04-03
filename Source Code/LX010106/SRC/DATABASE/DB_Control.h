/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_Control.h					   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : datas for Control Base									*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				None                                  		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			None		 	                 				  		*/
/******************************************************************************/
#ifndef CONTROL_H
#define CONTROL_H

#include "typedef.h"


/******************************************************************************/
/*                     ENUM DECLARATION				                         	*/
/******************************************************************************/

/* Base CONTROL	  */
typedef enum
{
    VENTIL_AUTHORIZATION_U16 = 0,
    CURRENT_MODE_U16,
    CHANGE_MODE_U16,
    VENTIL_STATE_U16,
    SIMV_CYCLES_U16,
    CALIB_PATIENT_PRESS_REQ_U16,
    CALIB_FLOW_INSP_REQ_U16,
    CALIB_FLOW_EXH_REQ_U16,
    CALIB_VALVE_PRESS_REQ_U16,
    CALIB_FAS_VALVE_REQ_U16,
    INHIBITED_BUZZER_U16,
    INHIBITION_AUTHORIZATION_U16,
    CANCELLED_ALARM_U16,
    BUZZER_CMD_U16,
    CALIB_ADJUST_CMD_U16,
    SETUP_CONTROL_SET_POINT_U16,
    SETUP_CONTROL_TYPE_U16,
    SUPPLY_AC_DC_BAT_U16,
    DISPLAY_BATTERY_U16,
    CURRENT_PATIENT_COUNTER_HOUR_U16,
    CURRENT_PATIENT_COUNTER_MIN_U16,
    CURRENT_MACHINE_COUNTER_HOUR_U16,
    CURRENT_MACHINE_COUNTER_MIN_U16,
    CONTROL_BUZZER_U16,
    VALVE_DETECTED_U16,
    AC_SELECTED_U16,
    DC_SELECTED_U16,
    REMOTE_STATE_U16,
    PROXI_DETECTED_U16,
    ALARM_DETECTED_U16,
    NEW_ALARM_HP_DETECTED_U16,
    Start_Limit_Setting,
    LIMIT_LOW_PIP_U16,
    LIMIT_HIGH_PIP_U16,
    LIMIT_PEEP_U16,
    LIMIT_VOL_CONTROL_U16,
    LIMIT_TI_CONTROL_U16,
    LIMIT_CONTROL_R_U16,
    LIMIT_PI_U16,
    LIMIT_LOW_VTI_U16,
    LIMIT_HIGH_VTI_U16,
    LIMIT_LOW_VTE_U16,
    LIMIT_HIGH_VTE_U16,
    LIMIT_P_SUPPORT_U16,
    LIMIT_TI_MIN_U16,
    LIMIT_TI_MAX_U16,
    LIMIT_SPO2_MINI_U16,
    LIMIT_SPO2_MAXI_U16,
    LIMIT_INSP_SENS_U16,
    LIMIT_SIGH_U16,
    LIMIT_TARGET_VT_U16,
    LIMIT_APNEA_U16,
    LIMIT_HIGH_FIO2,
    LIMIT_LOW_FIO2,
    LIMIT_SPO2,
    LIMIT_BACKUP_R_U16,
    LIMIT_PMAX_U16,
    End_Limit_Setting,
    UNCANCEL_CMD_U16,
    SUPPLY_BUS_FAILURE_U16,
    KEYBOARD_ANOMALIE_U16,
    VALIDATION_BIP_U16,
    BIP_RUNNING_U16,
    MAINTENANCE_MODE_U16,
    CALIBRATION_MODE_U16,
    TEST_BUZ_CARD_U16,
    TEST_BUZ_SEC_U16,
    TEST_VOLUME_U16,
    CANCEL_ALARM_ASKED,
    KEY_EVENT_U16,
    BACKLIGHT_OFF_U16,
    HIGH_PRESSURE_LED_REMINDER_U16,
    RECORD_SETTINGS_USB_U16,
    APPLY_SETTINGS_USB_U16,
    ERASE_KEY_USB_U16,
    RECORD_TIME_TENDANCE_U16,
    ERROR_SPO2_SENSOR_DETECTED,
    DETECTED_FIO2_SENSOR,
    CALIBRATED_FIO2_SENSOR,
    CALIB_ADJUST_VANNE_FIO2_CMD,
    CALIB_FIO2_REQ_U16,
    CALIB_FLOW_O2_REQ_U16,
    MEMO_CMD_VANNE_FIO2_TO_CALIB,
    CALIB_PRESS_O2_REQ_U16,
    FLOW_SAT_FLAG_U16,
    HIGH_PRESSURE_DETECTED_U16,
    HIGH_PRESSURE_EXHALATION_DETECTED_U16,
    HIGH_PRESSURE_FILTER_WINDOW_U16,
    FIO2_100_ACTIVE,
    LOAD_USB_SETTINGS_U16,
    COM_READY_U16,
    START_MONITORING_U16,
    SIMV_PSV_CYCLE_U16,
    BLOC_EXPI_DETECTED_U16,
    ADJUSTMENT_IN_PROGRESS_U16,
    VALVE_DETECT_IN_PROGRESS_U16,
    EXHAL_FLOW_USE_U16,
    FLAT_INT_U16,  
    FLAT_PROXI_U16,
    VALVE_O2_CMD_U16,
    CPAP_TRIG_I_U16,
    CPAP_TRIG_E_U16,
    CONTROLER_TYPE_U16,
    VTI_DISPLAY_DELAY_U16,
    VOLUNTARY_STOP_U16,
    SIMV_CONTROLLED_INSP_U16,
    END_OF_OPERATION_U16,
    CIRCUIT_CHECK_MODE_U16,
    end_of_db_control_table
} e_DB_CONTROL;


#ifdef DECLARATION_CONTROL_BASE
/******************************************************************************/
/*                     CONSTANT DECLARATION			                         	*/
/******************************************************************************/
/* Base Control array */
UWORD16 DB_Control[end_of_db_control_table];
#else
/******************************************************************************/
/*                     CONSTANT DECLARATION			                           */
/******************************************************************************/
/* Base Control array */
extern UWORD16 DB_Control[end_of_db_control_table];
#endif

#endif

