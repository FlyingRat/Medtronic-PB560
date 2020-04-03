/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Vsimv_Mode_Vol_Control.c 	  	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new limits		*/
/*%C        of the linked settings, function of Vsimv control conditions: 		*/
/*                                                            				  		*/
/*%C If VOL CONTROL < LOW VTE + 10 =>  LOW VTE = VOL CONTROL - 10             */
/*%C If VOL CONTROL > HIGH VTE - 10 => HIGH VTE = VOL CONTROL + 10            */
/*%C If VOL CONTROL < LOW VTI + 10 => LOW VTI = VOL CONTROL - 10              */
/*%C If VOL CONTROL > HIGH VTI - 10 => HIGH VTI = VOL CONTROL + 10            */
/*%C If LOW VM > (10 * VOL CONTROL * CONTROL R) 1000 - 5								*/
/*%C => LOW VM = (10 * VOL CONTROL * CONTROL R) 1000 - 5            				*/
/*%C => LOW VM is limited to its (min,max) values                 				*/
/*%C If HIGH VM < (10 * VOL CONTROL * CONTROL R) 1000 + 5							*/
/*%C => HIGH VM = (10 * VOL CONTROL * CONTROL R) 1000 + 5            	  		*/
/*%C => HIGH VM is limited to its (min,max) values                 				*/
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
#include "DB_IHM_Write_Adjust_Vsimv_Mode_Vol_Control.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/
UWORD16 DB_IHM_Write_Adjust_Vsimv_Mode_Vol_Control(UWORD16 *Value)
{
/* Id values recuperation from adjust base in vol mode */
   UWORD16 Adjust_Low_Vm   = EEP_DB_VSIMV_Adjust[ADJUST_LOW_VM_U16];
   UWORD16 Adjust_High_Vm  = EEP_DB_VSIMV_Adjust[ADJUST_HIGH_VM_U16];
   UWORD16 Adjust_Low_Vte  = EEP_DB_VSIMV_Adjust[ADJUST_LOW_VTE_U16];
   UWORD16 Adjust_High_Vte = EEP_DB_VSIMV_Adjust[ADJUST_HIGH_VTE_U16];
   UWORD16 Adjust_Low_Vti  = EEP_DB_VSIMV_Adjust[ADJUST_LOW_VTI_U16];
   UWORD16 Adjust_High_Vti = EEP_DB_VSIMV_Adjust[ADJUST_HIGH_VTI_U16];

/* Min, max and step High and Low Vm declaration */
   SWORD32 Adjust_High_Vm_Mini =
                        cDB_VSIMV_TEST_ADJUST_DB[ADJUST_HIGH_VM_U16].mini;
   SWORD32 Adjust_High_Vm_Maxi = 
                        cDB_VSIMV_TEST_ADJUST_DB[ADJUST_HIGH_VM_U16].maxi;
   SWORD32 Adjust_Low_Vm_Mini =
                        cDB_VSIMV_TEST_ADJUST_DB[ADJUST_LOW_VM_U16].mini;
   SWORD32 Adjust_Low_Vm_Maxi = 
                        cDB_VSIMV_TEST_ADJUST_DB[ADJUST_LOW_VM_U16].maxi;

/* Datas declaration for compute	 */
   UWORD32 Volume_Per_Minute = 0u;
   
/* Volume_Per_Minute en lpm avec 10: VM en dl; 1000: VOL_CONTROL en ml */
   Volume_Per_Minute = (100 * (UWORD32)(*Value) * (UWORD32)Simv_Backup_R)/1000u;
/* Volume_Per_Minute rounded to the upper 50 ml if it is not an integer value*/
   if((Volume_Per_Minute % 50) != 0)
   {
       Volume_Per_Minute = Volume_Per_Minute 
   					     - (Volume_Per_Minute % 50); 
       Volume_Per_Minute = Volume_Per_Minute 					  
					     + 50;
   }
   Volume_Per_Minute = Volume_Per_Minute / 10;


/*%C Vol Control writing */
   DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_VOL_CONTROL_U16],
									*Value);						
		  


/*%C Dependence test between Volume per minute and High Vm */
	if (Adjust_High_Vm <= (UWORD16)Volume_Per_Minute + cHighVmVolumePerMinuteHysteresis)
	{
/*%C  ADJUST_HIGH_VM affectation (limitation to High Vm min and max) */
      Adjust_High_Vm = (UWORD16)(Volume_Per_Minute + cHighVmVolumePerMinuteHysteresis); 

		DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_HIGH_VM_U16],
										Adjust_High_Vm);						
	}

/*%C Dependence test between vol control and low vte */
	if (*Value < Adjust_Low_Vte + cVolControlLowVteHysteresis)
	{
/*%C  ADJUST_LOW_VTE affectation */
      	Adjust_Low_Vte = (UWORD16)(*Value - cVolControlLowVteHysteresis);

		DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_LOW_VTE_U16]
								,Adjust_Low_Vte);
	}

/*%C Dependence test between vol control and high vte */
	if (*Value > Adjust_High_Vte - cVolControlHighVteHysteresis)
	{
/*%C  ADJUST_LOW_VTE affectation */
      	Adjust_High_Vte = (UWORD16)(*Value + cVolControlHighVteHysteresis);

		DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_HIGH_VTE_U16] 
								,Adjust_High_Vte);
	}

/*%C Dependence test between vol control and low vti */
	if (*Value < Adjust_Low_Vti + cVolControlLowVtiHysteresis)
	{
/*%C  ADJUST_LOW_VTI affectation */
      	Adjust_Low_Vti = (UWORD16)(*Value - cVolControlLowVtiHysteresis);

		DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_LOW_VTI_U16] 
								,Adjust_Low_Vti);
	}

/*%C Dependence test between vol control and high vti */
	if (*Value > Adjust_High_Vti - cVolControlHighVtiHysteresis)
	{
/*%C  ADJUST_HIGH_VTI affectation */
      	Adjust_High_Vti = (UWORD16)(*Value + cVolControlHighVtiHysteresis);

		DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_HIGH_VTI_U16] 
							,Adjust_High_Vti);
	}

/*%C In this function the result is always TRUE */
   return(TRUE);
}
