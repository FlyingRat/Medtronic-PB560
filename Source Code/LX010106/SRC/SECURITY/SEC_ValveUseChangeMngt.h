/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ValveUseChangeMngt.h                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Data declaration for SEC_ValveUseChangeMngt.c                          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SEC_VALVE_USE_CHANGE_MNGT_H
#define SEC_VALVE_USE_CHANGE_MNGT_H

/******************************************************************************/
/*                EXTERNAL FUNCTION DECLARATION                               */
/******************************************************************************/
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);

extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);

extern void DB_EventMngt (UWORD16 Value);

extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);

extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, 
								e_DB_ALARMS_STATE Value);

extern void SEC_ValveAlarmsToReset(void);

extern void DB_ControlWrite(e_DB_CONTROL Id,UWORD16 Value);

#endif