/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Ventilation_Compute_data.h                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Data declaration for compute functions                                 */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef VENTILATION_COMPUTE_DATA_H
#define VENTILATION_COMPUTE_DATA_H

	#define cDELTA_PI_PE_MIN 	50
	#define cPI_PE_LEAK_MIN 	100	
	#define cDELTA_PI_PE_MAX 	200
	#define cPI_PE_LEAK_MAX 	130	

	#ifdef DECLARATION_VENTILATION_COMPUTE_DATA_H
	/***************************************************************************/
	/*                           VARIABLE DECLARATION                 	      */
	/***************************************************************************/	
	/* Max pressure for adaptation                                       	      */
	SWORD16 CMP_PMaxAutoAdapt = 0;
	
	/* Max flow for adaptation                                          	         */
	SWORD16 CMP_FlowMaxMeasuredInsp = 0;
	
	/* Previous controller phase                                       	         */
	e_VEN_Controller_Phase CMP_PreviousControllerPhase = VEN_EXH_PLAT;
	
	/* Iteration counter for FullComputedPep                                      */
	UWORD16 CMP_FullPepCounter = 0;
	
	/* Exhalated pressure measure on one cycle                                    */
	SWORD32 CMP_FullPepMeasured = 0;
	
	/* Valve pressure previous cycle                                              */
	SWORD16 CMP_PvalveMeasured = 0;
	
	/* Flow set point default */
	UWORD32 CMP_DefaultQinsp = 500;
	
	/*%C Ventilation Report Compute variables */
	UWORD16 CMP_VentilReport_Array[DB_TREND_IHM_VENTIL_HOUR];

		
	/* Qee, leak and target Vt Correction	*/
	SWORD32 CMP_CumulVtiCorrected = 0;

	/* Vol control correction value for sinus ramp */
	UWORD16 CMP_CorrectorVtSin = 100;
	UWORD16 CMP_SetPoint_Mutex = FALSE;

	 UWORD16 CMP_UpStep_Mutex = FALSE;
	 UWORD16 CMP_DownStep_Mutex = FALSE;
	 UWORD16 CMP_TargetVT_Pi = 0;
	#else
	/******************************************************************************/
	/*             EXTERNAL VARIABLE DECLARATION                    	            */
	/******************************************************************************/
		
	/* Max pressure for adaptation declaration                             	      */
	extern SWORD16 CMP_PMaxAutoAdapt;
	
	/* Max pressure for adaptation declaration                             	      */
	extern SWORD16 CMP_FlowMaxMeasuredInsp;
	
	/* Previous controller phase                                       	         */
	extern e_VEN_Controller_Phase CMP_PreviousControllerPhase;
	
	/* Iteration counter for FullComputedPep                                      */
	extern UWORD16 CMP_FullPepCounter;
	
	/* Exhalated pressure measure on one cycle                                    */
	extern SWORD32 CMP_FullPepMeasured;
	
	/* Valve pressure previous cycle                                              */
	extern SWORD16 CMP_PvalveMeasured;
	
	/* Flow set point default */
	extern UWORD32 CMP_DefaultQinsp;
	
	/*%C Ventilation Report Variables */
	extern UWORD16 CMP_VentilReport_Array[];


	/* Qee, leak and target Vt Correction	*/
	extern SWORD32 CMP_CumulVtiCorrected;

	/* Vol control correction value for sinus ramp */
	extern UWORD16 CMP_CorrectorVtSin;
	extern UWORD16 CMP_SetPoint_Mutex;

	extern UWORD16 CMP_UpStep_Mutex;
	extern UWORD16 CMP_DownStep_Mutex;
	extern UWORD16 CMP_TargetVT_Pi;
	#endif
#endif