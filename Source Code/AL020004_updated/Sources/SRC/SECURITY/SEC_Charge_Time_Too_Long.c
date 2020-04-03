/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Charge_Time_Too_Long.c                                     */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of Time for charging too long default		      */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "define.h"
#include "enum.h"
#include "typedef.h"
#include "CHARGE_Data.h"
#include "DB_PowerSupply.h"
#include "DB_Control.h"
#include "SEC_ChargeTooLongAlarms.h"
#include "SYS_Gauge_Data.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_Charge_Time_Too_Long(void)
{
	UWORD16 ChargeRunning = DB_Control_Read(CHARGE_RUNNING);
	UWORD32 capacity_max;

    if ( TYPICAL_BAT_CAPACITY == CAPACITY_7S1P) {
		capacity_max = CAPACITY_MAX_LEVEL_7S1P; 
	} else { 
		capacity_max = CAPACITY_MAX_LEVEL_7S2P; 
    }   

	if ( (CumulChargeCurrent > capacity_max)
	  && (ChargeRunning == TRUE) )
	{
/*%C 	Then CHARGE_TIME_TOO_LONG_FLAG = TRUE 								  */ 		
		 DB_PowerSupply_Write(CHARGE_TIME_TOO_LONG_FLAG,TRUE);
	}
/*%C End if 																  */
}
