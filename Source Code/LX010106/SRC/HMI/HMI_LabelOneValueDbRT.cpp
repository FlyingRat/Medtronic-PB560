/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueDbRT.cpp                            	 	  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + Text + sep + value+ unit) 	  			      	*/
/*%C   Permet d'ecrire en temps reel la valeur lors d'un   					  		*/
/*%C   increment ou decrement																	*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelOneValueDbRT.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValueDbRT::LabelOneValueDbRT():LabelOneValue()
{

}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Increment de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueDbRT::IncreaseValue()
{
   UWORD16 Value = GetValue1();

   /*%C Access to data base */
   if(IncreaseValueOk(&Value))
   {
      /*%C Maj Objet */
      SetValue1(Value);
      /*%C ecriture DB */
      Value = Value * GetDivider();
      DataBaseAccess::WriteValue(&Value,
      									GetIdParam(), 
      									GetDbTarget());
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decrement de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueDbRT::DecreaseValue()
{
   UWORD16 Value = GetValue1();

   /*%C Access to data base */
   if(DecreaseValueOk(&Value))
   {
      /*%C Maj Objet */
      SetValue1(Value);
      /*%C ecriture DB */
      Value = Value * GetDivider();
      DataBaseAccess::WriteValue(&Value,
      									GetIdParam(),
      									GetDbTarget());
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueDbRT::ConfirmModifValue(e_BOOL _Confirm)
{
   LabelOneValue::ConfirmModifValue(_Confirm);
	if(!_Confirm)
   {
      UWORD16 Value = GetValueTemp();
      Value = Value * GetDivider();
      DataBaseAccess::WriteValue(&Value, GetIdParam(), GetDbTarget());
   }
}
