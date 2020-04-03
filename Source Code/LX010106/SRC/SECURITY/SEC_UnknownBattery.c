/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_UnknownBattery.c                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   Management of the alarm unknow battery                 */
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
#include "DB_AlarmStatus.h"
#include "DB_PowerSupply.h"
#include "SEC_UnknownBattery.h"      
#include "security_datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
 e_ALARM_ERROR SEC_UnknownBattery(void)
{
/*%C Alarm check supply state recovery from base                              */
    e_DB_ALARMS_STATE AlarmCheckSupply 
                                    = DB_AlarmStatusRead(ALARM_CHECK_SUPPLY_U16);

/*%C Alarm unknown battery state recovery from base                           */
    UWORD16 AlarmUnknownBattery = DB_AlarmStatusRead(ALARM_UNKNOWN_BATTERY_U16);

/*%C Unknown battery flag recovery from base                                  */
    UWORD16 UnknownBattery = DB_PowerSupplyRead(UNKNOWN_BATTERY_U16);

/*%C Force alarm used when small batteries have to be used                    */
	UWORD16 SmallBattForceAlarm = SEC_ForceUnknownBattery();

/*%C Alarm_Error = NO_ERR_AL                                                  */
    e_ALARM_ERROR Alarm_Error = NO_ERR_AL;


/*%C Check ALARM_UNKNOWN_BATTERY_U16 state                                    */
    switch(AlarmUnknownBattery)            
    {
/******************************************************************************/
/*%C                                  "FALSE" State                           */
/******************************************************************************/
    case ALARM_FALSE :
/*%C If (ALARM_CHECK_SUPPLY_U16 = ALARM_FALSE and UNKNOWN_BATTERY_U16 = TRUE) 
     or (SmallBattForceAlarm = TRUE)                                          */
/*%C then                                                                     */
        if (( (AlarmCheckSupply == ALARM_FALSE)
           && (UnknownBattery == TRUE) ) || (SmallBattForceAlarm == TRUE))
        {
/*%C        ALARM_UNKNOWN_BATTERY_U16 = ALARM_TRUE                            */
            DB_AlarmStatusWrite(ALARM_UNKNOWN_BATTERY_U16, ALARM_TRUE);
/*%C        Associated event is stored                                        */
            DB_EventMngt(EVENT_AL_UNKNOWN_BATTERY);
/*%C        Updating of priority register                                     */
            SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0020;
        }
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;               
        break;                                      
/******************************************************************************/
/*%C                                  "DETECTED" State                        */
/******************************************************************************/
    case ALARM_DETECTED :
/*%C    Alarm_Error = ERR_AL_UNKNOW_BATTERY                                   */
        Alarm_Error = ERR_AL_UNKNOW_BATTERY;
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
/*%C If (ALARM_CHECK_SUPPLY_U16 <> ALARM_FALSE or UNKNOWN_BATTERY_U16 = FALSE)
     and (SmallBattForceAlarm = FALSE)                                        */
/*%C then                                                                     */
        if (( (AlarmCheckSupply != ALARM_FALSE)
          || (UnknownBattery == FALSE) ) && (SmallBattForceAlarm == FALSE))
        {
/*%C        ALARM_UNKNOWN_BATTERY_U16 = ALARM_FALSE                           */
            DB_AlarmStatusWrite(ALARM_UNKNOWN_BATTERY_U16, ALARM_FALSE);
/*%C        Associated event is stored                                        */
            DB_EventMngt(EVENT_AL_END_OF_UNKNOWN_BATTERY);
/*%C        Updating the priority register                                    */
            SEC_Medium_Priority_2 = SEC_Medium_Priority_2 & 0xFFDF;
        }
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "CANCELED" State                        */
/******************************************************************************/
    case ALARM_CANCELED :
/*%C    Alarm_Error = ERR_AL_UNKNOW_BATTERY                                   */
        Alarm_Error = ERR_AL_UNKNOW_BATTERY;
        break;
/******************************************************************************/
/*%C                                  DEFAULT                                 */
/******************************************************************************/
    default:
/*%C    Alarm_Error = ERR_AL_UNKNOW_BATTERY                                   */
        Alarm_Error = ERR_AL_UNKNOW_BATTERY;
        break;
    }
/*%C End check alarm state                                                    */
    return(Alarm_Error);
}
