/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_Pres_Vol_CyclesMngt.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Respiratory cycle management in Pres and Vol mode 					* 
/*           																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : e_InspDetectType InspirationType       					*/
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
#include "CYC_Pres_Vol_CyclesMngt.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_InspDetectType CYC_Pres_Vol_CyclesMngt(void)
{
UWORD16 AdjustControlR = DB_CurrentRead(ADJUST_CONTROL_R_U16);
UWORD16 AdjustTiControl = DB_CurrentRead(ADJUST_TI_CONTROL_U16);
UWORD16 AdjustVolControl = DB_CurrentRead(ADJUST_VOL_CONTROL_U16);
UWORD16 InspSensNoSelect = DB_CurrentRead(INSP_SENS_NO_SELECT_U16);
/*%C High pressure flag state recovery in Data base  */
UWORD16 High_Pressure_Detected =
						 DB_ControlRead(HIGH_PRESSURE_DETECTED_U16);
UWORD16 Adjust_Sigh_Select = DB_CurrentRead(ADJUST_SIGH_SELECT_U16);
UWORD16 Adjust_Sigh_Cpt = DB_CurrentRead(ADJUST_SIGH_CPT_U16);
UWORD16 Adjust_Sigh_Vt_Coef = DB_CurrentRead(ADJUST_SIGH_VT_COEF_U16);
e_MODE_TYPES CurrentMode = DB_ControlRead(CURRENT_MODE_U16);
UWORD16 Adjustment_In_Progress = DB_ControlRead(ADJUSTMENT_IN_PROGRESS_U16);
e_InspDetectType InspirationType = NO_INSP;
UWORD16 TriggerIDetection = FALSE;
static UWORD16 Te = 0;
static e_InspDetectType MemoInspirationType = NO_INSP;
static UWORD16 SighCount = 0;
static MemoInspSensNoSelect = FALSE;
static UBYTE AdjustTiControlMutex = FALSE;

		/*%C Flag for reset of sight counter when ventilation stops */
		if (RazSightCpt == TRUE)
			{
				SighCount = 0;
				RazSightCpt = FALSE;
			}
									
	switch (CYC_ActiveModeState.VolPres)
	{

/******************************************************************************/
/*                          ACTIVATED STATE												*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.VolPres" is activated :     */
/*%C It is the initial value of the state machine. */
	case ACTIVATED :
	AdjustTiControlMutex = FALSE;

/*%C  Te computing : it is needed in case of mode change.*/
/*%C  	Te = (60/AdjustControlR)-AdjustTiControl */
	Te = (UWORD16)((60000 / AdjustControlR) - AdjustTiControl);
		

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
         CYC_ActiveModeState.VolPres = EXHALATION;
      }
/* If it is a mode change, an exhalation has already been occured */
      else
		{
/*%C 		Sigh detection */
/*%C 		If sigh option selected in VOL mode */
        	if ( (Adjust_Sigh_Select == TRUE) 
			  && (CurrentMode == VOL) )
      	{
/*%C 			if the counter is higher than the setting value, */
/*%C			the sigh detection flag is set 							*/
	         if (SighCount >= (Adjust_Sigh_Cpt - 1))
         	{
           		SighCount = 0;
           		VEN_SighDetected = TRUE;
				}
/*%C 			sigh counter is increased */
        		else
        		{
           		SighCount = SighCount + 1;
           		VEN_SighDetected = FALSE;
        		}
     		}
/*%C 		No Sigh detection */
			else
			{
				VEN_SighDetected = FALSE;
			}

/*%C The counter "VEN_TI_COUNT" starts. */
         TIM_StartCounter(VEN_TI_COUNT);
/*%C The kind of inspiration detection is CONTROLLED. */
         InspirationType = CONTROLLED;
/*%C Inspiration type memorization */
			MemoInspirationType = CONTROLLED;
/*%C A copy of adjust data base into current once is launched. */
         DB_CopyMngt();
/*%C "CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 			CYC_TeExpired = TRUE */ 
/*%C 			CYC_TiExpired = FALSE  */
         CYC_TeExpired = TRUE;
         CYC_TiExpired = FALSE;
/*%C The "Inspiration" state must be activated */
         CYC_ActiveModeState.VolPres =	INSPIRATION;
		}
		break;
	
/******************************************************************************/
/*                          EXHALATION STATE												*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.VolPres" is exhalation :     */
	case EXHALATION :
/*%C If a High pressure occurs, we must take the last Ti measurement to keep a right I/E ratio */
/*%C  Te = (60/AdjustControlR)-VEN_TiTeValueMesured.TiValCount */
		if(High_Pressure_Detected == TRUE)
		{
			Te = (UWORD16)((60000 / AdjustControlR ) - VEN_TiTeValueMesured.TiValCount ); 
		}


/*%C A trigger detection is launched, only if the adjustment is different from */
/*%C "OFF", and if it is, there is two case :*/
/*%C 	- the first one is: if an adjustment is not in progress, then the detection */
/*%C      can occur.   */
/*%C    - the second one is: if an adjustment is in progress, then we must know */
/*%C      if the initial value is "OFF". If it is,then the detection can't be launched,*/
/*%C	  else it is launched with the old value of setting (which wasn't still modified */
/*%C	  into the "current" database. */
		if (InspSensNoSelect == FALSE)
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
/*%C Inspiration type memorization */
				MemoInspirationType = TRIGGERED;
/*%C "CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TeExpired = TRUE */
/*%C 		CYC_TiExpired = FALSE  */
				CYC_TeExpired = TRUE;
				CYC_TiExpired = FALSE;
		}
		
/* Otherwise if the counter becomes equal or higher than the computed Te, then*/
	  	else if (TIM_ReadCounterValue(VEN_TE_COUNT) >= Te)
    	{

/*%C The kind of inspiration detection is CONTROLLED. */
			InspirationType = CONTROLLED;
/*%C Inspiration type memorization */
			MemoInspirationType = CONTROLLED;
/*%C "CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TeExpired = TRUE */
/*%C 		CYC_TiExpired = FALSE  */
			CYC_TeExpired = TRUE;
			CYC_TiExpired = FALSE;
		}
		else
		{
/*%C The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
		}
/*%C As long as there is no adjustment, we save if the "InspSensNoSelect" flag.*/
		if(Adjustment_In_Progress == FALSE)
		{
			MemoInspSensNoSelect = InspSensNoSelect;	
		}


/*%C Inspiration phase initialisation : */
/*%C If CYC_TeExpired == TRUE,then  */
	if (CYC_TeExpired == TRUE)
	{
/*%C 		Sigh detection */
/*%C 		If sigh option selected in VOL mode */
       	if ( (Adjust_Sigh_Select == TRUE) 
		  && (CurrentMode == VOL) )
      	{
/*%C 			if the counter is higher than the setting value, the flag is set */
	         if (SighCount >= (Adjust_Sigh_Cpt - 1))
         	{
	       		SighCount = 0;
	       		VEN_SighDetected = TRUE;
				AdjustTiControlMutex = FALSE;
			}
/*%C 			sigh counter is increased */
    		else
    		{
	       		SighCount = SighCount + 1;
	       		VEN_SighDetected = FALSE;
    		}
		}
		else
		{
			SighCount = 0;
			VEN_SighDetected = FALSE;
		}

										  
/*%C The exhalation duration is recorded in order to compute the IE ratio*/
/*%C into an other module .*/
      VEN_TiTeValueMesured.TeValCount = TIM_ReadCounterValue(VEN_TE_COUNT);
/*%C The counter "VEN_TI_COUNT" starts. */
      TIM_StartCounter(VEN_TI_COUNT);
/*%C A copy of adjust data base into current once is launched. */
/*%C Update of Rate and adjust TI for compute Te. */
      DB_CopyMngt();
	  AdjustControlR = DB_CurrentRead(ADJUST_CONTROL_R_U16);
	  AdjustTiControl = DB_CurrentRead(ADJUST_TI_CONTROL_U16);
/*%C  Te computing :*/
	   if ( (VEN_SighDetected == TRUE)
		  && (CurrentMode == VOL) )
		{
/*%C  	Te = ((60/AdjustControlR) * sigh coef - AdjustTiControl) */
			Te = (UWORD16)((60000 / AdjustControlR) * Adjust_Sigh_Vt_Coef / 10);
			Te = Te - (AdjustTiControl * 2);
		}
	   else
		{
/*%C  	Te = (60/AdjustControlR)-AdjustTiControl */
			Te = (UWORD16)((60000 / AdjustControlR) - AdjustTiControl);
		}

/*%C 	If sigh detected, Ti is increased function of sigh coef     */
	   if ( (VEN_SighDetected == TRUE)
		  && (CurrentMode == VOL)
		  && (AdjustTiControlMutex == FALSE))
		{
			AdjustTiControlMutex = TRUE;
/*%C  	Ti = AdjustTiControl * sigh coef */
			AdjustTiControl = (AdjustTiControl * Adjust_Sigh_Vt_Coef) / 10;
			DB_CurrentWrite(ADJUST_TI_CONTROL_U16, AdjustTiControl);
/*%C  	VolControl = AdjustVolControl * sigh coef */
			AdjustVolControl = (AdjustVolControl * Adjust_Sigh_Vt_Coef) / 10;
			DB_CurrentWrite(ADJUST_VOL_CONTROL_U16, AdjustVolControl);
		}
		else
		{

		}
/*%C The "Inspiration" state must be activated */
      CYC_ActiveModeState.VolPres = INSPIRATION;
	}
	break;
	
/******************************************************************************/
/*                          INSPIRATION STATE	   									*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.VolPres" is inspiration :     */
	case INSPIRATION :
  	   	VEN_SighDetected = FALSE;

	  	if ( (TIM_ReadCounterValue(VEN_TI_COUNT) >= AdjustTiControl)
	  	  || (High_Pressure_Detected >= TRUE) )
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
/*%C The "Exhalation" state must be activated */
      	CYC_ActiveModeState.VolPres = EXHALATION;
		}
		else
		{
			InspirationType = MemoInspirationType;
		}
		break;

/******************************************************************************/
/*                         DEFAULT											*/
/******************************************************************************/
	default:
			AdjustTiControlMutex = FALSE;
/*%C The "Exhalation" state must be activated */
      	CYC_ActiveModeState.VolPres = EXHALATION;
/*%C The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
	break;
	}

return (InspirationType);
}
