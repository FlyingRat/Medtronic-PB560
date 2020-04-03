/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Ti_Control.c   	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Ti_Control setting in the Vol mode								   */
/*                                                            				  		*/
/*%C TI CONTROL [min:300, max:6000, step:100, default:1500]    					*/
/*%C TI CONTROL is include in its own limits(otherwise, value is saturated)   */
/*   3 lpm <= (VOL CONTROL x 60) / (TI CONTROL*1000) <= 100 lpm               */
/*     in SQ flow pattern                                                     */
/*   3 lpm <= 3*(VOL CONTROL x 60) / 2*(TI CONTROL*1000) <= 100 lpm           */
/*     in D and S flow pattern                                                */
/*%C if the conditions on Control R or Vol Control are not respected, a limit	*/
/*%C flag is set for IHM indication and the value is saturated	  		         */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				Id                                    		  	*/
/*%IO Input/Output Parameter : 	*Value  	        			                  	*/
/*%O 	Output Parameter : 			True/False 	                 				  		*/
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "structure.h"
//#include "Ventilation_Constants.h"
#include "DRV_VarEeprom.h"
#include "DB_Control.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Adjust_Vol_Mode_Ti_Control.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Ti_Control(UWORD16 *Value,
                                                  UWORD16 Id)
{

    /* Function result declaration */
    UWORD16 Function_Result = FALSE;

    // recover vol mode values from adjust database
    UWORD32 Adjust_Vol_Control = (UWORD32)EEP_DB_VOL_Adjust[ADJUST_VOL_CONTROL_U16];
    e_RampType Adjust_Ramp = EEP_DB_VOL_Adjust[ADJUST_RAMP_U16];
    UWORD16 Adjust_Control_R  =  EEP_DB_VOL_Adjust[ADJUST_CONTROL_R_U16];
    UWORD16 Max_Breath_Time_Ms = (UWORD16)(60000ul / Adjust_Control_R);

    /* Computed values*/
    UWORD32 Peak_Flow_Lpm = 0;

    // dependence between ramp and Ti, changing ramp changes peak flow

    // TBD - peak flow rates for all ramps - Ti or Vt needs to constrain RAMP as well
    if (Adjust_Ramp == RAMP_RECTANGLE)
    {
        Peak_Flow_Lpm = 
            (Adjust_Vol_Control * 60ul) / (*Value);
    }
    else // if (Adjust_Ramp == RAMP_SINUS || Adjust_Ramp == RAMP_DECELERATED)
    {
        // decelerating ramp or sinusoidal peak flow = 1.5 * Vt / Ti
        Peak_Flow_Lpm = 
            (Adjust_Vol_Control * 60ul * 3u) / (2u * (*Value));
    }

    // update I:E and I/T for display purposes

    //   Up and down limit test											*/
    if ( (*Value < cDB_VOL_TEST_ADJUST_DB[Id].mini)
         || (*Value > cDB_VOL_TEST_ADJUST_DB[Id].maxi) )
    {
        Function_Result = TRUE;
    }
    else if ( (*Value * 2 > Max_Breath_Time_Ms) )
    {
        DB_ControlWrite(LIMIT_CONTROL_R_U16,
                        TRUE);
        Function_Result = TRUE;
    }
    else if ( (Peak_Flow_Lpm < cPeakFlowMin)
              || (Peak_Flow_Lpm > cPeakFlowMax) )
    {
        //  Value out of range => Vol Control flag for IHM indication 
        DB_ControlWrite(LIMIT_VOL_CONTROL_U16,
                        TRUE);
        Function_Result = TRUE;
    }
    else
    {
        // Setting authorized, deactivate limit flags
        DB_ControlWrite(LIMIT_CONTROL_R_U16,
                        FALSE);
        DB_ControlWrite(LIMIT_VOL_CONTROL_U16,
                        FALSE);
        Function_Result = FALSE;

        DB_ComputeWrite(COMPUTED_TI_CONTROL_U16,*Value);
        DB_ComputeBreathTimingRatios();
    }

    return(Function_Result);
}
