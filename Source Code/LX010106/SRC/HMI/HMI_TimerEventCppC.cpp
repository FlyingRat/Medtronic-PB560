/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_TimerEventCppC.cpp								 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Interface between IHM Timers Management and Driver of Counters 			  	*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_TimerEventCppC.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/
extern "C"
{
#include "typedef.h"
#include "DB_Config.h"
}



#include "HMI_InterfaceCppC.hpp"
#include "HMI_Controller.hpp"
#include "HMI_DatabaseAccess.hpp"
#include "DB_KeyboardEvent.h"


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/

#ifndef _BORLAND

extern "C" void IHM_TimerEventLauch(void)
{
	static UWORD16 DecounterIdPreviousStop=0;
	UWORD16 DecounterId;

	for ( DecounterId=DecounterIdPreviousStop ;
         DecounterId<end_of_minute_ihm_table_decnt ;
         DecounterId++)
	{
      if (  TIM_TestMinuteDecounterActivateOk(
            (e_TIM_MINUTE_TABLE_ID)DecounterId) == TRUE)
		{
         /*%C Counter expired, Stop and Call Ihm Controller action */
			if (	TIM_TestMinuteOverflowOk(
					(e_TIM_MINUTE_TABLE_ID)DecounterId) == TRUE)
			{
				Controller::GetInstance()->
								ManageTimerEvent(DecounterId);
				DecounterIdPreviousStop = DecounterId;
				return;
			}
		}
	}
	if (DecounterIdPreviousStop != 0)
	{
		for (DecounterId=0 ;DecounterId<DecounterIdPreviousStop ;DecounterId++)
		{
			if (	TIM_TestMinuteDecounterActivateOk(
					(e_TIM_MINUTE_TABLE_ID)DecounterId) == TRUE)
			{
            /*%C Counter expired, Stop and Call Ihm Controller action */
				if (	TIM_TestMinuteOverflowOk(
						(e_TIM_MINUTE_TABLE_ID)DecounterId) == TRUE)
				{
					Controller::GetInstance()->
									ManageTimerEvent(DecounterId);

					DecounterIdPreviousStop = DecounterId;
					return;
				}
			}
		}
	}
}
#endif
// Fonction de constructeur des objets à appeler lors de la phase init systeme

extern "C" void SETUP_HMI_Start(void)
{
		Controller::GetInstance()->ManageKeyboardEvent(KEYBOARD_INHIB_IT_GEN_EVENT_ARRAY_U16);
}

extern "C" void CIRCUIT_CHECK_HMI_Start(void)
{
		Controller::GetInstance()->ManageKeyboardEvent(KEYBOARD_NAVIG_IT_GEN_EVENT_U16);
}

extern "C" void VENTILATION_HMI_Start(void)
{
		Controller::GetInstance()->ManageKeyboardEvent(KEYBOARD_IT_GEN_EVENT_U16);
}
