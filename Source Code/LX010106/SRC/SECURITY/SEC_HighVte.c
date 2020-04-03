/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_HighVte.c                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C         Management of the alarm High Vte                                 */
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
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "SEC_HighVte.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_HighVte(void)
{
/* Alarm error declaration							                                 */
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/* Alarm low Vte recovery from base				                                 */
	e_DB_ALARMS_STATE Alarm_High_Vte = 	DB_AlarmStatusRead(ALARM_HIGH_VTE_U16);
/* Computed Vte recovery from base	 	                              		   */
	UWORD16 Computed_Vte = DB_ComputeRead(COMPUTED_VTE_U16);

/* Adjust low Vte recovery from base	 	                            	      */
	UWORD16 Adjust_High_Vte = DB_CurrentRead(ADJUST_HIGH_VTE_U16);
/* Low Vte no selecte state recovery from base	 	                    	      */
	UWORD16 High_Vte_No_Select = DB_CurrentRead (HIGH_VTE_NO_SELECT_U16);
/* Ventil state recovery from base	 	                				    	      */
   e_VentilState Ventil_State = DB_ControlRead(VENTIL_STATE_U16);
/* Ventil state memorization			 	                				    	      */
	static e_VentilState Memo_Ventil_State = VEN_VENTIL_DISABLE;
/* High vte cycle counter				 	                				    	      */
	static UWORD16 HVteCmp = 0;
/* No high vte cycle info				 	                				    	      */
	static UWORD16 NoHVteCmp= 0;


/*%C else, computed Vte keeps its value            				    	   */

	switch(Alarm_High_Vte)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                                  */
/******************************************************************************/
	case ALARM_FALSE :
/*%C If the Computed Vte is higher than Adjust low Vte */
/*%C & alarm high vte allowed (high Vte no select = FALSE) */
		if ( (Computed_Vte > Adjust_High_Vte)
		  && (High_Vte_No_Select == FALSE) )
		{
/*%C     Storage the Detected state of the alarm */
			DB_AlarmStatusWrite(ALARM_HIGH_VTE_U16,
									  ALARM_DETECTED);
/*%C     High Vte counter reset */
         HVteCmp = 0;
		}
	Alarm_Error = NO_ERR_AL;
	break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					               */
/******************************************************************************/
	case ALARM_DETECTED :

/*%C 	Increasing the default cycles counter when lower than 4 and once at */
/*%C  each cycle */
		if ( (HVteCmp < 3)
		  && (NoHVteCmp == 0) )
		{
/*%C 		increase the HVteCmp counter */
			HVteCmp = HVteCmp + 1;
/*%C 		Setting the flag to prohibe a new increment in the same cycle */
			NoHVteCmp = 1;
 		}

/*%C 	If computed vte is lower than adjusted high vte , */
/*%C 	or	no alarm is allowed (High Vte No Select = true), */
		if ( (Computed_Vte <= Adjust_High_Vte)
		  || (High_Vte_No_Select == TRUE) )
		{
/*%C 		Storage the False state of the alarm */
			DB_AlarmStatusWrite(ALARM_HIGH_VTE_U16,
									  ALARM_FALSE);
/*%C 		erazing of cycles counter */
			HVteCmp = 0;
		}
/*%C 	if the cycle counter is equal to 4 cycles and */
/*%C 	alarm high vte is detected, then 				 */
		else if (HVteCmp == 3)
		{
/*%C 		Storage of the true state in alarm base */
			DB_AlarmStatusWrite(ALARM_HIGH_VTE_U16,
									  ALARM_TRUE);
/*%C 		Storage of the associated event (EVENT_AL_HIGH_VTE)*/
			DB_EventMngt(EVENT_AL_HIGH_VTE);
/*%C		Priority register updating for buzzer and leds command */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0080;
		}

		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State												*/
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
/*%C  If computed vte is lower than adjusted low vte , */
/*%C  or no alarm is allowed (High Vte No Select = true), */
		if ( (Computed_Vte <= Adjust_High_Vte)
		  || (High_Vte_No_Select == TRUE) )
		{
/*%C 		Storage the False state of the alarm */
			DB_AlarmStatusWrite(ALARM_HIGH_VTE_U16,
									  ALARM_FALSE);
/*%C		Priority register updating for buzzer and leds command */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 & 0xFF7F;
/*%C 		erazing of cycles counter */
			HVteCmp = 0;
/*%C 		Storage of the associeted event ( end of alarm )*/
			DB_EventMngt(EVENT_AL_END_OF_HIGH_VTE);
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                               */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C  This alarm can't be canceled */
		Alarm_Error = ERR_AL_HIGH_VTE;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                        */
/******************************************************************************/
	default:
	  	Alarm_Error = ERR_AL_HIGH_VTE;
		break;
	}

/*%C On transition to exhalation, reset of the continuous default flag :*/
/*%C if Ventilation state is VEN_EXHALATION and was VEN_INSPIRATION_CONTROLED*/
/*%C or VEN_INSPIRATION_TRIGGERED 															*/
	if	( (Memo_Ventil_State == VEN_EXHALATION )
	  && ( (Ventil_State == VEN_INSPIRATION_CONTROLED)
		 || (Ventil_State == VEN_INSPIRATION_TRIGGERED) ) )
	{
/*%C  Freeing the flag allowing to increase counter (NoHVteCmp = 0)*/
		NoHVteCmp = 0;
	}
/*%C Updating the memory of ventil state */
	Memo_Ventil_State = Ventil_State ;

	return(Alarm_Error);
}
 