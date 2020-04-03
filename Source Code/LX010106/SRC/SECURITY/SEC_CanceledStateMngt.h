/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CanceledStateMngt.h                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  Data declaration for SEC_CanceledStateMngt.c                            */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   NONE                                                */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

#ifndef CANCELED_STATE_MNGT_H
#define CANCELED_STATE_MNGT_H

/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION                            */
/******************************************************************************/

/* Access to the alarm status base (read) */
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);

/* Access to the control write value */
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);

/* Access to the event management function */
extern void DB_EventMngt (UWORD16 Value);

/* Access to the keyboard event management function */
extern UWORD16 DB_KeyboardEventRead(e_DB_KEYBOARD_EVENT_ID Id);

extern void DB_KeyboardEventWrite(e_DB_KEYBOARD_EVENT_ID Id,
                                  UWORD16 Value);

/* Access to the control read value */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);


#endif

