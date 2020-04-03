/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_LeakComputing.c      		                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function computes leak value during inspiration     			  */
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
#include "DB_Current.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "Ventilation_Datas.h"
#include "CMP_LeakComputing.h"
#include "Ventilation_Compute_data.h"
#include "math.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void CMP_LeakComputing(void)
{							  

	SWORD16 Measure_Patient_Pressure = DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);
	UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);

	// Calcul de leak
	if (ValveDetected == FALSE)
	{
		// Calcul du débit de fuite
		VEN_LeakVtiCorrection =  ((sqrt(VEN_LeakFlowFactorAverage * (double)Measure_Patient_Pressure))/10);

	}
	else
	{
		VEN_LeakVteCorrection =  ((sqrt(VEN_LeakFlowFactorAverage * (double)Measure_Patient_Pressure))/10);

	}
}
