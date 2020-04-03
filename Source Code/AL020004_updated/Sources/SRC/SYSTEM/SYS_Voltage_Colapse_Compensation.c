/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Voltage_Colapse_Compensation.c                             */
/*									      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Compute of battery capacity			      */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                      */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "DB_PowerSupply.h"
#include "DB_Measurement.h"
#include "SYS_Voltage_Colapse_Compensation.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SYS_Voltage_Colapse_Compensation(void) 
{
	UWORD16 MeasureVBatfitered = DB_Measurement_Read(VBAT_MEASURE_FILTERED);
	static UWORD16 BatteryVoltageMax = 0;
	static UWORD16 BatteryVoltageMin = 0;
	static UWORD16 FirstRun = TRUE;
	UWORD16 VoltageColapse = 0;
	
	if (FirstRun == TRUE)
	{
	 FirstRun = FALSE;
	 TIM_StartDecounter32(SYS_BATTERY_VOLTAGE_OBSERVATION_PERIOD
										, TIME_BATTERY_VOLTAGE_OBSERVATION_PERIOD);
		BatteryVoltageMax = MeasureVBatfitered;
		BatteryVoltageMin = MeasureVBatfitered;
	}
	// Storage of battery voltage colapse and reset for a new estimation. 
	if (TIM_ReadValue32(SYS_BATTERY_VOLTAGE_OBSERVATION_PERIOD) == 0)
   {
	   VoltageColapse = 	BatteryVoltageMax - BatteryVoltageMin;
		DB_PowerSupply_Write(BATTERY_VOLTAGE_COLAPSE,(UWORD16) VoltageColapse);
		BatteryVoltageMax = MeasureVBatfitered; 
		BatteryVoltageMin = MeasureVBatfitered; 
		TIM_StartDecounter32(SYS_BATTERY_VOLTAGE_OBSERVATION_PERIOD
										, TIME_BATTERY_VOLTAGE_OBSERVATION_PERIOD);
	}
	// Estimation of the battery voltage colapse during 30 sec.								
	else 
	{
		if (MeasureVBatfitered < BatteryVoltageMin)
		{
			BatteryVoltageMin = MeasureVBatfitered;
		}
		if (MeasureVBatfitered > BatteryVoltageMax)
		{
			BatteryVoltageMax = MeasureVBatfitered;
		}
	}											
									
}	