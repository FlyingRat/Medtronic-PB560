/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Fio2Detection.h                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        Data declaration for SYS_Fio2Detection								      */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SYS_FIO2_DETECTION_H
#define SYS_FIO2_DETECTION_H


/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                          */
/******************************************************************************/
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
/* Access to the config write function */
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
/* Access to the decounter command                                            */
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 Value);
extern void DB_WriteDataInEepAndRam(UWORD16 xhuge *data_address,UWORD16 value);

#endif