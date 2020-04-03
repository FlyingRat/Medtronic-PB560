/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Backlight_Mngt.c                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Backlight management                                           */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/

#ifndef _TASKING         
#include "LH_ST10F276.h" 
#include <intrins.h>     
#else                    
#include "regf276e.h"    
#endif                   	
#include "io_declare.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_KeyboardEvent.h"
#include "Timer_Data.h"
#include "SYS_Backlight_Mngt.h"
#include "System_Datas.h"



/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

/*%C If the screen saver is OFF, the backlight command is always activated.	*/
/*%C If the screen saver is ON, the backlight command is activated 				*/
/*%C   - if a keypress is detected,															*/
/*%C   - if an alarm is detected, 															*/
/*%C and this during one minute after the condition vanishing.						*/

void SYS_Backlight_Mngt(void)
{
	UWORD16 Timer_Decounter_Value = 0;
	UWORD16 Alarm_Detected = DB_ControlRead(ALARM_DETECTED_U16);
	UWORD16 Adjust_Back_Light = DB_ConfigRead(ADJUST_BACKLIGHT_U16);
	UWORD16 Key_Event = DB_ControlRead(KEY_EVENT_U16);
	UWORD16 End_Of_Operation = DB_ControlRead(END_OF_OPERATION_U16);

	if (Adjust_Back_Light == FALSE)
	{
		if ( (Alarm_Detected == TRUE)
	  	  || (Key_Event == TRUE)
		  || (End_Of_Operation == TRUE))	
		{
	   	TIM_StartDecounter(SYS_TIME_BACKLIGHT,
	                      	 TIME_BACKLIGHT);
			/*%C Flag RAZ */
			if (Key_Event == TRUE)
			{
				DB_ControlWrite(KEY_EVENT_U16, FALSE);
			}
			if (End_Of_Operation == TRUE)
			{
				DB_ControlWrite(END_OF_OPERATION_U16, FALSE);
			}
		}

   		Timer_Decounter_Value = TIM_ReadDecounterValue(SYS_TIME_BACKLIGHT);

		if (Timer_Decounter_Value == 0)
		{
 	  		DIS_Backlight(WEAK);
			DB_ControlWrite(BACKLIGHT_OFF_U16, TRUE);
		}
		else
		{
 	  		DIS_Backlight(SWITCH_ON);
			DB_ControlWrite(BACKLIGHT_OFF_U16, FALSE);
		}
	}
	else
	{
 	  	DIS_Backlight(SWITCH_ON);
		DB_ControlWrite(BACKLIGHT_OFF_U16, FALSE);
	}
}

