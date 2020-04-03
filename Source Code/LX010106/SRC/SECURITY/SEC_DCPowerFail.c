/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_DCPowerFail.c                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Management of Loss DC Power alarm (Checking required)                  */
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
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_PowerSupply.h"
#include "DB_KeyboardEvent.h"
#include "SEC_DCPowerFail.h"
#include "security_datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_DCPowerFail(void)
{
/*%C Alarm DC power fail recovery from base	                                  */
	e_DB_ALARMS_STATE AlarmDCPowerFail =
								DB_AlarmStatusRead(ALARM_DC_POWER_FAIL_U16);
/*%C Alarm check supply recovery from base	                                  */
	e_DB_ALARMS_STATE AlarmCheckSupply =
								DB_AlarmStatusRead(ALARM_CHECK_SUPPLY_U16);	
/*%C Power type recovery from base	                                   		  */
	UWORD16 PowerType	= DB_PowerSupplyRead(POWER_TYPE_U16);
/*%C AC selected state recovery from base                             		  */
	UWORD16 ACSelected =	DB_ControlRead(AC_SELECTED_U16);
/*%C Uncancel command recovery from base                             		  */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
 	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/*%C Power type memorization					                              */
	static UWORD16 MemoPowerType = NONE;
/*%C Cancel request recovery from keyboard event base                         */
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);

	static UWORD16 LOW_DC_POWER_FAIL = 0x0004;

/*%C Check ALARM_DC_POWER_FAIL_U16 state*/
	switch(AlarmDCPowerFail)			
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
		if ( (AlarmCheckSupply == ALARM_FALSE)
		  && (PowerType == BATTERY)
		  && (MemoPowerType == DC) )
		{
		   DB_AlarmStatusWrite(ALARM_DC_POWER_FAIL_U16, ALARM_TRUE);
		   DB_EventMngt(EVENT_AL_DC_POWER_FAIL);
           SEC_Low_Priority = SEC_Low_Priority | LOW_DC_POWER_FAIL;
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         			  "DETECTED" State				               	  */
/******************************************************************************/
	case ALARM_DETECTED :
		Alarm_Error = ERR_AL_DC_POWER_FAIL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State				  			  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C The following state ,"ALARM_DISPLAYED", is written by HMI module. 		  */
/*%C So there is no action to do .											  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
		if  ( (AlarmCheckSupply == ALARM_FALSE) 
			 && (PowerType == DC) )
		{
			DB_AlarmStatusWrite(ALARM_DC_POWER_FAIL_U16, ALARM_FALSE);
            DB_EventMngt(EVENT_DC_RETURN);
			SEC_Low_Priority = SEC_Low_Priority & (~LOW_DC_POWER_FAIL);
 		}
		else if ( ( (AlarmCheckSupply == ALARM_FALSE)
					&& (PowerType == AC) )
				 || ( (AlarmCheckSupply != ALARM_FALSE)
					&& (ACSelected == TRUE) ) ) 
		{
			DB_AlarmStatusWrite(ALARM_DC_POWER_FAIL_U16, ALARM_FALSE);
			SEC_Low_Priority = SEC_Low_Priority & (~LOW_DC_POWER_FAIL);
 		}
		else if (KeyboardDoublePulseInhibEvent == TRUE )
	 	{
			DB_AlarmStatusWrite(ALARM_DC_POWER_FAIL_U16, ALARM_CANCELED);
			SEC_Low_Priority = SEC_Low_Priority & (~LOW_DC_POWER_FAIL);
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
		if ( ( (AlarmCheckSupply == ALARM_FALSE) 
		    && ( (PowerType != BATTERY) ) )

		  || ( (AlarmCheckSupply != ALARM_FALSE)
			 && (ACSelected == TRUE) ) )
		{
			DB_AlarmStatusWrite(ALARM_DC_POWER_FAIL_U16, ALARM_FALSE);
			DB_EventMngt(EVENT_DC_RETURN);
 		}

		/******************************************************************/
		/*		 				Reset of the "CANCELED" State             */
		/******************************************************************/

		else if(UncancelCmd == TRUE)
		{
	   	DB_AlarmStatusWrite(ALARM_DC_POWER_FAIL_U16, ALARM_TRUE);
        SEC_Low_Priority = SEC_Low_Priority | LOW_DC_POWER_FAIL;
		} 
		Alarm_Error = NO_ERR_AL;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
	  	Alarm_Error = ERR_AL_DC_POWER_FAIL;
		break;
	}
	if (PowerType != NONE)
	{
		MemoPowerType = PowerType;
	}
	return(Alarm_Error);
}
