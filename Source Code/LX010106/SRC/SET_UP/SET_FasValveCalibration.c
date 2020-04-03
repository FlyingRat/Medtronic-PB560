/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_FasValveCalibration.c 										 			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C Description          :calibration	of fas valve   			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                     										*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE																	*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_Config.h"
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "System_Datas.h"
#include "Driver_Datas.h"
#include "SET_FasValveCalibration.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SET_FasValveCalibration(UWORD16 RequestType)
{
	SWORD16 MeasureValvePressure = (SWORD16)DB_ComputeRead(MEASURE_VALVE_PRESSURE_S16);
	
	UWORD16 MeasureValveCurrent = (UWORD16)DB_ComputeRead(MEASURE_VALVE_CURRENT_U16);

	static UWORD16 Indice = 0;
	static UWORD16 MemoIndice = 255;
 	static UWORD16 MutexTestLimites;
	static e_BOOL TestLimitsOk = TRUE;  
 	UWORD16 FilteredValvePressDigit;
 	UWORD16 FilteredValveCurrentDigit;
	static UWORD16 DigitValvePress[80];
	static UWORD16 DigitValveCurrent[400];
   	static UWORD16 DigitNb1 = 0;
	static UWORD16 DigitNb2 = 0;
   	static SWORD16 ValveCmd = 0;
 	static UWORD16 Index = 0;

	e_CalibrationCommand Request = NO_CALIB;
/*%C Request type recovery from base		     						               */
	Request = DB_ControlRead(RequestType);

/*%C Setup control type writing in base 	 			                     */
	DB_ControlWrite(SETUP_CONTROL_TYPE_U16, CONTROL_PRESSURE_MAINT);
/*%C Set point writing in base 				                     			*/
	DB_ControlWrite(SETUP_CONTROL_SET_POINT_U16, 400);
	 
/*%C Find current index on calibration request */ 
	if (Request < (SEGMENT_1 + PWM_FAS_VALVE_CALIB_POINTS_NUMBER))
	{
		Indice = Request - SEGMENT_1;
	}

	if (Indice != MemoIndice)
	{
/*%C 	reset of Alarm state */
		DB_AlarmStatusWrite(TECH_ALARM_EXHAL_FLOW_OFFSET_DEFAULT_U16,
								  ALARM_FALSE);
/*%C 	Init of the lock of test limits function */
		MutexTestLimites = FALSE;
		Index = 0;
		TestLimitsOk = TRUE;
/*%C 	ValveCmd init */
		ValveCmd = VALVE_FAS_PWM_CALIB_POINTS[Indice];
/*%C 	Timers init */
		if ( (Request == SEGMENT_1)
	      || (Request == SEGMENT_2) ) 
		{
			TIM_StartDecounter(SYS_TIME_FAS_VALVE_CALIB, TIME_FAS_VALVE_EXTREMES_CALIB);
		}
		else if (Request == SEGMENT_3)
		{
			TIM_StartDecounter(SYS_TIME_FAS_VALVE_CALIB, TIME_FAS_VALVE_CURRENT_CALIB);
		}
	}

/*%C Average of ANC values */
	if (MeasureValvePressure < 0)
	{
	 	MeasureValvePressure = 0;
	}
	DigitValvePress[DigitNb1] = MeasureValvePressure * 10;
	DigitNb1++;
	DigitNb1 %= 80;
	FilteredValvePressDigit = average(DigitValvePress, 80); 

	DigitValveCurrent[DigitNb2] = MeasureValveCurrent * 10;
	DigitNb2++;
	DigitNb2 %= 100;
	FilteredValveCurrentDigit = average(DigitValveCurrent, 100); 

/*%C Segment 3 is for valve command / valve pressure calibration map */
	if (Request == SEGMENT_3)
	{
 		if (Index < VALVE_FAS_PRESS_CALIB_POINTS_NUMBER)
		{
/*%C		If a pressure calibration point is reached */
			if ( (MeasureValvePressure >= (SWORD16)VALVE_FAS_PRESS_CALIB_POINTS[Index])
			  || (ValveCmd == 0) )
			{
/*%C			Sending of valve command value for checking */
				TestLimitsOk = DB_ConfigWrite(OFFSET_FAS_VALVE_3_U16 + Index, ValveCmd) && TestLimitsOk;
/*%C			Increase index to check next pressure calibration point	  */
				Index ++ ;
			}
		}
/*%C  	Decrease valve command */
		ValveCmd -= 1;
		if (ValveCmd < 0)
		{
		 	ValveCmd = 0;
		}
	}
/*%C Move valve in the next position */
 	ACT_ValveCmd(ValveCmd);

/*%C When stabilisation timer is over */
	if ( (TIM_ReadDecounterValue(SYS_TIME_FAS_VALVE_CALIB) == 0)
	  && (MemoIndice == Indice )
	  && (MutexTestLimites == FALSE) )
	{
		if (Request == SEGMENT_3)
		{
/*%C		Sending of current filtered value for checking */
			TestLimitsOk = DB_ConfigWrite(I_VALVE_REF_U16, FilteredValveCurrentDigit) && TestLimitsOk;
		}
		else
		{
/*%C		Sending of pressure filtered value for checking */
			TestLimitsOk = TestLimitsOk && DB_ConfigWrite(OFFSET_FAS_VALVE_1_U16 + Indice,
												FilteredValvePressDigit);
		}
/*%C 	If the test fails */
		if (TestLimitsOk == FALSE)
		{
/*%C     	Alarm activation */
         	DB_AlarmStatusWrite(TECH_ALARM_VALVE_PRESS_OFFSET_DEFAULT_U16,
			                    ALARM_DETECTED);
/*%C     	Send alarm information to HMI */
			DB_ControlWrite(CALIB_FAS_VALVE_REQ_U16,
			                TEST_LIMITES_FALSE);
/*%C     	Long beep request									*/
		   	DB_ControlWrite(VALIDATION_BIP_U16,
							   BIP_LONG);
		}
		else
		{
/*%C	   	Send Event of Calibration & information of good Calibration */
			DB_EventMngt(EVENT_VALVE_PRESS_CALIB);
			DB_ControlWrite(CALIB_FAS_VALVE_REQ_U16, TEST_LIMITES_OK);
/*%C     Short beep request									*/
		   DB_ControlWrite(VALIDATION_BIP_U16,
							   BIP_SHORT);
		}
		MutexTestLimites = TRUE;
	 }
/*%C Updating of calibration segment */
	MemoIndice = Indice;
}

