/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_Flow_Conversion_Equation.c                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Equation of flow extrapolation when flow > 160l/m              */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : DigitFlow,							   	        	         */
/*%I                   OffsetFlow1,											            */
/*%I                   OffsetFlow2,											            */
/*%I                   CalibFlowPoint1,										         */
/*%I                   CalibFlowPoint2                                        */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Flow                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "INT_Flow_Conversion_Equation.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


SWORD16 INT_Flow_Conversion_Equation(SWORD16 DigitFlow,
                                     SWORD16 OffsetFlow1,
                                     SWORD16 OffsetFlow2,
                                     UWORD16 CalibFlowPoint1,
                                     UWORD16 CalibFlowPoint2)
{
   SWORD32 DeltaPointOffsets = 0;
	SWORD32 DeltaMesOffset = 0;
	SWORD32 DeltaPointCal = 0;
	SWORD16 Flow = 0;
	SWORD32 FlowTmp = 0;
	SWORD32 DeltaPointCalMin = -100; 
	SWORD32 DeltaPointCalMax =  100; 

/*%C The equation below is used :                                     */
/*%C    Flow(ml/m) = 10 * CalibFlowPoint2                             */
/*%C              + ( ( ((CalibFlowPoint1 - CalibFlowPoint2)*1000000)   */
/*%C                  * (DigitFlow - OffsetFlow2) )		             */
/*%C	              / (OffsetFlow1 - OffsetFlow2) )                   */
/*%C                / 100000                                            */

/*%C Compute of flow in the segment */ 
/*%C Computing in ADC points of the delta between the ends of the segment */
   DeltaPointOffsets = OffsetFlow1
                     - OffsetFlow2;
/*%C Computing of delta between the measure and the lower top of segment */
   DeltaMesOffset = DigitFlow - OffsetFlow2;
/*%C Computing of delta of flow between the end of positive segment and */
/*%C the measure	 */
   DeltaPointCal = (SWORD32)CalibFlowPoint1 
                  -(SWORD32)CalibFlowPoint2; 

/*%C Limitation of the DeltaPointCal :                                    */
/*%C The maximum absolute gap between 2 points of FLOW_CALIB_POINTS is 45 */
/*%C so the limitation is fixed to 100                                    */
   DeltaPointCal = saturation(DeltaPointCal,
 	                           DeltaPointCalMin,
  	                           DeltaPointCalMax);

   FlowTmp = (DeltaPointCal * 1000000L) / DeltaPointOffsets; 
   FlowTmp = (FlowTmp * DeltaMesOffset) / 100000L; 
                           
   Flow = (SWORD16)(10L * (SWORD32)CalibFlowPoint2 + FlowTmp);
	                 
   return(Flow);
}