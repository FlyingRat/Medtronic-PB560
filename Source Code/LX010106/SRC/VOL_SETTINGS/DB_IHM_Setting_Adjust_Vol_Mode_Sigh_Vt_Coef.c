/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Vt_Coef.c          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the sigh Vt coef setting in the Vol mode	 							*/
/*  					                                            				  		*/
/*%C SIGH VT COEF [min:10, max:20, step:1, default:10]   							*/
/*%C SIGH VT COEF is include in its own limits(otherwise, value is saturated)	*/
/*%C SIGH VT COEF * Vol Control < 2000ml													*/
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
#include "DB_Current.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Vt_Coef.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Vt_Coef(UWORD16 *Value,
															  		UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

   UWORD16 Adjust_Vol_Control = EEP_DB_VOL_Adjust[ADJUST_VOL_CONTROL_U16];

/*%C Limit tests */
   if ( (*Value < cDB_VOL_TEST_ADJUST_DB[Id].mini)
	  || (*Value > cDB_VOL_TEST_ADJUST_DB[Id].maxi)	)
   {
		Function_Result = TRUE;
   }
/*%C Vol Control / Sigh value dependance */
	else if ((*Value * Adjust_Vol_Control) / 10 >
								cDB_VOL_TEST_ADJUST_DB[ADJUST_VOL_CONTROL_U16].maxi)  
	{
/*%C  Value out of range => Vol Control flag for IHM indication */
		DB_ControlWrite(LIMIT_VOL_CONTROL_U16,
							 TRUE);
		Function_Result = TRUE;
	}
   else
   {
/*%C 	Setting authorized  */
		Function_Result = FALSE;
   }
	return(Function_Result);
}
