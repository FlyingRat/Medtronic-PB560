/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Pres_Mode_TiControl.c   	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits */
/*%C        of the Ti_Control setting in the Pres mode						  */
/*                                                            				  */
/*%C TI CONTROL [min:300, max:6000, step:100, default:1500]    				  */
/*%C TI CONTROL is include in its own limits(otherwise, value is saturated)   */
/*%C TI CONTROL <= 0.5 * 60 / CONTROL R  (i.e. I:E <= 1:1)                    */
/*%C If the conditions on Control R is not respected, a limit flag is set for */
/*%C IHM indication, and the value is saturated                               */
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
#include "DB_IHM_Setting_Adjust_Pres_Mode_Ti_Control.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Pres_Mode_Ti_Control(UWORD16 *Value,
                                                   UWORD16 Id)
{
    /* Function result declaration */
    UWORD16 Function_Result = FALSE;

    /* Id values recuperation from adjust base in pres mode */
    UWORD16 Adjust_Control_R = EEP_DB_PRES_Adjust[ADJUST_CONTROL_R_U16];

    // computed values
    UWORD16 Max_Breath_Time_Ms = (60000u / Adjust_Control_R);

    /*%C Limit tests */
    if ( (*Value < cDB_PRES_TEST_ADJUST_DB[Id].mini)
         || (*Value > cDB_PRES_TEST_ADJUST_DB[Id].maxi) )
    {
        Function_Result = TRUE;
    }
    // test for I:E < 1:1
    else if ( Max_Breath_Time_Ms < (*Value * 2) )
    {
        /*%C  => Control R flag for IHM indication */
        DB_ControlWrite(LIMIT_CONTROL_R_U16,
                        TRUE);
        Function_Result = TRUE;
    }
    else
    {
        // Setting authorized, clear limit flag
        DB_ControlWrite(LIMIT_CONTROL_R_U16,
                        FALSE);
        Function_Result = FALSE;

        DB_ComputeWrite(COMPUTED_TI_CONTROL_U16,*Value);
        DB_ComputeBreathTimingRatios();
    }
    return(Function_Result);
}
