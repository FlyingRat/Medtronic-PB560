/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_GlobalEventNode.cpp   		  		                  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  Parametres de deplacement dans l'arbre d'etat								   */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_GlobalEventNode.hpp"
#include "HMI_Tools.hpp"
#include "HMI_Config.hpp"
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

/******************************************************************************/
/*                        VARIABLE DECLARATION		               				*/
/******************************************************************************/

EventNode EventNodeGhostEnd;

EventNode EventNodeVentil;
EventNode EventNodeModifVentil;
EventNode EventNodeVt;
EventNode EventNodeModifVt;
EventNode EventNodePi;
EventNode EventNodeModifPi;
EventNode EventNodePi2;
EventNode EventNodeModifPi2;
EventNode EventNodePControl;
EventNode EventNodeModifPControl;
EventNode EventNodePSupport;
EventNode EventNodeModifPSupport;
EventNode EventNodeFVaci;
EventNode EventNodeModifFVaci;
EventNode EventNodePe;
EventNode EventNodeModifPe;
EventNode EventNodePente;
EventNode EventNodeModifPente;
EventNode EventNodeRampe;
EventNode EventNodeModifRampe;
EventNode EventNodeFrMini;
EventNode EventNodeModifFrMini;
EventNode EventNodeInspTime;
EventNode EventNodeModifInspTime;
EventNode EventNodeTriggerI;
EventNode EventNodeModifTriggerI;
EventNode EventNodeSoupirSelect;
EventNode EventNodeModifSoupirSelect;
EventNode EventNodeSoupirVtCoeff;
EventNode EventNodeModifSoupirVtCoeff;
EventNode EventNodeSoupirCpt;
EventNode EventNodeModifSoupirCpt;
EventNode EventNodeTriggerE;
EventNode EventNodeModifTriggerE;
EventNode EventNodeFsecu;
EventNode EventNodeModifFsecu;
EventNode EventNodeFiO2;
EventNode EventNodeModifFiO2;
EventNode EventNodeApnee;
EventNode EventNodeModifApnee;
EventNode EventNodeVtCible;
EventNode EventNodeModifVtCible;
EventNode EventNodePiMax;
EventNode EventNodeModifPiMax;
EventNode EventNodeTriggerEsigned;
EventNode EventNodeModifTriggerEsigned;
EventNode EventNodePreference;
EventNode EventNodeModeChange;
EventNode EventNodeModifModeChange;
EventNode EventNodeGhost;

EventNode EventNodeAlarm;
EventNode EventNodeModifAlarm;
EventNode EventNodeAlPi;
EventNode EventNodeAlPiMin;
EventNode EventNodeAlPiMax;
EventNode EventNodeAlVti;
EventNode EventNodeAlVtiMin;
EventNode EventNodeAlVtiMax;
EventNode EventNodeAlVte;
EventNode EventNodeAlVteMin;
EventNode EventNodeAlVteMax;
EventNode EventNodeAlCalibVte;
EventNode EventNodeAlCalibVte2;
EventNode EventNodeAlFuite;
EventNode EventNodeAlFuiteMax;
EventNode EventNodeAlFiO2;
EventNode EventNodeAlFiO2Min;
EventNode EventNodeAlFiO2Max;
EventNode EventNodeAlCalibFiO2;
EventNode EventNodeAlCalibFiO2_2;
EventNode EventNodeAlFr;
EventNode EventNodeAlFrMax;
EventNode EventNodeAlSpO2;
EventNode EventNodeAlSpO2Min;
EventNode EventNodeAlSpO2Max;
EventNode EventNodeAlTi;
EventNode EventNodeAlTiMin;
EventNode EventNodeAlTiMax;
EventNode EventNodeAlHisto;
EventNode EventNodeAlModeChange;
EventNode EventNodeModifAlModeChange;
EventNode EventNodeAlGhost;

EventNode EventNodeHistAlBack;
EventNode EventNodeHistAlCancelled;

EventNode EventNodeCircuitLeak;

EventNode EventNodeConfLang;
EventNode EventNodeModifConfLang;
EventNode EventNodeConfDate;
EventNode EventNodeConfMonth;
EventNode EventNodeConfDay;
EventNode EventNodeConfYear;
EventNode EventNodeConfTime;
EventNode EventNodeConfHour;
EventNode EventNodeConfMinute;
EventNode EventNodeConfSecond;
EventNode EventNodeConfPatientCount;
EventNode EventNodeModifConfPatientCount;
EventNode EventNodeConfPatientReset;
EventNode EventNodeModifConfPatientReset;
EventNode EventNodeConfMaint;
EventNode EventNodeConfNextPage;
EventNode EventNodeConfModeCycl;
EventNode EventNodeModifConfModeCycl;
EventNode EventNodeConfRelativePress;
EventNode EventNodeModifConfRelativePress;
EventNode EventNodeConfPressureUnit;
EventNode EventNodeConfAlarmTone;
EventNode EventNodeModifConfPressureUnit;
EventNode EventNodeModifConfAlarmTone;
EventNode EventNodeConfConvTrigE;
EventNode EventNodeModifConfConvTrigE;
EventNode EventNodeConfMachineHour;
EventNode EventNodePrefVoluntaryStopAlarm;
EventNode EventNodeModifPrefVoluntaryStopAlarm;
EventNode EventNodeConfig1BackToConfig;
EventNode EventNodeConfResetDefaultSetting;
EventNode EventNodeModifConfResetDefaultSetting;

EventNode EventNodePrefScreenSave;
EventNode EventNodeModifPrefScreenSave;
EventNode EventNodePrefBrightness;
EventNode EventNodeModifPrefBrightness;
EventNode EventNodePrefSoundLevel;
EventNode EventNodeModifPrefSoundLevel;
EventNode EventNodePrefKeyTone;
EventNode EventNodeModifPrefKeyTone;
EventNode EventNodePrefApneaAlarm;
EventNode EventNodeModifPrefApneaAlarm;
EventNode EventNodePrefDisconnectionAlarm;
EventNode EventNodeModifPrefDisconnectionAlarm;
EventNode EventNodePrefWaveDisplay;
EventNode EventNodeModifPrefWaveDisplay;
EventNode EventNodePrefPediatricCircuit;
EventNode EventNodeModifPrefPediatricCircuit;
EventNode EventNodePrefCurveConfig;
EventNode EventNodePrefTrend;
EventNode EventNodePrefBackVentil;

EventNode EventNodeMaintHistAno;
EventNode EventNodeMaintVoltCtrl;
EventNode EventNodeMaintSensorCal;
EventNode EventNodeMaintGhostStart;
EventNode EventNodeMaintPatientPressure;
EventNode EventNodeMaintPatientPressure1;
EventNode EventNodeMaintPatientPressure2;
EventNode EventNodeMaintPatientPressure3;
EventNode EventNoteMaintValvePressure;
EventNode EventNoteMaintValvePressure1;
EventNode EventNoteMaintValvePressure2;
EventNode EventNoteMaintValvePressure3;
EventNode EventNodeMaintFlowIns;
EventNode EventNodeMaintFlowIns1;
EventNode EventNodeMaintFlowIns2;
EventNode EventNodeMaintFlowIns3;
EventNode EventNodeMaintFlowIns4;
EventNode EventNodeMaintFlowIns5;
EventNode EventNodeMaintFlowIns6;
EventNode EventNodeMaintFlowIns7;
EventNode EventNodeMaintFlowIns8;
EventNode EventNodeMaintFlowIns9;
EventNode EventNodeMaintFlowExp;
EventNode EventNodeMaintFlowExp1;
EventNode EventNodeMaintFlowExp2;
EventNode EventNodeMaintFlowExp3;
EventNode EventNodeMaintFlowExp4;
EventNode EventNodeMaintFlowExp5;
EventNode EventNodeMaintFlowExp6;
EventNode EventNodeMaintFlowExp7;
EventNode EventNodeMaintFlowExp8;
EventNode EventNodeMaintFlowExp9;
EventNode EventNodeMaintFiO2Concent;
EventNode EventNodeMaintFiO2Concent1;
EventNode EventNodeMaintFiO2Concent2;
EventNode EventNodeMaintFlowO2;
EventNode EventNodeMaintFlowO2_1;
EventNode EventNodeMaintFlowO2_2;
EventNode EventNodeMaintFlowO2_3;
EventNode EventNodeMaintFlowO2_4;
EventNode EventNodeMaintFlowO2_5;
EventNode EventNodeMaintFlowO2_6;
EventNode EventNodeMaintFlowO2_7;
EventNode EventNodeMaintFlowO2_8;
EventNode EventNodeMaintFlowO2_9;
EventNode EventNodeMaintPressO2;
EventNode EventNodeMaintPressO2_1;
EventNode EventNodeMaintPressO2_2;
EventNode EventNodeMaintGhostEnd;
EventNode EventNodeMaintPwmBlower;
EventNode EventNodeModifMaintPwmBlower;
EventNode EventNodeMaintBackToConfig;

EventNode EventNodeHistAnoBackMaint;

EventNode EventNodeSupplyBuzVolt;
EventNode EventNodeSupplyBackUpBuz;
EventNode EventNodeSupplyBatteryMenu;
EventNode EventNodeSupplyAltCompens;
EventNode EventNodeModifSupplyAltCompens;
EventNode EventNodeSupplyBackToMaint;

EventNode EventNodeGraphGhost;

EventNode EventNodeCfgGraphVisu;
EventNode EventNodeModifCfgGraphVisu;
EventNode EventNodeCfgGraphPMax;
EventNode EventNodeModifCfgGraphPMax;
EventNode EventNodeCfgGraphQMax;
EventNode EventNodeModifCfgGraphQMax;
EventNode EventNodeCfgGraphVtMax;
EventNode EventNodeModifCfgGraphVtMax;
EventNode EventNodeCfgGraphTMax;
EventNode EventNodeModifCfgGraphTMax;
EventNode EventNodeCfgGraphRepresent;
EventNode EventNodeModifCfgGraphRepresent;
EventNode EventNodeCfgGraphBackPref;


EventNode EventNodeBatteryBackToMaint;

EventNode EventNodeUsbStop;

#ifdef HMI_CONFIG_USB_SETTINGS_TRANSFER
EventNode EventNodeUsbTransferSetOn;
EventNode EventNodeModifUsbTransferSetOn;
EventNode EventNodeUsbApplySet;
#endif

EventNode EventNodeUsbContRecord;
EventNode EventNodeModifUsbContRecord;

#ifdef HMI_CONFIG_USB_MONIT_TRANSFER
EventNode EventNodeUsbTransferMonit;
EventNode EventNodeModifUsbTransferMonit;
#endif

EventNode EventNodeUsbTransferTrend;
EventNode EventNodeModifUsbTransferTrend;

#ifdef HMI_CONFIG_USB_EVENTS_TRANSFER
EventNode EventNodeUsbTransferEvents;
EventNode EventNodeModifUsbTransferEvents;
#endif

EventNode EventNodeUsbEraseKey;
EventNode EventNodeModifUsbEraseKey;
EventNode EventNodeUsbGhost;

EventNode EventNodeTrendBack;

UWORD16 cInfoNodeDisplayTable[NB_NODE];
tInfoNode cInfoNode[cINFO_NODE_NB];

#ifdef HMI_CONFIG_M2
const tInfoNode cConstInfoNode[cINFO_NODE_NB] =
{
                        /*C% les modes :    V(A)C,  VP(A)C,   PSV,   VSIMV,  PSIMV,  CPAP */
                        /* id,              {Visible, Order} x nb_mode, Lock */
						{NodeVentil,		{{1,0},	{1,0},	{1,0},	{1,0},	{1,0},	{1,0}	},1},
						{NodeVt,			{{1,1},	{0,0},	{0,0},	{1,1},	{0,0},	{0,0}	},1},
						{NodePi,			{{0,0},	{1,1},	{0,0},	{0,0},	{0,0},	{0,0}	},1},
						{NodePi2,			{{0,0},	{0,0},	{0,0},	{1,2},	{0,0},	{0,0}	},1},
						{NodePControl,		{{0,0},	{0,0},	{0,0},	{0,0},	{1,1},	{0,0}	},1},
						{NodePSupport, 		{{0,0},	{0,0},	{1,1},	{0,0},	{1,2},	{0,0}	},1},
						{NodeFVaci,			{{0,0},	{0,0},	{0,0},	{1,4},	{1,4},	{0,0}	},1},
						{NodePe,			{{1,2},	{1,2},	{1,2},	{1,3},	{1,3},	{1,1}	},1},
						{NodePente,			{{0,0},	{1,3},	{1,3},	{0,0},	{1,9},	{0,0}	},1},
						{NodeRampe,			{{1,3},	{0,0},	{0,0},	{0,0},	{0,0},	{0,0}	},1},
						{NodeFrMini,		{{1,4},	{1,4},	{0,0},	{0,0},	{0,0},	{0,0}	},1},
						{NodeInspTime,		{{0,0},	{0,0},	{0,0},	{1,5},	{1,5},	{0,0}	},1},
						{NodeTriggerI,		{{1,5},	{1,5},	{1,4},	{1,6},	{1,6},	{0,0}	},1},
						{NodeSoupirSelect,	{{1,6},	{0,0},	{0,0},	{0,0},	{0,0},	{0,0}	},1},
						{NodeSoupirVtCoeff,	{{1,7},	{0,0},	{0,0},	{0,0},	{0,0},	{0,0}	},1},
						{NodeSoupirCpt,		{{1,8},	{0,0},	{0,0},	{0,0},	{0,0},	{0,0}	},1},
						{NodeTriggerE,		{{0,0},	{0,0},	{1,5},	{0,0},	{0,0},	{0,0}	},1},
						{NodeFsecu,			{{0,0},	{0,0},	{1,6},	{0,0},	{0,0},	{0,0}	},1},
						{NodeFiO2,			{{1,9}, {1,8}, {1,10},	{1,8},	{1,8},	{1,3}	},1},
						{NodeApnee,			{{0,0},	{0,0},	{1,7},	{1,7},	{1,7},	{1,2}	},1},
						{NodeVtCible,		{{0,0},	{1,6},	{1,8},	{0,0},	{0,0},	{0,0}	},1},
						{NodePiMax,			{{0,0},	{1,7},	{1,9},	{0,0},	{0,0},	{0,0}	},1},
						{NodeTriggerEsigned,{{0,0},	{0,0},	{0,0},	{0,0},	{0,0},	{0,0}	},1},
						{NodePreference,	{{1,10},{1,9},	{1,11},	{1,9}, {1,10},  {1,4}	},1},

						{NodeAlarm,			{{1,0},	{1,0},	{1,0},	{1,0},	{1,0},	{1,0}	},1},
						{NodeAlPi,			{{1,1},	{0,0},	{0,0},	{1,1},	{0,0},	{0,0}	},1},
						{NodeAlVti,			{{0,0},	{1,1},	{1,1},	{0,0},	{1,1},	{1,1}	},1},
						{NodeAlVte,			{{1,2},	{1,2},	{1,2},	{1,2},	{1,2},	{0,0}	},1},
						{NodeAlFuite,		{{0,0},	{0,0},	{0,0},	{0,0},	{0,0},	{1,2}	},1},
						{NodeAlFiO2,		{{0,0},	{0,0},	{0,0},	{0,0},	{0,0},	{0,0}	},1},
						{NodeAlFr,			{{1,3},	{1,3},	{1,3},	{1,3},	{1,3},	{1,3}	},1},
		 #ifdef HMI_CONFIG_SPO2
						{NodeAlSpO2,		{{1,4}, {1,4},  {1,4},  {1,4},  {1,4},  {1,4}	},1},
						{NodeAlTi,          {{0,0}, {0,0},  {1,5},  {0,0},  {0,0},  {0,0}	},1},
						{NodeAlHisto,       {{1,5}, {1,5},  {1,6},  {1,5},  {1,5},  {1,5}	},1},
		 #else
						{NodeAlSpO2,        {{0,0}, {0,0}, 	{0,0}, 	{0,0},	{0,0}, {0,0}	},1},
						{NodeAlTi,          {{0,0}, {0,0}, 	{1,4},	{0,0},	{0,0}, {0,0}	},1},
						{NodeAlHisto,       {{1,4}, {1,4}, 	{1,5}, 	{1,4},	{1,4}, {1,4}	},1},

		 #endif

				  {NodeMaintGhostStart,      {{1,0}, {1,0}, {1,0}, 	{1,0}, 	{1,0}, 	{1,0}	},1},
				  {NodeMaintPatientPressure, {{1,1}, {1,1}, {1,1}, 	{1,1}, 	{1,1}, 	{1,1}	},1},
				  {NoteMaintValvePressure,   {{1,2}, {1,2}, {1,2}, 	{1,2}, 	{1,2}, 	{1,2}	},1},
				  {NodeMaintFlowIns,         {{1,3}, {1,3}, {1,3},	{1,3}, 	{1,3},	{1,3}	},1},
				  {NodeMaintFlowExp,         {{1,4}, {1,4}, {1,4}, 	{1,4}, 	{1,4}, 	{1,4}	},1},
				  {NodeMaintFiO2Concent,     {{0,0}, {0,0}, {0,0}, 	{0,0}, 	{0,0}, 	{0,0}	},1},
				  {NodeMaintFlowO2,          {{1,5}, {1,5}, {1,5}, 	{1,5}, 	{1,5}, 	{1,5}	},1},
				  {NodeMaintPressO2,         {{1,6}, {1,6}, {1,6}, 	{1,6}, 	{1,6},	{1,6}	},1},
				  {NodeMaintGhostEnd,        {{1,7}, {1,7}, {1,7},	{1,7},	{1,7},	{1,7}	},1},

					{NodeGraphGhost,     {{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}},1},

/* fin de tableau ! */  {10999,              {{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}},1} };
/* ligne  conserver ! */

#elif defined HMI_CONFIG_XL2
const tInfoNode cConstInfoNode[cINFO_NODE_NB] =
{
						/*C% les modes :      V(A)C, VP(A)C, PSV, VSIMV,	PSIMV, CPAP */
						/* id,              {Visible, Order} x nb_mode, Lock */
						{NodeVentil,         {{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}},1},
						{NodeVt,             {{1,1}, {0,0}, {0,0}, {1,1}, {0,0}, {0,0}},1},
						{NodePi,             {{0,0}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodePi2,            {{0,0}, {0,0}, {0,0}, {1,2}, {0,0}, {0,0}},1},
						{NodePControl,	     {{0,0}, {0,0},	{0,0}, {0,0}, {1,1}, {0,0}},1},
						{NodePSupport, 		 {{0,0}, {0,0},	{1,1}, {0,0}, {1,2}, {0,0}},1},
						{NodeFVaci,          {{0,0}, {0,0}, {0,0}, {1,5}, {1,5}, {0,0}},1},
						{NodePe,             {{1,2}, {1,2}, {1,2}, {1,3}, {1,3}, {1,1}},1},
						{NodePente,          {{0,0}, {1,3}, {1,3}, {1,4}, {1,4}, {0,0}},1},
						{NodeRampe,          {{1,3}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeFrMini,         {{1,4}, {1,4}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeInspTime,		 {{1,5}, {1,5},	{0,0}, {1,6}, {1,6}, {0,0}},1},
						{NodeTriggerI,       {{1,6}, {1,6}, {1,4}, {1,7}, {1,7}, {0,0}},1},
						{NodeSoupirSelect,   {{1,7}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeSoupirVtCoeff,  {{1,8}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeSoupirCpt,      {{1,9}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeTriggerE,       {{0,0}, {0,0}, {1,5}, {1,8}, {1,8}, {0,0}},1},
						{NodeFsecu,          {{0,0}, {0,0}, {1,6}, {0,0}, {0,0}, {0,0}},1},
						{NodeFiO2,           {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeApnee,          {{0,0}, {0,0}, {1,7}, {1,9}, {1,9}, {1,2}},1},
						{NodeVtCible,        {{0,0}, {1,7}, {1,8}, {0,0}, {0,0}, {0,0}},1},
						{NodePiMax,          {{0,0}, {1,8}, {1,9}, {0,0}, {0,0}, {0,0}},1},
						{NodeTriggerEsigned, {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodePreference,     {{1,10},{1,9}, {1,10},{1,10}, {1,10}, {1,3}},1},

						{NodeAlarm,          {{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}},1},
						{NodeAlPi,           {{1,1}, {0,0}, {0,0}, {1,1}, {0,0}, {0,0}},1},
						{NodeAlVti,          {{0,0}, {1,1}, {1,1}, {0,0}, {1,1}, {1,1}},1},
						{NodeAlVte,          {{1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {0,0}},1},
						{NodeAlFuite,        {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {1,2}},1},
						{NodeAlFiO2,         {{1,4}, {1,4}, {1,4}, {1,4}, {1,4}, {1,4}},1},
						{NodeAlFr,           {{1,3}, {1,3}, {1,3}, {1,3}, {1,3}, {1,3}},1},
		 #ifdef HMI_CONFIG_SPO2
						{NodeAlSpO2,         {{1,5}, {1,5}, {1,5}, {1,5}, {1,5}, {1,5}},1},
						{NodeAlTi,           {{0,0}, {0,0}, {1,6}, {0,0}, {0,0}, {0,0}},1},
						{NodeAlHisto,        {{1,6}, {1,6}, {1,7}, {1,6}, {1,6}, {1,6}},1},
		 #else
						{NodeAlSpO2,         {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeAlTi,           {{0,0}, {0,0}, {1,5}, {0,0}, {0,0}, {0,0}},1},
						{NodeAlHisto,        {{1,5}, {1,5}, {1,6}, {1,5}, {1,5}, {1,5}},1},
		 #endif

				  {NodeMaintGhostStart,      {{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}},1},
				  {NodeMaintPatientPressure, {{1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}},1},
				  {NoteMaintValvePressure,   {{1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}},1},
				  {NodeMaintFlowIns,         {{1,3}, {1,3}, {1,3}, {1,3}, {1,3}, {1,3}},1},
				  {NodeMaintFlowExp,         {{1,4}, {1,4}, {1,4}, {1,4}, {1,4}, {1,4}},1},
				  {NodeMaintFiO2Concent,     {{1,5}, {1,5}, {1,5}, {1,5}, {1,5}, {1,5}},1},
				  {NodeMaintFlowO2,          {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
				  {NodeMaintPressO2,         {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
				  {NodeMaintGhostEnd,        {{1,6}, {1,6}, {1,6}, {1,6}, {1,6}, {1,6}},1},

								{NodeGraphGhost,     {{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}},1},

/* fin de tableau ! */  {10999,              {{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}},1} };
/* ligne  conserver ! */

#elif defined HMI_CONFIG_S2
const tInfoNode cConstInfoNode[cINFO_NODE_NB] =
{
						/*C% les modes :      V(A)C, VP(A)C, PSV, VSIMV, CPAP */
						/* id,              {Visible, Order} x nb_mode, Lock */
						{NodeVentil,         {{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}},1},
						{NodeVt,             {{1,1}, {0,0}, {0,0}, {1,1}, {0,0}, {0,0}},1},
						{NodePi,             {{0,0}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodePi2,            {{0,0}, {0,0}, {0,0}, {1,2}, {0,0}, {0,0}},1},
						{NodePControl,	     {{0,0}, {0,0},	{0,0}, {0,0}, {1,1}, {0,0}},1},
						{NodePSupport, 		 {{0,0}, {0,0},	{1,1}, {0,0}, {1,2}, {0,0}},1},
						{NodeFVaci,          {{0,0}, {0,0}, {0,0}, {1,4}, {1,4}, {0,0}},1},
						{NodePe,             {{1,2}, {1,2}, {1,2}, {1,3}, {1,3}, {1,1}},1},
						{NodePente,          {{0,0}, {1,3}, {1,3}, {0,0}, {0,0}, {0,0}},1},
						{NodeRampe,          {{1,3}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeFrMini,         {{1,4}, {1,4}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeInspTime,		 {{1,5}, {1,5},	{0,0}, {1,5}, {1,5}, {0,0}},1},
						{NodeTriggerI,       {{1,6}, {1,6}, {1,4}, {1,6}, {1,6}, {0,0}},1},
						{NodeSoupirSelect,   {{1,7}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeSoupirVtCoeff,  {{1,8}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeSoupirCpt,      {{1,9}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeTriggerE,       {{0,0}, {0,0}, {1,5}, {0,0}, {0,0}, {0,0}},1},
						{NodeFsecu,          {{0,0}, {0,0}, {1,6}, {0,0}, {0,0}, {0,0}},1},
						{NodeFiO2,           {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeApnee,          {{0,0}, {0,0}, {1,7}, {1,7}, {1,7}, {1,2}},1},
						{NodeVtCible,        {{0,0}, {1,7}, {1,8}, {0,0}, {0,0}, {0,0}},1},
						{NodePiMax,          {{0,0}, {1,8}, {1,9}, {0,0}, {0,0}, {0,0}},1},
						{NodeTriggerEsigned, {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodePreference,     {{1,10},{1,9}, {1,10},{1,8}, {1,8}, {1,3}},1},

						{NodeAlarm,          {{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}},1},
						{NodeAlPi,           {{1,1}, {0,0}, {0,0}, {1,1}, {0,0}, {0,0}},1},
						{NodeAlVti,          {{0,0}, {1,1}, {1,1}, {0,0}, {1,1}, {1,1}},1},
						{NodeAlVte,          {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeAlFuite,        {{1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}},1},
						{NodeAlFiO2,         {{1,4}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeAlFr,           {{1,3}, {1,3}, {1,3}, {1,3}, {1,3}, {1,3}},1},
		 #ifdef HMI_CONFIG_SPO2
						{NodeAlSpO2,         {{0,0}, {1,4}, {1,4}, {1,4}, {1,4}, {1,4}},1},
						{NodeAlTi,           {{0,0}, {0,0}, {1,5}, {0,0}, {0,0}, {0,0}},1},
						{NodeAlHisto,        {{1,5}, {1,5}, {1,6}, {1,5}, {1,5}, {1,5}},1},
		 #else
						{NodeAlSpO2,         {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
						{NodeAlTi,           {{0,0}, {0,0}, {1,4}, {0,0}, {0,0}, {0,0}},1},
						{NodeAlHisto,        {{1,5}, {1,4}, {1,5}, {1,4}, {1,4}, {1,4}},1},

		 #endif

				  {NodeMaintGhostStart,      {{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}},1},
				  {NodeMaintPatientPressure, {{1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}},1},
				  {NoteMaintValvePressure,   {{1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}},1},
				  {NodeMaintFlowIns,         {{1,3}, {1,3}, {1,3}, {1,3}, {1,3}, {1,3}},1},
				  {NodeMaintFlowExp,         {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
				  {NodeMaintFiO2Concent,     {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
				  {NodeMaintFlowO2,          {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
				  {NodeMaintPressO2,         {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},1},
				  {NodeMaintGhostEnd,        {{1,4}, {1,4}, {1,4}, {1,4}, {1,4}, {1,4}},1},

								{NodeGraphGhost,     {{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}},1},

/* fin de tableau ! */  {10999,              {{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}},1} };
/* ligne  conserver ! */
#endif

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/

/******************************************************************************/
/*                           ACCESSEURS				                    			*/
/******************************************************************************/

/******************************************************************************/
/*                           METHODES                	      						*/
/******************************************************************************/
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation de la table de configuration du display pour chaque noeud */
/*%C comportant :  - la frame  laquelle le noeud appartient                  */
/*%C               - si le noeud est un noeud de modif ou non                 */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
#define NOT_MODIF_NODE 0
#define MODIF_NODE 1

void InitInfoNodeDisplayTable(void)
{
   UWORD16 i,j;

   /* initialisation du tableau en ram avec le tableau de constantes */
   for(i=0; i<cINFO_NODE_NB; i++)
   {
	  cInfoNode[i].NodeId = cConstInfoNode[i].NodeId;
	  cInfoNode[i].Lock = cConstInfoNode[i].Lock;

	  for(j=0; j<cMAX_MODE; j++)
	  {
		 cInfoNode[i].InfoByMode[j].Visible =  cConstInfoNode[i].InfoByMode[j].Visible;
		 cInfoNode[i].InfoByMode[j].Order =  cConstInfoNode[i].InfoByMode[j].Order;
	  }
   }

   /*%C Mise  zro de la table */
   for(i=0; i<NB_NODE; i++)
	  cInfoNodeDisplayTable[i] = 0;

   /*%C Les noeuds de la frame ventilation */
   cInfoNodeDisplayTable[NodeVentil] =                (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifVentil] =           (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeVt] =                    (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifVt] =               (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodePi] =                    (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPi] =               (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodePi2] =                   (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPi2] =              (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodePControl] =              (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPControl] =         (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodePSupport] =              (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPSupport] =         (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeFVaci] =                 (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifFVaci] =            (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodePe] =                    (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPe] =               (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodePente] =                 (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPente] =            (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeRampe] =                 (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifRampe] =            (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeFrMini] =                (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifFrMini] =           (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifInspTime] =         (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeInspTime] =              (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeTriggerI] =              (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifTriggerI] =         (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeSoupirSelect] =          (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifSoupirSelect] =     (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeSoupirVtCoeff] =         (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifSoupirVtCoeff] =    (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeSoupirCpt] =             (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifSoupirCpt] =        (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeTriggerE] =              (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifTriggerE] =         (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeFsecu] =                 (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifFsecu] =            (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeFiO2] =                  (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifFiO2] =             (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeApnee] =                 (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifApnee] =            (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeVtCible] =               (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifVtCible] =          (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodePiMax] =                 (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPiMax] =            (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeTriggerEsigned] =        (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifTriggerEsigned] =   (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodePreference] =            (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModeChange] =            (FRAME_VENTILATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifModeChange] =       (FRAME_VENTILATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeGhost] =                 (FRAME_VENTILATION | MODIF_NODE);

   /*%C Les noeuds de la frame Alarme */
   cInfoNodeDisplayTable[NodeAlarm] =                 (FRAME_ALARME | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifAlarm] =            (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlPi] =                  (FRAME_ALARME | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlPiMin] =               (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlPiMax] =               (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlVti] =                 (FRAME_ALARME | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlVtiMin] =              (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlVtiMax] =              (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlVte] =                 (FRAME_ALARME | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlVteMin] =              (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlVteMax] =              (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlCalibVte] =            (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlCalibVte2] =           (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlFuite] =               (FRAME_ALARME | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlFuiteMax] =            (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlFiO2] =                (FRAME_ALARME | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlFiO2Min] =             (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlFiO2Max] =             (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlCalibFiO2] =           (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlCalibFiO2_2] =         (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlFr] =                  (FRAME_ALARME | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlFrMax] =               (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlSpO2] =                (FRAME_ALARME | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlSpO2Min] =             (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlSpO2Max] =             (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlTi] =                  (FRAME_ALARME | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlTiMin] =               (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlTiMax] =               (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlHisto] =               (FRAME_ALARME | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlModeChange] =          (FRAME_ALARME | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifAlModeChange] =     (FRAME_ALARME | MODIF_NODE);
   cInfoNodeDisplayTable[NodeAlGhost] =               (FRAME_ALARME | MODIF_NODE);

   /*%C Les noeuds de la frame historique alarme */
   cInfoNodeDisplayTable[NodeHistAlBack] =            (FRAME_HISTO_ALARME | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeHistAlCancelled] =       (FRAME_HISTO_ALARME | NOT_MODIF_NODE);

   //   Circuit Check Frame nodes 
   cInfoNodeDisplayTable[NodeTestCircuitLeak] =      (FRAME_CIRCUIT_CHECK | NOT_MODIF_NODE);

   /*%C Les noeuds de la frame configuration */
   /* Nodes in the configuration frame */
   cInfoNodeDisplayTable[NodeConfLang] =              (FRAME_CONFIGURATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifConfLang] =         (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfDate] =              (FRAME_CONFIGURATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfMonth] =             (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfDay] =               (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfYear] =              (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfTime] =              (FRAME_CONFIGURATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfHour] =              (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfMinute] =            (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfSecond] =            (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfPatientCount] =      (FRAME_CONFIGURATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifConfPatientCount] = (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfPatientReset] =      (FRAME_CONFIGURATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifConfPatientReset] = (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfResetDefaultSetting] =      (FRAME_CONFIGURATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifConfResetDefaultSetting] = (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfMaint] =             (FRAME_CONFIGURATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfNextPage] =          (FRAME_CONFIGURATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodePrefVoluntaryStopAlarm] =(FRAME_CONFIGURATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPrefVoluntaryStopAlarm] = (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfPressureUnit] =      (FRAME_CONFIGURATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifConfPressureUnit] = (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfAlarmTone] =      (FRAME_CONFIGURATION | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifConfAlarmTone] = (FRAME_CONFIGURATION | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfMachineHour] =       (FRAME_CONFIGURATION | NOT_MODIF_NODE);

   /* Nodes in the configuration/setup 2 frame */

   cInfoNodeDisplayTable[NodeConfModeCycl] =          (FRAME_CONFIGURATION1 | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifConfModeCycl] =     (FRAME_CONFIGURATION1 | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfRelativePress] =     (FRAME_CONFIGURATION1 | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifConfRelativePress] =(FRAME_CONFIGURATION1 | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfConvTrigE] =         (FRAME_CONFIGURATION1 | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifConfConvTrigE] =    (FRAME_CONFIGURATION1 | MODIF_NODE);
   cInfoNodeDisplayTable[NodeConfig1BackToConfig] =          (FRAME_CONFIGURATION1 | NOT_MODIF_NODE);

   /*%C Les noeuds de la frame Preference */
   cInfoNodeDisplayTable[NodePrefScreenSave] =        (FRAME_PREFERENCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPrefScreenSave] =   (FRAME_PREFERENCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodePrefBrightness] =        (FRAME_PREFERENCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPrefBrightness] =   (FRAME_PREFERENCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodePrefSoundLevel] =        (FRAME_PREFERENCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPrefSoundLevel] =   (FRAME_PREFERENCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodePrefKeyTone] =           (FRAME_PREFERENCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPrefKeyTone] =      (FRAME_PREFERENCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodePrefApneaAlarm] =        (FRAME_PREFERENCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPrefApneaAlarm] =   (FRAME_PREFERENCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodePrefDisconnectionAlarm] =        (FRAME_PREFERENCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPrefDisconnectionAlarm] =   (FRAME_PREFERENCE | MODIF_NODE);

#ifdef HMI_CONFIG_CURVES
  #ifdef HMI_CONFIG_CURVE_CFG
   cInfoNodeDisplayTable[NodePrefCurveConfig] =       (FRAME_PREFERENCE | NOT_MODIF_NODE);
  #else
   cInfoNodeDisplayTable[NodePrefWaveDisplay] =       (FRAME_PREFERENCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPrefWaveDisplay] =  (FRAME_PREFERENCE | MODIF_NODE);
  #endif
#endif  
   cInfoNodeDisplayTable[NodePrefPediatricCircuit] =       (FRAME_PREFERENCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifPrefPediatricCircuit] =  (FRAME_PREFERENCE | MODIF_NODE);

   cInfoNodeDisplayTable[NodePrefTrend] =             (FRAME_PREFERENCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodePrefBackVentil] =        (FRAME_PREFERENCE | NOT_MODIF_NODE);

   /*%C Les noeuds de la frame Maintenance */
   cInfoNodeDisplayTable[NodeMaintHistAno] =          (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintVoltCtrl] =         (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintSensorCal] =        (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintGhostStart] =       (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintPatientPressure] =  (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintPatientPressure1] = (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintPatientPressure2] = (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintPatientPressure3] = (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NoteMaintValvePressure] =    (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NoteMaintValvePressure1] =   (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NoteMaintValvePressure2] =   (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NoteMaintValvePressure3] =   (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowIns] =          (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowIns1] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowIns2] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowIns3] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowIns4] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowIns5] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowIns6] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowIns7] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowIns8] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowIns9] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowExp] =          (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowExp1] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowExp2] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowExp3] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowExp4] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowExp5] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowExp6] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowExp7] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowExp8] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowExp9] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFiO2Concent] =      (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFiO2Concent1] =     (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFiO2Concent2] =     (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowO2] =           (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowO2_1] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowO2_2] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowO2_3] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowO2_4] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowO2_5] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowO2_6] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowO2_7] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowO2_8] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintFlowO2_9] =         (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintPressO2] =          (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintPressO2_1] =        (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintPressO2_2] =        (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintGhostEnd] =         (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintPwmBlower] =        (FRAME_MAINTENANCE | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifMaintPwmBlower] =   (FRAME_MAINTENANCE | MODIF_NODE);
   cInfoNodeDisplayTable[NodeMaintBackToConfig] =     (FRAME_MAINTENANCE | NOT_MODIF_NODE);

   /*%C Les noeuds de la frame Histo Anomalies */
   cInfoNodeDisplayTable[NodeHistAnoBackMaint] =      (FRAME_HISTO_ANOMALIE | NOT_MODIF_NODE);

   /*%C Les noeuds de la frame Voltage Check */
   cInfoNodeDisplayTable[NodeSupplyBuzVolt] =         (FRAME_VOLTAGE_CHECK | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeSupplyBackUpBuz] =       (FRAME_VOLTAGE_CHECK | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeSupplyBatteryMenu] =     (FRAME_VOLTAGE_CHECK | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeSupplyAltCompens] =      (FRAME_VOLTAGE_CHECK | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifSupplyAltCompens] = (FRAME_VOLTAGE_CHECK | MODIF_NODE);
   cInfoNodeDisplayTable[NodeSupplyBackToMaint] =     (FRAME_VOLTAGE_CHECK | NOT_MODIF_NODE);

   /*C% Les noeuds de la frame Graphe */
   cInfoNodeDisplayTable[NodeGraphGhost] =            (FRAME_GRAPH | MODIF_NODE);

   /*C% Les noeuds de la frame Configuration Graphe */
   cInfoNodeDisplayTable[NodeCfgGraphVisu] =             (FRAME_CONFIG_GRAPH | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifCfgGraphVisu] =        (FRAME_CONFIG_GRAPH | MODIF_NODE);
   cInfoNodeDisplayTable[NodeCfgGraphPMax] =             (FRAME_CONFIG_GRAPH | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifCfgGraphPMax] =        (FRAME_CONFIG_GRAPH | MODIF_NODE);
   cInfoNodeDisplayTable[NodeCfgGraphQMax] =             (FRAME_CONFIG_GRAPH | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifCfgGraphQMax] =        (FRAME_CONFIG_GRAPH | MODIF_NODE);
   cInfoNodeDisplayTable[NodeCfgGraphVtMax] =            (FRAME_CONFIG_GRAPH | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifCfgGraphVtMax] =       (FRAME_CONFIG_GRAPH | MODIF_NODE);
   cInfoNodeDisplayTable[NodeCfgGraphTMax] =             (FRAME_CONFIG_GRAPH | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifCfgGraphTMax] =        (FRAME_CONFIG_GRAPH | MODIF_NODE);
   cInfoNodeDisplayTable[NodeCfgGraphRepresent] =        (FRAME_CONFIG_GRAPH | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifCfgGraphRepresent] =   (FRAME_CONFIG_GRAPH | MODIF_NODE);
   cInfoNodeDisplayTable[NodeCfgGraphBackPref] =         (FRAME_CONFIG_GRAPH | NOT_MODIF_NODE);

   /*C% Les noeuds de la frame Batterie */
   cInfoNodeDisplayTable[NodeBatteryBackToMaint] =       (FRAME_BATTERIE | NOT_MODIF_NODE);

   /*C% Les noeuds de la frame USB */
   cInfoNodeDisplayTable[NodeUsbGhost] =                 (FRAME_USB | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeUsbEraseKey] =              (FRAME_USB | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifUsbEraseKey] =         (FRAME_USB | MODIF_NODE);
#ifdef HMI_CONFIG_USB_SETTINGS_TRANSFER
   cInfoNodeDisplayTable[NodeUsbTransferSetOn] =         (FRAME_USB | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifUsbTransferSetOn] =    (FRAME_USB | MODIF_NODE);
   cInfoNodeDisplayTable[NodeUsbApplySet] =              (FRAME_USB | MODIF_NODE);
#endif
   cInfoNodeDisplayTable[NodeUsbContRecord] =            (FRAME_USB | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifUsbContRecord] =       (FRAME_USB | MODIF_NODE);
#ifdef HMI_CONFIG_USB_MONIT_TRANSFER
   cInfoNodeDisplayTable[NodeUsbTransferMonit] =         (FRAME_USB | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifUsbTransferMonit] =    (FRAME_USB | MODIF_NODE);
#endif   
   cInfoNodeDisplayTable[NodeUsbTransferTrend] =         (FRAME_USB | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifUsbTransferTrend] =    (FRAME_USB | MODIF_NODE);
#ifdef HMI_CONFIG_USB_EVENTS_TRANSFER
   cInfoNodeDisplayTable[NodeUsbTransferEvents] =        (FRAME_USB | NOT_MODIF_NODE);
   cInfoNodeDisplayTable[NodeModifUsbTransferEvents] =   (FRAME_USB | MODIF_NODE);
#endif   
   cInfoNodeDisplayTable[NodeUsbStop] =                  (FRAME_USB | NOT_MODIF_NODE);

   /*C% Les noeuds de la frame tendance */
   cInfoNodeDisplayTable[NodeTrendBack] =                (FRAME_TENDANCE | NOT_MODIF_NODE);

   /*%C Le noeud fantome */
   cInfoNodeDisplayTable[NodeGhostEnd] =                 (FRAME_NONE | MODIF_NODE);

   /*%C Le noeud free */
   cInfoNodeDisplayTable[NodeFree] =                     (FRAME_NONE | NOT_MODIF_NODE);

   /* Contrle du contenu de la premire partie de la table (noeuds ventil) */
   if(!Tools::CheckInfoNodeTable(cVentilStartNode, cVentilEndNode))
	   Tools::Panic(PANIC_MODULE_EVENT_NODE_VENTIL);

   /* Contrle du contenu de la deuxime partie de la table (noeuds alarm) */
   if(!Tools::CheckInfoNodeTable(cAlarmStartNode, cAlarmEndNode))
	   Tools::Panic(PANIC_MODULE_EVENT_NODE_ALARM);

   /* Contrle du contenu de la troisime partie de la table (noeuds calibration
	  maitenance) */
   if(!Tools::CheckInfoNodeTable(cMaintCalibStartNode, cMaintCalibEndNode))
	   Tools::Panic(PANIC_MODULE_EVENT_NODE_MAINT_CALIB);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des noeud																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void InitGloblaEventNode()
{
/*%C Mthodes de codages des noeuds */

									/*%C Codage :
						   Id,
						   LinkedMenuControlNodeId,
						   OnButtonUp,
						   OnButtonDown
						   OnTimeOut,
						   OnButtonValid
						   OnButtonMonitor,
						   OnButtonLongValid
						   IdNodeOnUp,
						   IdNodeOnDown,
						   IdNodeOnTimeout,
						   IdNodeOnValid,
						   IdNodeOnMonitor,
						   IdNodeOnLongValid

									*/


/*--- Noeud d'init------------------------------------------------------------*/

EventNodeGhostEnd.Init(NodeGhostEnd, NodeGhostEnd,
						   &Controller::NoAction,
									&Controller::NoAction,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodeVentil,
									NodeVt,
						   NodeFree,
						   NodeModifVentil,
						   NodeFree,
						   NodeFree);


/*--- Noeud Ventilation -----------------------------------------------------*/

EventNodeVentil.Init(NodeVentil,   NodeVentil,
						   &Controller::MoveUp,
									&Controller::MoveDown,
						   &Controller::NoAction,
						   &Controller::MoveToModifNode,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodeModeChange,
						   NodeVt,
						   NodeFree,
						   NodeModifVentil,
						   NodeFree,
						   NodeFree);

EventNodeModifVentil.Init(NodeModifVentil,   NodeModifVentil,
						   &Controller::ModifyUp,
									&Controller::ModifyDown,
						   &Controller::ReturnToNodeTO,
						   &Controller::ReturnToNode,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodeFree,
									NodeFree,
						   NodeVentil,
						   NodeVentil,
						   NodeVentil,
						   NodeFree);

EventNodeVt.Init(NodeVt,   NodeVt,
						   &Controller::MoveUp,
									&Controller::MoveDown,
						   &Controller::NoAction,
						   &Controller::MoveToModifNodeLoupe,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodeVentil,
						   NodePi,
						   NodeFree,
						   NodeModifVt,
						   NodeFree,
						   NodeFree);

EventNodeModifVt.Init(NodeModifVt,   NodeModifVt,
						   &Controller::ModifyUp,
									&Controller::ModifyDown,
						   &Controller::ReturnToNodeTOLoupe,
						   &Controller::ReturnToNodeLoupe,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodeFree,
									NodeFree,
						   NodeVt,
						   NodeVt,
						   NodeFree,
						   NodeFree);

EventNodePi.Init(NodePi,   NodePi,
						   &Controller::MoveUp,
									&Controller::MoveDown,
						   &Controller::NoAction,
						   &Controller::MoveToModifNodeLoupe,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodeVt,
						   NodePi2,
						   NodeFree,
						   NodeModifPi,
						   NodeFree,
						   NodeFree);

EventNodeModifPi.Init(NodeModifPi,   NodeModifPi,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodePi,
                           NodePi,
                           NodeFree,
                           NodeFree);

EventNodePi2.Init(NodePi2,   NodePi2,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePi,
                           NodeFVaci,
                           NodeFree,
                           NodeModifPi2,
                           NodeFree,
                           NodeFree);

EventNodeModifPi2.Init(NodeModifPi2,   NodeModifPi2,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodePi2,
                           NodePi2,
                           NodeFree,
                           NodeFree);

EventNodePControl.Init(NodePControl,   NodePControl,
						   &Controller::MoveUp,
									&Controller::MoveDown,
						   &Controller::NoAction,
						   &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
						   &Controller::NoAction,
						   NodeVt,
						   NodePSupport,
						   NodeFree,
						   NodeModifPControl,
						   NodeFree,
						   NodeFree);

EventNodeModifPControl.Init(NodeModifPControl,   NodeModifPControl,
						   &Controller::ModifyUp,
									&Controller::ModifyDown,
						   &Controller::ReturnToNodeTOLoupe,
						   &Controller::ReturnToNodeLoupe,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodeFree,
									NodeFree,
						   NodePControl,
						   NodePControl,
						   NodeFree,
						   NodeFree);

EventNodePSupport.Init(NodePSupport,   NodePSupport,
						   &Controller::MoveUp,
									&Controller::MoveDown,
						   &Controller::NoAction,
						   &Controller::MoveToModifNodeLoupe,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodePControl,
						   NodeFVaci,
						   NodeFree,
						   NodeModifPSupport,
						   NodeFree,
						   NodeFree);

EventNodeModifPSupport.Init(NodeModifPSupport,   NodeModifPSupport,
						   &Controller::ModifyUp,
									&Controller::ModifyDown,
						   &Controller::ReturnToNodeTOLoupe,
						   &Controller::ReturnToNodeLoupe,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodeFree,
									NodeFree,
						   NodePSupport,
						   NodePSupport,
						   NodeFree,
						   NodeFree);

EventNodeFVaci.Init(NodeFVaci,   NodeFVaci,
						   &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupeNodeInspTime,
                           &Controller::NoAction,
                           &Controller::NoAction,
						   NodePSupport,
						   NodeInspTime,
						   NodeFree,
						   NodeModifFVaci,
						   NodeFree,
						   NodeFree);

EventNodeModifFVaci.Init(NodeModifFVaci,   NodeModifFVaci,
						   &Controller::ModifyUpNodeInspTime,
									&Controller::ModifyDownNodeInspTime,
						   &Controller::ReturnToNodeTOLoupe,
						   &Controller::ReturnToNodeLoupe,
									&Controller::NoAction,
						   &Controller::NoAction,
						   NodeFree,
									NodeFree,
						   NodeFVaci,
						   NodeFVaci,
						   NodeFree,
						   NodeFree);

EventNodePe.Init(NodePe,   NodePe,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFVaci,
                           NodePente,
                           NodeFree,
                           NodeModifPe,
                           NodeFree,
                           NodeFree);

EventNodeModifPe.Init(NodeModifPe,   NodeModifPe,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodePe,
                           NodePe,
                           NodeFree,
                           NodeFree);

EventNodePente.Init(NodePente,   NodePente,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePe,
                           NodeRampe,
                           NodeFree,
                           NodeModifPente,
                           NodeFree,
                           NodeFree);

EventNodeModifPente.Init(NodeModifPente,   NodeModifPente,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
									NodePente,
                           NodePente,
                           NodeFree,
                           NodeFree);

EventNodeRampe.Init(NodeRampe,   NodeRampe,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePente,
									NodeFrMini,
                           NodeFree,
									NodeModifRampe,
									NodeFree,
                           NodeFree);

EventNodeModifRampe.Init(NodeModifRampe,   NodeModifRampe,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeRampe,
                           NodeRampe,
                           NodeFree,
                           NodeFree);

EventNodeFrMini.Init(NodeFrMini,   NodeFrMini,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::NoAction,
									&Controller::MoveToModifNodeLoupeNodeInspTime,
									&Controller::NoAction,
                           &Controller::NoAction,
									NodeRampe,
						   NodeInspTime,
						   NodeFree,
                           NodeModifFrMini,
                           NodeFree,
                           NodeFree);

EventNodeModifFrMini.Init(NodeModifFrMini,   NodeModifFrMini,
						   &Controller::ModifyUpNodeInspTime,
									&Controller::ModifyDownNodeInspTime,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeFrMini,
                           NodeFrMini,
						   NodeFree,
						   NodeFree);

EventNodeInspTime.Init(NodeInspTime,   NodeInspTime,
						   &Controller::MoveUp,
									&Controller::MoveDown,
						   &Controller::NoAction,
					   &Controller::MoveToModifNodeLoupeNodeInspTime,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodeFrMini,
						   NodeTriggerI,
						   NodeFree,
						   NodeModifInspTime,
						   NodeFree,
						   NodeFree);

EventNodeModifInspTime.Init(NodeModifInspTime,   NodeModifInspTime,
							&Controller::ModifyUpNodeInspTime,
							&Controller::ModifyDownNodeInspTime,
						   &Controller::ReturnToNodeTOLoupe,
						   &Controller::ReturnToNodeLoupe,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodeFree,
									NodeFree,
						   NodeInspTime,
						   NodeInspTime,
						   NodeFree,
						   NodeFree);

EventNodeTriggerI.Init(NodeTriggerI,   NodeTriggerI,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupeNodeIsens,
                           &Controller::NoAction,
                           &Controller::NoAction,
						   NodeInspTime,
                           NodeSoupirSelect,
                           NodeFree,
                           NodeModifTriggerI,
                           NodeFree,
                           NodeFree);

EventNodeModifTriggerI.Init(NodeModifTriggerI,   NodeModifTriggerI,
                           &Controller::ModifyUpNodeIsens,
									&Controller::ModifyDownNodeIsens,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeTriggerI,
									NodeTriggerI,
                           NodeFree,
                           NodeFree);


EventNodeSoupirSelect.Init(NodeSoupirSelect,   NodeSoupirSelect,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeTriggerI,
                           NodeSoupirVtCoeff,
                           NodeFree,
                           NodeModifSoupirSelect,
                           NodeFree,
                           NodeFree);

EventNodeModifSoupirSelect.Init(NodeModifSoupirSelect,   NodeModifSoupirSelect,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeSoupirSelect,
									NodeSoupirSelect,
                           NodeFree,
                           NodeFree);

EventNodeSoupirVtCoeff.Init(NodeSoupirVtCoeff,   NodeSoupirVtCoeff,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeSoupirSelect,
                           NodeSoupirCpt,
                           NodeFree,
                           NodeModifSoupirVtCoeff,
                           NodeFree,
                           NodeFree);

EventNodeModifSoupirVtCoeff.Init(NodeModifSoupirVtCoeff,   NodeModifSoupirVtCoeff,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeSoupirVtCoeff,
									NodeSoupirVtCoeff,
                           NodeFree,
                           NodeFree);

EventNodeSoupirCpt.Init(NodeSoupirCpt,   NodeSoupirCpt,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeSoupirVtCoeff,
                           NodeTriggerE,
                           NodeFree,
                           NodeModifSoupirCpt,
                           NodeFree,
                           NodeFree);

EventNodeModifSoupirCpt.Init(NodeModifSoupirCpt,   NodeModifSoupirCpt,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeSoupirCpt,
									NodeSoupirCpt,
                           NodeFree,
                           NodeFree);

EventNodeTriggerE.Init(NodeTriggerE,   NodeTriggerE,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeTriggerI,
                           NodeFsecu,
                           NodeFree,
                           NodeModifTriggerE,
                           NodeFree,
                           NodeFree);

EventNodeModifTriggerE.Init(NodeModifTriggerE,   NodeModifTriggerE,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeTriggerE,
                           NodeTriggerE,
                           NodeFree,
                           NodeFree);

EventNodeFsecu.Init(NodeFsecu,   NodeFsecu,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeTriggerE,
									NodeApnee,
									NodeFree,
                           NodeModifFsecu,
                           NodeFree,
                           NodeFree);

EventNodeModifFsecu.Init(NodeModifFsecu,   NodeModifFsecu,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
									&Controller::ReturnToNodeLoupeNodeModifFsecu,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeFsecu,
                           NodeFsecu,
                           NodeFree,
                           NodeFree);

EventNodeFiO2.Init(NodeFiO2,   NodeFiO2,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::NoAction,
									&Controller::MoveToModifNodeLoupe,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeFsecu,
									NodeApnee,
                           NodeFree,
                           NodeModifFiO2,
                           NodeFree,
									NodeFree);

EventNodeModifFiO2.Init(NodeModifFiO2,   NodeModifFiO2,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeFiO2,
                           NodeFiO2,
                           NodeFree,
                           NodeFree);

EventNodeApnee.Init(NodeApnee,   NodeApnee,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::NoAction,
									&Controller::MoveToModifNodeLoupe,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeFiO2,
									NodeVtCible,
                           NodeFree,
                           NodeModifApnee,
                           NodeFree,
									NodeFree);

EventNodeModifApnee.Init(NodeModifApnee,   NodeModifApnee,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeApnee,
                           NodeApnee,
                           NodeFree,
                           NodeFree);

EventNodeVtCible.Init(NodeVtCible,   NodeVtCible,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeApnee,
                           NodePiMax,
                           NodeFree,
                           NodeModifVtCible,
									NodeFree,
                           NodeFree);

EventNodeModifVtCible.Init(NodeModifVtCible,   NodeModifVtCible,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeVtCible,
                           NodeVtCible,
                           NodeFree,
                           NodeFree);

EventNodePiMax.Init(NodePiMax,   NodePiMax,
                           &Controller::MoveUp,
						   &Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeVtCible,
                           NodeTriggerEsigned,
                           NodeFree,
                           NodeModifPiMax,
                           NodeFree,
                           NodeFree);

EventNodeModifPiMax.Init(NodeModifPiMax,   NodeModifPiMax,
                           &Controller::ModifyUp,
                           &Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
						   NodeFree,
                           NodePiMax,
                           NodePiMax,
                           NodeFree,
                           NodeFree);

EventNodeTriggerEsigned.Init(NodeTriggerEsigned,   NodeTriggerEsigned,
                           &Controller::MoveUp,
						   &Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePiMax,
                           NodePreference,
                           NodeFree,
                           NodeModifTriggerEsigned,
                           NodeFree,
                           NodeFree);

EventNodeModifTriggerEsigned.Init(NodeModifTriggerEsigned,   NodeModifTriggerEsigned,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeTriggerEsigned,
                           NodeTriggerEsigned,
                           NodeFree,
                           NodeFree);

EventNodePreference.Init(NodePreference,   NodePreference,
                           &Controller::MoveUp,
									&Controller::MoveDownNodePreference,
                           &Controller::NoAction,
                           &Controller::MoveValidNodePreference,
									&Controller::NoAction,
                           &Controller::NoAction,
                           NodeTriggerEsigned,
                           NodeModeChange,
                           NodeVentil,
                           NodePrefBackVentil,
                           NodeVentil,
                           NodeVentil);

EventNodeModeChange.Init(NodeModeChange,   NodeModeChange,
                           &Controller::MoveUp,
									&Controller::MoveDownNodePreference,
                           &Controller::NoAction,
                           &Controller::ChangeModeSimplify,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePreference,
                           NodeGhost,
                           NodeFree,
                           NodeModifModeChange,
                           NodeFree,
                           NodeFree);

EventNodeModifModeChange.Init(NodeModifModeChange,   NodeModifModeChange,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
									&Controller::ReturnToNodeTO,
									&Controller::ReturnToNode,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeFree,
									NodeFree,
									NodeModeChange,
									NodeModeChange,
									NodeFree,
									NodeFree);

EventNodeGhost.Init(NodeGhost,   NodeGhost,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeModeChange,
                           NodeVentil,
                           NodeModeChange,
                           NodeModeChange,
                           NodeFree,
									NodeFree);

/*--- Noeud Alarme -----------------------------------------------------------*/

EventNodeAlarm.Init(NodeAlarm,   NodeAlarm,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNode,
                           &Controller::MoveValid,
                           &Controller::NoAction,
                           NodeAlModeChange,
                           NodeAlPi,
                           NodeFree,
                           NodeModifAlarm,
                           NodeAlarm,
                           NodeFree);

EventNodeModifAlarm.Init(NodeModifAlarm,   NodeModifAlarm,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNode,
                           &Controller::MoveMonitorNodeModifVentil,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeAlarm,
                           NodeAlarm,
                           NodeAlarm,
                           NodeFree);

EventNodeAlPi.Init(NodeAlPi,   NodeAlPi,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlarm,
                           NodeAlVti,
                           NodeFree,
                           NodeAlPiMin,
                           NodeFree,
                           NodeFree);

EventNodeAlPiMin.Init(NodeAlPiMin,   NodeAlPiMin,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
									&Controller::MoveToNextModifNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodeFree,
									NodeFree,
                           NodeAlPi,
                           NodeAlPiMax,
                           NodeFree,
                           NodeFree);

EventNodeAlPiMax.Init(NodeAlPiMax,   NodeAlPiMax,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodeFree,
									NodeFree,
                           NodeAlPi,
                           NodeAlPi,
                           NodeFree,
                           NodeFree);

EventNodeAlVti.Init(NodeAlVti,   NodeAlVti,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlPi,
                           NodeAlVte,
                           NodeFree,
                           NodeAlVtiMin,
                           NodeFree,
                           NodeFree);

EventNodeAlVtiMin.Init(NodeAlVtiMin,   NodeAlVtiMin,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::MoveToNextModifNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlVti,
                           NodeAlFr,
									NodeAlVti,
                           NodeAlVtiMax,
									NodeFree,
                           NodeFree);

EventNodeAlVtiMax.Init(NodeAlVtiMax,   NodeAlVtiMax,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlVti,
                           NodeAlFr,
                           NodeAlVti,
                           NodeAlVti,
                           NodeFree,
                           NodeFree);

EventNodeAlVte.Init(NodeAlVte,   NodeAlVte,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlVti,
                           NodeAlFuite,
                           NodeFree,
                           NodeAlVteMin,
                           NodeFree,
                           NodeFree);

EventNodeAlVteMin.Init(NodeAlVteMin,   NodeAlVteMin,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::MoveToNextModifNodeAlVteMin,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlVti,
                           NodeAlFuite,
                           NodeAlVte,
                           NodeAlCalibVte,
                           NodeFree,
                           NodeFree);

EventNodeAlVteMax.Init(NodeAlVteMax,   NodeAlVteMax,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
									&Controller::ReturnToNodeTOLoupe,
									&Controller::ReturnToNodeLoupe,
									&Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlVti,
                           NodeAlFuite,
                           NodeAlVte,
                           NodeAlVte,
                           NodeFree,
                           NodeFree);

EventNodeAlCalibVte.Init(NodeAlCalibVte,   NodeAlCalibVte,
                           &Controller::ModifyUpNodeAlCalibVte,
									&Controller::ModifyDownNodeAlCalibVte,
									&Controller::ReturnToNodeTOLoupeNodeAlCalibVte,
                           &Controller::MoveToNextModifNodeAlCalibVte,
									&Controller::NoAction,
									&Controller::NoAction,
                           NodeAlVti,
									NodeAlFuite,
									NodeAlVte,
									NodeAlVteMax,
                           NodeFree,
                           NodeFree);

EventNodeAlCalibVte2.Init(NodeAlCalibVte2,   NodeAlCalibVte2,
                           &Controller::NoAction,
									&Controller::NoAction,
									&Controller::NoAction,
									&Controller::NoAction,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeFree,
									NodeFree,
									NodeAlVte,
                           NodeAlVteMax,
                           NodeFree,
                           NodeFree);

EventNodeAlFuite.Init(NodeAlFuite,   NodeAlFuite,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlVte,
                           NodeAlFiO2,
                           NodeFree,
									NodeAlFuiteMax,
                           NodeFree,
									NodeFree);

EventNodeAlFuiteMax.Init(NodeAlFuiteMax,   NodeAlFuiteMax,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodeFree,
									NodeFree,
									NodeAlFuite,
						   NodeAlFuite,
                           NodeFree,
                           NodeFree);


EventNodeAlFiO2.Init(NodeAlFiO2,   NodeAlFiO2,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlFuite,
                           NodeAlFr,
                           NodeFree,
									NodeAlFiO2Min,
                           NodeFree,
									NodeFree);

EventNodeAlFiO2Min.Init(NodeAlFiO2Min,   NodeAlFiO2Min,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::MoveToNextModifNodeAlFiO2Min,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodeAlFuite,
									NodeAlFr,
									NodeAlFiO2,
                           NodeAlCalibFiO2,
                           NodeFree,
                           NodeFree);

EventNodeAlFiO2Max.Init(NodeAlFiO2Max,   NodeAlFiO2Max,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodeAlFuite,
									NodeAlFr,
                           NodeAlFiO2,
                           NodeAlFiO2,
                           NodeFree,
                           NodeFree);

EventNodeAlCalibFiO2.Init(NodeAlCalibFiO2,   NodeAlCalibFiO2,
                           &Controller::ModifyUpNodeAlCalibFiO2,
									&Controller::ModifyDownNodeAlCalibFiO2,
									&Controller::ReturnToNodeTOLoupeNodeAlCalibFiO2,
                           &Controller::MoveToNextModifNodeAlCalibFiO2,
									&Controller::NoAction,
									&Controller::NoAction,
                           NodeAlFuite,
									NodeAlFr,
									NodeAlFiO2,
									NodeAlFiO2Max,
                           NodeFree,
                           NodeFree);

EventNodeAlCalibFiO2_2.Init(NodeAlCalibFiO2_2,   NodeAlCalibFiO2_2,
                           &Controller::NoAction,
									&Controller::NoAction,
									&Controller::NoAction,
									&Controller::NoAction,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeFree,
									NodeFree,
									NodeAlFiO2,
                           NodeAlFiO2Max,
                           NodeFree,
                           NodeFree);

EventNodeAlFr.Init(NodeAlFr,   NodeAlFr,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlFiO2,
									NodeAlSpO2,
                           NodeFree,
                           NodeAlFrMax,
                           NodeFree,
                           NodeFree);

EventNodeAlFrMax.Init(NodeAlFrMax,   NodeAlFrMax,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
									&Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
									&Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlFiO2,
									NodeAlSpO2,
                           NodeAlFr,
                           NodeAlFr,
                           NodeFree,
									NodeFree);

EventNodeAlSpO2.Init(NodeAlSpO2,   NodeAlSpO2,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::NoAction,
									&Controller::MoveToModifNodeLoupe,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeAlFr,
                           NodeAlTi,
                           NodeAlSpO2,
                           NodeAlSpO2Min,
                           NodeAlarm,
                           NodeAlarm);

EventNodeAlSpO2Min.Init(NodeAlSpO2Min,   NodeAlSpO2Min,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::MoveToNextModifNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodeAlFr,
                           NodeAlTi,
                           NodeAlSpO2,
                           NodeAlSpO2Max,
                           NodeAlarm,
                           NodeAlarm);

EventNodeAlSpO2Max.Init(NodeAlSpO2Max,   NodeAlSpO2Max,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodeAlFr,
                           NodeAlTi,
                           NodeAlSpO2,
									NodeAlSpO2,
                           NodeAlarm,
									NodeAlarm);


EventNodeAlTi.Init(NodeAlTi,   NodeAlTi,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::NoAction,
									&Controller::MoveToModifNodeLoupe,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeAlSpO2,
                           NodeAlHisto,
                           NodeAlTi,
                           NodeAlTiMin,
                           NodeAlarm,
                           NodeAlarm);

EventNodeAlTiMin.Init(NodeAlTiMin,   NodeAlTiMin,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::MoveToNextModifNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodeAlSpO2,
                           NodeAlHisto,
                           NodeAlTi,
                           NodeAlTiMax,
                           NodeAlarm,
                           NodeAlarm);

EventNodeAlTiMax.Init(NodeAlTiMax,   NodeAlTiMax,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTOLoupe,
                           &Controller::ReturnToNodeLoupe,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodeAlSpO2,
                           NodeAlHisto,
                           NodeAlTi,
									NodeAlTi,
                           NodeAlarm,
									NodeAlarm);

EventNodeAlHisto.Init(NodeAlHisto,   NodeAlHisto,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveValidNodeAlHisto,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlTi,
                           NodeAlModeChange,
                           NodeAlarm,
									NodeHistAlBack,
									NodeAlarm,
                           NodeAlarm);

EventNodeAlModeChange.Init(NodeAlModeChange,   NodeAlModeChange,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::ChangeModeSimplify,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeAlHisto,
                           NodeAlarm,
                           NodeAlarm,
                           NodeModifAlModeChange,
                           NodeAlarm,
                           NodeAlarm);

EventNodeModifAlModeChange.Init(NodeModifAlModeChange,   NodeModifAlModeChange,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
									NodeFree,
                           NodeAlModeChange,
                           NodeAlModeChange,
                           NodeAlarm,
                           NodeAlarm);

EventNodeAlGhost.Init(NodeAlGhost,   NodeAlGhost,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveMonitor,
                           &Controller::NoAction,
                           cUsbStartNode,
                           cUsbStartNode,
                           NodeFree,
                           NodeFree,
                           cUsbStartNode,
									NodeFree);


/*--- Histo Alarme -----------------------------------------------------------*/

EventNodeHistAlBack.Init(NodeHistAlBack,   NodeHistAlBack,
                           &Controller::MoveUpNodeHistAlBack,
									&Controller::MoveDownNodeHistAlBack,
									&Controller::MoveTimeOutNodeHistAlBack,
									&Controller::MoveValidNodeHistAlBack,
									&Controller::NoAction,
                           &Controller::NoAction,
                           NodeHistAlCancelled,
                           NodeHistAlCancelled,
									NodeAlarm,
                           NodeAlHisto,
									NodeHistAlBack,
                           NodeHistAlBack);

EventNodeHistAlCancelled.Init(NodeHistAlCancelled,   NodeHistAlCancelled,
                           &Controller::MoveUpNodeHistAlBack,
									&Controller::MoveUpNodeHistAlBack,
									&Controller::MoveTimeOutNodeHistAlBack,
									&Controller::NoAction,
									&Controller::NoAction,
									&Controller::MoveValidNodeHistAlCancelled,
                           NodeHistAlBack,
                           NodeHistAlBack,
                           NodeAlarm,
									NodeHistAlCancelled,
									NodeHistAlCancelled,
									NodeHistAlCancelled);

//--- Circuit Check node ---------------------------------------------------------
    EventNodeCircuitLeak.Init(NodeTestCircuitLeak,    
							  NodeTestCircuitLeak,
                              &Controller::AbortCircuitLeakTest,
                              &Controller::AbortCircuitLeakTest,
                              &Controller::AbortCircuitLeakTest,
                              &Controller::StartCircuitLeakTest, // valid button
							  &Controller::AbortCircuitLeakTest,  // nav button
                              &Controller::AbortCircuitLeakTest,
                              NodeFree,
                              NodeFree,
                              NodeFree,
                              NodeFree,
                              NodeFree,
                              NodeFree);

/*--- Noeud Configuration ----------------------------------------------------*/

EventNodeConfLang.Init(NodeConfLang,   NodeConfLang,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
						   NodeConfNextPage,
                           NodeConfDate,
                           NodeFree,
                           NodeModifConfLang,
                           NodeFree,
                           NodeFree);

EventNodeModifConfLang.Init(NodeModifConfLang,   NodeModifConfLang,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodeConfLang,
                           NodeConfDate,
									NodeConfLang,
                           NodeConfLang,
                           NodeFree,
                           NodeFree);

EventNodeConfDate.Init(NodeConfDate,   NodeConfDate,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
									&Controller::MoveToModifNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeConfLang,
                           NodeConfTime,
                           NodeFree,
                           NodeConfMonth,
                           NodeFree,
                           NodeFree);

EventNodeConfMonth.Init(NodeConfMonth,   NodeConfMonth,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::MoveToNextModifNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeConfTime,
									NodeConfPatientReset,
                           NodeConfDate,
                           NodeConfDay,
                           NodeFree,
                           NodeFree);

EventNodeConfDay.Init(NodeConfDay,   NodeConfDay,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::MoveToNextModifNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeConfTime,
									NodeConfPatientReset,
                           NodeConfDate,
                           NodeConfYear,
                           NodeFree,
                           NodeFree);

EventNodeConfYear.Init(NodeConfYear,   NodeConfYear,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
									&Controller::ReturnToNodeTO,
                           &Controller::ReturnToNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeConfTime,
									NodeConfPatientReset,
                           NodeConfDate,
                           NodeConfDate,
                           NodeFree,
                           NodeFree);

EventNodeConfTime.Init(NodeConfTime,   NodeConfTime,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeConfDate,
					       NodePrefVoluntaryStopAlarm,
                           NodeFree,
                           NodeConfHour,
                           NodeFree,
                           NodeFree);

EventNodeConfHour.Init(NodeConfHour,   NodeConfHour,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::MoveToNextModifNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeConfTime,
                           NodeConfTime,
                           NodeConfTime,
                           NodeConfMinute,
                           NodeFree,
                           NodeFree);

EventNodeConfMinute.Init(NodeConfMinute,   NodeConfMinute,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::MoveToNextModifNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeConfTime,
									NodeConfTime,
                           NodeConfTime,
									NodeConfSecond,
                           NodeFree,
                           NodeFree);

EventNodeConfSecond.Init(NodeConfSecond,   NodeConfSecond,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeConfTime,
                           NodeConfTime,
                           NodeConfTime,
                           NodeConfTime,
                           NodeFree,
                           NodeFree);

EventNodePrefVoluntaryStopAlarm.Init(NodePrefVoluntaryStopAlarm,   NodePrefVoluntaryStopAlarm,
						   &Controller::MoveUp,
						   &Controller::MoveDown,
						   &Controller::NoAction,
						   &Controller::MoveToModifNode,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodeConfTime,
						   NodeConfPressureUnit,
						   NodePrefVoluntaryStopAlarm,
						   NodeModifPrefVoluntaryStopAlarm,
						   NodeFree,
						   NodeFree);

EventNodeModifPrefVoluntaryStopAlarm.Init(NodeModifPrefVoluntaryStopAlarm,   NodeModifPrefVoluntaryStopAlarm,
						   &Controller::ModifyUp,
						   &Controller::ModifyDown,
						   &Controller::ReturnToNodeTO,
						   &Controller::ReturnToNode,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodeFree,
						   NodeFree,
						   NodePrefVoluntaryStopAlarm,
						   NodePrefVoluntaryStopAlarm,
						   NodeFree,
						   NodeFree);

EventNodeConfPressureUnit.Init(NodeConfPressureUnit,   NodeConfPressureUnit,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::NoAction,
									&Controller::MoveToModifNode,
									&Controller::NoAction,
									&Controller::NoAction,
									NodePrefVoluntaryStopAlarm,
									NodeConfAlarmTone,
									NodeConfPressureUnit,
									NodeModifConfPressureUnit,
									NodeFree,
									NodeFree);

EventNodeModifConfPressureUnit.Init(NodeModifConfPressureUnit,   NodeModifConfPressureUnit,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
                           NodeFree,
                           NodeConfPressureUnit,
                           NodeConfPressureUnit,
                           NodeFree,
                           NodeFree);
/* Alarm Tone*/
EventNodeConfAlarmTone.Init(NodeConfAlarmTone,   NodeConfAlarmTone,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::NoAction,
									&Controller::MoveToModifNode,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeConfPressureUnit,
									NodeConfPatientCount,
									NodeConfAlarmTone,
									NodeModifConfAlarmTone,
									NodeFree,
									NodeFree);

EventNodeModifConfAlarmTone.Init(NodeModifConfAlarmTone,   NodeModifConfAlarmTone,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
                           NodeFree,
                           NodeConfAlarmTone,
                           NodeConfAlarmTone,
                           NodeFree,
                           NodeFree);

EventNodeConfPatientCount.Init(NodeConfPatientCount,   NodeConfPatientCount,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::NoAction,
									&Controller::MoveValid,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeConfAlarmTone,
									NodeConfResetDefaultSetting,
									NodeConfPatientReset,
									NodeConfPatientReset,
									NodeConfPatientReset,
									NodeConfPatientReset);

EventNodeModifConfPatientCount.Init(NodeModifConfPatientCount,   NodeModifConfPatientCount,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::NoAction,
									&Controller::MoveValid,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodeConfPatientCount,
                           NodeConfPatientCount,
                           NodeConfPatientCount,
                           NodeConfPatientCount,
                           NodeConfPatientCount,
                           NodeConfPatientCount);


EventNodeConfPatientReset.Init(NodeConfPatientReset,   NodeConfPatientReset,
                           &Controller::MoveUpNodeConfPatientReset,
									&Controller::MoveDownNodeConfPatientReset,
									&Controller::NoAction,
                           &Controller::MoveToModifNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeConfPatientCount,
									NodeConfMaint,
									NodeConfPatientReset,
                           NodeModifConfPatientReset,
                           NodeFree,
                           NodeFree);

EventNodeModifConfPatientReset.Init(NodeModifConfPatientReset,   NodeModifConfPatientReset,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
									&Controller::MoveValidNodeModifConfPatientReset,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeFree,
                           NodeFree,
									NodeConfPatientReset,
									NodeConfPatientReset,
									NodeFree,
									NodeFree);

EventNodeConfMachineHour.Init(NodeConfMachineHour,   NodeConfMachineHour,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveValid,
                           &Controller::NoAction,
									&Controller::NoAction,
									NodeConfPatientCount,
									NodeConfMaint,
                           NodeFree,
                           NodeMaintHistAno,
                           NodeFree,
                           NodeFree);

// Reset Default Settings 
EventNodeConfResetDefaultSetting.Init(NodeConfResetDefaultSetting,   NodeConfResetDefaultSetting,
									&Controller::MoveUpNodeConfRestoreDefaultSetting,
								    &Controller::MoveDownNodeConfRestoreDefaultSetting,
									&Controller::NoAction,
									&Controller::MoveToModifNode,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeConfPatientCount,
									NodeConfMaint,
									NodeConfResetDefaultSetting,
									NodeModifConfResetDefaultSetting,
									NodeFree,
									NodeFree);

EventNodeModifConfResetDefaultSetting.Init(NodeModifConfResetDefaultSetting,   NodeModifConfResetDefaultSetting,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
					       &Controller::MoveValidNodeModifConfRestoreDefaultSetting,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
                           NodeFree,
                           NodeConfResetDefaultSetting,
                           NodeConfResetDefaultSetting,
                           NodeFree,
                           NodeFree);

EventNodeConfMaint.Init(NodeConfMaint,   NodeConfMaint,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveValid,
                           &Controller::NoAction,
									&Controller::NoAction,
									NodeConfResetDefaultSetting,
							NodeConfNextPage,
                           NodeFree,
                           NodeMaintHistAno,
                           NodeFree,
                           NodeFree);

/* next page node */

EventNodeConfNextPage.Init(NodeConfNextPage,   NodeConfNextPage,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveValid,
                           &Controller::NoAction,
									&Controller::NoAction,
									NodeConfMaint,
									NodeConfLang,
                           NodeFree,
                           NodeConfModeCycl,
                           NodeFree,
                           NodeFree);



EventNodeConfModeCycl.Init(NodeConfModeCycl,   NodeConfModeCycl,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::NoAction,
									&Controller::MoveToModifNode,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeConfig1BackToConfig,
									NodeConfRelativePress,
									NodeConfModeCycl,
									NodeModifConfModeCycl,
									NodeFree,
									NodeFree);

EventNodeModifConfModeCycl.Init(NodeModifConfModeCycl,   NodeModifConfModeCycl,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
                           NodeFree,
                           NodeConfModeCycl,
                           NodeConfModeCycl,
                           NodeFree,
                           NodeFree);

EventNodeConfRelativePress.Init(NodeConfRelativePress,   NodeConfRelativePress,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::NoAction,
									&Controller::MoveToModifNode,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeConfModeCycl,
									NodeConfConvTrigE,
									NodeConfRelativePress,
									NodeModifConfRelativePress,
									NodeFree,
									NodeFree);

EventNodeModifConfRelativePress.Init(NodeModifConfRelativePress,   NodeModifConfRelativePress,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
                          NodeFree,
                           NodeConfRelativePress,
                           NodeConfRelativePress,
                           NodeFree,
                           NodeFree);

 // Configuration / Setup 2 Menu
EventNodeConfConvTrigE.Init(NodeConfConvTrigE,   NodeConfConvTrigE,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::NoAction,
									&Controller::MoveToModifNode,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeConfRelativePress,
									NodeConfig1BackToConfig,
									NodeConfConvTrigE,
									NodeModifConfConvTrigE,
									NodeFree,
									NodeFree);

EventNodeModifConfConvTrigE.Init(NodeModifConfConvTrigE,   NodeModifConfConvTrigE,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNode,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
                           NodeFree,
                           NodeConfConvTrigE,
                           NodeConfConvTrigE,
                           NodeFree,
                           NodeFree);


EventNodeConfig1BackToConfig.Init(NodeConfig1BackToConfig,   NodeConfig1BackToConfig,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveValid,
                           &Controller::NoAction,
									&Controller::NoAction,
									NodeConfConvTrigE,
									NodeConfModeCycl,
                           NodeFree,
                           NodeConfNextPage,
                           NodeFree,
                           NodeFree);

/*--- Noeud Preference -------------------------------------------------------*/

EventNodePrefScreenSave.Init(NodePrefScreenSave,   NodePrefScreenSave,
                           &Controller::MoveUpNodePrefScreenSave,
									&Controller::MoveDownNodePrefScreenSave,
                           &Controller::MoveTimeOutNodePrefScreenSave,
                           &Controller::MoveToModifNodePrefScreenSave,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePrefBackVentil,
                           NodePrefBrightness,
                           NodeVentil,
                           NodeModifPrefScreenSave,
                           NodePrefScreenSave,
                           NodePrefScreenSave);

EventNodeModifPrefScreenSave.Init(NodeModifPrefScreenSave,   NodeModifPrefScreenSave,
                           &Controller::ModifyUpNodePrefScreenSave,
									&Controller::ModifyDownNodePrefScreenSave,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNodePrefScreenSave,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePrefScreenSave,
                           NodePrefScreenSave,
                           NodePrefScreenSave,
                           NodePrefScreenSave,
									NodePrefScreenSave,
                           NodePrefScreenSave);

EventNodePrefBrightness.Init(NodePrefBrightness,   NodePrefBrightness,
                           &Controller::MoveUpNodePrefScreenSave,
									&Controller::MoveDownNodePrefScreenSave,
                           &Controller::MoveTimeOutNodePrefScreenSave,
                           &Controller::MoveToModifNodePrefScreenSave,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePrefScreenSave,
                           NodePrefSoundLevel,
                           NodeVentil,
                           NodeModifPrefBrightness,
                           NodePrefScreenSave,
                           NodePrefScreenSave);

EventNodeModifPrefBrightness.Init(NodeModifPrefBrightness,   NodeModifPrefBrightness,
                           &Controller::ModifyUpNodePrefScreenSave,
									&Controller::ModifyDownNodePrefScreenSave,
                           &Controller::ReturnToNodeTONodePrefScreenSave,
                           &Controller::ReturnToNodePrefScreenSave,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePrefScreenSave,
                           NodePrefScreenSave,
                           NodePrefBrightness,
                           NodePrefBrightness,
                           NodePrefScreenSave,
                           NodePrefScreenSave);

EventNodePrefSoundLevel.Init(NodePrefSoundLevel,   NodePrefSoundLevel,
                           &Controller::MoveUpNodePrefScreenSave,
									&Controller::MoveDownNodePrefScreenSave,
                           &Controller::MoveTimeOutNodePrefScreenSave,
                           &Controller::MoveToModifNodePrefScreenSave,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePrefBrightness,
                           NodePrefKeyTone,
                           NodeVentil,
                           NodeModifPrefSoundLevel,
                           NodePrefScreenSave,
                           NodePrefScreenSave);

EventNodeModifPrefSoundLevel.Init(NodeModifPrefSoundLevel,   NodeModifPrefSoundLevel,
                           &Controller::ModifyUpNodePrefScreenSave,
									&Controller::ModifyDownNodePrefScreenSave,
                           &Controller::ReturnToNodeTONodePrefScreenSave,
                           &Controller::ReturnToNodePrefScreenSave,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodePrefScreenSave,
                           NodePrefScreenSave,
									NodePrefSoundLevel,
                           NodePrefSoundLevel,
                           NodePrefScreenSave,
                           NodePrefScreenSave);

EventNodePrefKeyTone.Init(NodePrefKeyTone,   NodePrefKeyTone,
                           &Controller::MoveUpNodePrefScreenSave,
									&Controller::MoveDownNodePrefScreenSave,
                           &Controller::MoveTimeOutNodePrefScreenSave,
                           &Controller::MoveToModifNodePrefScreenSave,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePrefSoundLevel,
						   NodePrefApneaAlarm,
                           NodeVentil,
                           NodeModifPrefKeyTone,
                           NodePrefScreenSave,
                           NodePrefScreenSave);

EventNodeModifPrefKeyTone.Init(NodeModifPrefKeyTone,   NodeModifPrefKeyTone,
                           &Controller::ModifyUpNodePrefScreenSave,
									&Controller::ModifyDownNodePrefScreenSave,
						   &Controller::ReturnToNodeTONodePrefScreenSave,
						   &Controller::ReturnToNodePrefScreenSave,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodePrefScreenSave,
						   NodePrefScreenSave,
						   NodePrefKeyTone,
						   NodePrefKeyTone,
						   NodePrefScreenSave,
						   NodePrefScreenSave);

EventNodePrefApneaAlarm.Init(NodePrefApneaAlarm,   NodePrefApneaAlarm,
						   &Controller::MoveUpNodePrefScreenSave,
						   &Controller::MoveDownNodePrefScreenSave,
						   &Controller::MoveTimeOutNodePrefScreenSave,
						   &Controller::MoveToModifNodePrefScreenSave,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodePrefKeyTone,
                           NodePrefDisconnectionAlarm,
                           NodeVentil,
                           NodeModifPrefApneaAlarm,
                           NodePrefScreenSave,
                           NodePrefScreenSave);

EventNodeModifPrefApneaAlarm.Init(NodeModifPrefApneaAlarm,   NodeModifPrefApneaAlarm,
                           &Controller::ModifyUpNodePrefScreenSave,
									&Controller::ModifyDownNodePrefScreenSave,
                           &Controller::ReturnToNodeTONodePrefScreenSave,
                           &Controller::ReturnToNodePrefScreenSave,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
                           NodeFree,
                           NodePrefApneaAlarm,
                           NodePrefApneaAlarm,
                           NodeFree,
                           NodeFree);

EventNodePrefDisconnectionAlarm.Init(NodePrefDisconnectionAlarm,   NodePrefDisconnectionAlarm,
                           &Controller::MoveUpNodePrefScreenSave,
									&Controller::MoveDownNodePrefScreenSave,
                           &Controller::MoveTimeOutNodePrefScreenSave,
                           &Controller::MoveToModifNodePrefScreenSave,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePrefApneaAlarm,
#ifdef HMI_CONFIG_CURVES
  #ifdef HMI_CONFIG_CURVE_CFG
						   NodePrefCurveConfig,
  #else
						   NodePrefWaveDisplay,
  #endif
#else
						   NodePrefPediatricCircuit,
#endif						   
						   NodeVentil,
                           NodeModifPrefDisconnectionAlarm,
                           NodePrefScreenSave,
						   NodePrefScreenSave);

EventNodeModifPrefDisconnectionAlarm.Init(NodeModifPrefDisconnectionAlarm,   NodeModifPrefDisconnectionAlarm,
                           &Controller::ModifyUpNodePrefScreenSave,
									&Controller::ModifyDownNodePrefScreenSave,
                           &Controller::ReturnToNodeTONodePrefScreenSave,
						   &Controller::ReturnToNodePrefScreenSave,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
                           NodeFree,
                           NodePrefDisconnectionAlarm,
                           NodePrefDisconnectionAlarm,
                           NodeFree,
						   NodeFree);
#ifdef HMI_CONFIG_CURVES

  #ifdef HMI_CONFIG_CURVE_CFG

EventNodePrefCurveConfig.Init(NodePrefCurveConfig,   NodePrefCurveConfig,
						   &Controller::MoveUpNodePrefScreenSave,
									&Controller::MoveDownNodePrefScreenSave,
									&Controller::MoveTimeOutNodePrefScreenSave,
									&Controller::MoveValidNodePrefCurveConfig,
									&Controller::NoAction,
									&Controller::NoAction,
									NodePrefDisconnectionAlarm,
									NodePrefPediatricCircuit,
									NodeVentil,
									NodeCfgGraphVisu,
									NodePrefScreenSave,
									NodePrefScreenSave);
  #else

EventNodePrefWaveDisplay.Init(NodePrefWaveDisplay,   NodePrefWaveDisplay,
						   &Controller::MoveUpNodePrefScreenSave,
									&Controller::MoveDownNodePrefScreenSave,
									&Controller::MoveTimeOutNodePrefScreenSave,
									&Controller::MoveToModifNodePrefScreenSave,
									&Controller::NoAction,
									&Controller::NoAction,
									NodePrefDisconnectionAlarm,
									NodePrefPediatricCircuit,
									NodeVentil,
									NodeModifPrefWaveDisplay,
									NodePrefScreenSave,
									NodePrefScreenSave);

EventNodeModifPrefWaveDisplay.Init(NodeModifPrefWaveDisplay,   NodeModifPrefWaveDisplay,
						   &Controller::ModifyUpNodePrefScreenSave,
									&Controller::ModifyDownNodePrefScreenSave,
									&Controller::ReturnToNodeTONodePrefScreenSave,
									&Controller::ReturnToNodePrefScreenSave,
									&Controller::NoAction,
									&Controller::NoAction,
									NodePrefScreenSave,
									NodePrefScreenSave,
									NodePrefWaveDisplay,
									NodePrefWaveDisplay,
									NodePrefScreenSave,
									NodePrefScreenSave);
  #endif
#endif  


EventNodePrefPediatricCircuit.Init(NodePrefPediatricCircuit,   NodePrefPediatricCircuit,
						   &Controller::MoveUpNodePrefScreenSave,
									&Controller::MoveDownNodePrefScreenSave,
									&Controller::MoveTimeOutNodePrefScreenSave,
									&Controller::MoveToModifNodePrefScreenSave,
									&Controller::NoAction,
									&Controller::NoAction,
#ifdef HMI_CONFIG_CURVES
  #ifdef HMI_CONFIG_CURVE_CFG
									NodePrefCurveConfig,
  #else
									NodePrefWaveDisplay,
  #endif
#else
									NodePrefDisconnectionAlarm,
#endif
									NodePrefTrend,
									NodeVentil,
									NodeModifPrefPediatricCircuit,
									NodePrefScreenSave,
									NodePrefScreenSave);

EventNodeModifPrefPediatricCircuit.Init(NodeModifPrefPediatricCircuit,   NodeModifPrefPediatricCircuit,
						   &Controller::ModifyUpNodePrefScreenSave,
									&Controller::ModifyDownNodePrefScreenSave,
									&Controller::ReturnToNodeTONodePrefScreenSave,
									&Controller::ReturnToNodePediatric,
									&Controller::NoAction,
									&Controller::NoAction,
									NodePrefScreenSave,
									NodePrefScreenSave,
									NodePrefPediatricCircuit,
									NodePrefPediatricCircuit,
									NodePrefScreenSave,
									NodePrefScreenSave);


EventNodePrefTrend.Init(NodePrefTrend,   NodePrefTrend,
						   &Controller::MoveUpNodePrefScreenSave,
									&Controller::MoveDownNodePrefScreenSave,
						   &Controller::MoveTimeOutNodePrefScreenSave,
						   &Controller::MoveValidNodePrefTrend,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   NodePrefPediatricCircuit,
                           NodePrefBackVentil,
									NodeVentil,
                           NodeTrendBack,
                           NodePrefScreenSave,
									NodePrefScreenSave);

EventNodePrefBackVentil.Init(NodePrefBackVentil,   NodePrefBackVentil,
                           &Controller::MoveUpNodePrefScreenSave,
									&Controller::MoveDownNodePrefScreenSave,
                           &Controller::MoveTimeOutNodePrefScreenSave,
                           &Controller::MoveValidNodePrefBackVentil,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodePrefTrend,
                           NodePrefScreenSave,
									NodeVentil,
                           NodeVentil,
                           NodePrefScreenSave,
									NodePrefScreenSave);

/*--- Noeud Maintenance ------------------------------------------------------*/

EventNodeMaintHistAno.Init(NodeMaintHistAno,   NodeMaintHistAno,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveValid,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeMaintBackToConfig,
                           NodeMaintVoltCtrl,
                           NodeFree,
                           NodeHistAnoBackMaint,
                           NodeFree,
                           NodeFree);

EventNodeMaintVoltCtrl.Init(NodeMaintVoltCtrl,   NodeMaintVoltCtrl,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveValid,
                           &Controller::NoAction,
									&Controller::NoAction,
                           NodeMaintHistAno,
									NodeMaintSensorCal,
                           NodeFree,
                           NodeSupplyBuzVolt,
                           NodeFree,
                           NodeFree);

EventNodeMaintSensorCal.Init(NodeMaintSensorCal,   NodeMaintSensorCal,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
									&Controller::MoveValid,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeMaintVoltCtrl,
                           NodeMaintPwmBlower,
                           NodeFree,
									NodeMaintPatientPressure,
                           NodeFree,
                           NodeFree);

EventNodeMaintGhostStart.Init(NodeMaintGhostStart,   NodeMaintGhostStart,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
						   &Controller::NoAction,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeFree,
									NodeFree);


EventNodeMaintPatientPressure.Init(NodeMaintPatientPressure,   NodeMaintPatientPressure,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
						   &Controller::MoveToModifNodeBlowerAction,
                           &Controller::MoveToModifNodeConsultCalib2Value,
                           &Controller::NoAction,
                           NodeMaintSensorCal,
                           NoteMaintValvePressure,
                           NodeFree,
                           NodeMaintPatientPressure1,
                           NodeMaintPatientPressure3,
                           NodeFree);

EventNodeMaintPatientPressure1.Init(NodeMaintPatientPressure1,   NodeMaintPatientPressure1,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NodeMaintSensorCal,
                           NoteMaintValvePressure,
                           NodeMaintPatientPressure,
                           NodeMaintPatientPressure,
                           NodeMaintPatientPressure2,
                           NodeMaintPatientPressure2);

EventNodeMaintPatientPressure2.Init(NodeMaintPatientPressure2,   NodeMaintPatientPressure2,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalib,
                           &Controller::VerifAndReturnToNodeCalib,
                           NodeMaintSensorCal,
                           NoteMaintValvePressure,
                           NodeMaintPatientPressure,
                           NodeMaintPatientPressure,
                           NodeMaintPatientPressure,
                           NodeMaintPatientPressure);

EventNodeMaintPatientPressure3.Init(NodeMaintPatientPressure3,   NodeMaintPatientPressure3,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextModifConsultCalib2Value,
                           &Controller::NoAction,
                           NodeMaintSensorCal,
                           NoteMaintValvePressure,
                           NodeMaintPatientPressure,
                           NodeMaintPatientPressure,
                           NodeMaintPatientPressure,
                           NodeMaintPatientPressure2);

EventNoteMaintValvePressure.Init(NoteMaintValvePressure,   NoteMaintValvePressure,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeCalibAuto,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeMaintPatientPressure,
                           NodeMaintFlowIns,
                           NodeFree,
                           NoteMaintValvePressure1,
                           NoteMaintValvePressure2,
                           NoteMaintValvePressure);

EventNoteMaintValvePressure1.Init(NoteMaintValvePressure1,   NoteMaintValvePressure1,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalibAuto,
                           &Controller::NoAction,
									NodeMaintPatientPressure,
                           NodeMaintFlowIns,
									NoteMaintValvePressure,
                           NoteMaintValvePressure,
                           NoteMaintValvePressure,
                           NoteMaintValvePressure2);

EventNoteMaintValvePressure2.Init(NoteMaintValvePressure2,   NoteMaintValvePressure2,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalibAuto,
                           &Controller::NoAction,
                           NodeMaintFlowIns,
                           NoteMaintValvePressure,
                           NoteMaintValvePressure,
                           NoteMaintValvePressure,
                           NoteMaintValvePressure,
                           NoteMaintValvePressure3);

EventNoteMaintValvePressure3.Init(NoteMaintValvePressure3,   NoteMaintValvePressure3,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::VerifAndReturnToNodeCalib,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalibAuto,
                           &Controller::NoAction,
                           NodeMaintFlowIns,
                           NoteMaintValvePressure,
                           NoteMaintValvePressure,
                           NoteMaintValvePressure,
                           NoteMaintValvePressure,
                           NoteMaintValvePressure);

EventNodeMaintFlowIns.Init(NodeMaintFlowIns,   NodeMaintFlowIns,
                           &Controller::MoveUp,
									&Controller::MoveDown,                           
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeBlowerAction,
                           &Controller::MoveToModifNodeConsultCalib,
                           &Controller::NoAction,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowIns1,
                           NodeMaintFlowIns9,
                           NodeFree);

EventNodeMaintFlowIns1.Init(NodeMaintFlowIns1,   NodeMaintFlowIns1,
                           &Controller::NoAction,
						   &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowIns,
                           NodeMaintFlowIns2,
                           NodeMaintFlowIns2);

EventNodeMaintFlowIns2.Init(NodeMaintFlowIns2,   NodeMaintFlowIns2,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
									&Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowIns,
                           NodeMaintFlowIns3,
                           NodeMaintFlowIns3);

EventNodeMaintFlowIns3.Init(NodeMaintFlowIns3,   NodeMaintFlowIns3,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowIns,
                           NodeMaintFlowIns4,
                           NodeMaintFlowIns4);

EventNodeMaintFlowIns4.Init(NodeMaintFlowIns4,   NodeMaintFlowIns4,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowIns,
                           NodeMaintFlowIns5,
                           NodeMaintFlowIns5);

EventNodeMaintFlowIns5.Init(NodeMaintFlowIns5,   NodeMaintFlowIns5,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NoteMaintValvePressure,
									NodeMaintFlowExp,
                           NoteMaintValvePressure,
									NodeMaintFlowIns,
                           NodeMaintFlowIns6,
                           NodeMaintFlowIns6);

EventNodeMaintFlowIns6.Init(NodeMaintFlowIns6,   NodeMaintFlowIns6,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowIns,
                           NodeMaintFlowIns7,
                           NodeMaintFlowIns7);

EventNodeMaintFlowIns7.Init(NodeMaintFlowIns7,   NodeMaintFlowIns7,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowIns,
                           NodeMaintFlowIns8,
                           NodeMaintFlowIns8);

EventNodeMaintFlowIns8.Init(NodeMaintFlowIns8,   NodeMaintFlowIns8,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalib,
                           &Controller::VerifAndReturnToNodeCalib,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowIns,
                           NodeMaintFlowIns,
                           NodeMaintFlowIns);

EventNodeMaintFlowIns9.Init(NodeMaintFlowIns9,   NodeMaintFlowIns9,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::MoveToNextModifConsultCalib,
                           &Controller::NoAction,
                           NodeMaintSensorCal,
                           NoteMaintValvePressure,
                           NodeMaintPatientPressure,
                           NodeMaintFlowIns,
                           NodeMaintFlowIns,
                           NodeMaintPatientPressure2);

EventNodeMaintFlowExp.Init(NodeMaintFlowExp,   NodeMaintFlowExp,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeCalibAuto,
                           &Controller::MoveToModifNodeConsultCalib,
                           &Controller::NoAction,
                           NodeMaintFlowIns,
                           NodeMaintFiO2Concent,
                           NodeFree,
                           NodeMaintFlowExp1,
                           NodeMaintFlowExp9,
                           NodeMaintFlowIns);

EventNodeMaintFlowExp1.Init(NodeMaintFlowExp1,   NodeMaintFlowExp1,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalibAuto,
                           &Controller::NoAction,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp2);

EventNodeMaintFlowExp2.Init(NodeMaintFlowExp2,   NodeMaintFlowExp2,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalibAuto,
                           &Controller::NoAction,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
									NoteMaintValvePressure,
                           NodeMaintFlowExp,
									NodeMaintFlowExp,
                           NodeMaintFlowExp3);

EventNodeMaintFlowExp3.Init(NodeMaintFlowExp3,   NodeMaintFlowExp3,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalibAuto,
                           &Controller::NoAction,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp4);

EventNodeMaintFlowExp4.Init(NodeMaintFlowExp4,   NodeMaintFlowExp4,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalibAuto,
                           &Controller::NoAction,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp5);

EventNodeMaintFlowExp5.Init(NodeMaintFlowExp5,   NodeMaintFlowExp5,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp6);

EventNodeMaintFlowExp6.Init(NodeMaintFlowExp6,   NodeMaintFlowExp6,
                           &Controller::NoAction,
									&Controller::NoAction,
									&Controller::VerifAndMoveToNextModifNodeCalib,
                           &Controller::NoAction,
									&Controller::ReturnToNodeCalibAuto,
                           &Controller::NoAction,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp7);

EventNodeMaintFlowExp7.Init(NodeMaintFlowExp7,   NodeMaintFlowExp7,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalibAuto,
                           &Controller::NoAction,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp8);

EventNodeMaintFlowExp8.Init(NodeMaintFlowExp8,   NodeMaintFlowExp8,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::VerifAndReturnToNodeCalib,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalibAuto,
                           &Controller::NoAction,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NoteMaintValvePressure,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp,
                           NodeMaintFlowExp);

EventNodeMaintFlowExp9.Init(NodeMaintFlowExp9,   NodeMaintFlowExp9,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextModifConsultCalib,
                           &Controller::NoAction,
                           NodeMaintSensorCal,
                           NoteMaintValvePressure,
                           NodeMaintPatientPressure,
									NodeMaintFlowExp,
                           NodeMaintFlowExp,
									NodeMaintPatientPressure2);

EventNodeMaintFiO2Concent.Init(NodeMaintFiO2Concent,   NodeMaintFiO2Concent,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeFiO2Concent,
                           &Controller::MoveToModifNodeConsultCalibFiO2Concent,
                           &Controller::NoAction,
                           NodeFree,
                           NodeMaintPwmBlower,
                           NodeFree,
                           NodeMaintFiO2Concent1,
                           NodeMaintFiO2Concent2,
                           NodeFree);

EventNodeMaintFiO2Concent1.Init(NodeMaintFiO2Concent1,   NodeMaintFiO2Concent1,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   &Controller::ReturnToNodeCalib,
						   &Controller::VerifAndReturnToNodeCalib,
						   NodeFree,
						   NodeFree,
						   NodeFree,
						   NodeMaintFiO2Concent,
						   NodeMaintFiO2Concent,
						   NodeMaintFiO2Concent);

EventNodeMaintFiO2Concent2.Init(NodeMaintFiO2Concent2,   NodeMaintFiO2Concent2,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   &Controller::NoAction,
						   &Controller::MoveToNextModifConsultCalib,
						   &Controller::NoAction,
						   NodeFree,
						   NodeFree,
						   NodeFree,
						   NodeMaintFiO2Concent,
						   NodeMaintFiO2Concent,
						   NodeMaintFiO2Concent);

EventNodeMaintFlowO2.Init(NodeMaintFlowO2,   NodeMaintFlowO2,
						   &Controller::MoveUp,
									&Controller::MoveDown,
						   &Controller::NoAction,
						   //&Controller::MoveToModifNodeBlowerAction,
						   &Controller::MoveToModifNode,
						   &Controller::MoveToModifNodeConsultCalib,
                           &Controller::NoAction,
                           NodeMaintFiO2Concent,
                           NodeMaintPressO2,
                           NodeFree,
                           NodeMaintFlowO2_1,
                           NodeMaintFlowO2_9,
                           NodeFree);

EventNodeMaintFlowO2_1.Init(NodeMaintFlowO2_1,   NodeMaintFlowO2_1,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeMaintFlowO2,
                           NodeMaintFlowO2_2,
                           NodeMaintFlowO2_2);

EventNodeMaintFlowO2_2.Init(NodeMaintFlowO2_2,   NodeMaintFlowO2_2,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeMaintFlowO2,
                           NodeMaintFlowO2_3,
                           NodeMaintFlowO2_3);

EventNodeMaintFlowO2_3.Init(NodeMaintFlowO2_3,   NodeMaintFlowO2_3,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeMaintFlowO2,
                           NodeMaintFlowO2_4,
                           NodeMaintFlowO2_4);

EventNodeMaintFlowO2_4.Init(NodeMaintFlowO2_4,   NodeMaintFlowO2_4,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeMaintFlowO2,
                           NodeMaintFlowO2_5,
                           NodeMaintFlowO2_5);

EventNodeMaintFlowO2_5.Init(NodeMaintFlowO2_5,   NodeMaintFlowO2_5,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalib,
                           &Controller::VerifAndReturnToNodeCalib,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeMaintFlowO2,
                           NodeMaintFlowO2,
                           NodeMaintFlowO2);
/* On ne passe pas par les noeuds de calibration dbit O2 suivants (comme sur supportair)*/
EventNodeMaintFlowO2_6.Init(NodeMaintFlowO2_6,   NodeMaintFlowO2_6,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeMaintFlowO2,
                           NodeMaintFlowO2_7,
                           NodeMaintFlowO2_7);

EventNodeMaintFlowO2_7.Init(NodeMaintFlowO2_7,   NodeMaintFlowO2_7,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeMaintFlowO2,
                           NodeMaintFlowO2_8,
                           NodeMaintFlowO2_8);

EventNodeMaintFlowO2_8.Init(NodeMaintFlowO2_8,   NodeMaintFlowO2_8,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextNodeJumpCalib,
                           &Controller::VerifAndMoveToNextModifNodeCalib,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeMaintFlowO2,
                           NodeMaintFlowO2_9,
                           NodeMaintFlowO2_9);

EventNodeMaintFlowO2_9.Init(NodeMaintFlowO2_9,   NodeMaintFlowO2_9,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextModifConsultCalib,
                           &Controller::VerifAndReturnToNodeCalib,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeMaintFlowO2,
                           NodeMaintFlowO2,
                           NodeMaintFlowO2);


EventNodeMaintPressO2.Init(NodeMaintPressO2,   NodeMaintPressO2,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveToModifNode,
                           &Controller::MoveToModifNodeConsultCalib,
                           &Controller::NoAction,
                           NodeMaintFlowO2,
                           NodeMaintPwmBlower,
                           NodeFree,
                           NodeMaintPressO2_1,
                           NodeMaintPressO2_2,
                           NodeFree);

EventNodeMaintPressO2_1.Init(NodeMaintPressO2_1,   NodeMaintPressO2_1,
                           &Controller::ModifyUpRefreshBlower,
									&Controller::ModifyDownRefreshBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::ReturnToNodeCalib,
                           &Controller::VerifAndReturnToNodeCalib,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeMaintPressO2,
                           NodeMaintPressO2,
                           NodeMaintPressO2);

EventNodeMaintPressO2_2.Init(NodeMaintPressO2_2,   NodeMaintPressO2_2,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveToNextModifConsultCalib,
                           &Controller::NoAction,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeMaintPressO2,
                           NodeMaintPressO2,
                           NodeMaintPressO2);


EventNodeMaintPwmBlower.Init(NodeMaintPwmBlower,   NodeMaintPwmBlower,
                           &Controller::MoveUpNodeMaintPwmBlower,
									&Controller::MoveDownNodeMaintPwmBlower,
                           &Controller::NoAction,
                           &Controller::MoveToModifNodeMaintPwmBlower,
                           &Controller::StartBlowerBurnTest,
                           &Controller::NoAction,
                           NodeMaintSensorCal,
                           NodeMaintBackToConfig,
                           NodeMaintHistAno,
                           NodeModifMaintPwmBlower,
                           NodeMaintHistAno,
                           NodeMaintHistAno);

EventNodeModifMaintPwmBlower.Init(NodeModifMaintPwmBlower,   NodeModifMaintPwmBlower,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
                           &Controller::ReturnToNodeMaintPwmBlowerTO,
                           &Controller::ReturnToNodeMaintPwmBlower,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeMaintSensorCal,
                           NodeMaintPwmBlower,
                           NodeMaintPwmBlower,
                           NodeMaintPwmBlower,
                           NodeMaintHistAno,
                           NodeMaintHistAno);

EventNodeMaintBackToConfig.Init(NodeMaintBackToConfig,   NodeMaintBackToConfig,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveValid,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeMaintPwmBlower,
                           NodeMaintHistAno,
                           NodeMaintHistAno,
									NodeConfMaint,
                           NodeMaintHistAno,
                           NodeMaintHistAno);


EventNodeMaintGhostEnd.Init(NodeMaintGhostEnd,   NodeMaintGhostEnd,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeFree,
									NodeFree);

/*--- Noeud Histo anomalie ---------------------------------------------------*/

EventNodeHistAnoBackMaint.Init(NodeHistAnoBackMaint,   NodeHistAnoBackMaint,
                           &Controller::MoveValid,
									&Controller::MoveValid,
                           &Controller::NoAction,
									&Controller::MoveValid,
                           &Controller::MoveValid,
                           &Controller::NoAction,
                           NodeHistAnoBackMaint,
                           NodeHistAnoBackMaint,
                           NodeFree,
                           NodeMaintHistAno,
                           NodeFree,
                           NodeFree);

/*--- Noeud Controle de tension ----------------------------------------------*/

EventNodeSupplyBuzVolt.Init(NodeSupplyBuzVolt,   NodeSupplyBuzVolt,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::PlayBuzzer,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeSupplyBackToMaint,
                           NodeSupplyBackUpBuz,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeFree);

EventNodeSupplyBackUpBuz.Init(NodeSupplyBackUpBuz,   NodeSupplyBackUpBuz,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::PlayBuzzerSec,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeSupplyBuzVolt,
                           NodeSupplyBatteryMenu,
                           NodeFree,
                           NodeFree,
                           NodeFree,
                           NodeFree);

EventNodeSupplyBatteryMenu.Init(NodeSupplyBatteryMenu,   NodeSupplyBatteryMenu,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveValid,
                           &Controller::NoAction,
                           &Controller::NoAction,
									NodeSupplyBackUpBuz,
                           NodeSupplyAltCompens,
									NodeFree,
                           NodeBatteryBackToMaint,
                           NodeFree,
                           NodeFree);

EventNodeSupplyAltCompens.Init(NodeSupplyAltCompens,   NodeSupplyAltCompens,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::NoAction,
									&Controller::MoveToModifNode,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeSupplyBatteryMenu,
									NodeSupplyBackToMaint,
									NodeFree,
									NodeModifSupplyAltCompens,
									NodeFree,
									NodeFree);

EventNodeModifSupplyAltCompens.Init(NodeModifSupplyAltCompens,   NodeModifSupplyAltCompens,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
									&Controller::ReturnToNodeTO,
									&Controller::ReturnToNode,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeFree,
									NodeFree,
									NodeSupplyAltCompens,
									NodeSupplyAltCompens,
									NodeFree,
									NodeFree);


EventNodeSupplyBackToMaint.Init(NodeSupplyBackToMaint,   NodeSupplyBackToMaint,
                           &Controller::MoveUp,
									&Controller::MoveDown,
                           &Controller::NoAction,
                           &Controller::MoveValid,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeSupplyAltCompens,
                           NodeSupplyBuzVolt,
                           NodeMaintHistAno,
                           NodeMaintVoltCtrl,
                           NodeMaintHistAno,
                           NodeMaintHistAno);


/*--- Noeud Graph ------------------------------------------------------------*/

EventNodeGraphGhost.Init(NodeGraphGhost,   NodeGraphGhost,
                           &Controller::MoveUpNodeGraphGhost,
									&Controller::MoveDownNodeGraphGhost,
									&Controller::NoAction,
                           &Controller::NoAction,
									&Controller::MoveMonitor,
                           &Controller::NoAction,
									NodeFree,
									NodeFree,
									NodeGraphGhost,
									NodeGraphGhost,
									cUsbStartNode,
                           NodeFree);

/*--- Noeud Config graph -----------------------------------------------------*/
#ifdef HMI_CONFIG_CURVES
  #ifdef HMI_CONFIG_CURVE_CFG
EventNodeCfgGraphVisu.Init(NodeCfgGraphVisu, NodeCfgGraphVisu,
                           &Controller::MoveUpNodeCfgGraphVisu,
									&Controller::MoveDownNodeCfgGraphVisu,
                           &Controller::MoveTimeOutNodeCfgGraphVisu,
                           &Controller::MoveToModifNodeCfgGraphVisu,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeCfgGraphBackPref,
                           NodeCfgGraphPMax,
									NodePrefCurveConfig,
                           NodeModifCfgGraphVisu,
									NodeCfgGraphVisu,
                           NodeCfgGraphVisu);

EventNodeModifCfgGraphVisu.Init(NodeModifCfgGraphVisu, NodeModifCfgGraphVisu,
                           &Controller::ModifyUpNodeCfgGraphVisu,
									&Controller::ModifyDownNodeCfgGraphVisu,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNodeCfgGraphVisuVisu,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu);

EventNodeCfgGraphPMax.Init(NodeCfgGraphPMax, NodeCfgGraphPMax,
                           &Controller::MoveUpNodeCfgGraphVisu,
									&Controller::MoveDownNodeCfgGraphVisu,
                           &Controller::MoveTimeOutNodeCfgGraphVisu,
                           &Controller::MoveToModifNodeCfgGraphVisu,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeCfgGraphVisu,
                           NodeCfgGraphQMax,
                           NodePrefCurveConfig,
                           NodeModifCfgGraphPMax,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu);

EventNodeModifCfgGraphPMax.Init(NodeModifCfgGraphPMax, NodeModifCfgGraphPMax,
                           &Controller::ModifyUpNodeCfgGraphVisu,
									&Controller::ModifyDownNodeCfgGraphVisu,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNodeCfgGraphVisu,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu,
                           NodeCfgGraphPMax,
                           NodeCfgGraphPMax,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu);

EventNodeCfgGraphQMax.Init(NodeCfgGraphQMax, NodeCfgGraphQMax,
                           &Controller::MoveUpNodeCfgGraphVisu,
									&Controller::MoveDownNodeCfgGraphVisu,
									&Controller::MoveTimeOutNodeCfgGraphVisu,
                           &Controller::MoveToModifNodeCfgGraphVisu,
									&Controller::NoAction,
                           &Controller::NoAction,
                           NodeCfgGraphPMax,
                           NodeCfgGraphVtMax,
                           NodePrefCurveConfig,
                           NodeModifCfgGraphQMax,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu);

EventNodeModifCfgGraphQMax.Init(NodeModifCfgGraphQMax, NodeModifCfgGraphQMax,
                           &Controller::ModifyUpNodeCfgGraphVisu,
									&Controller::ModifyDownNodeCfgGraphVisu,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNodeCfgGraphVisu,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu,
                           NodeCfgGraphQMax,
                           NodeCfgGraphQMax,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu);

EventNodeCfgGraphVtMax.Init(NodeCfgGraphVtMax, NodeCfgGraphVtMax,
                           &Controller::MoveUpNodeCfgGraphVisu,
									&Controller::MoveDownNodeCfgGraphVisu,
                           &Controller::MoveTimeOutNodeCfgGraphVisu,
                           &Controller::MoveToModifNodeCfgGraphVisu,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeCfgGraphQMax,
                           NodeCfgGraphTMax,
                           NodePrefCurveConfig,
                           NodeModifCfgGraphVtMax,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu);

EventNodeModifCfgGraphVtMax.Init(NodeModifCfgGraphVtMax, NodeModifCfgGraphVtMax,
                           &Controller::ModifyUpNodeCfgGraphVisu,
									&Controller::ModifyDownNodeCfgGraphVisu,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNodeCfgGraphVisu,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVtMax,
									NodeCfgGraphVtMax,
                           NodeCfgGraphVisu,
									NodeCfgGraphVisu);

EventNodeCfgGraphTMax.Init(NodeCfgGraphTMax, NodeCfgGraphTMax,
                           &Controller::MoveUpNodeCfgGraphVisu,
									&Controller::MoveDownNodeCfgGraphVisu,
                           &Controller::MoveTimeOutNodeCfgGraphVisu,
                           &Controller::MoveToModifNodeCfgGraphVisu,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeCfgGraphVtMax,
                           NodeCfgGraphRepresent,
                           NodePrefCurveConfig,
                           NodeModifCfgGraphTMax,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu);

EventNodeModifCfgGraphTMax.Init(NodeModifCfgGraphTMax, NodeModifCfgGraphTMax,
                           &Controller::ModifyUpNodeCfgGraphVisu,
									&Controller::ModifyDownNodeCfgGraphVisu,
                           &Controller::ReturnToNodeTO,
                           &Controller::ReturnToNodeCfgGraphVisu,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu,
                           NodeCfgGraphTMax,
                           NodeCfgGraphTMax,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu);

EventNodeCfgGraphRepresent.Init(NodeCfgGraphRepresent, NodeCfgGraphRepresent,
                           &Controller::MoveUpNodeCfgGraphVisu,
									&Controller::MoveDownNodeCfgGraphVisu,
                           &Controller::MoveTimeOutNodeCfgGraphVisu,
                           &Controller::MoveToModifNodeCfgGraphVisu,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeCfgGraphTMax,
                           NodeCfgGraphBackPref,
                           NodePrefCurveConfig,
                           NodeModifCfgGraphRepresent,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu);

EventNodeModifCfgGraphRepresent.Init(NodeModifCfgGraphRepresent, NodeModifCfgGraphRepresent,
                           &Controller::ModifyUpNodeCfgGraphVisu,
									&Controller::ModifyDownNodeCfgGraphVisu,
                           &Controller::ReturnToNodeTO,
									&Controller::ReturnToNodeCfgGraphVisu,
                           &Controller::NoAction,
									&Controller::NoAction,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu,
                           NodeCfgGraphRepresent,
                           NodeCfgGraphRepresent,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu);

EventNodeCfgGraphBackPref.Init(NodeCfgGraphBackPref, NodeCfgGraphBackPref,
                           &Controller::MoveUpNodeCfgGraphVisu,
									&Controller::MoveDownNodeCfgGraphVisu,
                           &Controller::MoveTimeOutNodeCfgGraphVisu,
                           &Controller::MoveValidNodeCfgGraphBackPref,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           NodeCfgGraphRepresent,
                           NodeCfgGraphVisu,
                           NodePrefCurveConfig,
                           NodePrefCurveConfig,
                           NodeCfgGraphVisu,
                           NodeCfgGraphVisu);
  #endif
#endif                           

/*--- Noeud menu batterie-----------------------------------------------------*/

EventNodeBatteryBackToMaint.Init(NodeBatteryBackToMaint, NodeBatteryBackToMaint,
                           &Controller::NoAction,
									&Controller::NoAction,
									&Controller::NoAction,
									&Controller::MoveValid,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeFree,
									NodeFree,
									NodeFree,
									NodeSupplyBatteryMenu,
									NodeFree,
									NodeFree);

/*--- Noeud menu USB-----------------------------------------------------*/

EventNodeUsbGhost.Init(NodeUsbGhost,   NodeUsbGhost,
                           &Controller::NoAction,
									&Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::NoAction,
                           &Controller::MoveMonitor,
                           &Controller::NoAction,
						   NodeUsbContRecord,
						   NodeUsbContRecord,
						   NodeUsbContRecord,
                           NodeUsbContRecord,
                           cVentilStartNode,
									NodeFree);



EventNodeUsbContRecord.Init(NodeUsbContRecord, NodeUsbContRecord,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::MoveTimeOutUSB,
									&Controller::MoveToModifNode,
									&Controller::MoveMonitor,
									&Controller::NoAction,
									NodeUsbEraseKey,
									NodeUsbTransferTrend,
									NodeVentil,
									NodeModifUsbContRecord,
									cVentilStartNode,
									NodeFree);

EventNodeModifUsbContRecord.Init(NodeModifUsbContRecord, NodeModifUsbContRecord,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
									&Controller::ReturnToNodeTO,
									&Controller::ReturnToNodeUsb,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeModifUsbContRecord,
									NodeModifUsbContRecord,
									NodeUsbContRecord,
									NodeUsbContRecord,
									NodeFree,
									NodeFree);


EventNodeUsbTransferTrend.Init(NodeUsbTransferTrend, NodeUsbTransferTrend,
						   &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::MoveTimeOutUSB,
									&Controller::MoveToModifNode,
									&Controller::MoveMonitor,
									&Controller::NoAction,
									NodeUsbContRecord,
									NodeUsbEraseKey,
									NodeVentil,
									NodeModifUsbTransferTrend,
									cVentilStartNode,
									NodeFree);

EventNodeModifUsbTransferTrend.Init(NodeModifUsbTransferTrend, NodeModifUsbTransferTrend,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
									&Controller::ReturnToNodeTO,
									&Controller::ReturnToNodeUsb,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeModifUsbTransferTrend,
									NodeModifUsbTransferTrend,
									NodeUsbTransferTrend,
									NodeUsbTransferTrend,
									NodeFree,
									NodeFree);

EventNodeUsbEraseKey.Init(NodeUsbEraseKey, NodeUsbEraseKey,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::MoveTimeOutUSB,
									&Controller::MoveToModifNode,
									&Controller::MoveMonitor,
									&Controller::NoAction,
									NodeUsbTransferTrend,
									NodeUsbContRecord,
									NodeVentil,
									NodeModifUsbEraseKey,
									cVentilStartNode,
									NodeFree);

EventNodeModifUsbEraseKey.Init(NodeModifUsbEraseKey, NodeModifUsbEraseKey,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
									&Controller::ReturnToNodeUsbTO,
									&Controller::ReturnToNodeUsb,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeModifUsbEraseKey,
									NodeModifUsbEraseKey,
									NodeUsbEraseKey,
									NodeUsbEraseKey,
									NodeFree,
									NodeFree);


#ifdef HMI_CONFIG_USB_SETTINGS_TRANSFER
EventNodeUsbTransferSetOn.Init(NodeUsbTransferSetOn, NodeUsbTransferSetOn,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::MoveTimeOutUSB,
									&Controller::MoveToModifNode,
									&Controller::MoveMonitor,
									&Controller::NoAction,
									NodeUsbEraseKey,
									NodeUsbContRecord,
									NodeVentil,
									NodeModifUsbTransferSetOn,
									cVentilStartNode,
									NodeFree);

EventNodeModifUsbTransferSetOn.Init(NodeModifUsbTransferSetOn, NodeModifUsbTransferSetOn,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
									&Controller::ReturnToNodeUsbTO,
									&Controller::MoveToNextModifNodeUsbTransferSetOn,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeModifUsbTransferSetOn,
									NodeModifUsbTransferSetOn,
									NodeUsbTransferSetOn,
									NodeUsbApplySet,
									NodeFree,
									NodeFree);

EventNodeUsbApplySet.Init(NodeUsbApplySet, NodeUsbApplySet,
						   &Controller::ModifyUp,
						   &Controller::ModifyDown,
									&Controller::ReturnToNodeUsbTO,
									&Controller::ReturnToNodeUsb,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeUsbApplySet,
									NodeUsbApplySet,
									NodeUsbTransferSetOn,
									NodeUsbTransferSetOn,
									cVentilStartNode,
									NodeFree);
#endif

#ifdef HMI_CONFIG_USB_MONIT_TRANSFER
EventNodeUsbTransferMonit.Init(NodeUsbTransferMonit, NodeUsbTransferMonit,
						   &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::MoveTimeOutUSB,
									&Controller::MoveToModifNode,
									&Controller::MoveMonitor,
									&Controller::NoAction,
									NodeUsbContRecord,
									NodeUsbTransferTrend,
									NodeVentil,
									NodeModifUsbTransferMonit,
									cVentilStartNode,
									NodeFree);

EventNodeModifUsbTransferMonit.Init(NodeModifUsbTransferMonit, NodeModifUsbTransferMonit,
						   &Controller::ModifyUp,
									&Controller::ModifyDown,
									&Controller::ReturnToNodeTO,
									&Controller::ReturnToNodeUsb,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeModifUsbTransferMonit,
									NodeModifUsbTransferMonit,
									NodeUsbTransferMonit,
									NodeUsbTransferMonit,
									NodeFree,
									NodeFree);
#endif
									
#ifdef HMI_CONFIG_USB_EVENTS_TRANSFER
EventNodeUsbTransferEvents.Init(NodeUsbTransferEvents, NodeUsbTransferEvents,
                           &Controller::MoveUp,
									&Controller::MoveDown,
									&Controller::MoveTimeOutUSB,
									&Controller::MoveToModifNode,
									&Controller::MoveMonitor,
									&Controller::NoAction,
									NodeUsbTransferTrend,
									NodeUsbEraseKey,
									NodeVentil,
									NodeModifUsbTransferEvents,
									cVentilStartNode,
									NodeFree);

EventNodeModifUsbTransferEvents.Init(NodeModifUsbTransferEvents, NodeModifUsbTransferEvents,
                           &Controller::ModifyUp,
									&Controller::ModifyDown,
									&Controller::ReturnToNodeTO,
									&Controller::ReturnToNodeUsb,
									&Controller::NoAction,
									&Controller::NoAction,
									NodeModifUsbTransferEvents,
									NodeModifUsbTransferEvents,
									NodeUsbTransferEvents,
									NodeUsbTransferEvents,
									NodeFree,
									NodeFree);
#endif

EventNodeUsbStop.Init(NodeUsbStop, NodeUsbStop,
                           &Controller::NoAction,
									&Controller::NoAction,
									&Controller::MoveTimeOutUSB,
									&Controller::ValidUsbStop,
									&Controller::MoveMonitor,
									&Controller::NoAction,
									NodeUsbContRecord,
									NodeUsbEraseKey,
									NodeVentil,
									cVentilStartNode,
									cVentilStartNode,
									NodeFree);

/*--- Noeud menu Tendance-----------------------------------------------------*/

EventNodeTrendBack.Init(NodeTrendBack, NodeTrendBack,
                           &Controller::MoveUpNodeTrendBack,
									&Controller::MoveDownNodeTrendBack,
									&Controller::MoveTimeOutNodeTrendBack,
									&Controller::MoveValidNodeTrendBack,
									&Controller::MoveMonitor,
									&Controller::NoAction,
									NodeTrendBack,
									NodeTrendBack,
									NodePrefTrend,
									NodePrefTrend,
									NodeTrendBack,
									NodeTrendBack);

   /*%C Init de la table de configuration du display */
   InitInfoNodeDisplayTable();
}
