/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ProxDisconnection.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        Management of alarm Prox Disconnection                            */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : ProxiDisconnectionDelay						 		  */
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
#include "SEC_ProxDisconnection.h"
#include "Security_Datas.h"
#include "Ventilation_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_ProxDisconnection(UWORD16 ProxiDisconnectionDelay)
{
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/*%C Flag Proximal Detected state recovery from base 						  */
	UWORD16 ProxiDetected = DB_ControlRead(PROXI_DETECTED_U16);
/*%C Alarm Proximal Disconnection state recovery from base 					  */
	e_DB_ALARMS_STATE AlarmProxiDisconnection = DB_AlarmStatusRead(ALARM_PROXI_DISCONNECTION_U16);
/*%C Alarm No Proximal state recovery from base 							  */
	e_DB_ALARMS_STATE AlarmNoProximal = DB_AlarmStatusRead(ALARM_NO_PROXIMAL_U16);
/*%C Alarm Check Proximal state recovery from base 							  */
	e_DB_ALARMS_STATE AlarmCheckProximal = DB_AlarmStatusRead(ALARM_CHECK_PROXIMAL_U16);

/*%C Check ALARM_PROXI_DISCONNECTION_U16 state 								  */    
	switch(AlarmProxiDisconnection)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C If PROXI_DETECTED_U16 = FALSE */
/*%C and ALARM_NO_PROXIMAL_U16 < ALARM_TRUE and VEN_ThirdCycle = TRUE, then   */
		if( (ProxiDetected == FALSE)
		 && (AlarmNoProximal < ALARM_TRUE)
		 && (VEN_ThirdCycle == TRUE) )
		{
/*%C 		ALARM_PROXI_DISCONNECTION_U16 = ALARM_DETECTED  				  */
			DB_AlarmStatusWrite(ALARM_PROXI_DISCONNECTION_U16, 
									  ALARM_DETECTED);
/*%C 		Timer is launched 												  */
			TIM_StartDecounter(SEC_PROX_DISC,
									 ProxiDisconnectionDelay);
	 	}
/*%C 	End if 																  */
/*%C  Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C If PROXI_DETECTED_U16 = TRUE */
/*%C or ALARM_NO_PROXIMAL_U16 >= ALARM_TRUE or ALARM_CHECK_PROXIMAL_U16 >= TRUE*/
/*%C or VEN_ThirdCycle = FALSE, then   */
		if ( (ProxiDetected == TRUE)
		  || (AlarmNoProximal >= ALARM_TRUE)
		  || (AlarmCheckProximal >= ALARM_TRUE)
		  || (VEN_ThirdCycle == FALSE) )
		{
/*%C 		ALARM_PROXI_DISCONNECTION_U16 = ALARM_FALSE  					  */
			DB_AlarmStatusWrite(ALARM_PROXI_DISCONNECTION_U16,
									  ALARM_FALSE);
	 	}
/*%C Else if timer reached delay and 										  */ 
/*%C ALARM_CHECK_PROXIMAL_U16 < ALARM_DETECTED, then 						  */
		else if ( (TIM_ReadDecounterValue(SEC_PROX_DISC) == 0) && (AlarmCheckProximal < ALARM_DETECTED) )
		{
/*%C		 ALARM_PROXI_DISCONNECTION_U16 = ALARM_TRUE						  */			
			 DB_AlarmStatusWrite(ALARM_PROXI_DISCONNECTION_U16, 
			 						   ALARM_TRUE);
/*%C		 Associated event is stored										  */
			 DB_EventMngt(EVENT_AL_PROXIMAL_DISCONNECTION);
/*%C		 Up dating priority register									  */
			 SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0002;
		}
/*%C	End if 																  */
/*%C  Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State					  		  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C  The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  */
/*%C  So there is no action to do.											  */
/*%C  Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C If PROXI_DETECTED_U16 = TRUE */
/*%C or ALARM_NO_PROXIMAL_U16 >= ALARM_TRUE or ALARM_CHECK_PROXIMAL_U16 >=   */
/*%C TRUE or VEN_ThirdCycle = FALSE, then  									 */
		if ( (ProxiDetected == TRUE)
		  || (AlarmNoProximal >= ALARM_TRUE)
		  || (AlarmCheckProximal >= ALARM_TRUE)
		  || (VEN_ThirdCycle == FALSE) )
		{
/*%C 		ALARM_PROXI_DISCONNECTION_U16 = ALARM_FALSE  					  */
			DB_AlarmStatusWrite(ALARM_PROXI_DISCONNECTION_U16, 
									  ALARM_FALSE);
/*%C 		The associated event is stored 									  */
		 	DB_EventMngt(EVENT_AL_END_OF_PROXI_DISCONNECTION);
/*%C 		The medium priority 2 register is updated.						  */		 
			SEC_Medium_Priority_2 =	SEC_Medium_Priority_2 & 0xFFFD;
		}
/*%C 	End if 																  */
/*%C  Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C This alarm can't be canceled 										  	  */
/*%C Alarm_Error = ERR_AL_PROXI_DISCONNECTION								  */
		Alarm_Error = ERR_AL_PROXI_DISCONNECTION;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C Alarm_Error = ERR_AL_PROXI_DISCONNECTION								  */
	  	Alarm_Error = ERR_AL_PROXI_DISCONNECTION;
		break;
	
}
/*%C End of check alarm state												  */
return(Alarm_Error);
    
}


