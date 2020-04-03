/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Pres_Mode_Max_Pressure.c   	        	*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Max Pressure setting in the Pres mode	     						*/
/*                                                            				  		*/
/*%C P Max [min:80, max:600, step:10, default:180] 									*/
/*                                                            				  		*/
/*%C P Control is include in its own limits(otherwise, value is saturated)    */
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
#include "DB_IHM_Setting_Adjust_Pres_Mode_Max_Pressure.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Pres_Mode_Max_Pressure(UWORD16 *Value,
																	  UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;

	UWORD16 Adjust_P_Control = EEP_DB_PRES_Adjust[ADJUST_P_CONTROL_U16];

/* read of the pressure convention */
	UWORD16 Pressure_Support_Relative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);

/* Id values recuperation from adjust base in pres mode */
   UWORD16 Adjust_Peep = EEP_DB_PRES_Adjust[ADJUST_PEEP_U16];


/*%C Limit tests */
/*%C Down Limit test */
   if ( (*Value < cDB_PRES_TEST_ADJUST_DB[Id].mini)
	  || (*Value > cDB_PRES_TEST_ADJUST_DB[Id].maxi) )
	{
		Function_Result = TRUE;
	}
/*%C P Max / P Control dependance */
   else if (*Value < Adjust_P_Control)
   {
/*%C  Value limited to its max */
      *Value = Adjust_P_Control;
		DB_ControlWrite(LIMIT_PI_U16,
						    TRUE);
      Function_Result = FALSE;
   }
/*%C P Max / P Control dependance */
   else if (*Value > Adjust_P_Control + cPControlPiMaxHysteresis)
   		
   {
/*%C  Value limited to its max */
      *Value = Adjust_P_Control + cPControlPiMaxHysteresis;
		DB_ControlWrite(LIMIT_PI_U16,
						    TRUE);
      Function_Result = FALSE;
   }
   /*%C P Max + Peep > 55in relative*/
   else if ((*Value > cDB_PRES_TEST_ADJUST_DB[Id].maxi - Adjust_Peep)
   			&& (Pressure_Support_Relative == TRUE))
   {
/*%C  Value limited to its max */
      *Value = cDB_PRES_TEST_ADJUST_DB[Id].maxi - Adjust_Peep;
	DB_ControlWrite(LIMIT_PEEP_U16,
			    TRUE);
      Function_Result = FALSE;
   }
   else
   {
/*%C  Setting authorized */
      Function_Result = FALSE;
		DB_ControlWrite(LIMIT_PI_U16,
						    FALSE);
   }

	return(Function_Result);
}
