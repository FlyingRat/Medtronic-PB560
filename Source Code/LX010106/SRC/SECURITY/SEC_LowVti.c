/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_LowVti.c                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C         Management of the alarm Low Vti                                  */
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
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "SEC_LowVti.h"
#include "Security_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
e_ALARM_ERROR SEC_LowVti(void)
{
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
	e_DB_ALARMS_STATE AlarmLowVti = 	DB_AlarmStatusRead(ALARM_LOW_VTI_U16);
	UWORD16 AlarmDisconnection = 	DB_AlarmStatusRead(ALARM_DISCONNECTION_U16);
	UWORD16 ComputedVti = DB_ComputeRead(COMPUTED_VTI_U16);
	UWORD16 AdjustLowVti = DB_CurrentRead(ADJUST_LOW_VTI_U16);
	UWORD16 LowVtiNoSelect = DB_CurrentRead (LOW_VTI_NO_SELECT_U16);
    e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);

   	static UWORD16 MemoVentilState = VEN_VENTIL_DISABLE;
	static UWORD16 LVtiCmp = 0;
	static UWORD16 NoLVtiCmp= 0;


/*%C Check ALARM_LOW_VTI_U16 state 											  */
	switch(AlarmLowVti)
	{
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	case ALARM_FALSE :
/*%C 	if COMPUTED_VTI_U16 < ADJUST_LOW_VTI_U16 and  						  */
/*%C 	LOW_VTI_NO_SELECT_U16 = FALSE, then									  */
      if ( (ComputedVti < AdjustLowVti)
        && (LowVtiNoSelect == FALSE) )
      {
/*%C     ALARM_LOW_VTI_U16 = ALARM_DETECTED  								  */
         DB_AlarmStatusWrite(ALARM_LOW_VTI_U16,
									  ALARM_DETECTED);
/*%C     LVtiCmp counter reset 												  */
         LVtiCmp = 0;
      }
/*%	  End if 																  */
/*%C Alarm_Error = NO_ERR_AL 											      */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	case ALARM_DETECTED :

/*%C  If  LVtiCmp < 3 and NoLVtiCmp = 0, then 								  */
		if ( ( LVtiCmp < 3)
		  && (NoLVtiCmp == 0) )
		{
/*%C 		increase LVtiCmp counter 										  */
			LVtiCmp = LVtiCmp + 1;
/*%C 		Setting NoLVtiCmp to prohibe a new increment in the same cycle 	  */
			NoLVtiCmp = 1;
		}
/*%C  End if																  */

/*%C 	if COMPUTED_VTI_U16 >= ADJUST_LOW_VTI_U16 or  						  */
/*%C 	LOW_VTI_NO_SELECT_U16 = TRUE, then									  */
		if ( (ComputedVti >= AdjustLowVti)
		  || (LowVtiNoSelect == TRUE)
		  || (AlarmDisconnection >= ALARM_TRUE) )
		{
/*%C 		ALARM_LOW_VTI_U16 = ALARM_FALSE									  */
			DB_AlarmStatusWrite(ALARM_LOW_VTI_U16,
									  ALARM_FALSE);
/*%C		Priority register updating for buzzer and leds command 			  */
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xFFFD;
/*%C 		erazing of LVtiCmp cycles counter 								  */
		 	LVtiCmp = 0;
		}
/*%C 	Else if LVtiCmp = 3, then 											  */
		else if (LVtiCmp == 3)
		{
/*%C 		ALARM_LOW_VTI_U16 = ALARM_TRUE									  */
			DB_AlarmStatusWrite(ALARM_LOW_VTI_U16,
										ALARM_TRUE);
/*%C 		Storage of the associated event									  */
			DB_EventMngt(EVENT_AL_LOW_VTI);
/*%C		Priority register updating for buzzer and leds command 			  */
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 | 0x0002;
		}
/*%C 	End if 																  */
/*%C Alarm_Error = NO_ERR_AL 											      */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "TRUE" State						 	  */
/******************************************************************************/
	case ALARM_TRUE :
/*%C  The following state ,"ALARM_DISPLAYED", is written by HMI module. 	  */
/*%C  So there is no action to do.											  */
/*%C  Alarm_Error = NO_ERR_AL 											      */
		Alarm_Error = NO_ERR_AL;
		break;

/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	case ALARM_DISPLAYED	:
/*%C 	if COMPUTED_VTI_U16 >= ADJUST_LOW_VTI_U16 or  						  */
/*%C 	LOW_VTI_NO_SELECT_U16 = TRUE, then									  */
		if ( (ComputedVti >= AdjustLowVti)
		  || (LowVtiNoSelect == TRUE)
		  || (AlarmDisconnection >= ALARM_TRUE) )
		{
/*%C 		ALARM_LOW_VTI_U16 = ALARM_FALSE									  */
			DB_AlarmStatusWrite(ALARM_LOW_VTI_U16,
									  ALARM_FALSE);
/*%C		Priority register updating for buzzer and leds command 			  */
			SEC_Medium_Priority_1 = SEC_Medium_Priority_1 & 0xFFFD;
/*%C 		erazing of cycles counter LVtiCmp								  */
			LVtiCmp = 0;
/*%C 		Storage of the associeted event									  */
 			DB_EventMngt(EVENT_AL_END_OF_LOW_VTI);
 		}
/*%C Alarm_Error = NO_ERR_AL 											      */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C 	This alarm can't be canceled 										  */
/*%C Alarm_Error = ERR_AL_LOW_VTI 											  */
		Alarm_Error = ERR_AL_LOW_VTI;
		break;
/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	default:
/*%C Alarm_Error = ERR_AL_LOW_VTI 											  */
	  	Alarm_Error = ERR_AL_LOW_VTI;
		break;
	}
/*%C End of check alarm state 												  */
/*%C On inspiration to exhalation transition, continuous default flag reset:  */
/*%C If VENTIL_STATE_U16 = VEN_EXHALATION and 								  */
/*%C ( MemoVentilState = VEN_INSPIRATION_CONTROLED or						  */
/*%C MemoVentilState = VEN_INSPIRATION_TRIGGERED ), then 					  */	
	if	( (VentilState == VEN_EXHALATION )
	  && ( (MemoVentilState == VEN_INSPIRATION_CONTROLED)
		 || (MemoVentilState == VEN_INSPIRATION_TRIGGERED) ) )
	{
/*%C 	Freeing the flag NoLVtiCmp allowing to increase counter 			  */
		NoLVtiCmp = 0;
	}
/*%C End if 																  */
/*%C Updating MemoVentilState  the memory of ventil state 				  	  */
	MemoVentilState = VentilState ;

	return(Alarm_Error);
}


  