/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabTwoValueDefault.cpp 	           	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	d'une valeur mais qui passe a "Non" ou 					*/
/*%C  autre pour un certaine valeur															*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelTabTwoValueDefault.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Tools.hpp"


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelTabTwoValueDefault::LabelTabTwoValueDefault():LabelTabTwoValue()
{
   DefaultValue1 = 0;
	NameDefaultValue1 = NULL;
	DefaultValue2 = 0;
	NameDefaultValue2 = NULL;
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelTabTwoValueDefault::SetDefaultValue1(UWORD16 _DefaultValue1)
{
   DefaultValue1 = _DefaultValue1;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabTwoValueDefault::GetDefaultValue1()
{
	return DefaultValue1;
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueDefault::SetNameDefaultValue1(UBYTE** _NameDefaultValue1)
{
   NameDefaultValue1 = _NameDefaultValue1;
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelTabTwoValueDefault::GetPtrNameDefaultValue1()
{
	return NameDefaultValue1;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTabTwoValueDefault::GetNameDefaultValue1()
{
	if(NameDefaultValue1 != NULL)
   {
		return (NameDefaultValue1[Label::GetLanguage()]);
	}
	else
	{
      return (UBYTE *)"???";
	}
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueDefault::SetDefaultValue2(UWORD16 _DefaultValue2)
{
   DefaultValue2 = _DefaultValue2;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabTwoValueDefault::GetDefaultValue2()
{
	return DefaultValue2;
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueDefault::SetNameDefaultValue2(UBYTE** _NameDefaultValue2)
{
   NameDefaultValue2 = _NameDefaultValue2;
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelTabTwoValueDefault::GetPtrNameDefaultValue2()
{
	return NameDefaultValue2;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTabTwoValueDefault::GetNameDefaultValue2()
{
	if(NameDefaultValue2 != NULL)
   {
		return (NameDefaultValue2[Label::GetLanguage()]);
	}
	else
	{
      return (UBYTE *)"???";
	}
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueDefault::SetValue1(UWORD16 _Value1)
{
	if((GetDefaultValue1() == _Value1) && 
		(NameDefaultValue1 != NULL))
   {
		SetValue1IsString(TRUE);
		
		GetFValue1()->SetText(GetNameDefaultValue1());
		GetFValue1()-> SetCol(FIRST_VALUE_COLUMN+
                     (COLUMN_WIDTH-
                     Tools::GetStringPixelSize
                     (GetNameDefaultValue1(),
                     GetFontValue1()))/2);

		GetFValue1()->StoreValue(_Value1);
		if(GetLoupe() != NULL)
      {
			GetLoupe()->SetValue(GetNameDefaultValue1());
		}
	}
   else
   {
		SetValue1IsString(FALSE);
		LabelTabOneValue::SetValue1(_Value1);
	}
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueDefault::SetValue2(UWORD16 _Value2)
{
   if((GetDefaultValue2() == _Value2) && (NameDefaultValue2 != NULL))
   {
		SetValue2IsString(TRUE);
		GetFValue2()-> SetCol(THIRD_VALUE_COLUMN+
                     (COLUMN_WIDTH-
                     Tools::GetStringPixelSize
                     (GetNameDefaultValue2(),
                     GetFontValue2()))/2);

      _Value2 = _Value2 / GetDivider();
		GetFValue2()->StoreValue(_Value2);
		GetFValue2()->SetText(GetNameDefaultValue2());
		if(GetLoupe() != NULL)
      {
			GetLoupe()->SetValue(GetNameDefaultValue2());
		}
	}
	else
   {
		SetValue2IsString(FALSE);
		LabelTabTwoValue::SetValue2(_Value2);
	}
}

/******************************************************************************/
/*                           METHODES                							      */
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NameDefaultValue1   : nom lorsque valeur1 par defaut 			   		*/
/*%I		DefaultValue1       : valeur1 par defaut						      		*/
/*%I		NameDefaultValue2   : nom lorsque valeur2 par defaut 		      		*/
/*%I		DefaultValue2       : valeur2 par defaut										*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValueDefault::InitDefaultValue( UBYTE** _NameDefaultValue1,
                                                UWORD16 _DefaultValue1,
                                                UBYTE** _NameDefaultValue2,
                                                UWORD16 _DefaultValue2)
{
   NameDefaultValue1 = _NameDefaultValue1;
	DefaultValue1 = _DefaultValue1;
	NameDefaultValue2 = _NameDefaultValue2;
	DefaultValue2 = _DefaultValue2;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Opperation de changement de la langue  de l'Objet								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValueDefault::RefreshLanguage()
{
	if(IsValue1IsString())
   {
      GetFValue1()-> SetCol(FIRST_VALUE_COLUMN+
                     (COLUMN_WIDTH-
                     Tools::GetStringPixelSize
                     (GetNameDefaultValue1(),
                     GetFontValue1()))/2);

		GetFValue1()->SetText(GetNameDefaultValue1());
   }
	if(IsValue2IsString())
   {
      GetFValue2()-> SetCol(THIRD_VALUE_COLUMN+
                     (COLUMN_WIDTH-
                     Tools::GetStringPixelSize
                     (GetNameDefaultValue2(),
                     GetFontValue2()))/2);

		GetFValue2()->SetText(GetNameDefaultValue2());
	}
	LabelTabTwoValue::RefreshLanguage();
}

