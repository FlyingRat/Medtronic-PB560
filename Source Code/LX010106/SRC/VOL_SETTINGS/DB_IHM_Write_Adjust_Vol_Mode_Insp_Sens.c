/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Vol_Mode_Insp_Sens.c    	  	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new Insp 		*/
/*%C        Sens value depending on the High R value :                  		*/
/*                                                            				  		*/
/*%C Insp sens value writing                                          			*/
/*%C If Insp Sens no select = true, High R No Select is activated        		*/
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
#include "DB_Rtc.h"
#include "DB_IHMAccessParaDatabase.h"	 
#include "DB_IHM_Write_Adjust_Vol_Mode_Insp_Sens.h"	 

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Write_Adjust_Vol_Mode_Insp_Sens(UWORD16 *Value)
{

/*%C Insp Sens no select flag recovery */
	UWORD16 Insp_Sens_No_Select = EEP_DB_VOL_Adjust[INSP_SENS_NO_SELECT_U16];
	
	UWORD16 CurrentMode = DB_ControlRead(CURRENT_MODE_U16);

	UWORD16 AdjustMode = DB_ConfigRead(ADJUST_MODE_U16);

/*%C Insp Sens value writing in current base for immediate application, */
/*%C except when the mode is changing) */

	if(CurrentMode == AdjustMode)
	{
		DB_CurrentWrite(ADJUST_INSP_SENS_U16,*Value);
	}

/*%C Insp Sens value writing */
   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_INSP_SENS_U16],
									*Value);


/*%C If Insp Sens no select = TRUE, High R no select is activated */
	if (Insp_Sens_No_Select == TRUE)
	{  	

      	DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[INSP_SENS_NO_SELECT_U16],
									   TRUE);
      	DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[HIGH_R_NO_SELECT_U16],
									   TRUE);
     	DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_HIGH_R_U16],
									   cDB_VOL_TEST_ADJUST_DB[ADJUST_HIGH_R_U16].maxi);
	}
	else
	{
	   	DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[INSP_SENS_NO_SELECT_U16],
									   FALSE);
	}

/*%C In this function the result is always TRUE */
   return(TRUE);
}
