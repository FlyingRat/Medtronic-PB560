/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Pres_Mode_Target_Vt.c	     	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new value		*/
/*%C        of the Target VT in the Pres mode        	     							*/
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

UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Target_Vt(UWORD16 *Value)
{

/* Id values recuperation from adjust base in psv mode */

   	UWORD16 Target_Vt_Select = EEP_DB_PRES_Adjust[TARGET_VT_SELECT_U16];
   	UWORD16 Adjust_Low_Vte = EEP_DB_PRES_Adjust[ADJUST_LOW_VTE_U16];
   	UWORD16 Adjust_Low_Vti = EEP_DB_PRES_Adjust[ADJUST_LOW_VTI_U16];
   	UWORD16 Adjust_High_Vti = EEP_DB_PRES_Adjust[ADJUST_HIGH_VTI_U16];
   	UWORD16 Adjust_High_Vte = EEP_DB_PRES_Adjust[ADJUST_HIGH_VTE_U16];
   	UWORD16 Target_Vt_Default_Value
   						= cDB_PRES_TEST_ADJUST_DB[ADJUST_TARGET_VT_U16].defvalue;

   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_TARGET_VT_U16],
								   *Value);

if(Target_Vt_Select == TRUE)
{ 
/*%C Target Vt / Low Vte dependance */
	if (Adjust_Low_Vte >= *Value)
	{
      DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_LOW_VTE_U16],
								      *Value - 10);
	}                                

/*%C Target Vt / Low Vti dependance */
	if (Adjust_Low_Vti >= *Value)
	{
      DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_LOW_VTI_U16],
								      *Value - 10);
	}                                

/*%C Target Vt / High Vti dependance */
	if (Adjust_High_Vti <= *Value)
	{
      DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_HIGH_VTI_U16],
								      *Value + cDB_PRES_TEST_ADJUST_DB[ADJUST_TARGET_VT_U16].step);
	}                                

/*%C Target Vt / High Vte dependance */
	if (Adjust_High_Vte <= *Value)
	{
      DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_HIGH_VTE_U16],
								      *Value + cDB_PRES_TEST_ADJUST_DB[ADJUST_TARGET_VT_U16].step);
	}
}                                

/*%C This function always return TRUE */
	return(TRUE);
}
