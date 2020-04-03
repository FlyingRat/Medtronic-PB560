/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0104                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_LeakDisconnection.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Low Pressure alarm Management Modes without Valve              */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  Disconnection_Delay                                   */
/*%I                    LowPressure                                           */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : Alarm_Error                                           */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Event.h"
#include "Security_Datas.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_Current.h"
#include "SEC_LeakDisconnection.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_LeakDisconnection(UWORD16 Disconnection_Delay)
{
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
	SWORD16 MeasurePatientPressure =
								 (SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);
  	SWORD16 MeasureQinsp = (SWORD16)DB_ComputeRead(MEASURE_QINSP_S16);
	UWORD16 ComputedVti = DB_ComputeRead(COMPUTED_VTI_U16); 
    SWORD16 LowPress = (SWORD16)((DB_CurrentRead(PI_SET_POINT_U16)*8)/10);
	e_DB_ALARMS_STATE AlarmDisconnection =
								DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);
   	switch(AlarmDisconnection)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C  If Patient Pressure <= Low pressureor if the inspiratory flow is upper  */
/*%c  than 600 dl/min during inpiration phase and Vti lower than 20 mL        */
	   if   ((MeasurePatientPressure <= LowPress)
		  || ((ComputedVti <= cQMINVTIDISCONNECTION)
		  && (MeasureQinsp > cQMAXLEAKDISCONNECTION_600)))
	   {
/*%C		Alarm is turned to Detected and count down is activated */
			DB_AlarmStatusWrite(ALARM_DISCONNECTION_U16, ALARM_DETECTED);
			TIM_StartDecounter(SEC_LOW_PRESS, Disconnection_Delay);
	   }
	 	Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C 	If the measure Patient Pressure > Low pressure 			 */
/*%C 	and if the inspiratory flow is lower than 600 dl/min     */
/*%C 	or Vti upper than 20 mL 								 */
	   if ( (MeasurePatientPressure > LowPress)
		  && ((ComputedVti > cQMINVTIDISCONNECTION)
		  || (MeasureQinsp <= cQMAXLEAKDISCONNECTION_600)))
		{ 
/*%C		Alarm is turned to False 						  	 */
			DB_AlarmStatusWrite(ALARM_DISCONNECTION_U16,ALARM_FALSE);
		}
/*%C	Else If the Alarm is detected and the delay is over */
	  	else if (TIM_ReadDecounterValue(SEC_LOW_PRESS) == 0)
	  	{ 
/*%C 		The Alarm is turned to TRUE, and the corresponding event is recorded*/
		  	DB_AlarmStatusWrite(ALARM_DISCONNECTION_U16, ALARM_TRUE);
			DB_EventMngt(EVENT_AL_DISCONNECTION);
/*%C		Priority register updating for buzzer and leds command */
			SEC_High_Priority_1	= SEC_High_Priority_1| 0x0001;
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
/*%C 	If the measure Patient Pressure > Low pressure 			 */
/*%C 	and if the inspiratory flow is lower than 600 dl/min 	 */
/*%C 	or Vti upper than 20 mL 								 */
	   if ( (MeasurePatientPressure > LowPress)
		  && ((ComputedVti > cQMINVTIDISCONNECTION)
		  || (MeasureQinsp <= cQMAXLEAKDISCONNECTION_600)))
		 
	   { 
/*%C		Alarm is turned to False */
			DB_AlarmStatusWrite(ALARM_DISCONNECTION_U16,ALARM_FALSE);
/*%C 		The end of alarm event is sent*/
			DB_EventMngt(EVENT_AL_END_OF_DISCONNECTION);
/*%C		Priority register updating for buzzer and leds command */
			SEC_High_Priority_1= SEC_High_Priority_1& 0xFFFE;
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C 	This alarm can't be canceled */
	  	Alarm_Error = ERR_AL_DISCONNECTION;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
		Alarm_Error = ERR_AL_DISCONNECTION;
		break;
	}
return(Alarm_Error);
}

