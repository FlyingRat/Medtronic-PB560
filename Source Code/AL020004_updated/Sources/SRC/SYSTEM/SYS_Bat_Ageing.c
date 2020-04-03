/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Bat_Ageing.c 		                                      		*/
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Compute of battery Aeging								  		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

													  
/******************************************************************************/
/*                                INCLUDE FILES		                      		*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "DB_Measurement.h"
#include "DB_PowerSupply.h"
#include "DB_EEPROM_BAT.h"
#include "DB_Control.h"
#include "SYS_Gauge_Data.h"
#include "SYS_Bat_Ageing.h"

/******************************************************************************/
/*                                FUNCTION BODY											*/
/******************************************************************************/
void SYS_Bat_Ageing(void)
{
	static UBYTE NewDischarge = FALSE;
	static UWORD16 Ageing_Per_Cent_Samples[10];
	
	SWORD16 Ibat_Average = DB_Measurement_Read(IBAT_AVERAGE);
	UWORD16 Coulomb_Compute_discharge_ready_flag = DB_Measurement_Read(COULOMB_COMPUTE_DISCHARGE_READY_FLAG);
	UWORD16 ComputeCapacityReadyFlag = DB_Control_Read(COMPUTE_CAPACITY_READY_FLAG);
	UWORD16 Discharge_Bat_State =  DB_Control_Read(DISCHARGE_BAT_STATE);
	UWORD16 BatAgeing = DB_PowerSupply_Read(BAT_AGEING);
	UWORD16 Fem =  DB_PowerSupply_Read(FEM_COMPUTE);
	
	UWORD32 Ageing_Per_Cent = 0;
	UWORD32 CapacityCompute = 0;
   UWORD32 Dif_Capacity = 0;
   UWORD32 Compare=0;
   UWORD32 slope = 0;
	UWORD16 Loop;
	UWORD16 AgeingFilterCompute = 0 ;
	UWORD16 Index = 0;
	UWORD16 Age = 0;
   UWORD16 Age1 = 0;
   UWORD16 Age2 = 0;
   UWORD16 Capa1 = 0;
	UWORD16 Capa2 = 0;
	UWORD16 Bat_ageing_Max = 0;
	UWORD16 Bat_ageing_Min = 0;

	/*%C To compute the ageing, the current must be positive							*/
	if( Ibat_Average < 0 )
	{
		Ibat_Average = -Ibat_Average;
	}
	
/******************************************************************************/
/*%C Inintializations for Battery Ageing computing									   */
/******************************************************************************/
   /*%C If A new discharge occurs                                             */
	if ((ComputeCapacityReadyFlag == TRUE)
		&& (BatteryChangingDetectedFlagToAgeingCompute == TRUE)
		&& (TIM_ReadValue32(SYS_BAT_AGEING_READY_DELAY) == 0 )
		&& (Coulomb_Compute_discharge_ready_flag == TRUE))
	{
		/*%C Locking the flag of new discharge												*/
		BatteryChangingDetectedFlagToAgeingCompute = FALSE;
				
		/*%C Store capacities at T1 for each discharge curve.    				   */
		for (Index = 0;Index < NB_CURVES;Index++)
	 	{ 	
			Age = cCapacityBasedVoltage[IDX_AGE][Index];
			CapacityCompute = (UWORD32)(SYS_Voltage_Capacity_Conversion(Fem,0,Age)); 
			CapacityCompute = CapacityCompute * (UWORD32)(Age);
			CapacityCompute = CapacityCompute * TYPICAL_BAT_CAPACITY;
			CapacityCompute = CapacityCompute / 10000;
			AgeingCompute[IDX_T1][Index] = (UWORD16)(CapacityCompute);		
		}
		
		/*%C Others parameters initialization.    				 					  */
		VOLTAGE_AT_T1  = Fem;
		DELTA_CAPACITY = 0;
		DELTA_BAT_VOLTAGE = 0;
		SAMPLES_AGEING_NUMBER = 0;
        NewDischarge = TRUE;
		
		/*%C Flag setting that forbide to take in account the first 				*/
		/*%C value of IBatAverage for delta capacity computing.      				*/
		Coulomb_Compute_discharge_ready_flag = FALSE;
		DB_Measurement_Write(COULOMB_COMPUTE_DISCHARGE_READY_FLAG,FALSE);
	}

	/******************************************************************************/
	/*%C Mesure of delta capacity by coulometer between T1 and T2                 */
	/******************************************************************************/
  
   /*%C If battery voltage level is high enough                               */
	if(Fem > MIN_BAT_VOLTAGE_TO_COMPUTE_AGEING)
	{		
		/*%C check if the computed value is in the limits								*/
		if (VOLTAGE_AT_T1 > Fem)
	 	{
	 		DELTA_BAT_VOLTAGE = VOLTAGE_AT_T1 - Fem;
	 	}
	 	/*%C if Dela Voltage is negative then value = 0                			*/
	 	else
	 	{
	 		DELTA_BAT_VOLTAGE = 0;
		}
		
		/*%C Update of Capacity counter at each Ibat Average value Refresh  		*/
	 	if (Coulomb_Compute_discharge_ready_flag == TRUE)
 		{
	 		/*%C Add measure in µA.h with a correcting factor (+14%) in oder to   */ 
			/*%C compensate lack of current measurment accuracy.                  */
			/* 14% pour compenser un default de calcul sur le cumul du courant	*/
			/* pour enlever cette correction il faudrait revoir si la mesure et	*/
			/* le cumul de courant sont corrects											*/
			DELTA_CAPACITY = DELTA_CAPACITY
									+ (((UWORD32)(Ibat_Average) * 114) / 60);
			/*%C Check if the delta capacity is higher than the max value			*/
			if (DELTA_CAPACITY > ((UWORD32)(TYPICAL_BAT_CAPACITY) * 1000))
			{
				/*%C Then the delta capacity = the max value 							*/
				DELTA_CAPACITY = (UWORD32)(TYPICAL_BAT_CAPACITY) * 1000;
			}
			
			/*%C Reset of the flag allowing Ibat Average sum at next Ibat Average refresh*/
			DB_Measurement_Write(COULOMB_COMPUTE_DISCHARGE_READY_FLAG,FALSE);
		}	
		
		/******************************************************************************/
		/*%C Battery Ageing computing at T2                									*/
		/******************************************************************************/
		/*%C If delta battery voltage is significant			              		    */
		if ((DELTA_BAT_VOLTAGE > DELTA_MEANINGFUL_VOLTAGE)
			&& (Coulomb_Compute_discharge_ready_flag == TRUE))
		{
			/*%C Store capacities at T2 for each discharge curve.    				 */
			for (Index = 0;Index < NB_CURVES;Index++)
		 	{ 	
				Age = cCapacityBasedVoltage[IDX_AGE][Index];
				CapacityCompute = (UWORD32)(SYS_Voltage_Capacity_Conversion(Fem,0,Age)); 
				CapacityCompute = CapacityCompute * (UWORD32)(Age);
				CapacityCompute = CapacityCompute * TYPICAL_BAT_CAPACITY;
				CapacityCompute = CapacityCompute / 10000;
				AgeingCompute[IDX_T2][Index] = (UWORD16)(CapacityCompute);	
			}
			
			/*%C Compute of Theorical DELTA CAPACITY for each discharge curve     */
			/*%C between T1 and T2.															    */
         for (Index = 0;Index < NB_CURVES;Index++)
         {
				AgeingCompute[IDX_DELTA_CAPACITY][Index] = 
				           (AgeingCompute[IDX_T1][Index]
						     - AgeingCompute[IDX_T2][Index]);			     
		   } 
		   
		   /*%C Search the nearest Theorical curve according to						 */
		   /*%C real DELTA_CAPACITY consumption.                                 */
			Index = 0;
			Compare =(UWORD32)(AgeingCompute[IDX_DELTA_CAPACITY][Index])*1000;
			while((DELTA_CAPACITY <= Compare) && (Index < NB_CURVES))
			{
				Index = Index + 1;	
				Compare =(UWORD32)(AgeingCompute[IDX_DELTA_CAPACITY][Index])*1000;
			}
													
			/*%C Compute and fix the ageing compute boundaries according			  */ 
			/*%C to the nearest Theorical curve.					        				  */
			if (Index <= 0)
			{
				/*%C if the Theorical curve is the first curve					        */ 
			   Bat_ageing_Max = BAT_AGEING_MAX;
			   Bat_ageing_Min = cCapacityBasedVoltage[IDX_AGE][Index+1];
			   Age = cCapacityBasedVoltage[IDX_AGE][Index];
				Ageing_Per_Cent = DELTA_CAPACITY / AgeingCompute[IDX_DELTA_CAPACITY][Index];
				Ageing_Per_Cent = Ageing_Per_Cent * Age;
				Ageing_Per_Cent = Ageing_Per_Cent/1000;	
			}
			else if (Index >= NB_CURVES) 
			{
				/*%C if the Theorical curve is the last curve					        */
				Bat_ageing_Max = cCapacityBasedVoltage[IDX_AGE][Index-1];
				Bat_ageing_Min = BAT_AGEING_MIN;
				Age = cCapacityBasedVoltage[IDX_AGE][Index-1];
				Ageing_Per_Cent = DELTA_CAPACITY / AgeingCompute[IDX_DELTA_CAPACITY][Index-1];
				Ageing_Per_Cent = Ageing_Per_Cent * Age;
				Ageing_Per_Cent = Ageing_Per_Cent/1000;
			}	
			else
			{
				/*%C if the Theorical curve is between the first and the last curve */
				Bat_ageing_Max = cCapacityBasedVoltage[IDX_AGE][Index-1];
				Bat_ageing_Min = cCapacityBasedVoltage[IDX_AGE][Index];

				Age1 = cCapacityBasedVoltage[IDX_AGE][Index-1];
				Age2 = cCapacityBasedVoltage[IDX_AGE][Index];
				Capa1 = AgeingCompute[IDX_DELTA_CAPACITY][Index-1];
                Capa2 = AgeingCompute[IDX_DELTA_CAPACITY][Index];
				slope = Age1 - Age2;
				slope = slope * 1000; 
				slope = slope / (Capa1 - Capa2);
				Ageing_Per_Cent = slope *(DELTA_CAPACITY - (UWORD32)(Capa2)*1000);
				Ageing_Per_Cent= Ageing_Per_Cent/1000000;
				Ageing_Per_Cent = Ageing_Per_Cent + Age2;
			}
			
			/*%C check if the ageing computed value is in the limits					*/
			if (Ageing_Per_Cent > Bat_ageing_Max)
			{
				/*%C if the value is higher than  the max : then value = max		*/
				Ageing_Per_Cent = Bat_ageing_Max;	
			}
			else if (Ageing_Per_Cent < Bat_ageing_Min) 
			{
				/*%C If the value is lower than the min.then value = min.			*/
				Ageing_Per_Cent = Bat_ageing_Min;	
			}	
	
			/*%C RS232 Debug																		*/
			DB_PowerSupply_Write(BAT_AGEING_COMPUTED,(UWORD16)(Ageing_Per_Cent));
			
			/*%C Battery Ageing filtering          									   */			
			if(NewDischarge == TRUE)
			{
				/*%C Locking the flag 															*/
				NewDischarge = FALSE;		
				/*%C Store the EEPROM ageing value 											*/
				Ageing_Per_Cent_Samples[SAMPLES_AGEING_NUMBER%10] = BatAgeing; 
				/*%C Increment array index 													*/
				SAMPLES_AGEING_NUMBER = (SAMPLES_AGEING_NUMBER + 1)%10;
			}
			/*%C Store the ageing value 														*/
			Ageing_Per_Cent_Samples[SAMPLES_AGEING_NUMBER%10] = (UWORD16)(Ageing_Per_Cent);
			/*%C Increment array index 														*/
			SAMPLES_AGEING_NUMBER = (SAMPLES_AGEING_NUMBER + 1)%10;
			
			/*%C Filter ageing percent value 												*/
			for( Loop = 0 ; Loop < SAMPLES_AGEING_NUMBER ; Loop++)
			{
				AgeingFilterCompute = AgeingFilterCompute 
													+ Ageing_Per_Cent_Samples[Loop];
			}
			/*%C Update the filtered measure 												*/
			AgeingFilterCompute = (AgeingFilterCompute / SAMPLES_AGEING_NUMBER);	
	
	
			/*%C Update data bases with ageing filtered value							*/
			DB_PowerSupply_Write(BAT_AGEING,AgeingFilterCompute);
			DB_EEPROM_BAT_Write(DATA_VARIABLE_BAT_AGEING_1,AgeingFilterCompute);
			
			/*%C Re-Init of Capacity Counter*/
			/*%C Reset of AgeingCompute table for next ageing estimation. 		   */
			/*%C Capacities at T2 become capacities at T1 for each discharge curve */
	      for (Index = 0;Index < NB_CURVES;Index++)
	      {
	        	AgeingCompute[IDX_T1][Index] = AgeingCompute[IDX_T2][Index];
	  		} 	
			/*%C Reset of other parameters.           				 					*/
			DELTA_CAPACITY = 0;
			VOLTAGE_AT_T1  = Fem;
		}			
	}
}
