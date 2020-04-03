/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Cpap_Mode.c  	 	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function schedules the different	*/
/*%C        settings in DataBase for the CPAP mode: 									*/
/*                                                            				  		*/
/******************************************************************************/
/*%I Input Parameter :				Id                                    		  	*/
/*%IO Input/Output Parameter : 	*Value  	        			                  	*/
/*%O Output Parameter : 			True/False 	                 				  		*/
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "DB_Current.h"
#include "DB_IHM_Setting_Adjust_Cpap_Mode.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Cpap_Mode(UWORD16 *Value, 
                                       UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Id choice for the limits check */
	switch (Id)
	{
/*%C  Peep limits check function call */
		case ADJUST_PEEP_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Cpap_Mode_Peep(Value,
			                                                      Id);
			break;
		}
/*%C  Apnea limits check function call */
		case ADJUST_APNEA_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Cpap_Mode_Apnea_Time(Value,
			                                                            Id);
			break;
		}

/*%C  Low vti limits check function call */
		case ADJUST_LOW_VTI_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Cpap_Mode_Low_Vti(Value,
			                                                         Id);
			break;
		}

/*%C  High Vti limits check function call */
		case ADJUST_HIGH_VTI_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Cpap_Mode_High_Vti(Value,
			                                                          Id);
			break;
		}
/*%C  High R limits check function call */
		case ADJUST_HIGH_R_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Cpap_Mode_High_R(Value,
			                                                        Id);
			break;
		}
/*%C  High Leak limits check function call */
		case ADJUST_HIGH_LEAK_U16:
		{
			Function_Result = DB_IHM_Setting_Adjust_Cpap_Mode_High_Leak(Value,
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
