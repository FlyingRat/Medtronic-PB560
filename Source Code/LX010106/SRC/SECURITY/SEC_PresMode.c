/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_PresMode.c                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   It schedules the alarms in the PRES mode                               */
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
#include "enum.h"
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "SEC_PresMode.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_PresMode(void)
{
	SWORD16 LowPress = 0;
	UWORD16 LowPresDelay = 0;
	UWORD32 TempDisconnectionDelay = 0;
	UWORD16 PressureValue = 0;
    UWORD16 Adjust_Control_R = DB_CurrentRead(ADJUST_CONTROL_R_U16);
	UWORD16 ComputedPiSetPoint = DB_ComputeRead(COMPUTED_PI_SET_POINT_U16);
    UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);
	UWORD16 DisconnectionDelay = DB_CurrentRead(ADJUST_DISCONNECTION_DELAY_U16);

/* Disconnection delay :*/
	TempDisconnectionDelay = (UWORD32)((1000*60)/Adjust_Control_R);
/*%C We have to check the robustness as	 TempLowPresDelay is an UWORD32 and*/
/*%C LowPresDelay is an UWORD16                                          */
	if(TempDisconnectionDelay >= 0x0000ffff)
	{
		LowPresDelay = 0xffff;
	}
	else
	{
		LowPresDelay = (UWORD16)TempDisconnectionDelay;
	}
/* It must be the max between its adjustment and 60/rate */
	if(DisconnectionDelay < LowPresDelay)
	{
		DisconnectionDelay = LowPresDelay;
	}
	
/*%C HIGH PRESSURE ALARM 													  */
/*%C Compute of the compare value for the alarm detection :					  */ 
/*%C if COMPUTED_PI_SET_POINT_U16 < cTHIRTY_PRESSURE_THRESHOLD, then  				  */ 
	if (ComputedPiSetPoint < cTHIRTY_PRESSURE_THRESHOLD) 
	{
/*%C PressureValue = PI_SET_POINT_U16 + 5cmH2O 								  */
		PressureValue = ComputedPiSetPoint + 50;
	} 
/*%C else 																	  */ 
	else 
	{
/*%C 	PressureValue = COMPUTED_PI_SET_POINT_U16 + 10cmH2O 							  */
		PressureValue = ComputedPiSetPoint + 100;
/*%C 	if PressureValue > cHIGH_PRESSURE, then  							  */ 
		if (PressureValue > cHIGH_PRESSURE)
		{
/*%C	 PressureValue = cHIGH_PRESSURE										  */
			PressureValue = cHIGH_PRESSURE;
		}
/*%C 	End if 																  */
	}

/*%C 	End if 																  */
	SEC_HighPressure(PressureValue);

/*%C HIGH VTI ALARM															  */
	SEC_HighVti();

/*%C LOW VTI ALARM 															  */
	SEC_LowVti();

/*%C PROX DISCONNECTION ALARM												  */
	TempDisconnectionDelay = (UWORD32)DisconnectionDelay + 2000;
/*%C We have to check the limit	 TempLowPresDelay to be as an UWORD16 format */
	if(TempDisconnectionDelay >= 0x0000ffff)
	{
		TempDisconnectionDelay = 0x0000ffff;
	}

	SEC_ProxDisconnection((UWORD16)TempDisconnectionDelay);

/*%C  CHECK PRESSURE ALARM */
	   SEC_CheckPressure(DisconnectionDelay);

/*%C  CHECK PROXIMAL ALARM */ 	 	 
       SEC_CheckProximal(DisconnectionDelay); 

/*%C OCCLUSION ALARM 														  */
		SEC_Occlusion();
		
/*%C 	Alarms  for Leak modes */
	if(ValveDetected == FALSE)
	{
		SEC_LeakDisconnection(DisconnectionDelay);

/*%C 	Leak Occlusion*/
		SEC_LeakOcclusion();
	}
	else
	{
/*%C DISCONNECTION ALARM 
/*%C LowPress = 80% COMPUTED_PI_SET_POINT_U16										  */
		LowPress = (SWORD16)((ComputedPiSetPoint * 8)/10);													  
		SEC_Disconnection(DisconnectionDelay,LowPress);

/*%C  VALVE LEAKAGE ALARM */
		SEC_ValveLeakage();
	
/*%C    VALVE PRESSURE ALARM */
		SEC_CheckValvePressure(DisconnectionDelay);	
	}

}