/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EEP_WaitEndTransmit.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   */
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
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Driver_Eeprom_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

										   
void DRV_EEP_WaitEndTransmit(void)
{
/*%C  RAZ dof flag underflow timer 3			*/
	T3IR = 0;		
/*%C 50 * 200ns, delay of timer3 = 10µs  */
	T3 = 0x0032;   
/*%C count down, fc=fcpu/8, start timer */
	T3CON  = 0x00C0;   
/*%C Waiting end of transfert or timeout(10us)		*/
	while ( SSCBSY == 0 && T3IR == 0);  
	while ( SSCBSY == 1 && T3IR == 0);  
	if (T3IR) DRV_EEP_WriteStatus = DRV_EEP_TIME_OUT_TRANSMIT;
/*%C stop Timer3	 */
	T3CON = 0x0000;   
}	