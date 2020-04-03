/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_BuzzerCmd.h                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  Data declaration for SEC_BuzzerCmd.c                                    */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   NONE                                                */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

#ifndef SEC_BUZZER_CMD_H
#define SEC_BUZZER_CMD_H

/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION                            */
/******************************************************************************/


/* Access to the decounter function */
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);

/* Access to the decounter function */
extern void TIM_InitDecounter(e_TIM_TABLE_ID offset_table,
                              UWORD16 value);

/* Access to the reading decounter function */
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);

/* Access to the buzzer driver */
extern void DRV_Buz_Sound(e_TYPE_SOUND sound,
                          e_NUMBER_BUZ NumBuzzer);

/* Access to the control write value */
extern void DB_ControlWrite(e_DB_CONTROL Id,
									 UWORD16 Value);

/* Access to the control read value */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);


#endif
