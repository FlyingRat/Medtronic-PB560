/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_Led_White.c                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  This function commands the white led				     */
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

extern void DRV_OutputPort(e_OUTPUT_NAME _Port, UWORD16 _Value);

void DRV_Led_White(e_TYPE_BLINK Blink)
{

/*%C Led off command  */
   if (Blink == NO_LED)
	{
/*%C  shut down the led  */
	   Id_Led_White = FALSE;
	   Led_White_On = FALSE;
	}
/*%C Blink led command  */
   else if (Blink == BLINK_LED)
	{
/*%C  Blink counter initialized  */
	   CounterBlink = 0;
/*%C  Orange led set on */
	   Id_Led_White = TRUE;
	   Led_White_On = TRUE;
	}
/*%C else, shut down the led  */
   else
	{
	   Id_Led_White = FALSE;
	   Led_White_On = TRUE;	 
	}
/*%C Port activation */   
   DRV_OutputPort(OUT_LED_O2, (UWORD16) Led_White_On);
}