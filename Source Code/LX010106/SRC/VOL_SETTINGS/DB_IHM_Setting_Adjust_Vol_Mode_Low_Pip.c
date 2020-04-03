/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Low_Pip.c 		         		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the low pip setting in the Vol mode										*/
/*                                                            				  		*/
/*%C LOW PIP [min:20, max:350, step:10, default:20]        							*/
/*%C LOW PIP is include in its own limits(otherwise, value is saturated)		*/
/*%C LOW PIP <= HIGH PIP - 80                      									*/
/*%C LOW PIP >= PEEP + 20                            									*/
/*%C If the conditions on High Pip or Peep are not respected, a limit flag is	*/
/*%C set for IHM indication and the value is saturated       				  		*/
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
#include "DB_IHM_Setting_Adjust_Vol_Mode_Low_Pip.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Low_Pip(UWORD16 *Value,
															  UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/* Id values recuperation from adjust base in vol mode */
   UWORD16 Adjust_High_Pip = EEP_DB_VOL_Adjust[ADJUST_HIGH_PIP_U16];
   UWORD16 Adjust_Peep     = EEP_DB_VOL_Adjust[ADJUST_PEEP_U16];

/*%C Limit tests */
   if (*Value < cDB_VOL_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Value limited to its min */
      *Value = cDB_VOL_TEST_ADJUST_DB[Id].mini;
		Function_Result = FALSE;
   }
   else if (*Value > cDB_VOL_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_VOL_TEST_ADJUST_DB[Id].maxi;
		Function_Result = FALSE;
   }			
/*%C Dependence test between Low Pip and High pip */
	else if (*Value > Adjust_High_Pip - cLowPipHighPipHysteresis)
	{
/*%C  Value out of range,        */
/*%C  => value saturation        */
      *Value = (Adjust_High_Pip - cLowPipHighPipHysteresis); 
/*%C  => High Pip flag for IHM indication */
		DB_ControlWrite(LIMIT_HIGH_PIP_U16,
							 TRUE);
		Function_Result = FALSE;
	}
/*%C Dependence test between Low Pip and Peep */
	else if (*Value < Adjust_Peep + cPeepLowPipHysteresis)
	{
/*%C  Value out of range,        */
/*%C  => value saturation        */
      *Value = (Adjust_Peep + cPeepLowPipHysteresis); 
/*%C  => High Pip flag for IHM indication */
		DB_ControlWrite(LIMIT_PEEP_U16,
							 TRUE);
		Function_Result = FALSE;
	}
   else
   {
/*%C Setting authorized, High Pip and Peep flag desactivation */
		DB_ControlWrite(LIMIT_HIGH_PIP_U16,
							 FALSE);
		DB_ControlWrite(LIMIT_PEEP_U16,
							 FALSE);
      Function_Result = FALSE;
   }

	return(Function_Result);
}
