#if defined(SUPPORTAIR_M2)
/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_HighFio2_M2.c                                           	  */
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
#include "define.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "SEC_HighFio2.h"
#include "Security_Datas.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_HighFio2_M2(void)
{
	e_DB_ALARMS_STATE AlarmHighFio2 = DB_AlarmStatusRead(ALARM_HIGH_FIO2_U16);
   UWORD16 DetectedFio2Sensor = DB_ControlRead(DETECTED_FIO2_SENSOR);
	UWORD16 CalibratedFio2Sensor = DB_ControlRead(CALIBRATED_FIO2_SENSOR);
	UWORD16 FiO2100Active = DB_ControlRead(FIO2_100_ACTIVE);
	UWORD16 MeasureFio2 = DB_ComputeRead(MEASURE_FIO2) / 10; 
	UWORD16 AdjustFio2 = DB_ConfigRead(ADJUST_FIO2);
	UWORD16 ComputedHighFio2 = 0; 
  	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

	ComputedHighFio2 = AdjustFio2 + 15;

	switch(AlarmHighFio2)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :

/*%C 	The alarm is not detected if tne FIO2 mesiure is greater than 18%    */
/*%C 	or there's no FIO2 selected		  									 */
/*%C 	or there's no FIO2 sensor detected 									 */
/*%C 	or there's no FIO2 sensor calibrated		  						 */

		if ((MeasureFio2 > ComputedHighFio2)
		&& (AdjustFio2 > cFIO2_MIN_ADJUST)
		&& (CalibratedFio2Sensor == TRUE)
		&& (FiO2100Active == FALSE) 
		&&	(TIM_ReadDecounterValue(SEC_100_FIO2_TIM) == 0))
		{
/*%C	Alarm is turned to Detected & stored */
			DB_AlarmStatusWrite(ALARM_HIGH_FIO2_U16, ALARM_DETECTED);
			TIM_StartDecounter(SEC_HIGH_FIO2_TIM,TIME_HIGH_FIO2);
		}
		
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					               */
/******************************************************************************/
	case ALARM_DETECTED :

		if ((MeasureFio2 <= ComputedHighFio2)
		|| (AdjustFio2 == cFIO2_MIN_ADJUST)
		|| (CalibratedFio2Sensor == FALSE)
		|| (FiO2100Active == TRUE)
		||	(TIM_ReadDecounterValue(SEC_100_FIO2_TIM) != 0))
 		{
/*%C 		Alarm is turned to false  */
			DB_AlarmStatusWrite(ALARM_HIGH_FIO2_U16, ALARM_FALSE);
		}

		else if(TIM_ReadDecounterValue(SEC_HIGH_FIO2_TIM) == 0)
		{
/*%C  	Alarm is turned to True & stored with its associated event */
			DB_AlarmStatusWrite(ALARM_HIGH_FIO2_U16, ALARM_TRUE);
			DB_EventMngt(EVENT_AL_HIGH_FIO2 );
/*%C 		Up dating priority register */
			SEC_Medium_Priority_3 = SEC_Medium_Priority_3 | 0x0080;
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
		if ((MeasureFio2 <= ComputedHighFio2)
		|| (AdjustFio2 == cFIO2_MIN_ADJUST)
		|| (CalibratedFio2Sensor == FALSE)
		|| (FiO2100Active == TRUE) 
		||	(TIM_ReadDecounterValue(SEC_100_FIO2_TIM) != 0))
		{
/*%C 		Alarm is turned to false & stored with associeted event */
			DB_AlarmStatusWrite(ALARM_HIGH_FIO2_U16, ALARM_FALSE);
			DB_EventMngt(EVENT_AL_END_OF_HIGH_FIO2 );
/*%C 		Up dating priority register */
			SEC_Medium_Priority_3 = SEC_Medium_Priority_3 & 0xFF7F;
		}
		Alarm_Error = NO_ERR_AL;

		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :
		Alarm_Error = ERR_AL_HIGH_FIO2;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
	  	Alarm_Error = ERR_AL_HIGH_FIO2;
		break;
	}
	return(Alarm_Error);
}
#endif