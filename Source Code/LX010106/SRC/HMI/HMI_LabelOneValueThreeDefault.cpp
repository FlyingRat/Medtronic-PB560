/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueThreeDefault.cpp  	    	           	 	  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage d'une valeur mais qui passe a "Non"	 						*/
/*%C ou autre pour un certaine valeur avec 3 flags paramétrables 					*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelOneValueThreeDefault.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/



/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValueThreeDefault::LabelOneValueThreeDefault():LabelOneValueDefault()
{
   DefaultValue = 0;
   NameDefaultValue = NULL;
   DefaultValue1 = 0;
   NameDefaultValue1 = NULL;
   DefaultValue2 = 0;
   NameDefaultValue2 = NULL;
   DisplayValue = FALSE;
   DisplayValue1 = FALSE;
   DisplayValue2 = FALSE;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelOneValueThreeDefault::SetDefaultValue(UWORD16 _DefaultValue)
{
   DefaultValue = _DefaultValue;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueThreeDefault::GetDefaultValue()
{
   return DefaultValue;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueThreeDefault::SetNameDefaultValue(UBYTE** _NameDefaultValue)
{
   NameDefaultValue = _NameDefaultValue;
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelOneValueThreeDefault::GetPtrNameDefaultValue()
{
   return NameDefaultValue;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValueThreeDefault::GetNameDefaultValue()
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

void LabelOneValueThreeDefault::SetDefaultValue1(UWORD16 _DefaultValue1)
{
   DefaultValue1 = _DefaultValue1;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueThreeDefault::GetDefaultValue1()
{
   return DefaultValue1;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueThreeDefault::SetNameDefaultValue1(UBYTE** _NameDefaultValue1)
{
   NameDefaultValue1 = _NameDefaultValue1;
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelOneValueThreeDefault::GetPtrNameDefaultValue1()
{
   return NameDefaultValue1;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValueThreeDefault::GetNameDefaultValue1()
{
   if(NameDefaultValue1 != NULL)
   {
      return (NameDefaultValue1[GetLanguage()]);
   }
   else
	{
      return (UBYTE *)"???";
	}
}
/*----------------------------------------------------------------------------*/

void LabelOneValueThreeDefault::SetDefaultValue2(UWORD16 _DefaultValue2)
{
   DefaultValue2 = _DefaultValue2;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueThreeDefault::GetDefaultValue2()
{
   return DefaultValue2;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueThreeDefault::SetNameDefaultValue2(UBYTE** _NameDefaultValue2)
{
   NameDefaultValue2 = _NameDefaultValue2;
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelOneValueThreeDefault::GetPtrNameDefaultValue2()
{
   return NameDefaultValue2;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValueThreeDefault::GetNameDefaultValue2()
{
   if(NameDefaultValue2 != NULL)
   {
      return (NameDefaultValue2[GetLanguage()]);
   }
   else
	{
      return (UBYTE *)"???";
	}
}

/*----------------------------------------------------------------------------*/
void LabelOneValueThreeDefault::SetValue1(UWORD16 _Value1)
{
   if((GetDefaultValue() == _Value1) && (NameDefaultValue != NULL))
   {
      DisplayValue = TRUE;
      SetValueIsString(TRUE);
      GetFValue1()->StoreValue(_Value1);
      GetFValue1()->SetText(GetNameDefaultValue());
      if(GetLoupe() != NULL)
      {
         GetLoupe()->SetValue(GetNameDefaultValue());
      }
   }
   else if((GetDefaultValue1() == _Value1) && (NameDefaultValue1 != NULL))
   {
      DisplayValue1 = TRUE;
      SetValueIsString(TRUE);
      GetFValue1()->StoreValue(_Value1);
      GetFValue1()->SetText(GetNameDefaultValue1());
      if(GetLoupe() != NULL)
      {
         GetLoupe()->SetValue(GetNameDefaultValue1());
      }
   }
   else if((GetDefaultValue2() == _Value1) && (NameDefaultValue2 != NULL))
   {
      DisplayValue2 = TRUE;
      SetValueIsString(TRUE);
      GetFValue1()->StoreValue(_Value1);
      GetFValue1()->SetText(GetNameDefaultValue2());
      if(GetLoupe() != NULL)
      {
         GetLoupe()->SetValue(GetNameDefaultValue2());
      }
   }
   else
   {
      DisplayValue = FALSE;
      DisplayValue1 = FALSE;
      DisplayValue2 = FALSE;
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
/*%I	  	NameDefaultValue   : nom lorsque valeur par defaut 				      */
/*%I		DefaultValue       : valeur par defaut								        	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueThreeDefault::InitDefaultValue(  UBYTE** _NameDefaultValue,
                                                   UWORD16 _DefaultValue,
                                                   UBYTE** _NameDefaultValue1,
                                                   UWORD16 _DefaultValue1,
                                                   UBYTE** _NameDefaultValue2,
                                                   UWORD16 _DefaultValue2)
{
	/*%C Initialisation */
   NameDefaultValue = _NameDefaultValue;
   DefaultValue = _DefaultValue;
   NameDefaultValue1 = _NameDefaultValue1;
   DefaultValue1 = _DefaultValue1;
   NameDefaultValue2 = _NameDefaultValue2;
   DefaultValue2 = _DefaultValue2;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Operation de changement de la langue de l'Objet  								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NameDefaultValue   : nom lorsque valeur par defaut 				      */
/*%I		DefaultValue       : valeur par defaut								        	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueThreeDefault::RefreshLanguage()
{
  	/* Change object languague */
   if(IsValueIsString() && !this->IsStopMonitoring())
   {
      if(DisplayValue == TRUE)
		{
         GetFValue1()->SetTextOnly(GetNameDefaultValue());
		}
      else if (DisplayValue1 == TRUE)
		{
         GetFValue1()->SetTextOnly(GetNameDefaultValue1());
		}
      else if (DisplayValue2 == TRUE)
		{
         GetFValue1()->SetTextOnly(GetNameDefaultValue2());
		}
   }
   LabelOneValue::RefreshLanguage();
}
