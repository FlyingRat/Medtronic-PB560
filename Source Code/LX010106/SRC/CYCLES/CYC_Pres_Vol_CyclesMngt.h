/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_Pres_Vol_CyclesMngt.h */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Respiratory cycle management in Pres and Vol mode */ 
/*           */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                           */
/******************************************************************************/

#ifndef CYC_PRES_VOL_CYCLESMNGT_H
#define CYC_PRES_VOL_CYCLESMNGT_H




/******************************************************************************/
/*                       EXTERNAL FUNCTION DECLARATION  */
/******************************************************************************/
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern void TIM_StartCounter(e_TIM_TABLE_ID);
extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);
extern void DB_CopyMngt(void);
extern UWORD16 CYC_TriggerIDetection(void);
extern void DB_CurrentWrite(e_DB_ADJUST_CURRENT Id, UWORD16 Value);

#endif