/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Battery_Unchargeable.c                                     */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of Not chargeable battery default			      */
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
#include "DB_Control.h"
#include "DB_PowerSupply.h"
#include "DB_Measurement.h"
#include "SEC_BatUnchAlarms.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_Battery_Unchargeable(void)
{

SWORD16 IChargeMaxMeasured = DB_Measurement_Read(I_CHARGE_MAX_MEASURED);
UWORD16 ChargeRunning = DB_Control_Read(CHARGE_RUNNING);
UWORD16 InitBatState = DB_Control_Read(INIT_BAT_STATE);  
UWORD16 ChargeFallFlag = FALSE;
static UWORD16 PreviousChargeRunning = FALSE;


/*%C if PreviousChargeRunning = TRUE and CHARGE_RUNNING = FALSE				  */
/*%C and INIT_BAT_STATE = FALSE, then 										  */

	if ( 	(PreviousChargeRunning == TRUE)
	  	&& (ChargeRunning == FALSE)
		&&	(InitBatState == FALSE))
	{
/*%C	ChargeFall = TRUE 													  */
		ChargeFallFlag = TRUE;
	}
/*%C Else ChargeFallFlag = FALSE											  */
	else
	{
		ChargeFallFlag = FALSE;
	}
/*%C End if 															   	  */
/*%C If I_CHARGE_MAX_MEASURED < ICHARGE_MIN_LEVEL and ChargeFallFlag = TRUE   */
	if ( (IChargeMaxMeasured < ICHARGE_MIN_LEVEL)
	  && (ChargeFallFlag == TRUE) )
	{
/*%C	BAT_UNCHARGEABLE_FLAG = TRUE										  */
		DB_PowerSupply_Write(BAT_UNCHARGEABLE_FLAG,TRUE);
	}
/*%C End if 																  */
	PreviousChargeRunning = ChargeRunning;
}
