/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Vsimv_Mode_High_Vte.c	          		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the            	*/
/*%C        High_Vte setting in the Vsimv mode         								*/
/*                                                            				  		*/
/*%C if HIGH VTE < LOW VTE + 20 => LOW VTE = HIGH VTE - 20  						*/
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
#include "DB_IhmAccessParaDataBase.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Write_Adjust_Vsimv_Mode_High_Vte(UWORD16 *Value)
{
/*%C Id values recuperation from adjust base in Vsimv mode */
   UWORD16 Adjust_Low_Vte = EEP_DB_VSIMV_Adjust[ADJUST_LOW_VTE_U16];
   UWORD16 Low_Vte_No_Select = EEP_DB_VSIMV_Adjust[LOW_VTE_NO_SELECT_U16];

/*%C High Vte Writing */
   DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_HIGH_VTE_U16],
 								   *Value);

   if (Low_Vte_No_Select == TRUE)
   {
/*%C  High/Low Vte dependance */
      if (*Value < Adjust_Low_Vte + cLowVteHighVteHysteresis)
      {
/*%C     Low Vte writing by DB_WriteDataInEepAndRam function call 	*/
         Adjust_Low_Vte = (UWORD16)(*Value - cLowVteHighVteHysteresis);

         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_LOW_VTE_U16],
								Adjust_Low_Vte);
      }
   }
   return(TRUE);
}


 