/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : VEN_Cycles.c                												*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                 Ventilation cycles management             					*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                   					*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE					  												*/
/******************************************************************************/
#define DECLARATION_CYCLES_DATAS

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "io_declare.h"
#include "Structure.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "DB_Compute.h"
#include "DB_Config.h"
#include "Timer_Data.h"
#include "Ventilation_Constants.h"
#include "Ventilation_Datas.h"
#include "Ventilation_Cycles_Datas.h"
#include "VEN_Cycles.h"
#include "Ventilation_Compute_data.h"




/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void VEN_Cycles(void)
{
	e_MODE_TYPES CurrentMode = DB_ControlRead(CURRENT_MODE_U16);  
	UWORD16 ChangeMode = DB_ControlRead(CHANGE_MODE_U16);
	UWORD16 VentilAuthorization = DB_ControlRead(VENTIL_AUTHORIZATION_U16);
	UWORD16 AdjustApnea = DB_CurrentRead(ADJUST_APNEA_U16);
/*%C Reading speed blower in data base */
	SWORD16 MeasureSpeedBlower = (SWORD16)DB_ComputeRead(MEASURE_SPEED_BLOWER_U16);

	UWORD16 ValveDetectInProgress =	DB_ControlRead(VALVE_DETECT_IN_PROGRESS_U16);

	UWORD16 PiSetPoint = DB_CurrentRead(PI_SET_POINT_U16);

	e_InspDetectType InspirationDetectionType = CONTROLLED;
 	UWORD16 Delay = 0;



/*****************************************************************************/
/*%C               When the ventilation is on stand by mode :                */
/*%C                  VentilAuthorization is False                           */
/*****************************************************************************/
 	if (VentilAuthorization == FALSE)
	{

/*%C  The copy function of the adjustments into the current data base */
/*%C  is launched																		*/
	  	DB_CopyMngt();
		
/*%C ********** Vt target variables initialisation ****************************/
		DB_ComputeWrite(COMPUTED_PI_SET_POINT_U16,PiSetPoint);
		CMP_SetPoint_Mutex = FALSE;
/*			Pi_Set_Point = Pi_Set_Point;					*/
/*%C  	Set point mutex initialization (used in CMP_TargetVt) */
		CMP_UpStep_Mutex = FALSE;
		CMP_DownStep_Mutex = FALSE;
		CMP_TargetVT_Pi = 0;
/*****************************************************************************/
/*%C  Initialization of "VEN_ActiveModeState" variables and flags */
		CYC_ActiveModeState.VolPres = ACTIVATED;
		CYC_ActiveModeState.Psvt = ACTIVATED;
		CYC_ActiveModeState.Psv = ACTIVATED;
		CYC_ActiveModeState.Vsimv = ACTIVATED;
		CYC_ActiveModeState.Psimv = ACTIVATED;
		CYC_ActiveModeState.Cpap = ACTIVATED;
      CYC_TiExpired = FALSE;
      CYC_TeExpired = FALSE;

/*%C  The inspiration type is set to NO_INSP. */
      InspirationDetectionType = NO_INSP;	
/*%C  write into control data base the right state :  VEN_VENTIL_DISABLE */
	 	DB_ControlWrite(VENTIL_STATE_U16,
	 					    VEN_VENTIL_DISABLE);
/*%C  Initialization flag for the machine state */
		CYC_FirstInspirationActive = FALSE;		  
		

		/*%C Flag for reset of sight counter when ventilation stops */
		RazSightCpt = TRUE;
		 /*%C If we are in mode change, and as the database copy is made, we make un ventilation request. */
	if(ChangeMode == TRUE)
	{
/*%C  Speed blower test turbine test launch */
		TIM_StartDecounter (SEC_SPEED_BLOW_TIM,
                          TIME_SPEED_BLOW);
		DB_ConfigWrite(VENTIL_REQ_U16,TRUE);
/*%C  Change mode flag reset */
		DB_ControlWrite(CHANGE_MODE_U16,
			   				 FALSE);
		VEN_Synchro_Reset_Alarms = TRUE;	  
		
	}
	}

/*****************************************************************************/
/*%C                   if the ventilation is on...                           */
/*****************************************************************************/
	else
	{
	/*---------------------------------------------------------------------------*/
/*%C                           Time Out Management :                         */
/*%C  If a mode change is requested, in exhalation phase, then						*/
/*%C  if an exhalation delay overruns : 													*/
/*%C  - apnea + 1s in VOL and PRES															*/
/*%C  - 3s in CPAP and PSVT 																	*/
/*%C  - 0s in VSIMV and PSIMV (The 2s initialization are managed in				*/
/*%C  	CYC_Vsimv_CyclesMngt)																*/

	   if ( (ChangeMode == TRUE) 
	    && ((CYC_TiExpired == TRUE)
			|| (CurrentMode == CPAP)) )
		{
			VEN_Synchro_Reset_Alarms = TRUE;	
/*********************************************************************************************/
		

/*%C  Stop the ventilation. */
			DB_ConfigWrite(VENTIL_REQ_U16,FALSE);
			DB_ControlWrite(VENTIL_AUTHORIZATION_U16,FALSE);
			VEN_MutexVanneO2 = TRUE;

/*******************************************************************************************/								
/*%C  		the regulation phase becomes inspiration, 								*/
/*%C			so VEN_TeExpired becomes TRUE and  VEN_TiExpired becomes FALSE		*/
			CYC_TeExpired = FALSE;
      		CYC_TiExpired = FALSE;

/*%C 			Initialization of "VEN_ActiveModeState" variables and flags */
			CYC_ActiveModeState.VolPres = ACTIVATED;
			CYC_ActiveModeState.Psvt = ACTIVATED;
			CYC_ActiveModeState.Psv = ACTIVATED;
			CYC_ActiveModeState.Cpap = ACTIVATED;
			
			CYC_ActiveModeState.Vsimv = ACTIVATED;
			CYC_ActiveModeState.Psimv = ACTIVATED;
			CYC_FirstInspirationActive = FALSE;


		}

/*---------------------------------------------------------------------------*/
/*%C	Call of the state machine depending on the current mode :       */

		switch (CurrentMode)
		{
#ifdef CONFIG_VOL_MODE
/*%C 		If the current mode is VOL, then "CYC_Pres_Vol_CyclesMngt" */
/*%C		is launched, the type of controller is FLOW */
	   	case VOL :
		   		InspirationDetectionType = CYC_Pres_Vol_CyclesMngt();
				VEN_ControllerType = CONTROL_FLOW;
				DB_ControlWrite(CONTROLER_TYPE_U16,VEN_ControllerType);
				break;
#endif
/*%C 		If the current mode is PRESS, then "CYC_Pres_Vol_CyclesMngt" */
/*%C		is launched, the type of controller is PRESSURE */
	   	case PRES :
		  		InspirationDetectionType = CYC_Pres_Vol_CyclesMngt();
				VEN_ControllerType = CONTROL_PRESSURE;
				DB_ControlWrite(CONTROLER_TYPE_U16,VEN_ControllerType);
				break;

/*%C 		If the current mode is PSVT, then "CYC_Psvt_CyclesMngt" is launched, */
/*%C		the type of controller is PRESSURE */
			case PSVT :    
		  		InspirationDetectionType = CYC_Psvt_CyclesMngt();
				VEN_ControllerType = CONTROL_PRESSURE;
				DB_ControlWrite(CONTROLER_TYPE_U16,VEN_ControllerType);
				break;
#ifdef CONFIG_SIMV_MODE
/*%C 		If the current mode is VSIMV, then "CYC_Simv_CyclesMngt" is launched */
			case VSIMV :  
		  		InspirationDetectionType = CYC_Vsimv_CyclesMngt();
/*%C 			if the cycle of SIMV is PSV, then the type of controller is */
/*%C			PRESSURE */
				if(VEN_SIMVCycle == PSV_Cycle)
				{
					VEN_ControllerType = CONTROL_PRESSURE;
					DB_ControlWrite(CONTROLER_TYPE_U16,VEN_ControllerType);
				}
/*%C 			else, the type of controller is FLOW */
				else
				{
					VEN_ControllerType = CONTROL_FLOW;
					DB_ControlWrite(CONTROLER_TYPE_U16,VEN_ControllerType);
				}
				break;

/*%C 		If the current mode is PSIMV, then "CYC_Simv_CyclesMngt" is launched,*/
/*%C		the type of controller is PRESSURE */
			case PSIMV :      
				InspirationDetectionType = CYC_Psimv_CyclesMngt();
				VEN_ControllerType = CONTROL_PRESSURE;
				DB_ControlWrite(CONTROLER_TYPE_U16,VEN_ControllerType);
				break;
#endif

/*%C 		If the current mode is CPAP, then "CYC_Cpap_CyclesMngt" is launched, */
/*%C		the type of controller is PRESSURE */
			case CPAP :
				InspirationDetectionType = CYC_CpapCyclesMngt();
				VEN_ControllerType = CONTROL_PRESSURE;
				DB_ControlWrite(CONTROLER_TYPE_U16,VEN_ControllerType);
				break;

			default:
/*%C 			The inspiration type is set to NO_INSP. */
	         InspirationDetectionType = NO_INSP;
				break;
		}
/*---------------------------------------------------------------------------*/
/*             Generation of the respiratory and controller phases           */ 

/*%C  if the inspiration is expired, then  */
/*%C  write into control data base the right state : VEN_EXHALATION */
/*%C  launch the function "CYC_Exh_Controller_Phase" */
		if (CYC_TiExpired == TRUE)
		{
			DB_ControlWrite(VENTIL_STATE_U16,
								 VEN_EXHALATION);
			CYC_Exh_Controller_Phase();
		}
/*%C  else if the exhalation is expired, and the type of inspiration is */
/*%C  CONTROLLED then */ 
/*%C  write into control data base the right state : VEN_INSPIRATION_CONTROLED*/
/*%C  launch the function "CYC_Insp_Controller_Phase" */
		else if(CYC_TeExpired == TRUE) 
		{
			CYC_Insp_Controller_Phase();
			if(InspirationDetectionType == CONTROLLED)
			{
				DB_ControlWrite(VENTIL_STATE_U16,
								 VEN_INSPIRATION_CONTROLED);
			}
			else if(InspirationDetectionType == TRIGGERED)
			{
				DB_ControlWrite(VENTIL_STATE_U16,
								 VEN_INSPIRATION_TRIGGERED);
			}
		
		}

	}
			
}


