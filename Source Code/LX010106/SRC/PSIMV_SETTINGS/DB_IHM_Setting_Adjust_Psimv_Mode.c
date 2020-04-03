/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psimv_Mode.c  		                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function schedules the different	*/
/*%C        settings in DataBase for the Psimv mode: 									*/
/*                                                            				  		*/
/******************************************************************************/
/*%I  Input Parameter :				Id                                    		  	*/
/*%IO Input/Output Parameter : 	*Value  	        			                  	*/
/*%O  Output Parameter : 			True/False 	                 				  		*/
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "DB_Current.h"
#include "DB_IHM_Setting_Adjust_Psimv_Mode.h"

/* locate database code to specific section */
#include "locate_database_code.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode(UWORD16 *Value,
                                         UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Id choice for the limits check */
	switch (Id)
	{
/*%C  P control limits check function call */
		case ADJUST_P_CONTROL_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_PControl(Value,
			                                                            Id);
			break;
		}

/*%C  Ti control limits check function call */
		case ADJUST_TI_CONTROL_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Psimv_ModeTiControl(Value,
			                                                             Id);
			break;
		}

/*%C  Control R limits check function call */
		case ADJUST_CONTROL_R_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_ControlR(Value,
			                                                             Id);
			break;
		}

/*%C  P support limits check function call */
		case ADJUST_P_SUPPORT_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_PSupport(Value,
			                                                            Id);
			break;
		}

/*%C  Peep limits check function call */
		case ADJUST_PEEP_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_Peep(Value,
			                                                        Id);
			break;
		}

/*%C  Apnea limits check function call */
		case ADJUST_APNEA_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_Apnea_Time(Value,
			                                                              Id);
			break;
		}

/*%C  Insp sens limits check function call */
		case ADJUST_INSP_SENS_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_Insp_Sens(Value,
			                                                             Id);
			break;
		}

/*%C  Exh sens limits check function call */
		case ADJUST_EXH_SENS_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_Exh_Sens(Value,
			                                                             Id);
			break;
		}

/*%C  Exh sens limits check function call */
		case ADJUST_EXH_SENS_NEGATIVE_U16:
		{
/*%C     Exh sens writing function call  */
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_Exh_Sens_Neg(Value,
			                                                           Id);
			break;
		}

/*%C  Low vti limits check function call */
		case ADJUST_LOW_VTI_U16:
		{
		   Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_Low_Vti(Value,
			                                                           Id);
			break;
		}

/*%C  High vti limits check function call */
		case ADJUST_HIGH_VTI_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_High_Vti(Value,
			                                                            Id);
			break;
		}

/*%C  Low vte limits check function call */
		case ADJUST_LOW_VTE_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_Low_Vte(Value,
			                                                           Id);
			break;
		}

		case ADJUST_HIGH_VTE_U16:
		{
/*%C     Low vte limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_High_Vte(Value,
																						  Id); 

			break;
		}

		case ADJUST_RISE_TIME_U16:
		{
/*%C     Rise Time limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_Rise_Time(Value,
																						  Id); 

			break;
		}

/****************************************************************************/
/* No VM alarm settings on OUS project because there is not enough space on screen */
/*%C  Low vm limits check function call */
//		case ADJUST_LOW_VM_U16:
//		{
//			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_Low_Vm(Value,
//			                                                          Id);
//			break;
//		}
//
///*%C  High vm limits check function call */
//		case ADJUST_HIGH_VM_U16:
//		{
//			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_High_Vm(Value,
//			                                                           Id);
//			break;
//		}
/****************************************************************************/
/*%C  High R limits check function call */
		case ADJUST_HIGH_R_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_High_R(Value,
		                                                          Id);
			break;
		}
/*%C  Disconnection delay function call */
		case ADJUST_DISCONNECTION_DELAY_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Cpap_Mode_Disco_Delay(Value,
			                                                        		Id);
			Function_Result = DB_IHM_Setting_Adjust_Pres_Mode_Disco_Delay(Value,
			                                                        		Id);
			Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode_Disco_Delay(Value,
			                                                        		Id);
			Function_Result = DB_IHM_Setting_Adjust_Psv_Mode_Disco_Delay(Value,
			                                                        		Id);
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_Disco_Delay(Value,
			                                                        		Id);
			Function_Result = DB_IHM_Setting_Adjust_Vsimv_Mode_Disco_Delay(Value,
			                                                        		Id);

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
