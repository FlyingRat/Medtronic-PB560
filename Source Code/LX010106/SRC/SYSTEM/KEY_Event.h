/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : KEY_Event.c                                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Keyboard Events management                                     */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef KEY_EVENT_H
#define KEY_EVENT_H


/******************************************************************************/
/*                               CONSTANT DECLARATION                     	   */
/******************************************************************************/
// Durée de répétition automatique de touche: 60 ms
#define cKEY_AutoRepeatDelay 100

#define cKEY_LongBetweenAutoDelay 500

/******************************************************************************/
/*                       EXTERNAL FUNCTION DECLARATION	                     */
/******************************************************************************/

extern void DB_KeyboardEventWrite(e_DB_KEYBOARD_EVENT_ID Id,
                                  UWORD16 Value);

extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);
extern void TIM_StopDecounter(e_TIM_TABLE_ID offset_table);

extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);

extern UWORD16 TIM_TestOverflowOk(e_TIM_TABLE_ID offset_table);

extern void DB_ControlWrite(e_DB_CONTROL Id,
									 UWORD16 Value);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

#endif
