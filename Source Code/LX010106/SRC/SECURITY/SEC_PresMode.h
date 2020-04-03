/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_PresMode.h                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Data declaration for SEC_PresMode.c                                    */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SEC_PRES_MODE_H
#define SEC_PRES_MODE_H

/* Access to the current read value */
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
/* Access to the disconnection alarm */
extern e_ALARM_ERROR SEC_Disconnection(UWORD16 Disconnection_Delay,
										 SWORD16 LowPressure);
extern e_ALARM_ERROR SEC_HighPressure(UWORD16 PressureCompareValue);
extern e_ALARM_ERROR SEC_ProxDisconnection(UWORD16 ProxiDisconnectionDelay);
extern e_ALARM_ERROR SEC_HighVti(void);
extern e_ALARM_ERROR SEC_LowVti(void);
extern e_ALARM_ERROR SEC_Occlusion(void);
extern e_ALARM_ERROR SEC_ValveLeakage(void);
extern e_ALARM_ERROR SEC_LeakDisconnection(UWORD16 Disconnection_Delay);
extern e_ALARM_ERROR SEC_LeakOcclusion(void);
extern e_ALARM_ERROR SEC_CheckPressure(UWORD16 Delay);
extern e_ALARM_ERROR SEC_CheckProximal(UWORD16 Delay);
extern e_ALARM_ERROR SEC_CheckValvePressure(UWORD16 Delay);
#endif