/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Pres_Mode_Control_R.c  		        		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : this function controls the limits of the   		*/
/*%C CONTROL R setting in the Pres mode:						                     */
/*%C                                                                         	*/
/*%C CONTROL R [min:5, max:60, step:1, default:13]   									*/
/*%C CONTROL R is include in its own limits (otherwise, value is saturated)   */
/*%C TI CONTROL <= 0.5 * 60 / CONTROL R  (i.e. I:E <= 1:1)                    */
/*%C If the condition on Ti Control is not respected, a flag is set and the   */
/*%C value is saturated                                                       */
/*                                                            				  		*/
/******************************************************************************/
/*%I  Input Parameter :			   Id                                		  	   */
/*%IO Input/Output Parameter : 	*Value  	   			                  	   */
/*%O  Output Parameter : 		   True/False 	                 				      */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "DRV_VarEeprom.h"
#include "structure.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Adjust_Pres_Mode_Control_R.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Setting_Adjust_Pres_Mode_Control_R(UWORD16 *Value,
																  UWORD16 Id)
{

    /* Function result declaration */
   UWORD16 Function_Result = FALSE;

    // recover settings from database
    UWORD16 Adjust_Ti_Control = EEP_DB_PRES_Adjust[ADJUST_TI_CONTROL_U16];

    // computed values
    UWORD16 Max_Breath_Time_Ms = (60000u / *Value);

    /*%C Limit tests */
   if ( (*Value < cDB_PRES_TEST_ADJUST_DB[Id].mini)
     || (*Value > cDB_PRES_TEST_ADJUST_DB[Id].maxi) )
	{
		Function_Result = TRUE;
	}
    // test for I:E < 1:1
    else if ( Max_Breath_Time_Ms < (Adjust_Ti_Control * 2) )
    {
        /*%C  => Control Ti flag for IHM indication */
        DB_ControlWrite(LIMIT_TI_CONTROL_U16,
                        TRUE);
        Function_Result = TRUE;
    }
   else
   {
        // setting authorized - clear limit flag
        DB_ControlWrite(LIMIT_TI_CONTROL_U16,
                        FALSE);
		Function_Result = FALSE;

        DB_ComputeWrite(COMPUTED_RATE_U16,*Value);
        DB_ComputeBreathTimingRatios();
   }


	return(Function_Result);
}
