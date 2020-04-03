/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psimv_Mode_High_Vm.c		          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the High_Vm setting in the Psimv mode 									*/
/*                                                            				  		*/
/*%C HIGH VM [min:20, max:990, step:5, default:OFF=90] 								*/
/*%C HIGH VM is include in its own limits(otherwise, value is saturated)   	*/
/*%C HIGH VM >= LOW VM + 10 dlpm                   									*/
/*%C If the condition on Low Vm is not respected, a limit flag is	set         */
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
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Adjust_Psimv_Mode_High_Vm.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_High_Vm(UWORD16 *Value,
														    	 UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Id values recuperation from adjust base in psimv mode */
   UWORD16 Adjust_Low_Vm = EEP_DB_PSIMV_Adjust[ADJUST_LOW_VM_U16];

/*%C Limit tests */
   if (*Value < cDB_PSIMV_TEST_ADJUST_DB[Id].mini)
	{
	   Function_Result = TRUE;
	}
   else if (*Value > cDB_PSIMV_TEST_ADJUST_DB[Id].maxi)
	{
/*%C  High Vm No select flag writing  	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[HIGH_VM_NO_SELECT_U16],
										TRUE);
	   Function_Result = TRUE;
	}
/*%C Dependence test between high and low Vm */
   else if (*Value < Adjust_Low_Vm + cLowVmHighVmHysteresis)
   {
	   if (EEP_DB_PSIMV_Adjust[LOW_VM_NO_SELECT_U16] == FALSE)
      {
/*%C     Value out of range,        */
         *Value = (Adjust_Low_Vm + cLowVmHighVmHysteresis);
/*%C     => Low vm flag for IHM indication */
		   DB_ControlWrite(LIMIT_LOW_VM_U16,
							   TRUE);
      }
	   Function_Result = FALSE;
   }
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_PSIMV_Adjust[HIGH_VM_NO_SELECT_U16] == TRUE)
	{
		DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[HIGH_VM_NO_SELECT_U16],
										FALSE);
/*%C  Low vm flag desactivation */
		DB_ControlWrite(LIMIT_LOW_VM_U16,
							 FALSE);
		Function_Result = TRUE;
	}
   else
   {
/*%C  Setting authorized */
/*%C  Low vm flag desactivation */
		DB_ControlWrite(LIMIT_LOW_VM_U16,
							 FALSE);

      Function_Result = FALSE;
   }
	
   return(Function_Result);
}
