/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Charge_Discharge_Compute.c                         		  	*/
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    % Computing of charge & discharge cycles			  		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "DB_EEPROM_BAT.h"
#include "DB_Control.h"
#include "DB_PowerSupply.h"
#include "SYS_Gauge_Data.h"
#include "SYS_Charge_Discharge_Compute.h"

/******************************************************************************/
/*                                FUNCTION BODY                               */
/******************************************************************************/

void SYS_Charge_Discharge_Compute(void)
{

	static UWORD16 StartDischargeCapacity = 0;
	UWORD16 Compute = 0;
	UWORD16 CapacityPerCent = 	DB_PowerSupply_Read(PER_CENT_BAT_U16);
	UWORD16 DischargeBatCycles = DB_PowerSupply_Read(DISCHARGE_BAT_CYCLES);	
	UWORD16 ComputeCapacityReadyFlag = 
									DB_Control_Read(COMPUTE_CAPACITY_READY_FLAG);


	/*%C When the end of discharge is detected											*/
	/*%C or a changing of battery is detected 											*/
	/*%C and the compute of Capacity is ready												*/
	/*%C And afetr 2 minutes																	*/
	if((ComputeCapacityReadyFlag == TRUE)
		&& (BatteryChangingDetectedFlagToCycleCompute == TRUE)
		&& (TIM_ReadValue32(SYS_BAT_CYCLE_READY_DELAY) == 0 ))
	{
		/*%C Locking the flag of new battery												*/
		BatteryChangingDetectedFlagToCycleCompute = FALSE;
		/*%C Store the capacity percent at a discharge start 							*/
		StartDischargeCapacity = CapacityPerCent ;
	}
	/*%C Compute the discharge percent 														*/
	if (StartDischargeCapacity > CapacityPerCent)
	{
		Compute = StartDischargeCapacity - CapacityPerCent;
	}
	else
	{
		/* No function */
	}
	/*%C Filter the delta of capacity percentage											*/
	if (Compute >= 5)
	{
		/*%C Check if the value is in the limits 											*/
		/*%C when the value is higher than 100 %											*/
		if (Compute > 100)																			
		{	
			/*%C The computed value equals 100 %											*/		
			Compute = 100;
		}
		else
		{
			/* No function */
		}
		/*%C Init the value to the next compute											*/
		StartDischargeCapacity = CapacityPerCent ;
		/*%C Computing number of battery discharge cycles 								*/
		Compute = Compute + DischargeBatCycles;
		/*%C Update of the number of discharge cycles in Power Supply Base		*/
		DB_PowerSupply_Write(DISCHARGE_BAT_CYCLES,Compute);
		/*%C Storage of the number of discharge cycles in Battery eeprom 			*/
		DB_EEPROM_BAT_Write(DATA_VARIABLE_NBR_CYCLE_1, Compute/256);
		DB_EEPROM_BAT_Write(DATA_VARIABLE_NBR_CYCLE_2, Compute%256);
	}
	else 
	{
		/* Nofunction */
	}	
}











