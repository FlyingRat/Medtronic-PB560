/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_VolMode.h                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Data declaration for SEC_VolMode                                       */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SEC_VOL_MODE_H
#define SEC_VOL_MODE_H

/* Access to the current read value */
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
/* Access to the disconnection alarm */
extern e_ALARM_ERROR SEC_Disconnection(UWORD16 Disconnection_Delay,
										 SWORD16 LowPressure);
extern e_ALARM_ERROR SEC_HighPressure(UWORD16 PressureCompareValue);
extern e_ALARM_ERROR SEC_ProxDisconnection(UWORD16 ProxiDisconnectionDelay);
extern e_ALARM_ERROR SEC_CheckVolume(void);
extern e_ALARM_ERROR SEC_InspiratoryFlowFailure(void);
extern e_ALARM_ERROR SEC_ValveLeakage(void);
extern e_ALARM_ERROR SEC_CheckPressure(UWORD16 Delay);
extern e_ALARM_ERROR SEC_CheckProximal(UWORD16 Delay);
extern e_ALARM_ERROR SEC_CheckValvePressure(UWORD16 Delay);
#endif