/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vsimv_Mode_Low_Vm.c 		          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Low_Vm setting in the Vsimv mode									*/
/*                                                            				  		*/
/*%C LOW VM [min:5, max:500, step:5, default:OFF=40]      							*/
/*%C LOW VM is include in its own limits(otherwise, value is saturated)		   */
/*%C LOW VM < (10 * VOL CONTROL x SIMV BACKUP R) /1000                        */
/*%C LOW VM <= HIGH VM - 10 dlpm         									            */
/*%C If the conditions on High Vm, Vol Control or SIMV BACKUP R are not       */
/*%C respected, a limit flag is	set for IHM indication and the value is      */
/*%C saturated                                                                */
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
#include "DB_IHM_Setting_Adjust_Vsimv_Mode_Low_Vm.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Vsimv_Mode_Low_Vm(UWORD16 *Value,
															   UWORD16 Id)
{

/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Id values recuperation from adjust base in pres mode */
   UWORD16 Adjust_High_Vm = EEP_DB_VSIMV_Adjust[ADJUST_HIGH_VM_U16];

/*%C Up and down limit test											*/
   if (*Value < cDB_VSIMV_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[LOW_VM_NO_SELECT_U16],
										TRUE);
		Function_Result = TRUE;
   }
   else if (*Value > cDB_VSIMV_TEST_ADJUST_DB[Id].maxi)
   {
		Function_Result = TRUE;
   }
/*%C Dependence test between high and low Vm */
   else if (*Value > Adjust_High_Vm - cLowVmHighVmHysteresis)
   {
	   if (EEP_DB_VSIMV_Adjust[HIGH_VM_NO_SELECT_U16] == FALSE)
      {
/*%C     Value out of range,        */
/*%C     => value robustness        */
         *Value = (Adjust_High_Vm - cLowVmHighVmHysteresis);
/*%C     => Low vm flag for IHM indication */
		   DB_ControlWrite(LIMIT_HIGH_VM_U16,
							   TRUE);
      }
	   Function_Result = FALSE;
   }
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_VSIMV_Adjust[LOW_VM_NO_SELECT_U16] == TRUE)
	{
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[LOW_VM_NO_SELECT_U16],
										FALSE);
/*%C  High Vm flag desactivation */
		DB_ControlWrite(LIMIT_HIGH_VM_U16,
							 FALSE);
/*%C  Vol Control and Control R flag desactivation */
		DB_ControlWrite(LIMIT_VOL_CONTROL_U16,
							 FALSE);
		DB_ControlWrite(LIMIT_CONTROL_R_U16,
							 FALSE);
		Function_Result = TRUE;
	}
   else
   {
/*%C  Setting authorized */
/*%C  High Vm flag desactivation */
		DB_ControlWrite(LIMIT_HIGH_VM_U16,
							 FALSE);
/*%C  Vol Control and Control R flag desactivation */
		DB_ControlWrite(LIMIT_VOL_CONTROL_U16,
							 FALSE);
		DB_ControlWrite(LIMIT_CONTROL_R_U16,
							 FALSE);

      Function_Result = FALSE;
   }

	return(Function_Result);
}
