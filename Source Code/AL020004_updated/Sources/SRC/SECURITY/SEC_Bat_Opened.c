/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Bat_Opened.c                                               */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of Opened battery default					      */
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
#include "DB_Control.h"
#include "DB_Measurement.h"
#include "SEC_BatOpenAlarms.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_Bat_Opened(void)
{
	SWORD16 TempBat = (SWORD16) DB_PowerSupply_Read(TEMP_BAT_S16);
	UWORD16 PowerType = DB_PowerSupply_Read(POWER_TYPE_U16);
	UWORD16 Vbat_Measure_Filtered = DB_Measurement_Read(VBAT_MEASURE_FILTERED);
	UWORD16 ChargeRunning = DB_Control_Read(CHARGE_RUNNING);
	
/*%C If the default is not detected :										  */ 
/*%C if POWER_TYPE_U16  =  BAT_SUPPLY										  */
/*%C  or VBAT_MEASURE_FILTRED > BATTERY_ABSENT_TENSION_LEVEL 			  	  */
/*%C  or TEMP_BAT  < TEMP_BAT_RETURN_LEVEL 									  */
/*%C  or CHARGE_RUNNING != FALSE											  */
	
	if((Vbat_Measure_Filtered > BATTERY_ABSENT_TENSION_LEVEL)
		||(ChargeRunning != FALSE )
		||(TempBat < TEMP_BAT_RETURN_LEVEL)
		||(PowerType == BAT_SUPPLY))	
	{
/*%C 	Then a timer runs 													  */
		TIM_StartDecounter16(TIM_BAT_OPENED,TIME_BAT_OPENED);
	}
/*%C End if 																  */

/*%C If the timer is over 													  */
	if (TIM_ReadValue16(TIM_BAT_OPENED)== 0)
	{
/*%C 	Then BAT_OPENED_FLAG = TRUE 										  */
		DB_PowerSupply_Write(BAT_OPENED_FLAG,TRUE);
	}

/*%C Else if VBAT_MEASURE_FILTRED  >  TENSION_BAT_RETURN_LEVEL 				  */
/*%C  and TEMP_BAT  > TEMP_BAT_RETURN_LEVEL									  */
/*%C  and CHARGE_RUNNING = FALSE, then 										  */
	
	else if ( (Vbat_Measure_Filtered > TENSION_BAT_RETURN_LEVEL)
			 && (TempBat > TEMP_BAT_RETURN_LEVEL)
		 	 && (ChargeRunning == FALSE) )
		{
/*%C 		Then BAT_OPENED_FLAG = FALSE 									  */
			DB_PowerSupply_Write(BAT_OPENED_FLAG,FALSE);
		}
/*%C End if 																  */
	}
