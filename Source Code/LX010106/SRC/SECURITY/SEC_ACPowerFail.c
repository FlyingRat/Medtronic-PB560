/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ACPowerFail.c                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Management of Loss AC Power alarm (Checking requiered)                 */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter :	Alarm_Error                                           */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_KeyboardEvent.h"
#include "DB_Event.h"
#include "DB_PowerSupply.h"
#include "SEC_ACPowerfail.h"
#include "Timer_Data.h"
#include "Security_Datas.h"

/* locate security code to specific section */
#include "locate_security_code.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_ACPowerFail(void)
{
/* Alarm AC power fail recovery from alarm status base                        */
	e_DB_ALARMS_STATE AlarmACPowerFail =
		DB_AlarmStatusRead(ALARM_AC_POWER_FAIL_U16);
/* Alarm check supply fail recovery from alarm status base                    */
	e_DB_ALARMS_STATE AlarmCheckSupply =
		DB_AlarmStatusRead(ALARM_CHECK_SUPPLY_U16);
/* Power type recovery from power supply base                                 */
	UWORD16 PowerType 			= DB_PowerSupplyRead(POWER_TYPE_U16);
/* AC state recovery from control base                                        */
	UWORD16 ACSelected 		= DB_ControlRead(AC_SELECTED_U16);
/* Uncancel recovery from control base                                        */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
/* Ventil state recovery from control base                                    */
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
/* Ventil state memorization                                                  */
	static e_VentilState Memo 	= VEN_VENTIL_DISABLE;
/* Cancel request recovery from keyboard event base                           */
	UWORD16 KeyboardDoublePulseInhibEvent =
		DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
/* Inspiration cycle counter                                                  */
	static UBYTE CycleCnt = 0;
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
	static UWORD16 LOW_AC_POWER_FAIL = 0x0002;
	static UWORD16 MED_AC_POWER_FAIL = 0x0080;

/*%C Check ALARM_AC_POWER_FAIL_U16 state 									  */
	switch (AlarmACPowerFail)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C if ALARM_CHECK_SUPPLY_U16 = ALARM_FALSE and 	 						  */
/*%C (POWER_TYPE_U16 = BATTERY or POWER_TYPE_U16 = DC, then 				  */
		if ((AlarmCheckSupply == ALARM_FALSE)
			&& ((PowerType == DC)
				|| (PowerType == BATTERY)))
		{
/*%C  ALARM_AC_POWER_FAIL_U16 = ALARM_TRUE									  */
			DB_AlarmStatusWrite(ALARM_AC_POWER_FAIL_U16, ALARM_TRUE);
/*%C  the associated event is sent 											  */
			DB_EventMngt(EVENT_AL_AC_POWER_FAIL); 
/*%C  Set the low priority alarm; Updating of priority register 							   			  */
			SEC_Low_Priority = SEC_Low_Priority | LOW_AC_POWER_FAIL;
		}
/*%C else if ALARM_CHECK_SUPPLY_U16 >=  ALARM_TRUE and 				 		  */
/*%C AC_SELECTED_U16 = FALSE, then 											  */
		else if ((AlarmCheckSupply >= ALARM_TRUE)
				 && (ACSelected == FALSE))
		{
/*%C 	ALARM_AC_POWER_FAIL_U16 = ALARM_DETECTED							  */
			DB_AlarmStatusWrite(ALARM_AC_POWER_FAIL_U16, ALARM_DETECTED);
/*%C 	cycle counter CycleCnt reset										  */
			CycleCnt = 0;
/*%C 	if VENTIL_STATE_U16 = VEN_VENTIL_DISABLE  							  */
/*%C 	then the 5s delay validation decounter is launched 				 	  */
			if (VentilState ==  VEN_VENTIL_DISABLE)
			{
				TIM_StartDecounter(SEC_FAIL_AC_TIM, TIME_FAIL_AC);
			}
/*%C 	End if																  */
		}
/*%C End if																	  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C if ( ALARM_CHECK_SUPPLY_U16 = ALARM_FALSE and 	 			   		  	  */
/*%C POWER_TYPE_U16 = AC ) or (ALARM_CHECK_SUPPLY_U16 <> ALARM_FALSE and      */
/*%C AC_SELECTED_U16 = TRUE, then 											  */
	if ( ( (AlarmCheckSupply == ALARM_FALSE)
			&& (PowerType == AC))
	  || ( (AlarmCheckSupply != ALARM_FALSE)
	    && (ACSelected == TRUE) ) )
		{
/*%c  ALARM_AC_POWER_FAIL_U16 = ALARM_FALSE									  */
			DB_AlarmStatusWrite(ALARM_AC_POWER_FAIL_U16, ALARM_FALSE);
/*%C  Clear Medimum and Low priority alarm; Up dating of priority register 										  */
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & (~MED_AC_POWER_FAIL);
			SEC_Low_Priority = SEC_Low_Priority & (~LOW_AC_POWER_FAIL);
		}
/*%C Else, 																	  */
		else
		{
/*%C  if VENTIL_STATE_U16 <> VEN_VENTIL_DISABLE  and						  */
/*%C  ( VENTIL_STATE_U16 = VEN_EXHALATION and 								  */
/*%C  ( Memo = VEN_INSPIRATION_CONTROLED or Memo = VEN_INSPIRATION_TRIGGERED) */
			if ((VentilState != VEN_VENTIL_DISABLE)
				&& ((VentilState == VEN_EXHALATION)
					&& ((Memo == VEN_INSPIRATION_CONTROLED)
						||  (Memo == VEN_INSPIRATION_TRIGGERED))))
			{
/*%C 	Then increasing CycleCnt				   							  */
				CycleCnt = CycleCnt + 1;
			}
/*%C 	End if 																  */
/*%C 	If  (VENTIL_STATE_U16 = VEN_VENTIL_DISABLE and delay reached  )       */
/*%C	or ( VENTIL_STATE_U16 = VEN_VENTIL_DISABLE and CycleCnt > 2 )	 	  */
			if (((VentilState == VEN_VENTIL_DISABLE)
				 && (TIM_ReadDecounterValue(SEC_FAIL_AC_TIM) == 0))
				|| ((VentilState != VEN_VENTIL_DISABLE)
					&& (CycleCnt >= 2)))
			{
/*%C 	Then ALARM_AC_POWER_FAIL_U16 = ALARM_TRUE						      */
				DB_AlarmStatusWrite(ALARM_AC_POWER_FAIL_U16, ALARM_TRUE);
/*%C 		the associated event is sent 									  */
				DB_EventMngt(EVENT_AL_AC_POWER_FAIL);
/*%C 		Set medium priority alarm; Priority register updating										  */
				SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | MED_AC_POWER_FAIL;
			}
/*%C 	End if 																  */
		}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State		  					  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 	 	  */
/*%C So there is no action to do .											  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C if ( ALARM_CHECK_SUPPLY_U16 = ALARM_FALSE and 	 			   		  	  */
/*%C POWER_TYPE_U16 = AC ) or (ALARM_CHECK_SUPPLY_U16 <> ALARM_FALSE and      */
/*%C AC_SELECTED_U16 = TRUE, then 											  */
	if ( ( (AlarmCheckSupply == ALARM_FALSE)
			&& (PowerType == AC))
	  || ( (AlarmCheckSupply != ALARM_FALSE)
       && (ACSelected == TRUE) ) )
		{
			/*%C  ALARM_AC_POWER_FAIL_U16 = ALARM_FALSE									  */
			DB_AlarmStatusWrite(ALARM_AC_POWER_FAIL_U16, ALARM_FALSE);
			/*%C  the associated event is sent 											  */
			DB_EventMngt(EVENT_AC_RETURN);
			/*%C  Clear medium and low priority alarms; Up dating of priority register 	  */
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & (~MED_AC_POWER_FAIL);
			SEC_Low_Priority = SEC_Low_Priority & (~LOW_AC_POWER_FAIL);
		}

/*%C Else if KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE 					  */
		else if (KeyboardDoublePulseInhibEvent == TRUE)
		{
/*%C Then ALARM_AC_POWER_FAIL_U16 = ALARM_CANCELED 							  */
			DB_AlarmStatusWrite(ALARM_AC_POWER_FAIL_U16, ALARM_CANCELED);
/*%C Updating of priority register 											  */
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & (~MED_AC_POWER_FAIL);
			// Also remove Low Priority
			SEC_Low_Priority = SEC_Low_Priority  & (~LOW_AC_POWER_FAIL);
		}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C if ( ALARM_CHECK_SUPPLY_U16 = ALARM_FALSE and 	 			   		  	  */
/*%C POWER_TYPE_U16 = AC ) or (ALARM_CHECK_SUPPLY_U16 <> ALARM_FALSE and      */
/*%C AC_SELECTED_U16 = TRUE, then 											  */
		if (((AlarmCheckSupply == ALARM_FALSE)
			 && (PowerType == AC))

			|| ((AlarmCheckSupply != ALARM_FALSE)
				&& (ACSelected == TRUE)))
		{
/*%C  ALARM_AC_POWER_FAIL_U16 = ALARM_FALSE									  */
			DB_AlarmStatusWrite(ALARM_AC_POWER_FAIL_U16, ALARM_FALSE);
/*%C  the associated event is sent 											  */
			DB_EventMngt(EVENT_AC_RETURN);
		}


		/******************************************************************/
		/*		 				Reset of the "CANCELED" State             */
		/******************************************************************/

/*%C Else If UNCANCEL_CMD_U16 = TRUE, then 								  	  */
		else if (UncancelCmd == TRUE)
		{
/*%C  ALARM_AC_POWER_FAIL_U16 = ALARM_TRUE									  */
/*%C  Up dating of priority register for leds & buzzer 						  */
			DB_AlarmStatusWrite(ALARM_AC_POWER_FAIL_U16, ALARM_TRUE);

			if (AlarmCheckSupply != ALARM_FALSE)
			{
				SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | MED_AC_POWER_FAIL;
			}
            else if ( (PowerType == DC) || (PowerType == BATTERY) ) 
            {
				SEC_Low_Priority = SEC_Low_Priority | LOW_AC_POWER_FAIL;
			}

		}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C Alarm_Error = ERR_AL_AC_POWER_FAIL 									  */
		Alarm_Error = ERR_AL_AC_POWER_FAIL;
		break;
	}
/*%C End of Check Alarm state												  */
/*%C Updating the Memo Ventil state 										  */
	Memo = VentilState;

	return (Alarm_Error);
}

