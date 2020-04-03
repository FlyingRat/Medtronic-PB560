/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  :DRV_EEPROM_BAT_Launch.h            					              	*/
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

#ifndef DRV_EEPROM_BAT_LAUNCH_H
#define DRV_EEPROM_BAT_LAUNCH_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/	
/******************************************************************************/
extern void DRV_EEPROM_BAT_INIT_NEW_BATTERY(void);
extern void DRV_EEPROM_BAT_ReadMemory(void);
extern void DRV_EEPROM_BAT_WriteMemory(void);
extern UWORD16 DRV_EEPROM_BAT_DifferenceZoneReadWrite(void);
extern UWORD32 TIM_ReadValue32(e_TIM_TABLE_ID_32);
extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);

#endif
