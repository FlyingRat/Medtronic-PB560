/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_PsimvMode.c                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   It schedules the alarms in the PSIMV mode                              */
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
#include "DB_Current.h"
#include "DB_Config.h"
#include "DB_AlarmStatus.h"
#include "DB_Event.h"
#include "SEC_PsimvMode.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_PsimvMode(void)
{
   	UWORD16 PiSetPoint = DB_CurrentRead(PI_SET_POINT_U16);
   	SWORD16 LowPress = 0;
   	UWORD16 LowPresDelay = 0;
	UWORD32 TempLowPresDelay = 0;
   	UWORD16 PressureValue = 0;
    UWORD16 Adjust_Control_R = DB_CurrentRead(ADJUST_CONTROL_R_U16);
	UWORD16 DisconnectionDelay = DB_CurrentRead(ADJUST_DISCONNECTION_DELAY_U16);
	UWORD16 ApneaAlarmActivation = DB_ConfigRead(APNEA_ALARM_ACTIVATION);
	/* Alarm apnea recovery from alarm status base                                */
	e_DB_ALARMS_STATE AlarmApnea = DB_AlarmStatusRead(ALARM_APNEA_U16);
   	UWORD16 Adjust_Ti_Control = DB_CurrentRead(ADJUST_TI_CONTROL_U16);

/*%C DISCONNECTION ALARM 													  */
/*%C LowPress = 80% PI_SET_POINT_U16										  */
	LowPress = (SWORD16)((PiSetPoint*8)/10);
/*%C LowPressDelay is  60/ADJUST_CONTROL_R_U16 plus TI control 				  */
	TempLowPresDelay = (UWORD32)(((1000*60) / Adjust_Control_R)+ Adjust_Ti_Control );
/*%C We have to check the robustness as	 TempLowPresDelay is an UWORD32 and*/
/*%C LowPresDelay is an UWORD16                                          */
	if(TempLowPresDelay >= 0x0000ffff)
	{
		LowPresDelay = 0xffff;
	}
	else
	{
		LowPresDelay = (UWORD16)TempLowPresDelay;
	}
/*%C take the biggest value between the disconnection delay adjsutment and the computed delay */
	if(DisconnectionDelay < LowPresDelay)
	{
		DisconnectionDelay = LowPresDelay;	
	}
	SEC_Disconnection(DisconnectionDelay,
	                  LowPress);

/*%C HIGH PRESSURE ALARM 													  */
/*%C Compute of the compare value for the alarm detection :					  */ 
/*%C if PI_SET_POINT_U16 < cTHIRTY_PRESSURE_THRESHOLD, then 				  */
	if (PiSetPoint < cTHIRTY_PRESSURE_THRESHOLD)
	{
/*%C PressureValue =  PI_SET_POINT_U16 + 5cmH2O							  	  */ 
		PressureValue = PiSetPoint + 50;
	}
/*%C Else 																	  */ 
	else
	{
/*%C PressureValue = PI_SET_POINT_U16 + 10cmH2O 							  */
		PressureValue = PiSetPoint + 100;
/*%C  If PressureValue > cHIGH_PRESSURE, then  							 	  */ 
		if (PressureValue > cHIGH_PRESSURE)
		{
/*%C	PressureValue = cHIGH_PRESSURE 										  */	
			PressureValue = cHIGH_PRESSURE;
		}
/*%C	End if 																  */
	}
/*%C	End if 																  */
	SEC_HighPressure(PressureValue);

/*%C Apnea flag management for SIMV Cycles */
    SEC_Simv_Apnea_Flag();

/*%C Apnea alarm is launched only if it is activated */	
	if(ApneaAlarmActivation == TRUE)
	{
/*%C APNEA ALARM 															  */
		SEC_ApneaSimv();
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

/*%C  HIGH VTI ALARM 														  */
	SEC_HighVti();

/*%C LOW VTI ALARM 															  */
	SEC_LowVti();

/*%C PROX DISCONNECTION ALARM 												  */	
	TempLowPresDelay = (UWORD32)DisconnectionDelay + 2000;
/*%C We have to check the limit	 TempLowPresDelay to be as an UWORD16 format */
	if(TempLowPresDelay >= 0x0000ffff)
	{
		TempLowPresDelay = 0x0000ffff;
	}
	SEC_ProxDisconnection((UWORD16)TempLowPresDelay);

/*%C  CHECK PRESSURE ALARM */
	SEC_CheckPressure(DisconnectionDelay);

/*%C  CHECK PROXIMAL ALARM */ 	 	 
	SEC_CheckProximal(DisconnectionDelay); 

/*%C 	VALVE PRESSURE ALARM */
	SEC_CheckValvePressure(DisconnectionDelay);

/*%C OCCLUSION ALARM 														  */
	SEC_Occlusion();

/*%C Breath Time Cycled alarm 												  */
	SEC_BreathTimeCycled();
/*%C  VALVE LEAKAGE ALARM */
	 SEC_ValveLeakage();
}