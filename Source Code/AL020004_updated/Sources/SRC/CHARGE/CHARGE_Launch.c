/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CHARGE_Launch.c                                                */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     													  */
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
#include "CHARGE_Launch.h"
	#define DECLARATION_CHARGE_DATA
#include "CHARGE_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void CHARGE_Launch(void)
{

UWORD16 	Charge_Bat_State = DB_Control_Read(CHARGE_BAT_STATE);
UWORD16 	Init_Bat_State = DB_Control_Read(INIT_BAT_STATE);
UWORD16 	Charge_Authorization = DB_Control_Read(CHARGE_AUTHORIZATION);
UWORD16 	Sampling_OK = DB_Control_Read(SAMPLING_OK);	
UWORD16 	Volt_Out_Of_Bounds_Flag = DB_PowerSupply_Read(VOLT_OUT_OF_BOUNDS_FLAG);
UWORD16 	Charge_Fail_Flag = DB_PowerSupply_Read(CHARGE_FAIL_FLAG);
UWORD16 	Charge_Time_Too_Long_Flag = DB_PowerSupply_Read(CHARGE_TIME_TOO_LONG_FLAG);
UWORD16 	Charge_Temp_Fail_Flag = DB_PowerSupply_Read(CHARGE_TEMP_FAIL_FLAG);
UWORD16 	Init_Chargeur_Fail = DB_PowerSupply_Read(INIT_CHARGEUR_FAIL);
UWORD16  	Measure_Vbat = DB_Measurement_Read(MEASURE_VBAT);
UWORD16 	BatUnchargeableFlag = DB_PowerSupply_Read(BAT_UNCHARGEABLE_FLAG);
UWORD16 	CoolingFanFailureFlag = DB_PowerSupply_Read(COOLING_FAN_FAILURE_FLAG);
UWORD16 	AmbiantTempTooHigh	= DB_PowerSupply_Read(AMBIENT_TEMP_TOO_HIGH);

SWORD16  IBatMeasureFiltered = (SWORD16) DB_Measurement_Read(IBAT_MEASURE_FILTERED);
SWORD16  BatteryTemp = (SWORD16)DB_Measurement_Read(BATTERY_TEMP);
SWORD16  IChargeMaxMeasured = DB_Measurement_Read(I_CHARGE_MAX_MEASURED);
UWORD16  MaintenanceControl = DB_Control_Read(MAINTENANCE_CONTROL);

UBYTE 	Supply_State = (UBYTE)DB_Control_Read(SUPPLY_STATE);
UWORD16 Charge_Cut_Off_Delay = 0;

static UWORD16 PreviousMaintenanceControl = FALSE ;
static UWORD16 FirstInitCharge = TRUE ;
static UWORD16 ChargeInitialization = FALSE ;


/*%C If MAINTENANCE_CONTROL = FALSE, then 									  */
	if(MaintenanceControl == FALSE)
	{

/* Fonction Init */
/*%C Check condition for charging initialization : 							  */
/*%C If SUPPLY_STATE = AC_SUPPLY and INIT_CHARGEUR_FAIL = FALSE 			  */
/*%C and CHARGE_AUTHORIZATION = FALSE			  							  */
/*%C and SAMPLING_OK = TRUE and BATTERY_TEMP >  BATTERY_ABSENT_TEMP_LEVEL 	  */
/*%C and VOLT_OUT_OF_BOUNDS_FLAG = FALSE and CHARGE_FAIL_FLAG = FALSE		  */
/*%C and CHARGE_TIME_TOO_LONG_FLAG = FALSE and CHARGE_TEMP_FAIL_FLAG = FALSE  */
/*%C and BAT_UNCHARGEABLE_FLAG = FALSE	and									  */
/*%C (COOLING_FAN_FAILURE_FLAG = FALSE or AMBIENT_TEMP_TOO_HIGH = FALSE), then*/
	
	
		if((Supply_State == AC_SUPPLY)
			&& (Init_Chargeur_Fail == FALSE)
			&& (Charge_Authorization == FALSE)
			&& (Sampling_OK == TRUE)
			&& (BatteryTemp > BATTERY_ABSENT_TEMP_LEVEL)
			&& (Volt_Out_Of_Bounds_Flag == FALSE)
			&& (Charge_Fail_Flag == FALSE)
			&& (Charge_Time_Too_Long_Flag == FALSE)
			&& (Charge_Temp_Fail_Flag == FALSE)
			&&	(BatUnchargeableFlag == FALSE)
			&&	((CoolingFanFailureFlag == FALSE) || (AmbiantTempTooHigh == FALSE)))


		{
/*%C 		If MEASURE_VBAT < VBAT_STARTING_CHARGE	and 					  */
/*%C		FirstInitCharge = TRUE, then  									  */
			if(	(Measure_Vbat < VBAT_STARTING_CHARGE)
				&&	(FirstInitCharge == TRUE))
			{
/*%C 			Initialize chargeur: ChargeInitialization = TRUE, 			  */
/*%C			FirstInitCharge = FALSE										  */
				ChargeInitialization = TRUE ;
				FirstInitCharge = FALSE ;
			}
/*%C 		Else if (MEASURE_VBAT > VBAT_STARTING_CHARGE) and 				  */
/*%C			 FirstInitCharge = TRUE, then								  */
			else if (	(Measure_Vbat > VBAT_STARTING_CHARGE)
						&&	(FirstInitCharge == TRUE))
			{
/*%C 			ChargeInitialization = FALSE, FirstInitCharge = TRUE		  */
				ChargeInitialization = FALSE ;
				FirstInitCharge = TRUE ;				
			}
			else
			{
				/*%C No Function */
			}
/*%C		End if															  */			
/*%C 		Initialize Chargeur */
/*%C 		If FirstInitCharge = FALSE and ChargeInitialization = TRUE, then  */
			if (	(FirstInitCharge == FALSE)
				&&	(ChargeInitialization == TRUE))
			{
/*%C 			INIT_BAT_STATE = TRUE 										  */
				DB_Control_Write(INIT_BAT_STATE,TRUE); 
/*%C 			Call of Init charge function */
				CHARGE_Init();
/*%C 			I_CHARGE_MAX_MEASURED = 0  									  */
				DB_Measurement_Write(I_CHARGE_MAX_MEASURED,0);
			}
			else
			{
				/*%C No Function */	
			}
/*%C		End if 															  */
		}
/*%C	End if 																  */	
/* Fonction Charge */
/*%C Check condition for charging initialization : 							  */
/*%C If SUPPLY_STATE = AC_SUPPLY and CHARGE_AUTHORIZATION = TRUE 			  */
/*%C and INIT_CHARGEUR_FAIL = FALSE			  							  	  */
/*%C and BATTERY_TEMP >  BATTERY_ABSENT_TEMP_LEVEL, then				 	  */
		if ( (Supply_State == AC_SUPPLY)										
		  && (Charge_Authorization == TRUE)									
		  && (Init_Chargeur_Fail == FALSE)										
		  && (BatteryTemp > BATTERY_ABSENT_TEMP_LEVEL) )
		{
/*%C 		Reset Flags FirstInitCharge and ChargeInitialization  			  */
			FirstInitCharge = TRUE ;
			ChargeInitialization = FALSE ;

/*%C 		Call of charge function											  */
			CHARGE_Charge();

/*%C 		Update DataBase 												  */
/*%C 		BAT_UNCHARGEABLE_FLAG = FALSE, BAT_STATE_U16 = BAT_CHARGE		  */
/*%C 		CHARGE_BAT_STATE = TRUE, CHARGE_RUNNING = TRUE					  */
			DB_PowerSupply_Write(BAT_UNCHARGEABLE_FLAG,FALSE);
			DB_PowerSupply_Write(BAT_STATE_U16,BAT_CHARGE);	
			DB_Control_Write(CHARGE_BAT_STATE,TRUE); 
			DB_Control_Write(CHARGE_RUNNING,TRUE);

/*%C 		If IBAT_MEASURE_FILTERED > I_CHARGE_MAX_MEASURED, then			  */
			if (IBatMeasureFiltered > IChargeMaxMeasured)
			{
/*%C 			I_CHARGE_MAX_MEASURED = IBatMeasureFiltered					  */
				DB_Measurement_Write(I_CHARGE_MAX_MEASURED,IBatMeasureFiltered);
			}
/*%C		End if 															  */	
		}
/*%C	End if 																  */
		
		Charge_Bat_State = DB_Control_Read(CHARGE_BAT_STATE);
		Init_Bat_State = DB_Control_Read(INIT_BAT_STATE);
	
/*%C If IBAT_MEASURE_FILTERED > ICHARGE_CUT_OFF and 						  */
/*%C 	( CHARGE_BAT_STATE = TRUE or INIT_BAT_STATE = TRUE ), then            */
		if((IBatMeasureFiltered > ICHARGE_CUT_OFF) 
			&& (Charge_Bat_State == TRUE)				
			|| (Init_Bat_State == TRUE))
		{
/*%C 		New start cut off timer  									  	  */
/*%C 		it will equals 0 when Ibat is under 150 mA during 10 seconds 	  */
	 		TIM_StartDecounter16(CHARGE_CUT_OFF_DELAY,CHARGE_CUT_OFF_PERIOD); 
		}
/*%C	End if 																  */	
	
/* Fonction StopCharge */
/*%C If VOLT_OUT_OF_BOUNDS_FLAG = TRUE or  CHARGE_FAIL_FLAG = TRUE or 		  */
/*%C CHARGE_TIME_TOO_LONG_FLAG = TRUE or CHARGE_TEMP_FAIL_FLAG = TRUE 		  */ 
/*%C or SUPPLY_STATE <> AC_SUPPLY or Charge_Cut_Off_Delay = 0 or	  		  */
/*%C BATTERY_TEMP <  BATTERY_ABSENT_TEMP_LEVEL or							  */
/*%C (COOLING_FAN_FAILURE_FLAG = TRUE and AMBIENT_TEMP_TOO_HIGH = TRUE), then */
		Charge_Cut_Off_Delay = TIM_ReadValue16(CHARGE_CUT_OFF_DELAY);

		if((Volt_Out_Of_Bounds_Flag == TRUE) 								 
			|| (Charge_Fail_Flag == TRUE) 									 
			|| (Charge_Time_Too_Long_Flag == TRUE) 						 
			|| (Charge_Temp_Fail_Flag == TRUE) 								 
			|| (Supply_State != AC_SUPPLY)									 
			|| (Charge_Cut_Off_Delay == 0) 				 
			|| (BatteryTemp < BATTERY_ABSENT_TEMP_LEVEL)
			||	((CoolingFanFailureFlag == TRUE)
			&&	(AmbiantTempTooHigh == TRUE)))
		{
/*%C 		call of Stop charge function 									  */
			CHARGE_StopCharge();
/*%C 		If CHARGE_BAT_STATE = TRUE, then  								  */
			if(Charge_Bat_State == TRUE)
			{
/*%C 			Then update charging function state in data bases 			  */
/*%C 			BAT_STATE = BAT_IDLE, CHARGE_RUNNING = FALSE 				  */
/*%C 			CHARGE_BAT_STATE = FALSE 									  */		
				DB_PowerSupply_Write(BAT_STATE_U16,BAT_IDLE);	
				DB_Control_Write(CHARGE_RUNNING,FALSE);
				DB_Control_Write(CHARGE_BAT_STATE,FALSE); 
			}
			else
			{
				/*%C No Function */
			}
/*%C		End if 															  */
		}
/*%C	End if 																  */
	}
/*%C Else 																	  */
	else
	{
/*%C If  PreviousMaintenanceControl = FALSE, then  							  */
		if(PreviousMaintenanceControl == FALSE)
		{
/*%C		Stop charge 													  */
/*%C 		update charging function state in data bases 					  */
/*%C 		BAT_STATE = BAT_IDLE, CHARGE_RUNNING = FALSE 					  */
/*%C 		CHARGE_BAT_STATE = FALSE 										  */
			CHARGE_StopCharge();	
			DB_PowerSupply_Write(BAT_STATE_U16,BAT_IDLE);	
			DB_Control_Write(CHARGE_RUNNING,FALSE);
			DB_Control_Write(CHARGE_BAT_STATE,FALSE); 
		}
/*%C	End if 																  */
	}
/*%C End if 																  */
	PreviousMaintenanceControl = MaintenanceControl;
}
