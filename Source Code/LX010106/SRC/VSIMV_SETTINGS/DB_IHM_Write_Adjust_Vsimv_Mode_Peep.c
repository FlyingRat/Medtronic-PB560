/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Vsimv_Mode_Peep.c  			         		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new limits		*/
/*%C        of the linked settings, function of peep conditions:					*/
/*                                                            				  		*/
/*%C If PEEP + P SUPPORT < LOW PIP => LOW PIP = P SUPPORT + PEEP           	*/
/*%C If PEEP + P SUPPORT > HIGH PIP -2 => HIGH PIP = P SUPPORT + PEEP + 2     */
/*%C If PEEP > LOW PIP -2 => LOW PIP = PEEP + 2                               */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				*Value                                		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
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
#include "DB_IHM_Setting_Adjust_Vsimv_Mode_Peep.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Write_Adjust_Vsimv_Mode_Peep(UWORD16 *Value)
{
/* Id values recuperation from adjust base in vol mode */
	UWORD16 Adjust_Low_Pip		=     EEP_DB_VSIMV_Adjust[ADJUST_LOW_PIP_U16];
	UWORD16 Adjust_High_Pip		=     EEP_DB_VSIMV_Adjust[ADJUST_HIGH_PIP_U16];
	UWORD16 Adjust_P_Support	=     EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16];
/* read of the pressure convention */
	UWORD16 Pressure_Support_Relative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);

/*%C Peep value writing */
	DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_PEEP_U16],
									*Value);


/*%C Dependence test between peep and low pip */
	if (*Value + cPeepLowPipHysteresis > Adjust_Low_Pip )
	{	
/*%C  ADJUST_LOW_PIP affectation */
      DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_LOW_PIP_U16],
									   (*Value + cPeepLowPipHysteresis));
   }

/*%C Dependence test between peep and high pip */
	if ((*Value + Adjust_P_Support < Adjust_Low_Pip )
	&& (Pressure_Support_Relative == TRUE))
	{
/*%C  ADJUST_LOW_PIP affectation */

      	 Adjust_Low_Pip = (UWORD16)(*Value + Adjust_P_Support);

     	 DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_LOW_PIP_U16],
									Adjust_Low_Pip);
  	 }

/*%C Dependence test between peep and high pip */
	if ((*Value + Adjust_P_Support > Adjust_High_Pip - cPiHighPipHysteresis )
	&& (Pressure_Support_Relative == TRUE))
	{
/*%C  ADJUST_LOW_PIP affectation */

      	Adjust_High_Pip = (UWORD16)(*Value + Adjust_P_Support + cPiHighPipHysteresis);

     	 DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_HIGH_PIP_U16],
									Adjust_High_Pip);
  	 }


/*%C In this function the result is always TRUE */
	return(TRUE);
}
