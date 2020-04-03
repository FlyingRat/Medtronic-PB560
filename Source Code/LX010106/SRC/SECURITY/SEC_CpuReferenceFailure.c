/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CpuReferenceFailure.c 			      					  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   					Management of Cpu reference alarm		              */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter :	Alarm_Error  	  									  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#ifndef _TASKING
	#include "LH_ST10F276.h"
	#include <intrins.h>
#else	    
 		#include "regf276e.h"
#endif 	
#include "typedef.h"
#include "io_declare.h"
#include "enum.h"
#include "DB_Event.h"
#include "DB_Control.h"
#include "DB_KeyboardEvent.h"
#include "DB_AlarmStatus.h"
#include "security_datas.h"
#include "SEC_CpuReferenceFailure.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

#define cTIME_CPU_REF_FAILURE 1000
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CpuReferenceFailure(void)
{
/* Alarm supply measure state recovery from base     			              */
	e_DB_ALARMS_STATE Alarm_Cpu_Reference =
								DB_AlarmStatusRead(ALARM_CPU_REFERENCE_U16);
/* Cancel request recovery from keyboard event base                           */
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
/* Uncancel command recovery from base                             			  */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
/* Alarm error declaration					                  		          */
 	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

/*%C Check ALARM_CPU_REFERENCE_U16 state 									  */
	switch(Alarm_Cpu_Reference)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C  if ALIM_FAILURE_5VREF = FALSE or ALIM_FAILURE_10VREF = FALSE, then	  */
		if ( (ALIM_FAILURE_5VREF == FALSE)
		  || (ALIM_FAILURE_10VREF == FALSE) )
		{
/*%C 	The apnea decounter is launched every time in the FALSE state         */
			TIM_StartDecounter(SEC_CPU_REF_FAILURE,
								 cTIME_CPU_REF_FAILURE);
/*%C	ALARM_CPU_REFERENCE_U16 = ALARM_DETECTED							  */
			DB_AlarmStatusWrite(ALARM_CPU_REFERENCE_U16, ALARM_DETECTED);
		}
/*%C	End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
	   Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C  The alarm is set to TRUE after a duration  	  */
		if(TIM_ReadDecounterValue(SEC_CPU_REF_FAILURE) == 0)
		{									  
/*%C  ALARM_CPU_REFERENCE_U16 = ALARM_TRUE								  	  */
      		DB_AlarmStatusWrite(ALARM_CPU_REFERENCE_U16, ALARM_TRUE);
/*%C  Associated event is stored                                 			  */
     		 DB_EventMngt(EVENT_AL_CPU_REFERENCE);
/*%C  Priority register update                                 				  */
       		SEC_High_Priority_1= SEC_High_Priority_1| 0x2000;
		}
		else if ( (ALIM_FAILURE_5VREF == TRUE)
		  && (ALIM_FAILURE_10VREF == TRUE) )
		{
/*%C	 ALARM_CPU_REFERENCE_U16 = ALARM_FALSE 								  */
			DB_AlarmStatusWrite(ALARM_CPU_REFERENCE_U16, ALARM_FALSE);
		}
/*%C Alarm_Error = NO_ERR_AL 												  */
	   Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "TRUE" State						   	  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 		  */
/*%C  So there is no action to do.											  */
/*%C  Alarm_Error = NO_ERR_AL 												  */			  
	   Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C  if ALIM_FAILURE_5VREF = TRUE and ALIM_FAILURE_10VREF = TRUE, then	  	  */
		if ( (ALIM_FAILURE_5VREF == TRUE)
		  && (ALIM_FAILURE_10VREF == TRUE) )
		{
/*%C	 ALARM_CPU_REFERENCE_U16 = ALARM_FALSE 								  */
			DB_AlarmStatusWrite(ALARM_CPU_REFERENCE_U16, ALARM_FALSE);
/*%C  	 Associated end event is stored                                 	  */
      		DB_EventMngt(EVENT_AL_END_CPU_REFERENCE);
/*%C     Updating of priority register 									  	  */
      		SEC_High_Priority_1= SEC_High_Priority_1& 0xDFFF;
		}
/*%C  Else if KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE, then 			  */
	   else if (KeyboardDoublePulseInhibEvent == TRUE )
 	   {
/*%C	ALARM_CPU_REFERENCE_U16 = ALARM_CANCELED							  */
		   DB_AlarmStatusWrite(ALARM_CPU_REFERENCE_U16, ALARM_CANCELED);
/*%C     	Updating of priority register 									  */
			SEC_High_Priority_1= SEC_High_Priority_1& 0xDFFF;
	   }
/*%C   End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
      Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C  if ALIM_FAILURE_5VREF = TRUE and ALIM_FAILURE_10VREF = TRUE, then	  	  */
		if ( (ALIM_FAILURE_5VREF == TRUE)
		  && (ALIM_FAILURE_10VREF == TRUE) )
		{
/*%C	  ALARM_CPU_REFERENCE_U16 = ALARM_FALSE 							  */
			DB_AlarmStatusWrite(ALARM_CPU_REFERENCE_U16, ALARM_FALSE);
/*%C  		Associated end event is stored                                 	  */
      		DB_EventMngt(EVENT_AL_END_CPU_REFERENCE);
		}

		/******************************************************************/
		/*		 				Reset of the "CANCELED" State             */
		/******************************************************************/

/*%C 	Else if UNCANCEL_CMD_U16 = TRUE, then  								  */
		else if (UncancelCmd == TRUE)
		{
/*%C 	ALARM_CPU_REFERENCE_U16 = ALARM_TRUE								  */
/*%C 	Up dating of priority register for leds & buzzer 					  */
	   	DB_AlarmStatusWrite(ALARM_CPU_REFERENCE_U16, ALARM_TRUE);
			SEC_High_Priority_1= SEC_High_Priority_1| 0x2000;
		}
/*%C	End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */ 
		Alarm_Error = NO_ERR_AL;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C Alarm_Error = ERR_AL_CPU_REFERENCE										  */
	  	Alarm_Error = ERR_AL_CPU_REFERENCE;
		break;
	}
/*%C End check alarm state 													  */
	return(Alarm_Error);
}
