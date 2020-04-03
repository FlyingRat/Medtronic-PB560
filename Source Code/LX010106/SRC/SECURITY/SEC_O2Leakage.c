/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0306                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_O2Leakage.c                                   	  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            Management of the alarm 02 leakage                */
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
#include "define.h"
#include "Structure.h"
#include "DB_Compute.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "SEC_O2Leakage.h"
#include "Security_Datas.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_O2Leakage(void)
{
	e_DB_ALARMS_STATE AlarmO2Leakage =
								DB_AlarmStatusRead(ALARM_O2_LEAKAGE_U16);
	UWORD16 FIO2_100_Active= DB_ControlRead(FIO2_100_ACTIVE);
	UWORD16 Adjust_FIO2= DB_ConfigRead(ADJUST_FIO2);
	SWORD16 Measure_QO2 = (SWORD16)DB_ComputeRead(MEASURE_QO2_S16);
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
  	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

	static e_VentilState MemoVentilState = VEN_VENTIL_DISABLE;
	static SWORD16 Maxi = 0;

/*%C We must compute the variation of the QO2 each respiratory cycles. */

	if(((VentilState == VEN_INSPIRATION_CONTROLED)
	 ||(VentilState == VEN_INSPIRATION_TRIGGERED))
	  &&(MemoVentilState ==VEN_EXHALATION))
	{
			Maxi = 0;
	}
	if((VentilState == VEN_INSPIRATION_CONTROLED)
	 ||(VentilState == VEN_INSPIRATION_TRIGGERED))
	{
		if(Measure_QO2 > Maxi)
		{
			Maxi = Measure_QO2;
		}
	}
	if (Adjust_FIO2 > cFIO2_MIN_ADJUST )
	{
		TIM_StartDecounter(SEC_O2_LEAKAGE, cTEN_SECOND);							
	}

	switch(AlarmO2Leakage)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C If QO2 is upper or equal to 0.5 lpm, and Fio2 is not selected, */
/*%C and 100% O2 is not active, */
/*%C and the cycle is ended */
	    if((Maxi >= cO2_LEAKAGE_THRESHOLD)
		 &&(FIO2_100_Active == FALSE)
		 &&(Adjust_FIO2 <= cFIO2_MIN_ADJUST)
		 &&(TIM_ReadDecounterValue(SEC_O2_LEAKAGE) == 0)
		 &&(VentilState == VEN_EXHALATION)
		 &&((MemoVentilState == VEN_INSPIRATION_CONTROLED)
		  ||(MemoVentilState ==VEN_INSPIRATION_TRIGGERED)))
		{
/*%C 		The Alarm is turned to TRUE, and the corresponding event is recorded*/
		  	DB_AlarmStatusWrite(ALARM_O2_LEAKAGE_U16, ALARM_TRUE);
			DB_EventMngt(EVENT_AL_O2_LEAKAGE);
/*%C		Priority register updating for buzzer and le ds command */
			SEC_High_Priority_2	= SEC_High_Priority_2| 0x0080;
		}
/*%C else if the ventilation is disable, and the QO2 is upper than 0.5 lpm */
		else if((VentilState == VEN_VENTIL_DISABLE)
			  &&(Measure_QO2 > cO2_LEAKAGE_THRESHOLD))
		{
/*%C 		The Alarm is turned to TRUE, and the corresponding event is recorded*/
		  	DB_AlarmStatusWrite(ALARM_O2_LEAKAGE_U16, ALARM_TRUE);
			DB_EventMngt(EVENT_AL_O2_LEAKAGE);
/*%C		Priority register updating for buzzer and leds command */
			SEC_High_Priority_2	= SEC_High_Priority_2| 0x0080;
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
/*%C If QO2 becomes lower than 0.5 lpm, or Fio2 is  selected, */
/*%C or 100% O2 is not active. */
	    if(((Maxi < cO2_LEAKAGE_THRESHOLD)
		 &&((VentilState == VEN_EXHALATION)
		 &&((MemoVentilState == VEN_INSPIRATION_CONTROLED)
		  ||(MemoVentilState ==VEN_INSPIRATION_TRIGGERED))))
		 ||((Adjust_FIO2 > cFIO2_MIN_ADJUST)
		  &&(VentilState != VEN_VENTIL_DISABLE))
		 ||(FIO2_100_Active == TRUE))
		{
/*%C 		The Alarm is turned to FALSE, and the corresponding event is recorded*/
		  	DB_AlarmStatusWrite(ALARM_O2_LEAKAGE_U16, ALARM_FALSE);
			DB_EventMngt(EVENT_AL_END_OF_O2_LEAKAGE);
/*%C		Priority register updating for buzzer and leds command */
			SEC_High_Priority_2	= SEC_High_Priority_2 & 0xFF7F;
		}
		else if((Measure_QO2 <= cO2_LEAKAGE_THRESHOLD) 
			 &&(VentilState == VEN_VENTIL_DISABLE))
		{
/*%C 		The Alarm is turned to FALSE, and the corresponding event is recorded*/
		  	DB_AlarmStatusWrite(ALARM_O2_LEAKAGE_U16, ALARM_FALSE);
			DB_EventMngt(EVENT_AL_END_OF_O2_LEAKAGE);
/*%C		Priority register updating for buzzer and leds command */
			SEC_High_Priority_2	= SEC_High_Priority_2 & 0xFF7F;
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
	MemoVentilState = VentilState;
	return(Alarm_Error);
}