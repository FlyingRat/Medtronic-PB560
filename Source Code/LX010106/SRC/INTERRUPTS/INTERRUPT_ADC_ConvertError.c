/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INTERRUPT_ADC_ConvertError.c                         */
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
#include "INTERRUPT_ADC_ConvertError.h"
#include "Driver_ADConverter_data.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

#ifndef _TASKING
void INTERRUPT_ADC_ConvertError(void) interrupt 0x29
#else
interrupt (0x29)
  void INTERRUPT_ADC_ConvertError(void)
#endif
{ 
	UWORD16 Read;

	ADST = 0;
	ADEIE = 0;
	ADEIR = 0;
	//Vidage des registres du résultat de convertion
 	Read = ADDAT;
	Read = ADDAT2;
	DRV_ADC_ConvertInit();
	ErrorNumber++;
	ADEIE = 1;
}
