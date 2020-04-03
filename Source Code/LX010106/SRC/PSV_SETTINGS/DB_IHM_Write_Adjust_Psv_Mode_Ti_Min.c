/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Psv_Mode_Ti_Min.c           	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new value   	*/
/*%C        of the Ti min setting in the Psv mode	        							*/
/*                                                            				  		*/
/*%C In automatic mode the Ti Min value is value: adjust rise time + 300ms    */
/*%C In the other cases the Ti Min value is given by the value parameter      */
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

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/


UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Ti_Min(UWORD16 *Value)
{

/* Id values recuperation from adjust base in psv mode */
   UWORD16 Adjust_Rise_Time   = EEP_DB_PSV_Adjust[RISE_TIME_U16];
   UWORD16 Ti_Min_Auto_Select = EEP_DB_PSV_Adjust[TI_MIN_AUTO_SELECT_U16];
   UWORD16 Adjust_Ti_Max = EEP_DB_PSV_Adjust[ADJUST_TI_MAX_U16];

/*%C Automatic mode test */
   if (Ti_Min_Auto_Select == TRUE)
   {
/*%C  Ti Min writing (fixed to Adjust Rise Time + 300 ms) */
      DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_TI_MIN_U16],
									   Adjust_Rise_Time + cDeltaRiseTime);			
   }
/*%C The Ti min is written to the setting value : */
	else
	{
      DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_TI_MIN_U16],
								      *Value);						          
   }

/*%C Ti Min/Max dependance */
   if (*Value > Adjust_Ti_Max)
   {
      DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_TI_MAX_U16],
								      *Value);
   }

/*%C This function always returns TRUE */
   return(TRUE);
}
