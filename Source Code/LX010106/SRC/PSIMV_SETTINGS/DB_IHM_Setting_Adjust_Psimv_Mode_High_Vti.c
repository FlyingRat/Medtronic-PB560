/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psimv_Mode_High_Vti.c	          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the High Vti setting in the Psimv mode  								*/
/*                                                            				  		*/
/*%C HIGH VTI [min:80, max:3000, step:10, default:2000] 	    						*/
/*%C HIGH VTI is include in its own limits(otherwise, value is saturated)	   */
/*%C HIGH VTI >= LOW VTI + 20 ml       									            */
/*%C If the conditions on Low Vti is not respected, a limit flag is	set for  */
/*%C IHM indication and the value is saturated                                */
/*%C If the Low Vti is set to No, the low Vti is refreshed with the high Vti  */
/*%C conditions                                                               */
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
#include "DB_IHM_Setting_Adjust_Psimv_Mode_High_Vti.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_High_Vti(UWORD16 *Value,
															     UWORD16 Id)
{

/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Id values recuperation from adjust base in psimv mode */
   UWORD16 Adjust_Low_Vti = EEP_DB_PSIMV_Adjust[ADJUST_LOW_VTI_U16];
   
/*%C Limit tests */
   if (*Value < cDB_PSIMV_TEST_ADJUST_DB[Id].mini)
	{
		Function_Result = TRUE;
	}
  else if (*Value > cDB_PSIMV_TEST_ADJUST_DB[Id].maxi)
	{
/*%C  High Vti No select flag writing  	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[HIGH_VTI_NO_SELECT_U16],
										TRUE);
		Function_Result = TRUE;
	}
/*%C Down limit test */
   else if (*Value < Adjust_Low_Vti + cLowVtiHighVtiHysteresis)
   {
/*%C  If the low Vti value is not set, low Vti = high Vti - 20 */
      if (EEP_DB_PSIMV_Adjust[LOW_VTI_NO_SELECT_U16] == FALSE)
      {
/*%C     => Low vti flag for IHM indication */
		   DB_ControlWrite(LIMIT_LOW_VTI_U16,
							   TRUE);
		   Function_Result = TRUE;
      }
   }
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_PSIMV_Adjust[HIGH_VTI_NO_SELECT_U16] == TRUE)
	{
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[HIGH_VTI_NO_SELECT_U16],
										FALSE);
/*%C  Low vti flag desactivation */
		DB_ControlWrite(LIMIT_LOW_VTI_U16,
							 FALSE);
		Function_Result = TRUE;
	}
   else
   {
/*%C  Setting authorized */
/*%C  Low vti flag desactivation */
		DB_ControlWrite(LIMIT_LOW_VTI_U16,
							 FALSE);

      Function_Result = FALSE;
   }

	return(Function_Result);
}
