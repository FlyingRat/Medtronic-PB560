/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Temp_Sensor_Failure.c                                      */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of anomaly of Temperature sensor		     	  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "DB_PowerSupply.h"
#include "DB_Measurement.h"
#include "SEC_TempSensAlarms.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_Temp_Sensor_Failure(void)
{
	SWORD16 AmbientTemp = (SWORD16)DB_PowerSupply_Read(AMBIENT_TEMP_S16);

/*%C If TEMP_AMB < TEMP_SENSOR_FAILURE_MIN,  ie. minus 25 degree celsius 	  */
/*%C or TEMP_AMB > TEMP_SENSOR_FAILURE_MAX  ie. greater than 75 degree celsius*/
	if ( (AmbientTemp < TEMP_SENSOR_FAILURE_MIN)
	  || (AmbientTemp > TEMP_SENSOR_FAILURE_MAX) )
	{
/*%C 	Then TEMP_SENSOR_FAILURE_FLAG = TRUE  						  		  */
		DB_PowerSupply_Write(TEMP_SENSOR_FAILURE_FLAG,TRUE);
	}
	else
	{
/*%C Else TEMP_SENSOR_FAILURE_FLAG = FALSE  								  */
		DB_PowerSupply_Write(TEMP_SENSOR_FAILURE_FLAG,FALSE);
	}
/*%C End if 																  */
}
