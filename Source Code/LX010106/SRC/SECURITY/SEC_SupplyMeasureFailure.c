/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_SupplyMeasureFailure.c                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                       Management of measure supply alarm                 */
/*                                                                            */
/*                                                                            */
/*  Takes the status of the power supply and only alarms when the status shows*/
/*  a voltage issue for 5 seconds.  This allows for the voltages to settle and*/
/*  elimanates spurious alarm conditions when AC is removed and transitions to*/
/*  running on battery.  Thus reducing the momentary nusiance alarms. Testing */
/*  shows that the voltages settle out after approximately 600 ms.  5 seconds */
/*  should allow for plenty of margin.                                                                          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter :    Alarm_Error                                        */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES                               */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Event.h"
#include "DB_Control.h"
#include "DB_KeyboardEvent.h"
#include "DB_AlarmStatus.h"
#include "DB_PowerSupply.h"
#include "security_datas.h"
#include "SEC_SupplyMeasureFailure.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/* Time power supply failure needs to persist before annunciating alarm */
/* 5 seconds */
#define cTIME_Supply_Measure 5000

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_SupplyMeasureFailure(void)
{
/*%C Alarm supply measure state recovery from base                            */
    e_DB_ALARMS_STATE Alarm_Supply_Measure =
                                DB_AlarmStatusRead(ALARM_SUPPLY_MEASURE_U16);
/*%C Supply measure failure information from power supply base                */
    UWORD16 Supply_Measure_Failure =
                                DB_PowerSupplyRead(SUPPLY_MEASURE_FAILURE_U16);
/*%C Cancel request recovery from keyboard event base                         */
    UWORD16 KeyboardDoublePulseInhibEvent =    
                        DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
/*%C Uncancel command recovery from base                                      */
    UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
/*%C Alarm error declaration                                                  */
    e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

/*%C Check ALARM_SUPPLY_MEASURE_U16 state                                     */
    switch(Alarm_Supply_Measure)
    {
/******************************************************************************/
/*%C                                  "FALSE" State                           */
/******************************************************************************/
    case ALARM_FALSE :
/*%C    If SUPPLY_MEASURE_FAILURE_U16 = TRUE, then                            */
        if (Supply_Measure_Failure == TRUE)
        {
/*%C    ALARM_SUPPLY_MEASURE_U16 = ALARM_DETECTED                             */
            DB_AlarmStatusWrite(ALARM_SUPPLY_MEASURE_U16, ALARM_DETECTED);
            TIM_StartDecounter(SEC_CHECK_SUPPLY, cTIME_Supply_Measure);
        }
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "DETECTED" State                        */
/******************************************************************************/
    case ALARM_DETECTED :

        if (Supply_Measure_Failure == FALSE)
        {
            DB_AlarmStatusWrite(ALARM_SUPPLY_MEASURE_U16, ALARM_FALSE);
        }
        else
        {
            /* if power supply has detected issue for 5 seconds then alarm */
            if (TIM_ReadDecounterValue(SEC_CHECK_SUPPLY) == 0)
            {
/*%C    The alarm is set to TRUE immediatly                                   */
/*%C    ALARM_SUPPLY_MEASURE_U16 = ALARM_TRUE                                 */
        DB_AlarmStatusWrite(ALARM_SUPPLY_MEASURE_U16, ALARM_TRUE);
/*%C    Associated event is stored                                            */
        DB_EventMngt(EVENT_AL_SUPPLY_MEASURE);
/*%C    Priority register update                                              */
        SEC_Medium_Priority_3 = SEC_Medium_Priority_3 | 0x0001;
            }
        }
/*%C    Alarm_Error = NO_ERR_AL                                               */
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
    case ALARM_DISPLAYED :
/*%C    If SUPPLY_MEASURE_FAILURE_U16 = FALSE, then                           */
        if (Supply_Measure_Failure == FALSE)
        {
/*%C        ALARM_SUPPLY_MEASURE_U16 = ALARM_FALSE                            */
            DB_AlarmStatusWrite(ALARM_SUPPLY_MEASURE_U16, ALARM_FALSE);
/*%C        Associated event is stored                                        */
            DB_EventMngt(EVENT_AL_END_SUPPLY_MEASURE);
/*%C        Updating of priority register                                     */
            SEC_Medium_Priority_3 = SEC_Medium_Priority_3 & 0xFFFE;
        }
/*%C    End if                                                                */    
/*%C    If KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE, then                 */
        if (KeyboardDoublePulseInhibEvent == TRUE )
        {
/*%C        ALARM_SUPPLY_MEASURE_U16 = ALARM_CANCELED                         */
            DB_AlarmStatusWrite(ALARM_SUPPLY_MEASURE_U16, ALARM_CANCELED);
/*%C        Updating of priority register                                     */
            SEC_Medium_Priority_3 = SEC_Medium_Priority_3 & 0xFFFE;
        }
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "CANCELED" State                        */
/******************************************************************************/
    case ALARM_CANCELED :
/*%C    If SUPPLY_MEASURE_FAILURE_U16 = FALSE, then                           */
        if (Supply_Measure_Failure == FALSE)
        {
/*%C        ALARM_SUPPLY_MEASURE_U16 = ALARM_FALSE                            */
            DB_AlarmStatusWrite(ALARM_SUPPLY_MEASURE_U16, ALARM_FALSE);
/*%C        Associated event is stored                                        */
            DB_EventMngt(EVENT_AL_END_SUPPLY_MEASURE);
        }
/*%C    End if                                                                */
        /**********************************************************************/
        /*                         Reset of the "CANCELED" State              */
        /**********************************************************************/
/*%C    If aUNCANCEL_CMD_U16 = TRUE, then                                     */
        if (UncancelCmd == TRUE)
        {
/*%C        ALARM_SUPPLY_MEASURE_U16 = ALARM_TRUE                             */
            DB_AlarmStatusWrite(ALARM_SUPPLY_MEASURE_U16, ALARM_TRUE);
/*%C        Updating of priority register for leds & buzzer                   */
            SEC_Medium_Priority_3 = SEC_Medium_Priority_3 | 0x0001;
        }
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */ 
        Alarm_Error = NO_ERR_AL;
        break;

/******************************************************************************/
/*%C                                  DEFAULT                                 */
/******************************************************************************/
    default:
/*%C    Alarm_Error = ERR_AL_SUPPLY_MEASURE                                   */
        Alarm_Error = ERR_AL_SUPPLY_MEASURE;
        break;
    }
/*%C End of check alarm state                                                 */
    return(Alarm_Error);
}
