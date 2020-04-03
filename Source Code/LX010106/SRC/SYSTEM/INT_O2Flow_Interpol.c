/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_O2Flow_Interpol.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Inspiration Flow O2  values conversion                            */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_Measurement.h"
#include "Driver_Datas.h"
#include "System_Datas.h"
#include "INT_O2Flow_Interpol.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void INT_O2Flow_Interpol(void)
{
/*%C Variables for gliding window of filtering compute & computing */
	static UWORD16 O2FlowSample1Nb = 0;
	static SWORD16 O2FlowSample1[80]; 
	SWORD32 O2FlowSampleCumul1 = 0;
   UWORD16 i = 0;
	SWORD16 Flow_O2 = 0;
	SWORD16 Offset_O2_flow[FLOW_O2_CALIB_POINTS_NUMBER] = {0,0,0,0,0};
	SWORD16 MeasuredFlow = 0;
	SWORD16 FilteredFlow = 0;
	UWORD16 NegativeFlow = FALSE;
	SWORD32 CorrectedFlow = 0;
 	SWORD16 MeasureQO2Corrected = 0;
/* Barometric correction */
	UWORD16 AdjustBarometricCorrector 
   									= DB_ConfigRead(ADJUST_BAROMETRIC_CORRECTOR_U16);
/* Barometric pressure */
	UWORD16 MeasureAbsolutePressure
                              = DB_ComputeRead(MEASURE_ABSOLUTE_PRESSURE_U16);
/* Maintenance mode recovery from base */
	UWORD16 MaintenanceMode = DB_ControlRead(MAINTENANCE_MODE_U16);

/*%C Read the offsets of O2iratory flow, for the 8 segments of the curve*/
/*%C in the "config" data base*/
   Offset_O2_flow[SEGMENT0] = DB_ConfigRead(OFFSET_O2_FLOW_1);
	Offset_O2_flow[SEGMENT1] = DB_ConfigRead(OFFSET_O2_FLOW_2);
	Offset_O2_flow[SEGMENT2] = DB_ConfigRead(OFFSET_O2_FLOW_3);
	Offset_O2_flow[SEGMENT3] = DB_ConfigRead(OFFSET_O2_FLOW_4);
	Offset_O2_flow[SEGMENT4] = DB_ConfigRead(OFFSET_O2_FLOW_5);


/******************************************************************************/
/*                            O2 FLOW                                			*/
/******************************************************************************/


	Flow_O2 = AD_Digit.FlowO2;
/******************************************************************************/
/*%C                     negative flow detection                              */
/******************************************************************************/
/*%C First, if a negative flow is detected ( the ADC value of flow is lower */
/*%C than  OFFSET_O2_FLOW_1 (207)), then the absolute value of the digit*/
/*%C flow is taken, and a flag is set*/ 
/*%C The absolute value will allow to do a classic interpolation, witch is */
/*%C only possible on positive value */
/*%C When it is done, the flag will allow to invert the polarity of that value*/
	if (Flow_O2 < Offset_O2_flow[SEGMENT0])
	{
		Flow_O2 = Offset_O2_flow[SEGMENT0]
		           + (Offset_O2_flow[SEGMENT0]
		           - Flow_O2);
		NegativeFlow = TRUE;
	}

/******************************************************************************/
/*%C    Interpolation of a flow < 160 l/min according to apropriate segment   */
/******************************************************************************/
/*%C Digital Flow value is compared (<=) to the offset of each segment .*/
/*%C If the good segment is found, then the function of interpolation */
/*%C is launched. */
/*%C The equation used is : */
/*%C    Flow(ml/m) = 10 * FLOW_CALIB_POINTS[SEGMENT(n)]     */
/*%C              + (10 * (FLOW_CALIB_POINTS[SEGMENT(n)]  */
/*%C	               - FLOW_CALIB_POINTS[SEGMENT(n-1)])	*/
/*%C                /(OffsetO2Flow[SEGMENT(n)]			*/
/*%C	               - OffsetO2Flow[SEGMENT(n-1)]))     */
/*%C              * (Flow(Digit) - OffsetO2Flow[SEGMENT(n)])*/

/*%C If digital flow <= SEGMENT1 */ 
	if(Flow_O2 <= Offset_O2_flow[SEGMENT1])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_O2,
	                                               Offset_O2_flow[SEGMENT1],
	                                               Offset_O2_flow[SEGMENT0],
	                                               FLOW_O2_CALIB_POINTS[SEGMENT1],
	                                               FLOW_O2_CALIB_POINTS[SEGMENT0]);
	}
/*%C Else, if digital flow is > SEGMENT1 & <= SEGMENT2 */ 
	else if(Flow_O2 <= Offset_O2_flow[SEGMENT2])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_O2,
	                                               Offset_O2_flow[SEGMENT2],
	                                               Offset_O2_flow[SEGMENT1],
	                                               FLOW_O2_CALIB_POINTS[SEGMENT2],
	                                               FLOW_O2_CALIB_POINTS[SEGMENT1]);
	}
/*%C Else, if digital flow is > SEGMENT2 &<= SEGMENT3 */ 
	else if(Flow_O2 <= Offset_O2_flow[SEGMENT3])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_O2,
	                                               Offset_O2_flow[SEGMENT3],
	                                               Offset_O2_flow[SEGMENT2],
	                                               FLOW_O2_CALIB_POINTS[SEGMENT3],
	                                               FLOW_O2_CALIB_POINTS[SEGMENT2]);
   }
/*%C Else, if digital flow is > SEGMENT3 &<= SEGMENT4 */ 
	else if(Flow_O2 <= Offset_O2_flow[SEGMENT4])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_O2,
	                                               Offset_O2_flow[SEGMENT4],
	                                               Offset_O2_flow[SEGMENT3],
	                                               FLOW_O2_CALIB_POINTS[SEGMENT4],
	                                               FLOW_O2_CALIB_POINTS[SEGMENT3]);
	}

/*%C Else, if digital flow is > SEGMENT4 */ 
	else if (Flow_O2 > Offset_O2_flow[SEGMENT4]) 
	{
   MeasuredFlow =
   INT_Flow_Conversion_Equation(Flow_O2,
	                             Offset_O2_flow[FLOW_O2_CALIB_POINTS_NUMBER-1],
	                             Offset_O2_flow[FLOW_O2_CALIB_POINTS_NUMBER-2],
	                             FLOW_CALIB_POINTS[FLOW_O2_CALIB_POINTS_NUMBER-1],
	                             FLOW_CALIB_POINTS[FLOW_O2_CALIB_POINTS_NUMBER-2]);
   }
	
   
/******************************************************************************/
/*%C                     Negative flow treatment                              */
/******************************************************************************/
/*%C if the flow is negative, then the computed flow is inverted    */
	if (NegativeFlow == TRUE)
	{
		MeasuredFlow = - MeasuredFlow;
		NegativeFlow = FALSE;
	}

/******************************************************************************/
/*%C                     Flow measure up and low limit                        */
/******************************************************************************/
	  
/*%C Computed flow saturation between -200 and 2000 (- 20lpm, 200lpm) */
	MeasuredFlow = (SWORD16)saturation(MeasuredFlow,
									  -200,
									  2000);

/*%C  Measure QO2 correction (Corrected QO2 = P0/P * Measure QO2) */
/*%C Absolute pressure for correction must be in kPa */
   if ( (AdjustBarometricCorrector == TRUE)
	  && (MaintenanceMode == FALSE) )
   {
      CorrectedFlow = (cP0 * (SWORD32)MeasuredFlow)
      				 								/ (SWORD32)MeasureAbsolutePressure;
/*%C  Corrected QO2 writing in compute base */
		DB_ComputeWrite(MEASURE_QO2_S16, (UWORD16)CorrectedFlow);
   }
	else
	{
/*%C  Measure QO2 writing in compute base */
		DB_ComputeWrite(MEASURE_QO2_S16, MeasuredFlow);
	}

/*%C Storage of Digitized flow in Measurement base  */
	DB_MeasurementWrite(QO2_CAN_U16, AD_Digit.FlowO2);


/******************************************************************************/
/*%C                     compute of the 2 filtered values                     */
/******************************************************************************/
/*%C the first,filtered value is the average of the 80 last values */	 
   O2FlowSample1[O2FlowSample1Nb] = MeasuredFlow;
	O2FlowSample1Nb = O2FlowSample1Nb + 1;
   O2FlowSample1Nb = O2FlowSample1Nb %80;
   O2FlowSampleCumul1 = 0;
   for(i=0; i<80; i++)
   {
      O2FlowSampleCumul1 =O2FlowSampleCumul1 +  O2FlowSample1[i];
	}
   FilteredFlow = (SWORD16)(O2FlowSampleCumul1/80);                    
/*%C Storage in Compute base of filtering flow */
   DB_ComputeWrite(FILTER_QO2_S16, FilteredFlow);
	
}