
/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_TriggerEDetection.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                Detection of the exhalation trigger                			*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                     					*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : UWORD16  TriggerEDetected      								*/
/******************************************************************************/


											  
/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Compute.h"
#include "DB_Current.h"
#include "DB_Control.h"
#include "Ventilation_Datas.h"
#include "Ventilation_Cycles_Datas.h"
#include "CYC_TriggerEDetection.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 CYC_TriggerEDetection(void)
{
	SWORD16 MeasureQinspLeakCorrected = (SWORD16)DB_ComputeRead(MEASURE_QINSP_LEAKCORRECTED_S16);
	SWORD16 MeasureQinsp = (SWORD16)DB_ComputeRead(MEASURE_QINSP_S16); 
	UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16); 
	UWORD16 AdjustExhSens = DB_CurrentRead(ADJUST_EXH_SENS_U16);	
	UWORD16 RiseTime = DB_CurrentRead(RISE_TIME_U16);
	UWORD16 VenTiCount = TIM_ReadCounterValue(VEN_TI_COUNT);
	UWORD16 TriggerEDetected = 0;
	UWORD16 MutexInitQmax = 0;
	static UWORD16 PreviousControllerPhase = VEN_INSP_RISE;
	UWORD16 Current_Mode = DB_ControlRead(CURRENT_MODE_U16); 
	SWORD16 CurrentQinsp = 0;

	if (ValveDetected == FALSE)
	{
	 MeasureQinsp = MeasureQinspLeakCorrected;
	}
/*%C the mesure flow takes the sensor measure*/
	CurrentQinsp = MeasureQinsp;
/*%C Allow the trigger detection after 100ms :*/
/*%C if the inspiration counter is equal to or higher than 100ms, then*/
	if (VenTiCount >= RiseTime)
	{
/*%C  Memorizing the flow max value :*/
/*%C  if the filter Qi measured is higher than Qmax, then Qmax is set to */
/*%C  filter Qi value . */ 
		if (CurrentQinsp > CYC_Qmax)
		{
			CYC_Qmax = CurrentQinsp;
		}
/*%C  Expiratory trigger detection :*/	
/*%C  SWORD32 cast allows a signed multiplication 32 bits */
/*%C  if inspiratory phase is Inspiratory plateau */
/*%C  and Ti counter is over 200 ms */
/*%C  and Qinsp < (ADJUST_EXH_SENS_U16 * flowMax)/100 */
		else if ( (MeasureQinsp < 
								((SWORD32)CYC_Qmax * (SWORD32)(AdjustExhSens) / 100)) 
				 && ( (VEN_Controller_Phase == VEN_INSP_PLAT)
        		   || (VEN_Controller_Phase == VEN_INSP_RISE) ) )
		{
			TriggerEDetected = TRUE;
		}
		else
		{
			TriggerEDetected = FALSE;
		} 	
	}
	else
	{
		TriggerEDetected = FALSE;
	}
/*%C Previous controller phase refresh */
	PreviousControllerPhase = VEN_Controller_Phase;
	return(TriggerEDetected);
}