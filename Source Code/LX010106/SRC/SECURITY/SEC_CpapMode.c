/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CpapMode.c                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   It schedules the alarms in the CPAP mode                               */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Current.h"
#include "DB_Config.h"
#include "DB_AlarmStatus.h"
#include "DB_Event.h"
#include "SEC_CpapMode.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_CpapMode(void)
{
	UWORD16 AdjustPeep = 0;
	SWORD16 LowPress = 0;
	UWORD16 LowPresDelay = 0;
	UWORD32 TempLowPresDelay = 0;
	UWORD16 PressureValue = 0;
	UWORD16 AdjustApnea = DB_CurrentRead(ADJUST_APNEA_U16);
	UWORD16 DisconnectionDelay = DB_CurrentRead(ADJUST_DISCONNECTION_DELAY_U16);
	UWORD16 ApneaAlarmActivation = DB_ConfigRead(APNEA_ALARM_ACTIVATION);
	/* Alarm apnea recovery from alarm status base                                */
	e_DB_ALARMS_STATE AlarmApnea = DB_AlarmStatusRead(ALARM_APNEA_U16);

/*%C DISCONNECTION ALARM 													  */
/*%C LowPress = 80% COMPUTED_PI_SET_POINT_U16 								  */
	LowPress = (SWORD16)((DB_CurrentRead(PI_SET_POINT_U16)*8)/10);

	TempLowPresDelay = (UWORD32)AdjustApnea + 2000;
/*%C We have to check the robustness as	 TempLowPresDelay is an UWORD32 and*/
/*%C LowPresDelay is an UWORD16 */
	if(TempLowPresDelay >= 0x0000ffff)
	{
		LowPresDelay = 0xffff;
	}
	else
	{
		LowPresDelay = (UWORD16)TempLowPresDelay;		
	}
/*%C If ADJUST_APNEA_U16 + 2s < TIME_LOW_PRESS, then 						  */
   if (LowPresDelay < DisconnectionDelay)
   { 
/*%C	LowPresDelay = min between ADJUST_DISCONNECTION_DELAY_U16 and  ADJUST_APNEA_U16 + 2s */
		LowPresDelay = DisconnectionDelay; 
   } 
/*%C End if 		  */

	SEC_LeakDisconnection(LowPresDelay);
	


/*%C HIGH PRESSURE ALARM 													  */
/*	Adjust peep recovery from base 										  */
	AdjustPeep = DB_CurrentRead(ADJUST_PEEP_U16);
/*%C Compute of the compare value for the alarm detection :					  */ 
/*%C PressureValue =  ADJUST_PEEP_U16 + 10cmH2O 					 	  */
	PressureValue = AdjustPeep + 100;
/*%C High pressure value saturated to cHIGH_PRESSURE cmH2O 						 	  */
/*%C If PressureValue >  cHIGH_PRESSURE cmH2O			  							  */
	if (PressureValue > cHIGH_PRESSURE)
	{
/*%C Then PressureValue = cHIGH_PRESSURE cmH2O										  */
		PressureValue = cHIGH_PRESSURE;
	}
/*%C End if 																  */

	SEC_HighPressure(PressureValue);

/*%C Apnea alarm is launched only if it is activated */	
	if(ApneaAlarmActivation == TRUE)
	{
/*%C APNEA ALARM 															  */
		SEC_Apnea();
	}
	else if	 (AlarmApnea != ALARM_FALSE)
	{
/*%C 	ALARM_APNEA_U16 = ALARM_FALSE										  */
		DB_AlarmStatusWrite(ALARM_APNEA_U16,
	   						  ALARM_FALSE );
/*%C	Associated event is stored											  */
		DB_EventMngt(EVENT_AL_END_OF_APNEA );
/*%C  Updating of the priority register for leds & buzzer 					  */
		SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xFFFE;
	}

/*%C Controlled Cycles                                                        */
	SEC_ControlledCycles();

/*%C HIGH VTI ALARM															  */
	SEC_HighVti();

/*%C LOW VTI ALARM 															  */
	SEC_LowVti();

/*%C PROX DISCONNECTION ALARM 		    */
	TempLowPresDelay = (UWORD32)LowPresDelay + 2000;
/*%C We have to check the limit	 TempLowPresDelay to be as an UWORD16 format */
	if(TempLowPresDelay >= 0x0000ffff)
	{
		TempLowPresDelay = 0x0000ffff;
	}												  	
    SEC_ProxDisconnection((UWORD16)TempLowPresDelay);


/*%C Leak Occlusion*/
	SEC_LeakOcclusion();

/*%C  CHECK PRESSURE ALARM */
	SEC_CheckPressure(LowPresDelay);

/*%C  CHECK PROXIMAL ALARM */ 	 	 
    SEC_CheckProximal(LowPresDelay); 


}