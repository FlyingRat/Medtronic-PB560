/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_HighRate.c                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                High Rate alarm management                                */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Alarm_Error*/
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
#include "SEC_Highrate.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_HighRate(void)
{
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
	UWORD16 MeasureR = DB_ComputeRead(MEASURE_R_U16);
	e_DB_ALARMS_STATE AlarmHighRate = DB_AlarmStatusRead(ALARM_HIGH_RATE_U16);
	UWORD16 AdjustHighR = DB_CurrentRead(ADJUST_HIGH_R_U16);
	UWORD16 HighRNoSelect = DB_CurrentRead(HIGH_R_NO_SELECT_U16);
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
	static e_VentilState HRateMemoCycle = VEN_VENTIL_DISABLE;
	static UWORD16 NoHRateCycleCounter = 0;
	static UWORD16 HRateCycleCounter = 0;


/*%C Check ALARM_HIGH_RATE_U16 state 										  */
	switch(AlarmHighRate)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C 	If MEASURE_R_U16 is higher than ADJUST_HIGH_R_U16					  */
/*%C 	and HIGH_R_NO_SELECT_U16 = FALSE				 					  */
		if ( (MeasureR > AdjustHighR)
		  && (HighRNoSelect == FALSE) )
		{
/*%C     Then ALARM_HIGH_RATE_U16 = ALARM_DETECTED	 	 					  */
	   	DB_AlarmStatusWrite(ALARM_HIGH_RATE_U16, ALARM_DETECTED);
/*%C     HRateCycleCounter reset 						 					  */
         HRateCycleCounter = 0;
		}
/*%C 	End if 											 					  */
/*%C 	Alarm_Error = NO_ERR_AL							 					  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :

/*%C 	If HRateCycleCounter < 4  and 					   					  */
/*%C  	NoHRateCycleCounter = 0						       					  */
		if ( (HRateCycleCounter < 4)
		  && (NoHRateCycleCounter == 0) )
		{
/*%C 		Then increase HRateCycleCounter counter 						  */
			HRateCycleCounter = HRateCycleCounter + 1;
/*%C 		Setting the flag to prohibe a new increment in the same cycle 	  */
			NoHRateCycleCounter = 1;
 		}
/*%C 	End if																  */

/*%C 	if HRateCycleCounter = 4, then										  */
		if (HRateCycleCounter == 4)
	   {
/*%C 	ALARM_HIGH_RATE_U16 = ALARM_TRUE, associated event stored 			  */
      	DB_AlarmStatusWrite(ALARM_HIGH_RATE_U16, ALARM_TRUE);
   		DB_EventMngt(EVENT_AL_HIGH_RATE );
/*%C   	Priority register updating for buzzer and leds command 				  */
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | 0x0040;
	   }
/*%C	End if 																  */
/*%C 	If MEASURE_R_U16 <= ADJUST_HIGH_R_U16 							 	  */
/*%C 	or HIGH_R_NO_SELECT_U16 = TRUE, then   								  */
		if ( (MeasureR <= AdjustHighR)
		  || (HighRNoSelect == TRUE) )	
	   {
/*%C 		ALARM_HIGH_RATE_U16 = ALARM_FALSE, associated event stored 		  */
     		DB_AlarmStatusWrite(ALARM_HIGH_RATE_U16, ALARM_FALSE);
/*%C 		Reset HRateCycleCounter cycle counter 				 			  */
      	HRateCycleCounter = 0;
		}
/*%C	End if 													 			  */
/*%C	Alarm_Error = NO_ERR_AL									 			  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State						      */
/******************************************************************************/
	case ALARM_TRUE :
/*%C  The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  */
/*%C  So there is no action to do.											  */
/*%C  Updating the value of error code										  */
/*%C	Alarm_Error = NO_ERR_AL									 			  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C 	If MEASURE_R_U16 <= ADJUST_HIGH_R_U16 								  */
/*%C 	or HIGH_R_NO_SELECT_U16 = TRUE, then   								  */
		if ( (MeasureR <= AdjustHighR)
		  || (HighRNoSelect == TRUE) )	
	   {
/*%C 		ALARM_HIGH_RATE_U16 = ALARM_FALSE, associated event stored 		  */
     		DB_AlarmStatusWrite(ALARM_HIGH_RATE_U16, ALARM_FALSE);
   		DB_EventMngt(EVENT_AL_END_OF_HIGH_RATE );
/*%C		Priority register updating for buzzer and leds command 			  */
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xFFBF;
/*%C 		Reset HRateCycleCounter cycle counter 				   			  */
      	HRateCycleCounter = 0;
	   }
/*%C   End if																  */
/*%C  Updating the value of error code*/
/*%C	Alarm_Error = NO_ERR_AL									 			  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C This alarm can't be canceled 											  */
/*%C	Alarm_Error = ERR_AL_HIGH_RATE		   					 			  */
	Alarm_Error = ERR_AL_HIGH_RATE;
	break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C  Updating the value of error code										  */
/*%C	Alarm_Error = ERR_AL_HIGH_RATE		   					 			  */
		Alarm_Error = ERR_AL_HIGH_RATE;
		break;
	}
/*%C End of Check Alarm 													  */
/*%C On transition from exhalation to inspiration :							  */
/*%C if HRateMemoCycle = VEN_EXHALATION				 						  */
/*%C and  VENTIL_STATE_U16  = VEN_INSPIRATION_CONTROLED or 				  	  */
/*%C VENTIL_STATE_U16 = VEN_INSPIRATION_TRIGGERED, then					  	  */
	if ( (HRateMemoCycle == VEN_EXHALATION)
	  && ( (VentilState  == VEN_INSPIRATION_CONTROLED)
		 || (VentilState == VEN_INSPIRATION_TRIGGERED) ) )
	{
/*%C 	Freeing the flag allowing to increase counter, NoHRateCycleCounter = 0*/
		NoHRateCycleCounter = 0;
	}
/*%C Updating  the memory of ventil state 									  */
	HRateMemoCycle = VentilState;
/*%C Return the value of error code											  */
	return (Alarm_Error);
}


