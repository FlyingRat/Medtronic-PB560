/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Vsimv_Mode_Apnea_Time.c     	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new value		*/
/*%C        of the Apnea Time in the Vsimv mode      	     							*/
/*                                                            				  		*/
/*%C In automatic mode apnea = 12 sec                                         */
/*%C In normal mode, Apnea time is written by the value parameter             */
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
#include "Timer_Data.h"
#include "DRV_VarEeprom.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Write_Adjust_Vsimv_Mode_Apnea_Time(UWORD16 *Value)
{

/* Apnea time declaration */
   UWORD16 Apnea_Time_Default = cApneaTimeSimv;
   UWORD16 Auto_Apnea_Select   = EEP_DB_VSIMV_Adjust[AUTO_APNEA_SELECT_U16];
/* Id values recuperation from adjust base in Pres mode */
   UWORD16 Disconnection_Delay_Auto =
   								 EEP_DB_VSIMV_Adjust[DISCONNECTION_DELAY_AUTO_U16];


/*%C Limit tests */
   if (Auto_Apnea_Select == TRUE)
   {
/*%C  Apnea time writing (fixed to default value) */
      DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_APNEA_U16],
								      Apnea_Time_Default);						
   }
/*%C The apnea time is written to the setting value : */
	else
	{
      DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_APNEA_U16],
								      *Value);						          
   }

   /*%C the disconnection delay is apnea time + 1s if flag on AUTO */
	if (Disconnection_Delay_Auto == TRUE)
	{
/*%C Auto value is the max between AdjustApnea + 2s and 15s */
		if (TIME_LOW_PRESS > (*Value + 2000))
		{
			DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
									  TIME_LOW_PRESS);
		}
		else
		{
			DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
									  *Value + 2000);
		}
	}

/*%C This function always return TRUE */
	return(TRUE);
}
