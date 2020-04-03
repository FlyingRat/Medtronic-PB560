/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_VoluntaryStop.c                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   Management of alarm voluntary stop	                  */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NO_ERR_AL                                             */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "DB_KeyboardEvent.h"
#include "DB_Control.h"
#include "SEC_VoluntaryStop.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_VoluntaryStop(void)
{
/* Alarm Voluntary stop recovery from base				    			  */
	e_DB_ALARMS_STATE AlarmVoluntaryStop =
							DB_AlarmStatusRead(ALARM_VOLUNTARY_STOP_U16);
/* Alarm error declaration													  */
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

/* Cancel request recovery from keyboard event base                           */
	SWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);

/* Uncancel command recovery from base                             			  */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);

/* Voluntary stop flag recovery from base                             			  */
	UWORD16 VoluntaryStop = DB_ControlRead(VOLUNTARY_STOP_U16);

	switch(AlarmVoluntaryStop)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
		case ALARM_FALSE:
		{ 

/*%C     	If VOLUNTARY_STOP_U16 = TRUE, then 						 	  */
		   if (VoluntaryStop == TRUE)
			{
/*%C        	   ALARM_VOLUNTARY_STOP_U16 = ALARM_TRUE				  */
			   DB_AlarmStatusWrite(ALARM_VOLUNTARY_STOP_U16,
				     							  ALARM_TRUE);
/*%C		Associated event is stored 										  */
			DB_EventMngt(EVENT_AL_VOLUNTARY_STOP);
/*%C        	   Up dating the priority register 							  */
				SEC_High_Priority_2= SEC_High_Priority_2| 0x2000;
			}
/*%C 		  End if 														  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		   Alarm_Error = NO_ERR_AL;
		   break;
	 	}
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
		case ALARM_DETECTED :
		{
/*%C Alarm_Error = ERR_AL_AL_VOLUNTARY_STOP 							   	  */
			Alarm_Error = ERR_AL_VOLUNTARY_STOP;
		   break;
		}
/******************************************************************************/
/*%C	         					 "TRUE" State						  	  */
/******************************************************************************/
		case ALARM_TRUE :
		{
/*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 	 	  */
/*%C So there is no action to do.										  	  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		   Alarm_Error = NO_ERR_AL;
		   break;
		}
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
		case ALARM_DISPLAYED	:
		{
					if (VoluntaryStop == FALSE)
 			{
/*%C        	ALARM_VOLUNTARY_STOP_U16 = ALARM_CANCELED				  */
				DB_AlarmStatusWrite(ALARM_VOLUNTARY_STOP_U16, ALARM_FALSE);
/*%C			Associated event is stored 										  */
				DB_EventMngt(EVENT_AL_END_OF_VOLUNTARY_STOP);
/*%C 			Up dating of priority register 								  */
				SEC_High_Priority_2= SEC_High_Priority_2& 0xDFFF;
			}		  
/*%C   Else If KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE, then				  */
			else if (KeyboardDoublePulseInhibEvent == TRUE )
			{
/*%C        	ALARM_VOLUNTARY_STOP_U16 = ALARM_CANCELED				  */
				DB_AlarmStatusWrite(ALARM_VOLUNTARY_STOP_U16, ALARM_CANCELED);
/*%C 			Up dating of priority register 								  */
				SEC_High_Priority_2= SEC_High_Priority_2& 0xDFFF;
/*%C			Voluntary stop is reset */
			}

				
/*%C Alarm_Error = NO_ERR_AL 												  */
		   Alarm_Error = NO_ERR_AL;
		   break;

		}
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
		case ALARM_CANCELED :
		{

			if (VoluntaryStop == FALSE)
 			{
/*%C        	ALARM_NO_VALVE_DETECTION_U16 = ALARM_TRUE				  */
				DB_AlarmStatusWrite(ALARM_VOLUNTARY_STOP_U16, ALARM_FALSE);
/*%C			Associated event is stored 										  */
				DB_EventMngt(EVENT_AL_END_OF_VOLUNTARY_STOP);
			}
		/******************************************************************/
		/*		 				Reset of the "CANCELED" State                   */
		/******************************************************************/
				 
/*%C 	If a command of inhibition of the cancel, is true, */
/*%C 	then the alarm is set to TRUE */
		else if(UncancelCmd == TRUE)
		{
/*%C    	ALARM_VOLUNTARY_STOP_U16 = ALARM_TRUE				  */
			DB_AlarmStatusWrite(ALARM_VOLUNTARY_STOP_U16,
				     							  ALARM_TRUE);
/*%C    	Up dating the priority register 							  */
			SEC_High_Priority_2= SEC_High_Priority_2| 0x2000;
		}

/*%C Alarm_Error = NO_ERR_AL 							   	  				  */
	    Alarm_Error = NO_ERR_AL;
	    break;
		}
			   
/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
		default:
		{
/*%C 		Alarm_Error = ERR_AL_VOLUNTARY_STOP 							   	  */
	  	   Alarm_Error = ERR_AL_VOLUNTARY_STOP;
		   break;
		}
	}
/*%C End of check alarm state 												  */
	return(Alarm_Error);
}
