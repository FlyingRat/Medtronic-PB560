/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckValve.c                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C         Valve Alarm management (Check it)                                */
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
#include "DB_Compute.h"
#include "DB_Control.h"
#include "DB_AlarmStatus.h"	
#include "DB_Current.h"
#include "Security_Datas.h"
#include "SEC_CheckValve.h"
#include "Ventilation_Datas.h"
#include "Ventilation_Compute_data.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckValve(void)
{
    SWORD32 const CONVERT_RATE_TO_SECS = 60000;
	SWORD32 TimerCount = 0;
	SWORD32 MeasureRate = (SWORD32) DB_ComputeRead(MEASURE_R_U16);
	SWORD16 ComputedVtiExh = (SWORD16)DB_ComputeRead(COMPUTED_VTI_EXH_S16);
	UWORD16 ComputedVti = DB_ComputeRead(COMPUTED_VTI_U16);
	e_DB_ALARMS_STATE AlarmCheckValve= DB_AlarmStatusRead(ALARM_CHECK_VALVE_U16);
 	SWORD16 VtiDelta = - (SWORD16)((ComputedVti*4)/10);
   e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
   static UWORD16 CycleCount = 0;
   /*%C VentilState recovery from base                                          */
	UWORD16 VentilState = DB_ControlRead(VENTIL_STATE_U16);
/*%C Initialisation of static and local variables                            */
	static e_VentilState MemoVentilState = VEN_VENTIL_DISABLE;

/*%C    According to ISO 80601-2-72_2015                                      */
/*%C    201.12.4.107 * Obstruction ALARM CONDITION                            */
/*%C        "The obstruction TECHNICAL ALARM CONDITION shall be HIGH PRIORITY.*/
/*%C         The maximum ALARM CONDITION DELAY shall be no more than two      */
/*%C         breath cycles or 5 s, whichever is greater."                     */

    // check valve alarm is used to satisfy detection of occlusion on the exhalation or
    // exhaust side of valve.
    const SWORD32 MAX_OCCLUSION_TIMER_DELAY = 5000;  // 5 secs
    const UWORD16 MAX_NUM_BREATHS_FOR_OCCLUSION_DETECTION = 2;

/*%C Check ALARM_CHECK_VALVE_U16 state */
   switch(AlarmCheckValve)
   {
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	   case ALARM_FALSE :
	   {
/*%C     If COMPUTED_VTI_EXH_S16 < - 4/10 COMPUTED_VTI_U16 or 	        */
/*%C		Valve current out of limits or  			  */
/*%C		Flow with negative saturation , then  			  */
	      if (  (ComputedVtiExh < VtiDelta) 
				|| (VEN_ValveCurrentSat == TRUE)
				|| (VEN_FlowNegSat == TRUE))
	      {
			  // Increment the breath count if the detection is during inhalation phase
			  // because the conditions above was determine from the previous breath.			
			  if((VEN_Controller_Phase == VEN_INSP_RISE) || 
				 (VEN_Controller_Phase == VEN_INSP_PLAT) )
			  {
                  CycleCount = 1; 
				  // Since the breath count is incremented, the timer must be 5 secs minus the previous breath time. 
				  TimerCount =  MAX_OCCLUSION_TIMER_DELAY - (CONVERT_RATE_TO_SECS / MeasureRate);
				  if (TimerCount < 0)
				  {
					 TimerCount = 0;
				  }			  
			      TIM_StartDecounter(SEC_CHECK_VALVE,
									 (UWORD16) TimerCount);
			  }
			  else
			  {
				  CycleCount = 0; 
				  TIM_StartDecounter(SEC_CHECK_VALVE,
					 	 (UWORD16) MAX_OCCLUSION_TIMER_DELAY);
			  }

/*%C        ALARM_CHECK_VALVE_U16 = ALARM_DETECTED 							  */
		      DB_AlarmStatusWrite(ALARM_CHECK_VALVE_U16,
		                          ALARM_DETECTED);
			  VEN_IsVtiExhUpdated = FALSE;

	      }
/*%C End if 																  */
	      Alarm_Error = NO_ERR_AL;
/*%C    Alarm_Error = NO_ERR_AL 											  */
     	   break;
	   }
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	   case ALARM_DETECTED :
	   {
/*%C     If COMPUTED_VTI_EXH_S16 >= - 4/10 COMPUTED_VTI_U16 and      */
/*%C		Valve current into the limits and  			  */
/*%C		Flow without negative saturation , then  			  */
	      if (  (ComputedVtiExh >= VtiDelta) 
				&& (VEN_ValveCurrentSat != TRUE)
				&& (VEN_FlowNegSat != TRUE))
	      {

               CycleCount = 0; 
/*%C      ALARM_CHECK_VALVE_U16 = ALARM_FALSE 								  */
	     	   DB_AlarmStatusWrite(ALARM_CHECK_VALVE_U16,
	     	                       ALARM_FALSE);
			   VEN_IsVtiExhUpdated = FALSE;
			   break;
	      }

        // Check if VTI exhalation has been
	    // updated.  If it has been updated and the check above doesn't 
		// change the alarm status to ALARM_FALSE, then increment a cycle count 
		// and wait for the next breath.
		if (VEN_IsVtiExhUpdated == TRUE )
	    {										 
/*%C        The cycle counter CycleCount is increased                         */
			CycleCount = CycleCount + 1;
			VEN_IsVtiExhUpdated = FALSE;
		}

/*%C      The delay is reached and COMPUTED_VTI_U16 >= 20 or   */
/* %C		 Valve current out of limits or Flow with negative saturation    */
		if (TIM_ReadDecounterValue(SEC_CHECK_VALVE) == 0)
		{
			if (CycleCount >= MAX_NUM_BREATHS_FOR_OCCLUSION_DETECTION)
			{
    	      if ( ((ComputedVti >= 20 ) 
    			||  (VEN_ValveCurrentSat == TRUE)
    			||  (VEN_FlowNegSat == TRUE)))  
    	      {
    /*%C      ALARM_CHECK_VALVE_U16 = ALARM_TRUE 								  */
    /*%C       the associated event is stored 									  */
    		      DB_AlarmStatusWrite(ALARM_CHECK_VALVE_U16,
    		                          ALARM_TRUE);
    		      DB_EventMngt(EVENT_AL_CHECK_VALVE);
    /*%C          the priority register is Up dated								  */
    		      SEC_High_Priority_1= SEC_High_Priority_1| 0x0080;
    	      }
            }
        }
    /*%C 	End if 																  */
/*%C    Alarm_Error = NO_ERR_AL 										      */
	      Alarm_Error = NO_ERR_AL;
	      break;
	   }
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	   case ALARM_TRUE :
	   {
/*%C     The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  */
/*%C     So there is no action to do .										  */
/*%C    Alarm_Error = NO_ERR_AL 											  */
	      Alarm_Error = NO_ERR_AL;
	      break;
	   }
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	   case ALARM_DISPLAYED	:
	   {
/*%C     If COMPUTED_VTI_EXH_S16 >= - 4/10 COMPUTED_VTI_U16 and      */
/*%C		Valve current into the limits, then  			  */
/*%C		Flow without negative saturation , then  			  */
	      if (  (ComputedVtiExh >= VtiDelta) 
				&& (VEN_ValveCurrentSat != TRUE)
				&& (VEN_FlowNegSat != TRUE))
	      {
/*%C        Init of cycles counter CycleCount                                 */
			  CycleCount = 0;
/*%C      ALARM_CHECK_VALVE_U16 = ALARM_FALSE 								  */
		      DB_AlarmStatusWrite(ALARM_CHECK_VALVE_U16,
		                          ALARM_FALSE);
		      SEC_High_Priority_1= SEC_High_Priority_1& 0xFF7F;
/*%C        The event of end of alarm is stored 							  */
		      DB_EventMngt(EVENT_AL_END_OF_CHECK_VALVE);
			  VEN_IsVtiExhUpdated = FALSE;
	      }
/*%C	 End if																  */
/*%C    Alarm_Error = NO_ERR_AL 											  */
	      Alarm_Error = NO_ERR_AL;
	      break;
	   }
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
/*%C	There is not cancellation for this alarm, so this state shall not be  */
/*%C	reached                                                               */
	   case ALARM_CANCELED :
	   {
/*%C    Alarm_Error = ERR_AL_CHECK_VALVE 									  */			
	      Alarm_Error = ERR_AL_CHECK_VALVE;
	      break;
	   }
/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	   default:
	   {
/*%C    Alarm_Error = ERR_AL_CHECK_VALVE 									  */	
  	      Alarm_Error = ERR_AL_CHECK_VALVE;
		   break;
	   }
   }

    MemoVentilState = VentilState;
/*%C End of Check Alarm state												  */
	return(Alarm_Error);
}

