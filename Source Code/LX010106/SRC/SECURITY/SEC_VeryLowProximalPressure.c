/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_VeryLowProximalPressure.c 		                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           proximal pressure Offset Default		                      		*/
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
#include "SEC_VeryLowProximalPressure.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_VeryLowProximalPressure(void)
{
/* Technical very low proximal pressure recovery from base						   */
	UWORD16 TechAlarmVeryLowProximalPress = 
				DB_AlarmStatusRead(TECH_ALARM_VERY_LOW_PROXIMAL_PRESS_U16);
/* Measure patient pressure proximal pressure recovery from base 				   */
	SWORD16 MeasurePatientPressureProxi = 
				DB_ComputeRead(MEASURE_PATIENT_PRESSURE_PROXI_S16);

/*%C When the alarm is false and if the measured pressure is lower */
/*%C than - 10cmH2O, the alarm is turned to detected and stored */
	if ( (MeasurePatientPressureProxi < cVERY_NEGATIVE)
	  && (TechAlarmVeryLowProximalPress == ALARM_FALSE) )
	{
		DB_AlarmStatusWrite(TECH_ALARM_VERY_LOW_PROXIMAL_PRESS_U16,
		                    ALARM_DETECTED);
/*%C  Alarm validation delay start */
		TIM_StartDecounter(SEC_PROXI_CST,
		                   TIME_SEC_PROXI_CST);
	}
/*%C If the measured pressure is upper than - 10cmH2O */
/*%C and the alarm is'nt false, alarm is turned to false and stored */

	if ( (MeasurePatientPressureProxi > cVERY_NEGATIVE)
	  && (TechAlarmVeryLowProximalPress != ALARM_FALSE) )
	{
	   DB_AlarmStatusWrite(TECH_ALARM_VERY_LOW_PROXIMAL_PRESS_U16,
	                       ALARM_FALSE);
	}
/*%C When the alarm is always detected and the delay is over */
/*%C Alarm is turned to true and stored with its associated event */

	if ( (TIM_ReadDecounterValue(SEC_PROXI_CST) == 0)
	  && (TechAlarmVeryLowProximalPress == ALARM_DETECTED) ) 
	{
		DB_AlarmStatusWrite(TECH_ALARM_VERY_LOW_PROXIMAL_PRESS_U16,
		                    ALARM_TRUE);
   	DB_EventMngt(EVENT_ALT_VERY_LOW_PROXI_PRESS);
	}	
}