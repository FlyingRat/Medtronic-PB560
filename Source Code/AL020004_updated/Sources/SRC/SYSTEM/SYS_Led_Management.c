/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Led_Management.c                         		  		  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   Power supply leds management						      */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "typedef.h"
#include "p18f6622.h"
#include "IO_Declare.h"
#include "define.h"
#include "enum.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Measurement.h"
#include "DB_PowerSupply.h"
#include "SYS_Led_Management.h" 
/******************************************************************************/
/*                                FUNCTION BODY                               */
/******************************************************************************/

void SYS_Led_Management(void)
{
	UWORD16 MaintenanceControl = DB_Control_Read(MAINTENANCE_CONTROL);

/*%C Etat Bat 																  */
	UWORD16 ChargeBatState = DB_Control_Read(CHARGE_BAT_STATE);
	UWORD16 EndOfBatteryFlag = DB_PowerSupply_Read(END_OF_BATTERY_FLAG) ;	
	UWORD16 NoBatFlag = DB_PowerSupply_Read(NO_BAT_FLAG);
	UWORD16 IChargeSetPoint = DB_Config_Read(ICHARGE_SETPOINT);
	SWORD16  IBatMeasureFiltered = (SWORD16) DB_Measurement_Read(IBAT_MEASURE_FILTERED);

/*%C Source alimentation 													  */
	UWORD16 SupplyState = DB_Control_Read(SUPPLY_STATE);

/*%C The flag for blinking led is initialized to False 						  */
	static UWORD16 BatLedOn = FALSE;

/*%C Initialize FirstRun variable  											  */
	static UWORD16 FirstRun = TRUE ;
/*%C If MAINTENANCE_CONTROL = FALSE, then 									  */	
	if(MaintenanceControl == FALSE)
	{
/*%C 	If FirstRun variable is TRUE, then									  */
		if(FirstRun == TRUE)
		{
/*%C 		Update FirstRun value 											  */
			FirstRun = FALSE ;
/*%C 		Start decounter to initialize blink state 						  */
			TIM_StartDecounter16(SYS_BLINK_BAT_LED , TIME_BLINK_BAT_LED_CHARGE_MAX);
			TIM_StartDecounter16(SYS_BLINK_BAT_LED , TIME_BLINK_BAT_LED_CHARGE_MIN);
		}
/*%C	End if 																  */
	
/* Led AC */
/******************************************************************************/
/*%C Reading data base supply type: 										  */
/*%C	If SUPPLY_STATE = AC_SUPPLY											  */
		if (SupplyState == AC_SUPPLY)
		{
/*%C 		Then AC led is turned On: PRESENCE_AC = TRUE					  */
			PRESENCE_AC = TRUE;
		}
		else
		{
/*%C else the AC led is turned Off : PRESENCE_AC = FALSE					  */
			PRESENCE_AC = FALSE;
		}
/******************************************************************************/
	
	
	
/*%C When the device is charging the battery */
/******************************************************************************/
/*%C If CHARGE_BAT_STATE = TRUE and IBAT_MEASURE_FILTERED >ICHARGE_MIN_BAT_OK,*/
/*%C then											  						  */
		if(	(ChargeBatState == TRUE)
			&&	(IBatMeasureFiltered > ICHARGE_MIN_BAT_OK))
		{
/*% 		If blinking timer over and BatLedOn = FALSE, then				  */
			if 	((TIM_ReadValue16(SYS_BLINK_BAT_LED) == 0)		
		  		&& (BatLedOn == FALSE))
			{
/*%C 			If ICHARGE_SETPOINT = 15000, then 							  */
				if (IChargeSetPoint == 15000)
				{
/*%C				Start blinking timer with max charge delay		  		  */
					TIM_StartDecounter16(SYS_BLINK_BAT_LED , TIME_BLINK_BAT_LED_CHARGE_MAX);
				}
				else
				{
/*%C				Else start blinking timer with min charge delay			  */
					TIM_StartDecounter16(SYS_BLINK_BAT_LED , TIME_BLINK_BAT_LED_CHARGE_MIN);
				}
/*%C			End if														  */
			
/*%C 			The flag for battery led is turned to TRUE 					  */
				BatLedOn = TRUE;
			}
/*%C		End if 															  */
/*%C 		If blinking timer is over and BatLedOn = TRUE, then  			  */
			if 	((TIM_ReadValue16(SYS_BLINK_BAT_LED) == 0)		
		  		&& (BatLedOn == TRUE) )
			{
/*%C 			If ICHARGE_SETPOINT = 15000, then 							  */
				if (IChargeSetPoint == 15000)
				{
/*%C				Start blinking timer with max charge delay		  		  */
					TIM_StartDecounter16(SYS_BLINK_BAT_LED , TIME_BLINK_BAT_LED_CHARGE_MAX);
				}
				else
				{
/*%C				Else start blinking timer with min charge delay			  */
					TIM_StartDecounter16(SYS_BLINK_BAT_LED , TIME_BLINK_BAT_LED_CHARGE_MIN);
				}
/*%C			End if 														  */
/*%C 			The flag for battery led is turned to FALSE 				  */
				BatLedOn = FALSE;
			}
/*%C		End if															  */
		}
/*%C	End if 																  */
/******************************************************************************/
	
	
	
/* Led Bat */
/******************************************************************************/
/*%C If BatLedOn = TRUE and CHARGE_BAT_STATE = TRUE and 					  */
/*%C IBAT_MEASURE_FILTERED >ICHARGE_MIN_BAT_OK or (CHARGE_BAT_STATE = FALSE   */
/*%C and NO_BAT_FLAG = FALSE and SUPPLY_STATE = BAT_SUPPLY, then 			  */
		if (	((BatLedOn == TRUE)
			&&	(ChargeBatState == TRUE)
			&&	(IBatMeasureFiltered > ICHARGE_MIN_BAT_OK))
		  	|| ((ChargeBatState == FALSE)		
		   && (NoBatFlag == FALSE)
			&& (SupplyState == BAT_SUPPLY)))
		{
/*%C The battery led is turned ON. LED_ETAT_BAT = TRUE						  */
			LED_ETAT_BAT = TRUE;
		}
		else 
		{
/*%C Else the battery led is turned Off. LED_ETAT_BAT = FALSE 				  */
			LED_ETAT_BAT = FALSE;
		}
/*%C	End if 																  */
/******************************************************************************/
	}
	else
	{
		/*No function	*/	
	}
/*%C End if 																  */
}
