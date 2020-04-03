/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Keyboard.h                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                       KEYBOARD management	           				   		*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/



#ifndef SYS_KEYBOARD_H
#define SYS_KEYBOARD_H




 
/******************************************************************************/
/*                      EXTERNAL CONSTANT DECLARATION                     	  */
/******************************************************************************/

/* tick of clock computing to the keyboard management*/
#define SCHEDULER_PERIOD_KEYBOARD_MS 20

#define CHANGE_MS_TO_STEPS(millisecondes) \
       (millisecondes / SCHEDULER_PERIOD_KEYBOARD_MS)

/*Key press validation delay : 120ms*/
#define cSYS_DebounceValidated 120
/*delay before a key become unactivated : 40ms*/
#define cSYS_DebounceDesactivated 40
/*delay of Key pulse width : 40ms*/  
#define cSYS_PulseTime 40 


/******************************************************************************/
/*                       EXTERNAL FUNCTION DECLARATION	                     */
/******************************************************************************/

extern UWORD16 KEY_Touch_Detection(e_SYS_KeyboardInput Touch);
extern void DRV_Key_Sound_Cloc(void);
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value); 
extern void KEY_Event(void);

/* Access to the decounter command                                            */
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 Value);

extern UWORD16 TIM_TestOverflowOk(e_TIM_TABLE_ID offset_table);

extern void DB_KeyboardEventWrite(e_DB_KEYBOARD_EVENT_ID Id,
                                  UWORD16 Value);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);


#endif
