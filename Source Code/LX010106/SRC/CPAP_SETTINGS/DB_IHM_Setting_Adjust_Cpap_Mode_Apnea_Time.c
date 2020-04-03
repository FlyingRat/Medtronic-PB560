/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Cpap_Mode_Apnea_Time.c    	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Apnea Time setting in the Cpap mode	  							*/
/*                                                            				  		*/
/*%C Apnea Time (ms) [min:1000, max:60000, step:1000, default:30000]          */
/*%C Apnea Time is include in its own limits(otherwise, value is saturated)   */
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

UWORD16 DB_IHM_Setting_Adjust_Cpap_Mode_Apnea_Time(UWORD16 *Value,
																  UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Limit tests */
/*%C Up Limit test */
   if (*Value > cDB_CPAP_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_CPAP_TEST_ADJUST_DB[Id].maxi;
      Function_Result = FALSE;
   }
/*%C Down Limit test and auto flag selection */
   else if (*Value < cDB_CPAP_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Auto apnea flag writing by DB_WriteDataInEepAndRam function call 	*/
      DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[AUTO_APNEA_SELECT_U16],
										TRUE);
		Function_Result = TRUE;
   }			
/*%C If "Auto apnea flag" activated => "Auto apnea flag" cancelled */
	else if (EEP_DB_CPAP_Adjust[AUTO_APNEA_SELECT_U16] == TRUE)
	{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[AUTO_APNEA_SELECT_U16],
										FALSE);										
		Function_Result = TRUE;
	}
/*%C Setting authorized */
   else
   {
      Function_Result = FALSE;
   }

	return(Function_Result);

}
