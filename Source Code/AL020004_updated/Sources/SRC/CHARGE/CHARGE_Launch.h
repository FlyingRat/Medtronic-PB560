/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CHARGE_Launch.h                                                */
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


#ifndef CHARGE_LAUNCH_H
#define CHARGE_LAUNCH_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/	
/******************************************************************************/

extern void CHARGE_Init(void);
extern void CHARGE_Charge(void);
extern void CHARGE_StopCharge(void);
extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);
extern void DB_Control_Write(e_DB_Control Id, UWORD16 Value);
extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
extern UWORD16 DB_Control_Read(e_DB_Control Id);
extern void TIM_StartDecounter16(e_TIM_TABLE_ID_16,UWORD16);
extern UWORD16 TIM_ReadValue16(e_TIM_TABLE_ID_16);
extern UWORD16 DB_Measurement_Read(e_DB_Measurement Id);
extern void DB_Measurement_Write(e_DB_Measurement Id, UWORD16 Value);



#endif
