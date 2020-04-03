/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Backlight_Mngt.h                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Backilght management                                           */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/



#ifndef SYS_BACKLIGHT_MNGT_H
#define SYS_BACKLIGHT_MNGT_H



/******************************************************************************/
/*                            CONSTANT DECLARATION                     	   */
/******************************************************************************/
#define TIME_BACKLIGHT 60000


/******************************************************************************/
/*                       EXTERNAL FUNCTION DECLARATION	                     */
/******************************************************************************/
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern void TIM_StartDecounter(e_TIM_TABLE_ID,UWORD16);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID);
extern UWORD16 DB_KeyboardEventRead(e_DB_KEYBOARD_EVENT_ID Id);
extern void DIS_Backlight(e_TYPE_BACKLIGHT_LEVEL Level);
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value);
#endif