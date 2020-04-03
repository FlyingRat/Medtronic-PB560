/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_KeyboardEventCppC.cpp                               	 		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Interface between IHM Timers Managt and Driver of Counters			      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "typedef.h"

#include "HMI_Controller.hpp"
#include "HMI_DataBaseAccess.hpp"

extern "C"
{
#include "DB_KeyboardEvent.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/


extern "C" void HMI_KeyboardEventLaunch()
{
UWORD16 _Value;
UWORD16 _BackLightOff;

	/*%C Detect all events */
	for (UWORD16 i = 0;i < end_of_db_Keyboard_Event_table;i++)
	{

		/*%C Read DataBase Keyboard */
		DataBaseAccess::ReadValue(&_Value, i, KEYBOARD);

		/*%C Event active ? */
  		if (_Value == TRUE)
		{
			/*%C Read Backlight Flag */
			DataBaseAccess::ReadValue(&_BackLightOff, BACKLIGHT_OFF_U16, CONTROL);
			/*%C Launch HMI only if Backlight On - else Switch On Backlight */
			if (_BackLightOff == FALSE)
			{
				Controller::GetInstance()->ManageKeyboardEvent(i);
			}
			else
			{				
				/*%C Ventilation button bypasses the normal functioning (activates the HMI handler
				     _AND_ activates the backlight */
				if ((i == KEYBOARD_START_VENTIL_DOWN_EVENT_U16) ||
			        (i == KEYBOARD_START_VENTIL_UP_EVENT_U16) ||
				    (i == KEYBOARD_STOP_VENTIL_EVENT_U16) ||
				    (i == KEYBOARD_CONFIRM_STOP_VENTIL_EVENT_U16) )
						Controller::GetInstance()->ManageKeyboardEvent(i);					

				/*%C Reset Backlight flag */
				_Value = FALSE;
				DataBaseAccess::WriteValue(&_Value, BACKLIGHT_OFF_U16, CONTROL);
			}

			/*%C Reset Event flag */
			_Value = FALSE;
			DataBaseAccess::WriteValue(&_Value, i, KEYBOARD);

			/*%C Set Key_Event flag */
			_Value = TRUE;
			DataBaseAccess::WriteValue(&_Value, KEY_EVENT_U16, CONTROL);
		}
	}
}



