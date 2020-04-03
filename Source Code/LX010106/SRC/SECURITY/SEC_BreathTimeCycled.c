/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_BreathTimeCycled.c               									*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   					Management of breath time cycled			                  */
/*%C    This alarm is detected if 4 of the 6 last ends of PSV inspiration are */
/*%C    detected on time condition													     	*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter :	Alarm_Error  														*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Event.h"
#include "DB_KeyboardEvent.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "security_datas.h"
#include "SEC_BreathTimeCycled.h"
#include "Ventilation_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_BreathTimeCycled(void)
{
    e_BOOL OldBreathsModified = FALSE;
    UWORD16 l;
    UWORD16 j = 0;
    UWORD16 PsTimeEndCycleNumber = 0;
    e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
    static UWORD16 PreviousVentilState = VEN_VENTIL_DISABLE;
    e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);   
    e_DB_ALARMS_STATE Alarm_Breath_Time_Cycled =
        DB_AlarmStatusRead(ALARM_BREATH_TIME_CYCLED_U16);

    /* if we have an old sponateous breaths remove them from the alarm detection 
       criteria */
    for (l = 0; l < 6; l++)
    {
        if (VEN_SIMV_PS_End[l].EndType == PS_TIMED_END)
        {
            if (TIM_TestOverflowOk(VEN_SIMV_PS_End[l].TimerId))
            {
                VEN_SIMV_PS_End[l].EndType = PS_FLOW_END;
                OldBreathsModified = TRUE;
            }
        }
    }

    switch (Alarm_Breath_Time_Cycled)
    {
    /******************************************************************************/
    /*%C	         					 "FALSE" State                                  */
    /******************************************************************************/
    case ALARM_FALSE :
        /*%C 	At each respiration cycle													*/
        if ( ( (VentilState == VEN_EXHALATION)
               &&  (PreviousVentilState != VEN_EXHALATION) )
             || OldBreathsModified == TRUE)
        {
            /*%C 		If there are more than 4 PS timed ends, an alarm is detected			*/
            for (j = 0; j < 6; j++)
            {
                if (VEN_SIMV_PS_End[j].EndType == PS_TIMED_END)
                {
                    PsTimeEndCycleNumber += 1;
                }
            }
            if (PsTimeEndCycleNumber >= 4)
            {
                DB_AlarmStatusWrite(ALARM_BREATH_TIME_CYCLED_U16, ALARM_TRUE);
                /*%C 			Storage of the associated event (EVENT_AL_BREATH_TIME_CYCLED)*/
                DB_EventMngt(EVENT_AL_BREATH_TIME_CYCLED);
                /*%C  		Priority register update                                 */
                SEC_Medium_Priority_3 = SEC_Medium_Priority_3 | 0x0100;
            }
        }
        Alarm_Error = NO_ERR_AL;
        break;
        /******************************************************************************/
        /*%C	         					 "DETECTED" State 					               */
        /******************************************************************************/
    case ALARM_DETECTED :
        /*%C  No detected state  */
        Alarm_Error = ERR_AL_BREATH_TIME_CYCLED;
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
    case ALARM_DISPLAYED    :
        /*%C At each respiration cycle													*/
        if ( ( (VentilState == VEN_EXHALATION)
               &&   (PreviousVentilState != VEN_EXHALATION) )
             || OldBreathsModified == TRUE)
        {
            /*%C If there are less than 2 Psv cycles, the alarm is cancelled			*/
            for (j = 0; j < 6; j++)
            {
                if (VEN_SIMV_PS_End[j].EndType == PS_TIMED_END)
                {
                    PsTimeEndCycleNumber += 1;
                }
            }
            if (PsTimeEndCycleNumber <= 2)
            {
                DB_AlarmStatusWrite(ALARM_BREATH_TIME_CYCLED_U16, ALARM_FALSE);
                /*%C  	Priority register update                                 */
                SEC_Medium_Priority_3 = SEC_Medium_Priority_3 & 0xFEFF;
                /*%C 		Storage of the associated end of event (EVENT_AL_BREATH_TIME_CYCLED)*/
                DB_EventMngt(EVENT_AL_END_BREATH_TIME_CYCLED);

            }
        }

        /*%C  function return = no error	*/
        Alarm_Error = NO_ERR_AL;
        break;
        /******************************************************************************/
        /*%C	         					 "CANCELED" State                               */
        /******************************************************************************/
    case ALARM_CANCELED :
        /*%C  This alarm cannot be cancelled	*/
        Alarm_Error = ERR_AL_BREATH_TIME_CYCLED;
        break;

        /******************************************************************************/
        /*%C	         					 DEFAULT                                        */
        /******************************************************************************/
    default:
        /*%C 	function return = error	*/
        Alarm_Error = ERR_AL_BREATH_TIME_CYCLED;
        break;
    }

    /*%C Previous ventil state refresh					*/
    PreviousVentilState = VentilState;


    return(Alarm_Error);
}
