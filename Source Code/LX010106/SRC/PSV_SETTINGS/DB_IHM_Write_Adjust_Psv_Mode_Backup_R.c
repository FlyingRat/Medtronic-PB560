/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Psv_Mode_Backup_R.c      	       		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the new value		*/
/*%C        of the Backup R in the Psv mode and writes the apnea value     	*/
/*%C        if necessary                                                     	*/
/*                                                            				  		*/
/*%C  - if backup R = OFF and Apnea on AUTO, Apnea Time = 30000ms             */
/*%C  - if backup R = OFF and Apnea <> AUTO, Apnea Time = 60 / Backup R       */
/*%C  - if Ti min > 30 / Backup R => Ti Min = 30 / Backup R                   */
/*%C  - if Backup R > High R - 5 => High R = Backup R + 5                     */
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
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Write_Adjust_Psv_Mode_Backup_R.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Backup_R(UWORD16 *Value)
{

/* Apnea time declaration */
   UWORD32 Apnea_time = 0;

/* Id values recuperation from adjust base in psv mode */
   UWORD16 Adjust_Backup_R     = *Value;
   UWORD16 Adjust_High_R       = EEP_DB_PSV_Adjust[ADJUST_HIGH_R_U16];
   UWORD16 Auto_Apnea_Select   = EEP_DB_PSV_Adjust[AUTO_APNEA_SELECT_U16];
   UWORD16 Backup_R_No_Select  = EEP_DB_PSV_Adjust[BACKUP_R_NO_SELECT_U16];
   UWORD16 Apnea_Default_Value =	30000;
   UWORD16 Adjust_Ti_Min       = EEP_DB_PSV_Adjust[ADJUST_TI_MIN_U16];
   UWORD16 High_R_No_Select	 = EEP_DB_PSV_Adjust[HIGH_R_NO_SELECT_U16];
   UWORD16 Adjust_Ti_Min_Limit = 0;

/*%C Backup R writing */
   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_BACKUP_R_U16],
									*Value);

/*%C Apnea time affectation in auto mode with backup R set*/
   Apnea_time =  cApneaTimeCoeff / (UWORD32)Adjust_Backup_R;
/*%C Rounded to 100ms */
   Apnea_time = (Apnea_time /100) *100;

/*%C Apnea saturation (max) */
   	if (Apnea_time > (UWORD32)cDB_PSV_TEST_ADJUST_DB[ADJUST_APNEA_U16].maxi)
	{
      Apnea_time =  (UWORD32)cDB_PSV_TEST_ADJUST_DB[ADJUST_APNEA_U16].maxi;
	}
	else if (Apnea_time <= 3000)
	{
      Apnea_time =  3000;
	}
/*%C Apnea time writing if Apnea set on automatic */

/*%C Limit tests */

    if (EEP_DB_PSV_Adjust[BACKUP_R_NO_SELECT_U16] == TRUE)
	{
/*%C     Apnea time writing (fixed to default value) */
         DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_APNEA_U16],
									      Apnea_Default_Value);
	}
	else
	{
/*%C     Apnea time writing, linked to the Backup R :        */
/*%C     Apnea time = 60000 / Backup R             */
         DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_APNEA_U16],
									      (UWORD16)Apnea_time);
    }
 
	DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[AUTO_APNEA_SELECT_U16],
									      TRUE);
	DB_IHM_Write_Adjust_Psv_Mode_Apnea_Time((UWORD16 huge*)&EEP_DB_PSV_Adjust[ADJUST_APNEA_U16]);

/*%C Ti min / Backup R dependance */
   Adjust_Ti_Min_Limit = cTiMinCoeff / Adjust_Backup_R;
   Adjust_Ti_Min_Limit = (Adjust_Ti_Min_Limit / 100) * 100;

   if (Adjust_Ti_Min > Adjust_Ti_Min_Limit)
   {
      DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_TI_MIN_U16],
									   Adjust_Ti_Min_Limit);
   }
/*%C High R / Backup R dependance */
   if ( (Adjust_Backup_R > Adjust_High_R - 5)
     && (High_R_No_Select == FALSE) )
   {
   	  if(Adjust_Backup_R + 5 < cDB_PSV_TEST_ADJUST_DB[ADJUST_HIGH_R_U16].mini)	
      {
	  		DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_HIGH_R_U16],
									   cDB_PSV_TEST_ADJUST_DB[ADJUST_HIGH_R_U16].mini);
	  }
	  else
	  {
	  	  	DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_HIGH_R_U16],
									   Adjust_Backup_R + 5);
	  }
   }


/*%C This function always return TRUE */
	return(TRUE);

}
