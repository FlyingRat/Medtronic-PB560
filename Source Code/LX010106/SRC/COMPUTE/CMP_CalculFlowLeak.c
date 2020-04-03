/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_CalculFlowLeak.c                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C This function computes the close loop of the rinse flow                  */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "DB_Config.h"
#include "DB_AlarmStatus.h"
#include "Ventilation_Constants.h"
#include "enum.h"
#include "CMP_CalculFlowLeak.h"
#include "Ventilation_Datas.h"
#include "structure.h"
#include "DB_IhmAccessParaDataBase.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void CMP_CalculFlowLeak(void)
{

/* Local valve current                                                     */
	UWORD16 ValveCurrentMean = 0;
	static UWORD16 PreviousValveCurrentMean	= 0;
/* Ti counter value recovery from base                                        */
	UWORD16 TiCounterValue = TIM_ReadCounterValue(VEN_TI_COUNT);
/* Pi set point recovery from base                                            */
   UWORD16 Pi_Set_Point = DB_CurrentRead(PI_SET_POINT_U16);
/* Inspiratory max pressure recovery from base                                */
   UWORD16 Computed_Pip =  DB_ComputeRead(COMPUTED_PIP_U16);
/* Peep recovery from base                                                    */
   UWORD16 Adjust_Peep =  DB_CurrentRead(ADJUST_PEEP_U16);
/* Exhal Flow Use state recovery from base 									  */
   UWORD16 ExhalFlowUse = DB_ControlRead(EXHAL_FLOW_USE_U16);
/* Pediatric Circuit state recovery from base */
   UWORD16 PediatricCircuit = DB_ConfigRead(ADJUST_PEDIATRIC_CIRCUIT_U16);
/* Fas valve calibration current recovery from base */
   UWORD16	IValveRef = DB_ConfigRead(I_VALVE_REF_U16);
/* Fas valve calibration offsets recovery from base */
	UWORD16 OffsetFasValve3	= DB_ConfigRead(OFFSET_FAS_VALVE_3_U16);
	UWORD16 OffsetFasValve4	= DB_ConfigRead(OFFSET_FAS_VALVE_4_U16);
	UWORD16 OffsetFasValve5	= DB_ConfigRead(OFFSET_FAS_VALVE_5_U16);
	UWORD16 OffsetFasValve6	= DB_ConfigRead(OFFSET_FAS_VALVE_6_U16);
	UWORD16 OffsetFasValve7	= DB_ConfigRead(OFFSET_FAS_VALVE_7_U16);
	UWORD16 OffsetFasValve8	= DB_ConfigRead(OFFSET_FAS_VALVE_8_U16);
	UWORD16 OffsetFasValve9	= DB_ConfigRead(OFFSET_FAS_VALVE_9_U16);
/* Valve command initialisation declaration */
   SWORD32 ValveCommandInit = 0;
/* Valve command minimum saturation declaration */
   SWORD32 ValveCommandMin = 0;
/* Valve command maximum saturation declaration */
   SWORD32 ValveCommandMax = 0;
/* Valve command coefficient declaration */
   SWORD32 ValveCommandCoeff = 0;
/* Valve command temperature correction factor declaration */
	SWORD32 TempCorrectionFactor = 0;
/* Peep Memorization                                                          */
   static UWORD16 Adjust_Peep_Memo = 250;
/* Alarm disconnection state recovery from base                               */
   UWORD16 Alarm_Disconnection = DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);
/* Alarm disconnection state recovery from base                               */
   UWORD16 Alarm_CheckValve = DB_AlarmStatusRead(ALARM_CHECK_VALVE_U16);
/* Use to apply the default value                                             */
	UBYTE DefaultValueToApply = FALSE;
/* Temp rise open valve min declaration                                       */
	UWORD16 TempRiseOpenValveMin = 0;
/* Rise time value for peep > 20 cmH2O                                        */
	SWORD32 High_Peep_Rise_Time = VEN_RiseCompute((SWORD32)Adjust_Peep,
		                                          20,
		                                          1000,
		                                          90,
	                                             300);


/**********************************************************************/					  
/* Valve current mean computing                                       */
/**********************************************************************/
	ValveCurrentMean = (UWORD16)(VEN_MeasuredValues.CumulValveCurrent / (SWORD32)VEN_CptCumulValveCurrent);
	DB_ComputeWrite(MEAN_INSP_VALVE_CURRENT_U16, ValveCurrentMean);
	/*%C Read call to apply the saturation */
	ValveCurrentMean = DB_ComputeRead(MEAN_INSP_VALVE_CURRENT_U16);
	VEN_MeasuredValues.CumulValveCurrent = 0;
	VEN_CptCumulValveCurrent = 0;

/*****************************************************************/					  
/* Valve pwm start point, saturations and coeff values computing */
/*****************************************************************/
	/* Temperature correction factor calculation and filtering */
	if (VEN_FirstCycle == FALSE)
	{
		PreviousValveCurrentMean = ValveCurrentMean;
		/*%C RAZ Valve current saturation */
		VEN_ValveCurrentSat = FALSE;
		/*%C RAZ negative flow saturation */
		VEN_FlowNegSat = FALSE;

	}

	/*%C Current measure out of saturations */
	if (	(ValveCurrentMean < cDB_Saturate_COMPUTE[MEAN_INSP_VALVE_CURRENT_U16].cDB_TEST_DB.mini) 
		|| (ValveCurrentMean > cDB_Saturate_COMPUTE[MEAN_INSP_VALVE_CURRENT_U16].cDB_TEST_DB.maxi))
	{
		/*%C Temp factor is not used anymore */
		TempCorrectionFactor = 1000;
		/*%C Check valve alarm activation */
		VEN_ValveCurrentSat = TRUE;
	}
	else
	{
		/*%C Temp factor calculation */
		TempCorrectionFactor = (((SWORD32)PreviousValveCurrentMean * 2) + (SWORD32)ValveCurrentMean - (cTEMP_CORRECTION_FACTOR_OFFSET * 3)) * 3333;
		TempCorrectionFactor = TempCorrectionFactor / ((SWORD32)IValveRef - (cTEMP_CORRECTION_FACTOR_OFFSET * 10));
		/*%C RAZ Valve current saturation */
		VEN_ValveCurrentSat = FALSE;
	}

	/*%C Valve current memo */
	PreviousValveCurrentMean = ValveCurrentMean;

 	/* calibration points selection depending on peep */
	if ((Adjust_Peep == 20)
	 || (Adjust_Peep == 30))
	{
		ValveCommandInit = (SWORD32)OffsetFasValve6;
		ValveCommandMin = (SWORD32)OffsetFasValve8;
		ValveCommandMax = (SWORD32)OffsetFasValve3;
	}
	else 
	{
		ValveCommandInit = (SWORD32)OffsetFasValve7;
		ValveCommandMin = (SWORD32)OffsetFasValve9;
		ValveCommandMax = (SWORD32)OffsetFasValve3;
	 }
	/* temperature correction*/
	ValveCommandInit = (ValveCommandInit * TempCorrectionFactor) / 100;
	DB_ComputeWrite(VALVE_COMMAND_INIT_U16, (UWORD16)ValveCommandInit);
	/*%C Read call to apply the saturation */
	ValveCommandInit = DB_ComputeRead(VALVE_COMMAND_INIT_U16);

	ValveCommandMin = (ValveCommandMin * TempCorrectionFactor) / 100;
	DB_ComputeWrite(VALVE_COMMAND_MIN_U16, (UWORD16)ValveCommandMin);
	/*%C Read call to apply the saturation */
	ValveCommandMin = DB_ComputeRead(VALVE_COMMAND_MIN_U16);
				
	ValveCommandMax = (ValveCommandMax * TempCorrectionFactor) / 100;
	/* Max saturation margin: +200 */
	ValveCommandMax = ValveCommandMax + 2000;
	DB_ComputeWrite(VALVE_COMMAND_MAX_U16, (UWORD16)ValveCommandMax);		  
	/*%C Read call to apply the saturation */
	ValveCommandMax = DB_ComputeRead(VALVE_COMMAND_MAX_U16);

	ValveCommandCoeff = ( ((SWORD32)OffsetFasValve5 - (SWORD32)OffsetFasValve9) * TempCorrectionFactor);
	ValveCommandCoeff = ValveCommandCoeff / cREF_VALVE_COMMAND_COEFF;
	DB_ComputeWrite(VALVE_COMMAND_COEFF_U16, (UWORD16)ValveCommandCoeff);
	/*%C Read call to apply the saturation */
	ValveCommandCoeff = DB_ComputeRead(VALVE_COMMAND_COEFF_U16);

/*%C Use default values if :       					*/
/*%C   Peep setting change       					*/
/*%C   Disconnexion status       					*/
/*%C   Alarm Disconnexion trigered					*/
/*%C   First cycle status						     	*/
	if ( (Adjust_Peep != Adjust_Peep_Memo) 
	  || (VEN_Disconnexion_Flag == TRUE)
	  || (Alarm_Disconnection >= ALARM_TRUE) 
	  || (VEN_FirstCycle == FALSE) )
	{
		DefaultValueToApply = TRUE;
	}
	else
	{
		DefaultValueToApply = FALSE;
	}


/******************************************************************************/	
/*%C Command valve calculation : Single Branche - Adult circuit               */
/******************************************************************************/	

/*%C Rinse flow computing    */
/*%C If we are in single branch without a pediatric circuit and PEEP is over 9cmH2O */  
	if ( (ExhalFlowUse == FALSE)
		  &&(PediatricCircuit == FALSE)
		  && (Adjust_Peep > 90)	)
	{
	/*%C Target Flow calculation */
		if 	(Adjust_Peep <= 120)
		{
	  		VEN_TargetFlow = VEN_RiseCompute(Adjust_Peep,
	     											50,
	     											100,
	     											120,
													300);
		}
		else
		{
	  		VEN_TargetFlow = VEN_RiseCompute(Adjust_Peep,
	     											130,
	     											350,
	     											150,
													600);
 	   }
 	/*%C If Default Value detected                      */
		if (DefaultValueToApply == TRUE)
		{   
			VEN_CommandFlow = ValveCommandInit;
		}
	/*%C else, valve opening computing if flow leak measure is not in the         */
	/*%C expected range (20% of flow)                                             */
		else if ((SWORD32)VEN_FleakMeasured > (SWORD32)(VEN_TargetFlow * 120UL / 100)) 
	   {
	/*%C Flow set point increase/decrease with an invert proportionnal peep       */
	/*%C correction value                                                         */
			if ((VEN_FleakMeasured - VEN_TargetFlow) > 150)
			{
		      // Décrément de la consigne avec un coefficient inversement proportionnel à la Pep
				VEN_CommandFlow = VEN_CommandFlow - (100*((SWORD32)VEN_TargetFlow)/(3*((Adjust_Peep)+10)) * ValveCommandCoeff) / 1000;
			}
	
			else if ((VEN_FleakMeasured - VEN_TargetFlow) > 70)
			{
			  // Décrément de la consigne avec un coefficient inversement proportionnel à la Pep
				VEN_CommandFlow = VEN_CommandFlow - (30*((SWORD32)VEN_TargetFlow)/(3*((Adjust_Peep)+10)) * ValveCommandCoeff) / 1000;
			}
	
			else if ((VEN_FleakMeasured - VEN_TargetFlow) > 0)
			{
			  // Décrément de la consigne avec un coefficient inversement proportionnel à la Pep
				VEN_CommandFlow = VEN_CommandFlow - (6*((SWORD32)VEN_TargetFlow)/(3*((Adjust_Peep)+10)) * ValveCommandCoeff) / 1000;
			}
	   }
	/*%C else, valve opening computing if flow leak measure is not in the         */
	/*%C expected range (20% of flow)                                             */
		else if ((SWORD32)VEN_FleakMeasured < (SWORD32)(VEN_TargetFlow * 80UL / 100))
	   {
	/*%C Flow set point increase/decrease with an invert proportionnal peep       */
	/*%C correction value                                                         */
			if ((Alarm_CheckValve >= ALARM_DETECTED) && (VEN_ValveCurrentSat == FALSE ))
			{
				VEN_CommandFlow = VEN_CommandFlow + 400;
			}

			if ((VEN_TargetFlow - VEN_FleakMeasured) > 150)
			{
		      // Décrément de la consigne avec un coefficient inversement proportionnel à la Pep
				VEN_CommandFlow = VEN_CommandFlow + (250*((SWORD32)VEN_TargetFlow)/(3*((Adjust_Peep)+10)) * ValveCommandCoeff) / 1000;
			}
	
			else if ((VEN_TargetFlow - VEN_FleakMeasured) > 70)
			{
			  // Décrément de la consigne avec un coefficient inversement proportionnel à la Pep
				VEN_CommandFlow = VEN_CommandFlow + (75*((SWORD32)VEN_TargetFlow)/(3*((Adjust_Peep)+10)) * ValveCommandCoeff) / 1000;
			}
	
			else if ((VEN_TargetFlow - VEN_FleakMeasured) > 0)
			{
			  // Décrément de la consigne avec un coefficient inversement proportionnel à la Pep
				VEN_CommandFlow = VEN_CommandFlow + (15*((SWORD32)VEN_TargetFlow)/(3*((Adjust_Peep)+10)) * ValveCommandCoeff) / 1000;
			}
	   }
 	}
/******************************************************************************/	
/*%C Command valve calculation : Double Branche - pediatric & adult circuit   */
/******************************************************************************/	
	else
	{
	/*%C Target Flow calculation */
 		VEN_TargetFlow = VEN_RiseCompute(Adjust_Peep,
	    	                  				50,
	        	              				100,
	            	          				150,
	                	      				300);

 	/*%C If Default Value detected                      */
		if (DefaultValueToApply == TRUE)
		{   
			VEN_CommandFlow = ValveCommandInit;
		}
	/*%C else, valve opening computing if flow leak measure is not in the         */
	/*%C expected range (20% of flow)                                             */
		else if ((SWORD32)VEN_FleakMeasured > (SWORD32)(VEN_TargetFlow * 120UL / 100)) 
	   {
	/*%C Flow set point increase/decrease with an invert proportionnal peep       */
	/*%C correction value                                                         */
			if ((VEN_FleakMeasured - VEN_TargetFlow) > 150)
			{
		      // Décrément de la consigne avec un coefficient inversement proportionnel à la Pep
				VEN_CommandFlow = VEN_CommandFlow - (100*((SWORD32)VEN_TargetFlow)/((Adjust_Peep)+10) * ValveCommandCoeff) / 1000;
			}
	
			else if ((VEN_FleakMeasured - VEN_TargetFlow) > 70)
			{
			  // Décrément de la consigne avec un coefficient inversement proportionnel à la Pep
				VEN_CommandFlow = VEN_CommandFlow - (30*((SWORD32)VEN_TargetFlow)/((Adjust_Peep)+10) * ValveCommandCoeff) / 1000;
			}
	
			else if ((VEN_FleakMeasured - VEN_TargetFlow) > 0)
			{
			  // Décrément de la consigne avec un coefficient inversement proportionnel à la Pep
				VEN_CommandFlow = VEN_CommandFlow - (6*((SWORD32)VEN_TargetFlow)/((Adjust_Peep)+10) * ValveCommandCoeff) / 1000;
			}
	   }
	/*%C else, valve opening computing if flow leak measure is not in the         */
	/*%C expected range (20% of flow)                                             */
		else if ((SWORD32)VEN_FleakMeasured < (SWORD32)(VEN_TargetFlow * 80UL / 100))
	   {
	/*%C Flow set point increase/decrease with an invert proportionnal peep       */
	/*%C correction value                                                         */
			if ((Alarm_CheckValve >= ALARM_DETECTED) && (VEN_ValveCurrentSat == FALSE ))
			{
				VEN_CommandFlow = VEN_CommandFlow + 400;
			}

			else if ((VEN_TargetFlow - VEN_FleakMeasured) > 150)
			{
		      // Décrément de la consigne avec un coefficient inversement proportionnel à la Pep
				VEN_CommandFlow = VEN_CommandFlow + (250*((SWORD32)VEN_TargetFlow)/((Adjust_Peep)+10) * ValveCommandCoeff) / 1000;
			}
	
			else if ((VEN_TargetFlow - VEN_FleakMeasured) > 70)
			{
			  // Décrément de la consigne avec un 50*100coefficient inversement proportionnel à la Pep
				VEN_CommandFlow = VEN_CommandFlow + (75*((SWORD32)VEN_TargetFlow)/((Adjust_Peep)+10) * ValveCommandCoeff) / 1000;
			}
	
			else if ((VEN_TargetFlow - VEN_FleakMeasured) > 0)
			{
			  // Décrément de la consigne avec un coefficient inversement proportionnel à la Pep
				VEN_CommandFlow = VEN_CommandFlow + (15*((SWORD32)VEN_TargetFlow)/((Adjust_Peep)+10) * ValveCommandCoeff) / 1000;
			}
	   }
   }
						 

/******************************************************************************/	
/*%C Command Valve Saturation                                                 */
/******************************************************************************/	

	/*%C Working saturation */
   VEN_CommandFlow = saturation(VEN_CommandFlow,
	                             ValveCommandMin,
										  ValveCommandMax);

	/*%C Specific case for Peep = 0 to 1 - Valve = Closed all the time */
	if (Adjust_Peep <= 10)
	{
		VEN_CommandFlow = cVALVE_CMD_OFF * 10;
	}

/******************************************************************************/	
/*%C Valve rise time calculation		                                          */
/******************************************************************************/	

 /*%C If Default Value detected                      */
	if (DefaultValueToApply == TRUE)
	{ 
	/*%C  If adust peep > 20, the rise time is computed                           */
		if (Adjust_Peep > 20)
		{
			if (PediatricCircuit == FALSE)
			{
				VEN_TempRiseOpenValve = VEN_RiseCompute(Adjust_Peep,
	     										50,
	     										500,
	     										150,
												200);
			}
			else
			{
		  		VEN_TempRiseOpenValve = 300;
			}  	
		}
	/*%C  If adust peep = 20, rise time = 600 ms                                  */
		else if (Adjust_Peep == 20)
		{
			if (PediatricCircuit == FALSE)
			{
				VEN_TempRiseOpenValve = 600;
			}
			else
			{
				VEN_TempRiseOpenValve = 300;
			}
		}
		else 
		{
   	/*%C  If adust peep = 0 or peep = 1, rise time is not used and the fas valve is */
	/*%C  fully closed for these settings */
		}
	}
/*%C else time computing if error of 20%                                      */
	else if (VEN_TRiseDecrem == TRUE)
/*%C Valve opening Rise time decreased of ten percent                         */
	{
		VEN_TempRiseOpenValve = VEN_TempRiseOpenValve - 
		                        VEN_TempRiseOpenValve / 10;
	}
/*%C else time computing if error of 20%                                      */
	else if (VEN_TRiseIncrem == TRUE)
   {
/*%C  Valve opening Rise time increased of ten percent                        */
		VEN_TempRiseOpenValve = VEN_TempRiseOpenValve + 
		                        VEN_TempRiseOpenValve / 10;
	}
/*%C Rise time limitation                                                     */
	if (Adjust_Peep < 20)
	{
/*%C  Rise time fixed to 800 ms if peep in [10;20[                            */
		if (Adjust_Peep == 10)
		{
			VEN_TempRiseOpenValve = 800;
		}
/*%C  Rise time fixed to 1500 ms if peep in [0;10[                            */
		else
		{
			VEN_TempRiseOpenValve = 1500;
		}
	}
	else
	{ 
		if (VEN_TempRiseOpenValve > High_Peep_Rise_Time)
		{
		   VEN_TempRiseOpenValve = High_Peep_Rise_Time;
		}
	}

	if (PediatricCircuit == TRUE)
	{
	  	if (Adjust_Peep < 100)
		{
/*%C  		Rise time min for opening valve fixed to 120 ms                         */
			if (VEN_TempRiseOpenValve < 120)
			{
	  	 		VEN_TempRiseOpenValve = 120;
			}
		}
		else
		{
/*%C  		Rise time min for opening valve fixed to 100 ms                         */
			if (VEN_TempRiseOpenValve < 100)
			{
	 	  		VEN_TempRiseOpenValve = 100;
			}
		}
	}
	else
	{
/*%C  	Rise time min for opening valve                         */
		if (ExhalFlowUse == TRUE)
		{
	   		TempRiseOpenValveMin = 200;
		}
		else
		{
			TempRiseOpenValveMin = (UWORD16)VEN_RiseCompute(Adjust_Peep,
	     													50,
	     													200,
	     													150,
															120);
		}
		if (VEN_TempRiseOpenValve < TempRiseOpenValveMin)
		{
  			VEN_TempRiseOpenValve = TempRiseOpenValveMin;
		}
	}



/*%C Analysis variable initialization                                         */
	VEN_TRiseIncrem = FALSE;
	VEN_TRiseDecrem = FALSE;
	VEN_MutexSignal1 = FALSE;
	VEN_MutexSignal2 = FALSE;
	VEN_MutexSignal3 = FALSE;
	VEN_PeMin = Computed_Pip;
	VEN_TRise_Rebond = 0;

/*%C Peep memorization                                                        */
	Adjust_Peep_Memo = Adjust_Peep;

/*%C Flow Leak memorization                                                        */
	VEN_MemoFleakMeasured = VEN_FleakMeasured;
}
