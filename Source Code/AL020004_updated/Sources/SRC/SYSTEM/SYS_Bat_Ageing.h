/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Bat_Ageing.h 	            					              		*/
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

#ifndef SYS_BAT_AGEING_H
#define SYS_BAT_AGEING_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/	
/******************************************************************************/

	extern void TIM_StartDecounter16(e_TIM_TABLE_ID_16,UWORD16);
	extern UWORD16 TIM_ReadValue16(e_TIM_TABLE_ID_16);
	extern UWORD32 TIM_ReadValue32(e_TIM_TABLE_ID_32);

	extern UWORD16 DB_Measurement_Read(e_DB_Measurement Id);
	extern void DB_Measurement_Write(e_DB_Measurement Id, UWORD16 Value);

	extern UWORD16 DB_Control_Read(e_DB_Control Id);

	extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
	extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);

	extern void DB_EEPROM_BAT_Write(e_EEPROM_BAT_DATA Id, UBYTE Value);
	extern UWORD16 SYS_Voltage_Capacity_Conversion(UWORD16 Fem, 
								UWORD16 PercentColapse,UWORD16 Ageing); 

#endif
