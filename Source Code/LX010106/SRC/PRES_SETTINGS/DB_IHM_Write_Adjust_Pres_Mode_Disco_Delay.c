/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Pres_Mode_Disco_Delay.c 		     		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new limits		*/
/*%C        of the linked settings function of disconnection delay     	  		*/
/*                                                            				  		*/
/*%C If disconnection delay is on AUTO, delay = 180 / Control R					*/
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
#include "DB_IHMAccessparaDataBase.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Disco_Delay(UWORD16 *Value)
{

/* Control R recovery from base */
	UWORD16 AdjustControlR= EEP_DB_PRES_Adjust[ADJUST_CONTROL_R_U16];
/* Id values recuperation from adjust base in Pres mode */
   UWORD16 Disconnection_Delay_Auto =
   								 EEP_DB_PRES_Adjust[DISCONNECTION_DELAY_AUTO_U16];

	if (Disconnection_Delay_Auto == TRUE)
	{
	DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
								   (180 / AdjustControlR) * 1000);
	}
	else
	{
	DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
								  	*Value);
	}

/* In this function the result is always TRUE */
	return(TRUE);
}
 