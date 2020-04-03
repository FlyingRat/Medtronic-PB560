/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_Temperature_Launch.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE       */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif
#include "io_declare.h"

					 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_Temperature_WaitEndTransmit(void)
{
/*%CRAZ of flag underflow timer 3	*/
	T3IR = 0;
/*%C24 * 200ns, delay of timer3 = 4.8µs	 */
	T3 = 0x0018;   
	//--------------------------------------------------------
/*%C T3 CON = 0x00C0 = 1100 0000b					  */
/*%C T3I = 000 	: Prescaler factor = 8				  */
/*%C			: Input frequency = 2.5MHz	          */
/*%C 			: Resolution = 400ns			      */
/*%C			: Period = 26ms					      */
/*%C T3M = 000	: Timer Mode						  */
/*%C T3R = 1	: Timer/Counter3 démarrage		      */
/*%C T3UD = 1 et 									  */
/*%C T3UDE = 0	: Count Down						  */
/*%C count down, fc=fcpu/8, start timer				  */

	T3CON  = 0x00C0;	
/*%CWaitting end of transmition or timeout (10us)for each toggle of T3IR	  */
	while ( SSCBSY == 0 && T3IR == 0);  
	while ( SSCBSY == 1 && T3IR == 0);  
/*%Cif (T3IR) DRV_RTC_Status = DRV_RTC_TIME_OUT_TRANSMIT; */
/*%Cstop Timer3										  */
	T3CON = 0x0000;     
}