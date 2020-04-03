/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psimv_Mode_Low_Vte.c		          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Low_Vte setting in the Psimv mode 									*/
/*                                                            				  		*/
/*%C LOW VTE [min:30, max:2000, step:10, default:OFF=300]  							*/
/*%C LOW VTE is include in its own limits(otherwise, value is saturated)	   */
/*%C LOW VTE <= HIGH VTE - 20	   															*/
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
#include "DB_IHM_Setting_Adjust_Psimv_Mode_Low_Vte.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Low_Vte(UWORD16 *Value,
															    UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;
   UWORD16 Adjust_High_Vte	= EEP_DB_PSIMV_Adjust[ADJUST_HIGH_VTE_U16];

/*%C Limit tests */
   if (*Value < cDB_PSIMV_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Low Vte No select flag writing  	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[LOW_VTE_NO_SELECT_U16],
										TRUE);
		Function_Result = TRUE;
	}
   else if (*Value > cDB_PSIMV_TEST_ADJUST_DB[Id].maxi)
   {
		Function_Result = TRUE;
	}
/*%C Up limit test */
   else if (*Value > Adjust_High_Vte - cLowVteHighVteHysteresis)
   {
/*%C  If the high Vte value is not set, high Vte = low Vte + 20 */
      if (EEP_DB_PSIMV_Adjust[HIGH_VTE_NO_SELECT_U16] == FALSE)
      {
/*%C     => High vti flag for IHM indication */
		   DB_ControlWrite(LIMIT_HIGH_VTE_U16,
							   TRUE);
		   Function_Result = TRUE;
      }
   }
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_PSIMV_Adjust[LOW_VTE_NO_SELECT_U16] == TRUE)
	{
/*%C  Low Vte No select flag writing in RAM and EEPROM 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[LOW_VTE_NO_SELECT_U16],
										FALSE);										
/*%C  High vte flag desactivation */
		DB_ControlWrite(LIMIT_HIGH_VTE_U16,
							 FALSE);
		Function_Result = TRUE;
	}
/*%C  Value in range  */
   else
   {
/*%C  High vte flag desactivation */
		DB_ControlWrite(LIMIT_HIGH_VTE_U16,
							 FALSE);
		Function_Result = FALSE;
   }

   return(Function_Result);
}
