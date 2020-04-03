/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_TurbineOverheat.c                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  Management of turbine overheat alarm                    */
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
#include "Structure.h"
#include "DB_Event.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_KeyboardEvent.h"
#include "DB_AlarmStatus.h"
#include "security_datas.h"
#include "SEC_TurbineOverheat.h"
#include "Timer_Data.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_TurbineOverheat(void)
{
/*%C Alarm supply measure state recovery from base                            */
    e_DB_ALARMS_STATE Alarm_Turbine_Overheat =
                                DB_AlarmStatusRead(ALARM_TURBINE_OVERHEAT_U16);
/*%C Measure speed blower recovery from base                                  */
    UWORD16 MeasureSpeedBlower = DB_ComputeRead(MEASURE_SPEED_BLOWER_U16);
/*%C Measure blower temperature recovery from base                            */
    SWORD16 MeasureBlowerTemperature =
                       (SWORD16)DB_ComputeRead(MEASURE_BLOWER_TEMPERATURE_S16);
/*%C Blower command recovery from base                                        */
    UWORD16 BlowerCommand = DB_ComputeRead(BLOWER_COMMAND_U16);
    static UWORD16 PreviousBlowerCommand = 0;

/*%C Alarm error declaration                                                  */
    e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

    switch(Alarm_Turbine_Overheat)
    {
/******************************************************************************/
/*%C                                  "FALSE" State                           */
/******************************************************************************/
    case ALARM_FALSE :
/*%C    If (BLOWER_COMMAND_U16 <> PreviousBlowerCommand                       */
/*%C    or if BLOWER_COMMAND_U16 == 0    )                                    */
/*%C    and MEASURE_SPEED_BLOWER_U16 < 1000, then                             */      
        if (((BlowerCommand != PreviousBlowerCommand)
            ||(BlowerCommand == 0 ))    
            &&(MeasureSpeedBlower < 1000))
        {
/*%C        Associated timer is started                                       */
            TIM_StartDecounter(SEC_BLOWER_OVERHEAT, TIME_BLOWER_OVERHEAT);
/*%C        ALARM_TURBINE_OVERHEAT_U16 = ALARM_DETECTED                       */
            DB_AlarmStatusWrite(ALARM_TURBINE_OVERHEAT_U16, ALARM_DETECTED);
        }
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "DETECTED" State                        */
/******************************************************************************/
    case ALARM_DETECTED :
/*%C    If ( -30°C < MEASURE_BLOWER_TEMPERATURE_S16 and                       */
/*%C    MEASURE_BLOWER_TEMPERATURE_S16 < 70°C ) or                            */
/*%C    MEASURE_SPEED_BLOWER_U16 > 1000rpm, then                              */
        if (((MeasureBlowerTemperature < 700)  
            &&(MeasureBlowerTemperature > -300 ))
            ||(MeasureSpeedBlower > 1000)) 
        {
/*%C        ALARM_TURBINE_OVERHEAT_U16 = ALARM_FALSE                          */
            DB_AlarmStatusWrite(ALARM_TURBINE_OVERHEAT_U16, ALARM_FALSE);  
        }
/*%C    Else if timer reached delay, then                                     */
        else if (TIM_ReadDecounterValue(SEC_BLOWER_OVERHEAT) == 0)
        {
/*%C        ALARM_TURBINE_OVERHEAT_U16 = ALARM_TRUE                           */
            DB_AlarmStatusWrite(ALARM_TURBINE_OVERHEAT_U16, ALARM_TRUE);
/*%C        Associated event management                                       */
            DB_EventMngt(EVENT_AL_TURBINE_OVERHEAT);
/*%C        Updating priority register                                        */
            SEC_High_Priority_1 = SEC_High_Priority_1 | 0x0800;
        }
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "TRUE" State                            */
/******************************************************************************/
    case ALARM_TRUE :
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "DISPLAYED" State                       */
/******************************************************************************/
    case ALARM_DISPLAYED :
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "CANCELED" State                        */
/******************************************************************************/
    case ALARM_CANCELED :
/*%C    Alarm_Error = ERR_AL_TURBINE_OVERHEAT                                 */
        Alarm_Error = ERR_AL_TURBINE_OVERHEAT;
        break;
/******************************************************************************/
/*%C                                  DEFAULT                                 */
/******************************************************************************/
    default:
/*%C    Alarm_Error = ERR_AL_TURBINE_OVERHEAT                                 */
        Alarm_Error = ERR_AL_TURBINE_OVERHEAT;
        break;
    }
/*%C End check alarm state                                                    */
/*%C PreviousBlowerCommand = BLOWER_COMMAND_U16                               */
    PreviousBlowerCommand = BlowerCommand ;
    return(Alarm_Error);
}
