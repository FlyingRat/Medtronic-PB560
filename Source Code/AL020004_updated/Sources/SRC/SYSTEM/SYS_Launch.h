/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  :SYS_Launch.h            					              					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        			  										      		  					*/
/*%C          																  						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                             	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef SYS_LAUNCH_H
#define SYS_LAUNCH_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/	
/******************************************************************************/
extern UWORD16 DB_EEPROM_BAT_Read(e_EEPROM_BAT_DATA Id);
extern void DB_EEPROM_BAT_Write(e_EEPROM_BAT_DATA Id, UBYTE Value);
extern UWORD16 DB_Control_Read(e_DB_Control Id);
extern UWORD16 DB_Control_Write(e_DB_Control Id, UWORD16 Value);
extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);
extern UWORD32 TIM_ReadValue32(e_TIM_TABLE_ID_32);
extern void TIM_StartDecounter32(e_TIM_TABLE_ID_32 offset_table,UWORD32 value);
extern void SYS_Voltage_Colapse_Compensation(void);

extern void SYS_Gas_Gauge_Percent(void);
extern void SYS_Bat_Ageing(void);
extern void	SYS_Gas_Gauge_Minute(void);
extern void	SYS_Charge_Discharge_Compute(void);
extern void SYS_ImpedanceCompute(void);
extern void	SYS_Led_Management(void);

#endif
