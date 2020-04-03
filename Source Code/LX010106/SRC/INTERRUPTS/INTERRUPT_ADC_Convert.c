/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_ADC_ChannelConvert.c                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif
#include "io_declare.h"	
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Driver_Datas.h"
#include "Driver_ADConverter_data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

#ifndef _TASKING
void INTERRUPT_ADC_Convert(void) interrupt 0x28
#else
interrupt (0x28)
 void INTERRUPT_ADC_Convert(void)
#endif
{  
	PECC0 = 0x0210 ;			  		    			// Réinitialisation du compteur de PECC
	DSTP0 = _sof_(conversion_numerique);    	// Réinitialisation du pointeur DESTINATION du PECC0

	// affectation du résultat de conversion
 	AD_Digit.PatientPressure 	= NUM_PRESSION_INTERNE;
  	AD_Digit.FlowInsp     		= NUM_DEBIT_INSPIRATOIRE;
  	AD_Digit.TestBuzzer    		= NUM_TEST_BUZZER;
  	AD_Digit.Pfi			 		= NUM_PFI ;
  	AD_Digit.Fio2					= NUM_FIO2;
 	AD_Digit.ValvePressure		= NUM_PRESSION_VALVE;
  	AD_Digit.FlowExh     		= NUM_DEBIT_EXPIRATOIRE;
	AD_Digit.ProxPressure		= NUM_PRESSION_PROX;
 	AD_Digit.MesAbsPressure		= NUM_PRESSION_ABSOLUE;	// A MODIFIER
 	AD_Digit.FlowO2				= NUM_MES_DEBIT_O2;
  	AD_Digit.MesIValve     		= NUM_MES_I_VALVE; // A MODIFIER
 	AD_Digit.MesVBat				= NUM_MES_V_BAT;
  	AD_Digit.Volt24       		= NUM_MES_24V;	
  	AD_Digit.O2Pressure    		= NUM_PRES_O2;
  	AD_Digit.InfoSupply			= NUM_MES_FLOW_TEMP; // A MODIFIER
 	AD_Digit.MesBlowerTemp		= NUM_MES_BLOWER_TEMP;
	DRV_Acquisition_Disponible  	= TRUE; 				// Fin d'acquisition
}
