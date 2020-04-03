/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_ExhalationComputings.c                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function computes pressure and flow values during exhalation      */
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
#include "enum.h"
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_AlarmStatus.h"
#include "DB_Compute.h"
#include "Ventilation_Datas.h"
#include "CMP_ExhalationComputings.h"
#include "Ventilation_Compute_data.h"
#include "Ventilation_Constants.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void CMP_ExhalationComputings(void)
{
/* Real exhalated flow                                                        */
	SWORD16 Qreal = 0;
/* Gap on volume set point adaptation                                         */
	UWORD32 Ecart = 100;
/* Gap computing between patient pressure and exhalated pressure              */
	SWORD16 Delta = 0;
/* Volume inspirated per minute                                               */
	SWORD32 Computed_Vmi = 0;
/* Real exhalated flow                                                        */
	UWORD16 VtWob = 0;
/* Theorical flow inspiration                                                 */
	static UWORD32 TheoricalQinsp = 0;
/* Te counter value recovery from base                                        */
	UWORD16 TeCounterValue = TIM_ReadCounterValue(VEN_TE_COUNT);
/* Ti counter value recovery from base                                        */
	UWORD16 TiCounterValue = TIM_ReadCounterValue(VEN_TI_COUNT);
/* Sinus correction                                                     */
	UWORD32 CorrectorVtSinTemp = 0;
/* Flow sat flag                                                     */
	UWORD16 FlowSatFlag = FALSE;
/* Exhalated pressure setting recovery from base                              */
	UWORD16 Adjust_Peep = DB_CurrentRead(ADJUST_PEEP_U16);
/* Exhalated pressure computation recovery from base                           */
	SWORD16 Computed_Pep = (SWORD16)DB_ComputeRead(COMPUTED_PEEP_U16);
/* Local inspiratory flow                                                     */
	SWORD16 Vti = 0;
	SWORD32 VtiCorrection = 0;
/* Local exhalated flow during inspiration                                    */
	UWORD16 Vte_Insp = 0;
/* Inspiratory measure recovery from base                                     */
	SWORD16 Measure_Qinsp = (SWORD16)DB_ComputeRead(MEASURE_QINSP_S16);
/* Low Filter Inspiratory measure recovery from base                                     */
	SWORD16 Measure_Qinsp_Low_Filter = (SWORD16)DB_ComputeRead(FILTER_QI_LOW_S16);
/* Exhalated measure recovery from base                                       */
	SWORD16 Measure_Qexh = (SWORD16)DB_ComputeRead(MEASURE_QEXH_S16);
	SWORD16 Measure_Qexh_Filtred = (SWORD16)DB_ComputeRead(FILTER_QE_S16);
/* Exhalated measure recovery from base                                       */
	SWORD16 Filter_Patient_Pressure = 
							(SWORD16)DB_ComputeRead(FILTER_PATIENT_PRESSURE_S16);
/* Adjust Ramp recovery from base                                             */
	e_RampType Adjust_Ramp = DB_CurrentRead(ADJUST_RAMP_U16);
/* Adjust Vol Control recovery from base                                      */
	UWORD16 Adjust_Vol_Control = DB_CurrentRead(ADJUST_VOL_CONTROL_U16);
/* Alarm high pressure recovery from base                                     */
	UWORD16 Alarm_High_Pressure = DB_AlarmStatusRead(ALARM_HIGH_PRESSURE_U16);
/* Adjust Ti recovery from base                                     */
	UWORD16 Adjust_Ti_Control = DB_CurrentRead(ADJUST_TI_CONTROL_U16);
/* Rate measure recovery from base                                     */
	UWORD16 Measure_R = DB_ComputeRead(MEASURE_R_U16);
/* Valve detection state recovery from base */
	UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);
/* Current mode recovery from base */
	UWORD16 Current_Mode = DB_ControlRead(CURRENT_MODE_U16);
/* Simv cycle recovery from control base                                      */
	UWORD16 Simv_Cycles = DB_ControlRead(SIMV_CYCLES_U16);   
/* Pediatric Circuit state recovery from base */
	UWORD16 PediatricCircuit = DB_ConfigRead(ADJUST_PEDIATRIC_CIRCUIT_U16);
/* Exhal Flow Use state recovery from base */
	UWORD16 ExhalFlowUse = DB_ControlRead(EXHAL_FLOW_USE_U16);
/* Alarm disconnection state recovery from base                               */
	UWORD16 Alarm_Disconnection = DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);
/* Patient pressure recovery from base */
	SWORD16 Measure_Patient_Pressure = (SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);
/* Proximal pressure recovery from base */  
	SWORD16 Measure_Proximal_Pressure = (SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_PROXI_S16);
/*%C Computed ESTIMATED_PROXIMAL_PRESSURE_S16 recovery from Base  */
	SWORD16 EstimatedProximalPressure = DB_ComputeRead(ESTIMATED_PROXIMAL_PRESSURE_S16);
/*%C Computed PROXI_DETECTED_U16 recovery from Base  */
	UWORD16 ProxiDetected = DB_ControlRead(PROXI_DETECTED_U16);

#ifdef CONFIG_MEASURE_O2
/* Temp Value Calcul */
	UWORD32 FiO2 = 0;
#endif
	static SWORD32 PiMean = 0;	
	static SWORD32 VtiLeakage = 0;
	static SWORD32 Computed_Leak = 0;
/* Exhalated pressure measure array index                                     */
	static UWORD16 PepCounter = 0;
	static SWORD16 CumulPressExh = 0;
	SWORD16 QinspLeakCorrected = 0;
/* Counter              */
	UBYTE i = 0;
/*%C Inspiratory rise pressure initialization                                 */
	VEN_Rise_Pi_Set_Point = VEN_PepMeasured;




/*******************************************/
/*      Data recording for Qee computing   */
/*******************************************/

/*%C  Recording starts after 20 ms in exhalation phase  */
	if (TeCounterValue > 20)
	{
		// Limitation du pointeur
		VEN_Qee_SampleSize = VEN_Qee_SampleSize + 1;
		VEN_PtrMesureFlowPress = VEN_PtrMesureFlowPress + 1;
		VEN_PtrMesureFlowPress %= cPLATEAU_TABLES_LENGHT;
		// Stockage d'un tableau de 70 valeurs
		VEN_MesureFlowQinsp[VEN_PtrMesureFlowPress] = Measure_Qinsp;
		if (VEN_MesureFlowQinsp[VEN_PtrMesureFlowPress] < 0)
		{
			VEN_MesureFlowQinsp[VEN_PtrMesureFlowPress] = 0;
		}
		VEN_MesureFlowQexh[VEN_PtrMesureFlowPress] = Measure_Qexh;
		if (VEN_MesureFlowQexh[VEN_PtrMesureFlowPress] < 0)
		{
			VEN_MesureFlowQexh[VEN_PtrMesureFlowPress] = 0;
		}

 		if (ProxiDetected == FALSE)
		{	
			VEN_MesurePressure[VEN_PtrMesureFlowPress] = EstimatedProximalPressure;
		}
		else
		{
			VEN_MesurePressure[VEN_PtrMesureFlowPress] = Measure_Proximal_Pressure;
		}
	}
	else 
	{
 		// Initialization of the samplesize counter before starting recording */
		VEN_Qee_SampleSize = 0; 
		VEN_PtrMesureFlowPress = 0;
	}

/*%C Inspiration to exhalation transition                                     */
	if ( (VEN_Controller_Phase == VEN_EXH_FALL)
	  && (VEN_Controller_Phase != CMP_PreviousControllerPhase) ) 
	{										 
   
/************************************/
/* Vte computing during inspiration */
/************************************/

/*%C  Vte_Insp = summation of Qexh (during inspi) / 60   */
		Vte_Insp = (UWORD16)(VEN_MeasuredValues.CumulVteInsp / 60);
/*%C  Cumul Vte insp reset   */
		VEN_MeasuredValues.CumulVteInsp = 0;
/*%C  Vte insp writing in compute base                                        */
		DB_ComputeWrite(COMPUTED_VTE_INSP_U16,
								Vte_Insp);

/***************************************/					  
/* Inspiratory pressure mean computing */
/***************************************/
		PiMean = (VEN_MeasuredValues.CumulPi / (SWORD32)TiCounterValue) * 10;
		VEN_MeasuredValues.CumulPi = 0;

/************************************/
/*      Vti computing               */
/************************************/

/*%C  Negative value of cumul Vti are set to zero   */
		if (VEN_MeasuredValues.CumulVti < 0)
		{
			VEN_MeasuredValues.CumulVti = 0;
		}
/*%C  Vti = summation of Qinsp / 60   */
		Vti = (UWORD16)(VEN_MeasuredValues.CumulVti / 60);
/*%C  Qinsp sum of reset */
		VEN_MeasuredValues.CumulVti = 0;



/*************************************/
/*  Vti Corrected when a leak is present */
/**************************************/

		if(CMP_CumulVtiCorrected < 0)
		{
			CMP_CumulVtiCorrected = 0;
		}
		VtiLeakage = CMP_CumulVtiCorrected / 60;
		CMP_CumulVtiCorrected = 0;
		if (VtiLeakage < 0) 
		{
			VtiLeakage = 0;
		}



/*%C  Tubing compensation */
/*%C  Double Branch Compensation */
		if (ExhalFlowUse == TRUE)
		{
/*%C  	Double Branch Pediatric Compensation */
			if (PediatricCircuit == TRUE)
			{
				VtiCorrection = (VT_COEF_PEDIA_DBRANCH * (SWORD32)(VEN_MeasuredValues.PiMax - Computed_Pep)) / 100UL;
			}
/*%C  	Double Branch Adult Compensation */
			else
			{
				VtiCorrection = (VT_COEF_ADULT_DBRANCH * (SWORD32)(VEN_MeasuredValues.PiMax - Computed_Pep)) / 100UL;
			}
		}
/*%C  	Single Branch Compensation */
		else
		{
/*%C  		Single Branch Pediatric Compensation */
			if (PediatricCircuit == TRUE)
			{
				VtiCorrection = (VT_COEF_PEDIA_SBRANCH * (SWORD32)(VEN_MeasuredValues.PiMax - Computed_Pep)) / 100UL;
			}
/*%C  		Single Branch Adult Compensation */
			else
			{
				VtiCorrection = (VT_COEF_ADULT_SBRANCH * (SWORD32)(VEN_MeasuredValues.PiMax - Computed_Pep)) / 100UL;
			}
		}
/*%C  	Vti Correction Saturation */
		if (VtiCorrection > 100) 
		{
			VtiCorrection = 100;
		}
		else if (VtiCorrection < 0)
		{
			VtiCorrection = 0;
		}

/*%C  	Tubing compensation affectation */
		Vti = Vti - (SWORD16)VtiCorrection;

/*%C  	Tubing compensation affectation for Vti leak*/
		if (VtiCorrection > VtiLeakage)
		{
			VtiLeakage = 0;
		}
		else
		{
			VtiLeakage = VtiLeakage - (SWORD16)VtiCorrection;
		}

/*%C	Volume mode correction */		
		if (Current_Mode == VOL)
		{
			Vti = Vti + 5;
		}
	 
/*%C  Negative Vti filter */
		if (Vti < 0) 
		{
			Vti = 0;
		}


		///////////////////////////////////////
		//       Choix du Vt à utiliser      //
		////       et Vm computing  		 //

/*%C  Volume inspirated per minute computing                                  */
/*%C  Volume per minute (dl/min)= Inspiratory volume (ml) * rate measure      */
/*%C  The volume per minute is displayed in l/min.	   					      */
/*%C  Computation is made according to vt used						 		  */  

      
		if (ValveDetected == TRUE) 
		{	
			// Stockage de la valeur de Vt Corrected IHM
			DB_ComputeWrite(COMPUTED_VTI_U16,Vti);
			Computed_Vmi = (((SWORD32)Vti * (SWORD32)Measure_R) / 100);
		}
		else
		{
			// Stockage de la valeur de Vt Corrected IHM
			DB_ComputeWrite(COMPUTED_VTI_U16,(UWORD16)VtiLeakage);
		 	Computed_Vmi = (((SWORD32)VtiLeakage * (SWORD32)Measure_R) / 100);
		}
/*%C  Volume inspirated per minute writing in compute base                    */
		DB_ComputeWrite(COMPUTED_VMI_U16,
								(UWORD16)Computed_Vmi);

/*%C  Vti writing in compute base for VSIMV mode                              */
/*%C  (in order to simplify High/Low Vti/Vte alarm in this mode	            */
		if ( (Simv_Cycles == PSV_Cycle)
		  && (Current_Mode == VSIMV) )
		{
/*%C  	Psv Cycle flag storage in control base (for VTE computing)	         */
			DB_ControlWrite(SIMV_PSV_CYCLE_U16,
								TRUE);
		}
		else
		{
			DB_ControlWrite(SIMV_PSV_CYCLE_U16,
									FALSE);
		}

#ifdef CONFIG_MEASURE_O2
/************************************/
/* FiO2 Computing					*/
/************************************/
		TiCounterValue = TIM_ReadCounterValue(VEN_TI_COUNT);

		// use measured reading from sensor, sensor is slow to respond to gas 
		// changes and already provides smooth output of data
		FiO2 = DB_ComputeRead(MEASURE_FIO2);

		// round value
		if(FiO2%10 < 5)
		{
			FiO2 = FiO2/10;
		}
		else
		{
			FiO2 = FiO2/10+1;
		}
	// Saturation du calcul
		// Calculation Saturation
		if(FiO2 > 250) 
			FiO2 = 250; 

		DB_ComputeWrite(COMPUTED_FIO2, (UWORD16)(FiO2));
#endif

/************************************/
/* Flow set point correction        */
/************************************/
/*%C If flow mode selected and if phase has changed                           */
		if ( (VEN_ControllerType == CONTROL_FLOW)	
		  && (VEN_Controller_Phase != CMP_PreviousControllerPhase) )
		{
/*%C  If no alarm high pressure detected, a flow correction is computed       */
/*%C  This correction is only made when the gap is higher than 5%             */
			if (Alarm_High_Pressure == ALARM_FALSE)
			{
/*%C     when vti > 0, the gap is: adjust volume * 100 / inspirated volume    */
				if (Vti > 0)
				{
					Ecart = ((UWORD32)Adjust_Vol_Control * 100UL) / (UWORD32)Vti;
				}
/*%C     when vti <= 0, the gap is fixed to 100                               */
				else
				{
					Ecart = 110;
				}
		
/*%C     The ratio is limited to 100% , if out of range :   */
/*%C    if the VTI measurement is between VOL CONTROL - 2 ml and VOL CONTROL + 2 ml, the ratio is 100% */
/*%C	-->  CMP_DefaultQinsp keeps the same as TheoricalQinsp */ 
				if ( (Vti - (SWORD16)Adjust_Vol_Control < 2) 
				  && (Vti - (SWORD16)Adjust_Vol_Control > -2) )
				{
					Ecart = 100;
				}

/*%C     Saturation value between 95 and 105									         */
				Ecart = saturation((SWORD32)Ecart,
										(SWORD32)cQ_STEP_MIN,
										(SWORD32)cQ_STEP_MAX);
			}
/*%C  else, no alarm high pressure detected, the ratio is fixed to 100 and    */
/*%C  the flow set point keeps its value                                      */
			else
			{ 
				Ecart = 100;  
			}
/*%C  Theorical flow set point computing                                      */
/*%C  Computing with rectangle ramp                                           */
			if (Adjust_Ramp == RAMP_RECTANGLE)
			{
				TheoricalQinsp = ((((UWORD32)Adjust_Vol_Control * 60UL *10UL)
										/ (UWORD32)Adjust_Ti_Control)+ cOFFSETQINSP);
			}
			else if (Adjust_Ramp == RAMP_SINUS)
			{
				TheoricalQinsp = 0; 
			}			
/*%C  Computing with decelerated ramp                                         */
			else
			{
				TheoricalQinsp = ( (((UWORD32)Adjust_Vol_Control *3UL *10UL *60UL)/ 
										(2UL*(UWORD32)Adjust_Ti_Control)) + (UWORD32)cOFFSETQINSP);
			}
		
/*%C  New flow set point computing                                            */
			CMP_DefaultQinsp = (CMP_DefaultQinsp * Ecart)/ 100;
	
/*%C  Flow inspiration limitation :                                           */

/*%C  Flow inspiration limitation (for decelerated or rectangle ramp) :       */
			if (Adjust_Ramp != RAMP_SINUS)
			{		
/*%C  	Max flow limitation :                                                */
/*%C  	Limitation when theorical Qinsp < 200                                */
				if (TheoricalQinsp < 200)
				{
/*%C     	Default Qinsp limited to 3 * theorical Qinsp                      */
					if (CMP_DefaultQinsp > 3 * TheoricalQinsp)
					{
						CMP_DefaultQinsp = 3 * TheoricalQinsp;
/*%C 				The Saturation of autoadaptative Volume Loop is reached	 */
						FlowSatFlag = TRUE;
					}
				}
/*%C  	Limitation when theorical Qinsp >= 200                               */
				else 
				{
/*%C     	Default Qinsp limited to 2 * theorical Qinsp                    */
					if (CMP_DefaultQinsp > (TheoricalQinsp * 200) / 100)
					{
						CMP_DefaultQinsp = (TheoricalQinsp * 200) / 100;
/*%C 				The Saturation of autoadaptative Volume Loop is reached	 */
						FlowSatFlag = TRUE;
					}
				}

/*%C  	Min flow limitation :                                                */
/*%C  	Default Qinsp limited to 0.5 * theorical Qinsp                       */
				if (CMP_DefaultQinsp < (TheoricalQinsp * 50) / 100)
				{
					CMP_DefaultQinsp = (TheoricalQinsp * 50) / 100; 
/*%C 			The Saturation of autoadaptative Volume Loop is reached	 */        
					FlowSatFlag = TRUE;					  
				}
			}

/*%C  Flow inspiration set point update                                       */
			VEN_Qi_Set_Point = (UWORD16)CMP_DefaultQinsp;

/*%C  Correction value computing for sinus ramp                               */
			if (Adjust_Ramp == RAMP_SINUS)
			{
				CorrectorVtSinTemp = ((UWORD32)CMP_CorrectorVtSin * Ecart) / 100UL;
				CMP_CorrectorVtSin = (UWORD16)CorrectorVtSinTemp;

/*%C  	Max correction value saturation                               */
				if (CMP_CorrectorVtSin >= 400)	
				{
					CMP_CorrectorVtSin = 400;
/*%C  		Check volume alarm flag activation                               */
					FlowSatFlag = TRUE;
				}
/*%C  	Min correction value saturation                               */
				else if (CMP_CorrectorVtSin <= 50)
				{
					CMP_CorrectorVtSin = 50;
/*%C  		Check volume alarm flag activation                               */
					FlowSatFlag = TRUE;
				}
				else
				{
					FlowSatFlag = FALSE;
				}
				DB_ControlWrite(FLOW_SAT_FLAG_U16,FlowSatFlag);
			}
		}

/*%C Max pressure for adaptation update                                       */
		VEN_PMax = VEN_MeasuredValues.PiMax;

/*%C  Pip is rounded to the closer integer value                  */
		VEN_MeasuredValues.PiMax = VEN_MeasuredValues.PiMax - (VEN_MeasuredValues.PiMax % 5);
/*%C  Inspiratory pressure max storage in compute base                         */
		DB_ComputeWrite(COMPUTED_PIP_U16,
								VEN_MeasuredValues.PiMax);
		// reset Inspiratory pressure max measure 
		VEN_MeasuredValues.PiMax = 0;

		//  Update low-pass filtered peak inspiratory pressure used for display
		//  LPF PIP is truncated to the nearest 0.5 cmH2O value
		VEN_MeasuredValues.LpfPiMax = VEN_MeasuredValues.LpfPiMax - (VEN_MeasuredValues.LpfPiMax % 5);
		DB_ComputeWrite(COMPUTED_LPF_PIP_U16, VEN_MeasuredValues.LpfPiMax);
		// reset LPF Peak Inspiratory Pressure
		VEN_MeasuredValues.LpfPiMax = 0;

/*%C  PValveMax is rounded to the closer integer value                  */
		VEN_MeasuredValues.PValveMax = VEN_MeasuredValues.PValveMax - (VEN_MeasuredValues.PValveMax % 5);
/*%C  PValveMax pressure max storage in compute base                         */
		DB_ComputeWrite(COMPUTED_P_VALVE_MAX_U16,
								VEN_MeasuredValues.PValveMax);
/*%C  Valve pressure max measure reset                                  */
		VEN_MeasuredValues.PValveMax = 0;
	}

/************************************/
/*  EXHALATED PRESSURE COMPUTE      */
/************************************/

/*%C Index limitation (10 values)      */
	PepCounter %= cPEP_MEASURE_NUMBER;

/*%C Patient pressure memorization (10 values array)      */
	VEN_MeasuredValues.MesurePep[PepCounter++] = Filter_Patient_Pressure;

/*%C Exhalated pressure average reset      */
	VEN_PepMeasured = 0;

/*%C Exhalated pressure average computing (5 values)      */
	for(i=0; i<cPEP_MEASURE_NUMBER; i++)
	{
		VEN_PepMeasured = VEN_PepMeasured +
								VEN_MeasuredValues.MesurePep[(PepCounter + i)%cPEP_MEASURE_NUMBER];
	}
	VEN_PepMeasured = VEN_PepMeasured / cPEP_MEASURE_NUMBER;

/*%C values less than 0.5mbar are filtered      */
	if (VEN_PepMeasured <= 0)
	{
		VEN_PepMeasured = 0;
	}
	else if(Adjust_Peep == 0)
	{
/*%C  VEN_PepMeasured is rounded to the closer integer value                  */
		VEN_PepMeasured = VEN_PepMeasured - (VEN_PepMeasured % 5);
	}
	else
	{
/*%C  VEN_PepMeasured is rounded to the closer integer value                  */
		VEN_PepMeasured = VEN_PepMeasured - (VEN_PepMeasured % 5) + 5;
	}

	
/************************************/
/* Exhalated flow computing         */
/************************************/
/*%C The exhalated flow summation is made with the difference between         */
/*%C Measure_Qexh and Measure_Qinsp  with Measure_Qexh > Measure_Qinsp        */
		Qreal = Measure_Qexh - Measure_Qinsp;

/*%C When the flow difference is between -10 and +10, no Vte integration          */
	if ((Qreal < -10) || (Qreal > 10))
	{
		VEN_MeasuredValues.CumulVte = VEN_MeasuredValues.CumulVte + Qreal;
	}
	
			
	QinspLeakCorrected = (SWORD16)((SWORD16)Measure_Qinsp - (SWORD16)VEN_LeakVtiCorrection);
	DB_ComputeWrite(MEASURE_QINSP_LEAKCORRECTED_S16,(UWORD16)QinspLeakCorrected);

/*%C Cumul pressure expiration summation									  */   
	CumulPressExh = CumulPressExh + (Adjust_Peep - Measure_Patient_Pressure);

/************************************/
/* WOB curves during exhalation     */
/************************************/
/*%C Exhalated flow summation     */
	VEN_MeasuredValues.CumulVtWob = 
							VEN_MeasuredValues.CumulVtWob - (SWORD32)Qreal;
	
	if (VEN_MeasuredValues.CumulVtWob < 0)
	{
		VEN_MeasuredValues.CumulVtWob = 0;
	}

/*%C VtWob computing if valve is detected                                     */
	if (ValveDetected == TRUE)
	{
/*%C  VtWob = CumulVtWob / 6                                                  */
		VtWob = (UWORD16)(VEN_MeasuredValues.CumulVtWob / 6);
/*%C  Limitation value for WOB curve display (32000)                          */
		if (VtWob > 32000)
		{
			VtWob = 32000;
		}
/*%C  Value writing in compute base                                           */
		DB_ComputeWrite(CURVE_CORRECTED_VT_WOB_U16,
								VtWob);
	}
	else
	{
/*%C  Value writing in compute base                                           */
		DB_ComputeWrite(CURVE_CORRECTED_VT_WOB_U16,
								0);
	}																
	
/*%C Summation of inspirated flow during exhalation                           */
	VEN_MeasuredValues.CumulVtiExh = VEN_MeasuredValues.CumulVtiExh + 
							(SWORD32)Measure_Qinsp;

/************************************/
/* Flow negative saturation check   */
/************************************/

/*%C If flow has negative saturation at 500ms then Alarm check valve */
	if (TeCounterValue == 500)
	{
		if   ( (Measure_Qinsp_Low_Filter < -150)
			&& ((SWORD32)VEN_MemoFleakMeasured < (SWORD32)(VEN_TargetFlow * 80UL / 100)) )

		{
			VEN_FlowNegSat = TRUE;
		}
		else 
		{
			VEN_FlowNegSat = FALSE;
		}
	}
	
/************************************/
/* Exhal Flow max computing         */
/************************************/
/*%C Exhal Flow max computing (Max of measure Qexp)         */
	
	if (Measure_Qexh_Filtred > VEN_ExhalFlowMaxMeasured)
	{
		VEN_ExhalFlowMaxMeasured = Measure_Qexh_Filtred;
	}

/***********************************************************************/
/* Signal analysis for ramp time valve opening autoadaptation          */
/***********************************************************************/

/*%C Gap computing between patient pressure and exhalated pressure min        */
	Delta = Filter_Patient_Pressure - VEN_PeMin;

/*%C Exhalated pressure min update (Pe min is min of filter patient pressure) */
	if (Filter_Patient_Pressure < VEN_PeMin)
	{
		VEN_PeMin = Filter_Patient_Pressure;
		VEN_TRise_Rebond = TeCounterValue;
	}
 
/*%C Mutex rearm when exhalated pressure min < adjusted peep + 5 and          */
/*%C exhalation delay > rise opening valve time                               */
	if ( (VEN_PeMin < (SWORD16)Adjust_Peep + 5)
	  && (TeCounterValue > VEN_TempRiseOpenValve) )
	{
		VEN_MutexSignal1 = FALSE;
	}
/*%C If the exhalated pressure + 0.5 cmH2O is not reached before Te + 300 ms  */
/*%C there is an "exhalated leg"  */

	if ( (Filter_Patient_Pressure > (SWORD16)Adjust_Peep + 5)
	  && (TeCounterValue == 300) 
	  && (VEN_MutexSignal1 == FALSE) 
	  && (VEN_MutexSignal3 == FALSE) )
	{
/*%C  "Big leg priority"  */
		if (Filter_Patient_Pressure - (SWORD16)Adjust_Peep > 10)
		{ 
			VEN_MutexSignal2 = TRUE;
		}
		VEN_MutexSignal1 = TRUE;
		VEN_TRiseIncrem = TRUE;
		VEN_TRiseDecrem = FALSE;
	}
/*%C  If the exhalated pressure is higher than exhalated pressure min  */
/*%C  +- 10 mbar  */
	else if ( ( ( (Delta > (SWORD16)Adjust_Peep / 10) 
			   && (Delta > 3) )
			 || (Delta > 10) )
		   && (VEN_PeMin < (SWORD16)Adjust_Peep + 5)
		   && (TeCounterValue < VEN_TRise_Rebond + 700)
		   && (VEN_MutexSignal1 == FALSE)
		   && (VEN_MutexSignal2 == FALSE) )
	{
		VEN_MutexSignal1 = TRUE;
		VEN_TRiseIncrem = FALSE;
		VEN_TRiseDecrem = TRUE;
	}
/*%C  If there is a big rebound  */
	else if ( ( ( (Delta > (SWORD16)Adjust_Peep / 5)
			  && (Delta > 6) )
		    || (Delta > 20) )
		    && (VEN_PeMin < (SWORD16)Adjust_Peep + 5)
		    && (TeCounterValue < VEN_TRise_Rebond + 700) 
		    && (VEN_MutexSignal1 == FALSE) )
	{
		VEN_MutexSignal1 = TRUE;
		VEN_MutexSignal3 = TRUE;
		VEN_TRiseIncrem = FALSE;
		VEN_TRiseDecrem = TRUE;
	}

  /*%C Reccording of FLOW_SAT_FLAG_U16 in DB_Control at Inspiration to Exhalation transition */
	if ( (VEN_Controller_Phase == VEN_EXH_FALL)
	  && (VEN_Controller_Phase != CMP_PreviousControllerPhase) ) 
	{
		DB_ControlWrite(FLOW_SAT_FLAG_U16,
								FlowSatFlag);

		// Set the negative flow flag to prevent the occlusion 
		// alarm from being activated due to a detection of patient effort.
		if (VEN_NegativeFlowCounter >= MAX_NEGATIVE_FLOW_COUNTER)
		{
			VEN_DetectedNegativeFlow = TRUE;		  
		}
		else
		{
			VEN_DetectedNegativeFlow = FALSE;
		}
	}

/************************************************************/
/* Update of Qee computing clearance  (For Qleak estimation)*/
/************************************************************/

  	
}

