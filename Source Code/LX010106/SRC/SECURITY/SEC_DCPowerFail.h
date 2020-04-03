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

#ifndef SEC_DCPOWERFAIL_H
#define SEC_DCPOWERFAIL_H

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
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, 
								e_DB_ALARMS_STATE Value);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DB_EventMngt(UWORD16 Value);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
										 UWORD16 value);
extern UWORD16 DB_PowerSupplyRead(e_DB_POWERSUPPLY Id);
extern UWORD16 DB_KeyboardEventRead(e_DB_KEYBOARD_EVENT_ID Id);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);

#endif