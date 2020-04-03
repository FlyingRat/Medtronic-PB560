/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_CpapCyclesMngt.c 														*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Respiratory cycle management in CPAP mode 			            */
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
#include "Ventilation_Datas.h"
#include "Ventilation_Cycles_Datas.h"
#include "CYC_CpapCyclesMngt.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_InspDetectType CYC_CpapCyclesMngt(void)
{
UWORD16 TiMaxAuto = 0;
e_InspDetectType InspirationType = NO_INSP;
t_CYC_TiLimit Ti={0,0};

/*%C High pressure flag state recovery in Data base  */
UWORD16 High_Pressure_Detected=
						 DB_ControlRead(HIGH_PRESSURE_DETECTED_U16);

	switch (CYC_ActiveModeState.Cpap)
	{
/******************************************************************************/
/*                          ACTIVATED STATE												*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Cpap" is activated :     */
/*%C It is the initial value of the state machine. */
	case ACTIVATED :
/*%C 		"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TiExpired = TRUE */
/*%C 		CYC_TeExpired = FALSE  */
		CYC_TeExpired = FALSE;
		CYC_TiExpired = TRUE;
/*%C  The "Exhalation" state must be activated */
		CYC_ActiveModeState.Cpap = CPAP_EXHALATION;
/*%C  The counter "VEN_TE_COUNT" starts. */
		TIM_StartCounter(VEN_TE_COUNT);
/*%C Flow max initialization */
		CYC_Qmax = 0;
		break;


/******************************************************************************/
/*                         CPAP EXHALATION STATE										*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Cpap" is cpap exhalation :     				*/
	case CPAP_EXHALATION :
/*%C  If an inspiration trigger is selected and detected, then  					*/
		if (CYC_TriggerIDetection() == TRUE) 
		{
/*%C 		The kind of inspiration detection is TRIGGERED. */
			InspirationType =	TRIGGERED;
/*%C 		"CYC_TeExpired" and "CYC_TiExpired" are set to the correct values :*/
/*%C 		CYC_TeExpired = TRUE */
/*%C 		CYC_TiExpired = FALSE  */
			CYC_TeExpired = TRUE;
			CYC_TiExpired = FALSE;
/*%C 		The "PSV Inspiration" state must be activated */
     		CYC_ActiveModeState.Cpap = CPAP_INSPIRATION;
		}
		else
		{
/*%C 		The inspiration type is set to NO_INSP. */
         InspirationType = NO_INSP;
		}

/*%C  Inspiration phase initialization : */
/*%C  If CYC_TeExpired == TRUE,then  */
		if (CYC_TeExpired == TRUE)
		{										  
/*%C  	The exhalation duration is recorded in order to compute the IE ratio*/
/*%C 		into an other module .*/
	      VEN_TiTeValueMesured.TeValCount = TIM_ReadCounterValue(VEN_TE_COUNT);
/*%C 		The counter "VEN_TI_COUNT" starts. */
	      TIM_StartCounter(VEN_TI_COUNT);
/*%C 		A copy of adjust data base into current once is launched. */
	      DB_CopyMngt();
		}
/*%C  Flow max initialization */
		CYC_Qmax = 0;
		break;

/******************************************************************************/
/*                        CPAP INSPIRATION STATE	   		   					*/
/******************************************************************************/
/*%C In case of "CYC_ActiveModeState.Cpap" is psv inspiration :     				*/
	case CPAP_INSPIRATION :

/*%C  Searching the Ti Limits :*/
/*%C  CYC_TiLimitsCompute function is launch and return TiMin and Timax */
		Ti = CYC_TiLimitsCompute();
/*%C  if an exhalation trigger occurs after a minimal inspiration delay */
/*%C  or if the inspiration delay becomes higher than the maximal limit,*/
/*%C  or if a high pressure alarm occurs, then */
		if (((CYC_TriggerEDetection() == TRUE)
		&& (TIM_ReadCounterValue(VEN_TI_COUNT) >= Ti.TiMin))
	  	|| (High_Pressure_Detected >= TRUE))
	   {
         InspirationType = NO_INSP;
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
      	CYC_ActiveModeState.Cpap  = CPAP_EXHALATION;
		}

	break;


/******************************************************************************/
/*                         DEFAULT											*/
/******************************************************************************/
	default:
/*%C  The "cc Exhalation" state must be activated */
      CYC_ActiveModeState.Cpap  = CPAP_EXHALATION;
/*%C  The inspiration type is set to NO_INSP. */
      InspirationType = NO_INSP;
/*%C  Flow max initialization */
	  CYC_Qmax = 0;
	break;
	}

return (InspirationType);
}