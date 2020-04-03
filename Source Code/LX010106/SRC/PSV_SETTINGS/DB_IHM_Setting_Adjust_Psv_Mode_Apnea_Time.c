/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psv_Mode_Apnea_Time.c     	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the Apnea Time setting in the Psv mode	     							*/
/*                                                            				  		*/
/*%C Apnea Time (ms) [min:1000, max:60000, step:1000, default:30000]          */
/*%C Apnea Time is include in its own limits(otherwise, value is saturated)   */
/*%C Automatic mode is reached by the down key, in this mode the apnea time   */
/*%C value is given by the Backup R :                                         */
/*%C  - if backup R = OFF, Apnea Time = 30 000                                */
/*%C  - if backup R <> OFF, Apnea Time = 2 * 60 * 1000 / backup R             */
/*%C  In this function, the auto flag is set and the value is saturated, the  */
/*%C  apnea time value is written in the                                      */
/*%C  DB_IHM_Write_Adjust_Psv_Mode_Apnea_Time function                        */
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
#include "DB_IHM_Setting_Adjust_Psv_Mode_Apnea_Time.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Apnea_Time(UWORD16 *Value,
																  UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/* Id values recuperation from adjust base in psv mode */
   UWORD16 AdjustBackupR = EEP_DB_PSV_Adjust[ADJUST_BACKUP_R_U16];
   UWORD16 BackupRNoselect = EEP_DB_PSV_Adjust[BACKUP_R_NO_SELECT_U16];


/*%C Limit tests */
/*%C Up Limit test */
   if (*Value > cDB_PSV_TEST_ADJUST_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].maxi;
/*%C  Auto apnea flag writing by DB_WriteDataInEepAndRam function call 	*/
      DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[AUTO_APNEA_SELECT_U16],
										TRUE);
      Function_Result = FALSE;
   }
/*%C Down Limit test and auto flag selection */
   else if (*Value < cDB_PSV_TEST_ADJUST_DB[Id].mini)
   {
/*%C  Value limited to its min */
      *Value = cDB_PSV_TEST_ADJUST_DB[Id].mini;
/*%C Apnea value can't be "AUTO" when Backup R value is "OFF" */
		if(BackupRNoselect == FALSE)
		{
/*%C  Auto apnea flag writing by DB_WriteDataInEepAndRam function call 	*/

		}
		Function_Result = FALSE;
   }
   /*%C Dependence test between backUp R and apnea*/
   else if (	(*Value < cApneaTimeCoeff2 / AdjustBackupR)
   			&& 	(BackupRNoselect == FALSE))
   {
		/*%C  Value out of range => Control R flag for IHM indication */
		DB_ControlWrite(LIMIT_BACKUP_R_U16,TRUE);
		Function_Result = TRUE;
   }
   			
/*%C If "Auto apnea flag" activated => "Auto apnea flag" cancelled */
	else if (EEP_DB_PSV_Adjust[AUTO_APNEA_SELECT_U16] == TRUE)
	{
/*%C Flag writing by DB_WriteDataInEepAndRam function call 	*/
		DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[AUTO_APNEA_SELECT_U16],
										FALSE);										
		Function_Result = TRUE;
	}
/*%C Setting authorized */
   else
   {
      Function_Result = FALSE;
   }

	return(Function_Result);
}
