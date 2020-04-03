/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Psv_Mode_Apnea_Time.c     	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new value		*/
/*%C        of the Apnea Time in the Psv mode        	     							*/
/*                                                            				  		*/
/*%C In automatic mode :                                                      */
/*%C  - if backup R = OFF, Apnea Time = 30000ms                               */
/*%C  - if backup R <> OFF, Apnea Time = 60 * 1000 / backup R             		*/
/*%C In normal mode, Apnea time is written by the value parameter             */
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
#include "Timer_Data.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Apnea_Time(UWORD16 *Value)
{

/* Function result declaration */
   UWORD16 Rest = 0;
/* Apnea time declaration */
   UWORD32 Apnea_time = 0;
/* Id values recuperation from adjust base in psv mode */
   UWORD16 Adjust_Backup_R     = EEP_DB_PSV_Adjust[ADJUST_BACKUP_R_U16];
   UWORD16 Auto_Apnea_Select   = EEP_DB_PSV_Adjust[AUTO_APNEA_SELECT_U16];
   UWORD16 Backup_R_No_Select  = EEP_DB_PSV_Adjust[BACKUP_R_NO_SELECT_U16];
   UWORD16 Apnea_Default_Value = 30000;

/* Id values recuperation from adjust base in Pres mode */
   UWORD16 Disconnection_Delay_Auto =
   								 EEP_DB_PSV_Adjust[DISCONNECTION_DELAY_AUTO_U16];

/*%C Apnea time affectation in auto mode with backup R set*/
   Apnea_time =  cApneaTimeCoeff / (UWORD32)Adjust_Backup_R;
/*%C Rounded to 100ms */
   Rest = (UWORD16)(Apnea_time % 100);
   Apnea_time = Apnea_time - Rest;
/*%C Apnea saturation (max) */
   if (Apnea_time > (UWORD32)cDB_PSV_TEST_ADJUST_DB[ADJUST_APNEA_U16].maxi)
	{
      Apnea_time =  (UWORD32)cDB_PSV_TEST_ADJUST_DB[ADJUST_APNEA_U16].maxi;
	}

/*%C Limit tests */
   if (EEP_DB_PSV_Adjust[AUTO_APNEA_SELECT_U16] == TRUE)
   {
      if (EEP_DB_PSV_Adjust[BACKUP_R_NO_SELECT_U16] == TRUE)
		{
/*%C     Apnea time writing (fixed to default value) */
         DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_APNEA_U16],
									      Apnea_Default_Value);						
		}
		else
		{
/*%C     Apnea time writing, linked to the Backup R :        */
/*%C     Apnea time = Max[3s,(60 * 1000) / Backup R ]            		*/
		if (Apnea_time<3000)
		{
			Apnea_time=3000;
		} 
         DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_APNEA_U16],
									      (UWORD16)Apnea_time);
      }									      						
   }
/*%C The apnea time is written to the setting value : */
	else
	{
      DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_APNEA_U16],
								      *Value);						          
   }



/*%C the disconnection delay is apnea time + 1s if flag on AUTO */
	if (Disconnection_Delay_Auto == TRUE)
	{
/*%C Auto value is the max between AdjustApnea + 2s and 15s */
		if (TIME_LOW_PRESS > (*Value + 2000))
		{
			DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
									  TIME_LOW_PRESS);
		}
		else
		{
			DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
									  *Value + 2000);
		}
	}

/*%C This function always return TRUE */
	return(TRUE);
}
