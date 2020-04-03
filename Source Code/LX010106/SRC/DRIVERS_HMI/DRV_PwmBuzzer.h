/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_PwmBuzzer.h                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef DRV_PWMBUZZER_H
#define DRV_PWMBUZZER_H

/******************************************************************************/
/*           EXTERNAL FUNCTION DECLARATION        	                        	*/
/******************************************************************************/
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table, 
			                           UWORD16 value); 

#endif
