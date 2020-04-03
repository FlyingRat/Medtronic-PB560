/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_GlobalEventNode.hpp  	 	  		                       	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_GlobalEventNode.cpp   			             	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef GlobalEventNodeH
#define GlobalEventNodeH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "enum.h"
#include "typedef.h"
#include "HMI_EventNode.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
typedef enum
{
   /*C% Ventil menu Node */
   NodeVentil = 0,   NodeModifVentil,  NodeVt, NodeModifVt, NodePi, NodeModifPi, NodePi2, NodeModifPi2,
   NodePControl, NodeModifPControl, NodePSupport, NodeModifPSupport, NodeFVaci, NodeModifFVaci, NodePe, NodeModifPe, NodePente,
	NodeModifPente, NodeRampe, NodeModifRampe, NodeFrMini, NodeModifFrMini, NodeInspTime, NodeModifInspTime,
	NodeTriggerI, NodeModifTriggerI, NodeSoupirSelect, NodeModifSoupirSelect, NodeSoupirVtCoeff, NodeModifSoupirVtCoeff,
   NodeSoupirCpt, NodeModifSoupirCpt, NodeTriggerE, NodeModifTriggerE, NodeFsecu, NodeModifFsecu, NodeFiO2,
   NodeModifFiO2, NodeApnee, NodeModifApnee, NodeVtCible, NodeModifVtCible, NodePiMax, NodeModifPiMax,
   NodeTriggerEsigned, NodeModifTriggerEsigned, NodePreference, NodeModeChange,
	NodeModifModeChange, NodeGhost,

   /*C% Alarm menu Node */
   NodeAlarm, NodeModifAlarm, NodeAlPi, NodeAlPiMin, NodeAlPiMax, NodeAlVti, NodeAlVtiMin,
	NodeAlVtiMax, NodeAlVte, NodeAlVteMin, NodeAlVteMax, NodeAlCalibVte, NodeAlCalibVte2, NodeAlFuite,
   NodeAlFuiteMax, NodeAlFiO2, NodeAlFiO2Min, NodeAlFiO2Max, NodeAlCalibFiO2, NodeAlCalibFiO2_2, NodeAlFr, NodeAlFrMax, NodeAlSpO2,
   NodeAlSpO2Min, NodeAlSpO2Max, NodeAlTi, NodeAlTiMin, NodeAlTiMax,
	NodeAlHisto, NodeAlModeChange, NodeModifAlModeChange, NodeAlGhost,

   /*C% History Alarm menu Node */
   NodeHistAlBack, NodeHistAlCancelled,

   /*C% Configuration menu Node */
    NodeConfLang, 
    NodeModifConfLang, 
    NodeConfDate, 
    NodeConfMonth, 
    NodeConfDay, 
    NodeConfYear, 
    NodeConfTime,
	NodeConfHour, 
    NodeConfMinute, 
    NodeConfSecond, 
    NodePrefVoluntaryStopAlarm, 
    NodeModifPrefVoluntaryStopAlarm, 
    NodeConfPressureUnit, 
    NodeModifConfPressureUnit,
    NodeConfAlarmTone, 
    NodeModifConfAlarmTone,
    NodeConfPatientCount, 
    NodeModifConfPatientCount, 
    NodeConfPatientReset, 
    NodeModifConfPatientReset,
	NodeConfMaint, 
    NodeConfResetDefaultSetting, 
    NodeModifConfResetDefaultSetting,
    NodeConfMachineHour, 
	NodeConfNextPage, 

	/*C% Configuration/setup 2 menu Node */

    NodeConfModeCycl, 
    NodeModifConfModeCycl, 
    NodeConfRelativePress, 
    NodeModifConfRelativePress ,

    NodeConfConvTrigE, 
    NodeModifConfConvTrigE, 
	NodeConfig1BackToConfig, 

    // Circuit Check menu nodes
	NodeTestCircuitLeak,

	/*C% Preference menu Node */
   NodePrefScreenSave, NodeModifPrefScreenSave, NodePrefBrightness, NodeModifPrefBrightness, NodePrefSoundLevel, NodeModifPrefSoundLevel, NodePrefKeyTone,
	NodeModifPrefKeyTone, NodePrefApneaAlarm, NodeModifPrefApneaAlarm, NodePrefDisconnectionAlarm, NodeModifPrefDisconnectionAlarm,
#ifdef HMI_CONFIG_CURVES
  #ifdef HMI_CONFIG_CURVE_CFG
   NodePrefCurveConfig,
  #else
   NodePrefWaveDisplay,
   NodeModifPrefWaveDisplay,
  #endif
#endif  
   NodePrefPediatricCircuit,
   NodeModifPrefPediatricCircuit,
   NodePrefTrend,
   NodePrefBackVentil,

   /*C% Maintenance menu Node */
   NodeMaintHistAno, NodeMaintVoltCtrl, NodeMaintSensorCal,
   NodeMaintGhostStart,
   NodeMaintPatientPressure, NodeMaintPatientPressure1, NodeMaintPatientPressure2, NodeMaintPatientPressure3,
   NoteMaintValvePressure, NoteMaintValvePressure1, NoteMaintValvePressure2, NoteMaintValvePressure3,
   NodeMaintFlowIns, NodeMaintFlowIns1, NodeMaintFlowIns2, NodeMaintFlowIns3, NodeMaintFlowIns4, NodeMaintFlowIns5, NodeMaintFlowIns6, NodeMaintFlowIns7, NodeMaintFlowIns8, NodeMaintFlowIns9,
   NodeMaintFlowExp, NodeMaintFlowExp1, NodeMaintFlowExp2, NodeMaintFlowExp3, NodeMaintFlowExp4, NodeMaintFlowExp5, NodeMaintFlowExp6, NodeMaintFlowExp7,  NodeMaintFlowExp8, NodeMaintFlowExp9,
   NodeMaintFiO2Concent, NodeMaintFiO2Concent1, NodeMaintFiO2Concent2,
   NodeMaintFlowO2, NodeMaintFlowO2_1, NodeMaintFlowO2_2, NodeMaintFlowO2_3, NodeMaintFlowO2_4, NodeMaintFlowO2_5, NodeMaintFlowO2_6, NodeMaintFlowO2_7, NodeMaintFlowO2_8, NodeMaintFlowO2_9,
   NodeMaintPressO2, NodeMaintPressO2_1, NodeMaintPressO2_2,
   NodeMaintGhostEnd,
   NodeMaintPwmBlower, NodeModifMaintPwmBlower, NodeMaintBackToConfig,

   /*C% History Anomalies menu Node */
   NodeHistAnoBackMaint,

   /*C% Supply Control menu Node */
   NodeSupplyBuzVolt, NodeSupplyBackUpBuz, NodeSupplyBatteryMenu, NodeSupplyAltCompens, NodeModifSupplyAltCompens, NodeSupplyBackToMaint,

   /*C% Graph menu Node */
   NodeGraphGhost,

   /*C% Config Graph menu Node */
   NodeCfgGraphVisu, NodeModifCfgGraphVisu, NodeCfgGraphPMax, NodeModifCfgGraphPMax, NodeCfgGraphQMax, NodeModifCfgGraphQMax, NodeCfgGraphVtMax,
	NodeModifCfgGraphVtMax, NodeCfgGraphTMax, NodeModifCfgGraphTMax, NodeCfgGraphRepresent, NodeModifCfgGraphRepresent, NodeCfgGraphBackPref,

   /*C% Battery menu Node */
	NodeBatteryBackToMaint,

	/*C% USB menu Node */
	NodeUsbGhost,
   NodeUsbContRecord, NodeModifUsbContRecord,
   NodeUsbTransferTrend, NodeModifUsbTransferTrend,
   NodeUsbEraseKey, NodeModifUsbEraseKey,
#ifdef HMI_CONFIG_USB_SETTINGS_TRANSFER
	NodeUsbTransferSetOn, NodeModifUsbTransferSetOn, NodeUsbApplySet,
#endif
#ifdef HMI_CONFIG_USB_MONIT_TRANSFER
   NodeUsbTransferMonit, NodeModifUsbTransferMonit,
#endif
#ifdef HMI_CONFIG_USB_EVENTS_TRANSFER
   NodeUsbTransferEvents, NodeModifUsbTransferEvents,
#endif
   NodeUsbStop,
	/*C% Tendance menu Node */
	NodeTrendBack,

	/*C% Fantom Node */
	NodeGhostEnd,

   /*C% Node NULL */
   NodeFree,

   /*C% Number of Node */
   NB_NODE
} IndexNode;

/* ATTENTION - A MODIFIER SI RAJOUT OU SUPPRESSION DE NODE */
/*C% End Node menu constant */
const UWORD16 cVentilStartNode = NodeVentil;
const UWORD16 cVentilEndNode = NodePreference;
const UWORD16 cAlarmStartNode = NodeAlarm;
const UWORD16 cAlarmEndNode = NodeAlHisto;
const UWORD16 cMenuLastNode = NodeTrendBack;
const UWORD16 cUsbStartNode = NodeUsbContRecord;
const UWORD16 cUsbEndNode = NodeUsbEraseKey;
const UWORD16 cMaintCalibStartNode = NodeMaintGhostStart;
const UWORD16 cMaintCalibEndNode = NodeMaintGhostEnd;

#define cMAX_MODE (nb_of_mode)

typedef struct {
   UWORD16 NodeId;
   tInfoNodeForMode InfoByMode[cMAX_MODE];
   UWORD16 Lock;
} tInfoNode;

#define cINFO_NODE_NB   47
extern tInfoNode cInfoNode[cINFO_NODE_NB];
extern const tInfoNode cConstInfoNode[cINFO_NODE_NB];


extern EventNode EventNodeVentil;
extern EventNode EventNodeModifVentil;
extern EventNode EventNodeVt;
extern EventNode EventNodeModifVt;
extern EventNode EventNodePi;
extern EventNode EventNodeModifPi;
extern EventNode EventNodePi2;
extern EventNode EventNodeModifPi2;
extern EventNode EventNodePControl;
extern EventNode EventNodeModifPControl;
extern EventNode EventNodePSupport;
extern EventNode EventNodeModifPSupport;
extern EventNode EventNodeFVaci;
extern EventNode EventNodeModifFVaci;
extern EventNode EventNodePe;
extern EventNode EventNodeModifPe;
extern EventNode EventNodePente;
extern EventNode EventNodeModifPente;
extern EventNode EventNodeRampe;
extern EventNode EventNodeModifRampe;
extern EventNode EventNodeFrMini;
extern EventNode EventNodeModifFrMini;
extern EventNode EventNodeInspTime;
extern EventNode EventNodeModifInspTime;
extern EventNode EventNodeTriggerI;
extern EventNode EventNodeModifTriggerI;
extern EventNode EventNodeSoupirSelect;
extern EventNode EventNodeModifSoupirSelect;
extern EventNode EventNodeSoupirVtCoeff;
extern EventNode EventNodeModifSoupirVtCoeff;
extern EventNode EventNodeSoupirCpt;
extern EventNode EventNodeModifSoupirCpt;
extern EventNode EventNodeTriggerE;
extern EventNode EventNodeModifTriggerE;
extern EventNode EventNodeFsecu;
extern EventNode EventNodeModifFsecu;
extern EventNode EventNodeFiO2;
extern EventNode EventNodeModifFiO2;
extern EventNode EventNodeApnee;
extern EventNode EventNodeModifApnee;
extern EventNode EventNodeVtCible;
extern EventNode EventNodeModifVtCible;
extern EventNode EventNodePiMax;
extern EventNode EventNodeModifPiMax;
extern EventNode EventNodeTriggerEsigned;
extern EventNode EventNodeModifTriggerEsigned;
extern EventNode EventNodePreference;
extern EventNode EventNodeModeChange;
extern EventNode EventNodeModifModeChange;
extern EventNode EventNodeGhost;

extern EventNode EventNodeAlarm;
extern EventNode EventNodeModifAlarm;
extern EventNode EventNodeAlPi;
extern EventNode EventNodeAlPiMin;
extern EventNode EventNodeAlPiMax;
extern EventNode EventNodeAlVti;
extern EventNode EventNodeAlVtiMin;
extern EventNode EventNodeAlVtiMax;
extern EventNode EventNodeAlVte;
extern EventNode EventNodeAlVteMin;
extern EventNode EventNodeAlVteMax;
extern EventNode EventNodeAlCalibVte;
extern EventNode EventNodeAlCalibVte2;
extern EventNode EventNodeAlFuite;
extern EventNode EventNodeAlFuiteMax;
extern EventNode EventNodeAlFiO2;
extern EventNode EventNodeAlFiO2Min;
extern EventNode EventNodeAlFiO2Max;
extern EventNode EventNodeAlCalibFiO2;
extern EventNode EventNodeAlCalibFiO2_2;
extern EventNode EventNodeAlFr;
extern EventNode EventNodeAlFrMax;
extern EventNode EventNodeAlSpO2;
extern EventNode EventNodeAlSpO2Min;
extern EventNode EventNodeAlSpO2Max;
extern EventNode EventNodeAlTi;
extern EventNode EventNodeAlTiMin;
extern EventNode EventNodeAlTiMax;
extern EventNode EventNodeAlHisto;
extern EventNode EventNodeAlModeChange;
extern EventNode EventNodeModifAlModeChange;
extern EventNode EventNodeAlGhost;

extern EventNode EventNodeHistAlBack;
extern EventNode EventNodeHistAlCancelled;

extern EventNode EventNodeConfLang;
extern EventNode EventNodeModifConfLang;
extern EventNode EventNodeConfDate;
extern EventNode EventNodeConfMonth;
extern EventNode EventNodeConfDay;
extern EventNode EventNodeConfYear;
extern EventNode EventNodeConfTime;
extern EventNode EventNodeConfHour;
extern EventNode EventNodeConfMinute;
extern EventNode EventNodeConfSecond;
extern EventNode EventNodeConfPatientCount;
extern EventNode EventNodeModifConfPatientCount;
extern EventNode EventNodeConfPatientReset;
extern EventNode EventNodeModifConfPatientReset;
extern EventNode EventNodeConfMaint;
extern EventNode EventNodeConfNextPage;
extern EventNode EventNodeConfModeCycl;
extern EventNode EventNodeModifConfModeCycl;
extern EventNode EventNodeConfRelativePress;
extern EventNode EventNodeModifConfRelativePress;
extern EventNode EventNodeConfPressureUnit;
extern EventNode EventNodeConfAlarmTone;
extern EventNode EventNodeModifConfPressureUnit;
extern EventNode EventNodeModifConfAlarmTone;
extern EventNode EventNodeConfConvTrigE;
extern EventNode EventNodeModifConfConvTrigE;
extern EventNode EventNodeConfMachineHour;
extern EventNode EventNodeConfig1BackToConfig;
extern EventNode EventNodeConfResetDefaultSetting;
extern EventNode EventNodeModifConfResetDefaultSetting;

extern EventNode EventNodePrefScreenSave;
extern EventNode EventNodeModifPrefScreenSave;
extern EventNode EventNodePrefBrightness;
extern EventNode EventNodeModifPrefBrightness;
extern EventNode EventNodePrefSoundLevel;
extern EventNode EventNodeModifPrefSoundLevel;
extern EventNode EventNodePrefKeyTone;
extern EventNode EventNodeModifPrefKeyTone;
extern EventNode EventNodePrefVoluntaryStopAlarm;
extern EventNode EventNodeModifPrefVoluntaryStopAlarm;
extern EventNode EventNodePrefApneaAlarm;
extern EventNode EventNodeModifPrefApneaAlarm;
extern EventNode EventNodePrefDisconnectionAlarm;
extern EventNode EventNodeModifPrefDisconnectionAlarm;
extern EventNode EventNodePrefWaveDisplay;
extern EventNode EventNodeModifPrefWaveDisplay;
extern EventNode EventNodePrefPediatricCircuit;
extern EventNode EventNodeModifPrefPediatricCircuit;
extern EventNode EventNodePrefCurveConfig;
extern EventNode EventNodePrefTrend;
extern EventNode EventNodePrefBackVentil;

extern EventNode EventNodeCircuitLeak;

extern EventNode EventNodeMaintHistAno;
extern EventNode EventNodeMaintVoltCtrl;
extern EventNode EventNodeMaintSensorCal;
extern EventNode EventNodeMaintGhostStart;
extern EventNode EventNodeMaintPatientPressure;
extern EventNode EventNodeMaintPatientPressure1;
extern EventNode EventNodeMaintPatientPressure2;
extern EventNode EventNodeMaintPatientPressure3;
extern EventNode EventNoteMaintValvePressure;
extern EventNode EventNoteMaintValvePressure1;
extern EventNode EventNoteMaintValvePressure2;
extern EventNode EventNoteMaintValvePressure3;
extern EventNode EventNodeMaintFlowIns;
extern EventNode EventNodeMaintFlowIns1;
extern EventNode EventNodeMaintFlowIns2;
extern EventNode EventNodeMaintFlowIns3;
extern EventNode EventNodeMaintFlowIns4;
extern EventNode EventNodeMaintFlowIns5;
extern EventNode EventNodeMaintFlowIns6;
extern EventNode EventNodeMaintFlowIns7;
extern EventNode EventNodeMaintFlowIns8;
extern EventNode EventNodeMaintFlowIns9;
extern EventNode EventNodeMaintFlowExp;
extern EventNode EventNodeMaintFlowExp1;
extern EventNode EventNodeMaintFlowExp2;
extern EventNode EventNodeMaintFlowExp3;
extern EventNode EventNodeMaintFlowExp4;
extern EventNode EventNodeMaintFlowExp5;
extern EventNode EventNodeMaintFlowExp6;
extern EventNode EventNodeMaintFlowExp7;
extern EventNode EventNodeMaintFlowExp8;
extern EventNode EventNodeMaintFlowExp9;
extern EventNode EventNodeMaintFiO2Concent;
extern EventNode EventNodeMaintFiO2Concent1;
extern EventNode EventNodeMaintFiO2Concent2;
extern EventNode EventNodeMaintFlowO2;
extern EventNode EventNodeMaintFlowO2_1;
extern EventNode EventNodeMaintFlowO2_2;
extern EventNode EventNodeMaintFlowO2_3;
extern EventNode EventNodeMaintFlowO2_4;
extern EventNode EventNodeMaintFlowO2_5;
extern EventNode EventNodeMaintFlowO2_6;
extern EventNode EventNodeMaintFlowO2_7;
extern EventNode EventNodeMaintFlowO2_8;
extern EventNode EventNodeMaintFlowO2_9;
extern EventNode EventNodeMaintPressO2;
extern EventNode EventNodeMaintPressO2_1;
extern EventNode EventNodeMaintPressO2_2;
extern EventNode EventNodeMaintGhostEnd;
extern EventNode EventNodeMaintPwmBlower;
extern EventNode EventNodeModifMaintPwmBlower;
extern EventNode EventNodeMaintBackToConfig;

extern EventNode EventNodeHistAnoBackMaint;

extern EventNode EventNodeSupplyBuzVolt;
extern EventNode EventNodeSupplyBackUpBuz;
extern EventNode EventNodeSupplyBatteryMenu;
extern EventNode EventNodeSupplyAltCompens;
extern EventNode EventNodeModifSupplyAltCompens;
extern EventNode EventNodeSupplyBackToMaint;

extern EventNode EventNodeGraphGhost;

extern EventNode EventNodeCfgGraphVisu;
extern EventNode EventNodeModifCfgGraphVisu;
extern EventNode EventNodeCfgGraphPMax;
extern EventNode EventNodeModifCfgGraphPMax;
extern EventNode EventNodeCfgGraphQMax;
extern EventNode EventNodeModifCfgGraphQMax;
extern EventNode EventNodeCfgGraphVtMax;
extern EventNode EventNodeModifCfgGraphVtMax;
extern EventNode EventNodeCfgGraphTMax;
extern EventNode EventNodeModifCfgGraphTMax;
extern EventNode EventNodeCfgGraphRepresent;
extern EventNode EventNodeModifCfgGraphRepresent;
extern EventNode EventNodeCfgGraphBackPref;

extern EventNode EventNodeBatteryBackToMaint;

extern EventNode EventNodeUsbStop;

#ifdef HMI_CONFIG_USB_SETTINGS_TRANSFER
extern EventNode EventNodeUsbTransferSetOn;
extern EventNode EventNodeModifUsbTransferSetOn;
extern EventNode EventNodeUsbApplySet;
#endif

extern EventNode EventNodeUsbContRecord;
extern EventNode EventNodeModifUsbContRecord;
extern EventNode EventNodeUsbTransferMonit;
extern EventNode EventNodeModifUsbTransferMonit;
extern EventNode EventNodeUsbTransferTrend;
extern EventNode EventNodeModifUsbTransferTrend;
extern EventNode EventNodeUsbTransferEvents;
extern EventNode EventNodeModifUsbTransferEvents;
extern EventNode EventNodeUsbEraseKey;
extern EventNode EventNodeModifUsbEraseKey;
extern EventNode EventNodeUsbGhost;

extern EventNode EventNodeTrendBack;

extern EventNode EventNodeGhostEnd;

extern void InitGloblaEventNode();

#endif
