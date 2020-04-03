/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Fio2Calibration.c                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            Management of the alarm leakage                               */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES                               */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_KeyboardEvent.h"
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "SEC_Fio2CalibrationNeeded.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_Fio2CalibrationNeeded(void)
{
/*%C UncancelCmd recovery from base                                           */
    UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
/*%C KeyboardDoublePulseInhibEvent recovery from base                         */
    UWORD16 KeyboardDoublePulseInhibEvent =    
                          DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
/*%C AlarmNeededFio2Calib recovery from base                                  */
    e_DB_ALARMS_STATE AlarmNeededFio2Calib =
                          DB_AlarmStatusRead(ALARM_NEEDED_FIO2_CALIB_U16);
/*%C Fio2OffsetDefault recovery from base                                     */
    e_DB_ALARMS_STATE Fio2OffsetDefault = 
                          DB_AlarmStatusRead(TECH_ALARM_FIO2_OFFSET_DEFAULT);
/*%C DetectedFio2Sensor recovery from base                                    */
    UWORD16 DetectedFio2Sensor = DB_ControlRead(DETECTED_FIO2_SENSOR);
/*%C CalibratedFio2Sensor recovery from base                                  */
    UWORD16 CalibratedFio2Sensor = DB_ControlRead(CALIBRATED_FIO2_SENSOR);
/*%C AdjustFio2 recovery from base                                            */
    UWORD16 AdjustFio2 = DB_ConfigRead(ADJUST_FIO2); 
/*%C Ventil authorization recovery from base                                  */
    UWORD16 Ventil_Authorization = DB_ControlRead(VENTIL_AUTHORIZATION_U16);
    e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

    switch(AlarmNeededFio2Calib)
    {
/******************************************************************************/
/*%C                            "FALSE" State                                 */
/******************************************************************************/
    case ALARM_FALSE :
/*%C    If TECH_ALARM_FIO2_OFFSET_DEFAULT = ALARM_DETECTED                    */
/*%C    or ( VENTIL_AUTHORIZATION_U16 = TRUE and DETECTED_FIO2_SENSOR = TRUE  */
/*%C    and CALIBRATED_FIO2_SENSOR = FALSE), then                             */
        if( (Fio2OffsetDefault == ALARM_DETECTED ) 
        ||( (Ventil_Authorization == TRUE)
         && (DetectedFio2Sensor == TRUE)
         && (CalibratedFio2Sensor == FALSE)))
        {
/*%C        ALARM_NEEDED_FIO2_CALIB_U16 = ALARM_TRUE                          */
            DB_AlarmStatusWrite(ALARM_NEEDED_FIO2_CALIB_U16, ALARM_TRUE);
/*%C        The associated event is launched                                  */
            DB_EventMngt(EVENT_AL_NEEDED_FIO2_CALIB );
/*%C        Updating priority register                                        */
            SEC_Medium_Priority_3 = SEC_Medium_Priority_3 | 0x0800;
        }
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                         "DETECTED" State                                 */
/******************************************************************************/
    case ALARM_DETECTED :
/*%C    Alarm_Error = ERR_AL_NEEDED_FIO2_CALIB                                */
        Alarm_Error = ERR_AL_NEEDED_FIO2_CALIB;
        break;
/******************************************************************************/
/*%C                             "TRUE" State                                 */
/******************************************************************************/
    case ALARM_TRUE :
/*%C    The following state ,"ALARM_DISPLAYED", is written by HMI module.     */
/*%C    So there is no action to do.                                          */
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                            "DISPLAYED" State                             */
/******************************************************************************/
    case ALARM_DISPLAYED :
/*%C    If DETECTED_FIO2_SENSOR = FALSE or CALIBRATED_FIO2_SENSOR = TRUE, then*/
        if((DetectedFio2Sensor == FALSE)
        || (CalibratedFio2Sensor == TRUE))
        {
/*%C        ALARM_NEEDED_FIO2_CALIB_U16 = ALARM_FALSE                         */
            DB_AlarmStatusWrite(ALARM_NEEDED_FIO2_CALIB_U16, ALARM_FALSE);
/*%C        Updating priority register                                        */
            SEC_Medium_Priority_3 = SEC_Medium_Priority_3 & 0xF7FF;
        }
/*%C    Else if KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE, then            */
        else if (KeyboardDoublePulseInhibEvent == TRUE)
        {
/*%C        ALARM_NEEDED_FIO2_CALIB_U16 = ALARM_CANCELED                      */
            DB_AlarmStatusWrite(ALARM_NEEDED_FIO2_CALIB_U16, ALARM_CANCELED);
/*%C        Updating priority register                                        */
            SEC_Medium_Priority_3 = SEC_Medium_Priority_3 & 0xF7FF;
        }
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;
/******************************************************************************/
/*%C                                  "CANCELED" State                        */
/******************************************************************************/
    case ALARM_CANCELED :
/*%C    If DETECTED_FIO2_SENSOR = FALSE or CALIBRATED_FIO2_SENSOR = TRUE, then*/
        if((DetectedFio2Sensor == FALSE)
        || (CalibratedFio2Sensor == TRUE))
        {
/*%C        ALARM_NEEDED_FIO2_CALIB_U16 = ALARM_FALSE                         */
            DB_AlarmStatusWrite(ALARM_NEEDED_FIO2_CALIB_U16, ALARM_FALSE);
/*%C        Updating priority register                                        */
            SEC_Medium_Priority_3 = SEC_Medium_Priority_3 & 0xF7FF;
        }
        /**********************************************************************/
        /*                         Reset of the "CANCELED" State              */
        /**********************************************************************/
                 
/*%C    If UNCANCEL_CMD_U16 == TRUE, then                                     */
        else if(UncancelCmd == TRUE)
        {
/*%C        ALARM_NEEDED_FIO2_CALIB_U16 = ALARM_TRUE                          */
            DB_AlarmStatusWrite(ALARM_NEEDED_FIO2_CALIB_U16, ALARM_TRUE);
/*%C        Updating priority register                                        */
            SEC_Medium_Priority_3 = SEC_Medium_Priority_3 | 0x0800;
        }
/*%C    Alarm_Error = NO_ERR_AL                                               */
        Alarm_Error = NO_ERR_AL;
        break;

/******************************************************************************/
/*%C                                  DEFAULT                                 */
/******************************************************************************/
    default:
/*%C    Alarm_Error = ERR_AL_NEEDED_FIO2_CALIB                                */
        Alarm_Error = ERR_AL_NEEDED_FIO2_CALIB;
        break;
    }
    return(Alarm_Error);
}
