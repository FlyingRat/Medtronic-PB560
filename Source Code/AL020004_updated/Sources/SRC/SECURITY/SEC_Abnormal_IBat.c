/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Abnormal_IBat.c                                            */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of anomaly of battery intensity			      */
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
#include "SEC_AbnIBatAlarms.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_Abnormal_IBat(void)
{

	SWORD16 IbatMeasureFiltered 
					= (SWORD16)DB_Measurement_Read(IBAT_MEASURE_FILTERED);
	SWORD16 BatteryTemp 
					= (SWORD16)DB_Measurement_Read(BATTERY_TEMP);
	UWORD16 BatState 
					= DB_PowerSupply_Read(BAT_STATE_U16);
	UWORD16 InitBatState 
					= DB_Control_Read(INIT_BAT_STATE);
	UWORD16 BatOpenedFlag = DB_PowerSupply_Read(BAT_OPENED_FLAG);

/*%C If IBAT_MEASURE_FILTRED < ZERO_DISCHARGE_MIN_POSITIVE_LEVEL or 	 	  */
/*%C BAT_STATE_U16 <> BAT_DISCHARGE, then   								  */
	if(	(IbatMeasureFiltered < (DISCHARGE_MIN_POSITIVE_LEVEL))
		||	(BatState !=  BAT_DISCHARGE))
	{

/*%C	If  (IBAT_MEASURE_FILTRED > ZERO_NEGATIVE_LEVEL 					  */ 
/*%C 	and  IBAT_MEASURE_FILTRED < ZERO_POSITIVE_LEVEL), then				  */
		if (	(IbatMeasureFiltered > (ZERO_NEGATIVE_LEVEL))
			&&	(IbatMeasureFiltered < (ZERO_POSITIVE_LEVEL)))
		{
/*%C 		The timer runs													  */
			TIM_StartDecounter16(TIM_ABNORMAL_IBAT,TIME_ABNORMAL_IBAT);
		}

/*%C 	Else if  BAT_STATE_U16 = BAT_CHARGE or BAT_STATE = BAT_DISCHARGE	  */
/*%C  	or  INIT_BAT_STATE = TRUE or BATTERY_TEMP < BATTERY_ABSENT_TEMP_LEVEL */
/*%C or (TIM_ReadValue16(TIM_NO_COMMUT) <> 0) or BAT_OPENED_FLAG = TRUE, then */
		else if	(	(BatState == BAT_CHARGE)
	 				|| (BatState ==  BAT_DISCHARGE)
					||	(InitBatState == TRUE)
					|| (BatteryTemp < BATTERY_ABSENT_TEMP_LEVEL)
					|| (TIM_ReadValue16(TIM_NO_COMMUT) != 0)
					||	(BatOpenedFlag == TRUE))
		{
/*%C 		The timer runs 													  */
			TIM_StartDecounter16(TIM_ABNORMAL_IBAT,TIME_ABNORMAL_IBAT);
		}
/*%C	End if																  */
	}	
/*%C End if 																  */
/*%C If delay is reached  													  */
	if(TIM_ReadValue16(TIM_ABNORMAL_IBAT)== 0)
	{
/*%C 	Then ABNORMAL_IBAT_FLAG = TRUE 										  */	
		DB_PowerSupply_Write(ABNORMAL_IBAT_FLAG,TRUE);
	}
	else
	{
		/*%C No function */
	}
/*%C End if 																  */
}
