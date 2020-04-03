/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : VEN_Security.h                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   It schedules all the alarms depending on the authorization of         */
/*%C	 ventilation, and the current mode                                      */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef VEN_SECURITY_H
#define VEN_SECURITY_H

/******************************************************************************/
/*                      EXTERNAL FUNCTION DECLARATION                         */
/******************************************************************************/
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void DB_EventMngt(UWORD16 Value);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value);
extern void SEC_VentilAuthorization(void);
extern void SEC_FirstCycleDetection(void);
extern e_ALARM_ERROR SEC_HighVte(void);
extern e_ALARM_ERROR SEC_LowVte(void);
extern e_ALARM_ERROR SEC_HighRate(void);
extern e_ALARM_ERROR SEC_CheckBuzzer(void);
extern e_ALARM_ERROR SEC_BuzzerBatteryLow(void);
extern e_ALARM_ERROR SEC_BuzzerBatteryChargeFailure(void);
extern e_ALARM_ERROR SEC_TechnicalProblem(void);
extern void SEC_CheckSettings(void);
extern e_ALARM_ERROR SEC_NoProximal(void);
extern e_ALARM_ERROR SEC_CheckValve(void);
extern e_ALARM_ERROR SEC_ValveLeakage(void);
extern e_ALARM_ERROR SEC_CheckRemoteAlarm(void);
extern e_ALARM_ERROR SEC_ACPowerFail(void);
extern e_ALARM_ERROR SEC_DCPowerFail(void);
extern e_ALARM_ERROR SEC_CheckSupply(void);
extern e_ALARM_ERROR SEC_LowBattery(void);
extern e_ALARM_ERROR SEC_EndOfBattery(void);
extern e_ALARM_ERROR SEC_CheckBattery(void);
extern e_ALARM_ERROR SEC_NoBattery(void);
extern e_ALARM_ERROR SEC_UnknownBattery(void);
extern e_ALARM_ERROR SEC_CheckBatteryCharge(void);
extern void SEC_VolMode(void);
extern void SEC_PresMode(void);
extern void SEC_VsimvMode(void);
extern void SEC_PsimvMode(void);
extern void SEC_PsvtMode(void);
extern void SEC_CpapMode(void);
extern void	SEC_ClockDefault(void);
extern void	SEC_SpeedDefault(void);
extern void	SEC_KeyboardDefault(void);
extern void	SEC_VeryLowInternalPressure(void);
extern void	SEC_VeryLowProximalPressure(void);
extern void	SEC_VeryLowValvePressure(void);
extern void SEC_ExhFlowOffsetDefault(void);
extern void SEC_AlarmIndication(void);
extern void  SEC_CanceledStateMngt(void);
extern void  SEC_ResetAlarms(void);
extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, 
										  e_DB_ALARMS_STATE Value);
extern e_ALARM_ERROR SEC_CalibrationFailure(void);
extern e_ALARM_ERROR SEC_AmbientTemperature(void);
extern e_ALARM_ERROR SEC_BatteryTemperature(void);
extern e_ALARM_ERROR SEC_CoolingFanFailure(void);
extern e_ALARM_ERROR SEC_Failure24V(void);
extern e_ALARM_ERROR SEC_SupplyMeasureFailure(void);
extern e_ALARM_ERROR SEC_TurbineOverheat(void);
extern e_ALARM_ERROR SEC_CpuReferenceFailure(void);
extern void SEC_ValveUseChangeMngt(void);
extern void SEC_LooseFlashPointer(void);


extern e_ALARM_ERROR SEC_Leakage(void);

extern void SEC_Fio2OffsetDefault(void);


extern void SEC_CpapMode(void);

extern e_ALARM_ERROR SEC_VoluntaryStop(void);

extern e_ALARM_ERROR SEC_Fio2CalibrationNeeded(void);

extern e_ALARM_ERROR SEC_CheckFio2_XL2(void);

#if defined(CONFIG_ALARM_O2)
extern e_ALARM_ERROR SEC_CheckFio2(void);
extern e_ALARM_ERROR SEC_LowFio2_M2(void);
extern e_ALARM_ERROR SEC_HighFio2_M2(void);
extern e_ALARM_ERROR SEC_NoFio2Sensor_M2(void);
extern e_ALARM_ERROR SEC_CheckO2Supply(void);
extern e_ALARM_ERROR SEC_MissingO2Supply(void);
extern e_ALARM_ERROR SEC_CheckO2(void);
extern e_ALARM_ERROR SEC_O2Leakage(void);
extern e_ALARM_ERROR SEC_100_Fio2(void);
#endif

#if ! defined(CONFIG_ALARM_O2)

extern e_ALARM_ERROR SEC_LowFio2_XL2(void);
extern e_ALARM_ERROR SEC_HighFio2_XL2(void);
extern e_ALARM_ERROR SEC_NoFio2Sensor_XL2(void);
#endif

#endif