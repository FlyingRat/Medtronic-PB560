/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0104                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_InspiratoryFlowfailure.c                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C         Inspiratory Flow Failure Alarm management                        */
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
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "Security_Datas.h"
#include "ventilation_Datas.h"
#include "SEC_InspiratoryFlowFailure.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_InspiratoryFlowFailure(void)
{
    UWORD16 InspFlowFailure = 
						DB_AlarmStatusRead(ALARM_INSP_FLOW_FAILURE_U16);
    UWORD16 TurbineOverheat = 
						DB_AlarmStatusRead(ALARM_TURBINE_OVERHEAT_U16);
    UWORD16 Speeddefault = 
						DB_AlarmStatusRead(TECH_ALARM_SPEED_DEFAULT_U16);
    UWORD16 Disconnection = 
        DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);
    SWORD16 MeasureQinsp = DB_ComputeRead(MEASURE_QINSP_S16);
    e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
    /* maxi and mini are 1/10 liters											  */
    static SWORD16 maxi= -2000;
    static SWORD16 mini= 2000;   
    static e_VentilState MemoState = VEN_VENTIL_DISABLE;
    e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

    /*%C If MEASURE_QINSP_S16 > maxi 				 							  */
	if (maxi < MeasureQinsp)
	{
        /*%C then maxi = MEASURE_QINSP_S16 											  */
		maxi = MeasureQinsp;
	}
    /*%C End if																	  */

    /*%C If MEASURE_QINSP_S16 < mini 											  */
	if (mini > MeasureQinsp)
	{
        /*%C then mini = MEASURE_QINSP_S16 											  */
		mini = MeasureQinsp;
	}
    /*%C End if																	  */
    /*%C Check  ALARM_INSP_FLOW_FAILURE_U16 state 								  */
    switch (InspFlowFailure)
   {
    /******************************************************************************/
    /*%C	         					 "FALSE" State                            */
    /******************************************************************************/
	   case ALARM_FALSE :
	   {
	    if ( ( (maxi - mini) <  cDELTA_FLOW_LMN)
			&& (TurbineOverheat == ALARM_FALSE )
			&& (Speeddefault == ALARM_FALSE )
                 && (Disconnection == ALARM_FALSE )
			&& (VEN_SecondCycle == TRUE)
			&& (VentilState != VEN_EXHALATION)
	  		&& (MemoState == VEN_EXHALATION) )
	       {
                /*%C 		Associated event is stored										  */
                /*%C 		Priority register updating for buzzer and leds command 		  	  */
			DB_AlarmStatusWrite(ALARM_INSP_FLOW_FAILURE_U16, ALARM_TRUE);
			DB_EventMngt(EVENT_AL_INSP_FLOW_FAILURE);
			SEC_High_Priority_2 = SEC_High_Priority_2 | 0x0010;
	       }
	      Alarm_Error = NO_ERR_AL;
     	   break;
	   }
        /******************************************************************************/
        /*%C	         					 "DETECTED" State 					      */
        /******************************************************************************/
	   case ALARM_DETECTED :
	   {
            /*%C Alarm_Error = ERR_AL_INSP_FLOW_FAILURE									  */    
	      Alarm_Error = ERR_AL_INSP_FLOW_FAILURE;
	      break;
	   }
        /******************************************************************************/
        /*%C	         					 "TRUE" State							  */
        /******************************************************************************/
	   case ALARM_TRUE :
	   {
            /*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 		  */
            /*%C So there is no action to do .											  */
	      Alarm_Error = NO_ERR_AL;
	      break;
	   }
        /******************************************************************************/
        /*%C	         					 "DISPLAYED" State                        */
        /******************************************************************************/
	   case ALARM_DISPLAYED	:
	   {
	if ( ((maxi - mini) >  cDELTA_FLOW_LMN) 
		|| (TurbineOverheat == ALARM_TRUE)
                 || (Speeddefault == ALARM_TRUE) 
                 || (Disconnection == ALARM_TRUE ) )
   {
         DB_AlarmStatusWrite(ALARM_INSP_FLOW_FAILURE_U16, ALARM_FALSE);
                /*%C 	 Priority register updating for buzzer and leds command 		  	  */
         SEC_High_Priority_2= SEC_High_Priority_2& 0xFFEF;
                /*%C     The event of end of alarm is stored 								  */
		 DB_EventMngt(EVENT_AL_END_OF_INSP_FLOW_FAILURE);
   }
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
	      Alarm_Error = ERR_AL_INSP_FLOW_FAILURE;
	      break;
	   }
        /******************************************************************************/
        /*%C	         					 DEFAULT                                  */
        /******************************************************************************/
	   default:
	   {
  	      Alarm_Error = ERR_AL_INSP_FLOW_FAILURE;
		   break;
	   }
	}
	if ( (VentilState != VEN_EXHALATION)
	  && (MemoState == VEN_EXHALATION) )
	{
        /*%C  Then Init of the maxi and mini level 									  */
		maxi = -2000;
		mini = 2000;
	}
    /*%C  Up dating  ventil state in MemoState 									  */
	 	MemoState = VentilState;

    return(Alarm_Error);
}
