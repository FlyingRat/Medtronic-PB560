/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckValvePressure.c                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C         Valve pressure Alarm management                                  */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "Security_Datas.h"
#include "SEC_CheckValvePressure.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckValvePressure(UWORD16 Delay)
{
/* Filter valve pressure recovery from base			                          */
	SWORD16 FilterValvePressure = (SWORD16) DB_ComputeRead(FILTER_VALVE_PRESSURE_S16);
/* Alarm check valve pressure recovery from base			                          */
	e_DB_ALARMS_STATE AlarmCheckValvePressure = 
							DB_AlarmStatusRead(ALARM_CHECK_VALVE_PRESSURE_U16);
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/* Ventil state recovery from base			                          */
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
/* Valve detected recovery from base			                          */
	UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);

	static e_VentilState MemoVentilState = VEN_VENTIL_DISABLE;
	static SWORD16 maxi = 0;
	static SWORD16 mini = 400;	

/* 	Filter valve pressure maxi and mini calculation */
/*	If we are in inspiration */
	if ( (VentilState == VEN_INSPIRATION_CONTROLED)
	  || (VentilState == VEN_INSPIRATION_TRIGGERED) )
	{
/*		maxi is updated */
		if (maxi < FilterValvePressure)
		{
			maxi = FilterValvePressure;
		}
	}
/*	If we are in exhalation */
	if (VentilState == VEN_EXHALATION)
	{
/*		mini is updated */
		if (mini > FilterValvePressure)
		{
			mini = FilterValvePressure;
		}
		if (mini < 0)
		{
			mini = 0;
		}
	}

	switch (AlarmCheckValvePressure)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                             */
/******************************************************************************/
		case ALARM_FALSE :
		{
/*%C		If the delta betwen min & max is lower than 1.0 mb  */
			if ( (VentilState != VEN_EXHALATION)
			  && (MemoVentilState == VEN_EXHALATION)
			  && (ValveDetected == TRUE) )
			{
				if (maxi - mini < 10)
				{
/*%C				Alarm is turned to detected, the default timer is started */
					DB_AlarmStatusWrite(ALARM_CHECK_VALVE_PRESSURE_U16,
											ALARM_DETECTED);
					TIM_StartDecounter(SEC_CHECK_VALVE_PRESSURE,
											Delay);
				}
			}
			Alarm_Error = NO_ERR_AL;
			break;
		}
/******************************************************************************/
/*%C	         					 "DETECTED" State 					               */
/******************************************************************************/
		case ALARM_DETECTED :
		{
/*%C     	If the delta betwen min & max is higher than 1.0 mb  */
			if (maxi - mini > 10)
			{
/*%C        	Alarm is turned to False */
				DB_AlarmStatusWrite(ALARM_CHECK_VALVE_PRESSURE_U16,
										ALARM_FALSE);
			}

/*%C     	When the default delay is reached */
			else if (TIM_ReadDecounterValue(SEC_CHECK_VALVE_PRESSURE) == 0)   
			{
/*%C        	Alarm is turned to TRUE, the priority register is Up dated,*/
/*%C        	the associated event is stored */
				DB_AlarmStatusWrite(ALARM_CHECK_VALVE_PRESSURE_U16,
										ALARM_TRUE);
				DB_EventMngt(EVENT_AL_CHECK_VALVE_PRESSURE);
				SEC_High_Priority_2 = SEC_High_Priority_2 | 0x1000;
			}
			Alarm_Error = NO_ERR_AL;
			break;
		}
/******************************************************************************/
/*%C	         					 "TRUE" State												*/
/******************************************************************************/
		case ALARM_TRUE :
		{
/*%C     	The following state ,"ALARM_DISPLAYED", is written by HMI module. */
/*%C     	So there is no action to do .*/
			Alarm_Error = NO_ERR_AL;
			break;
		}
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                              */
/******************************************************************************/
		case ALARM_DISPLAYED :
		{
/*%C     	If the delta betwen min & max is higher than 1.0 mb  */ 
			if (maxi - mini > 10)
			{
/*%C        	Alarm is turned to False */
				DB_AlarmStatusWrite(ALARM_CHECK_VALVE_PRESSURE_U16,
										ALARM_FALSE);
				SEC_High_Priority_2 = SEC_High_Priority_2 & 0xEFFF;
/*%C        	The event of end of alarm is stored */
				DB_EventMngt(EVENT_AL_END_CHECK_VALVE_PRESSURE);
			}

			Alarm_Error = NO_ERR_AL;
			break;
		}
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
/*%C	There is not cancellation for this alarm, so this state shall not be    */
/*%C	reached                                                                 */
		case ALARM_CANCELED :
		{
			Alarm_Error = ERR_AL_CHECK_VALVE_PRESSURE;
			break;
		}
/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
		default:
		{
			Alarm_Error = ERR_AL_CHECK_VALVE_PRESSURE;
			break;
		}
	}

/* 	If new exhalation is detected */   
	if ( (VentilState == VEN_EXHALATION) && (MemoVentilState != VEN_EXHALATION) )
	{
/*		mini is resetted */
		mini = maxi;
	}
/* 	If new inspiration is detected */   
	if ( ( VentilState != VEN_EXHALATION) && (MemoVentilState == VEN_EXHALATION) )
	{
/*		maxi is resetted */
		maxi = mini;
	}

	MemoVentilState = VentilState;
	return(Alarm_Error);
}

