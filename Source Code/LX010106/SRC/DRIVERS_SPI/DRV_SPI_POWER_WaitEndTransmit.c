/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_RTC_Launch.c                         								*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
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
#include "DRV_SPI_POWER_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_SPI_POWER_WaitEndTransmit(void)
{
	T3IR = 0;			// RAZ du flag underflow timer 3
	T3 = 50;   	// 50 * 200ns, duree du timer3 > 4.8µs
	//--------------------------------------------------------
/*%C  T3 CON = 0x00C0 = 1100 0000b					*/
/*%C  T3I = 000 	: Prescaler factor = 8			*/
/*%C  				: Input frequency = 2.5MHz		*/
/*%C  				: Resolution = 200ns				*/
/*%C  				: Period = 26ms					*/
/*%C  T3M = 000	: Timer Mode						*/
/*%C  T3R = 1		: Timer/Counter3 démarrage		*/
/*%C  T3UD = 1 et 
/*%C  T3UDE = 0	: Count Down						*/
	T3CON  = 0x00C0;	/*%C   count down, fc=fcpu/8, start timer

/*%C  attente de la fin du transfert ou timeout(10us)		 */
	while ( SSCBSY == 0 && T3IR == 0);
 
	while ( SSCBSY == 1 && T3IR == 0);  
	if (T3IR) DRV_SPI_POWER_Status = DRV_SPI_POWER_TIME_OUT_TRANSMIT;
	T3CON = 0x0000;     /*%C   stop Timer3						 */
}