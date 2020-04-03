/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_EndOfCharge_Fail.c                                         */
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of bad end of charge default					  		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "define.h"
#include "enum.h"
#include "DB_PowerSupply.h"
#include "DB_Measurement.h"
#include "DB_Control.h"
#include "SEC_EndChargeAlarms.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_EndOfCharge_Fail(void)
{
	UWORD16 MeasureVCharge = DB_Measurement_Read(MEASURE_VCHARGE);
	UWORD16 MeasureVBat = DB_Measurement_Read(MEASURE_VBAT);	
	UWORD16 Delta = ONE_HUNDRED / END_OF_CHARGE_VOLTAGE_TOLERANCE ;
	UWORD16 InitBatState = DB_Control_Read(INIT_BAT_STATE); 
	UWORD16 ChargeRunning = DB_Control_Read(CHARGE_RUNNING); 
	UWORD16 ChargeRunningFlag = FALSE;
	UWORD16 	Init_Chargeur_Fail = DB_PowerSupply_Read(INIT_CHARGEUR_FAIL);

	static UWORD16 PreviousChargeRunning = FALSE;
	Delta = END_OF_CHARGE_VOLTAGE / Delta ;
	
	if ( (PreviousChargeRunning == TRUE)
	  && (ChargeRunning == FALSE) )
	{
		ChargeRunningFlag = TRUE;
	}
	else
	{
		ChargeRunningFlag = FALSE;
	}
	
	
	/*%C if MEASURE_VCHARGE != END_OF_CHARGE_VOLTAGE +/- END_OF_CHARGE_VOLTAGE_TOLERANCE */
	/*%C during the end of charge setting voltage   */
	/*%C Or MEASURE_VBAT!= END_OF_CHARGE_VOLTAGE +/- END_OF_CHARGE_VOLTAGE_TOLERANCE */
	/*%C during the end of charge */
	
	if ( 		(Init_Chargeur_Fail == TRUE)
	  		|| (((MeasureVBat < END_OF_CHARGE_VOLTAGE - Delta)
	   	|| (MeasureVBat > END_OF_CHARGE_VOLTAGE + Delta))
		 	&& (ChargeRunningFlag == TRUE)))
	{
		DB_PowerSupply_Write(END_OF_CHARGE_FAILURE_FLAG,TRUE);
	}
		PreviousChargeRunning = ChargeRunning;
}
