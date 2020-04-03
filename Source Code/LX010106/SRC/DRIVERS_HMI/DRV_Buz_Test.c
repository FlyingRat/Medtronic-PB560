/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_Buz_Test.c                         */
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
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "io_declare.h"
#include "DB_Control.h"
#include "Driver_Datas.h"
#include "DRV_Buz_Test.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_Buz_Test(e_NUMBER_BUZ NumBuzzer, e_TYPE_TEST_BUZ Mode)
{
	// Arrêt des buzzers
	if (Mode == NO_BUZ)
	{
		if (NumBuzzer == BUZ_CARD)
		{ 
			// sortie Pwm3 désactivée
			PWMCON1 &= 0xFFF7;   
			/*%C  Arrêt du timer T7													                  */
			T7R = 0;
			T7 = 0;
	 	
			// Information pour l'anomalie Buzzer
			DB_ControlWrite(CONTROL_BUZZER_U16,FALSE);
		}
		else 
		{
			SEC_BUZ = 0;
		}
	}
	// Marche des buzzers
	else
	{
		if (NumBuzzer == BUZ_CARD)
		{
			/*%C Niveau sonore max */
			PW3 = 0;
			// sortie Pwm3 activée
			PWMCON1 |= 0x0008;
			/*%C  Démarrage du timer T7											                  */
			T7R = 1;
	
			// Information pour l'anomalie Buzzer
			DB_ControlWrite(CONTROL_BUZZER_U16,TRUE);
		}
		else 
		{
			SEC_BUZ = 1;
		}
	}
}
