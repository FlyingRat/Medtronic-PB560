/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_VentilationReport.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   			This function computes the different values					  */
/*%C             		of the ventilation report        					  */                                                
/*%C                                                                          */
/*%C    	The average and deviation are computed cycle by cycle             */
/*%C         			with those formulas                                   */
/*%C       	Avg(n) = (n/(n-1)*Avg(n-1) + Val(n)/n)							  */
/*%C		AvgVar(n) = (n/(n-1)*AvgVar(n-1) + (Val(n) - Avg(n))²/n			  */
/*%C        Sigma(n) = Sqrt(AvgVar(n))                                        */          
/*%C																		  */
/*%C 		Beware using the SquareRoot function with Tasking : 			  */
/*%C   		long time compute (400µS per Op) and false result				  */		
/*																			  */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include <math.h>
#ifndef _TASKING
#include <intrins.h>
#include "LH_ST10F276.h"
#else
#include "regf276e.h"
#endif	 
#include "typedef.h"
#include "io_declare.h"
#include "enum.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "Ventilation_compute_data.h"
#include "CMP_VentilationReport.h"
#include "math.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void CMP_VentilationReport(void)
{
	UWORD16 PatientCounter_Hour;
	UWORD16 PatientCounter_Minute;
	UWORD16 Save_PatientCounter_Hour;
	UWORD16 Save_PatientCounter_Minute;
	UWORD16 Delta_PatientVentil;
	UWORD16 ValveDetected;

	UWORD16 Compute_U16 = 0 ;
	UWORD16 Tampon_U16 = 0 ;

 	UWORD32 Tampon_U32 = 0 ;
	UWORD32 Compute_U32 = 0 ;
	UWORD32 Value_U32 = 0 ;
	UWORD32 Value1_U32 = 0 ;
	UWORD32 Value2_U32 = 0 ;
	UWORD32 Counter = 0 ;
	UWORD32 Variance = 0;

	FLOAT32 ComputeFLOAT32 = 0;
	
	/****************************************************************************/
	/*						Number cycle counter								*/
	/****************************************************************************/

	/*%C Pre-incrementation of number cycle counter */
	Counter = ((UWORD32)(CMP_VentilReport_Array[DB_TREND_NB_CYCLE_COUNTER_MSB]) << 16) 
				| (UWORD32)(CMP_VentilReport_Array[DB_TREND_NB_CYCLE_COUNTER_LSB]);
	Counter = Counter + 1 ;	
	/*%C Store number cylce counter */
	CMP_VentilReport_Array[DB_TREND_NB_CYCLE_COUNTER_MSB] = (UWORD16)(Counter >> 16); 
	CMP_VentilReport_Array[DB_TREND_NB_CYCLE_COUNTER_LSB] = (UWORD16)(Counter)  ;
		
	/*On ne prend pas en compte le premier cycle */
	if (Counter > 1)
	{
		Counter = Counter - 1 ;
		/****************************************************************************/
		/*						Volume courant inspiré								*/
		/****************************************************************************/
	
		Value_U32 = (UWORD32)(DB_ComputeRead(COMPUTED_VTI_U16));
		/* Augmente la precision de calcul de la valeur moyenne	*/
		Value_U32 = Value_U32 * 10;
	
		/*%C Compute Vti average */
		Compute_U32 = (UWORD32)CMP_VentilReport_Array[DB_TREND_AVG_VTI];
		Compute_U32 = Compute_U32 * (Counter - 1); 
		Compute_U32 = Compute_U32 + Value_U32;
		Compute_U32 = Compute_U32 / Counter;
		/*%C Strore Vti average	*/
		CMP_VentilReport_Array[DB_TREND_AVG_VTI] = (UWORD16)(Compute_U32);
	
		 
		/******************************************************************************/
		/*						Volume courant expiré			    				  */
		/******************************************************************************/
		
		Value_U32 = (UWORD32)(DB_ComputeRead(COMPUTED_VTE_U16));
		/* Augmente la precision de calcul de la valeur moyenne	*/
		Value_U32 = Value_U32 * 10;
	
		/*%C Compute Vte average */
		Compute_U32 = (UWORD32)CMP_VentilReport_Array[DB_TREND_AVG_VTE];
		Compute_U32 = Compute_U32 * (Counter - 1); 
		Compute_U32 = Compute_U32 + Value_U32;
		Compute_U32 = Compute_U32 / Counter;
		/*%C Strore Vte average	*/
		CMP_VentilReport_Array[DB_TREND_AVG_VTE] = (UWORD16)(Compute_U32);
	

	
		/******************************************************************************/
		/*						   Volume minute								      */
		/******************************************************************************/
	
		Value_U32 = DB_ComputeRead(COMPUTED_VMI_U16);	
		/* Augmente la precision de calcul de la valeur moyenne	*/
		Value_U32 = Value_U32 * 10 ;
	
		/*%C Compute Vm average */
		Compute_U32 = (UWORD32)CMP_VentilReport_Array[DB_TREND_AVG_VM];
		Compute_U32 = Compute_U32 * (Counter - 1); 
		Compute_U32 = Compute_U32 + Value_U32;
		Compute_U32 = Compute_U32 / Counter;
		/*%C Strore Vm average	*/
		CMP_VentilReport_Array[DB_TREND_AVG_VM] = (UWORD16)(Compute_U32);
	

	
		/******************************************************************************/
		/*						   Frequence respiratoire 							  */ 
		/******************************************************************************/
	
	    Value_U32 = (UWORD32)(DB_ComputeRead(MEASURE_R_U16));
		/* Augmente la precision de calcul de la valeur moyenne	*/
		Value_U32 = Value_U32 * 10;
	
		/*%C Compute Fr average */
		Compute_U32 = (UWORD32)CMP_VentilReport_Array[DB_TREND_AVG_FR];
		Compute_U32 = Compute_U32 * (Counter - 1); 
		Compute_U32 = Compute_U32 + Value_U32;
		Compute_U32 = Compute_U32 / Counter;
		/*%C Strore Fr average	*/
		CMP_VentilReport_Array[DB_TREND_AVG_FR] = (UWORD16)(Compute_U32);
	

			
		/******************************************************************************/
		/*								Fuite									      */
		/******************************************************************************/
	
		ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);
	
		/*%C if leak mode detected */
		if (ValveDetected == FALSE)
		{
			CMP_VentilReport_Array[DB_TREND_LEAK_MODE] = TRUE ;
			Value_U32 = (UWORD32)(DB_ComputeRead(COMPUTED_LEAK_U16));
			/* Augmente la precision de calcul de la valeur moyenne	*/
			Value_U32 = Value_U32 * 10;
		
			/*%C Compute Leak average */
			Compute_U32 = (UWORD32)CMP_VentilReport_Array[DB_TREND_AVG_LEAK];
			Compute_U32 = Compute_U32 * (Counter - 1); 
			Compute_U32 = Compute_U32 + Value_U32;
			Compute_U32 = Compute_U32 / Counter;
			/*%C Strore Leak average	*/
			CMP_VentilReport_Array[DB_TREND_AVG_LEAK] = (UWORD16)(Compute_U32);
		}
		/*%C if mode valve detected */
		else
		{
			CMP_VentilReport_Array[DB_TREND_LEAK_MODE] = FALSE ;
			Value_U32 = 0 ;
			Compute_U32 = 0 ;
			CMP_VentilReport_Array[DB_TREND_AVG_LEAK] = 0 ;
		}
	

	
		/******************************************************************************/
		/*							Presssion inspiré								*/
		/******************************************************************************/
	
		Value_U32 = (UWORD32)(DB_ComputeRead(COMPUTED_PIP_U16));
		/* Augmente la precision de calcul de la valeur moyenne	*/
		Value_U32 = Value_U32 * 10;
	
		/*%C Compute Pi average */
		Compute_U32 = (UWORD32)CMP_VentilReport_Array[DB_TREND_AVG_PI];
		Compute_U32 = Compute_U32 * (Counter - 1); 
		Compute_U32 = Compute_U32 + Value_U32;
		Compute_U32 = Compute_U32 / Counter;
		/*%C Strore Pi average	*/
		CMP_VentilReport_Array[DB_TREND_AVG_PI] = (UWORD16)(Compute_U32);
	
	
		/******************************************************************************/
		/*							 Temps Apnée 									*/
		/******************************************************************************/
	
	   	if (CMP_VentilReport_Array[DB_TREND_NB_APNEA] >= 1)	
		{
			CMP_VentilReport_Array[DB_TREND_APNEA] = 
				(UWORD16)(CMP_VentilReport_Array[DB_TREND_APNEA_TIME] / CMP_VentilReport_Array[DB_TREND_NB_APNEA]);
		}
		else
		{
			/*%C No function*/
		}		
	
		 /******************************************************************************/
		/*							  Index Apnée									*/
		/******************************************************************************/
	
		if (CMP_VentilReport_Array[DB_TREND_VENTIL_HOUR] >=1)	
		{
			CMP_VentilReport_Array[DB_TREND_IA] = 
				CMP_VentilReport_Array[DB_TREND_NB_APNEA] / CMP_VentilReport_Array[DB_TREND_VENTIL_HOUR];
		}
		else
		{
			/* No function */
		}
	
		/******************************************************************************/
		/*							%Spon %Contr									*/
		/******************************************************************************/
	
		/*%C Compute the percentage of triggered cycles */
		Value1_U32 = ((UWORD32)(CMP_VentilReport_Array[DB_TREND_NB_CYCLE_TRIGERRED_MSB]) << 16) 
					| (UWORD32)(CMP_VentilReport_Array[DB_TREND_NB_CYCLE_TRIGERRED_LSB]);
		Value2_U32 = ((UWORD32)(CMP_VentilReport_Array[DB_TREND_NB_CYCLE_CONTROLLED_MSB]) << 16) 
					| (UWORD32)(CMP_VentilReport_Array[DB_TREND_NB_CYCLE_CONTROLLED_LSB]);
		/*%C The divider must be different to 0	*/
		if (Value1_U32 == 0 && Value2_U32 == 0)
		{
			/*%C No function */	
		}
		else
		{
			CMP_VentilReport_Array[DB_TREND_PERCENT_TRIGGERED] = (UWORD16)((100 * Value1_U32) / 
									(Value2_U32 + Value1_U32));
	
			/*%C Compute the percentage of controlled cycles */
			CMP_VentilReport_Array[DB_TREND_PERCENT_CONTROLLED] = 100 - CMP_VentilReport_Array[DB_TREND_PERCENT_TRIGGERED];
		}
	
		/****************************************************************************/
		/*						Average Ventilation time							*/
		/****************************************************************************/
		/*%C Read the patient counter in the config base */
		PatientCounter_Hour = DB_ControlRead(CURRENT_PATIENT_COUNTER_HOUR_U16);
		PatientCounter_Minute = (UBYTE)DB_ControlRead(CURRENT_PATIENT_COUNTER_MIN_U16 );
		Save_PatientCounter_Hour = DB_TrendRead(DB_TREND_SAVE_PC_HOUR);
		Save_PatientCounter_Minute = DB_TrendRead(DB_TREND_SAVE_PC_MIN);
		
		/*%C Compute the duration of the patient ventilation in minutes*/
		Delta_PatientVentil = (PatientCounter_Hour * 60 + PatientCounter_Minute) 
		- (Save_PatientCounter_Hour * 60 + Save_PatientCounter_Minute);
		
		CMP_VentilReport_Array[DB_TREND_VENTIL_HOUR] = Delta_PatientVentil / 60;
		CMP_VentilReport_Array[DB_TREND_VENTIL_MIN] = Delta_PatientVentil % 60;
	}
	else
	{
		/*Pendant le premier cycle on ne fait pas de calcul*/
	}
}