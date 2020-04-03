/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vsimv_Mode_Insp_Sens.c 	  	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages the new Insp 		*/
/*%C        Sens setting:                                                 		*/
/*                                                            				  		*/
/*%C INSP SENS [min:1, max:5, step:1, default:2]         							*/
/*%C INSP SENS is include in its own limits(otherwise, value is saturated)   	*/
/******************************************************************************/
/*%I 	Input Parameter :				*Value                                		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
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

UWORD16 DB_IHM_Setting_Adjust_Vsimv_Mode_Insp_Sens(UWORD16 *Value,
																   UWORD16 Id)
{
/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Limit tests */
   if ((*Value < cDB_VSIMV_TEST_ADJUST_DB[Id].mini) ||
      (*Value == (UWORD16) (cDB_VSIMV_TEST_ADJUST_DB[Id].mini - cDB_VSIMV_TEST_ADJUST_DB[Id].step)))   
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
/*%C Setting in range 	*/
   else
   {
		Function_Result = FALSE;
   }

   return(Function_Result);
}
