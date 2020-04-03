/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Pres_Mode_P_Control.c   	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the P Control setting in the Pres mode	     							*/
/*                                                            				  		*/
/*%C P Control [min:50, max:600, step:10, default:150] with valve					*/
/*%C P Control [min:50, max:300, step:10, default:150] without valve				*/
/*                                                            				  		*/
/*%C P Control is include in its own limits(otherwise, value is saturated)    */
/*%C P Control > Peep + 50 with valve detected       							      */
/*%C P Control > Peep + 20 without valve		       							      */
/*%C If the conditions on PEEP is not respected, a limit flag is	set for     */
/*%C IHM indication, and the value is saturated                               */
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
#include "DB_Config.h"
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Adjust_Pres_Mode_P_Control.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Pres_Mode_P_Control(UWORD16 *Value,
												  UWORD16 Id,
												  UWORD16 Pi_Max,
												  UWORD16 Pi_Min,
												  UWORD16 Delta_Peep_Pi)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;


/* Id values recuperation from adjust base in pres mode */
   UWORD16 Adjust_Peep = EEP_DB_PRES_Adjust[ADJUST_PEEP_U16];

	UWORD16 Valve_Detected = DB_ControlRead(VALVE_DETECTED_U16);
	UWORD16 VentilAuthorization = DB_ControlRead(VENTIL_AUTHORIZATION_U16);
/* read of the pressure convention */
	UWORD16 Pressure_Support_Relative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);

	e_MODE_TYPES CurrentMode = 	DB_ControlRead(CURRENT_MODE_U16);

/*%C Pi max is 60 cmH2O if ventilation is off and delta pi/pe is 2 cmh2O */
	if (VentilAuthorization == FALSE)
	{
		Pi_Max = cDB_PRES_TEST_ADJUST_DB[Id].maxi;
		Pi_Min = 20;
		Delta_Peep_Pi = 20;
	}
	else if((CurrentMode |= PRES)
	&&(Valve_Detected == FALSE))
	{
		Pi_Max = 300;
		Pi_Min = 60;
		Delta_Peep_Pi = 20;
	} 	 


/*%C Up and down limit test											*/
   if ((*Value < Pi_Min)
   && (Pressure_Support_Relative == FALSE))
	{
		*Value = Pi_Min;
		Function_Result = FALSE;
	}
	else if ((Adjust_Peep + *Value < Pi_Min)
   && (Pressure_Support_Relative == TRUE))
	{
		*Value = Pi_Min - Adjust_Peep ;
		Function_Result = FALSE;
	}
  	else if ((*Value > Pi_Max)
	&& (Pressure_Support_Relative == FALSE))
	{
		*Value = Pi_Max;
		Function_Result = FALSE;
	}
/*%C Dependence test between P Control and PEEP when P control is Relative */
   	else if ((Adjust_Peep + *Value >= Pi_Max)
   		&& (Pressure_Support_Relative == TRUE))
   	{
/*%C  Value out of range,        */
/*%C  => value saturation        */
      *Value = Pi_Max - Adjust_Peep;
/*%C  => Peep flag for IHM indication */
		DB_ControlWrite(LIMIT_PEEP_U16,
							 TRUE);
		Function_Result = FALSE;
	} 
/*%C Dependence test between P Control and PEEP when P control is absolut */
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
/*%C Dependence test between P Control and PEEP when P control is absolut */
   else if ((*Value < Delta_Peep_Pi)
   		&& (Pressure_Support_Relative == TRUE))
   {
/*%C  Value out of range,        */
/*%C  => value saturation        */
      *Value = Delta_Peep_Pi;

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
