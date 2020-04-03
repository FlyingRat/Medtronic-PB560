/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psimv_Mode_Apnea_Time.c   	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Apnea Time setting in the Psimv mode    							*/
/*                                                            				  		*/
/*%C Apnea Time (ms) [min:1000, max:60000, step:1000, default:30000]          */
/*%C Apnea Time is include in its own limits(otherwise, value is saturated)   */
/*%C Automatic mode is reached by the down key, in this mode the apnea time   */
/*%C value is 12 sec							                                       */
/*%C Automatic mode is also reached when apnea time < 2 * Ti Control	   */
/*%C A limit flag is set in this case									   */
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
#include "DB_IHM_Setting_Adjust_Psimv_Mode_Apnea_Time.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Apnea_Time(UWORD16 *Value,
																    UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;
   UWORD16 Adjust_Ti_Control = EEP_DB_PSIMV_Adjust[ADJUST_TI_CONTROL_U16];

/*%C Limit tests */
/*%C Up Limit */
   if (*Value > cDB_PSIMV_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_PSIMV_TEST_ADJUST_DB[Id].maxi;
		Function_Result = FALSE;
   }
/*%C Down Limit */
   else if (*Value < cDB_PSIMV_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Value limited to its min */
      *Value = cDB_PSIMV_TEST_ADJUST_DB[Id].mini;
/*%C  Auto apnea flag writing by DB_WriteDataInEepAndRam function call 	*/
      DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[AUTO_APNEA_SELECT_U16],
										TRUE);
		Function_Result = FALSE;
   }			
   else if (*Value <  2 * Adjust_Ti_Control)
   {

		DB_ControlWrite(LIMIT_TI_CONTROL_U16,TRUE);
		if ( (Adjust_Ti_Control * 2) %1000 != 0)
		{
		 	*Value = (((Adjust_Ti_Control * 2) /1000) + 1) * 1000;
		}
		else
		{
		 	*Value = Adjust_Ti_Control * 2;
		}
/*%C  Auto apnea flag writing by DB_WriteDataInEepAndRam function call 	*/
      DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[AUTO_APNEA_SELECT_U16],
										TRUE);
		Function_Result = FALSE;
   }			
/*%C If "Auto apnea flag" activated => "Auto apnea flag" cancelled */
	else if (EEP_DB_PSIMV_Adjust[AUTO_APNEA_SELECT_U16] == TRUE)
	{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[AUTO_APNEA_SELECT_U16],
										FALSE);										
      	DB_ControlWrite(LIMIT_TI_CONTROL_U16,FALSE);
		Function_Result = TRUE;
	}
   else
   {
      Function_Result = FALSE;
   }
	  
	return(Function_Result);
}
