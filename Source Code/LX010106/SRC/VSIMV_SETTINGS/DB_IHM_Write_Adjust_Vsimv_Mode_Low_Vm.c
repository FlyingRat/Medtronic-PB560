/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Vsimv_Mode_Low_Vm.c		          		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the            	*/
/*%C        Low Vm setting in the Vsimv mode    	      	  						*/
/*                                                            				  		*/
/*%C if LOW VM > HIGh VM - 10 => HIGH VM = LOW VM + 10								*/
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

UWORD16 DB_IHM_Write_Adjust_Vsimv_Mode_Low_Vm(UWORD16 *Value)
{
/*%C Id values recuperation from adjust base in vsimv mode */
   UWORD16 Adjust_High_Vm = EEP_DB_VSIMV_Adjust[ADJUST_HIGH_VM_U16];


/*%C Low Vm Writing */
   DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_LOW_VM_U16],
 								   *Value);


/*%C  High/Low Vm dependance */
      if (*Value > Adjust_High_Vm - cLowVmHighVmHysteresis)
      {
/*%C     High Vm writing by DB_WriteDataInEepAndRam function call 	*/
         Adjust_High_Vm = (UWORD16)(*Value + cLowVmHighVmHysteresis);

         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_HIGH_VM_U16],
								Adjust_High_Vm);
      }
   return(TRUE);
}



 