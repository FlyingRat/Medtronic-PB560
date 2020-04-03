/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_EventMngt.h 				   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration for DB_EventMngt.c	*/
/*                                                                    		  	*/
/*%I 	Input Parameter : 			None 	        			                  		*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None	                      				  		*/
/******************************************************************************/
#ifndef DB_EVENTMNGT_H
#define DB_EVENTMNGT_H


#ifdef DECLARATION_EVENT_MNGT_H
/******************************************************************************/
/*                 CONSTANT DECLARATION				                          	*/
/******************************************************************************/


/* Start of event common parameters  */
const  	UWORD16 BeginCommonEventParam = EVENT_DAY_ID;
/* End of event common parameters  */
const  	UWORD16 EndCommonEventParam   = EVENT_SETFIO2MAX_ID;
/* Start of specific parameters  */
const  	UWORD16 BeginSpecificEventParam = EVENT_SPECPAR_1_ID;
/* End of specific parameters  */
const  	UWORD16 EndSpecificEventParam = EVENT_STATE_ID;
// Event data schema version (pre-LX010100 == 0)
const   UWORD16 EventDataSchemaVersion = 1;

/* Data list to save during an event record */

/************************************************************************/ 
/* WARNING !!															*/
/* The total number of parameters in this list must be kept even. 		*/
/* Else a trap exception will happen because of reading an even address */
/************************************************************************/ 

/* Common parameters to all modes */
#ifndef _BORLAND
const t_DB_CommonEventMngtParam DB_CommonEventMngtParam[EndCommonEventParam - BeginCommonEventParam + 1] = 
#else
const t_DB_CommonEventMngtParam DB_CommonEventMngtParam[EVENT_SETFIO2MAX_ID - EVENT_DAY_ID + 1] = 
#endif
{
/* Day (Unit:day) */
{DB_RTC,			DB_RTC_DAY_U16,		 			   FULL}, 	 
/* Month (Unit:month) */
{DB_RTC,			DB_RTC_MONTH_U16,	 			   FULL},
/* Year (Unit:year - 2000) */
{DB_RTC,			DB_RTC_YEAR_U16,	 			   FULL}, 
/* Hour (Unit:hour) */
{DB_RTC,			DB_RTC_HOUR_U16,	 			   FULL},   
/* Minute (Unit:minute) */
{DB_RTC,			DB_RTC_MINUTE_U16,	 			   FULL}, 	
/* Second (Unit:second) */
{DB_RTC,			DB_RTC_SECOND_U16,	 			   FULL}, 
/* MSB device hour (Unit:hour * 256) */
{DB_CONTROL,	CURRENT_MACHINE_COUNTER_HOUR_U16,	   MSB},	 
/* LSB device hour (Unit:hour) */
{DB_CONTROL,	CURRENT_MACHINE_COUNTER_HOUR_U16,	   LSB},   
/* Ventilation mode (Unit: VOL, PRES, PSV, VOL SIMV, PRES SIMV, CPAP) */
{DB_CONTROL,	CURRENT_MODE_U16,						FULL}, 
/* Ventilation type (Unit : Leak = 0, Valve = 1) */
{DB_CONTROL,    VALVE_DETECTED_U16,	 			   FULL},
/* Trigger E Convention (Unit : positive = 0, negative = 1) */
{DB_CONFIG,    TRIGG_E_POSITIVE,	 			   FULL},
/* Pression Unit (Unit : mbar = 0, cmH20 = 1, hPa = 2) */
{DB_CONFIG,    PRESSURE_UNIT_U16,	 			   FULL},
/* Schema Version (4 bits) + Cycling convention (I:E = 1, I/T = 0) */
{DB_CONFIG,    ADJUST_CYCLING_MODE_U16,	 			   FULL},
/* MSB 24V supply (Unit : 10-1 V) */
{DB_COMPUTE,		MEASURE_SUPPLY_24V_U16,				MSB},
/* LSB 24V supply (Unit : 10-1 V) */
{DB_COMPUTE,		MEASURE_SUPPLY_24V_U16,				LSB},
/* MSB battery buzzer voltage (Unit : 10-3 V) */
{DB_COMPUTE,		MEASURE_BATTERY_BUZZER_VOLTAGE_U16,	MSB},
/* LSB battery buzzer voltage (Unit : 10-3 V) */
{DB_COMPUTE,		MEASURE_BATTERY_BUZZER_VOLTAGE_U16,	LSB},
/* MSB Watchdog (Unit : 10-1 V) */
{DB_COMPUTE,    MEASURE_PFI_VOLTAGE_U16,	 			   MSB},
/* LSB Watchdog (Unit : 10-1 V) */
{DB_COMPUTE,    MEASURE_PFI_VOLTAGE_U16,	 			   LSB},
/* MSB Internal Temperature (Unit : 10-1 °C) */	 
{DB_POWERSUPPLY,		AMBIENT_TEMP_S16,  	MSB},
/* LSB Internal Temperature (Unit : 10-1 °C) */
{DB_POWERSUPPLY,		AMBIENT_TEMP_S16,  	LSB},
/* MSB Battery Voltage (Unit : 10-1 V) */	 
{DB_COMPUTE,		MEASURE_BATTERY_VOLTAGE_U16,		MSB},
/* LSB Battery Voltage (Unit : 10-1 V) */
{DB_COMPUTE,		MEASURE_BATTERY_VOLTAGE_U16,		LSB},
/* MSB Battery Temperature (Unit : 10-1 °C) */
{DB_POWERSUPPLY,		TEMP_BAT_S16,  	MSB},
/* LSB Battery Temperature (Unit : 10-1 °C) */
{DB_POWERSUPPLY,		TEMP_BAT_S16,  	LSB},
/* MSB Battery Capacity (Unit : ma/h) */
{DB_POWERSUPPLY,		CAPACITY_U16,  	MSB},			  
/* LSB Battery Capacity (Unit : ma/h) */
{DB_POWERSUPPLY,		CAPACITY_U16,  	LSB},
/* MSB Battery Minute : (min)			*/
{DB_POWERSUPPLY,		JAUGE_MINUTE_U16,  	MSB},			  
/* LSB Battery Minute : (min) */
{DB_POWERSUPPLY,		JAUGE_MINUTE_U16,  	LSB},
/* FiO2 measure (Unit : % ) */
{DB_COMPUTE,		MEASURE_FIO2,  					FULL},
/* SpO2 measure (Unit : % ) */
{DB_COMPUTE,		MEASURE_SPO2_U16, 					 	FULL},
/* Heart Rate (Unit : bpm )*/	  
{DB_COMPUTE,		MEASURE_HR_U16, 					 	FULL},
/* MSB Pip pressure measure (Unit:10-1 mbar * 256) */
{DB_COMPUTE,		COMPUTED_PIP_U16,					MSB},	 
/* LSB Pip pressure measure (Unit:10-1 mbar) */
{DB_COMPUTE,		COMPUTED_PIP_U16,					LSB},	 
/* MSB exhalated pressure measure (Unit:10-1 mbar * 256) */
{DB_COMPUTE,		COMPUTED_PEEP_U16,					MSB},  
/* LSB exhalated pressure measure (Unit:10-1 mbar) */
{DB_COMPUTE,		COMPUTED_PEEP_U16,					LSB},	 
/* Free */
{DB_NULL, 		    0,                               FULL},
/* Free */
{DB_NULL, 		    0,                               FULL},
/* Free */
{DB_NULL, 		    0,                               FULL},
/* Rate measure (Unit:cycle/min) */
{DB_COMPUTE,	MEASURE_R_U16,							FULL}, 
/* MSB inspirated volume measure (Unit:ml*256) */
{DB_COMPUTE,	COMPUTED_VTI_U16,						MSB},
/* LSB inspirated volume measure (Unit:ml) */
{DB_COMPUTE,	COMPUTED_VTI_U16,						LSB},  				
/* MSB exhalated volume measure (Unit:ml*256) */
{DB_COMPUTE,	COMPUTED_VTE_U16,						MSB},  
/* LSB exhalated volume measure (Unit:ml) */
{DB_COMPUTE,	COMPUTED_VTE_U16,						LSB},	 
/* MSB Volume per minute measure (Unit : ml) */  
{DB_COMPUTE,	COMPUTED_VMI_U16,						MSB},	 
/* LSB Average Volume measure (Unit : ml) */
{DB_COMPUTE,	COMPUTED_VMI_U16,						LSB},	 
/* Leakage measure (Unit : l/min) */
{DB_COMPUTE,	COMPUTED_LEAK_U16,					FULL},
/* MSB Ti measure (Unit:10-1s) */
{DB_COMPUTE,	MEASURE_TI_U16,						MSB},	 
/* LSB Ti measure (Unit:10-1s) */
{DB_COMPUTE,	MEASURE_TI_U16,						LSB},	 
/* MSB Te measure (Unit:10-1s) */
{DB_COMPUTE,	MEASURE_TE_U16,						MSB},	 
/* LSB Te measure (Unit:10-1s) */
{DB_COMPUTE,	MEASURE_TE_U16,						LSB},	 
/* Power type ( AC=0, DC=1, BATTERY=2, BAT DEFAULT=3) */
{DB_CONTROL,	SUPPLY_AC_DC_BAT_U16,				FULL}, 
/* Battery level (Unit:%)*/
{DB_POWERSUPPLY,	PER_CENT_BAT_U16,					FULL},
/* Relative pressure (ABS=0, REL=1)	*/
{DB_CONFIG,		PRESSURE_SUPPORT_RELATIVE_U16,						FULL},
/* Barometric compensation (OFF=0, YES=1)	*/
{DB_CONFIG,		ADJUST_BAROMETRIC_CORRECTOR_U16,						FULL},
/* Sound level (Unit : % )	*/
{DB_CONFIG,		SOUND_LEVEL_SELECT_U16,						FULL},
/* Pediatric circuit (Adult=0, Pediatric=1)	*/
{DB_CONFIG,		ADJUST_PEDIATRIC_CIRCUIT_U16,						FULL},
/* Disconnection delay (Unit:s)	*/
{DB_CURRENT,		ADJUST_DISCONNECTION_DELAY_U16,						FULL},
/* Apnea alarm activation (OFF=0, YES=1)	*/
{DB_CONFIG,		APNEA_ALARM_ACTIVATION,						FULL},
/* Voluntary stop alarm activation (OFF=0, YES=1)	*/
{DB_CONFIG,		VOLUNTARY_STOP_ALARM_ACTIVATION,						FULL},
/* SpO2 maxi setting (Unit : %)	*/
{DB_CONFIG,		ADJUST_HIGH_SPO2,						FULL},
/* FiO2 setting (Unit : %)	*/
{DB_CONFIG,		ADJUST_FIO2,							FULL},
/* FiO2 mini setting (Unit : %)	*/
{DB_CONFIG,		ADJUST_LOW_FIO2,						FULL},
/* FiO2 maxi setting (Unit : %)	*/
{DB_CONFIG,		ADJUST_HIGH_FIO2,						FULL}
};


/* Specific parameters for the PSV mode */
#ifndef _BORLAND
const t_DB_EventMngtParam DB_PsvEventMngtParam[EndSpecificEventParam - BeginSpecificEventParam + 1] = 
#else
const t_DB_EventMngtParam DB_PsvEventMngtParam[EVENT_STATE_ID -	EVENT_SPECPAR_1_ID + 1] = 
#endif
{
{ADJUST_P_SUPPORT_U16,	FULL}, /* Inspirated pression settting (Unit : mbar) */
{0,     STORAGE_CONSTANT}, /* Reserved */
{ADJUST_PEEP_U16,  	FULL}, /* Exhaltion pression setting (Unit : mbar) */
{ADJUST_RISE_TIME_U16, 	FULL}, /* Insp press slope setting (Unit : 1 to 4) */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_EXH_SENS_U16, FULL}, /* Exhalation trigger setting(Unit : %) */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_BACKUP_R_U16, FULL},/* Frequency setting(Unit : c/min) */
{ADJUST_INSP_SENS_U16, FULL}, /* Inspiration trigger setting(Unit : %) */
{ADJUST_APNEA_U16, FULL}, /* Apnea setting (Unit :s) */
{ADJUST_TARGET_VT_U16, MSB}, /* MSB Vol total setting Target (Unit : ml*256) */
{ADJUST_TARGET_VT_U16, LSB}, /* LSB Vol total setting Target (Unit : ml) */
{ADJUST_MAX_PRESSURE_U16,FULL},/* Insp pression maxi setting (Unit : mbar) */
{ADJUST_LOW_VTI_U16, MSB},/* MSB Tot Insp Vol min set Target (Unit : ml*256) */
{ADJUST_LOW_VTI_U16, LSB},/* LSB Tot Insp Vol min set Target (Unit : ml) */
{ADJUST_HIGH_VTI_U16, MSB},/* MSB Tot Insp Vol max set Target (Unit : ml*256) */
{ADJUST_HIGH_VTI_U16, LSB},/* LSB Tot Insp Vol max set Target (Unit : ml) */
{ADJUST_LOW_VTE_U16, MSB},/* MSB Tot Exhal Vol min set Target (Unit : ml*256) */
{ADJUST_LOW_VTE_U16, LSB},/* LSB Tot Exhal Vol min set Target (Unit : ml) */
{ADJUST_HIGH_VTE_U16, MSB},/* MSB Tot Exhal Vol max set Target (Unit : ml*256)*/
{ADJUST_HIGH_VTE_U16, LSB},/* LSB Tot Exhal Vol max set Target (Unit : ml) */
{ADJUST_HIGH_R_U16, FULL},/* Frequency maxi setting (Unit : C/min) */
{ADJUST_HIGH_LEAK_U16, FULL},/* Leak maxi setting (unit : l/min) */
{ADJUST_TI_MIN_U16,  FULL},/* Inspiration time mini setting (Unit : s) */
{ADJUST_TI_MAX_U16,  FULL},/* Inspiration time mini setting (Unit : s) */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{MEAS_ABS_PRESS_MMHG_U16,     MSB}, /* Reserved */
{MEAS_ABS_PRESS_MMHG_U16,     LSB}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{TRUE,    	STORAGE_CONSTANT},/* Reserved */
};

/* Specific parameters for the PRES mode */
#ifndef _BORLAND
const t_DB_EventMngtParam DB_PresEventMngtParam[EndSpecificEventParam - BeginSpecificEventParam + 1] = 
#else
const t_DB_EventMngtParam DB_PresEventMngtParam[EVENT_STATE_ID - EVENT_SPECPAR_1_ID + 1] = 
#endif
{
{ADJUST_P_CONTROL_U16,	FULL}, /* Inspirated pression settting (Unit : mbar) */
{0,     STORAGE_CONSTANT}, /* Reserved */
{ADJUST_PEEP_U16,  	FULL}, /* Exhaltion pression setting (Unit : mbar) */
{ADJUST_RISE_TIME_U16, 	FULL}, /* Insp press slope setting (Unit : 1 to 4) */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{ADJUST_CONTROL_R_U16,   FULL},/* Adjust Control R */
{ADJUST_INSP_SENS_U16, FULL}, /* Inspiration trigger setting(Unit : /) */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_TARGET_VT_U16, MSB}, /* MSB Vol total setting Target (Unit : ml*256) */
{ADJUST_TARGET_VT_U16, LSB}, /* LSB Vol total setting Target (Unit : ml) */
{ADJUST_MAX_PRESSURE_U16,FULL},/* Insp pression maxi setting (Unit : mbar) */
{ADJUST_LOW_VTI_U16, MSB},/* MSB Tot Insp Vol min set Target (Unit : ml*256) */
{ADJUST_LOW_VTI_U16, LSB},/* LSB Tot Insp Vol min set Target (Unit : ml) */
{ADJUST_HIGH_VTI_U16, MSB},/* MSB Tot Insp Vol max set Target (Unit : ml*256) */
{ADJUST_HIGH_VTI_U16, LSB},/* LSB Tot Insp Vol max set Target (Unit : ml) */
{ADJUST_LOW_VTE_U16, MSB},/* MSB Tot Exhal Vol min set Target (Unit : ml*256) */
{ADJUST_LOW_VTE_U16, LSB},/* LSB Tot Exhal Vol min set Target (Unit : ml) */
{ADJUST_HIGH_VTE_U16, MSB},/* MSB Tot Exhal Vol max set Target (Unit : ml*256)*/
{ADJUST_HIGH_VTE_U16, LSB},/* LSB Tot Exhal Vol max set Target (Unit : ml) */
{ADJUST_HIGH_R_U16, FULL},/* Frequency maxi setting (Unit : C/min) */
{ADJUST_HIGH_LEAK_U16, FULL},/* Leak maxi setting (unit : l/min) */
{ADJUST_TI_CONTROL_U16, FULL}, /* Inspiratory Time */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{MEAS_ABS_PRESS_MMHG_U16,     MSB}, /* Reserved */
{MEAS_ABS_PRESS_MMHG_U16,     LSB}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{TRUE,    	STORAGE_CONSTANT},/* Reserved */
};

/* Specific parameters for the VOL mode */
#ifndef _BORLAND
const t_DB_EventMngtParam DB_VolEventMngtParam[EndSpecificEventParam - BeginSpecificEventParam + 1] = 
#else
const t_DB_EventMngtParam DB_VolEventMngtParam[EVENT_STATE_ID - EVENT_SPECPAR_1_ID + 1] = 
#endif
{
{ADJUST_VOL_CONTROL_U16, MSB}, /* Inspirated volume settting (Unit : ml) */
{ADJUST_VOL_CONTROL_U16, LSB}, /* Inspirated volume settting (Unit : ml) */
{ADJUST_PEEP_U16,  	FULL}, /* Exhaltion pression setting (Unit : mbar) */
{ADJUST_RAMP_U16, 	FULL}, /* Insp press slope setting (Unit : 1 to 4) */
{0,    	STORAGE_CONSTANT},/* Reserved */
{0,    	STORAGE_CONSTANT},/* Reserved */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_CONTROL_R_U16,   FULL},/* Adjust Control R */
{ADJUST_INSP_SENS_U16, FULL}, /* Inspiration trigger setting(Unit : /) */
{0,    	STORAGE_CONSTANT},/* Reserved */
{0,    	STORAGE_CONSTANT},/* Reserved */
{0,    	STORAGE_CONSTANT},/* Reserved */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_LOW_PIP_U16, FULL},/* Min pressure setting (Unit : cmH2o) */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_HIGH_PIP_U16, FULL},/* Max pressure setting (Unit : cmH2o)  */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_LOW_VTE_U16, MSB},/* MSB Tot Exhal Vol min set Target (Unit : ml*256) */
{ADJUST_LOW_VTE_U16, LSB},/* LSB Tot Exhal Vol min set Target (Unit : ml) */
{ADJUST_HIGH_VTE_U16, MSB},/* MSB Tot Exhal Vol max set Target (Unit : ml*256)*/
{ADJUST_HIGH_VTE_U16, LSB},/* LSB Tot Exhal Vol max set Target (Unit : ml) */
{ADJUST_HIGH_R_U16, FULL},/* Frequency maxi setting (Unit : C/min) */
{0,     STORAGE_CONSTANT}, /* Reserved */
{ADJUST_TI_CONTROL_U16, FULL}, /* Inspiratory Time */
{0,     STORAGE_CONSTANT}, /* Reserved */
{ADJUST_SIGH_SELECT_U16,	FULL},	/* Sight Select (Unit: YES / NO) */
{ADJUST_SIGH_CPT_U16,		FULL},	/* Sight Counter (Unit : ) */
{ADJUST_SIGH_VT_COEF_U16,	FULL},	/* Sight Coefficient (Unit : ) */
{MEAS_ABS_PRESS_MMHG_U16,     MSB}, /* Reserved */
{MEAS_ABS_PRESS_MMHG_U16,     LSB}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{TRUE,    	STORAGE_CONSTANT},/* Reserved */
};

/* Specific parameters for the VSIMV mode */
#ifndef _BORLAND
const t_DB_EventMngtParam DB_VsimvEventMngtParam[EndSpecificEventParam - BeginSpecificEventParam + 1] = 
#else
const t_DB_EventMngtParam DB_VsimvEventMngtParam[EVENT_STATE_ID - EVENT_SPECPAR_1_ID + 1] = 
#endif
{
{ADJUST_VOL_CONTROL_U16, MSB}, /* Inspirated volume settting (Unit : ml) */
{ADJUST_VOL_CONTROL_U16, LSB}, /* Inspirated volume settting (Unit : ml) */
{ADJUST_PEEP_U16,  	FULL}, /* Exhaltion pression setting (Unit : mbar) */
{ADJUST_RISE_TIME_U16, 	FULL}, /* SIMV rise time(Unit : NA) */
{ADJUST_TI_CONTROL_U16,   FULL}, /* Inspiration time (Unit : s/10 */
{ADJUST_EXH_SENS_U16, FULL}, /* Exhalation trigger setting(Unit : %) */
{0,     STORAGE_CONSTANT}, /* Reserved */
{ADJUST_CONTROL_R_U16,   FULL},/* Adjust Control R */
{ADJUST_INSP_SENS_U16, FULL}, /* Inspiration trigger setting(Unit : /) */
{ADJUST_APNEA_U16, FULL}, /* Apnea setting (Unit :s) */
{ADJUST_P_SUPPORT_U16,	FULL}, /* Inspirated pression settting (Unit : mbar) */
{0,    	STORAGE_CONSTANT},/* Reserved */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_LOW_PIP_U16, FULL},/* Min pressure setting (Unit : cmH2o) */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_HIGH_PIP_U16, FULL},/* Max pressure setting (Unit : cmH2o)  */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_LOW_VTE_U16, MSB},/* MSB Tot Exhal Vol min set Target (Unit : ml*256) */
{ADJUST_LOW_VTE_U16, LSB},/* LSB Tot Exhal Vol min set Target (Unit : ml) */
{ADJUST_HIGH_VTE_U16, MSB},/* MSB Tot Exhal Vol max set Target (Unit : ml*256)*/
{ADJUST_HIGH_VTE_U16, LSB},/* LSB Tot Exhal Vol max set Target (Unit : ml) */
{ADJUST_HIGH_R_U16, FULL},/* Frequency maxi setting (Unit : C/min) */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{MEAS_ABS_PRESS_MMHG_U16,     MSB}, /* Reserved */
{MEAS_ABS_PRESS_MMHG_U16,     LSB}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{TRUE,    	STORAGE_CONSTANT},/* Reserved */
};

/* Specific parameters for the PSIMV mode */
#ifndef _BORLAND
const t_DB_EventMngtParam DB_PsimvEventMngtParam[EndSpecificEventParam - BeginSpecificEventParam + 1] = 
#else
const t_DB_EventMngtParam DB_PsimvEventMngtParam[EVENT_STATE_ID - EVENT_SPECPAR_1_ID + 1] =
#endif
{
{ADJUST_P_CONTROL_U16,  FULL}, /* Inspirated pressure settting (Unit : cmH2o) */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_PEEP_U16,  	FULL}, /* Exhaltion pression setting (Unit : mbar) */
{ADJUST_RISE_TIME_U16, 	FULL}, /* SIMV rise time(Unit : NA) */
{ADJUST_TI_CONTROL_U16,   FULL}, /* Inspiration time (Unit : s/10 */
{ADJUST_EXH_SENS_U16, FULL}, /* Exhalation trigger setting(Unit : %) */
{0,     STORAGE_CONSTANT}, /* Reserved */
{ADJUST_CONTROL_R_U16,   FULL},/* Adjust Control R */
{ADJUST_INSP_SENS_U16, FULL}, /* Inspiration trigger setting(Unit : /) */
{ADJUST_APNEA_U16, FULL}, /* Apnea setting (Unit :s) */
{ADJUST_P_SUPPORT_U16,	FULL}, /* Inspirated pression settting (Unit : mbar) */
{0,    	STORAGE_CONSTANT},/* Reserved */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_LOW_VTI_U16, MSB},/* MSB Tot Insp Vol min set Target (Unit : ml*256) */
{ADJUST_LOW_VTI_U16, LSB},/* LSB Tot Insp Vol min set Target (Unit : ml) */
{ADJUST_HIGH_VTI_U16, MSB},/* MSB Tot Insp Vol max set Target (Unit : ml*256) */
{ADJUST_HIGH_VTI_U16, LSB},/* LSB Tot Insp Vol max set Target (Unit : ml) */
{ADJUST_LOW_VTE_U16, MSB},/* MSB Tot Exhal Vol min set Target (Unit : ml*256) */
{ADJUST_LOW_VTE_U16, LSB},/* LSB Tot Exhal Vol min set Target (Unit : ml) */
{ADJUST_HIGH_VTE_U16, MSB},/* MSB Tot Exhal Vol max set Target (Unit : ml*256)*/
{ADJUST_HIGH_VTE_U16, LSB},/* LSB Tot Exhal Vol max set Target (Unit : ml) */
{ADJUST_HIGH_R_U16, FULL},/* Frequency maxi setting (Unit : C/min) */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{MEAS_ABS_PRESS_MMHG_U16,     MSB}, /* Reserved */
{MEAS_ABS_PRESS_MMHG_U16,     LSB}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{TRUE,    	STORAGE_CONSTANT},/* Reserved */
};

/* Specific parameters for the CPAP mode */
#ifndef _BORLAND
const t_DB_EventMngtParam DB_CpapEventMngtParam[EndSpecificEventParam - BeginSpecificEventParam + 1] = 
#else
const t_DB_EventMngtParam DB_CpapEventMngtParam[EVENT_STATE_ID - EVENT_SPECPAR_1_ID + 1] = 
#endif
{
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{ADJUST_PEEP_U16,  	FULL}, /* Exhaltion pression setting (Unit : mbar) */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{ADJUST_APNEA_U16, FULL}, /* Apnea setting (Unit :s) */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,    	STORAGE_CONSTANT},/* Reserved */
{0,    	STORAGE_CONSTANT},/* Reserved */
{ADJUST_LOW_VTI_U16, MSB},/* MSB Tot Insp Vol min set Target (Unit : ml*256) */
{ADJUST_LOW_VTI_U16, LSB},/* LSB Tot Insp Vol min set Target (Unit : ml) */
{ADJUST_HIGH_VTI_U16, MSB},/* MSB Tot Insp Vol max set Target (Unit : ml*256) */
{ADJUST_HIGH_VTI_U16, LSB},/* LSB Tot Insp Vol max set Target (Unit : ml) */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{ADJUST_HIGH_R_U16, FULL},/* Frequency maxi setting (Unit : C/min) */
{ADJUST_HIGH_LEAK_U16, FULL}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{MEAS_ABS_PRESS_MMHG_U16,     MSB}, /* Reserved */
{MEAS_ABS_PRESS_MMHG_U16,     LSB}, /* Reserved */
{0,     STORAGE_CONSTANT}, /* Reserved */
{TRUE,    	STORAGE_CONSTANT},/* Reserved */
};

#else
/******************************************************************************/
/*                 CONSTANT DECLARATION				                          	*/
/******************************************************************************/

/* Particular parameters to modify if one of the previous list is modified  */

/* Start of event common parameters  */
extern const  	UWORD16 BeginCommonEventParam;			
/* End of event common parameters  */
extern const  	UWORD16 EndCommonEventParam;  	              
/* Start of specific parameters  */
extern const  	UWORD16 BeginSpecificEventParam;
/* End of specific parameters  */
extern const  	UWORD16 EndSpecificEventParam;		


/* Data list to save during an event record */
/* Common parameters to all modes */

extern const t_DB_CommonEventMngtParam DB_CommonEventMngtParam[] ;

/* Specific parameters for the PSV mode */
extern const t_DB_EventMngtParam DB_PsvEventMngtParam[];

/* Specific parameters for the PRES mode */
extern const t_DB_EventMngtParam DB_PresEventMngtParam[];

/* Specific parameters for the VOL mode */
extern const t_DB_EventMngtParam DB_VolEventMngtParam[];

/* Specific parameters for the VSIMV mode */
extern const t_DB_EventMngtParam DB_VsimvEventMngtParam[];

/* Specific parameters for the CPAP mode */
extern const t_DB_EventMngtParam DB_CpapEventMngtParam[];
#endif


/******************************************************************************/
/*                 EXTERNAL FUNCTION DECLARATION	                          	*/
/******************************************************************************/

/* Access to the config read value */
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
/* Access to the control read value */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
/* Access to the control read value */
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
/* Access to the control read value */
extern UWORD16 DB_RTCRead(e_DB_RTC Id);
/* Access to the control read value */
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
/* Access to the Powersupply read value */
extern UWORD16 DB_PowerSupplyRead(e_DB_POWERSUPPLY Id);
/* Access to the flash event management */
extern void DRV_EVENT_PushEvent(e_EVENT_PARAMETERS Id_Event,UBYTE value);


#endif
