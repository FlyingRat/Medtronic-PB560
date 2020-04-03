/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : define.h                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef DEFINE_H
#define DEFINE_H
/******************************************************************************/
/*         					  EVENT FLASH DEFINE						      */

/* Event Flash start address */
#define EVENT_FLASH_START_ADDRESS   	0x100000		
/* Event Flash end address */
#define EVENT_FLASH_END_ADDRESS     	0x17FFFF   	
/* Bottom boot memory type  29F400BB */
#define BOTTOM_BOOT     	   		0x22AB		
/* Top boot memory type  29F400BT */
#define TOP_BOOT        	   		0x2223 

/******************************************************************************/
/*         					  MONITORING FLASH DEFINE 					      */

/* flash size carateristics */
#define NAND_FLASH_BLOCK_NUMBER_LIMIT 2048
#define NAND_FLASH_PAGE_NUMBER    64
#define NAND_FLASH_COLUMN_NUMBER  2112
#define NAND_PAGE_CLUSTER_SIZE  512
#define NAND_FLASH_BLOCK_SIZE (64*2048UL)

		
#define MONITORING_FLASH_POINTER_ADDRESS  0x500000
#define MONITORING_FLASH_BLOCK_SIZE 0x20000	
#define MONITORING_FLASH_PAGE_SIZE 2048
#define LAST_PAGE_TO_ERASE 62
#define LAST_PAGE_IN_BLOCK 63
#define MONIT_BUFFER_SIZE 4   
#define MONIT_BUFFER_SIZE_READ 240   
#define FIFTEEN_MINUTES 90000
#define MAXIMUM_MONIT_DATA_NUMBER 512		
#define MAXIMUM_MONIT_RECEIVED_DATA 128

 
#define TREND_FLASH_BLOCK_SIZE 0x20000
#define TREND_FLASH_PAGE_SIZE 2048
#define TREND_BUFFER_SIZE 4   
#define TREND_BUFFER_SIZE_READ 240   
#define MAXIMUM_TREND_DATA_NUMBER 512		


#define DETAILLED_MONITORING_BUFFER_TYPE 1
#define TREND_BUFFER_TYPE 0

/* Buffer size for RTC access	*/
#define SIZE_OF_FIFO_RTC_ACCESS 		16
/*Buffer size for EEPROM Access	*/
#define SIZE_OF_FIFO_EEP_ACCESS 		64


#define NB_LANGUAGE 19
/* Alarm info field */
#define INFO_ALARM_TWO_MESSAGES 	 (0x80)
#define INFO_ALARM_DELAYED_MESSAGE   (0x40)

/* Bit7 Bit6 .................... Bit0
   |     |
   |     |_ 1 <=> Alarm has a delayed message
   |_ 1 <=> Alarm has two messages; 0 <=> Alarm has only one message
*/


#define cPEEP_CPAP_MIN 30

/*----------------------------------------------------------------------*/
/* 		Blower set point parameter for setup mode 							*/
/*----------------------------------------------------------------------*/
/* Integral constant	for flow */
/* Constante intégrale pour le mode maintenance	*/
#define cVEN_KPB_MAINT_FLOW 20000L
/* Proportional constant for flow */
#define cVEN_KIB_MAINT_FLOW 1000L

/* Integral constant	for speed */
#define cVEN_KPB_MAINT_SPEED 1000L
/* Proportional constant for speed */
#define cVEN_KIB_MAINT_SPEED 50L

/* Integral constant	for pressure */
#define cVEN_KPB_MAINT_PRESS 80000L
/* Proportional constant for pressure */
#define cVEN_KIB_MAINT_PRESS 4000L

#define CAN_STEP_PER_CENT					1062887 // (CAN par 10 % Fio2) * 10^6;

// FiO2 Calibration Point = 20.9 % of O2
#define FIO2_CALIB_POINT 	209

#define cDELTA_HIGH_FIO2			15
#define cDELTA_LOW_FIO2				15
#define cDELTA_HIGH_SPO2			1
#define cDELTA_LOW_SPO2				1
#define cFIO2_DIGIT_MIN_LEVEL 	62

#define cFIO2_TO_HIGH_FIO2 				15
#define cFIO2_TO_LOW_FIO2 					15
#define cFIO2_MIN_ADJUST 					21
#define cO2_LEAKAGE_THRESHOLD 			50
#define cO2_MISSING_SUPPLY_THRESHOLD 	100
#define cO2_CHECK_SUPPLY_THRESHOLD 		2800

#define cTHREE_CYCLES 		3
#define cFIVE_SECOND 		5000
#define cTEN_SECOND			10000

/******************************************************************************/
/*										VERSION DEFINE												*/
/******************************************************************************/
#define LU			0x4C55  // Legendair US
#define LX			0x4C58  // Legendair XL2
#define LM			0x4C4D  // Supportair M2
#define LS			0x4C53  // Legendair S2	  

/****************************************************************************/
/*              Absolut pressure sensor limits                             */

#define ABS_PRES_MAX    8250
#define ABS_PRES_MIN    4500

/******************************************************************************/
/*										HMI DEFINE													*/
/******************************************************************************/
#ifdef _TASKING
	#define NO_THIS (void*) this
#else
	#define NO_THIS 
#endif

#define TI_MAX_MAX		3000
#define TI_MAX_MIN		800
#define TI_MAX_STEP		100


#endif




