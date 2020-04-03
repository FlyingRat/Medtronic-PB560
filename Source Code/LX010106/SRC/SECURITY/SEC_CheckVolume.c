/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CheckVolume.c                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Management of the Volume alarm (Checking required)                     */
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
#include "SEC_CheckVolume.h"
#include "security_datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CheckVolume(void)
{
/* Ventilation Mode recovery from base 										  */
    e_MODE_TYPES Current_Mode = DB_ControlRead(CURRENT_MODE_U16);
	e_VEN_SIMVCycle VEN_SIMVCycle = DB_ControlRead(SIMV_CYCLES_U16);

/* Alarm CheckVolume recovery from base 									  */	
	e_DB_ALARMS_STATE AlarmHighPressure =
								DB_AlarmStatusRead(ALARM_HIGH_PRESSURE_U16);
/* Alarm High Pressure recovery from base 									  */	
	e_DB_ALARMS_STATE AlarmCheckVolume =
								DB_AlarmStatusRead(ALARM_CHECK_VOLUME_U16);
/* Alarm Inspiratory flow failure recovery from base 						  */	
	e_DB_ALARMS_STATE InspFlowFailure = 
								DB_AlarmStatusRead(ALARM_INSP_FLOW_FAILURE_U16);
/* Alarm Disconnection recovery from base 									  */
	e_DB_ALARMS_STATE AlarmDisconnection =
								DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);
	UWORD16 AdjustVolControl = DB_CurrentRead(ADJUST_VOL_CONTROL_U16);
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16); 
/* Saturation state of autoadaptative Volume loop 							  */
	UWORD16 flowSatFlag = DB_ControlRead(FLOW_SAT_FLAG_U16); 
	static e_VentilState MemoVentilState = VEN_EXHALATION;
	static UWORD16 CIFCycleCounter = 0;
	static UWORD16 WaitCycle = FALSE;
	UWORD16 OverVolControl = FALSE;
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
	UWORD16 ComputedVti = DB_ComputeRead(COMPUTED_VTI_U16);
   
/*%C if COMPUTED_VTI_U16 < (ADJUST_VOL_CONTROL_U16 - ADJUST_VOL_CONTROL_U16 / 10)*/
   if(ComputedVti < AdjustVolControl - (AdjustVolControl / 10))
   {
/*%C  Then OverVolControl = TRUE											  */
      OverVolControl = TRUE;
   }
/*%C else, the OverVolControl flag is set to FALSE  						  */
   else
   {
      OverVolControl = FALSE;
   }

 /*%C Check ALARM_CHECK_VOLUME_U16 state 									  */
   switch(AlarmCheckVolume)
   {
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
      case ALARM_FALSE:
		{
/*%C     CIFCycleCounter Counter reset 										  */ 
	      CIFCycleCounter = 0;

/*%C     if OverVolControl = TRUE and WaitCycle = TRUE and 					  */
/*%C     ALARM_INSP_FLOW_FAILURE_U16 = FALSE, then 	  	  					  */
         if ( (OverVolControl == TRUE)
           && (WaitCycle == TRUE)
		   && (InspFlowFailure == ALARM_FALSE) )
         {
/*%C     	ALARM_CHECK_VOLUME_U16 = ALARM_DETECTED  						  */
            DB_AlarmStatusWrite(ALARM_CHECK_VOLUME_U16,
			                      ALARM_DETECTED);
         }
/*%C End if																	  */
/*%C Alarm_Error = NO_ERR_AL 												  */
	      Alarm_Error = NO_ERR_AL;
	      break;
		}
/******************************************************************************/
/*%C	         					 "DETECTED" State 			              */
/******************************************************************************/
      case ALARM_DETECTED :
		{
/*%C If WaitCycle = TRUE, then 												  */
         if (WaitCycle == TRUE)
         {
/*%C        if OverVolControl = FALSE or  									  */
/*%C 		ALARM_DISCONNECTION_U16 >= ALARM_TRUE or FLOW_SAT_FLAG_U16 = FALSE*/
/*%C		or ALARM_INSP_FLOW_FAILURE_U16 >= ALARM_TRUE					  */
            if ((OverVolControl == FALSE)
				|| (AlarmDisconnection >= ALARM_TRUE) 
				|| (flowSatFlag==FALSE)
				|| (InspFlowFailure >= ALARM_TRUE) )

            {
/*%C         Then ALARM_CHECK_VOLUME_U16 = ALARM_FALSE    					  */
   	         DB_AlarmStatusWrite(ALARM_CHECK_VOLUME_U16,
   			                     ALARM_FALSE);
            }
/*%C        Else If CIFCycleCounter <= 6									  */
      	   else if (CIFCycleCounter <= 6)
	         {
/*%C           Then Increase cycles counter CIFCycleCounter					  */
		         CIFCycleCounter = CIFCycleCounter + 1;
	         }
/*%C 		End if															  */
         }
/*%C End if 															   	  */
/*%C     If CIFCycleCounter > 6 and ALARM_DISCONNECTION_U16 < ALARM_TRUE and  */
/*%C	 ALARM_HIGH_PRESSURE_U16 < ALARM_TRUE, then 						  */
	     	if ((CIFCycleCounter > 6) && (AlarmDisconnection < ALARM_TRUE) && (AlarmHighPressure < ALARM_TRUE))
		   {
/*%C        ALARM_CHECK_VOLUME_U16 =  ALARM_TRUE 							  */
/*%C 		Associated event is stored										  */
			   DB_EventMngt(EVENT_AL_CHECK_VOLUME );
			   DB_AlarmStatusWrite(ALARM_CHECK_VOLUME_U16, ALARM_TRUE);
/*%C		   Priority register updating for buzzer and leds command 		  */
			   SEC_High_Priority_1= SEC_High_Priority_1| 0x0100;
		   }
/*%C	 End if 															  */
/*%C Alarm_Error = NO_ERR_AL 												  */
	      Alarm_Error = NO_ERR_AL;
	      break;
		}
/******************************************************************************/
/*%C	         					 "TRUE" State				  			  */
/******************************************************************************/
      case ALARM_TRUE :
		{
/*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  	  */
/*%C So there is no action to do.									      	  */
/*%C Alarm_Error = NO_ERR_AL 												  */
	      Alarm_Error = NO_ERR_AL;
         break;
		}
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	   case ALARM_DISPLAYED	:
		{
/*%C     If (OverVolControl = FALSE & WaitCycle = TRUE) 					  */
/*%C or ALARM_DISCONNECTION_U16 > ALARM_TRUE or  							  */
/*%C ALARM_HIGH_PRESSURE_U16 > ALARM_TRUE or  								  */
/*%C ALARM_INSP_FLOW_FAILURE_U16 > ALARM_TRUE, then 	 					  */
			if ( ( (OverVolControl == FALSE) && (WaitCycle == TRUE) )
    			 ||(AlarmDisconnection >= ALARM_TRUE)
				 ||(AlarmHighPressure >= ALARM_TRUE)
				 || (InspFlowFailure >= ALARM_TRUE) ) 
               
			{
/*%C        ALARM_CHECK_VOLUME_U16 = ALARM_FALSE,							  */
   				DB_AlarmStatusWrite(ALARM_CHECK_VOLUME_U16,
   			                    ALARM_FALSE);
 				DB_EventMngt(EVENT_AL_END_OF_CHECK_VOLUME);
/*%C			Priority register updating for buzzer and leds command        */
				SEC_High_Priority_1= SEC_High_Priority_1& 0xFEFF;
			}
/*%C End if 																  */
/*%C Alarm_Error = NO_ERR_AL 												  */
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
/*%C Alarm_Error = ERR_AL_CHECK_VOLUME 										  */
	      Alarm_Error = ERR_AL_CHECK_VOLUME;
	      break;
		}
/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	   default:
  	   {
/*%C Alarm_Error = ERR_AL_CHECK_VOLUME 										  */
  	      Alarm_Error = ERR_AL_CHECK_VOLUME;
			break;
		}
   }
/*%C End of Check Alarm state												  */

/*%C If (CURRENT_MODE_U16 = VOL or (CURRENT_MODE_U16 = VSIMV and 			  */ 
/*%C ( SIMV_CYCLES_U16 = CAV_Cycle or SIMV_CYCLES_U16 = CV_Cycle))) and		  */
/*%C ( VENTIL_STATE_U16 = VEN_EXHALATION and								  */
/*%C (MemoVentilState = VEN_INSPIRATION_CONTROLED  or 						  */
/*%C MemoVentilState = VEN_INSPIRATION_TRIGGERED))					 		  */
   if (
         (  
         (Current_Mode == VOL)
         ||( (Current_Mode == VSIMV) && ( (VEN_SIMVCycle == CAV_Cycle) || (VEN_SIMVCycle == CV_Cycle) ) ) 
         )
	   &&
         (   
         (VentilState == VEN_EXHALATION)
         && ( (MemoVentilState == VEN_INSPIRATION_CONTROLED) || (MemoVentilState == VEN_INSPIRATION_TRIGGERED) )
         )
	  )
   {
/*%C Then WaitCycle = TRUE													  */
      WaitCycle = TRUE;      
   }
/*%C else,  WaitCycle =  FALSE 												  */
   else
   {
      WaitCycle = FALSE;      
   }
/* End if 																	  */
/*%C Updating previous ventilation state 									  */
	MemoVentilState = VentilState;

	return(Alarm_Error);
}
