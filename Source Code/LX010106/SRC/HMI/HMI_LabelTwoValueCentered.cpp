/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTwoValueCentered.cpp	   	      	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + Text + sep + value					 					*/
/*%C   + unit + value + unit) centré dans la fenêtre  								*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelTwoValueCentered.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelTwoValueCentered::LabelTwoValueCentered():LabelTwoValue()
{
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelTwoValueCentered::SetValue2(UWORD16 _Value2)
{

   if(GetColAdjust() && GetNbDigitsChanged())
   {
      GetFUnit2()->Hide();
      GetFValue2()->SetCol(GetEndColValue1());
      GetFValue2()->SetValue(_Value2);
      GetFValue2()->Show();
      Format2(_Value2);
      GetFUnit2()->Show();
   }
   else
   {
      if(Tools::FindNbDigit(_Value2) != Tools::FindNbDigit(GetFValue2()->GetValue()))
      {
         GetFUnit2()->Hide();
   		GetFValue2()->SetValue(_Value2);
	      Format2(_Value2);
		   GetFUnit2()->Show();
	   }
      else
         GetFValue2()->SetValue(_Value2);

   }

   if(GetLoupe() != NULL)
   {
      if(GetFloatValue2() == 0)
      {
         GetLoupe()->SetValue(_Value2);
      }
      else
      {
         GetLoupe()->SetValue(_Value2,1);
      }
   }
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'affichage																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE									 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValueCentered::Refresh()
{
   UWORD16 _Size = 0;
   UWORD16 _Col = 0;
   UWORD16 _Spacing = 4;
   UWORD16 _ColSep, _ColValue1;
   UWORD16 _Value1, _Value2;
   UWORD16 _NBDigitsBefore, _NBDigitsAfter;   



   if(!IsStopMonitoring())
   {
      if(GetIdParam() != NO_ID)
      {
         DataBaseAccess::ReadValue(	&_Value1,
         									GetIdParam(),
         									GetDbTarget());
         _Value1 = _Value1 / GetDivider();
      }
      if(GetIdParam2() != NO_ID)
      {
         DataBaseAccess::ReadValue(	&_Value2,
         									GetIdParam2(),
         									GetDbTarget2());
         _Value2 = _Value2 / GetDivider();
      }

   }

   _NBDigitsBefore = Tools::FindNbDigit(_Value2) + Tools::FindNbDigit(_Value1);
   _NBDigitsAfter = Tools::FindNbDigit(GetFValue2()->GetValue()) + Tools::FindNbDigit(GetFValue1()->GetValue());
   
   if( _NBDigitsBefore != _NBDigitsAfter)
   {
      /* Calcul de la taille totale */
      /* Valeur #1 */
      /*-----------*/
      /*... Label */
      _Size += Tools::GetStringPixelSize(GetName(), GetFontLabel());
      /*... Espace */
      _Size += _Spacing;
      /*...Séparateur */
      _ColSep = _Size;
      _Size += Tools::GetStringPixelSize(GetSep(), GetFontLabel());
      /*... Espace */
      _Size += _Spacing;
      /*...Valeur */
      _ColValue1 = _Size;
      _Size += Tools::GetNumberPixelSize(_Value1, GetFontValue1(),GetFloatValue1());
      /*... Espace */
      _Size += _Spacing;
      /*...Unité */
      _Size += Tools::GetStringPixelSize(GetUnit1(), GetFontUnit1());


      /* Valeur #2 */
      /*-----------*/
      /*... Espace */
      _Size += _Spacing;
      /*...Valeur */
      _Size += Tools::GetNumberPixelSize(_Value2, GetFontValue2(),GetFloatValue2());
      /*... Espace */
      _Size += _Spacing;
      /*...Unité */
      _Size += Tools::GetStringPixelSize(GetUnit2(), GetFontUnit1());

      _Col = (DISPLAY_WINDOW_WIDTH - _Size) / 2;


      GetFLabel()->Hide();
      GetFSep()->Hide();
      GetFValue1()->Hide();
      GetFUnit1()->Hide();
      GetFValue2()->Hide();
      GetFUnit2()->Hide();

      SetColLabel(_Col);
      SetColSep(_Col + _ColSep);
      SetColValue1(_Col + _ColValue1);

      SetValue1(_Value1);
      SetNbDigitsChanged(TRUE);
      SetValue2(_Value2);

      GetFLabel()->Show();
      GetFSep()->Show();
      GetFValue1()->Show();
      GetFUnit1()->Show();
      GetFValue2()->Show();
      GetFUnit2()->Show();
   }
   else
   {
      SetValue1(_Value1);
      SetValue2(_Value2);
   }
}
