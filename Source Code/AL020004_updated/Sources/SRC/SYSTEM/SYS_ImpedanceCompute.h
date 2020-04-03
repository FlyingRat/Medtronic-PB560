/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_ImpedanceCompute.h                                     	 	*/
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


#ifndef SYS_IMPEDANCE_COMPUTE_H
#define SYS_IMPEDANCE_COMPUTE_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/	
/******************************************************************************/

	extern UBYTE DB_EEPROM_BAT_Read(e_EEPROM_BAT_DATA Id);
	extern void DB_EEPROM_BAT_Write(e_EEPROM_BAT_DATA Id, UBYTE Value);
	
	extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
	extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);

	extern void TIM_StartDecounter16(e_TIM_TABLE_ID_16,UWORD16);
	extern UWORD16 TIM_ReadValue16(e_TIM_TABLE_ID_16);
		
	extern UWORD16 DB_Measurement_Read(e_DB_Measurement Id);

#endif
