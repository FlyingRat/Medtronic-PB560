/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Pres_Mode.c 	   	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages the different		*/
/*%C        settings for a write operation in DataBase for the PRES mode	   */
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
#include "DB_IHM_Write_Adjust_Pres_Mode.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Write_Adjust_Pres_Mode(UWORD16 *Value,
                                      UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;


/*%C Function of Id, the setting writing is done in EEPROM and RAM            */
	switch (Id)
	{
/*%C  P control writing */
		case ADJUST_P_CONTROL_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Pres_Mode_P_Control(Value);
			break;
		}

/*%C  Control R writing function call*/
		case ADJUST_CONTROL_R_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Pres_Mode_Control_R(Value);
			break;
		}

/*%C  Ti control writing */
		case ADJUST_TI_CONTROL_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_TI_CONTROL_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Rise Time writing */
		case ADJUST_RISE_TIME_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_RISE_TIME_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Peep writing */
		case ADJUST_PEEP_U16:
		{
		   	DB_IHM_Write_Adjust_Pres_Mode_Peep(Value);
			Function_Result = TRUE;
			break;
		}

/*%C  Peep writing */
		case PEEP_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[PEEP_NO_SELECT_U16],
										   *Value);
			Function_Result = TRUE;
			break;
		}

/*%C  Insp sens writing function call*/
		case ADJUST_INSP_SENS_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Pres_Mode_Insp_Sens(Value);	
			break;
		}

/*%C  Insp sens no select writing function call */
		case INSP_SENS_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[INSP_SENS_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Low vti writing */
		case ADJUST_LOW_VTI_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Pres_Mode_Low_Vti(Value);
			break;
		}

/*%C  Low Vti no select writing function call */
		case LOW_VTI_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[LOW_VTI_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}


/*%C  High vti writing */
		case ADJUST_HIGH_VTI_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Pres_Mode_High_Vti(Value);
			break;
		}

/*%C  High Vti no select writing function call */
		case HIGH_VTI_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[HIGH_VTI_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Low vte writing */
		case ADJUST_LOW_VTE_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Pres_Mode_Low_Vte(Value);
			break;
		}

/*%C  Low Vte no select writing function call */
		case LOW_VTE_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[LOW_VTE_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High vte writing */
		case ADJUST_HIGH_VTE_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Pres_Mode_High_Vte(Value);
			break;
		}

/*%C  High Vte no select writing function call */
		case HIGH_VTE_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[HIGH_VTE_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High R writing */
		case ADJUST_HIGH_R_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_HIGH_R_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High R no select writing function call */
		case HIGH_R_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[HIGH_R_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Target VT writing  */
		case ADJUST_TARGET_VT_U16:
		{
/*%C     Target VT writing function call  */
			Function_Result = DB_IHM_Write_Adjust_Pres_Mode_Target_Vt(Value);
			break;
		}

/*%C  Target VT no select writing  */
		case TARGET_VT_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[TARGET_VT_SELECT_U16],
										   *Value);
			Function_Result = TRUE;
			break;
		}

/*%C  Max Pressure writing  */
		case ADJUST_MAX_PRESSURE_U16:
		{
/*%C     Max pressure writing function call  */
			Function_Result = DB_IHM_Write_Adjust_Pres_Mode_Max_Pressure(Value);
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
		DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[DISCONNECTION_DELAY_AUTO_U16],
										*Value);						
			break;
		}

/*%C  High Leak writing  */
		case ADJUST_HIGH_LEAK_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_HIGH_LEAK_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}
/*%C  High Leak no select writing  */
		case HIGH_LEAK_SELECT_U16:
		{
/*%C     EEPROM and RAM writing  */
		   DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[HIGH_LEAK_SELECT_U16],
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
