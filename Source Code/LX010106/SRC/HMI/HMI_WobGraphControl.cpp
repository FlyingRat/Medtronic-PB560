/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_WobGraphControl.cpp                  	 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C   Synchronisation des phases inspiratoires pour le WOB	  						*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/
#include "HMI_WobGraphControl.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/
#include "HMI_DataBaseAccess.hpp"
extern "C"
{
#include "enum.h"
#include "DB_Control.h"
}
/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/

WobGraphControl::WobGraphControl()
{
   Init();
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation : Pas de ventilation													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void WobGraphControl::Init()
{
   VentilState = VEN_VENTIL_DISABLE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion de la synchronisation des phases inspiratoires							*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void WobGraphControl::ManageGraph()
{
	/*%C Reading of the selected graph */
	Graph *GraphTarget = GetGraphTarget();

   /*%C Reading of the state ventil in DataBase */
	UWORD16 Value;
	DataBaseAccess::ReadValue(&Value, VENTIL_STATE_U16, CONTROL);
	e_VentilState CurrentMode = (e_VentilState)Value;

	/* if VentilState swtich to inspiration then Reset the selected graph */
	if((VentilState == VEN_EXHALATION) &&
		((CurrentMode == VEN_INSPIRATION_CONTROLED)||
		(CurrentMode == VEN_INSPIRATION_TRIGGERED)))
   {
		GraphTarget->Reset();
   }

	/* VentilSate Update */
	VentilState = CurrentMode;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reset de l'objet : Pas de ventilation												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void WobGraphControl::Reset()
{
   VentilState = VEN_VENTIL_DISABLE;
}
