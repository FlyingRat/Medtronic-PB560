/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_PiSetPointPsimvMode.c                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   It computes the pi set point value, in the PIMV mode function of the   */
/*%C   cycle phase (CP or PSV)															   */
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
#include "define.h"
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_Compute.h"
#include "CMP_PiSetPointPsimvMode.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void CMP_PiSetPointPsimvMode(void)
{
/* Pressure control recovery from current base                                */
   UWORD16 Adjust_P_Control = DB_CurrentRead(ADJUST_P_CONTROL_U16);   
/* Pressure support recovery from current base                                */
   UWORD16 Adjust_P_Support = DB_CurrentRead(ADJUST_P_SUPPORT_U16);   
/* Exhalated pressure recovery from current base                              */
   UWORD16 Adjust_Peep = DB_CurrentRead(ADJUST_PEEP_U16);   
/* Simv cycle recovery from control base                                      */
   UWORD16 Simv_Cycles = DB_ControlRead(SIMV_CYCLES_U16);
  /* read of the pressure convention */
	UWORD16 Pressure_Support_Relative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);   
/* Pi set point declaration                                                   */
   UWORD16 Pi_Set_Point = 0;   



/*%C If the cycle phase is CP or CAP, Pi set point = P control + Peep         */
   if ( (Simv_Cycles == CP_Cycle)
     || (Simv_Cycles == CAP_Cycle) )
   {
		if(Pressure_Support_Relative == TRUE)
		{
	   		Pi_Set_Point = Adjust_P_Control + Adjust_Peep;
		}
		else
		{
			Pi_Set_Point = Adjust_P_Control; 
		}
/*%C  Value writing in current base                                           */
		DB_CurrentWrite(PI_SET_POINT_U16,
		                Pi_Set_Point);

		DB_ComputeWrite(COMPUTED_PI_SET_POINT_U16,
						Pi_Set_Point);
   }
/*%C If the cycle phase is PSV, Pi set point = P support + Peep               */
   else if (Simv_Cycles == PSV_Cycle)
   {
		if(Pressure_Support_Relative == TRUE)
		{
	  		Pi_Set_Point = Adjust_P_Support + Adjust_Peep;
		}
		else
		{
			Pi_Set_Point = Adjust_P_Support;
		}
/*%C  Value writing in current base                                           */
		DB_CurrentWrite(PI_SET_POINT_U16,
		                Pi_Set_Point);

		DB_ComputeWrite(COMPUTED_PI_SET_POINT_U16,
						Pi_Set_Point);
   }   
/*%C else, the mode is not PSIMV, the Pi set point is computed in the         */
/*%C DB_CopyMngt                                                              */
}