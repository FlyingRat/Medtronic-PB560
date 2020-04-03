/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueSignDefault.cpp  	                 	 	  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage d'une valeur mais qui passe a "Non"	 						*/
/*%C ou autre pour une certaine valeur														*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelOneValueSignDefault.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/



/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValueSignDefault::LabelOneValueSignDefault():LabelOneValueSign()
{
   DefaultValue = 0;
   NameDefaultValue = NULL;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
//---------------------------------------------------------------------------
void LabelOneValueSignDefault::SetDefaultValue(UWORD16 _DefaultValue)
{
   DefaultValue = _DefaultValue;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueSignDefault::GetDefaultValue()
{
   return DefaultValue;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueSignDefault::SetNameDefaultValue(UBYTE** _NameDefaultValue)
{
   NameDefaultValue = _NameDefaultValue;
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelOneValueSignDefault::GetPtrNameDefaultValue()
{
   return NameDefaultValue;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValueSignDefault::GetNameDefaultValue()
{
   if(NameDefaultValue != NULL)
   {
      return (NameDefaultValue[GetLanguage()]);
   }
   else
	{
      return (UBYTE *)"???";
	}
}
/*----------------------------------------------------------------------------*/
void LabelOneValueSignDefault::SetValue1(UWORD16 _Value1)
{
   if((GetDefaultValue() == _Value1) && (NameDefaultValue != NULL))
   {
      SetValueIsString(TRUE);
      GetFValue1()->StoreValue(_Value1);
      GetFValue1()->SetText(GetNameDefaultValue());
      if(GetLoupe() != NULL)
      {
         GetLoupe()->SetValue(GetNameDefaultValue());
      }
   }
   else
   {
      SetValueIsString(FALSE);
      LabelOneValueSign::SetValue1(_Value1);
   }
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
/*%I	  	NameDefaultValue   : nom lorsque valeur par defaut 			      	*/
/*%I		DefaultValue       : valeur par defaut							         	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueSignDefault::InitDefaultValue(UBYTE** _NameDefaultValue,
                                                UWORD16 _DefaultValue)
{
	/*%C Initialisation */
   NameDefaultValue = _NameDefaultValue;
   DefaultValue = _DefaultValue;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Opperation de changement de la langue de l'Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																 			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueSignDefault::RefreshLanguage()
{
   if(IsValueIsString() && !IsStopMonitoring())
   {
      GetFValue1()->SetTextOnly(GetNameDefaultValue());
   }
   LabelOneValueSign::RefreshLanguage();
}

