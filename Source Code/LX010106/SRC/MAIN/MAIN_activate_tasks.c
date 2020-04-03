/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_activate_tasks.c                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                               									*/
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
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Main_Data.h"
#include "MAIN_activate_tasks.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void MAIN_activate_tasks(void)
{

/*%C Internal and external watchdog are blocked during intialization 			*/
	if (MAIN_End_of_init == FALSE) 
	{
/*%C 	Hard watch dog activated	 			*/
		WDOG = !WDOG;
/*%C 	Internal watch dog activated	 			*/
		_srvwdt_();
	}

/*%C Every 5ms, a synchro signal is given	 			*/
	TestSchedulerStep = (UBYTE)((CounterTop1ms + 1)% NB_1MS_BY_SCHEDULER_STEP);
	if (TestSchedulerStep == 0)
	{
		MAIN_TopTimer5ms = TRUE;
		CounterTop1ms = 0;
	}
	else 
	{
		CounterTop1ms++;
	}

/*%C One SPI access per scheduler step:	 			*/
/*%C - EEprom driver mngt	 								*/
	if (spi_chip_access == SPI_EEPROM)
	{
		// Driver E2prom
		DRV_EEP_Launch();
/*%C 	Eeprom to RTC peripheric switch		 								*/
		spi_chip_access = SPI_RTC;
	}
/*%C - RTC driver mngt	 									*/
	else if (spi_chip_access == SPI_RTC)
	{
	  	DRV_RTC_Launch();
/*%C 	RTC to power card peripheric switch		 								*/
		spi_chip_access = SPI_POWER;
	}
/*%C - Power card communication 							*/
	else if (spi_chip_access == SPI_POWER)
	{
  		DRV_SPI_POWER_Launch();
/*%C 	Power card to eeprom peripheric switch		 								*/
		spi_chip_access = SPI_EEPROM;
	}
}
