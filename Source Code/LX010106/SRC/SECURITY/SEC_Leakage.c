/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Leakage.c                                             	  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            Management of the alarm leakage                               */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "SEC_Leakage.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_Leakage(void)
{
	e_DB_ALARMS_STATE AlarmLeakage =
								DB_AlarmStatusRead(ALARM_LEAKAGE_U16);
	e_DB_ALARMS_STATE AlarmDisconnection =
								DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);
    UWORD16 ValveDetected = 	DB_ControlRead(VALVE_DETECTED_U16);
	UWORD16 ComputedLeak = DB_ComputeRead(COMPUTED_LEAK_U16); 
	UWORD16 AdjustHighLeak = DB_CurrentRead(ADJUST_HIGH_LEAK_U16) * 10;
	UWORD16 HighLeakSelect = DB_CurrentRead(HIGH_LEAK_SELECT_U16);
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
	static UWORD16 LeakCounter = 0;
	static e_VentilState MemoState = VEN_VENTIL_DISABLE;


	switch(AlarmLeakage)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :

/*%C 	The alarm is detected if the computed leak is higher    */
/*%C 	than Adjust leak										*/
		if ((ComputedLeak > AdjustHighLeak)
		&& (HighLeakSelect == TRUE)
		&& (AlarmDisconnection < ALARM_TRUE))
		{
		/*%C		Alarm is turned to Detected & stored */
			DB_AlarmStatusWrite(ALARM_LEAKAGE_U16,
									  ALARM_DETECTED);
			LeakCounter = 0;
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					               */
/******************************************************************************/
	case ALARM_DETECTED :

		if ((ComputedLeak <= AdjustHighLeak)
		|| (HighLeakSelect == FALSE)
		|| (AlarmDisconnection >= ALARM_TRUE))
		{
/*%C 		Alarm is turned to false  */
			DB_AlarmStatusWrite(ALARM_LEAKAGE_U16, ALARM_FALSE);
		}

		else if ( (VentilState != VEN_EXHALATION)
	  			&& (MemoState == VEN_EXHALATION)
				&& (LeakCounter < 3) )
		{
			LeakCounter = LeakCounter + 1;
		}

	    if(LeakCounter == 3)
		{
/*%C  	Alarm is turned to True & stored with its associated event */
			DB_AlarmStatusWrite(ALARM_LEAKAGE_U16,
									  ALARM_TRUE);
			DB_EventMngt(EVENT_AL_LEAKAGE );
/*%C        Updating priority register    */
            // Create a high priority alarm for Max Leak Alarm                                    */
            SEC_High_Priority_3 = SEC_High_Priority_3 | 0x0002;
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State												*/
/******************************************************************************/
	case ALARM_TRUE :
/*%C 	The following state ,"ALARM_DISPLAYED", is written by HMI module. */
/*%C  So there is no action to do .*/
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                              */
/******************************************************************************/
	case ALARM_DISPLAYED	:
		if ((ComputedLeak <= AdjustHighLeak)
		|| (HighLeakSelect == FALSE)
		|| (AlarmDisconnection >= ALARM_TRUE))
		{
/*%C 		Alarm is turned to false & stored with associeted event */
			DB_AlarmStatusWrite(ALARM_LEAKAGE_U16,
									  ALARM_FALSE);
			DB_EventMngt(EVENT_AL_END_OF_LEAKAGE);
            // Deactivate the high priority alarm for Max Leak Alarm
/*%C 		Updating priority register */
            SEC_High_Priority_3 = SEC_High_Priority_3 & 0xFFFD;
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :
		Alarm_Error = ERR_AL_LEAKAGE;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
	  	Alarm_Error = ERR_AL_LEAKAGE;
		break;
	}
	/*%C  Up dating  ventil state */
	 	MemoState = VentilState;
	return(Alarm_Error);
}

