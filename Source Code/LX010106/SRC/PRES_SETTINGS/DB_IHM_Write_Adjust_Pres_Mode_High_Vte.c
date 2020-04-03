/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Pres_Mode_High_Vte.c  		        		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new limits		*/
/*%C        of the linked settings function of High Vte conditions     	  		*/
/*                                                            				  		*/
/*%C If High Vte < Low Vte + 20 => Low Vte = High Vte - 20	   				   */
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
UWORD16 DB_IHM_Write_Adjust_Pres_Mode_High_Vte(UWORD16 *Value)
{

/* Id values recuperation from adjust base in Pres mode */
   UWORD16 Adjust_Low_Vte = EEP_DB_PRES_Adjust[ADJUST_LOW_VTE_U16];
   UWORD16 Low_Vte_No_Select	= EEP_DB_PRES_Adjust[LOW_VTE_NO_SELECT_U16];

	DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_HIGH_VTE_U16],
									*Value);

/*%C Low Vte writing */
   if ( (*Value < Adjust_Low_Vte + cLowVteHighVteHysteresis)
	  && (Low_Vte_No_Select == TRUE) )
   {
	   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_LOW_VTE_U16],
									   *Value - cLowVteHighVteHysteresis);
   }

/* In this function the result is always TRUE */
	return(TRUE);
}



 