/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psv_Mode_Low_Vte.c		          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Low_Vte setting in the Psv mode  									*/
/*                                                            				  		*/
/*%C LOW VTE [min:30, max:2000, step:10, default:OFF=300]  							*/
/*%C LOW VTE is include in its own limits(otherwise, value is saturated)	   */
/*%C LOW VTE < HIGH VTE - 20                                            	   */
/*%C LOW VTE < TARGET VT - 10                                            	   */
/*%C If the conditions on High Vte or target VT are not respected, limit flags*/
/*%C are	set for IHM indication, and the values are saturated                 */
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
#include "DB_IHM_Setting_Adjust_Psv_Mode_Low_Vte.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Low_Vte(UWORD16 *Value,
															   UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;
   UWORD16 Adjust_High_Vte	= EEP_DB_PSV_Adjust[ADJUST_HIGH_VTE_U16];
   UWORD16 Adjust_Target_Vt = EEP_DB_PSV_Adjust[ADJUST_TARGET_VT_U16];
   UWORD16 Target_Vt_Select = EEP_DB_PSV_Adjust[TARGET_VT_SELECT_U16];

/*%C Up and down limit test											*/
/*%C If value < min or > max => "no select flag" activated 	*/
   if (*Value < cDB_PSV_TEST_ADJUST_DB[Id].mini)
	{
/*%C  No select flag indication */
		DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[LOW_VTE_NO_SELECT_U16],
										TRUE);
		Function_Result = TRUE;
	}
   else if (*Value > cDB_PSV_TEST_ADJUST_DB[Id].maxi)
	{
		Function_Result = TRUE;
	}
/*%C Up limit test */
   else if (*Value > Adjust_High_Vte - cLowVteHighVteHysteresis)
   {
/*%C  If the high Vte value is not set, high Vte = low Vte + 20 */
      if (EEP_DB_PSV_Adjust[HIGH_VTE_NO_SELECT_U16] == FALSE)
      {
/*%C     => High vti flag for IHM indication */
		   DB_ControlWrite(LIMIT_HIGH_VTE_U16,
							   TRUE);
		   Function_Result = TRUE;
      }
   }
/*%C Up limit test */
   else if ( (*Value > Adjust_Target_Vt - cLowVteTargetVtHysteresis)
          && (Target_Vt_Select == TRUE) )
   {
/*%C  => Target Vt flag for IHM indication */
	   DB_ControlWrite(LIMIT_TARGET_VT_U16,
						   TRUE);
	   Function_Result = TRUE;
   }
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_PSV_Adjust[LOW_VTE_NO_SELECT_U16] == TRUE)
	{
		DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[LOW_VTE_NO_SELECT_U16],
										FALSE);										
/*%C  High Vte limit flag desactivation */
		DB_ControlWrite(LIMIT_HIGH_VTE_U16,
							 FALSE);
/*%C  Target Vt flag desactivation */
	   DB_ControlWrite(LIMIT_TARGET_VT_U16,
						   FALSE);
		Function_Result = TRUE;
	}
/*%C  Value in range  */
   else
   {
/*%C  High Vte limit flag desactivation */
		DB_ControlWrite(LIMIT_HIGH_VTE_U16,
							 FALSE);
/*%C  => Target Vt flag for IHM indication */
	   DB_ControlWrite(LIMIT_TARGET_VT_U16,
						   FALSE);
		Function_Result = FALSE;
   }

   return(Function_Result);
}
