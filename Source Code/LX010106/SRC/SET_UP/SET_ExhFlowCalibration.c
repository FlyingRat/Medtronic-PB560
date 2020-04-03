/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_ExhFlowCalibration.c 										 			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C Description          :calibration	of exhalation flow	     					*/
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
#include "DB_AlarmStatus.h"
#include "System_Datas.h"
#include "Driver_Datas.h"
#include "SET_ExhFlowCalibration.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SET_ExhFlowCalibration(UWORD16 RequestType, t_SYS_CalibrationParameters CP)
{
   static UWORD16 Indice = 0;
	static UWORD16 MemoIndice = 255;

	e_BOOL TestLimitsOk;  
	
   static UWORD16 DigitNb = 0;
/*%C calibration have a wait state of 100ms minimum to have a correct         */
/*%C acquisition of measured values  */
	UWORD16 FilteredDigit;
	SWORD32 ToleranceMore;
	SWORD32 ToleranceLess;
	SWORD16 FilterQi = (SWORD16)DB_ComputeRead(FILTER_QI_S16);
	static UWORD16 MutexTestLimites;
/* Tableau pour le filtrage des valeurs de debit inspi et expi pour           */
/* la calibration	*/
	static UWORD16 Digit[80];

	e_CalibrationCommand Request = NO_CALIB;
/*%C Request type recovery from base		     						               */
	Request = DB_ControlRead(RequestType);
 
/*%C Find current index on calibration request */ 
	if (Request < (SEGMENT_1 + CP.CalibPointsNumber))
		Indice = Request - SEGMENT_1;

/*%C Check a difference to detect a calibration request */
	if (Indice != MemoIndice)
	{
/*%C 	reset of Alarm state */
		DB_AlarmStatusWrite(TECH_ALARM_EXHAL_FLOW_OFFSET_DEFAULT_U16,
								  ALARM_FALSE);
/*%C 	Init of the lock of test limits function */
		MutexTestLimites = FALSE;
/*%C 	Start delay for measure stabilization */
   	TIM_StartDecounter(SYS_TIME_AUTO_CALIB, TIME_AUTO_CALIB);
/*%C 	Start the maximum time out for automatic calibration */
   	TIM_StartDecounter(SYS_TIME_OUT_CALIB, TIME_OUT_CALIB);
	}
		
/*%C Sending the type of regulation needed */
	DB_ControlWrite(SETUP_CONTROL_TYPE_U16, CP.RegulationType);
	DB_ControlWrite(SETUP_CONTROL_SET_POINT_U16, (UWORD16)((UWORD32)CP.CalibPoint[Indice] * 100/10));  // convertit en 10ème de mbar ou de dl 
	
/*%C Average of ANC values */
   Digit[DigitNb++] = AD_Digit.FlowExh;
   DigitNb %= 80;
	FilteredDigit = average(Digit, 80); 
/*%C 0 lpm segment exhalation flow sensor */
	if (Indice == 0) 
	{
/*%C 	Compute and saturation of  positive gap */
		ToleranceMore = (SWORD32)CP.CalibPoint[Indice] + 20;// soit + 2 lpm de tolerance
/*%C 	Compute and saturation of  negative gap */
	   ToleranceLess = (SWORD32)CP.CalibPoint[Indice] - 20;// - 2 lpm 
	}
/*%C 5 lpm segment exhalation flow sensor */
	else if ((Indice == 1)||(Indice == 3))
	{
/*%C 	Compute and saturation of positive gap */
	   ToleranceMore = (SWORD32)CP.CalibPoint[Indice] * 1020 / 100;// soit 2 % de tolerance
/*%C 	Compute and saturation of  negative gap */
	   ToleranceLess = (SWORD32)CP.CalibPoint[Indice] * 960 / 100;// 4 %
	}
/*%C Other segments */
	else
	{
/*%C 	Compute and saturation of  positive gap */
	   ToleranceMore = (SWORD32)CP.CalibPoint[Indice] * 1010 / 100;// 1%
/*%C 	Compute and saturation of  negative gap */
	   ToleranceLess = (SWORD32)CP.CalibPoint[Indice] * 990 / 100;// 1%
	}

/*%C Check if measured flow is out of range (Min & max) */
	if ( ((SWORD32)FilterQi > ToleranceMore) 
	  || ((SWORD32)FilterQi < ToleranceLess) )
	{   
/*%C  Stabilization time counter launch */
   	TIM_StartDecounter(SYS_TIME_AUTO_CALIB, TIME_AUTO_CALIB);
 	}

/*%C When the flow is stabilized */
	if ( (TIM_ReadDecounterValue(SYS_TIME_AUTO_CALIB) == 0)
	  && (MemoIndice == Indice )
	  && (MutexTestLimites == FALSE) )
	{
/*%C	Sending of filtered value for checking */
		TestLimitsOk = DB_ConfigWrite(CP.FirstOffsetIndex + Indice,
												FilteredDigit);
/*%C 	If the test fails */
		if (TestLimitsOk == FALSE)
		{
/*%C     Alarm activation */
         DB_AlarmStatusWrite(TECH_ALARM_EXHAL_FLOW_OFFSET_DEFAULT_U16,
			                    ALARM_DETECTED);
/*%C     Send alarm information to HMI */
			DB_ControlWrite(CALIB_FLOW_EXH_REQ_U16,
			                TEST_LIMITES_FALSE);
/*%C     Long beep request									*/
		   DB_ControlWrite(VALIDATION_BIP_U16,
							   BIP_LONG);
		}
		else
		{
/*%C	   Send Event of Calibration & information of good Calibration */
			DB_EventMngt(CP.EventCalibration);
			DB_ControlWrite(CALIB_FLOW_EXH_REQ_U16, TEST_LIMITES_OK);
/*%C     Short beep request									*/
		   DB_ControlWrite(VALIDATION_BIP_U16,
							   BIP_SHORT);
		}
		MutexTestLimites = TRUE;
	}
/*%C When the maximum delay for automatic calibration is over */
	else if ( (TIM_ReadDecounterValue(SYS_TIME_OUT_CALIB) == 0)
			 && ( MutexTestLimites == FALSE) )
	{
/*%C 	Alarm activation */
		DB_AlarmStatusWrite(CP.OffsetAlarmIndex, ALARM_DETECTED);
/*%C  Send alarm information to HMI */
		DB_ControlWrite(CALIB_FLOW_EXH_REQ_U16, TEST_LIMITES_FALSE);
		MutexTestLimites = TRUE;
/*%C  Long beep request									*/
	   DB_ControlWrite(VALIDATION_BIP_U16,
	 					   BIP_LONG);
	}

/*%C Updating of calibration segment */
	MemoIndice = Indice;
}

