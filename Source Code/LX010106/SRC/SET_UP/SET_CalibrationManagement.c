/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_CalibrationManagement.c 												*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C Description          : Management of sensors calibration		     			*/
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
#include "Ventilation_Constants.h"
#include "Structure.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "System_Datas.h"
#include "SET_CalibrationManagement.h"
#include "Driver_Datas.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SET_CalibrationManagement(void)
{
	e_CalibrationCommand CalibFasValveReq = 
   											DB_ControlRead(CALIB_FAS_VALVE_REQ_U16);
   e_CalibrationCommand CalibPatientPressReq = 
   											DB_ControlRead(CALIB_PATIENT_PRESS_REQ_U16);
  	e_CalibrationCommand CalibValvePressReq =
  												DB_ControlRead(CALIB_VALVE_PRESS_REQ_U16);
   e_CalibrationCommand CalibFlowInspReq =
   											DB_ControlRead(CALIB_FLOW_INSP_REQ_U16);
   e_CalibrationCommand CalibFlowExhReq =
   											DB_ControlRead(CALIB_FLOW_EXH_REQ_U16);
	e_CalibrationCommand CalibAjustCmd = DB_ControlRead(CALIB_ADJUST_CMD_U16);

	e_CalibrationCommand CalibFlowO2Req = DB_ControlRead(CALIB_FLOW_O2_REQ_U16); 
	
	e_CalibrationCommand CalibPressO2Req =
													 DB_ControlRead(CALIB_PRESS_O2_REQ_U16); 
	e_CalibrationCommand CalibFiO2Req =
													 DB_ControlRead(CALIB_FIO2_REQ_U16); 


/*%C Proximal and patient pressure sensor													*/
/*%C Patient pressure calibration verification											*/
	if (CalibPatientPressReq >= AUTOCALIB_SEG_1)
	{
		SYS_CalibProcessing = TRUE;
	 	SET_CalibrationVerification(CALIB_PATIENT_PRESS_REQ_U16,
	 									  CalibrationParameters[SYS_PATIENT_PRESS_CALIB]);
	}
/*%C Patient pressure calibration verification											*/
	else if (CalibPatientPressReq > NO_CALIB)
	{
		SYS_CalibProcessing = TRUE;
		SET_DefaultCalibration(CALIB_PATIENT_PRESS_REQ_U16,
									  CalibrationParameters[SYS_PATIENT_PRESS_CALIB],
									  AD_Digit.PatientPressure,
									  AD_Digit.ProxPressure,
									  AD_Digit.ValvePressure);
	}
				
/*%C Valve pressure sensor																		*/

/*%C Valve pressure calibration verification												*/
	else if (CalibValvePressReq >= AUTOCALIB_SEG_1)
	{
		SYS_CalibProcessing = TRUE;
		SET_CalibrationVerification(CALIB_VALVE_PRESS_REQ_U16,
											 CalibrationParameters[SYS_VALVE_PRESS_CALIB]);
	}
/*%C Valve pressure calibration 																*/
	else if (CalibValvePressReq > NO_CALIB)
	{
		SYS_CalibProcessing = TRUE;
	 	SET_DefaultCalibration(CALIB_VALVE_PRESS_REQ_U16,
	 								  CalibrationParameters[SYS_VALVE_PRESS_CALIB],
	 								  AD_Digit.ValvePressure,
	 								  0,0);
	}

/*%C Inspiration flow sensor		 															*/

/*%C Inspiration flow calibration verification											*/
	else if (CalibFlowInspReq >= AUTOCALIB_SEG_1)
	{
		SYS_CalibProcessing = TRUE;
	 	SET_CalibrationVerification(CALIB_FLOW_INSP_REQ_U16,
	  										 CalibrationParameters[SYS_INSP_FLOW_CALIB]);
	}
/*%C Inspiration flow calibration 															*/
	else if (CalibFlowInspReq > NO_CALIB)
	{
		SYS_CalibProcessing = TRUE;
  		SET_DefaultCalibration(CALIB_FLOW_INSP_REQ_U16,
  									  CalibrationParameters[SYS_INSP_FLOW_CALIB],
  									  AD_Digit.FlowInsp,
  									  0,0);
	}

/*%C Exhalated flow sensor		 																*/

/*%C Exhalated flow calibration verification												*/
	else if (CalibFlowExhReq >= AUTOCALIB_SEG_1)
	{
		SYS_CalibProcessing = TRUE;
		SET_CalibrationVerification(CALIB_FLOW_EXH_REQ_U16,
											 CalibrationParameters[SYS_EXH_FLOW_VERIF]);
	}
/*%C Exhalated	flow calibration 																*/
	else if (CalibFlowExhReq > NO_CALIB)
	{
		SYS_CalibProcessing = TRUE;
		SET_ExhFlowCalibration(CALIB_FLOW_EXH_REQ_U16,
									  CalibrationParameters[SYS_EXH_FLOW_CALIB]);
	}

/*%C Fas valve 		 																*/

/*%C Fas valve calibratin verification												*/
	else if (CalibFasValveReq == END_AUTOCALIB)
	{
		SYS_CalibProcessing = TRUE;
/*%C  Correspondant control writing					                 					*/
		DB_ControlWrite(SETUP_CONTROL_TYPE_U16, CONTROL_PRESSURE_MAINT);
/*%C  Set point reset									                 					*/
		DB_ControlWrite(SETUP_CONTROL_SET_POINT_U16, 0);
/*%C  Set point reset									                 					*/
		DB_ControlWrite(CALIB_FAS_VALVE_REQ_U16, NO_CALIB);
	}
/*%C Fas valve calibration 																*/
	else if (CalibFasValveReq > NO_CALIB)
	{
		SYS_CalibProcessing = TRUE;
		SET_FasValveCalibration(CALIB_FAS_VALVE_REQ_U16);
	}



/*%C O2	flow calibration verification														*/
	else if (CalibFlowO2Req >= AUTOCALIB_SEG_1)
	{
		SYS_CalibProcessing = TRUE;
		SET_CalibrationVerification(CALIB_FLOW_O2_REQ_U16,
											 CalibrationParameters[SYS_O2_FLOW_CALIB]);
	}
/*%C O2	flow calibration 																		*/
	else if (CalibFlowO2Req > NO_CALIB)
	{
		SYS_CalibProcessing = TRUE;
		SET_DefaultCalibration(CALIB_FLOW_O2_REQ_U16,
									  CalibrationParameters[SYS_O2_FLOW_CALIB],
									  AD_Digit.FlowO2,
									  0,0);
	}

/*%C O2	pressure calibration verification												*/
	else if (CalibPressO2Req >= AUTOCALIB_SEG_1)
	{
		SYS_CalibProcessing = TRUE;
		SET_CalibrationVerification(CALIB_PRESS_O2_REQ_U16,
											 CalibrationParameters[SYS_O2_PRESSURE_CALIB]);
	}
/*%C O2	pressure calibration 	  															*/
	else if (CalibPressO2Req > NO_CALIB)
	{
		SYS_CalibProcessing = TRUE;
		SET_DefaultCalibration(CALIB_PRESS_O2_REQ_U16,
							   CalibrationParameters[SYS_O2_PRESSURE_CALIB],
							   AD_Digit.O2Pressure,
							   0,0);
	}

/*%C else, no calibration or verification to do	 										*/
	else 
	{
		SYS_CalibProcessing = FALSE;
		DB_ControlWrite(SETUP_CONTROL_TYPE_U16,
							 CONTROL_SPEED);
		DB_ControlWrite(SETUP_CONTROL_SET_POINT_U16,
							 CalibAjustCmd);

	}

/*%C Fio2 sensor calibration	 										*/
	if (CalibFiO2Req > NO_CALIB)
	{
		SET_DefaultCalibration(CALIB_FIO2_REQ_U16,
							 CalibrationParameters[SYS_FIO2_CALIB],
							 AD_Digit.Fio2,
							  0,0);
	}		
}