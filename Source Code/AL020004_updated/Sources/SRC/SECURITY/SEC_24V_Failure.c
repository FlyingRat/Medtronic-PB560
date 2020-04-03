/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_24V_Fail.c                                              	  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of 24 V supply default					      	  */
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
#include "DB_Control.h"
#include "DB_Measurement.h"
#include "DB_Control.h"
#include "SEC_24VAlarms.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_24V_Fail(void)
{
	UWORD16 Measure24VUtil = DB_Measurement_Read(MEASURE_24VUTIL);
	UWORD16 Delta = (TYPICAL_24VUTIL_VALUE * MEASURE_24VUTIL_TOLERANCE) / 100;

	/*%C If the default is not detected : */ 
	/*%C If MEASURE_24VUTIL > TYPICAL_24VUTIL_VALUE x (1 - MEASURE_24VUTIL_TOLERANCE)
	     or MEASURE_24VUTIL < TYPICAL_24VUTIL_VALUE x (1 + MEASURE_24VUTIL_TOLERANCE)*/
	if ( (Measure24VUtil > TYPICAL_24VUTIL_VALUE - Delta)
	  && (Measure24VUtil < TYPICAL_24VUTIL_VALUE + Delta) )
	{
		/*%C Then a timer runs */
		TIM_StartDecounter16(TIM_24V_FAIL,TIME_24V_FAIL);
	}
	
	/*%C If the delay is over */
	/*%C The flag FAILURE_24V_FLAG is set, and flags CPU_ON, */
	/*%C VENTIL_AUTHORIZATION, MAINTENANCE_MODE are reset */
	if (TIM_ReadValue16(TIM_24V_FAIL) == 0)
	{
		/*%C Update FAILURE_24V_FLAG */
		DB_PowerSupply_Write(FAILURE_24V_FLAG,TRUE);
		/*%C Update the CPU_ON Flag */
		DB_Control_Write(CPU_ON,FALSE);

		/*%C Update the ventilation authorization Flag */
		DB_PowerSupply_Write(VENTIL_AUTHORIZATION,FALSE);
		/*%C Update the maintenance mode Flag */
		DB_PowerSupply_Write(MAINTENANCE_MODE,FALSE);
	}

	/*%C Else if MEASURE_24VUTIL >= TYPICAL_24VUTIL_VALUE x (1-MEASURE_24VUTIL_TOLERANCE)*/
    /*%C and MEASURE_24VUTIL <=  TYPICAL_24VUTIL_VALUE x (1+MEASURE_24VUTIL_TOLERANCE)*/

	else if ( (Measure24VUtil > TYPICAL_24VUTIL_VALUE - Delta)
	 		 && (Measure24VUtil < TYPICAL_24VUTIL_VALUE + Delta) )
	{
		/*%C Then flag FAILURE_24V_FLAG is reset */
		/*%C and CPU_ON is set */
 	 	DB_PowerSupply_Write(FAILURE_24V_FLAG,FALSE);
		/*%C Update the CPU_ON Flag */
		DB_Control_Write(CPU_ON,TRUE);
	}
}
