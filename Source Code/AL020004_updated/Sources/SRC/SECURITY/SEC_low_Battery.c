/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_low_Battery.c                                              */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of Low battery default						      */
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
#include "DB_Control.h"
#include "SEC_LowBatAlarms.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_low_Battery(void)
{
	UWORD16 GaugeMinute = DB_PowerSupply_Read(GAUGE_MINUTE_U16);
	UWORD16 PowerType = DB_PowerSupply_Read(POWER_TYPE_U16);
	UWORD16 EndOfBattery = DB_PowerSupply_Read(END_OF_BATTERY_FLAG);
	UWORD16 GaugeAvalaible = DB_PowerSupply_Read(GAUGE_AVALAIBLE_U16);
	UWORD16 PerCentBat = DB_PowerSupply_Read(PER_CENT_BAT_U16);
	UWORD16 ComputeCapacityReadyFlag = 
							DB_Control_Read(COMPUTE_CAPACITY_READY_FLAG);
	
	// As per IEC 60601-1-11 Clause 8.4: A TECHNICAL ALARM CONDITION of at 
    // least LOW PRIORITY shall remain active until the INTERNAL ELECTRICAL 
    // POWER SOURCE is returned to a level that is above the ALARM LIMIT or 
    // until it is depleted.
		if ((ComputeCapacityReadyFlag == TRUE)
		&& (EndOfBattery == FALSE)
     	&& ((PerCentBat < LOW_BATTERY_DETECTION_PERCENTAGE_LEVEL)	
		|| ((GaugeMinute < LOW_BATTERY_DETECTION_MINUTE_LEVEL)	
		&&	(GaugeAvalaible == TRUE))))
	{
		DB_PowerSupply_Write(LOW_BATTERY_FLAG,TRUE);
	}
        // only perform this check when not on battery
        // battery gauge may flucuate when at the threshold level			 
	else if ( ((PowerType != BAT_SUPPLY) &&
               (ComputeCapacityReadyFlag == TRUE)&&
			   (EndOfBattery == FALSE) &&
               (PerCentBat >= LOW_BATTERY_DETECTION_PERCENTAGE_LEVEL)	
              )
			  || (EndOfBattery == TRUE) 				
			)
	{
		DB_PowerSupply_Write(LOW_BATTERY_FLAG,FALSE);
	}
}
