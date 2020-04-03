/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Pres_Mode_High_Leak.c           			*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the High leak setting in the Pres mode  	   						*/
/*                                                            				  		*/
/*%C HIGH LEAK [min:0 = OFF, max:200, step:5, default:0]      						*/
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

UWORD16 DB_IHM_Setting_Adjust_Pres_Mode_High_Leak(UWORD16 *Value,
															   UWORD16 Id)
{

/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Limit tests */
/*%C Down limit test */
/*%C Up limit test */
   if (*Value < cDB_PRES_TEST_ADJUST_DB[Id].mini)
   {
		Function_Result = TRUE;
   }
   else if (*Value > cDB_PRES_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  High leak flag writing by DB_WriteDataInEepAndRam function call 	*/
       DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[HIGH_LEAK_SELECT_U16],
										FALSE);
		Function_Result = TRUE;
   }
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_PRES_Adjust[HIGH_LEAK_SELECT_U16] == FALSE)
	{
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[HIGH_LEAK_SELECT_U16],
										TRUE);
		Function_Result = TRUE;
	}
   else
   {
/*%C  Setting authorized */
      Function_Result = FALSE;
   }
	return(Function_Result);
}
