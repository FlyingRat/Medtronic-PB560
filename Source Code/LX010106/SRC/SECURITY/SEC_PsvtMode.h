/******************************************************************************/
/*                                                                            */
/* Project N�  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_PsvtMode.h                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Data declaration for SEC_PsvtMode                                      */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SEC_PSVT_MODE_H
#define SEC_PSVT_MODE_H

extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void DB_EventMngt (UWORD16 Value);

/* Access to the current read value */
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
/* Access to the disconnection alarm */
extern e_ALARM_ERROR SEC_Disconnection(UWORD16 Disconnection_Delay,
										 SWORD16 LowPressure);
extern e_ALARM_ERROR SEC_HighPressure(UWORD16 PressureCompareValue);
extern e_ALARM_ERROR SEC_Apnea(void);
extern e_ALARM_ERROR  SEC_ControlledCycles(void);
extern e_ALARM_ERROR SEC_ProxDisconnection(UWORD16 ProxiDisconnectionDelay);
extern e_ALARM_ERROR SEC_HighVti(void);
extern e_ALARM_ERROR SEC_LowVti(void);
extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, 
								e_DB_ALARMS_STATE Value);
extern e_ALARM_ERROR SEC_Occlusion(void);
extern e_ALARM_ERROR SEC_ValveLeakage(void);
extern e_ALARM_ERROR SEC_LeakDisconnection(UWORD16 Disconnection_Delay);
extern e_ALARM_ERROR SEC_LeakOcclusion(void);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern e_ALARM_ERROR SEC_CheckPressure(UWORD16 Delay);
extern e_ALARM_ERROR SEC_CheckProximal(UWORD16 Delay);
extern e_ALARM_ERROR SEC_CheckValvePressure(UWORD16 Delay);
#endif