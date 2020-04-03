/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : FAN_Loop_Controller.c                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                									*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                             INCLUDE FILES		                          		*/
/******************************************************************************/

#include "typedef.h"
#include "FAN_Loop_Controller.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UBYTE FAN_Loop_Controller(UWORD16 Setpoint, UWORD16 Measure)
{
	/*%C Proportional regulation coefficient  */
	UWORD16 kP = 35;
	/*%C Integral regulation coefficient  */
	UWORD16 kI = 10;
	/*%C Calculation proportional term */
   SWORD32 P = 0;
  	/*%C calculation integral term     */
   static SWORD32 I = 0;
	/*%C calculation  Error = SetPoint - Measure */
	SWORD32 error = 0;

   /*%C memorization of the prévious sertpoint  */
   static SWORD32 PreviousResult = 0;
   /*%C Temporary variable */
   SWORD32 Tmp;

	/*%C  initialization of the calculation 						 */
	SWORD32 Result = 0;
	
	/*%C Compute error = Setpoint - Measure */
	error = (SWORD32)(Setpoint) - (SWORD32)Measure;
	
	/*%C Compute Proportional term */
    P = error * kP;
	P = P /100;
	P = saturation(P,-640,640);
	
	/*%C Compute  Intégral term */
	I = I * 1000 + error * kI;
	I = I / 1000;
 	I = saturation(I,0,640);
 	
	/*%C Compute Setpoint  (PWM*10) */
   Result =  P + I;
	/*%C Calculation of the gap between the setpoint and the previous setpoint */
	Tmp = (Result-PreviousResult);
 	/*%C Changement de valeur de PWM si la nouvelle consigne est supérieure */
 	/*%C à 9 10ième de pas de PWM par rapport à la consigne précédente      */
   if ( (Tmp > 9) || (Tmp < -9))
	{
		Result = PreviousResult+ Tmp;	
		PreviousResult = Result;		
	}
	else
	{
		Result = PreviousResult;
	}		
		  
	/*%C Ajustement à la valeur entière de PWM et saturation sur la plage de PWM autorisée*/
	Result = saturation(Result/10,10,64);					  
 
	/*%C Affectation de la consigne de vitesse													     */			  
	return  (UBYTE)Result;
}
