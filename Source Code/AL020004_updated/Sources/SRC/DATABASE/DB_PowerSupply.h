/******************************************************************************/
/*																			  							*/
/* Project Number	: 	RB0505      			     		                  			*/
/*																			  							*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_PowerSupply.h	 		   				                  	  	*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : datas for Power Supply Base					  		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :		None                                  		  			*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 		None		 	                 			  				*/
/******************************************************************************/
#ifndef DB_POWERSUPPLY_H
#define DB_POWERSUPPLY_H




/******************************************************************************/
/*                     ENUM DECLARATION				                         	*/
/******************************************************************************/

/* Base PowerSupply	  																			*/
typedef enum 
{

/******************************************************************************/
/* Trame echange CPU - Carte Gestion Alimentation par SPI 							*/
/* Carte alimentation vers CPU																*/
   V_BAT_U16 = 0,
	TEMP_BAT_S16,		
	BAT_STATE_U16,
	POWER_TYPE_U16,
	GAUGE_MINUTE_U16,
	GAUGE_AVALAIBLE_U16,
	PER_CENT_BAT_U16,
	NO_BAT_FLAG,
	BAT_OPENED_FLAG,
	CHARGE_FAIL_FLAG,
	BAT_UNCHARGEABLE_FLAG,
	CHARGE_TIME_TOO_LONG_FLAG,
	ABNORMAL_IBAT_FLAG,
	VOLT_OUT_OF_BOUNDS_FLAG,
	INIT_CHARGEUR_FAIL,
	UNKNOWN_BATTERY_FLAG,
	AMBIENT_TEMP_S16,
	END_OF_BATTERY_FLAG,
	LOW_BATTERY_FLAG,
	CHARGE_TEMP_FAIL_FLAG,
	DISCHARGE_TEMP_FAIL_FLAG,
	FAILURE_5V_FLAG,
	FAILURE_3V_FLAG,
	FAILURE_MES_VACDC_FLAG,
	FAILURE_MES_VDC_FLAG,
	TEMP_SENSOR_FAILURE_FLAG,
	FAILURE_24V_FLAG,
	AMBIENT_TEMP_TOO_HIGH,
	COOLING_FAN_FAILURE_FLAG,
	BAT_SUPPLIER,
/******************************************************************************/


/******************************************************************************/
/* Trame echange CPU - Carte Gestion Alimentation par SPI 							*/
/* Carte CPU vers Carte alimentation														*/
	VENTIL_AUTHORIZATION,
	MAINTENANCE_MODE,
	CALIBRATION_MODE,
/******************************************************************************/


/******************************************************************************/
/* FLAG SPI Communication																		*/
	COMMUNICATION_FAILURE_FLAG,
	NO_COMMUNICATION_CPU,
/******************************************************************************/


/******************************************************************************/
/* FLAG EEPROM Communication																	*/
	COMMUNICATION_EEPROM_FAILURE,
	READ_DATA_EEPROM_BAT_FAILURE,
	WRITE_DATA_EEPROM_BAT_FAILURE,
/******************************************************************************/


/******************************************************************************/
/* FLAG BATTERY Information																	*/
	BAT_CHANGING_DETECTION,
	NEW_BAT_FLAG,
	BAT_CAPACITY_THEORICAL_FOR_GAUGE,
	BAT_CAPACITY_COMPENSATED,
	BAT_AGEING,
	BAT_AGEING_COMPUTED,
	BAT_IMPEDANCE,
	DISCHARGE_BAT_CYCLES,
	FEM_COMPUTE,
	BATTERY_VOLTAGE_COLAPSE,

/******************************************************************************/

	end_of_db_Powersupply_table
} e_DB_POWERSUPPLY;


/******************************************************************************/
/*                     CONSTANT DECLARATION			                         	*/
/******************************************************************************/

#ifdef DECLARATION_POWERSUPPLY_BASE

	/* Base Power supply array */
	UWORD16 DB_powerSupply[end_of_db_Powersupply_table];

#else

	/* Base Power supply array */
	extern UWORD16 DB_powerSupply[end_of_db_Powersupply_table];

#endif

#endif 
