/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Psv_Mode_Peep.c	     	       		*/
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
#include "DB_IHM_Write_Adjust_Psv_Mode_Peep.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/




UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Peep(UWORD16 *Value)
{
 /* Id values recuperation from adjust base in Psv mode */
	UWORD16 Adjust_Max_Pressure = EEP_DB_PSV_Adjust[ADJUST_MAX_PRESSURE_U16];
	UWORD16 Pressure_Support_Relative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);
	UWORD16 Target_Vt_Select = EEP_DB_PSV_Adjust[TARGET_VT_SELECT_U16];
								   
/*%C In relative mode, and Vt target not selected, if the Peep becomes upper than */
/*%C 55mbar - Pmax, then Pmax takes PSupport value */							   
	if ((Adjust_Max_Pressure + *Value >= cDB_PSV_TEST_ADJUST_DB[ADJUST_MAX_PRESSURE_U16].maxi)
	&& (Pressure_Support_Relative == TRUE)
	&& (Target_Vt_Select == FALSE))
	{
	   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_MAX_PRESSURE_U16],
									   EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16]);
	   DB_CurrentWrite(ADJUST_MAX_PRESSURE_U16,EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16]);	
	}
	
	DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_PEEP_U16],
										   *Value);				   						

/*%C This function always return TRUE */
	return(TRUE);
}
