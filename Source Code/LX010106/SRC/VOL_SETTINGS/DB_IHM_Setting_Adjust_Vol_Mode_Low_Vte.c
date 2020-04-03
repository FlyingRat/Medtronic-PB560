/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Low_Vte.c		          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Low_Vte setting in the Vol mode										*/
/*                                                            				  		*/
/*%C LOW VTE [min:30, max:2000, step:10, default:OFF=300]  							*/
/*%C LOW VTE is include in its own limits(otherwise, value is saturated)	   */
/*%C LOW VTE <= VOL CONTROL -10                                               */
/*%C If the conditions on Low Vte is not respected, the value is saturated 	*/
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
#include "DB_IHM_Setting_Adjust_Vol_Mode_Low_Vte.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Low_Vte(UWORD16 *Value,
															  UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Id value recovery from adjust base in vol mode */
   UWORD16 Adjust_Vol_Control	= EEP_DB_VOL_Adjust[ADJUST_VOL_CONTROL_U16];

/*%C Up and down limit test											*/
   if (*Value < cDB_VOL_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[LOW_VTE_NO_SELECT_U16],
										TRUE);
		Function_Result = TRUE;
   }
   else if (*Value > cDB_VOL_TEST_ADJUST_DB[Id].maxi)
   {
		Function_Result = TRUE;
   }
   else if (*Value > Adjust_Vol_Control - cVolControlLowVteHysteresis)
   {
/*%C  Vol Control limit flag activation */
		DB_ControlWrite(LIMIT_VOL_CONTROL_U16,
							 TRUE);
		Function_Result = TRUE;
   }			
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_VOL_Adjust[LOW_VTE_NO_SELECT_U16] == TRUE)
	{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[LOW_VTE_NO_SELECT_U16],
										FALSE);
/*%C  Vol Control limit flag activation */
		DB_ControlWrite(LIMIT_VOL_CONTROL_U16,
							 FALSE);
		Function_Result = TRUE;
	}
/*%C  Value in range  */
   else
   {
/*%C  Vol Control limit flag activation */
		DB_ControlWrite(LIMIT_VOL_CONTROL_U16,
							 FALSE);
		Function_Result = FALSE;
   }
   return(Function_Result);
}
