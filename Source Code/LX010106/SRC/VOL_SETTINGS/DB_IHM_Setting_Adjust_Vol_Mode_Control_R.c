/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Control_R.c  		        		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : this function controls the limits of the   		*/
/*%C CONTROL R setting in the Vol mode:									            */
/*%C                                                                         	*/
/*%C CONTROL R [min:1, max:60, step:1, default:13]   						  */
/*%C CONTROL R is include in its own limits(otherwise, value is saturated)   	*/
/*   TI CONTROL <= (60/2*CONTROL R)  so I:E <= 1:1                            */
/*   If Sigh = YES then CONTROL R >= 4                                        */
/*%C If the conditions on VOL CONTROL is not respected, a limit flag is set 	*/
/*%C for IHM indication and the value is saturated      		                  */
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
#include "DB_IHM_Setting_Adjust_Vol_Mode_Control_R.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Control_R(UWORD16 *Value,
																 UWORD16 Id)
{

    /*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

    //   recover vol mode adjusted settings
    UWORD16 Adjust_Ti_Control = EEP_DB_VOL_Adjust[ADJUST_TI_CONTROL_U16];
    UWORD16 Adjust_Sigh_Select = EEP_DB_VOL_Adjust[ADJUST_SIGH_SELECT_U16];

    /* Computed values*/
    UWORD16 Max_Breath_Time_Ms = (60000u / *Value);

    /*%C Limit tests */
   if ( (*Value < cDB_VOL_TEST_ADJUST_DB[Id].mini)
     || (*Value > cDB_VOL_TEST_ADJUST_DB[Id].maxi)	)
   {
		Function_Result = TRUE;
   }
    // maximum I:E ratio of 1:1
    else if ( Max_Breath_Time_Ms < (Adjust_Ti_Control * 2) )
   {
        DB_ControlWrite(LIMIT_TI_CONTROL_U16,
							 TRUE);
		Function_Result = TRUE;
   }
    else if (Adjust_Sigh_Select == TRUE)
    {
        //  Dependence test between rate and sigh
        if (*Value < 4)
        {
            DB_ControlWrite(LIMIT_SIGH_U16,
                            TRUE);
            Function_Result = TRUE;
        }
    }
   else
   {
        //    Value in range => clear limit flags
        DB_ControlWrite(LIMIT_TI_CONTROL_U16,
							 FALSE);
        DB_ControlWrite(LIMIT_SIGH_U16,
                        FALSE);
		Function_Result = FALSE;

        DB_ComputeWrite(COMPUTED_RATE_U16,*Value);
        DB_ComputeBreathTimingRatios();
   }

	return(Function_Result);
}

