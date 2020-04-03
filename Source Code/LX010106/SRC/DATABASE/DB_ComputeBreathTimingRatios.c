/******************************************************************************/
/*																			  */
/* Project Number	: 	RB0505     			     		                      */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                 			  */
/* Filename	: DB_ComputeBreathTimingRatios.c                                  */
/*                                                           				  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*   Functional description : 	This function computes the I:E and I/T% for   */
/*                              a given Rate and Insp Time and writes them    */
/*                              to the COMPUTE database                       */
/*                                                            				  */
/******************************************************************************/
/*   	Input Parameter : 			None		        			          */
/*      Input/Output Parameter : 	None 	        			              */
/*   	Output Parameter : 			None	                       			  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DB_Compute.h"
#include "DB_Current.h"
#include "DB_IhmAccessParaDataBase.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

// called from the Rate and TiControl settings to update the I:E and I/T ratios
void DB_ComputeBreathTimingRatios(void)
{
    // based on a set Inspiratory Time, calculate the I:E and I/T ratios
    UWORD16 AdjustControlR;
    UWORD16 AdjustTiControl;

    UWORD16 CalcIt;
    const UWORD16 CalcIeNumerator = 10;
    UWORD16 CalcIeDenominator;
    UWORD32 ETimeMs;

    DB_IhmAccessParaDataBase(&AdjustTiControl,
                             COMPUTED_TI_CONTROL_U16, 
                             COMPUTE, 
                             READ);

    DB_IhmAccessParaDataBase(&AdjustControlR,
                             COMPUTED_RATE_U16,
                             COMPUTE, 
                             READ);

    // I/T = Ti (ms) / (60 / Rate) =  Ti * Rate / 60
    CalcIt = (UWORD16)((UWORD32)AdjustTiControl * AdjustControlR / 60u);  // 0.1% accuracy

    // I:E Denominator
    if (CalcIt == 0)
    {
        CalcIeDenominator =  0u;
    }
    else
    {
        ETimeMs = (60000ul / AdjustControlR) - AdjustTiControl;
        CalcIeDenominator =  (UWORD16)((ETimeMs * 10) / AdjustTiControl);
    }

    // write I/T and I:E to compute database
    DB_IhmAccessParaDataBase(&CalcIt,
                             COMPUTED_I_T_U16, 
                             COMPUTE, 
                             WRITE);

    DB_IhmAccessParaDataBase(&CalcIeNumerator,
                             COMPUTED_IE_NUMERATOR_U16, 
                             COMPUTE, 
                             WRITE);

    DB_IhmAccessParaDataBase(&CalcIeDenominator,
                             COMPUTED_IE_DENOMINATOR_U16, 
                             COMPUTE, 
                             WRITE);
}
