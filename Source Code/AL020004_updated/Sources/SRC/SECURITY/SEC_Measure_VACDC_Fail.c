/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Measure_VACDC_Fail.c                              		  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of AC DC supply default				      	  */
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
#include "DB_Control.h"
#include "SEC_VACDCFailAlarms.h"
#include "Switch_Data.h"
/******************************************************************************/
/*                            FUNCTION BODY                        			  */
/******************************************************************************/

void SEC_Measure_VACDC_Fail(void)
{
	UWORD16 MeasureVACDC = DB_Measurement_Read(MEASURE_VACDC);
	UWORD16 Delta = (TYPICAL_VACDC_VALUE * MEASURE_VACDC_TOLERANCE) / 100 ;

/*%C If the default is not detected :										  */ 
/*%C If (MEASURE_VACDC >  TYPICAL_VACDC_VALUE x (1 - MEASURE_VACDC_TOLERANCE) */
/*%C and MEASURE_VACDC < TYPICAL_VACDC_VALUE x (1 + MEASURE_VACDC_TOLERANCE)) */
/*%C or AC_Loss_Detected = TRUE												  */
	
	if (		((MeasureVACDC > TYPICAL_VACDC_VALUE - Delta)
	 	 	&& (MeasureVACDC < TYPICAL_VACDC_VALUE + Delta))
			|| (AC_Loss_Detected == TRUE))
	{
/*%C 	Then a timer runs 													  */
		TIM_StartDecounter16(TIM_VACDC_FAIL,TIME_VACDC_FAIL);
	}
/*%C End if 																  */

/*%C If the timer is over 													  */
	if (TIM_ReadValue16(TIM_VACDC_FAIL)== 0)
	{
/*%C 	Then FAILURE_MES_VACDC_FLAG = TRUE 									  */
		DB_PowerSupply_Write(FAILURE_MES_VACDC_FLAG,TRUE);
	}
/*%C Else if (MEASURE_VACDC >= TYPICAL_VACDC_VALUE	x 						  */ 
/*%C(1-MEASURE_VACDC_TOLERANCE)												  */
/*%C and MEASURE_VACDC <= TYPICAL_VACDC_VALUE x (1+MEASURE_VACDC_TOLERANCE))  */
/*%C or AC_Loss_Detected = TRUE												  */
	else if ( 	((MeasureVACDC >= TYPICAL_VACDC_VALUE - Delta)
			 	&& (MeasureVACDC <= TYPICAL_VACDC_VALUE + Delta))
				||	(AC_Loss_Detected == TRUE))
	{
/*%C 	Then FAILURE_MES_VACDC_FLAG = FALSE 								  */
		DB_PowerSupply_Write(FAILURE_MES_VACDC_FLAG,FALSE);
	}
/*%C End if 																  */
}
