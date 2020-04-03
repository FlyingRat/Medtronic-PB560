/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Pres_Mode_Insp_Sens.c    	  	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new Insp 		*/
/*%C        Sens value depending on the High R value :                  		*/
/*                                                            				  		*/
/*%C Insp sens value writing.                                          			*/
/*%C If Insp Sens value = 0, Insp Sens and High R No Select are activated 		*/
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
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_IHM_Write_Adjust_Pres_Mode_Insp_Sens.h"
#include "DB_IhmAccessParaDataBase.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Insp_Sens(UWORD16 *Value)
{
/*%C Insp Sens no select flag recovery */
	UWORD16 Insp_Sens_No_Select = EEP_DB_PRES_Adjust[INSP_SENS_NO_SELECT_U16];

	UWORD16 CurrentMode = DB_ControlRead(CURRENT_MODE_U16);

	UWORD16 AdjustMode = DB_ConfigRead(ADJUST_MODE_U16);

/*%C Insp Sens value writing in current base for immediate application, */
/*%C except when the mode is changing) */

	if(CurrentMode == AdjustMode)
	{
		DB_CurrentWrite(ADJUST_INSP_SENS_U16,*Value);
	}

/*%C Insp Sens value writing */
   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_INSP_SENS_U16],
									*Value);


 

/*%C If Insp Sens no select is TRUE, High R no select is activated */
   if (Insp_Sens_No_Select == TRUE)
	{ 
/*%C  No select flag indication */
      	DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[INSP_SENS_NO_SELECT_U16],
									   TRUE); 	  
     	DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[HIGH_R_NO_SELECT_U16],
									   TRUE);
     	DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_HIGH_R_U16],
									   cDB_PRES_TEST_ADJUST_DB[ADJUST_HIGH_R_U16].maxi);
	}
	else
	{
/*%C  No select flag indication */
      	DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[INSP_SENS_NO_SELECT_U16],
									   FALSE); 
	}

/*%C In this function the result is always TRUE */
   return(TRUE);
}
