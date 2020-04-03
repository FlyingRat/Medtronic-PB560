/******************************************************************************/
/*                                                                            */
/* Project N°  : RB0505                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DB_Config.h                                               */
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

#ifndef DB_CONFIG_H
#define DB_CONFIG_H

/******************************************************************************/
/*                           INCLUDE FILES		                      			*/
/******************************************************************************/



/******************************************************************************/
/*                           	#DEFINE		                      					*/
/******************************************************************************/

/******************************************************************************/
/*                         ENUM DECLARATION    	                	      		*/
/******************************************************************************/
// Base CONTROL
// Base CONFIG
//Attention la base config est signée
typedef enum {
	TOTAL_CAPACITY_BAT,				// mA/h
	REMAINING_CAPACITY_BAT,			// mA/h
	IMPEDANCE_BAT,   					// Impédance de la batterie 1 en mOhm
	EEPROM_ERROR,						// Une erreur eeprom a été détectée
	END_OF_BATTERY_ALARM,			// Une alarme "end of battery" est présente
	AGEING_BAT,							// Veillissement Bat
	ICHARGE_SETPOINT,					//Consigne du courant de charge
	CHARGE_CYCLE_NBR,					// Nombre de cycles de charge
	DISCHARGE_CYCLE_NBR,				// Nombre de cycles de Décharge
	end_of_db_config_table
} e_DB_Config;

/******************************************************************************/
/*                             BASE DECLARATION                               */
/******************************************************************************/
#ifdef DECLARATION_CONFIG_BASE

	UWORD16 DB_Config[end_of_db_config_table];

#else

	extern UWORD16 DB_Config[end_of_db_config_table];

#endif



#endif
