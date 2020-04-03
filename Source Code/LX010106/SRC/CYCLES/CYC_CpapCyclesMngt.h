/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_CpapCyclesMngt.h 														*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Data declration for CYC_CpapCyclesMngt.c								*/ 
/*           																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                           			*/
/******************************************************************************/

#ifndef CYC_CPAP_CYCLESMNGT_H
#define CYC_CPAP_CYCLESMNGT_H


/******************************************************************************/
/*                       EXTERNAL FUNCTION DECLARATION  */
/******************************************************************************/
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void TIM_StartCounter(e_TIM_TABLE_ID);
extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);
extern void DB_CopyMngt(void);
extern UWORD16 CYC_TriggerIDetection(void);
extern t_CYC_TiLimit CYC_TiLimitsCompute(void);
extern UWORD16 CYC_TriggerEDetection(void);
#endif