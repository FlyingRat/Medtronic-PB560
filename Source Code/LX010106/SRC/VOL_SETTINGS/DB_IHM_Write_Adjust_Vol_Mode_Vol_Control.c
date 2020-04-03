/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Vol_Mode_Vol_Control.c 	  	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new limits		*/
/*%C        of the linked settings, function of vol control conditions:   		*/
/*                                                            				  		*/
/*%C If VOL CONTROL - 10 < LOW VTE  =>  LOW VTE  = VOL CONTROL - 10				*/
/*%C If VOL CONTROL + 10 > HIGH VTE =>  HIGH VTE = VOL CONTROL	+ 10				*/
/*%C If VOL CONTROL * SIGH VT COEF > 2000ml  											*/
/*%C											=>  SIGH VT COEF = VOL CONTROL / 2000		*/
/******************************************************************************/
/*%I 	Input Parameter :				*Value                                		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			True/False 	                 				  		*/
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DRV_VarEeprom.h"
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_IHMAccessparaDataBase.h"
#include "DB_IHM_Write_Adjust_Vol_Mode_Vol_Control.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Write_Adjust_Vol_Mode_Vol_Control(UWORD16 *Value)
{
/* Id values recuperation from adjust base in vol mode */
   UWORD16 Adjust_Low_Vte   = EEP_DB_VOL_Adjust[ADJUST_LOW_VTE_U16];
   UWORD16 Adjust_High_Vte  = EEP_DB_VOL_Adjust[ADJUST_HIGH_VTE_U16];
   UWORD16 Adjust_Sigh_Vt_Coef = EEP_DB_VOL_Adjust[ADJUST_SIGH_VT_COEF_U16];


/*%C Vol Control writing */
   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_VOL_CONTROL_U16],
									*Value);						
		  
/*%C Dependence test between vol control and low vte */
	if (*Value < Adjust_Low_Vte + cVolControlLowVteHysteresis)
	{
/*%C  ADJUST_LOW_VTE affectation */
		DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_LOW_VTE_U16]
										, *Value - cVolControlLowVteHysteresis);
	}
/*%C Dependence test between vol control and high vte */
	if (*Value > Adjust_High_Vte - cVolControlHighVteHysteresis)
	{
/*%C  ADJUST_LOW_VTE affectation */
		DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_HIGH_VTE_U16] 
										, *Value + cVolControlHighVteHysteresis);
	}

/*%C Dependence test between vol control and Vt sigh coef */
	if ((*Value * Adjust_Sigh_Vt_Coef) / 10 >
									 cDB_VOL_TEST_ADJUST_DB[ADJUST_VOL_CONTROL_U16].maxi)
	{
/*%C  ADJUST_SIGH_VT_COEF affectation */
		DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_SIGH_VT_COEF_U16] 
			,((cDB_VOL_TEST_ADJUST_DB[ADJUST_VOL_CONTROL_U16].maxi * 10) / *Value));
	}

/*%C In this function the result is always TRUE */
   return(TRUE);
}
