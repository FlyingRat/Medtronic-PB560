/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_BuzzerBatteryLow.h                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*   Date        |  Programmer    | Modification                              */
/*----------------------------------------------------------------------------*/
/*%R V 4   |                | */
/*  13/02/08	  |   PESSUS        | Creation, rename                         */
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

#ifndef SEC_BUZZERBATTERYLOW_H
#define SEC_BUZZERBATTERYLOW_H

/************************************************************************/
/*                         ENUM DECLARATION    	                			*/
/************************************************************************/


/************************************************************************/
/*                       STRUCTURE DECLARATION     	               	*/
/************************************************************************/


/************************************************************************/
/*                   EXTERNAL CONSTANT DECLARATION                     	*/
/************************************************************************/
/************************************************************************/
/*                   EXTERNAL VARIABLE DECLARATION                    	*/
/************************************************************************/

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);

extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, 
								e_DB_ALARMS_STATE Value);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DB_EventMngt (UWORD16 Value);
extern UWORD16 DB_KeyboardEventRead(e_DB_KEYBOARD_EVENT_ID Id);
extern void TIM_StartMinuteDecounter(e_TIM_MINUTE_TABLE_ID offset_table,UWORD32 value,e_BOOL autoreload);
extern UWORD32 TIM_ReadMinuteDecounterValue(e_TIM_MINUTE_TABLE_ID offset_table);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
#endif
