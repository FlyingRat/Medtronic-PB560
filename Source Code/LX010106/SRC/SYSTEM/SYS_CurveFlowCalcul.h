/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_CurveFlowCalcul.h                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        DAta declaration for SYS_CurveFlowCalcul							      */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SYS_CURVE_FLOW_CALCUL_H
#define SYS_CURVE_FLOW_CALCUL_H


/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                          */
/******************************************************************************/
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DB_ComputeWrite(e_DB_COMPUTE Id,	UWORD16 Value);
extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);

#endif