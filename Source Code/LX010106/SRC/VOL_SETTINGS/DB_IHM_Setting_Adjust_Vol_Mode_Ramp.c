/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Ramp.c			          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Ramp setting in the Vol mode										   */
/*                                                            				  		*/
/*   RAMP [min:0, max:2, step:1, default:0]    see e_RampType enum            */
/*   3 lpm <= (VOL CONTROL x 60) / (TI CONTROL*1000) <= 100 lpm               */
/*     to allow SQ flow pattern                                               */
/*   3 lpm <= 3*(VOL CONTROL x 60) / 2*(TI CONTROL*1000) <= 100 lpm           */
/*     to allow D and S flow pattern                                          */
/*   if the conditions on Vol Control are not respected, a limit              */
/*   flag is set for IHM indication and the value is saturated	  		      */
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
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Adjust_Vol_Mode_Ramp.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Ramp(UWORD16 *Value)
{

    static UWORD16 PreviousValue = 0;
    static UWORD16 InitializePreviousValue = TRUE;

    // initialize return value
    UWORD16 Function_Result = FALSE;

    // recover vol mode values from adjust database
    UWORD32 Adjust_Vol_Control = (UWORD32)EEP_DB_VOL_Adjust[ADJUST_VOL_CONTROL_U16];
    UWORD16 Adjust_Control_R  =  EEP_DB_VOL_Adjust[ADJUST_CONTROL_R_U16];
    UWORD16 Adjust_Ti_Control  =  EEP_DB_VOL_Adjust[ADJUST_TI_CONTROL_U16];

    /* Computed values*/
    UWORD32 Peak_Flow_Lpm = 0;

    // Only once per power up, update the previous value from
    // the database.
    if (InitializePreviousValue)
    {
        PreviousValue = EEP_DB_VOL_Adjust[ADJUST_RAMP_U16];
        InitializePreviousValue = FALSE;
    }

    /*%C Each operation (increment/decrement) gives the modulus result: */
    /*%C D => R ; R => S ; S => D*/
    *Value = *Value % nb_of_ramps;
    if (PreviousValue == *Value)
    {
        *Value = (nb_of_ramps - 1);
    }

    // dependence between ramp and Ti, changing ramp changes peak flow
    if (*Value == RAMP_RECTANGLE)
    {
        Peak_Flow_Lpm = 
            (Adjust_Vol_Control * 60ul) / (Adjust_Ti_Control);
    }
    else // if (Adjust_Ramp == RAMP_SINUS || Adjust_Ramp == RAMP_DECELERATED)
    {
        // decelerating ramp or sinusoidal peak flow = 1.5 * Vt / Ti
        Peak_Flow_Lpm = 
            (Adjust_Vol_Control * 60ul * 3u) / (2u * Adjust_Ti_Control);
    }

    if ( (Peak_Flow_Lpm < cPeakFlowMin)
         || (Peak_Flow_Lpm > cPeakFlowMax) )
    {
        //  Value out of range => Vol Control flag for IHM indication 
        DB_ControlWrite(LIMIT_VOL_CONTROL_U16,
                        TRUE);
        Function_Result = TRUE;
    }
    else
    {
        // setting authorized - reset limit flags
        DB_ControlWrite(LIMIT_VOL_CONTROL_U16,
                        FALSE);
        Function_Result = FALSE;
        PreviousValue = *Value;
    }

    return(Function_Result);
}
