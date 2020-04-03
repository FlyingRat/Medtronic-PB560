/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Message.hpp 				  			 		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_Message.cpp 						  		      	*/
/*%C			                                                                  */
/******************************************************************************/
//---------------------------------------------------------------------------

#ifndef HMI_MESSAGE_HPP
#define HMI_MESSAGE_HPP
//---------------------------------------------------------------------------

extern "C"
{
#include "typedef.h"
#include "DB_AlarmStatus.h"
#include "DB_Event.h"
#include "DB_Control.h"
#include "Enum.h"
#include "define.h"
}


/*START_MESSAGES*/

// generated from PB500 Message Translations.xlsm revision 30837

/*C Messages d'alarme */
extern const UBYTE *const huge cMSG_Alarm[Mark_Displayed_Alarm] [NB_LANGUAGE];

















































































/*C Messages historique alarme*/
extern const UBYTE *const huge cMSG_HistAlarm[End_Event_Alarm - Start_Alarm] [NB_LANGUAGE];














































































/*C Menu Mémorisation des alarmes */
extern const UBYTE *const huge cMSG_TitleMemoAlarms[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_EmptyList[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CancelledAlarm[NB_LANGUAGE];


/*C Messages Mois */
extern const UBYTE *const huge cMSG_Month[13][NB_LANGUAGE];













/*C Messages Menu de Configuration */
extern const UBYTE *const huge cMSG_Configuration[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CounterMachine[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Language[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CountryLanguage[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Date[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Time[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ModeCycle[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_RelativePressure[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_RelativePressureAbs[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_RelativePressureRel[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PressureUnitType[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Alarm_Tone[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TriggerEConv[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Negative[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Positive[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CounterPatient[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ResetPatientHrs[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Maintenance[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_NextPage[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Configuration2[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_RestoreDefaultSetting[NB_LANGUAGE];

/*C Messages Menu Préférence */
extern const UBYTE *const huge cMSG_Preferences[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ScreenSave[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Brightness[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_SoundLevel[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_KeySound[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Key[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Bip[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BipAndKey[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VoluntaryStopAlarm[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ApneaAlarm[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_DisconnectionAlarm[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_WaveformDisplay[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CurveConfiguration[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_RapportVentil[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PediatricCircuit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BackVentil[NB_LANGUAGE];

// Circuit Check Messages
extern const UBYTE *const huge cMSG_CircuitCheck[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_LeakTestInstr1[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_LeakTestInstr2[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_LeakTestInstr3[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TestStatus[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TestStates[nb_of_test_states][NB_LANGUAGE];




extern const UBYTE *const huge cMSG_CircuitLeak[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_LanguageCode[NB_LANGUAGE];

/*C Messages du Menu Maintenance */
extern const UBYTE *const huge cMSG_MenuMaintenance[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_SoftwareVersion[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_SupplySoftwareVersion[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ShortSerial[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_HistoAnom[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VoltCtrl[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_SensorCal[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PatientPressure[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ValvePressure[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FlowIns[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FlowExp[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CalibFiO2[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_O2Pressure[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FlowO2[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PwmBlower[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Back[NB_LANGUAGE];

/*C Messages Menu Controle des tensions */
extern const UBYTE *const huge cMSG_MenuVoltControl[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_SupplyTest[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_WatchdogTest[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_AbsPress[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Temperature[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BlowerTemperature[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Buzzer[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BuzzerSec[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BatteryMenu[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BaroCorrect[NB_LANGUAGE];

/*C Messages Menu batterie */
extern const UBYTE *const huge cMSG_InternalBatteryMenu[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BatSupplier[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BatTheoreticalCapacity[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FirstUseDate[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BatAgeing[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CyclesDone[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BatteryVoltage[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BatteryTemperature[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BatSupplierUnknown[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BatSupplier3[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_NoBat[NB_LANGUAGE];

/*C Messages Menu Historique anomalies */
extern const UBYTE *const huge cMSG_MenuHistoAno[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Cpt[NB_LANGUAGE];

/*C Messages du Menu Welcome */
extern const UBYTE *const huge cMSG_Welcome[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Machine[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PatWelcome[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VSoft[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CopyrightWelcome[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CompanyWelcome[NB_LANGUAGE];

/*C Messages des Modes de Ventilation */
extern const UBYTE *const huge cMSG_Mode[nb_of_mode][NB_LANGUAGE];





extern const UBYTE *const huge cMSG_Mode2[nb_of_mode][NB_LANGUAGE];





extern const UBYTE *const huge cMSG_Mode3[nb_of_mode][NB_LANGUAGE];





extern const UBYTE *const huge cMSG_InspTrigger[nb_of_trigger_levels][NB_LANGUAGE];






extern const UBYTE *const huge cMSG_EnableMode[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_DisableMode[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_AutoMode[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PressureSlope[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Rampe[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ExhalationPressure[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CpapPressure[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_InsuflationPressureControl[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_InsuflationPressureControl2[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_InsuflationPressureSupport[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CurrantVolume[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_InspirationTrigger[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ExhalationTrigger[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ControlRate[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BackupRate[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Apnee[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TiControl[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_IERation[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ITRation[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TiMon[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TeMon[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Pulse[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Soupir[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VtSoupir[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CptSoupir[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FiO2[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VTCible[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PiMax[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VaciRate[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_InsuflationPressurePeakMon[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Vti[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Vte[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Vm[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_RateMon[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_IERationMon[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ITRationMon[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FuiteMon[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FiO2Mon[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_SpO2[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_StartVentil[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_StopVentil[NB_LANGUAGE];

extern const UBYTE *const huge cMSG_StopConfirmVentil[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VPreferences[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_IsensHelperTxt[NB_LANGUAGE];

/*C Messages Menu d'Alarme */
extern const UBYTE *const huge cMSG_MiniTab[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PatientTab[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_MaxiTab[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PiMbar[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VteMl[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VmLpm[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FrCMin[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TiS[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VtiMl[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FiO2Pc[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ExhalationPressureMon[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_SpO2Pc[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FuiteParam[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_MeanAirwayPressureMon[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_HistoAlarm[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_switchMode[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CalibQExpTab[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CalibQExpProcessing[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CalibFiO2Tab[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CalibFiO2Processing[NB_LANGUAGE];


extern const UBYTE *const huge cMSG_SettingBlock[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_BlockedSetting[End_Limit_Setting - Start_Limit_Setting - 1][NB_LANGUAGE];

























/*C Messages Menu Courbes */
extern const UBYTE *const huge cMSG_Vmi[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_OutOfLimit[NB_LANGUAGE];

/*C Units */
extern const UBYTE *const huge cMSG_PressureUnit[3][NB_LANGUAGE];


extern const UBYTE *const huge cMSG_VolumeUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VolumeLiterUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PerCentUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FlowUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_StandardFlowUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FrequencyUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_SpeedUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TensionUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PowerUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TempUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_AbsPressUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PressBarUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_HourUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_MinuteUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_SecondUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_eventUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_DayUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_MonthUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_HoursByDayUnit[NB_LANGUAGE];

/*C Miscellaneous Messages */
extern const UBYTE *const huge cMSG_Stop[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Wait[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ShortWait[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_No[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Off[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Yes[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_On[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_NoneUnit[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Slash[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Colon[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Sup[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_MoreOrLess[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Auto[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_IEHeader[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Pediatric[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Am[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Pm[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Original[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Compliant[NB_LANGUAGE];

extern const UBYTE *const huge cMSG_MenuGraphConfig[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Visualisation[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PressionMax[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_DebitMax[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VtMax[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TempsMax[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Representation[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CurveVisualisation1[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CurveVisualisation2[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CurveRepresentation1[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_CurveRepresentation2[NB_LANGUAGE];

/*C Messages Menu Rapport de ventilation */
extern const UBYTE *const huge cMSG_ReportTitle[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VentTimeReport[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ReportDay[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ReportTableTitle[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VtiReport[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VteReport[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VmReport[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_Spo2Report[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_IAReport[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_SpontReport[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_FrReport[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_LeakReport[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_PipReport[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TapneaReport[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ContrReport[NB_LANGUAGE];

/*C Messages Menu Clé USB */
extern const UBYTE *const huge cMSG_TitleUSB[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_EraseKey[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TransferOnUSB[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TransferToVentil[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TransferToKey[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_ContRecordUSB[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TransferMonitUSB[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TransferTrendUSB[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_TransferEventsUSB[NB_LANGUAGE];

/*C Messages d'alarme USB */
extern const UBYTE *const huge cMSG_UsbErrDisconnect[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_UsbErrFullKey[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_UsbErrTooManyKeys[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_UsbErrTransfer[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_UsbErrErase[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_UsbErrFile[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_UsbErrPortability[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_SettingsOverWrite[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_VentilCompatible[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_NotEnoughKeySpace[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_UsbErrTransfProcessing[NB_LANGUAGE];
extern const UBYTE *const huge cMSG_UsbErrEraseProcessing[NB_LANGUAGE];










































































































































































































































































































































































/*END_MESSAGES*/

#endif
