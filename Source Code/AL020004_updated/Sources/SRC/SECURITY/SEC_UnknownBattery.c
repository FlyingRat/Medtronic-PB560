/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_UnknownBattery.c                                   		  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of Unknown Battery						     	  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "DB_PowerSupply.h"
#include "SEC_UnkBatAlarms.h"
#include "SYS_Gauge_Data.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_UnknownBattery(void)
{

	UWORD16 CommunicationEepromFailure = DB_PowerSupply_Read(COMMUNICATION_EEPROM_FAILURE);

/*%C If COMMUNICATION_EEPROM_FAILURE <> TRUE 								  */
	if (CommunicationEepromFailure != TRUE )
	{
/*%C 	Then a timer runs 													  */
		TIM_StartDecounter16(TIM_UNKNOW_BATTERY,TIME_UNKNOW_BATTERY);
	}
/*%C End if 																  */
	
/*%C If the delay is over 													  */ 
	if((TIM_ReadValue16(TIM_UNKNOW_BATTERY)== 0)
		||((TYPICAL_BAT_CAPACITY!=CAPACITY_7S2P)&&(TYPICAL_BAT_CAPACITY!=CAPACITY_7S1P)))
	{
/*%C 	Then UNKNOWN_BATTERY_FLAG = TRUE 									  */
		DB_PowerSupply_Write(UNKNOWN_BATTERY_FLAG,TRUE);
	}
/*%C Else UNKNOWN_BATTERY_FLAG = FALSE										  */
	else
	{
		DB_PowerSupply_Write(UNKNOWN_BATTERY_FLAG,FALSE);
	}
/*%C End if 																  */
}
