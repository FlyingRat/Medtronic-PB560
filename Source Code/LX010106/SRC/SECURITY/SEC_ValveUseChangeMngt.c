/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ValveUseChangeMngt.c                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   It manages the valve use and change alarm							         */
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
#include "define.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "Security_Datas.h"
#include "Ventilation_Datas.h"
#include "SEC_ValveUseChangeMngt.h"
#include "DB_Compute.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void SEC_ValveUseChangeMngt(void)
{
	e_MODE_TYPES CurrentMode = DB_ControlRead(CURRENT_MODE_U16);
	UWORD16 VentilReq = DB_ConfigRead (VENTIL_REQ_U16);
	UWORD16 VentilAuthorization = DB_ControlRead (VENTIL_AUTHORIZATION_U16);
	UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);
	UWORD16 PiSetPoint = DB_CurrentRead(PI_SET_POINT_U16);
	UWORD16 AdjustPeep = DB_CurrentRead(ADJUST_PEEP_U16);
	UWORD16 Valve_Detect_In_Progress = DB_ControlRead(VALVE_DETECT_IN_PROGRESS_U16);
	e_DB_ALARMS AlarmEnleverValve1 = DB_AlarmStatusRead(ALARM_ENLEVER_VALVE_1_U16);
	e_DB_ALARMS AlarmEnleverValve2 = DB_AlarmStatusRead(ALARM_ENLEVER_VALVE_2_U16);
	e_DB_ALARMS AlarmUtiliserValveChangerPePi1 = 
	   				DB_AlarmStatusRead(ALARM_UTILISER_VALVE_CHANGER_PE_PI_1_U16);
	e_DB_ALARMS AlarmUtiliserValveChangerPePi2 = 
					DB_AlarmStatusRead(ALARM_UTILISER_VALVE_CHANGER_PE_PI_2_U16);
	e_DB_ALARMS AlarmEnleverValveChangerPePi1 = 
	  				DB_AlarmStatusRead(ALARM_ENLEVER_VALVE_CHANGER_PE_PI_1_U16);
	e_DB_ALARMS AlarmEnleverValveChangerPePi2 = 
	  				DB_AlarmStatusRead(ALARM_ENLEVER_VALVE_CHANGER_PE_PI_2_U16);
	e_DB_ALARMS AlarmUtiliserValve1 =
	   									 DB_AlarmStatusRead(ALARM_UTILISER_VALVE_1_U16);
	e_DB_ALARMS AlarmUtiliserValve2 = 
	   									 DB_AlarmStatusRead(ALARM_UTILISER_VALVE_2_U16);
	UWORD16 Delta_Pressure = 0;
	Delta_Pressure = PiSetPoint - AdjustPeep;


/*%C Valve management if a ventilation request is detected */
	if ( (VentilReq == TRUE)
	  && (VentilAuthorization == FALSE) )
	{

/******************* ALARM_ENLEVER_VALVE_CHANGER_PE_PI	*****************/
		if ( ( (CurrentMode == PSVT)
		    || (CurrentMode == PRES) )
		  && (ValveDetected == TRUE)
		  && (Delta_Pressure < 50)	)
		{
/*%C		if first cycle not achieved and alarm not yet detected */
			if ( (VEN_FirstCycle == FALSE)
			  && (AlarmEnleverValveChangerPePi1 == ALARM_FALSE)
			  && (AlarmEnleverValveChangerPePi2 == ALARM_FALSE) )
			{
				DB_AlarmStatusWrite(ALARM_ENLEVER_VALVE_CHANGER_PE_PI_1_U16,
										  ALARM_TRUE);
				DB_AlarmStatusWrite(ALARM_ENLEVER_VALVE_CHANGER_PE_PI_2_U16,
										  ALARM_TRUE);
				DB_EventMngt(EVENT_AL_DISCONNECT_VALVE_CHANGE_PI_PE);
				SEC_High_Priority_2 = SEC_High_Priority_2 | 0x0200;
			}
		}
		
/******************* ALARM_ENLEVER_VALVE ****************/
		if ( (CurrentMode == CPAP) 
		  && (ValveDetected == TRUE)
/*%C The alarm can't be triggered if the detection */
/*%C has not already been done before.          */
		  && (Valve_Detect_In_Progress == FALSE) )
		{ 
/*%C		if first cycle not achieved and alarm not yet detected */
		 	if ( (VEN_FirstCycle == FALSE)
		 	  && (AlarmEnleverValve1 == ALARM_FALSE)	 
		 	  && (AlarmEnleverValve2 == ALARM_FALSE) )	 
	 		{
				DB_AlarmStatusWrite(ALARM_ENLEVER_VALVE_1_U16, ALARM_TRUE);
				DB_AlarmStatusWrite(ALARM_ENLEVER_VALVE_2_U16, ALARM_TRUE);				
				DB_EventMngt(EVENT_AL_DISCONNECT_VALVE);
				SEC_High_Priority_2 = SEC_High_Priority_2 | 0x0800;
	 		}
		}

/******************* ALARM UTILISER VALVE PE PI		 ****************/
		if ( ( (CurrentMode == PSVT)
		    || (CurrentMode == PRES)	)
		  && ( (ValveDetected == FALSE)
		    && ( (PiSetPoint > 300)
		      || (AdjustPeep < 40) ) ) ) 
			{
				if ( (TIM_ReadDecounterValue(SEC_SPEED_BLOW_TIM)==0)
				  && (AlarmUtiliserValveChangerPePi1 == ALARM_FALSE)
				  && (AlarmUtiliserValveChangerPePi2 == ALARM_FALSE) )
				{
					DB_AlarmStatusWrite(ALARM_UTILISER_VALVE_CHANGER_PE_PI_1_U16,
											  ALARM_TRUE);
					DB_AlarmStatusWrite(ALARM_UTILISER_VALVE_CHANGER_PE_PI_2_U16,
											  ALARM_TRUE);	 
					DB_EventMngt(EVENT_AL_CONNECT_VALVE_CHANGE_PI_PE);
					SEC_High_Priority_2 = SEC_High_Priority_2 | 0x0100;
				}
			}

#if defined(CONFIG_VOL_MODE) || defined(CONFIG_SIMV_MODE)
/********************* ALARME UTILISER VALVE	**************/
		if ( ( (CurrentMode == VOL)
			 || (CurrentMode == VSIMV)
			 || (CurrentMode == PSIMV) )
		  && (ValveDetected == FALSE) )
		{
			if ( (VEN_FirstCycle == FALSE)
			  && (AlarmUtiliserValve1 == ALARM_FALSE)
			  && (AlarmUtiliserValve2 == ALARM_FALSE) )
			{
				DB_AlarmStatusWrite(ALARM_UTILISER_VALVE_1_U16, ALARM_TRUE);
				DB_AlarmStatusWrite(ALARM_UTILISER_VALVE_2_U16, ALARM_TRUE);
				DB_EventMngt(EVENT_AL_CONNECT_VALVE);
				SEC_High_Priority_2 = SEC_High_Priority_2 | 0x0400;
			}
		}
#endif
	}
	else if (VentilReq == FALSE)
	{
		SEC_ValveAlarmsToReset();
 	}



/*****************************************************************/


/*%C ENLEVER_VALVE_CHANGER_PE_PI auto cancellation	***********/

	if (((	(CurrentMode == PRES) || ( CurrentMode == PSVT)) 
				&& (ValveDetected == TRUE) 
				&& (Delta_Pressure >= 50))
				||(((CurrentMode == PRES) || ( CurrentMode == PSVT)) 
				&& (ValveDetected == FALSE))
				||	(CurrentMode == VOL)
     			|| (CurrentMode== VSIMV)
				|| (CurrentMode == PSIMV)
				|| (CurrentMode== CPAP))
	{
		if ( (AlarmEnleverValveChangerPePi1 >= ALARM_TRUE)
		  && (AlarmEnleverValveChangerPePi2 >= ALARM_TRUE) )
		{
			DB_EventMngt(EVENT_AL_END_OF_DISCONNECT_VALVE_CHANGE_PI_PE);
		}
/*%C !!! Always cancel the N°2 before the N°1 in order to let the */
/*%C N°1 alarm message memorization */
	  	DB_AlarmStatusWrite(ALARM_ENLEVER_VALVE_CHANGER_PE_PI_2_U16,
	  							  ALARM_FALSE);
		DB_AlarmStatusWrite(ALARM_ENLEVER_VALVE_CHANGER_PE_PI_1_U16,
								  ALARM_FALSE);
		SEC_High_Priority_2 = SEC_High_Priority_2 & 0xFDFF;
	}

/*%C ALARM_ENLEVER_VALVE auto cancellation	***********/
	if ( (CurrentMode != CPAP)
	  || (ValveDetected == FALSE)
	  || (VentilReq == FALSE) )
	{
		if ( (AlarmEnleverValve1 >= ALARM_TRUE)
			&&(AlarmEnleverValve2 >= ALARM_TRUE) )
		{
			DB_EventMngt(EVENT_AL_END_OF_DISCONNECT_VALVE);
		}
/*%C !!! Always cancel the N°2 before the N°1 in order to let the */
/*%C N°1 alarm message memorization */
		DB_AlarmStatusWrite(ALARM_ENLEVER_VALVE_2_U16,
								  ALARM_FALSE);
		DB_AlarmStatusWrite(ALARM_ENLEVER_VALVE_1_U16,
								  ALARM_FALSE);
		SEC_High_Priority_2 = SEC_High_Priority_2 & 0xF7FF;
   }

/*%C ALARM_UTILISER_VALVE_CHANGER_PE_PI auto cancellation	***********/
	if ( ( (CurrentMode == VOL)
	    || (CurrentMode == VSIMV)
		|| (CurrentMode == PSIMV)	)
	    || (ValveDetected == TRUE)
	    || ( (PiSetPoint <= 300)
	      && (AdjustPeep >= 40) ) )
	{
		if ( (AlarmUtiliserValveChangerPePi1 >= ALARM_TRUE)
		  && (AlarmUtiliserValveChangerPePi2 >= ALARM_TRUE) )
		{
			DB_EventMngt(EVENT_AL_END_OF_CONNECT_VALVE_CHANGE_PI_PE);
		}
/*%C !!! Always cancel the N°2 before the N°1 in order to let the */
/*%C N°1 alarm message memorization */
		DB_AlarmStatusWrite(ALARM_UTILISER_VALVE_CHANGER_PE_PI_2_U16,
								  ALARM_FALSE);
		DB_AlarmStatusWrite(ALARM_UTILISER_VALVE_CHANGER_PE_PI_1_U16,
								  ALARM_FALSE);
		SEC_High_Priority_2 = SEC_High_Priority_2 & 0xFEFF;
	}		       

/*%C ALARM_UTILISER_VALVE auto cancellation	***********/

		if ( ( (CurrentMode == VOL)
			 || (CurrentMode == VSIMV)
			 || (CurrentMode == PSIMV) )
		  && (ValveDetected == TRUE) )
	{
		if ( (AlarmUtiliserValve1 >= ALARM_TRUE)
		  && (AlarmUtiliserValve2 >= ALARM_TRUE) )
		{
			DB_EventMngt(EVENT_AL_END_OF_CONNECT_VALVE);
		}
/*%C !!! Always cancel the N°2 before the N°1 in order to let the */
/*%C N°1 alarm message memorization */
		DB_AlarmStatusWrite(ALARM_UTILISER_VALVE_2_U16,
								  ALARM_FALSE);
		DB_AlarmStatusWrite(ALARM_UTILISER_VALVE_1_U16,
								  ALARM_FALSE);
		SEC_High_Priority_2 = SEC_High_Priority_2 & 0xFBFF;
	}

 /*%C In case of mode change, the alarms are reset */
	if(VEN_Synchro_Reset_Alarms == TRUE)
	{
		SEC_ValveAlarmsToReset();
		VEN_Synchro_Reset_Alarms = FALSE;

	}					
}
