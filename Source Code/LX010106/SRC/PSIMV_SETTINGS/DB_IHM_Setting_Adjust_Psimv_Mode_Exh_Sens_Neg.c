/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psimv_Mode_Exh_Sens_Neg.c   	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Exh Sens Neg setting in the Psimv mode	  							*/
/*                                                            				  		*/
/*%C Exh Sens [min:10, max:90, step:5, default:15]             					*/
/*%C Exh Sens is include in its own limits(otherwise, value is saturated)     */
/*%C Automatic mode is reached by the up key                                  */
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

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Exh_Sens_Neg(UWORD16 *Value,
																	UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C  Down limit test 	*/
   if (*Value < cDB_PSIMV_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Value limited to its min */
      *Value = cDB_PSIMV_TEST_ADJUST_DB[Id].mini;
/*%C  Auto exh sens flag writing by DB_WriteDataInEepAndRam function call 	*/
      DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[AUTO_EXH_SENS_NEG_SELECT_U16],
										TRUE);
		Function_Result = FALSE;
   }			
/*%C Limit tests */
   else if (*Value > cDB_PSIMV_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_PSIMV_TEST_ADJUST_DB[Id].maxi;
		Function_Result = FALSE;
   }
/*%C If "Auto exh sens flag" activated => "Auto exh sens flag" cancelled */
	else if (EEP_DB_PSIMV_Adjust[AUTO_EXH_SENS_NEG_SELECT_U16] == TRUE)
	{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[AUTO_EXH_SENS_NEG_SELECT_U16],
										FALSE);										
		Function_Result = TRUE;
	}
/*%C Setting authorized	 */
   else
   {
      Function_Result = FALSE;
   }

	return(Function_Result);
}
