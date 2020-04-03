/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Checkproximal.c                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          		Management of check proximal alarme                       */
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
#include "DB_Event.h"
#include "DB_Compute.h"					
#include "DB_Current.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_KeyboardEvent.h"
#include "SEC_Checkproximal.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckProximal(UWORD16 Delay)
{

	SWORD16 FilterPatientPressureProxi =
						(SWORD16)DB_ComputeRead(FILTER_PATIENT_PRESSURE_PROXI_S16);
	e_DB_ALARMS_STATE AlarmCheckProximal = 
						DB_AlarmStatusRead(ALARM_CHECK_PROXIMAL_U16);
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
	UWORD16 Adjust_Peep = DB_CurrentRead(ADJUST_PEEP_U16);															
    UWORD16 FlatProxi = DB_ControlRead(FLAT_PROXI_U16);
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

/*%C Check ALARM_CHECK_PROXIMAL_U16 state 									  */	
	switch(AlarmCheckProximal)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :

/*%C if FLAT_PROXI_U16 = TRUE and  			 							      */
/*%C ( (FILTER_PATIENT_PRESSURE_PROXI_S16 > ADJUST_PEEP_U16 + 15) 			  */ 
/*%C or ( FILTER_PATIENT_PRESSURE_PROXI_S16 < ADJUST_PEEP_U16 - 15))   		  */
/*%C and FILTER_PATIENT_PRESSURE_PROXI_S16 > 15, then						  */
			if ( (FlatProxi==TRUE)
			  && (  (FilterPatientPressureProxi > (SWORD16)Adjust_Peep + 15)
			      ||(FilterPatientPressureProxi < (SWORD16)Adjust_Peep - 15))
			  &&(FilterPatientPressureProxi > 15) )
				 
			{
/*%C 			ALARM_CHECK_PROXIMAL_U16 = ALARM_DETECTED 					  */
/*%C			proximal default timer is launched 						  	  */
				DB_AlarmStatusWrite(ALARM_CHECK_PROXIMAL_U16, ALARM_DETECTED);
				TIM_StartDecounter(SEC_CHECK_PROXI, Delay);
			}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 				          */
/******************************************************************************/
	case ALARM_DETECTED :

/*%C if (FLAT_PROXI_U16 = FALSE)	or										  */
/*%C ( ADJUST_PEEP_U16- 1.5 cmH20 < FILTER_PATIENT_PRESSURE_PROXI_S16 and     */ 
/*%C FILTER_PATIENT_PRESSURE_PROXI_S16 < ADJUST_PEEP_U16 + 1.5 cmH2O ) or 	  */ 
/*%C FILTER_PATIENT_PRESSURE_PROXI_S16 < 1.5 cmH2O 							  */

		if (  (FlatProxi==FALSE)
	        ||(  (FilterPatientPressureProxi < (SWORD16)Adjust_Peep + 15)
			   &&(FilterPatientPressureProxi > (SWORD16)Adjust_Peep - 15))
		    ||(FilterPatientPressureProxi < 15) )
		  
		    
		{
/*%C  Then ALARM_CHECK_PROXIMAL_U16 = ALARM_FALSE  							  */
			DB_AlarmStatusWrite(ALARM_CHECK_PROXIMAL_U16, ALARM_FALSE);
		}
/*%C   Else if delay of presence is over 									  */
		else if (TIM_ReadDecounterValue(SEC_CHECK_PROXI) == 0)
		{
/*%C   Then	ALARM_CHECK_PROXIMAL_U16 = ALARM_TRUE 		  					  */
			DB_AlarmStatusWrite(ALARM_CHECK_PROXIMAL_U16, ALARM_TRUE);
/*%C 	Associated event is stored 											  */
			DB_EventMngt(EVENT_AL_CHECK_PROXIMAL);
/*%C  	Priority register updating for buzzer and leds command 				  */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0001;
		}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State						  	  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C  The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  */
/*%C  So there is no action to do.											  */
/*%C  Updating the value of error code										  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C if (FLAT_PROXI_U16 = FALSE)	or										  */
/*%C ( ADJUST_PEEP_U16- 1.5 cmH20 < FILTER_PATIENT_PRESSURE_PROXI_S16 and 	  */
/*%C FILTER_PATIENT_PRESSURE_PROXI_S16	< ADJUST_PEEP_U16 + 1.5 cmH2O ) or    */ 
/*%C FILTER_PATIENT_PRESSURE_PROXI_S16 < 1.5 cmH2O 							  */
		if (  (FlatProxi==FALSE)
	        ||(  (FilterPatientPressureProxi < (SWORD16)Adjust_Peep + 15)
			   &&(FilterPatientPressureProxi > (SWORD16)Adjust_Peep - 15))
		    ||(FilterPatientPressureProxi < 15) )
		{
/*%C  	Then ALARM_CHECK_PROXIMAL_U16 = ALARM_FALSE							  */
/*%C 	Associated event is stored 											  */
			DB_AlarmStatusWrite(ALARM_CHECK_PROXIMAL_U16, ALARM_FALSE);
			DB_EventMngt(EVENT_AL_END_OF_CHECK_PROXIMAL);
/*%C  	Priority register updating for buzzer and leds command 				  */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 & 0xFFFE;
		}
/*%C 	Else if KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE 				  */
		else if (KeyboardDoublePulseInhibEvent == TRUE)
		{
/*%C Then ALARM_CHECK_PROXIMAL_U16 = ALARM_CANCELED							  */ 
			DB_AlarmStatusWrite(ALARM_CHECK_PROXIMAL_U16, ALARM_CANCELED);
/*%C  	Priority register updating for buzzer and leds command 			  	  */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 & 0xFFFE;
		}
/*%C End if 																  */
/*%C 	Updating the value of error code									  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C if (FLAT_PROXI_U16 = FALSE)	or										  */
/*%C ( ADJUST_PEEP_U16- 1.5 cmH20 < FILTER_PATIENT_PRESSURE_PROXI_S16 and 	  */
/*%C FILTER_PATIENT_PRESSURE_PROXI_S16	< ADJUST_PEEP_U16 + 1.5 cmH2O ) or    */ 
/*%C FILTER_PATIENT_PRESSURE_PROXI_S16 < 1.5 cmH2O 							  */
		if (  (FlatProxi==FALSE)
	        ||(  (FilterPatientPressureProxi < (SWORD16)Adjust_Peep + 15)
			   &&(FilterPatientPressureProxi > (SWORD16)Adjust_Peep - 15))
		    ||(FilterPatientPressureProxi < 15) )
		{
/*%C  	Then ALARM_CHECK_PROXIMAL_U16 = ALARM_FALSE							  */
/*%C 	Associated event is stored 											  */
			DB_AlarmStatusWrite(ALARM_CHECK_PROXIMAL_U16, ALARM_FALSE);
			DB_EventMngt(EVENT_AL_END_OF_CHECK_PROXIMAL);
		}
		/******************************************************************/
		/*		 				Reset of the "CANCELED" State             */
		/******************************************************************/
				 
/*%C 	Else If UNCANCEL_CMD_U16 = TRUE 									  */
/*%C 	then the alarm is set to TRUE */
		else if(UncancelCmd == TRUE)
		{
/*%C   Then	ALARM_CHECK_PROXIMAL_U16 = ALARM_TRUE 		  					  */
	   	DB_AlarmStatusWrite(ALARM_CHECK_PROXIMAL_U16,
	   							  ALARM_TRUE);
/*%C  	Priority register updating for buzzer and leds command 				  */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0001;
		}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
		Alarm_Error = NO_ERR_AL;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C  Updating the value of error code										  */
/*%C Alarm_Error = ERR_AL_CHECK_PROXIMAL 								      */
		Alarm_Error = ERR_AL_CHECK_PROXIMAL;
		break;
	}
/*%C End of Check Alarm state												  */	
/*%C Return the value of error code											  */
	return (Alarm_Error);

}
