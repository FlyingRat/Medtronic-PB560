/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SWITCH_Supply_Detection.c                                      */
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "p18f6622.h"
#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "DB_Measurement.h"
#include "DB_Control.h"
#include "CHARGE_Data.h"
#include "SWITCH_Supply_Detection.h"
	#define DECLARATION_SWITCH_DATA
#include "Switch_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SWITCH_Supply_Detection(void)
{
	UWORD16 Measure_Vacdc = DB_Measurement_Read(VACDC_MEASURE_FILTERED);
	UWORD16 Measure_Vdc = DB_Measurement_Read(VDC_MEASURE_FILTERED);	
	UWORD16 Measure_VBat = DB_Measurement_Read(VBAT_MEASURE_FILTERED);
	UWORD16 Supply_State = DB_Control_Read(SUPPLY_STATE);

	/*%C Check measure VACDC */
	if (Measure_Vacdc >= (AC_DETECTION_LEVEL))
	{
		/*%C When measure VACDC is higher than AC_DETECTION_LEVEL, AC detected */
		AC_Loss_Detected = FALSE;
	}
	if (Measure_Vacdc < AC_DETECTION_LEVEL )
	{
		/*%C When measure VACDC is lower to AC_DETECTION_LEVEL, */ 
		/*%C AC loss detected */
		AC_Loss_Detected = TRUE;

		/*%C Reset counter CHARGE_Init */
		Init_Chargeur_Autorisation = FALSE ;
	}
	
	
	/*%C Check measure VDC */
	if (	(Measure_Vdc >= DC_DETECTION_HIGH_LEVEL)
		||	((Measure_Vdc >= DC_DETECTION_LOW_LEVEL)
		&&	(DC_Loss_Detected == FALSE)))
	{
		/*%C When measure VACDC is higher than DC_DETECTION_LEVEL, DC detected */
		DC_Loss_Detected = FALSE;
	}

	if (Measure_Vdc < DC_DETECTION_LOW_LEVEL)
	{
		/*%C When measure VDC is lower to DC_DETECTION_LEVEL, */ 
		/*%C DC loss detected */
		DC_Loss_Detected = TRUE;

	}
	if (	(Measure_Vdc >= DC_DETECTION_RESUME_LEVEL)
		||	(Measure_Vdc <= DC_ZERO_LEVEL))
	{
		/*%C Update interrupt DC_LOW_LEVEL_FLAG 											*/
		DB_Control_Write(DC_LOW_LEVEL_FLAG,FALSE);
	}

	/*%C Check measure VBatterie */
	if (Measure_VBat >= VBAT_DETECTION_LEVEL)
	{
		/*%C When measure VBat is higher than BATT_DETECTION_LEVEL, BATT detected */
		BAT_Loss_Detected = FALSE;
	}
	if (Measure_VBat < VBAT_DETECTION_LEVEL)
	{
		/*%C When measure VBATT is lower to BATT_Loss_Detected, */ 
		/*%C VBatt loss detected */
		BAT_Loss_Detected = TRUE;
	}
}
