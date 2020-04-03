/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Fio2OffsetDefaul.h                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            									                         				*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SEC_FIO2OFFSETDEFAULT_H
#define SEC_FIO2OFFSETDEFAULT_H

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, 
										  e_DB_ALARMS_STATE Value);
extern void DB_EventMngt(UWORD16 Value);

#endif