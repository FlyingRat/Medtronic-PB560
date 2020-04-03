/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_ProxiPress_Interpol.c                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Proximal pressure values conversion                            */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES                               */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Compute.h"
#include "DB_Measurement.h"
#include "DB_Config.h"
#include "INT_ProxiPress_Interpol.h"
#include "Driver_Datas.h"
#include "System_Datas.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void INT_ProxiPress_Interpol(void)
{
/*%C Variables for gliding window of filtering compute */
	static UWORD16 PatientPressProxSampleNb = 0;
	static SWORD16 PatientPressProxSample[4] = {0,0,0,0};
	SWORD32 PatientPressProxSampleCumul = 0 ;
	UWORD16 i = 0;
	SWORD32 TempCompute = 0;
	UWORD16 Offset_Patient_Prox_Press_1 = 0; 
	UWORD16 Offset_Patient_Prox_Press_2 = 0;
	SWORD16 Measure_patient_pressure_proxi = 0;
	SWORD16 Filter_patient_pressure_proxi = 0;


/******************************************************************************/
/*                          Patient Proximal Pressure                         */
/******************************************************************************/

/*%C Pressure is computed in xx.x H2O cm 	 */
/*%C The equation represent a Straight line with offset to 0 & a point */
/*%C to 40 cm H2O.						  */
/*%C A multiplication by 10 is done to obtain a pressure computed */
/*%C in xx.x H2O cm.*/
/*%C The equation is:           */
/*%C      Press = ((ADC_Proxi_Pressure_Value - Offset1) * 40 * 10) */
/*%C               / (Offset2 - Offset1) */	

/*%C So, first, Read the offsets of patient pressure in the "config" data base*/
   Offset_Patient_Prox_Press_1 = DB_ConfigRead(OFFSET_PATIENT_PROX_PRESS_1_U16);
   Offset_Patient_Prox_Press_2 = DB_ConfigRead(OFFSET_PATIENT_PROX_PRESS_2_U16);

/*%C Second, the patient pressure is computed with the equation above */
   TempCompute = (SWORD32)AD_Digit.ProxPressure -
                                       (SWORD32)Offset_Patient_Prox_Press_1;
   TempCompute = TempCompute *(PATIENT_PRESSURE_CALIB_POINTS[1]*10);
   TempCompute = TempCompute 
 /((SWORD32)Offset_Patient_Prox_Press_2 - (SWORD32)Offset_Patient_Prox_Press_1);
   Measure_patient_pressure_proxi = (SWORD16)TempCompute;

/*%C Third, a filter measure is computed:  */
/*%C it's the average between the 4 last measurements	 */
   PatientPressProxSample[PatientPressProxSampleNb] 
      = Measure_patient_pressure_proxi;
   PatientPressProxSampleNb = PatientPressProxSampleNb + 1;
   PatientPressProxSampleNb = PatientPressProxSampleNb %4;
   for(i=0; i<4; i++)
   {
      PatientPressProxSampleCumul = PatientPressProxSampleCumul 
                                  + PatientPressProxSample[i];
   }
   Filter_patient_pressure_proxi = (SWORD16)(PatientPressProxSampleCumul/4); 

/*%C The computed proximal pressure is stored into the Compute base  */
   DB_ComputeWrite(MEASURE_PATIENT_PRESSURE_PROXI_S16,
                   Measure_patient_pressure_proxi);
/*%C The filtered proximal pressure is stored into the Compute base  */
   DB_ComputeWrite(FILTER_PATIENT_PRESSURE_PROXI_S16,
                   Filter_patient_pressure_proxi);
/*%C The CAN value of proximal pressure is stored into Measurement data base */
   DB_MeasurementWrite(PATIENT_PRESSURE_PROXI_CAN_U16,
                       AD_Digit.ProxPressure);

}