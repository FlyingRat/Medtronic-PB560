/******************************************************************************/
/*                                                                            */
/* Project N°  :  RC0306                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : ACT_O2ValveCmd.c												  */
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
#ifndef _TASKING
	#include "LH_ST10F276.h"
	#include <intrins.h>
#else
	#ifdef _TESTRT
		#include "IO_TestRT.h"
	#else
		#include "regf276e.h"
	#endif
#endif  
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "DB_Compute.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "Ventilation_Constants.h"
#include "Ventilation_Datas.h"
#include "ACT_O2ValveCmd.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void ACT_O2ValveCmd(SWORD32 Kp,SWORD32 Ki,SWORD32 Consigne)
{
SWORD32 Error=0,Prop;
UWORD16 ValveCommand;
SWORD16 QO2 = (SWORD16)DB_ComputeRead(MEASURE_QO2_S16);   

UWORD16 AdjustO2 = DB_ConfigRead(ADJUST_FIO2);
UWORD16 Fio2_100Active = DB_ControlRead(FIO2_100_ACTIVE);
UWORD16 MaintenanceMode = DB_ControlRead(MAINTENANCE_MODE_U16);

UWORD16 O2AdjustMin = 0;

	// Read O2 Adjust min value 
	DB_IhmAccessParaDataBase(&O2AdjustMin, ADJUST_FIO2, CONFIG, MIN);
	
   // calcul de l'erreur 
   Error = Consigne - (SWORD32)QO2;

   // Calcul du terme proportionnel1 divisé par 1000 pour augmenter précision du réglage de Kp1
   Prop = (Kp * Error)/1000;
   // Calcul du terme integral divisé par 1000 pour augmenter précision du réglage de Ki
   VEN_IntegralValveO2 = VEN_IntegralValveO2 + (Ki * Error)/1000;
   // Limitation de l'intégrale maxi
   if (VEN_IntegralValveO2 > cVEN_INTEGRAL_VALVEO2_MAX) VEN_IntegralValveO2 = cVEN_INTEGRAL_VALVEO2_MAX;
      // Limitation de l'intégrale mini
   if (VEN_IntegralValveO2 < cVEN_INTEGRAL_VALVEO2_MIN) VEN_IntegralValveO2 = cVEN_INTEGRAL_VALVEO2_MIN;

	// Calcul du terme proportionnel + integral + dérivé 
	ValveCommand = (UWORD16)((Prop + VEN_IntegralValveO2) / 10);

   // Limitation de la commande valve
   if (ValveCommand > cVEN_INTEGRAL_VALVEO2_MAX/10)  ValveCommand = cVEN_INTEGRAL_VALVEO2_MAX/10;
   if (ValveCommand <= 0) ValveCommand = 0;
            
   if ((AdjustO2 > O2AdjustMin) || (Fio2_100Active == TRUE) || (MaintenanceMode == TRUE))
  	  // Chargement de la valeur de la commande de valve (O2 ou Ballonnet)
     VANNE_O2_CMD = cVALVEO2_CMD_OFF - ValveCommand;
   else
	  // Fermeture complete de la vanne
	  VANNE_O2_CMD = cVALVEO2_CMD_OFF;

	// Sauvegarde de la valeur pour le réglage manuel de la calibration du QO2
	DB_ControlWrite(MEMO_CMD_VANNE_FIO2_TO_CALIB, ValveCommand);
	
}