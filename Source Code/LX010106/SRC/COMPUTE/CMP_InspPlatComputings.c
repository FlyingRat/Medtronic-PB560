/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_InspPlatComputings.c                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function computes the pressure inspiration during plateau phase.  */
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
#include "math.h"
#include "DB_Current.h"
#include "DB_Compute.h"
#include "Ventilation_Datas.h"
#include "Ventilation_Compute_Data.h"
#include "CMP_InspPlatComputings.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void CMP_InspPlatComputings(void)
{
/* Ramp type recovery 														  */
	e_RampType Ramp = DB_CurrentRead(ADJUST_RAMP_U16);

/* Adjust Ti recovery 														  */
	UWORD16 Adjust_Ti_Control = DB_CurrentRead(ADJUST_TI_CONTROL_U16);

/* Adjust Vol control recovery */
	UWORD16 AdjustVolControl = DB_CurrentRead(ADJUST_VOL_CONTROL_U16);

/* Inspiratory counter value */
	UWORD16 VenTiCount = 0;

/* Qi temp */
 	FLOAT32 Qitemp = 0;

/* Rise time recovery */
	UWORD16 Computed_Rise_Time = DB_ComputeRead(COMPUTED_RISE_TIME_U16);


/*%C If VEN_ControllerType = CONTROL_FLOW and 								  */
/*%C ADJUST_RAMP_U16 = RAMP_DECELERATED, then 								  */
	if ( (VEN_ControllerType == CONTROL_FLOW) 
	  && (Ramp == RAMP_DECELERATED) )
   {
/*%C Inspiratory flow computing with decelerated ramp 						  */
/*%C VenTiCount = Inspiratory timer value recovery for flow computing  		  */
	   VenTiCount = TIM_ReadCounterValue(VEN_TI_COUNT);
/*%C  Inspiratory flow computing: 											  */
/*%C  VEN_Qi_Set_Point = (CMP_DefaultQinsp / 3) + 			   		   		  */
/*%C  	 (2/3 CMP_DefaultQinsp * (ADJUST_TI_CONTROL_U16 - VenTiCount) /   	  */
/*%C	(ADJUST_TI_CONTROL_U16 - COMPUTED_RISE_TIME_U16))		 			  */
		VEN_Qi_Set_Point = ((UWORD16)CMP_DefaultQinsp / 3) + 
								 ((UWORD16)(CMP_DefaultQinsp * 2 *
		(Adjust_Ti_Control - VenTiCount) / (3 * (Adjust_Ti_Control 
																		- Computed_Rise_Time))));
	}
	else if (Ramp == RAMP_SINUS)
	{
	   VenTiCount = TIM_ReadCounterValue(VEN_TI_COUNT);
/*%C  	Qi = Qmax * II/2 * sin(II/2 * t)			*/
/*%C  	Qi = Vt/Ti * II/2 * sin(II/Ti * t)			*/
/*%C  	with II = 3.14 and Ti = inspiration	delay		*/
		Qitemp = sin((FLOAT32)(3.14f * (FLOAT32)VenTiCount 
		 / (FLOAT32)Adjust_Ti_Control));

		Qitemp *= (FLOAT32)((FLOAT32)AdjustVolControl * 600.0f 
		 / (FLOAT32)Adjust_Ti_Control) * 1.571f;

/*%C  	Qi Set point correction		*/
		Qitemp = (UWORD16)Qitemp * (FLOAT32)CMP_CorrectorVtSin / 100.0f;

		VEN_Qi_Set_Point = (UWORD16)Qitemp + 5;
	}
}
