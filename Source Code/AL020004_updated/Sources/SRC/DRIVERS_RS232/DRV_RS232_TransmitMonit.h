/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  :DRV_RS232_TransmitMonit.h  					              				*/
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


#ifndef DRV_RS232_TRANSMITMONIT_H
#define DRV_RS232_TRANSMITMONIT_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/
/******************************************************************************/

extern UWORD16 DB_Measurement_Read(e_DB_Measurement Id);
extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
extern UBYTE DB_EEPROM_BAT_Read(e_EEPROM_BAT_DATA Id);
extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);


#endif
