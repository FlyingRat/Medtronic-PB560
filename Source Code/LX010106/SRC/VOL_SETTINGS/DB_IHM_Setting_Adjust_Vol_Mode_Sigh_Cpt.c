/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Cpt.c 		         		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the sigh cpt setting in the Vol mode	 								*/
/*  					                                            				  		*/
/*%C SIGH CPT [min:50, max:250, step:50, default:50]       							*/
/*%C SIGH CPT is include in its own limits(otherwise, value is saturated)		*/
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

UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Cpt(UWORD16 *Value,
															  UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Limit tests */
   if ( (*Value < cDB_VOL_TEST_ADJUST_DB[Id].mini)
	  || (*Value > cDB_VOL_TEST_ADJUST_DB[Id].maxi)	)
   {
		Function_Result = TRUE;
   }
   else
   {
/*%C 	Setting authorized  */
		Function_Result = FALSE;
   }
	return(Function_Result);
}
