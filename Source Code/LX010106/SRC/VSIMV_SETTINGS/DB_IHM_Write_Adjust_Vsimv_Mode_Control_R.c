/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Vsimv_Mode_Control_R.c           		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new limits		*/
/*%C        of the linked settings function of control R conditions   	  		*/
/*                                                            				  		*/
/*%C If CONTROL R > HIGH R - 5 =>  HIGH R = CONTROL R + 5 except if       		*/
/*%C CONTROL R is OFF                                         				  		*/
/*%C                                                          				  		*/
/*%C Apnea time writing :                                    				  		*/
/*%C - if apnea time is auto with Control R OFF:                              */
/*%C                                      apnea time  = 30 s             		*/
/*%C - if apnea time is auto with Control R <> OFF:                           */
/*%C                                      apnea time  = 60 / Control R			*/
/*%C                                                          				  		*/
/*%C If LOW VM > (10 * VOL CONTROL * CONTROL R) / 1000 - 5							*/
/*%C => LOW VM = (10 * VOL CONTROL * CONTROL R) / 1000 - 5    				  		*/
/*%C If HIGH VM < (10 * VOL CONTROL * CONTROL R) / 1000 + 5 						*/
/*%C => HIGH VM = (10 * VOL CONTROL * CONTROL R) / 1000 + 5            	  		*/
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
#include "DB_IHM_Write_Adjust_Vsimv_Mode_Control_R.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Write_Adjust_Vsimv_Mode_Control_R(UWORD16 *Value)
{

   
/* Id values recuperation from adjust base in vsimv mode */
   UWORD16 Control_R_No_Select = EEP_DB_VSIMV_Adjust[CONTROL_R_NO_SELECT_U16];
   UWORD16 Adjust_High_R       = EEP_DB_VSIMV_Adjust[ADJUST_HIGH_R_U16];
   UWORD16 Adjust_Vol_Control  = EEP_DB_VSIMV_Adjust[ADJUST_VOL_CONTROL_U16];
   UWORD16 Apnea_Default_Value =	30000;
   UWORD16 High_R_No_Select	= EEP_DB_VSIMV_Adjust[HIGH_R_NO_SELECT_U16];
   UWORD16 Adjust_Low_Vm		= EEP_DB_VSIMV_Adjust[ADJUST_LOW_VM_U16];
   UWORD16 Adjust_High_Vm		= EEP_DB_VSIMV_Adjust[ADJUST_HIGH_VM_U16];

/* Min, max and step High and Low Vm declaration */
   SWORD32 Adjust_High_Vm_Mini= cDB_VSIMV_TEST_ADJUST_DB[ADJUST_HIGH_VM_U16].mini;
   SWORD32 Adjust_High_Vm_Maxi= cDB_VSIMV_TEST_ADJUST_DB[ADJUST_HIGH_VM_U16].maxi;
   SWORD32 Adjust_Low_Vm_Mini = cDB_VSIMV_TEST_ADJUST_DB[ADJUST_LOW_VM_U16].mini;
   SWORD32 Adjust_Low_Vm_Maxi = cDB_VSIMV_TEST_ADJUST_DB[ADJUST_LOW_VM_U16].maxi;

 /* Datas declaration for the compute	 */
   UWORD32 Volume_Per_Minute = 0;
	UWORD16 Temp_Control_R = *Value;

	if(Temp_Control_R <= cSIMV_BACKUP_R_MIN)
	{
		Temp_Control_R = cSIMV_BACKUP_R_MIN; 	
	}


/*%C Computed values*/
/* Volume_Per_Minute en lpm avec 10: VM en dl; 1000: VOL_CONTROL en ml */
   Volume_Per_Minute = (100 * (UWORD32)Adjust_Vol_Control * (UWORD32)Temp_Control_R)/1000u;
/* Volume_Per_Minute rounded to the upper 50 ml if it is not an integer value*/
   if((Volume_Per_Minute % 50) != 0)
   {
       Volume_Per_Minute = Volume_Per_Minute 
   					     - (Volume_Per_Minute % 50); 
       Volume_Per_Minute = Volume_Per_Minute 					  
					     + 50;
   }
   Volume_Per_Minute = Volume_Per_Minute / 10;



/*%C Control R writing */
	DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_CONTROL_R_U16],
									*Value);						

/*%C Dependence test between Control R and High R */
   if ( (*Value > Adjust_High_R - cAlarmRHysteresis)
     && (High_R_No_Select == FALSE) )
   {
/*%C  ADJUST_HIGH_R affectation */
      Adjust_High_R = (UWORD16)(*Value + cAlarmRHysteresis);

      DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_HIGH_R_U16],
								Adjust_High_R);
   }


/*%C Dependence test between Volume per minute and High Vm */
	if (Adjust_High_Vm <= (UWORD16)Volume_Per_Minute + cHighVmVolumePerMinuteHysteresis)
	{
/*%C  ADJUST_HIGH_VM affectation (limitation to High Vm min and max) */
      Adjust_High_Vm = 
           (UWORD16)(Volume_Per_Minute + cHighVmVolumePerMinuteHysteresis); 

		DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_HIGH_VM_U16],
										Adjust_High_Vm);						
	}

/* In this function the result is always TRUE */
	return(TRUE);
}
