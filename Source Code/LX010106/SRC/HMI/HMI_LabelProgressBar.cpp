/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelProgressBar.cpp  	    		           	 	  				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon+Text+sep+progressbar)									*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelProgressBar.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Tools.hpp"
#include "HMI_DataBaseAccess.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "Driver_Display_Data.h"


/******************************************************************************/
/*                           CONSTANT DECLARATION	                			   */
/******************************************************************************/

#define HEIGHT_PROGRESSION_BAR		11//15
#define WIDTH_PROGRESSION_BAR		   101

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelProgressBar::LabelProgressBar():EditableObject()
{
   FSep.SetParent(this);

   SetColSep(72);
   SetColValue(80);
   SetSep((UBYTE *)":");
	PixelValue = 0;
    BipRequest = TRUE;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
TextField* LabelProgressBar::GetFSep()
{
   return &this->FSep;
}
/*----------------------------------------------------------------------------*/
void LabelProgressBar::SetSep(UBYTE *_Sep)
{
   FSep.SetText(_Sep);
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelProgressBar::GetSep()
{
   return FSep.GetText();
}
/*----------------------------------------------------------------------------*/
void LabelProgressBar::SetValue(UWORD16 _Value)
{
	SWORD16 ValueDelta = 0;
	SWORD16 Tampon = 0;
   UWORD16 NewPixelValue;
	UWORD16 ColTmp;

   /*%C Calcule la nouvelle coordonnée d'affichage */
	ColTmp = ColValue + GetCol();
   if(LimitDelta != 0)
      NewPixelValue = (	_Value - LowLimit) * 
      						(WIDTH_PROGRESSION_BAR-1) / 
      						LimitDelta;
   else
    	NewPixelValue = 0;

   /*%C Limite l'affichage à la taille max de la barre de progression */
   if(NewPixelValue >= WIDTH_PROGRESSION_BAR)
    	NewPixelValue = WIDTH_PROGRESSION_BAR-1;

   /*%C Ecart d'affichage */
   ValueDelta = NewPixelValue - PixelValue;

   if(this->IsVisible())
   {
   /*%C Affichage du remplissage de la barre de progression */
      if (ValueDelta > 0)
      {
         /*%C Affichage du niveau */
         InterfaceCppC::DisBox(  GetLine()-HEIGHT_PROGRESSION_BAR+1,
                                 ColTmp + 8 + (UWORD16)PixelValue,
                                 HEIGHT_PROGRESSION_BAR-2,
                                 (UWORD16)ValueDelta,
                                 TRUE,
                                 1,
                                 GetPage());
      }
      /*%C Effacement */
      else if (ValueDelta < 0)
      {
         /*%C Il faut eviter d'effacer le cadre si Value dépasse la limite */
         Tampon = PixelValue - NewPixelValue;
         InterfaceCppC::EraseZone(  GetLine()-HEIGHT_PROGRESSION_BAR+1,
                                    ColTmp + 8 + (UWORD16)NewPixelValue+1,
                                    HEIGHT_PROGRESSION_BAR-2,
                                    (UWORD16)Tampon-1,
                                    OFF,
                                    GetPage());
      }

	   /*%C Effacement du curseur précédent */
    	InterfaceCppC::EraseZone(  GetLine()+1, ColTmp + 8 + PixelValue - 3,
                                 7,
                                 6,
                                 OFF, GetPage());

    	/*%C Affichage du curseur */
	   InterfaceCppC::DisplaySymbol( TRIANGLE_BLACK,
                                    GetLine()+1,
                                    ColTmp + 8 + NewPixelValue - 3,
                                    GetPage());
	}

   /*%C Mémorisation des valeurs */
   PixelValue = NewPixelValue;
   RealValue = _Value;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelProgressBar::GetValue()
{
   return RealValue;
}
/*----------------------------------------------------------------------------*/
void LabelProgressBar::SetColSep(UWORD16 _ColSep)
{
   TextField* Sep = GetFSep();
	Sep->SetCol(_ColSep);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelProgressBar::GetColSep()
{
   return FSep.GetCol();
}
/*----------------------------------------------------------------------------*/
void LabelProgressBar::SetColValue(UWORD16 _ColVal)
{
   ColValue = _ColVal;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelProgressBar::GetColValue()
{
   return ColValue;
}
/*----------------------------------------------------------------------------*/
void LabelProgressBar::SetLimits(UWORD16 _LowL, UWORD16 _HighL)
{
   LowLimit = _LowL;
   LimitDelta = _HighL - _LowL;
}
/*----------------------------------------------------------------------------*/ 
e_BOOL LabelProgressBar::GetBipRequest()
{
    return BipRequest;
}
/*----------------------------------------------------------------------------*/
void LabelProgressBar::SetBipRequest(e_BOOL Request)
{
    BipRequest = Request;
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
/*%I		Value  : Valeur												               	*/
/*%I		NameUnit    : nom du separateur													*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelProgressBar::Init(  e_SYMBOL _Icon,
                              UBYTE **_Name,
							         UWORD16 _Line,
                              UWORD16 _Col,
							         UWORD16 _Value )
{
   Label::Init(_Icon, _Name, _Line, _Col);
   SetValue(_Value);
}


/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelProgressBar::RefreshLanguage()
{
   Label::RefreshLanguage();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Passage en inversion video																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	InvertVideo   : invertion si TRUE												*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelProgressBar::SetInvertVideo(e_BOOL _InvertVideo)
{
   Label::SetInvertVideo(_InvertVideo);
   FSep.SetReverseVideo(_InvertVideo);
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
void LabelProgressBar::Refresh()
{
   if(GetIdParam() != NO_ID)
   {
		UWORD16 Value;
		DataBaseAccess::ReadValue(&Value, GetIdParam(), GetDbTarget());
		SetValue(Value);
    }
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
void LabelProgressBar::Show()
{
	UWORD16 ColTmp;

	Refresh();

	Label::Show();
	FSep.Show();

	ColTmp = ColValue + GetCol();

   /*%C Dessine le - */
	InterfaceCppC::DisplayLine(GetLine()- HEIGHT_PROGRESSION_BAR/2,
                              ColTmp,
                              0,
                              5,
                              1,
                              GetPage());

	InterfaceCppC::DisplayLine(GetLine()- HEIGHT_PROGRESSION_BAR/2 + 1,
                              ColTmp,
                              0,
                              5,
                              1,
                              GetPage());

   /*%C Dessine le cadre du progressbar */

	InterfaceCppC::DisplayLine(GetLine()- HEIGHT_PROGRESSION_BAR+1,
                              ColTmp+8,
                              HEIGHT_PROGRESSION_BAR-2,
                              0,
                              1,
                              GetPage());

	InterfaceCppC::DisplayLine(GetLine(),
                              ColTmp+8 + 1,
                              0,
                              WIDTH_PROGRESSION_BAR-2,
                              1,
                              GetPage());

	InterfaceCppC::DisplayLine(GetLine()- HEIGHT_PROGRESSION_BAR+1,
                              ColTmp+8+WIDTH_PROGRESSION_BAR,
                              HEIGHT_PROGRESSION_BAR-2,
                              0,
                              1,
                              GetPage());

	InterfaceCppC::DisplayLine(GetLine()- HEIGHT_PROGRESSION_BAR, ColTmp+8 + 1,
                              0,
                              WIDTH_PROGRESSION_BAR-2,
                              1,
                              GetPage());

   /*%C Dessine la valeur actuelle par un cadre plein */
   InterfaceCppC::DisBox(  	GetLine()-HEIGHT_PROGRESSION_BAR+1,
	                           ColTmp+8,
   	                        HEIGHT_PROGRESSION_BAR-2,
      	                     PixelValue,
         	                  TRUE,
            	               1,
               	            GetPage());

	/*%C Dessine le + */
	InterfaceCppC::DisplayLine(GetLine()- HEIGHT_PROGRESSION_BAR/2,
                              ColTmp+8+WIDTH_PROGRESSION_BAR+4,
                              0,
                              5,
                              1,
                              GetPage());

	InterfaceCppC::DisplayLine(GetLine()- HEIGHT_PROGRESSION_BAR/2 + 1,
                              ColTmp+8+WIDTH_PROGRESSION_BAR+4,
                              0,
                              5,
                              1,
                              GetPage());

	InterfaceCppC::DisplayLine(GetLine()- HEIGHT_PROGRESSION_BAR/2 - 2,
                              ColTmp+8+WIDTH_PROGRESSION_BAR+6,
                              5,
                              0,
                              1,
                              GetPage());

	InterfaceCppC::DisplayLine(GetLine()- HEIGHT_PROGRESSION_BAR/2 - 2,
                              ColTmp+8+WIDTH_PROGRESSION_BAR+7,
                              5,
                              0,
                              1,
                              GetPage());

   /*%C Affiche le symbole */
	InterfaceCppC::DisplaySymbol( TRIANGLE_WHITE,
                                 GetLine()+1,
                                 ColTmp + 8 + PixelValue - 3,
                                 GetPage());
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
void LabelProgressBar::Hide()
{
   FSep.Hide();
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
void LabelProgressBar::Blink(e_BOOL _Actif)
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
	_Actif = _Actif;
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
void LabelProgressBar::IncreaseValue()
{
	UWORD16 Value = GetValue();

   /*%C Access to data base */
   if(GetIdParam() != NO_ID)
   {
    	if(DataBaseAccess::IncrementValue(&Value, GetIdParam(), GetDbTarget()))
      {
			SetValue(Value);
      }
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
void LabelProgressBar::DecreaseValue()
{
	UWORD16 Value = GetValue();

	/*%C Access to data base */
	if(GetIdParam() != NO_ID)
   {
		if(DataBaseAccess::DecrementValue(&Value, GetIdParam(), GetDbTarget()))
      {
			SetValue(Value);
		}
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelProgressBar::StartModifMode()
{
	UWORD16 ColTmp;
	ColTmp = ColValue + GetCol();

   Label::StartModifMode();
	SetValue(GetValue());
   SetValueTemp(GetValue());

	/*%C Affiche le symbole */
	InterfaceCppC::DisplaySymbol( TRIANGLE_BLACK,
                                 GetLine()+1,
                                 ColTmp + 8 + PixelValue - 3,
                                 GetPage());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelProgressBar::ConfirmModifValue(e_BOOL _Confirm)
{
	UWORD16 ColTmp;
	ColTmp = ColValue + GetCol();

	if(_Confirm)
   {
      /*%C Acces DB */
		if(GetIdParam() != NO_ID)
      {
			UWORD16 Value = GetValue();
			DataBaseAccess::WriteValue(&Value, GetIdParam(), GetDbTarget());

			/*%C Request a short bip sound */
            if (GetBipRequest())
    			Tools::ShortBipRequest();
		}
    }
	else
   {
		/*%C affiche l'ancienne valeur */
		SetValue(GetValueTemp());
	}

	/*%C Affiche le symbole */
    if (this->IsVisible()) {
    	InterfaceCppC::DisplaySymbol( TRIANGLE_WHITE,
                                     GetLine()+1,
                                     ColTmp + 8 + PixelValue - 3,
                                     GetPage());
    }
}




