/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Main_Data.h                                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          It is the entry point, the "main", of the software :            */
/*%C          It initializes the processor target (registers and variables)   */
/*%C          and launch the scheduler.                                       */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#define MAXIMUM_VENTILATION_NUMBER_OF_TASKS 32

#ifdef DECLARATION_MAIN_DATA
	#ifndef MAIN_DATA_H
	#define MAIN_DATA_H


UWORD16 CounterTemperature = 0;
e_SPI_ACCESS spi_chip_access = SPI_EEPROM;
//UWORD16 TopTimer5ms = FALSE;
UWORD16 TestSchedulerStep;
UWORD16 CounterTop1ms = 0;
UWORD16 MAIN_Interfaces_Second_Init = FALSE;
UWORD16 MAIN_End_of_init = FALSE;
UWORD16 MAIN_TopTimer5ms = FALSE;
UWORD16 MAIN_CrcEepromTrouble = FALSE;
t_MEASURES_TIMES Ventilation_TimesOfTask[MAXIMUM_VENTILATION_NUMBER_OF_TASKS];


	#endif
#else
	#ifndef MAIN_DATA_H
	#define MAIN_DATA_H

extern UWORD16 CounterTemperature;
extern e_SPI_ACCESS spi_chip_access;
//extern UWORD16 TopTimer5ms;
extern UWORD16 TestSchedulerStep;
extern UWORD16 CounterTop1ms;
extern UWORD16 MAIN_Interfaces_Second_Init;
extern UWORD16 MAIN_End_of_init;
extern UWORD16 MAIN_TopTimer5ms;
extern UWORD16 MAIN_CrcEepromTrouble;
extern t_MEASURES_TIMES Ventilation_TimesOfTask[];

	#endif
#endif
