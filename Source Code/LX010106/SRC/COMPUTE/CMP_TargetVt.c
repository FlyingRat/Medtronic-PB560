/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_TargetVt.c 			                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function computes the Pi set point function of target Vt.	      */
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
#include "structure.h"
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "Ventilation_Datas.h"
#include "Ventilation_Compute_Data.h"
#include "Ventilation_Constants.h"
#include "CMP_TargetVt.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


UWORD16 CMP_TargetVt(void)
{


	UWORD16 AdjustPressure = 0;

/* Target Vt Select recovery */
	UWORD16 Adjust_Target_Vt = DB_CurrentRead(ADJUST_TARGET_VT_U16);

/* Adjust mode recovery */
	UWORD16 Adjust_Mode = DB_ConfigRead(ADJUST_MODE_U16);

/* Target Vt No Select recovery */
	UWORD16 Target_Vt_Select = DB_CurrentRead(TARGET_VT_SELECT_U16);

/* High pressure alarm recovery */
	UWORD16 AlarmHighPressure = DB_AlarmStatusRead(ALARM_HIGH_PRESSURE_U16);
/* Max pressure recovery */
	UWORD16 AdjustMaxPressure = DB_CurrentRead(ADJUST_MAX_PRESSURE_U16);

/* read of the pressure convention */
	UWORD16 PressureSupportRelative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);

/* Adjust Peep for relative mode */
	UWORD16 AdjustPeep = DB_CurrentRead(ADJUST_PEEP_U16);

/* Adjust pressure recovery */
	UWORD16 AdjustPControl = DB_CurrentRead(ADJUST_P_CONTROL_U16);
	UWORD16 AdjustPSupport = DB_CurrentRead(ADJUST_P_SUPPORT_U16);

/* Adjust pressure recovery */
	UWORD16 ComputedVti = DB_ComputeRead(COMPUTED_VTI_U16);

/* Pi set point recovery */
	UWORD16 PiSetPoint = DB_CurrentRead(PI_SET_POINT_U16);

/* Computed Pi set point recovery */
	UWORD16 ComputedPiSetPoint = DB_ComputeRead(COMPUTED_PI_SET_POINT_U16);

/*%C If the convention is relative, then AdjustMaxPressure = AdjustMaxPressure + AdjustPeep */
	if(PressureSupportRelative == TRUE)
	{
		AdjustMaxPressure = AdjustMaxPressure + AdjustPeep;
	}

/*%C Pressure set point choice:             	                        			*/
/*%C - first function call, the start value is Pi set point (setting value)	*/
/*%C - others function calls, the start value is Computed Pi set point */
/*%C 		(Computed value in CMP_InspRiseComputings)	*/
/*%C The set point mutex initialization is made when the target Vt is */
/*%C unactivated (in CMP_InspRiseComputings) */
	if (CMP_SetPoint_Mutex == FALSE)
	{
		CMP_TargetVT_Pi = PiSetPoint;
		CMP_SetPoint_Mutex = TRUE;
	}

/*%C Pressure choice for Pmax:             	                        			*/
	if (Adjust_Mode == PRES)
	{
		AdjustPressure = PiSetPoint;
	}
	else if (Adjust_Mode == PSVT)
	{
		AdjustPressure = PiSetPoint;
	}

/*%C With no high pressure              	                        			*/
	if (AlarmHighPressure < ALARM_TRUE)
	{
/*%C	If the measured flow is > Target VT + 20 %                			*/
		if (ComputedVti > (Adjust_Target_Vt * 12UL / 10))
		{
			CMP_UpStep_Mutex = FALSE;
/*%C		If the pressure set point is higher than the adjusted pressure	*/
			if (CMP_TargetVT_Pi > AdjustPressure)
			{
/*%C			Decrease value computing				*/
				if (CMP_DownStep_Mutex == FALSE)
		   	{
					VEN_PressureDownStep = cMIN_STEP;
					CMP_DownStep_Mutex = TRUE;
		      }
				else
				{
/*%C				Decrease value * 2				*/
					VEN_PressureDownStep = VEN_PressureDownStep * 2;
/*%C				Decrease value saturation (cMAX_STEP)				*/
					if (VEN_PressureDownStep > cMAX_STEP)
					{
					   VEN_PressureDownStep = cMAX_STEP;
					}
				}
/*%C			Pi set point decrease with down step	*/
		      CMP_TargetVT_Pi = CMP_TargetVT_Pi - VEN_PressureDownStep;
			}
		}

/*%C	else, the measured flow is lower than the target Vt	*/
      else if (ComputedVti < Adjust_Target_Vt)
		{
			CMP_DownStep_Mutex = FALSE;
			// Si la consigne de pression est inférieure à la pression max autorisée 			
			if (CMP_TargetVT_Pi < AdjustMaxPressure)
			{
				// Calcul de l'incrément à appliquer
				if (CMP_UpStep_Mutex == FALSE)
				{
			      VEN_PressureUpStep = cMIN_STEP;
			      CMP_UpStep_Mutex = TRUE;
			   }
				else
			   {
/*%C				Increase value * 2				*/
				   VEN_PressureUpStep = VEN_PressureUpStep * 2;
/*%C				Increase value saturation (cMAX_STEP)				*/
				   if (VEN_PressureUpStep > cMAX_STEP)
					{
				   	VEN_PressureUpStep = cMAX_STEP;
					}
				}
/*%C			Pi set point increase with down step	*/
			   CMP_TargetVT_Pi = CMP_TargetVT_Pi + VEN_PressureUpStep;
			}
		}
/*%C	if the computed vti = target Vt	*/
		else
		{
			CMP_DownStep_Mutex = FALSE;
			CMP_UpStep_Mutex = FALSE;
		}
	}
/*%C else, an high pressure is detected	*/
	else
	{
/*%C The pressure is decreased until the high pressure disapears	*/
		// Initialisation des mutex
		CMP_DownStep_Mutex = FALSE;
		CMP_UpStep_Mutex = FALSE;
		// restauration valeur consigne avant la pression haute
		CMP_TargetVT_Pi = CMP_TargetVT_Pi - VEN_PressureUpStep;
	}

/*%C Pi set point saturation between adjusted and max pressure	*/
	CMP_TargetVT_Pi = (UWORD16)saturation(CMP_TargetVT_Pi,
										  AdjustPressure,
										  AdjustMaxPressure);
return(CMP_TargetVT_Pi);
}
