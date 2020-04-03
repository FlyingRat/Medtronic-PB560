/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IHM_Setting_Adjust_Cpap_Mode_High_R.c  			          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the High_R setting in the Psv mode										*/
/*                                                            				  		*/
/*%C HIGH R [min:10, max:120, step:1, default:120 = OFF]								*/
/*%C HIGH R is include in its own limits(otherwise, value is saturated)  	   */
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
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Setting_Adjust_Cpap_Mode_High_R(UWORD16 *Value,
															 UWORD16 Id)
{

/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Limit tests */
/*%C Down limit test */
   if (*Value < cDB_CPAP_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Value limited to its min */
      *Value = cDB_CPAP_TEST_ADJUST_DB[Id].mini;

		Function_Result = FALSE;
   }
/*%C Up limit test */
   else if (*Value > cDB_CPAP_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_CPAP_TEST_ADJUST_DB[Id].maxi;
/*%C  High R flag writing by DB_WriteDataInEepAndRam function call 	*/
      DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[HIGH_R_NO_SELECT_U16],
										TRUE);
		Function_Result = FALSE;
   }
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_CPAP_Adjust[HIGH_R_NO_SELECT_U16] == TRUE)
	{
		DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[HIGH_R_NO_SELECT_U16],
										FALSE);
		Function_Result = TRUE;
	}
	else
   {
/*%C  Value in range*/
		Function_Result = FALSE;
   }

	return(Function_Result);
}
