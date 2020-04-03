/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_BatteryPeriodicalSignal.h                                  */
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

#ifndef SEC_BATTERYPERIODICALSIGNAL_H
#define SEC_BATTERYPERIODICALSIGNAL_H


/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, 
								e_DB_ALARMS_STATE Value);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DB_EventMngt (UWORD16 Value);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
										 UWORD16 value);
extern UWORD16 DB_PowerSupplyRead(e_DB_POWERSUPPLY Id);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
extern void DB_ControlWrite(e_DB_CONTROL Id, 
									 UWORD16 Value);
/* Access to the buzzer driver */
extern void DRV_Buz_Sound(e_TYPE_SOUND sound,
                          e_NUMBER_BUZ NumBuzzer);
extern void TIM_StartMinuteDecounter(e_TIM_MINUTE_TABLE_ID offset_table,
													UWORD32 value,e_BOOL autoreload);
extern UWORD32 TIM_ReadMinuteDecounterValue(e_TIM_MINUTE_TABLE_ID offset_table);
#endif