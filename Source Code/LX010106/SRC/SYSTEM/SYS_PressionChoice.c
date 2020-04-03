/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_PressionChoice.c                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C  This function uses the prox detection algorithm to determine whether    */
/*    to use internal pressure sensor or proximal pressure sensor to display  */
/*    pressure readings on the screen and other subsystems such as alarms and
      breath delivery.  The detection algorithm checks for a flat .4 or .3
      cmh20 of prox data and including a high delta value between the internal
      pressure sensor and the prox pressure sensor data.  Also, if
      leak is present and the exhalation valve is detected then use the following
      detection:
           If the PEEP setting is greater than 4 cmH20, then use the
           same algorithm for detecting a prox disconnection when the
           ventilator is in a leak configuration mode.  Basically, when
           the proximal pressure is less than 2 cmH20, declare a prox
           disconnect alarm.
 
           If the PEEP setting is less than 4 cmH20 and measured PEEP is
           greater than measured PIP or measured PIP is less than the circuit
           disconnect low pressure limit, then declare a prox disconnect alarm.

/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                           INCLUDE FILES		                              */
/******************************************************************************/


#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_Current.h"
#include "Timer_Data.h"
#include "SYS_PressionChoice.h"
#include "math.h"
#include "Ventilation_Datas.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SYS_PressionChoice(void)
{
   SWORD16 MeasurePatientPressureProxi = (SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_PROXI_S16);
   SWORD16 FilterPatientPressureProxi = (SWORD16)DB_ComputeRead(FILTER_PATIENT_PRESSURE_PROXI_S16);
   SWORD16 MeasureInternalPressure = (SWORD16)DB_ComputeRead(MEASURE_INTERNAL_PRESSURE_S16);
   SWORD16 FilterInternalPressure = (SWORD16)DB_ComputeRead(FILTER_INTERNAL_PRESSURE_S16);
   UWORD16 HighPressureExhalationDetected = (UWORD16)DB_ControlRead(HIGH_PRESSURE_EXHALATION_DETECTED_U16);

   e_MODE_TYPES Adjust_Mode  = DB_ConfigRead(ADJUST_MODE_U16);
   UWORD16 ComputedPiSetPoint = DB_ComputeRead(COMPUTED_PI_SET_POINT_U16);
   UWORD16 AdjustPeep =  DB_CurrentRead(ADJUST_PEEP_U16);
	/* Valve detection state recovery from base */
   UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);
   UWORD16 VentilState = DB_ControlRead(VENTIL_STATE_U16);
   SWORD32 MeasureQinsp = (SWORD32)(SWORD16)DB_ComputeRead(MEASURE_QINSP_S16);
   UWORD16 AdjustPediatricCircuit = DB_ConfigRead(ADJUST_PEDIATRIC_CIRCUIT_U16);
   UWORD16 ProxiDetected = DB_ControlRead(PROXI_DETECTED_U16);
   e_VEN_ControllerType ControlerType = DB_ControlRead(CONTROLER_TYPE_U16);
   SWORD32 CalculatedQee = (SWORD32)(SWORD16)DB_ComputeRead(COMPUTE_QEE_S16);
   SWORD32 ComputedPeep = (SWORD32)DB_ComputeRead(COMPUTED_PEEP_U16);
   UWORD16 Adjust_Peep = DB_CurrentRead(ADJUST_PEEP_U16);
   UWORD16 Computed_Pip = DB_ComputeRead(COMPUTED_PIP_U16);

	static SWORD16 maxi_prox_CPAP= 0x8000;
  	static SWORD16 mini_prox_CPAP= 0x7FFF;
	static SWORD16 maxi_int_CPAP= 0x8000;
  	static SWORD16 mini_int_CPAP= 0x7FFF;
	static SWORD16 maxi_prox= 0x8000;
  	static SWORD16 mini_prox= 0x7FFF;
	static SWORD16 maxi_int= 0x8000;
  	static SWORD16 mini_int= 0x7FFF;
	static SWORD16 HighPprox =0x8000;
  	static UWORD16 FlatProxi = FALSE;
	static UWORD16 FlatInt = FALSE;
	static UWORD16 SpecialCase = FALSE;

  	static e_VentilState MemoState 	= VEN_VENTIL_DISABLE;

	
	SWORD16 Delta_prox = 0;
	SWORD16 Delta_int  = 0;
	SWORD32 PresLevel = 0;
	SWORD16 EstimatedProximalePressure = 0;
	SWORD32 DeltaPressure = 0;
	UWORD16 PatientCircuitR = 0; 

    double PressureFactor =0;
    SWORD32 EQLeak = 0;
    SWORD32  ELeakCoeff = 0;
	const SWORD32 cDETECTION_LEAK_CRITERIA = 15; // estimated lower threshold for leak indicator; (i.e leak is small)
    const SWORD32 cLEAK_OFFSET = 60;             // projected ceiling of Qee under minimal leak
    const double  cMIN_PRESSURE_FACTOR = 7.07;   // pressure factor for peep of 0.5 cmH20
	const SWORD32 cMIN_LEAK_CONFIG_PEEP_SET = 4; // The lowest allowable peep setting under a leak configuration mode.
/******************************************************************************/
/*                  GESTION DES FLAGS FLAT PROXI ET FLAT INT 		          */
/*Detection des signaux plats sur capteurs de pression proximal et interne.   */
/******************************************************************************/		 
    		 
/******************************************************************************/
/*                  MANAGEMENT FLAGS FLAT AND FLAT PROXI INT		          */
/*Detection of signals on flat proximal sensors and internal pressure.        */
/******************************************************************************/
      		 
 // Recherche de la valeur de pression max sur interne et proximal pendant le cycle respi en cours.   
 // Search the value of max on internal and proximal during breathing during cycle.	  	 
	  	 
 // Pour tous les modes autres que CPAP.   
 // For all modes other than CPAP.
    if ( Adjust_Mode != CPAP )
 	{	  
		// Mise a jour des valeurs maxi de la valeur pression interne et proximal pendant l'inspi.  
        // pression proximale.

        // Update of the maximum values of internal and proximal pressure value during inspiration
        // proximal pressure.
        if ( FilterPatientPressureProxi > maxi_prox ) 
        {
        	maxi_prox = FilterPatientPressureProxi;
			mini_prox =  maxi_prox;

			// Cas special de bloquage en expi du capteur pression interne à un niveau inférieur de la PEEP, menant
		   	// abusivement à une FLAT PROX=TRUE et FLAT INT=FALSE.(contraire à la réalité).
		   	// Enregitrement de la valeur de la pression proximal lors de la pression haute.   

            // In case special blocking expi internal pressure sensor at a lower level of PEEP, leading 
            // Abused a FLAT FLAT PROX = TRUE and FALSE = INT. (Contrary to fact). 
            // Value, recording of the proximal pressure at the high pressure.

		   	if ( HighPressureExhalationDetected == TRUE )
		   	{
				maxi_int = FilterInternalPressure;
				mini_int = maxi_int;
		   	} 
        }
        // pression interne. 
        // Internal pressure.
        if ( FilterInternalPressure > maxi_int ) 
        {
        	maxi_int = FilterInternalPressure;
			mini_int = maxi_int;
        }
	
		// Mise a jour des valeurs mini de la valeur pression interne et proximal pendant l'expi.   
		// pression proximale. 

        // Updating the minimum values ??of the internal and proximal pressure during expiration value. 
        // Proximal pressure.
		if ( FilterPatientPressureProxi < mini_prox ) 
		{
			mini_prox = FilterPatientPressureProxi;
		}
		// pression interne. 
        // Internal pressure.
		if ( FilterInternalPressure < mini_int ) 
		{
			mini_int = FilterInternalPressure;
		}
	}
	// Pour le mode CPAP. 
    // For the CPAP mode.
	if ( Adjust_Mode == CPAP )
	{
		// pression proximale.
        // Proximal pressure.
	  	if ( maxi_prox_CPAP < FilterPatientPressureProxi ) 
		{
			maxi_prox_CPAP = FilterPatientPressureProxi;
		}
	    if ( mini_prox_CPAP > FilterPatientPressureProxi ) 
		{
			mini_prox_CPAP = FilterPatientPressureProxi;
		}
		// pression interne.
        // Internal pressure.
		if ( maxi_int_CPAP < FilterInternalPressure ) 
		{
			maxi_int_CPAP = FilterInternalPressure;
		}
	    if ( mini_int_CPAP > FilterInternalPressure ) 
		{
			mini_int_CPAP = FilterInternalPressure;
		}
	}
	// Calcul du delta de pression à la transition expi-inspi et réinintilalisation des min et max.
    // Calculate the delta pressure transition expire inspiration and réinintilalisation of min and max.
	if (( VentilState != VEN_EXHALATION )&&( MemoState == VEN_EXHALATION ))
	 {	
		 // Calcul des deltas pression prox	et int.
         // Calculation of pressure and prox int deltas.
		 if ( Adjust_Mode != CPAP )
		 {
		 	Delta_prox = maxi_prox - mini_prox;
		 	Delta_int = maxi_int - mini_int;
		 }
		 else
		 {
		 	Delta_prox = maxi_prox_CPAP - mini_prox_CPAP;
		 	Delta_int = maxi_int_CPAP - mini_int_CPAP;
		 }

		 // Mise à jour à true du flag flat proxi si Delata < 0.3 CmH2O pour CPAP.
		 // ou si Delata < 0.4 CmH2O pour les autres modes.

         // Update the flag to true if flat proximal Delata <0.3 cmH2O CPAP. 
         // Or Delata <0.4 cmH2O for other modes.
		 if (( Delta_prox < 4 ) && ( Adjust_Mode != CPAP )
		 	||( Delta_prox < 3 ) && ( Adjust_Mode == CPAP ))
		 {
		 	FlatProxi = TRUE;
		 }		
		 else 
		 {
		 	FlatProxi = FALSE;
		    // Mise à false temporaire des flag de detection de la high pressure
			// le temps de la prise en compte du retour du capteur de pression proximal.

            // Update the temporary false flag detection of high pressure 
            // Time of the inclusion of the back proximal pressure sensor.
			DB_ControlWrite(HIGH_PRESSURE_DETECTED_U16,FALSE);
			DB_ControlWrite(HIGH_PRESSURE_EXHALATION_DETECTED_U16,FALSE);
		 }

		 // Mise à jour à true du flag flat internal si Delata < 0.3 CmH2O pour CPAP.
		 // ou si Delata < 0.4 CmH2O pour les autres modes.

         // Update the flag to true if internal flat Delata <0.3 cmH2O CPAP. 
         // Or Delata <0.4 cmH2O for other modes.
		 if (( Delta_int < 4 ) && ( Adjust_Mode != CPAP )
		 	||( Delta_int < 2 ) && ( Adjust_Mode == CPAP )) 
		 {
		 	FlatInt = TRUE;
		 }			
		 else 
		 {
		 	FlatInt = FALSE;
			// Mise à false temporaire des flag de detection de la high pressure
			// le temps de la prise en compte du retour du capteur de pression interne.

            // Update the temporary false flag detection of high pressure 
            // Time of the inclusion of the back internal pressure sensor.
			DB_ControlWrite(HIGH_PRESSURE_DETECTED_U16,FALSE);
			DB_ControlWrite(HIGH_PRESSURE_EXHALATION_DETECTED_U16,FALSE);
		 }

		 // Ecriture en base.
         // Write to the database.
		 DB_ControlWrite(FLAT_PROXI_U16,FlatProxi);
		 DB_ControlWrite(FLAT_INT_U16,FlatInt);
		
		 // Réinitialisation des maxi et des mini.
         // Reset maxi and mini.
		 maxi_prox = 0x8000; 
		 mini_prox = 0x7FFF;
		 maxi_int = 0x8000; 
		 mini_int = 0x7FFF;
		 maxi_prox_CPAP = 0x8000; 
		 mini_prox_CPAP = 0x7FFF;
		 maxi_int_CPAP = 0x8000; 
		 mini_int_CPAP = 0x7FFF;	 	
	}

/******************************************************************************/
/* CHOIX DU NIVEAU DE DELTA DE PRESSION INTERNE/PROXI DISCRIMINANT POUR		   */
/* TEST SWITCH CAPTEUR PRESSION												   */
/*******************************************************************************/
// Choix du niveau de Delat Pression entre proximal et interne en fonction du débit pour reconnaitre une perte proximale.
// Choix du niveau de Resistance du circuit patient.


/******************************************************************************/ 
/* CHOICE OF LEVEL OF INTERNAL PRESSURE DELTA / PROXI DISCRIMINANT FOR         */ 
/* TEST PRESSURE SENSOR SWITCH                                                 */ 
/*******************************************************************************/ 
// Selecting the level Delat between proximal and internal pressure versus flow to recognize a proximal loss. 
// Selection of Resistance level of patient circuit.

    // Pour un circuit pédiatrique. 
    // For a pediatric circuit.
 	if ( AdjustPediatricCircuit == TRUE )
	{
		// Delta pression.
        // Delta pressure.
		PresLevel = (( MeasureQinsp * MeasureQinsp * 7 ) / 100000 ) + (( 853 * MeasureQinsp ) / 10000 ) + 10;
		// Resistance
		PatientCircuitR = 10;
	}
	// Pour un circuit adulte.
    // For an adult circuit.
	else
	{
		// Delta pression.
        // Delta pressure
		PresLevel = (( MeasureQinsp * MeasureQinsp * 4 ) / 100000 ) + (( 373 * MeasureQinsp ) / 10000 ) + 10;
		// Resistance
		PatientCircuitR = 0;
	}

	//	Limitation: Delta pression min.
	if (PresLevel < 40)	
	{
		PresLevel = 40;
	}
	//	Limitation: Delta pression max.
	else if (( ControlerType == CONTROL_PRESSURE )
	   		&&( PresLevel > (SWORD32)( ComputedPiSetPoint - AdjustPeep - 10 ))) 
	{
    	PresLevel = (SWORD32)( ComputedPiSetPoint - AdjustPeep - 10 );
	}

/******************************************************************************/
/*                  TEST SWITCH CAPTEUR PRESSION			 		          */
/*Interne vers Proximal. 													  */
/*Proximal vers Interne.   													  */
/******************************************************************************/
/************************************************* *****************************/ 
/* TEST PRESSURE SENSOR SWITCH           * / 
/* Internal to Proximal.                 * / 
/* Proximal to Internal.                 * / 
/************************************************* *****************************/
    // Calculate an estimated leak indicator
    EQLeak = CalculatedQee - cLEAK_OFFSET;

    // Ensure leak level indicator 
    if (EQLeak < 0)
    {
        EQLeak = 0;
    }

    // Calculate a pressure factor -- The 10 is used for scaling purposes only.
    PressureFactor = sqrt((double) (ComputedPeep* 10));

    // Keep the smallest minimum pressure factor of cMIN_PRESSURE_FACTOR
    if ( PressureFactor < cMIN_PRESSURE_FACTOR)
    {
        PressureFactor =  cMIN_PRESSURE_FACTOR;
    }

    // The 10 is used for scaling purposes only.
    // Calculate a leak coefficent 
    ELeakCoeff = ((double) EQLeak / PressureFactor) * 10.0;


    // When a leak and valve is detected and PEEP is greater than cMIN_LEAK_CONFIG_PEEP_SET, 
    // use the same algorithm for detecting a prox disconnection in a leak 
    // configuration mode.
    // 
    // However, if a leak and valve is connected and PEEP is less than the 
    // cMIN_LEAK_CONFIG_PEEP_SET, use the PIP and the circuit disconnect low pressure limit 
    // to determine a prox disconnection.  
    //
    // The algorithm below determines that the prox is invalid.
    if ((ELeakCoeff > cDETECTION_LEAK_CRITERIA) &&
        (ValveDetected == TRUE))
    {   
		if (  ((Adjust_Peep >= cMIN_LEAK_CONFIG_PEEP_SET) && 
          ( MeasurePatientPressureProxi < cPRESSURE_PROX_LEAK_CHOICE_LEVEL ))
		    ||((Adjust_Peep < cMIN_LEAK_CONFIG_PEEP_SET ) && 
			   ((ComputedPeep >= Computed_Pip) ||
			    (Computed_Pip <= VEN_CircuitDisconnectLowPressLimit)))
			
		   )
        {       
            TIM_StartDecounter(SYS_PRESSURE_CHOICE,TIME_PRESSURE_CHOICE);
        }
    }
	// Conditions nominales de test pour un switch interne vers proxi.

    // Nominal test conditions for an internal switch to proximal.
	else if ( ( ( (MeasurePatientPressureProxi < cPRESSURE_CHOICE_LEVEL1 )
	      || ( (MeasurePatientPressureProxi > MeasureInternalPressure + PresLevel )
	        || ( MeasurePatientPressureProxi < MeasureInternalPressure - PresLevel ) ) )
	   && ( ValveDetected == TRUE ) )
      || ( ( ValveDetected == FALSE )
	    && ( MeasurePatientPressureProxi < cPRESSURE_PROX_LEAK_CHOICE_LEVEL ) ) )

	{
		TIM_StartDecounter(SYS_PRESSURE_CHOICE,TIME_PRESSURE_CHOICE);
	}

    // When a leak and valve is detected and PEEP is greater than cMIN_LEAK_CONFIG_PEEP_SET, 
    // use the same algorithm for detecting a prox disconnection in a leak 
    // configuration mode.
    // 
    // However, if a leak and valve is connected and PEEP is less than the 
    // cMIN_LEAK_CONFIG_PEEP_SET, use the PIP and the circuit disconnect low pressure limit 
    // to determine a prox disconnection.  
    //
    // The algorithm below determines that the prox is valid.
    if (  (ELeakCoeff > cDETECTION_LEAK_CRITERIA) &&
       (ValveDetected == TRUE) )
    {
		if (  ((Adjust_Peep >= cMIN_LEAK_CONFIG_PEEP_SET) && 
          ( MeasurePatientPressureProxi >= cPRESSURE_PROX_LEAK_CHOICE_LEVEL ))
		    ||((Adjust_Peep < cMIN_LEAK_CONFIG_PEEP_SET ) && 
			   (ComputedPeep < Computed_Pip) && 
			   (Computed_Pip > VEN_CircuitDisconnectLowPressLimit))			
		   )
        {       
            TIM_StartDecounter(SYS_PRESSURE_CHOICE_INT,TIME_PRESSURE_CHOICE_INT);
        }
    }
	// Conditions nominales de test pour un switch proxi vers interne.
    // Nominal test conditions for a switch to proximal internal.
	else if ( ( ( ( MeasurePatientPressureProxi < MeasureInternalPressure + PresLevel ) 
		    && ( MeasurePatientPressureProxi > MeasureInternalPressure - PresLevel ) ) 
		  && ( ValveDetected == TRUE ) )
	  || ( ( ValveDetected == FALSE )
		&& ( MeasurePatientPressureProxi >= cPRESSURE_PROX_LEAK_CHOICE_LEVEL ) ) )
	{
		TIM_StartDecounter(SYS_PRESSURE_CHOICE_INT,TIME_PRESSURE_CHOICE_INT);
	}

	// Si les conditions nominales de test interne vers proxi sont respectés pendant 400 ms, on switche à l'inspi suivante.
	// Si on detecte un défaut de capteur interne (non lié à une déconnection), on switche immédiatement.  

    // If the nominal conditions proximal to internal test are met for 400 ms, we switche to the next inspiration. 
    // If a default internal sensor (not related to a disconnection) is detected, it immediately switche.
	if	(((( TIM_ReadDecounterValue(SYS_PRESSURE_CHOICE) == 0 )&&( FlatProxi != TRUE ))
	      ||(( FlatInt == TRUE )&&( FlatProxi != TRUE )))
		&&(( VentilState == VEN_INSPIRATION_CONTROLED )||( VentilState == VEN_INSPIRATION_TRIGGERED )))
	
	{
		DB_ControlWrite(PROXI_DETECTED_U16,TRUE);			
	} 
			
	// Si les conditions nominales de test proxi vers interne sont respectés pendant 50 ms, on switche immédiatement.
	// Si on detecte un défaut de capteur proximal, on switche immédiatement.

    // If the nominal conditions proximal to internal test are met for 50 ms is switche immediately. 
    // If a fault is detected proximal sensor, it switche immediately.
	else if	(((( TIM_ReadDecounterValue(SYS_PRESSURE_CHOICE_INT) == 0 )&&( FlatInt != TRUE )))
			||(( FlatProxi == TRUE )&&( FlatInt != TRUE ))
			||( VentilState == VEN_VENTIL_DISABLE )) 	
	{
		DB_ControlWrite(PROXI_DETECTED_U16,FALSE);			
	}

	// Lecture dans la base		
    // Read in the database
	ProxiDetected = DB_ControlRead(PROXI_DETECTED_U16);


/******************************************************************************/
/*                  SWITCH EN FONCTION DE LA DETECTION			 		      */
/******************************************************************************/
	if (ProxiDetected == FALSE) 
	{
		// Stockage de la pression interne comme pression patient dans la base.	
        // Store the internal pressure as pressure in the patient base.
	  	DB_ComputeWrite(MEASURE_PATIENT_PRESSURE_S16,MeasureInternalPressure);
	  	DB_ComputeWrite(FILTER_PATIENT_PRESSURE_S16,FilterInternalPressure);
	}
	else
	{
            //  Unstable PEEP with Humidifier          
            //  Based on the testing results submitted, 
            //  the ventilator intermittingly cannot drive to target PEEP
            //  due to a humidifier attached to the circuit.  
            //  So by providing the ventilator with internal pressure reading instead of
            //  prox pressures reading, the ventilator was able to drive to the PEEP consistently 
            //  without any fluctuating PEEP values and still deliver within PEEP accuracy specification.
            //  This fix is only applicable in non-leak configuration mode and 
            //  the BD must be in exhalation phase (rise or plateau). 
             if (  ((VEN_Controller_Phase == VEN_EXH_PLAT) || (VEN_Controller_Phase == VEN_EXH_FALL))
                && (ValveDetected == TRUE))
            {
                // Store internal pressures
                DB_ComputeWrite(MEASURE_PATIENT_PRESSURE_S16,MeasureInternalPressure);
                DB_ComputeWrite(FILTER_PATIENT_PRESSURE_S16,FilterInternalPressure);
            }
            else
            {
				// Stockage de la pression proximale comme pression patient dans la base.
				// Store the proximal pressure as pressure in the patient base.
				DB_ComputeWrite(MEASURE_PATIENT_PRESSURE_S16,MeasurePatientPressureProxi);
				DB_ComputeWrite(FILTER_PATIENT_PRESSURE_S16,FilterPatientPressureProxi);
            }
	}


	// Extrampolation de la pression proximale à partir de la pression interne et de la resistance du circuit
	// afin de minimiser l'erreur sur l'estimation du VTI.

    // Extrampolation the proximal pressure from the internal pressure and the resistance of the circuit 
    // To minimize the error in the estimation of VTI. 


	// Calcul du delta de pression du au circuit patient.
    // Calculate the delta pressure of the patient circuit.
	DeltaPressure = MeasureQinsp * MeasureQinsp ;
	DeltaPressure = DeltaPressure * (SWORD32)PatientCircuitR;
	DeltaPressure = DeltaPressure / 100000;  
	// Estimation de la pression proximale. 
    // Estimate the proximal pressure.
	EstimatedProximalePressure = MeasureInternalPressure - (SWORD16)DeltaPressure;

	// Stockage de la pression interne comme pression patient dans la base.	
    // Store the internal pressure as pressure in the patient base.
	DB_ComputeWrite(ESTIMATED_PROXIMAL_PRESSURE_S16, (UWORD16)EstimatedProximalePressure);
	
	// Mémorisation du cycle
    // Storing the cycle
	MemoState = VentilState;
}
