/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EEPROM_BAT_Launch.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        Read or Write or Init access of the EERPOM Battery						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "define.h"
#define DECLARATION_EEPROM_BAT_DATA
#include "DB_PowerSupply.h"
#include "DB_Measurement.h"
#include "DRV_EEPROM_BAT_Data.h"
#include "DRV_EEPROM_BAT_Launch.h"

extern UWORD16 DB_Measurement_Read(e_DB_Measurement Id);
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_EEPROM_BAT_Launch(void)
{
	static UBYTE FirstRun = TRUE;
	UWORD16 BatChangingDetection = DB_PowerSupply_Read(BAT_CHANGING_DETECTION);
	UWORD16 NoBatFlag = DB_PowerSupply_Read (NO_BAT_FLAG);
	UWORD16 CommunicationEepromFailure = DB_PowerSupply_Read(COMMUNICATION_EEPROM_FAILURE);
	UWORD16 EeepromBatDifferneceZoneReadWrite = 
					DRV_EEPROM_BAT_DifferenceZoneReadWrite();
	SWORD16  BatteryTemp = (SWORD16)DB_Measurement_Read(BATTERY_TEMP);

	/*C Detection of Battery changing 														*/
	if ( (FirstRun == TRUE)
	  || (BatChangingDetection == TRUE) )
	{
		/*%C Locking the flag of first run													*/
		FirstRun = FALSE;	
		/*%C We must init the communication between the Pic and the battery		*/
		State = INIT;
		STEP = RESET;
		/*%C Initialization of the failure communication flag							*/
		DB_PowerSupply_Write(COMMUNICATION_EEPROM_FAILURE,TRUE);
		DB_PowerSupply_Write(READ_DATA_EEPROM_BAT_FAILURE, TRUE);
		DB_PowerSupply_Write(WRITE_DATA_EEPROM_BAT_FAILURE, TRUE);
		DB_PowerSupply_Write(BAT_CHANGING_DETECTION, FALSE);
		DB_PowerSupply_Write(NEW_BAT_FLAG,TRUE);
		DB_PowerSupply_Write(BAT_SUPPLIER, UNKNOWN_SUPPLIER);
	}
	
	/*%C Check condition to init the memory of the battery: 							*/
	/*%C When we are a new battery															*/
	if (State == INIT)
	{
		DRV_EEPROM_BAT_INIT_NEW_BATTERY();
	}

	/*%C Check condition to read the memory of the battery: 							*/
	/*%C When we have a reading access														*/
	/*%C & the battery is known																*/
	else if ( (State == READ) 
			 && (CommunicationEepromFailure == FALSE) )
	{
		/* Read all data of the EEPROM Battery	(64 bytes)								*/
		DRV_EEPROM_BAT_ReadMemory();
	}
	/*%C Check condition to write in the battery memory: 								*/
	/*%C When we have a writable access														*/
	/*%C & the last access is lower than 1/4 of hours									*/ 
	/*%C & both array are different (reading and wirting array)						*/
	/*%C & the battery is known																*/
	else if ( (State == WRITE) 
			 && (TIM_ReadValue32(TIME_ACCESS_EEPROM_WRITE) == 0) 
			 && (EeepromBatDifferneceZoneReadWrite == TRUE)
			 && (CommunicationEepromFailure == FALSE) )
	{
		/* Write all data on the EEPROM Battery (32 bytes)								*/
		DRV_EEPROM_BAT_WriteMemory();
	}
	else
	{
		State = READ;
	}
}




