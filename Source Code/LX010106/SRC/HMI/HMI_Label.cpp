/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Label.cpp	       			                          	 		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + Text)												      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_Label.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Message.hpp"
#include "HMI_Tools.hpp"

/******************************************************************************/
/*                        VARIABLE DECLARATION		              		   		*/
/******************************************************************************/


UWORD16 NbLanguage = NB_LANGUAGE;

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
Label::Label():DisplayObject()
{
   Centered = FALSE;
	FIcon.SetParent(this);
   FLabel.SetParent(this);

   SetNbLanguage(NB_LANGUAGE);
   Name = NULL;
   LoupeObject = NULL;
   FLabel.SetCol(13);
   FIcon.SetCol(0);
   SetPreviousIcon(this->FIcon.GetSymbol());
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void Label::SetCentered(e_BOOL _Centered)
{
   Centered = _Centered;

   if(Centered)
   {
      UWORD16 _Size = GetPixelSize();
      if(_Size <= DISPLAY_WINDOW_WIDTH)
         SetColLabel((DISPLAY_WINDOW_WIDTH - _Size)/2);
   }
}
/*----------------------------------------------------------------------------*/
e_BOOL Label::GetCentered()
{
   return(Centered);
}
/*----------------------------------------------------------------------------*/
UWORD16 Label::GetNbLanguage()
{
   return NbLanguage;
}
/*----------------------------------------------------------------------------*/
void Label::SetNbLanguage(UWORD16 _NbLang)
{
   NbLanguage = _NbLang;
}
/*----------------------------------------------------------------------------*/
void Label::SetPreviousIcon(e_SYMBOL _PreviousIcon)
{
   PreviousIcon = _PreviousIcon;
}
/*----------------------------------------------------------------------------*/
e_SYMBOL Label::GetPreviousIcon()
{
   return PreviousIcon;
}
/*----------------------------------------------------------------------------*/
void Label::SetIcon(e_SYMBOL _Icon)
{
   FIcon.SetSymbol(_Icon);
}
/*----------------------------------------------------------------------------*/
void Label::SetColLabel(UWORD16 _ColLabel)
{
   FLabel.SetCol(_ColLabel);
}
/*----------------------------------------------------------------------------*/
UWORD16 Label::GetColLabel()
{
   return(FLabel.GetCol());
}
/*----------------------------------------------------------------------------*/
void Label::SetFontLabel(UWORD16 _FontLabel)
{
   FLabel.SetFont(_FontLabel);
}
/*----------------------------------------------------------------------------*/
UWORD16 Label::GetFontLabel()
{
   return(FLabel.GetFont());
}
/*----------------------------------------------------------------------------*/
UWORD16 Label::GetPixelSize()
{
   return(Tools::GetStringPixelSize(GetName(), GetFontLabel()));
}
/*----------------------------------------------------------------------------*/
UWORD16 Label::GetEndCol()
{
   return(GetColLabel() + GetPixelSize());
}
/*----------------------------------------------------------------------------*/
void Label::SetName(UBYTE** _Name)
{
   Name = _Name;
   FLabel.SetText(GetName());
}
/*----------------------------------------------------------------------------*/
UBYTE** Label::GetPtrName()
{
   return Name;
}
/*----------------------------------------------------------------------------*/
UBYTE* Label::GetName()
{
   if(Name != NULL)
   {
      return (Name[GetLanguage()]);
   }
   else
   {
      return (UBYTE *)"";
   }
}
/*----------------------------------------------------------------------------*/
SymbolField* Label::GetFIcon()
{
    return &this->FIcon;
}
/*----------------------------------------------------------------------------*/
TextField* Label::GetFLabel()
{
   return &this->FLabel;
}
/*----------------------------------------------------------------------------*/
Loupe* Label::GetLoupe()
{
   return LoupeObject;
}
/*----------------------------------------------------------------------------*/
void Label::SetLoupe(Loupe *_LoupeObject)
{
   LoupeObject = _LoupeObject;
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
/*%I		Icon : icone												               		*/
/*%I		Name : Pointeur sur le tableau de nom						         		*/
/*%I		Line : ligne 												               		*/
/*%I		Col : colonne												            			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Label::Init( e_SYMBOL _Icon,
                  UBYTE **_Name,
                  UWORD16 _Line,
                  UWORD16 _Col)
{
   DisplayObject::SetLine(_Line);
   DisplayObject::SetCol(_Col);
   FIcon.SetSymbol(_Icon);
	SetPreviousIcon(_Icon);
   SetName(_Name);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Passage en invertion video																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo : invertion si TRUE					               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Label::SetInvertVideo(e_BOOL _InvertVideo)
{
   FIcon.SetReverseVideo(_InvertVideo);
   FLabel.SetReverseVideo(_InvertVideo);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Lock de l'Objet																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Label::Lock(e_BOOL _Lock)
{
   if(_Lock)
   {
      SetPreviousIcon(FIcon.GetSymbol());

		if(FIcon.GetReverseVideo())
		{
    		FIcon.SetSymbol(KEY_WHITE);
		}
		else
		{
	    	FIcon.SetSymbol(LOCKS);
		}
    }
	else
   {
    	FIcon.SetSymbol(GetPreviousIcon());
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Label::Show()
{
   DisplayObject::Show();
   FIcon.Show();
   FLabel.Show();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet	 																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Label::Hide()
{
   FIcon.Hide();
   FLabel.Hide();
   DisplayObject::Hide();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet	 																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/

void Label::Blink(e_BOOL _Actif)
{
   FLabel.Blink(_Actif);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C L'objet gagne le focus																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Label::WinFocus()
{
	if(!FLabel.GetReverseVideo())
	{
      if(FIcon.GetSymbol() == LOS)
		{
			FIcon.SetSymbol(BLACK_LOS);
		}
		else
		{
			FIcon.SetSymbol(BLACK_SQUARES);
		}
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C L'objet perd le focus																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Label::LoseFocus()
{
	if(FIcon.GetSymbol() == BLACK_LOS)
	{
		FIcon.SetSymbol(LOS);
	}
   else
	{
		FIcon.SetSymbol(FREE_SQUARE);
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Label::StartModifMode()
{
   SetPreviousIcon(FIcon.GetSymbol());
   FIcon.SetSymbol(LESS_OR_MORE);

   /*%C duplication car perte de requetes vers carte graphique */
   FIcon.SetSymbol(LESS_OR_MORE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Label::StopModifMode()
{
   FIcon.SetSymbol(GetPreviousIcon());
  	
  	/*%C duplication car perte de requetes vers carte graphique */
   FIcon.SetSymbol(GetPreviousIcon());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Cancel de la modification de'un Objet												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Label::CancelModifMode()
{
   FIcon.SetSymbol(GetPreviousIcon());

   /*%C duplication car perte de requetes vers carte graphique */
   FIcon.SetSymbol(GetPreviousIcon());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Label::RefreshLanguage()
{
   FLabel.SetTextOnly(GetName());
}



