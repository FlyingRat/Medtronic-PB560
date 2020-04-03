/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CHARGE_Init.h                                                	*/
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


#ifndef CHARGE_INIT_H
#define CHARGE_INIT_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/	
/******************************************************************************/

extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
extern UWORD16 DB_Control_Read(e_DB_Control Id);
extern UWORD16 TIM_ReadValue16(e_TIM_TABLE_ID_16);
extern UWORD16 DB_Measurement_Read(e_DB_Measurement Id);
extern UBYTE CHARGE_Loop_Controller(UWORD16 Setpoint, UWORD16 Measure);

extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);
extern void DB_Control_Write(e_DB_Control Id, UWORD16 Value);
extern void TIM_StartDecounter16(e_TIM_TABLE_ID_16,UWORD16);


#endif
