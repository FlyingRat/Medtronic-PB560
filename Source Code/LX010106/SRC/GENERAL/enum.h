/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: enum.h	 	   				   					               		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : 	enum file declaration								*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		       			                  	*/
/*%IO Input/Output Parameter :   None                                		  	*/
/*%O 	Output Parameter : 			None     	                				  		*/
/******************************************************************************/

#ifndef ENUM_H
#define ENUM_H

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "Product.h"

/******************************************************************************/
/*                     ENUM DECLARATION    				                     	*/
/******************************************************************************/

typedef enum 
{
	LOGO_LEGENDAIR = 0,
	KEY_WHITE,
	BAT,
	BLACK_SQUARES,
	FREE_SQUARE,
	KEY,
	LOS,
	BLACK_LOS,
	LESS_OR_MORE,
	RAMPE1,
	RAMPE2,
	RISETIME1,
	RISETIME2,
	RISETIME3,
	RISETIME4,
	TRIGGER,
	TRIGGERINV,
	VENTIL,
	LOCKS,
	PAUSE,
	VALVE_BLACK,
	VALVE_WHITE,
	CADRE_WHITE_BG,
	CADRE_WHITE_HD,
	CADRE_BLACK_BG,
	CADRE_BLACK_HD,
	TRIANGLE_BLACK,
	TRIANGLE_WHITE,
	FLECHE_GRAPH_HAUT,
	FLECHE_GRAPH_DROITE,
	CADRE_WHITE_HG,
	CADRE_WHITE_BD,
	CADRE_BLACK_HG,
	CADRE_BLACK_BD,
	BAT_INV,
	CADRE_BLACK_BGw,
	CADRE_BLACK_BDw,
	CADRE_BLACK_HGw,
	CADRE_BLACK_HDw,
	CADRE_WHITE_HGw,
	CADRE_WHITE_HDw,
	CADRE_WHITE_BDw,
	CADRE_WHITE_BGw,
	BELL_BLACK,
	ALARM_TRIANGLE_BLACK,
	EQUAL,
  	HEART,
	CADRE_WHITE_ALARM_HGw,
	CADRE_WHITE_ALARM_HDw,
	CADRE_WHITE_ALARM_BDw,
	CADRE_WHITE_ALARM_BGw,
	HEART_INVERSE_VIDEO,
	ALARM_TRIANGLE_BLACK_DOT,
	RAMPE3,
   LOGO_M2,
   LOGO_XL2,
   LOGO_S2,
   LOGO_XL2_US,   
    /* ATTENTION - NE RIEN RAJOUTER AVANT CET ENUM 					*/
    /* SINON PLUS D'AFFICHAGE DE VERSION DANS LE SOFT DE TEST 	*/
	CHART_VERSION = 58,
	TRADEMARK,
	COMPANY,
	WHITE_SQUARE,
  	WHITE_LOCK,
	NO
} e_SYMBOL;

/* Mettre à jour cette enum selon le nombre de langues sélectionnées
   ATTENTION :
   1- Le define NB_LANGUAGE (define.h) doit être cohérent avec l'enum ci-dessus !
   2- L'ordre de l'enum ci-dessus doit respecter l'ordre des tables dans HMI_Message.cpp !
*/
typedef enum
{
   HMI_LANG_CHINESE = 0,
   HMI_LANG_DANISH,
   HMI_LANG_GERMAN,
   HMI_LANG_ENGLISH,
   HMI_LANG_ENGLISH_US,
   HMI_LANG_SPANISH,
   HMI_LANG_FRENCH,
   HMI_LANG_GREEK,
   HMI_LANG_ITALIAN,
   HMI_LANG_JAPANESE,
   HMI_LANG_KOREAN,
   HMI_LANG_DUTCH,
   HMI_LANG_NORWISH,
   HMI_LANG_POLISH,
   HMI_LANG_PORTUGUESE,
   HMI_LANG_RUSSIAN,
   HMI_LANG_FINNISH,
   HMI_LANG_SWEDISH,
   HMI_LANG_TURKISH
} e_HMI_LANG;

#define HMI_LANG_LAST HMI_LANG_TURKISH

typedef enum
{
	TIMIN = 0,
	TIMAX,
	end_of_e_TI
} e_TI;

typedef enum 
{
	ACTIVATED = 0,
	// Etats des modes VC, VAC, VPC et VPAC
	EXHALATION,
	INSPIRATION,
	// Etats des modes AI et AI FR
	PSV_EXHALATION,	
	PSV_INSPIRATION, 
	CC_EXHALATION,	  
	CC_INSPIRATION,
	// Etats du mode VSIMV
	SIMV_VSIMV_EXHALATION, 
	SIMV_CAV_INSPIRATION,
	SIMV_PSV_INSPIRATION,
	SIMV_CV_EXHALATION,
	SIMV_CV_INSPIRATION,
	SIMV_VSIMV_EXHALATION_APNEA,
	SIMV_CV_INSPIRATION_APNEA,
	// Etats du mode PSIMV
	SIMV_PSIMV_EXHALATION,
	SIMV_CAP_INSPIRATION,
	SIMV_CP_EXHALATION,
	SIMV_CP_INSPIRATION,
	SIMV_PSIMV_EXHALATION_APNEA,
	SIMV_CP_INSPIRATION_APNEA,
 	// Etats du mode PPC  //****
	CPAP_EXHALATION,		 //****
	CPAP_INSPIRATION		 //****
} e_ActiveModeState;

/* Alarm priority */
typedef enum 
{
    /* (Technical) */
    /*%C Message technique, Pas de buzzer, Pas de led (VLP), Sans Néon */
    /*%C Technical message, no buzzer, no led (VLP), no backlight */
	TEC = 0, 		
    /* (Without Priority) */   
    /*%C Pas de message, Pas de buzzer, Pas de led, Sans Néon */
    /*%C No message, no buzzer, no led, no backlight */
	WP,  			 
    /* (Very Low Priority) */
    /*%C Message, Pas de buzzer, Pas de Led, Sans Néon */
    /*%C Message, no buzzer, no led, no backlight */
	VLP, 			
    /* (Low Priority) */
    /*%C Message, Pas Buzzer, Led orange continue, Sans Néon */
    /*%C Message, no buzzer, orange continuous led, no backlight */
	LP,   		
    /* (Medium Priority) */
    /*%C Message, Buzzer moyen, Led orange clignotante, Avec Néon */    
    /*%C Message, slow buzzer, orange blinking led, backlight */
   MPR,  		
    /* (High Priority) */
    /*%C Message, Buzzer rapide ,Led rouge clignotante ,Avec Néon */
    /*%C Message, fast buzzer, red blinking led, backlight */
	HP,   		
    /* (Very High Priority) */ 
    /*%C Message, Buzzer continu, Led rouge continue, Avec Néon */
    /*%C Message, continuous buzzer, red continuous led, backlight	*/
	VHP,			
    /* (Ultimate Alarm) */
    /*%C Pas de Message, Buzzer continu, Pas de Led rouge continue(Hard) */
    /*%C No message, continuous buzzer, no red led (hard) */
	UA, 			
    /* (Inhibited Alarm) */
    /*%C Message, Buzzer inhibe, led allumé en fonction du niveau d'alarme */
    /*%C Message, buzzer inhibited, led (function of level) */
	IA 			
} e_DB_ALARM_LEVEL_PRIORITY;

/* Alarm error*/
typedef enum
{
	NO_ERR_AL = 0,
	ERR_AL_DISCONNECTION,
	ERR_AL_HIGH_PRESSURE,
	ERR_AL_APNEA,
	ERR_AL_HIGH_VTI,
	ERR_AL_LOW_VTI,				  
	ERR_AL_LOW_VTE,
	ERR_AL_HIGH_VTE,
	ERR_AL_HIGH_VM,
	ERR_AL_LOW_VM,
	ERR_AL_LOW_RATE,
	ERR_AL_HIGH_RATE,
	ERR_AL_POWER_SUPPLY_LOSS,
	ERR_AL_AC_POWER_FAIL,
	ERR_AL_DC_POWER_FAIL,
	ERR_AL_CHECK_SUPPLY,
	ERR_AL_PERIODICAL_SIGNAL,
	ERR_AL_LOW_BATTERY,
	ERR_AL_END_OF_BATTERY,
	ERR_AL_CHECK_BATTERY,
	ERR_AL_NO_BATTERY,
	ERR_AL_CHECK_BUZZER,
	ERR_AL_BUZZER_BATTERY_LOW, 
 	ERR_AL_BUZZER_BATTERY_FAILURE, 
 	ERR_AL_BUZZER_BATTERY_CHARGE_FAILURE, 
	ERR_AL_TECHNICAL_PROBLEM,
	ERR_AL_EEPROM_OUT_OF_RANGE,
	ERR_AL_EEPROM_LOOSING_PARAM,
	ERR_AL_NEW_VERSION,
	ERR_AL_ERROR_VERSION,
	ERR_AL_REVERSED_IE,
	ERR_AL_CHECK_PRESSURE,
	ERR_AL_CHECK_PROXIMAL,
	ERR_AL_PROXI_DISCONNECTION,
	ERR_AL_NO_PROXIMAL,
	ERR_AL_NO_VALVE_DETECTION,
	ERR_AL_CHECK_VALVE,
	ERR_AL_CHECK_VOLUME,
	ERR_AL_VALVE_LEAKAGE,
	ERR_AL_CHECK_REMOTE_ALARM,
	ERR_AL_UNKNOW_BATTERY,
	ERR_AL_CHECK_BATTERY_CHARGE,
	ERR_AL_COOLING_FAN,
	ERR_AL_AMBIENT_TEMP,
	ERR_AL_BAT_TEMP,
	ERR_AL_FAILURE_24V,
	ERR_AL_SUPPLY_MEASURE,
	ERR_AL_TURBINE_OVERHEAT,
	ERR_AL_OCCLUSION,
	ERR_AL_CPU_REFERENCE,
	ERR_AL_CONTROLLED_CYCLES,
	ERR_AL_CHECK_VALVE_PRESSURE,
	ERR_AL_CHECK_PIPE,
	ERR_AL_LEAKAGE,
	ERR_AL_CHECK_FIO2,
	ERR_AL_LOW_FIO2,
	ERR_AL_HIGH_FIO2,
	ERR_AL_NO_FIO2_SENSOR,
	ERR_AL_CHECK_O2_SUPPLY,
	ERR_AL_MISSING_O2_SUPPLY,
	ERR_AL_CHECK_O2,
	ERR_AL_O2_LEAKAGE,
	ERR_AL_BREATH_TIME_CYCLED,
	ERR_AL_INSP_FLOW_FAILURE,
	ERR_AL_LEAK_OCCLUSION,
	ERR_AL_VOLUNTARY_STOP,
	ERR_AL_NEEDED_FIO2_CALIB,
	end_of_error_alarm_table
} e_ALARM_ERROR;

/* Alarm state */
typedef enum
{
	ALARM_FALSE = 0,
	ALARM_DETECTED,
	ALARM_TRUE,
	ALARM_DISPLAYED,
	ALARM_CANCELED,
	end_of_alarms_state_table
} e_DB_ALARMS_STATE;

/* Alarm Indication state */
typedef enum
{
	ALARM_FALSE_STATE = 0,
	ALARM_DETECTED_STATE,
   ALARM_INHIBITED_STATE,
	end_of_alarms_indication_state_table
} e_DB_ALARMS_INDICATION_STATE;

/* Version base */
/* Do not modify the enum order */
typedef enum 
{
	VERSION_NUMBER_0 = 0,
	VERSION_NUMBER_1,
	VERSION_NUMBER_2,
	VERSION_NUMBER_3,
	SERIAL_NUMBER_1,
	SERIAL_NUMBER_2,
	SERIAL_NUMBER_3,
	SERIAL_NUMBER_4,
	SERIAL_NUMBER_5,
	SERIAL_NUMBER_6,
	end_of_db_version_table
} e_DB_VERSION;

/* Trend base */
typedef enum
{
   DB_TREND_VENTIL_HOUR = 0,
   DB_TREND_VENTIL_MIN,
   DB_TREND_AVG_VTI,
   DB_TREND_AVG_VTE,
   DB_TREND_AVG_VM,
   DB_TREND_AVG_FR,
   DB_TREND_LEAK_MODE,      
   DB_TREND_AVG_LEAK,
   DB_TREND_AVG_PI,
   DB_TREND_IA,
   DB_TREND_APNEA,
   DB_TREND_PERCENT_CONTROLLED,
   DB_TREND_PERCENT_TRIGGERED,
   DB_TREND_SAVE_RTC_DAY,
   DB_TREND_SAVE_RTC_MONTH,
   DB_TREND_SAVE_RTC_YEAR,
   DB_TREND_SAVE_PC_HOUR,
   DB_TREND_SAVE_PC_MIN,
   DB_TREND_NB_APNEA,
   DB_TREND_APNEA_TIME,
   DB_TREND_NB_CYCLE_COUNTER_MSB,
   DB_TREND_NB_CYCLE_COUNTER_LSB,
   DB_TREND_NB_CYCLE_TRIGERRED_MSB,
   DB_TREND_NB_CYCLE_TRIGERRED_LSB,
   DB_TREND_NB_CYCLE_CONTROLLED_MSB,
   DB_TREND_NB_CYCLE_CONTROLLED_LSB,
   DB_TREND_VENTIL_REPORT_UPD,
   DB_TREND_IHM_VENTIL_HOUR,
   DB_TREND_IHM_VENTIL_MIN,
   DB_TREND_IHM_AVG_VTI,
   DB_TREND_IHM_AVG_VTE,
   DB_TREND_IHM_AVG_VM,
   DB_TREND_IHM_AVG_FR,
   DB_TREND_IHM_LEAK_MODE,      
   DB_TREND_IHM_AVG_LEAK,
   DB_TREND_IHM_AVG_PI,
   DB_TREND_IHM_IA,
   DB_TREND_IHM_APNEA,
   DB_TREND_IHM_PERCENT_CONTROLLED,
   DB_TREND_IHM_PERCENT_TRIGGERED,
   DB_TREND_IHM_SAVE_RTC_DAY,
   DB_TREND_IHM_SAVE_RTC_MONTH,
   DB_TREND_IHM_SAVE_RTC_YEAR,
   end_of_db_trend_table
} e_DB_Trend;

/* Database list*/
typedef enum 
{
	ADJUST = 0,
	CONTROL,
	COMPUTE,
	VERSION,
	CONFIG,
	RTC,
	ALARMS,
	POWER_SUPPLY,
	KEYBOARD,
    USB,
  	TREND,
	CURRENT,
	REVISION,
	end_of_type_of_db_target
} e_TYPE_OF_DB_TARGET;

/* Database operation */
typedef enum 
{
	READ = 0,
	WRITE,
	DECREASE,
	INCREASE,
    MIN,
    MAX,
    STEP,
    READ_INFO,
    WRITE_INFO
} e_DATA_OPERATION;

/* Ventilation Modes */
typedef enum 
{
	VOL = 0,
	PRES,
	PSVT,
	VSIMV,
	PSIMV,
	CPAP,
  	nb_of_mode
} e_MODE_TYPES;

typedef enum
{
    TRIGGER_LEVEL_OFF = 0,
    TRIGGER_LEVEL_0P,
    TRIGGER_LEVEL_1P,
    TRIGGER_LEVEL_2,
    TRIGGER_LEVEL_3,
    TRIGGER_LEVEL_4,
    TRIGGER_LEVEL_5,
    nb_of_trigger_levels
} e_TRIGGER_LEVELS;

typedef enum
{
    TEST_STATE_NOT_RUN = 0,
    TEST_STATE_RUNNING,
    TEST_STATE_ABORTED,
    TEST_STATE_PASS,
    TEST_STATE_FAIL,
    nb_of_test_states
} e_TEST_STATES;

/* SIMV States */
typedef enum 
{
	CAV_Cycle = 0,   
	CV_Cycle,		
	PSV_Cycle,		
	CAP_Cycle,		
	CP_Cycle		
} e_VEN_SIMVCycle;

/* Supply States */
typedef enum 
{
	NONE = 0,
	AC,
	DC,
	BATTERY
} e_SupplyInfo;  

/* RTC States */
typedef enum 
{
	NO_REQUEST = 0,
	ADJUST_DATE,
	ADJUST_HOUR
} e_RTC_OPERATION;

/* Erase states */
typedef enum 
{
	ERASE_OK = 0,
	BAD_TOTAL_ERASE
} e_BadEraseState;

/* Ramp states */
typedef enum 
{
	RAMP_DECELERATED = 0,
	RAMP_RECTANGLE,
    RAMP_SINUS,
    nb_of_ramps
} e_RampType;


/* Control States */
typedef enum 
{
	NO_CONTROL = 0,
	CONTROL_SPEED,
	CONTROL_PRESSURE,
	CONTROL_PRESSURE_VALVE,
	CONTROL_PRESSURE_MAINT,
	CONTROL_FLOW,
	CONTROL_FLOW_EXH,
	CONTROL_FLOW_O2,
	CONTROL_FLOW_O2_MANUEL,
	CONTROL_PRESSURE_O2
} e_VEN_ControllerType;

typedef enum 
{
	VEN_EXH_PLAT = 0,
	VEN_INSP_RISE,
	VEN_INSP_PLAT,
	VEN_EXH_FALL
} e_VEN_Controller_Phase;

/* Calibration States */
typedef enum 
{
	NO_CALIB = 0,
	SEGMENT_1,        
	SEGMENT_2,                                                             
	SEGMENT_3,                                                               
	SEGMENT_4,                                                                
	SEGMENT_5,                                                                
	SEGMENT_6,       
	SEGMENT_7,
	SEGMENT_8,  
	TEST_LIMITES_REQUEST, 
	TEST_LIMITES_OK,
	TEST_LIMITES_FALSE,       
	AUTOCALIB_SEG_1,    
	AUTOCALIB_SEG_2,  
	AUTOCALIB_SEG_3,  
	AUTOCALIB_SEG_4,
	AUTOCALIB_SEG_5,
	AUTOCALIB_SEG_6,
	AUTOCALIB_SEG_7,
	AUTOCALIB_SEG_8,
	END_AUTOCALIB
} e_CalibrationCommand;		

// Types de calibration
typedef enum 
{
	SYS_PATIENT_PRESS_CALIB = 0,
	SYS_VALVE_PRESS_CALIB,
	SYS_INSP_FLOW_CALIB,
	SYS_EXH_FLOW_CALIB,
	SYS_EXH_FLOW_VERIF,
	SYS_FIO2_CALIB,
	SYS_O2_FLOW_CALIB,
	SYS_O2_PRESSURE_CALIB,
   end_of_sys_calib
} e_CalibrationType;



/* States ventilation */
typedef enum 
{
	VEN_EXHALATION = 251,
	VEN_INSPIRATION_CONTROLED,
	VEN_INSPIRATION_TRIGGERED,
	VEN_VENTIL_DISABLE
} e_VentilState;

typedef enum 
{
	CONTROLLED = 0,
	TRIGGERED,
   NO_INSP
} e_InspDetectType;

/* Déclaration des détections de touches		*/
typedef enum 
{
	KEY_NO_KEYBOARD = 0,
	KEY_CODE_MONIT_AND_DOWN,
	KEY_CODE_MONIT_AND_UP,
	KEY_CODE_UP_AND_DOWN,
	Mark_Begin_Simple_Touch,
	KEY_CODE_UP,
	KEY_CODE_DOWN,
	KEY_CODE_VALID,     
	KEY_CODE_MONIT,
	KEY_CODE_STARTSTOPVENTIL,
	KEY_CODE_100_O2,
	KEY_CODE_NAVIG,
	Number_of_key
    /* Attention après un ajout de touche - ne pas oublier de compléter la */
    /* matrice dans keyboard.c*/
} e_SYS_KeyboardInput;

typedef enum
{
	KEY_LONGPUSH_KEY_NO_KEYBOARD = 0,
	KEY_LONGPUSH_KEY_CODE_MONIT_AND_DOWN,
	KEY_LONGPUSH_KEY_CODE_MONIT_AND_UP,
	KEY_LONGPUSH_KEY_CODE_UP_AND_DOWN,
	KEY_LONGPUSH_KEY_CODE_UP,
	KEY_LONGPUSH_KEY_CODE_DOWN,
	KEY_LONGPUSH_KEY_CODE_VALID,     
	KEY_LONGPUSH_KEY_CODE_MONIT,
	KEY_LONGPUSH_KEY_CODE_STARTSTOPVENTIL,
	end_of_keyboard_longpush_decnt,
	KEY_AUTOREPEAT_KEY_NO_KEYBOARD,
	KEY_AUTOREPEAT_KEY_CODE_MONIT_AND_DOWN,
	KEY_AUTOREPEAT_KEY_CODE_MONIT_AND_UP,
	KEY_AUTOREPEAT_KEY_CODE_UP_AND_DOWN,
	KEY_AUTOREPEAT_KEY_CODE_UP,
	KEY_AUTOREPEAT_KEY_CODE_DOWN,
	KEY_AUTOREPEAT_KEY_CODE_VALID,     
	KEY_AUTOREPEAT_KEY_CODE_MONIT,
	KEY_AUTOREPEAT_KEY_CODE_STARTSTOPVENTIL,
	end_of_keyboard_autorepeat_decnt,
	KEY_ANO_KEYB,
	KEY_DELAY_BETWEEN_LONG_AUTOREPEAT,
   KEY_DOUBLE_PULSE_TIME_OUT,
	KEY_CONFIRM_VENT_STOP_TIMER,
	VEN_TI_COUNT,
	VEN_TE_COUNT,
	VEN_SIMV_PERIOD_COUNT,
	VEN_CONTROLLED_CYCLE_PERIOD_COUNT,
	VEN_TIME_CALIB_FIO2,
	VEN_VALVE_TIM,
	VEN_VENTILATION_BIP,
	VEN_END_COUNT0,
	VEN_END_COUNT1,
	VEN_END_COUNT2,
	VEN_END_COUNT3,
	VEN_END_COUNT4,
	VEN_END_COUNT5,
	SYS_TIME_OUT_SPEED,
	SYS_1MINPAT,
	SYS_TIME_OUT_CALIB,
	SYS_TIME_AUTO_CALIB,
	SYS_TIME_FAS_VALVE_CALIB,
	SYS_TIME_SUPPLY_CHANGE,
	SYS_TIME_DETECT_FIO2,
	SYS_TIME_BACKLIGHT,
	SYS_PRESSURE_CHOICE,
	SYS_PRESSURE_CHOICE_INT,
	SYS_PROXIMAL_TO_INTERNAL_SWITCH,
	SYS_CHECK_PRESSURE,
	SYS_CHECK_PROXIMAL,
	SYS_VALVE_TIM,
	SEC_PRESSURE_CHOICE,
	SEC_LOW_PRESS,
	SEC_HIGH_PRESSURE,
	SEC_HIGH_PRESSURE_DETECT,
	SEC_CPAP_HIGH_PRESSURE,
	SEC_HIGH_PRESSURE_ALARM,
	SEC_FLAG_HIGH_PRESSURE,
	SEC_APNEA,
	SEC_CHECK_PRESSURE,
	SEC_CHECK_PROXIMAL,
	SEC_NO_BATTERY_TIM,
	SEC_CHECK_FIO2_TIM,
	SEC_KEYBOARD_TIM,	
	SEC_SPEED_BLOW_TIM,
   SEC_START_BIP_SOUND,
   SEC_STOP_BIP_SOUND,
	SEC_LOW_FIO2_TIM,
	SEC_CPU_REFERENCE_FAILURE_TIM,
	SEC_FLOW,
	SEC_TIME_WAIT_STARTING,
	SEC_HIGH_FIO2_TIM,
	SEC_BAT_LOW_LEVEL,
	SEC_HIGH_SPO2_TIM,
	SEC_LOW_SPO2_TIM,
	SEC_BAT_VERY_LOW_LEVEL,
	SEC_BUZ_READ, 
	SEC_BATTERY_FAILURE_CO_BUZ, 
 	SEC_DETECTION_BATTERY_FAILURE_CO_BUZ, 
	SEC_FAIL_AC_TIM,
	SEC_FAIL_DC_TIM,
	SEC_VALVE_CST,
	SEC_PROXI_CST,
	SEC_INT_CST,
	SEC_CHECK_VALVE,
	SEC_VALVE_PRESS,
	SEC_INHIB_CHECK_FIO2,
	SEC_INHIB_LOW_FIO2,
	SEC_INHIB_HIGH_FIO2,
	SEC_INHIB_CHECK_REMOTE,
	SEC_CANCEL_HIGH_PRESSURE,
	SEC_CHECK_SUPPLY,
	SEC_PPC_APNEA,// delai d'apnée pour le mode PPC
	SEC_PROX_DISC,
	SEC_RAZ_CHECK_BAT,
	SEC_CHECK_PRESS,
	SEC_CHECK_PRESS2,
	SEC_CHECK_PROXI,
	SEC_CHECK_REMOTE,
	SEC_BAT_P_S_TIM,
	SEC_INHIB_BUZZER,
    SEC_LOW_PRIORITY_BURST,
    SEC_MEDIUM_PRIORITY_BURST,
    SEC_HIGH_PRIORITY_BURST,
    SEC_BUZZER_PULSE,
    SEC_BUZZER_SILENCE,
    SEC_BUZZER_SOUND_MAX,
	SET_VALIDATION_BIP,
	SEC_NO_PROXIMAL,
	SET_HISTO_BIP,
	SEC_BLOWER_OVERHEAT,
	ACT_MIN_FLOW,
	ACT_STOP_ADAPTATION,
	WAIT_USB_BUSY,
	USB_CONNECT_DISCONNECT_KEY,
	USB_WAIT_READ_FIFO,
	SPI_FRAME_TIME,
	SPI_WAIT_DISPLAY_BATTERY_GAUGE,
	TIM_COM_RECORDING_MONIT,
	TIM_USB_RECORDING_MONIT,
	SEC_CHECK_VALVE_PRESSURE,
	SEC_LEAKAGE,
	SEC_CHECK_O2_SUPPLY,
	SEC_O2_LEAKAGE,
	SEC_100_FIO2_TIM,
	INT_MEASURE_BUZZER,
	SEC_CANCEL_BATTERY_FAILURE_CO_BUZ,
	ACT_BOOST_FREQ, 
	SEC_LEAK_OCCLUSION,
	SEC_CPU_REF_FAILURE,
	SEC_APNEA_FLAG,
	SEC_OCCLUSION_TIMER,
	end_of_table_cnt_decnt
} e_TIM_TABLE_ID; 

typedef enum
{
	TimerWelcomeEvent = 0,
	TimerHideLoupe,
	TimerBlinkEvent,
	TimeOutModifEvent,
	TimerQuitHistoAlarme,
	TimerQuitPreferences,
	TimerQuitGraphConfig,
	TimerRefresh,
	TimerStopModifMode,
	TimerAutoCalibTest,
	TimerRefreshAlarm,
	TimerSwapAlarm,
	TimerTriggerOk,
	TimerSpyPraram,
	TimerHideAlarmMessage,
	TimerHideStopVentMess,
	TimerAddToBlinkEvent,
	TimerWaitCalibVerif,
	TimerHistoAlarmSeek,
	TimerHistoAnoSeek,
	TimerWaitCalibQExp,
	TimerWaitCalibFiO2,   
	TimerUsbMessage,
   	TimerUsbProcessing,
	Timer100PrCentO2,
	TimerVenRecordingApnea,
	TimerUsbRecordingDetailledHorodatage,
	TimerUsbCommandTooLong,//USB_COMMAND_TOO_LONG,
   	TimerQuitVentilReport,
	SEC_PERIODICAL_BIP,
   	TimerEndLongDownKey,
   	TimerEndLongUpKey,
    TimerDoubleAlarm,  
	SEC_BATTERY_FAILURE_CHARGE_BUZ_READ,
    SEC_LOW_BATTERY_BUZ_READ,
	SEC_BATTERY_FAILURE_CC_BUZ,  
    TimerLeakTest,
	end_of_minute_ihm_table_decnt,
	end_of_minute_table_cnt_decnt
} e_TIM_MINUTE_TABLE_ID; 

typedef enum
{
  COUNT = 0,
  DECOUNT
} e_TYPE_USE_TIMER;

// type d'accés RTC
typedef enum 
{
	FREE_RTC,
	READ_RTC,
	WRITE_RTC,
	ERROR_RTC
} e_DRV_RTC_ACCESS_STATE;

// adresse des registres RTC en lecture -> + 0x0080 pour l'écriture
typedef enum 
{
	RTC_SECOND = 0,
	RTC_MINUTE,
	RTC_HOUR,
	RTC_DAY,
	RTC_DATE,
	RTC_MONTH,
	RTC_YEAR,
	RTC_SEC_ALARM1,
	RTC_MIN_ALARM1,
	RTC_HOURS_ALARM1,
	RTC_DAY_ALARM1,
	RTC_SEC_ALARM2,
	RTC_MIN_ALARM2,
	RTC_HOURS_ALARM2,
	RTC_DAY_ALARM2,
	RTC_CONTROL,
	RTC_STATUS,
	RTC_CHARGER,
	RTC_BEGIN_RAM // 96 octets
} e_DRV_RTC_REGISTER;

typedef enum
{
	DRV_RTC_NO_ERROR = 0,
	DRV_RTC_TIME_OUT_TRANSMIT
}e_DRV_RTC_ERROR;

typedef enum 
{
	READ_EEP = 0,
	WRITE_EEP,
	FREE_EEP,
	ERROR_EEP
} e_EEP_ACCESS_STATE;	

typedef enum
{
	DRV_EVENT_FREE = 0,
	DRV_EVENT_ERASE,
	DRV_EVENT_WRITE

}e_DRV_EVENT_STATE;


typedef enum
{
	DRV_EEP_NO_ERROR = 0,
	DRV_EEP_TIME_OUT_WRITE,
	DRV_EEP_TIME_OUT_TRANSMIT
}e_DRV_EEP_WRITE_ERROR;

typedef enum
{
	DRV_EEP_WRITE_PENDING = 0,
	DRV_EEP_FREE	
} e_STATE_OF_DRIVE_EEP;


typedef enum

{
	DRV_INIT = 0,
	DRV_LOAD_TABLE,
	DRV_BRITHNESSAJUST,
	DRV_NEGATIVE_CAR,
	DRV_DISPLAY_PAGE,	
	DRV_STRING,	
	DRV_NUMBER,	
	DRV_SYMBOL,	
	DRV_PIXEL,	
	DRV_LINE,
	DRV_BOX,	
	DRV_ERASE_ZONE,	
	DRV_ERASE_PAGE,
	DRV_BACKLIHGHTADJUST
}e_DRV_DISPLAY_FUNCTION;

/*%C Kind of sound */
typedef enum 
{
	NO_SOUND = 0,
	BIP_SHORT_SOUND,
	BIP_LONG_SOUND,
	BIP_VERY_LONG_SOUND,
	START_BIP_SOUND,
	STOP_BIP_SOUND,
	BATTERY_SOUND,
	VERY_SLOW_SOUND,
	SLOW_SOUND,
	FAST_SOUND,
	USB_CONNECT,
	USB_DISCONNECT,
	CONTINU_SOUND
} e_TYPE_SOUND;

/*%C Kind of buzzer test */
typedef enum 
{
	NO_BUZ = 0,
	BUZ
} e_TYPE_TEST_BUZ;

/*%C Backlight Level Intensity */
typedef enum 
{
	SWITCH_OFF = 0,
	WEAK,
	SWITCH_ON
} e_TYPE_BACKLIGHT_LEVEL;

/*%C Buzzer number to test */
typedef enum 
{
	BUZ_CARD = 0,
	BUZ_SEC,
	BUZ_ALL,
	BUZ_VOLUME
} e_NUMBER_BUZ;

/*%C Kind of LED display */
typedef enum 
{
	NO_LED = 0,
	BLINK_LED,
	CONTINU_LED
} e_TYPE_BLINK;

/*%C Validation bip for menu navigation and ventilation start/stop */
typedef enum 
{
	NO_BIP = 0,
	BIP_SHORT,
	BIP_LONG,
	BIP_VERY_LONG,
	BIP_START_VENTIL,
	BIP_STOP_VENTIL,
	BURST,
	BIP_USB_CONNECT,
	BIP_USB_DISCONNECT,
	BIP_SHORT_VALID,
	BIP_BATTERY_PERIODICAL
} e_VALIDATION_BIP;

/*%C Validation bip type (cloc, bip, cloc and bip, no cloc/bip) */
typedef enum 
{
	NO_CLOC_BIP = 0,
	CLOC,
	BIP,
	BIP_AND_CLOC
} e_VALIDATION_BIP_TYPE;

typedef enum 
{
	SPI_EEPROM = 0,
	SPI_RTC,
	SPI_POWER	
} e_SPI_ACCESS;

typedef enum
{
	PIM = 0,
	VIM,
	PSV,
	end_of_e_SIMV
}
e_SIMV;

typedef enum
{
	PS_FLOW_END = 0,
	PS_HIGH_PRESS_END,
	PS_TIMED_END,
	end_of_e_SIMV_PS_End
}
e_SIMV_PS_End;

typedef enum
{
	Month_start = 0,
	JANUARY,
	FEBRUARY,
	MARSH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
} e_Month;

typedef enum 
{
	DB_RTC,
	DB_CURRENT,
	DB_CONFIG,
	DB_CONTROL,
	DB_COMPUTE,
    DB_POWERSUPPLY,
    DB_NULL
} e_DataBaseType;


/* Output new Port 16 pins */
typedef enum
{
  	OUT_LED_VENTIL = 0,
	OUT_LED_O2,
	FREE_1Q3,
  	CE_EEP, /* Start Chip Enable Spi */
  	CE_RTC1,
	CE_RTC2,
	CE_INT_PRES_SENS,
	CE_PROX_PRES_SENS,
	CE_VALVE_PRES_SENS,
	CE_SPI_USB,
	CE_SPI_PIC,
	CE_FLOW_INSP_SENS,
	CE_FLOW_EXP_SENS, /* End Chip Enable SPI */
	CE_SPI_PIC_IC44,
 	FREE_2Q7,
	FREE_2Q8
}e_OUTPUT_NAME;



/******************************************************************************/
/*%C SPI Communication */
/******************************************************************************/

/*%C enum frame transmission to power board */
typedef enum
{
	SPI_POWER_TRANSMIT_START_FRAME_MSB = 0,
	SPI_POWER_TRANSMIT_START_FRAME_LSB,
	SPI_POWER_TRANSMIT_VENTIL_AUTHORIZATION,
	SPI_POWER_TRANSMIT_MAINTENANCE_MODE,
	SPI_POWER_TRANSMIT_CALIBRATION_MODE,
	SPI_POWER_TRANSMIT_CRC,
	SPI_POWER_TRANSMIT_END_FRAME,
	SPI_POWER_TRANSMIT_EndOfFrame

}e_SPI_POWER_TRANSMIT;

/*%C enum frame SPI POWER receive */
typedef enum
{
	SPI_POWER_RECEIVE_MSB_START_FRAME = 0,
	SPI_POWER_RECEIVE_LSB_START_FRAME,
	SPI_POWER_RECEIVE_MSB_V_BAT_U16,
	SPI_POWER_RECEIVE_LSB_V_BAT_U16,		
	SPI_POWER_RECEIVE_MSB_TEMP_BAT_S16,
	SPI_POWER_RECEIVE_LSB_TEMP_BAT_S16,
	SPI_POWER_RECEIVE_MSB_BAT_CYCLES_U16,
	SPI_POWER_RECEIVE_LSB_BAT_CYCLES_U16,
	SPI_POWER_RECEIVE_LSB_BAT_STATE_U16,
	SPI_POWER_RECEIVE_LSB_POWER_TYPE_U16,
	SPI_POWER_RECEIVE_MSB_JAUGE_MINUTE_U16,
	SPI_POWER_RECEIVE_LSB_JAUGE_MINUTE_U16,
	SPI_POWER_RECEIVE_LSB_JAUGE_AVALAIBLE_U16,
	SPI_POWER_RECEIVE_LSB_PER_CENT_BAT_U16,
	SPI_POWER_RECEIVE_LSB_NO_PRESENCE_BAT_U16,
	SPI_POWER_RECEIVE_LSB_BAT_KO_U16,
	SPI_POWER_RECEIVE_LSB_CHARGE_KO_U16,
	SPI_POWER_RECEIVE_LSB_UNKNOWN_BATTERY_U16,
	SPI_POWER_RECEIVE_MSB_AMBIENT_TEMP_S16,
	SPI_POWER_RECEIVE_LSB_AMBIENT_TEMP_S16,
	SPI_POWER_RECEIVE_LSB_BATTERY_END_U16,
	SPI_POWER_RECEIVE_LSB_BATTERY_LOW_U16,
	SPI_POWER_RECEIVE_LSB_FIRST_DATE_DAY_U16,
	SPI_POWER_RECEIVE_LSB_FIRST_DATE_MONTH_U16,
	SPI_POWER_RECEIVE_LSB_FIRST_DATE_YEAR_U16,
	SPI_POWER_RECEIVE_LSB_BAT_TEMP_OVERFLOW,
	SPI_POWER_RECEIVE_LSB_SUPPLY_MEASURE_FAILURE,
	SPI_POWER_RECEIVE_LSB_FAILURE_24V_FLAG,
	SPI_POWER_RECEIVE_LSB_AMBIENT_TEMP_OUTOFBOUNDS,
	SPI_POWER_RECEIVE_LSB_COOLING_FAN_FAILURE_FLAG,
	SPI_POWER_RECEIVE_LSB_FIRST_VERSION_IDENTIFIANT,
	SPI_POWER_RECEIVE_LSB_SECOND_VERSION_IDENTIFIANT,
	SPI_POWER_RECEIVE_LSB_THIRD_VERSION_IDENTIFIANT,
	SPI_POWER_RECEIVE_LSB_BAT_FIRST_DATE_HOUR_U16,
	SPI_POWER_RECEIVE_LSB_BAT_FIRST_DATE_MINUTE_U16,
	SPI_POWER_RECEIVE_LSB_BAT_FIRST_DATE_SECOND_U16,
	SPI_POWER_RECEIVE_LSB_BAT_AGEING_U16,
	SPI_POWER_RECEIVE_LSB_BAT_SUPPLIER_U16,
	SPI_POWER_RECEIVE_LSB_BAT_TYPICAL_CAPACITY_U16,
	SPI_POWER_RECEIVE_CRC,
	SPI_POWER_RECEIVE_END_FRAME,
	SPI_POWER_RECEIVE_EndOfTable,
	SPI_POWER_RECEIVE_BufferSize = 70

}e_SPI_POWER_RECEIVE;


typedef enum
{
	DRV_SPI_POWER_NO_ERROR = 0,
	DRV_SPI_POWER_TIME_OUT_TRANSMIT,
	DRV_SPI_POWER_NO_FRAME,
	DRV_SPI_POWER_BAD_FRAME
}e_DRV_SPI_POWER_ERROR;



/* !! Be carefull when changing this enum -> check that the PC software is up to date) */
typedef enum
{
	COM_VOL_A = 0, /* PB560-520 */
	COM_PSVT,	   /* PB560-520 */
	COM_PRES_A,	   /* PB560-520 */
	COM_VSIMV,	   /* PB560-520 */
	COM_CPAP,	   /* PB560-520 */
	COM_VOL_C,	   /* PB560-520 */
	COM_PSV,	   /* PB560-520 */
	COM_PRES_C,    /* PB560-520 */
	COM_VOL_US,	   /* PB540 */
	COM_PRES_US,   /* PB540 */
	COM_PSV_US,	   /* PB540 */
	COM_VSIMV_US,  /* PB540 */
	COM_PSIMV_US,  /* PB540 */
	COM_CPAP_US,   /* PB540 */
	COM_PSIMV,	   /* PB560-520 */
	End_of_Table_Mode_COM
}e_MODE_COM;


typedef enum
{
	MONITORAGE = 0 ,
	HORODATAGE
}e_Monit_Buffer_Data_Type;



typedef enum
{
	DATA_FRAME0 = 0,
	DATA_FRAME1,
	DATA_FRAME2,
	SIZE_FRAME_UART1
} e_FrameUART1;

typedef enum
{
	REQUEST = 0,
	RUNNING,
	ENDED
} e_Flash_Read_Status;

typedef enum
{
	I_T = 0,
	I_E
} e_Cycling_Mode;


typedef enum
{
	ORIGINAL = 0,
	COMPLIANT
} e_Alarm_Tone;

/******************************************************************************/
/*%C Monitoring Enum																				*/
/******************************************************************************/
/*%C For Com only */

typedef enum
{
	MONIT_MSB_PRESSURE = 0,
	MONIT_LSB_PRESSURE,
	MONIT_MSB_CORRECTED_FLOW_INSP,
	MONIT_LSB_CORRECTED_FLOW_INSP,
	MONIT_MSB_CORRECTED_FLOW_EXHAL,
	MONIT_LSB_CORRECTED_FLOW_EXHAL,
	MONIT_CORRECTED_VT_LEAK,
	MONIT_SPO2,
	MONIT_HR,
	MONIT_ALARM_1,
	MONIT_ALARM_2,
	MONIT_ALARM_3,
	MONIT_ALARM_4,
	MONIT_ALARM_5,
	MONIT_ALARM_6,
	MONIT_ALARM_7,
	MONIT_ALARM_8,
	MONIT_ALARM_9,
  	MONIT_SYMBOL,
	MONIT_VENTIL_MODE,
	End_Of_Table_Direct_Monitoring
} e_DIRECT_MONITORING;

/******************************************************************************/
/*%C Detailled Monitoring Enum */
/******************************************************************************/
/*%C For Usb and Flash */

typedef enum
{
	DETAILLED_DATA_TYPE = 0,

	DETAILLED_DAY = 1,
	DETAILLED_VENTIL_STATE = 1,

	DETAILLED_MONTH = 2,
	DETAILLED_PATIENT_PRESSURE_MSB = 2,

	DETAILLED_YEAR = 3,
	DETAILLED_PATIENT_PRESSURE_LSB = 3,

	DETAILLED_HOUR = 4,
	DETAILLED_INSP_FLOW_MSB = 4,

	DETAILLED_MINUTE = 5,
	DETAILLED_INSP_FLOW_LSB = 5,

	DETAILLED_SECOND = 6,
	DETAILLED_EXH_FLOW_MSB = 6,

	DETAILLED_RESERVED1 = 7,
	DETAILLED_EXH_FLOW_LSB = 7,

	DETAILLED_RESERVED2 = 8,
	DETAILLED_LEAK = 8,

	End_Of_Table_Detailled_Monitoring = 9

} e_DETAILLED_MONITORING;

/******************************************************************************/
/*%C Trends Enum																					*/
/******************************************************************************/
/*%C For Usb and Com */

typedef enum
{
	TREND_DAY = 0,
	TREND_MONTH,
	TREND_YEAR,
	TREND_HOUR,
	TREND_MINUTE,
	TREND_SECOND,
	TREND_VENTIL_MODE,
	TREND_VENTIL_TYPE,
	TREND_MSB_P_MAX,
	TREND_LSB_P_MAX,
	TREND_MSB_AV_PEP,
	TREND_LSB_AV_PEP,
	TREND_MSB_LEAKAGE,
	TREND_LSB_LEAKAGE,
	TREND_MSB_AV_VOLUME,
	TREND_LSB_AV_VOLUME,
	TREND_IE_RATIO_NUMERATOR,
	TREND_IE_RATIO_DENOMINATOR,
	TREND_FREQUENCY,
	TREND_MSB_INSPIRATED_VOLUME,
	TREND_LSB_INSPIRATED_VOLUME,
	TREND_MSB_EXHALED_VOLUME,
	TREND_LSB_EXHALED_VOLUME,
	TREND_HEART_RATE,
	TREND_SPO2,
	End_Of_Table_Trends
} e_TREND ;

/******************************************************************************/
/*%C Events Enum																					*/
/******************************************************************************/
/*%C For Usb and Com */

typedef enum
{
	/* Common parameters */
  	EVENT_NB_ID = 0,		/*0  : Event number   		Unit	: _ */
  	EVENT_DAY_ID,			/*1  : day 						Unit : day */
  	EVENT_MON_ID,			/*2  : month 			   	Unit : month */
  	EVENT_YEA_ID,			/*3  : year 				   Unit : year - 2000 */
  	EVENT_HOU_ID,			/*4  : hour 			   	Unit : h */
  	EVENT_MIN_ID,		  	/*5  : minute 					Unit : min */
  	EVENT_SCD_ID,			/*6  : second					Unit : s */
  	EVENT_CPTMACHHOURMSB_ID,	/*7  : MSB machine hour    Unit : h * 256 */
  	EVENT_CPTMACHHOURLSB_ID,	/*8  : LSB machine hour 	Unit : h */
  	EVENT_MODE_ID,			/*9  : Mode Ventilation 	Unit : sans */
  	EVENT_TYPE_ID,			/*10 : Type Ventil			Unit : sans */
   EVENT_TRIGECONV_ID,	/*11 : Trig E Convention 	Unit : sans */
 	EVENT_PUNITCONV_ID,	/*12 : P Unit Convention   Unit : sans */
 	EVENT_CYCL_ID,			/*13 : Cycling					Unit : sans */
 	EVENT_24VMSB_ID,		/*14 : MSB24V Supply  		Unit : 10-1 V * 256 */
 	EVENT_24VLSB_ID,		/*15 : LSB24V Supply  		Unit : 10-1 V */
	EVENT_5VMSB_ID,		/*16 : MSB5V supply			Unit : 10-1 V * 256 */
 	EVENT_5VLSB_ID, 		/*17 : LSB5V supply			Unit : 10-1 V */
 	EVENT_WTDMSB_ID,		/*18 : MSB Watchdog volt	Unit : 10-1 V * 256 */
 	EVENT_WTDLSB_ID,		/*19 : LSB Watchdog volt	Unit : 10-1 V */
 	EVENT_TINTMSB_ID,		/*20 : MSB Internal Temp	Unit : 10-1 °C *256 */
 	EVENT_TINTLSB_ID,		/*21 : LSB Internal Temp	Unit : 10-1 °C */
 	EVENT_VBATMSB_ID,		/*22 : MSB Battery volt		Unit : 10-1 V * 256 */
 	EVENT_VBATLSB_ID,		/*23 : LSB Battery volt		Unit : 10-1 V */
 	EVENT_TBATMSB_ID,		/*24 : MSB Battery temp		Unit : 10-1 °C *256 */
 	EVENT_TBATLSB_ID,		/*25 : LSB Battery temp		Unit : 10-1 °C */
 	EVENT_QBATMSB_ID, 	/*26 : MSB Bat capacity 	Unit : ma/h	* 256 */
  	EVENT_QBATLSB_ID,		/*27 : LSB Bat	capacity 	Unit : ma/h */
 	EVENT_MBATMSB_ID, 		/*28 : MSB Bat minute 	Unit : min	* 256 */
  	EVENT_MBATLSB_ID,		/*29 : LSB Bat	minute 	Unit : min */
 	EVENT_FIO2_ID,			/*30 : FiO2						Unit : % */
 	EVENT_SPO2_ID,			/*31 : SpO2						Unit : % */
 	EVENT_FREQCAR_ID,		/*32 : Frequence cardiaque	Unit : p/min */
 	EVENT_PMAXMSB_ID,		/*33 : MSB Mesure Pmax     Unit : 10-1 mbar*256 */
 	EVENT_PMAXLSB_ID,		/*34 : LSB Mesure Pmax 		Unit : 10-1 mbar */
 	EVENT_PEPMSB_ID,		/*35 : MSB Mesure Pep 		Unit : 10-1 mbar*256 */
  	EVENT_PEPLSB_ID,		/*36 : LSB Mesure Pep 		Unit : 10-1 mbar */
 	EVENT_RAPIT_ID,		/*37 : Rapport I/T			Unit : % */
 	EVENT_RAPIEMSB_ID,	/*38 : MSB Rapport I/E		Unit : 10-1	* 256 */
 	EVENT_RAPIELSB_ID,	/*39 : LSB Rapport I/E		Unit : 10-1 */
 	EVENT_FREQ_ID,			/*40 : Mesure Fréquence    Unit : c/min */
 	EVENT_VTIMSB_ID,		/*41 : MSB Mesure Vti		Unit : ml * 256 */
  	EVENT_VTILSB_ID,		/*42 : LSB Mesure Vti 		Unit : ml */
 	EVENT_VTEMSB_ID,	   /*43 : MSB Mesure Vte  		Unit : ml * 256 */
 	EVENT_VTELSB_ID,		/*44 : LSB Mesure Vte 		Unit : ml */
  	EVENT_VMMSB_ID, 	 	/*45 : MSB Mesure Vm 	   Unit : 10-1l/min*256 */
  	EVENT_VMLSB_ID, 		/*46 : LSB Mesure Vm 	   Unit : 10-1l/min */
  	EVENT_LEAK_ID, 		/*47 : Mesure fuite			Unit : l/min */
  	EVENT_TIMSB_ID,		/*48 : MSB Mesure du TI		Unit : ms*256 */
  	EVENT_TILSB_ID,		/*49 : LSB Mesure du TI		Unit : ms */
  	EVENT_TEMSB_ID,		/*50 : MSB Mesure du TE		Unit : ms*256 */
  	EVENT_TELSB_ID, 		/*51 : LSB Mesure du TE		Unit : ms */
  	EVENT_SUPPLY_TYPE,	/*52 : Type d'alimentation	Unit : / */
  	EVENT_BATLEVEL_ID,	/*53 : Niveau de batterie 	Unit : % */
	EVENT_SETRELATIVE_PRESSURE_ID, /*54 : Relative pressure (ABS=0, REL=1)	*/
	EVENT_SETBAROMETRIC_COMP_ID, /*55 : Barometric compensation (OFF=0, YES=1)	*/
	EVENT_SETSOUND_LEVEL_ID, /*56 : Sound level (Unit : % )	*/
	EVENT_SETPEDIATRIC_CIRCUIT_ID, /*57 : Pediatric circuit (Adult=0, Pediatric=1)	*/
	EVENT_SETDISCONNECTION_DELAY_ID, /*58 : Disconnection delay (Unit:s)	*/
	EVENT_SETAPNEA_ALARM_ID, /*59 : Apnea alarm activation(OFF=0, YES=1)	*/
  	EVENT_SETSPO2MIN_ID,	/*60 : Reglage SpO2 min		Unit : % */
  	EVENT_SETSPO2MAX_ID,	/*61 : Reglage SpO2 max		Unit : % */
  	EVENT_SETFIO2_ID,		/*62 : Reglage FiO2 			Unit : % */
  	EVENT_SETFIO2MIN_ID,	/*63 : Reglage FiO2 min		Unit : % */
  	EVENT_SETFIO2MAX_ID,	/*64 : Reglage FiO2 max		Unit : % */ 

  	/* Specific	parameters  */ 
  	EVENT_SPECPAR_1_ID,			/*65 66*/
  	EVENT_SPECPAR_2_ID, 
  	EVENT_SPECPAR_3_ID,		  	/*67 68*/
  	EVENT_SPECPAR_4_ID, 
  	EVENT_SPECPAR_5_ID,		/*69 70*/
  	EVENT_SPECPAR_6_ID, 
  	EVENT_SPECPAR_7_ID,		  /*71 72*/
  	EVENT_SPECPAR_8_ID, 
  	EVENT_SPECPAR_9_ID,			/*73 74*/
  	EVENT_SPECPAR_10_ID, 
  	EVENT_SPECPAR_11_ID,		/*75 76*/
  	EVENT_SPECPAR_12_ID, 
  	EVENT_SPECPAR_13_ID,		/*77 78*/
  	EVENT_SPECPAR_14_ID, 
  	EVENT_SPECPAR_15_ID,			/*79 80*/
  	EVENT_SPECPAR_16_ID, 
  	EVENT_SPECPAR_17_ID,	 	/*81 82*/
  	EVENT_SPECPAR_18_ID, 
  	EVENT_SPECPAR_19_ID,			/*83 84*/
  	EVENT_SPECPAR_20_ID, 
  	EVENT_SPECPAR_21_ID,				/*85 86*/
  	EVENT_SPECPAR_22_ID, 
  	EVENT_SPECPAR_23_ID,		/*87 88*/
  	EVENT_SPECPAR_24_ID, 
  	EVENT_SPECPAR_25_ID,			/*89 90*/
	EVENT_SPECPAR_26_ID, 
	EVENT_SPECPAR_27_ID,			/*91 92*/
	EVENT_SPECPAR_28_ID, 
	EVENT_SPECPAR_29_ID,			/*93 94*/
	EVENT_SPECPAR_30_ID,
	EVENT_SPECPAR_31_ID,			/*95 96*/
  	EVENT_STATE_ID, 
  	EVENT_Last_Event_Parameter = EVENT_STATE_ID,
	End_Of_Table_Events			
} e_EVENT_PARAMETERS;


/******************************************************************************/
/*%C Settings Enum */
/******************************************************************************/
/*%C For Usb Only */

typedef enum
{
	/*%C Settings parameters */
	SETTINGS_COMPATIBILITY = 0,
	SETTINGS_MODE,
	SETTINGS_CYCLING_MODE_LSB,
	SETTINGS_CYCLING_MODE_MSB,
	SETTINGS_PRESSURE_UNIT_LSB,
	SETTINGS_PRESSURE_UNIT_MSB,
	SETTINGS_LOW_SPO2_LSB,
	SETTINGS_LOW_SPO2_MSB,
	SETTINGS_SPO2_LOW_SELECT_LSB,
	SETTINGS_SPO2_LOW_SELECT_MSB,
	SETTINGS_HIGH_SPO2_LSB,
	SETTINGS_HIGH_SPO2_MSB,
	SETTINGS_SPO2_HIGH_SELECT_LSB,
	SETTINGS_SPO2_HIGH_SELECT_MSB,
	SETTINGS_VOL_CONTROL_LSB,
	SETTINGS_VOL_CONTROL_MSB,
	SETTINGS_P_CONTROL_LSB,
	SETTINGS_P_CONTROL_MSB,
	SETTINGS_P_SUPPORT_LSB,
	SETTINGS_P_SUPPORT_MSB,
	SETTINGS_PEEP_LSB,
	SETTINGS_PEEP_MSB,
	SETTINGS_PEEP_NO_SELECT_LSB,
	SETTINGS_PEEP_NO_SELECT_MSB,
	SETTINGS_RISE_TIME_LSB,
	SETTINGS_RISE_TIME_MSB,
	SETTINGS_RAMP_LSB,
	SETTINGS_RAMP_MSB,
	SETTINGS_I_T_LSB,
	SETTINGS_I_T_MSB,
	SETTINGS_IE_NUMERATOR_LSB,
	SETTINGS_IE_NUMERATOR_MSB,
	SETTINGS_IE_DENOMINATOR_LSB,
	SETTINGS_IE_DENOMINATOR_MSB,
	SETTINGS_CONTROL_R_LSB,
	SETTINGS_CONTROL_R_MSB,
	SETTINGS_BACKUP_R_LSB,
	SETTINGS_BACKUP_R_MSB,
	SETTINGS_BACKUP_R_NO_SELECT_LSB,
	SETTINGS_BACKUP_R_NO_SELECT_MSB,
	SETTINGS_APNEA_LSB,
	SETTINGS_APNEA_MSB,
	SETTINGS_AUTO_APNEA_SELECT_LSB,
	SETTINGS_AUTO_APNEA_SELECT_MSB,
	SETTINGS_INSP_SENS_LSB,
	SETTINGS_INSP_SENS_MSB,
	SETTINGS_INSP_SENS_NO_SELECT_LSB,
	SETTINGS_INSP_SENS_NO_SELECT_MSB,
	SETTINGS_EXH_SENS_LSB,
	SETTINGS_EXH_SENS_MSB,
	SETTINGS_AUTO_EXH_SENS_SELECT_LSB,
	SETTINGS_AUTO_EXH_SENS_SELECT_MSB,
	SETTINGS_TARGET_VT_LSB,
	SETTINGS_TARGET_VT_MSB,
	SETTINGS_TARGET_VT_SELECT_LSB,
	SETTINGS_TARGET_VT_SELECT_MSB,
	SETTINGS_MAX_PRESSURE_LSB,
	SETTINGS_MAX_PRESSURE_MSB,
	SETTINGS_LOW_VTI_LSB,
	SETTINGS_LOW_VTI_MSB,
	SETTINGS_LOW_VTI_NO_SELECT_LSB,
	SETTINGS_LOW_VTI_NO_SELECT_MSB,
	SETTINGS_HIGH_VTI_LSB,
	SETTINGS_HIGH_VTI_MSB,
	SETTINGS_HIGH_VTI_NO_SELECT_LSB,
	SETTINGS_HIGH_VTI_NO_SELECT_MSB,
	SETTINGS_LOW_VTE_LSB,
	SETTINGS_LOW_VTE_MSB,
	SETTINGS_LOW_VTE_NO_SELECT_LSB,
	SETTINGS_LOW_VTE_NO_SELECT_MSB,
	SETTINGS_HIGH_VTE_LSB,
	SETTINGS_HIGH_VTE_MSB,
	SETTINGS_HIGH_VTE_NO_SELECT_LSB,
	SETTINGS_HIGH_VTE_NO_SELECT_MSB,
	SETTINGS_HIGH_PIP_LSB,
	SETTINGS_HIGH_PIP_MSB,
	SETTINGS_LOW_PIP_LSB,
	SETTINGS_LOW_PIP_MSB,
	SETTINGS_HIGH_R_LSB,
	SETTINGS_HIGH_R_MSB,
	SETTINGS_HIGH_R_NO_SELECT_LSB,
	SETTINGS_HIGH_R_NO_SELECT_MSB,
	SETTINGS_HIGH_LEAK_LSB,
	SETTINGS_HIGH_LEAK_MSB,
	SETTINGS_HIGH_LEAK_SELECT_LSB,
	SETTINGS_HIGH_LEAK_SELECT_MSB,
	SETTINGS_TI_MIN_LSB,
	SETTINGS_TI_MIN_MSB,
	SETTINGS_TI_MIN_AUTO_SELECT_LSB,
	SETTINGS_TI_MIN_AUTO_SELECT_MSB,
	SETTINGS_TI_MAX_LSB,
	SETTINGS_TI_MAX_MSB,
	SETTINGS_TI_MAX_AUTO_SELECT_LSB,
	SETTINGS_TI_MAX_AUTO_SELECT_MSB,
	SETTINGS_DISCONNECTION_DELAY_LSB,
	SETTINGS_DISCONNECTION_DELAY_MSB,
	SETTINGS_DISCONNECTION_DELAY_AUTO_LSB,
	SETTINGS_DISCONNECTION_DELAY_AUTO_MSB,
	SETTINGS_SIGH_SELECT_LSB,
	SETTINGS_SIGH_SELECT_MSB,
	SETTINGS_SIGH_VT_COEF_LSB,
	SETTINGS_SIGH_VT_COEF_MSB,
	SETTINGS_SIGH_CPT_LSB,
	SETTINGS_SIGH_CPT_MSB,
	SETTINGS_APNEA_ALARM_ACTIVATION_LSB,
	SETTINGS_APNEA_ALARM_ACTIVATION_MSB,
	SETTINGS_PEDIATRIC_CIRCUIT_LSB,
	SETTINGS_PEDIATRIC_CIRCUIT_MSB,
	SETTINGS_PRESSURE_SUPPORT_RELATIVE_LSB,
	SETTINGS_PRESSURE_SUPPORT_RELATIVE_MSB,
	End_Of_Table_Settings
} e_Settings;




/******************************************************************************/
/*%C USB enum */
/******************************************************************************/

typedef enum
{
	/*%C Serial Number */
	USB_SETTING_SERIAL_NUMBER_1 = 0,
	USB_SETTING_SERIAL_NUMBER_2,
	USB_SETTING_SERIAL_NUMBER_3,
	USB_SETTING_SERIAL_NUMBER_4,
	USB_SETTING_SERIAL_NUMBER_5,
	USB_SETTING_SERIAL_NUMBER_6,
	USB_SETTING_SERIAL_NUMBER_7,
	USB_SETTING_SERIAL_NUMBER_8,
	USB_SETTING_SERIAL_NUMBER_9,
	USB_SETTING_SERIAL_NUMBER_10,
	USB_SETTING_SERIAL_NUMBER_11,
	USB_SETTING_SERIAL_NUMBER_12,
	/*%C Date and Time */
	USB_SETTING_DATE_YEAR,
	USB_SETTING_DATE_MONTH,
	USB_SETTING_DATE_DAY,
	USB_SETTING_DATE_HOUR,
	USB_SETTING_DATE_MINUTE,
	USB_SETTING_DATE_SECOND,
	End_of_e_usb_frame_serialNumberAndDate
} e_USB_SerialNumberAndDate_Frame;


typedef enum
{
	/*%C Serial Number */
	USB_SERIAL_NUMBER_1 = 0,
	USB_SERIAL_NUMBER_2,
	USB_SERIAL_NUMBER_3,
	USB_SERIAL_NUMBER_4,
	USB_SERIAL_NUMBER_5,
	USB_SERIAL_NUMBER_6,
	USB_SERIAL_NUMBER_7,
	USB_SERIAL_NUMBER_8,
	USB_SERIAL_NUMBER_9,
	USB_SERIAL_NUMBER_10,
	USB_SERIAL_NUMBER_11,
	USB_SERIAL_NUMBER_12,
	End_of_e_usb_frame_serialNumber
} e_USB_SerialNumber_Frame;



typedef enum
{
	/*%C Insert Enum data */ 
	USB_SETTINGS_DATA = 0,
	USB_SETTINGS_MSB_CRC_FRAME,
	USB_SETTINGS_LSB_CRC_FRAME,
	End_of_e_usb_frame_setting
} e_USB_Settings_Frame;

/*%C Step Driver Order */
typedef enum 
{
	Usb_FirstStep = 0 ,
	Usb_ReadCurrentDirectoryNext,
	Usb_OpenFile,
	Usb_CreateFile,
	Usb_ReadFile,
	Usb_WriteSerialNumberAndDateAtIndex,
	Usb_WriteSerialNumberAndDateAtEndOfFile,
	Usb_WriteSerialNumberAtEndOfFile,
	Usb_WriteFileAtIndex,
	Usb_WriteAtTheEndOfFile,
	Usb_UpadateDateAndTime,
	Usb_WriteCRC,
	Usb_CloseFile,
	End_of_e_usb_transfer_apply
} e_USB_Transfer_Apply;



/*%C Step search File Driver */
typedef enum 
{
	FileSettingNext = 0 ,
	FileSettingNotFound,
	FileSettingFound,
	end_of_e_usb_file_setting
} e_USB_File_Settings;


/*%C Step choose file type extension */
typedef enum 
{
	SettingsType = 0 ,
	ContinuousRecordingType ,
	MonitoringTransferType,
	TrendsTransferType,
	EventsTransferType,
	end_of_e_usb_file_type
} e_USB_File_Type;

/*%C Frame Usb */
typedef enum
{
	USB_ID_FRAME = 0,
	/*%C Insert Enum data */ 
	USB_DATA,
	USB_End_Of_Continuous_Frame
} e_USB_Continuous_Frame;

/*%C NAND Flash State */ 
typedef enum
{
	NAND_FREE = 0,
	NAND_ERASE,
	NAND_MONIT_WRITE,
	NAND_MONIT_READ,
	NAND_TREND_WRITE,
	NAND_TREND_READ
} e_NAND_FLASH_STATE;





#endif




