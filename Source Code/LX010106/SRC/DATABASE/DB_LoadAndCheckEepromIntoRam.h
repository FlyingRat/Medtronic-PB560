/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_LoadAndCheckEepromIntoRam.h				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration for               	*/
/*%C        DB_LoadAndCheckEepromIntoRam.c			                           */
/*                                                            				  		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		        			                  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None      	                 				  		*/
/******************************************************************************/

#ifndef LOAD_AND_CHECK_EEPROM_INTO_RAM_H
#define LOAD_AND_CHECK_EEPROM_INTO_RAM_H

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "DB_current.h"
#include "DB_config.h"
/******************************************************************************/
/*                 VARIABLE DECLARATION                                       */
/******************************************************************************/

/* Tables for check eeprom result */
UWORD16 DB_EepVolAdjustDbError[end_of_adjust_table];
UWORD16 DB_EepPresAdjustDbError[end_of_adjust_table];
UWORD16 DB_EepPsvAdjustDbError[end_of_adjust_table];
UWORD16 DB_EepVsimvAdjustDbError[end_of_adjust_table];
UWORD16 DB_EepPsimvAdjustDbError[end_of_adjust_table];
UWORD16 DB_EepCpapAdjustDbError[end_of_adjust_table];

extern void EEP_FIFO_PushOneData(	UWORD16 xhuge *ptr_DataRam,
												e_EEP_ACCESS_STATE access_type);

#endif												 