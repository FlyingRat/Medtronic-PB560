/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelMode.cpp  			                          	 	  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage du mode d'alarme 											      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelMode.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelMode::LabelMode():Label()
{
   SetNameMode(NULL,NULL,NULL,NULL,NULL);
   FSep.Init(0, 175, FONT_4, FALSE, (UBYTE *)"/");

   FNominalMode.SetFont(FONT_4);
   FNominalMode.SetCol(16);

   FModifMode.SetFont(FONT_4);
   FModifMode.SetCol(16);

   FStateModifMode.SetFont(FONT_1);
   FStateModifMode.SetCol(80);

   FActifMode.SetFont(FONT_4);
   FActifMode.SetCol(184);

   FStateActifMode.SetFont(FONT_1);
   FStateActifMode.SetCol(250);

   NameMode2Display = FALSE;

   FNominalMode.SetParent(this);
   FModifMode.SetParent(this);
	FStateModifMode.SetParent(this);
   FActifMode.SetParent(this);
	FStateActifMode.SetParent(this);
   FSep.SetParent(this);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelMode::SetNameMode2Display(e_BOOL _NameMode2Display)
{
   NameMode2Display = _NameMode2Display;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelMode::IsNameMode2Display()
{
   return NameMode2Display;
}
/*----------------------------------------------------------------------------*/
void LabelMode::SetInModification(e_BOOL _InModification)
{
   InModification = _InModification;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelMode::IsInModification()
{
   return InModification;
}
/*----------------------------------------------------------------------------*/
e_MODE_TYPES LabelMode::GetActifMode(void)
{
   return ActifMode;
}
/*----------------------------------------------------------------------------*/
void LabelMode::SetActifMode(e_MODE_TYPES _ActifMode)
{
   ActifMode = _ActifMode;
}
/*----------------------------------------------------------------------------*/
e_MODE_TYPES LabelMode::GetModifMode(void)
{
   return ModifMode;
}
/*----------------------------------------------------------------------------*/
void LabelMode::SetModifMode(e_MODE_TYPES _ModifMode)
{
   ModifMode = _ModifMode;
}
/*----------------------------------------------------------------------------*/
void LabelMode::SetNominalValue(UBYTE* _ModeName)
{
   FNominalMode.SetText(_ModeName);
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelMode::IsNominalMode()
{
   return (e_BOOL)(NominalMode == TRUE);
}
/*----------------------------------------------------------------------------*/
void LabelMode::SetNominalMode(e_BOOL _NominalMode)
{
   NominalMode = _NominalMode;
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne le nom court d'un mode														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Mode : Numero du mode								               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Nom court d'un mode			  														*/
/******************************************************************************/
UBYTE* LabelMode::GetNameMode3(e_MODE_TYPES _Mode)
{
   if(NameMode3 != NULL)
   {
      UBYTE **tmp;
      tmp = NameMode3;

      /*%C positionnement de la ligne (ici NB_LANGUAGE = nb de langues) */
      tmp = &tmp[this->GetNbLanguage()*(_Mode)];
      
      /*%C lecture de la colonne */
      return tmp[GetLanguage()];
   }
   else
	{
      return (UBYTE *)"???";
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne le nom court d'un mode														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Mode : Numero du mode								               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Nom court d'un mode			  														*/
/******************************************************************************/
UBYTE* LabelMode::GetNameMode2(e_MODE_TYPES _Mode)
{
   if(NameMode2 != NULL)
   {
      UBYTE **tmp;
      tmp = NameMode2;

      /*%C positionnement de la ligne (ici NB_LANGUAGE = nb de langues) */
      tmp = &tmp[this->GetNbLanguage()*(_Mode)];

      /*%C lecture de la colonne */
      return tmp[GetLanguage()];
   }
   else
	{
      return (UBYTE *)"???";
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne le nom court d'un mode														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Mode : Numero du mode								               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Nom long d'un mode			  														*/
/******************************************************************************/
UBYTE* LabelMode::GetNameMode(e_MODE_TYPES _Mode)
{
   if(NameMode != NULL)
   {
      UBYTE **tmp;
      tmp = this->NameMode;
      
      /*%C positionnement de la ligne (ici NB_LANGUAGE = nb de langues) */
      tmp = &tmp[GetNbLanguage()*(_Mode)];
     
      /*%C lecture de la colonne */
      return tmp[GetLanguage()];
   }
   else
	{
      return (UBYTE *)"???";
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Retourne nom du mode lorsque l'on est pas en	cour de modification			*/
/*%C    de mode (nominal)																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Mode : Numero du mode								               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Nom long d'un mode			  														*/
/******************************************************************************/
UBYTE* LabelMode::GetNameNominalMode(e_MODE_TYPES _Mode)
{
   if(IsInModification())
   {
      return GetNameMode3(_Mode);
   }
   else if(!IsNameMode2Display())
   {
      return GetNameMode(_Mode);
   }
   else
   {
      return GetNameMode2(_Mode);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Initialisation des noms de mode et d'etat											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NameMode : tableau des noms de mode longs				      				*/
/*%I		NameMode2 : tableau des noms de mode couts				      			*/
/*%I		ActifName : nom pour mode actif							         			*/
/*%I		NoActifName : nom pour mode inactif									      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::SetNameMode(  UBYTE** _NameMode,
                              UBYTE** _NameMode2,
                              UBYTE** _NameMode3,
                              UBYTE** _ActifName,
                              UBYTE** _NoActifName)
{
   NameMode = _NameMode;
   NameMode2 = _NameMode2;
   NameMode3 = _NameMode3;
   ActifName = _ActifName;
   NoActifName = _NoActifName;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage du mode nominale cad lorsque l'on 										*/
/*%C est pas en modification du mode                                       	*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	  NONE																			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::ShowNominalView()
{
   FModifMode.Hide();
   FStateModifMode.Hide();
   FActifMode.Hide();
   FStateActifMode.Hide();
   FSep.Hide();

   FNominalMode.Show();
   SetNominalValue((UBYTE*)GetNameNominalMode(GetActifMode()));

   SetNominalMode(TRUE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage du mode lorsque l'on est en modification du mode					*/
/*%C est pas en modification du mode                                       	*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	  NONE																			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::ShowMultiModeView()
{
   if(GetActifMode() != GetModifMode())
   {
      FNominalMode.Hide();

      FModifMode.Show();
      FStateModifMode.Show();
      FActifMode.Show();
      FStateActifMode.Show();
      FSep.Show();

      FModifMode.SetText(GetNameMode(GetModifMode()));
      FStateModifMode.SetText(NoActifName[GetLanguage()]);
      FActifMode.SetText(GetNameMode(GetActifMode()));
      FStateActifMode.SetText(ActifName[GetLanguage()]);

      SetNominalMode(FALSE);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	  NONE																			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::Show()
{
   Label::Show();

   if(IsNominalMode())
   {
      ShowNominalView();
   }
   else
   {
      ShowMultiModeView();
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	  NONE																			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::Hide()
{
   FNominalMode.Hide();
   FModifMode.Hide();
   FStateModifMode.Hide();
   FActifMode.Hide();
   FStateActifMode.Hide();
   Label::Hide();   
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet																			*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	  NONE																			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::Blink(e_BOOL _Actif)
{
   if(IsNominalMode())
   {
      FNominalMode.Blink(_Actif);
   }
   else
   {
      FStateModifMode.Blink(_Actif);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'Objet																			*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	  NONE																			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::Refresh()
{
   UWORD16 _Val;
   if(GetIdParam() != NO_ID)
   {
      DataBaseAccess::ReadValue(	&_Val, GetIdParam(), GetDbTarget());

      SetActifMode((e_MODE_TYPES)_Val);
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Increment de la valeur courante														*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	  NONE																			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::IncreaseValue()
{
   UWORD16 Value = ModifMode;

   /*%C Access to data base */
   if(IncreaseValueOk(&Value))
   {
      SetModifMode((e_MODE_TYPES)Value);
   }
   /*%C Access to data base */
   SetNominalValue(GetNameNominalMode(GetModifMode()));
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decrement de la valeur courante														*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	  NONE																			      	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::DecreaseValue()
{
   UWORD16 Value = ModifMode;

   /*%C Access to data base */
   if(DecreaseValueOk(&Value))
   {
      SetModifMode((e_MODE_TYPES)Value);
   }
   /*%C Access to data base*/
   SetNominalValue(GetNameNominalMode(GetModifMode()));
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation d'increment																	*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	  	Val : valeur a incrementer												       	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE								  													  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé  														*/
/******************************************************************************/
e_BOOL LabelMode::IncreaseValueOk(UWORD16* _Val)
{
   if(GetIdParam() != NO_ID)
   {
      return DataBaseAccess::IncrementValue(	_Val, 
      													GetIdParam(), 
      													GetDbTarget());
   }
   return FALSE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation de decrement 																*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	  	Val : valeur a decrementer												       	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE							   													  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé	  														*/
/******************************************************************************/
 e_BOOL LabelMode::DecreaseValueOk(UWORD16* _Val)
{
   if(GetIdParam() != NO_ID)
   {
      return DataBaseAccess::DecrementValue(	_Val, 
      													GetIdParam(), 
      													GetDbTarget());
   }
   return FALSE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification d'un Objet													*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	 	NONE																			       	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE								  													  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::StartModifMode()
{
   SetInModification(TRUE);
   Label::StartModifMode();
   SetModifMode(GetActifMode());
   ShowNominalView();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret de la modification d'un Objet													*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	 	NONE																			       	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE								  													  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::StopModifMode()
{
	SetInModification(FALSE);
	Label::StopModifMode();
	SetNominalValue(GetNameNominalMode(GetActifMode()));

	/*%C Request a short bip sound */
	Tools::ShortBipRequest();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Cancel de la modification d'un Objet													*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	 	NONE																			       	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE								  													  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::CancelModifMode()
{
   SetInModification(FALSE);
   Label::StopModifMode();
   SetModifMode(GetActifMode());
   SetNominalValue(GetNameNominalMode(GetActifMode()));
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Lock de l'Objet																				*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	 	NONE																			       	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE								  													  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::Lock(e_BOOL _Lock)
{
   if(_Lock)
   {
      SetPreviousIcon(GetFIcon()->GetSymbol());
      GetFIcon()->SetSymbol(KEY);
   }
   else
   {
      GetFIcon()->SetSymbol(GetPreviousIcon());
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'objet									*/
/*%C																									*/
/*%I Input Parameter : 																			*/
/*%I	 	NONE																			       	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE								  													  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelMode::RefreshLanguage()
{
   FNominalMode.SetTextOnly((UBYTE*)GetNameNominalMode(GetActifMode()));
   FModifMode.SetTextOnly(GetNameMode(GetModifMode()));
   FStateModifMode.SetTextOnly(NoActifName[GetLanguage()]);
   FActifMode.SetTextOnly(GetNameMode(GetActifMode()));
   FStateActifMode.SetTextOnly(ActifName[GetLanguage()]);
}

