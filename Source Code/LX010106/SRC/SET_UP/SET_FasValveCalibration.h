/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_FasValveCalibration.h	 												*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            									                          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SET_FASVALVECALIBRATION_H
#define SET_FASVALVECALIBRATION_H

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void DB_AlarmStatusWrite(e_DB_ALARMS Id,
								e_DB_ALARMS_STATE Value);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern UWORD16 DB_ConfigWrite(e_DB_CONFIG Id,
										UWORD16 Value);
extern void DB_EventMngt (UWORD16 Value);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);
//extern UWORD16 DB_KeyboardEventRead(e_DB_KEYBOARD_EVENT_ID Id);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
extern UWORD16 average(UWORD16 *Data, UWORD16 Size); 

extern void ACT_ValveCmd(UWORD16 Consigne);
extern void DB_ComputeWrite(e_DB_COMPUTE Id,
                               UWORD16 Value);

#endif