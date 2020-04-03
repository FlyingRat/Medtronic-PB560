/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Peep.c 			         		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Peep setting in the Vol mode											*/
/*                                                            				  		*/
/*%C PEEP [min:0, max:200, step:10, default:0]             							*/
/*%C PEEP is include in its own limits(otherwise, value is saturated)	      */
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
#include "DB_Config.h"
#include "DB_Current.h"
#include "DB_IhmAccessParaDataBase.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Peep(UWORD16 *Value,
														  UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Up and down limit test											*/
/*   *Value non signé, il passe donc de 0 au max de son type         */
/*   => fixé à la valeur min de la PEEP                              */
   if ( (*Value <= cDB_VOL_TEST_ADJUST_DB[Id].mini)
     || (*Value > cDB_VOL_TEST_ADJUST_DB[Id].maxi +
                  cDB_VOL_TEST_ADJUST_DB[Id].step) )
   {
/*%C  Value limited to its min */
      *Value = cDB_VOL_TEST_ADJUST_DB[Id].mini;
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[PEEP_NO_SELECT_U16],
										TRUE);
		Function_Result = FALSE;
   }
   else if (*Value >= cDB_VOL_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_VOL_TEST_ADJUST_DB[Id].maxi;
		Function_Result = FALSE;
   }			
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_VOL_Adjust[PEEP_NO_SELECT_U16] == TRUE)
	{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[PEEP_NO_SELECT_U16],
										FALSE);
		Function_Result = FALSE;
	}
	else
   { 
/*%C  Value in range  */
      Function_Result = FALSE;
   }

	return(Function_Result);
}
