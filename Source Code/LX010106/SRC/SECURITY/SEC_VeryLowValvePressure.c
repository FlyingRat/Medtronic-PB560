/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_VeryLowValvePressure.c		 		                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Very Low Valve pressure Default		                  			*/
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
#include "DB_Event.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "Security_Datas.h"
#include "SEC_VeryLowValvePressure.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_VeryLowValvePressure(void)
{
/* Technical very low valve pressure alarm recovery from base                 */
	UWORD16 TechAlarmVeryLowValvePress = 
				DB_AlarmStatusRead(TECH_ALARM_VERY_LOW_VALVE_PRESS_U16);
/* Measure valve pressure recovery from base						                  */
	SWORD16 MeasureValvePressure = DB_ComputeRead(MEASURE_VALVE_PRESSURE_S16);
 
/*%C When the alarm is still false and if the measured pressure is lower */
/*%C than - 10cmH2O, the alarm is turned to detected and stored */
	if ( (MeasureValvePressure < cVERY_NEGATIVE)
	  && (TechAlarmVeryLowValvePress == ALARM_FALSE) )
	{
		DB_AlarmStatusWrite(TECH_ALARM_VERY_LOW_VALVE_PRESS_U16,
		                    ALARM_DETECTED);
/*%C 	Starting delay for validating default */
		TIM_StartDecounter(SEC_VALVE_CST,TIME_SEC_VALVE_CST);
	}
/*%C If the measured pressure is upper than - 10cmH2O */
/*%C and the alarm is'nt false, alarm is turned to false and stored */
	if ((MeasureValvePressure > cVERY_NEGATIVE)
		&& (TechAlarmVeryLowValvePress != ALARM_FALSE) )
	{
	   DB_AlarmStatusWrite(TECH_ALARM_VERY_LOW_VALVE_PRESS_U16,
	                       ALARM_FALSE);
	}
/*%C When the alarm is always detected and the delay is over */
/*%C Alarm is turned to true and stored with associated event */
	if ( (TIM_ReadDecounterValue(SEC_VALVE_CST) == 0)
	  && (TechAlarmVeryLowValvePress == ALARM_DETECTED) ) 
	{
		DB_AlarmStatusWrite(TECH_ALARM_VERY_LOW_VALVE_PRESS_U16,
		                    ALARM_TRUE);
   	DB_EventMngt(EVENT_ALT_VERY_LOW_VALVE_PRESS);
	}	
}