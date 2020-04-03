/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : KEY_Event.c                                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description :                                                */
/*%C Keyboard Events management                                               */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/



/******************************************************************************/
/*                              INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_KeyboardEvent.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "Timer_Data.h"
#include "System_Datas.h"
#include "KEY_Event.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void KEY_Event(void)
{
    UWORD16 i = 0;
    UWORD16 AutoRepeatTimerIndex = 0;
    UWORD16 Timer_OverFlow = FALSE;
    UWORD16 Timer_Decounter_Value = 0;

    /*%c Short pulses detection for all the keys */
    for (i = 0;i < Number_of_key;i++)
    {
        /*%C Test the id of the Key */
        switch (i)
        {
        /******************************************************************************/
        /*%C             FOR KEY = UP                             */
        
        case  KEY_CODE_UP:
            {
                /*%C if Pulse field or autorepeat field  is true */              
                if ((SYS_Num_Keyboard[i].pulse == TRUE)
                    || (SYS_Num_Keyboard[i].AutoRepeatPush == TRUE))
                {
                    /*%C Storage of the associated event in Database */
                    DB_KeyboardEventWrite(KEYBOARD_UP_EVENT_U16,
                                          TRUE);
                    /*%C reset the auto repeat field of the key */
                    SYS_Num_Keyboard[i].AutoRepeatPush = FALSE;
                    /*%C if Pulse field or autorepeat field  is false */
                }
                else
                {
                    /*%C Long push field of the key is turned to true */
                    if (SYS_Num_Keyboard[i].EventLongPush == TRUE)
                    {
                        /*%C Storage of the associated event in Database */
                        DB_KeyboardEventWrite(KEYBOARD_LONG_UP_EVENT_U16,
                                              TRUE);
                        /*%C reset the long push field of the key */
                        SYS_Num_Keyboard[i].EventLongPush = FALSE;
                        /*%C The auto repeat field of the key is turned to true */
                        SYS_Num_Keyboard[i].AutoRepeatSelected = TRUE;
                        /*%C Starting decounting for auto repeat delay */
                        TIM_StartDecounter(KEY_DELAY_BETWEEN_LONG_AUTOREPEAT,
                                           cKEY_LongBetweenAutoDelay); 
                    }
                }
                break;
            }
            /******************************************************************************/
            /*%C   FOR KEY = DOWN                                     */

        case  KEY_CODE_DOWN:
            {
                /*%C if Pulse field or autorepeat field  is true */          
                if ((SYS_Num_Keyboard[i].pulse == TRUE)
                    || (SYS_Num_Keyboard[i].AutoRepeatPush == TRUE))
                {
                    /*%C Storage of the associated event in Database  */
                    DB_KeyboardEventWrite(KEYBOARD_DOWN_EVENT_U16,
                                          TRUE);
                    /*%C reset the auto repeat field of the key */
                    SYS_Num_Keyboard[i].AutoRepeatPush = FALSE;
                    /*%C if Pulse field or autorepeat field  is false */
                }
                else
                {
                    /*%C Long push field of the key is turned to true */
                    if (SYS_Num_Keyboard[i].EventLongPush == TRUE)
                    {
                        /*%C Storage of the associated event in Database */
                        DB_KeyboardEventWrite(KEYBOARD_LONG_DOWN_EVENT_U16,
                                              TRUE);
                        /*%C reset the long push field of the key */
                        SYS_Num_Keyboard[i].EventLongPush = FALSE;
                        /*%C The auto repeat field of the key is turned to true */ 
                        SYS_Num_Keyboard[i].AutoRepeatSelected = TRUE;
                        /*%C Starting decounting for auto repeat delay */
                        TIM_StartDecounter(KEY_DELAY_BETWEEN_LONG_AUTOREPEAT,
                                           cKEY_LongBetweenAutoDelay); 
                    }
                }
                break;
            }
            /******************************************************************************/
            /*%C   FOR KEY = VALID                                   */

        case  KEY_CODE_VALID:
            {
                /*%C if Pulse field  is true */      
                if (SYS_Num_Keyboard[i].pulse == TRUE)
                {
                    /*%C Storage of the associated event in Database  */
                    DB_KeyboardEventWrite(KEYBOARD_VALID_EVENT_U16,
                                          TRUE);
                }
                /*%C if Pulse field  is false */
                else
                {
                    /*%C if Long Push field  is true */
                    if (SYS_Num_Keyboard[i].EventLongPush == TRUE)
                    {
                        /*%C Storage of the associated event in Database  */
                        DB_KeyboardEventWrite(KEYBOARD_LONG_VALID_EVENT_U16,
                                              TRUE);
                        /*%C reset the long push field of the key */
                        SYS_Num_Keyboard[i].EventLongPush = FALSE;
                    }
                }
                break;
            }

            /******************************************************************************/
            /*%C   FOR KEY = MONIT                                    */

        case  KEY_CODE_MONIT:
            {
                /*%C if Pulse field  is true */      
                if (SYS_Num_Keyboard[i].pulse == TRUE)
                {
                    /*%C If the double pulse time out is reached */       
                    if (TIM_ReadDecounterValue(KEY_DOUBLE_PULSE_TIME_OUT) == 0)
                    {
                        /*%C Storage of the associated event in Database  */
                        /*%C Pulse is TRUE => double pulse and long are FALSE  */
                        DB_ControlWrite(CANCEL_ALARM_ASKED,TRUE);
                        DB_KeyboardEventWrite(KEYBOARD_INHIB_EVENT_U16,
                                              TRUE);
                        DB_KeyboardEventWrite(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16,
                                              FALSE);
                        DB_KeyboardEventWrite(KEYBOARD_LONG_INHIB_EVENT_U16,
                                              FALSE);
                        /*%C Double pulse timer launch (3s)           */
                        TIM_StartDecounter(KEY_DOUBLE_PULSE_TIME_OUT,
                                           TIME_DOUBLE_PULSE);
                    }
                    else
                    {
                        /*%C Storage of the associated event in Database  */
                        /*%C Double pulse is TRUE => pulse and long are FALSE  */
                        DB_KeyboardEventWrite(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16,
                                              TRUE);
                        DB_KeyboardEventWrite(KEYBOARD_INHIB_EVENT_U16,
                                              FALSE);
                        DB_KeyboardEventWrite(KEYBOARD_LONG_INHIB_EVENT_U16,
                                              FALSE);
                        /*%C The double pulse is detected, the timer is set to zero  */
                        TIM_TableOfCntAndDecnt[KEY_DOUBLE_PULSE_TIME_OUT].value = 0;
                        TIM_TableOfCntAndDecnt[KEY_DOUBLE_PULSE_TIME_OUT].type = 0;
                        TIM_TableOfCntAndDecnt[KEY_DOUBLE_PULSE_TIME_OUT].activate
                            = FALSE;
                    }
                }
                else
                {
                    if (SYS_Num_Keyboard[i].EventLongPush == TRUE)
                    {
                        /*%C Storage of the associated event in Database  */
                        /*%C Long push is TRUE => pulse and double pulse are FALSE  */
                        DB_KeyboardEventWrite(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16,
                                              FALSE);
                        DB_KeyboardEventWrite(KEYBOARD_INHIB_EVENT_U16,
                                              FALSE);
                        DB_KeyboardEventWrite(KEYBOARD_LONG_INHIB_EVENT_U16,
                                              TRUE);
                        SYS_Num_Keyboard[i].EventLongPush = FALSE;
                    }
                }
                break;
            }

            /******************************************************************************/
            /*%C   FOR KEY = NAVIG                                    */


        case  KEY_CODE_NAVIG:
            {
                /*%C if Pulse field  is true */      
                if (SYS_Num_Keyboard[i].pulse == TRUE)
                {
                    /*%C Storage of the associated event in Database  */
                    DB_KeyboardEventWrite(KEYBOARD_NAVIG_EVENT_U16,
                                          TRUE);
                }
                /*%C if Pulse field  is false */
                else
                {
                    /*%C if Long Push field  is true */
                    if (SYS_Num_Keyboard[i].EventLongPush == TRUE)
                    {
                        /*%C Storage of the associated event in Database  */
                        DB_KeyboardEventWrite(KEYBOARD_LONG_NAVIG_EVENT_U16,
                                              TRUE);
                        /*%C reset the long push field of the key */
                        SYS_Num_Keyboard[i].EventLongPush = FALSE;
                    }
                }
                break;
            }


            /******************************************************************************/
            /*%C   FOR KEY  = MONIT & DOWN                            */

        case  KEY_CODE_MONIT_AND_DOWN:
            {
                /*%C if Pulse field  is true */      
                if (SYS_Num_Keyboard[i].pulse == TRUE)
                {
                    /*%C Storage of the associated event in Database */
                    DB_KeyboardEventWrite(KEYBOARD_BRIGHTNESS_DOWN_EVENT_U16,
                                          TRUE);
                }
                /*%C if Pulse field  is false */
                else
                {
                    /*%C if Long Push field  is true */
                    if (SYS_Num_Keyboard[i].EventLongPush == TRUE)
                    {
                        /*%C reset the long push field of the key */
                        SYS_Num_Keyboard[i].EventLongPush = FALSE;
                    }
                }
                break;
            }

            /******************************************************************************/
            /*%C     FOR KEY = MONIT & UP                             */

        case  KEY_CODE_MONIT_AND_UP:
            {
                /*%C if Pulse field  is true */      
                if (SYS_Num_Keyboard[i].pulse == TRUE)
                {
                    /*%C Storage of the associated event in Database */
                    DB_KeyboardEventWrite(KEYBOARD_BRIGHTNESS_UP_EVENT_U16,
                                          TRUE);
                }
                /*%C if Pulse field  is false */
                else
                {
                    /*%C if Long Push field  is true */
                    if (SYS_Num_Keyboard[i].EventLongPush == TRUE)
                    {
                        /*%C reset the long push field of the key */
                        SYS_Num_Keyboard[i].EventLongPush = FALSE;
                    }
                }
                break;
            }

            /******************************************************************************/
            /*%C   FOR KEY = UP & DOWN                                */

        case  KEY_CODE_UP_AND_DOWN:
            {
                /*%C if Long Push field  is true */      
                if (SYS_Num_Keyboard[i].EventLongPush == TRUE)
                {
                    /*%C Storage of the associated event in Database  */
                    DB_KeyboardEventWrite(KEYBOARD_LOCK_EVENT_U16,
                                          TRUE);
                    /*%C reset the long push field of the key */
                    SYS_Num_Keyboard[i].EventLongPush = FALSE;
                }
                break;
            }

#ifdef CONFIG_REGUL_O2
            /******************************************************************************/
            /*%C   FOR KEY = 100 % O2                                 */


        case  KEY_CODE_100_O2:
            {
                if (SYS_Num_Keyboard[i].pulse == TRUE)
                {
                    DB_KeyboardEventWrite(KEYBOARD_100_FIO2, TRUE);
                }
                else
                {
                    if (SYS_Num_Keyboard[i].EventLongPush == TRUE)
                    {
                        DB_KeyboardEventWrite(KEYBOARD_LONG_100_FIO2,TRUE);
                        SYS_Num_Keyboard[i].EventLongPush = FALSE;
                    }
                }
                break;

                break;
            }
#endif
            /******************************************************************************/
            /*%C          DEFAULT                                     */

            /*%C All the fields of keyboard event database have to be set to             */
            /*%C "KEYBOARD_NO_EVENT" value                 */
        default:
            {

                /* Nothing is done, the events are reset by HMI					*/

                break;
            }

        }

        /******************************************************************************/
        /*%C LONG PRESS Management...and ventilation "start/stop" treatment...    */
        /*%C ...Auto-repeat mode		                                          */

        if (SYS_Num_Keyboard[i].level == TRUE)
        {
            // the key is pressed (level is TRUE)

            if (SYS_Num_Keyboard[i].MutexLongPush == FALSE)
            {
                // long push timer for this key is not active (mutex is FALSE)...
                // start its long push timer 
                TIM_StartDecounter((e_TIM_TABLE_ID)i,
                                   SYS_Num_Keyboard[i].TimerLongPush);
                // and set the long push timer mutex to indicate the timer has started
                SYS_Num_Keyboard[i].MutexLongPush = TRUE;

                if (i == KEY_CODE_STARTSTOPVENTIL)
                {
                    if (DB_ConfigRead(VENTIL_REQ_U16) == TRUE)
                    {
                        if (SYS_WaitingForStopConfirm == TRUE)
                        {
                            // ventilating... start key pressed waiting for stop vent confirmation
                            // shutdown confirmed
                            DB_KeyboardEventWrite(KEYBOARD_STOP_VENTIL_EVENT_U16,
                                                  TRUE);
                            SYS_WaitingForStopConfirm = FALSE;
                            TIM_StopDecounter(KEY_CONFIRM_VENT_STOP_TIMER);

                            // Sound a validation bip to confirm key press
                            DB_ControlWrite(VALIDATION_BIP_U16,
                                            BIP_SHORT);
                        }
                        else
                        {
                            // ventilating... start key pressed to stop ventilation 
                            DB_KeyboardEventWrite(KEYBOARD_START_VENTIL_DOWN_EVENT_U16,
                                                  TRUE);
                            SYS_MutexStartStopVentilUP = TRUE;
                            SYS_MutexStopInfoVentil = TRUE;
                        }
                    }
                    else
                    {
                        // not ventilating... start key pressed to start ventilation
                        DB_KeyboardEventWrite(KEYBOARD_START_VENTIL_UP_EVENT_U16,
                                              TRUE);
                    }
                }
                else
                {
                    if (SYS_WaitingForStopConfirm == TRUE)
                    {
                        // pressing a key other than start/stop while in the WaitingForStopConfirm
                        // state cancels the shutdown process

                        // record vent up to signal the controller to redisplay monitored data
                        DB_KeyboardEventWrite(KEYBOARD_START_VENTIL_UP_EVENT_U16,
                                              TRUE);
                        SYS_WaitingForStopConfirm = FALSE;
                        TIM_StopDecounter(KEY_CONFIRM_VENT_STOP_TIMER);
                    }
                }
            }
            else
            {
                // the long push timer is already active
                Timer_OverFlow = TIM_TestOverflowOk((e_TIM_TABLE_ID)i);
                if (Timer_OverFlow == TRUE)
                {
                    // the long push timer is active and has expired

                    if ( (i == KEY_CODE_STARTSTOPVENTIL)
                         && (SYS_MutexStopInfoVentil == TRUE) )
                    {
                        // the start/stop ventilation button has been pressed for 3 seconds
                        // in the StopInfoVentil "hold for 3 sec" state

                        // record the KEYBOARD_CONFIRM_STOP_VENTIL_EVENT_U16 in the database 
                        // to activate the "press start/stop again to confirm stop" message
                        DB_KeyboardEventWrite(KEYBOARD_CONFIRM_STOP_VENTIL_EVENT_U16,
                                              TRUE);

                        // Sound the stop bip (2 bips) 
                        DB_ControlWrite(VALIDATION_BIP_U16,
                                        BIP_STOP_VENTIL);

                        SYS_MutexStopInfoVentil = FALSE;
                        /*%C The timer must not be launched again, if the level is not go down*/
                        /*%C then the "MutexStartStopVentilUP" flag must have */
                        /*%C the "FALSE" value*/
                    }
                    else
                    {
                        // key id is not KEY_CODE_STARTSTOPVENTIL
                        SYS_Num_Keyboard[i].EventLongPush = TRUE;
                    }
                }
                else
                {
                    // the long push timer is not active or has not expired
                    /*%C Auto-repeat mode management after a long press :*/
                    /*%C If Auto-repeat is "TRUE" and the decounter of  */
                    /*%C "SYS_DELAY_BETWEEN_LONG_AUTOREPEAT is equal to 0 :*/
                    Timer_Decounter_Value = 
                        TIM_ReadDecounterValue(KEY_DELAY_BETWEEN_LONG_AUTOREPEAT); 
                    if ((SYS_Num_Keyboard[i].AutoRepeatSelected == TRUE)
                        && (Timer_Decounter_Value == 0))
                    {

                        /*%C then the index of Autorepeat timer is the index "i"  with */
                        /*%C the offset "end_of_keyboard_longpush_decnt"*/             
                        AutoRepeatTimerIndex = i+ end_of_keyboard_longpush_decnt;
                        /*%C if the mutex value of autorepeat for the selected key */
                        /*%C is "FALSE"*/
                        if (SYS_Num_Keyboard[i].MutexAutoRepeatPush==FALSE)
                        {
                            /*%C then the mutex of autorepeat get a "TRUE" value , and the*/
                            /*%C decounter associated to the "AutoRepeatTimerIndex" is   */
                            /*%C initialized with "100ms" value*/
                            SYS_Num_Keyboard[i].MutexAutoRepeatPush=TRUE;
                            TIM_StartDecounter((e_TIM_TABLE_ID)AutoRepeatTimerIndex,
                                               cKEY_AutoRepeatDelay);  
                        }
                        /*%C if the mutex value of autorepeat for the selected key */
                        /*%C is "TRUE"*/
                        else
                        {
                            /*%C then, if the "Timer_OverFlow" of "AutoRepeatTimerIndex" */
                            /*%C is true, then SYS_Num_Keyboard[i].MutexAutoRepeatPush*/
                            /*%C get "FALSE" value and SYS_Num_Keyboard[i].AutoRepeatPush*/
                            /*%C get "TRUE" value */
                            Timer_OverFlow = TIM_TestOverflowOk(
                                                               (e_TIM_TABLE_ID)AutoRepeatTimerIndex);
                            if (Timer_OverFlow == TRUE)
                            {
                                SYS_Num_Keyboard[i].MutexAutoRepeatPush=FALSE; 
                                SYS_Num_Keyboard[i].AutoRepeatPush=TRUE;               
                            }
                        }
                    }
                }
            }
        }
        else
        {
            // the key is released 

            if ((i == KEY_CODE_STARTSTOPVENTIL)
                && (SYS_WaitingForStopConfirm == TRUE))
            {
                if (TIM_ReadDecounterValue(KEY_CONFIRM_VENT_STOP_TIMER) == 0)
                {
                    // the vent stop confirmation timer is active and has expired
                    // record the ventilation up event in the database (ventilation never stopped)
                    // this signals the controller to redisplay monitored data
                    DB_KeyboardEventWrite(KEYBOARD_START_VENTIL_UP_EVENT_U16,
                                          TRUE);
                    SYS_WaitingForStopConfirm = FALSE;
                    TIM_StopDecounter(KEY_CONFIRM_VENT_STOP_TIMER);
                }
            }
            else if ((i == KEY_CODE_STARTSTOPVENTIL)
                     && (SYS_MutexStartStopVentilUP == TRUE))
            {
                // the start/stop ventilation key has been released and the Start/Stop
                // Ventilation process is active (MutexStartStopVentilUP is TRUE)
                if (TIM_ReadDecounterValue((e_TIM_TABLE_ID)i) == 0)
                {
                    // wait for the start/stop button down event to confirm stop
                    SYS_WaitingForStopConfirm = TRUE;
                    TIM_StartDecounter(KEY_CONFIRM_VENT_STOP_TIMER,
                                       TIME_CONFIRM_VENT_STOP_TIMEOUT);
                }
                else
                {
                    // the start/stop ventilation button pressed timer has not expired 
                    // record the ventilation up event in the database (ventilation never stopped)
                    // this signals the controller to redisplay monitored data
                    DB_KeyboardEventWrite(KEYBOARD_START_VENTIL_UP_EVENT_U16,
                                          TRUE);
                }
                // reset the start/stop ventilation mutex to allow another stop attempt
                SYS_MutexStartStopVentilUP = FALSE;
            }
            /*%C otherwise SYS_Num_Keyboard[i].EventLongPush get "FALSE" value	 */
            /*%C 	       SYS_Num_Keyboard[i].AutoRepeatPush get "FALSE" value	  */
            /*%C 	       SYS_Num_Keyboard[i].MutexLongPush get "FALSE" value */
            /*%C 	       SYS_Num_Keyboard[i].AutoRepeatSelected get "FALSE" value */
            /*%C 	       SYS_Num_Keyboard[i].MutexAutoRepeatPush get "FALSE" value*/
            SYS_Num_Keyboard[i].EventLongPush = FALSE;
            SYS_Num_Keyboard[i].AutoRepeatPush = FALSE;
            SYS_Num_Keyboard[i].MutexLongPush = FALSE;
            SYS_Num_Keyboard[i].AutoRepeatSelected = FALSE;
            SYS_Num_Keyboard[i].MutexAutoRepeatPush= FALSE;
        }
    }
    /*EOF*/
}