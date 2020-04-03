/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Controller.hpp		                                      	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  */
/*%C Classe declaration for HMI_Controller.cpp		                          */
/*%C                                                                          */
/******************************************************************************/

#ifndef ControllerH
#define ControllerH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Label.hpp"
#include "HMI_LabelOneValue.hpp"
#include "HMI_LabelOneValueSign.hpp"
#include "HMI_LabelOneValueDbRT.hpp"
#include "HMI_LabelOneValueSignFlag.hpp"
#include "HMI_LabelOneValueDefault.hpp"
#include "HMI_LabelOneValueThreeDefault.hpp"
#include "HMI_LabelOneValueFourDefault.hpp"
#include "HMI_LabelOneValueFlag.hpp"
#include "HMI_LabelOneValueFiO2Flag.hpp"
#include "HMI_LabelOneValueTrig.hpp"
#include "HMI_LabelProgressBar.hpp"
#include "HMI_LabelTwoValueLock.hpp"
#include "HMI_LabelTabOneValue.hpp"
#include "HMI_LabelTabOneValueFlag.hpp"
#include "HMI_LabelTabTwoValue.hpp"
#include "HMI_LabelTabTwoValueTwoLabels.hpp"
#include "HMI_LabelRatio.hpp"
#include "HMI_LabelRatioTrunk.hpp"
#include "HMI_LabelTabTwoValueFlag.hpp"
#include "HMI_LabelValueString.hpp"
#include "HMI_LabelStringTwoItems.hpp"
#include "HMI_LabelTwoStringsTwoItems.hpp"
#include "HMI_LabelStringNItems.hpp"
#include "HMI_LabelLanguage.hpp"
#include "HMI_LabelMode.hpp"
#include "HMI_Rampe.hpp"
#include "HMI_RiseTime.hpp"

#include "HMI_AutoCalibValue.hpp"
#include "HMI_ManualCalibValue.hpp"
#include "HMI_ManualCalibTwoValue.hpp"
#include "HMI_VDate.hpp"
#include "HMI_VTime.hpp"
#include "typedef.h"
#include "HMI_IhmType.hpp"
#include "HMI_BlinkTable.hpp"
#include "HMI_RefreshTable.hpp"
#include "HMI_ParameterSpy.hpp"
#include "HMI_VTimer.hpp"

#include "HMI_Loupe.hpp"
#include "HMI_AlarmTable.hpp"
#include "HMI_AlarmManager.hpp"

#include "HMI_FrameWelcome.hpp"
#include "HMI_FrameConfiguration.hpp"
#include "HMI_FramePreference.hpp"
#include "HMI_FrameCircuitCheck.hpp"
#include "HMI_FrameMaintenance.hpp"
#include "HMI_FrameHistoAno.hpp"
#include "HMI_FrameVoltControl.hpp"
#include "HMI_FrameVentilation.hpp"
#include "HMI_FrameAlarme.hpp"
#include "HMI_FrameHistoAlarme.hpp"
#include "HMI_FrameGraph.hpp"
#include "HMI_FrameGraphConfig.hpp"
#include "HMI_FrameBatteryMenu.hpp"
#include "HMI_FrameUSB.hpp"
#include "HMI_FrameTendance.hpp"
#include "HMI_MessageDelayed.hpp"
#include "HMI_MessageDialog.hpp"
#include "HMI_Setup1.hpp"

extern "C"
{
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_Current.h"
#include "DB_Usb.h"
#include "DRV_VarEeprom.h"
#include "DB_WriteDataInEepAndRam.h"
#include "io_declare.h"
extern void It_watchdog(void);
}


/******************************************************************************/
/*                           	DEFINES                    	      			  	*/
/******************************************************************************/
#define cSPECIAL_FIVE_LINES 255
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/



class MenuControlNode;

class Controller
{

#ifdef _BORLAND
    friend class SettingFile;
    friend class BinarySettingFile;
    friend class TForm1;      
#endif

private:

    typedef enum
    {
        eGoUp, eGoDown, eGoValid, eGoLongValid, eGoMonitor
    } WayId;

    typedef enum
    {
        eOnStart,eOnWait,eStartVentil, eStopVentil
    } LegendState;

    typedef enum
    {
        eSTEP_LEVEL_LOW, eSTEP_LEVEL_HIGH
    } eSTEP_LEVEL;

    /* Paramettres */

    MenuControlNode *CurrentNode;

    MenuControlNode *UsbProcessingNode;
    e_BOOL UsbCmdInProgress;

    Loupe* CurrentLoupe;

    MenuControlNode* ArrayNode;


    UWORD16 CurrentFrame;

    UWORD16 CurrentVirtualFrame;

    LegendState LState;

    e_BOOL  LockOn,
        UsbLock,
        UsbKeyDetected,
        ModeChangeOn,
        ModifNodeOn,
        PSupportNull,
        IESelected,
        TrigEPosSelected,
        ValveDetected,
        ImpactDisplay,
        OnWait,
        DifferMonitoringStart,
        MonitoringMode,
        ExhalFlowUsed,
        VentButtonOn,
        BuzzerVoltRefreshReq,
        HighPressAlarmToBeRemoved,
        LeakTestRunning;

    UWORD16 LeakTestTimerCount;

    MessageDialog TopMessage;           

    BlinkTable BTable;

    RefreshTable RTable;

    AlarmTable ATable;

    ParameterSpy PSpy;

    AlarmManager AManager;
    e_BOOL IsDoubleMessageTimerStarted;

    VTimer Timer;

    DisplayObject   *RefreshTableAlarm[12],
        *RefreshTableMaintenance[12],
        *RefreshTableConfig[6],
        *RefreshTableVolt[5];

    e_MODE_TYPES CurrentMode;

    e_MODE_TYPES ConsultMode;

    bool EraseFlag;

    UWORD16     LastBrightness, 
        LastSoundLevel, 
        MemoSoundLevel;

    /* Noeud fantome */
    DisplayObject   GhostObject;

    /* fenetre accueil */
    FrameWelcome    FWelcome;

    /* fenetre USB */
    FrameUSB                 FUsb;
    MessageDelayed            UsbDelayed;
    Label                    LStopUsb;

#ifdef HMI_CONFIG_USB_SETTINGS_TRANSFER
    LabelTwoStringsTwoItems  LVSTransferSetOn;
#endif

    LabelStringTwoItems      LVSEraseKey,
        LVSContRecord;
#ifdef HMI_CONFIG_USB_EVENTS_TRANSFER
    LabelStringTwoItems      LVSFTransfEvents;
#endif

#ifdef HMI_CONFIG_USB_MONIT_TRANSFER
    LabelOneValueFlag         LOVFTransfMonit;
#endif

    LabelOneValueFlag         LOVFTransfTrend;

    UWORD16 PreviousErrorCode;                              
    /* fenetre Tendance */
    FrameTendance                 FTendance;
    Label                       LRTendance;

    /* fenetre Configuration */
    FrameConfiguration            FConfiguration;
    Label                         LMaintenance ,LRVentil;
	Label               	      LNextPage;
    VTime                         VTConf;
    VDate                         VDConf;
    LabelLanguage                 LVSLanguage;
    LabelStringTwoItems       LVSVoluntaryStopAlarm;

    LabelStringNItems          LVSPressureUnit;
  	LabelStringTwoItems          LVSAlarmTone;
    LabelTwoValue              LOVPatientHrs;
    LabelOneValue              LOVMachineHrs;
    LabelStringTwoItems         LVSSResetPatientHrs;
    LabelOneValueFourDefault   LOVFDAjustKeyTone;
    LabelStringTwoItems         LVSSRestoreDefaultSettings;

    /* fenetre Préférences */
    FramePreference     FPreference;
    LabelStringTwoItems     LVSScreenSave, LVSKeySound, LVSWaveformDisplay,
        LVSBaroCorrector, LVSApneaAlarm,
        LVSPediatricCircuit;
    LabelProgressBar        LPBSoundLevel, LPBBrightness;
    Label                   LRVentilMenu, LCurveConfiguration, LTrendMenu;
    LabelOneValueFlag    LOVFDisconnectionAlarm;

    // Circuit Test Window
    FrameCircuitCheck    &FCircuitCheck;
    Label                LCircuitLeak;

    /* fenetre Maintenance */
    FrameMaintenance    FMaintenance;
    LabelOneValueDbRT   LOVPwmBlower;
    Label               LHistoAnom,LVoltCtrl,LSensorCal,LRConfMaint;
    AutoCalibValue      LOVFlowExp,LOVValvePressure;
    ManualCalibValue    LOVFlowIns,LOVFlowO2,LOVPressO2,LOVFiO2Concent;
    ManualCalibTwoValue  LOVPatientPressure;

    /* fenetre Histo Anomalies */
    FrameHistoAno       FHistoAno;
    Label               LRMaintAno;

    /* fenetre Controle des tensions */
    FrameVoltControl    FVoltControl;
    Label               LRMaintTension,
        LOVBuzzSec,
        LBackupBuzzer,
        LBatteryMenu,
        LRMaintBattery;

    LabelOneValue        LOVBuzzerVoltage,
        LOVBuzz,
        LOVTempBat;

    /* fenetre batterie interne */
    FrameBatteryMenu    FBatteryMenu;

    /* fenetre Ventilation*/
    FrameVentilation                FVentilation;
    LabelStringTwoItems             LSTVChgtModeV,
        LSTVSoupir;

    LabelMode                       LModeVent;

    LabelOneValue                   LOVVT,
        LOVPi,
        LOVPControl,
        LOVPSupport,
        LOVPi2,
        LOVFVaci,
        LOVFRMini,
        LOVIT,
        LOVInspTime,
        LOVPiMax,
        LOVCptSoupir;
#ifdef HMI_CONFIG_100_FIO2
    LabelOneValueFiO2Flag     LOVFiO2;
#else
    LabelOneValue             LOVFiO2;
#endif

    LabelOneValueSign          LOVSVtSoupir;
    LabelOneValueSignFlag      LOVSTrigE;
    LabelOneValueFlag          LOVTrigE;

    Label                      LIE;

    LabelOneValueThreeDefault  LOVTDSupport;

    LabelOneValueFlag               LOVPe,
        LOVApnee,
        LOVVTCible,
        LOVFSecu;
    LabelStringNItems         LOVTrigI;

    RiseTime                   LOVPente;


    Rampe                       LOVRampe;



    Label                               LPreferences;

    //fenetre Alarme
    FrameAlarme          FAlarme;

    LabelStringTwoItems  LOVChgtModeA;

    Label                LHistoAlarm;

    LabelMode            LModeAlarm;

    LabelTabOneValueFlag LOVFrCMin,
        LTOVFuiteLMin;

    //	LabelTabTwoValue     LOVPiMbar;
    LabelTabTwoValueTwoLabels     LOVPiMbar;

    LabelTabTwoValueFlag LOVVteMl, 
        LOVVtiMl, 
        LTTVTiS,
        LTTVSpO2,
        LTTVFiO2;

    LabelStringTwoItems     LSTICalibQExp,
        LSTICalibFiO2;

    /* fenetre HistAlarme */
    FrameHistoAlarme    FHistoAlarme;
    Label               LRAlarmeA, 
        LCancelledAlarm;

    /* fenetre Courbes */
    FrameGraph      FGraph;

    /* fenetre configuration courbe */
    FrameGraphConfig            FGraphConfig;

    LabelOneValueDefault    LOVPMax, 
        LOVQMax, 
        LOVVtMax, 
        LOVTMax;

    LabelStringTwoItems      LVSVisu, 
        LVSRepresentation;

    Label                        LRGraphPref;

    UWORD16                 SegmentNumber;
    e_BOOL                  StartCalib;
    e_BOOL                  StartVerif;

    e_BOOL                  LongUpKeyDetected,
        LongDownKeyDetected;
    eSTEP_LEVEL             StepLevel;

    UWORD16 SaveBuzzerVoltParamId;
    e_TYPE_OF_DB_TARGET SaveBuzzerVoltDbId;

    MessageDialog BottomMessage;  

    /* Methodes */

    MenuControlNode* GetNextValidNode(  MenuControlNode* StartNode, 
                                        WayId way);

    MenuControlNode* FindFirstValidNode(MenuControlNode* StartNode, 
                                        WayId Beginway);


    void MoveToOtherNode(WayId way);

    void ManageLegendState(LegendState State);

    void GoToTopBottomFrame(UWORD16 Frame,WayId Way);

    void SendNodeModify(UWORD16 IdNode,e_BOOL IsNotTO);

    void ChangeNameMode(e_BOOL IsLongNameMode);

    void ShowBattery(e_BOOL Visible);

    void ShowTempBattery(e_BOOL Visible);

    void Reset();

    void SetHighPressAlarmToBeRemoved(e_BOOL _ToBeRemoved);
    e_BOOL HasHighPressAlarmToBeRemoved();

    e_BOOL IsVtCibleEnable();

    void SetVtCibleEnable();

    e_BOOL IsFSecuEnable();

    void SetFSecuEnable();

    e_BOOL IsSoupirEnable();

    void SetSoupirEnable();

    e_BOOL IsInhibApneaEnable();

    UWORD16 RebuildEventNodeTree(e_MODE_TYPES Mode, UWORD16 FirstNode, UWORD16 LastNode);

    void RebuildEventNodeTreeForAllModes( UWORD16 FirstNode, UWORD16 LastNode);

    UWORD16 GetNodeIdFromEventId(UWORD16 _Id);

    UWORD32 IsNodeInTree( e_MODE_TYPES Mode, UWORD16 NodeToFind, UWORD16 FirstNode, UWORD16 LastNode);

    void SetMCycl(e_BOOL _ModeCycl);

    void SetPressureUnit(UWORD16 _Val);

    void SetValve(e_BOOL _ValveDetected);

    void SendInfoValve(e_BOOL _ValveDetected);

    void SetPressConvention(e_BOOL _Conv);   

    void SendInfoBlocExpi(e_BOOL _BlocExpiDetected);

    void SetExhalFlowUsed(e_BOOL Flag);          

    void SendInfoFio2Sensor(e_BOOL _IsOk);

    void SendInfoSpo2Sensor(e_BOOL _IsOk);

    void SendInfoBadSupplyCheck(e_BOOL _IsBad);

    void UsbMoveCurrentNode(MenuControlNode *_CurrentNode, e_BOOL _forced);   

    void UsbUpdateNavigNodes(UWORD16 _NodeId);      

    void Spo2MonitorEnabled(e_BOOL _IsOk);

    void Fio2MonitorEnabled(e_BOOL _IsOk);

    e_BOOL IsFio2Sensor();

    e_BOOL IsSpo2Sensor();

    void SetConvTrigE(e_BOOL _ConvTrigE);

    void SetInhibApneaOk(e_BOOL _ApneaAlarm);

    void SetTrigEPosSelected(e_BOOL _TriggEPosSelected);   

    void HideVentil(e_MODE_TYPES Mode);

    void HideVentil(e_MODE_TYPES Mode, UWORD16 NodeId);

    void ShowVentil(  UWORD16 FirstLine,
                      UWORD16 Increment,
                      e_MODE_TYPES Mode);

    void ShowVentil( e_MODE_TYPES Mode, UWORD16 NodeId);                     

    void ShowMaintCalib();

    void HideAlarm(e_MODE_TYPES Mode);

    void HideAlarm(e_MODE_TYPES Mode, UWORD16 NodeId);   

    void ShowAlarm(   UWORD16 FirstLine,
                      UWORD16 Increment,
                      e_MODE_TYPES Mode);

    void ShowAlarm( e_MODE_TYPES Mode, UWORD16 NodeId);                     

    void DisplayAlarmTable(UWORD16 _NbParam, e_MODE_TYPES _Mode);

    void SendInfoUsbErrorCodeReady(e_BOOL _ErrorCodeReady);

    void SetUsbLock(e_BOOL _UsbLock);
    e_BOOL GetUsbLock();

    void SetUsbKeyDetected(e_BOOL _UsbKeyDetected);
    e_BOOL GetUsbKeyDetected();

    void SetUsbCmdInProgress(e_BOOL _UsbCmdInProgress);
    e_BOOL IsUsbCmdInProgress();

    e_BOOL GetEndOfInit();
    void SetEndOfInit(e_BOOL _EndOfInit);

    e_BOOL GetImpactDisplay();
    void SetImpactDisplay(e_BOOL _ImpactDisplay);

    void UpdateMode(void);

    void ShowMonitoring(void);

    void ForceQExpCalibrationStop(void);

    void ForceFiO2CalibrationStop(void);    

    static void StartSavingUsbSettings(void);

    void DecreaseBlowerStep();

    void IncreaseBlowerStep();

    e_BOOL GetLongUpKeyDetected();
    e_BOOL GetLongDownKeyDetected();
    void SetLongUpKeyDetected(e_BOOL _LongUpDetected);
    void SetLongDownKeyDetected(e_BOOL _LongDownDetected);

    e_BOOL IsVentButtonOn(); 
    void SetVentButtonOn(e_BOOL _VentButtonOn); 

    void SetDifferMonitoring(e_BOOL _differ); 
    e_BOOL IsDifferMonitoring();

    void SetBuzzerVoltRefreshReq(e_BOOL _refresh_request);
    e_BOOL IsBuzzerVoltRefreshReq();

    void InsertDoubleMessage();
    void RemoveDoubleMessage();

    MenuControlNode* GetPressureNode();
    void BuildPressureMessage(  MenuControlNode* node1,
                                MenuControlNode* node2,
                                UBYTE* buffer);
    UWORD16 UpdateCalibrationPoints();

protected:

    /* Parametres */

    /* Methodes */

public:

    typedef void (Controller::* PController)();

    /* Parametres */

    /* Methodes */

    Controller();

    void Init();

    void InitConfiguration();

    void SetCurrentNode(MenuControlNode *CurrentNode);
    MenuControlNode* GetCurrentNode();

    void SetCurrentMode(e_MODE_TYPES CurrentMode);
    e_MODE_TYPES GetCurrentMode();

    void SetConsultMode(e_MODE_TYPES ConsultMode);
    e_MODE_TYPES GetConsultMode();

    void SetCurrentFrame(UWORD16 CurrentFrame);
    UWORD16 GetCurrentFrame();

    static Controller* GetInstance();
    static void RemoveInstance();
    MenuControlNode* GetNodeAt(UWORD16 index);

    void ShowFrame(UWORD16 FrameId);

    static void ManageSpyEvent(EventId event);

    static void ManageTimerEvent(UWORD16 _Timer);

    static void ProtoManageTimerEvent(UWORD16 _Timer);   

    static void ManageKeyboardEvent(UWORD16 _Key);

    static void ProtoManageKeyboardEvent(UWORD16 _Key);   

    void MoveCurrentNode(MenuControlNode *CurrentNode);
    void ChangeMenuWithMode(e_MODE_TYPES Mode);
    void ManageLineMenuVentil(MenuControlNode* MasterNode);

    VFrame* GetFrameObject(UWORD16 id);

    void SetBrightness(UWORD16 Value);
    UWORD16 GetBrightness();

    UWORD16 GetLanguage();
    void SetLanguage(UWORD16 _Lang);
    void ChangeLanguage(UWORD16 NumLanguage);   

    e_BOOL IsVentilOn();

    void SetLockOn(e_BOOL Flag);
    e_BOOL IsLockOn();

    void SetPSupportNull(e_BOOL Flag);
    e_BOOL IsPSupportNull();

    void SetLState(LegendState State);
    LegendState GetLState();

    void ShowMessageFrame(e_BOOL Visible, UBYTE* Message, e_SYMBOL Symbol);
    void HideMessageFrame();
    void ManageLock(e_BOOL Actif);
    void ManageUsbLock(e_BOOL Actif);   
    void StopModifMode(e_MODE_TYPES NewMode);

    e_BOOL IsModeChange();

    void SetModeChange(e_BOOL Flag);

    e_BOOL IsLastShutDownError();
    e_BOOL IsModifNodeOn();

    void SetUsbProcessingNode(MenuControlNode* _Node);
    MenuControlNode* GetUsbProcessingNode();

    void SetModifNodeOn(e_BOOL Flag);
    void ManageInhibKey(e_BOOL IsLongKey);
    void ChangePages();
    void StopAllMenuAction();
    void SetMonitoringMode(e_BOOL Flag);
    void SetSupplyBusFailure(e_BOOL Flag);   
    void ManageCalibAuto();
    void ManageHistoAlarmSeek();
    void ManageHistoAnoSeek();
    void AlarmDetect(e_BOOL Actif, AlarmEvent* Alarm);
    void ShowAlarm(e_BOOL Actif,UWORD16 AlarmId, UWORD16 Action);
    void SettingBlockDetect();
    void ManageTrigger(UWORD16 Event);
    void SetVisibleTrigger(e_BOOL Flag);
    void StartBlowerBurnTest();
    void StopBlowerBurnTest();

    void StartCircuitLeakTest();
    void StopCircuitLeakTest();
    void AbortCircuitLeakTest();
    void CircuitLeakTestTimerCallback();

    void ShowMenu(UWORD16 FirstNodeId);
    void ManageVerifPointCalib(PController CallFct);
    void VerifAndManageCalibAuto();
    void ChangeBrightness(WayId Sens);
    void PlayBuzzer();
    void PlayBuzzerSec();
    void StopTimer(UWORD16 Event);
    void StartBuzzerVoltRefresh();
    void StopBuzzerVoltRefresh();
    void BuzzerVoltRefresh();

    void BuildTree();
    void NoAction();
    void MoveDown();
    void MoveUp();
    void MoveDownNodeMaintPwmBlower();
    void MoveUpNodeMaintPwmBlower();
    void ReturnToNodeMaintPwmBlowerTO();
    void ReturnToNodeMaintPwmBlower();   
    void ModifyUp();
    void ModifyDown();
    void ModifyUpRefreshBlower();
    void ModifyDownRefreshBlower();   
    void MoveValid();
    void MoveMonitor();
    void MoveDownNodePreference();
    void MoveMonitorNodeModifVentil();
    void MoveValidNodeAlHisto();
    void MoveDownNodeAlModeChange();
    void MoveValidNodePreference();
    void MoveValidNodeHistAlBack();
    void MoveUpNodeHistAlBack();
    void MoveDownNodeHistAlBack();   
    void MoveValidNodeHistAlCancelled();
    void MoveValidNodePrefBackVentil();
    void MoveUpNodeGraphGhost();
    void MoveDownNodeGraphGhost();
    void MoveValidNodeCfgGraphBackPref();
    void MoveUpNodePrefScreenSave();
    void MoveDownNodePrefScreenSave();
    void ModifyUpNodePrefScreenSave();
    void ModifyDownNodePrefScreenSave();
    void MoveToModifNodePrefScreenSave();
    void ReturnToNodePrefScreenSave();
    void ReturnToNodeTONodePrefScreenSave();
    void MoveTimeOutNodePrefScreenSave();
    void MoveTimeOutNodeHistAlBack();
    void MoveTimeOutUSB();
    void MoveValidNodePrefCurveConfig();
    void MoveValidNodePrefTrend();
    void MoveUpNodeCfgGraphVisu();
    void MoveDownNodeCfgGraphVisu();
    void ModifyUpNodeCfgGraphVisu();
    void ModifyDownNodeCfgGraphVisu();
    void MoveToModifNodeCfgGraphVisu();
    void ReturnToNodeCfgGraphVisu();
    void MoveTimeOutNodeCfgGraphVisu();
    void MoveUpNodeTrendBack();
    void MoveDownNodeTrendBack();
    void MoveValidNodeTrendBack();
    void MoveTimeOutNodeTrendBack();
    void MoveToModifNode();
    void MoveToModifNodeBlowerAction();
    void MoveToModifNodeMaintPwmBlower();
    void MoveToModifNodeCalibAuto();
    void MoveToNextModifNode();
    void MoveToNextModifNodeOnKey(WayId Key);
    void MoveToNextModifNodeCalib();
    void VerifAndMoveToNextModifNodeCalib();
    void ReturnToNode();
    void ReturnToNodeUsb();
    void ReturnToNodeUsbTO();      
    void ReturnToNodeOnKey(WayId Key);
    void ReturnToNodeOnKeyUsb(WayId Key);
    void ValidUsbStop();      
    void ReturnToNodeCalib();
    void VerifAndReturnToNodeCalib();
    void ReturnToNodeTO();
    void ManageModeChange();
    void EndModifToNode();
    void MoveToModifNodeLoupe();
    void ReturnToNodeLoupe();
    void ReturnToNodeTOLoupe();
    void ReturnToNodeLoupe1191();
    void MoveToNextModifConsultCalib();
    void MoveToNextModifConsultCalib2Value();
    void ReturnToNodeOnConsultCalib();
    void ReturnToNodeOnConsultCalib2Value();
    void MoveToModifNodeConsultCalib();
    void MoveToModifNodeConsultCalib2Value();
    void ChangeModeSimplify();
    void MoveToNextNodeJumpCalib();
    void ReturnToNodeCalibAuto();
    void ReturnToNodeCfgGraphVisuVisu();
    void ReturnToNodeLoupe1151();
    void ReturnToNodeLoupeNodeModifFsecu();
    void MoveToNextModifNodeAlVteMin();
    void MoveToNextModifNodeAlCalibVte();
    void ReturnToNodeTOLoupeNodeAlCalibVte();
    void ReturnToNodeToCalibNodeAlCalibVte();
    void ModifyUpNodeAlCalibVte();
    void ModifyDownNodeAlCalibVte();
    void UpdateColNodeAlCalibVte();
    void MoveToCalibAuto();
    void MoveToNextModifNodeAlFiO2Min();
    void MoveToNextModifNodeAlCalibFiO2();
    void ReturnToNodeTOLoupeNodeAlCalibFiO2();
    void ReturnToNodeToCalibNodeAlCalibFiO2();
    void ModifyUpNodeAlCalibFiO2();
    void ModifyDownNodeAlCalibFiO2();
    void UpdateColNodeAlCalibFiO2();
    void MoveToCalibAutoFiO2();
    void MoveValidNodeModifConfPatientReset();
    void MoveUpNodeConfPatientReset();
    void MoveDownNodeConfPatientReset();
    void MoveToNextModifNodeUsbTransferSetOn();
    void DisplayBreathTiming();
    void ModifyUpNodeInspTime();
    void ModifyDownNodeInspTime();
    void MoveToModifNodeLoupeNodeInspTime();
    void ModifyUpNodePlusPeep();
    void ModifyDownPeepNodePlusPeep();
    void ModifyUpPeepNodePlusPeep();   
    void ModifyDownNodePlusPeep();   
    void Stop100FiO2();
    void MoveToModifNodeFiO2Concent();
    void MoveToModifNodeConsultCalibFiO2Concent();
    void ReturnToNodePediatric();
    void MoveUpNodeConfRestoreDefaultSetting();
    void MoveDownNodeConfRestoreDefaultSetting();
    void MoveValidNodeModifConfRestoreDefaultSetting();
	void DisplayIsensHelperText();
	void ModifyUpNodeIsens();
    void ModifyDownNodeIsens();
	void MoveToModifNodeLoupeNodeIsens();
};

#include "HMI_MenuControlNode.hpp"
extern "C" e_DRV_EVENT_STATE DRV_EVENT_TransStateFlash(void);


#endif
