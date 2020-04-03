/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  :SYS_Gas_Gauge_Percent.h            					          	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        			  										      		  					*/
/*%C          																  						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef SYS_GAS_GAUGE_PERCENT_H
#define SYS_GAS_GAUGE_PERCENT_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/	
/******************************************************************************/

	extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
	extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);

	extern UWORD16 DB_Control_Read(e_DB_Control Id);
	extern UWORD16 DB_Control_Write(e_DB_Control Id, UWORD16 Value);
	
	extern UWORD16 DB_Measurement_Read(e_DB_Measurement Id);
	extern void DB_Measurement_Write(e_DB_Measurement Id, UWORD16 Value);

	extern UBYTE DB_EEPROM_BAT_Read(e_EEPROM_BAT_DATA Id);
	extern UWORD16 SYS_Voltage_Capacity_Conversion(UWORD16 Fem, 
								UWORD16 PercentColapse,UWORD16 Ageing); 

#endif
