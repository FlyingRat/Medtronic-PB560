/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : LOOP_Controller.c                                              */
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
#include "CHARGE_Data.h"
#include "CHARGE_Loop_Controller.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UBYTE CHARGE_Loop_Controller(UWORD16 Setpoint
						   , UWORD16 Measure)
{
	SWORD32 Error = 0;
	SWORD32 Prop = 0;
	SWORD32 Result = 0;
	static SWORD32 Integral = 0 ;
	UWORD16 Kp_Bat_Regul = 0;
	UWORD16 Ki_Bat_Regul = 0;

	/* PRegulation parameters																	*/
	Ki_Bat_Regul = 50;
	Kp_Bat_Regul = 8;

	/*%C setpoint & measure delta computing 													*/
	Error = (SWORD32)(Setpoint) - (SWORD32)Measure;

	/*%C Adaptation depending on proportionel & integral fact 							*/
	Prop = Kp_Bat_Regul * Error;
	Integral = Integral + (Ki_Bat_Regul * Error);

	/*%C Adaptation of computed value to output scale										*/
	Result = (Prop + Integral) / 500; 
	/*%C Result saturation between 0 and 0x40 */
	Result = saturation(Result,
							  0,
							  0x40);
	/*%C Final value (compute with offset ) */
	Result = 0x40 - Result;
	return((UBYTE)Result);
}

