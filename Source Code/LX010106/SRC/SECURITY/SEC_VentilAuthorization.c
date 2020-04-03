/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_VentilAuthorization.c                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function launches the speed blower test timer when the ventil     */
/*%C   request is detected.                                                   */
/*%C   It gives the ventilation authorization too if a ventilation            */
/*%C	 request is detected and if the speed blower test is over.              */
/*%C   It stops the ventilation when the stop request is commanded.           */
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
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_KeyboardEvent.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "SEC_VentilAuthorization.h"
#include "Security_Datas.h"
#include "Ventilation_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_VentilAuthorization(void)
{
/* Ventil request recovery from config base */
	UWORD16 VentilReq = DB_ConfigRead(VENTIL_REQ_U16);
/* Ventil request memorization */
	static UWORD16 VentilReqMemo = FALSE;
/* Ventil authorization recovery */
	UWORD16 Ventil_Authorization = DB_ControlRead(VENTIL_AUTHORIZATION_U16);
	UWORD16 Keyboard_Start_Ventil_Up_Event = 
                      DB_KeyboardEventRead(KEYBOARD_START_VENTIL_UP_EVENT_U16);
	UWORD16 Keyboard_Stop_Ventil_Event = 
                      DB_KeyboardEventRead(KEYBOARD_STOP_VENTIL_EVENT_U16);

	e_CalibrationCommand CalibFlowExhReq =
   										DB_ControlRead(CALIB_FLOW_EXH_REQ_U16);
	e_DB_ALARMS AlarmEnleverValve1 = DB_AlarmStatusRead(ALARM_ENLEVER_VALVE_1_U16);
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
	UWORD16 ChangeMode = DB_ControlRead(CHANGE_MODE_U16);
	static UWORD16 FlagStopStart = FALSE;


	if ( AlarmEnleverValve1 !=FALSE
		|| AlarmUtiliserValveChangerPePi1 !=FALSE
		|| AlarmEnleverValveChangerPePi1 !=FALSE
		|| AlarmUtiliserValve1 !=FALSE
	   )
		{
		FlagStopStart = TRUE;
		}
	else
		{
		FlagStopStart = FALSE;
		}


/******************************************************************************/
/*    					 VENTIL REQUEST DETECTION   										*/
/******************************************************************************/

/*%C If a short press is made on the ventilation key, the ventilation request */
/*%C is detected */
   if (Keyboard_Start_Ventil_Up_Event == TRUE)
	{
/*%C  Ventil request writing in config base */
      DB_ConfigWrite(VENTIL_REQ_U16,
                     TRUE);
  	}
/******************************************************************************/
/*    					 VENTIL REQUEST DESACTIVATION   									*/
/******************************************************************************/

/*%C If the stop ventil event is detected, the ventilation request is detected*/
   if (Keyboard_Stop_Ventil_Event == TRUE)
	{
/*%C  Ventil request writing in config base */
      DB_ConfigWrite(VENTIL_REQ_U16,
                     FALSE);


  	}

/******************************************************************************/
/*    					 BLOWER TEST LAUNCH DETECTION										*/
/******************************************************************************/

/*%C If a ventilation request is detected, the speed blower test turbine timer*/
/*%C is launched */
   if ( (VentilReq == TRUE)
	  && (VentilReqMemo == FALSE) )
	{
/*%C Voluntary stop is reset */
		DB_ControlWrite(VOLUNTARY_STOP_U16, FALSE);

/*%C  Speed blower test turbine test launch */
		TIM_StartDecounter (SEC_SPEED_BLOW_TIM,
                          TIME_SPEED_BLOW);
/*%C  If an unvolontary stop has been detected, the device starts directly 	*/
/*%C  in ventilation mode, so the ventilation start bip is not needed		 	*/
		if (VEN_StartBip == TRUE)
		{
/*%C  	Start bip command (one bip)	*/
			DB_ControlWrite(VALIDATION_BIP_U16,
							 	 BIP_START_VENTIL);
		}
	}
/*%C Ventilation request memorization */
	VentilReqMemo = VentilReq;

/******************************************************************************/
/*    					 VENTILATION START DETECTION										*/
/******************************************************************************/

/*%C If no ventilation authorization, with ventilation request detected and   */
/*%C speed test over                                                          */
   if ( (Ventil_Authorization == FALSE)
	  && (VentilReq == TRUE)
	  && (SEC_SpeedTestEnded == TRUE)
	  && (CalibFlowExhReq == NO_CALIB)
	  && (FlagStopStart== FALSE) )

	{
/*%C  Ventil authorization writing in control base */
      DB_ControlWrite (VENTIL_AUTHORIZATION_U16,
                       TRUE);
/*%C  Ventilation start event writing 					*/
		DB_EventMngt(EVENT_VENTIL);

	}
/******************************************************************************/
/*    					 VENTILATION STOP DETECTION										*/
/******************************************************************************/

/*%C If the ventilation is running and if a stop request is detected, the		*/
/*%C ventilation authorization flag is set to FALSE, the ventilation led is   */
/*%C activated, the buzzer bips twice   													*/
   if ( (Ventil_Authorization == TRUE)
	  && (VentilReq == FALSE) )
	{
/*%C  Ventil authorization writing in control base */
      DB_ControlWrite (VENTIL_AUTHORIZATION_U16,
                       FALSE);
/*%C  Ventilation volontary stop event writing 					*/
   		DB_EventMngt(EVENT_VOLUNTARY_STOP_VENTIL );

/*%C  Start bip authorization (volontary stop) */
		VEN_StartBip = TRUE;

/*%C Voluntary stop is set */
		DB_ControlWrite(VOLUNTARY_STOP_U16, TRUE);
	}

/******************************************************************************/
/*    					 VENTILATION LED MANAGEMENT										*/
/******************************************************************************/

/*%C If the ventilation request is made, the ventilation led is desactivated 	*/
   if (VentilReq == TRUE)
	{
/*%C  Ventilation led desactivation */
      DRV_Led_Ventil(FALSE);
	}
/*%C else, if we are not in mode change,the ventilation is unauthorized, the ventilation led is activated	*/
	else if(ChangeMode == FALSE)
	{
/*%C  Ventilation led activation */
      DRV_Led_Ventil(TRUE);
	}
}
