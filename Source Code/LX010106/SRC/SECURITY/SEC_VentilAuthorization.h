/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_VentilAuthorization.h                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Data declaration for SEC_VentilAuthorization.c                         */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SEC_VENTIL_AUTHORIZATION_H
#define SEC_VENTIL_AUTHORIZATION_H

/******************************************************************************/
/*                EXTERNAL FUNCTION DECLARATION                               */
/******************************************************************************/

/* Access to the Control base (Write)                                         */
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value);

/* Access to the Control base (Read)                                         */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

/* Access to the Config base (Read)                                           */
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

/* Access to the Config base (Read)                                           */
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

/* Access to the Config base (Write)                                          */
extern UWORD16 DB_ConfigWrite(e_DB_CONFIG Id,
										UWORD16 Value);

/* Access to the Control base (Write)                                         */
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value);

/* Access to the Keyboard base (Write)                                        */
extern void DB_KeyboardEventWrite(e_DB_KEYBOARD_EVENT_ID Id,
                                  UWORD16 Value);

/* Access to the Keyboard base (Read)                                         */
extern UWORD16 DB_KeyboardEventRead(e_DB_KEYBOARD_EVENT_ID Id);

/* Access to the decounter command                                            */
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 Value);

/* Access to the decounter command                                            */
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);

/* Access led ventil driver command                                           */
extern void DRV_Led_Ventil(e_BOOL VentilLedCommand);

/* Access to the buzzer driver */
extern void DRV_Buz_Sound(e_TYPE_SOUND sound,
                          e_NUMBER_BUZ NumBuzzer);

extern void DB_EventMngt (UWORD16 Value);

extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);

#endif