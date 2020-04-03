/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_End_Of_Battery.c                                           */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of end of battery default					      */
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
#include "SEC_EndBatAlarms.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_End_Of_Battery(void)
{
UWORD16 GaugeMinute = DB_PowerSupply_Read(GAUGE_MINUTE_U16);
UWORD16 PerCentBat = DB_PowerSupply_Read(PER_CENT_BAT_U16);
UWORD16 PowerType = DB_PowerSupply_Read(POWER_TYPE_U16);
UWORD16 GaugeAvalaible = DB_PowerSupply_Read(GAUGE_AVALAIBLE_U16);
UWORD16 ComputeCapacityReadyFlag = 
									DB_Control_Read(COMPUTE_CAPACITY_READY_FLAG);

	// As per IEC 60601-1-11 Clause 8.4: A TECHNICAL ALARM CONDITION of at 
    // least LOW PRIORITY shall remain active until the INTERNAL ELECTRICAL 
    // POWER SOURCE is returned to a level that is above the ALARM LIMIT or 
    // until it is depleted.
	if (   (ComputeCapacityReadyFlag == TRUE)
     	&& ((PerCentBat < END_OF_BATTERY_DETECTION_PERCENTAGE_LEVEL)	
		|| ((GaugeMinute < END_OF_BATTERY_DETECTION_MINUTE_LEVEL)	
		&&	(GaugeAvalaible == TRUE))))
	{
		DB_PowerSupply_Write(END_OF_BATTERY_FLAG,TRUE);
	}
    // only perform this check when not on battery
    // battery gauge may flucuate when at the threshold level			 
	else if ( ( PowerType != BAT_SUPPLY) &&
              (ComputeCapacityReadyFlag == TRUE) &&
     	      (PerCentBat >= END_OF_BATTERY_DETECTION_PERCENTAGE_LEVEL)	
		     )
	{
		DB_PowerSupply_Write(END_OF_BATTERY_FLAG,FALSE);
	}
}
