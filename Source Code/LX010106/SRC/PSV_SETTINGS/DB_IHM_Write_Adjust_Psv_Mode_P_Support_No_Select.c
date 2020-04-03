/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Psv_Mode_P_Support_No_Select.c       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new value   	*/
/*%C        of the P support no select and its dependancies values 				*/
/*%C        in the Psv mode			                         				  		*/
/*                                                          				  		*/
/*%C If P support is OFF, Ti min and Ti max are set to their AUTO values      */
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
#include "DB_Current.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_Rtc.h"
#include "DRV_VarEeprom.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Write_Adjust_Psv_Mode_P_Support_No_Select.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Write_Adjust_Psv_Mode_P_Support_No_Select(UWORD16 *Value)
{

/* Id values recuperation from adjust and compute base in psv mode */
   UWORD16 P_Support_No_Select = EEP_DB_PSV_Adjust[P_SUPPORT_NO_SELECT_U16];
   UWORD16 Rise_Time = EEP_DB_PSV_Adjust[RISE_TIME_U16];
   UWORD16 Measure_R = DB_ComputeRead(MEASURE_R_U16);

/* Id values recovery from adjust base in psv mode */
   UWORD16 Ti_Max_Min = cTiMaxmax;

/*%C Test between 3s and 30 / Measure_R */
    if (Ti_Max_Min > 30 / Measure_R)
	{
	   Ti_Max_Min = 30 / Measure_R;
	}
/* else, keeps its declaration value */

/*%C P support no select writing in Eeprom an Ram */
   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[P_SUPPORT_NO_SELECT_U16],
								   *Value);
								   
/*%C P support dependancies writing */
	if (P_Support_No_Select == TRUE)
	{
/*%C 	Ti min writing */
	   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_TI_MIN_U16],
									   Rise_Time + 300);
/*%C 	Ti max writing */
	   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_TI_MAX_U16],
									   Ti_Max_Min);
	}
/*%C else, ti min and ti max keep their value  */

/*%C This function always returns TRUE */
   return(TRUE);
}
