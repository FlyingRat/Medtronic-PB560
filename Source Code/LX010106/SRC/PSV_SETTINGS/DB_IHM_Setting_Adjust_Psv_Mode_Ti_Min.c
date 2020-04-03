/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psv_Mode_Ti_Min.c        	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Ti min setting in the Psv mode	        							*/
/*                                                            				  		*/
/*%C Ti min [min:100, max:3000, step:100, default:600]           					*/
/*%C Apnea Time is include in its own limits(otherwise, value is saturated)   */
/*%C Automatic mode is reached by the down key, in this mode the Ti min       */
/*%C value is : adjust rise time + 300ms                                      */
/*%C In this function, just the auto flag is set, and the value is written in */
/*%C the DB_IHM_Write_Adjust_Psv_Mode_Ti_Min function                         */
/*                                                            				  		*/
/*%C Ti Min <= 1000 * (60 * 1/2) / Backup R                                   */
/*%C Ti Min <= Ti max                                                         */
/*%C If the conditions on Backup R or Ti max are not respected, a flag is set */
/*%C for IHM indication and the value is saturated                            */
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
#include "DB_IHM_Setting_Adjust_Psv_Mode_Ti_Min.h" 

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Ti_Min(UWORD16 *Value,
															 UWORD16 Id)
{
/* Function result declaration */
   UWORD16 Function_Result = FALSE;
   UWORD16 Rest = 0;

/* Id values recuperation from adjust base in psv mode */
   UWORD16 Adjust_Backup_R = EEP_DB_PSV_Adjust[ADJUST_BACKUP_R_U16];
   UWORD16 Adjust_Ti_Max   = EEP_DB_PSV_Adjust[ADJUST_TI_MAX_U16];
   UWORD16 Ti_Max_Auto_Select   = EEP_DB_PSV_Adjust[TI_MAX_AUTO_SELECT_U16];

   if (*Value < cDB_PSV_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Value limited to its min */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].mini;
/*%C  Auto ti min flag writing by DB_WriteDataInEepAndRam function call 	*/
      DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[TI_MIN_AUTO_SELECT_U16],
										TRUE);
		Function_Result = FALSE;
   }			
/*%C Limit tests */
   else if (*Value > cDB_PSV_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].maxi;
		Function_Result = FALSE;
   }
/*%C Dependence test between Ti min and backup R */
	else if (*Value > cTiMinCoeff / Adjust_Backup_R)
	{
/*%C  Value out of range,        */
/*%C  => value saturation        */
      *Value = (cTiMinCoeff / Adjust_Backup_R);
/*%C  Rounded to 100ms        */
      Rest = *Value % 100;
      *Value = *Value - Rest;
/*%C  => Backup R flag for IHM indication */
		DB_ControlWrite(LIMIT_BACKUP_R_U16,
							 TRUE);
		Function_Result = FALSE;
	}
/*%C Dependence test between Ti min and Ti max */
	else if (*Value > Adjust_Ti_Max)
	{
      if (Ti_Max_Auto_Select == FALSE)
      {
/*%C     Value out of range,        */
/*%C     => value saturation        */
         *Value = Adjust_Ti_Max;
/*%C     => Ti max flag for IHM indication */
		   DB_ControlWrite(LIMIT_TI_MAX_U16,
							   TRUE);
      }
		Function_Result = FALSE;
	}
/*%C If "Auto ti min flag" activated => "Auto ti min flag" cancelled */
	else if (EEP_DB_PSV_Adjust[TI_MIN_AUTO_SELECT_U16] == TRUE)
	{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[TI_MIN_AUTO_SELECT_U16],
										FALSE);
		Function_Result = TRUE;
	}
   else
   {
/*%C  Setting authorized, Backup R and Ti max limit flag desactivation */
		DB_ControlWrite(LIMIT_BACKUP_R_U16,
							 FALSE);
		DB_ControlWrite(LIMIT_TI_MAX_U16,
							 FALSE);
      Function_Result = FALSE;
   }

	return(Function_Result);
}
