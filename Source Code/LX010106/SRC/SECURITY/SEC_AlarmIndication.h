/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_AlarmIndication.h                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  Data declaration for SEC_AlarmIndication.c.                             */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   NONE                                                */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

#ifndef ALARM_INDICATION_H
#define ALARM_INDICATION_H

#ifdef DECLARATION_ALARM_INDICATION
/******************************************************************************/
/*                   VARIABLE DECLARATION    			                        */
/******************************************************************************/

/* Alarm level declaration */
   e_DB_ALARM_LEVEL_PRIORITY Alarm_Level = WP;

/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION                            */
/******************************************************************************/

/* Access to the config write value */
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value);
/* Access to the config read value */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

/* Access to the alarm status base (read) */
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);

/* Access to the keyboard event read function */
extern UWORD16 DB_KeyboardEventRead(e_DB_KEYBOARD_EVENT_ID Id);

/* Access to the keyboard event write function */
extern void DB_KeyboardEventWrite(e_DB_KEYBOARD_EVENT_ID Id,
                                  UWORD16 Value);

/* Access to the buzzer command function */
extern void SEC_BuzzerCmd(e_DB_ALARM_LEVEL_PRIORITY Buzzer_Command_Type);

/* Access to the led command function */
extern void SEC_LedCmd(UWORD16 LedCmdType);

/* Access to the decounter function */
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);
/* Access to the reading decounter function */
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);

/* Settings and alarms event management */
extern void DB_EventMngt (UWORD16 Value);

extern UWORD16 DB_ConfigWrite(e_DB_CONFIG Id,
										UWORD16 Value);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern void TIM_StopDecounter(e_TIM_TABLE_ID offset_table);

extern void DRV_BuzInit(void);

#else
/******************************************************************************/
/*                  EXTERNAL VARIABLE DECLARATION  	                        */
/******************************************************************************/
/* Alarm level declaration */
   extern e_DB_ALARM_LEVEL_PRIORITY Alarm_Level ;


#endif

#endif


