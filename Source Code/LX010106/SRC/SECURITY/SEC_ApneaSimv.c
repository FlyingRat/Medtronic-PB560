/******************************************************************************/
/*                                                                            */
/* Project N�  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ApneaSimv.c                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C     			Management of apnea alarm for Simv mode                   */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O *%O Output Parameter : Alarm_Error                                       */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "DB_Event.h"
#include "enum.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "Security_Datas.h"
#include "DB_KeyboardEvent.h"
#include "SEC_ApneaSimv.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR  SEC_ApneaSimv(void)
{
	
/* Alarm apnea recovery from alarm status base                                */
	e_DB_ALARMS_STATE AlarmApnea = DB_AlarmStatusRead(ALARM_APNEA_U16);
/* Apnea setting recovery from current base                                   */
	UWORD16 AdjustApnea = DB_CurrentRead(ADJUST_APNEA_U16);
/* Ventilation state recovery from control base                               */
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
/* Cancel request recovery from keyboard event base                           */
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
/* Uncancel command recovery from control base                                */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
/* Alarm error declaration							                          */
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/* Reset apnea counter								                          */
	static UWORD16 ResetApneaCpt = 0;
/* Apnea previous cycle								                          */
	static e_VentilState ApneaPreviousCycle = VEN_VENTIL_DISABLE;
/*%C Check ALARM_APNEA_U16 state 											  */
switch(AlarmApnea)
{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C 	The apnea decounter is launched every time in the FALSE state         */
		TIM_StartDecounter(SEC_APNEA,
								 AdjustApnea);
/*%C  ALARM_APNEA_U16 =  ALARM_DETECTED					 					  */
	 	DB_AlarmStatusWrite(ALARM_APNEA_U16,
	 							  ALARM_DETECTED);
/*%C Alarm_Error = NO_ERR_AL												  */
	Alarm_Error = NO_ERR_AL;
   break;

/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C If the apnea counter is over, then										  */
	if (TIM_ReadDecounterValue(SEC_APNEA) == 0)
	{
/*%C  ALARM_APNEA_U16 = ALARM_TRUE											  */
/*%C  Storage of the associated event										  */
/*%C  Updating of priority register for leds & buzzer 						  */
   	DB_AlarmStatusWrite(ALARM_APNEA_U16,
   							  ALARM_TRUE);
		DB_EventMngt(EVENT_AL_APNEA );
		SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | 0x0001;
 	}
/*%C Else if VENTIL_STATE_U16 = VEN_INSPIRATION_TRIGGERED and  				  */
/*%C ApneaPreviousCycle = VEN_EXHALATION, then 								  */
   else if((VentilState == VEN_INSPIRATION_TRIGGERED)
	  &&(ApneaPreviousCycle == VEN_EXHALATION))
   {
/*%C  ALARM_APNEA_U16 = ALARM_FALSE											  */
	 	DB_AlarmStatusWrite(ALARM_APNEA_U16,
	 							  ALARM_FALSE);
/*%C  Reset of apnea counter ResetApneaCpt									  */
  	   ResetApneaCpt = 0; 
   }
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL												  */
	Alarm_Error = NO_ERR_AL;
   break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 		  */
/*%C So there is no action to do.											  */
/*%C Alarm_Error = NO_ERR_AL												  */
	Alarm_Error = NO_ERR_AL;
	break;

/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C If VENTIL_STATE_U16 = VEN_INSPIRATION_TRIGGERED and  				  	  */
/*%C ApneaPreviousCycle = VEN_EXHALATION, then 								  */
	if ( (VentilState == VEN_INSPIRATION_TRIGGERED)
	  && (ApneaPreviousCycle == VEN_EXHALATION) )
	{
/*%C     Increasing  the counter of apnea cycle ResetApneaCpt				  */
	  	   ResetApneaCpt = ResetApneaCpt + 1;
	}
/*%C else if VENTIL_STATE_U16 = VEN_INSPIRATION_CONTROLED and  			  	  */
/*%C ApneaPreviousCycle = VEN_EXHALATION, then 								  */
   else if ( (VentilState == VEN_INSPIRATION_CONTROLED)
	      && (ApneaPreviousCycle == VEN_EXHALATION) )
	{
/*%C the reset apnea counter ResetApneaCpt is reset (set to 0) 				  */
      ResetApneaCpt = 0;
	}
/*%C End if		 															  */

/*%C If ResetApneaCpt >=  cNB_APNEA_CYCLE_SIMV, then 			  			  */	
	if (ResetApneaCpt >= cNB_APNEA_CYCLE_SIMV)
	{
/*%C 	ALARM_APNEA_U16 = ALARM_APNEA_U16									  */
		DB_AlarmStatusWrite(ALARM_APNEA_U16,
	   						  ALARM_FALSE );
/*%C	Associated event is stored 											  */
		DB_EventMngt(EVENT_AL_END_OF_APNEA );
/*%C  Reset of apnea counter ResetApneaCpt									  */
  	   ResetApneaCpt = 0;
/*%C  Updating of the priority register for leds & buzzer 					  */
		SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xFFFE;
	}
/*%C Else If KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE, then				  */
	else if (KeyboardDoublePulseInhibEvent == TRUE )
	{
/*%C	ALARM_APNEA_U16 = ALARM_CANCELED									  */
		DB_AlarmStatusWrite(ALARM_APNEA_U16,
								  ALARM_CANCELED);
/*%C  Updating of the priority register for leds & buzzer 					  */
		SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xFFFE;
	}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL												  */
	Alarm_Error = NO_ERR_AL;
	break;

/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :

/*%C If VENTIL_STATE_U16 = VEN_INSPIRATION_TRIGGERED and  			  	  	  */
/*%C ApneaPreviousCycle = VEN_EXHALATION, then 								  */
	if ( (VentilState == VEN_INSPIRATION_TRIGGERED)
     && (ApneaPreviousCycle == VEN_EXHALATION) )
	{
/*%C     Increasing  the counter of apnea cycle ResetApneaCpt				  */
	  	   ResetApneaCpt = ResetApneaCpt + 1;
	}
/*%C else if VENTIL_STATE_U16 = VEN_INSPIRATION_CONTROLED and  			  	  */
/*%C ApneaPreviousCycle = VEN_EXHALATION, then 								  */
   else if ( (VentilState == VEN_INSPIRATION_CONTROLED)
	      && (ApneaPreviousCycle == VEN_EXHALATION) )
	{
/*%C  the "reset apnea counter ResetApneaCpt is reset (set to 0) 			  */
		ResetApneaCpt = 0;
	}
/*%C End if 																  */

/*%C If ResetApneaCpt >= cNB_APNEA_CYCLE_SIMV, then 						  */	
	if (ResetApneaCpt >= cNB_APNEA_CYCLE_SIMV)
	{
/*%C  ALARM_APNEA_U16 = ALARM_FALSE 										  */
		DB_AlarmStatusWrite(ALARM_APNEA_U16,
	   						  ALARM_FALSE );
/*%C   Associated event is sent												  */
		DB_EventMngt(EVENT_AL_END_OF_APNEA );
/*%C  ResetApneaCpt is reseted												  */
		ResetApneaCpt = 0;
/*%C  Up dating of the priority register for leds & buzzer 					  */
		SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xFFFE;
	}
		/******************************************************************/
		/*		 				Reset of the "CANCELED" State             */
		/******************************************************************/
			 
/*%C Else if UNCANCEL_CMD_U16 = TRUE, then   								  */
	else if(UncancelCmd == TRUE)
	{
/*%C  ALARM_APNEA_U16 = ALARM_TRUE											  */
/*%C  Updating of priority register for leds & buzzer 						  */
   	DB_AlarmStatusWrite(ALARM_APNEA_U16,
   							  ALARM_TRUE);
		SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | 0x0001;
	}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL												  */
	Alarm_Error = NO_ERR_AL;
	break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C Alarm_Error = NO_ERR_AL												  */
	Alarm_Error = NO_ERR_AL;
	break;
	}
/*%C	End of check alarm state											  */
/*%C Updating the previous ventil state memory ApneaPreviousCycle  		  	  */
	ApneaPreviousCycle =  VentilState;

	return (Alarm_Error);
}
