/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_Led_Ventil.c                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  This function commands the ventilation led, this led is off during      */
/*%C  ventilation                                                             */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   VentilLedCommand                                    */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
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
#include "io_declare.h"
#include "enum.h"
#include "DRV_Led_Ventil.h"

void DRV_Led_Ventil(e_BOOL VentilLedCommand)
{

/*%C Ventil led management (TRUE/FALSE)        */
	DRV_OutputPort(OUT_LED_VENTIL, (UWORD16)VentilLedCommand);

}
