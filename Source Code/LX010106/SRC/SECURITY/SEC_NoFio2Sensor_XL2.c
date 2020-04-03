/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0104                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_NoFio2Sensor_XL2.c                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   It manages the NON detection of Fio2 sensor alarm	    	          */
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
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_KeyboardEvent.h"
#include "DB_Event.h"
#include "DB_AlarmStatus.h"
#include "Security_Datas.h"
#include "SEC_NoFio2Sensor.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


e_ALARM_ERROR SEC_NoFio2Sensor_XL2(void)
 {
/* Uncancel recovery from control base                                        */
	UWORD16 UncancelCmd = DB_ControlRead(UNCANCEL_CMD_U16);
	e_DB_ALARMS_STATE AlarmNoFio2Sensor = 
							DB_AlarmStatusRead(ALARM_NO_FIO2_SENSOR_U16);
  	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;
    UWORD16 DetectedFio2Sensor = 	DB_ControlRead(DETECTED_FIO2_SENSOR);
  	e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
	UWORD16 KeyboardDoublePulseInhibEvent =	
						DB_KeyboardEventRead(KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16);
  	UWORD16 AdjustmentInProgress = DB_ControlRead(ADJUSTMENT_IN_PROGRESS_U16);
	static e_VentilState MemoVentilState = VEN_VENTIL_DISABLE;
	static UWORD16 NoFio2SensorCpt = 0;
	static UWORD16 Fio2HighSelect = FALSE;
 	static UWORD16 Fio2LowSelect = FALSE;

	if(AdjustmentInProgress == FALSE)
	{
		Fio2HighSelect = DB_ConfigRead(FIO2_HIGH_SELECT);
		Fio2LowSelect =  DB_ConfigRead(FIO2_LOW_SELECT);
	}					 

   switch(AlarmNoFio2Sensor)
   {
/******************************************************************************/
/*%C	         					 "FALSE" State                            */
/******************************************************************************/
	   case ALARM_FALSE :
	   {
/*%C     If the Fio2 sensor is not detected and alarm on FiO2 is selected    */
  	if(((Fio2LowSelect == TRUE)
	|| (Fio2HighSelect == TRUE)) 
	&&(DetectedFio2Sensor == FALSE))

		{
/*%C     Alarm is turned to detected										 */
			DB_AlarmStatusWrite(ALARM_NO_FIO2_SENSOR_U16, ALARM_DETECTED);
		}
	else
		{
		 NoFio2SensorCpt = 0;
		}
	      Alarm_Error = NO_ERR_AL;
     	   break;
	   }
/******************************************************************************/
/*%C	         					 "DETECTED" State 					      */
/******************************************************************************/
	   case ALARM_DETECTED :
	   {
		  	if(((Fio2HighSelect == FALSE)
			&& (Fio2LowSelect == FALSE))
	  		|| (DetectedFio2Sensor == TRUE))
		   {
/*%C        Alarm is turned to False */
	     	   DB_AlarmStatusWrite(ALARM_NO_FIO2_SENSOR_U16,ALARM_FALSE);
			   NoFio2SensorCpt = 0;
	      }
			else 
			{
				if(( VentilState != VEN_EXHALATION)
				&&(	MemoVentilState == VEN_EXHALATION)
				)
				{
					NoFio2SensorCpt = NoFio2SensorCpt +1;
				}
	
	
	/*%C     When the detection cycle number is reached */
		     	if (NoFio2SensorCpt == 2)   
		      	{
	/*%C        Alarm is turned to TRUE, the priority register is Up dated,*/
	/*%C        the associated event is stored */
			      	DB_AlarmStatusWrite(ALARM_NO_FIO2_SENSOR_U16,ALARM_TRUE);
			      	DB_EventMngt(EVENT_AL_NO_FIO2_SENSOR );
		      		SEC_High_Priority_2= SEC_High_Priority_2| 0x0008;
						NoFio2SensorCpt = 0;
		      	}
	    	} 
		  Alarm_Error = NO_ERR_AL;
	      break;
		}
/******************************************************************************/
/*%C	         					 "TRUE" State						 	  */
/******************************************************************************/
	   case ALARM_TRUE :
	   {
	 /*%C     The following state ,"ALARM_DISPLAYED", is written by HMI module. */
/*%C     So there is no action to do .*/
	      Alarm_Error = NO_ERR_AL;
	      break;
		}
/******************************************************************************/
/*%C	         					 "DISPLAYED" State                        */
/******************************************************************************/
	   case ALARM_DISPLAYED	:
	   {
	  	if(((Fio2HighSelect == FALSE)
		&& (Fio2LowSelect == FALSE))
  		|| (DetectedFio2Sensor == TRUE))
   	      {
/*%C        Alarm is turned to False */
	     	DB_AlarmStatusWrite(ALARM_NO_FIO2_SENSOR_U16, ALARM_FALSE);
			NoFio2SensorCpt = 0;
			SEC_High_Priority_2= SEC_High_Priority_2 & 0xFFF7;
/*%C        The event of end of alarm is stored */
		    DB_EventMngt(EVENT_AL_END_OF_NO_FIO2_SENSOR);
	      }
/*%C Else if KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16 = TRUE, then 			  */
	else if (KeyboardDoublePulseInhibEvent == TRUE)
 		{
	      DB_AlarmStatusWrite(ALARM_NO_FIO2_SENSOR_U16,
	      						  ALARM_CANCELED);
/*%C  	Priority register updating for buzzer and leds command */
			SEC_High_Priority_2= SEC_High_Priority_2 & 0xFFF7;
		}
      	Alarm_Error = NO_ERR_AL;
	  	break;
		}
/******************************************************************************/
/*%C	         					 "CANCELED" State                         */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C 	when sensor detected or alarm FiO2 unselected						 */
	  	if(((Fio2HighSelect == FALSE)
		&& (Fio2LowSelect == FALSE))
  		|| (DetectedFio2Sensor == TRUE))
		{
/*%C 		Alarm is turned to false and stored with associated event */
			DB_AlarmStatusWrite(ALARM_NO_FIO2_SENSOR_U16, ALARM_FALSE);
		  	DB_EventMngt(EVENT_AL_END_OF_NO_FIO2_SENSOR);
		}
		/******************************************************************/
		/*		 				Reset of the "CANCELED" State             */
		/******************************************************************/
				 
/*%C 	If a command of inhibition of the cancel, is true, */
/*%C 	then the alarm is set to TRUE */
		else if(UncancelCmd == TRUE)
		{
/*%C 		Storage of True state of the alarm*/
/*%C 		Up dating of priority register for leds & buzzer */
	   	DB_AlarmStatusWrite(ALARM_NO_FIO2_SENSOR_U16,
	   							  ALARM_TRUE);
/*%C  	Priority register updating for buzzer and leds command */
	      SEC_High_Priority_2= SEC_High_Priority_2| 0x0008;
		}
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C	         					 DEFAULT                                  */
/******************************************************************************/
	   default:
 	       Alarm_Error = ERR_AL_NO_FIO2_SENSOR;
		   break;
	   }
    MemoVentilState = VentilState ;
	return(Alarm_Error);
}

