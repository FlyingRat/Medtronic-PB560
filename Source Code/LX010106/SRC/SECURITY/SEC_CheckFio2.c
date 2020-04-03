/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckFio2.c                                             	  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            Management of the alarm leakage                               */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "SEC_CheckFio2.h"
#include "Security_Datas.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckFio2(void)
{
	e_DB_ALARMS_STATE AlarmCheckFio2 =
								DB_AlarmStatusRead(ALARM_CHECK_FIO2_U16);
    UWORD16 DetectedFio2Sensor = 	DB_ControlRead(DETECTED_FIO2_SENSOR);
	UWORD16 CalibratedFio2Sensor = 	DB_ControlRead(CALIBRATED_FIO2_SENSOR);
	UWORD16 MeasureFio2 = DB_ComputeRead(MEASURE_FIO2) / 10; 
	UWORD16 AdjustFio2 = DB_ConfigRead(ADJUST_FIO2);

  	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

	switch(AlarmCheckFio2)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :

/*%C 	The alarm is not detected if tne FIO2 mesiure is greater than 18%    */
/*%C 	or there's no FIO2 selected		  									 */
/*%C 	or there's no FIO2 sensor detected 									 */
/*%C 	or there's no FIO2 sensor calibrated		  						 */

		if ((MeasureFio2 < 18)
		&& (AdjustFio2 > 21)
		&& (DetectedFio2Sensor == TRUE)
		&& (CalibratedFio2Sensor == TRUE))
		{
/*%C		Alarm is turned to Detected & stored */
			 TIM_StartDecounter(SEC_CHECK_FIO2_TIM,TIME_CHECK_FIO2);
			 DB_AlarmStatusWrite(ALARM_CHECK_FIO2_U16, ALARM_DETECTED);
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					               */
/******************************************************************************/
	case ALARM_DETECTED :

		if ((MeasureFio2 >= 18)
		|| (AdjustFio2 == 21)
		|| (DetectedFio2Sensor == FALSE)
		|| (CalibratedFio2Sensor == FALSE))
		{
/*%C 		Alarm is turned to false  */
			DB_AlarmStatusWrite(ALARM_CHECK_FIO2_U16, ALARM_FALSE);
		}

		else if(TIM_ReadDecounterValue(SEC_CHECK_FIO2_TIM) == 0)
		{
/*%C  	Alarm is turned to True & stored with its associated event */
			DB_AlarmStatusWrite(ALARM_CHECK_FIO2_U16,
									  ALARM_TRUE);
			DB_EventMngt(EVENT_AL_CHECK_FIO2 );
/*%C 		Up dating priority register */
			SEC_High_Priority_2= SEC_High_Priority_2|0x0004;
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State												*/
/******************************************************************************/
	case ALARM_TRUE :
/*%C 	The following state ,"ALARM_DISPLAYED", is written by HMI module. */
/*%C  So there is no action to do .*/
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                              */
/******************************************************************************/
	case ALARM_DISPLAYED	:
		if ((MeasureFio2 >= 18)
		|| (AdjustFio2 == 21)
		|| (DetectedFio2Sensor == FALSE)
		|| (CalibratedFio2Sensor == FALSE))
   
		{
/*%C 		Alarm is turned to false & stored with associeted event */
			DB_AlarmStatusWrite(ALARM_CHECK_FIO2_U16,
									  ALARM_FALSE);
			DB_EventMngt(EVENT_AL_END_OF_CHECK_FIO2 );
/*%C 		Up dating priority register */
			SEC_High_Priority_2= SEC_High_Priority_2& 0xFFFB;
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :
		Alarm_Error = ERR_AL_CHECK_FIO2;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
	  	Alarm_Error = ERR_AL_CHECK_FIO2;
		break;
	}
	return(Alarm_Error);
}

