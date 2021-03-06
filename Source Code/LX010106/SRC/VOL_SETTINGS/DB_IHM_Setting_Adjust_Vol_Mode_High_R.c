/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IHM_Setting_Adjust_Vol_Mode_High_R.c				          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the High_R setting in the Vol mode										*/
/*                                                            				  		*/
/*%C HIGH R [min:10, max:70, step:1, default:OFF:70] 									*/
/*%C HIGH R is include in its own limits(otherwise, value is saturated)   	   */
/*%C CONTROL R <= HIGH R - 5	                       									*/
/*%C If the conditions on Control R is not respected a limit flag is set for, */
/*%C IHM indication and the value is saturated                                */
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
#include "DB_IHM_Setting_Adjust_Vol_Mode_High_R.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_High_R(UWORD16 *Value,
															 UWORD16 Id)
{

/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Id values recuperation from adjust base in vol mode */
   UWORD16 Adjust_Control_R	=     EEP_DB_VOL_Adjust[ADJUST_CONTROL_R_U16];

/*%C If no Insp Sens selected, high R setting is forbidden */
   if (EEP_DB_VOL_Adjust[INSP_SENS_NO_SELECT_U16] == TRUE)
	{
      *Value = EEP_DB_VOL_Adjust[ADJUST_HIGH_R_U16];
/*%C  Limit flag for HMI indication */
		DB_ControlWrite(LIMIT_INSP_SENS_U16,
							 TRUE);
		Function_Result = FALSE;
   }
/*%C Down limit test */
   else if (*Value < cDB_VOL_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Value limited to its min */
      *Value = cDB_VOL_TEST_ADJUST_DB[Id].mini;

		Function_Result = FALSE;
   }
/*%C Limit tests */
   else if (*Value < Adjust_Control_R + cAlarmRHysteresis)
   {
/*%C  Value limited to its min */
      *Value = Adjust_Control_R + cAlarmRHysteresis;
/*%C  Limit flag for HMI indication */
		DB_ControlWrite(LIMIT_CONTROL_R_U16,
							 TRUE);

		Function_Result = FALSE;
   }
   else if (*Value > cDB_VOL_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_VOL_TEST_ADJUST_DB[Id].maxi;
/*%C  No select flag writing */
		DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[HIGH_R_NO_SELECT_U16],
										TRUE);
		Function_Result = FALSE;
   }			
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_VOL_Adjust[HIGH_R_NO_SELECT_U16] == TRUE)
	{
		DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[HIGH_R_NO_SELECT_U16],
										FALSE);
/*%C  Limit flag desactivation */
		DB_ControlWrite(LIMIT_CONTROL_R_U16,
							 FALSE);
/*%C  Limit flag for HMI indication */
		DB_ControlWrite(LIMIT_INSP_SENS_U16,
							 FALSE);
		Function_Result = TRUE;
	}
	else
   {
/*%C  Value in range */
/*%C  Limit flag for HMI indication */
		DB_ControlWrite(LIMIT_INSP_SENS_U16,
							 FALSE);
		Function_Result = FALSE;
   }

	return(Function_Result);
}
