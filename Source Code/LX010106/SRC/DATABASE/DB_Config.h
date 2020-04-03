/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_Config.h					   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : 	datas declaration for config base				*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None			      	                       	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None				            				  		*/
/******************************************************************************/
#ifndef CONFIG_H
#define CONFIG_H
/******************************************************************************/
/*                     ENUM DECLARATION				                         	*/
/******************************************************************************/
/* Config base */
/* Do not modify the enum order; if you add any configuration settings you must*/
/*   change the software version of the program otherwise you get EEPROM POST */
/*   errors                                                                   */
/*                                                                            */
/******************************************************************************/

typedef enum {
	ADJUST_LANGUAGE_U16=0,
	ADJUST_MODE_U16,
	ADJUST_KEYLOCK_U16,
	VENTIL_REQ_U16,
	OFFSET_INSP_FLOW_1_U16,
	OFFSET_INSP_FLOW_2_U16,
	OFFSET_INSP_FLOW_3_U16,
	OFFSET_INSP_FLOW_4_U16,
	OFFSET_INSP_FLOW_5_U16,
	OFFSET_INSP_FLOW_6_U16,
	OFFSET_INSP_FLOW_7_U16,
	OFFSET_INSP_FLOW_8_U16,
	OFFSET_EXH_FLOW_1_U16,
	OFFSET_EXH_FLOW_2_U16,
	OFFSET_EXH_FLOW_3_U16,
	OFFSET_EXH_FLOW_4_U16,
	OFFSET_EXH_FLOW_5_U16,
	OFFSET_EXH_FLOW_6_U16,
	OFFSET_EXH_FLOW_7_U16,
	OFFSET_EXH_FLOW_8_U16,
	OFFSET_O2_FLOW_1,
	OFFSET_O2_FLOW_2,
	OFFSET_O2_FLOW_3,
	OFFSET_O2_FLOW_4,
	OFFSET_O2_FLOW_5,
	OFFSET_O2_FLOW_6,
	OFFSET_O2_FLOW_7,
	OFFSET_PATIENT_PRESS_1_U16,
	OFFSET_PATIENT_PRESS_2_U16,
	OFFSET_PATIENT_PROX_PRESS_1_U16,
	OFFSET_PATIENT_PROX_PRESS_2_U16,
	OFFSET_PRESS_O2,
	I_VALVE_REF_U16,
	OFFSET_FAS_VALVE_1_U16,
	OFFSET_FAS_VALVE_2_U16,
	OFFSET_FAS_VALVE_3_U16,
	OFFSET_FAS_VALVE_4_U16,
	OFFSET_FAS_VALVE_5_U16,
	OFFSET_FAS_VALVE_6_U16,
	OFFSET_FAS_VALVE_7_U16,
	OFFSET_FAS_VALVE_8_U16,
	OFFSET_FAS_VALVE_9_U16,
	OFFSET_VALVE_PRESS_U16,
	OFFSET_VALVE_PRESS_2_U16,
	OFFSET_FIO2,
	ADJUST_BRIGHTNESS_U16,
	ADJUST_BACKLIGHT_U16,
/* Do not modify the enum order; due to trap record */
	SAVED_PATIENT_COUNTER_HOUR_U16,  
/* Do not modify the enum order; due to trap record */
	SAVED_PATIENT_COUNTER_MIN_U16,
/* Do not modify the enum order; due to trap record */
	SAVED_MACHINE_COUNTER_HOUR_U16,
/* Do not modify the enum order; due to trap record */
	SAVED_MACHINE_COUNTER_MIN_U16,
/* Do not modify the enum order; due to trap record */
 	RETRIEVAL_EVENT_ADRESS_MSB_U16,
/* Do not modify the enum order; due to trap record */
 	RETRIEVAL_EVENT_ADRESS_LSB_U16,
/* Do not modify the enum order; due to trap record */
	FLASH_MONIT_WRITE_BLOCK_U16,
/* Do not modify the enum order; due to trap record */
	FLASH_MONIT_WRITE_PAGE_U16,
/* Do not modify the enum order; due to trap record */
	FLASH_MONIT_WRITE_COLUMN_U16,
/* Do not modify the enum order; due to trap record */
	FLASH_TREND_WRITE_BLOCK_U16,
/* Do not modify the enum order; due to trap record */
	FLASH_TREND_WRITE_PAGE_U16,
/* Do not modify the enum order; due to trap record */
	FLASH_TREND_WRITE_COLUMN_U16,
/* Do not modify the enum order; due to trap record */
	FLASH_FIRST_PARTITION_FULL_U16,
/* Do not modify the enum order; due to trap record */
	FLASH_SECOND_PARTITION_FULL_U16,

	SPEED_COM_U16,
	RAZ_COUNTER_PAT_DATE_U16,
	RAZ_COUNTER_PAT_MONTH_U16,
	RAZ_COUNTER_PAT_YEAR_U16,
	RAZ_COUNTER_PAT_HOUR_U16,
	RAZ_COUNTER_PAT_MIN_U16,	 
	BAD_ERASE_U16,	 					/* record of flash interrupt*/
	SOUND_LEVEL_SELECT_U16,
	PREVIOUS_SOUND_LEVEL_SELECT_U16,
   	CURVE_DISPLAY_TYPE_MODE_U16,
	CURVE_MAX_PRESSURE_U16,
   	CURVE_MAX_FLOW_U16,
	CURVE_MAX_VT_U16,
	CURVE_MAX_TIME_U16,
   	CURVE_DRAW_MODE_U16,
	ADJUST_CYCLING_MODE_U16,
	ADJUST_KEY_TONE_U16,
	ADJUST_WAVEFORM_DISPLAY_U16,
	ADJUST_BAROMETRIC_CORRECTOR_U16,
	ADJUST_FIO2,
	ADJUST_FIO2_SELECT,
	ADJUST_LOW_FIO2,
	ADJUST_HIGH_FIO2,
	ADJUST_LOW_SPO2,
	ADJUST_HIGH_SPO2,
   	SPO2_LOW_SELECT,
	SPO2_HIGH_SELECT,
  	FIO2_LOW_SELECT,
	FIO2_HIGH_SELECT,
	PRESSURE_UNIT_U16,
	TRIGG_E_POSITIVE,
	APNEA_ALARM_ACTIVATION,
	FLASH_MEMORY_MANUFACTURER,
	FLASH_MEMORY_DEVICE,
	FLASH_MEMORY_FIVE_ADDRESS_CYCLES,
	PARAM_COMPATIBILITY,
	IHM_LOCKED_FRAME_ID,
	ADJUST_PEDIATRIC_CIRCUIT_U16,
	PREVIOUS_MODE_U16,
	PRESSURE_SUPPORT_RELATIVE_U16,
	PRESSURE_SUPPORT_CHANGED_U16,
	VOLUNTARY_STOP_ALARM_ACTIVATION,	
	SOUND_TYPE_SELECT_U16,
 	end_of_db_config_table
} e_DB_CONFIG;

#ifdef DECLARATION_CONFIG_BASE
/******************************************************************************/
/*                     CONSTANT DECLARATION			                           */
/******************************************************************************/
/* Base Compute Array*/
UWORD16 DB_Config[end_of_db_config_table];
#else
/******************************************************************************/
/*                     CONSTANT DECLARATION			                         	*/
/******************************************************************************/
/* Base Compute Array*/
extern UWORD16 DB_Config[end_of_db_config_table];
#endif

#endif
