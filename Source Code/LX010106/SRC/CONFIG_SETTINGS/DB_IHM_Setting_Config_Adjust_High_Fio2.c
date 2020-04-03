/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Config_Adjust_High_Fio2.c   	     				*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Low Fio2 setting in the Config base     							*/
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
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Config_Adjust_High_Fio2.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Config_Adjust_High_Fio2(UWORD16 *Value,
															 UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;
   UWORD16 AdjustLowFio2 = DB_ConfigRead(ADJUST_LOW_FIO2);
	UWORD16 DetectedFio2Sensor= DB_ControlRead(DETECTED_FIO2_SENSOR);

/*%C Down Limit test */
   if (*Value < cDB_TEST_CONFIG_DB[Id].mini)
	{
		Function_Result = TRUE;
	}
/*%C Up Limit test */
   else if (*Value > cDB_TEST_CONFIG_DB[Id].maxi)
	{
		if	(DetectedFio2Sensor == FALSE)
		{
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
			DB_WriteDataInEepAndRam(&EEP_DB_Config[FIO2_HIGH_SELECT],
											FALSE);
		}
		Function_Result = TRUE;
	}
/*%C Limit tests */
   else if (*Value < AdjustLowFio2 + cDeltaHighLowFio2)
	{
		DB_ControlWrite(LIMIT_LOW_FIO2, TRUE);
		Function_Result = TRUE;
	}
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_Config[FIO2_HIGH_SELECT] == FALSE)
	{
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_Config[FIO2_HIGH_SELECT],
										TRUE);
/*%C  Limit Flag writing For HMI indication 	*/
		DB_ControlWrite(LIMIT_LOW_FIO2, FALSE);
		Function_Result = TRUE;
	}
   else
   {
/*%C  Limit Flag writing For HMI indication 	*/
		DB_ControlWrite(LIMIT_LOW_FIO2, FALSE);
/*%C  Setting authorized */
      Function_Result = FALSE;
   }

	return(Function_Result);
}
