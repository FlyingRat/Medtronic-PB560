/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psv_Mode_Max_Pressure.c   	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Max Pressure setting in the Psv mode	     						*/
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
#include "DB_IHM_Setting_Adjust_Psv_Mode_Max_Pressure.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Max_Pressure(UWORD16 *Value,
																UWORD16 Id)
{

     UWORD16 Adjust_P_Support = EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16];

/* read of the pressure convention */
	UWORD16 Pressure_Support_Relative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);

/* Id values recuperation from adjust base in pres mode */
   UWORD16 Adjust_Peep = EEP_DB_PSV_Adjust[ADJUST_PEEP_U16];
/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Limit tests */
/*%C Down Limit test */
   if (*Value < cDB_PSV_TEST_ADJUST_DB[Id].mini)
	{
/*%C  Value limited to its min */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].mini;
		Function_Result = FALSE;
	}
/*%C Up Limit test */
   else if (*Value > cDB_PSV_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].maxi;
      Function_Result = FALSE;
   }
/*%C P Max / P Control dependance */
   else if (*Value < Adjust_P_Support)
   {
/*%C  Value limited to its max */
      *Value = Adjust_P_Support;
		DB_ControlWrite(LIMIT_P_SUPPORT_U16,
						    TRUE);
      Function_Result = FALSE;
   }
/*%C P Max / P Control dependance */
   else if (*Value > Adjust_P_Support + cPSupportPiMaxHysteresis)
   {
/*%C  Value limited to its max */
      *Value = Adjust_P_Support + cPSupportPiMaxHysteresis;
		DB_ControlWrite(LIMIT_P_SUPPORT_U16,
						    TRUE);
      Function_Result = FALSE;
   }
      /*%C P Max + Peep > 55in relative*/
   else if ((*Value > cDB_PSV_TEST_ADJUST_DB[Id].maxi - Adjust_Peep)
   			&& (Pressure_Support_Relative == TRUE))
   {
/*%C  Value limited to its max */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].maxi - Adjust_Peep;
	  	DB_ControlWrite(LIMIT_PEEP_U16,
						    TRUE);
      Function_Result = FALSE;
   }
   else
   {
/*%C  Setting authorized */
      Function_Result = FALSE;
   }

	return(Function_Result);
}
