/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Pres_Mode_High_Vti.c  		        		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new limits		*/
/*%C        of the linked settings function of High Vte conditions     	  		*/
/*                                                            				  		*/
/*%C If High Vti < Low Vti + 20 => Low Vti = High Vti - 20	   				   */
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
#include "DB_IHMAccessparaDataBase.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Write_Adjust_Pres_Mode_High_Vti(UWORD16 *Value)
{

/* Id values recuperation from adjust base in Pres mode */
   UWORD16 Adjust_Low_Vti = EEP_DB_PRES_Adjust[ADJUST_LOW_VTI_U16];
   UWORD16 Low_Vti_No_Select = EEP_DB_PRES_Adjust[LOW_VTI_NO_SELECT_U16];

	DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_HIGH_VTI_U16],
									*Value);

/*%C Low Vti writing */
   if ( (*Value < Adjust_Low_Vti + cLowVtiHighVtiHysteresis)
	  && (Low_Vti_No_Select == TRUE) )
   {
	   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_LOW_VTI_U16],
									   *Value - cLowVtiHighVtiHysteresis);
   }

/* In this function the result is always TRUE */
	return(TRUE);
}




 