/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Vsimv_Mode_Ti_Control.c     	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new value		*/
/*%C        of the Ti Control in the Vsimv mode      	     							*/
/*                                                            				  		*/
/*%C If apnea time < 2 * Ti Control => apnea time = 2 * Ti control                 */
/*%C rounded the second sup								             			*/
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

UWORD16 DB_IHM_Write_Adjust_Vsimv_Mode_Ti_Control(UWORD16 *Value)
{

/* Apnea time declaration */
   UWORD16 Adjust_Apnea   = EEP_DB_VSIMV_Adjust[ADJUST_APNEA_U16];

/* Ti Control writing */
   DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_TI_CONTROL_U16],
						      *Value);						


/*%C Link with apnea time setting */
   if (Adjust_Apnea < *Value * 2)
   {
		if ( (*Value * 2) %1000 != 0)
		{
		 	DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_APNEA_U16],
									(((*Value * 2) /1000) + 1) * 1000 );
		}
		else
		{
		 	DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_APNEA_U16],
									*Value * 2);
		}
   }
/*%C This function always return TRUE */
	return(TRUE);
}
