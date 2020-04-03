/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Cpap_Mode_Low_Vti.c 		          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Low_Vti setting in the Cpap mode  									*/
/*                                                            				  		*/
/*%C LOW VTI [min:30, max:2000, step:10, default:30 = OFF]    						*/
/*%C LOW VTI is include in its own limits(otherwise, value is saturated)	   */
/*%C LOW VTI <= HIGH VTI - 20 ml       									            */
/*%C If the conditions on High Vti is not respected, a limit flag is	set for  */
/*%C IHM indication and the value is saturated                                */
/*%C If the High Vti is set to No, the high Vti is refreshed with the low Vti */
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
#include "DB_IHM_Setting_Adjust_Cpap_Mode_Low_Vti.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Cpap_Mode_Low_Vti(UWORD16 *Value,
															  UWORD16 Id)
{

/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Id values recuperation from adjust base in Cpap  mode */
   UWORD16 Adjust_High_Vti = EEP_DB_CPAP_Adjust[ADJUST_HIGH_VTI_U16];
   
/*%C Limit tests */
/*%C Down limit test */
   if (*Value < cDB_CPAP_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Low Vti writing by DB_WriteDataInEepAndRam function call 	*/
      DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[LOW_VTI_NO_SELECT_U16],
										TRUE);
		Function_Result = TRUE;
   }
   else if (*Value > cDB_CPAP_TEST_ADJUST_DB[Id].maxi)
   {
		Function_Result = TRUE;
   }
/*%C Up limit test */
   else if (*Value > Adjust_High_Vti - cLowVtiHighVtiHysteresis)
   {
/*%C  If the high Vti value is not set, high Vti = low Vti + 20 */
/*%C     => High vti flag for IHM indication */
	        DB_ControlWrite(LIMIT_HIGH_VTI_U16,
				   TRUE);
		Function_Result = TRUE;
   }
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_CPAP_Adjust[LOW_VTI_NO_SELECT_U16] == TRUE)
	{
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[LOW_VTI_NO_SELECT_U16],
										FALSE);
/*%C  High vti flag desactivation */
		DB_ControlWrite(LIMIT_HIGH_VTI_U16,
							 FALSE);
		Function_Result = TRUE;
	}
   else
   {
/*%C  Setting authorized */
/*%C  High vti flag desactivation */
		DB_ControlWrite(LIMIT_HIGH_VTI_U16,
							 FALSE);

      Function_Result = FALSE;
   }

	return(Function_Result);
}
