/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Psv_Mode.c 	   	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages the different		*/
/*%C        settings for a write operation in DataBase for the PSV mode   	   */
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
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_IHM_Write_Adjust_Psv_Mode.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


UWORD16 DB_IHM_Write_Adjust_Psv_Mode(UWORD16 *Value,
                                     UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

	UWORD16 CurrentMode = DB_ControlRead(CURRENT_MODE_U16);

	UWORD16 AdjustMode = DB_ConfigRead(ADJUST_MODE_U16);

/*%C Function of Id, the setting writing is done in EEPROM and RAM            */

	switch (Id)
	{
/*%C  P Support writing  */
		case ADJUST_P_SUPPORT_U16:
		{
/*%C     EEPROM and RAM writing  */
			Function_Result =	DB_IHM_Write_Adjust_Psv_Mode_P_Support(Value);
			break;
		}

/*%C  P Support no select writing  */
		case P_SUPPORT_NO_SELECT_U16:
		{
/*%C     P support writing function call  */
			Function_Result =
							 DB_IHM_Write_Adjust_Psv_Mode_P_Support_No_Select(Value);
			break;
		}

/*%C  Peep writing  */
		case ADJUST_PEEP_U16:
		{
			DB_IHM_Write_Adjust_Psv_Mode_Peep(Value);
			Function_Result = TRUE;
			break;
		}

/*%C  Peep writing */
		case PEEP_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[PEEP_NO_SELECT_U16],
										   *Value);
			Function_Result = TRUE;
			break;
		}

/*%C  Rise time writing  */
		case ADJUST_RISE_TIME_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_RISE_TIME_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Backup R writing  */
		case ADJUST_BACKUP_R_U16:
		{
/*%C     Backup R writing function call (apnea time link) */
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_Backup_R(Value);
			break;
		}

/*%C  Backup R writing  */
		case BACKUP_R_NO_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[BACKUP_R_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Apnea writing  */
		case ADJUST_APNEA_U16:
		{
/*%C     Apnea time writing function call  */
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_Apnea_Time(Value);
			break;
		}

/*%C  Apnea no select  writing  */
		case AUTO_APNEA_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[AUTO_APNEA_SELECT_U16],
										   *Value);
			Function_Result = TRUE;
			break;
		}

/*%C  Target VT writing  */
		case ADJUST_TARGET_VT_U16:
		{
/*%C     Target VT writing function call  */
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_Target_Vt(Value);
			break;
		}

/*%C  Target VT no select writing  */
		case TARGET_VT_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[TARGET_VT_SELECT_U16],
										   *Value);
			Function_Result = TRUE;
			break;
		}

/*%C  Max Pressure writing  */
		case ADJUST_MAX_PRESSURE_U16:
		{
/*%C     Max pressure writing function call  */
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_Max_Pressure(Value);
			break;
		}

/*%C  Insp sens writing  */
		case ADJUST_INSP_SENS_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_INSP_SENS_U16],
										   *Value);						

/*%C Insp Sens value writing in current base for immediate application, */
/*%C except when the mode is changing) */

			if(CurrentMode == AdjustMode)
			{
				DB_CurrentWrite(ADJUST_INSP_SENS_U16,*Value);
			}
			Function_Result = TRUE;
			break;
		}

/*%C  Exh sens writing  */
		case ADJUST_EXH_SENS_U16:
		{
/*%C     Exh sens writing function call  */
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_Exh_Sens(Value);
			break;
		}

/*%C  Exh sens limits check function call */
		case ADJUST_EXH_SENS_NEGATIVE_U16:
		{
/*%C     Exh sens writing function call  */
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_Exh_Sens_Neg(Value);
			break;
		}

/*%C  Ti min writing  */
		case ADJUST_TI_MIN_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_Ti_Min(Value);
			break;
		}

/*%C  Ti min no select  writing  */
		case TI_MIN_AUTO_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[TI_MIN_AUTO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Ti max writing  */
		case ADJUST_TI_MAX_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_Ti_Max(Value);
			break;
		}

/*%C  Ti max no select  writing  */
		case TI_MAX_AUTO_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[TI_MAX_AUTO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Low vti writing  */
		case ADJUST_LOW_VTI_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_Low_Vti(Value);
			break;
		}

/*%C  Low Vti no select  writing  */
		case LOW_VTI_NO_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[LOW_VTI_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High vti writing  */
		case ADJUST_HIGH_VTI_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_High_Vti(Value);
			break;
		}

/*%C  High Vti no select  writing  */
		case HIGH_VTI_NO_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[HIGH_VTI_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Low vte writing  */
		case ADJUST_LOW_VTE_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_Low_Vte(Value);
			break;
		}

/*%C  Low vte no select writing  */
		case LOW_VTE_NO_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[LOW_VTE_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High vte writing  */
		case ADJUST_HIGH_VTE_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Psv_Mode_High_Vte(Value);
			break;
		}

/*%C  High vte no select writing  */
		case HIGH_VTE_NO_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[HIGH_VTE_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High R writing  */
		case ADJUST_HIGH_R_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_HIGH_R_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High R no select writing  */
		case HIGH_R_NO_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[HIGH_R_NO_SELECT_U16],
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
		DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[DISCONNECTION_DELAY_AUTO_U16],
										*Value);						
			break;
		}

/*%C  High Leak writing  */
		case ADJUST_HIGH_LEAK_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_HIGH_LEAK_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High Leak no select writing  */
		case HIGH_LEAK_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[HIGH_LEAK_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
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
