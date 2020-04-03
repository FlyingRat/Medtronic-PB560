/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode.c 	   	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages the different		*/
/*%C        settings for an increase or a decrease operation in DataBase    	*/
/*%C        for the VOL mode, function of Id.									  		*/
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
#include "DB_IHM_Setting_Adjust_Vol_Mode.h"
#include "DB_Current.h"

/* locate database code to specific section */
#include "locate_database_code.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Vol_Mode(UWORD16 *Value,
                                       UWORD16 Id)
{
    /* Function result declaration */
   UWORD16 Function_Result = FALSE;

    /*%C Id choice for the limits check */
	switch (Id)
	{
		case ADJUST_VOL_CONTROL_U16:
		{
            /*%C     Vol control limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_Vol_Control(Value,
																						    Id);

			break;
		}

		case ADJUST_CONTROL_R_U16:
		{
            /*%C     Control R limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_Control_R(Value,
																						  Id); 
			break;
		}

		case ADJUST_TI_CONTROL_U16:
		{
            /*%C     Ti control limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_Ti_Control(Value,
																							Id); 
			break;
		}

		case ADJUST_RAMP_U16:
		{
            /*%C     Ramp limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_Ramp(Value);

			break;
		}

		case ADJUST_PEEP_U16:
		{
            /*%C     Peep limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_Peep(Value,
  																				   Id); 
			break;
		}

		case ADJUST_INSP_SENS_U16:
		{
            /*%C     Insp sens limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_Insp_Sens(Value,
																						  Id); 
			break;
		}

		case ADJUST_LOW_PIP_U16:
		{
            /*%C     Low pip limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_Low_Pip(Value,
																					   Id); 
			break;
		}

		case ADJUST_HIGH_PIP_U16:
		{
            /*%C     High pip limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_High_Pip(Value,
																						 Id); 
			break;
		}

		case ADJUST_LOW_VTE_U16:
		{
            /*%C     Low vte limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_Low_Vte(Value,
																						Id); 

			break;
		}

		case ADJUST_HIGH_VTE_U16:
		{
            /*%C     Low vte limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_High_Vte(Value,
																						Id); 

			break;
		}

		case ADJUST_HIGH_R_U16:
		{
            /*%C     High R limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_High_R(Value,
																					  Id); 
			break;
		}

		case ADJUST_SIGH_SELECT_U16:
		{
            /*%C     Sigh Select (FALSE or TRUE) */
            Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Select(Value,
                                                                         Id);
			break;
		}

		case ADJUST_SIGH_CPT_U16:
		{
            /*%C     Sigh cpt function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Cpt(Value,
																				  		 Id); 
			break;
		}

		case ADJUST_SIGH_VT_COEF_U16:
		{
            /*%C     High R limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Vt_Coef(Value,
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

		default :
		{
			Function_Result = FALSE;
			break;
		}
	}
    return(Function_Result);
}
