/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_GraphControl.cpp	                                 			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Gestion des graphique																      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_GraphControl.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/



/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
GraphControl::GraphControl()
{
   SetGraphTarget(NULL);
}
/*----------------------------------------------------------------------------*/
void GraphControl::Construct()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void GraphControl::SetGraphTarget(Graph* _GraphTarget)
{
   GraphTarget = _GraphTarget;
}
/*----------------------------------------------------------------------------*/
Graph* GraphControl::GetGraphTarget()
{
   return GraphTarget;
}
/*----------------------------------------------------------------------------*/
void GraphControl::SetRefreshTime(UWORD16 _RefreshTime)
{
   	_RefreshTime = _RefreshTime;
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}
/*----------------------------------------------------------------------------*/
UWORD16 GraphControl::GetRefreshTime()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	return(0);
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphControl::ManageGraph()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reset du graphique																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphControl::Reset()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Init du temps de refresh du graphique												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	RefreshTime																				*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphControl::InitRefreshTime(UWORD16 RefreshTime)
{
   	RefreshTime = RefreshTime;
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}
