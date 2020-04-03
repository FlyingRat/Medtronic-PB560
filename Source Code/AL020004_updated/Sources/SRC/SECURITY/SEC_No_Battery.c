/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_No_Battery.c       		                                  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of No battery default						      */
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
#include "SEC_NoBattAlarms.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_No_Battery(void)
{
	SWORD16 TempBat = (SWORD16) DB_PowerSupply_Read(TEMP_BAT_S16);
	UWORD16 PowerType = DB_PowerSupply_Read(POWER_TYPE_U16);
	
/*%C If the default is not detected : 										  */ 
/*%C If TEMP_BAT  > BATTERY_ABSENT_TEMP_LEVEL or POWER_TYPE  =  BAT_SUPPLY    */
	if ( (TempBat > BATTERY_ABSENT_TEMP_LEVEL)
	  || (PowerType == BAT_SUPPLY) )	
	{
/*%C 	Then a timer runs 													  */
		TIM_StartDecounter16(TIM_NO_BAT,TIME_NO_BAT);
	}
/*%C End if 																  */
/*%C If timer reached value 0, the default was detected during 500ms, 		  */
	if(TIM_ReadValue16(TIM_NO_BAT)== 0)
	{
/*%C 	Then NO_BAT_FLAG = TRUE 											  */
		DB_PowerSupply_Write(NO_BAT_FLAG,TRUE);
	}
/*%C Else NO_BAT_FLAG = FALSE 												  */
	else
	{
		DB_PowerSupply_Write(NO_BAT_FLAG,FALSE);
	}
/*%C End if 																  */
}
