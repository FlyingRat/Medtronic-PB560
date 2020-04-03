/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Ventilation_Datas.h                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Description fonctionnelle:		 	                          */
/*                                                                      	   */
/*%C Data declaration for ventilation functions                               */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/



#ifndef VENTILATION_DATAS_H
#define VENTILATION_DATAS_H

#include "enum.h"


/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
#define cPVALVE_MEASURE_NUMBER          	10
#define cFLEAK_MEASURE_NUMBER           	10
#define cPEP_MEASURE_NUMBER				 	10
#define cPERIOD_OF_VEN_COMPUTE_CALL		 	10UL

#define cVEN_COMMAND_QLEAK_DB_DEF  			9800UL
#define cVEN_COMMAND_QLEAK_SB_DEF  			10700UL
#define cVEN_COMMAND_VALVE_DEF  			2000UL
#define cPLATEAU_TABLES_LENGHT 				70
#define cSTABILITY_CONDITION_POS 			5		
#define cSTABILITY_CONDITION_NEG 			-5		

/******************************************************************************/
/*                            STRUCTURE DECLARATION							  */
/******************************************************************************/


typedef struct
	{
	  	UWORD16 TiValCount;
	  	UWORD16 TeValCount;
	} t_VEN_TiTeValueMesured;

typedef struct
	{
	SWORD32 CumulVti;
	SWORD32 CumulVte;
	SWORD32 CumulVteInsp;
	SWORD32 CumulVtiExh;
	SWORD16 PiMax;
	SWORD16 LpfPiMax;
	SWORD32 CumulPi;
	SWORD16 MesurePep[cPEP_MEASURE_NUMBER];
	SWORD16 MeasurePvalve[cPVALVE_MEASURE_NUMBER];
	SWORD16 MeasureFlowLeak[cFLEAK_MEASURE_NUMBER];
	SWORD32 CumulVtWob;
	SWORD16 PValveMax;
	SWORD32 CumulValveCurrent;
	} t_VEN_MeasuredValues;

typedef struct
	{
	UWORD16 EndType;
	UWORD16 TimerId;
	} t_VEN_SIMV_PS_End;

#ifdef DECLARATION_VENTILATION_DATAS

/******************************************************************************/
/*                           VARIABLE DECLARATION                    	      */
/******************************************************************************/
UWORD16 VEN_CptCumulValveCurrent = 0;
SWORD32 VEN_IntegralBlower = 0;
SWORD32 VEN_IntegralValve = 0;

e_VEN_ControllerType VEN_ControllerType = CONTROL_PRESSURE;

UWORD16 AdjustMode = PRES;
UWORD16 ChangeMode = FALSE;
UWORD16 VentilAuthorization = FALSE;
UWORD16 AdjustApnea = 0;

e_VEN_SIMVCycle VEN_SIMVCycle = CAV_Cycle;

/* Counters for Ti and Te computing															*/
t_VEN_TiTeValueMesured VEN_TiTeValueMesured = {1000, 1000};

/* P Max init = 10 à plus de 2 mbar (to avoid a null peep at the first exhalation) */
t_VEN_MeasuredValues VEN_MeasuredValues = {100,0,0,0,0,0,0,0,0,0};

e_VEN_Controller_Phase VEN_Controller_Phase = VEN_EXH_PLAT;

/* Parameter declaration for autoadaptation rise inspiration (Kp, Ki) */
SWORD32 VEN_PerCentRisePI = 0;
SWORD32 VEN_PerCentRiseQI = 0;

/* Rinse flow close loop command */
SWORD32 VEN_CommandFlow = 0;
SWORD32 VEN_TargetFlow = 0;
UWORD16 VEN_ValveCurrentSat = 0;
UWORD16 VEN_FlowNegSat = 0;

/* Leak measure */
double	VEN_LeakFlowFactorAverage = 0;
UWORD16 VEN_Qee_SampleSize= 0;
SWORD16 VEN_FleakMeasured = 0;
SWORD16 VEN_MemoFleakMeasured = 0;
double VEN_LeakVtiCorrection = 0;
double VEN_LeakVteCorrection = 0;

/* Auto adaptation measure */
SWORD16 VEN_ExhalFlowMaxMeasured = 0;
SWORD32 VEN_TempRiseOpenValve = 0;

// Variables pour l'analyse du signal
UWORD16 VEN_TRiseIncrem = FALSE;
UWORD16 VEN_TRiseDecrem = FALSE;
UWORD16 VEN_MutexSignal1 = FALSE;
UWORD16 VEN_MutexSignal2 = FALSE;
UWORD16 VEN_MutexSignal3 = FALSE;

/* Peep min measure declaration (initialiazed to 1000 => 100 cmH2O)           */
SWORD16 VEN_PeMin = 1000;
UWORD16 VEN_TRise_Rebond = 0;

/* Inspiratory flow measure (updated in flow control)                         */
SWORD16 VEN_Vti = 500;

/* Inspiratory rise pressure                          */
UWORD16 VEN_Rise_Pi_Set_Point = 150;

/* Measured peep                          */
SWORD16 VEN_PepMeasured = 0;

/* Inspiratory flow set point                          */
UWORD16 VEN_Qi_Set_Point = 200;

/* First cycle flag*/
UWORD16 VEN_FirstCycle = FALSE;
/* Second cycle flag*/
UWORD16 VEN_SecondCycle = FALSE;
/* Third cycle flag*/
UWORD16 VEN_ThirdCycle = FALSE;

/*%C unvoluntary Stop flag */ 
UWORD16 VEN_UnvolontaryStop = FALSE;

UWORD16 VEN_TeFall = 0;

UWORD16 VEN_PressureUpStep = cMIN_STEP;
UWORD16 VEN_PressureDownStep = cMIN_STEP;

// Pression maxi en inspiration
SWORD16 VEN_PMax = 100;

/*%C Start bip flag after an unvolontary stop */ 
UWORD16 VEN_StartBip = TRUE;

/*%C Sigh detection flag */ 
UWORD16 VEN_SighDetected = FALSE;

/*%C Autorization Regul O2 Flag */
UWORD16 VEN_AuthorizationRegulO2 = FALSE;
UWORD16 VEN_LaunchCalibO2 = FALSE;
SWORD32 VEN_IntegralValveO2 = 0;

UWORD16 VEN_TrigExpDetected = FALSE;
UWORD16 VEN_InitValve = FALSE;
UWORD16 VEN_CpapFirstCycle = FALSE;
/* Flow min declaration  */
SWORD32 VEN_MeasureQinspMin = 0;
/* Flow max declaration  */
SWORD32 VEN_MeasureQinspMax = 0;
/* Temporary flow min declaration  */
SWORD32 VEN_TemporaryMeasureQinspMin = 2000;
/* Temporary flow max declaration  */
SWORD32 VEN_TemporaryMeasureQinspMax = -300;
SWORD16 VEN_MutexReadjust = FALSE;

/* Flow Cumul in Cpap mode                                                    */
SWORD32 VEN_CumulVtiCpap = 0;
/* Flow cumul counter                                                     */
UWORD16 VEN_CumulFlowCounter = 0;


SWORD32 VEN_PreviousAverageFlow = 5;
SWORD32 VEN_PreviousMeasureQinsp = 0;
UWORD16 VEN_PtrMesureFlowPress = 0;
UWORD16 VEN_PtrLeakFlowFactor = 0;
UWORD16 VEN_LeakFactorCptValues = 0;

UWORD16 VEN_Mutex_High_Pressure = FALSE;
UWORD16 VEN_MutexTimerReadjust = FALSE;

UWORD16 VEN_SIMV_Cycle_History[6];
t_VEN_SIMV_PS_End VEN_SIMV_PS_End[6]= {	{0, VEN_END_COUNT0},
										{0, VEN_END_COUNT1},
										{0, VEN_END_COUNT2},
										{0, VEN_END_COUNT3},
										{0, VEN_END_COUNT4},
										{0, VEN_END_COUNT5} };
SWORD32 VEN_MesureFlowQinsp[cPLATEAU_TABLES_LENGHT];
SWORD32 VEN_MesureFlowQexh[cPLATEAU_TABLES_LENGHT];
SWORD32 VEN_MesurePressure[cPLATEAU_TABLES_LENGHT];

UWORD16 VEN_Disconnexion_Flag = FALSE;

UWORD16 VEN_VentilationStart = FALSE;
UWORD16 VEN_MutexVanneO2 = FALSE;
UWORD16 VEN_Synchro_Reset_Alarms = FALSE;

// Store the low pressure limit of the circuit disconnect.
SWORD32 VEN_CircuitDisconnectLowPressLimit = 0;

// Used for detecting patient effort
UWORD16 VEN_NegativeFlowCounter = 0;
UWORD16 VEN_DetectedNegativeFlow = FALSE;
const UWORD16 MAX_NEGATIVE_FLOW_COUNTER = 5;  // this represents 50 ms

// Used for SEC_CheckValve to ensure that the VTI EXH data has been updated.
UWORD16 VEN_IsVtiExhUpdated = FALSE;

#else

/******************************************************************************/
/*                       EXTERNAL VARIABLE DECLARATION                    	  */
/******************************************************************************/
extern UWORD16 VEN_CptCumulValveCurrent;
extern SWORD32 VEN_IntegralBlower;
extern SWORD32 VEN_IntegralValve ;

extern e_VEN_SIMVCycle VEN_SIMVCycle;	     

extern UWORD16 AdjustMode;
extern UWORD16 ChangeMode;
extern UWORD16 VentilAuthorization;
extern UWORD16 AdjustApnea;


// Durée de la chute en expiration du cycle en cours
extern UWORD16 VEN_TeFall;

// Phase de régulation courante
extern e_VEN_Controller_Phase VEN_Controller_Phase;

// Consignes de régulation
//extern t_VEN_CmpCons VEN_CmpCons;
extern UWORD16 VEN_PressureUpStep;
extern UWORD16 VEN_PressureDownStep;

// Pression maxi en inspiration
extern SWORD16 VEN_PMax;

// Commande de boucle ouverte du débit de rinçage
extern SWORD32 VEN_CommandFlow;
extern SWORD32 VEN_TargetFlow;
extern UWORD16 VEN_ValveCurrentSat;
extern UWORD16 VEN_FlowNegSat;

// Variable pour l'execution d'une régul de valve pour précharger la boucle fermée
//extern BIT VEN_RegulValve;

/* Parameter declaration for autoadaptation rise inspiration (Kp, Ki) */
extern SWORD32 VEN_PerCentRisePI;
extern SWORD32 VEN_PerCentRiseQI;

// Type de démarrage d'inspiration
//extern e_VEN_InspDetectType VEN_InspDetectType; 
// Fréquence mesurée sur la base du cycle de ventilation précédent
//extern UWORD16 VEN_CurrentFreq;
// Valeurs mesurées (CumulVti, CumulVte, PiMax, MesurePep, MeasurePvalve)
extern t_VEN_MeasuredValues VEN_MeasuredValues;

// Type de régulation à générer (pression ou débit)
extern e_VEN_ControllerType VEN_ControllerType;

// Etat de ventilation du mode actif
//extern t_VEN_ActiveModeState VEN_ActiveModeState;

extern t_VEN_TiTeValueMesured VEN_TiTeValueMesured;

/* Leak measure */
extern double VEN_LeakFlowFactorAverage;
extern UWORD16 VEN_Qee_SampleSize;
extern SWORD16 VEN_FleakMeasured;
extern SWORD16 VEN_MemoFleakMeasured;
extern double VEN_LeakVtiCorrection;
extern double VEN_LeakVteCorrection;

/* Auto adaptation measure */
extern SWORD16 VEN_MeasuredLastPExh;
extern SWORD16 VEN_ExhalFlowMaxMeasured;
extern SWORD32 VEN_TempRiseOpenValve;

/* Signal analysis variable */
extern UWORD16 VEN_TRiseIncrem ;
extern UWORD16 VEN_TRiseDecrem ;
extern UWORD16 VEN_MutexSignal1;
extern UWORD16 VEN_MutexSignal2 ;
extern UWORD16 VEN_MutexSignal3 ;

/* Peep min measure declaration (initialiazed to 1000 => 100 cmH2O)          */
extern SWORD16 VEN_PeMin ;
extern UWORD16 VEN_TRise_Rebond;

/* Inspiratory flow measure (updated in flow control)                         */
extern SWORD16 VEN_Vti ;

/* Inspiratory rise pressure                          */
extern UWORD16 VEN_Rise_Pi_Set_Point;

/* Measured peep        */
extern SWORD16 VEN_PepMeasured;

/* Inspiratory flow set point  */
extern UWORD16 VEN_Qi_Set_Point;

/* First cycle flag*/
extern UWORD16 VEN_FirstCycle;
/* Second cycle flag*/
extern UWORD16 VEN_SecondCycle;
/* Third cycle flag*/
extern UWORD16 VEN_ThirdCycle;

/*%C unvoluntary Stop flag */ 
extern UWORD16 VEN_UnvolontaryStop ;

/*%C Start bip flag after an unvolontary stop */ 
extern UWORD16 VEN_StartBip;

/*%C Sigh detection flag */ 
extern UWORD16 VEN_SighDetected;

/*%C Autorization Regul O2 Flag */
extern UWORD16 VEN_AuthorizationRegulO2;
extern UWORD16 VEN_LaunchCalibO2;
extern SWORD32 VEN_IntegralValveO2;

extern UWORD16 VEN_TrigExpDetected;
extern UWORD16 VEN_InitValve;
extern UWORD16 VEN_CpapFirstCycle;
extern SWORD32 VEN_MeasureQinspMin;
extern SWORD32 VEN_MeasureQinspMax;
extern SWORD32 VEN_TemporaryMeasureQinspMin;
extern SWORD32 VEN_TemporaryMeasureQinspMax;
extern SWORD16 VEN_MutexReadjust;

/* Flow Cumul in Cpap mode                                                    */
extern SWORD32 VEN_CumulVtiCpap;
/* Flow cumul counter                                                     */
extern UWORD16 VEN_CumulFlowCounter;

extern SWORD32 VEN_PreviousAverageFlow;
extern SWORD32 VEN_PreviousMeasureQinsp;
extern UWORD16 VEN_PtrMesureFlowPress;
extern UWORD16 VEN_PtrLeakFlowFactor;
extern UWORD16 VEN_LeakFactorCptValues;

extern UWORD16 VEN_MutexTimerReadjust;
extern UWORD16 VEN_Mutex_High_Pressure;

extern UWORD16 VEN_SIMV_Cycle_History[6];
extern t_VEN_SIMV_PS_End VEN_SIMV_PS_End[6];
extern SWORD32 VEN_MesureFlowQinsp[cPLATEAU_TABLES_LENGHT];
extern SWORD32 VEN_MesureFlowQexh[cPLATEAU_TABLES_LENGHT];
extern SWORD32 VEN_MesurePressure[cPLATEAU_TABLES_LENGHT];


extern UWORD16 VEN_Disconnexion_Flag;

extern UWORD16 VEN_VentilationStart;

extern UWORD16 VEN_MutexVanneO2;

extern UWORD16 VEN_Synchro_Reset_Alarms;

// Store the low pressure limit of the circuit disconnect.
extern SWORD32 VEN_CircuitDisconnectLowPressLimit;

// Used for detecting patient effort
extern UWORD16 VEN_DetectedNegativeFlow;
extern UWORD16 VEN_NegativeFlowCounter;
extern const UWORD16 MAX_NEGATIVE_FLOW_COUNTER;

// Used for SEC_CheckValve to ensure that the VTI EXH data has been updated.
extern UWORD16 VEN_IsVtiExhUpdated;

#endif
#endif



