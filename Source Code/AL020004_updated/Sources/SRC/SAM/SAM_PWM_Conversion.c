/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SAM_PWM_Conversion.c															*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                 	Conversion des sorties PWM						   			*/
/******************************************************************************/
/*%I Input Parameter :  CanValue			  													*/
/*%I                    PWM_Value                   									*/
/*%IO Input/Output :    NONE	                                                */
/* 															                              */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES											*/
/******************************************************************************/
#include "p18f6622.h"
#include "typedef.h"
#include "enum.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SAM_PWM_Conversion( UBYTE PWMValue, e_SAM_PWM PWMControlType)
{
	/*%C PWM command function of control type	*/
	switch(PWMControlType)
	{
		/*%C Ventil PWM command 	*/
		case PWM_V_Ventil :
		{
			CCPR2L = PWMValue;
			break ;
		}
		/*%C V charge PWM command 	*/
		case PWM_V_Charge :
		{
			CCPR4L = PWMValue;
			break ;
		}

		/*%C I charge PWM command 	*/
		case PWM_I_Charge :
		{
			CCPR5L = PWMValue;
			break ;
		}
		default :
		{	
			break ;
		}
	}
}
