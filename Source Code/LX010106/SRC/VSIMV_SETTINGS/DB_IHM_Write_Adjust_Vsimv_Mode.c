/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Vsimv_Mode.c 	  	                 		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages the different		*/
/*%C        settings for a write operation in DataBase for the VSIMV mode 	   */
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
#include "DB_IHM_Write_Adjust_Vsimv_Mode.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Write_Adjust_Vsimv_Mode(UWORD16 *Value,
                                       UWORD16 Id)
{
/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

	UWORD16 CurrentMode = DB_ControlRead(CURRENT_MODE_U16);

	UWORD16 AdjustMode = DB_ConfigRead(ADJUST_MODE_U16);

	switch (Id)
	{

/*%C  Vol control writing function call */
		case ADJUST_VOL_CONTROL_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_Vol_Control(Value);	

			break;
		}

/*%C  Ti control writing */
		case ADJUST_TI_CONTROL_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_Ti_Control(Value);	

			break;
		}

/*%C  Control R writing function call */
		case ADJUST_CONTROL_R_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_Control_R(Value);	
			break;
		}

/*%C  P support writing */
		case ADJUST_P_SUPPORT_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_P_Support(Value);	
			break;
		}

/*%C  Peep writing */
		case ADJUST_PEEP_U16:
		{
 			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_Peep(Value);
			break;
		}

/*%C  Peep writing */
		case PEEP_NO_SELECT_U16:
		{
		   DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[PEEP_NO_SELECT_U16],
										   *Value);
			Function_Result = TRUE;
			break;
		}

/*%C  Apnea time writing function call */
		case ADJUST_APNEA_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_Apnea_Time(Value);
			break;
		}

/*%C  Apnea time no select writing */
		case AUTO_APNEA_SELECT_U16:
		{
         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[AUTO_APNEA_SELECT_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  Insp sens writing */
		case ADJUST_INSP_SENS_U16:
		{
         	DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_INSP_SENS_U16],
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

/*%C  Exh sens writing*/
		case ADJUST_EXH_SENS_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_Exh_Sens(Value);					

			break;
		}

/*%C  Exh sens limits check function call */
		case ADJUST_EXH_SENS_NEGATIVE_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_Exh_Sens_Neg(Value);					
			break;
		}

/*%C  Low pip writing */
		case ADJUST_LOW_PIP_U16:
		{
         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_LOW_PIP_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High pip writing*/
		case ADJUST_HIGH_PIP_U16:
		{
         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_HIGH_PIP_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}


/*%C  Low vti writing*/
		case ADJUST_LOW_VTI_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_Low_Vti(Value);
			break;
		}

/*%C  Low vti no select writing */
		case LOW_VTI_NO_SELECT_U16:
		{
         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[LOW_VTI_NO_SELECT_U16],
										   *Value);
			Function_Result = TRUE;
			break;
		}

/*%C  High vti writing*/
		case ADJUST_HIGH_VTI_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_High_Vti(Value);
			break;
		}

/*%C  High vti no select writing */
		case HIGH_VTI_NO_SELECT_U16:
		{
         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[HIGH_VTI_NO_SELECT_U16],
										   *Value);
			Function_Result = TRUE;
			break;
		}

/*%C  Low vte writing */
		case ADJUST_LOW_VTE_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_Low_Vte(Value);
			break;
		}

/*%C  Low vte no select writing */
		case LOW_VTE_NO_SELECT_U16:
		{
         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[LOW_VTE_NO_SELECT_U16],
										   *Value);
			Function_Result = TRUE;
			break;
		}

/*%C  High vte writing */
		case ADJUST_HIGH_VTE_U16:
		{
			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_High_Vte(Value);
			break;
		}

/*%C  High vte no select writing */
		case HIGH_VTE_NO_SELECT_U16:
		{
         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[HIGH_VTE_NO_SELECT_U16],
										   *Value);
			Function_Result = TRUE;
			break;
		}

/*%C  Rise time writing*/
		case ADJUST_RISE_TIME_U16:
		{
			DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_RISE_TIME_U16],
										   *Value); 

			break;
		}
/****************************************************************************/
/* No VM alarm settings on OUS project because there is not enough space on screen */
//
///*%C  Low vm writing */
//		case ADJUST_LOW_VM_U16:
//		{
//			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_Low_Vm(Value);
//			break;
//		}
//
///*%C  Low vm no select writing */
//		case LOW_VM_NO_SELECT_U16:
//		{
//         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[LOW_VM_NO_SELECT_U16],
//										   *Value);						
//			Function_Result = TRUE;
//			break;
//		}
//
///*%C  High vm writing */
//		case ADJUST_HIGH_VM_U16:
//		{
//			Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode_High_Vm(Value);
//			break;
//		}
//
///*%C  High vm no select writing */
//		case HIGH_VM_NO_SELECT_U16:
//		{
//         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[HIGH_VM_NO_SELECT_U16],
//										   *Value);						
//			Function_Result = TRUE;
//			break;
//		}

/*%C  High R writing */
		case ADJUST_HIGH_R_U16:
		{
         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_HIGH_R_U16],
										   *Value);						
			Function_Result = TRUE;
			break;
		}

/*%C  High r no select writing */
		case HIGH_R_NO_SELECT_U16:
		{
         DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[HIGH_R_NO_SELECT_U16],
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
		DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[DISCONNECTION_DELAY_AUTO_U16],
										*Value);						
			break;
		}

		default:
		{
			Function_Result = FALSE;
			break;
		}
	}
	return(Function_Result);
}
