/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMU_EventNode.cpp   		                                			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Contient les liens entre les noeuds de l'arbre							      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_EventNode.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
EventNode::EventNode()
{

}

/******************************************************************************/
/*                           ACCESSEURS				                				*/
/******************************************************************************/
void EventNode::SetOnButtonUp(Controller::PController _OnButtonUp)
{
	OnButtonUp = _OnButtonUp;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetOnButtonDown(Controller::PController _OnButtonDown)
{
	OnButtonDown = _OnButtonDown;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetOnTimeOut(Controller::PController _OnTimeOut)
{
	OnTimeOut = _OnTimeOut;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetOnButtonValid(Controller::PController _OnButtonValid)
{
	OnButtonValid = _OnButtonValid;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetOnButtonMonitor(Controller::PController _OnButtonMonitor)
{
	OnButtonMonitor = _OnButtonMonitor;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetOnButtonLongValid(Controller::PController _OnButtonLongValid)
{
	OnButtonLongValid = _OnButtonLongValid;
}
/*----------------------------------------------------------------------------*/
UWORD16 EventNode::GetId() const
{
	return Id;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetId(UWORD16 _Id)
{
	Id = _Id;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetLinkedMenuControlNodeId(UWORD16 _Id)
{
	LinkedMenuControlNodeId = _Id;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetIdNodeOnUp(UWORD16 _IdNodeOnUp)
{
	IdNodeOnUp = _IdNodeOnUp;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetIdNodeOnDown(UWORD16 _IdNodeOnDown)
{
	IdNodeOnDown = _IdNodeOnDown;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetIdNodeOnTimeOut(UWORD16 _IdNodeOnTimeOut)
{
	IdNodeOnTimeOut = _IdNodeOnTimeOut;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetIdNodeOnValid(UWORD16 _IdNodeOnValid)
{
	IdNodeOnValid = _IdNodeOnValid;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetIdNodeOnLongValid(UWORD16 _IdNodeOnLongValid)
{
	IdNodeOnLongValid = _IdNodeOnLongValid;
}
/*----------------------------------------------------------------------------*/
void EventNode::SetIdNodeOnMonitor(UWORD16 _IdNodeOnMonitor)
{
	IdNodeOnMonitor = _IdNodeOnMonitor;
}
/*----------------------------------------------------------------------------*/
UWORD16 EventNode::GetLinkedMenuControlNodeId() const
{
	return LinkedMenuControlNodeId;
}
/*----------------------------------------------------------------------------*/

UWORD16 EventNode::GetIdNodeOnUp() const
{
	return IdNodeOnUp;
}
/*----------------------------------------------------------------------------*/
UWORD16 EventNode::GetIdNodeOnDown() const
{
	return IdNodeOnDown;
}
/*----------------------------------------------------------------------------*/
UWORD16 EventNode::GetIdNodeOnTimeOut() const
{
	return IdNodeOnTimeOut;
}
/*----------------------------------------------------------------------------*/
UWORD16 EventNode::GetIdNodeOnValid() const
{
	return IdNodeOnValid;
}
/*----------------------------------------------------------------------------*/
UWORD16 EventNode::GetIdNodeOnLongValid() const
{
	return IdNodeOnLongValid;
}
/*----------------------------------------------------------------------------*/
UWORD16 EventNode::GetIdNodeOnMonitor() const
{
	return IdNodeOnMonitor;
}

/******************************************************************************/
/*                           METHODES                									*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		OnButtonUp        : Methode a appeler sur un UP								*/
/*%I		OnButtonDown      : Methode a appeler sur un DOWN						  	*/
/*%I		OnTimeOut         : Methode a appeler sur un TIMEOUT     				*/
/*%I		OnButtonValid     : Methode a appeler sur un VALID							*/
/*%I		OnButtonMonitor   : Methode a appeler sur un MONITOR						*/
/*%I		OnButtonLongValid : Methode a appeler sur un LONG VALID					*/
/*%I		IdNodeOnUp        : Id du noeud destination sur un UP						*/
/*%I		IdNodeOnDown      : Id du noeud destination sur un DOWN					*/
/*%I		IdNodeOnTimeOut   : Id du noeud destination sur un TIMEOUT				*/
/*%I		IdNodeOnValid     : Id du noeud destination sur un VALID					*/
/*%I		IdNodeOnMonitor   : Id du noeud destination sur un MONITOR				*/
/*%I		IdNodeOnLongValid : Id du noeud destination sur un LONG VALID 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void EventNode::Init(UWORD16 _Id,
                     UWORD16 _LinkedMenuControlNodeId,
                		Controller::PController _OnButtonUp,
                		Controller::PController _OnButtonDown,
                		Controller::PController _OnTimeOut,
                		Controller::PController _OnButtonValid,
                		Controller::PController _OnButtonMonitor,
                		Controller::PController _OnButtonLongValid,
                		UWORD16 _IdNodeOnUp,
                		UWORD16 _IdNodeOnDown,
                		UWORD16 _IdNodeOnTimeOut,
                		UWORD16 _IdNodeOnValid,
                		UWORD16 _IdNodeOnMonitor,
                		UWORD16 _IdNodeOnLongValid)
{
	SetOnButtonUp(_OnButtonUp);
   SetOnButtonDown(_OnButtonDown);
   SetOnTimeOut(_OnTimeOut);
   SetOnButtonValid(_OnButtonValid);
   SetOnButtonMonitor(_OnButtonMonitor);
   SetOnButtonLongValid(_OnButtonLongValid);
   SetId(_Id);
   SetLinkedMenuControlNodeId(_LinkedMenuControlNodeId);
   SetIdNodeOnUp(_IdNodeOnUp);
   SetIdNodeOnDown(_IdNodeOnDown);
   SetIdNodeOnTimeOut(_IdNodeOnTimeOut);
   SetIdNodeOnValid(_IdNodeOnValid);
   SetIdNodeOnLongValid(_IdNodeOnLongValid);
   SetIdNodeOnMonitor(_IdNodeOnMonitor);
}

