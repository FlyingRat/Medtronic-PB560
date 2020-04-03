/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Cpap_Mode.c 	   	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages the different		*/
/*%C        settings for a write operation in DataBase for the CPAP mode  	   */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				Id                                    		  	*/
/*%IO Input/Output Parameter : 	*Value  	        			                  	*/
/*%O 	Output Parameter : 			True/False 	                 				  		*/
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "DRV_VarEeprom.h"
#include "DB_Current.h"
#include "enum.h"
#include "structure.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Write_Adjust_Cpap_Mode.h"
#include "Timer_Data.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Write_Adjust_Cpap_Mode(UWORD16 *Value,
                                     UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;
/* Id values recuperation from adjust base in Pres mode */
   UWORD16 Disconnection_Delay_Auto =
   								 EEP_DB_CPAP_Adjust[DISCONNECTION_DELAY_AUTO_U16];

/*%C Function of Id, the setting writing is done in EEPROM and RAM            */

	switch (Id)
	{
/*%C  Peep writing  */
		case ADJUST_PEEP_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[ADJUST_PEEP_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}
/*%C  Apnea writing  */
		case ADJUST_APNEA_U16:
		{
			if (EEP_DB_CPAP_Adjust[AUTO_APNEA_SELECT_U16] == TRUE)
			{
		   		DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[ADJUST_APNEA_U16],
										 30000);
			}
			else
			{
		   		DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[ADJUST_APNEA_U16],
										   *Value);
			}
			/*%C    If disconnection delay is AUTO */
			if (Disconnection_Delay_Auto == TRUE)
			{
			/*%C Auto value is the max between AdjustApnea + 2s and 15s */
				if (TIME_LOW_PRESS > (*Value + 2000))
				{
					DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
											  TIME_LOW_PRESS);
				}
				else
				{
					DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[ADJUST_DISCONNECTION_DELAY_U16],
											  *Value + 2000);
				}
			}
			Function_Result = TRUE;										   						
			break;
		}
/*%C  Low vti writing  */
		case ADJUST_LOW_VTI_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Cpap_Mode_Low_Vti(Value);
			break;
		}

/*%C  Low Vti no select  writing  */
		case LOW_VTI_NO_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[LOW_VTI_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High vti writing  */
		case ADJUST_HIGH_VTI_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Cpap_Mode_High_Vti(Value);
			break;
		}

/*%C  High Vti no select  writing  */
		case HIGH_VTI_NO_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[HIGH_VTI_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}
/*%C  High R writing  */
		case ADJUST_HIGH_R_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[ADJUST_HIGH_R_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High R no select writing  */
		case HIGH_R_NO_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[HIGH_R_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}
/*%C  High Leak writing  */
		case ADJUST_HIGH_LEAK_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[ADJUST_HIGH_LEAK_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High Leak no select writing  */
		case HIGH_LEAK_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[HIGH_LEAK_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Adjust disconnection delay function call */
		case ADJUST_DISCONNECTION_DELAY_U16:
		{
 			Function_Result = DB_IHM_Write_Adjust_Cpap_Mode_Disco_Delay(Value);
			Function_Result = DB_IHM_Write_Adjust_Pres_Mode_Disco_Delay(Value);
			Function_Result = DB_IHM_Write_Adjust_Psimv_Mode_Disco_Delay(Value);
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_Disco_Delay(Value);
			Function_Result = DB_IHM_Write_Adjust_Vol_Mode_Disco_Delay(Value);
			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_Disco_Delay(Value);
			break;
		}

/*%C  Disconnection delay auto flag writing */
		case DISCONNECTION_DELAY_AUTO_U16:
		{
		DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[DISCONNECTION_DELAY_AUTO_U16],
										*Value);						
			break;
		}

		default :
		{
			Function_Result = FALSE;
			break;
		}
	}
	return (Function_Result);
}

