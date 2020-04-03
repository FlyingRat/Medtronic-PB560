/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_CalculAutoAdaptInsp.c                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C This function computes a correction value for the control command        */
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
#include "DB_Compute.h"
#include "DB_Current.h"
#include "DB_Control.h"
#include "enum.h"
#include "Ventilation_Compute_Data.h"
#include "Ventilation_Datas.h"
#include "CMP_CalculAutoAdaptInsp.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void CMP_CalculAutoAdaptInsp(void)
{
/* Pi set point recovery from base                */
   UWORD16 Pi_Set_Point = DB_CurrentRead(PI_SET_POINT_U16);
/* Pi set point memorization    */
	static UWORD16 Pi_Set_Point_Memo=0;
/* Inspiratory max pressure    */
   UWORD16 Computed_Pip = DB_ComputeRead(COMPUTED_PIP_U16);
   UWORD16 HighPressureDetected = DB_ControlRead(HIGH_PRESSURE_DETECTED_U16);

/*****************************/
/*%C Pressure adaptation     */
/*****************************/
	if (VEN_ControllerType == CONTROL_PRESSURE)
   {
/*%C Inpiratory rise pressure initialization if the pressure is too low       */
/*%C or if the inspiratory pressure set point has changed                     */
		if ( (Computed_Pip < cPRESSURE_MIN)
		  || (Pi_Set_Point != Pi_Set_Point_Memo) )
		{
			VEN_PerCentRisePI = cVEN_PER_CENT_RISE_PRESS_DEF;
		}
/*%C  If the max pressure is under 105% of inspiratory pressure set point     */
/*%C  the inspiratory rise pressure percentage is increased                   */
		else if ( ((SWORD32)CMP_PMaxAutoAdapt <=
		                (SWORD32)(Pi_Set_Point * 105UL / 100))
			    && (HighPressureDetected == FALSE) )
		{
			VEN_PerCentRisePI = VEN_PerCentRisePI + cVEN_PER_CENT_RISE_PRESS_STEP;
		}
/*%C  If the max pressure is higher than 105% of inspiratory pressure set     */
/*%C  point the inspiratory rise pressure percentage is decreased             */
		else if ( ((SWORD32)CMP_PMaxAutoAdapt 
		                                 > (SWORD32)(Pi_Set_Point * 105UL / 100))
			    || (HighPressureDetected >= TRUE) )
		{
			VEN_PerCentRisePI = VEN_PerCentRisePI - cVEN_PER_CENT_RISE_PRESS_STEP;
		}
		
/*%C  Inspiratory rise pressure percentage saturation [-60, 100]              */
		VEN_PerCentRisePI = saturation(VEN_PerCentRisePI,
		                               cVEN_PER_CENT_RISE_PRESS_MIN,
		                               cVEN_PER_CENT_RISE_PRESS_MAX);
	
/*%C  Max pressure adaptation initialization                          	      */
		CMP_PMaxAutoAdapt = 0;
/*%C  Pi set point memorization                                      	      */
		Pi_Set_Point_Memo = Pi_Set_Point;
   }

/*****************************/
/*%C Flow adaptation         */
/*****************************/
	else
   {
/*%C  Flow adaptation if the Qinsp max is lower than Qinsp set point  */
		if ((SWORD32)CMP_FlowMaxMeasuredInsp < (SWORD32)VEN_Qi_Set_Point)
		{
			VEN_PerCentRiseQI = VEN_PerCentRiseQI + cVEN_PER_CENT_RISE_FLOW_STEP;
		}
/*%C  Flow adaptation if the Qinsp max is higher than 105% of Qinsp set point */
		else if ((SWORD32)CMP_FlowMaxMeasuredInsp >((SWORD32)VEN_Qi_Set_Point *
		                                           105UL / 100))
		{
			VEN_PerCentRiseQI = VEN_PerCentRiseQI - cVEN_PER_CENT_RISE_FLOW_STEP;
		}
		
/*%C  Inspiratory rise flow percentage saturation [-60, 100]                  */
		VEN_PerCentRiseQI = saturation(VEN_PerCentRiseQI,
		                               cVEN_PER_CENT_RISE_FLOW_MIN,
		                               cVEN_PER_CENT_RISE_FLOW_MAX);
	
/*%C  Max flow adaptation initialization                       	            */
		CMP_FlowMaxMeasuredInsp = 0;
   }
}
