/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueDefault.cpp  	                    	 	  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	d'une valeur mais qui passe a	"Non" 						*/
/*%C ou autre pour une certaine valeur														*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelOneValueDefault.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/




/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValueDefault::LabelOneValueDefault():LabelOneValue()
{
   DefaultValue = 0;
   NameDefaultValue = NULL;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelOneValueDefault::SetDefaultValue(UWORD16 _DefaultValue)
{
   DefaultValue = _DefaultValue;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueDefault::GetDefaultValue()
{
   return DefaultValue;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueDefault::SetNameDefaultValue(UBYTE** _NameDefaultValue)
{
   NameDefaultValue = _NameDefaultValue;
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelOneValueDefault::GetPtrNameDefaultValue()
{
   return NameDefaultValue;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValueDefault::GetNameDefaultValue()
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
void LabelOneValueDefault::SetValue1(UWORD16 _Value1)
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
      _Value1 = _Value1 / GetDivider();
      LabelOneValue::SetValue1(_Value1);
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
/*%I		DefaultValue       : valeur par defaut			               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueDefault::InitDefaultValue( UBYTE** _NameDefaultValue,
                                             UWORD16 _DefaultValue)
{
   /*%C Initialisation */
   NameDefaultValue = _NameDefaultValue;
   DefaultValue = _DefaultValue;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE		             																*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueDefault::RefreshLanguage()
{
   if(IsValueIsString() && !IsStopMonitoring())
   {
      GetFValue1()->SetTextOnly(GetNameDefaultValue());
   }
   LabelOneValue::RefreshLanguage();
}
