/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_EditableObject.cpp                                  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet Modifiable par l'utilisateur											      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_EditableObject.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   	   */
/******************************************************************************/

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR      						   */
/******************************************************************************/
EditableObject::EditableObject():Label()
{

}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void EditableObject::SetValueTemp(UWORD16 _ValueTemp)
{
   ValueTemp = _ValueTemp;
}
/*----------------------------------------------------------------------------*/
UWORD16 EditableObject::GetValueTemp()
{
   return ValueTemp;
}
/*----------------------------------------------------------------------------*/
void EditableObject::SetValueFlagTemp(UWORD16 _ValueFlagTemp)
{
   ValueFlagTemp = _ValueFlagTemp;
}
/*----------------------------------------------------------------------------*/
UWORD16 EditableObject::GetValueFlagTemp()
{
   return ValueFlagTemp;
}
/*----------------------------------------------------------------------------*/
void EditableObject::SetIdFlagTemp(UWORD16 _IdFlagTemp)
{
   IdFlagTemp = _IdFlagTemp;
}
/*----------------------------------------------------------------------------*/
UWORD16 EditableObject::GetIdFlagTemp()
{
   return IdFlagTemp;
}
/*----------------------------------------------------------------------------*/
void EditableObject::SetDbIdFlagTemp(e_TYPE_OF_DB_TARGET _DbIdFlagTemp)
{
   DbIdFlagTemp = _DbIdFlagTemp;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET EditableObject::GetDbIdFlagTemp()
{
   return DbIdFlagTemp;
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirmation de modification de la valeur											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Confirm : TRUE si confirme															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void EditableObject::ConfirmModifValue(e_BOOL _Confirm)
{
	/* Pour éviter les warnings */
	_Confirm = _Confirm;
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */	
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void EditableObject::StopModifMode()
{
   /*%C Stop of the modification of an Object */
   Label::StopModifMode();
   ConfirmModifValue(TRUE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Cancel de la modification de'un Objet												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void EditableObject::CancelModifMode()
{
	/*%C Cancel the modification of an Object */
   Label::CancelModifMode();
   ConfirmModifValue(FALSE);
}
