/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psv_Mode_Insp_Sens.c		          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Insp sens setting in the Psv mode									*/
/*                                                            				  		*/
/*%C INSP SENS [min:1, max:5, step:1, default:2]         							*/
/*%C INSP SENS is include in its own limits(otherwise, value is saturated)		*/
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

UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Insp_Sens(UWORD16 *Value,
																 UWORD16 Id)
{
/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Limit tests */
/*%C Down limit test */
   if (*Value < cDB_PSV_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Value limited to its min */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].maxi;
		Function_Result = FALSE;
   }
/*%C Up limit test */
   else if (*Value > cDB_PSV_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].mini;
		Function_Result = FALSE;
   }
/*%C Setting in range 	*/
   else
   {
		Function_Result = FALSE;
   }

   return(Function_Result);
}
