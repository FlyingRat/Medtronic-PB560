/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_HighVti.c                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   High Vti Alarm management                                              */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Alarm_Error
*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "DB_Event.h"
#include "enum.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "SEC_HighVti.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_HighVti(void)
{
/* Alarm error declaration							                          */
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/* Alarm high Vti	recovery from base			                              */
	e_DB_ALARMS_STATE AlarmHighVti =	DB_AlarmStatusRead(ALARM_HIGH_VTI_U16);
/* Alarm disconnection recovery from base			                          */
	e_DB_ALARMS_STATE AlarmDisconnection =
										DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);
/* Computed Vti recovery from base					                          */
 	UWORD16 ComputedVti = DB_ComputeRead(COMPUTED_VTI_U16);
/* Adjust high VTI recovery from base				                          */
	UWORD16 AdjustHighVti = DB_CurrentRead(ADJUST_HIGH_VTI_U16);
/* High VTI no select recovery from base			                          */
	UWORD16 HighVtiNoSelect = DB_CurrentRead (HIGH_VTI_NO_SELECT_U16);
/* Ventil state recovery from base					                          */
   e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
/* Ventil state memorization recovery from base	                              */
	static e_VentilState MemoVentilState = VEN_VENTIL_DISABLE;
/* No high 	                              									  */
	static UWORD16 NoHVtiCmp = 0;
/* High vti cycle counter								                      */
   static UWORD16 HVtiCmp =0;


/*%C Check ALARM_HIGH_VTI_U16 state 									   	  */
	switch(AlarmHighVti)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C 	If COMPUTED_VTI_U16 > ADJUST_HIGH_VTI_U16 and 				 		  */ 
/*%C 	HIGH_VTI_NO_SELECT_U16 = False and 							 		  */ 
/*%C 	ALARM_DISCONNECTION_U16 <= ALARM_DETECTED					 		  */ 
		if ( (ComputedVti > AdjustHighVti) 
		  && (HighVtiNoSelect == FALSE) 
	     && (AlarmDisconnection <= ALARM_DETECTED) ) 
		{ 
/*%C		Then ALARM_HIGH_VTI_U16 = ALARM_DETECTED						  */
			DB_AlarmStatusWrite(ALARM_HIGH_VTI_U16,ALARM_DETECTED);
/*%C  	High Vti counter HVtiCmp reset 										  */
	      HVtiCmp = 0;
		}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 				          */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C  If HVtiCmp < 3 and NoHVtiCmp = 0								 		  */
		if ( (HVtiCmp < 3) 
		  && (NoHVtiCmp == 0) ) 
		{ 
/*%C 		Then increase the HVtiCmp counter 								  */
			HVtiCmp = HVtiCmp +1;
/*%C 		setting NoHVtiCmp 											      */ 
			NoHVtiCmp =	1;
		}
/*%C 	End if 														 		  */
/*%C 	If COMPUTED_VTI_U16 <= ADJUST_HIGH_VTI_U16 or 				 		  */ 
/*%C 	HIGH_VTI_NO_SELECT_U16 = True or 							 		  */ 
/*%C 	ALARM_DISCONNECTION_U16 >= ALARM_TRUE						 		  */
		if ( (ComputedVti <= AdjustHighVti)
		  || (HighVtiNoSelect == TRUE)
		  || (AlarmDisconnection >= ALARM_TRUE) )
		{
/*%C 		Then reset HVtiCmp												  */ 
			HVtiCmp = 0; 
/*%C		ALARM_HIGH_VTI_U16 = ALARM_FALSE 								  */
	 		DB_AlarmStatusWrite(ALARM_HIGH_VTI_U16,ALARM_FALSE); 
		}
/*%C 	Else if HVtiCmp = 3								 					  */
		else if (HVtiCmp == 3)
	  	{
/*%C		Then ALARM_HIGH_VTI_U16 = ALARM_TRUE   							  */
			DB_AlarmStatusWrite(ALARM_HIGH_VTI_U16,ALARM_TRUE); 
/*%C 		Storage of the associated event									  */ 
			DB_EventMngt(EVENT_AL_HIGH_VTI); 
/*%C		Priority register updating for buzzer and leds command  		  */
			SEC_High_Priority_1= SEC_High_Priority_1|0x0004; 
		}
/*%C	End if 																  */
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
/*%C 	If COMPUTED_VTI_U16 <= ADJUST_HIGH_VTI_U16 or 				 		  */ 
/*%C 	HIGH_VTI_NO_SELECT_U16 = TRUE or 							 		  */ 
/*%C 	ALARM_DISCONNECTION_U16 >= ALARM_TRUE						 		  */ 
		if (((ComputedVti <= AdjustHighVti) 
		|| (HighVtiNoSelect == TRUE)
		|| (AlarmDisconnection >= ALARM_TRUE))) 
		{ 
/*%C 		Then reset HVtiCmp												  */
			HVtiCmp = 0; 
/*%C		 ALARM_HIGH_VTI_U16 = ALARM_FALSE							   	  */
			DB_AlarmStatusWrite(ALARM_HIGH_VTI_U16,ALARM_FALSE); 
/*%C		Priority register updating for buzzer and leds command 			  */
			SEC_High_Priority_1= SEC_High_Priority_1& 0xFFFB;
/*%C 		Storage of the associated event									  */
			DB_EventMngt(EVENT_AL_END_OF_HIGH_VTI); 
		}
/*%C 	End if 																  */
/*%C Alarm_Error = NO_ERR_AL												  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C This alarm can't be canceled 											  */
/*%C Alarm_Error = ERR_AL_HIGH_VTI											  */
		Alarm_Error = ERR_AL_HIGH_VTI;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C Alarm_Error = ERR_AL_HIGH_VTI											  */
	  	Alarm_Error = ERR_AL_HIGH_VTI;
		break;
	}
/*%C End of check Alarm state 												 */
/*%C If VENTIL_STATE_U16 = VEN_EXHALATION and 						 		 */
/*%C ( MemoVentilState = VEN_INSPIRATION_CONTROLED or 				 		 */
/*%C MemoVentilState = VEN_INSPIRATION_TRIGGERED )					 		 */
	if	( (VentilState == VEN_EXHALATION )
	  && ( (MemoVentilState == VEN_INSPIRATION_CONTROLED)
		 || (MemoVentilState == VEN_INSPIRATION_TRIGGERED) ) )
	{
/*%C 	Then NoHVtiCmp = 0													  */
		NoHVtiCmp = 0;
	}
/*%C End if															 		  */
/*%C Up dating the memory of the ventil state 					 		  	  */
		MemoVentilState = VentilState ;

	return(Alarm_Error);
}



























