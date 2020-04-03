/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SWITCH_State_Control.h                                      	*/
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


#ifndef SWITCH_STATE_CONTROL_H
#define SWITCH_STATE_CONTROL_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/
/******************************************************************************/

extern UWORD16 DB_Control_Read(e_DB_Control Id);
extern void DB_Control_Write(e_DB_Control Id, UWORD16 Value);
extern void DRV_Switch(UBYTE Supply_Cmd);
extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);
extern UWORD16 TIM_ReadValue16(e_TIM_TABLE_ID_16);
extern void TIM_StartDecounter16(e_TIM_TABLE_ID_16 offset_table, UWORD16 value);
extern UWORD16 DB_Measurement_Read(e_DB_Measurement Id);


#endif
