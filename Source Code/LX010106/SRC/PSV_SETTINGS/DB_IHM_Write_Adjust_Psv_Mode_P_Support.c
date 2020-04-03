/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Psv_Mode_P_Support.c	     	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new value		*/
/*%C        of the P Support in the Psv mode     	 	  	     						*/
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
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Write_Adjust_Psv_Mode_P_Support(UWORD16 *Value)
{

	UWORD16 Adjust_Max_Pressure = EEP_DB_PSV_Adjust[ADJUST_MAX_PRESSURE_U16];

   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16],
								   *Value);
								   
	if (Adjust_Max_Pressure < *Value)
	{
	   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_MAX_PRESSURE_U16],
									   *Value);
	}
	else if (Adjust_Max_Pressure > *Value + cPSupportPiMaxHysteresis)
	{
	   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_MAX_PRESSURE_U16],
									   *Value + cPSupportPiMaxHysteresis);
	}								   						

/*%C This function always return TRUE */
	return(TRUE);
}
