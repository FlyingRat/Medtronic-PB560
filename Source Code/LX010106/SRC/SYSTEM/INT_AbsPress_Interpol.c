
/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_AbsPress_Interpol.c                                    	  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Absolute pressure values conversion                            */
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
#include "define.h"
#include "DB_Compute.h"
#include "DB_Measurement.h"
#include "INT_AbsPress_Interpol.h"
#include "Driver_Datas.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void INT_AbsPress_Interpol(void)
{
/*%CVariables for gliding window of filtering compute */
	static SWORD16 AbsPressSample[80] ;
    static UWORD16 AbsPressSampleNb = 0;
    SWORD32 AbsPressSampleCumul = 0;
	SWORD32 TempCompute = 0;
	SWORD16 Measure_Abs_press = 0;
	SWORD16 Filtered_Abs_Press = 0;
	UWORD16 i = 0;
	SWORD32 MeasAbsPressmmHg = 0;
/******************************************************************************/
/*                            Absolute Pressure                               */
/******************************************************************************/

/*%C Pressure is computed in xx.x H2O cm 	 */
/*%C The equation is:           */
/*%C      Press = ((ADC_Abs_Pressure_Value - Offset) * Sensitivity / 1000 */
/*%C Sensitivity is the value of one increment of the ADC : 0.61035 cm H2O */
/*%c So in the software, it is a constant witch is 61035 cm H2O*/
/*%C So the result is divided by 1000 to have a correct value in cm H2O . */


/* ------------------------------ NOTA -------------------------------------- */
/* how to compute the sensitivity for a pressure sensor 600 to +1100 cm H2O:  */
/*   - sensor sensitivity = 4000 mV / 500 cmH2O = 8 mV/cmH2O       */
/*   - ADC value for 1 cnH2O = (8mV * 1024) / 5000mV             */
/*     = 1.6384 CAN /mbar ==> 1 increment of ADC = 0.61035 cmH2O  */
/*----------------------------------------------------------------------------*/
    

/*%C Second, the Abs pressure is computed with the equation above */
	TempCompute = (SWORD32)AD_Digit.MesAbsPressure;
	TempCompute = TempCompute * SENSITIVITY_SENSOR_PRESSURE_ABS;
	Measure_Abs_press = (SWORD16)(TempCompute / 10000);
/*%C Theorical offset of 537 */
	Measure_Abs_press = Measure_Abs_press + 537;
/*%C The computed Abs pressure in hPa is stored into the Compute base  */
   DB_ComputeWrite(MEASURE_ABSOLUTE_PRESSURE_U16,
                   (UWORD16)Measure_Abs_press);

/*%C Abs pressure filtering on 80 values */
   AbsPressSample[AbsPressSampleNb++] = Measure_Abs_press;
   AbsPressSampleNb = (AbsPressSampleNb % 80);
   AbsPressSampleCumul = 0;
   for(i=0; i<80; i++)
   {
   	AbsPressSampleCumul = AbsPressSampleCumul + AbsPressSample[i];
	}
	Filtered_Abs_Press = (SWORD16)(AbsPressSampleCumul / 80); 
/*%C Translation hPa into mmHg */
	MeasAbsPressmmHg = ((SWORD32)Filtered_Abs_Press * 75) / 10;            
/*%c Due the AMDEC, we must put robustnes on output measure : */
/*%C   max 1100hpa = 825mmHg */
/*%C   min  600hpa = 450mmHg */
	if(MeasAbsPressmmHg >= ABS_PRES_MAX)
	{
		MeasAbsPressmmHg = ABS_PRES_MAX;
	}
	else if (MeasAbsPressmmHg <= ABS_PRES_MIN)
	{
		MeasAbsPressmmHg = ABS_PRES_MIN;
	} 

/*%C The computed Abs pressure is stored into the Compute base  */
   DB_ComputeWrite(MEAS_ABS_PRESS_MMHG_U16,
                   (UWORD16)MeasAbsPressmmHg);

/*%C The CAN value of Abs pressure is stored into Measurement data base */  
   DB_MeasurementWrite(ABS_PRESSURE_CAN_U16,
                       AD_Digit.MesAbsPressure);	
}
