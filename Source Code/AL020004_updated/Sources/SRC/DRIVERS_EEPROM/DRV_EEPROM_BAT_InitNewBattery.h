/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  :DRV_EEPROM_BAT_InitNewBattery.h	       					         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        			  										      		  					*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef DRV_EEPROM_BAT_WRITE_H
#define DRV_EEPROM_BAT_WRITE_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/	
/******************************************************************************/
extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);
extern UWORD16 TIM_ReadValue16(e_TIM_TABLE_ID_16 offset_table);
extern void TIM_StartDecounter16(e_TIM_TABLE_ID_16 offset_table, UWORD16 value);
extern void DB_EEPROM_BAT_Write(e_EEPROM_BAT_DATA Id, UBYTE Value);

#endif
