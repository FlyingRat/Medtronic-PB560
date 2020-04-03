/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0104                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_LeakOcclusion.c                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          Leak occlusion Alarm management                                 */
/*%C                                                                          */
/*%C	This alarm is used to signal patient rebreathing                      */
/*%C	ComputedVtiExh variable used to measure tidal volue in the            */
/*%C    negative direction                                                    */
/*%C    ComputedVti variable tidal volume using inspiratory flow sensor       */
/*%C                                                                          */
/*%C                                                                          */
/*%C                                                                          */
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
#include "DB_AlarmStatus.h"
#include "Security_Datas.h"
#include "SEC_LeakOcclusion.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_LeakOcclusion(void)
{
	SWORD16 ComputedVtiExh = (SWORD16)DB_ComputeRead(COMPUTED_VTI_EXH_S16);
	UWORD16 ComputedVti = DB_ComputeRead(COMPUTED_VTI_U16);
	e_DB_ALARMS_STATE AlarmLeakOcclusion= DB_AlarmStatusRead(ALARM_LEAK_OCCLUSION_U16);
 	SWORD16 VtiDelta = - (SWORD16)((ComputedVti*4)/10);
   e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/*%C Check ALARM_LEAK_OCCLUSION_U16 state */
   switch(AlarmLeakOcclusion)
   {
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	   case ALARM_FALSE :
	   {
/*%C     If COMPUTED_VTI_EXH_S16 < - 2/10 COMPUTED_VTI_U16, then  			  */
	      if (ComputedVtiExh < VtiDelta)
	      {
/*%C        ALARM_LEAK_OCCLUSION_U16 = ALARM_DETECTED 							  */
		      DB_AlarmStatusWrite(ALARM_LEAK_OCCLUSION_U16,
		                          ALARM_DETECTED);
/*%C 		default timer is started 									 	  */
		      TIM_StartDecounter(SEC_LEAK_OCCLUSION,
		                         TIME_SEC_LEAK_OCCLUSION);
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
/*%C     If COMPUTED_VTI_EXH_S16 >= - 2/10 COMPUTED_VTI_U16, then  			  */
	      if (ComputedVtiExh >= VtiDelta)
	      {
/*%C      ALARM_LEAK_OCCLUSION_U16 = ALARM_FALSE 								  */
	     	   DB_AlarmStatusWrite(ALARM_LEAK_OCCLUSION_U16,
	     	                       ALARM_FALSE);
	      }
/*%C      Else if the default delay is reached and COMPUTED_VTI_U16 >= 20     */
	      else if ((TIM_ReadDecounterValue(SEC_LEAK_OCCLUSION) == 0) && (ComputedVti >= 20 ))  
	      {
/*%C      ALARM_LEAK_OCCLUSION_U16 = ALARM_TRUE 								  */
/*%C       the associated event is stored 									  */
		      DB_AlarmStatusWrite(ALARM_LEAK_OCCLUSION_U16,
		                          ALARM_TRUE);
		      DB_EventMngt(EVENT_AL_LEAK_OCCLUSION);
/*%C          the priority register is Up dated								  */
		      SEC_High_Priority_2= SEC_High_Priority_2|0x0004; 
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
/*%C     If COMPUTED_VTI_EXH_S16 >= - 2/10 COMPUTED_VTI_U16, then  			  */
	      if (ComputedVtiExh >= VtiDelta)
	      {
/*%C      ALARM_LEAK_OCCLUSION_U16 = ALARM_FALSE 								  */
		      DB_AlarmStatusWrite(ALARM_LEAK_OCCLUSION_U16,
		                          ALARM_FALSE);
		      SEC_High_Priority_2= SEC_High_Priority_2& 0xFFFB;
/*%C        The event of end of alarm is stored 							  */
		      DB_EventMngt(EVENT_AL_END_OF_LEAK_OCCLUSION);
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
	      Alarm_Error = ERR_AL_LEAK_OCCLUSION;
	      break;
	   }
/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	   default:
	   {
/*%C    Alarm_Error = ERR_AL_CHECK_VALVE 									  */	
  	      Alarm_Error = ERR_AL_LEAK_OCCLUSION;
		   break;
	   }
   }
/*%C End of Check Alarm state												  */
	return(Alarm_Error);
}

