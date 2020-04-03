/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_CalibrationManagement.c 												*/
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
#include "Structure.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_AlarmStatus.h"
#include "System_Datas.h"
#include "SYS_CalibrationManagement.h"
#include "Driver_Datas.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SYS_CalibrationManagement(void)
{

   e_CalibrationCommand CalibFlowExhReq =
   											DB_ControlRead(CALIB_FLOW_EXH_REQ_U16);
	e_CalibrationCommand CalibAjustCmd = 
												DB_ControlRead(CALIB_ADJUST_CMD_U16);
  	e_CalibrationCommand CalibFio2 =
  												DB_ControlRead(CALIB_FIO2_REQ_U16);

   static Mutex_InitRegul = FALSE;

/*%C Exhalated flow sensor		 																*/

/*%C Exhalated	flow calibration 																*/
	if (CalibFlowExhReq > NO_CALIB)
	{
		SYS_ExhFlowCalibration(CalibFlowExhReq,
									  CalibrationParameters[SYS_EXH_FLOW_CALIB]);
	
      Mutex_InitRegul = TRUE;
	}

/*%C else, no calibration to do	 															*/
	else if (Mutex_InitRegul == TRUE)
	{
		DB_ControlWrite(SETUP_CONTROL_TYPE_U16,
							 CONTROL_SPEED);
		DB_ControlWrite(SETUP_CONTROL_TYPE_U16,
							 CalibAjustCmd);
	   Mutex_InitRegul = FALSE;
	}

/*%C Fio2 calibration 																*/
	else if (CalibFio2 > NO_CALIB)
	{
	 	SYS_Fio2Calibration(CALIB_FIO2_REQ_U16,
	 								  CalibrationParameters[SYS_FIO2_CALIB],
	 								  AD_Digit.Fio2);
	}

}