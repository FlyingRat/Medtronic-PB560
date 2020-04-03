/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Pres_Mode_Peep.c         	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Peep setting in the Pres mode    	     							*/
/*                                                            				  		*/
/*%C Peep [min:0, max:200, step:10, default:0]                   					*/
/*%C Peep is include in its own limits(otherwise, value is saturated)         */
/*%C P Control > Peep + 50 with valve detected       							      */
/*%C P Control > Peep + 20 without valve		       							      */
/*%C If the conditions on Peep is not respected, a limit flag is set for 		*/
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
#include "DB_IHM_Setting_Adjust_Pres_Mode_Peep.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Pres_Mode_Peep(UWORD16 *Value,
											 UWORD16 Id,
											 UWORD16 Pi_Max,
											 UWORD16 Peep_Min)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;


/* Peep/Pi gap declaration   */
	UWORD16 Delta_Peep_Pi = 50;

	UWORD16 Valve_Detected = DB_ControlRead(VALVE_DETECTED_U16);
	UWORD16 VentilAuthorization = DB_ControlRead(VENTIL_AUTHORIZATION_U16);

	UWORD16 Adjust_P_Control = EEP_DB_PRES_Adjust[ADJUST_P_CONTROL_U16];

	UWORD16 Adjust_Max_Pressure = EEP_DB_PRES_Adjust[ADJUST_MAX_PRESSURE_U16];

	UWORD16 TargetVtSelect = EEP_DB_PRES_Adjust[TARGET_VT_SELECT_U16];	

	/* read of the pressure convention */
	UWORD16 Pressure_Support_Relative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);

	e_MODE_TYPES CurrentMode = 	DB_ControlRead(CURRENT_MODE_U16);

/*%C If no valve detected : */
	if (VentilAuthorization == FALSE)
	{
		Pi_Max = 550;
		Delta_Peep_Pi = 20;
		Peep_Min = 0;
	}
	else if(Valve_Detected == FALSE)
	{
		Pi_Max = 300;
		Delta_Peep_Pi = 20;
		Peep_Min = 40;		
	} 
	else if(Valve_Detected == TRUE)
	{
		Pi_Max = 550;
		Delta_Peep_Pi = 50;
		Peep_Min = 0;		
	} 

/*%C Up and down limit test											*/
/*   *Value non signé, il passe donc de 0 au max de son type         */
/*   => fixé à la valeur min de la PEEP                              */
   if ( (*Value <= Peep_Min)
     || (*Value > cDB_PRES_TEST_ADJUST_DB[Id].maxi +
                  cDB_PRES_TEST_ADJUST_DB[Id].step) )	
	{
/*   	No select flag for PEEP < 0                              */
		if ((*Value <= cDB_PRES_TEST_ADJUST_DB[Id].mini)
		   || (*Value > cDB_PRES_TEST_ADJUST_DB[Id].maxi +
                  cDB_PRES_TEST_ADJUST_DB[Id].step) )
		{
/*%C  		Flag writing by DB_WriteDataInEepAndRam function call 	*/
			DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[PEEP_NO_SELECT_U16],
											TRUE);
		}
		else
		{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
			DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[PEEP_NO_SELECT_U16],
										FALSE);
		}
/*%C  Value limited to its min */
	   *Value = Peep_Min;
		Function_Result = FALSE;
	}
   else if (*Value > cDB_PRES_TEST_ADJUST_DB[Id].maxi)
	{
/*%C  Value limited to its max */
	   *Value = cDB_PRES_TEST_ADJUST_DB[Id].maxi;   
		Function_Result = FALSE;
   }
/*%C Dependence test between P Control and PEEP */
   else if ((*Value > Adjust_P_Control - Delta_Peep_Pi)
   		&& (Pressure_Support_Relative == FALSE))
   {
/*%C  Value out of range,        */
/*%C  => value saturation        */
      *Value = Adjust_P_Control - Delta_Peep_Pi;
/*%C  => Peep flag for IHM indication */
		DB_ControlWrite(LIMIT_PI_U16,
							 TRUE);
		Function_Result = FALSE;
	}
/*%C Dependence test between P Control and PEEP */
   else if ((*Value > (Pi_Max - Adjust_P_Control))
   		&& (Pressure_Support_Relative == TRUE))
   {
/*%C  Value out of range,        */
/*%C  => value saturation        */
      *Value = Pi_Max - Adjust_P_Control;
/*%C  => Peep flag for IHM indication */
		DB_ControlWrite(LIMIT_PI_U16,
							 TRUE);
		Function_Result = FALSE;
	}

/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_PRES_Adjust[PEEP_NO_SELECT_U16] == TRUE)
	{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[PEEP_NO_SELECT_U16],
										FALSE);
		Function_Result = FALSE;
	}
   else
   {
/*%C  Setting authorized, Peep flag desactivation */
		DB_ControlWrite(LIMIT_PI_U16,
							 FALSE);
      Function_Result = FALSE;
   }

	return(Function_Result);
}
