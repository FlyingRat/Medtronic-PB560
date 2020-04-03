/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Charge_Fail.c                                              */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of battery charge default						  */
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
#include "DB_Config.h"
#include "DB_Control.h"
#include "SEC_ChargeFailAlarms.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_Charge_Fail(void)
{
UWORD16 VbatMeasureFiltered = DB_Measurement_Read(VBAT_MEASURE_FILTERED);
SWORD16 Ibat = (SWORD16)DB_Measurement_Read(I_BAT);
UWORD16 ChargeRunning = DB_Control_Read(CHARGE_RUNNING); 
UWORD16 IChargeSetpoint = DB_Config_Read(ICHARGE_SETPOINT);
UWORD16 Delta = IChargeSetpoint / 100 ;
Delta = Delta * ICHARGE_SETPOINT_TOLERANCE ;

/*%C If CHARGE_RUNNING = FALSE												  */ 
	if (ChargeRunning == FALSE)
	{
/*%C 	Then a timer runs 													  */
		TIM_StartDecounter16(TIM_CHARGE_RUNNING,TIME_CHARGE_RUNNING);
	}
/*%C End if 																  */
/*%C If the timer is over 													  */
	
	if (TIM_ReadValue16(TIM_CHARGE_RUNNING)== 0)
	{
/*%C 	Then the charge is running for 12s 									  */
/*%C 	if (IBAT_MEASURE_FILTRED < ICHARGE_SETPOINT x 						  */ 
/*%C	(1+ICHARGE_SETPOINT_TOLERANCE) and IBAT_MEASURE_FILTRED >			  */
/*%C 	ICHARGE_SETPOINT x (1- ICHARGE_SETPOINT_TOLERANCE)) 				  */
/*%C 	or VBAT_MESURE_FILTRED > TENSION_LEVEL_FOR_CONSTANT_CURRENT) 		  */
		if ( ( (Ibat < IChargeSetpoint + Delta )
		    && (Ibat > IChargeSetpoint - Delta) )
		  || (VbatMeasureFiltered > TENSION_LEVEL_FOR_CONSTANT_CURRENT) )
		{
/*%C 		Then a timer runs 												  */
			TIM_StartDecounter16(SEC_CHARGE_FAIL,TIME_CHARGE_FAIL);
		}
/*%C	End if 																  */
/*%C 	If the timer is over 												  */
		if (TIM_ReadValue16(SEC_CHARGE_FAIL)== 0)
		{
/*%C 		Then CHARGE_FAIL_FLAG = TRUE 									  */
			DB_PowerSupply_Write(CHARGE_FAIL_FLAG,TRUE);
		}
/*%C	End if 																  */
	}
/*%C End if 																  */
}
