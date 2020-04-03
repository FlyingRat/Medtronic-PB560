/******************************************************************************/
/*                                                                            */
/* Project N°  :  RR0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_Psvt_CyclesMngt.c 														*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Respiratory cycle management in PSVT  mode           			   */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : e_InspDetectType InspirationType                      */
/******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES		                           */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "Ventilation_Datas.h"
#include "Ventilation_Cycles_Datas.h"
#include "CYC_Psvt_CyclesMngt.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_InspDetectType CYC_Psvt_CyclesMngt(void)
{
UWORD16 AdjustBackUpR = DB_CurrentRead(ADJUST_BACKUP_R_U16);
UWORD16 BackUpRNoSelect = DB_CurrentRead(BACKUP_R_NO_SELECT_U16);
UWORD16 Insp_Sens_No_Select = DB_CurrentRead(INSP_SENS_NO_SELECT_U16);
UWORD16 AdjustApnea = DB_CurrentRead(ADJUST_APNEA_U16);
UWORD16 High_Pressure_Detected = DB_ControlRead(HIGH_PRESSURE_DETECTED_U16);
UWORD16 Adjustment_In_Progress = DB_ControlRead(ADJUSTMENT_IN_PROGRESS_U16);
UWORD16 BackUpDelay = 60000U / AdjustBackUpR;
e_InspDetectType InspirationType = NO_INSP;
t_CYC_TiLimit Ti ={0,0};
UWORD16 BackuUpRNoSelectChange = FALSE;
UWORD16 TriggerIDetection = FALSE;
static UWORD16 PreviousBackuUpRNoSelect = FALSE;
static MemoInspSensNoSelect = FALSE;

/*%C Backup R no select state change detection in order to leave the  			*/
/*%C CC EXHALATION state, because during an apnea the setting change is not 	*/
/*%C made (insp/exh transition)    															*/
	if ( (PreviousBackuUpRNoSelect == FALSE)
	  && (BackUpRNoSelect == TRUE) )
	{
		BackuUpRNoSelectChange = TRUE;
	}	  	 
/*%C Previous Backup R no select updating													*/
	PreviousBackuUpRNoSelect = BackUpRNoSelect;

	switch (CYC_ActiveModeState.Psvt)
	{
/******************************************************************************/
/*                          ACTIVATED STATE												*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Psvt" is activated :     */
/*%C It is the initial value of the state machine. */
	case ACTIVATED :
/*%C if "CYC_TeExpired" is false :*/
      if (CYC_TeExpired == FALSE)
      {
/*%C The counter "VEN_TE_Count" starts. */
         TIM_StartCounter(VEN_TE_COUNT);
/*%C The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
/*%C "CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 			CYC_TeExpired = FALSE */
/*%C 			CYC_TiExpired = TRUE  */
         CYC_TeExpired = FALSE;
         CYC_TiExpired = TRUE;
/*%C The "Exhalation" state must be activated */
         CYC_ActiveModeState.Psvt = PSV_EXHALATION;
      }
/* If it is a mode change, an exhalation has already occured */
      else
		{
/*%C The counter "VEN_TI_COUNT" starts. */
         TIM_StartCounter(VEN_TI_COUNT);
/*%C The kind of inspiration detection is TRIGGERED. */
         InspirationType = TRIGGERED;
/*%C A copy of adjust data base into current's is launched. */
         DB_CopyMngt();
/*%C "CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 			CYC_TeExpired = TRUE */ 
/*%C 			CYC_TiExpired = FALSE  */
         CYC_TeExpired = TRUE;
         CYC_TiExpired = FALSE;
/*%C The "Inspiration" state must be activated */
         CYC_ActiveModeState.Psvt =	PSV_INSPIRATION;
		}
/*%C Flow max initialization */
		CYC_Qmax = 0;
		break;


/******************************************************************************/
/*                         PSV EXHALATION STATE											*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Psvt" is psv exhalation :     */
	case PSV_EXHALATION :
/*%C A trigger detection is launched, only if the adjustment is different from */
/*%C "OFF", and if it is, there is two case :*/
/*%C 	- the first one is: if an adjustment is not in progress, then the detection */
/*%C      can occur.   */
/*%C    - the second one is: if an adjustment is in progress, then we must know */
/*%C      if the initial value is "OFF". If it is,then the detection can't be launched,*/
/*%C	  else it is launched with the old value of setting (which wasn't still modified */
/*%C	  into the "current" database. */
		if (Insp_Sens_No_Select == FALSE)
		{
			if(Adjustment_In_Progress == TRUE)
			{
				if(MemoInspSensNoSelect == FALSE)
				{
					TriggerIDetection = CYC_TriggerIDetection();
				}
				else
				{	
					TriggerIDetection = FALSE;
				}
			}
			else
			{
				TriggerIDetection = CYC_TriggerIDetection();
			}
		}
		else
		{
			TriggerIDetection = FALSE;	
		}
		if(TriggerIDetection == TRUE)
		{
/*%C The kind of inspiration detection is TRIGGERED. */
			InspirationType =	TRIGGERED;
/*%C "CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TeExpired = TRUE */
/*%C 		CYC_TiExpired = FALSE  */
			CYC_TeExpired = TRUE;
			CYC_TiExpired = FALSE;
/*%C The "PSV Inspiration" state must be activated */
	     	CYC_ActiveModeState.Psvt = PSV_INSPIRATION;
		}	
/*%C Otherwise if the backup R isn't set to OFF (BackUpRNoSelect == FALSE)*/
/*%C and the Te counter becomes equal or higher than the computed Te, then*/
	  	else if ((BackUpRNoSelect == FALSE) 
	  	&& (TIM_ReadCounterValue(VEN_TE_COUNT) >= AdjustApnea))
    	{
/*%C The kind of inspiration detection is CONTROLLED. */
			InspirationType = CONTROLLED;
/*%C "CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TeExpired = TRUE */
/*%C 		CYC_TiExpired = FALSE  */
			CYC_TeExpired = TRUE;
			CYC_TiExpired = FALSE;
/*%C The "PSV Inspiration" state must be activated */
      	CYC_ActiveModeState.Psvt = CC_INSPIRATION;
		}
		else
		{
/*%C The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
		}
/*%C As long as there is no adjustment, we save if the "InspSensNoSelect" flag.*/
		if(Adjustment_In_Progress == FALSE)
		{
			MemoInspSensNoSelect = Insp_Sens_No_Select;	
		}

/*%C Inspiration phase initialisation : */
/*%C If CYC_TeExpired == TRUE,then  */
	if (CYC_TeExpired == TRUE)
		{										  
/*%C The exhalation duration is recorded in order to compute the IE ratio*/
/*%C into an other module .*/
      VEN_TiTeValueMesured.TeValCount = TIM_ReadCounterValue(VEN_TE_COUNT);
/*%C The counter "VEN_TI_COUNT" starts. */
      TIM_StartCounter(VEN_TI_COUNT);
/*%C The counter "VEN_CONTROLLED_CYCLE_PERIOD_COUNT" starts */
		TIM_StartCounter(VEN_CONTROLLED_CYCLE_PERIOD_COUNT);
/*%C A copy of adjust data base into current once is launched. */
      DB_CopyMngt();
		}
/*%C Flow max initialization */
	CYC_Qmax = 0;
	break;

/******************************************************************************/
/*                        PSV INSPIRATION STATE	   		   						*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Psvt" is psv inspiration :     */
	case PSV_INSPIRATION :

/*%C Searching the Ti Limits :*/
/*%C CYC_TiLimitsCompute function is launch and return TiMin and Timax */
		Ti = CYC_TiLimitsCompute();
/*%C if an exhalation trigger occurs after a minimal inspiration delay */
/*%C or if the inspiration delay becomes higher than the maximal limit,*/
/*%C or if a high pressure alarm occurs, then */
		if (((CYC_TriggerEDetection() == TRUE)
		&& (TIM_ReadCounterValue(VEN_TI_COUNT) >= Ti.TiMin))
	 	|| (TIM_ReadCounterValue(VEN_TI_COUNT) >= Ti.TiMax)
	  	|| (High_Pressure_Detected >= TRUE))
	   {
         InspirationType = NO_INSP;
/*%C The inspiration duration is recorded in order to compute the IE ratio*/
/*%C into an other module .*/
			VEN_TiTeValueMesured.TiValCount = TIM_ReadCounterValue(VEN_TI_COUNT);
/*%C The counter "VEN_TE_COUNT" starts. */
			TIM_StartCounter(VEN_TE_COUNT);
/*%C The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
/*%C "CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TiExpired = TRUE */
/*%C 		CYC_TeExpired = FALSE  */
			CYC_TiExpired = TRUE;
			CYC_TeExpired = FALSE;
/*%C The "Exhalation" state must be activated */
      	CYC_ActiveModeState.Psvt  = PSV_EXHALATION;
		}

	break;

/******************************************************************************/
/*                        CC INSPIRATION STATE	   		   						*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Psvt" is cc inspiration :     */
	case CC_INSPIRATION :

/*%C Searching the Ti Limits :*/
/*%C CYC_TiLimitsCompute function is launch and return TiMin and Timax */
		Ti = CYC_TiLimitsCompute();

/*%C if an exhalation trigger occurs after a minimal inspiration delay */
/*%C or if the inspiration delay becomes higher than the maximal limit,*/
/*%C or if a high pressure alarm occurs, then */
		if (((CYC_TriggerEDetection() == TRUE)
		&& (TIM_ReadCounterValue(VEN_TI_COUNT) >= Ti.TiMin))
	 	|| (TIM_ReadCounterValue(VEN_TI_COUNT) >= Ti.TiMax)
	  	|| (High_Pressure_Detected >= TRUE))
	   {
/*%C The inspiration duration is recorded in order to compute the IE ratio*/
/*%C into an other module .*/
			VEN_TiTeValueMesured.TiValCount = TIM_ReadCounterValue(VEN_TI_COUNT);
/*%C The counter "VEN_TE_COUNT" starts. */
			TIM_StartCounter(VEN_TE_COUNT);
/*%C The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
/*%C "CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TiExpired = TRUE */
/*%C 		CYC_TeExpired = FALSE  */
			CYC_TiExpired = TRUE;
			CYC_TeExpired = FALSE;
/*%C The "cc Exhalation" state must be activated */
      	CYC_ActiveModeState.Psvt  = CC_EXHALATION;
		}

	break;

/******************************************************************************/
/*                         CC EXHALATION STATE											*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Psvt" is cc exhalation :     */
	case CC_EXHALATION :
/*%C A trigger detection is launched, only if the adjustment is different from */
/*%C "OFF", and if it is, there is two case :*/
/*%C 	- the first one is: if an adjustment is not in progress, then the detection */
/*%C      can occur.   */
/*%C    - the second one is: if an adjustment is in progress, then we must know */
/*%C      if the initial value is "OFF". If it is,then the detection can't be launched,*/
/*%C	  else it is launched with the old value of setting (which wasn't still modified */
/*%C	  into the "current" database. */
		if (Insp_Sens_No_Select == FALSE)
		{
			if(Adjustment_In_Progress == TRUE)
			{
				if(MemoInspSensNoSelect == FALSE)
				{
					TriggerIDetection = CYC_TriggerIDetection();
				}
				else
				{	
					TriggerIDetection = FALSE;
				}
			}
			else
			{
				TriggerIDetection = CYC_TriggerIDetection();
			}
		}
		else
		{
			TriggerIDetection = FALSE;	
		}
		if(TriggerIDetection == TRUE)
		{
/*%C The kind of inspiration detection is TRIGGERED. */
			InspirationType =	TRIGGERED;
/*%C "CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TeExpired = TRUE */
/*%C 		CYC_TiExpired = FALSE  */
			CYC_TeExpired = TRUE;
			CYC_TiExpired = FALSE;
/*%C The "PSV Inspiration" state must be activated */
	     	CYC_ActiveModeState.Psvt = PSV_INSPIRATION;
		}	
/* Otherwise if the counter becomes equal or higher than the computed Te, then*/
	  	else if ( ( (BackUpRNoSelect == FALSE)
	  	         && (TIM_ReadCounterValue(VEN_CONTROLLED_CYCLE_PERIOD_COUNT) 
	  											>= BackUpDelay) )
				 || (BackuUpRNoSelectChange == TRUE) )
    	{
/*%C The kind of inspiration detection is CONTROLLED. */
			InspirationType = CONTROLLED;
/*%C "CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TeExpired = TRUE */
/*%C 		CYC_TiExpired = FALSE  */
			CYC_TeExpired = TRUE;
			CYC_TiExpired = FALSE;
/*%C The "PSV Inspiration" state must be activated */
      	CYC_ActiveModeState.Psvt = CC_INSPIRATION;
		}
		else
		{
/*%C The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
		}

/*%C Inspiration phase initialisation : */
/*%C If CYC_TeExpired == TRUE,then  */
	if (CYC_TeExpired == TRUE)
		{										  
/*%C The exhalation duration is recorded in order to compute the IE ratio*/
/*%C into an other module .*/
      VEN_TiTeValueMesured.TeValCount = TIM_ReadCounterValue(VEN_TE_COUNT);
/*%C The counter "VEN_TI_COUNT" starts. */
      TIM_StartCounter(VEN_TI_COUNT);
/*%C The counter "VEN_CONTROLLED_CYCLE_PERIOD_COUNT" starts */
		TIM_StartCounter(VEN_CONTROLLED_CYCLE_PERIOD_COUNT);
/*%C A copy of adjust data base into current once is launched. */
      DB_CopyMngt();
		}
/*%C Flow max initialization */
	CYC_Qmax = 0;
	break;

/******************************************************************************/
/*                         DEFAULT											*/
/******************************************************************************/
	default:
/*%C The "cc Exhalation" state must be activated */
      	CYC_ActiveModeState.Psvt  = CC_EXHALATION;
/*%C The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
/*%C Flow max initialization */
		CYC_Qmax = 0;
	break;
	}

return (InspirationType);
}