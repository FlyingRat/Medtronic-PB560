/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Counters.h                                           		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Patient & Machine counters management                          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef SYS_COUNTERS_H
#define	SYS_COUNTERS_H

#define cFIFTY_NINE_MINUTES 59U
#define cOVERFLOW_LIMIT 65000UL


extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);
extern UWORD16 TIM_TestOverflowOk(e_TIM_TABLE_ID offset_table);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
#endif