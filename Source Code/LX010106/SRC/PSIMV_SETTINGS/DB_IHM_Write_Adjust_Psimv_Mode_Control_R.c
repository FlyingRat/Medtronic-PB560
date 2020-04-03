/******************************************************************************/
/*																			  							*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Psimv_Mode_Control_R.c           		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new limits		*/
/*%C        of the linked settings function of control R conditions   	  		*/
/*                                                            				  		*/
/*%C If CONTROL R > HIGH R - 5 =>  HIGH R = CONTROL R + 5 except if       		*/
/*%C CONTROL R is OFF                                         				  		*/
/*                                                            				  		*/
/*%C Apnea time writing :                                    				  		*/
/*%C - if apnea time is auto with Control R OFF:                              */
/*%C                                      apnea time  = 30 s             		*/
/*%C - if apnea time is auto with Control R <> OFF:                           */
/*%C                                      apnea time  = 60 / Control R			*/
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
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_IHMAccessparaDataBase.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Write_Adjust_Psimv_Mode_Control_R(UWORD16 *Value)
{
   
/* Id values recuperation from adjust base in vsimv mode */
   UWORD16 Control_R_No_Select = EEP_DB_PSIMV_Adjust[CONTROL_R_NO_SELECT_U16];
   UWORD16 Adjust_High_R       = EEP_DB_PSIMV_Adjust[ADJUST_HIGH_R_U16];
   UWORD16 Adjust_Control_R    = EEP_DB_PSIMV_Adjust[ADJUST_CONTROL_R_U16];
   UWORD16 Apnea_Default_Value = 30000;
   UWORD16 High_R_No_Select	= EEP_DB_PSIMV_Adjust[HIGH_R_NO_SELECT_U16];

/*%C Control R writing */
	DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[ADJUST_CONTROL_R_U16],
									*Value);						

/*%C Dependence test between Control R and High R */
   if ( (*Value > Adjust_High_R - cAlarmRHysteresis)
     && (High_R_No_Select == FALSE) )
   {
/*%C  ADJUST_HIGH_R affectation */
      Adjust_High_R = (UWORD16)(*Value + cAlarmRHysteresis);

      DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[ADJUST_HIGH_R_U16],
							Adjust_High_R);
   }


/* In this function the result is always TRUE */
	return(TRUE);
}
