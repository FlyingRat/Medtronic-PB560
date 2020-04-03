/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ValveLeakage.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            Management of the alarm Valve leakage                         */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Alarm_Error                                           */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "SEC_ValveLeakage.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_ValveLeakage(void)
{
	e_DB_ALARMS_STATE AlarmValveLeakage =
								DB_AlarmStatusRead(ALARM_VALVE_LEAKAGE_U16);
	UWORD16 ComputedVti = DB_ComputeRead(COMPUTED_VTI_U16); 
	UWORD16 ComputedVteInsp = DB_ComputeRead(COMPUTED_VTE_INSP_U16);
	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
	static e_VentilState MemoVentilState = VEN_VENTIL_DISABLE;
	static UWORD16 ExhalQCount = 0;
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
/*%C Check ALARM_VALVE_LEAKAGE_U16 state 									  */
	switch(AlarmValveLeakage)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :

/*%C  If COMPUTED_VTE_INSP_U16 > 70% COMPUTED_VTI_U16 and					  */
/*%C 	COMPUTED_VTI_U16 > 40 ml, then		    							  */   
		if ((ComputedVteInsp >((ComputedVti * 7)/10))
		 && (ComputedVti > 40))
		{
/*%C 	   ALARM_VALVE_LEAKAGE_U16 = ALARM_DETECTED							  */
			DB_AlarmStatusWrite(ALARM_VALVE_LEAKAGE_U16,
									  ALARM_DETECTED);
/*%C  	Init of cycles counter ExhalQCount									  */
			ExhalQCount = 0;
		}
/*%C	End if 																  */
/*%C	Alarm_Error = NO_ERR_AL											  	  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :

/*%C 	If COMPUTED_VTE_INSP_U16 <= 70% COMPUTED_VTI_U16 or					  */
/*%C 	COMPUTED_VTI_U16 <= 40 ml, then		    							  */
	   if ((ComputedVteInsp <= (ComputedVti * 7)/10)
		|| (ComputedVti <= 40))
		{
/*%C  	Init of cycles counter ExhalQCount									  */
			ExhalQCount = 0;
/*%C 	 ALARM_VALVE_LEAKAGE_U16 = ALARM_FALSE  							  */
			DB_AlarmStatusWrite(ALARM_VALVE_LEAKAGE_U16, ALARM_FALSE);
		}
/*%C 	End if 																  */


/*%C  If COMPUTED_VTE_INSP_U16 > 70% COMPUTED_VTI_U16 and					  */
/*%C 	COMPUTED_VTI_U16 > 40 ml, then		    							  */ 
		if ((ComputedVteInsp > ((ComputedVti * 7)/10))
		 && (ComputedVti > 40))
		{

/*%C 		If ( VENTIL_STATE_U16 = VEN_INSPIRATION_CONTROLED or		      */
/*%C		VENTIL_STATE_U16 = VEN_INSPIRATION_TRIGGERED ) and 				  */
/*%C		MemoVentilState == VEN_EXHALATION , then    					  */
			if ( ( (VentilState == VEN_INSPIRATION_CONTROLED)
			  	 || (VentilState == VEN_INSPIRATION_TRIGGERED) )
			  && (MemoVentilState == VEN_EXHALATION) )
			{
/*%C 		ExhalQCount is increased 										  */
		      ExhalQCount = ExhalQCount + 1;
			}
/*%C 		End if															  */

/*%C 		If ExhalQCount = 3, then   										  */
			if (ExhalQCount == 3) 
			{
/*%C  		ALARM_VALVE_LEAKAGE_U16 = ALARM_TRUE 							  */
				DB_AlarmStatusWrite(ALARM_VALVE_LEAKAGE_U16,
										  ALARM_TRUE);
/*%C		Associated event is stored 										  */
				DB_EventMngt(EVENT_AL_VALVE_LEAKAGE );
/*%C 		Updating priority register 										  */
				SEC_Medium_Priority_2 = SEC_Medium_Priority_2 | 0x0008;
			}
/*%C		End if 															  */
		}
/*%C	End if 																  */
/*%C	Alarm_Error = NO_ERR_AL											  	  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State							  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C  The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  */
/*%C  So there is no action to do.											  */
/*%C	Alarm_Error = NO_ERR_AL											  	  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C 	If COMPUTED_VTE_INSP_U16 <= 70% COMPUTED_VTI_U16 or					  */
/*%C 	COMPUTED_VTI_U16 <= 40 ml, then		    							  */
	   	if ((ComputedVteInsp <= (ComputedVti * 7)/10)
		|| (ComputedVti <= 40))
		{
/*%C  		Init of cycles counter ExhalQCount								  */
			ExhalQCount = 0;
/*%C 		ALARM_VALVE_LEAKAGE_U16 = ALARM_FALSE 							  */
			DB_AlarmStatusWrite(ALARM_VALVE_LEAKAGE_U16,
									  ALARM_FALSE);
/*%C		Associated event is stored 										  */
			DB_EventMngt(EVENT_AL_END_OF_VALVE_LEAKAGE );
/*%C 		Updating priority register 										  */
			SEC_Medium_Priority_2 = SEC_Medium_Priority_2 & 0xFFF7;
		}
/*%C	End if 																  */
/*%C	Alarm_Error = NO_ERR_AL											  	  */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C	Alarm_Error = ERR_AL_VALVE_LEAKAGE		   						  	  */
		Alarm_Error = ERR_AL_VALVE_LEAKAGE;
		break;

/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C	Alarm_Error = ERR_AL_VALVE_LEAKAGE		   						  	  */
	  	Alarm_Error = ERR_AL_VALVE_LEAKAGE;
		break;
	}
/*%C End of check alarm state												 */
/*%C Updating the memory of the ventil state MemoVentilState				 */
	MemoVentilState = VentilState;
	return(Alarm_Error);
}


 