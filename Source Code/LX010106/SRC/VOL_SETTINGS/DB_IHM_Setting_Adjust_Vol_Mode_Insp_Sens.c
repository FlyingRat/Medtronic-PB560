/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Insp_Sens.c		          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Insp sens setting in the Vol mode									*/
/*                                                            				  		*/
/*%C INSP SENS [min:OFF=0, max:5, step:1, default:OFF=0]   							*/
/*%C INSP SENS is include in its own limits(otherwise, value is saturated)   	*/
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

UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Insp_Sens(UWORD16 *Value,
																 UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Limit tests */
   if ((*Value < cDB_VOL_TEST_ADJUST_DB[Id].mini) ||
       (*Value == (UWORD16) (cDB_VOL_TEST_ADJUST_DB[Id].mini - cDB_VOL_TEST_ADJUST_DB[Id].step)) )
   {
/*%C  Value limited to its min*/
      *Value = cDB_VOL_TEST_ADJUST_DB[Id].maxi;
	  Function_Result = FALSE;
   }
   else if (*Value > cDB_VOL_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max*/
      *Value = cDB_VOL_TEST_ADJUST_DB[Id].mini;
	  Function_Result = FALSE;
   }
/*%C Setting in range 	*/
   else
   {
		Function_Result = FALSE;
   }
/*%C Update no select flag */
    if (*Value == 0)
        DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[INSP_SENS_NO_SELECT_U16],
									   TRUE);
    else
        DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[INSP_SENS_NO_SELECT_U16],
									   FALSE);

   return(Function_Result);
}
