/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_High_Pip.c  		        		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the High Pip setting in the Vol mode									*/
/*                                                            				  		*/
/*%C HIGH PIP [min:150, max:600, step:10, default:400] 								*/
/*%C HIGH PIP is include in its own limits(otherwise, value is saturated)   	*/
/*%C LOW PIP <= HIGH PIP - 80                      									*/
/*%C HIGH PIP >= PEEP + 100                          									*/
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
#include "DB_IHM_Setting_Adjust_Vol_Mode_High_Pip.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_High_Pip(UWORD16 *Value,
																UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/* Id values recuperation from adjust base in vol mode */
   UWORD16 Adjust_Low_Pip  = EEP_DB_VOL_Adjust[ADJUST_LOW_PIP_U16];
   UWORD16 Adjust_Peep     = EEP_DB_VOL_Adjust[ADJUST_PEEP_U16];

/*%C Limit tests */
   if ( (*Value < cDB_VOL_TEST_ADJUST_DB[Id].mini)
     || (*Value > cDB_VOL_TEST_ADJUST_DB[Id].maxi) )
   {
		Function_Result = TRUE;
   }			
/*%C Dependence test between Low Pip and High pip */
	else if (*Value < Adjust_Low_Pip + cLowPipHighPipHysteresis)
	{
/*%C  => Low Pip flag for IHM indication */
		DB_ControlWrite(LIMIT_LOW_PIP_U16,
							 TRUE);
/*%C  Peep flag limit detection */
		if (*Value < Adjust_Peep + cPeepHighPipHysteresis)
		{
/*%C  	=> Peep flag for IHM indication */
			DB_ControlWrite(LIMIT_PEEP_U16,
							 	TRUE);
		}
		Function_Result = TRUE;
	}
/*%C Dependence test between High Pip and Peep */
	else if (*Value < Adjust_Peep + cPeepHighPipHysteresis)
	{
/*%C  => Peep flag for IHM indication */
		DB_ControlWrite(LIMIT_PEEP_U16,
							 TRUE);
		Function_Result = TRUE;
	}
   else
   {
/*%C  Value in range => Low pip and Peep flag desactivation */
		DB_ControlWrite(LIMIT_LOW_PIP_U16,
							 FALSE);
		DB_ControlWrite(LIMIT_PEEP_U16,
							 FALSE);
      Function_Result = FALSE;
   }
  
	return(Function_Result);
}
