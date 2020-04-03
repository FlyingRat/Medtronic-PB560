/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vsimv_Mode_Rise_Time.c   	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Rise Time setting in the Vsimv mode	     							*/
/*                                                            				  		*/
/*%C RISE TIME [min:1, max:4, step:1, default:2]                					*/
/*%C RISE TIME is include in its own limits(otherwise, value is saturated)    */
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

UWORD16 DB_IHM_Setting_Adjust_Vsimv_Mode_Rise_Time(UWORD16 *Value,
																  UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;
 
/*%C Limit tests */
/*%C Up and down limit test											*/
   if (*Value < cDB_VSIMV_TEST_ADJUST_DB[Id].mini)
	{
/*%C  Value limited to its min */
	   *Value = cDB_VSIMV_TEST_ADJUST_DB[Id].maxi;
		Function_Result = FALSE;
	}
   else if (*Value > cDB_VSIMV_TEST_ADJUST_DB[Id].maxi)
	{
/*%C  Value limited to its max */
	   *Value = cDB_VSIMV_TEST_ADJUST_DB[Id].mini;   
		Function_Result = FALSE;
   }
   else
   {
/*%C  Setting authorized */
      Function_Result = FALSE;
   }

	return(Function_Result);
}
