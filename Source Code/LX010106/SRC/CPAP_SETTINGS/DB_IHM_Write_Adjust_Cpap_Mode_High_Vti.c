/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Cpap_Mode_High_Vti.c 	          		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the            	*/
/*%C        High_Vti setting in the Cpap mode  	      								*/
/*                                                            				  		*/
/*%C if HIGH VTI < LOW VTI + 20 => LOW VTI = HIGH VTI - 20  						*/
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

UWORD16 DB_IHM_Write_Adjust_Cpap_Mode_High_Vti(UWORD16 *Value)
{
/*%C Id values recuperation from adjust base in psv mode */
   UWORD16 Adjust_Low_Vti = EEP_DB_CPAP_Adjust[ADJUST_LOW_VTI_U16];
   UWORD16 Low_Vti_No_Select = EEP_DB_CPAP_Adjust[LOW_VTI_NO_SELECT_U16];

/*%C High Vti Writing */
   DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[ADJUST_HIGH_VTI_U16],
 								   *Value);

   if (Low_Vti_No_Select == TRUE)
   {
/*%C  High/Low Vti dependance */
      if (*Value < Adjust_Low_Vti + cLowVtiHighVtiHysteresis)
      {
/*%C     Low Vti writing by DB_WriteDataInEepAndRam function call 	*/
         DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[ADJUST_LOW_VTI_U16],
										   *Value - cLowVtiHighVtiHysteresis);
      }
   }
   return(TRUE);
}

 