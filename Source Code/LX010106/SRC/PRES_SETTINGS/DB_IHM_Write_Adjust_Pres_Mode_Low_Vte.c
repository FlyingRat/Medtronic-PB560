/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Pres_Mode_Low_Vte.c  		        		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new limits		*/
/*%C        of the linked settings function of Low Vte conditions     	  		*/
/*                                                            				  		*/
/*%C If Low Vte > High Vte - 20 => High Vte = Low Vte + 20	   				   */
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
UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Low_Vte(UWORD16 *Value)
{

/* Id values recuperation from adjust base in Pres mode */
   UWORD16 Adjust_High_Vte = EEP_DB_PRES_Adjust[ADJUST_HIGH_VTE_U16];

	DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_LOW_VTE_U16],
									*Value);

/*%C High Vte writing */
   if (*Value > Adjust_High_Vte - cLowVteHighVteHysteresis)
   {
	   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_HIGH_VTE_U16],
									   *Value + cLowVteHighVteHysteresis);
   }

/* In this function the result is always TRUE */
	return(TRUE);
}


 