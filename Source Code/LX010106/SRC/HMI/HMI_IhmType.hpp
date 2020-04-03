/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_IhmType.hpp	 		  		                             	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_IhmType.cpp  		      	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef IhmTypeH
#define IhmTypeH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/
extern "C"
{
#include "typedef.h"
}


/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
/* Attention le numéro de frame doit être toujours pair car le bit0 est réservé */
/* Beware the frame number must be always even because bit0 is reserved */
#define FRAME_WELCOME         2	// Frame Welcome
#define FRAME_VENTILATION     4	// Frame Ventilation
#define FRAME_ALARME          6	// Frame Alarme
#define FRAME_HISTO_ALARME    8	// Frame Histo Alarme
#define FRAME_CONFIGURATION   10	// Frame Configuration
#define FRAME_PREFERENCE      12  // Frame Preference
#define FRAME_MAINTENANCE     14 	// Frame Maintenance
#define FRAME_HISTO_ANOMALIE  16  // Frame Histo Anomalie
#define FRAME_VOLTAGE_CHECK   18  // Frame Voltage Check
#define FRAME_GRAPH           20  // Frame Graph
#define FRAME_CONFIG_GRAPH    22  // Frame Config Graph
#define FRAME_BATTERIE        24  // Frame menu batterie
#define FRAME_USB             26  // Frame menu USB
#define FRAME_TENDANCE        28  // Frame menu Tendance
#define FRAME_CIRCUIT_CHECK   30  // Frame menu Circuit Check
#define FRAME_CONFIGURATION1  32  // Frame Configuration 1
#define FRAME_NONE            34  // Frame Nulle


#define VIDEO_PAGE1  1
#define VIDEO_PAGE2  2
#define VIRTUAL_PAGE 3

#define FONT_1 1	//ARIAL 9
#define FONT_2 2	//ARIAL 8
#define FONT_3 3	//ARIAL FREE
#define FONT_4 4	//ARIAL BLACK 11
#define FONT_5 5	//ARIAL BOLD 29

#define NO_ID 999

#define HORI 0
#define VERT 1

#define VENTIL_FIRST_NODE_LINE		40
#define VENTIL_NODE_SPACING			19
#define ALARM_FIRST_NODE_LINE		   75
#define ALARM_NODE_SPACING			   40
#define ALARM_FIRST_NODE_LINE_PSVT	   74
#define ALARM_NODE_SPACING_PSVT		   32
#define ALARM_FIRST_NODE_LINE_VSIMV	   74
#define ALARM_NODE_SPACING_VSIMV		   32
#define ALARM_FIRST_NODE_LINE_VOL	   78
#define ALARM_NODE_SPACING_VOL		   40

typedef struct
{
   UWORD16 evenement;
	UWORD16 day;
	UWORD16 month;
	UWORD16 year;
	UWORD16 hour;
	UWORD16 min;
	UWORD16 cpt;
} FlashEvent;

typedef enum
{
   LED_ALARM_RED,
   LED_ALARM_ORANGE,
   LED_VENTIL,
   LED_WHITE,
   LED_AC,
   LED_DC,
    LED_BAT
} e_TYPE_OF_LED;

typedef struct
{
    UWORD16 id;
    UWORD16 action;
    e_BOOL logtolast;
	UWORD16 day;
	UWORD16 month;
	UWORD16 year;
	UWORD16 hour;
	UWORD16 min;
} AlarmEvent;

#define NB_ANOMALI_DISPLAY    				9
#define NB_ALARME_DISPLAY     				8

#define TIME_HISTO_ALARM_SEEK	   			20
#define TIME_HISTO_ANO_SEEK					20
#define TIME_REFRESH					         160
#define TIME_WAIT_CALIB_VERIF			   	100
#define TIME_SPY_PARAM					   	300
#define TIME_ADD_TO_BLINK_EVENT		   	400
#define TIME_REFRESH_ALARM				   	800
#define TIME_BLINK_EVENT				   	400
#define TIME_HIDE_ALARM_MESSAGE		   	800
#define TIME_HIDE_STOP_VENT_MESS		   	1000
#define TIME_HIDE_LOUPE					   	1000
#define TIME_AUTO_CALIB_TEST			   	1000
#define TIME_SWAP_ALARM					   	1500
#define TIME_TRIGGER_OK					   	2000
#define TIME_WAIT_FIO2_DETECT             2000
#define TIME_WELCOME_EVENT				   	7000
#define TIME_OUT_MODIF_EVENT			   	7000
#define TIME_QUIT_HISTO_ALARME		   	30000
#define TIME_QUIT_PREFERENCES		   		14000
#define TIME_QUIT_VENTIL_REPORT 	   	   300000
#define TIME_QUIT_GRAPH_CONFIG            14000
#define TIME_STOP_MODIF_MODE			   	14000
#define TIME_HIDE_MACHINE_HOURS_METER		15000
#define TIME_INHIB_30S_FIO2					30000
#define TIME_100_PR_CENT_O2					120000
#define TIME_USB_MESSAGE					   100
#define TIME_USB_ERROR_CODE_MESSAGE		   2000
#define TIME_USB_PROCESSING				   600
#define TIME_END_LONG_DOWN_KEY			   200
#define TIME_END_LONG_UP_KEY			   200
#define TIME_DOUBLE_MESSAGE                30000
#define TIME_LEAK_TEST                 2000

/*%C Constantes de calibration */
extern "C" const e_BOOL FlowFloatSegmentList[];

extern "C" const e_BOOL PatientPressureFloatSegmentList[];

extern "C" const e_BOOL ValvePressureFloatSegmentList[];

extern "C" const e_BOOL FiO2FloatSegmentList[];

extern "C" const e_BOOL FlowO2FloatSegmentList[];

extern "C" const e_BOOL O2PressureFloatSegmentList[];

typedef enum
{
   ProgExhalFlowUsed,    /* these two entries have to be declared before */
   ProgExhalFlowUnused,  /* 'Exhal' & 'Insp' ones ! */
   ProgInspControlEvent,
   ProgInspTrigEvent,
   ProgExhEvent,
   ProgHideBatEvent,
   ProgStartVentilOk,
   ProgStartVentilKo,
   ProgShowBatEvent,
   ProgInibAlarmOK,
   ProgInibAlarmNOK,
   ProgCancelAlarmOK,
   ProgCancelAlarmNOK,
   ProgRemoveHighPressureAlarm,   
   ProgValveMissing,
   ProgValveDetected,
   ProgBlocExpiMissing,
   ProgBlocExpiDetected,
   ProgSpo2SensorNoError,
   ProgSpo2SensorError,
   ProgFio2SensorOK,
   ProgFio2SensorNOK,
   ProgCheckSupplyNoError,
   ProgCheckSupplyError,
   ProgUsbKeyDetected,
   ProgUsbKeyNotDetected,
   ProgUsbErrorCodeReady,
   ProgUsbNewModeDetected,
   ProgStartMonitoring,
   ProgSupplyBusFailure,
   ProgSupplyBusOK   
} EventId;

#endif
