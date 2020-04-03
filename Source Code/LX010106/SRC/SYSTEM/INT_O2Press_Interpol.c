/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_O2Press_Interpol.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           O2 pressure values conversion                            */
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
#include "INT_O2Press_Interpol.h"
#include "Driver_Datas.h"
#include "System_Datas.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void INT_O2Press_Interpol(void)
{
/*%CVariables for gliding window of filtering compute */
	static SWORD16 O2PressSample[10] = {0,0,0,0,0,0,0,0,0,0};
   static UBYTE O2PressSampleNb = 0;
   SWORD32 O2PressSampleCumul = 0;
	SWORD32 TempCompute = 0;
	UWORD16 Offset_O2_press = 0;
	SWORD16 Measure_O2_press = 0;
	SWORD16 Filtered_O2_Press = 0;
	UWORD16 i = 0;

/******************************************************************************/
/*                            O2 Pressure                                  	*/
/******************************************************************************/

/*%C Pressure is computed in xx.x bar 	 */
/*%C The equation is:           */
/*%C      Press = ((ADC_O2_Pressure_Value - Offset) * Sensitivity / 1000 */
/*%C Sensitivity is the value of one increment of the ADC : 0.8800 bar */
/*%c So in the software, it is a constant witch is 8800 */
/*%C So the result is divided by 1000 to have a correct value in bar */


/* ------------------------------ NOTA -------------------------------------- */
/* how to compute the sensitivity for a pressure sensor 0 à +6897 mBar (+100 psi):  */
/*   - sensor sensitivity = 4000 mV / 6897 mBar = 0.580mV/mBar       */
/*   - ADC value for 1 cnH2O = (0.580mV * 1024) / 5000mV             */
/*     = 0.1187 CAN /mbar */
/*     ==> 1 increment of ADC = 8.424 mbar - Arrounded to 8.8 after set */
/*----------------------------------------------------------------------------*/
    
/*%C So, first, Read the offsets of O2 pressure in the "config" data base*/
	Offset_O2_press = DB_ConfigRead(OFFSET_PRESS_O2);

/*%C Second, the O2 pressure is computed with the equation above */
	TempCompute = (SWORD32)AD_Digit.O2Pressure - (SWORD32)Offset_O2_press;
	TempCompute = TempCompute * SENSITIVITY_SENSOR_PRESSURE_O2;
	Measure_O2_press = (SWORD16)(TempCompute/1000);

/*%C O2 pressure filtering on 10 values */
   O2PressSample[O2PressSampleNb++] = Measure_O2_press;
   O2PressSampleNb = (UBYTE)(O2PressSampleNb % 10);
   O2PressSampleCumul = 0;
   for(i=0; i<10; i++)
   {
   	O2PressSampleCumul = O2PressSampleCumul + O2PressSample[i];
	}
	Filtered_O2_Press = (SWORD16)(O2PressSampleCumul / 10);                


/*%C The computed O2 pressure is stored into the Compute base  */
   DB_ComputeWrite(MEASURE_PRESSURE_O2_S16,
                   Measure_O2_press);

/*%C The filtered O2 pressure is stored into the Compute base  */
   DB_ComputeWrite(FILTER_PRESSURE_O2_S16,
                   Filtered_O2_Press);

/*%C The CAN value of O2 pressure is stored into Measurement data base */  
   DB_MeasurementWrite(O2_PRESSURE_CAN_U16,
                       AD_Digit.O2Pressure);	
	
}