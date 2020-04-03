/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Psv_Mode_Ti_Max.c           	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new value		*/
/*%C        of the Ti max setting in the Psv mode	        							*/
/*                                                            				  		*/
/*%C In automatic mode the Ti Max is the min between 3s and 30 / Measure R    */
/*%C In normal mode the Ti Max takes the setting value                        */
/*%C If the Ti min no select flag is set and Ti max < Ti min                  */
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
#include "DB_Current.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DRV_VarEeprom.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Write_Adjust_Psv_Mode_Ti_Max.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Ti_Max(UWORD16 *Value)
{

/* Id values recovery from adjust base in psv mode */
   UWORD16 Ti_Max_Auto_Select = EEP_DB_PSV_Adjust[TI_MAX_AUTO_SELECT_U16];
   UWORD16 Adjust_Ti_Min = EEP_DB_PSV_Adjust[ADJUST_TI_MIN_U16];
   UWORD16 Adjust_BackUp_R = EEP_DB_PSV_Adjust[ADJUST_BACKUP_R_U16];

/* Min Ti Max declaration (3000ms)*/
   UWORD16 Ti_Max_Min = cTiMaxmax;

/* Test between 3s and 30 / BackUp_R */
    if (Ti_Max_Min > 30000 / Adjust_BackUp_R)
	{
	   Ti_Max_Min = (30000 / Adjust_BackUp_R);
	}
/* else, keeps its declaration value */

/*%C Automatic mode test */
   if (Ti_Max_Auto_Select == TRUE)
   {
/*%C  Ti Max writing (fixed to min(3s, 30/Measure_R)) */
      DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_TI_MAX_U16],
									   Ti_Max_Min);			
   }
/*%C The Ti Max is written to the setting value : */
	else
	{
      DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_TI_MAX_U16],
								      *Value);
   }

/*%C Ti Min/Max dependance */
   if (*Value < Adjust_Ti_Min)
   {
      DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_TI_MIN_U16],
								      *Value);
   }
/*%C This function always return TRUE */
	return(TRUE);
}
