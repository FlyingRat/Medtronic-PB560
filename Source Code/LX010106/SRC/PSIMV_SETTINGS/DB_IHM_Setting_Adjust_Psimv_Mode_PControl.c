/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psimv_Mode_PControl.c   	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the P Control setting in the Psimv mode     							*/
/*                                                            				  		*/
/*%C P Control [min:50, max:600, step:10, default:150]          					*/
/*%C P Control is include in its own limits(otherwise, value is saturated)    */
/*%C P Control + PEEP <= 600                       							      */
/*                                                            				  		*/
/*%C If the conditions on PEEP is not respected, a limit flag is	set for     */
/*%C IHM indication and the value is saturated                                */
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
#include "DB_Config.h"
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Adjust_Psimv_Mode_PControl.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_PControl(UWORD16 *Value,
																   UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;
 /* Peep/Pi gap declaration   */
	UWORD16 Delta_Peep_Pi = 20;
/* Id values recuperation from adjust base in psimv mode */
   UWORD16 Adjust_Peep = EEP_DB_PSIMV_Adjust[ADJUST_PEEP_U16];
/* read of the pressure convention */
	UWORD16 Pressure_Support_Relative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);
 
	if(Pressure_Support_Relative == FALSE)
	{
		Delta_Peep_Pi = 50;
	}
	else
	{
		Delta_Peep_Pi = 20;
	}
/*%C Limit tests */
   if (*Value < cDB_PSIMV_TEST_ADJUST_DB[Id].mini)
   {			
/*%C  Value limited to its min */
      *Value = cDB_PSIMV_TEST_ADJUST_DB[Id].mini;
		Function_Result = FALSE;
	}
   else if (*Value > cDB_PSIMV_TEST_ADJUST_DB[Id].maxi)		
	{
/*%C  Value limited to its max */
      *Value = cDB_PSIMV_TEST_ADJUST_DB[Id].maxi;
		Function_Result = FALSE;
	}
/*%C Dependence test between P Control  and PEEP */
   else if ((*Value + Adjust_Peep > cMaxPressure )
   		&& (Pressure_Support_Relative == TRUE))
   {
/*%C  Value out of range,        */
      *Value = (cMaxPressure - Adjust_Peep);
/*%C  => Peep flag for IHM indication */
		DB_ControlWrite(LIMIT_PEEP_U16,
							 TRUE);
		Function_Result = FALSE;
	}
	/*%C Dependence test between P Control and PEEP */
   else if ((*Value < Adjust_Peep + Delta_Peep_Pi)
      	&& (Pressure_Support_Relative == FALSE))
   {
/*%C  Value out of range,        */
/*%C  => value saturation        */
      *Value = Adjust_Peep + Delta_Peep_Pi;
/*%C  => Peep flag for IHM indication */
		DB_ControlWrite(LIMIT_PEEP_U16,
							 TRUE);
		Function_Result = FALSE;
	}
   else
   {
/*%C  Setting authorized, Peep flag desactivation */
		DB_ControlWrite(LIMIT_PEEP_U16,
							 FALSE);
      Function_Result = FALSE;
   }

	return(Function_Result);
}
