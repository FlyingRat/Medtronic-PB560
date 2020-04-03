/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psv_Mode_Backup_R.c      	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Backup R setting in the Psv mode	     							*/
/*                                                            				  		*/
/*%C BACKUP R [min:4, max:40, step:1, default:4 = OFF]           					*/
/*%C BACKUP R is include in its own limits(otherwise, value is saturated)     */
/*%C 30 / BACKUP R <= APNEA TIME	        							      				*/
/*                                                            				  		*/
/*%C If the condition on APNEA TIME is not respected, a limit flag            */
/*%C is set for IHM indication and the value is saturated                     */
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
#include "DB_IHM_Setting_Adjust_Psv_Mode_Backup_R.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Backup_R(UWORD16 *Value,
																UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;

	UWORD16 Adjust_Apnea = EEP_DB_PSV_Adjust[ADJUST_APNEA_U16];


/*%C Limit tests */
/*%C Down Limit test */
   if (*Value < cDB_PSV_TEST_ADJUST_DB[Id].mini)			
	{
/*%C  Value limited to its min */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].mini;

		Function_Result = FALSE;
	}
/*%C Up Limit test */
   else if (*Value > cDB_PSV_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].maxi;
      Function_Result = FALSE;
   }
   else
   {
/*%C  Limit flag desactivation */
		DB_ControlWrite(LIMIT_APNEA_U16, FALSE);
/*%C  Setting authorized */
      Function_Result = FALSE;
   }

	return(Function_Result);
}
