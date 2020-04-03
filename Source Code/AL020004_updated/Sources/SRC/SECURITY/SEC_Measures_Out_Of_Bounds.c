/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Measures_Out_Of_Bounds.c                                   */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of Out of Bounds defaults					      */
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
#include "SEC_OutBoundsAlarms.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_Measures_Out_Of_Bounds(void)
{
	UWORD16 VbatMeasureFiltered = DB_Measurement_Read(VBAT_MEASURE_FILTERED);

/*%C If VBAT_MEASURE_FILTERED < BAT_MAX_LEVEL								  */ 
	if (VbatMeasureFiltered < BAT_MAX_LEVEL)
	{
/*%C 	Then a timer is started as the default is not detected 				  */ 
		TIM_StartDecounter16(TIM_MEASURES_OUT_OF_BOUNDS,TIME_MEASURES_OUT_OF_BOUNDS);
	}
/*%C End if 																  */
/*%C If timer reached value 0, the default was detected during 300ms, 		  */
	if (TIM_ReadValue16(TIM_MEASURES_OUT_OF_BOUNDS)== 0)
	{
/*%C 	Then VOLT_OUT_OF_BOUNDS = TRUE 										  */
		DB_PowerSupply_Write(VOLT_OUT_OF_BOUNDS_FLAG,TRUE);
	}
/*%C End if 																  */
}
