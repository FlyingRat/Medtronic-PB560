/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelSymbol.cpp  	  		  		           	 	  				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + text + symbol)											*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelSymbol.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"


/******************************************************************************/
/*                           CONSTANT DECLARATION	               			   */
/******************************************************************************/

#define HEIGHT_PROGRESSION_BAR		15
#define WIDTH_PROGRESSION_BAR		   101

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelSymbol::LabelSymbol():EditableObject()
{
   FSymbol.SetParent(this);
   FSep.SetParent(this);
   FTextUnderSymbol.SetParent(this);

   SetSymbol(RISETIME1);
   SetColSep(83);
   SetColSymbol(88);
   SetSep((UBYTE *)":");
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelSymbol::SetSep(UBYTE *_Sep)
{
   GetFSep()->SetText(_Sep);
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelSymbol::GetSep()
{
   return GetFSep()->GetText();
}
/*----------------------------------------------------------------------------*/
void LabelSymbol::SetUsedTextUnderSymbol(e_BOOL _UsedTextUnderSymbol)
{
    UsedTextUnderSymbol = _UsedTextUnderSymbol;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelSymbol::IsUsedTextUnderSymbol()
{
    return(UsedTextUnderSymbol);
}
/*----------------------------------------------------------------------------*/
void LabelSymbol::SetSymbol(e_SYMBOL _Symbol)
{
   if(_Symbol != RAMPE1)
   {
        if(IsUsedTextUnderSymbol())
            FTextUnderSymbol.Hide();
        SetUsedTextUnderSymbol(FALSE);
   }

   FSymbol.SetSymbol(_Symbol);

   if(GetLoupe() != NULL)
   {
      switch(_Symbol)
      {
         case RISETIME1 :  GetLoupe()->SetValue(1);
                           break;
         case RISETIME2 :  GetLoupe()->SetValue(2);
                           break;
         case RISETIME3 :  GetLoupe()->SetValue(3);
                           break;
         case RISETIME4 :  GetLoupe()->SetValue(4);
                           break;
         case RAMPE1    :  GetLoupe()->SetValue((UBYTE*)"SQ");
                           break;
         case RAMPE2    :  GetLoupe()->SetValue((UBYTE*)"D");
                           break;
         case RAMPE3    :  GetLoupe()->SetValue((UBYTE*)"S");
                           break;
         default : break;                           
      }
   }
   if(_Symbol == RAMPE1)
   {
        SetUsedTextUnderSymbol(TRUE);
  	  	FTextUnderSymbol.SetText((UBYTE*)"SQ");
  	  	FTextUnderSymbol.Show();
   }
}
/*----------------------------------------------------------------------------*/
e_SYMBOL LabelSymbol::GetSymbol()
{
   return FSymbol.GetSymbol();
}
/*----------------------------------------------------------------------------*/
void LabelSymbol::SetColSymbol(UWORD16 _ColSymbol)
{
   FSymbol.SetCol(_ColSymbol);
   FTextUnderSymbol.SetCol(_ColSymbol + 10);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelSymbol::GetColSep()
{
   return GetFSep()->GetCol();
}
/*----------------------------------------------------------------------------*/
void LabelSymbol::SetColSep(UWORD16 _ColSep)
{
   GetFSep()->SetCol(_ColSep);
}
/*----------------------------------------------------------------------------*/
TextField* LabelSymbol::GetFSep()
{
   return &this->FSep;
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
/*%I	  	Icon   : icone												               		*/
/*%I		Name   : Pointeur sur le tableau de nom						         	*/
/*%I		Line   : ligne 												               	*/
/*%I		Col    : colonne												            		*/
/*%I		Symbol  : Symbole																		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelSymbol::Init( e_SYMBOL _Icon,
                        UBYTE **_Name,
                        UWORD16 _Line,
                        UWORD16 _Col,
                        e_SYMBOL _Symbol)
{

   Label::Init(_Icon, _Name, _Line, _Col);
   SetSymbol(_Symbol);
   FTextUnderSymbol.SetFont(FONT_2);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Convertion int / symbole  															  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
e_SYMBOL LabelSymbol::IntToSymbol(UWORD16 _Val)
{
	/* Pour éviter les warnings */
	_Val = _Val;
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */	

	return (e_SYMBOL)0;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Convertion symbole / int																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
UWORD16 LabelSymbol::SymbolToInt()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
	return 0;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'affichage																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelSymbol::Refresh()
{
   UWORD16 Value;
   DataBaseAccess::ReadValue(&Value, GetIdParam(), GetDbTarget());
   SetSymbol(IntToSymbol(Value));
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelSymbol::Show()
{
   Label::Show();
   Refresh();
   FSymbol.Show();
   if(IsUsedTextUnderSymbol())
        FTextUnderSymbol.Show();
   GetFSep()->Show();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelSymbol::Hide()
{
   FSymbol.Hide();
   if(IsUsedTextUnderSymbol())
        FTextUnderSymbol.Hide();
   GetFSep()->Hide();
   Label::Hide();   
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelSymbol::Blink(e_BOOL _Actif)
{
   FSymbol.Blink(_Actif);

   if(IsUsedTextUnderSymbol())
        FTextUnderSymbol.Blink(_Actif);

   if(GetLoupe() != NULL)
   {
      GetLoupe()->Blink(_Actif);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Increment de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelSymbol::IncreaseValue()
{
   e_SYMBOL Symbol = GetSymbol();

   UWORD16 ValSymbol = SymbolToInt();

   /*%C Access to data base*/
   if(IncreaseValueOk(&ValSymbol))
   {
      Symbol = IntToSymbol(ValSymbol);
      SetSymbol(Symbol);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decrement de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelSymbol::DecreaseValue()
{
   e_SYMBOL Symbol = GetSymbol();
   UWORD16 ValSymbol = SymbolToInt();

   /*%C Access to data base */
   if(DecreaseValueOk(&ValSymbol))
   {
      Symbol = IntToSymbol(ValSymbol);
      SetSymbol(Symbol);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Autorisation d'increment																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Val : valeur a incrementer															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé   														*/
/******************************************************************************/
e_BOOL LabelSymbol::IncreaseValueOk(UWORD16* _Val)
{
   return DataBaseAccess::IncrementValue(_Val, GetIdParam(), GetDbTarget());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Autorisation de decrement																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Val : valeur a incrementer															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé   														*/
/******************************************************************************/
e_BOOL LabelSymbol::DecreaseValueOk(UWORD16* _Val)
{
   return DataBaseAccess::DecrementValue(_Val, GetIdParam(), GetDbTarget());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Debut de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE							   														*/
/******************************************************************************/
void LabelSymbol::StartModifMode()
{
   Label::StartModifMode();
   SetSymbol(GetSymbol());
   SetValueTemp((UWORD16)GetSymbol());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Confirme la modification de la valeur de Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE							   														*/
/******************************************************************************/

void LabelSymbol::ConfirmModifValue(e_BOOL _Confirm)
{
   if(_Confirm)
   {
      /*%C Acces DB */
      UWORD16 Value = SymbolToInt();

      DataBaseAccess::WriteValue(&Value, GetIdParam(), GetDbTarget());

	  /*%C Request a short bip sound */
	  Tools::ShortBipRequest();
   }
   else
   {
      /*%C affiche l'ancienne valeur */
      SetSymbol((e_SYMBOL)GetValueTemp());
   }
}

