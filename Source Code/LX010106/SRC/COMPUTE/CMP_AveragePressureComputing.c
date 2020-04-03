/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_AveragePressureComputing.c                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function computes the average pressure on one cycle			      */
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
#include "DB_Compute.h"
#include "Ventilation_datas.h"
#include "Ventilation_Compute_data.h"
#include "CMP_AveragePressureComputing.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void CMP_AveragePressureComputing(void)
{
	static UWORD16 Counter = 0;
	static UWORD32 CumulPressure = 0;
	static UWORD32 AveragePressure = 0;

/* Filter patient pressure recovery from base */
   SWORD16 Filter_Patient_Pressure = 
                          (SWORD16)DB_ComputeRead(FILTER_PATIENT_PRESSURE_S16);

/*%C  The average pressure is made with positive values                       */
		if (Filter_Patient_Pressure > 0)
		{
/*%C  	Pressure Cumul computing                                             */
			CumulPressure = CumulPressure + Filter_Patient_Pressure;
		}
/*%C  Counter increase				                                             */
		Counter = Counter + 1;


/*%C The average computing is made during the exhalation/inspiration 			*/
/*%C transition:																				   */
/*%C The average is computed and stored in compute base, the cumul and the 	*/
/*%C counter are set to zero																   */
	if ( (VEN_Controller_Phase == VEN_INSP_RISE)
	  && (VEN_Controller_Phase != CMP_PreviousControllerPhase) )
   {
		AveragePressure =  CumulPressure / Counter;
		DB_ComputeWrite(AVERAGE_PRESSURE_U16,
							 (UWORD16)AveragePressure);
		Counter = 0;
		CumulPressure = 0;
		AveragePressure = 0;							 		
	}
}
