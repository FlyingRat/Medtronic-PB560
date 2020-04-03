/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psimv_Mode_High_Vte.c	          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the High Vte setting in the Psimv mode									*/
/*                                                            				  		*/
/*%C HIGH VTE [min:80, max:3000, step:10, default:OFF=700]   						*/
/*%C HIGH VTE is include in its own limits(otherwise, value is saturated)	   */
/*%C HIGH VTE > LOW VTE + 20                                                  */
/*%C If the conditions on High Vte is not respected, the value is saturated 	*/
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
#include "DB_IHM_Setting_Adjust_Psimv_Mode_High_Vte.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_High_Vte(UWORD16 *Value,
															     UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Id value recovery from adjust base in vol mode */
   UWORD16 Adjust_Low_Vte	= EEP_DB_PSIMV_Adjust[ADJUST_LOW_VTE_U16];

/*%C Up and down limit test											*/
/*%C Down limit test */
   if (*Value < cDB_PSIMV_TEST_ADJUST_DB[Id].mini)
   {
		Function_Result = TRUE;
   }
   else if (*Value > cDB_PSIMV_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[HIGH_VTE_NO_SELECT_U16],
										TRUE);
		Function_Result = TRUE;
   }
   else if (*Value < Adjust_Low_Vte + cLowVteHighVteHysteresis)
   {
/*%C  If the low Vte value is not set, low Vte = high Vte - 20 */
      if (EEP_DB_PSIMV_Adjust[LOW_VTE_NO_SELECT_U16] == FALSE)
      {
/*%C     => Low vte flag for IHM indication */
		   DB_ControlWrite(LIMIT_LOW_VTE_U16,
							   TRUE);
		   Function_Result = TRUE;
      }
   }
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_PSIMV_Adjust[HIGH_VTE_NO_SELECT_U16] == TRUE)
	{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[HIGH_VTE_NO_SELECT_U16],
										FALSE);
/*%C  Low vte flag desactivation */
		DB_ControlWrite(LIMIT_LOW_VTE_U16,
							 FALSE);
		Function_Result = TRUE;
	}
/*%C  Value in range  */
   else
   {
/*%C  Low vte flag desactivation */
		DB_ControlWrite(LIMIT_LOW_VTE_U16,
							 FALSE);
		Function_Result = FALSE;
   }
   return(Function_Result);
}
