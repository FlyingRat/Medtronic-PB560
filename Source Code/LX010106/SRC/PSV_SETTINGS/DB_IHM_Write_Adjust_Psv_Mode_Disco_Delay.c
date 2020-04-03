/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Psv_Mode_Disco_Delay.c     	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new value		*/
/*%C        of the disco in the Psv mode        	     							*/
/*                                                            				  		*/
/*%C  - if backup R = OFF, disco delay = 15 s:		 					            */
/*%C  - if backup R <> OFF:													            */
/*%C  	- if disco delay is Auto, disco delay = apnea time + 1 s             */
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

UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Disco_Delay(UWORD16 *Value)
{

/* Adjust apnea recovery from base */
	UWORD16 AdjustApnea= EEP_DB_PSV_Adjust[ADJUST_APNEA_U16];

/* Id values recuperation from adjust base in Psv mode */
   UWORD16 Disconnection_Delay_Auto =
   								 EEP_DB_PSV_Adjust[DISCONNECTION_DELAY_AUTO_U16];


/*%C the disconnection delay is apnea time + 1s if flag on AUTO */
	if (Disconnection_Delay_Auto == TRUE)
	{
/*%C Auto value is the max between AdjustApnea + 2s and 15s */
		if (TIME_LOW_PRESS > (AdjustApnea + 2000))
		{
			DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
									  TIME_LOW_PRESS);
		}
		else
		{
			DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
									  AdjustApnea + 2000);
		}
	}

/*%C 	the disconnection delay is the setting value if flag not on AUTO */
        else
        {
			DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
									  	*Value);
        }


/* In this function the result is always TRUE */
	return(TRUE);
}
