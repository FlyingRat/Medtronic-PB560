/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ClockDefault.h                                             */
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

#ifndef SEC_CLOCKDEFAULT_H
#define SEC_CLOCKDEFAULT_H

/************************************************************************/
/*                   CONSTANT DECLARATION                               */
/************************************************************************/

#define cFIFTY_NINE_SECONDS 59U
#define cFIFTEEN_SECONDS 1500U
#define cTEN_SECONDS 1000U
#define cFIVE_SECONDS 500U
/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, 
								e_DB_ALARMS_STATE Value);
extern UWORD16 DB_RTCRead(e_DB_RTC Id);
extern void DB_EventMngt (UWORD16 Value);
#endif