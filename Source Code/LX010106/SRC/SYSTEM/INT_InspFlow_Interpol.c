/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_InspFlow_Interpol.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Inspiration Flow  values conversion                            */
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
#include "INT_InspFlow_Interpol.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void INT_InspFlow_Interpol(void)
{
/*%C Variables for gliding window of filtering compute & computing */
	static UWORD16 InspFlowSample1Nb = 0;
	static SWORD16 InspFlowSample1[80]; 
	static UWORD16 InspFlowSample2Nb = 0;
	static SWORD16 InspFlowSample2[10]; 
	SWORD32 InspFlowSampleCumul1 = 0;
	SWORD32 InspFlowSampleCumul2 = 0;
   UWORD16 i = 0;
	SWORD16 Flow_Insp = 0;
	SWORD16 Offset_insp_flow[FLOW_CALIB_POINTS_NUMBER] = {0,0,0,0,0,0,0,0};
	SWORD16 MeasuredFlow = 0;
	SWORD16 FilteredFlow = 0;
	UWORD16 NegativeFlow = FALSE;
	SWORD32 CorrectedFlow = 0;
    SWORD32 Compute = 0;
/* Barometric correction */
	UWORD16 AdjustBarometricCorrector 
   									= DB_ConfigRead(ADJUST_BAROMETRIC_CORRECTOR_U16);
/* Barometric pressure */
	UWORD16 MeasureAbsolutePressure
                              = DB_ComputeRead(MEASURE_ABSOLUTE_PRESSURE_U16);
/* Exhalation Flow Calibration Request? */  
   e_CalibrationCommand CalibFlowExhReq
   								 = DB_ControlRead(CALIB_FLOW_EXH_REQ_U16);
/* Maintenance mode recovery from base */
	UWORD16 MaintenanceMode = DB_ControlRead(MAINTENANCE_MODE_U16);

/*%C Read the offsets of inspiratory flow, for the 8 segments of the curve*/
/*%C in the "config" data base*/
   Offset_insp_flow[SEGMENT0] = DB_ConfigRead(OFFSET_INSP_FLOW_1_U16);
	Offset_insp_flow[SEGMENT1] = DB_ConfigRead(OFFSET_INSP_FLOW_2_U16);
	Offset_insp_flow[SEGMENT2] = DB_ConfigRead(OFFSET_INSP_FLOW_3_U16);
	Offset_insp_flow[SEGMENT3] = DB_ConfigRead(OFFSET_INSP_FLOW_4_U16);
	Offset_insp_flow[SEGMENT4] = DB_ConfigRead(OFFSET_INSP_FLOW_5_U16);
	Offset_insp_flow[SEGMENT5] = DB_ConfigRead(OFFSET_INSP_FLOW_6_U16);
	Offset_insp_flow[SEGMENT6] = DB_ConfigRead(OFFSET_INSP_FLOW_7_U16);
	Offset_insp_flow[SEGMENT7] = DB_ConfigRead(OFFSET_INSP_FLOW_8_U16);


/******************************************************************************/
/*                            INSPIRATORY FLOW                                */
/******************************************************************************/


	Flow_Insp = AD_Digit.FlowInsp;
/******************************************************************************/
/*%C                     negative flow detection                              */
/******************************************************************************/
/*%C First, if a negative flow is detected ( the ADC value of flow is lower */
/*%C than  OFFSET_INSP_FLOW_1_U16 (207)), then the absolute value of the digit*/
/*%C flow is taken, and a flag is set*/ 
/*%C The absolute value will allow to do a classic interpolation, witch is */
/*%C only possible on positive value */
/*%C When it is done, the flag will allow to invert the polarity of that value*/
	if (Flow_Insp < Offset_insp_flow[SEGMENT0])
	{
		Flow_Insp = Offset_insp_flow[SEGMENT0]
		           + (Offset_insp_flow[SEGMENT0]
		           - Flow_Insp);
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
/*%C                /(OffsetInspFlow[SEGMENT(n)]			*/
/*%C	               - OffsetInspFlow[SEGMENT(n-1)]))     */
/*%C              * (Flow(Digit) - OffsetInspFlow[SEGMENT(n)])*/

/*%C If digital flow <= 224 */ 
	if(Flow_Insp <= Offset_insp_flow[SEGMENT1])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Insp,
	                                               Offset_insp_flow[SEGMENT1],
	                                               Offset_insp_flow[SEGMENT0],
	                                               FLOW_CALIB_POINTS[SEGMENT1],
	                                               FLOW_CALIB_POINTS[SEGMENT0]);
	/*%C Correction to improve the accuracy between [0 -> 1.1l/min] and [1.1 -> 1.9l/min] */
	/*%C and [1.9 -> 5l/min] */
	  /*%C Segment : [0 -> 1.1l/min] */
	  if(MeasuredFlow <= 11)
	  {
		  /*%C y =  1.58*x */
		  Compute = (SWORD32)MeasuredFlow * 158;
		  Compute = Compute / 100;
	  }
	  /*%C Segment : [1.1 -> 1.9l/min] */
	  else if((MeasuredFlow > 11) && (MeasuredFlow <= 19))
	  {
		  /*%C y =  1.04*x + 6 */
		  Compute = (SWORD32)MeasuredFlow * 104;
		  Compute = Compute + 600;
		  Compute = Compute / 100;
	  }
	  /*%C Segment : [1.9 -> 5l/min] */
	  else
	  {
		  /*%C y =  0.78*x + 10.8 */
		  Compute = (SWORD32)MeasuredFlow * 78;
		  Compute = Compute + 1080;
		  Compute = Compute / 100;
	  }
	  /*%C Affectation */
	  MeasuredFlow = (SWORD16)Compute; 
	}
/*%C Else, if digital flow is > 224 & <= 251 */ 
	else if(Flow_Insp <= Offset_insp_flow[SEGMENT2])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Insp,
	                                               Offset_insp_flow[SEGMENT2],
	                                               Offset_insp_flow[SEGMENT1],
	                                               FLOW_CALIB_POINTS[SEGMENT2],
	                                               FLOW_CALIB_POINTS[SEGMENT1]);
	}
/*%C Else, if digital flow is > 251 &<= 446 */ 
	else if(Flow_Insp <= Offset_insp_flow[SEGMENT3])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Insp,
	                                               Offset_insp_flow[SEGMENT3],
	                                               Offset_insp_flow[SEGMENT2],
	                                               FLOW_CALIB_POINTS[SEGMENT3],
	                                               FLOW_CALIB_POINTS[SEGMENT2]);
   }
/*%C Else, if digital flow is > 446 &<= 582 */ 
	else if(Flow_Insp <= Offset_insp_flow[SEGMENT4])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Insp,
	                                               Offset_insp_flow[SEGMENT4],
	                                               Offset_insp_flow[SEGMENT3],
	                                               FLOW_CALIB_POINTS[SEGMENT4],
	                                               FLOW_CALIB_POINTS[SEGMENT3]);
	}
/*%C Else, if digital flow is > 582 &<= 713 */ 
	else if(Flow_Insp <= Offset_insp_flow[SEGMENT5])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Insp,
	                                               Offset_insp_flow[SEGMENT5],
	                                               Offset_insp_flow[SEGMENT4],
	                                               FLOW_CALIB_POINTS[SEGMENT5],
	                                               FLOW_CALIB_POINTS[SEGMENT4]);
	}
/*%C Else, if digital flow is > 713 &<= 889 */ 
	else if(Flow_Insp <= Offset_insp_flow[SEGMENT6])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Insp,
	                                               Offset_insp_flow[SEGMENT6],
	                                               Offset_insp_flow[SEGMENT5],
	                                               FLOW_CALIB_POINTS[SEGMENT6],
	                                               FLOW_CALIB_POINTS[SEGMENT5]);
	}
/*%C Else, if digital flow is > 889 &<= 947 */
	else if(Flow_Insp <= Offset_insp_flow[SEGMENT7])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Insp,
	                                               Offset_insp_flow[SEGMENT7],
	                                               Offset_insp_flow[SEGMENT6],
	                                               FLOW_CALIB_POINTS[SEGMENT7],
	                                               FLOW_CALIB_POINTS[SEGMENT6]);
	}

/******************************************************************************/
/*%C    Extrapolation of a flow >= 160 l/min according to last segment        */
/******************************************************************************/
/*%C if digital flow value is upper than 947, then a function of extrapolation*/
/*%C is launched, and the corresponding equation become : */
/*%C    Flow(ml/m) = 10 * FLOW_CALIB_POINTS[FLOW_CALIB_POINTS_NUMBER-1]     */
/*%C              + (1000 * (FLOW_CALIB_POINTS[FLOW_CALIB_POINTS_NUMBER-1]  */
/*%C	               - FLOW_CALIB_POINTS[FLOW_CALIB_POINTS_NUMBER-2])	*/
/*%C                /(OffsetInspFlow[FLOW_CALIB_POINTS_NUMBER-1]			*/
/*%C	               - OffsetInspFlow[FLOW_CALIB_POINTS_NUMBER-2]))     */
/*%C              * (Flow(Digit) - OffsetInspFlow[FLOW_CALIB_POINTS_NUMBER-1])*/

/*%C Else, if digital flow > 947 */
	else if (Flow_Insp > Offset_insp_flow[SEGMENT7]) 
	{
   MeasuredFlow =
   INT_Flow_Conversion_Equation(Flow_Insp,
	                             Offset_insp_flow[FLOW_CALIB_POINTS_NUMBER-1],
	                             Offset_insp_flow[FLOW_CALIB_POINTS_NUMBER-2],
	                             FLOW_CALIB_POINTS[FLOW_CALIB_POINTS_NUMBER-1],
	                             FLOW_CALIB_POINTS[FLOW_CALIB_POINTS_NUMBER-2]);
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

/*%C  Measure Qinsp correction (Corrected Qinsp = P0/P * Measure Qinsp) */
/*%C Absolute pressure for correction must be in kPa */
   if ( (AdjustBarometricCorrector == TRUE)
	  && (MaintenanceMode == FALSE)
	  && (CalibFlowExhReq <= NO_CALIB) )
   {
      CorrectedFlow = (CT_BODY_TEMP *(cP0 * (SWORD32)MeasuredFlow))
      					/ (SWORD32)MeasureAbsolutePressure;
      CorrectedFlow = CorrectedFlow / 1000;
/*%C Saturation +/- 1 CAN */
	   if ((AD_Digit.FlowInsp <= (Offset_insp_flow[SEGMENT0] + 1)) && 
			 (AD_Digit.FlowInsp >= (Offset_insp_flow[SEGMENT0] - 1)))
		{
			CorrectedFlow = 0;
		}
/*%C  Corrected Qinsp writing in compute base */
		DB_ComputeWrite(MEASURE_QINSP_S16, (UWORD16)CorrectedFlow);
/*%C  Affectation */
		MeasuredFlow = (SWORD16)CorrectedFlow;
	    }
	else
	{
/*%C Saturation +/- 1 CAN */
	   if ((AD_Digit.FlowInsp <= (Offset_insp_flow[SEGMENT0] + 1)) && 
			 (AD_Digit.FlowInsp >= (Offset_insp_flow[SEGMENT0] - 1)))
		{
			MeasuredFlow = 0;
		}
/*%C  Measure Qinsp writing in compute base */
		DB_ComputeWrite(MEASURE_QINSP_S16, MeasuredFlow);
	}
/*%C Storage of Digitized flow in Measurement base  */
	DB_MeasurementWrite(QI_CAN_U16, AD_Digit.FlowInsp);


/******************************************************************************/
/*%C                     compute of the 2 filtered values                     */
/******************************************************************************/
/*%C the first,filtered value is the average of the 80 last values */	 
   InspFlowSample1[InspFlowSample1Nb] = MeasuredFlow;
	InspFlowSample1Nb = InspFlowSample1Nb + 1;
   InspFlowSample1Nb = InspFlowSample1Nb %80;
   InspFlowSampleCumul1 = 0;
   for(i=0; i<80; i++)
   {
      InspFlowSampleCumul1 =InspFlowSampleCumul1 +  InspFlowSample1[i];
	}
   FilteredFlow = (SWORD16)(InspFlowSampleCumul1/80);                    
/*%C Saturation +/- 0.2 l/min */
   if (FilteredFlow >= -2 && FilteredFlow <= 2)
	{
		FilteredFlow = 0;
	}
/*%C Storage in Compute base of filtering flow */
   DB_ComputeWrite(FILTER_QI_S16, FilteredFlow);
	
/*%C the second, filtered value is the average of the 10 last values */
   InspFlowSample2[InspFlowSample2Nb] = MeasuredFlow;
	InspFlowSample2Nb = InspFlowSample2Nb + 1;
   InspFlowSample2Nb = InspFlowSample2Nb %10;
   InspFlowSampleCumul2 = 0;
   for(i=0; i<10; i++)
   {
      InspFlowSampleCumul2 = InspFlowSampleCumul2 + InspFlowSample2[i];
	}
	FilteredFlow = (SWORD16)(InspFlowSampleCumul2/10);                    
/*%C Saturation +/- 0.2 l/min */
   if (FilteredFlow >= -2 && FilteredFlow <= 2)
	{
		FilteredFlow = 0;
	}
/*%C Storage in Compute base of calibrated flow filter	*/
	DB_ComputeWrite(FILTER_QI_LOW_S16, FilteredFlow);
}