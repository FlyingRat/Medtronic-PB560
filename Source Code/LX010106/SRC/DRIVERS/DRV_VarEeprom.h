/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DRV_VarEeprom.h     		   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	declaration for var eeprom	            */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		      	                          	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None                        				  		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/


#ifndef DRV_VAR_EEPROM_H
#define DRV_VAR_EEPROM_H

/************************************************************************/
/*                           INCLUDE FILES		                        */
/************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Current.h"
#include "DB_Config.h"

/************************************************************************/
/*                   EXTERNAL CONSTANT DECLARATION                     	*/
/************************************************************************/

/*%C Eeprom start address for the address memorization                        */
/*%C This address is written in the file "_Legendair_US.ilo" for the          */
/*%C eeprom segment                                                           */
#define BEGIN_RAM_ADRESS_OF_EEP_DATA 0xFF000


#ifdef EEP_VAR_SOURCE
#define _EXTERN
#else
#define _EXTERN extern
#endif



/************************************************************************/
/*                   EXTERNAL VARIABLE DECLARATION                    	*/
/************************************************************************/


/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                    */
/************************************************************************/

/* ---------------------------------------------------------------------------*/
/*		 /\																						   */
/*    /!!\		ATTENTION, DECLARER EN 1er LE NUMERO DE VERSION						*/
/*   /____\																							*/
/* ---------------------------------------------------------------------------*/


#ifndef _BORLAND

	#ifndef _TASKING
/* Version number */
_EXTERN UWORD16  EEP_DB_Version_Number[end_of_db_version_table];

// Définition de la Table des para de réglage pour la configuration
_EXTERN UWORD16  EEP_DB_Config[end_of_db_config_table];

/* Setting parameter table for the VOL mode */
_EXTERN UWORD16  EEP_DB_VOL_Adjust[end_of_adjust_table];

/* Setting parameter table for the PRES mode */
_EXTERN UWORD16  EEP_DB_PRES_Adjust[end_of_adjust_table];

/* Setting parameter table for the PSV mode */
_EXTERN UWORD16  EEP_DB_PSV_Adjust[end_of_adjust_table];

/* Setting parameter table for the VSIMV mode */
_EXTERN UWORD16  EEP_DB_VSIMV_Adjust[end_of_adjust_table];

/* Setting parameter table for the PSIMV mode */
_EXTERN UWORD16  EEP_DB_PSIMV_Adjust[end_of_adjust_table];

/* Setting parameter table for the CPAP mode */
_EXTERN UWORD16  EEP_DB_CPAP_Adjust[end_of_adjust_table];

/* Setting parameter table for the TREND Data */
_EXTERN UWORD16  EEP_DB_TREND[end_of_db_trend_table];

/* PUST ERROR variable definition and location */
_EXTERN UWORD16 huge End_Of_Database;

/* PUST ERROR variable definition and location */
_EXTERN UWORD16 huge PUST_ERROR;



	#else
/* Version number */
_EXTERN UWORD16 _huge EEP_DB_Version_Number[end_of_db_version_table];

// Définition de la Table des para de réglage pour la configuration
_EXTERN UWORD16 _huge EEP_DB_Config[end_of_db_config_table];

/* Setting parameter table for the VOL mode */
_EXTERN UWORD16 _huge EEP_DB_VOL_Adjust[end_of_adjust_table];

/* Setting parameter table for the PRES mode */
_EXTERN UWORD16 _huge EEP_DB_PRES_Adjust[end_of_adjust_table];

/* Setting parameter table for the PSV mode */
_EXTERN UWORD16 _huge EEP_DB_PSV_Adjust[end_of_adjust_table];

/* Setting parameter table for the VSIMV mode */
_EXTERN UWORD16 _huge EEP_DB_VSIMV_Adjust[end_of_adjust_table];

/* Setting parameter table for the PSIMV mode */
_EXTERN UWORD16 _huge EEP_DB_PSIMV_Adjust[end_of_adjust_table];

/* Setting parameter table for the CPAP mode */
_EXTERN UWORD16 _huge EEP_DB_CPAP_Adjust[end_of_adjust_table];

/* Setting parameter table for the TREND Data */
_EXTERN UWORD16 _huge EEP_DB_TREND[end_of_db_trend_table];

/* PUST ERROR variable definition and location */
_EXTERN UWORD16 _huge End_Of_Database;

/* PUST ERROR variable definition and location */
_EXTERN UWORD16 _huge PUST_ERROR;
	#endif	


#else
_EXTERN UWORD16 EEP_DB_Version_Number[end_of_db_version_table];

// Définition de la Table des para de réglage pour la configuration
_EXTERN UWORD16 EEP_DB_Config[end_of_db_config_table];

/* Setting parameter table for the VOL mode */
_EXTERN UWORD16 EEP_DB_VOL_Adjust[end_of_adjust_table];

/* Setting parameter table for the PRES mode */
_EXTERN UWORD16 EEP_DB_PRES_Adjust[end_of_adjust_table];

/* Setting parameter table for the PSV mode */
_EXTERN UWORD16 EEP_DB_PSV_Adjust[end_of_adjust_table];

/* Setting parameter table for the VSIMV mode */
_EXTERN UWORD16 EEP_DB_VSIMV_Adjust[end_of_adjust_table];

/* Setting parameter table for the PSIMV mode */
_EXTERN UWORD16 EEP_DB_PSIMV_Adjust[end_of_adjust_table];

/* Setting parameter table for the CPAP mode */
_EXTERN UWORD16 EEP_DB_CPAP_Adjust[end_of_adjust_table];

/* Setting parameter table for the TREND Data */
_EXTERN UWORD16 EEP_DB_TREND[end_of_db_trend_table];

/* PUST ERROR variable definition and location */
_EXTERN UWORD16 End_Of_Database;

/* PUST ERROR variable definition and location */
_EXTERN UWORD16 PUST_ERROR;
#endif

#endif
