
#if defined(LEGENDAIR_XL2)
/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_LowFio2.c                                             	  */
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
#include "SEC_LowFio2.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_LowFio2_XL2(void)
{
	e_DB_ALARMS_STATE AlarmLowFio2 =	DB_AlarmStatusRead(ALARM_LOW_FIO2_U16);
   UWORD16 DetectedFio2Sensor = DB_ControlRead(DETECTED_FIO2_SENSOR);
	UWORD16 CalibratedFio2Sensor = DB_ControlRead(CALIBRATED_FIO2_SENSOR);
	UWORD16 MeasureFio2 = DB_ComputeRead(COMPUTED_FIO2);
	UWORD16 AdjustLowFio2 = DB_ConfigRead(ADJUST_LOW_FIO2);
  	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
	UWORD16 AdjustmentInProgress = DB_ControlRead(ADJUSTMENT_IN_PROGRESS_U16);
	e_DB_ALARMS_STATE AlarmCheckFio2 =
								DB_AlarmStatusRead(ALARM_CHECK_FIO2_U16);
	static UWORD16 Fio2LowSelect = FALSE;

	if(AdjustmentInProgress == FALSE)
	{
		Fio2LowSelect = DB_ConfigRead(FIO2_LOW_SELECT);
	}

	switch(AlarmLowFio2)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :

/*%C 	The alarm is  detected if the FIO2 mesiure is greater than Low FiO2    */
/*%C 	and there's FIO2 selected		  									 */
/*%C 	and there's FIO2 sensor detected 									 */
/*%C 	and there's  FIO2 sensor calibrated		  						 */

		if ((MeasureFio2 < AdjustLowFio2)
		&& (Fio2LowSelect == TRUE)
		&& (CalibratedFio2Sensor == TRUE)
		&& (AlarmCheckFio2 < ALARM_DISPLAYED) )
		{
/*%C		Alarm is turned to Detected & stored */
			DB_AlarmStatusWrite(ALARM_LOW_FIO2_U16, ALARM_DETECTED);
			TIM_StartDecounter(SEC_LOW_FIO2_TIM,TIME_LOW_FIO2);
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					               */
/******************************************************************************/
	case ALARM_DETECTED :

		if ((MeasureFio2 >= AdjustLowFio2)
		|| (Fio2LowSelect == FALSE)
		|| (CalibratedFio2Sensor == FALSE)
		|| (AlarmCheckFio2 == ALARM_DISPLAYED) )
		{
/*%C 		Alarm is turned to false  */
			DB_AlarmStatusWrite(ALARM_LOW_FIO2_U16, ALARM_FALSE);
		}

		else if(TIM_ReadDecounterValue(SEC_LOW_FIO2_TIM) == 0)
		{
/*%C  	Alarm is turned to True & stored with its associated event */
			DB_AlarmStatusWrite(ALARM_LOW_FIO2_U16, ALARM_TRUE);
			DB_EventMngt(EVENT_AL_LOW_FIO2 );
/*%C 		Up dating priority register */
			SEC_Medium_Priority_3 = SEC_Medium_Priority_3 | 0x0040;
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

		if ((MeasureFio2 >= AdjustLowFio2)
		|| (Fio2LowSelect == FALSE)
		|| (CalibratedFio2Sensor == FALSE)
		|| (AlarmCheckFio2 == ALARM_DISPLAYED) )
		{
/*%C 		Alarm is turned to false & stored with associeted event */
			DB_AlarmStatusWrite(ALARM_LOW_FIO2_U16, ALARM_FALSE);
			DB_EventMngt(EVENT_AL_END_OF_LOW_FIO2 );
/*%C 		Up dating priority register */
			SEC_Medium_Priority_3 = SEC_Medium_Priority_3 & 0xFFBF;	
			}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :
		Alarm_Error = ERR_AL_LOW_FIO2;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
	  	Alarm_Error = ERR_AL_LOW_FIO2;
		break;
	}
	return(Alarm_Error);
}
#endif

