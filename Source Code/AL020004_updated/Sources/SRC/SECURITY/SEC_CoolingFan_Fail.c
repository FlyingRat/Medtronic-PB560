/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CoolingFan_Fail.c                                       	  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of Cooling fan default					      	  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "DB_PowerSupply.h"
#include "DB_Measurement.h"
#include "DB_Control.h"
#include "SEC_CoolFanAlarms.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_CoolingFan_Fail(void)
{
	UWORD16 TempSensorFailureFlag 	= DB_PowerSupply_Read(TEMP_SENSOR_FAILURE_FLAG) ;
	UWORD16 Failure3VFlag 		= DB_PowerSupply_Read(FAILURE_3V_FLAG);

	UWORD16 MeasureFanSpeed = DB_Measurement_Read(MEASURE_FAN_SPEED);

	UWORD16 FanSpeedSetpoint = DB_Control_Read(FAN_SPEED_SETPOINT);
	UWORD16 Delta = FanSpeedSetpoint / 100 ;
	Delta = Delta * FAN_SPEED_TOLERANCE ;
	
/*%C If the default is not detected :										  */ 
/*%C if FAN_SPEED > FAN_SPEED_SETPOINT - 20%  								  */
/*%C and FAN_SPEED < FAN_SPEED_SETPOINT + 20%  								  */
/*%C or TEMP_SENSOR_FAILURE_FLAG = TRUE										  */
/*%C or FAILURE_3V_FLAG = TRUE												  */
	
	if( 	(MeasureFanSpeed > FanSpeedSetpoint - Delta)
	  	&& (MeasureFanSpeed < FanSpeedSetpoint + Delta) 
		||	(TempSensorFailureFlag == TRUE )
		|| (Failure3VFlag == TRUE))
	{
/*%C 	Then a timer runs 													  */
		TIM_StartDecounter16(TIM_COOLING_FAN_FAIL,TIME_COOLING_FAN_FAIL);
	}
/*%C End if 																  */
/*%C If the timer is over 													  */
	if (TIM_ReadValue16(TIM_COOLING_FAN_FAIL)== 0)
	{
/*%C 	Then COOLING_FAN_FAILURE_FLAG = TRUE								  */
		DB_PowerSupply_Write(COOLING_FAN_FAILURE_FLAG,TRUE);
	}	
/*%C else if FAN_SPEED <= FAN_SPEED_SETPOINT + 20%  						  */
/*%C and FAN_SPEED >= FAN_SPEED_SETPOINT - 20%,  							  */
	else if ( (MeasureFanSpeed >= FanSpeedSetpoint - Delta)
			 && (MeasureFanSpeed <= FanSpeedSetpoint + Delta) )
	{
/*%C 	Then COOLING_FAN_FAILURE_FLAG = FALSE								  */
		DB_PowerSupply_Write(COOLING_FAN_FAILURE_FLAG,FALSE);
	}
/*%C End if 																  */
}
