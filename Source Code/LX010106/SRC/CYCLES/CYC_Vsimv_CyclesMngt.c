/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_Vsimv_CyclesMngt.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Respiratory cycle management in Vol SIMV mode 					   */
/*           																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : e_InspDetectType InspirationType           				*/
/******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "DB_AlarmStatus.h"
#include "Ventilation_Datas.h"
#include "Ventilation_Cycles_Datas.h"
#include "CYC_Vsimv_CyclesMngt.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

e_InspDetectType CYC_Vsimv_CyclesMngt(void)
{
UWORD16 AdjustControlR = DB_CurrentRead(ADJUST_CONTROL_R_U16);
UWORD16 AdjustBackupR = DB_CurrentRead(ADJUST_BACKUP_R_U16);
UWORD16 AdjustTiControl = DB_CurrentRead(ADJUST_TI_CONTROL_U16);
UWORD16 AdjustApnea = DB_CurrentRead(ADJUST_APNEA_U16);
UWORD16 High_Pressure_Detected = DB_ControlRead(HIGH_PRESSURE_DETECTED_U16);
e_DB_ALARMS_STATE AlarmApneaFlag = DB_AlarmStatusRead(ALARM_APNEA_FLAG_U16);
t_CYC_TiLimit Ti = {0,0};
e_InspDetectType InspirationType = NO_INSP;
 UWORD16 SIMVPeriod = 0;
 UWORD16 SIMVBackupPeriod = 0;
/*%C Counter value at the exhalation start */
static UWORD16 ExhStartSimvCounter = 0;
static UWORD16 i = 0;
static UWORD16 j = 0;
static UWORD16 PsvCycleOccured = FALSE;
static UWORD16 VimDelayed = FALSE;
static UWORD16 VimCanceled = FALSE;
static UWORD16 ResetApneaCpt = 0;

/*%C SIMV period used in "normal" mode     */
	SIMVPeriod = 60000U / AdjustControlR;
/*%C SIMV period used after apnea detection    */
	SIMVBackupPeriod = 60000U / AdjustBackupR;

	switch (CYC_ActiveModeState.Vsimv)
	{
/******************************************************************************/
/*                          ACTIVATED STATE												*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Vsimv" is activated :     */
/*%C It is the initial value of the state machine. */
/*%C The Te counter is launched */
	case ACTIVATED :
/*%C  if "CYC_TeExpired" is false :*/
      if (CYC_FirstInspirationActive == FALSE)
      {
			CYC_FirstInspirationActive = TRUE;
/*%C 		The counter "VEN_TE_Count" starts. */
         TIM_StartCounter(VEN_TE_COUNT);
/*%C 		The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
/*%C 		"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 			CYC_TeExpired = FALSE */
/*%C 			CYC_TiExpired = TRUE  */
         CYC_TeExpired = FALSE;
         CYC_TiExpired = TRUE;
/*%C 		Record of the new phase of VSIMV mode */			
			VEN_SIMVCycle = CAV_Cycle;
			DB_ControlWrite(SIMV_CYCLES_U16,CAV_Cycle);
			DB_ControlWrite(SIMV_CONTROLLED_INSP_U16,FALSE);
/*%C  	The decounter of Apnea is launched */
			TIM_StartDecounter(SEC_APNEA,AdjustApnea);
			TIM_StartDecounter(SEC_APNEA_FLAG,AdjustApnea);
      }
/*%C 	If an inspiration trigger is detected before the 2s init				*/
	   else if (CYC_TriggerIDetection() == TRUE)
		{
/*%C 		The counter "VEN_TI_COUNT" starts. */
         	TIM_StartCounter(VEN_TI_COUNT);
/* 			The counter "VEN_SIMV_PERIOD_COUNT" starts */
			TIM_StartCounter(VEN_SIMV_PERIOD_COUNT);
/*%C		Initializes the VIM canceled flag information */
			VimCanceled = FALSE;
/*%C 		The kind of inspiration detection is TRIGGERED. */
         	InspirationType = TRIGGERED;
/*%C 		A copy of adjust data base into current once is launched. */
         	DB_CopyMngt();
/*%C 		"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 			CYC_TeExpired = TRUE */ 
/*%C 			CYC_TiExpired = FALSE  */
         CYC_TeExpired = TRUE;
         CYC_TiExpired = FALSE;
/*%C 		Record of the new phase of VSIMV mode */			
			VEN_SIMVCycle = CAV_Cycle;
			DB_ControlWrite(SIMV_CYCLES_U16,CAV_Cycle);
			DB_ControlWrite(SIMV_CONTROLLED_INSP_U16,FALSE);
/*%C 		The "CAV Inspiration" state must be activated */
      	CYC_ActiveModeState.Vsimv = SIMV_CAV_INSPIRATION;
/*%C  	The decounter of Apnea is launched */
			TIM_StartDecounter(SEC_APNEA,AdjustApnea);
			TIM_StartDecounter(SEC_APNEA_FLAG,AdjustApnea);
		}
/*%C 	If the 2s initialization are reached 				*/
	   else if (TIM_ReadCounterValue(VEN_TE_COUNT) >= cINIT_SIMV_DELAY)
		{
/*%C 		The counter "VEN_TI_COUNT" starts. */
         TIM_StartCounter(VEN_TI_COUNT);
/* 		The counter "VEN_SIMV_PERIOD_COUNT" starts */
			TIM_StartCounter(VEN_SIMV_PERIOD_COUNT);
/*%C		Initializes the VIM canceled flag information */
			VimCanceled = FALSE;
/*%C 		The kind of inspiration detection is TRIGGERED. */
         InspirationType = CONTROLLED;
/*%C 		A copy of adjust data base into current once is launched. */
         DB_CopyMngt();
/*%C 		"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 			CYC_TeExpired = TRUE */ 
/*%C 			CYC_TiExpired = FALSE  */
        	CYC_TeExpired = TRUE;
         	CYC_TiExpired = FALSE;
/*%C 		Record of the new phase of VSIMV mode */			
			VEN_SIMVCycle = CV_Cycle;
			DB_ControlWrite(SIMV_CYCLES_U16,CV_Cycle);
			DB_ControlWrite(SIMV_CONTROLLED_INSP_U16,FALSE);
/*%C 		The "CV Inspiration" state must be activated */
      		CYC_ActiveModeState.Vsimv = SIMV_CV_INSPIRATION;
/*%C  		The decounter of Apnea is launched */
			AdjustApnea = DB_CurrentRead(ADJUST_APNEA_U16);
			TIM_StartDecounter(SEC_APNEA,AdjustApnea);
			TIM_StartDecounter(SEC_APNEA_FLAG,AdjustApnea);	  
		}
/*%C Flow max initialization */
		CYC_Qmax = 0;
		break;

/******************************************************************************/
/*                         VSIMV EXHALATION STATE									*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Vsimv" is VSIMV exhalation :     */
	case SIMV_VSIMV_EXHALATION :
/*%C  If an inspiration trigger is selected and detected, then  */
		if ( CYC_TriggerIDetection() == TRUE)
		{
/*%C 		If  Measure Ti < Simv period - Adjust Ti Control*/
/*%C 		=> the next inspi is a PSV cycle  */
			if (TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT) < 
																	SIMVPeriod - AdjustTiControl)
			{
/*%C 			The kind of inspiration detection is TRIGGERED. */
				InspirationType =	TRIGGERED;
/*%C 			"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values:*/
/*%C 			CYC_TeExpired = TRUE */
/*%C 			CYC_TiExpired = FALSE  */
				CYC_TeExpired = TRUE;
				CYC_TiExpired = FALSE;
/*%C 			Record of the new phase of VSIMV mode */			
				VEN_SIMVCycle = PSV_Cycle;
				DB_ControlWrite(SIMV_CYCLES_U16,PSV_Cycle);
				DB_ControlWrite(SIMV_CONTROLLED_INSP_U16,FALSE);
/*%C 			The "CAV Inspiration" state must be activated */
     			CYC_ActiveModeState.Vsimv = SIMV_PSV_INSPIRATION;
				PsvCycleOccured = TRUE;

			}

/*%C 		else if SIMV timer < Simv period		*/
/*%C 		=> the next inspi is a CAV cycle (PIM)  */
/*%C 		=> the Simv period counter is launched  */
			else if ( (TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT) < SIMVPeriod)
				 || ( (TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT) <
						   ExhStartSimvCounter + 2 * VEN_TiTeValueMesured.TiValCount)
					&& (VimDelayed == TRUE) ) )
			{
/*%C 			The kind of inspiration detection is TRIGGERED. */
				InspirationType =	TRIGGERED;
/*%C 			"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values:*/
/*%C 				CYC_TeExpired = TRUE */
/*%C 				CYC_TiExpired = FALSE  */
				CYC_TeExpired = TRUE;
				CYC_TiExpired = FALSE;
/*%C 			Record of the new phase of VSIMV mode */			
				VEN_SIMVCycle = CAV_Cycle;
				DB_ControlWrite(SIMV_CYCLES_U16,CAV_Cycle);
				DB_ControlWrite(SIMV_CONTROLLED_INSP_U16,FALSE);
/*%C			The "CAV Inspiration" state must be activated */
 				CYC_ActiveModeState.Vsimv = SIMV_CAV_INSPIRATION;
/*%C			Initializes the VIM canceled flag information */
				VimCanceled = TRUE;
/*%C			Initializes the VIM delayed flag information */
				VimDelayed = FALSE;
/*%C			If a PSV cycle has occured during the inspiration, */
/*%C			it's mentionned in the history cycle array */
				if (PsvCycleOccured == TRUE)
				{
					VEN_SIMV_Cycle_History[i] = PSV;
					PsvCycleOccured = FALSE;
				}
/*%C			else, a PIM cycle is mentionned in the history cycle array  */
				else
				{
					VEN_SIMV_Cycle_History[i] = PIM;
				}
/*%C			Array index increasing  */
				i = (i + 1) % 6;
			}
		}
/*%C 	else if no insp sens selected and  simv period is reached */
/*%C 	=> the next inspi is a CV cycle (VIM) */
/*%C 	=> the Simv period counter is launched  */
		else if ( (VimCanceled == FALSE)
			   && ( ( (TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT) >= SIMVPeriod)
		           && (VimDelayed == FALSE) )
				 || ( (TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT) >=
						   ExhStartSimvCounter + 2 * VEN_TiTeValueMesured.TiValCount)
					&& (VimDelayed == TRUE) ) ) )
		{
/*%C 		The kind of inspiration detection is CONTROLLED. */
			InspirationType =	CONTROLLED;
/*%C 		"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values:*/
/*%C 		CYC_TeExpired = TRUE */
/*%C 		CYC_TiExpired = FALSE  */
			CYC_TeExpired = TRUE;
			CYC_TiExpired = FALSE;
/*%C 		Record of the new phase of VSIMV mode */			
			VEN_SIMVCycle = CV_Cycle;
			DB_ControlWrite(SIMV_CYCLES_U16,CV_Cycle);
			DB_ControlWrite(SIMV_CONTROLLED_INSP_U16,FALSE);
/*%C 		The "CV Inspiration" state must be activated */
	  		CYC_ActiveModeState.Vsimv = SIMV_CV_INSPIRATION;
/*%C		The counter "VEN_SIMV_PERIOD_COUNT" starts */
			TIM_StartCounter(VEN_SIMV_PERIOD_COUNT);
/*%C		Initializes the VIM delayed flag information */
			VimDelayed = FALSE;
/*%C		If a PSV cycle has occured during the inspiration, */
/*%C		it's mentionned in the history cycle array */
			if (PsvCycleOccured == TRUE)
			{
				VEN_SIMV_Cycle_History[i] = PSV;
				PsvCycleOccured = FALSE;
			}
/*%C		else, a VIM cycle is mentionned in the history cycle array  */
			else
			{
				VEN_SIMV_Cycle_History[i] = VIM;
			}
/*%C		Array index increasing  */
			i = (i + 1) % 6;
		}
		else if ( (VimCanceled == TRUE)
		       && (TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT) >= SIMVPeriod) )
		{
/* 			The counter "VEN_SIMV_PERIOD_COUNT" starts */
			TIM_StartCounter(VEN_SIMV_PERIOD_COUNT);
/*%C		Initializes the VIM canceled flag information */
			VimCanceled = FALSE;
		}
				else if (AlarmApneaFlag >= ALARM_DISPLAYED)
			{
	/*%C 		The kind of inspiration detection is CONTROLLED. */
				InspirationType =	CONTROLLED;
	/*%C 		"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values:*/
	/*%C 		CYC_TeExpired = TRUE */
	/*%C 		CYC_TiExpired = FALSE  */
				CYC_TeExpired = TRUE;
				CYC_TiExpired = FALSE;
	/*%C 		Record of the new phase of VSIMV mode */			
				VEN_SIMVCycle = CV_Cycle;
				DB_ControlWrite(SIMV_CYCLES_U16,CV_Cycle);
				DB_ControlWrite(SIMV_CONTROLLED_INSP_U16,TRUE);
	/*%C 		The "CV Inspiration apnea" state must be activated */
				CYC_ActiveModeState.Vsimv = SIMV_CV_INSPIRATION_APNEA;
	/*%C		The counter "VEN_SIMV_PERIOD_COUNT" starts */
				TIM_StartCounter(VEN_SIMV_PERIOD_COUNT);
	/*%C		Initializes the VIM canceled flag information */
				VimCanceled = FALSE;
	/*%C		Initializes the VIM delayed flag information */
				VimDelayed = FALSE;
			}

		else
		{
/*%C 		The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
		}


/*%C Inspiration phase initialisation : */
/*%C If CYC_TeExpired == TRUE,then  */
	if (CYC_TeExpired == TRUE)
	{
						  
/*%C  The exhalation duration is recorded in order to compute the IE ratio*/
/*%C  into an other module .*/
	  VEN_TiTeValueMesured.TeValCount = TIM_ReadCounterValue(VEN_TE_COUNT);
/*%C  The counter "VEN_TI_COUNT" starts. */
      TIM_StartCounter(VEN_TI_COUNT);
/*%C  A copy of adjust data base into current once is launched. */
      DB_CopyMngt();
/*%C  The decounter of Apnea is launched */
 	  AdjustApnea = DB_CurrentRead(ADJUST_APNEA_U16);
	  TIM_StartDecounter(SEC_APNEA,AdjustApnea);
	  TIM_StartDecounter(SEC_APNEA_FLAG,AdjustApnea);
	}
/*%C Flow max initialization */
	CYC_Qmax = 0;
	break;

/******************************************************************************/
/*                         CAV INSPIRATION STATE	   							*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Vsimv" is CAV inspiration :     */
	case SIMV_CAV_INSPIRATION :

/*%C	If the SIMV period is reached during the CAV inspiration (following a   */
/*%C	PIM), the SIMV period timer is launched   */
		if (TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT) >= SIMVPeriod)
		{
/*%C		The counter "VEN_SIMV_PERIOD_COUNT" starts */
			TIM_StartCounter(VEN_SIMV_PERIOD_COUNT);
/*%C		Initializes the VIM canceled flag information */
			VimCanceled = FALSE;
		}
		
/*%C  if Ti counter is equal to or upper than the adjusted Ti Control,*/
/*%C  or the high pressure alarm is TRUE, then */
	  	if ( (TIM_ReadCounterValue(VEN_TI_COUNT) >= AdjustTiControl)
	  	  || (High_Pressure_Detected >= TRUE) )
	   {
/*%C 		The inspiration duration is recorded in order to compute the IE ratio*/
/*%C 		into an other module .*/
			VEN_TiTeValueMesured.TiValCount = TIM_ReadCounterValue(VEN_TI_COUNT);
/*%C 		The counter "VEN_TE_COUNT" starts. */
			TIM_StartCounter(VEN_TE_COUNT);
/*%C 		The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
/*%C 		"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 			CYC_TiExpired = TRUE */
/*%C 			CYC_TeExpired = FALSE  */
			CYC_TiExpired = TRUE;
			CYC_TeExpired = FALSE;
/*%C 		The "Exhalation" state must be activated */
      	CYC_ActiveModeState.Vsimv = SIMV_VSIMV_EXHALATION;
/*%C 		Gives the timer value for the exhalation start */
			ExhStartSimvCounter = 	TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT);
		}
	break;
		

/******************************************************************************/
/*                        PSV INSPIRATION STATE	   		   						*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Simv" is psv inspiration :     */
	case SIMV_PSV_INSPIRATION :

/*%C  Searching the Ti Limits :*/
/*%C  CYC_TiLimitsCompute function is launch and return TiMin and Timax */
		Ti = CYC_TiLimitsCompute();

/*%C  if an exhalation trigger occurs after a minimal inspiration delay */
/*%C  or if the inspiration delay becomes higher than the maximal limit,*/
/*%C  or if a high pressure alarm occurs, then */
		if ( ( (CYC_TriggerEDetection() == TRUE)
		    && (TIM_ReadCounterValue(VEN_TI_COUNT) >= Ti.TiMin) )
	 	  || (TIM_ReadCounterValue(VEN_TI_COUNT) >= Ti.TiMax)
	  	  || (High_Pressure_Detected >= TRUE) )
	   {
/*%C 		The inspiration duration is recorded in order to compute the IE ratio*/
/*%C 		into an other module .*/
			VEN_TiTeValueMesured.TiValCount = TIM_ReadCounterValue(VEN_TI_COUNT);
/*%C 		The counter "VEN_TE_COUNT" starts. */
			TIM_StartCounter(VEN_TE_COUNT);
/*%C 		The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
/*%C 		"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TiExpired = TRUE */
/*%C 		CYC_TeExpired = FALSE  */
			CYC_TiExpired = TRUE;
			CYC_TeExpired = FALSE;
/*%C 		The "Exhalation" state must be activated */
      		CYC_ActiveModeState.Vsimv  = SIMV_VSIMV_EXHALATION;
/*%C 		Gives the timer value for the exhalation start 								*/
			ExhStartSimvCounter = 	TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT);
/*%C		If there is not enough time (2*ti) until Tb	*/
/*%C		the next VIM should be delayed  													*/
			if (ExhStartSimvCounter + 2 * VEN_TiTeValueMesured.TiValCount >=
																						 SIMVPeriod)
			{
				VimDelayed = TRUE;
			}
/*%C 		Pressure spontaneous breath end management */
/*%C 		The 6 last type of PSV inspiration end conditions are saved */
/*%C 		When 4 or more are terminated by time, an alarm is set (VEN_Security)*/
			if (TIM_ReadCounterValue(VEN_TI_COUNT) >= Ti.TiMax)
			{
				VEN_SIMV_PS_End[j].EndType = PS_TIMED_END;
				TIM_StartDecounter(VEN_SIMV_PS_End[j].TimerId, 60000);
			}
			else if (High_Pressure_Detected >= TRUE)
			{
				VEN_SIMV_PS_End[j].EndType = PS_HIGH_PRESS_END;
			}
			else
			{
				VEN_SIMV_PS_End[j].EndType = PS_FLOW_END;
			}
			j = (j + 1) % 6;
		}
  		break;

/******************************************************************************/
/*                        CV INSPIRATION STATE	   		   						*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Simv" is CV inspiration :     */
	case SIMV_CV_INSPIRATION :
/*%C  if Ti counter is equal to or upper than the adjusted Ti Control,*/
/*%C  or the high pressure alarm is TRUE, then */
		if ( (TIM_ReadCounterValue(VEN_TI_COUNT) >= AdjustTiControl)	 	
	     || (High_Pressure_Detected >= TRUE) )
	   {
/*%C 		The inspiration duration is recorded in order to compute the IE ratio*/
/*%C 		into an other module .*/
			VEN_TiTeValueMesured.TiValCount = TIM_ReadCounterValue(VEN_TI_COUNT);
/*%C 		The counter "VEN_TE_COUNT" starts. */
			TIM_StartCounter(VEN_TE_COUNT);
/*%C 		The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
/*%C 		"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TiExpired = TRUE */
/*%C 		CYC_TeExpired = FALSE  */
			CYC_TiExpired = TRUE;
			CYC_TeExpired = FALSE;
/*%C 		The "cv Exhalation" state must be activated */
      	CYC_ActiveModeState.Vsimv  = SIMV_VSIMV_EXHALATION;
/*%C 		Gives the timer value for the exhalation start */
			ExhStartSimvCounter = 	TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT);
		}
	break;

/******************************************************************************/
/*                        CV INSPIRATION APNEA STATE	   		   			  */
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Simv" is CV inspiration :     */
	case SIMV_CV_INSPIRATION_APNEA :
/*%C  if Ti counter is equal to or upper than the adjusted Ti Control,*/
/*%C  or the high pressure alarm is TRUE, then */
		if ( (TIM_ReadCounterValue(VEN_TI_COUNT) >= AdjustTiControl)	 	
	     || (High_Pressure_Detected >= TRUE) )
	   {
/*%C 		The inspiration duration is recorded in order to compute the IE ratio*/
/*%C 		into an other module .*/
			VEN_TiTeValueMesured.TiValCount = TIM_ReadCounterValue(VEN_TI_COUNT);
/*%C 		The counter "VEN_TE_COUNT" starts. */
			TIM_StartCounter(VEN_TE_COUNT);
/*%C 		The inspiration type is set to NO_INSP. */
         	InspirationType = NO_INSP;
/*%C 		"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TiExpired = TRUE */
/*%C 		CYC_TeExpired = FALSE  */
			CYC_TiExpired = TRUE;
			CYC_TeExpired = FALSE;
/*%C 		The "cv Exhalation" state must be activated */
      		CYC_ActiveModeState.Vsimv  = SIMV_VSIMV_EXHALATION_APNEA;
/*%C 		Gives the timer value for the exhalation start */
			ExhStartSimvCounter = 	TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT);
		}
	break;

/******************************************************************************/
/*                         VSIMV EXHALATION APNEA STATE									*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Vsimv" is VSIMV exhalation :     */
	case SIMV_VSIMV_EXHALATION_APNEA :
/*%C  	If an inspiration trigger is selected and detected, then  */
		if ( CYC_TriggerIDetection() == TRUE)
		{
/*%C 		if SIMV timer < Simv backup period		*/
/*%C 		=> the next inspi is a CAV cycle (PIM)  */
/*%C 		=> the Simv backup period counter is launched  */
			if (TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT) < SIMVBackupPeriod)
			{
/*%C 			The kind of inspiration detection is TRIGGERED. */
				InspirationType =	TRIGGERED;
/*%C 			"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values:*/
/*%C 				CYC_TeExpired = TRUE */
/*%C 				CYC_TiExpired = FALSE  */
				CYC_TeExpired = TRUE;
				CYC_TiExpired = FALSE;
/*%C 			Record of the new phase of VSIMV mode */			
				VEN_SIMVCycle = CAV_Cycle;
				DB_ControlWrite(SIMV_CYCLES_U16,CAV_Cycle);
				DB_ControlWrite(SIMV_CONTROLLED_INSP_U16,FALSE);

/*%C			if the "reset apnea"counter is lower than 2, then */
      			if (ResetApneaCpt < cNB_TRIGGER_APNEA_OFF)
				{
/*%C     			Increasing  the counter of apnea cycle */
	  	   			ResetApneaCpt = ResetApneaCpt + 1;
				}
/*%C 			if no alarm apnea 			 */
				if (ResetApneaCpt >= cNB_TRIGGER_APNEA_OFF)
				{
/*%C 				The "CAV Inspiration" state must be activated */
	  				CYC_ActiveModeState.Vsimv = SIMV_CAV_INSPIRATION;
      				ResetApneaCpt = 0;
				}
				else
				{
/*%C 				Staying in "CV Inspiration apnea" state */
	  				CYC_ActiveModeState.Vsimv = SIMV_CV_INSPIRATION_APNEA;
				}

/*%C 			The counter "VEN_TI_COUNT" starts. */
				TIM_StartCounter(VEN_TI_COUNT);
/*%C			The counter "VEN_SIMV_PERIOD_COUNT" starts */
				TIM_StartCounter(VEN_SIMV_PERIOD_COUNT);
/*%C			Initializes the VIM canceled flag information */
				VimCanceled = FALSE;
				VEN_SIMV_Cycle_History[i] = PIM;
/*%C			Array index increasing  */
				i = (i + 1) % 6;
			}
		}
/*%C 	else if no insp sens selected and  simv period is reached */
/*%C 	=> the next inspi is a CV cycle (VIM) */
/*%C 	=> the Simv backup period counter is launched  */
		else if (TIM_ReadCounterValue(VEN_SIMV_PERIOD_COUNT) >= SIMVBackupPeriod)

		{
/*%C 		The kind of inspiration detection is CONTROLLED. */
			InspirationType =	CONTROLLED;
/*%C 		"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values:*/
/*%C 		CYC_TeExpired = TRUE */
/*%C 		CYC_TiExpired = FALSE  */
			CYC_TeExpired = TRUE;
			CYC_TiExpired = FALSE;
/*%C 		Record of the new phase of VSIMV mode */			
			VEN_SIMVCycle = CV_Cycle;
			DB_ControlWrite(SIMV_CYCLES_U16,CV_Cycle);
			DB_ControlWrite(SIMV_CONTROLLED_INSP_U16,TRUE);
/*%C 		Staying in "CV Inspiration apnea" state */
	 		CYC_ActiveModeState.Vsimv = SIMV_CV_INSPIRATION_APNEA;
/*%C		The counter "VEN_SIMV_PERIOD_COUNT" starts */
			TIM_StartCounter(VEN_SIMV_PERIOD_COUNT);
/*%C		Initializes the VIM canceled flag information */
			VimCanceled = FALSE;
/*%C		A VIM cycle is mentionned in the history cycle array  */
			VEN_SIMV_Cycle_History[i] = VIM;
/*%C		Array index increasing  */
			i = (i + 1) % 6;
/*%C		Apnea reset counter reset  */
			ResetApneaCpt = 0;
		}
		else
		{
/*%C 		The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
		}

/*%C Inspiration phase initialisation : */
/*%C If CYC_TeExpired == TRUE,then  */
	if (CYC_TeExpired == TRUE)
	{
									  
/*%C  The exhalation duration is recorded in order to compute the IE ratio*/
/*%C  into an other module .*/
		VEN_TiTeValueMesured.TeValCount = TIM_ReadCounterValue(VEN_TE_COUNT);
/*%C  The counter "VEN_TI_COUNT" starts. */
      TIM_StartCounter(VEN_TI_COUNT);
/*%C  A copy of adjust data base into current once is launched. */
      DB_CopyMngt();
/*%C  The decounter of Apnea is launched */
 	  AdjustApnea = DB_CurrentRead(ADJUST_APNEA_U16);
	  TIM_StartDecounter(SEC_APNEA,AdjustApnea);
	  TIM_StartDecounter(SEC_APNEA_FLAG,AdjustApnea);
	}
/*%C Flow max initialization */
	CYC_Qmax = 0;
	break;



/******************************************************************************/
/*                         DEFAULT											*/
/******************************************************************************/
	default:
/*%C  The "cv Exhalation" state must be activated */
		CYC_ActiveModeState.Vsimv  = SIMV_CV_EXHALATION;
/*%C  The inspiration type is set to NO_INSP. */
		InspirationType = NO_INSP;
/*%C Flow max initialization */
		CYC_Qmax = 0;
	break;
	}
/******************************************************************************/
/*%C            Excessive leak detection													*/
/******************************************************************************/

	return(InspirationType);
}
