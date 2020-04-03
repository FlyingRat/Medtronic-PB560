/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_VTimer.cpp                           	 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C   Objet d'interface Timer				   					  						*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/
#include "HMI_VTimer.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/
#include "HMI_Controller.hpp"
#include "HMI_TimerEventCppC.hpp"
/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
VTimer::VTimer()
{

}
 
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Lancement d'un timer																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Delay : Chargement du timer en ms												*/
/*%I		Event : evenement à générer à expiration du compteur						*/
/*%I		AutoReload : si TRUE rechargement du timer à expiration du compteur	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTimer::StartTimer(UWORD32 _Delay, 
								UWORD16 _Event, 
								e_BOOL _AutoReload)
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

	/*%C Start the minute decounter */
	TIM_StartMinuteDecounter(( e_TIM_MINUTE_TABLE_ID)_Event,
                              _Delay,_AutoReload);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arrêt d'un timer																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Event : evenement à générer à expiration du compteur						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTimer::StopTimer(UWORD16 _Event)
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

	/*%C Stop the minute decounter */
	TIM_StopMinuteDecounter((e_TIM_MINUTE_TABLE_ID)_Event);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Annulation de tous les timers															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTimer::RemoveAll(void)
{
	UWORD16 DecounterId;

	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

	/*%C Stop all the timer of the minute decounter list */
   	for(DecounterId = 0; DecounterId< end_of_minute_ihm_table_decnt; 
   	DecounterId++)
	{
		/*%C Stop the minute decounter */
   		TIM_StopMinuteDecounter((e_TIM_MINUTE_TABLE_ID)DecounterId);
 	}
}
