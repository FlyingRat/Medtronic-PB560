/******************************************************************************/
/*                                                                            */
/* Project N°  :  RC0306                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : VEN_O2_Autorization.c	   									  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                 		Actuators management                					*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                   					*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE 																	*/
/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Control.h"
#include "DB_AlarmStatus.h"
#include "Ventilation_Datas.h"
#include "VEN_O2_Autorization.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void VEN_O2_Autorization(void)
{
UWORD16 DetectedFio2Sensor = DB_ControlRead(DETECTED_FIO2_SENSOR);

UWORD16 CalibFio2 = DB_ControlRead (CALIBRATED_FIO2_SENSOR);

UWORD16 CalibFio2Req = DB_ControlRead(CALIB_FIO2_REQ_U16);
UWORD16 AlarmCalibFio2 = DB_AlarmStatusRead(ALARM_CALIB_FIO2_U16);

/*%C if no sensor detected => no O2 calibration */
   if (DetectedFio2Sensor == FALSE)
	{
   		VEN_AuthorizationRegulO2 = TRUE;
         if (CalibFio2Req >= SEGMENT_1)
				DB_ControlWrite(CALIB_FIO2_REQ_U16, NO_CALIB);
         if (AlarmCalibFio2 > ALARM_FALSE)
  	      	DB_AlarmStatusWrite(ALARM_CALIB_FIO2_U16, ALARM_FALSE);
         VEN_LaunchCalibO2 = FALSE;
	}
	else if (CalibFio2 == FALSE) 
   {
         /*%C Calibration O2 timer launch at ventilation start */
         if (VEN_LaunchCalibO2 == FALSE)
         {
	   		VEN_AuthorizationRegulO2 = FALSE;
            /*%C Timer calibration 45 s launch */
            TIM_StartDecounter(VEN_TIME_CALIB_FIO2,TIME_CALIB_FIO2);
            /*%C O2 calibration launch */
            DB_ControlWrite(CALIB_FIO2_REQ_U16, SEGMENT_1);
	  	      DB_AlarmStatusWrite(ALARM_CALIB_FIO2_U16, ALARM_TRUE);
            VEN_LaunchCalibO2 = TRUE;
         }
         else if (TIM_ReadDecounterValue(VEN_TIME_CALIB_FIO2) == 0)
         {
	   		VEN_AuthorizationRegulO2 = TRUE;
            DB_ControlWrite(CALIB_FIO2_REQ_U16, TEST_LIMITES_REQUEST);
	  	      DB_AlarmStatusWrite(ALARM_CALIB_FIO2_U16, ALARM_FALSE);
            VEN_LaunchCalibO2 = FALSE;
         }
   }
	else if (CalibFio2 == TRUE) 
	   		VEN_AuthorizationRegulO2 = TRUE;
}
