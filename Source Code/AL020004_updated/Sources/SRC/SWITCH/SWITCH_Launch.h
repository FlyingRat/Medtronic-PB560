/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SWITCH_Launch.c                                                */
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


#ifndef SWITCH_LAUNCH_H
#define SWITCH_LAUNCH_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/
/******************************************************************************/

extern void SYS_Voltage_Colapse_Compensation(void);
extern void SWITCH_Supply_Detection(void);
extern void SWITCH_State_Control(void);
extern void DRV_Switch(UBYTE Supply_Cmd);
extern UWORD16 DB_Control_Read(e_DB_Control Id);
extern void DB_Control_Write(e_DB_Control Id, UWORD16 Value);
extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);

#endif
