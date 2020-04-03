/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_CurveFlowCalcul.c    	                           		  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Flow computing for waveform display	                           */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES	                             */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "SYS_CurveFlowCalcul.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SYS_CurveFlowCalcul(void)
{
 	SWORD16 MeasureQ;
	SWORD16 MeasureQExh = (SWORD16)DB_ComputeRead(MEASURE_QEXH_S16);
 	SWORD16 MeasureQInsp = (SWORD16)DB_ComputeRead(MEASURE_QINSP_S16);
	SWORD16 MeasureQinspLeak = (SWORD16)DB_ComputeRead(MEASURE_QINSP_LEAKCORRECTED_S16); 
	UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16); 
	UWORD16 VentilState = DB_ControlRead(VENTIL_STATE_U16);
 	UWORD16 Qinsp = 0;
	UWORD16 VenTiCount = TIM_ReadCounterValue(VEN_TI_COUNT);
	SWORD16 Measure_Patient_Pressure = 
                          (SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);
	SWORD16 Computed_Pep = 
                          (SWORD16)DB_ComputeRead(COMPUTED_PEEP_U16);

/*%C Measure Qinsp choice function of valve detection */
	if (ValveDetected == TRUE)
	{
		Qinsp = MeasureQInsp;
	}
	else
	{
		Qinsp = MeasureQinspLeak;
	}

/*%C During inspiration, Measure Qinsp is displayed  */
	if (VentilState != VEN_EXHALATION)
	{
		MeasureQ = Qinsp;
	}
/*%C During exhalation, (Measure Qexh - Measure Qinsp) is displayed  */
	else
	{
		MeasureQ = Qinsp - MeasureQExh;
		if (MeasureQ > 0)
		{
			MeasureQ = 0;	
		} 
	}

/*%C Inspiratory flow filtering - QInsp = 0                            */
/*%C If Patient pressure < Pep mesured and Ti_mesured < 200ms to avoid */
/*%C leakage error in the Vti compute */
	if ((Measure_Patient_Pressure < (Computed_Pep + 20)) && (VenTiCount < 200))
	{   
	   MeasureQ = 0;
	}

/*%C Flow Curve stored in the compute base  */
  	DB_ComputeWrite(CURVE_CORRECTED_FLOW_S16,MeasureQ);
}
