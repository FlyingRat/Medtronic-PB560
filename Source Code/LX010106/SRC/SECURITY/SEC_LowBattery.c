/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_LowBattery.c                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C              Management of Low battery level alarm                       */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Alarm_Error                                           */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES                               */
/******************************************************************************/
#include "DB_KeyboardEvent.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "DB_PowerSupply.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "SEC_LowBattery.h"
#include "security_datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_LowBattery(void)
{
/*%C Alarm end of battery recovery from base                                  */
	e_DB_ALARMS_STATE AlarmEndOfBattery =
	DB_AlarmStatusRead(ALARM_END_OF_BATTERY_U16);
/*%C Alarm low battery state recovery from base                               */
	e_DB_ALARMS_STATE AlarmLowBattery =
	DB_AlarmStatusRead(ALARM_LOW_BATTERY_U16);
/*%C Alarm check supply state recovery from base                              */
	e_DB_ALARMS_STATE AlarmCheckSupply =
	DB_AlarmStatusRead(ALARM_CHECK_SUPPLY_U16);    
/*%C Battery low state recovery from base                                     */
	UWORD16 BatteryLow = DB_PowerSupplyRead(BATTERY_LOW_U16);
/*%C AC selected state recovery from base                                     */
	UWORD16 AC_Selected = DB_ControlRead(AC_SELECTED_U16);
/*%C Battery voltage recovery from base                                       */
	UWORD16 MeasureBatteryVoltage  = 
	DB_ComputeRead(MEASURE_BATTERY_VOLTAGE_U16);
/*%C Alarm error declaration                                                  */
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

	/* Power type recovery from power supply base                                 */
	UWORD16 PowerType           = DB_PowerSupplyRead(POWER_TYPE_U16);

	// Alarm no battery state recovery from base                                
    e_DB_ALARMS_STATE AlarmNoBattery = DB_AlarmStatusRead(ALARM_NO_BATTERY_U16);

    // Keep a history of the previous power type.
	static UWORD16 PreviousPowerType = AC;
	static UWORD16 PreviousAcSelected = TRUE;
	static e_DB_ALARMS_STATE PrevAlarmCheckSupply = ALARM_FALSE;

	// low and Hi alarm battery indicators
	static UWORD16 LOW_LOWBAT = 0x0008;
	static UWORD16 HI_LOWBAT  = 0x0008;

	// Initialize the Previous history of the power type,
	// check supply and ac select states.
	static UWORD16 IsInitialize = FALSE;
	if (IsInitialize == FALSE)
	{
	   IsInitialize = TRUE;
       if (PowerType != NONE)
       {
	   PreviousPowerType = PowerType;
       }
	   PreviousAcSelected = AC_Selected;
	   PrevAlarmCheckSupply = AlarmCheckSupply;
	}

    // As per IEC 60601-1-11 Clause 8.4: A TECHNICAL ALARM CONDITION of at 
    // least LOW PRIORITY shall remain active until the INTERNAL ELECTRICAL 
    // POWER SOURCE is returned to a level that is above the ALARM LIMIT or 
    // until it is depleted.

	switch (AlarmLowBattery)
	{
/******************************************************************************/
/*%C                                  "FALSE" State                           */
/******************************************************************************/
	case ALARM_FALSE :
		if ((AlarmEndOfBattery < ALARM_TRUE) || (AlarmNoBattery < ALARM_TRUE))
		{
			if ( ( (AlarmCheckSupply == ALARM_FALSE)
                   && (PowerType != NONE)
				   && (BatteryLow == TRUE) )
				 || ( (AlarmCheckSupply >= ALARM_TRUE)
					  && (MeasureBatteryVoltage <= cLOW_BATTERY) ) )
			{
				DB_AlarmStatusWrite(ALARM_LOW_BATTERY_U16, ALARM_DETECTED);
				TIM_StartDecounter(SEC_BAT_LOW_LEVEL, TIME_BAT_LOW_LEVEL);
			}
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C                                  "DETECTED" State                        */
/******************************************************************************/
	case ALARM_DETECTED :
		if ((AlarmCheckSupply != PrevAlarmCheckSupply)
		    || ((AlarmCheckSupply == ALARM_FALSE)
			   && (( BatteryLow == FALSE )
				  || (PreviousPowerType != PowerType) )) 
			||((AlarmCheckSupply >= ALARM_TRUE)
			   && ((MeasureBatteryVoltage > cLOW_BATTERY)
				   || (AC_Selected != PreviousAcSelected)))
			|| (AlarmEndOfBattery > ALARM_FALSE)
			|| (AlarmNoBattery > ALARM_FALSE)
		   )
		{
			DB_AlarmStatusWrite(ALARM_LOW_BATTERY_U16, ALARM_FALSE);
            Alarm_Error = NO_ERR_AL;
            break;
		}
		if (TIM_ReadDecounterValue(SEC_BAT_LOW_LEVEL) == 0)
		{
			DB_AlarmStatusWrite(ALARM_LOW_BATTERY_U16, ALARM_TRUE);
			DB_EventMngt(EVENT_AL_LOW_BATTERY);

			// If the battery is charging, then 
			// declare a low priority alarm. Otherwise declare a 
			// high priority since the battery has low battery life.
			if ( ((AlarmCheckSupply == ALARM_FALSE) && (PowerType == AC))
				 || ((AlarmCheckSupply >= ALARM_TRUE) && (AC_Selected == TRUE))
			   )
			{
			    // Declare a low priority for the Low Battery alarm
                SEC_Low_Priority = SEC_Low_Priority | LOW_LOWBAT;
			}
			else
			{
			    // Declare a high priority for the Low Battery alarm
				SEC_High_Priority_1 = SEC_High_Priority_1 | HI_LOWBAT;
			}

		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C                                  "TRUE" State                            */
/******************************************************************************/
	case ALARM_TRUE :
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C                                  "DISPLAYED" State                       */
/******************************************************************************/
	case ALARM_DISPLAYED    :
		if ((AlarmCheckSupply != PrevAlarmCheckSupply)
		    || ((AlarmCheckSupply == ALARM_FALSE)
			   && (( BatteryLow == FALSE )
				 || (PreviousPowerType != PowerType) )) 
			||((AlarmCheckSupply >= ALARM_TRUE)
			   && ((MeasureBatteryVoltage > cLOW_BATTERY)
				   || (AC_Selected != PreviousAcSelected)))
	        || (AlarmEndOfBattery > ALARM_FALSE)
			|| (AlarmNoBattery > ALARM_FALSE)
		   )
		{
			DB_AlarmStatusWrite(ALARM_LOW_BATTERY_U16, ALARM_FALSE);

			SEC_High_Priority_1 = SEC_High_Priority_1 & (~HI_LOWBAT);
            SEC_Low_Priority = SEC_Low_Priority & (~LOW_LOWBAT);

		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C                                  "CANCELED" State                        */
/******************************************************************************/
	case ALARM_CANCELED :
		Alarm_Error = ERR_AL_LOW_BATTERY;
		break;

/******************************************************************************/
/*%C                                  DEFAULT                                 */
/******************************************************************************/
	default:
		Alarm_Error = ERR_AL_LOW_BATTERY;
		break;
	}

    // Do not save the NONE state because
    // it cannot be used to evaluate the alarm
    // conditions.
    if (PowerType != NONE)
    {
        PreviousPowerType = PowerType;
    }
	PreviousAcSelected = AC_Selected;
	PrevAlarmCheckSupply = AlarmCheckSupply;
	return(Alarm_Error);
}
