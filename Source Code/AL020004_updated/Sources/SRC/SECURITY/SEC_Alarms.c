/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Alarms.c                                                   */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of supply defaults							      */
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
#include "SEC_Alarms.h"

	
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_Alarms(void)
{
static UWORD16 FlagPostStart = FALSE;
static UWORD16 TimerLock = FALSE;
UWORD16 NoBatFlag = DB_PowerSupply_Read (NO_BAT_FLAG);
static UWORD16 PreviousBatFlag = FALSE;

/*%C Detection of Battery changing : */
/*%C if NO_BAT_FLAG = FALSE && PreviousBatFlag = TRUE, then  				  */

	if ( (NoBatFlag == FALSE)
	  && (PreviousBatFlag == TRUE) )
	{
/*%C 	The flags CHARGE_FAIL_FLAG, VOLT_OUT_OF_BOUNDS_FLAG,  				  */
/*%C 	CHARGE_TIME_TOO_LONG_FLAG, ABNORMAL_IBAT_FLAG, BAT_UNCHARGEABLE_FLAG  */
/*%C 	are reset, and the flag BAT_CHANGING_DETECTION is set.		 		  */
 
		DB_PowerSupply_Write(CHARGE_FAIL_FLAG,FALSE);
		DB_PowerSupply_Write(VOLT_OUT_OF_BOUNDS_FLAG,FALSE);
		DB_PowerSupply_Write(CHARGE_TIME_TOO_LONG_FLAG,FALSE);
		DB_PowerSupply_Write(ABNORMAL_IBAT_FLAG,FALSE);
		DB_PowerSupply_Write(BAT_UNCHARGEABLE_FLAG,FALSE);
		DB_PowerSupply_Write(BAT_CHANGING_DETECTION,TRUE);
	}
/*%C End if 																  */
	PreviousBatFlag = NoBatFlag;
	
	
/*%C If 3 sec temporization in order to wait the voltage etablishment 		  */
/*%C during the device start is not locked (TimerLock = FALSE), then 		  */
	if (TimerLock == FALSE)
	{
/*%C	Start the temporization, and TimerLock = TRUE						  */
		TIM_StartDecounter16(SEC_END_OF_START,TIME_SEC_VALID_MESURES); 
		TimerLock = TRUE;
	}
/*%C End if 																  */
/*%C if the device starting delay is over, then 							  */
	if(TIM_ReadValue16(SEC_END_OF_START)== 0)
	{
/*%C 	FlagPostStart = TRUE 												  */	
		FlagPostStart = TRUE;
	}
/*%C Else Alarms flag cancellation, during the start of the device. 		  */
	else
	{
		DB_PowerSupply_Write(END_OF_BATTERY_FLAG,FALSE);
		DB_PowerSupply_Write(LOW_BATTERY_FLAG,FALSE);
		DB_PowerSupply_Write(NO_BAT_FLAG,FALSE);
		DB_PowerSupply_Write(BAT_OPENED_FLAG,FALSE);
		DB_PowerSupply_Write(CHARGE_TEMP_FAIL_FLAG,FALSE);
		DB_PowerSupply_Write(DISCHARGE_TEMP_FAIL_FLAG,FALSE);
		DB_PowerSupply_Write(CHARGE_FAIL_FLAG,FALSE);
		DB_PowerSupply_Write(VOLT_OUT_OF_BOUNDS_FLAG,FALSE);
		DB_PowerSupply_Write(FAILURE_5V_FLAG,FALSE);
		DB_PowerSupply_Write(FAILURE_3V_FLAG,FALSE);
		DB_PowerSupply_Write(FAILURE_24V_FLAG,FALSE);
		DB_PowerSupply_Write(FAILURE_MES_VACDC_FLAG,FALSE);
		DB_PowerSupply_Write(FAILURE_MES_VDC_FLAG,FALSE);
		DB_PowerSupply_Write(COOLING_FAN_FAILURE_FLAG,FALSE);
		DB_PowerSupply_Write(BAT_UNCHARGEABLE_FLAG,FALSE);
		DB_PowerSupply_Write(CHARGE_TIME_TOO_LONG_FLAG,FALSE);
		DB_PowerSupply_Write(ABNORMAL_IBAT_FLAG,FALSE);
		DB_PowerSupply_Write(TEMP_SENSOR_FAILURE_FLAG,FALSE);
		DB_PowerSupply_Write(AMBIENT_TEMP_TOO_HIGH,FALSE);
		DB_PowerSupply_Write(UNKNOWN_BATTERY_FLAG,FALSE);
		DB_PowerSupply_Write(COMMUNICATION_FAILURE_FLAG,FALSE);
	}
/*%C End if 																  */
/*%C If the device is started, i.e FlagPostStart = TRUE 					  */
	if (FlagPostStart == TRUE)
	{
/*%C 	Then the alarms survey is launched 									  */
		SEC_End_Of_Battery();
		SEC_low_Battery();
		SEC_24V_Fail();
		SEC_3V_Fail();
		SEC_5V_Fail();
		SEC_Measure_VACDC_Fail();
		SEC_Measure_VDC_Fail();
		SEC_Abnormal_IBat();
		SEC_Bat_Opened();
		SEC_Battery_Unchargeable();
		SEC_Charge_Discharge_Fail();
		SEC_Charge_Fail();
		SEC_Charge_Time_Too_Long();
		SEC_CoolingFan_Fail();
		SEC_Measures_Out_Of_Bounds();
		SEC_No_Battery();
		SEC_Temp_Sensor_Failure();
		SEC_Ambient_Temp_Too_High();
		SEC_UnknownBattery();
		SEC_CommFail();
	}
/*%C End if 																  */
}
