/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SWITCH_State_Control.c                                      	  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   Management of supply switch							  */
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
#include "Switch_Data.h"
#include "DB_Measurement.h"
#include "DB_PowerSupply.h"
#include "SWITCH_State_Control.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SWITCH_State_Control(void)
{

	UWORD16 FailureMesVACDCFlag = DB_PowerSupply_Read(FAILURE_MES_VACDC_FLAG);
	UWORD16 FailureMesVDCFlag = DB_PowerSupply_Read(FAILURE_MES_VDC_FLAG);
	UWORD16 EndOfBatteryFlag = DB_PowerSupply_Read(END_OF_BATTERY_FLAG); 
	UWORD16 Supply_State = DB_Control_Read(SUPPLY_STATE);
	UWORD16 DcLowLevelFlag = DB_Control_Read(DC_LOW_LEVEL_FLAG);
	UWORD16 MeasureVDC = DB_Measurement_Read(MEASURE_VDC);

	static UWORD16 FirstRunTimerNoCommut = FALSE ;


/******************************************************************************/
/*%C VACDC Commutation 														  */
/******************************************************************************/

	if ( 		
/*%C If AC_Loss_Detected = FALSE and FAILURE_MES_VACDC_FLAG = FALSE 		  */
/*%C The power supply source remain AC 										  */
/*%C 31.2 < VACDC < 34.95 Normal working conditions							  */
				(AC_Loss_Detected == FALSE)
		 	&& (FailureMesVACDCFlag == FALSE))
	{
/*%C 	Then Check if supply state is different from AC 					  */
/*%C 	If (SUPPLY_STATE <> AC_SUPPLY) and FirstRunTimerNoCommut = FALSE	  */
		if(	(Supply_State != AC_SUPPLY)
			&&	(FirstRunTimerNoCommut == FALSE))
		{
/*%C 		Then FirstRunTimerNoCommut = TRUE 	 							  */
			FirstRunTimerNoCommut = TRUE ;
/*%C 		And run Commut Timer 											  */
			TIM_StartDecounter16(TIM_NO_COMMUT,TIME_NO_COMMUT);
		}
/*%C	End if 																  */		
/*%C 	If commut delay is reached and SUPPLY_STATE <> AC_SUPPLY 			  */
		if(	(TIM_ReadValue16(TIM_NO_COMMUT) == 0)
			&&	(Supply_State != AC_SUPPLY))
		{
/*%C 	Then update supply state and database (control, power supply) 		  */
/*%C 	Update battery state (no discharge) 								  */
/*%C 	Start timer of transition 											  */
			Supply_State = AC_SUPPLY;
			DB_Control_Write(SUPPLY_STATE,Supply_State);
			DB_PowerSupply_Write(POWER_TYPE_U16,AC_SUPPLY);
			DB_Control_Write(DISCHARGE_BAT_STATE,FALSE);
			DB_PowerSupply_Write(BAT_STATE_U16,BAT_IDLE);
		}
/*%C	End if 																  */
	}
	
	else if (
/*%C Else if FAILURE_MES_VACDC_FLAG = TRUE and AC_Loss_Detected = FALSE and   */
/*%C SUPPLY_STATE = AC_SUPPLY 												  */
/*%C 	Then Failure Measure VACDC and current state is AC 					  */
 	  			(FailureMesVACDCFlag == TRUE)
 		 	&& (AC_Loss_Detected == FALSE)
			&&	(Supply_State == AC_SUPPLY))
	{
		/*%C No Function */
		/*%C Current state is AC, so stay on AC Supply */
	}

/******************************************************************************/
/*%C DC Commutation 														  */
/******************************************************************************/
/*%C Else If DC_LOW_LEVEL_FLAG = FALSE and DC_Loss_Detected = FALSE and 	  */
/*%C FAILURE_MES_VDC_FLAG = FALSE 											  */
	else if(	(DcLowLevelFlag == FALSE)
			&&	(DC_Loss_Detected == FALSE)
			&& (FailureMesVDCFlag == FALSE))
	{
/*%C 	Then if SUPPLY_STATE <> DC_SUPPLY and FirstRunTimerNoCommut = FALSE   */
		if(	(Supply_State != DC_SUPPLY)
			&&	(FirstRunTimerNoCommut == FALSE))
		{	
/*%C 		Then If MEASURE_VDC >= DC_PACK_LEVEL 							  */
			if(MeasureVDC >= DC_PACK_LEVEL)
			{
/*%C 			FirstRunTimerNoCommut = TRUE 								  */
				FirstRunTimerNoCommut = TRUE ;
/*%C 			Run Commut Timer 											  */
				TIM_StartDecounter16(TIM_NO_COMMUT,TIME_NO_COMMUT_PACK);
			}
/*%C 		Else 															  */
			else
			{
/*%C 			FirstRunTimerNoCommut = TRUE 								  */
				FirstRunTimerNoCommut = TRUE ;
/*%C 			Run Commut Timer 											  */
				TIM_StartDecounter16(TIM_NO_COMMUT,TIME_NO_COMMUT);
			}
/*%C		End if															  */
		}
/*%C	End if																  */
/*%C 	If commut delay is reached and SUPPLY_STATE <> DC_SUPPLY			  */
		if(	(TIM_ReadValue16(TIM_NO_COMMUT) == 0)
			&&	(Supply_State != DC_SUPPLY))
		{
/*%C 		Then Update supply state and database (control, power supply) 	  */
/*%C 		Update battery state (no discharge) 							  */
/*%C 		Start timer of transition 										  */
			Supply_State = DC_SUPPLY;
			DB_Control_Write(SUPPLY_STATE,Supply_State);
			DB_PowerSupply_Write(POWER_TYPE_U16,DC_SUPPLY);
			DB_Control_Write(DISCHARGE_BAT_STATE,FALSE);
			DB_PowerSupply_Write(BAT_STATE_U16,BAT_IDLE);
		}
/*%C	End if 																  */
	}
/*%C Else If FAILURE_MES_VDC_FLAG = TRUE and DC_Loss_Detected = FALSE and 	  */
/*%C SUPPLY_STATE = DC_SUPPLY, then										      */
	else if (
				(FailureMesVDCFlag == TRUE)
			&& (DC_Loss_Detected == FALSE)
			&& (Supply_State == DC_SUPPLY))
	{
		/*%C No Function */
		/*%C Current state is DC, so stay on DC Supply 						  */
	}

/******************************************************************************/
/*%C Battery Commutation 													  */
/******************************************************************************/
/*%C All other cases 														  */
/*%C Else 																	  */
	else
	{
/*%C 	If SUPPLY_STATE <> BAT_SUPPLY and FirstRunTimerNoCommut = FALSE 	  */
		if(	(Supply_State != BAT_SUPPLY)
			&&	(FirstRunTimerNoCommut == FALSE))
		{	
/*%C 		Then FirstRunTimerNoCommut = TRUE 								  */
			FirstRunTimerNoCommut = TRUE ;
/*%C 		Run Commut Timer												  */
			TIM_StartDecounter16(TIM_NO_COMMUT,TIME_NO_COMMUT);
		}
/*%C	End if 																  */
/*%C If commut delay is reached and SUPPLY_STATE <> BAT_SUPPLY				  */
		if(	(TIM_ReadValue16(TIM_NO_COMMUT) == 0)
			&&	(Supply_State != BAT_SUPPLY))
		{
/*%C 		Then Update supply state and database (control, power supply) 	  */
/*%C 		Update battery state (no discharge) 							  */
/*%C 		Start timer of transition 										  */
			Supply_State = BAT_SUPPLY;
			DB_Control_Write(SUPPLY_STATE,Supply_State);
			DB_PowerSupply_Write(POWER_TYPE_U16,BAT_SUPPLY);
			DB_Control_Write(DISCHARGE_BAT_STATE,TRUE);
	
		}
/*%C	End if 																  */
	}
/*%C End if 																  */
/*%C If timer of transition (TIME_NO_COMMUT) reached						  */
	if (TIM_ReadValue16(TIM_NO_COMMUT) == 0)
	{ 
/*%C 	Then FirstRunTimerNoCommut = FALSE 									  */
		FirstRunTimerNoCommut = FALSE ;	
/*%C 	Call Commutation fonction with the new supply state 				  */	
		DRV_Switch(Supply_State);
	}

/*%C Else */
	else
	{
/*%C 	On transition call commutation fonction with OU_DIODE 				  */
		DB_PowerSupply_Write(POWER_TYPE_U16,AC_DC_BAT);
		DB_Control_Write(SUPPLY_STATE,AC_DC_BAT);
		DRV_Switch(AC_DC_BAT);
	}
/*%C End if 																  */
}
