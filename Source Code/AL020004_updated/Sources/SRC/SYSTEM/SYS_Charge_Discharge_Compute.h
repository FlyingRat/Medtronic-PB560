/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Charge_Discharge_Compute.h                                 */
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef SYS_CHARGE_DISCHARGE_COMPUTE_H
#define SYS_CHARGE_DISCHARGE_COMPUTE_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/	
/******************************************************************************/

	extern UWORD16 DB_Control_Read(e_DB_Control Id);

	extern UWORD16 DB_EEPROM_BAT_Read(e_EEPROM_BAT_DATA Id);
	extern void DB_EEPROM_BAT_Write(e_EEPROM_BAT_DATA Id, UBYTE Value);

	extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
	extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);
	
	extern UWORD32 TIM_ReadValue32(e_TIM_TABLE_ID_32);

#endif
