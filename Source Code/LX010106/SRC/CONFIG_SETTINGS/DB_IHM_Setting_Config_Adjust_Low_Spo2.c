/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Config_Adjust_Low_Spo2.c   	     					*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Low Spo2 setting in the Config base      						*/
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
#include "define.h"
#include "DRV_VarEeprom.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Config_Adjust_Low_Spo2.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Config_Adjust_Low_Spo2(UWORD16 *Value,
															 UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;
   UWORD16 MeasureSpo2 = DB_ComputeRead(MEASURE_SPO2_U16);

/*%C Limit tests */
/*%C Down Limit test */
   if ( (*Value < cDB_TEST_CONFIG_DB[Id].mini)
	  || (*Value > cDB_TEST_CONFIG_DB[Id].maxi) )
	{
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_Config[SPO2_LOW_SELECT],
										FALSE);
		Function_Result = TRUE;
	}
/*%C Up Limit test */
   else if (*Value > MeasureSpo2 + cDELTA_LOW_SPO2)
   {
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_Config[SPO2_LOW_SELECT],
										FALSE);
		DB_ControlWrite(LIMIT_SPO2, TRUE);
		Function_Result = TRUE;
   }
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_Config[SPO2_LOW_SELECT] == FALSE)
	{
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_Config[SPO2_LOW_SELECT],
										TRUE);
		DB_ControlWrite(LIMIT_SPO2, FALSE);
		Function_Result = TRUE;
	}
   else
   {
/*%C  Setting authorized */
      Function_Result = FALSE;
   }

	return(Function_Result);
}
