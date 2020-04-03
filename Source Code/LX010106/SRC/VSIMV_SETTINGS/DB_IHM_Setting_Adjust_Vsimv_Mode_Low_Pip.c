/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vsimv_Mode_Low_Pip.c  	         		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the low pip setting in the Vsimv mode									*/
/*                                                            				  		*/
/*%C LOW PIP [min:20, max:350, step:10, default:20]        							*/
/*%C LOW PIP is include in its own limits(otherwise, value is saturated)		*/
/*%C LOW PIP >= PEEP + 20                           									*/
/*%C LOW PIP <= P_SUPPORT + PEEP	                  									*/
/*%C LOW PIP <= HIGH PIP -80	                     									*/
/*%C If the conditions on High Pip or Peep are not respected, a limit flag is	*/
/*%C set for IHM indication and the value is saturated        				  		*/
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
#include "DB_IHM_Setting_Adjust_Vsimv_Mode_Low_Pip.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Vsimv_Mode_Low_Pip(UWORD16 *Value,
															    UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;
/* Id values recuperation from adjust base in vol mode */
   UWORD16 Adjust_High_Pip = EEP_DB_VSIMV_Adjust[ADJUST_HIGH_PIP_U16];

/* Id values recuperation from adjust base in vsimv mode */
   UWORD16 Adjust_Peep      = EEP_DB_VSIMV_Adjust[ADJUST_PEEP_U16];
   UWORD16 Adjust_P_Support = EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16];
/* read of the pressure convention */
	UWORD16 Pressure_Support_Relative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);

/*%C Limit tests */
   if ( (*Value < cDB_VSIMV_TEST_ADJUST_DB[Id].mini)
     || (*Value > cDB_VSIMV_TEST_ADJUST_DB[Id].maxi) )
	{
      Function_Result = TRUE;
	}
/*%C Dependence test between Low Pip and P support */
	else if ((*Value > Adjust_P_Support + Adjust_Peep)
				&& (Pressure_Support_Relative == TRUE))
	{
/*%C  P Support flag for IHM indication */
		DB_ControlWrite(LIMIT_P_SUPPORT_U16,
							 TRUE);
/*%C  Peep flag for IHM indication */
		DB_ControlWrite(LIMIT_PEEP_U16,
							 TRUE);
		Function_Result = TRUE;
	}
/*%C Dependence test between Low Pip and P support */
	else if ((*Value > Adjust_P_Support)
		  		&& (Pressure_Support_Relative == FALSE))
	{
/*%C  P Support flag for IHM indication */
		DB_ControlWrite(LIMIT_P_SUPPORT_U16,
							 TRUE);

		Function_Result = TRUE;
	}
/*%C Dependence test between Low Pip and Peep */
	else if (*Value < Adjust_Peep + cPeepLowPipHysteresis)
	{
/*%C  => Peep flag for IHM indication */
		DB_ControlWrite(LIMIT_PEEP_U16,
							 TRUE);
		Function_Result = TRUE;
	}
/*%C Dependence test between Low Pip and High pip */
	else if (*Value > Adjust_High_Pip - cLowPipHighPipHysteresis)
	{
/*%C  Value out of range,        */
/*%C  => value robustness        */
      *Value = (Adjust_High_Pip - cLowPipHighPipHysteresis); 
/*%C  => High Pip flag for IHM indication */
		DB_ControlWrite(LIMIT_HIGH_PIP_U16,
							 TRUE);
		Function_Result = FALSE;
	}
   else
   {
/*%C  Peep flag desactivation */
		DB_ControlWrite(LIMIT_PEEP_U16,
							 FALSE);
/*%C  P Support flag for IHM indication */
		DB_ControlWrite(LIMIT_P_SUPPORT_U16,
							 FALSE);
      Function_Result = FALSE;
   }

	return(Function_Result);
}
