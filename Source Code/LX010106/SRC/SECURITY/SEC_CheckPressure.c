/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckPressure.c                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C         Management of check pressure alarm                               */
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
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "Security_Datas.h"
#include "SEC_CheckPressure.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckPressure(UWORD16 Delay)
{
    SWORD16 CheckPressAutorization = TRUE;
/* Alarm check pressure recovery from base 									  */
  	e_DB_ALARMS_STATE AlarmCheckPressure =
								DB_AlarmStatusRead(ALARM_CHECK_PRESSURE_U16);
/* Alarm Disconnection recovery from base 									  */
	e_DB_ALARMS_STATE AlarmDisconnection =
								DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);
/* Internal pressure flat signal recovery from base 						  */
    UWORD16 FlatInt = DB_ControlRead(FLAT_INT_U16);

	UWORD16 HighPressureExhalationDetected = (UWORD16)DB_ControlRead(HIGH_PRESSURE_EXHALATION_DETECTED_U16);

/* Alarm error declaration			 										  */
  	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;



/*%C  If ALARM DISCONNECTION >= ALARM_TRUE, then 					      */  
	if  (AlarmDisconnection >= ALARM_TRUE) 
	{
/*%C	Lauch delay timer of CHECK PRESSURE Alarm to prevent from 			  */
/*%C	occuring abusively right after DISCONNECTION ALARM stop.  			  */
	  	TIM_StartDecounter(SEC_CHECK_PRESS,Delay);
	}

/*%C  If ALARM DISCONNECTION < ALARM_DETECTED, then 				    	  */  
	if  (AlarmDisconnection < ALARM_DETECTED) 
	{ 
/*%C	Disconnection observation timer runs 						 		  */
		TIM_StartDecounter(SEC_CHECK_PRESS2,Delay - 1000);
	}
/*%C End if																	  */  	
/*%C If Disconnection observation timer reched delay, then					  */
	if (TIM_ReadDecounterValue(SEC_CHECK_PRESS2) == 0)
	{ 
/*%C  CheckPressAutorization = FALSE 										  */	
		CheckPressAutorization = FALSE;
	}
	else
	{ 
/*%C Else CheckPressAutorization = TRUE									  */
		CheckPressAutorization = TRUE;
	}
/*%C End if



 																  */
/*%C Check ALARM_CHECK_PRESSURE_U16 state 									  */
 	switch(AlarmCheckPressure)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C Check pressure timer runs												  */
	    TIM_StartDecounter(SEC_CHECK_PRESS,Delay);

/*%C  If FLAT_INT_U16 = TRUE, then 											  */
		if ( (FlatInt == TRUE)
		  && (HighPressureExhalationDetected == FALSE) )
	  	{
/*%C 	   ALARM_CHECK_PRESSURE_U16 = ALARM_DETECTED						  */
			DB_AlarmStatusWrite(ALARM_CHECK_PRESSURE_U16, ALARM_DETECTED);
		}
/*%C	End if 																  */
/*%C Alarm_Error = NO_ERR_AL											 	  */		
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C  If FLAT_INT_U16 = FALSE, then											  */
		if (FlatInt == FALSE)
		{
/*%C 	  ALARM_CHECK_PRESSURE_U16 = ALARM_FALSE 							  */
	 	   DB_AlarmStatusWrite(ALARM_CHECK_PRESSURE_U16, ALARM_FALSE);
		}
/*%C	End if 																  */
/*%C    If Check pressure timer reached delay and 							  */
/*%C    CheckPressAutorization = TRUE, then 	 							  */
		if ((TIM_ReadDecounterValue(SEC_CHECK_PRESS)==0)
		   &&(CheckPressAutorization == TRUE)) 
		{
/*%C	ALARM_CHECK_PRESSURE_U16 = ALARM_TRUE 								  */
			DB_AlarmStatusWrite(ALARM_CHECK_PRESSURE_U16,ALARM_TRUE);
/*%C	Associated event is stored											  */
		  	DB_EventMngt(EVENT_AL_CHECK_PRESSURE);
/*%C  	Priority register updating for buzzer and leds command 				  */
			SEC_High_Priority_1= SEC_High_Priority_1| 0x0020;
		}
/*%C	End if 																  */
/*%C Alarm_Error = NO_ERR_AL											 	  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C  The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  */
/*%C  So there is no action to do.											  */
/*%C Alarm_Error = NO_ERR_AL											 	  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C  If FLAT_INT_U16 = FALSE, then											  */
		if (FlatInt == FALSE)
		{
/*%C 	  ALARM_CHECK_PRESSURE_U16 = ALARM_FALSE							  */
	 	   DB_AlarmStatusWrite(ALARM_CHECK_PRESSURE_U16, ALARM_FALSE);
/*%C	  Associated event is sent 											  */
	     	DB_EventMngt(EVENT_AL_END_OF_CHECK_PRESSURE);
/*%C  	  Priority register updating for buzzer and leds command 			  */
			SEC_High_Priority_1= SEC_High_Priority_1& 0xFFDF;
		}
/*%C	End if 																  */
/*%C Alarm_Error = NO_ERR_AL											 	  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C Alarm_Error = ERR_AL_CHECK_PRESSURE									  */
		Alarm_Error = ERR_AL_CHECK_PRESSURE;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C Alarm_Error = ERR_AL_CHECK_PRESSURE									  */
		Alarm_Error = ERR_AL_CHECK_PRESSURE;
		break;
	}
/*%C End of check alarm state 												  */
	return (Alarm_Error);
}


