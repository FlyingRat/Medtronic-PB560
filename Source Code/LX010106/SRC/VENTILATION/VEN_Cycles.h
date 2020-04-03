/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : VEN_Cycles.h                												*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                 Ventilation cycles management             					*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                   					*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE					  												*/
/******************************************************************************/

#ifndef VEN_CYCLES_H
#define VEN_CYCLES_H

extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern void DB_CopyMngt(void);
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);
extern e_InspDetectType CYC_Pres_Vol_CyclesMngt(void);
extern e_InspDetectType CYC_Psvt_CyclesMngt(void);
extern e_InspDetectType CYC_CpapCyclesMngt(void);
extern e_InspDetectType CYC_Vsimv_CyclesMngt(void);
extern e_InspDetectType CYC_Psimv_CyclesMngt(void);		
extern void CYC_Exh_Controller_Phase(void);
extern void CYC_Insp_Controller_Phase(void);
extern UWORD16 CYC_TriggerIDetection(void);
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern UWORD16 DB_ConfigWrite(e_DB_CONFIG Id,
										UWORD16 Value);
extern void ACT_BrakePower(UBYTE percentage);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);
extern void DB_ComputeWrite(e_DB_COMPUTE Id, UWORD16 Value);
#endif
