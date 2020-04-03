/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_ExhFlow_Interpol.c                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Exhalation  Flow  values conversion                            */
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
#include "DB_Compute.h"
#include "DB_Measurement.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "Driver_Datas.h"
#include "System_Datas.h"
#include "INT_ExhFlow_Interpol.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void INT_ExhFlow_Interpol(void)
{
/*%C Variables for gliding window of filtering compute & computing */
	static UWORD16 ExhFlowSampleNb = 0;
	static SWORD16 ExhFlowSample[80];
	SWORD32 ExhFlowSampleCumul;
   	UWORD16 i = 0;
	SWORD16 Flow_Exh = 0;
	SWORD16 Offset_exh_flow[FLOW_CALIB_POINTS_NUMBER] = {0,0,0,0,0,0,0,0};
	SWORD16 MeasuredFlow = 0;
	SWORD16 FilteredFlow = 0;
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

/*%C Read the offsets of expiratory flow, for the 8 segments of the curve*/
/*%C in the "config" data base*/
   Offset_exh_flow[SEGMENT0] = DB_ConfigRead(OFFSET_EXH_FLOW_1_U16);
	Offset_exh_flow[SEGMENT1] = DB_ConfigRead(OFFSET_EXH_FLOW_2_U16);
	Offset_exh_flow[SEGMENT2] = DB_ConfigRead(OFFSET_EXH_FLOW_3_U16);
	Offset_exh_flow[SEGMENT3] = DB_ConfigRead(OFFSET_EXH_FLOW_4_U16);
	Offset_exh_flow[SEGMENT4] = DB_ConfigRead(OFFSET_EXH_FLOW_5_U16);
	Offset_exh_flow[SEGMENT5] = DB_ConfigRead(OFFSET_EXH_FLOW_6_U16);
	Offset_exh_flow[SEGMENT6] = DB_ConfigRead(OFFSET_EXH_FLOW_7_U16);
	Offset_exh_flow[SEGMENT7] = DB_ConfigRead(OFFSET_EXH_FLOW_8_U16);

/******************************************************************************/
/*                            EXHALATION  FLOW                                */
/******************************************************************************/


	Flow_Exh = AD_Digit.FlowExh;
/*%C Negative values filtering */
	if (Flow_Exh <= Offset_exh_flow[SEGMENT0])
	{
	   MeasuredFlow = 0;
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
/*%C                /(OffsetExhFlow[SEGMENT(n)]			*/
/*%C	               - OffsetExhFlow[SEGMENT(n-1)]))     */
/*%C              * (Flow(Digit) - OffsetExhFlow[SEGMENT(n)])*/

/*%C If digital flow <= 224 */ 
	else if(Flow_Exh <= Offset_exh_flow[SEGMENT1])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Exh,
	                                               Offset_exh_flow[SEGMENT1],
	                                               Offset_exh_flow[SEGMENT0],
	                                               FLOW_CALIB_POINTS[SEGMENT1],
	                                               FLOW_CALIB_POINTS[SEGMENT0]);
	/*%C Correction to improve the accuracy between [0 -> 0.3l/min] and [0.3 -> 1.1l/min] */
	/*%C and [1.1 -> 3.2l/min] AND and [3.2 -> 5l/min] */
	  /*%C Segment : [0 -> 0.3l/min] */
	  if(MeasuredFlow <= 3)
	  {
		  /*%C y =  5*x */
		  Compute = (SWORD32)MeasuredFlow * 500;
		  Compute = Compute / 100;
	  }
	  /*%C Segment : [0.3 -> 1.1l/min] */
	  else if((MeasuredFlow > 3) && (MeasuredFlow <= 11))
	  {
		  /*%C y =  1.11*x + 12.3 */
		  Compute = (SWORD32)MeasuredFlow * 111;
		  Compute = Compute + 1230;
		  Compute = Compute / 100;
	  }
	  /*%C Segment : [1.1 -> 3.2l/min] */
	  else if((MeasuredFlow > 11) && (MeasuredFlow <= 32))
	  {
		  /*%C y =  0.56*x + 18.6 */
		  Compute = (SWORD32)MeasuredFlow * 56;
		  Compute = Compute + 1860;
		  Compute = Compute / 100;
	  }
	  /*%C Segment : [3.2 -> 5l/min] */
	  else
	  {
		  /*%C y =  0.79*x + 10.9 */
		  Compute = (SWORD32)MeasuredFlow * 79;
		  Compute = Compute + 1090;
		  Compute = Compute / 100;
	  }
	  /*%C Affectation */
	  MeasuredFlow = (SWORD16)Compute; 
	}
/*%C If digital flow <= 279 */ 
	else if(Flow_Exh <= Offset_exh_flow[SEGMENT2])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Exh,
	                                               Offset_exh_flow[SEGMENT2],
	                                               Offset_exh_flow[SEGMENT1],
	                                               FLOW_CALIB_POINTS[SEGMENT2],
	                                               FLOW_CALIB_POINTS[SEGMENT1]);
	}
/*%C If digital flow <= 475 */ 
	else if(Flow_Exh <= Offset_exh_flow[SEGMENT3])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Exh,
	                                               Offset_exh_flow[SEGMENT3],
	                                               Offset_exh_flow[SEGMENT2],
	                                               FLOW_CALIB_POINTS[SEGMENT3],
	                                               FLOW_CALIB_POINTS[SEGMENT2]);
   }
/*%C If digital flow <= 594 */ 
	else if(Flow_Exh <= Offset_exh_flow[SEGMENT4])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Exh,
	                                               Offset_exh_flow[SEGMENT4],
	                                               Offset_exh_flow[SEGMENT3],
	                                               FLOW_CALIB_POINTS[SEGMENT4],
	                                               FLOW_CALIB_POINTS[SEGMENT3]);
	}
/*%C If digital flow <= 748 */ 
	else if(Flow_Exh <= Offset_exh_flow[SEGMENT5])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Exh,
	                                               Offset_exh_flow[SEGMENT5],
	                                               Offset_exh_flow[SEGMENT4],
	                                               FLOW_CALIB_POINTS[SEGMENT5],
	                                               FLOW_CALIB_POINTS[SEGMENT4]);
	}
/*%C If digital flow <= 908 */ 
	else if(Flow_Exh <= Offset_exh_flow[SEGMENT6])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Exh,
	                                               Offset_exh_flow[SEGMENT6],
	                                               Offset_exh_flow[SEGMENT5],
	                                               FLOW_CALIB_POINTS[SEGMENT6],
	                                               FLOW_CALIB_POINTS[SEGMENT5]);
	}
/*%C If digital flow <= 995 */
	else if(Flow_Exh <= Offset_exh_flow[SEGMENT7])
	{
      MeasuredFlow =	INT_Flow_Conversion_Equation(Flow_Exh,
	                                               Offset_exh_flow[SEGMENT7],
	                                               Offset_exh_flow[SEGMENT6],
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
/*%C                /(OffsetExhFlow[FLOW_CALIB_POINTS_NUMBER-1]			*/
/*%C	               - OffsetExhFlow[FLOW_CALIB_POINTS_NUMBER-2]))     */
/*%C              * (Flow(Digit) - OffsetExhFlow[FLOW_CALIB_POINTS_NUMBER-1])*/

/*%C If digital flow > 995 */
	else if (Flow_Exh > Offset_exh_flow[SEGMENT7]) 
	{
   MeasuredFlow =
   INT_Flow_Conversion_Equation(Flow_Exh,
	                             Offset_exh_flow[FLOW_CALIB_POINTS_NUMBER-1],
	                             Offset_exh_flow[FLOW_CALIB_POINTS_NUMBER-2],
	                             FLOW_CALIB_POINTS[FLOW_CALIB_POINTS_NUMBER-1],
	                             FLOW_CALIB_POINTS[FLOW_CALIB_POINTS_NUMBER-2]);
   }
	
/******************************************************************************/
/*%C                     Flow measure saturation		                        */
/******************************************************************************/
/*%C The computed flow is saturated between 0 and 2000 (200 lpm) */
	MeasuredFlow = (SWORD16)saturation(MeasuredFlow,
									  0,
									  2000);
	if ( (AdjustBarometricCorrector == TRUE)
	  && (MaintenanceMode == FALSE)
	  && (CalibFlowExhReq <= NO_CALIB) )
   {
      CorrectedFlow = (CT_BODY_TEMP * (cP0 * (SWORD32)MeasuredFlow))
      				 								/ (SWORD32)MeasureAbsolutePressure;
      CorrectedFlow = CorrectedFlow / 1000;
		/*%C Saturation to 1 CAN*/
	   if (AD_Digit.FlowExh <= (Offset_exh_flow[SEGMENT0] + 1))
		{
			CorrectedFlow = 0;
		}

#ifdef CONFIG_VTE
		/*%C  Corrected Qinsp writing in compute base */
		DB_ComputeWrite(MEASURE_QEXH_S16, (UWORD16)CorrectedFlow);
#else
		DB_ComputeWrite(MEASURE_QEXH_S16, 0);
#endif
		/*%C  Affectation */
		MeasuredFlow = (SWORD16)CorrectedFlow;
   }
	
	else
	{
		/*%C Saturation to 1 CAN*/
	   if (AD_Digit.FlowExh <= (Offset_exh_flow[SEGMENT0] + 1))
		{
			MeasuredFlow = 0;
		}

#ifdef CONFIG_VTE
/*%C Storage in Compute base of calibrated flow without filter (deciliter )	*/
		DB_ComputeWrite(MEASURE_QEXH_S16, MeasuredFlow);
#else
		DB_ComputeWrite(MEASURE_QEXH_S16, 0);
#endif
	}


#ifdef CONFIG_VTE
/*%C Storage of Digitized flow in Measurement base  */
	DB_MeasurementWrite(QE_CAN_U16, AD_Digit.FlowExh);
#else
	DB_MeasurementWrite(QE_CAN_U16,0);
#endif
/******************************************************************************/
/*%C                     Filtered value computing			                     */
/******************************************************************************/
/*%C The filtered value is the average of the 80 last values */	 
   
   ExhFlowSample[ExhFlowSampleNb] = MeasuredFlow;
   ExhFlowSampleNb = ExhFlowSampleNb + 1;
   ExhFlowSampleNb = ExhFlowSampleNb %80;
   ExhFlowSampleCumul = 0;
   for(i=0; i<80; i++)
   {
      ExhFlowSampleCumul =ExhFlowSampleCumul +  ExhFlowSample[i];
	}
   FilteredFlow = (SWORD16)(ExhFlowSampleCumul/80);
/*%C Saturation 0.2 l/min */
   if (FilteredFlow <= 2)
	{
		FilteredFlow = 0;
	}
#ifdef CONFIG_VTE
/*%C The filtered flow is stored in Compute base */
   DB_ComputeWrite(FILTER_QE_S16, FilteredFlow);
#else
	DB_ComputeWrite(FILTER_QE_S16,0);
#endif
}