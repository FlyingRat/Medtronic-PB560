/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_Psimv_CyclesMngt.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Respiratory cycle management in Pres SIMV mode */ 
/*           */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                           */
/******************************************************************************/


#ifndef CYC_VSIMV_CYCLESMNGT_H
#define CYC_VSIMV_CYCLESMNGT_H

						  

/******************************************************************************/
/*                       EXTERNAL FUNCTION DECLARATION  */
/******************************************************************************/
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void TIM_StartCounter(e_TIM_TABLE_ID);
extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);
extern void DB_CopyMngt(void);
extern UWORD16 CYC_TriggerIDetection(void);
extern UWORD16 CYC_TriggerEDetection(void);
extern t_CYC_TiLimit CYC_TiLimitsCompute(void);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 Value);
#endif
