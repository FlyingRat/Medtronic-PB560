/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Eeprom_Data.h                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Global variables of "EEPROM"                          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*                                                                            */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifdef DECLARATION_EEPROM_DATA
	#ifndef EEPROM_DATA_H
	#define EEPROM_DATA_H

UBYTE EEP_FIFO_IdxPush= 0;
UBYTE EEP_FIFO_IdxPull= 0;
UBYTE EEP_FIFO_NbDataInFifo=0;
t_EEP_ACCESS_CONTROL EEP_FIFO_AccessDriver[SIZE_OF_FIFO_EEP_ACCESS];


	#endif
#else
	#ifndef EEPROM_DATA_H
	#define EEPROM_DATA_H

extern UBYTE EEP_FIFO_IdxPush;
extern UBYTE EEP_FIFO_IdxPull;
extern UBYTE EEP_FIFO_NbDataInFifo;
extern t_EEP_ACCESS_CONTROL EEP_FIFO_AccessDriver[SIZE_OF_FIFO_EEP_ACCESS];


	#endif
#endif