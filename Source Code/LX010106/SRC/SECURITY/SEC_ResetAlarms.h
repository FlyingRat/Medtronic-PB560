/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ResetAlarms.h                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  Data declaration for SEC_ResetAlarms.c                                  */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   NONE                                                */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

#ifndef SEC_RESET_ALARMS_H
#define SEC_RESET_ALARMS_H

/******************************************************************************/
/*                            EXTERNAL FUNCTION DECLARATIONS                  */
/******************************************************************************/

/* Access to the Alarm status write function */
extern void DB_AlarmStatusWrite(e_DB_ALARMS Id,
                                e_DB_ALARMS_STATE Value);

extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value);

extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);

#endif
