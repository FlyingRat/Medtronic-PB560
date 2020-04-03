/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Vol_Mode.c 	   	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages the different		*/
/*%C        settings for a write operation in DataBase for the VOL mode		   */
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
#include "DB_IHM_Write_Adjust_Vol_Mode.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Write_Adjust_Vol_Mode(UWORD16 *Value, UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;


/*%C Function of Id, the setting writing is done in EEPROM and RAM            */
	switch (Id)
	{
/*%C  Vol control writing function call */
		case ADJUST_VOL_CONTROL_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vol_Mode_Vol_Control(Value); 
			break;
		}

/*%C  Control R writing function call */
		case ADJUST_CONTROL_R_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vol_Mode_Control_R(Value);
			break;
		}

/*%C  Ti control writing */
		case ADJUST_TI_CONTROL_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_TI_CONTROL_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Ramp writing */
		case ADJUST_RAMP_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_RAMP_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Peep writing function call */
		case ADJUST_PEEP_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vol_Mode_Peep(Value);
			break;
		}

/*%C  Peep writing */
		case PEEP_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[PEEP_NO_SELECT_U16],
										   *Value);
			Function_Result = TRUE;
			break;
		}

/*%C  Insp sens writing function call */
		case ADJUST_INSP_SENS_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vol_Mode_Insp_Sens(Value);	
			break;
		}

/*%C  Insp sens no select writing function call */
		case INSP_SENS_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[INSP_SENS_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Low pip writing */
		case ADJUST_LOW_PIP_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_LOW_PIP_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High pip writing */
		case ADJUST_HIGH_PIP_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_HIGH_PIP_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Low vte  writing */
		case ADJUST_LOW_VTE_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_LOW_VTE_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Low vte No Select writing */
		case LOW_VTE_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[LOW_VTE_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High vte  writing */
		case ADJUST_HIGH_VTE_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_HIGH_VTE_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High vte No Select writing */
		case HIGH_VTE_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[HIGH_VTE_NO_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High R writing */
		case ADJUST_HIGH_R_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_HIGH_R_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High R no select writing function call */
		case HIGH_R_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[HIGH_R_NO_SELECT_U16],
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
		DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[DISCONNECTION_DELAY_AUTO_U16],
										*Value);						
			break;
		}

		case ADJUST_SIGH_SELECT_U16:
		{
/*%C     Sight Select writing */
		DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_SIGH_SELECT_U16],
										*Value);						
			break;
		}

		case ADJUST_SIGH_CPT_U16:
		{
/*%C     Sigh cpt writing*/
			DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_SIGH_CPT_U16],
											*Value);						
			break;
		}

		case ADJUST_SIGH_VT_COEF_U16:
		{
/*%C     Sigh coef writing */
			DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[ADJUST_SIGH_VT_COEF_U16],
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
