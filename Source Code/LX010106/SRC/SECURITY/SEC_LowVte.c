/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_LowVte.c                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C         Management of the alarm Low Vte                                  */
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
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "SEC_LowVte.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_LowVte(void)
{
/* Alarm error declaration							                          */
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/* Alarm low Vte recovery from base				                              */
	e_DB_ALARMS_STATE AlarmLowVte = 	DB_AlarmStatusRead(ALARM_LOW_VTE_U16);
/* Alarm disconnection recovery from base	 	                              */
	e_DB_ALARMS_STATE AlarmDisconnection = 
											DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);
/* Computed Vte recovery from base	 	                              		  */
	UWORD16 ComputedVte = DB_ComputeRead(COMPUTED_VTE_U16);
/* Adjust low Vte recovery from base	 	                          	      */
	UWORD16 AdjustLowVte = DB_CurrentRead(ADJUST_LOW_VTE_U16);
/* Low Vte no selecte state recovery from base	 	                    	  */
	UWORD16 LowVteNoSelect = DB_CurrentRead (LOW_VTE_NO_SELECT_U16);
/* Ventil state recovery from base	 	                				      */
   e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
/* Ventil state memorization			 	                				  */
	static e_VentilState MemoVentilState = VEN_VENTIL_DISABLE;
/* Low vte cycle counter				 	                				  */
	static UWORD16 LVteCmp = 0;
/* No low vte cycle info				 	                				  */
	static UWORD16 NoLVteCmp= 0;
/*%C Check ALARM_LOW_VTE_U16 state 											  */ 
switch(AlarmLowVte)
{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C 	If COMPUTED_VTE_U16 < ADJUST_LOW_VTE_U16 and						  */
/*%C 	LOW_VTE_NO_SELECT_U16 = FALSE and								 	  */
/*%C  	ALARM_DISCONNECTION_U16 <= ALARM_DETECTED, then						  */
		if ((ComputedVte < AdjustLowVte)
		&& (LowVteNoSelect == FALSE)
		&& (AlarmDisconnection <= ALARM_DETECTED) )
		{
/*%C 		ALARM_LOW_VTE_U16 = ALARM_DETECTED							 	  */
			DB_AlarmStatusWrite(ALARM_LOW_VTE_U16,
									  ALARM_DETECTED);
/*%C     LVteCmp counter reset 												  */
         LVteCmp = 0;
		}
/*%C    End if 																  */
/*%C    Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :

/*%C  If LVteCmp < 3 and NoLVteCmp = 0, then 								  */
		if ( ( LVteCmp < 3)
		  && (NoLVteCmp == 0) )
		{
/*%C 		increase LVteCmp 												  */
			LVteCmp = LVteCmp + 1;
/*%C 		Setting NoLVteCmp to prohibe a new increment in the same cycle 	  */
			NoLVteCmp = 1;
 		}
/*%C    End if 																  */
/*%C 	If COMPUTED_VTE_U16 >= ADJUST_LOW_VTE_U16 or						  */
/*%C 	LOW_VTE_NO_SELECT_U16 = TRUE or									 	  */
/*%C  	ALARM_DISCONNECTION_U16 >= ALARM_TRUE, then							  */
		if ( (ComputedVte >= AdjustLowVte)
		  || (LowVteNoSelect == TRUE)
		  || (AlarmDisconnection >= ALARM_TRUE) )
		{
/*%C 		Storage of the False state of the alarm 						  */
			DB_AlarmStatusWrite(ALARM_LOW_VTE_U16,
									  ALARM_FALSE);
/*%C 		erazing of cycles counter LVteCmp 								  */
			LVteCmp = 0;
		}
/*%C 	Else if LVteCmp = 3 									 			  */
		else if (LVteCmp == 3)
		{
/*%C 		ALARM_LOW_VTE_U16 = ALARM_TRUE						  			  */
			DB_AlarmStatusWrite(ALARM_LOW_VTE_U16,
									  ALARM_TRUE);
/*%C 		Storage of the associated event 								  */
			DB_EventMngt(EVENT_AL_LOW_VTE);
/*%C		Priority register updating for buzzer and leds command 			  */
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | 0x0004;
		}
/*%C    End if 																  */

/*%C    Alarm_Error = NO_ERR_AL												  */	
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C 	The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  */
/*%C  So there is no action to do.											  */
/*%C    Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C 	If COMPUTED_VTE_U16 >= ADJUST_LOW_VTE_U16 or						  */
/*%C 	LOW_VTE_NO_SELECT_U16 = TRUE or									 	  */
/*%C  	ALARM_DISCONNECTION_U16 >= ALARM_TRUE, then							  */
		if ( (ComputedVte >= AdjustLowVte)
		  || (LowVteNoSelect == TRUE)
		  || (AlarmDisconnection >= ALARM_TRUE) )
		{
/*%C 		ALARM_LOW_VTE_U16 = ALARM_FALSE 								 */
			DB_AlarmStatusWrite(ALARM_LOW_VTE_U16,
									  ALARM_FALSE);
/*%C		Priority register updating for buzzer and leds command 			 */
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xFFFB;
			
/*%C 		erazing of LVteCmp 												 */
			LVteCmp = 0;
/*%C 		Storage of the associeted event 								 */
			DB_EventMngt(EVENT_AL_END_OF_LOW_VTE);
		}
/*%C    End if 																 */
/*%C    Alarm_Error = NO_ERR_AL												 */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C  This alarm can't be canceled 											  */
/*%C    Alarm_Error = ERR_AL_LOW_VTE				 						  */
		Alarm_Error = ERR_AL_LOW_VTE;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C    Alarm_Error = ERR_AL_LOW_VTE				 						  */
	  	Alarm_Error = ERR_AL_LOW_VTE;
		break;
}
/*%C End of check alarm state 												 */
/*%C If MemoVentilState == VEN_EXHALATION and 								 */
/*%C (VENTIL_STATE_U16 = VEN_INSPIRATION_CONTROLED  or 						 */
/*%C  VENTIL_STATE_U16 = VEN_INSPIRATION_TRIGGERED), then 	 	   			 */
	if	( (MemoVentilState == VEN_EXHALATION )
	  && ( (VentilState == VEN_INSPIRATION_CONTROLED)
	    || (VentilState == VEN_INSPIRATION_TRIGGERED) ) )
	{
/*%C 	Freeing the flag allowing to increase counter (NoLVteCmp = 0)		 */
		NoLVteCmp = 0;
	}
/*%C Updating MemoVentilState								 				 */
	MemoVentilState = VentilState ;

	return(Alarm_Error);
}
 