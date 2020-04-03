/******************************************************************************/
/*                                                                            */
/* Project N°  : RB0505                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DB_EEPROM_BAT.h                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          				Datas for EEPROM BAttery Base                         */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*                                                                            */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef DB_EEPROM_BAT_H
#define DB_EEPROM_BAT_H


/******************************************************************************/
/*                         ENUM DECLARATION    	                	      		*/
/******************************************************************************/
typedef enum
{  
	/*Données fixes stockées en page n°1 de l'EEPROM batterie (32 octets max)	*/
	DATA_FIXE_IDENTIFIANT_1 = 0,		/* Identifiant sur 8 octets					*/
	DATA_FIXE_IDENTIFIANT_2 = 1,
	DATA_FIXE_IDENTIFIANT_3 = 2,
	DATA_FIXE_IDENTIFIANT_4 = 3,
	DATA_FIXE_IDENTIFIANT_5 = 4,
	DATA_FIXE_IDENTIFIANT_6 = 5,
	DATA_FIXE_IDENTIFIANT_7 = 6,
	DATA_FIXE_IDENTIFIANT_8 = 7,
	DATA_FIXE_CAPACITE_1 = 8,			/* Capacité sur 2 octets						*/
	DATA_FIXE_CAPACITE_2 = 9,
	DATA_FIXE_DATE_1 = 10,				/* Date sur 6 octets								*/
	DATA_FIXE_DATE_2 = 11,
	DATA_FIXE_DATE_3 = 12,
	DATA_FIXE_DATE_4 = 13,
	DATA_FIXE_DATE_5 = 14,
	DATA_FIXE_DATE_6 = 15,
	/*Données variables stockées en page n°2 de l'EEPROM batterie (32 octets max)	*/
	DATA_VARIABLE_BAT_AGEING_1 = 32,	/* Veillissement sur 1 octet					*/
	DATA_VARIABLE_BAT_IMPEDANCE_1 = 33,	/* Impédance sur 2 octets 	(MSB)			*/
  	DATA_VARIABLE_BAT_IMPEDANCE_2 = 34,	/*									(LSB)			*/
	DATA_VARIABLE_NBR_CYCLE_1 = 35,		/* Nombre de cycles sur 2 octets	(MSB)	*/
	DATA_VARIABLE_NBR_CYCLE_2 = 36,		/*											(LSB)	*/
	DATA_VARIABLE_FIRST_BATTEY_USE = 37,
	DATA_VARIABLE_LIBRE_2 = 38,
	DATA_VARIABLE_LIBRE_3 = 39,
	/* Numemro de série de l'appareil utilisé sur 16 octets	*/
	DATA_VARIABLE_N_SERIE_1 = 40,	
	DATA_VARIABLE_N_SERIE_2 = 41,
	DATA_VARIABLE_N_SERIE_3 = 42,
	DATA_VARIABLE_N_SERIE_4 = 43,
	DATA_VARIABLE_N_SERIE_5 = 44,
	DATA_VARIABLE_N_SERIE_6 = 45,
	DATA_VARIABLE_N_SERIE_7 = 46,
	DATA_VARIABLE_N_SERIE_8 = 47,
	DATA_VARIABLE_N_SERIE_9 = 48,
	DATA_VARIABLE_N_SERIE_10 = 49,
	DATA_VARIABLE_N_SERIE_11 = 50,
	DATA_VARIABLE_N_SERIE_12 = 51,
	DATA_VARIABLE_N_SERIE_13 = 52,
	DATA_VARIABLE_N_SERIE_14 = 53,
	DATA_VARIABLE_N_SERIE_15 = 54,
	DATA_VARIABLE_N_SERIE_16 = 55,
	/*Page n°1 + Page n°2 = 64 octets														*/	
	EEPROM_BAT_EnOfTableData = 64	
} e_EEPROM_BAT_DATA;


/******************************************************************************/
/*                             BASE DECLARATION                               */
/******************************************************************************/
	#ifdef DECLARATION_EEPROM_BAT_BASE

		/*%C 64 bytes array data read EEPROM Battery										*/
		UBYTE Ram_Read_Bat[EEPROM_BAT_EnOfTableData];
		/*%C 32 bytes array data write EEPROM Battery									*/
		UBYTE Ram_Write_Bat[EEPROM_BAT_EnOfTableData-DATA_VARIABLE_BAT_AGEING_1];

	#else

		/*%C 64 bytes array data read EEPROM Battery										*/
		extern UBYTE Ram_Read_Bat[EEPROM_BAT_EnOfTableData];
		/*%C 32 bytes array data write EEPROM Battery									*/
		extern UBYTE Ram_Write_Bat[EEPROM_BAT_EnOfTableData
												- DATA_VARIABLE_BAT_AGEING_1];

	#endif

#endif
