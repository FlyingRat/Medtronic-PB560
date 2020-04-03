/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_Actuator.h																	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C             			Actuators management                  						*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SET_ACTUATOR_H
#define SET_ACTUATOR_H

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern void DB_ComputeWrite(e_DB_COMPUTE Id, 
							UWORD16 Value);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

/* Access to the control read value */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value); 
/* Access to the control read value */
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern void ACT_BrakePower(UBYTE percentage);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);
extern SWORD32 VEN_RiseCompute(SWORD32 x,
										SWORD32 x1,
										SWORD32 y1,
										SWORD32 x2,
										SWORD32 y2);
extern void ACT_BlowerCmd(SWORD32 Kp,
						 SWORD32 Ki,
						 UWORD16 Consigne,
						 e_VEN_ControllerType TypeRegul);
/*%C Management of Valve command*/
extern void ACT_ValveCmd(UWORD16 Value);
extern void ACT_ValveDetected(void);

extern void DRV_Buz_Sound(e_TYPE_SOUND sound, 
                          e_NUMBER_BUZ NumBuzzer);

extern void ACT_O2ValveCmd(SWORD32 Kp,SWORD32 Ki,SWORD32 Consigne);
#endif