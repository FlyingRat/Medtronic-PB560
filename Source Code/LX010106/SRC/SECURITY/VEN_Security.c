/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : VEN_Security.c                                                 */
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

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "Product.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_AlarmStatus.h"
#include "VEN_Security.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "Security_Datas.h"
#include "Ventilation_Datas.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void VEN_Security(void)
{
/* Ventil authorization recovery from base	                                 */
   UWORD16 Ventil_Authorization = DB_ControlRead(VENTIL_AUTHORIZATION_U16);
/* Ventil authorization memorization			                                 */
   static UWORD16 Ventil_Authorization_Memo = FALSE ;
/* Current mode recovery from base	  				                              */
   e_MODE_TYPES Current_Mode = DB_ControlRead(CURRENT_MODE_U16);
   UWORD16 ValveDetected = 	DB_ControlRead(VALVE_DETECTED_U16);
	UWORD16 ChangeMode = DB_ControlRead(CHANGE_MODE_U16);
	UWORD16 Valve_Detect_In_Progress = DB_ControlRead(VALVE_DETECT_IN_PROGRESS_U16);
	UWORD16 VoluntaryStopAlarmActivation = DB_ConfigRead(VOLUNTARY_STOP_ALARM_ACTIVATION);
/* Alarm no valve detection recovery from base				    			  */
	e_DB_ALARMS_STATE AlarmVoluntaryStop =
							DB_AlarmStatusRead(ALARM_VOLUNTARY_STOP_U16);

	static UWORD16 PreviousVolStopAlarmActivation = FALSE;

/*%C If valve detection in progress, then 								  	  		  */
	if (Valve_Detect_In_Progress == FALSE)
	{
/*%C Valve use/change alarm function call         */
   		SEC_ValveUseChangeMngt();
	}


/*%C Ventil authorization function call         */
   SEC_VentilAuthorization();
/*%C First cycle detection function call         */
   SEC_FirstCycleDetection();

/*%C Voluntary Stop alarm is launched only if it is activated */	
	if(VoluntaryStopAlarmActivation == TRUE)
	{
		if(PreviousVolStopAlarmActivation == FALSE)
		{
			DB_ControlWrite(VOLUNTARY_STOP_U16,FALSE);
		}
/*%C Voluntary stop alarm */
		SEC_VoluntaryStop();
	}
	else if(AlarmVoluntaryStop != ALARM_FALSE)
	{
/*%C    ALARM_VOLUNTARY_STOP_U16 = ALARM_FALSE				  */
		DB_AlarmStatusWrite(ALARM_VOLUNTARY_STOP_U16, ALARM_FALSE);
/*%C	Associated event is stored 										  */
		DB_EventMngt(EVENT_AL_END_OF_VOLUNTARY_STOP);
/*%C 	Up dating of priority register 								  */
		SEC_High_Priority_2= SEC_High_Priority_2& 0xDFFF;
		DB_ControlWrite(VOLUNTARY_STOP_U16,FALSE);
	}

/*%C Fio2 calibration needed */
	SEC_Fio2CalibrationNeeded();

/*%C 	At each change mode, an alarm reset is made         */
/*%C 	The inhibited and reset flag are reseted too         */
	   if (ChangeMode == TRUE)
	   {
			SEC_ResetAlarms();
/*%C 		High pressure flags initilization         */
			DB_ControlWrite(HIGH_PRESSURE_DETECTED_U16,
								 FALSE);
			DB_ControlWrite(HIGH_PRESSURE_EXHALATION_DETECTED_U16,
								 FALSE);
			DB_ControlWrite(HIGH_PRESSURE_FILTER_WINDOW_U16,
								 FALSE);
	   }
/******************************************************************************/
/*               SCHEDULED ALARMS DURING VENTILATION                          */
/******************************************************************************/
   if	(Ventil_Authorization == TRUE)
   {


/*%C  Alarms scheduled function of current mode in ventilation			   		*/
	   switch(Current_Mode)
	   {
#ifdef CONFIG_VOL_MODE
/******************************************************************************/
/*%C                           VOL MODE													*/
/******************************************************************************/
	   case VOL :
/*%C     Alarms scheduled in VOL mode */
         SEC_VolMode();
		   break;
#endif
/******************************************************************************/
/*%C                           PRES MODE													*/
/******************************************************************************/
	   case PRES :
/*%C     Alarms scheduled in PRES mode */
         SEC_PresMode();
		   break;

/******************************************************************************/
/*%C                           PSVT MODE													*/
/******************************************************************************/
 	   case PSVT :
/*%C     Alarms scheduled in PSVT mode */
         SEC_PsvtMode();
		   break;

#ifdef CONFIG_SIMV_MODE
/******************************************************************************/
/*%C                           VSIMV MODE													*/
/******************************************************************************/
	   case VSIMV :
/*%C     Alarms scheduled in VSIMV mode */
         SEC_VsimvMode();
		   break;


/******************************************************************************/
/*%C                           PSIMV MODE													*/
/******************************************************************************/
 	   case PSIMV :
/*%C     Alarms scheduled in PSIMV mode */
         SEC_PsimvMode();
		   break;
#endif

/******************************************************************************/
/*%C                          CPAP MODE													*/
/******************************************************************************/
	   case CPAP :
/*%C     Alarms scheduled in CPAP mode */
         SEC_CpapMode();
		   break;


/******************************************************************************/
/*                             DEFAULT 													*/
/******************************************************************************/
	   default:
		   break;
	   }

/*%C    Otherwise, in all modes, alarms below must be launched : */

/*%C  HIGH RATE ALARM */
	   SEC_HighRate();

/*%C  TURBINE OVERHEAT ALARM */
	   SEC_TurbineOverheat();

#ifdef SUPPORTAIR_M2
/*%C    FIO2 OFFSET ALARM */
	    SEC_Fio2OffsetDefault();

/*%C    CHECK FIO2 ALARM */
		SEC_CheckFio2();

 
/*%C    LOW FIO2 ALARM */
		SEC_LowFio2_M2();

/*%C    HIGH FIO2 ALARM */
	    SEC_HighFio2_M2();

/*%C    NO FIO2 SENSOR ALARM */
	    SEC_NoFio2Sensor_M2();

#elif defined (LEGENDAIR_XL2)

/*%C    CHECK FIO2 ALARM */
		SEC_CheckFio2_XL2();

/*%C    LOW FIO2 ALARM */
		SEC_LowFio2_XL2();

/*%C    HIGH FIO2 ALARM */
	    SEC_HighFio2_XL2();

/*%C    NO FIO2 SENSOR ALARM */
	    SEC_NoFio2Sensor_XL2();
#endif

#ifdef CONFIG_ALARM_O2

/*%C	CHECK O2 SUPPLY ALARM  */
		SEC_CheckO2Supply();

/*%C	MISSING O2 SUPPLY ALARM  */
		SEC_MissingO2Supply();

/*%C	CHECK O2 ALARM  */
		SEC_CheckO2();

/*%C	100% O2 ALARM */
		SEC_100_Fio2();

#endif

/*%C 	Alarms  for Leak modes */
		if(ValveDetected == FALSE)
		{

/*%C  		LEAKAGE ALARM */
		   	SEC_Leakage();
			
		}
		else
/*%C	WITH VALVE : valve detected = TRUE									  */
		{


#ifdef CONFIG_VTE
/*%C    	LOW VTE ALARM */
			SEC_LowVte();
#endif

/*%C Check Valve alarm is only launched after the third respiratory cycle, */
/*%C to prevent some valve from not working well */
/*%C when they are not at a good temperature */			
			if(VEN_ThirdCycle == TRUE)
			{
/*%C    	CHECK VALVE ALARM */
				SEC_CheckValve();
			}


#ifdef CONFIG_VTE
/*%C    	VALVE LEAKAGE ALARM */
			SEC_ValveLeakage();
		
/*%C    	HIGH VTE ALARM */
			SEC_HighVte();
#endif


		}

	}

	
	
/******************************************************************************/
/*%C             SCHEDULED ALARMS OUT OF VENTILATION                          */
/******************************************************************************/

   else 
   {
/*%C  Ventilation alarm reset when the ventilation is stopped						*/
		if (Ventil_Authorization_Memo == TRUE)
		{
			SEC_ResetAlarms();
		}
/*%C  Alarms scheduled function of current mode out of ventilation				*/
	   switch(Current_Mode)
	   {
/******************************************************************************/
/*%C                           VOL MODE													*/
/******************************************************************************/
	   case VOL :
		   break;

/******************************************************************************/
/*%C                           PSV MODE													*/
/******************************************************************************/
	   case PSVT :
	   case CPAP :
		   break;

/******************************************************************************/
/*%C                           PRES MODE													*/
/******************************************************************************/
	   case PRES :
		   break;
/******************************************************************************/
/*%C                           VSIMV MODE													*/
/******************************************************************************/
	   case VSIMV :
		   break;
/******************************************************************************/
/*%C                           PSIMV MODE													*/
/******************************************************************************/
	   case PSIMV :
		   break;
/******************************************************************************/
/*%C                           DEFAULT 													*/
/******************************************************************************/
	   default:
		   break;
	   }
   }
/******************************************************************************/
/*%C             SCHEDULED ALARMS IN AND OUT OF VENTILATION                   */
/******************************************************************************/
/*%C Alarms always checked */
/*%C CHECK SETTINGS ALARM */
	SEC_CheckSettings();

/*%C    FIO2 OFFSET ALARM */
    SEC_Fio2OffsetDefault();

/*%C TECHNICAL PROBLEM ALARM */
	SEC_TechnicalProblem();

/*%C AC POWER FAIL ALARM */
	SEC_ACPowerFail();

/*%C DC POWER FAIL ALARM */
	SEC_DCPowerFail();

/*%C CHECK SUPPLY ALARM */
	SEC_CheckSupply();

/*%C LOW BATTERY ALARM */
	SEC_LowBattery();

/*%C END OF BATTERY ALARM */
	SEC_EndOfBattery();

/*%C CHECK BATTERY ALARM */
	SEC_CheckBattery();

/*%C NO BATTERY ALARM */
	SEC_NoBattery();
	
/*%C CHECK BUZZER ALARM */
     SEC_CheckBuzzer();

/*%C CHECK LOW BATTERY BUZZER ALARM */
	SEC_BuzzerBatteryLow();

/*%C CHECK BATTERY BUZZER CHARGE FAILURE ALARM */
	SEC_BuzzerBatteryChargeFailure();

/*%C CHECK REMOTE ALARM */
	SEC_CheckRemoteAlarm();

/*%C Unknow battery ALARM */
	SEC_UnknownBattery();

/*%C CHECK battery ALARM */
	SEC_CheckBatteryCharge();

/*%C Cpu Reference alarm */
	SEC_CpuReferenceFailure();


/**************************/
/*%C  TECHNICAL ALARMS    */
/**************************/
/*%C Clock default ALARM */
	SEC_ClockDefault();

/*%C Speed default ALARM */
	SEC_SpeedDefault();

/*%C Keyboard default ALARM */
	SEC_KeyboardDefault();

/*%C Very Low Internal Pressure ALARM */
	SEC_VeryLowInternalPressure();

/*%C Very Low proximal Pressure ALARM */
	SEC_VeryLowProximalPressure();

/*%C Very Low valve Pressure ALARM */
	SEC_VeryLowValvePressure();

#ifdef CONFIG_VTE
/*%C Exhalation flow offset ALARM */
	SEC_ExhFlowOffsetDefault();

/*%C Exhalation flow calibration ALARM */
   SEC_CalibrationFailure();
#endif

/*%C Ambient temperature ALARM */
   SEC_AmbientTemperature();

/*%C Battery temperature ALARM */
   SEC_BatteryTemperature();

/*%C Cooling fan ALARM */
   SEC_CoolingFanFailure();

/*%C 24V failure ALARM */
   SEC_Failure24V();

/*%C Supply measure ALARM */
   SEC_SupplyMeasureFailure();

/*%C Flash Pointer ALARM */
	SEC_LooseFlashPointer();


#ifdef CONFIG_ALARM_O2
/*%C    O2 LEAKAGE ALARM  */
		SEC_O2Leakage();
#endif

/******************************************************************************/
/*%C             CANCELED STATE MANAGEMENT												*/
/******************************************************************************/
	SEC_CanceledStateMngt();

/******************************************************************************/
/*%C             ALARM INDICATION TREATMENT												*/
/******************************************************************************/
	SEC_AlarmIndication();

/* Ventilation authorization memorization													*/
	Ventil_Authorization_Memo = Ventil_Authorization;	  
	PreviousVolStopAlarmActivation = VoluntaryStopAlarmActivation;
}
