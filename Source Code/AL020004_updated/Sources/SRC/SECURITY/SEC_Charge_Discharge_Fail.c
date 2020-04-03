/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Charge_Discharge_Fail.c                                    */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of Charge & discharge default				      */
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
#include "SEC_ChargeDischAlarms.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_Charge_Discharge_Fail(void)
{
	UWORD16 VbatMeasureFiltered 	= DB_Measurement_Read(VBAT_MEASURE_FILTERED);
	UWORD16 Power_Type				= DB_PowerSupply_Read(POWER_TYPE_U16);
	UWORD16 InitBatState 			= DB_Control_Read(INIT_BAT_STATE);
	UWORD16 ChargeBatState 			= DB_Control_Read(CHARGE_BAT_STATE);

	SWORD16 BatteryTemp = (SWORD16)DB_Measurement_Read(BATTERY_TEMP);
	
	

/******************************************************************************/
/*%C CHARGE TEMP FAIL 												          */
/******************************************************************************/
/*%C Test the battery temperature :			 								  */
/*%C If (BATTERY_TEMP < BATTERY_NO_CHARGE_MIN_TEMP_LEVEL					  */
/*%C or BATTERY_TEMP > BATTERY_NO_CHARGE_MAX_TEMP_LEVEL)				      */
/*%C and ( INIT_BAT_STATE = TRUE										      */
/*%C or CHARGE_BAT_STATE = TRUE	)									  		  */
	if (	((BatteryTemp <  BATTERY_NO_CHARGE_MIN_TEMP_LEVEL)
	   ||	(BatteryTemp > BATTERY_NO_CHARGE_MAX_TEMP_LEVEL))
		&&	((InitBatState == TRUE)
		||	(ChargeBatState == TRUE)))
	{
/*%C 	Then CHARGE_TEMP_FAIL_FLAG = TRUE									  */	
		DB_PowerSupply_Write(CHARGE_TEMP_FAIL_FLAG,TRUE);
	}
	
/*%C else if (BATTERY_TEMP > BATTERY_NO_CHARGE_MIN_TEMP_LEVEL				  */
/*%C and BATTERY_TEMP < BATTERY_NO_CHARGE_MAX_TEMP_LEVEL)				 	  */
/*%C or POWER_TYPE != AC_SUPPLY												  */
/*%C or BATTERY_TEMP < BATTERY_ABSENT_TEMP_LEVEL							  */
	else if (	((BatteryTemp > BATTERY_NO_CHARGE_MIN_TEMP_LEVEL)
				&&	(BatteryTemp < BATTERY_NO_CHARGE_MAX_TEMP_LEVEL))
				||	(Power_Type != AC_SUPPLY)
				||	(BatteryTemp < BATTERY_ABSENT_TEMP_LEVEL))
	{
/*%C 	Then CHARGE_TEMP_FAIL_FLAG = FALSE 		 							  */
		DB_PowerSupply_Write(CHARGE_TEMP_FAIL_FLAG,FALSE);
	}

	else
	{
		/*%C No Function */
	}
/*%C End if 																  */

/******************************************************************************/
/*%C DISCHARGE TEMP FAIL 										  			  */
/******************************************************************************/
/*%C Test battery temperature 						  						  */
/*%C if ( VBAT_MEASURE_FILTRED >  TENSION_BAT_RETURN_LEVEL 					  */
/*%C and (BATTERY_TEMP < BATTERY_NO_DISCHARGE_MIN_TEMP_LEVEL				  */
/*%C or BATTERY_TEMP > BATTERY_NO_DISCHARGE_MAX_TEMP_LEVEL) )				  */
/*%C and Power_Type = BAT_SUPPLY,											  */
	if ( 		((VbatMeasureFiltered > TENSION_BAT_RETURN_LEVEL)
	  		&& ((BatteryTemp < BATTERY_NO_DISCHARGE_MIN_TEMP_LEVEL)
	    	|| (BatteryTemp > BATTERY_NO_DISCHARGE_MAX_TEMP_LEVEL)))
			&&	(Power_Type ==  BAT_SUPPLY))
	{ 
/*%C 		Then DISCHARGE_TEMP_FAIL_FLAG = TRUE    						  */
			DB_PowerSupply_Write(DISCHARGE_TEMP_FAIL_FLAG,TRUE);
	}

/*%C else if (BATTERY_TEMP > BATTERY_NO_DISCHARGE_MIN_TEMP_LEVEL			  */
/*%C and BATTERY_TEMP < BATTERY_NO_DISCHARGE_MAX_TEMP_LEVEL)				  */
/*%C or POWER_TYPE != BAT_SUPPLY											  */
	else if (	((BatteryTemp > BATTERY_NO_DISCHARGE_MIN_TEMP_LEVEL)
		    	&&	(BatteryTemp < BATTERY_NO_DISCHARGE_MAX_TEMP_LEVEL))
				||	(Power_Type !=  BAT_SUPPLY))
	{
/*%C 	Then DISCHARGE_TEMP_FAIL_FLAG = FALSE    							  */
		DB_PowerSupply_Write(DISCHARGE_TEMP_FAIL_FLAG,FALSE);
	}
	else
	{
		/*%C No Function */
	}
/*%C End if 																  */
}
