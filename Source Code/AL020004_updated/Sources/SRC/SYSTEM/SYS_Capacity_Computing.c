/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Capacity_Computing.c                                       */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Compute of battery capacity							  */
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
#include "IO_declare.h"
#include "DB_PowerSupply.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_Measurement.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SYS_Capacity_Computing(void)

{
UWORD32 BatImpedance = DB_Control_Read(IMPEDANCE_BAT);
UWORD32 AegingBat = DB_Config_Read(AGEING_BAT);
UWORD32 Ratio = 100 - AegingBat;
UWORD32 PerCentCapa; 
UWORD32 tensAVide = DB_Measurement_Read(MEASURE_VBAT);
UWORD32 CompensatedTypicalBatCap ;
UWORD32 BatCapacity;

CompensatedTypicalBatCap = TYPICAL_BAT_CAPACITY * Ratio;
CompensatedTypicalBatCap = CompensatedTypicalBatCap / 100;

if (tensAVide <= 2240)
	{
	PerCentCapa  = 0;
	}
else if (tensAVide <= 2504)
	{
	PerCentCapa  = 5;
	}
else if (tensAVide <= 2550)
	{
	PerCentCapa  = 10;
	}
else if (tensAVide <= 2589)
	{
	PerCentCapa  = 20;
	}
else if (tensAVide <= 2611)
	{
	PerCentCapa  = 30;
	}
else if (tensAVide <= 2626)
	{
	PerCentCapa  = 40;
	}
else if (tensAVide <= 2648)
	{
	PerCentCapa  = 50;
	}
else if (tensAVide <= 2681)
	{
	PerCentCapa  = 60;
	}
else if (tensAVide <= 2723)
	{
	PerCentCapa  = 70;
	}
else if (tensAVide <= 2769)
	{
	PerCentCapa  = 80;
	}
else if (tensAVide <= 2828)
	{
	PerCentCapa  = 90;
	}
else 
	{
	PerCentCapa  = 100;
	}

BatCapacity = CompensatedTypicalBatCap * PerCentCapa;
BatCapacity = BatCapacity / 100;



}
/*****************************************************************************************/

#include"TypeDef.h"
#include "Gauge_Datas.h"


/******************************************************************************/
/*                                FUNCTION BODY                               */
/******************************************************************************/
UWORD32 SYS_ComputeCapacityAccordingToVbat(UWORD16 Vbat,UWORD32 TotalCapacity)
{
	UWORD32 Delta_Voltage;
	UWORD32 CapacityPerCent;
	UWORD32 Slope;
	UWORD32 Capacity;
	UBYTE Index;
	
	//recherche du segment de la courbe capacité en fonction de la tension à vide
	for (Index = 0;Index < NB_POINTS;Index++)
	{
		if (Vbat < cCapacityBasedVoltage[Index][IDX_VOLTAGE])
		{
			break;
		}
	}
		
	if (Vbat <= cCapacityBasedVoltage[0][IDX_VOLTAGE]) 
	{
		Capacity = 0;	
	}
	else if (Vbat >= cCapacityBasedVoltage[NB_POINTS-1][IDX_VOLTAGE])
	{
		Capacity = TotalCapacity;	
	}
	else 
	{
		//Calcul du delta de tension entre les deux points du segment
		Delta_Voltage  = cCapacityBasedVoltage[Index][IDX_VOLTAGE] - cCapacityBasedVoltage[Index-1][IDX_VOLTAGE];
		//Calcul du delta de profondeur de décharge  entre les deux points du segment
		CapacityPerCent = cCapacityBasedVoltage[Index][IDX_CAPACITY] - cCapacityBasedVoltage[Index-1][IDX_CAPACITY];
		//Calcul de la pente profondeur de décharge en fonction de la tension (capacité par 100ième de mV)
		Slope = CapacityPerCent * 100000 / Delta_Voltage;
		//Calcul de l'écart de tension entre la tension batterie et le point inférieur du segment
		Delta_Voltage = (UWORD32)Vbat - cCapacityBasedVoltage[Index-1][IDX_VOLTAGE];
		//Calcul de la capacité
		CapacityPerCent = cCapacityBasedVoltage[Index-1][IDX_CAPACITY] + ((Slope * Delta_Voltage)/100000);
		Capacity = (TotalCapacity * CapacityPerCent)/100 ;
	}
	//Limitation du calcul
	if (Capacity > TotalCapacity) 
	{
		Capacity = TotalCapacity;
	}
	return Capacity;

}
