/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Psv_Mode_Max_Pressure.c     	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new value		*/
/*%C        of the Max Pressure in the Psv mode        	     						*/
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

UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Max_Pressure(UWORD16 *Value)
{

/*%C Target Vt saturation (max) */
   	if (*Value > (UWORD32)cDB_PSV_TEST_ADJUST_DB[ADJUST_MAX_PRESSURE_U16].maxi)
	{
      *Value =  cDB_PSV_TEST_ADJUST_DB[ADJUST_MAX_PRESSURE_U16].maxi;
	}
/*%C Value recording */
   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_MAX_PRESSURE_U16],
								   *Value);

/*%C This function always return TRUE */
	return(TRUE);
}
