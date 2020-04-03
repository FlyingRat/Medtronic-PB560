/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ParamNode.cpp 	   	      			 	  		 				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Node parameters															 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_ParamNode.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
ParamNode::ParamNode()
{

}
/*----------------------------------------------------------------------------*/
ParamNode::ParamNode(UWORD16 _Id,
                     Controller::PController _OnButtonUp,
                     Controller::PController _OnButtonDown,
                     Controller::PController _OnTimeOut,
                     Controller::PController _OnButtonValid,
                     Controller::PController _OnButtonRefresh,
                     Controller::PController _OnButtonLongValid)
{
   SetOnButtonUp(_OnButtonUp);
   SetOnButtonDown(_OnButtonDown);
   SetOnTimeOut(_OnTimeOut);
   SetOnButtonValid(_OnButtonValid);
   SetOnButtonRefresh(_OnButtonRefresh);
   SetOnButtonLongValid(_OnButtonLongValid);
   SetId(_Id);
}
/*----------------------------------------------------------------------------*/
void ParamNode::SetOnButtonUp(Controller::PController _OnButtonUp)
{
   OnButtonUp = _OnButtonUp;
}
/*----------------------------------------------------------------------------*/
void ParamNode::SetOnButtonDown(Controller::PController _OnButtonDown)
{
   OnButtonDown = _OnButtonDown;
}
/*----------------------------------------------------------------------------*/
void ParamNode::SetOnTimeOut(Controller::PController _OnTimeOut)
{
   OnTimeOut = _OnTimeOut;
}
/*----------------------------------------------------------------------------*/
void ParamNode::SetOnButtonValid(Controller::PController _OnButtonValid)
{
   OnButtonValid = _OnButtonValid;
}
/*----------------------------------------------------------------------------*/
void ParamNode::SetOnButtonRefresh(Controller::PController _OnButtonRefresh)
{
   OnButtonRefresh= _OnButtonRefresh;
}
/*----------------------------------------------------------------------------*/
void ParamNode::SetOnButtonLongValid(Controller::PController _OnButtonLongValid)
{
   OnButtonLongValid = _OnButtonLongValid;
}
/*----------------------------------------------------------------------------*/
UWORD16 ParamNode::GetId() const
{
   return Id;
}
/*----------------------------------------------------------------------------*/
void ParamNode::SetId(UWORD16 _Id)
{
   Id = _Id;
}
/*----------------------------------------------------------------------------*/
