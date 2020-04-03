/******************************************************************************/
/*                                                                            */
/* Project N°  :  RC0603                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_100_FiO2.c                                             	  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            Management of the alarm 100% O2                               */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "SEC_100_FiO2.h"

e_ALARM_ERROR SEC_100_Fio2(void)
{
	e_DB_ALARMS_STATE Alarm100Fio2 = 
					DB_AlarmStatusRead(ALARM_100_PER_CENT_O2_U16);
	e_DB_ALARMS_STATE AlarmCalibFio2 = 
					DB_AlarmStatusRead(ALARM_CALIB_FIO2_U16);
	e_DB_ALARMS_STATE AlarmCheckO2Supply = 
					DB_AlarmStatusRead(ALARM_CHECK_O2_SUPPLY_U16);
	e_DB_ALARMS_STATE AlarmMissO2Supply = 
					DB_AlarmStatusRead(ALARM_MISSING_O2_SUPPLY_U16);
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
	UWORD16 O2_100p100 = DB_ControlRead (FIO2_100_ACTIVE);
	
	
	switch(Alarm100Fio2)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :

		if(	(O2_100p100 == TRUE) 
			&& (AlarmCalibFio2 == ALARM_FALSE)
			&& (Alarm100Fio2 == ALARM_FALSE)
			&& (AlarmCheckO2Supply == ALARM_FALSE)
			&& (AlarmMissO2Supply == ALARM_FALSE ))
		{
/*%C 	Alarm is turned to True  with the associated event */
			DB_AlarmStatusWrite(ALARM_100_PER_CENT_O2_U16, ALARM_TRUE);
			DB_EventMngt(EVENT_AL_100_PER_CENT_O2);
		}
		
		Alarm_Error = NO_ERR_AL;
		break;	
		
	/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :



		Alarm_Error = ERR_AL_O2_LEAKAGE;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C 	The following state ,"ALARM_DISPLAYED", is written by HMI module. */
/*%C  So there is no action to do .*/
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                              */
/******************************************************************************/
	case ALARM_DISPLAYED	:
		
		if ((	(O2_100p100 == FALSE)
			||	(AlarmCheckO2Supply >= ALARM_TRUE) 
			|| (AlarmMissO2Supply >= ALARM_TRUE)) 
			&& (Alarm100Fio2 >= ALARM_TRUE))
		{
/*%C Alarm is turned to False with the associated event  */
			DB_AlarmStatusWrite(ALARM_100_PER_CENT_O2_U16, ALARM_FALSE);
			DB_EventMngt(EVENT_AL_END_OF_100_PER_CENT_O2);
			TIM_StartDecounter(SEC_100_FIO2_TIM,TIME_SEC_100_FIO2);
		}
		
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :
		Alarm_Error = ERR_AL_O2_LEAKAGE;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
	  	Alarm_Error = ERR_AL_O2_LEAKAGE;
		break;
	}
	return(Alarm_Error);
}