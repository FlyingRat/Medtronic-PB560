/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_Fio2_Interpol.c        	                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Fio2 values conversion 					                           */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "define.h"
#include "DB_Config.h"
#include "DB_Compute.h"
#include "DB_Measurement.h"
#include "Driver_Datas.h"
#include "System_Datas.h"
#include "INT_Fio2_Interpol.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void INT_Fio2_Interpol(void)
{
	UWORD16 AdjustFio2 = DB_ConfigRead(ADJUST_FIO2);
	UWORD16 ComputedPip = DB_ComputeRead(COMPUTED_PIP_U16);
	SWORD32 OffsetFIO2 = 0; 
	UWORD16 AveragePressure = DB_ComputeRead(AVERAGE_PRESSURE_U16);
	UWORD16 FIO2Value = 0;
	UWORD16 FIO2Corrected = 0;
	UWORD32 Full_Scale_Value = 0;
	UWORD32 Slope_Correc_Pres = 0;
	UWORD32 CellPressure = 0; 
   OffsetFIO2 = DB_ConfigRead(OFFSET_FIO2);

	// SensorSensitivity = 0.611175  mv/%	  à ajuster suivant les mesures effectuées par marie. refaire les calculs ci_dessous
	// AmplifierGain  = 74      (R14+R5)/R5
	// CanStepMv = ( Vrèf / ConverterResolution ) = 5.00/1024 = 4.887585   mv (Tension par pas de convertisseur)
	// FIO2Value(%) = CalibPt(Point de calibration FIO2) + ((FIO2Digit - OffsetFIO2)*CanStepPerCent /(SensorSensitivity * AmplifierGain))
  	// CanStepPerCent(% par pas de convertisseur) = CanStepMv/(SensorSensitivity * AmplifierGain) 
	//															 = 4.887585/(0.611175*74) = 0.107962453 %/pas de convertisseur
	// FIO2Value (%) = CalibPt + ((FIO2Digit  - OffsetFIO2)* CanStepPerCent)
	// FIO2Value (% 10^1) = CalibPt (%10^1) + ((FIO2Digit  - OffsetFIO2)* CanStepPerCent* 10^1)
	// Si  CanStepPerCent exprimé en %/pas de convertisseur*10^7 = 1079624
	// FIO2Value (% 10^1) = CalibPt (%10^1) + ((FIO2Digit  - OffsetFIO2)* CanStepPerCent / 10^6


   FIO2Value = (UWORD16)(((((SWORD32)AD_Digit.Fio2 - (SWORD32)OffsetFIO2) * (SWORD32)CAN_STEP_PER_CENT) / (SWORD32)(1000000)) + (SWORD32)FIO2_CALIB_POINT);

	if (FIO2Value > 2500)
	{
		FIO2Value = 2500;
	}

	//Coorection de la valeur de monitorage FIO2 en fonction de la pression moyenne des cycles ventilatoire.
	//Il est tenu compte de la Pmax à hauteur de 60% dans le calcul de la Pression Moyenne
	// à cause le l'effet mémoire de la cellule FiO2.
	CellPressure = 40 * (UWORD32)AveragePressure + 60 * (UWORD32)ComputedPip;
	CellPressure = CellPressure / 100;
											
   // Interpolation de la valeur de correction du Monitorage Fi02 en pleine échelle (100% O2) en fontction de la pression moyenne.
	Full_Scale_Value = VEN_RiseCompute(CellPressure,
												  0,
												  0,
												  800,
												  1300);
											
	// Interpolation de la valeur de correction du monitorage FiO2 en fonction de FiO2 value brute. 
	Slope_Correc_Pres = VEN_RiseCompute(FIO2Value,
													120,
													0,
													1000,
													Full_Scale_Value);

   // Prise en compte de la correction en pression sur la mesure de FiO2.
   FIO2Corrected = FIO2Value * 10 - (UWORD16)Slope_Correc_Pres;
	FIO2Corrected = FIO2Corrected / 10;
   DB_ComputeWrite(MEASURE_FIO2, (UWORD16)FIO2Corrected);
}
