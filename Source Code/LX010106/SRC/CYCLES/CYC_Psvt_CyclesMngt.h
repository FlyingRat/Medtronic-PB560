/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_Psvt_CyclesMngt.h 														*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Respiratory cycle management in PSVT  mode 						   */
/*           																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                           			*/
/******************************************************************************/

#ifndef CYC_PSVT_CYCLESMNGT_H
#define CYC_PSVT_CYCLESMNGT_H


/******************************************************************************/
/*                       EXTERNAL FUNCTION DECLARATION  */
/******************************************************************************/
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern void TIM_StartCounter(e_TIM_TABLE_ID);
extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);
extern void DB_CopyMngt(void);
extern UWORD16 CYC_TriggerIDetection(void);
extern UWORD16 CYC_TriggerEDetection(void);
extern t_CYC_TiLimit CYC_TiLimitsCompute(void);
#endif