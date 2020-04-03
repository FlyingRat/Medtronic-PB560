/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MenuObject.cpp 	   	      			 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet du menu															 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_MenuObject.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
MenuObject::MenuObject()
{
   SetIdParam(NO_ID);
   SetDbTarget(ADJUST);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void MenuObject::SetIdParam(UWORD16 _IdParam)
{
   IdParam = _IdParam;
}
/*----------------------------------------------------------------------------*/
UWORD16 MenuObject::GetIdParam()
{
   return IdParam;
}
/*----------------------------------------------------------------------------*/
void MenuObject::SetDbTarget(e_TYPE_OF_DB_TARGET _DbTarget)
{
   DbTarget = _DbTarget;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET MenuObject::GetDbTarget()
{
   return DbTarget;
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des paramettres d'acce a DB											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdParam : Id DB													               */
/*%I	   DbTarget : Target DB																 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MenuObject::InitDbAccess(UWORD16 _IdParam,
                              e_TYPE_OF_DB_TARGET _DbTarget)
{
   SetIdParam(_IdParam);
   SetDbTarget(_DbTarget);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C L'objet gagne le focus																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MenuObject::WinFocus()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C L'objet perd le focus																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MenuObject::LoseFocus()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MenuObject::StartModifMode()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MenuObject::StopModifMode()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Cancel de la modification de'un Objet												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MenuObject::CancelModifMode()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Modification de la valeur suivante													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MenuObject::ModifNextValue()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Increment de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MenuObject::IncreaseValue()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Decrement de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MenuObject::DecreaseValue()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Lock de l'Objet																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MenuObject::Lock(e_BOOL _Lock)
{
	/* Pour éviter les warnings */
	_Lock = _Lock;
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

