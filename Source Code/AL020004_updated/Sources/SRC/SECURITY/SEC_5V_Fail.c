/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_5V_Fail.c                                               	  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of 5 V supply default					      	  */
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
#include "SEC_5VAlarms.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_5V_Fail(void)
{
	
	UWORD16 Measure5V = DB_Measurement_Read(MEASURE_5V);
	UWORD16 Delta = (TYPICAL_5V_VALUE * MEASURE_5V_TOLERANCE) / 100;

/*%C If the default is not detected : 										  */ 
/*%C If MEASURE_5V > TYPICAL_5V_VALUE x (1 - MEASURE_5V_TOLERANCE) 			  */
/*%C and MEASURE_5V < TYPICAL_5V_VALUE x (1 + MEASURE_5V_TOLERANCE), then 	  */
	if ( (Measure5V > TYPICAL_5V_VALUE - Delta)
	  && (Measure5V < TYPICAL_5V_VALUE + Delta) )	
	{
/*%C 	Timer runs 															  */
		TIM_StartDecounter16(TIM_5V_FAIL,TIME_5V_FAIL);
	}
/*%C End if 																  */
/*%C If the timer is over, then  											  */
	if (TIM_ReadValue16(TIM_5V_FAIL)== 0)
	{
/*%C 	FAILURE_5V_FLAG = TRUE 												  */
		DB_PowerSupply_Write(FAILURE_5V_FLAG,TRUE);
	}

/*%C Else if MEASURE_5V >  TYPICAL__5V_VALUE x (1-MEASURE_5V_TOLERANCE) 	  */
/*%C and MEASURE_5V < TYPICAL__5V_VALUE x (1+MEASURE_5V_TOLERANCE), then     */
	else if ( (Measure5V >TYPICAL_5V_VALUE - Delta)
	 	    && (Measure5V < TYPICAL_5V_VALUE + Delta) )
	{
/*%C 	FAILURE_5V_FLAG = FALSE 											  */
 	 	DB_PowerSupply_Write(FAILURE_5V_FLAG,FALSE);
	}
/*%C End if 															 	  */
}
