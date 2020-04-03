/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vsimv_Mode_Ti_Control.c   	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Ti_Control setting in the Vsimv mode							   */
/*                                                            				  		*/
/*%C TI CONTROL [min:300, max:6000, step:100, default:1500]    					*/
/*%C TI CONTROL is include in its own limits(otherwise, value is saturated)   */
/*%C 3 lpm <= ( VOL CONTROL*60) / TI CONTROL <= 100 lpm 									*/
/*%C If Control R >= 8 Ti Control <= 0.33 * 60 * 1000/ Control R                            	*/
/*%C If Control R < 8 Ti Control <= 2400ms                            	*/
/*%C if the conditions on  Control R or Vol Control are not respected,     */
/*%C  a limit flag is set for IHM indication and the value is saturated.    	*/
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
#include "DB_IHM_Setting_Adjust_Vsimv_Mode_Ti_Control.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Vsimv_Mode_Ti_Control(UWORD16 *Value, 
                                                    UWORD16 Id)
{

    /* Function result declaration */
    UWORD16 Function_Result = FALSE;

    /* Datas declaration for the compute	 */
    UWORD32 Volume_Inspired_Per_Minute = 0;

    /* Id values recuperation from adjust base in vsimv mode */
    UWORD32 Adjust_Vol_Control   = 
        (UWORD32)EEP_DB_VSIMV_Adjust[ADJUST_VOL_CONTROL_U16];
    UWORD16 Adjust_Control_R = 
        EEP_DB_VSIMV_Adjust[ADJUST_CONTROL_R_U16];
    /*%C Ti control initialized to 2400ms */
    UWORD16 Ti_Control_Control_R_Limit = cITMaxSimvLimit;

    /*%C if control R > 8bpm, Ti control limit switches from 2400ms to  (0.33*60*1000 / Control R) 	*/  
    if (Adjust_Control_R >= cSimvControlR)
    {
        Ti_Control_Control_R_Limit = cITMaxSimvSec / Adjust_Control_R;  
    }


    /* Computed values*/
    Volume_Inspired_Per_Minute = (Adjust_Vol_Control * 60u) / (UWORD32)*Value;

    /*%C Limit tests */
    if ( (*Value < cDB_VSIMV_TEST_ADJUST_DB[Id].mini)
         || (*Value > cDB_VSIMV_TEST_ADJUST_DB[Id].maxi) )
    {
        Function_Result = TRUE;
    }
    /*%C Dependence test between Vol Control and Ti Control */
    else if ( (Volume_Inspired_Per_Minute < cPeakFlowMin)
              || (Volume_Inspired_Per_Minute > cPeakFlowMax) )
    {
        /*%C  Value out of range => Vol Control flag for IHM indication */
        DB_ControlWrite(LIMIT_VOL_CONTROL_U16,
                        TRUE);
        Function_Result = TRUE;
    }
    /*%C Dependence test between Control R and Ti Control */
    else if (*Value > Ti_Control_Control_R_Limit)
    {
        /*%C  => Control R flag for IHM indication */
        DB_ControlWrite(LIMIT_CONTROL_R_U16,
                        TRUE);
        Function_Result = TRUE;
    }
    else
    {
        /*%C Setting authorized, Vol Control and Simv Backup R flag desactivation */
        DB_ControlWrite(LIMIT_VOL_CONTROL_U16,
                        FALSE);
        DB_ControlWrite(LIMIT_CONTROL_R_U16,
                        FALSE);
        Function_Result = FALSE;

        DB_ComputeWrite(COMPUTED_TI_CONTROL_U16,*Value);
        DB_ComputeBreathTimingRatios();
    }

    return(Function_Result);
}
