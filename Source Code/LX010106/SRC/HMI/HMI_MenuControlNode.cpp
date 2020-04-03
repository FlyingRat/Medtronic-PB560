/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MenuControlNode.cpp 	   	      	 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Noeud de l'arbre d'etat												 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_MenuControlNode.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                     	   */
/******************************************************************************/

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
MenuControlNode::MenuControlNode()
{
   Visible = TRUE;
   Lock = FALSE;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
e_BOOL MenuControlNode::IsValid()
{
   return (e_BOOL)(IsVisible() && !IsLock());
}
/*----------------------------------------------------------------------------*/
EventNode* MenuControlNode::GetEventNode()
{
   return Param;
}
/*----------------------------------------------------------------------------*/
void MenuControlNode::SetEventNode(EventNode* _Param)
{
   Param = _Param;
}
/*----------------------------------------------------------------------------*/
e_BOOL MenuControlNode::GetVisible()
{
   return Visible;
}
/*----------------------------------------------------------------------------*/
e_BOOL MenuControlNode::GetLock()
{
   return Lock;
}
/*----------------------------------------------------------------------------*/
void MenuControlNode::SetVisible(e_BOOL _Visible)
{
   Visible = _Visible;
   if(Visible)
   {
      GetObject()->Show();
   }
   else
   {
      GetObject()->Hide();
   }
}
/*----------------------------------------------------------------------------*/
void MenuControlNode::SetLock(e_BOOL _Lock)
{
   Lock = _Lock;
   GetObject()->Lock(_Lock);
}
/*----------------------------------------------------------------------------*/
e_BOOL MenuControlNode::IsVisible()
{
   return (e_BOOL)(Visible == TRUE);
}
/*----------------------------------------------------------------------------*/
e_BOOL MenuControlNode::IsLock()
{
   return (e_BOOL)(Lock == TRUE);
}
/*----------------------------------------------------------------------------*/
DisplayObject* MenuControlNode::GetObject()
{
   return Object;
}
/*----------------------------------------------------------------------------*/
void MenuControlNode::SetObject(DisplayObject *_Object)
{
   Object = _Object;
}


/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Visible : TRUE si visible										         		*/
/*%I		Lock : TRUE si lock											            		*/
/*%I		Object  : Objet Graphique du noeud							         		*/
/*%I		Param    : lien de deplacement												 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MenuControlNode::Init(e_BOOL _Visible,
                           e_BOOL _Lock,
                           DisplayObject *_Object,
                           EventNode* _Param)
{
	/* Pour éviter les warnings */
   	_Lock = _Lock;

   	SetObject(_Object);
	Visible = _Visible;
   	SetEventNode(_Param);
}



