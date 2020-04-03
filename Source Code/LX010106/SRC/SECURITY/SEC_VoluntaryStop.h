/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_VoluntaryStop.h                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            									                                    */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SEC_VOLUNTARYSTOP_H
#define SEC_VOLUNTARYSTOP_H

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/

extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, 
								e_DB_ALARMS_STATE Value);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DB_EventMngt (UWORD16 Value);
extern UWORD16 DB_KeyboardEventRead(e_DB_KEYBOARD_EVENT_ID Id);
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value);

#endif