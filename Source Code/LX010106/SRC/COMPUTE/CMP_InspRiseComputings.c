/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_InspRiseComputings.c                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function computes the pressure inspiration during rise phase.     */
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
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_Compute.h"
#include "Ventilation_Datas.h"
#include "CMP_InspRiseComputings.h"
#include "Ventilation_Constants.h"
#include "Ventilation_Compute_data.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void CMP_InspRiseComputings(void)
{
/* Pi set point recovery */
	static UWORD16 Pi_Set_Point = 0;

/* Ramp recovery */
	UWORD16 Adjust_Ramp = DB_CurrentRead(ADJUST_RAMP_U16);
/* Ramp memorization */
	static UWORD16 Previous_Adjust_Ramp = 0;

/* Ti Control recovery */
	UWORD16 Adjust_Ti_Control = DB_CurrentRead(ADJUST_TI_CONTROL_U16);
/* Ti Control memorization */
	static UWORD16 Previous_Adjust_Ti_Control = 0;

/* Adjust mode recovery */
	UWORD16 Adjust_Mode = DB_ConfigRead(ADJUST_MODE_U16);
/* Adjust mode memorization */
	static UWORD16 Previous_Adjust_Mode = VOL;

/* Vol Control recovery */
	UWORD16 Adjust_Vol_Control = DB_CurrentRead(ADJUST_VOL_CONTROL_U16);

/* Previous adjust Vol Control */
	static UWORD16 Previous_Adjust_Vol_Control = 0;

/* Peep Control recovery */
	UWORD16 Adjust_Peep = DB_CurrentRead(ADJUST_PEEP_U16);

/* Previous adjust Vol Control */
	static UWORD16 Previous_Adjust_Peep = 0;
	
/* Target Vt select recovery */
	UWORD16 TargeVtSelect = DB_CurrentRead(TARGET_VT_SELECT_U16);



/* Vol Control recovery */
	UWORD16 Rise_Time = DB_CurrentRead(RISE_TIME_U16);

/* Ti counter recovery */
	UWORD16 VenTiCount = TIM_ReadCounterValue(VEN_TI_COUNT);

/* Theorical inspiratory flow */
	static UWORD32 TheoricalQinsp = 0;

	static PreviousTargeVtSelect = FALSE;

/*****************************/
/*   Pi set point            */
/*****************************/

/*%C In pressure mode, at the phase change, the set point is written 			*/
/*%C in the compute base 		                                       			*/
	if (VEN_ControllerType == CONTROL_PRESSURE)
	{

		if(VEN_Controller_Phase != CMP_PreviousControllerPhase)
		{
/*%C  if target Vt selected the set point is computed in order to reach an 	*/
/*%C 	adjusted target Vt 																		*/
			if (TargeVtSelect == TRUE)
			{	
				if( PreviousTargeVtSelect == FALSE )
				{
					CMP_SetPoint_Mutex = FALSE;
				}
				Pi_Set_Point = CMP_TargetVt();
			}
/*%C else no target Vt selected, the set point is the adjusted one     			*/
			else
			{
/*			Pi_Set_Point = Pi_Set_Point;					*/
/*%C  	Set point mutex initialization (used in CMP_TargetVt) */
				CMP_UpStep_Mutex = FALSE;
				CMP_DownStep_Mutex = FALSE;
				CMP_TargetVT_Pi = 0;
				CMP_SetPoint_Mutex = TRUE;
				Pi_Set_Point = DB_CurrentRead(PI_SET_POINT_U16);
			}
			DB_ComputeWrite(COMPUTED_PI_SET_POINT_U16,
		                Pi_Set_Point);
			PreviousTargeVtSelect = TargeVtSelect ;
   		}

/*****************************/
/*   Rise Pi set point       */
/*****************************/
/*%C  Rise Pi set point compute:  */
/*%C  Rise pi = (Pi set point - Pep) * Ti / Rise time + Pep  						*/
/*	  	when Ti >= Rise time => Rise pi = Pi set point									*/
      	if (VenTiCount < Rise_Time)
		{
			VEN_Rise_Pi_Set_Point = (UWORD16)(((UWORD32)(Pi_Set_Point -
	    	VEN_PepMeasured) * VenTiCount) / Rise_Time + VEN_PepMeasured);
		}
		else
		{
			VEN_Rise_Pi_Set_Point = Pi_Set_Point;
		}
   	}

/*****************************/
/*   Flow set point          */
/*****************************/

/*%C The inspiratory flow is computed once if the first cycle is detected or  */
/*%C if one of the following settings has changed :	                        */
/* - Ti		                                                                  */
/* - Vol Control                                                              */
/* - Ramp		                                                               */
/* - Mode		                                                               */
 	else if ( ( (VEN_ControllerType == CONTROL_FLOW)
		&& (VEN_Controller_Phase != CMP_PreviousControllerPhase) ) 
		&& ( (Adjust_Ti_Control != Previous_Adjust_Ti_Control)
		  || (Adjust_Vol_Control != Previous_Adjust_Vol_Control)
		  || (Adjust_Mode != Previous_Adjust_Mode)
	     || (Adjust_Ramp  != Previous_Adjust_Ramp)
	     || (Adjust_Peep  != Previous_Adjust_Peep)
		  || (VEN_FirstCycle == FALSE) ) )
   {
/*%C  If ramp is rectangle: flow = volume * 10 * 60 / Ti + Offset     			*/
/*%C  Volume (ml) => *10 pour obtenir une consigne en dl 							*/
/*%C	Ti (ms) et Offset en dl/min														   */
		if (Adjust_Ramp == RAMP_RECTANGLE)
		{
			TheoricalQinsp = ((UWORD32)Adjust_Vol_Control * 10L *60L / 
			                   (UWORD32)Adjust_Ti_Control)
			                  + cOFFSETQINSP;
		}
/*%C	If ramp is sinus														   */
		else if (Adjust_Ramp == RAMP_SINUS)
		{
		   TheoricalQinsp = 0;
			if (Adjust_Peep <= 60)
			{
				CMP_CorrectorVtSin = (UWORD16)VEN_RiseCompute((SWORD32)Adjust_Vol_Control,
																			 (SWORD32)50,
																			 (SWORD32)300,
																			 (SWORD32)150,
																			 (SWORD32)100);
			}
			else
			{
				CMP_CorrectorVtSin = (UWORD16)VEN_RiseCompute((SWORD32)Adjust_Vol_Control,
																			 (SWORD32)50,
																			 (SWORD32)200,
																			 (SWORD32)150,
																			 (SWORD32)100);
			}
		}
/*%C  If ramp is decelerated: flow = 3/2 * volume * 10 * 60 / Ti + Offset		*/
		else
		{
			TheoricalQinsp = ( (3L * (UWORD32)Adjust_Vol_Control * 10 * 60L) /
									 (2L * (UWORD32)Adjust_Ti_Control) )
			                   + cOFFSETQINSP;
		}
		
/*%C  Flow set point affectation                                            */
		CMP_DefaultQinsp = (UWORD16)TheoricalQinsp;
	   VEN_Qi_Set_Point = (UWORD16)TheoricalQinsp;
	
/*%C  Previous settings memorization: volume, Ti, ramp and mode               */
		Previous_Adjust_Ti_Control = Adjust_Ti_Control;
		Previous_Adjust_Ramp = Adjust_Ramp;
		Previous_Adjust_Mode = Adjust_Mode;
		Previous_Adjust_Vol_Control = Adjust_Vol_Control;
		Previous_Adjust_Peep = Adjust_Peep;
   }


}
