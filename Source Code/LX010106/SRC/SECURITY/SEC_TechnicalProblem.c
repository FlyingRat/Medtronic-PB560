/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_TechnicalProblem.c                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Management of alarm technical problem                          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Alarm_Error                                           */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES                               */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Event.h"
#include "DB_KeyboardEvent.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "SEC_TechnicalProblem.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_TechnicalProblem(void)
{
    e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/*%C MeasurePFIVoltage recovery from base                                     */
    UWORD16 MeasurePFIVoltage = DB_ComputeRead(MEASURE_PFI_VOLTAGE_U16);
/*%C AlarmTechnicalProblem recovery from base                                 */
    e_DB_ALARMS_STATE AlarmTechnicalProblem =
                               DB_AlarmStatusRead(ALARM_TECHNICAL_PROBLEM_U16);
/*%C KeyboardDoublePulseInhibEvent recovery from base                         */
    UWORD16 KeyboardDoublePulseInhibEvent =    
                        DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
/*%C UncancelCmd recovery from base                                           */
    UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
 
/*%C Check ALARM_TECHNICAL_PROBLEM_U16 state                                  */
    switch(AlarmTechnicalProblem)
    {
/******************************************************************************/
/*%C                                  "FALSE" State                           */
/******************************************************************************/
    case ALARM_FALSE :
/*%C    If  MEASURE_PFI_VOLTAGE_U16 >  cMAX_PFI, then                         */
        if(MeasurePFIVoltage > cMAX_PFI)
        {
/*%C        ALARM_TECHNICAL_PROBLEM_U16 = ALARM_TRUE                          */
            DB_AlarmStatusWrite(ALARM_TECHNICAL_PROBLEM_U16, ALARM_TRUE);
/*%C        Associated event is stored                                        */
            DB_EventMngt(EVENT_AL_TECHNICAL_PROBLEM); 
/*%C        Updating priority register                                        */ 
            SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | 0x2000;
        }
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "DETECTED" State                        */
/******************************************************************************/
    case ALARM_DETECTED :
/*%C    Immediate alarm                                                       */
/*%C    Alarm_Error = ERR_AL_TECHNICAL_PROBLEM                                */
        Alarm_Error = ERR_AL_TECHNICAL_PROBLEM;
        break;
/******************************************************************************/
/*%C                                  "TRUE" State                            */
/******************************************************************************/
    case ALARM_TRUE :
/*%C    The following state ,"ALARM_DISPLAYED", is written by HMI module.     */
/*%C    So there is no action to do.                                          */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "DISPLAYED" State                       */
/******************************************************************************/
    case ALARM_DISPLAYED    :
/*%C    If  MEASURE_PFI_VOLTAGE_U16 <=  cMAX_PFI, then                        */
        if (MeasurePFIVoltage <= cMAX_PFI)
        {
/*%C        ALARM_TECHNICAL_PROBLEM_U16 = ALARM_FALSE                         */
            DB_AlarmStatusWrite(ALARM_TECHNICAL_PROBLEM_U16, ALARM_FALSE);
/*%C        Associated event is stored                                        */
            DB_EventMngt(EVENT_AL_END_OF_TECHNICAL_PROBLEM);
/*%C        Updating priority register                                        */
            SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xDFFF;
       }

/*%C     Else if KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE, then           */
         else if (KeyboardDoublePulseInhibEvent == TRUE)
         {
/*%C         ALARM_TECHNICAL_PROBLEM_U16 = ALARM_CANCELED                     */
             DB_AlarmStatusWrite(ALARM_TECHNICAL_PROBLEM_U16, ALARM_CANCELED);
/*%C         Up dating priority register                                      */
             SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xDFFF;
        }
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "CANCELED" State                        */
/******************************************************************************/
    case ALARM_CANCELED :
/*%C    If  MEASURE_PFI_VOLTAGE_U16 <=  cMAX_PFI, then                        */
        if(MeasurePFIVoltage <= cMAX_PFI)
        {
/*%C        ALARM_TECHNICAL_PROBLEM_U16 = ALARM_FALSE                         */
            DB_AlarmStatusWrite(ALARM_TECHNICAL_PROBLEM_U16, ALARM_FALSE);
/*%C        Associated event is stored                                        */
            DB_EventMngt(EVENT_AL_END_OF_TECHNICAL_PROBLEM);
        }

        /**********************************************************************/
        /*                         Reset of the "CANCELED" State              */
        /**********************************************************************/

/*%C    Else If UNCANCEL_CMD_U16 = TRUE, then                                 */
        else if(UncancelCmd == TRUE)
        {
/*%C        ALARM_TECHNICAL_PROBLEM_U16 = ALARM_TRUE                          */
            DB_AlarmStatusWrite(ALARM_TECHNICAL_PROBLEM_U16, ALARM_TRUE);
/*%C        Updating priority register                                        */
            SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | 0x2000;
        }
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;

/******************************************************************************/
/*%C                                  DEFAULT                                 */
/******************************************************************************/
    default:
/*%C    Alarm_Error = ERR_AL_TECHNICAL_PROBLEM                                */
        Alarm_Error = ERR_AL_TECHNICAL_PROBLEM;
        break;
    }
/*%C End of check alarm state                                                 */
    return(Alarm_Error);
}



