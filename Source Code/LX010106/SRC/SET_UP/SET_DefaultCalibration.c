/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_DefaultCalibration.c 													*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C Description          : Sensors calibration		     								*/
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
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_AlarmStatus.h"
#include "System_Datas.h"
#include "DB_Measurement.h"
#include "Driver_Datas.h"
#include "SET_DefaultCalibration.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SET_DefaultCalibration(UWORD16 RequestType,
									 t_SYS_CalibrationParameters CP,
									 UWORD16 CAN_Digit1,
									 UWORD16 CAN_Digit2,
									 UWORD16 CAN_Digit3)
{
   UWORD16 CalibAdjustCmd = 0;
   UWORD16 CalibAdjustVanneFio2Cmd = 0;
   static UWORD16 Indice = 0;
	UWORD16 TestLimitsOk1 = 0;  
	UWORD16	TestLimitsOk2 = 0;
	UWORD16	TestLimitsOk3 = 0;
   static UWORD16 DigitNb1 = 0;
	UWORD32 FilteredDigit1=0;
/* Calibration array for inspirated and exhalated values filtering            */
	static UWORD16 Digit1[80];
	static UWORD16 Digit2[80];
   static UWORD16 DigitNb2 = 0;
	UWORD32 FilteredDigit2=0;
	static UWORD16 Digit3[80];
   static UWORD16 DigitNb3 = 0;
	UWORD32 FilteredDigit3=0;
	e_CalibrationCommand Request = NO_CALIB;
/*%C Request type recovery from base		     						               */
	Request = DB_ControlRead(RequestType);

/*%C Adjusted calibration command recovery from base		                     */
	CalibAdjustCmd = DB_ControlRead(CALIB_ADJUST_CMD_U16);
	CalibAdjustVanneFio2Cmd = DB_ControlRead(CALIB_ADJUST_VANNE_FIO2_CMD);

/*%C Calibration for requests differents from FIO2		                     */
	if (RequestType != CALIB_FIO2_REQ_U16)
	{
/*%C 	If a calibration is requested, the mark is memorized                    */
		if (Request < (SEGMENT_1 + CP.CalibPointsNumber))
		{
			Indice = Request - SEGMENT_1;
		}
/*%C 	If a calibration is requested, the mark is memorized                    */
		if (RequestType != CALIB_FLOW_O2_REQ_U16)
		{
/*%C 		Speed or pressure control test  						                     */
			if (CalibAdjustCmd == 0)
			{
/*%C  		Setup control type writing in base 	 			                     */
				DB_ControlWrite(SETUP_CONTROL_TYPE_U16,
									 CP.RegulationType);
/*%C  		Set point writing in base 				                     			*/
				DB_ControlWrite(SETUP_CONTROL_SET_POINT_U16,
									 CP.CalibPoint[Indice] * 10);   
			}
			else
			{
/*%C  		Setup control type writing in base 	  			                     */
				DB_ControlWrite(SETUP_CONTROL_TYPE_U16,
									 CONTROL_SPEED);
/*%C  		Set point writing in base 		  		                     			*/
				DB_ControlWrite(SETUP_CONTROL_SET_POINT_U16,
									 CalibAdjustCmd);
			}
		}
		else
		{
			if (CalibAdjustVanneFio2Cmd == 0)
			{
				DB_ControlWrite(SETUP_CONTROL_TYPE_U16,
									 CP.RegulationType);
				DB_ControlWrite(SETUP_CONTROL_SET_POINT_U16,
									 CP.CalibPoint[Indice] * 10); 
 			}
/*%C  	Manuel O2 calibration 		  		                     			*/
  	 		else	
			{
				DB_ControlWrite(SETUP_CONTROL_TYPE_U16,
									 CONTROL_FLOW_O2_MANUEL);
				DB_ControlWrite(SETUP_CONTROL_SET_POINT_U16,
									 CalibAdjustVanneFio2Cmd);
			}
		}
	}
	else
	{
		Indice = 0;
	}

/*%C CAN1 average compute (80 values)				                     			*/
	Digit1[DigitNb1++] = CAN_Digit1;
	DigitNb1 %= 80;
	FilteredDigit1 = average(Digit1,
									 80);                    
/*%C CAN2 average compute (proximal) if patient pressure calibration request	*/
	if (RequestType == CALIB_PATIENT_PRESS_REQ_U16)
	{
  		Digit2[DigitNb2++] = CAN_Digit2;
/*%C Average compute on 80 values					                     			*/
  		DigitNb2 %= 80;
		FilteredDigit2 = average(Digit2, 80);

		Digit3[DigitNb3++] = CAN_Digit3;
/*%C Average compute on 80 values					                     			*/
  		DigitNb3 %= 80;
		FilteredDigit3 = average(Digit3, 80);
	}                    

/*%C Offset verification asked by HMI   			*/
	if (Request == TEST_LIMITES_REQUEST)
	{
/*%C  CAN 1 filtered value is written in the config base for checking 			*/
		TestLimitsOk1 = DB_ConfigWrite(CP.FirstOffsetIndex + Indice,
							 			 		 (UWORD16)(FilteredDigit1));
/*%C  CAN 2 and 3 filtered value is written in the config base for checking  			*/
		if (RequestType == CALIB_PATIENT_PRESS_REQ_U16)
		{
		  TestLimitsOk2 = DB_ConfigWrite(OFFSET_PATIENT_PROX_PRESS_1_U16 + Indice,
 													(UWORD16)(FilteredDigit2));
			TestLimitsOk3 = DB_ConfigWrite(OFFSET_VALVE_PRESS_U16 + Indice,
 													(UWORD16)(FilteredDigit3));
		}
		else
		{
			TestLimitsOk2 = TRUE;
			TestLimitsOk3 = TRUE;
		}

/*%C  If the test fails, the alarm is activated and transmitted to HMI			*/
		if ( (TestLimitsOk1 == FALSE)
		  || (TestLimitsOk2 == FALSE)
		  || (TestLimitsOk3 == FALSE) )
		{
/*%C  		If the test 1 is FALSE, the alarm is written in the base					*/
			if (TestLimitsOk1 == FALSE)
			{ 
				DB_AlarmStatusWrite(CP.OffsetAlarmIndex,
									 	  ALARM_DETECTED);
			}
/*%C  		If the test 2 is FALSE, the alarm is written in the base					*/
			if (TestLimitsOk2 == FALSE)
			{ 
			  DB_AlarmStatusWrite(TECH_ALARM_PROXIMAL_PRESSURE_OFFSET_DEFAULT_U16,
			  							 ALARM_DETECTED);
			}
/*%C  		If the test 3 is FALSE, the alarm is written in the base					*/
			if (TestLimitsOk3 == FALSE)
			{ 
			  DB_AlarmStatusWrite(TECH_ALARM_VALVE_PRESS_OFFSET_DEFAULT_U16,
			  							 ALARM_DETECTED);
			}
/*%C  	The test result is written in control base									*/
			DB_ControlWrite(RequestType,
								 TEST_LIMITES_FALSE);
/*%C  	Long beep request									*/
			DB_ControlWrite(VALIDATION_BIP_U16,
								 BIP_LONG);
         if (RequestType == CALIB_FIO2_REQ_U16)
			{ 
				DB_ControlWrite(CALIBRATED_FIO2_SENSOR,
									 FALSE);	
				DB_ControlWrite(DETECTED_FIO2_SENSOR,
									 FALSE);	
			}
		}
/*%C 	else, the test is ok, the alarm is inhibited and transmitted to HMI		*/
		else
		{
/*%C 		Alarm inhibition for HMI															*/
			DB_ControlWrite(RequestType,
								 TEST_LIMITES_OK);
/*%C  		The calibration event is written in the event base							*/
			DB_EventMngt(CP.EventCalibration);
/*%C  		Short beep request									*/
			DB_ControlWrite(VALIDATION_BIP_U16,
								 BIP_SHORT);
			if (RequestType == CALIB_FIO2_REQ_U16)
			{
/*%C  			FIO2 calibration failure alarm cancellation								*/
				DB_AlarmStatusWrite(CP.OffsetAlarmIndex,
										  ALARM_FALSE);
				DB_ControlWrite(CALIBRATED_FIO2_SENSOR,
									 TRUE);
			}
		}
	}
}

