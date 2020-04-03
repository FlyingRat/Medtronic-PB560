/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_SpeedDefault.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Speed blower default on starting                               */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "DB_Event.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_AlarmStatus.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "SEC_SpeedDefault.h"
#include "Security_Datas.h"
#include "Ventilation_Constants.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_SpeedDefault(void)
{
	UWORD16 VentilReq	= DB_ConfigRead(VENTIL_REQ_U16);
	UWORD16 VentilAuthorization = DB_ControlRead(VENTIL_AUTHORIZATION_U16);
	SWORD16 FilterSpeedBlower	
						= (SWORD16)(SWORD16)DB_ComputeRead(FILTER_SPEED_BLOWER_S16);
	UWORD16 TechAlarmSpeedDefault
						=	DB_AlarmStatusRead(TECH_ALARM_SPEED_DEFAULT_U16);
/*%C When the ventil request is made but not yet authorized */
/*%C and if the speed test delay is reached */
	if ( (VentilReq == TRUE) 
	  && (VentilAuthorization == FALSE) 
	  && (TIM_ReadDecounterValue(SEC_SPEED_BLOW_TIM) == 0) )
	{
/*%C 	if the speed blower is 20% lower or higher than the test speed */
/*%C 	and if the technical alarm is not true */
		if ( (((SWORD32)FilterSpeedBlower < ((SWORD32)cSPEED_BLOWER_TEST *8) /10)
	     || ((SWORD32)FilterSpeedBlower > ((SWORD32)cSPEED_BLOWER_TEST *12) /10))
   	&& (TechAlarmSpeedDefault != ALARM_TRUE) )
		{
/*%C 		Alarm is turned to true and stored with the associated event */
	      DB_AlarmStatusWrite(TECH_ALARM_SPEED_DEFAULT_U16,
	                          ALARM_TRUE);
	      DB_EventMngt(EVENT_ALT_SPEED );
	   }
/*%C 	A flag is set to indicate the end of speed test */
	 	SEC_SpeedTestEnded = TRUE;
	}
/*%C When the ventilation stops and if the alarm was true, */
/*%C alarm is turned to False and stored */
	else if ( (VentilAuthorization == FALSE) 
		 	 && (DB_AlarmStatusRead(TECH_ALARM_SPEED_DEFAULT_U16) != ALARM_FALSE) )
	{
		 DB_AlarmStatusWrite(TECH_ALARM_SPEED_DEFAULT_U16,
		                     ALARM_FALSE);
	}
	else if (VentilAuthorization == TRUE) 
	{
/*%C 	Speed Test flag reset */
	 	SEC_SpeedTestEnded = FALSE;
	}
}   