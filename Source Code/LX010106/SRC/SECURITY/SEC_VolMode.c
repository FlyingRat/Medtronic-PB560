/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0104                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_VolMode.c                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   It schedules the alarms in the VOL mode                                */
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
#include "DB_Current.h"
#include "SEC_VolMode.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_VolMode(void)
{
	SWORD16 LowPress = 0;
	UWORD16 PressureValue = 0;
	UWORD32 TempDisconnectionDelay = 0;
	UWORD16 LowPresDelay = 0;
    UWORD16 Adjust_Control_R = DB_CurrentRead(ADJUST_CONTROL_R_U16);
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

/*%C CHECK VOLUME ALARM 													  */
	SEC_CheckVolume();

/*%C PROX DISCONNECTION ALARM												  */
	TempDisconnectionDelay = (UWORD32)DisconnectionDelay + 2000;
/*%C We have to check the limit	 TempLowPresDelay to be as an UWORD16 format */
	if(TempDisconnectionDelay >= 0x0000ffff)
	{
		TempDisconnectionDelay = 0x0000ffff;
	}

	SEC_ProxDisconnection((UWORD16)TempDisconnectionDelay);

/*%C HIGH PRESSURE ALARM  												      */
/*%C PressureValue =  ADJUST_HIGH_PIP_U16							 		  */
	PressureValue = DB_CurrentRead(ADJUST_HIGH_PIP_U16);
	SEC_HighPressure(PressureValue);
/*%C DISCONNECTION ALARM 													  */
/*%C LowPress = ADJUST_LOW_PIP_U16											  */
	LowPress = (SWORD16)DB_CurrentRead(ADJUST_LOW_PIP_U16);

	SEC_Disconnection(DisconnectionDelay,LowPress);
/*%C INSP FLOW FAILURE ALARM 												  */	   
	SEC_InspiratoryFlowFailure();
/*%C  VALVE LEAKAGE ALARM */
	SEC_ValveLeakage();

/*%C  CHECK PRESSURE ALARM */
	SEC_CheckPressure(DisconnectionDelay);

/*%C  CHECK PROXIMAL ALARM */ 	 	 
	SEC_CheckProximal(DisconnectionDelay); 

/*%C  VALVE PRESSURE ALARM */
	SEC_CheckValvePressure(DisconnectionDelay);
}