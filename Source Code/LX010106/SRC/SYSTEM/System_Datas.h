/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : System_Datas.h                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Global variables of "SYSTEM"                          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*                                                                            */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                           DEFINE  DECLARATION    	                		  */
/******************************************************************************/
#define SEGMENT0 0
#define SEGMENT1 1
#define SEGMENT2 2
#define SEGMENT3 3 
#define SEGMENT4 4 
#define SEGMENT5 5 
#define SEGMENT6 6 
#define SEGMENT7 7
#define FLOW_CALIB_POINTS_NUMBER 8
#define FLOW_CALIB_POINTS_NUMBER_4_PEDIATRIC_EXHAL 7
#define FLOW_CALIB_POINTS_NUMBER_NEGATIVE 		3
#define FLOW_O2_CALIB_POINTS_NUMBER  5
#define PWM_FAS_VALVE_CALIB_POINTS_NUMBER  3
#define VALVE_FAS_PRESS_CALIB_POINTS_NUMBER	7


/* Nombre de points de calibration pour la pression */
#define VALVE_PRESSURE_CALIB_POINTS_NUMBER 	1
#define PATIENT_PRESSURE_CALIB_POINTS_NUMBER 	2

/* Nombre de points de calibration pour la FiO2 */
#define FIO2_CALIB_POINTS_NUMBER   1

/* Nombre de points de calibration pour le débit O2 */
#define FLOW_O2_CALIB_POINTS_NUMBER  5

/* Nombre de points de calibration pour la Pression O2 */
#define O2_PRESSURE_CALIB_POINTS_NUMBER 	1

#define CT_BODY_TEMP 1054

#ifdef DECLARATION_SYSTEM_DATAS
#ifndef SYSTEM_DATAS_H
#define SYSTEM_DATAS_H

/************************************************************************/
/*                       STRUCTURE DECLARATION                     		*/
/************************************************************************/

typedef struct
{
	e_BOOL pulse;
	e_BOOL AutoRepeatSelected;
	e_BOOL AutoRepeatPush;
	e_BOOL level;
	e_BOOL EventLongPush;
	e_BOOL MutexLongPush;
	e_BOOL MutexAutoRepeatPush;
	e_BOOL flag;
	UWORD16 TimerLongPush;
	e_BOOL autorization;
	UWORD16 PulseTime;
	UWORD16 debounceDetected;
	UWORD16 debounceCanceled;
} t_SYS_Keyboard;

typedef struct
	{
 		UBYTE CalibPointsNumber;
 		e_VEN_ControllerType RegulationType;
 		UWORD16 *CalibPoint;
 		UWORD16 FirstOffsetIndex;
		UWORD16 OffsetAlarmIndex;
		UWORD16 EventCalibration;
	} t_SYS_CalibrationParameters;


/************************************************************************/
/*                       CONSTANT DECLARATION                     	*/
/************************************************************************/
const UWORD16 PATIENT_PRESSURE_CALIB_POINTS[8] = {0,40,0,0,0,0,0,0};
// Valeurs des points de calibration des capteurs de débit
const UWORD16 FLOW_CALIB_POINTS[8] = {0,5,12,20,37,60,90,130};

const UWORD16 VALVE_PRESSURE_CALIB_POINTS[8] = {0,0,0,0,0,0,0,0}; 

const UWORD16 VALVE_FAS_PWM_CALIB_POINTS[PWM_FAS_VALVE_CALIB_POINTS_NUMBER] = {0, 2672, 2672};
const UWORD16 VALVE_FAS_PRESS_CALIB_POINTS[VALVE_FAS_PRESS_CALIB_POINTS_NUMBER] = {50, 100, 150, 200, 250, 300, 350};

// Valeurs des points de calibration des capteurs de FiO2
const UWORD16 FIO2_CALIB_POINTS[8] = {21,0,0,0,0,0,0,0};

// Valeurs des points de calibration des capteurs de Débit O2
const UWORD16 FLOW_O2_CALIB_POINTS[8] = {0,5,20,40,50,0,0,0};

// Valeurs des points de calibration des capteurs de Pression O2
const UWORD16 O2_PRESSURE_CALIB_POINTS[8] = {0,0,0,0,0,0,0,0};

// Paramètres pour la calibration
const t_SYS_CalibrationParameters CalibrationParameters[end_of_sys_calib] = {

{PATIENT_PRESSURE_CALIB_POINTS_NUMBER,
 CONTROL_PRESSURE_MAINT,
 (UWORD16*)PATIENT_PRESSURE_CALIB_POINTS,
 OFFSET_PATIENT_PRESS_1_U16,
 TECH_ALARM_INTERNAL_PRESSURE_OFFSET_DEFAULT_U16,
 EVENT_PATIENT_PRESS_CALIB},
 	 	
{VALVE_PRESSURE_CALIB_POINTS_NUMBER,
 CONTROL_PRESSURE_VALVE,
 (UWORD16*)VALVE_PRESSURE_CALIB_POINTS, 
 OFFSET_VALVE_PRESS_U16, 
 TECH_ALARM_VALVE_PRESS_OFFSET_DEFAULT_U16,
 EVENT_VALVE_PRESS_CALIB},	
  	
{FLOW_CALIB_POINTS_NUMBER,	
 CONTROL_FLOW,	
 (UWORD16*)FLOW_CALIB_POINTS,	
 OFFSET_INSP_FLOW_1_U16, 
 TECH_ALARM_INSP_FLOW_OFFSET_DEFAULT_U16,
 EVENT_INSP_FLOW_CALIB},	 	

{FLOW_CALIB_POINTS_NUMBER,	
 CONTROL_FLOW,	
 (UWORD16*)FLOW_CALIB_POINTS,	
 OFFSET_EXH_FLOW_1_U16,	
 TECH_ALARM_EXHAL_FLOW_OFFSET_DEFAULT_U16,
 EVENT_EXH_FLOW_CALIB},

{FLOW_CALIB_POINTS_NUMBER,	
 CONTROL_FLOW_EXH,
 (UWORD16*)FLOW_CALIB_POINTS,
 OFFSET_EXH_FLOW_1_U16,
 TECH_ALARM_EXHAL_FLOW_OFFSET_DEFAULT_U16,
 EVENT_FIO2_CALIB},

{FIO2_CALIB_POINTS_NUMBER,
 NO_CONTROL,
 (UWORD16*)FIO2_CALIB_POINTS,
 OFFSET_FIO2,
 TECH_ALARM_FIO2_OFFSET_DEFAULT,
 EVENT_FIO2_CALIB},

{FLOW_O2_CALIB_POINTS_NUMBER,
 CONTROL_FLOW_O2,
 (UWORD16*)FLOW_O2_CALIB_POINTS,
 OFFSET_O2_FLOW_1,
 TECH_ALARM_OFFSET_O2_FLOW,
 EVENT_O2_FLOW_CALIB},
 	 	
{O2_PRESSURE_CALIB_POINTS_NUMBER,
 CONTROL_PRESSURE_O2,
 (UWORD16*)O2_PRESSURE_CALIB_POINTS,
 OFFSET_PRESS_O2,
 TECH_ALARM_O2_PRESSURE_OFFSET_DEFAULT,
 EVENT_O2_PRESS_CALIB}	 	
 
};


/************************************************************************/
/*                       VARIABLE DECLARATION                     		*/
/************************************************************************/

	t_SYS_Keyboard SYS_Num_Keyboard[Number_of_key];
	e_BOOL SYS_MutexStartStopVentilUP = FALSE;
	e_BOOL SYS_MutexStopInfoVentil = FALSE;
	e_BOOL SYS_WaitingForStopConfirm = FALSE;

	UWORD16	SYS_CounterPatientMin = 0;
	UWORD16	SYS_CounterPatientHour = 0;
	UWORD16	SYS_CounterMachineMin = 0;
	UWORD16	SYS_CounterMachineHour = 0;

	volatile UBYTE DataFrameUART1[SIZE_FRAME_UART1]; //Trame de reception

	e_BOOL SYS_CalibProcessing = FALSE;
	
#endif

#else
#ifndef SYSTEM_DATAS_H
#define SYSTEM_DATAS_H

/************************************************************************/
/*                       STRUCTURE DECLARATION                     		*/
/************************************************************************/

typedef struct
{
	e_BOOL pulse;
	e_BOOL AutoRepeatSelected;
	e_BOOL AutoRepeatPush;
	e_BOOL level;
	e_BOOL EventLongPush;
	e_BOOL MutexLongPush;
	e_BOOL MutexAutoRepeatPush;
	e_BOOL flag;
	UWORD16 TimerLongPush;
	e_BOOL autorization;
	UWORD16 PulseTime;
	UWORD16 debounceDetected;
	UWORD16 debounceCanceled;
} t_SYS_Keyboard;

typedef struct
	{
 		UBYTE CalibPointsNumber;
 		e_VEN_ControllerType RegulationType;
 		UWORD16 *CalibPoint;
 		UWORD16 FirstOffsetIndex;
		UWORD16 OffsetAlarmIndex;
		UWORD16 EventCalibration;
	} t_SYS_CalibrationParameters;

/************************************************************************/
/*                   EXTERNAL VARIABLE DECLARATION                     	*/
/************************************************************************/

extern t_SYS_Keyboard SYS_Num_Keyboard[Number_of_key];
extern e_BOOL SYS_MutexStartStopVentilUP;
extern e_BOOL SYS_MutexStopInfoVentil;
extern e_BOOL SYS_WaitingForStopConfirm;

extern UWORD16 SYS_CounterPatientMin;
extern UWORD16 SYS_CounterPatientHour;
extern UWORD16 SYS_CounterMachineMin;
extern UWORD16 SYS_CounterMachineHour;
extern volatile UBYTE DataFrameUART1[SIZE_FRAME_UART1]; //Trame de reception

extern e_BOOL SYS_CalibProcessing;

 
/************************************************************************/
/*                   EXTERNAL CONSTANT DECLARATION                     	*/
/************************************************************************/
extern const UWORD16 PATIENT_PRESSURE_CALIB_POINTS[8];
// Valeurs des points de calibration des capteurs de débit
extern const UWORD16 FLOW_CALIB_POINTS[8];

extern const UWORD16 VALVE_PRESSURE_CALIB_POINTS[8]; 

extern const UWORD16 VALVE_FAS_PRESS_CALIB_POINTS[VALVE_FAS_PRESS_CALIB_POINTS_NUMBER];
extern const UWORD16 VALVE_FAS_PWM_CALIB_POINTS[PWM_FAS_VALVE_CALIB_POINTS_NUMBER];
// Valeurs des points de calibration des capteurs de FiO2
extern const UWORD16 FIO2_CALIB_POINTS[8];

// Valeurs des points de calibration des capteurs de Débit O2
extern const UWORD16 FLOW_O2_CALIB_POINTS[8];

// Valeurs des points de calibration des capteurs de Pression O2
extern const UWORD16 O2_PRESSURE_CALIB_POINTS[8];


// Paramètres pour la calibration
extern const t_SYS_CalibrationParameters 
													CalibrationParameters[end_of_sys_calib];

#endif
#endif

