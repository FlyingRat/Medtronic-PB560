/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Gas_Gauge_Percent.c                                      */
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Compute of battery capacity							  		*/
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
#include "DB_PowerSupply.h"
#include "DB_Measurement.h"
#include "DB_Control.h"
#include "DB_EEPROM_BAT.h"
#include "SYS_Gauge_Data.h"
#include "SYS_Gas_Gauge_Percent.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SYS_Gas_Gauge_Percent(void)
{
	UWORD16 BatState = DB_PowerSupply_Read(BAT_STATE_U16);	
	UWORD16 BatAgeing = DB_PowerSupply_Read(BAT_AGEING);
	UWORD16 MeasureVBat = DB_Measurement_Read(MEASURE_VBAT);
	UWORD16 VoltageColapse = DB_PowerSupply_Read(BATTERY_VOLTAGE_COLAPSE);
	
	
	UWORD32 ComputeBatCapacityCompensated = 0;
	UWORD16 BatImpedance	= 0;
	UWORD16 ComputeBatPercent = 0;
	UWORD32 FemCompute = 0;
	UWORD16 Fem = 0;
	SWORD16 BatteryColapseVoltage = 0;
	SWORD16 BatteryColapsePercent = 0;
	SWORD32 Shunt_Voltage = 0;
	SWORD16 IBat;
	
	/*%C Test if the battery is in charge or discharge													*/
	if ((BatState == BAT_DISCHARGE)
		|| (BatState == BAT_CHARGE))
	{
		IBat = (SWORD16) DB_Measurement_Read(I_BAT);
		IBat = IBat/ 10;
	}
	else 
	{
		IBat = 0;
	}
	 
	/*%C Filter the value of BAT_FEM											      	             	*/
	if (SAMPLE_BAT_FEM >= 200)
	{	
		Fem = (UWORD16)(SUM_BAT_FEM / 200);
		
		DB_Control_Write(COMPUTE_CAPACITY_READY_FLAG,TRUE);
		
		/*%C Update data bases FEM value																   		*/
		DB_PowerSupply_Write(FEM_COMPUTE, Fem);
		
		BatteryColapseVoltage = 2000 + (SWORD16)VoltageColapse;
		
		if (BatteryColapseVoltage <= cCapacityBasedVoltage[0][IDX_CAPACITY_CURVE1])
		{
			BatteryColapseVoltage = cCapacityBasedVoltage[0][IDX_CAPACITY_CURVE1];
		}
		
		/*%C Dicharge percent compute																				*/
		BatteryColapsePercent = SYS_Voltage_Capacity_Conversion((UWORD16)BatteryColapseVoltage,0,BatAgeing);
		ComputeBatPercent = SYS_Voltage_Capacity_Conversion(Fem,(UWORD16)BatteryColapsePercent,BatAgeing);
		/*%C Dicharge percent storage                                                          */
		DB_PowerSupply_Write(PER_CENT_BAT_U16, ComputeBatPercent);
		 
		/*%C Compensated capacity compute																		*/
		ComputeBatCapacityCompensated = TYPICAL_BAT_CAPACITY * ((UWORD32) BatAgeing);
		ComputeBatCapacityCompensated = ComputeBatCapacityCompensated * ((UWORD32)ComputeBatPercent); 
		ComputeBatCapacityCompensated = ComputeBatCapacityCompensated / 10000;	
		/*%C Compensated capacty storage																			*/
		DB_PowerSupply_Write(BAT_CAPACITY_COMPENSATED,(UWORD16) ComputeBatCapacityCompensated);
														
		/*%C Init for the next compute																			*/
		SUM_BAT_FEM = 0;
		SAMPLE_BAT_FEM = 0;
	}
	else
	{
		/*%C Read the impedance value																					*/
		BatImpedance = DB_PowerSupply_Read(BAT_IMPEDANCE);
		/*%C Calcul the fem of battery																				*/
		FemCompute = (((UWORD32) MeasureVBat) * 10);
		Shunt_Voltage = (SWORD32)(BatImpedance) * (SWORD32)(IBat);
		Shunt_Voltage = Shunt_Voltage / 1000;
		FemCompute = FemCompute - Shunt_Voltage;
		FemCompute = FemCompute / 10;
		SUM_BAT_FEM = SUM_BAT_FEM + FemCompute;
		SAMPLE_BAT_FEM = SAMPLE_BAT_FEM + 1;
	}
}
