/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Config_Adjust_Mode.c   	     				*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of the adjust mode in the Config base     							*/
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
#include "define.h"
#include "DRV_VarEeprom.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_IHM_Setting_Config_Adjust_Mode.h"
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Config_Adjust_Mode(UWORD16 *Value,
															 UWORD16 Increase)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;
   UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);
   UWORD16 VentilAuthorization = DB_ControlRead(VENTIL_AUTHORIZATION_U16);


/*%C  	during ventilation, only the CPAP, PRES and PSV modes are authorized	 */
	if (VentilAuthorization == TRUE)
	{
/*%C  	Valve modes management */
		if (ValveDetected == TRUE)
		{
/*%C  		CPAP mode exclusion (only leak mode) */
			if (*Value == CPAP)
			{
/*%C  			if an increase request is made, the mode following is VOL */
				if (Increase == TRUE)
				{
					*Value = VOL;			
				}
/*%C  			else the previous mode is VSIMV */
				else
				{
					*Value = PSIMV;			
				}
			}
/*%C  		else, the mode is the next one (or previous function of increasing request) */
/*%C  		the value is saturated (5 modes) */
			else
			{
				if ((SWORD16)*Value < VOL)
				{
					*Value = PSIMV;
				}
				*Value = *Value % 5;
			}
		}
/*%C  	else, leak modes management, VSIMV and VOL are forbidden */
		else
		{
/*%C  	                increase sequence for leak modes: PRES --> PSVT --> CPAP --> PRES... */
                        if (Increase == TRUE)
                        {
                                if (*Value == VOL)
                                {
                                        *Value = PRES;
                                }
                                else if (*Value == VSIMV)
                                {
                                        *Value = CPAP;
                                }
                                else if (*Value > CPAP)
                                {
                                        *Value = PRES;
                                }
                        }
/*%C  	                decrease sequence for leak modes: CPAP --> PSVT --> PRES --> CPAP...*/
                        else
                        {
                                if ((SWORD16)*Value <= VOL)
                                {
                                        *Value = CPAP;
                                }
                                else if (*Value == PSIMV)
                                {
                                        *Value = PSVT;
                                }

                        }

		}
	}
/*%C  	out of ventilation, all modes are authorized	 */
	else
	{
		if ((SWORD16)*Value < VOL)
		{
			*Value = CPAP;
		}
		else if (*Value > CPAP)
		{
			*Value = VOL;
		}
	}


   Function_Result = FALSE;



	return(Function_Result);
}
