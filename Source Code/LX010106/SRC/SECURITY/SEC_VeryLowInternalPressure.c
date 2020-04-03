/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_VeryLowInternalPressure.c 		                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Very Low internal pressure Offset Default                  		*/
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
#include "SEC_VeryLowInternalPressure.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_VeryLowInternalPressure(void)
{
	/* Technical very low internal pressure recovery from base	 				   */
	UWORD16 TechAlarmVeryLowInternalPress = 
					DB_AlarmStatusRead(TECH_ALARM_VERY_LOW_INTERNAL_PRESS_U16);
	/* Measure internal pressure pressure recovery from base  		 			   */
	SWORD16 MeasureInternalPressure = 
					DB_ComputeRead(MEASURE_INTERNAL_PRESSURE_S16);

/*%C When the alarm is still false and if the measured pressure is lower */
/*%C than -10 cmH2O, the alarm is turned to detected and stored */
	if ( (MeasureInternalPressure < cVERY_NEGATIVE)
	  && (TechAlarmVeryLowInternalPress == ALARM_FALSE) )
	{
		DB_AlarmStatusWrite(TECH_ALARM_VERY_LOW_INTERNAL_PRESS_U16,
		                    ALARM_DETECTED);
/*%C  Validation delay start */
		TIM_StartDecounter(SEC_INT_CST,
		                   TIME_SEC_INT_CST);		
	}
/*%C If the measured pressure is upper than -10cmH2O 								*/
/*%C and the alarm is'nt false, alarm is turned to false and stored */
	if ( (MeasureInternalPressure >= cVERY_NEGATIVE)
	  && (TechAlarmVeryLowInternalPress != ALARM_FALSE) )
	{
	   DB_AlarmStatusWrite(TECH_ALARM_VERY_LOW_INTERNAL_PRESS_U16,
	                       ALARM_FALSE);
	}
/*%C When the alarm delay is reached, the */
/*%C alarm is turned to true and stored with its associated event */
	if ( (TIM_ReadDecounterValue(SEC_INT_CST) == 0)
	  && (TechAlarmVeryLowInternalPress == ALARM_DETECTED) ) 
	{
		DB_AlarmStatusWrite(TECH_ALARM_VERY_LOW_INTERNAL_PRESS_U16,
		                    ALARM_TRUE);
   	DB_EventMngt(EVENT_ALT_VERY_LOW_INT_PRESS );
	}	
}