/******************************************************************************/
/*                                                                            */
/* Project N°  : RB0505                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DB_Measurement.h                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*                                                                            */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef DB_MEASUREMENT_H
#define DB_MEASUREMENT_H


/******************************************************************************/
/*                         ENUM DECLARATION    	                	      		*/
/******************************************************************************/
typedef enum
 {
	BATTERY_TEMP = 0,			// Mesure de la température en 100ième de °C
	MEASURE_3V3,				// Mesure de la tension d'alimentation 3V3 en 100ième de V
	MEASURE_VACDC,				// Mesure de la tension ACDC provenant du secteur en 100ième de V
	I_BAT,						// Mesure du courant instantané batterie >0 courant de charge <0 courant de décharge en 10ième de mA
	MEASURE_VCHARGE,			// Mesure  de la tension fin de charge en 100ième de V
	TEMP_AMB,					// Mesure de la température ambiante en 100ième de °C	
	MEASURE_VDC,				// Mesure de la tension d'alimentation continue externe en 100ième de V
	MEASURE_24VUTIL,			// Mesure de la tension d'alimentation 24V en 100ième de V
	MEASURE_5V,					// Mesure de la tension d'alimentation 5V en 100ième de V	
	MEASURE_VBAT,				// Mesure de la tension de la batterie en 100ième de V
	
	IBAT_AVERAGE,				// Mesure du courant filtré batterie 
	IBAT_MEASURE_FILTERED,	// Mesure du courant de batterie filtré sur 100 ms en 10iéme de mA
	I_CHARGE_MAX_MEASURED,	// Mesure de l'intensité maxi en charge

	VBAT_MEASURE_FILTERED,	// Mesure de la tension V_Bat filtrée sur 100 ms en 100iéme de V

	VCHARGE_MEASURE_FILTERED,	// Mesure de la tension V_Charge filtrée sur 100 ms en 100iéme de V

	VACDC_MEASURE_FILTERED, // Mesure de la tension VACDC filtrée sur 100 ms en 100iéme de V

	VDC_MEASURE_FILTERED,	// Mesure de la tension VDC filtrée sur 100 ms en 100iéme de V

	MEASURE_FAN_SPEED,		// Mesure de la vitesse ventilateur de refroidissement
	
	COULOMB_COMPUTE_DISCHARGE_READY_FLAG, // Flag autorisant le coulomb metre à incrémenter son compteur en décharge
	
	COULOMB_COMPUTE_CHARGE_READY_FLAG,    // Flag autorisant le coulomb metre à incrémenter son compteur en charge

	end_of_db_measurement_table
	
} e_DB_Measurement;

/******************************************************************************/
/*                             BASE DECLARATION                               */
/******************************************************************************/

	#ifdef DECLARATION_MEASUREMENT_BASE
	
		UWORD16 DB_Measurement[end_of_db_measurement_table];
	
	#else
	
		extern UWORD16 DB_Measurement[end_of_db_measurement_table];
	
	#endif

#endif
