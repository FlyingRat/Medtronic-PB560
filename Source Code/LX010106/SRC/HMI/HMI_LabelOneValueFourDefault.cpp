/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueFourDefault.cpp  	    	           	 	  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage d'une valeur mais qui passe a "Non"	 						*/
/*%C ou autre pour un certaine valeur avec 4 flags paramétrables 					*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelOneValueFourDefault.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/



/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValueFourDefault::LabelOneValueFourDefault():LabelOneValueDefault()
{
   DefaultValue = 0;
   NameDefaultValue = NULL;
   DefaultValue1 = 0;
   NameDefaultValue1 = NULL;
   DefaultValue2 = 0;
   NameDefaultValue2 = NULL;
   DefaultValue3 = 0;
   NameDefaultValue3 = NULL;
   DisplayValue = FALSE;
   DisplayValue1 = FALSE;
   DisplayValue2 = FALSE;
   DisplayValue3 = FALSE;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelOneValueFourDefault::SetDefaultValue(UWORD16 _DefaultValue)
{
   DefaultValue = _DefaultValue;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueFourDefault::GetDefaultValue()
{
   return DefaultValue;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueFourDefault::SetNameDefaultValue(UBYTE** _NameDefaultValue)
{
   NameDefaultValue = _NameDefaultValue;
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelOneValueFourDefault::GetPtrNameDefaultValue()
{
   return NameDefaultValue;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValueFourDefault::GetNameDefaultValue()
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

void LabelOneValueFourDefault::SetDefaultValue1(UWORD16 _DefaultValue1)
{
   DefaultValue1 = _DefaultValue1;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueFourDefault::GetDefaultValue1()
{
   return DefaultValue1;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueFourDefault::SetNameDefaultValue1(UBYTE** _NameDefaultValue1)
{
   NameDefaultValue1 = _NameDefaultValue1;
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelOneValueFourDefault::GetPtrNameDefaultValue1()
{
   return NameDefaultValue1;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValueFourDefault::GetNameDefaultValue1()
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

void LabelOneValueFourDefault::SetDefaultValue2(UWORD16 _DefaultValue2)
{
   DefaultValue2 = _DefaultValue2;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueFourDefault::GetDefaultValue2()
{
   return DefaultValue2;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueFourDefault::SetNameDefaultValue2(UBYTE** _NameDefaultValue2)
{
   NameDefaultValue2 = _NameDefaultValue2;
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelOneValueFourDefault::GetPtrNameDefaultValue2()
{
   return NameDefaultValue2;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValueFourDefault::GetNameDefaultValue2()
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

void LabelOneValueFourDefault::SetDefaultValue3(UWORD16 _DefaultValue3)
{
   DefaultValue3 = _DefaultValue3;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValueFourDefault::GetDefaultValue3()
{
   return DefaultValue3;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueFourDefault::SetNameDefaultValue3(UBYTE** _NameDefaultValue3)
{
   NameDefaultValue3 = _NameDefaultValue3;
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelOneValueFourDefault::GetPtrNameDefaultValue3()
{
   return NameDefaultValue3;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValueFourDefault::GetNameDefaultValue3()
{
   if(NameDefaultValue3 != NULL)
   {
      return (NameDefaultValue3[GetLanguage()]);
   }
   else
	{
      return (UBYTE *)"???";
	}
}

/*----------------------------------------------------------------------------*/
void LabelOneValueFourDefault::SetValue1(UWORD16 _Value1)
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
   else if((GetDefaultValue3() == _Value1) && (NameDefaultValue3 != NULL))
   {
      DisplayValue3 = TRUE;
      SetValueIsString(TRUE);
      GetFValue1()->StoreValue(_Value1);
      GetFValue1()->SetText(GetNameDefaultValue3());
      if(GetLoupe() != NULL)
      {
         GetLoupe()->SetValue(GetNameDefaultValue3());
      }
   }
   else
   {
      DisplayValue = FALSE;
      DisplayValue1 = FALSE;
      DisplayValue2 = FALSE;
      DisplayValue3 = FALSE;
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
void LabelOneValueFourDefault::InitDefaultValue(  UBYTE** _NameDefaultValue,
                                                   UWORD16 _DefaultValue,
                                                   UBYTE** _NameDefaultValue1,
                                                   UWORD16 _DefaultValue1,
                                                   UBYTE** _NameDefaultValue2,
                                                   UWORD16 _DefaultValue2,
                                                   UBYTE** _NameDefaultValue3,
                                                   UWORD16 _DefaultValue3)
{
	/*%C Initialisation */
   NameDefaultValue = _NameDefaultValue;
   DefaultValue = _DefaultValue;
   NameDefaultValue1 = _NameDefaultValue1;
   DefaultValue1 = _DefaultValue1;
   NameDefaultValue2 = _NameDefaultValue2;
   DefaultValue2 = _DefaultValue2;
   NameDefaultValue3 = _NameDefaultValue3;
   DefaultValue3 = _DefaultValue3;
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
void LabelOneValueFourDefault::RefreshLanguage()
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
      else if (DisplayValue3 == TRUE)
		{
         GetFValue1()->SetTextOnly(GetNameDefaultValue3());
		}
   }
   LabelOneValue::RefreshLanguage();
}

