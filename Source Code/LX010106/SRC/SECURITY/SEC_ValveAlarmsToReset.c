/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ValveAlarmsToReset.c                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   It manages the valve use and change alarm							         */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "DB_AlarmStatus.h"
#include "Security_Datas.h"
#include "SEC_ValveAlarmsToReset.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void SEC_ValveAlarmsToReset(void)
{

/********************* ALARME VALVE	ANNULEES **************/
/* ATTENTION - toujours annuler la n°2 avant la n°1 pour laisser la mémo */
/* alarme sur le 1er message */
		DB_AlarmStatusWrite(ALARM_UTILISER_VALVE_CHANGER_PE_PI_2_U16,
								  ALARM_FALSE);
		DB_AlarmStatusWrite(ALARM_UTILISER_VALVE_CHANGER_PE_PI_1_U16,
		 						  ALARM_FALSE);
		DB_AlarmStatusWrite(ALARM_ENLEVER_VALVE_CHANGER_PE_PI_2_U16,
								  ALARM_FALSE); 
		DB_AlarmStatusWrite(ALARM_ENLEVER_VALVE_CHANGER_PE_PI_1_U16,
								  ALARM_FALSE); 
		DB_AlarmStatusWrite(ALARM_UTILISER_VALVE_2_U16,
								  ALARM_FALSE);
		DB_AlarmStatusWrite(ALARM_UTILISER_VALVE_1_U16,
								  ALARM_FALSE);
		DB_AlarmStatusWrite(ALARM_ENLEVER_VALVE_2_U16,
								  ALARM_FALSE);	
		DB_AlarmStatusWrite(ALARM_ENLEVER_VALVE_1_U16,
								  ALARM_FALSE);	
		SEC_High_Priority_2 = SEC_High_Priority_2 & 0xF0FF;
		SEC_SpeedTestEnded = FALSE;

}