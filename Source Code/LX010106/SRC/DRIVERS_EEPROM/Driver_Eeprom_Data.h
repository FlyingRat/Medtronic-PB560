/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Driver_Eeprom_data.h                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Description fonctionnelle:		 	                        	      */
/*                                                                      	   */
/*%C    Data declaration for eeprom driver functions                        	*/
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#define cDRV_EEP_TIME_OUT_10MS 10

#ifdef EEPROM_DATA_DECLARATION

	#ifndef DRIVER_EEPROM_DATA_H
	#define DRIVER_EEPROM_DATA_H


e_STATE_OF_DRIVE_EEP DRV_EEP_StateEepDriver = DRV_EEP_FREE;
UBYTE DRV_EEP_CounterTimeOutWrite;
e_DRV_EEP_WRITE_ERROR DRV_EEP_WriteStatus;
t_EEP_ACCESS_CONTROL DRV_EEP_CurrentDataPull; 
	#endif
#else

extern e_STATE_OF_DRIVE_EEP DRV_EEP_StateEepDriver;
extern UBYTE DRV_EEP_CounterTimeOutWrite;
extern e_DRV_EEP_WRITE_ERROR DRV_EEP_WriteStatus;
extern t_EEP_ACCESS_CONTROL DRV_EEP_CurrentDataPull;
#endif