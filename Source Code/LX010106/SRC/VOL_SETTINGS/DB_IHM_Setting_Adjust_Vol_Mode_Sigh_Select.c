/******************************************************************************/
/*																			  */
/* Project Number	: 	RB0505     			     		                      */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                 			  */
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Select.c 		          */
/*                                                           				  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 	Functional description : 	this function controls the limits		  */
/*%C        of the sigh select setting in the Vol mode	 					  */
/*  					                                            		  */
/*%C SIGH SELECT [min:0, max:1, step:1, default:0]       					  */
/*%C SIGH SELECT is allowed only for CONTROL R >= 4                           */
/*                                                            				  */
/*   if the conditions on CONTROL R are not respected, a limit                */
/*   flag is set for IHM indication and the value is saturated	  		      */
/******************************************************************************/
/*%I 	Input Parameter :				Id                                    */
/*%IO Input/Output Parameter : 	*Value  	        			              */
/*%O 	Output Parameter : 			True/False 	                 			  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DRV_VarEeprom.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Select.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          */
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Select(UWORD16 *Value,
                                                   UWORD16 Id)
{
    UWORD16 Function_Result = FALSE;

    UWORD16 Adjust_Control_R = EEP_DB_VOL_Adjust[ADJUST_CONTROL_R_U16];

    // Limit tests
    // OFF = 0 / ON = 1
    if ( (*Value < cDB_VOL_TEST_ADJUST_DB[Id].mini)
         || (*Value > cDB_VOL_TEST_ADJUST_DB[Id].maxi)  )
    {
        Function_Result = TRUE;
    }
    // Rate >= 4 to enable sigh feature
    else if ( (*Value == 1) && (Adjust_Control_R < 4) )
    {
        DB_ControlWrite(LIMIT_CONTROL_R_U16,
                        TRUE);
        Function_Result = TRUE;
    }
    else
    {
        // Setting authorized - clear limit flag
        DB_ControlWrite(LIMIT_CONTROL_R_U16,
                        FALSE);
        Function_Result = FALSE;
    }

    return(Function_Result);
}
