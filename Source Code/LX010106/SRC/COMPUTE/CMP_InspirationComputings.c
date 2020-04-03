/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_InspirationComputings.c                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function computes pressure and flow values during inspiration     */
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
#include "limits.h"
#include "DB_Current.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "Ventilation_Datas.h"
#include "CMP_InspirationComputings.h"
#include "Ventilation_Compute_data.h"
#include "Ventilation_Constants.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void CMP_InspirationComputings(void)
{
   SWORD16 Vte = 0;
   SWORD32 VteCorrection = 0;
   SWORD16 Reste = 0;
   SWORD16 PatientPressure = 0;
   SWORD16 VtiExh = 0;
   UWORD16 VtWob = 0;
   UWORD16 VenTiCount = TIM_ReadCounterValue(VEN_TI_COUNT);
   SWORD16 LowPressure = 0;
#ifdef CONFIG_VTE
   static UWORD16 VteCounter = 0;
   SWORD16 VteAverage = 0;
   static SWORD16 VteArray[3];
   UWORD16 i = 0;
#endif

#define VTE_MAX_BUFF  (5)
   UWORD16 i5 = 0;
   static UWORD16 Vte5dex = 0;
   static UWORD16 Vte5Counter = 0;
   static SWORD32 Sum5 = 0;
   static SWORD32 Vte5Average = 0;
   static SWORD32 Vte5Avg = 0;
   static SWORD32 Vte5diff = 0;
   static SWORD32 previousVte = 0;
   static SWORD32 Vte5Array[VTE_MAX_BUFF] = { 0, 0, 0, 0, 0 };

/* Exhalated pressure setting recovery from base                              */
   UWORD16 Adjust_Peep = DB_CurrentRead(ADJUST_PEEP_U16);
/* Exhalated flow recovery from base */
   SWORD16 MeasureQExh = (SWORD16)DB_ComputeRead(MEASURE_QEXH_S16);
/* Inspiratory Vt recovery from base */
   SWORD16 Vti = (SWORD16)DB_ComputeRead(COMPUTED_VTI_U16);
/* Inspiratory flow recovery from base */
   SWORD16 MeasureQInsp = (SWORD16)DB_ComputeRead(MEASURE_QINSP_S16);
   SWORD16 CurrentQInsp = 0;
/* Inspiratory flow recovery from base */
   UWORD16 Computed_Vti = DB_ComputeRead(COMPUTED_VTI_U16);
/* Patient pressure recovery from base */
   SWORD16 Measure_Patient_Pressure =
      (SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);
// Retrieve low-pass filtered Patient pressure
   SWORD16 Lpf_Patient_Pressure =
      (SWORD16)DB_ComputeRead(LPF_PATIENT_PRESSURE_S16);
/* Valve pressure recovery from base */
   SWORD16 Measure_Valve_Pressure =
      (SWORD16)DB_ComputeRead(MEASURE_VALVE_PRESSURE_S16);
   SWORD16 Computed_Pep =
      (SWORD16)DB_ComputeRead(COMPUTED_PEEP_U16);
/* Inspiratory filtered flow recovery from base */
   SWORD16 Filter_Qi_Low = (SWORD16)DB_ComputeRead(FILTER_QI_LOW_S16);
/* Valve detection state recovery from base */
   UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);
/* Rate measure recovery from base                                     */
   UWORD16 Measure_R = DB_ComputeRead(MEASURE_R_U16);
/* Simv cycle recovery from control base                                      */
   UWORD16 Simv_Cycles = DB_ControlRead(SIMV_CYCLES_U16);
   UWORD16 Simv_Psv_Cycle = DB_ControlRead(SIMV_PSV_CYCLE_U16);
/* Volume exhalated per minute                                                */
   SWORD32 Computed_Vme = 0;
/*%C High pressure flag state recovery in Data base  */
   UWORD16 High_Pressure_Detected = DB_ControlRead(HIGH_PRESSURE_DETECTED_U16);
/*%C Cumul pressure inspiration state recovery in Data base  */
   SWORD16 CumulPressInsp = DB_ComputeRead(CUMUL_PRESS_INSP_S16);
/* Current mode recovery from base */
   UWORD16 Current_Mode = DB_ControlRead(CURRENT_MODE_U16);
   UWORD16 ExhalFlowUse = DB_ControlRead(EXHAL_FLOW_USE_U16);
/* Pediatric Circuit state recovery from base */
   UWORD16 PediatricCircuit = DB_ConfigRead(ADJUST_PEDIATRIC_CIRCUIT_U16);
/* Valve current recovery from base */
   UWORD16 MeasureValveCurrent = (UWORD16)DB_ComputeRead(MEASURE_VALVE_CURRENT_U16);
/* Inspiratory max pressure recovery from base                                */
   UWORD16 Computed_Pip =  DB_ComputeRead(COMPUTED_PIP_U16);
   SWORD16 Qcorrection = DB_ComputeRead(COMPUTE_CORRECTED_Q);
   SWORD16 QinspLeakCorrected = 0;

   // This constant negative number helps to detect patient effort.
   // To determine this constant number we had to do an occlusion test
   // described in the clinical manual (occlusion test) section F.5.
   // Following those steps in section F.5 and capturing flow data from the vent
   // shows that the flow hovers between -3.6 to 2.0 lpm during inhalation plateau
   // with an occluded circuit.  Thus, by choosing a number below the normal
   // range of an occluded circuit flow data, it will ensure the flow was caused by
   // a patient effort not from an occluded circuit.
   const SWORD16 NEGATIVE_FLOW_CRITERIA = -50;

   CurrentQInsp = MeasureQInsp;
/*%C The values computing is made on the exhalation/inspiration transition    */
   if ((VEN_Controller_Phase == VEN_INSP_RISE)
       && (VEN_Controller_Phase != CMP_PreviousControllerPhase))
   {
/************************************/
/* Leak computing 			        */
/************************************/

      CMP_LeakFactors();



/************************************/
/* Exhal Flow using			        */
/************************************/

      /*%C If no Exhal Flow during the exhalation */
      if ((VEN_ExhalFlowMaxMeasured > 0)
          &&	(VEN_MeasuredValues.CumulVte > 0))
      {
         /*%C  Write the Flag on the base - The Exhal flow is used*/
         if (VEN_FirstCycle == TRUE)
         {
            DB_ControlWrite(EXHAL_FLOW_USE_U16,
                            TRUE);
         }
/*%C  		Exhalated flow compute (summation of Qexh during exhalation / 60 )      */
         Vte = (SWORD16)(VEN_MeasuredValues.CumulVte / 60);
         VEN_MeasuredValues.CumulVte = 0;
/*%C  		Tubing compensation */
/*%C  		Double Branch Compensation */
         if (ExhalFlowUse == TRUE)
         {
/*%C  		Double Branch Pediatric Compensation */
            if (PediatricCircuit == TRUE)
            {
               VteCorrection = (VT_COEF_PEDIA_DBRANCH * (SWORD32)(Computed_Pip - VEN_PepMeasured)) / 100UL;
            }
/*%C  		Double Branch Adult Compensation */
            else
            {
               VteCorrection = (VT_COEF_ADULT_DBRANCH * (SWORD32)(Computed_Pip - VEN_PepMeasured)) / 100UL;
            }
         }
/*%C  	Single Branch Compensation */
         else
         {
/*%C  		Single Branch Pediatric Compensation */
            if (PediatricCircuit == TRUE)
            {
               VteCorrection = (VT_COEF_PEDIA_SBRANCH * (SWORD32)(Computed_Pip - VEN_PepMeasured)) / 100UL;
            }
/*%C  		Single Branch Adult Compensation */
            else
            {
               VteCorrection = (VT_COEF_ADULT_SBRANCH * (SWORD32)(Computed_Pip - VEN_PepMeasured)) / 100UL;
            }
         }
/*%C  	Vte Correction Saturation */
         if (VteCorrection > 100)
         {
            VteCorrection = 100;
         }
         else if (VteCorrection < 0)
         {
            VteCorrection = 0;
         }

/*%C  	Tubing compensation affectation */
         Vte = Vte - (SWORD16)VteCorrection;

/*%C  		Vte is decrease to -5ml except for VOL mode  */
         if ((Current_Mode != VOL)
             && (Current_Mode != CPAP))
         {
            Vte = Vte - 5;
         }

/*%C  	Saturation VTE never < 10ml after a calculation*/
         if (Vte <= 10)
         {
            Vte = 10;
         }
      }
      else
      {
         /*%C  Write the Flag on the base - The Exhal flow is not used*/
         DB_ControlWrite(EXHAL_FLOW_USE_U16,
                         FALSE);
         /*%C In this case Vte = 0 */
         VEN_MeasuredValues.CumulVte = 0;
         Vte = 0;
      }
      /*%C RAZ of the memorized value */
      VEN_ExhalFlowMaxMeasured = 0;

      if (Vte5Counter == 0)
      {
         previousVte = Vte;
      }

      // store vte for averaging
      Vte5Array[Vte5dex++] = Vte;

      Vte5Counter++;
      if (Vte5Counter > VTE_MAX_BUFF)
      {
         Vte5Counter = VTE_MAX_BUFF;
      }

      // sanity check
      if (Vte5Counter < 1)
      {
         Vte5Counter = 1;
      }

      // keep index from going out of bounds
      if (Vte5dex >= VTE_MAX_BUFF)
      {
         Vte5dex = 0;
      }

      Sum5 = 0;
      for (i5 = 0; i5 < Vte5Counter; i5++)
      {
         Sum5 += Vte5Array[i5];
      }
      Vte5Average = Sum5 / Vte5Counter;
      Vte5Avg = Vte5Average;

      Vte5diff = Vte - previousVte;

      // abs value
      if (Vte5diff < 0)
      {
         Vte5diff *= -1;
      }

      // if the difference of the previous to current greater than 15 percent
      // reset the averages
      if (Vte5diff > ((5 + ((15 * previousVte) / 100))))
      {
         for (i5 = 0; i5 < VTE_MAX_BUFF; i5++)
         {
            Vte5Array[i5] = 0;
         }
         Sum5 = 0;
         Vte5Counter = 0;
         Vte5dex = 0;
         Vte5Average = 0;
         Vte5Avg = Vte;
      }

      // sanity check
      if (Vte5Avg < 0)
      {
         Vte5Avg = 0;
      }

      DB_ComputeWrite(COMPUTED_VTE_U16,
                      (UWORD16)Vte5Avg);

      previousVte = Vte;

#ifdef CONFIG_VTE
/*%C  Vte array filling				                                             */
      VteArray[VteCounter] = Vte;
      VteCounter = VteCounter + 1;
      VteCounter = VteCounter % 3;

/*%C Vte average on 3 cycles		                                             */
      for (i = 0; i < cNB_VTE_CYLES; i++)
      {
         VteAverage = VteAverage + VteArray[i];
      }
      VteAverage = VteAverage / cNB_VTE_CYLES;

/*%C Vte flag detection is set if Vte average is under 20ml                  */
      if (VteAverage < cVTE_MIN_DETECTION)
      {
         DB_ControlWrite(BLOC_EXPI_DETECTED_U16, FALSE);
      }
      else
      {
         DB_ControlWrite(BLOC_EXPI_DETECTED_U16, TRUE);
      }
      VteAverage = 0;
#endif
/*%C  Peep writing in compute base                                            */
      DB_ComputeWrite(COMPUTED_PEEP_U16,
                      VEN_PepMeasured);
/************************************/
/*      Vme computing                */
/************************************/

/*%C  Volume expired per minute computing                                     */
/*%C  Volume per minute (dl/min)= Exhalated volume (ml) * rate measure      	*/
/*%C  The volume per minute is displayed in l/min (2 digits => /100)			   */
      Computed_Vme = (((SWORD32)Vte * (SWORD32)Measure_R) / 100);
/*%C  Volume per minute writing in compute base                               */
      DB_ComputeWrite(COMPUTED_VME_U16,
                      (UWORD16)Computed_Vme);

      /*%C  Inspiratory flow computing (during exhalation)                          */
      VEN_MeasuredValues.CumulVtiExh = VEN_MeasuredValues.CumulVtiExh / 60;
      // clip Vti for assignment to 16-bit signed
      if (VEN_MeasuredValues.CumulVtiExh > SWORD16_MAX)
      {
         VtiExh = SWORD16_MAX;
      }
      else if (VEN_MeasuredValues.CumulVtiExh < SWORD16_MIN)
      {
         VtiExh = SWORD16_MIN;
      }
      else
      {
         VtiExh = (SWORD16)(VEN_MeasuredValues.CumulVtiExh);
      }
      VEN_MeasuredValues.CumulVtiExh  = 0;
      DB_ComputeWrite(COMPUTED_VTI_EXH_S16,
                      VtiExh);
      VEN_IsVtiExhUpdated = TRUE;  // This flag tells Check Valve alarm that the VTI EXH data has been updated. - SCR219
   }


/*%C Inspiratory flow filtering - QInsp = 0                            */
/*%C If Patient pressure < Pep mesured and Ti_mesured < 200ms to avoid */
/*%C leakage error in the Vti compute */
   if ((Measure_Patient_Pressure < (Computed_Pep + 20)) && (VenTiCount < 200))
   {
      CurrentQInsp = 0;
   }

/*%C WOB curve during inspiration                                             */

/*%C Inspirated flow summation                                                */
   VEN_MeasuredValues.CumulVtWob = VEN_MeasuredValues.CumulVtWob + CurrentQInsp;

/*%C Vt WOB is computed when the valve is detected                            */
   if (ValveDetected == TRUE)
   {
/*%C  Vt WOB reset if exhalation to inspiration transition                */
      if ((VEN_Controller_Phase == VEN_INSP_RISE)
          && (VEN_Controller_Phase != CMP_PreviousControllerPhase))
      {
         VEN_MeasuredValues.CumulVtWob = 0;
      }

/*%C  Spontaneous VT computing for WOB curve display                          */
      VEN_MeasuredValues.CumulVtWob = VEN_MeasuredValues.CumulVtWob / 6;
      VtWob = (UWORD16)(VEN_MeasuredValues.CumulVtWob);

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

/*%C Inspiratory pressure summation                                           */
   VEN_MeasuredValues.CumulPi = VEN_MeasuredValues.CumulPi + Measure_Patient_Pressure;

/*%C Inspiratory flow summation                                               */
   VEN_MeasuredValues.CumulVti = VEN_MeasuredValues.CumulVti + CurrentQInsp;

   // reset the negative flow counter every start of inspiration.
   if ((VEN_Controller_Phase == VEN_INSP_RISE)
       && (VEN_Controller_Phase != CMP_PreviousControllerPhase))
   {
      VEN_NegativeFlowCounter = 0;
   }

   // Detect a patient effort by counting the number of negative
   // flows consecutively up to MAX_NEGATIVE_FLOW_COUNTER.
   // If negative flows are detected then prevent the occlusion
   // alarm from being activated.
   if (MeasureQInsp < NEGATIVE_FLOW_CRITERIA)
   {
      if (VEN_NegativeFlowCounter >= MAX_NEGATIVE_FLOW_COUNTER)
      {
         // don't update the negative flow counter.
      }
      else
      {
         // Increment negative flow counter since flow is below the
         // NEGATIVE_FLOW_CRITERIA and the negative flow counter
         // has not exceed or equal to MAX_NEGATIVE_FLOW_COUNTER.
         VEN_NegativeFlowCounter++;
      }
   }
   else
   {
      // Only reset the counter if MAX_NEGATIVE_FLOW_COUNTER hasn't
      // reached.
      if (VEN_NegativeFlowCounter < MAX_NEGATIVE_FLOW_COUNTER)
      {
         VEN_NegativeFlowCounter = 0;
      }
   }

/*%C Inspiratory valve current summation                                               */
   VEN_MeasuredValues.CumulValveCurrent = VEN_MeasuredValues.CumulValveCurrent + MeasureValveCurrent;
   VEN_CptCumulValveCurrent = VEN_CptCumulValveCurrent + 1;

   QinspLeakCorrected = (SWORD16)((SWORD16)MeasureQInsp - (SWORD16)VEN_LeakVtiCorrection);

   // estimated corrected leak flow can not be negative during inspiration
   // this would mean that the estimated leak flow is greater than the measured
   // flow which is not possible during inspiration
   // if it is do not integrate leak estimation with Vti on this cycle.
   if (QinspLeakCorrected > 0)
   {
/*%C  Corrected Vti for leak circuit */
      CMP_CumulVtiCorrected = CMP_CumulVtiCorrected
         + ((SWORD32)MeasureQInsp
            - (SWORD32)VEN_LeakVtiCorrection);
   }
   DB_ComputeWrite(MEASURE_QINSP_LEAKCORRECTED_S16, (UWORD16)QinspLeakCorrected);
/*%C Negative inspiratory flow filtering                                      */
/*%C If Patient pressure < Pep mesured and Ti_mesured < 200ms to avoid */
/*%C leakage error in the Vte during Insp compute */
   if ((MeasureQExh < 0) ||
       ((Measure_Patient_Pressure < (Computed_Pep + 20)) && (VenTiCount < 200)))
   {
      MeasureQExh = 0;
   }
/*%C Exhalated flow summation during inspiration                              */
   VEN_MeasuredValues.CumulVteInsp = VEN_MeasuredValues.CumulVteInsp +
      MeasureQExh;

/*%C Inspiratory pressure max computing (max of measured patient pressure)    */
   if (Measure_Patient_Pressure > VEN_MeasuredValues.PiMax)
   {
      VEN_MeasuredValues.PiMax = Measure_Patient_Pressure;
   }

   // Pi max using the low-pass filter
   if (Lpf_Patient_Pressure > VEN_MeasuredValues.LpfPiMax)
   {
      VEN_MeasuredValues.LpfPiMax = Lpf_Patient_Pressure;
   }

/*%C Valve pressure max computing */
   if (Measure_Valve_Pressure > VEN_MeasuredValues.PValveMax)
   {
      VEN_MeasuredValues.PValveMax = Measure_Valve_Pressure;
   }

/*%C Auto adaptation pressure max computing during inspiration                */
   if (Measure_Patient_Pressure > CMP_PMaxAutoAdapt)
   {
      CMP_PMaxAutoAdapt = Measure_Patient_Pressure;
   }

/*%C Inspiratory flow max computing during 200ms                              */
   if ((Filter_Qi_Low > CMP_FlowMaxMeasuredInsp)
       && (VenTiCount < 1000))
   {
      CMP_FlowMaxMeasuredInsp = Filter_Qi_Low;
   }

/*%C Disconnection Test to put the default parameter on */
/*%C the Open Loop Valve control */

   if ((Current_Mode == VOL)
       || (Current_Mode == VSIMV))
   {
      LowPressure = (SWORD16)DB_CurrentRead(ADJUST_LOW_PIP_U16);
   }
   else
   {
      LowPressure = (SWORD16)((DB_CurrentRead(PI_SET_POINT_U16) * 8) / 10);
   }

   if (((MeasureQInsp > 1300)
        || (Measure_Patient_Pressure <= LowPressure))
       && (High_Pressure_Detected == FALSE))
   {
      VEN_Disconnexion_Flag = TRUE;
   }
   else if (((VenTiCount > 240)
             && (MeasureQInsp <= 1300)
             && (Measure_Patient_Pressure > LowPressure)
            )
            || (High_Pressure_Detected == TRUE))
   {
      VEN_Disconnexion_Flag = FALSE;
   }


}
