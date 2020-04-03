/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Vol_Control.c 		       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Vol_Control setting in the Vol mode								*/
/*                                                            				  		*/
/*%C VOL CONTROL [min:50, max:2000, step:10, default:500]         				*/
/*%C VOL CONTROL is include in its own limits(otherwise, value is saturated)  */
/*   3 lpm <= (VOL CONTROL x 60) /(TI CONTROL*1000) <= 100 lpm                */
/*      in SQ flow pattern                                                    */
/*   3 lpm <= 3*(VOL CONTROL x 60) / 2*(TI CONTROL*1000) <= 100 lpm           */
/*      in D and S flow pattern                                               */
/*%C VOL CONTROL * Vt Coef < 2000 ml						    							*/
/*%C If the conditions for Ti Control or Vt Coef are not respected, a limit   */
/*   flag is set for IHM indication and the value is saturated				  */
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
#include "DRV_VarEeprom.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Adjust_Vol_Mode_Vol_Control.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Vol_Control(UWORD16 *Value,
                                                   UWORD16 Id)
{
    // Function result declaration 
    UWORD16 Function_Result = FALSE;

    //  recover vol mode settings from adjust database
    UWORD16 Adjust_Ti_Control = EEP_DB_VOL_Adjust[ADJUST_TI_CONTROL_U16];
    UWORD16 Adjust_Sigh_Select = EEP_DB_VOL_Adjust[ADJUST_SIGH_SELECT_U16];
    UWORD16 Adjust_Sigh_Vt_Coef = EEP_DB_VOL_Adjust[ADJUST_SIGH_VT_COEF_U16];
    e_RampType Adjust_Ramp = EEP_DB_VOL_Adjust[ADJUST_RAMP_U16];

    /* Computed values*/
    UWORD32 Peak_Flow_Lpm = 0;

    // dependence between ramp and Ti, changing ramp changes peak flow

    // TBD - peak flow rates for all ramps - Ti or Vt needs to constrain RAMP as well
    if (Adjust_Ramp == RAMP_RECTANGLE)
    {
        Peak_Flow_Lpm = 
            (*Value * 60ul) / (Adjust_Ti_Control);
    }
    else // if (Adjust_Ramp == RAMP_SINUS || Adjust_Ramp == RAMP_DECELERATED)
    {
        // decelerating ramp or sinusoidal peak flow = 1.5 * Vt / Ti
        Peak_Flow_Lpm = 
            (*Value * 60ul * 3u) / (2u * Adjust_Ti_Control);
    }

    //   Up and down limit test
    if ( (*Value < cDB_VOL_TEST_ADJUST_DB[Id].mini)
         || (*Value > cDB_VOL_TEST_ADJUST_DB[Id].maxi) )
    {
        Function_Result = TRUE;
    }
    //   Dependence test between Peak Flow and Vol Control
    else if ( (Peak_Flow_Lpm < cPeakFlowMin)
              || (Peak_Flow_Lpm > cPeakFlowMax) )
    {
        // Value out of range => Ti Control flag for IHM indication
        DB_ControlWrite(LIMIT_TI_CONTROL_U16,
                        TRUE);
        Function_Result = TRUE;
    }
    //   Sigh limitation if activated
    else if (Adjust_Sigh_Select == TRUE)
    {
        //  Dependence test between Vol Control and sigh
        if ((*Value * Adjust_Sigh_Vt_Coef) / 10 
            > cDB_VOL_TEST_ADJUST_DB[Id].maxi )
        {
            DB_ControlWrite(LIMIT_SIGH_U16,
                            TRUE);
            Function_Result = TRUE;
        }
    }
    else
    {
        //  Setting authorized, deactivate Ti Control and sigh limit flags
        DB_ControlWrite(LIMIT_TI_CONTROL_U16,
                        FALSE);
        DB_ControlWrite(LIMIT_SIGH_U16,
                        FALSE);
        Function_Result = FALSE;
    }
    return(Function_Result);
}
