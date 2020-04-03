/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_CalibrationVerification.c 										 	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C Description          : Verification of calibration		     					*/
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
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_AlarmStatus.h"
#include "System_Datas.h"
#include "SET_CalibrationVerification.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SET_CalibrationVerification(UWORD16 RequestType,
											t_SYS_CalibrationParameters CP)
{
	UWORD16 Indice = 0;
	e_CalibrationCommand Request = DB_ControlRead(RequestType);


/*%C If a calibration is requested                     								*/
	if (Request < AUTOCALIB_SEG_1 + CP.CalibPointsNumber)
	{
/*%C  Calibration point indice computing                								*/
		Indice = Request - AUTOCALIB_SEG_1;
/*%C  Correspondant control writing					                 					*/
		DB_ControlWrite(SETUP_CONTROL_TYPE_U16,
							 CP.RegulationType);
/*%C  Set point writing ( * 10: tenth cmH2O or dl)									   */
		DB_ControlWrite(SETUP_CONTROL_SET_POINT_U16,
							 CP.CalibPoint[Indice] * 10);  
	}
/*%C Pressure control reset (end of verification)       								*/
	else
	{
/*%C  Correspondant control writing					                 					*/
		DB_ControlWrite(SETUP_CONTROL_TYPE_U16,
							 CP.RegulationType);
/*%C  Set point reset									                 					*/
		DB_ControlWrite(SETUP_CONTROL_SET_POINT_U16,
							 0);
/*%C  Set point reset									                 					*/
		DB_ControlWrite(RequestType,
							 NO_CALIB);
	}
}
