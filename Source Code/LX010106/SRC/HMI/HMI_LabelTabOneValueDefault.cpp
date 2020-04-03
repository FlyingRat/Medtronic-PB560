/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabOneValueDefault.cpp 	  	           	 	  				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	d'une valeur mais qui passe a	"Non" ou 					*/
/*%C  autre pour un certaine valeur															*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelTabOneValueDefault.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/



/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelTabOneValueDefault::LabelTabOneValueDefault():LabelTabOneValue()
{
   DefaultValue1 = 0;
   NameDefaultValue1 = NULL;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelTabOneValueDefault::SetDefaultValue1(UWORD16 _DefaultValue1)
{
   DefaultValue1 = _DefaultValue1;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabOneValueDefault::GetDefaultValue1()
{
   return DefaultValue1;
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValueDefault::SetNameDefaultValue1(UBYTE** _NameDefaultValue1)
{
   NameDefaultValue1 = _NameDefaultValue1;
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelTabOneValueDefault::GetPtrNameDefaultValue1()
{
   return NameDefaultValue1;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTabOneValueDefault::GetNameDefaultValue1()
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
void LabelTabOneValueDefault::SetValue1(UWORD16 _Value1)
{
	if((GetDefaultValue1() == _Value1) && (NameDefaultValue1 != NULL))
   {
		SetValue1IsString(TRUE);
		UWORD16 col = IsValue1Maxi() ? THIRD_VALUE_COLUMN : FIRST_VALUE_COLUMN;

		GetFValue1()->SetText(GetNameDefaultValue1());
		GetFValue1()-> SetCol(	col+
										(COLUMN_WIDTH-Tools::GetStringPixelSize
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


/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NameDefaultValue1   : nom lorsque valeur1 par defaut 			   		*/
/*%I		DefaultValue1       : valeur1 par defaut										*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValueDefault::InitDefaultValue( UBYTE** _NameDefaultValue1,
                                                UWORD16 _DefaultValue1)
{
   NameDefaultValue1 = _NameDefaultValue1;
   DefaultValue1 = _DefaultValue1;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Opperation de changement de la langue  de l'Objet								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValueDefault::RefreshLanguage()
{
   if(IsValue1IsString())
   {
      UWORD16 col = IsValue1Maxi() ? THIRD_VALUE_COLUMN : FIRST_VALUE_COLUMN;

      GetFValue1()-> SetCol(	col+
      								(COLUMN_WIDTH-
      								Tools::GetStringPixelSize
                     			(GetNameDefaultValue1(),
                     			GetFontValue1()))/2);

      GetFValue1()->SetTextOnly(GetNameDefaultValue1());
   }
   LabelTabOneValue::RefreshLanguage();
}

