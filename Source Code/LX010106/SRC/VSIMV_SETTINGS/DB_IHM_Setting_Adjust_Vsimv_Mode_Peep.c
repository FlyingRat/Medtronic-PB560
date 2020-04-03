/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vsimv_Mode_Peep.c         	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Peep setting in the Vsimv mode    	     							*/
/*                                                            				  		*/
/*%C Peep [min:0, max:200, step:10, default:0]                   					*/
/*%C Peep is include in its own limits(otherwise, value is saturated)         */
/*%C P Support + PEEP <= 600                        							      */
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
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Adjust_Vsimv_Mode_Peep.h"

/* locate database code to specific section */
#include "locate_database_code.h"
																							  
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Vsimv_Mode_Peep(UWORD16 *Value,
														    UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;
/* Peep/Pi gap declaration   */
	UWORD16 Delta_Peep_Pi = 50;
/* Id values recuperation from adjust base in vsimv mode */
   UWORD16 Adjust_P_Support = EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16];

	/* read of the pressure convention */
	UWORD16 Pressure_Support_Relative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);
 
/*%C Up and down limit test 								                  */
/*   *Value non signé, il passe donc de 0 au max de son type         */
/*   => fixé à la valeur min de la PEEP                              */
   if ( (*Value <= cDB_VSIMV_TEST_ADJUST_DB[Id].mini)
     || (*Value > cDB_VSIMV_TEST_ADJUST_DB[Id].maxi +
                  cDB_VSIMV_TEST_ADJUST_DB[Id].step) )
   {
/*%C  Value limited to its min */
      *Value = cDB_VSIMV_TEST_ADJUST_DB[Id].mini;
/*%C  Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[PEEP_NO_SELECT_U16],
										TRUE);
      Function_Result = FALSE;
   }
   else if (*Value > cDB_VSIMV_TEST_ADJUST_DB[Id].maxi) 			
	{
      Function_Result = TRUE;
	}
/*%C Dependence test between P Support  and PEEP */
   else if ((Adjust_P_Support + *Value > cMaxPressure )
   		&& (Pressure_Support_Relative == TRUE))
   {
/*%C  => P Support for IHM indication */
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
	else if (EEP_DB_VSIMV_Adjust[PEEP_NO_SELECT_U16] == TRUE)
	{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[PEEP_NO_SELECT_U16],
										FALSE);
		Function_Result = FALSE;
	}
   else
   {
/*%C  Setting authorized, P Support flag desactivation */
		DB_ControlWrite(LIMIT_P_SUPPORT_U16,
							 FALSE);
      Function_Result = FALSE;
   }

	return(Function_Result);
}
