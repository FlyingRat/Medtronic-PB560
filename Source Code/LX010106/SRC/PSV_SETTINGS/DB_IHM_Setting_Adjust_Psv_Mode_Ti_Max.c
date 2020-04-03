/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psv_Mode_Ti_Max.c        	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Ti max setting in the Psv mode	        							*/
/*                                                            				  		*/
/*%C Ti max [min:800, max:3000, step:100, default:3000]          					*/
/*%C Apnea Time is include in its own limits(otherwise, value is saturated)   */
/*%C TI_MIN <= TI_MAX                                                         */
/*%C The automatic mode is reached by the up key, a flag is set in this case  */
/*%C and the value is saturated                                               */
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
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DRV_VarEeprom.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Adjust_Psv_Mode_Ti_Max.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Ti_Max(UWORD16 *Value,
                                              UWORD16 Id)
{
/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/* Id values recuperation from adjust base in psv mode */
   UWORD16 Adjust_Ti_Min   = EEP_DB_PSV_Adjust[ADJUST_TI_MIN_U16];
   UWORD16 Ti_Min_Auto_Select   = EEP_DB_PSV_Adjust[TI_MIN_AUTO_SELECT_U16];

/*%C Limit tests */
/*%C Down limit test */
   if (*Value < cDB_PSV_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Value limited to its min */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].mini;
		Function_Result = FALSE;
   }
/*%C Up limit test */
   else if (*Value > cDB_PSV_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].maxi;
/*%C  Auto ti min flag writing by DB_WriteDataInEepAndRam function call 	*/
      DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[TI_MAX_AUTO_SELECT_U16],
										TRUE);
		Function_Result = FALSE;
   }
/*%C Dependence test between Ti min and Ti max */
	else if (*Value < Adjust_Ti_Min)
	{
      if (Ti_Min_Auto_Select == FALSE)
      {
/*%C     Value out of range,        */
/*%C     => value saturation        */
         *Value = Adjust_Ti_Min;
/*%C     => Ti max flag for IHM indication */
		   DB_ControlWrite(LIMIT_TI_MIN_U16,
							   TRUE);
      }
		Function_Result = FALSE;
	}
/*%C If "Auto ti min flag" activated => "Auto ti min flag" cancelled */
	else if (EEP_DB_PSV_Adjust[TI_MAX_AUTO_SELECT_U16] == TRUE)
	{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[TI_MAX_AUTO_SELECT_U16],
										FALSE);
		Function_Result = TRUE;
	}
   else
   {
/*%C  Setting authorized, Ti min flag desactivation */
		DB_ControlWrite(LIMIT_TI_MIN_U16,
							 FALSE);
      Function_Result = FALSE;
   }

	return(Function_Result);
}
