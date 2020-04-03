/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_Insp_Controller_Phase.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          Generation of the type of control Phase and the type of */ 
/*            control.                                     */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE       */
/******************************************************************************/



/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "Ventilation_Datas.h"
#include "Ventilation_Cycles_Datas.h"
#include "CYC_Insp_Controller_Phase.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void CYC_Insp_Controller_Phase(void)
{
UWORD16 VenTiCount = TIM_ReadCounterValue(VEN_TI_COUNT);
UWORD16 RiseTime = DB_CurrentRead(RISE_TIME_U16);
SWORD16 MeasurePatientPressure = DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);
UWORD16 AdjustRamp = DB_CurrentRead(ADJUST_RAMP_U16);
SWORD16 MeasureQinsp = 0;
UWORD16 AdjustTiControl = 0;
UWORD16 PiSetPoint = 0;
UWORD16 RiseTimeLimit = 0;

/*%C The management of the different phases of ventilation in inspiration */
/*%C depends on the kind of control : PRESSURE or FLOW */

/******************************************************************************/
/*%C                         IN PRESSURE MODE:					       			 */
/******************************************************************************/
if (VEN_ControllerType == CONTROL_PRESSURE)
{
/*%C Read the Pi set point value into data base. */
	PiSetPoint = DB_CurrentRead(PI_SET_POINT_U16);

/*%C The software must go into inspiration rise state during a step of */
/*%C scheduler.*/
/*%C So it is necessary to test the previous state :"VEN_EXH_FALL" or */
/*%C "VEN_EXH_PLAT"*/

   if ( (CYC_PreviousControllerPhase == VEN_EXH_FALL)
     || (CYC_PreviousControllerPhase == VEN_EXH_PLAT) )
   {
      VEN_Controller_Phase = VEN_INSP_RISE;
   }


/*%C While the value of the Ti Counter (counter of the inspiration phase) is*/
/*%C lower than the sum of the Rise Time and 200ms, and the patient pressure*/
/*%C is lower than 99% of Pi set point, and the actual state is different*/
/*%C from "VEN_INSP_PLAT", then the new phase of controller*/
/*%C is "VEN_INSP_RISE". */

   else if ( (VenTiCount < (RiseTime + cVEN_SLOPE_LIMIT))
          && (MeasurePatientPressure < (SWORD16)((SWORD32)PiSetPoint
                                                 * cDELTA_PI / 100)) 
          && (VEN_Controller_Phase != VEN_INSP_PLAT) )
   {
      VEN_Controller_Phase = VEN_INSP_RISE;
   }

/*%C In the other case, the new phase of controller is "VEN_INSP_PLAT".*/
else
   {   
      	VEN_Controller_Phase = VEN_INSP_PLAT;
		if ( (VEN_Controller_Phase == VEN_INSP_PLAT)
		  && (CYC_PreviousControllerPhase == VEN_INSP_RISE) )
		{
			DB_ComputeWrite(COMPUTED_RISE_TIME_U16,
								 VenTiCount);
		}
   }
}

/******************************************************************************/
/*%C                               IN FLOW MODE:								      */
/******************************************************************************/

else if (VEN_ControllerType == CONTROL_FLOW)
{
/*%C read the value of Qinsp Measure */
	MeasureQinsp = DB_ComputeRead(MEASURE_QINSP_S16);
/*%C read the value of adjusted Ti control */
	AdjustTiControl = DB_CurrentRead(ADJUST_TI_CONTROL_U16);
/*%C The rise phase must be limited by 33% of the inspiration delay*/
/*%C so a rise limit is computed :*/
/*%C RiseTimeLimit = min [ AdjustTiControl * 33% ; 150ms ]*/
	RiseTimeLimit = (AdjustTiControl * cRISE_TIME_PERCENT)/100;

/*%C The software must go into inspiration rise state during a step of */
/*%C scheduler.*/
/*%C So it is necessary to test the previous state : "VEN_EXH_PLAT" */
	if(CYC_PreviousControllerPhase == VEN_EXH_PLAT)
	{
		VEN_Controller_Phase = VEN_INSP_RISE;
	}
/*%C If ramp is Sinus => Controller phase goes directly to plateau */
	else if(AdjustRamp == RAMP_SINUS)
	{
		VEN_Controller_Phase = VEN_INSP_PLAT;
	}
/*%C While the value of the Ti Counter (counter of the inspiration phase) is*/
/*%C lower than 33% of Ti, */
/*%C and the Qi set point is lower than 90% of Qinsp Set point,or */
/*%C Ti counter is lower than 150ms,*/
/*%C and the actual state is different from "VEN_INSP_PLAT" ,then */
/*%C the new phase of controller is "VEN_INSP_RISE". */
	else if( (VenTiCount < RiseTimeLimit)
		     &&( (MeasureQinsp < 
		     			(SWORD16)((SWORD32)VEN_Qi_Set_Point * cDELTA_QINSP / 100))
			    ||(VenTiCount < cRISE_TIME_LIMIT) )
		  && (VEN_Controller_Phase != VEN_INSP_PLAT))
	{
		VEN_Controller_Phase = VEN_INSP_RISE;
	}
/*%C else the new phase is "VEN_INSP_PLAT" 	 */
	else
	{
		VEN_Controller_Phase = VEN_INSP_PLAT;
		if ( (VEN_Controller_Phase == VEN_INSP_PLAT)
		  && (CYC_PreviousControllerPhase == VEN_INSP_RISE) )
		{
			DB_ComputeWrite(COMPUTED_RISE_TIME_U16,
								 VenTiCount);
		}
	}
}

CYC_PreviousControllerPhase = VEN_Controller_Phase;
}
