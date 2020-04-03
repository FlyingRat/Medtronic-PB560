/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_TaskMeasure.c  											*/
/*																										*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Main_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_COM_Transmit_TaskMeasureResetMaximum(void)
{

	UWORD16 Loop = 0 ;

	/*%C Initilisation des valeurs maxi et mini du temps des taches */
	for (Loop = 0 ; Loop < MAXIMUM_VENTILATION_NUMBER_OF_TASKS ; Loop ++)
	{
		Ventilation_TimesOfTask[Loop].maxi = 0x0 ;
		//Ventilation_TimesOfTask[Loop].current = 0x0 ;
		Ventilation_TimesOfTask[Loop].mini   = 0xFFFF ;
	}
}
