/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INTERRUPT_COM_EndTransmit.c 									  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  														  					*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            	  	*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE       											  				*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#else
#include "regf276e.h"
#endif	 
#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "define.h"
#include "DRV_COM_Data.h"
#include "Flash_Monit_Data.h"
					 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

#ifndef _TASKING
 void INTERRUPT_COM_EndTransmit(void) interrupt (0x47)
#else
interrupt (0x47)
 void INTERRUPT_COM_EndTransmit(void)
#endif	 
{ 
	/*%C Interrupt inhibit  */
	S0TBIE = 0;
	DRV_COM_End_of_Transmit = TRUE;
	DRV_MONIT_New_Data = FALSE;
	DRV_TREND_New_Data = FALSE;

}	