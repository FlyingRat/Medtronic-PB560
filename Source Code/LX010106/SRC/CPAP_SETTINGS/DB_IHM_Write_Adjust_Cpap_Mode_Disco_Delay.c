/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Cpap_Mode_Disco_Delay.c     	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new value		*/
/*%C        of the disco in the Cpap mode        	     								*/
/*                                                            				  		*/
/*%C  	- if disco delay is Auto, disco delay = 15s             					*/
/*%C  	- else, disco delay = delay setting             							*/
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
#include "DB_Control.h"
#include "DB_Current.h"
#include "DB_Rtc.h"
#include "Timer_Data.h"
#include "DB_IhmAccessParaDataBase.h"


/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Write_Adjust_Cpap_Mode_Disco_Delay(UWORD16 *Value)
{

/* Id values recuperation from adjust base in Psv mode */
   UWORD16 Disconnection_Delay_Auto =
   								 EEP_DB_CPAP_Adjust[DISCONNECTION_DELAY_AUTO_U16];

/* Adjust apnea recovery from base */
	UWORD16 AdjustApnea= EEP_DB_CPAP_Adjust[ADJUST_APNEA_U16];

/*%C    If disconnection delay is AUTO */
	if (Disconnection_Delay_Auto == TRUE)
	{
/*%C Auto value is the max between AdjustApnea + 2s and 15s */
		if (TIME_LOW_PRESS > (*Value + 2000))
		{
			DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
									  TIME_LOW_PRESS);
		}
		else
		{
			DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
									  *Value + 2000);
		}
	}
/*%C 	the disconnection delay is the setting value if flag not on AUTO */
	else
	{
		DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
							  	*Value);
	}


/* In this function the result is always TRUE */
	return(TRUE);
}
