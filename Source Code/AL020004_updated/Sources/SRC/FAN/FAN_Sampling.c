/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : FAN_Sampling.c                            		  					*/
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Cooling fan acquisition								  			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "p18f6622.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Define.h"
#include "TIMer_Data.h"
#include "DB_Measurement.h"
#include "FAN_Data.h"
#include "FAN_Sampling.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void FAN_Sampling(void)
{
	/* Autorisation de l'interruption de la capture vitesse ventilateur			*/
	if(PIE1bits.CCP1IE == 0)
	{
		/*%C TMR1 frequence is 4 MHz, so period is 1us 									*/
		/*%C Capture period by turn 															*/
		/*%C Calcul the turn by minute 														*/
		/* = 60 000 000 000 / (Speed_Fan) 													*/
		
		Speed_Fan_Tr_Min = 60000000 / (UWORD32)Speed_Fan;
		
		/*%C Incorrect speed																		*/		
		if	(Speed_Fan_Tr_Min > 10000)
		{
			Speed_Fan_Tr_Min = 0;
		}
		else
		{
			/*%C No function																		*/
		}
		DB_Measurement_Write(MEASURE_FAN_SPEED,Speed_Fan_Tr_Min);
		PIE1bits.CCP1IE = 1;
		PIR1bits.CCP1IF = 0;
		TIM_StartDecounter16(FAN_SPEED_MEASURE_OVERFLOW,TIME_FAN_SPEED_MEASURE_OVERFLOW);
	}	
	else if (TIM_ReadValue16(FAN_SPEED_MEASURE_OVERFLOW) == 0)
	{
		DB_Measurement_Write(MEASURE_FAN_SPEED,0);
	}

	else
	{
		/*%C No function																			*/
	}

}
