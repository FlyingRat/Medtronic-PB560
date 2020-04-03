/******************************************************************************/
/*                                                                            */
/* Project N°  :  RC0306                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_O2Consigne.c												  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                       Valve management						     		  */
/*%C     															  		  */
/******************************************************************************/
/*%I Input Parameter :  Value                       						  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE												  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "Ventilation_Constants.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_Compute.h"
#include "DB_Current.h"
#include "CMP_O2Consigne.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


SWORD32 CMP_O2Consigne(void)
{
	 // Récupération de la valeur 100% O2	active
	UWORD16 o2_100p100 = DB_ControlRead (FIO2_100_ACTIVE);
	// Lecture du type de mode de ventilation
	UWORD16 CurrentMode = DB_ControlRead(CURRENT_MODE_U16);
	// Lecture de la mesure du rapport de cyclage.
	UWORD16 MeasureIT = DB_ComputeRead(MEASURE_IT_U16);
	// Lecture du vt
	UWORD16 AdjustVt = DB_CurrentRead(ADJUST_VOL_CONTROL_U16);
	//Info Présence Valve
	UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);
	
	// Récupération du débit inspiratoire
	SWORD16 Qinsp = (SWORD16)DB_ComputeRead(MEASURE_QINSP_S16); 
	
	//Recupération du VT	
	UWORD16 CmpVti = DB_ComputeRead(COMPUTED_VTI_U16);
	
	e_VEN_SIMVCycle VaciPhase =DB_ControlRead(SIMV_CYCLES_U16);
	
	UWORD16 AdjustFio2;
	SWORD32 ConsigneO2;
	SWORD32 CorrectionVt = 0; 
	SWORD32 CorrectionO2 = 0;
	
	static UWORD16 Mutex_FIO2_100_Active = FALSE;

  //Test si 100% O2 demandé
   if (o2_100p100 == TRUE)
   {
	  AdjustFio2 = 100;
	  //Réglage des seuils d'alarmes Low et High
	  if (Mutex_FIO2_100_Active == FALSE)
	  {
	  		//Flag d'exclusion
			Mutex_FIO2_100_Active = TRUE ; 
			DB_ConfigWrite(ADJUST_LOW_FIO2 , AdjustFio2 - cDELTA_LOW_FIO2);
			DB_ConfigWrite(ADJUST_HIGH_FIO2 , AdjustFio2 + cDELTA_HIGH_FIO2);
	  }
   }
   //Sinon récupération de la FIO2 réglée
   else
   {
      AdjustFio2 = DB_ConfigRead(ADJUST_FIO2);
 	  //Réglage des seuils d'alarmes Low et High
	  if (Mutex_FIO2_100_Active == TRUE)
	  {
	  		//Flag d'exclusion
			Mutex_FIO2_100_Active = FALSE ; 
			DB_ConfigWrite(ADJUST_LOW_FIO2 , AdjustFio2 - cDELTA_LOW_FIO2);
			DB_ConfigWrite(ADJUST_HIGH_FIO2 , AdjustFio2 + cDELTA_HIGH_FIO2);
	  }

   }

   // Non prise en compte d'un débit inspiré négatif pour la régul O2
   if (Qinsp < 0)
   {
      Qinsp = 0;
   }	 

   // Calcul de la Consigne O2
	//	(Signification du "AdjustFio2+2": Translation de 2% de l'ensemble de la régulation des modes à valves
	// pour compenser une faibesse générale de celle-ci).
  if (ValveDetected == TRUE)
  		ConsigneO2 = ((SWORD32)((((SWORD32)AdjustFio2+2) - 21)*100) / 79);
  else 	
  		ConsigneO2 = ((SWORD32)((((SWORD32)AdjustFio2) - 21)*100) / 79);

 ////////////////////////////////////////////////////////////////////
// CORRECTION POUR LES MODES A VALVE.	                             //
//	(VC(VAC),VPC(VPAC) valve, AI(AIFR) valve, AIFR, VACI)  			  //
//////////////////////////////////////////////////////////////////////

	if (ValveDetected == TRUE)
	{
	// CORECTION PAR RAPPORT AU VT.
		if (CmpVti < 400)
		{
	     	if (CmpVti < 100)
		   {
			CorrectionVt = VEN_RiseCompute((SWORD32)(CmpVti),
													50, 17000,
													100, 13000);
	    	}
		   else
			{
			
			CorrectionVt = VEN_RiseCompute((SWORD32)(CmpVti),
													100, 13000,
													400, 8000);
	    	}
		}
		else
		{
			CorrectionVt = VEN_RiseCompute((SWORD32)(CmpVti),
													400, 8000,
													1000, 1000);
		}

		CorrectionVt /= 1000;
      
												
	//CORECTION PAR RAPPORT AU %O2 REGLE.

		// Cas des Vti < 650mL.
		if (CmpVti < 650)
		{
      	if (AdjustFio2 < 80)
      	{
	      	CorrectionO2 = VEN_RiseCompute((SWORD32)(AdjustFio2),
												50, 0,
												80, 3000);
      	}
      	else
      	{
		      switch (AdjustFio2)
			   {
					  case 80 :
					  		CorrectionO2 = 3000; break;
					  case 85 :
					  		CorrectionO2 = 4000; break;
					  case 90 :
					  		CorrectionO2 = 5000; break;
					  case 95:
					  		CorrectionO2 = 17000; break;
					  case 100:
					  		CorrectionO2 = 25000; break;
			  		  default :
			  		  		CorrectionO2 = 3000; break;
		      }
			} 
		}

		// Cas des Vti > 650mL.
		else
		{
		   // Pour les modes Volume (VC,VAC,VACI sur cycle volume) 
		   if ((CurrentMode == VOL) ||
		    	((CurrentMode == VSIMV)&&((VaciPhase == CV_Cycle)||(VaciPhase == CAV_Cycle)))) 
				
			{  
			  switch (AdjustFio2)
				  {
				  case 85 :
				  		CorrectionO2 = 2000; break;
				  case 90 :
				  		CorrectionO2 = 6000; break;
				  case 95:
				  		CorrectionO2 = 15000; break;
				  case 100:
				  		CorrectionO2 = 25000; break;
				  default :
				  		CorrectionO2 = 0; break;
				  }
			}
			// Pour les modes Pression à valve (VPC(VPAC)à valve et AI(AIFR) à valve.
			else
			{ 
			 switch (AdjustFio2)
				  {
				  case 60 :
						CorrectionO2 = -3000; break;
				  case 65 :
						CorrectionO2 = -5000; break;
				  case 70 :
						CorrectionO2 = -5000; break;
				  case 75 :
						CorrectionO2 = -5000; break;
				  case 80 :
						CorrectionO2 = -5000; break;
				  case 85 :
				  		CorrectionO2 = -2000; break;
				  case 90 :
				  		CorrectionO2 = 1000; break;
				  case 95:
				  		CorrectionO2 = 10000; break;
				  case 100:
				  		CorrectionO2 = 25000; break;
				  default :
				  		CorrectionO2 = 0; break;
				  }	      
		   }
		}	 				  
	CorrectionO2 /= 1000;

	// Calcul de la consigne O2 corrigée: 
	// Intégration de la Correction fonction du VT et de la correction fonction du %O2 réglé.
	ConsigneO2 = ConsigneO2 * (100 + CorrectionVt + CorrectionO2)/100;
   }


/////////////////////////////////////////
// CORRECTION POUR LES MODES A FUITE.  //  
/////////////////////////////////////////
	
	// CORRECTION POUR LES MODES VPC(VPAC) A FUITE ET AI(AIFR) A FUITE.

   else if  (CurrentMode != CPAP)			
	{ 	
	   //Si I/T est supérieur à 45%
	   if (MeasureIT >= 45)
		{
		   if  (AdjustFio2 <= 60)
      	{
				CorrectionO2 = VEN_RiseCompute((SWORD32)(AdjustFio2),
										21, -23000,
										60, -20000);
			}
			else if  (AdjustFio2 <= 80)
      	{
				CorrectionO2 = VEN_RiseCompute((SWORD32)(AdjustFio2),
										60, -20000,
										80, -15000);
			}
			else
			{
			  switch (AdjustFio2)
				  {
				  case 85 :
				  		CorrectionO2 = 0; break;
				  case 90 :
				  		CorrectionO2 = 7000; break;
				  case 95:
				  		CorrectionO2 = 15000; break;
				  case 100:
				  		CorrectionO2 = 25000; break;
				  default :
				  		CorrectionO2 = 0; break;
				  }
			}
		}
		// Si I/T est compris entre 33 et 45%
		else if (MeasureIT >= 33)
		{
		  	if  (AdjustFio2 <= 60)
	      	{
				CorrectionO2 = VEN_RiseCompute((SWORD32)(AdjustFio2),
										21, -16000,
										60, -11000);
				}
			else if  (AdjustFio2 <= 80)
	      	{
				CorrectionO2 = VEN_RiseCompute((SWORD32)(AdjustFio2),
										60, -11000,
										80, -6000);
				}
			else
			{
			  switch (AdjustFio2)
				  {
				  case 85 :
				  		CorrectionO2 = 0; break;
				  case 90 :
				  		CorrectionO2 = 7000; break;
				  case 95:
				  		CorrectionO2 = 15000; break;
				  case 100:
				  		CorrectionO2 = 25000; break;
				  default :
				  		CorrectionO2 = 0; break;
				  }
			}
		}
		// Si I/T est inférieur à 33%
		else 
			{
		  	if  (AdjustFio2 <= 60)
	      	{
				CorrectionO2 = VEN_RiseCompute((SWORD32)(AdjustFio2),
										21, -16000,
										60, -8000);
				}
			else if  (AdjustFio2 <= 80)
	      	{
				CorrectionO2 = VEN_RiseCompute((SWORD32)(AdjustFio2),
										60, -8000,
										80, -2000);
				}
			else
				{
				  	switch (AdjustFio2)
					  {
					  case 85 :
					  		CorrectionO2 = 4000; break;
					  case 90 :
					  		CorrectionO2 = 12000; break;
					  case 95:
					  		CorrectionO2 = 20000; break;
					  case 100:
					  		CorrectionO2 = 30000; break;
					  default :
					  		CorrectionO2 = 0; break;
					  }
				}
		}

	CorrectionO2/= 1000;

	// Calcul de la consigne O2 corrigée
	ConsigneO2 = ConsigneO2 * (100 + CorrectionO2)/100;
   	
	}

	// CORRECTION POUR LE MODE PPC.
   else
	{
		if (AdjustFio2 >= 85) 		  
		{	  
			  switch (AdjustFio2)
				  {
				  case 85 :
				  		CorrectionO2 = 44000; break;
				  case 90 :
				  		CorrectionO2 = 46000; break;
				  case 95:
				  		CorrectionO2 = 49000; break;
				  case 100:
				  		CorrectionO2 = 52000; break;
				  default :
				  	   CorrectionO2 = 0; break;
				  }	      
	   }
		else
		{
		  	CorrectionO2 = VEN_RiseCompute((SWORD32)(AdjustFio2),
										21, 24000,
										80, 40000);
		}

      CorrectionO2/= 1000;

   	// Calcul de la consigne O2 corrigée
   	ConsigneO2 = ConsigneO2 * (100 + CorrectionO2)/100;
 	}

	ConsigneO2 = (SWORD32)(ConsigneO2 * (SWORD32)Qinsp) / 100;

	return(ConsigneO2);
}