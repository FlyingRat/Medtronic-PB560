/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_PowerSupply.h	 		   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : datas for Power Supply Base							*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				None                                  		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			None		 	                 				  		*/
/******************************************************************************/
#ifndef POWERSUPPLY_H
#define POWERSUPPLY_H

#include "typedef.h"


/******************************************************************************/
/*                     ENUM DECLARATION				                         */
/******************************************************************************/

/* Base PowerSupply	  */
typedef enum {
   V_BAT_U16 = 0,
	TEMP_BAT_S16,
	BAT_CYCLES_U16,	/* Identifier; Nb cycles */
	BAT_STATE_U16,	   /* Default...*/
	POWER_TYPE_U16,
	JAUGE_MINUTE_U16,
	JAUGE_HOUR_DISPLAY_U16,
	JAUGE_MINUTE_DISPLAY_U16,
	JAUGE_AVALAIBLE_U16,
	PER_CENT_BAT_U16,
	NO_PRESENCE_BAT_U16,
	BAT_KO_U16,
	CHARGE_KO_U16,
	UNKNOWN_BATTERY_U16,
 	AMBIENT_TEMP_S16,
	BATTERY_END_U16,
	BATTERY_LOW_U16,
	FIRST_DATE_DAY_U16,
	FIRST_DATE_MONTH_U16,
	FIRST_DATE_YEAR_U16,
	COOLING_FAN_FAILURE_FLAG_U16,
	AMBIENT_TEMP_OUTOFBOUNDS_U16,
	FAILURE_24V_FLAG_U16,
	BAT_TEMP_OUTOFBOUNDS_U16,
	SUPPLY_MEASURE_FAILURE_U16,
   POWER_SUPPLY_VERSION_NUMBER_0,
   POWER_SUPPLY_VERSION_NUMBER_1,
   POWER_SUPPLY_VERSION_NUMBER_2,
   SUPPLIER_U16,
   CAPACITY_U16,
    CAPACITY_THEORICAL_U16,
	FIRST_DATE_HOUR_U16,
	FIRST_DATE_MINUTE_U16,
	FIRST_DATE_SECOND_U16,
   AGING_U16,
	end_of_db_powersupply_table
} e_DB_POWERSUPPLY;

/* Battery_State */
#define BAT_IDLE							0
#define BAT_CHARGE						1
#define BAT_DISCHARGE					2

#ifdef DECLARATION_POWERSUPPLY_BASE
/******************************************************************************/
/*                     CONSTANT DECLARATION			                         */
/******************************************************************************/
/* Base Control array */
UWORD16 DB_powerSupply[end_of_db_powersupply_table];

#else
/******************************************************************************/
/*                     CONSTANT DECLARATION			                           */
/******************************************************************************/
/* Base Control array */
extern UWORD16 DB_powerSupply[end_of_db_powersupply_table];
#endif

#endif
