/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelValueString.cpp 		   	      	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + Text + sep + string)				 					*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelValueString.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"
#include "HMI_Tools.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelValueString::LabelValueString():EditableObject()
{
   FValue1.SetParent(this);
	FSep.SetParent(this);

   IntValue1 = 0;
   SetColSep(72);
   SetColValue1(80);
   SetSep((UBYTE *)":");
   SetFontValue1(FONT_4);
   SetColAdjust(FALSE);

   StopMonitoring = FALSE;   
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelValueString::SetVisible(e_BOOL V)
{
   DisplayObject::SetVisible(V);
   FSep.SetVisible(V);
   FValue1.SetVisible(V);
}
/*----------------------------------------------------------------------------*/
void LabelValueString::SetSep(UBYTE *_Sep)
{
   FSep.SetText(_Sep);
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelValueString::GetSep()
{
   return FSep.GetText();
}
/*----------------------------------------------------------------------------*/
void LabelValueString::SetValue1(UBYTE* _Value1)
{
   FValue1.SetText(_Value1);

   if(GetLoupe() != NULL)
   {
      GetLoupe()->SetValue(_Value1);
   }
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelValueString::GetValue1()
{
   return FValue1.GetText();
}
/*----------------------------------------------------------------------------*/
void LabelValueString::SetIntValue1(UWORD16 _IntValue1)
{
   IntValue1 = _IntValue1;
   SetValue1(GetValue1Name());
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelValueString::GetIntValue1()
{
   return IntValue1;
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelValueString::GetValue1Name()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	return (UBYTE *)"???";
}
/*----------------------------------------------------------------------------*/
void LabelValueString::SetColSep(UWORD16 _ColSep)
{
   UWORD16 _ColLimit = GetColLabel() + GetPixelSize() + 3;
   if(GetColAdjust())
   {
      if(_ColSep > _ColLimit)
         FSep.SetCol(_ColSep);
      else
         FSep.SetCol(_ColLimit);
   }
   else
      FSep.SetCol(_ColSep);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelValueString::GetColSep()
{
   return FSep.GetCol();
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelValueString::GetEndCol()
{
   UWORD16 _Col = FValue1.GetCol();
   _Col += Tools::GetStringPixelSize(GetValue1(),GetFontValue1());
   return(_Col);
}
/*----------------------------------------------------------------------------*/
void LabelValueString::SetColAdjust(e_BOOL _Adjust)
{
   ColAdjust =  _Adjust;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelValueString::GetColAdjust()
{
   return(ColAdjust);
}
/*----------------------------------------------------------------------------*/
void LabelValueString::SetColValue1(UWORD16 _ColValue1)
{
   UWORD16 _ColLimit = GetColSep() + 5;
   if(GetColAdjust())
   {
      if(_ColValue1 > _ColLimit)
         FValue1.SetCol(_ColValue1);
      else
         FValue1.SetCol(_ColLimit);
   }
   else
         FValue1.SetCol(_ColValue1);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelValueString::GetColValue1()
{
   return FValue1.GetCol();
}
/*----------------------------------------------------------------------------*/
void LabelValueString::SetFontValue1(UWORD16 _FontValue1)
{
   FValue1.SetFont(_FontValue1);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelValueString::GetFontValue1()
{
   return FValue1.GetFont();
}
/*----------------------------------------------------------------------------*/
TextField* LabelValueString::GetFSep()
{
   return &this->FSep;
}
/*----------------------------------------------------------------------------*/
TextField* LabelValueString::GetFValue1()
{
   return &this->FValue1;
}
/*----------------------------------------------------------------------------*/
void LabelValueString::SetStopMonitoring(e_BOOL Flag)
{
   StopMonitoring = Flag;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelValueString::IsStopMonitoring()
{
   return (e_BOOL)(StopMonitoring == TRUE);
}
/******************************************************************************/
/*                           METHODES                					  			   */
/******************************************************************************/
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE              					               					      */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelValueString::StopMonitoringMode()
{
   SetStopMonitoring(TRUE);
	FValue1.SetText((UBYTE *)"-");
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE              					               					      */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelValueString::StartMonitoringMode()
{
   SetStopMonitoring(FALSE);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet	 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelValueString::RefreshLanguage()
{
   Label::RefreshLanguage();
   if (GetColAdjust())
   {
      /* on réajuste les colonnes du séparateur et de la valeur en passant
         des paramètres à 0 */
      SetColSep(0);
      SetColValue1(0);
   }      
	FValue1.SetTextOnly(GetValue1Name());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Passage en invertion video								 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE												*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelValueString::SetInvertVideo(e_BOOL _InvertVideo)
{
   Label::SetInvertVideo(_InvertVideo);
   FValue1.SetReverseVideo(_InvertVideo);
   FSep.SetReverseVideo(_InvertVideo);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'affichage									 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelValueString::Refresh()
{
   if(!IsStopMonitoring())
   {
      if(this->GetIdParam() != NO_ID)
      {
         UWORD16 Value;
         DataBaseAccess::ReadValue(&Value, GetIdParam(), GetDbTarget());
         SetIntValue1(Value);
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet										 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelValueString::Show()
{
   Refresh();

   Label::Show();
   FValue1.Show();
   FSep.Show();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet										 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelValueString::Hide()
{
   FValue1.Hide();
   FSep.Hide();
   Label::Hide();   
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet											 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelValueString::Blink(e_BOOL _Actif)
{
   FValue1.Blink(_Actif);

   if(GetLoupe() != NULL)
   {
      GetLoupe()->Blink(_Actif);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Increment de la valeur courante						 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelValueString::IncreaseValue()
{
   UWORD16 Value = GetIntValue1();

   /*%C Access to data base */
   if(IncreaseValueOk(&Value))
   {
      SetIntValue1(Value);
   }
   /*%C Access to data base */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decrement de la valeur courante						 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelValueString::DecreaseValue()
{
   UWORD16 Value = GetIntValue1();

   /*%C Access to data base */
   if(DecreaseValueOk(&Value))
   {
      SetIntValue1(Value);
   }
   /*%C Access to data base */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation d'increment									 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Val : valeur a incrementer															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé   														*/
/******************************************************************************/
e_BOOL LabelValueString::IncreaseValueOk(UWORD16* _Val)
{
   if(GetIdParam() != NO_ID)
   {
      return DataBaseAccess::IncrementValue(_Val, GetIdParam(), GetDbTarget());
   }
   return FALSE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation de decrement								 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Val : valeur a incrementer															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé   														*/
/******************************************************************************/
e_BOOL LabelValueString::DecreaseValueOk(UWORD16* _Val)
{
   if(GetIdParam() != NO_ID)
   {
      return DataBaseAccess::DecrementValue(_Val, GetIdParam(), GetDbTarget());
   }
   return FALSE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification d'un Objet					 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelValueString::StartModifMode()
{
   Label::StartModifMode();
   SetIntValue1(GetIntValue1());
   SetValueTemp(GetIntValue1());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet	 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelValueString::ConfirmModifValue(e_BOOL _Confirm)
{
   if(_Confirm)
   {
      /*%C Acces DB */
      if(GetIdParam() != NO_ID)
      {
         UWORD16 Value = GetIntValue1();
         DataBaseAccess::WriteValue(&Value, GetIdParam(), GetDbTarget());
		 /*%C Request a short bip sound */
		 Tools::ShortBipRequest();
      }
   }
   else
   {
      /*%C affiche l'ancienne valeur */
      SetIntValue1(GetValueTemp());
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Renvoie la valeur courante								 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Valeur courante				  														*/
/******************************************************************************/
UWORD16 LabelValueString::GetFullValue()
{
   return(GetIntValue1());
}


