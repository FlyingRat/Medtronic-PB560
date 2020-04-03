/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_EndOfBattery.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Management of End of battery  alarm      				              */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter :	Alarm_Error */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "DB_KeyboardEvent.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_PowerSupply.h"
#include "DB_Control.h"
#include "SEC_EndOfBattery.h"
#include "security_datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_EndOfBattery(void)
{
/*%C Alarm end of battery recovery from base			                          */
	e_DB_ALARMS_STATE AlarmEndOfBattery =
	DB_AlarmStatusRead(ALARM_END_OF_BATTERY_U16);
/*%C Alarm check supply recovery from base				                      */
	e_DB_ALARMS_STATE AlarmCheckSupply =
	DB_AlarmStatusRead(ALARM_CHECK_SUPPLY_U16); 
/*%C AC selected state recovery from base				                          */
	UWORD16 AC_Selected = DB_ControlRead(AC_SELECTED_U16);
/*%C Measure battery voltage recovery from base				                  */
	UWORD16 MeasureBatteryVoltage = DB_ComputeRead(MEASURE_BATTERY_VOLTAGE_U16);
/*%C Battery end state recovery from base				                          */
	UWORD16 BatteryEnd =    DB_PowerSupplyRead(BATTERY_END_U16);
/* Power type recovery from power supply base                                 */
	UWORD16 PowerType           = DB_PowerSupplyRead(POWER_TYPE_U16);

	// Alarm no battery state recovery from base                                
    e_DB_ALARMS_STATE AlarmNoBattery = DB_AlarmStatusRead(ALARM_NO_BATTERY_U16);

/*%C Alarm error declaration	 								                  */
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

    // Keep a history of the previous power type.
	static UWORD16 PreviousPowerType = AC;
	static UWORD16 PreviousAcSelected = TRUE;
	static e_DB_ALARMS_STATE PrevAlarmCheckSupply = ALARM_FALSE;


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

/*%C Check ALARM_END_OF_BATTERY_U16 state */
	switch (AlarmEndOfBattery)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
	    if (AlarmNoBattery < ALARM_TRUE)
		{		
			if ( ( (AlarmCheckSupply == ALARM_FALSE)
                   && (PowerType != NONE)
				   && (BatteryEnd == TRUE ) )
				 || ( (AlarmCheckSupply >= ALARM_TRUE)
					  && (MeasureBatteryVoltage <= cEND_BATTERY) ) )
			{
				DB_AlarmStatusWrite(ALARM_END_OF_BATTERY_U16,
									ALARM_DETECTED);
				TIM_StartDecounter(SEC_BAT_VERY_LOW_LEVEL,
								   TIME_BAT_VERY_LOW_LEVEL);
			}
        }
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 			              */
/******************************************************************************/
    case ALARM_DETECTED :
		if ( (AlarmCheckSupply != PrevAlarmCheckSupply)
		   ||(AlarmNoBattery > ALARM_FALSE)
		   ||((AlarmCheckSupply == ALARM_FALSE)
		     && (( BatteryEnd == FALSE )
			  || (PreviousPowerType != PowerType) )) 
		   ||((AlarmCheckSupply >= ALARM_TRUE)
			 && ((MeasureBatteryVoltage > cEND_BATTERY)
		      || (AC_Selected != PreviousAcSelected)))
		   )
		{
			DB_AlarmStatusWrite(ALARM_END_OF_BATTERY_U16,
								ALARM_FALSE);
			SEC_High_Priority_1= SEC_High_Priority_1& 0xFFEF;
			SEC_Low_Priority = SEC_Low_Priority & 0xFFEF;

            Alarm_Error = NO_ERR_AL;
            break;
		}
/*%C 	If the 100ms delay has been reached, then 							  */
		if (TIM_ReadDecounterValue(SEC_BAT_VERY_LOW_LEVEL) == 0)
		{
			DB_AlarmStatusWrite(ALARM_END_OF_BATTERY_U16,
								ALARM_TRUE);
			DB_EventMngt(EVENT_AL_END_OF_BATTERY);

			// If the battery is charging, then 
			// declare a medium priority alarm. Otherwise declare a 
			// high priority since the battery is lower than 3% of
			// battery life.
			if ( ((AlarmCheckSupply == ALARM_FALSE) && (PowerType == AC))
			  || ((AlarmCheckSupply >= ALARM_TRUE) && (AC_Selected == TRUE))
			   )
			{
			    // Declare a low priority for End of Battery alarm
				SEC_Low_Priority = SEC_Low_Priority | 0x0010;
			}
			else
			{
			    // Declare a high priority for End of battery alarm.
				SEC_High_Priority_1= SEC_High_Priority_1| 0x0010;
				
                // When there's no AC, remove the low battery alarm since this alarm 
				// is active.
				DB_AlarmStatusWrite(ALARM_LOW_BATTERY_U16, ALARM_FALSE);
				SEC_High_Priority_1= SEC_High_Priority_1& 0xFFF7;
			}
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C  The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  */
/*%C  So there is no action to do.											  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED    :
		if ((AlarmCheckSupply != PrevAlarmCheckSupply)	
		   ||(AlarmNoBattery > ALARM_FALSE)			  
		   ||((AlarmCheckSupply == ALARM_FALSE)
		     && (( BatteryEnd == FALSE )
		      || (PreviousPowerType != PowerType) )) 
		   ||((AlarmCheckSupply >= ALARM_TRUE)
			 && ((MeasureBatteryVoltage > cEND_BATTERY)
		      || (AC_Selected != PreviousAcSelected)))
		     )
		{
			DB_AlarmStatusWrite(ALARM_END_OF_BATTERY_U16,
								ALARM_FALSE);
			SEC_High_Priority_1= SEC_High_Priority_1& 0xFFEF;
			SEC_Low_Priority = SEC_Low_Priority & 0xFFEF;

		}

		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
		Alarm_Error = ERR_AL_END_OF_BATTERY;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
		Alarm_Error = ERR_AL_END_OF_BATTERY;
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

