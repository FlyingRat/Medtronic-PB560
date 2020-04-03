/******************************************************************************/
/*                                                                            */
/* Project N°  :  RC0306                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Fio2Calibration.c	 													*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C Description          : Sensors calibration		     								*/
/******************************************************************************/
/*%I Input Parameter :  NONE                     										*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE																	*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_AlarmStatus.h"
#include "System_Datas.h"
#include "DB_Measurement.h"
#include "Driver_Datas.h"
#include "SET_DefaultCalibration.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SYS_Fio2Calibration(UWORD16 RequestType, t_SYS_CalibrationParameters CP, UWORD16 CAN_Digit1)
{

	e_CalibrationCommand Request;
//   UWORD16 CalibAdjustCmd, CalibAdjustQO2Cmd;
   static UWORD16 Indice = 0;
	e_BOOL TestLimitsOk1;  
	
   static UBYTE DigitNb1 = 0;
	// La calibration doit durer au moins 100ms pour que les données soient correctes
	UWORD32 FilteredDigit1=0;
	// Tableau pour le filtrage des valeurs de debit inspi et expi pour la calibration
	static UWORD16 Digit1[80];

   // Initialisation
	Request = DB_ControlRead(RequestType);

	// Traitement pour la calibration de la FIO2
	Indice = 0;

	// Calcule une moyenne du CAN 1
  	Digit1[DigitNb1++] = CAN_Digit1;
  	DigitNb1 %= 80;
	FilteredDigit1 = average(Digit1, 80);                    
	// Ajout d'1 point de CAN afin de reduire l'erreur sur le point 0 (mbar, l/min, etc...)
	FilteredDigit1 += 1;

	// IHM demande de contrôler l'offset choisi par l'utilisateur
	if (Request == TEST_LIMITES_REQUEST)
		{
		// Envoie la valeur filtrée du CAN 1 à DataBase pour vérification 
		TestLimitsOk1 = DB_ConfigWrite(CP.FirstOffsetIndex + Indice, (UWORD16)(FilteredDigit1));

		// Si le test a échoué
		if (TestLimitsOk1 == FALSE)
			{
 			// Alarme Echec calibration FIO2 
			 DB_AlarmStatusWrite(CP.OffsetAlarmIndex, ALARM_DETECTED);
			 DB_ControlWrite(CALIBRATED_FIO2_SENSOR, FALSE);	
			 DB_ControlWrite(RequestType, TEST_LIMITES_FALSE);
			 /*%C  	Long beep request */
		   DB_ControlWrite(VALIDATION_BIP_U16, BIP_LONG);
			}
		// Sinon
		else
			{
         // Evènement de calibration
			DB_EventMngt(CP.EventCalibration);
 			//Annulation uniquement de l'alarme Echec calibration FIO2 
			DB_AlarmStatusWrite(CP.OffsetAlarmIndex, ALARM_FALSE);
			DB_ControlWrite(CALIBRATED_FIO2_SENSOR, TRUE);
			DB_ControlWrite(RequestType, TEST_LIMITES_OK);
			/*%C     Short beep request*/
		   DB_ControlWrite(VALIDATION_BIP_U16, BIP_SHORT);
			}

		// On arrête la calibration
		#if defined(SUPPORTAIR_M2)
			DB_ControlWrite(RequestType, NO_CALIB);
		#endif 
		}

}