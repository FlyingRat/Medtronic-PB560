/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : FAN_Driving_Launch.c                                      	  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                        Cooling fan driving								  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "p18f6622.h"
#include "typedef.h"
#include "define.h"
#include "IO_Declare.h"
#include "enum.h"
#include "DB_PowerSupply.h"
#include "DB_Control.h"
#include "DB_Measurement.h"
	#define DECLARATION_FAN_DATA
#include "FAN_Data.h"
#include "FAN_Driving_Launch.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void FAN_Driving_Launch(void)
{

/******************************************************************************/
/*%C Variables 																  */
/******************************************************************************/
	
	/*%C Temperature */
	SWORD16 TempAmb 				= (SWORD16)DB_Measurement_Read(TEMP_AMB) ;
	SWORD16 BatteryTemp 			= (SWORD16)DB_Measurement_Read(BATTERY_TEMP) ;

	UWORD16 TempSensorFailureFlag 	= DB_PowerSupply_Read(TEMP_SENSOR_FAILURE_FLAG) ;
	UWORD16 Failure3VFlag 		= DB_PowerSupply_Read(FAILURE_3V_FLAG);

	UWORD16 MaintenanceControl = DB_Control_Read(MAINTENANCE_CONTROL) ;
	UWORD16 CalibrationMode 	= DB_PowerSupply_Read(CALIBRATION_MODE) ;
	UWORD16 MaintenanceMode 	= DB_PowerSupply_Read(MAINTENANCE_MODE);

	UWORD16 FanSpeed = 0 ;
	UWORD16 FanSetPointAmbiant = 0 ;
	UWORD16 FanSetPointBattery = 0 ;

	static UWORD16 FanSetPoint = 4000 ;


/******************************************************************************/
/*%C Compute consigne 								   						  */
/******************************************************************************/

/*%C Compute Ratio Speed Temp with Ambient temperature sensor				  */
	UWORD16 Temp_To_RpmAmb = (UWORD16)	(
													((((UWORD32)FAN_TR_MAX -(UWORD32)FAN_TR_MIN)*10000) 		
											 		/(TEMP_AMB_MAX - TEMP_AMB_MIN)
													)/100
													);

/*%C Compute Ratio Speed Temp with battery temperature sensor				  */
	UWORD16 Temp_To_RpmBat = (UWORD16) 	(
													((((UWORD32)FAN_TR_MAX - (UWORD32)FAN_TR_MIN)*10000)		
													/(TEMP_BAT_MAX - TEMP_BAT_MIN)
													)/100
													);

/*%C If TEMP_AMB > TEMP_AMB_MAX then TEMP_AMB = TEMP_AMB_MAX			 	  */
	if(TempAmb >= TEMP_AMB_MAX)
	{
		TempAmb = TEMP_AMB_MAX ; 
	}
/*%C Else If TEMP_AMB < TEMP_AMB_MIN then TEMP_AMB = TEMP_AMB_MIN			  */
	else if (TempAmb <= TEMP_AMB_MIN)
	{
		TempAmb = TEMP_AMB_MIN ;
	}
	else
	{
		/*%C No Function */
	}
/*%C End if 																  */
/*%C If BATTERY_TEMP > TEMP_BAT_MAX then BATTERY_TEMP = TEMP_BAT_MAX	  	  */
	if(BatteryTemp >= TEMP_BAT_MAX)
	{
		BatteryTemp = TEMP_BAT_MAX ; 
	}
/*%C Else If BATTERY_TEMP < TEMP_BAT_MIN then BATTERY_TEMP = TEMP_BAT_MIN	  */
	else if (BatteryTemp <= TEMP_BAT_MIN)
	{
		BatteryTemp = TEMP_BAT_MIN ;
	}
	else
	{
		/*%C No Function */
	}
/*%C End if 																  */
/*%C Compute FanSetPoint with Ambiant Sensor and Battery Sensor 			  */
	FanSetPointAmbiant = (UWORD16)(FAN_TR_MIN 
											+(((TempAmb - TEMP_AMB_MIN) * (UWORD32)Temp_To_RpmAmb)/100)
											);

	FanSetPointBattery = (UWORD16)( 
											FAN_TR_MIN 
											+(((BatteryTemp - TEMP_BAT_MIN)*(UWORD32)Temp_To_RpmBat)/100)
											);
		

/*%C If Ambiant temp is too high than Battery Temp, compute FanSetPoint		  */
/*%C with Ambiant Temp sensor												  */
/*%C Else if Battery Temp is too high than Ambiant Temp, compute 			  */
/*%C FanSetPoint with Battery Temp sensor									  */
	
	if(FanSetPointAmbiant >= FanSetPointBattery )
	{
		FanSetPoint = (FanSetPoint + FanSetPointAmbiant*2) / 3 ;
	}
	else 
	{
		FanSetPoint = (FanSetPoint + FanSetPointBattery*2) / 3 ;
	}
/*%C End if 	
															  */
	/*FanSetPoint saturation*/
	if(FanSetPoint<4000)FanSetPoint=4000;
	

/******************************************************************************/
/*%C Allows interruption 													  */
/******************************************************************************/
	FAN_Sampling();


/******************************************************************************/
/*%C Start Regulation 														  */
/******************************************************************************/
/*%C If MaintenanceControl = FALSE 											  */
	if(MaintenanceControl == FALSE)
	{
/*%C 	Then if MaintenanceMode = TRUE and CalibrationMode = TRUE			  */
		if ((MaintenanceMode == TRUE)
			&& (CalibrationMode == TRUE))
		{
/*%C Then Stop the FAN when a calibration is asked on the CPU				  */
			PWM_CMD_VENTIL = 0;
		}
/*%C	Else 																  */
		else
		{
/*%C 		If Temp_Sensor_Failure_Flag = TRUE or Failure3VFlag = TRUE		  */
			if (	(TempSensorFailureFlag == TRUE )
				|| (Failure3VFlag == TRUE))
			{	
/*%C 			Then Maximum speed for Fan setpoint							  */
				PWM_CMD_VENTIL = CMD_FAN_MAX;
			}
			else 
			{
				DB_Control_Write(FAN_SPEED_SETPOINT, FanSetPoint);
/*%C 			Else Update of measure speed fan in the data base			  */
				FanSpeed = DB_Measurement_Read(MEASURE_FAN_SPEED);
/*%C 			result of regulation is applied to the Output 				  */
				PWM_CMD_VENTIL = FAN_Loop_Controller(FanSetPoint,FanSpeed);
			}
/*%C		End if 															  */
		}
/*%C	End if 																  */
	}
	else
	{
/*%C Maintenance control													  */
	}
/*%C End if 																  */
}
