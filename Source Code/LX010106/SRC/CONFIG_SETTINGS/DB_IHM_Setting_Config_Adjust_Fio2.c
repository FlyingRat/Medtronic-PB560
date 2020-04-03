/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Config_Adjust_Fio2.c      	       				*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Fio2 setting in the Config base		     							*/
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

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Config_Adjust_Fio2(UWORD16 *Value,
														UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Limit tests */
/*%C Down Limit test */
   if (*Value <= cDB_TEST_CONFIG_DB[Id].mini)
	{
/*%C  Value limited to its min */
      *Value = cDB_TEST_CONFIG_DB[Id].mini;
		Function_Result = FALSE;
	}
/*%C Up Limit test */
   else if (*Value >= cDB_TEST_CONFIG_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_TEST_CONFIG_DB[Id].maxi;
      Function_Result = FALSE;
   }
   else
   {
/*%C  Value modulo 5  */
      *Value = *Value - *Value % 5;
	
/*%C  Setting authorized */
      Function_Result = FALSE;
   }

	return(Function_Result);
}
