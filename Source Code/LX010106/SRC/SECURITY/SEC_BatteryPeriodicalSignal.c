/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_BatteryPeriodicalSignal.c                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C    management of the alarm Battery periodical signal                     */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Alarm_Error                                           */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_AlarmStatus.h"
#include "DB_PowerSupply.h"
#include "DB_Control.h"
#include "SEC_BatteryPeriodicalSignal.h"	  
#include "security_datas.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
 e_ALARM_ERROR SEC_BatteryPeriodicalSignal(void)
{
/* Alarm check supply recovery from base						              */
	e_DB_ALARMS_STATE AlarmCheckSupply 
										= DB_AlarmStatusRead(ALARM_CHECK_SUPPLY_U16);
/* Alarm periodical recovery from base							              */
   UWORD16 AlarmPeriodSignal 	= DB_AlarmStatusRead(ALARM_PERIODICAL_SIGNAL_U16);
/* AC selected state recovery from base						                  */
	UWORD16 ACSelected 		= DB_ControlRead(AC_SELECTED_U16);
/* Power type recovery from base									          */
	UWORD16 PowerType 			= DB_PowerSupplyRead(POWER_TYPE_U16);
/* Ventil state memorization										          */
	static e_VentilState Memo 	= VEN_VENTIL_DISABLE;
/* Ventil state recovery from base										      */
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);	
/* Ventil state recovery from base										      */
	static UWORD16 CycleCpt = 0;
/* Alarm error declaration													  */
 	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
		
/*%C Check ALARM_PERIODICAL_SIGNAL_U16 state 								  */
switch(AlarmPeriodSignal)			
{								 
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C If ALARM_CHECK_SUPPLY_U16 = ALARM_FALSE and POWER_TYPE_U16 = BATTERY, 	  */
/*%C Then 																	  */
   if ( (AlarmCheckSupply == ALARM_FALSE)
	  && (PowerType == BATTERY) )
	{
/*%C  	ALARM_PERIODICAL_SIGNAL_U16 = ALARM_TRUE 							  */
		DB_AlarmStatusWrite(ALARM_PERIODICAL_SIGNAL_U16,
								  ALARM_TRUE);
/*%C  	DISPLAY_BATTERY_U16 = TRUE											  */
		DB_ControlWrite(DISPLAY_BATTERY_U16,
		              TRUE);
/*%C 	VALIDATION_BIP_U16 = BIP_BATTERY_PERIODICAL							  */
		DB_ControlWrite(VALIDATION_BIP_U16,
			 			BIP_BATTERY_PERIODICAL);

/*%C 	5 min timer launch for periodical bip								  */
		TIM_StartMinuteDecounter(SEC_PERIODICAL_BIP,
								 TIME_PERIODICAL_BIP,
								 FALSE);
	}
/*%C End if 																  */
/*%C If ALARM_CHECK_SUPPLY_U16 >= ALARM_TRUE and AC_SELECTED_U16 = FALSE, then*/
   if ( (AlarmCheckSupply >= ALARM_TRUE)
     && (ACSelected == FALSE) )
	{
/*%C  ALARM_PERIODICAL_SIGNAL_U16 = ALARM_DETECTED							  */
		DB_AlarmStatusWrite(ALARM_PERIODICAL_SIGNAL_U16,
								  ALARM_DETECTED);
/*%C  Cycles counter CycleCpt initialization 								  */
		CycleCpt = 0;
/*%C  If VENTIL_STATE_U16 = VEN_VENTIL_DISABLE, then 						  */
		if (VentilState == VEN_VENTIL_DISABLE)
		{
/*%C     	Then starting delay of default 									  */
			TIM_StartDecounter(SEC_BAT_P_S_TIM,
		   					   TIME_BAT_P_S);
		}
/*%C	End if 																  */			   
 	}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */	
	Alarm_Error = NO_ERR_AL;
	break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C If ( ALARM_CHECK_SUPPLY_U16 >= ALARM_TRUE and AC_SELECTED_U16 = TRUE )   */
/*%C or ( ALARM_CHECK_SUPPLY_U16 < ALARM_TRUE and POWER_TYPE_U16 <> BATTERY ),*/
/*%C Then 																	  */
   if ( ( (AlarmCheckSupply >= ALARM_TRUE)
	  && (ACSelected == TRUE) )
	|| ( (AlarmCheckSupply < ALARM_TRUE)
	  && (PowerType != BATTERY) ) )
	{
/*%C  ALARM_PERIODICAL_SIGNAL_U16 = ALARM_FALSE 							  */
		DB_AlarmStatusWrite(ALARM_PERIODICAL_SIGNAL_U16,
								  ALARM_FALSE);
 	}
/*%C End if 																  */

/*%C If VENTIL_STATE_U16 = VEN_EXHALATION and  								  */ 
/*%C (Memo = VEN_INSPIRATION_CONTROLED or Memo == VEN_INSPIRATION_TRIGGERED ) */
/*%C Then 																	  */
   if ( (VentilState == VEN_EXHALATION) 
	  && ( (Memo == VEN_INSPIRATION_CONTROLED)
	    || (Memo == VEN_INSPIRATION_TRIGGERED) ) )
	{
/*%C  	Cycles counter CycleCpt is increased 								  */
		CycleCpt = CycleCpt + 1;
	}
/*%C End if 																  */
/*%C if ( timer is over and VENTIL_STATE_U16 = VEN_VENTIL_DISABLE ) or		  */
/*%C ( CycleCpt >= 2 and VENTIL_STATE_U16 <> VEN_VENTIL_DISABLE ), then		  */
   if ( ((TIM_ReadDecounterValue(SEC_BAT_P_S_TIM) == 0)
      && (VentilState == VEN_VENTIL_DISABLE)) 
    ||  ((CycleCpt >= 2)
      && (VentilState != VEN_VENTIL_DISABLE)) )
	{
/*%C	ALARM_PERIODICAL_SIGNAL_U16 = ALARM_TRUE							  */		
		DB_AlarmStatusWrite(ALARM_PERIODICAL_SIGNAL_U16,
								  ALARM_TRUE);
/*%C  	DISPLAY_BATTERY_U16 = TRUE 											  */
		DB_ControlWrite(DISPLAY_BATTERY_U16,
		              TRUE);
/*%C 	VALIDATION_BIP_U16 = BIP_BATTERY_PERIODICAL							  */
		DB_ControlWrite(VALIDATION_BIP_U16,
			 			BIP_BATTERY_PERIODICAL);
/*%C 	5 min timer launch for periodical bip								  */
		TIM_StartMinuteDecounter(SEC_PERIODICAL_BIP,
								 TIME_PERIODICAL_BIP,
								 FALSE);
	}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
	Alarm_Error = NO_ERR_AL;
	break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C If ( ALARM_CHECK_SUPPLY_U16 >= ALARM_TRUE and AC_SELECTED_U16 = TRUE )   */
/*%C or ( ALARM_CHECK_SUPPLY_U16 < ALARM_TRUE and POWER_TYPE_U16 <> BATTERY ),*/
/*%C Then 																	  */
   if ( ( (AlarmCheckSupply >= ALARM_TRUE)
	  && (ACSelected == TRUE) )
	|| ( (AlarmCheckSupply < ALARM_TRUE)
	  && (PowerType != BATTERY) ) )
	{
/*%C  ALARM_PERIODICAL_SIGNAL_U16 = ALARM_FALSE 							  */
		DB_AlarmStatusWrite(ALARM_PERIODICAL_SIGNAL_U16,
								  ALARM_FALSE);
/*%C  DISPLAY_BATTERY_U16 = FALSE 											  */
      DB_ControlWrite(DISPLAY_BATTERY_U16,
                      FALSE);
 	}
/*%C End if 																  */
/*%C If Periodical bip timer reached 0, then								  */
	if (TIM_ReadMinuteDecounterValue(SEC_PERIODICAL_BIP) == 0)
	{
/*%C 	VALIDATION_BIP_U16 = BIP_START_VENTIL								  */
		DB_ControlWrite(VALIDATION_BIP_U16,
			 			BIP_START_VENTIL); 
/*%C 	5 min timer launch for periodical bip								  */
		TIM_StartMinuteDecounter(SEC_PERIODICAL_BIP,
								 TIME_PERIODICAL_BIP,
								 FALSE);
	}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
	Alarm_Error = NO_ERR_AL;
	break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C return error code when this case is activated 							  */
/*%C Alarm_Error = ERR_AL_PERIODICAL_SIGNAL 								  */
	Alarm_Error = ERR_AL_PERIODICAL_SIGNAL;
	break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C return error code when this case is activated 							  */
/*%C Alarm_Error = ERR_AL_PERIODICAL_SIGNAL 								  */
  	Alarm_Error = ERR_AL_PERIODICAL_SIGNAL;
	break;
}
/*%C End of check alarm state 												  */
/*%C Updating the Memo Ventil state 										  */
	Memo = VentilState;

	return(Alarm_Error);
}





