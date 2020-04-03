/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psimv_Mode_Peep.c         	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Peep setting in the Psimv mode    	     							*/
/*                                                            				  		*/
/*%C Peep [min:0, max:200, step:10, default:0]                   					*/
/*%C Peep is include in its own limits(otherwise, value is saturated)	      */
/*%C P Control + PEEP <= 600                        							      */
/*%C P Support + PEEP <= 600                        							      */
/*                                                            				  		*/
/*%C If the conditions on P Control P Support are not respected, a limit flag */
/*%C is set for IHM indication and the value is saturated                     */
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
#include "DB_IHM_Setting_Adjust_Psimv_Mode_Peep.h"

/* locate database code to specific section */
#include "locate_database_code.h"
																							  
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Peep(UWORD16 *Value,
														    UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;
/* Peep/Pi gap declaration   */
	UWORD16 Delta_Peep_Pi = 50;

/* Id values recuperation from adjust base in psv mode */
   UWORD16 Adjust_P_Support = EEP_DB_PSIMV_Adjust[ADJUST_P_SUPPORT_U16];
   UWORD16 Adjust_P_Control = EEP_DB_PSIMV_Adjust[ADJUST_P_CONTROL_U16];

	/* read of the pressure convention */
	UWORD16 Pressure_Support_Relative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);
 
/*%C Up and down limit test 								                  */
/*   *Value non signé, il passe donc de 0 au max de son type         */
/*   => fixé à la valeur min de la PEEP                              */
   if ( (*Value <= cDB_PSIMV_TEST_ADJUST_DB[Id].mini)
     || (*Value > cDB_PSIMV_TEST_ADJUST_DB[Id].maxi +
                  cDB_PSIMV_TEST_ADJUST_DB[Id].step) )
   {			
/*%C  Value limited to its min */
      *Value = cDB_PSIMV_TEST_ADJUST_DB[Id].mini;
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[PEEP_NO_SELECT_U16],
										TRUE);
		Function_Result = FALSE;
	}
   else if (*Value > cDB_PSIMV_TEST_ADJUST_DB[Id].maxi)		
	{
		Function_Result = TRUE;
	}
/*%C Dependence test between P Control  and PEEP */
   else if ((Adjust_P_Control + *Value > cMaxPressure )
   		&& (Pressure_Support_Relative == TRUE))
   {
/*%C  => P Control for IHM indication */
		DB_ControlWrite(LIMIT_PI_U16,
							 TRUE);
		Function_Result = TRUE;
	}
/*%C Dependence test between P Support and PEEP */
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
/*%C Dependence test between P Support and PEEP */
   else if ((Adjust_P_Support + *Value > cMaxPressure )
   		&& (Pressure_Support_Relative == TRUE))
   {
/*%C  Value out of range => P Support for IHM indication */
		DB_ControlWrite(LIMIT_P_SUPPORT_U16,
							 TRUE);
		Function_Result = TRUE;
	}
/*%C Dependence test between P Support and PEEP */
   else if ((*Value > Adjust_P_Support - Delta_Peep_Pi)
   		&& (Pressure_Support_Relative == FALSE))
   {
/*%C  Value out of range,        */
/*%C  => value saturation        */
      *Value = Adjust_P_Support - Delta_Peep_Pi;
/*%C  => Peep flag for IHM indication */
		DB_ControlWrite(LIMIT_P_SUPPORT_U16,
							 TRUE);
		Function_Result = FALSE;
	}
/*%C If "no select flag" activated => "no select flag" cancelled */
	else if (EEP_DB_PSIMV_Adjust[PEEP_NO_SELECT_U16] == TRUE)
	{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[PEEP_NO_SELECT_U16],
										FALSE);
		Function_Result = FALSE;
	}
   else
   {
/*%C  Setting authorized, P Control and P Support flag desactivation */
		DB_ControlWrite(LIMIT_PI_U16,
							 FALSE);
		DB_ControlWrite(LIMIT_P_SUPPORT_U16,
							 FALSE);
      Function_Result = FALSE;
   }

	return(Function_Result);
}
