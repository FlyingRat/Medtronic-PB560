/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Disconnection.c                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Disconnection alarm Management                                 */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  Disconnection_Delay                                   */
/*%I                    LowPressure                                           */
/*%IO Input/Output :    NONE                                                  */
/*%O Output Parameter : Alarm_Error                                           */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES                               */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "DB_Event.h"
#include "DB_Control.h"
#include "Security_Datas.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "SEC_Disconnection.h"
#include "Ventilation_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_Disconnection(UWORD16 Disconnection_Delay,
                                         SWORD16 LowPressure)
{    
    e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/*%C VentilState recovery from base                                           */
    e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
/*%C MeasurePatientPressure recovery from base                                */
    SWORD16 MeasurePatientPressureProxi =
                (SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_PROXI_S16);
/*%C MeasureQinsp recovery from base                                          */
    SWORD16 MeasureQinsp = (SWORD16)DB_ComputeRead(MEASURE_QINSP_S16);
/*%C AlarmDisconnection recovery from base                                    */
    e_DB_ALARMS_STATE AlarmDisconnection =
                          DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);
/*%C AlarmHighPressure recovery from base                                     */
    e_DB_ALARMS_STATE AlarmHighPressure =
                          DB_AlarmStatusRead(ALARM_HIGH_PRESSURE_U16);

    // Store the low pressure limit of the circuit disconnect.
    VEN_CircuitDisconnectLowPressLimit = LowPressure;

/*%C Check ALARM_DISCONNECTION_U16 state                                      */
    switch(AlarmDisconnection)
    {
/******************************************************************************/
/*%C                                  "FALSE" State                           */
/******************************************************************************/
    case ALARM_FALSE :
/*%C    If ALARM_HIGH_PRESSURE_U16 <= ALARM_DETECTED                          */
/*%C    and MEASURE_PATIENT_PRESSURE_PROXI_S16 <= Low pressure                */
/*%C    or ( MEASURE_QINSP_S16 > cQMAXDISCONNECTION    and                    */
/*%c    VENTIL_STATE_U16 <>  VEN_EXHALATION, then                             */
        if ( (AlarmHighPressure <= ALARM_DETECTED)
            && ((MeasurePatientPressureProxi <= LowPressure) 
            || ((MeasureQinsp > cQMAXDISCONNECTION)
            && (VentilState != VEN_EXHALATION))) )
        {
/*%C        ALARM_DISCONNECTION_U16 = ALARM_DETECTED,                         */
            DB_AlarmStatusWrite(ALARM_DISCONNECTION_U16, ALARM_DETECTED);
/*%C        Starting the corresponding timer                                  */
            TIM_StartDecounter(SEC_LOW_PRESS, Disconnection_Delay);
        }
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "DETECTED" State                        */
/******************************************************************************/
    case ALARM_DETECTED :
/*%C    If MEASURE_PATIENT_PRESSURE_PROXI_S16 > Low pressure                        */
/*%C    and MEASURE_QINSP_S16 <= cQMAXDISCONNECTION after                     */
/*%C    the first 240 ms of inspiration phase                                 */
/*%C    or ALARM_HIGH_PRESSURE_U16 > ALARM_DETECTED, then                     */
        if ( ((MeasurePatientPressureProxi > LowPressure)
          && (MeasureQinsp <= cQMAXDISCONNECTION)
          && (VentilState != VEN_EXHALATION)
          && (TIM_ReadCounterValue(VEN_TI_COUNT) > cMININSPDELAY))
          || (AlarmHighPressure > ALARM_DETECTED) )          
        { 
/*%C        ALARM_DISCONNECTION_U16 = ALARM_FALSE                             */
            DB_AlarmStatusWrite(ALARM_DISCONNECTION_U16, ALARM_FALSE);
        }
/*%C    Else If timer reached delay, then                                          */
        else if (TIM_ReadDecounterValue(SEC_LOW_PRESS) == 0)
        { 
/*%C        ALARM_DISCONNECTION_U16 = ALARM_TRUE                              */
            DB_AlarmStatusWrite(ALARM_DISCONNECTION_U16, ALARM_TRUE);
/*%C        Corresponding event is stored                                     */
            DB_EventMngt(EVENT_AL_DISCONNECTION);
/*%C        Priority register updating for buzzer and leds command            */
            SEC_High_Priority_1 = SEC_High_Priority_1 | 0x0001;
        }
/*%C    End if                                                                   */
/*%C    Alarm_Error = NO_ERR_AL                                                  */
        Alarm_Error = NO_ERR_AL;
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
/*%C    If MEASURE_PATIENT_PRESSURE_PROXI_S16 > Low pressure                        */
/*%C    and MEASURE_QINSP_S16 <= cQMAXDISCONNECTION after                     */
/*%C    the first 240 ms of inspiration phase                                 */
/*%C    or ALARM_HIGH_PRESSURE_U16 > ALARM_DETECTED                           */
        if ( ((MeasurePatientPressureProxi > LowPressure)
          && (MeasureQinsp <= cQMAXDISCONNECTION)
          && (VentilState != VEN_EXHALATION)
          && (TIM_ReadCounterValue(VEN_TI_COUNT) > cMININSPDELAY))
          || (AlarmHighPressure > ALARM_DETECTED) )          
        { 
/*%C        ALARM_DISCONNECTION_U16 = ALARM_FALSE                             */
            DB_AlarmStatusWrite(ALARM_DISCONNECTION_U16, ALARM_FALSE);
/*%C        The end of alarm event is stored                                  */
            DB_EventMngt(EVENT_AL_END_OF_DISCONNECTION);
/*%C        Priority register updating for buzzer and leds command            */
            SEC_High_Priority_1 = SEC_High_Priority_1 & 0xFFFE;
        }
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "CANCELED" State                        */
/******************************************************************************/
    case ALARM_CANCELED :
/*%C    This alarm can't be canceled                                          */
/*%C    Alarm_Error = ERR_AL_DISCONNECTION                                    */
        Alarm_Error = ERR_AL_DISCONNECTION;
        break;

/******************************************************************************/
/*%C                                  DEFAULT                                 */
/******************************************************************************/
    default:
/*%C    Alarm_Error = ERR_AL_DISCONNECTION                                    */
        Alarm_Error = ERR_AL_DISCONNECTION;
        break;
    }
/*%C End of check ALARM_DISCONNECTION_U16 state                               */
    return(Alarm_Error);
}



