/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CalibrationFailure.c                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Management of Low battery level alarm   				                     */
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
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_KeyboardEvent.h"
#include "security_datas.h"
#include "SEC_CalibrationFailure.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_CalibrationFailure(void)
{
/* Alarm low battery state recovery from base                                 */
	e_DB_ALARMS_STATE AlarmCalibrationFailure =
								DB_AlarmStatusRead(ALARM_CALIBRATION_FAIL_U16);
/* Cancel request recovery from keyboard event base                           */
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
/* Uncancel command recovery from base                             			   */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
/* Alarm error declaration					                  		               */
 	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;


switch(AlarmCalibrationFailure)
{
/******************************************************************************/
/*%C	         					 "FALSE" State                                  */
/******************************************************************************/
	case ALARM_FALSE :
/*%C  No treatment, the alarm is set to detected during the calibration of 	*/
/*%C  the exhalation flow                                                   	*/
	   Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					               */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C  The alarm is set to TRUE immediatly  */
      DB_AlarmStatusWrite(ALARM_CALIBRATION_FAIL_U16, ALARM_TRUE);
/*%C  Associated event management                                 */
      DB_EventMngt(EVENT_AL_CALIBRATION);
/*%C  Priority register updating for buzzzer and leds command                 */
      SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0100;

	   Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "TRUE" State												*/
/******************************************************************************/
	case ALARM_TRUE :
/*%C  The following state ,"ALARM_DISPLAYED", is written by HMI module. */
/*%C  So there is no action to do .*/
	   Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                              */
/******************************************************************************/
	case ALARM_DISPLAYED	:

/*%C  This alarm is only cancellable with a cancel request */

/*%C  Cancellation of the alarm if displayed and on key inhib long push detect*/
	   if (KeyboardDoublePulseInhibEvent == TRUE )
 	   {
		   DB_AlarmStatusWrite(ALARM_CALIBRATION_FAIL_U16, ALARM_CANCELED);
/*%C  	Priority register updating for buzzzer and leds command              */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 & 0xFEFF;
	   }

/*%C  function return = no error	*/
      Alarm_Error = NO_ERR_AL;
	   break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :

/*%C The only condition for a return to false state is the uncancel request  */

		/******************************************************************/
		/*		 				Reset of the "CANCELED" State                   */
		/******************************************************************/

/*%C If a command of inhibition of the cancel, is true, */
/*%C then the alarm is set to TRUE */
	if(UncancelCmd == TRUE)
	{
/*%C  Storage of alarm True state */
   	DB_AlarmStatusWrite(ALARM_CALIBRATION_FAIL_U16, ALARM_TRUE);
/*%C  Priority register updating for buzzzer and leds command                 */
		SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0100;
	} 

	Alarm_Error = NO_ERR_AL;
	break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
/*%C function return = error	*/
  	Alarm_Error = ERR_AL_LOW_BATTERY;
	break;
}

	return(Alarm_Error);
}
