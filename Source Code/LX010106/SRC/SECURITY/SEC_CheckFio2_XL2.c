/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0505                                                      */
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
#include "SEC_CheckFio2.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckFio2_XL2(void)
{
/* Alarm check Fio2 recovery from base 									  */
	e_DB_ALARMS_STATE AlarmCheckFio2 =
								DB_AlarmStatusRead(ALARM_CHECK_FIO2_U16);
/* Calibrated Fio2 sensor recovery from base 									  */
	UWORD16 CalibratedFio2Sensor = 	DB_ControlRead(CALIBRATED_FIO2_SENSOR);
/* Measure Fio2 recovery from base 									  */
	UWORD16 MeasureFio2 = DB_ComputeRead(MEASURE_FIO2) / 10; 

/* Alarm error declaration			 										  */
  	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

	switch(AlarmCheckFio2)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :

/*%C 	The alarm is detected if tne FIO2 mesure is lower than 18%    */
/*%C 	and FIO2 sensor is calibrated		  									 */
		if ((MeasureFio2 < 18)
		&& (CalibratedFio2Sensor == TRUE))
		{
/*%C		Alarm is turned to Detected & stored and associated timer is launched*/
			TIM_StartDecounter(SEC_CHECK_FIO2_TIM,TIME_CHECK_FIO2);
			DB_AlarmStatusWrite(ALARM_CHECK_FIO2_U16, ALARM_DETECTED);
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					               */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C 	The alarm is not detected if tne FIO2 mesiure is upper than 18%    */
/*%C 	or FIO2 sensor is not calibrated		  									 */
		if ((MeasureFio2 >= 18)
		|| (CalibratedFio2Sensor == FALSE))
		{
/*%C 		Alarm is turned to false  */
			DB_AlarmStatusWrite(ALARM_CHECK_FIO2_U16, ALARM_FALSE);
		}

/*%C 	Else if delay of default reached, then 								  */
		else if(TIM_ReadDecounterValue(SEC_CHECK_FIO2_TIM) == 0)
		{
/*%C  		Alarm is turned to True & stored with its associated event */
			DB_AlarmStatusWrite(ALARM_CHECK_FIO2_U16,
									  ALARM_TRUE);
			DB_EventMngt(EVENT_AL_CHECK_FIO2 );
/*%C 		Up dating priority register */
			SEC_High_Priority_3= SEC_High_Priority_3|0x0001;
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State												*/
/******************************************************************************/
	case ALARM_TRUE :
/*%C 	The following state ,"ALARM_DISPLAYED", is written by HMI module. */
/*%C  	So there is no action to do .*/
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                              */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C 	The alarm is not detected if tne FIO2 mesiure is upper than 18%    */
/*%C 	or FIO2 sensor is not calibrated		  									 */
		if ((MeasureFio2 >= 18)
		|| (CalibratedFio2Sensor == FALSE))
		{
/*%C 		Alarm is turned to false & stored with associeted event */
			DB_AlarmStatusWrite(ALARM_CHECK_FIO2_U16,
									  ALARM_FALSE);
			DB_EventMngt(EVENT_AL_END_OF_CHECK_FIO2 );
/*%C 		Up dating priority register */
			SEC_High_Priority_3= SEC_High_Priority_3& 0xFFFE;
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C	Alarm_Error = ERR_AL_CHECK_FIO2		  			  */
		Alarm_Error = ERR_AL_CHECK_FIO2;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
/*%C	Alarm_Error = ERR_AL_CHECK_FIO2		  			  */
	  	Alarm_Error = ERR_AL_CHECK_FIO2;
		break;
	}
	return(Alarm_Error);
}


