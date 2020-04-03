/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Voltage_Capacity_Conversion.c                              */
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
#include "SYS_Gauge_Data.h"
#include "SYS_Voltage_Capacity_Conversion.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
UWORD16 SYS_Voltage_Capacity_Conversion(UWORD16 Fem, UWORD16 PercentColapse,
                                UWORD16 Ageing) 
{
	UWORD16 BatState = DB_PowerSupply_Read(BAT_STATE_U16);
	
	UWORD32 CurveReference = 0;
	UWORD32 ComputeCurve = 0;
	UWORD16 BatteryCurveAgeing1 =0;
	UWORD16 BatteryCurveAgeing2 =0;
	SWORD16 ComputeCapacityPerCent = 0;	
	UWORD16 IndexPoint = 0;
	UWORD16 IndexCurve = 0;
	SWORD16 Delta_Voltage = 0;
	SWORD32 Slope = 0;
	SWORD16 Newcapacitypoint = 0;
	SWORD16 Newscale = 0;
	


 	/*%C Search the nearest theoritcal Capacity = f(Fem)curve according to Ageing       */
	while ((Ageing <= cCapacityBasedVoltage[IDX_AGE][IndexCurve]) && (IndexCurve < NB_CURVES))
	{
			IndexCurve = IndexCurve + 1;
	}

   /*%C Compute of the estimated curve : Capacity = f(Fem)                             */ 
	if (IndexCurve <= 0)
	{
		for (IndexPoint = 0;IndexPoint < NB_POINTS;IndexPoint++)
	 	{ 	
		  CapacityBasedVoltageComputed[IndexPoint][IDX_VOLTAGE_CURRENT]
		        = (SWORD16)cCapacityBasedVoltage[IndexPoint][IndexCurve];
		}
	}
	else if (IndexCurve >= NB_CURVES)
	{
		for (IndexPoint = 0;IndexPoint < NB_POINTS;IndexPoint++)
	 	{ 	
		  CapacityBasedVoltageComputed[IndexPoint][IDX_VOLTAGE_CURRENT]
		        = (SWORD16)cCapacityBasedVoltage[IndexPoint][IndexCurve-1];
		}
	}
	else
	{
		BatteryCurveAgeing1 = cCapacityBasedVoltage[IDX_AGE][IndexCurve-1];
	    BatteryCurveAgeing2 = cCapacityBasedVoltage[IDX_AGE][IndexCurve];
					
		CurveReference = ((UWORD32)(Ageing - BatteryCurveAgeing2))*1000;
		CurveReference = CurveReference /((UWORD32)(BatteryCurveAgeing1 - BatteryCurveAgeing2));
		
	 	for (IndexPoint = 0;IndexPoint < NB_POINTS;IndexPoint++)
	 	{ 	
		  ComputeCurve = (UWORD32)(cCapacityBasedVoltage[IndexPoint][IndexCurve-1]
		  							    - cCapacityBasedVoltage[IndexPoint][IndexCurve]);
		  ComputeCurve = ComputeCurve * CurveReference;				
		  ComputeCurve = ComputeCurve 
		  						  + (UWORD32)(cCapacityBasedVoltage[IndexPoint][IndexCurve])*1000;
		  ComputeCurve = ComputeCurve/1000;	
		  CapacityBasedVoltageComputed[IndexPoint][IDX_VOLTAGE_CURRENT]= (SWORD16)(ComputeCurve);				
	 	}
	}
	if (PercentColapse != 0)
	{
		Newscale = 100 - PercentColapse;
		for (IndexPoint = 0;IndexPoint < NB_POINTS;IndexPoint++)
		{	
			
			Newcapacitypoint = CapacityBasedVoltageComputed[IndexPoint][IDX_CAPACITY_CURENT] - (SWORD16)PercentColapse;
			Newcapacitypoint = Newcapacitypoint * 100;
			Newcapacitypoint = Newcapacitypoint / (SWORD16)Newscale;
			CapacityBasedVoltageComputed[IndexPoint][IDX_CAPACITY_CURENT] = Newcapacitypoint;	
		}		
	}

	/*%C Protect BAT_CAPACITY and BAT_CAPACITY_PERCENT 								*/
	if ((SWORD16)Fem >= CapacityBasedVoltageComputed[NB_POINTS-1][IDX_VOLTAGE_CURRENT])
	{
		ComputeCapacityPerCent = 100;	
	}
	
	/*%C Protect BAT_CAPACITY and BAT_CAPACITY_PERCENT 								*/
	else if ((SWORD16)Fem <= CapacityBasedVoltageComputed[0][IDX_VOLTAGE_CURRENT])
	{
		ComputeCapacityPerCent = 0;	
	}

	/*%C Compute BAT_CAPACITY and BAT_CAPACITY_PERCENT 								*/
	else 
	{
			/*%C Search the point of the curve : Capacite = f(Fem) 							*/
		IndexPoint = 0;
		while(((SWORD16)Fem >= CapacityBasedVoltageComputed[IndexPoint][IDX_VOLTAGE_CURRENT]) && (IndexPoint < NB_POINTS))
		{
			IndexPoint = IndexPoint + 1;
		}
		/*%C Calcul DELTA_VOLTAGE between the two point of curve 					*/
		Delta_Voltage  = CapacityBasedVoltageComputed[IndexPoint][IDX_VOLTAGE_CURRENT] 
							- CapacityBasedVoltageComputed[IndexPoint-1][IDX_VOLTAGE_CURRENT];
		/*%C Calcul DELTA_CAPACITY between the two point of curve 					*/
		ComputeCapacityPerCent = CapacityBasedVoltageComputed[IndexPoint][IDX_CAPACITY_CURENT] 
							   	  - CapacityBasedVoltageComputed[IndexPoint-1][IDX_CAPACITY_CURENT];
		/*%C Calcul slope between ComputeCapacityPerCent and Delta_Voltage		*/
		Slope = (SWORD32)(ComputeCapacityPerCent) * 100000 / (SWORD32)(Delta_Voltage);
	
		/*%C Calcul the point between battery tension and segment					*/		
		Delta_Voltage = (SWORD16)Fem 
						  - CapacityBasedVoltageComputed[IndexPoint-1][IDX_VOLTAGE_CURRENT];
		/*%C Calcul capacite 																	*/
		ComputeCapacityPerCent = CapacityBasedVoltageComputed[IndexPoint-1][IDX_CAPACITY_CURENT]*100
						          + (SWORD16)(Slope * (SWORD32)(Delta_Voltage)/1000);
		ComputeCapacityPerCent = ComputeCapacityPerCent/100;										
	}
		
	/*%C Limit the compute before end of charge								   		*/
	if (BatState != BAT_DISCHARGE && ComputeCapacityPerCent >=99)
	{
		/*%C the value is saturated to 99													*/
		ComputeCapacityPerCent = 99;
	}	
	/*%C Check if the value is lower than 0            							*/	
	if (ComputeCapacityPerCent < 0)	
	{		
		/*%C the value is saturated to 0															*/	   
		ComputeCapacityPerCent = 0;	
	}	
	/*%C retour de ComputeCapacityPercent 											      */
	return(UWORD16)(ComputeCapacityPerCent);
}