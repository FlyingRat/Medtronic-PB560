/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_ExhPlatComputings.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function computes pressure and flow values during exhalation      */
/*%C   plateau                                                                */
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
#include "DB_AlarmStatus.h"
#include "Ventilation_Datas.h"
#include "CMP_ExhPlatComputings.h"
#include "Ventilation_Compute_data.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void CMP_ExhPlatComputings(void)
{
/* Counter              */
	UBYTE i = 0;
/* Valve pressure measure array index                                         */
	static UWORD16 PvalveCounter = 0;
/* Flow leak measure array index                                              */
	static UWORD16 FleakCounter = 0;
/* Filter patient pressure recovery from base                                 */
	SWORD16 Filter_Patient_Pressure =
	                      (SWORD16)DB_ComputeRead(FILTER_PATIENT_PRESSURE_S16);
/* Filter patient pressure recovery from base                                 */
	SWORD16 Filter_Valve_Pressure =
	                      (SWORD16)DB_ComputeRead(MEASURE_VALVE_PRESSURE_S16);

/* Inspiratory flow recovery from base                                        */
	SWORD16 Filter_Qi =(SWORD16)DB_ComputeRead(FILTER_QI_S16);
/* Reading Te counters in data base */
	UWORD16 VenTeCount = TIM_ReadCounterValue(VEN_TE_COUNT);
/* Alarm disconnection state recovery from base                               */
   UWORD16 Alarm_Disconnection = DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);

/***********************************************************/
/*       Exhalated pressure measured continuously          */
/***********************************************************/

/*%C Exhalated pressure measure summation and iteration increase              */
	CMP_FullPepMeasured = CMP_FullPepMeasured + Filter_Patient_Pressure;
	CMP_FullPepCounter = CMP_FullPepCounter +1;

/***************************************************/
/*  Valve pressure compute during exhalation       */
/***************************************************/

/*%C Index limitation    */
	PvalveCounter %= cPVALVE_MEASURE_NUMBER;

/*%C Actual valve pressure memorization    */
	VEN_MeasuredValues.MeasurePvalve[PvalveCounter++] = Filter_Valve_Pressure;

/*%C Valve pressure average reset    */
	CMP_PvalveMeasured = 0;

/*%C Valve pressure average computing (5 values)      */
	for(i=0; i<cPVALVE_MEASURE_NUMBER; i++)
   {
		CMP_PvalveMeasured = CMP_PvalveMeasured + 
	VEN_MeasuredValues.MeasurePvalve[(PvalveCounter + i)%cPVALVE_MEASURE_NUMBER];
   }
	CMP_PvalveMeasured = CMP_PvalveMeasured / cPVALVE_MEASURE_NUMBER;

/*%C Negative values filtering     */
	if (CMP_PvalveMeasured < 0) CMP_PvalveMeasured = 0;



/**********************************************/
/*  Flow leak computing during exhalation     */
/**********************************************/

	if ((VEN_Disconnexion_Flag == TRUE) 
	 || (Alarm_Disconnection >= ALARM_TRUE))
	{
		VEN_FleakMeasured = 0;
	}
	else if (VenTeCount < 2500)
	{
		/*%C Index limitation     */
			FleakCounter %= cFLEAK_MEASURE_NUMBER;
		
		/*%C Actual patient pressure memorization     */
			VEN_MeasuredValues.MeasureFlowLeak[FleakCounter++] = Filter_Qi;
		
		/*%C Valve pressure average reset    */
			VEN_FleakMeasured = 0;
		
		/*%C Valve pressure average on 5 values    */
			for(i=0; i<cFLEAK_MEASURE_NUMBER; i++)
		   {
				VEN_FleakMeasured = VEN_FleakMeasured + 
			VEN_MeasuredValues.MeasureFlowLeak[(FleakCounter + i)%cFLEAK_MEASURE_NUMBER];
		   }
			VEN_FleakMeasured = VEN_FleakMeasured / cFLEAK_MEASURE_NUMBER;
		
		/*%C Negative values filtering    */
			if (VEN_FleakMeasured < 0)
			{
			   VEN_FleakMeasured = 0;
			}
		}
}

