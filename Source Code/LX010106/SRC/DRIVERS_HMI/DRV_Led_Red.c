/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_Led_Red.c                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  This function commands the red led, function of level alarm             */
/*%C  This level is given trough the blink state parameter                    */
/*%C  - if the blink command is off, the red led is set off                   */
/*%C  - if the blink command is on, the red led is set on and the blink       */
/*%C    counter is initialized                                                */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   Blink                                               */
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
#include "enum.h"
#include "Structure.h"
#include "Driver_Datas.h"
#include "io_declare.h"

void DRV_Led_Red(e_TYPE_BLINK Blink)
{

/*%C Led off command  */
   if (Blink == NO_LED)
	{
/*%C  shut down the led  */
	   Id_Led_Red = FALSE;
	   LED_ALARME_ROUGE = FALSE;
	}
/*%C Blink led command  */
   else if (Blink == BLINK_LED)
	{
/*%C  Blink counter initialized  */
	   CounterBlink = 0;
/*%C  Orange led set on */
	   Id_Led_Red = TRUE;
	   LED_ALARME_ROUGE = TRUE;
	}
/*%C else, shut down the led  */
   else
	{
	   Id_Led_Red = FALSE;
	   LED_ALARME_ROUGE = TRUE;
	}
}
