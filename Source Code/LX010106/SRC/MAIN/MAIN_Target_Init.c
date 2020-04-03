/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Target_Init.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C The function of target initialization is launched :                      */
/*%C  - allowing the use of the emulator          */
/*%C  - Watchdog setup            */
/*%C  - service the watchdog */
/*%C  - Input/Output port setup     */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
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
#include "define.h"
#include "io_declare.h"
#include "enum.h"
#include "MAIN_Target_Init.h"
  
									 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void MAIN_Target_Init_FirstStep(void)
{
	/******************************************************************************/
/*%C 									Watchdog Configuration : 								*/
/*%C The watchdog is used to force the device rebooting when a software task's*/
/*%C execution becomes too long. It is to prevent of task overflow, infinite */
/*%C loop,etc .*/
/*%C So,the Watchdog period ('Pwdt') must be longer than a schedule sequence */
/*%C (20ms), but long enough to do all te initialisation without reloading the*/
/*%C service watchdog.*/
/*%C So, if WDTCON = 0x0001 then WDTIN = WDTCON^0 = 1 */
/*%C and WDTREL = WDTCON^8~15 = 0.   */
/*%C So the watchdog Period :      */
/*%C 			Pwdt = (1/Fcpu) * 512 * ( 1 + [WDTIN]*63 ) * ( 256 - [WDTREL] )	*/
/*%C			Pwdt = 209.7ms      with Fcpu = 40MHz             */
/*%C So it seems to be OK           */
   WDTCON = 0x0001;


/******************************************************************************/
/*%C 									Port 2 Configuration : 									*/
	P2		= 0x0000;
/*%C Direction Control Register																*/
	DP2   = 0xE01A;
/*%C Open Drain Control Register																*/
	ODP2  = 0x1F65; 

/******************************************************************************/
/*%C 									Port 3 Configuration : 									*/
	P3 	= 0x76E0;	 //0x7660;
/*%C Direction Control Register																*/
	DP3   = 0xB6A7;
/*%C Open Drain Control Register																*/
	ODP3  = 0x495F;
	
/******************************************************************************/
/*%C 									Port 7 Configuration : 									*/
	P7 	= 0x00;
/*%C Direction Control Register																*/
	DP7   = 0xFF; 
/*%C Open Drain Control Register																*/
	ODP7  = 0x08; 

/******************************************************************************/
/*%C 									Port 6 Configuration : 									*/
	P6 = 0x00;
/*%C Direction Control Register																*/
	DP6   = 0x7F; 
/*%C Open Drain Control Register																*/
	ODP6  = 0x80; 


/******************************************************************************/
/*%C 									Port 8 Configuration : 									*/
/*%C Direction Control Register																*/
	DP8   = 0x00; 
/*%C Open Drain Control Register																*/
	ODP8  = 0xFF; 

/******************************************************************************/
/*%C SPI BUS Master port configuration 													*/
/******************************************************************************/
/*
	XDP6.5 	= 1
	XP6.5		= 1
	XOD6.5 	= 0

	XDP6.6 	= 1
	XP6.6		= 1
	XOD6.6 	= 0

	XDP6.7 	= 0
	XP6.7		= 1
	XOD6.7 	= 1
*/
	XSSCPORT = 0x019B;//0x019B ;
}

void MAIN_Target_Init_SecondStep(void)
{

/******************************************************************************/
/*%C  The Watchdog is activated,launched.	   											*/
 	_srvwdt_();

	RESET_USB = 1;

/*%C RAZ Chip Enable SPI */
	DRV_OutputPort(OUT_LED_VENTIL, 0);
	DRV_OutputPort(OUT_LED_O2, 0);
	DRV_OutputPort(FREE_1Q3, 0);
/*%C Only one RAZ CE to raz the other */
	DRV_OutputPort(CE_EEP, 1);
	DRV_OutputPort(CE_SPI_PIC_IC44, 0);
	DRV_OutputPort(FREE_2Q7, 0);
	DRV_OutputPort(FREE_2Q8, 0); 
	DRV_OutputPort(CE_SPI_USB, 1);
}

void MAIN_Target_Init(void)
{
	MAIN_Target_Init_FirstStep();
	MAIN_Target_Init_SecondStep();	
} 	  
 	  
