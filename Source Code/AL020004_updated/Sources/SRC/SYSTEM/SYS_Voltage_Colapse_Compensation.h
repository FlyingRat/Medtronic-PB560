/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Voltage_Colapse_Compesation.h 	            	      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        			  										      		  					*/
/*%C          																  						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SYS_VOLTAGE_COLAPSE_COMPENSATION_H
#define SYS_VOLTAGE_COLAPSE_COMPENSATION_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 		      */	
/******************************************************************************/
extern UWORD16 DB_Measurement_Read(e_DB_Measurement Id);
extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);
extern void TIM_StartDecounter32(e_TIM_TABLE_ID_32 offset_table,UWORD32 value);
extern UWORD32 TIM_ReadValue32(e_TIM_TABLE_ID_32);

#endif
