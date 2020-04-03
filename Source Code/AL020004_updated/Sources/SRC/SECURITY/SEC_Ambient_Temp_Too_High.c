/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Ambient_Temp_Too_High.c                                    */
/*													 				          */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of anomaly Temperature too high		     	  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "define.h"
#include "typedef.h"
#include "enum.h"
#include "DB_PowerSupply.h"
#include "DB_Measurement.h"
#include "SEC_AmbTempAlarms.h"



/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_Ambient_Temp_Too_High(void)
{

	UWORD16 TempSensorFailureFlag = DB_PowerSupply_Read(TEMP_SENSOR_FAILURE_FLAG);		
	SWORD16 TempAmb = (SWORD16)DB_Measurement_Read(TEMP_AMB);

/*%C If TEMP_AMB > AMBIENT_TEMP_MAX 					 					  */
/*%C and TEMP_SENSOR_FAILURE_FLAG = FALSE, then						 		  */

	if ( (TempAmb > AMBIENT_TEMP_MAX)
	  && (TempSensorFailureFlag == FALSE) )
	{
/*%C 	AMBIENT_TEMP_TOO_HIGH = TRUE										  */	
		DB_PowerSupply_Write(AMBIENT_TEMP_TOO_HIGH,TRUE);
	}

/*%C Else if (TEMP_AMB < AMBIENT_TEMP_MAX - AMBIANT_TEMP_HYSTERESIS			  */
/*%C or TEMP_SENSOR_FAILURE_FLAG = TRUE) then alarm is reset 				  */

	else if ( (TempAmb < (AMBIENT_TEMP_MAX  - AMBIANT_TEMP_HYSTERESIS))
			 || (TempSensorFailureFlag == TRUE) )
	{
/*%C 	AMBIENT_TEMP_TOO_HIGH = FALSE 										  */	
		DB_PowerSupply_Write(AMBIENT_TEMP_TOO_HIGH,FALSE);
	}
/*%C End if 																  */
}
