/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValue.cpp  			                          	 	   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + Text + sep + value+ unit)					      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelOneValue.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Tools.hpp"
#include "HMI_DisplayObject.hpp"
#include "HMI_DataBaseAccess.hpp"
#include "HMI_InterfaceCppC.hpp"

extern "C"
{
#include "stdfile.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValue::LabelOneValue():EditableObject()
{
   	FUnit1.SetParent(this);
	FSep.SetParent(this);
	FValue1.SetParent(this);

	SetColSep(83);
	SetColValue1(88);
	SetColUnit1(100);
	SetSep((UBYTE *)":");
	SetFontValue1(FONT_4);
	SetLabelOnly(FALSE);
	ValueIsString = FALSE;
	StopMonitoring = FALSE;
	Divider = 1;
	MaxDisplayValueConfigured = FALSE;
	MaxDisplayValue = 0xFFFF;
}


/******************************************************************************/
/*                           ACCESSEURS						                	   */
/******************************************************************************/
void LabelOneValue::SetVisible(e_BOOL V)
{
   DisplayObject::SetVisible(V);
   FUnit1.SetVisible(V);
   FValue1.SetVisible(V);
   FSep.SetVisible(V);
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetNameUnit(UBYTE** _NameUnit)
{
   NameUnit = _NameUnit;
	SetUnit1(GetNameUnit());
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValue::GetNameUnit()
{
	if(NameUnit != NULL)
   {
		return (NameUnit[GetLanguage()]);
	}
	else
	{
      return (UBYTE *)"???";
	}
}
/*----------------------------------------------------------------------------*/
TextField* LabelOneValue::GetFUnit1()
{
	return &this->FUnit1;
}
/*----------------------------------------------------------------------------*/
TextField* LabelOneValue::GetFSep()
{
	return &this->FSep;
}
/*----------------------------------------------------------------------------*/
ValueTextField* LabelOneValue::GetFValue1()
{
	return &this->FValue1;
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetSep(UBYTE *_Sep)
{
   FSep.SetText(_Sep);
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValue::GetSep()
{
	return FSep.GetText();
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetUnit1(UBYTE *_Unit1)
{
   FUnit1.SetText(_Unit1);
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValue::GetUnit1()
{
	return FUnit1.GetText();
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValue::GetEndColValue1()
{
   UWORD16 _Col = FUnit1.GetCol();
   _Col += Tools::GetStringPixelSize((UBYTE *)GetNameUnit(), GetFontUnit1());
   return(_Col + 2);
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetFontUnit1(UWORD16 _FontUnit1)
{
   FUnit1.SetFont(_FontUnit1);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValue::GetFontUnit1()
{
	return FUnit1.GetFont();
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetMaxDisplayValue(UWORD16 _MaxDisplayValue)
{
   MaxDisplayValue = _MaxDisplayValue;
   SetMaxDisplayValueConfigured(TRUE);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValue::GetMaxDisplayValue()
{
   return(MaxDisplayValue);
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetMaxDisplayValueConfigured(e_BOOL _MaxDisplayValueConfigured)
{
   MaxDisplayValueConfigured = _MaxDisplayValueConfigured;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelOneValue::IsMaxDisplayValueConfigured()
{
   return(MaxDisplayValueConfigured);
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SaturateValue(UWORD16* _Value)
{
	UWORD16 _max = GetMaxDisplayValue();
	UWORD16 _abs = 0;

	if (IsMaxDisplayValueConfigured())
	{
		if (*_Value > _max)
		{
			if (*_Value & 0x8000)
			{
            	/* negative value */
				_abs = ~(*_Value - 1);
				if (_abs > _max)
					*_Value = (~_max) + 1;
            }
			else
				*_Value = _max;
		}
	}
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetValue1(UWORD16 _Value1)
{
	static e_BOOL WasString;
	WasString = FALSE;
   UWORD16 _NbDigitsBefore, _NbDigitsAfter;
   SWORD16 _ValueSignBefore, _ValueSignAfter;

	if(IsValueIsString())
   {
		SetValueIsString(FALSE);
		WasString = TRUE;
	}

   if(IsSignValue())
   {
		_ValueSignBefore = (SWORD16)(FValue1.GetValue() * GetDivider());
		_ValueSignAfter = (SWORD16)(_Value1 * GetDivider());

      _NbDigitsBefore = 0;
      _NbDigitsAfter = 0;

      if(_ValueSignBefore != _ValueSignAfter)
      {
         if(_ValueSignBefore<0)
         {
            _NbDigitsBefore++;
		   }

		   if(_ValueSignAfter<0)
         {
            _NbDigitsAfter++;
		   }
         _NbDigitsBefore += Tools::FindNbDigit(abs(_ValueSignBefore / GetDivider()));
         _NbDigitsAfter += Tools::FindNbDigit(abs(_ValueSignAfter / GetDivider()));
      }
	}
   else
   {
      _NbDigitsBefore = Tools::FindNbDigit(FValue1.GetValue());
      _NbDigitsAfter = Tools::FindNbDigit(_Value1);
   }

   if((_NbDigitsBefore != _NbDigitsAfter) || GetInitNbDigits())
	   SetNbDigitsChanged(TRUE);
   else
	   SetNbDigitsChanged(FALSE);

	/*%C Gestion du deplacement de l'unite */
	if(GetNbDigitsChanged())
   {
	  FUnit1.Hide();
	  if(_NbDigitsAfter > _NbDigitsBefore)
		 HideAll();
		FValue1.SetValue(_Value1);
		Format(_Value1);
		FUnit1.Show();
	}
	else
   {
		/*%C reaffichage unite si valeur precedante  = string */
		if(WasString)
      {
			FUnit1.Hide();
			Format(_Value1);
		}
      FValue1.SetValue(_Value1);
		if(WasString)
      {
         FUnit1.Show();
      }
	}

	if(GetLoupe() != NULL)
   {
		if(GetFloatValue1() == 0)
      {
			GetLoupe()->SetValue(_Value1);
		}
		else
      {
			GetLoupe()->SetValue(_Value1,1);
		}
	}
	SetInitNbDigits(FALSE);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValue::GetValue1()
{
	return FValue1.GetValue();
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelOneValue::GetStringValue1()
{
#ifdef  _BORLAND
   UWORD16 _Value, _Divider;
   FLOAT32 _FValue;
   _Divider = GetDivider();

   if(GetFloatValue1())
   {
      _FValue = ((FLOAT32) FValue1.GetValue()) / _Divider / 10;
      sprintf(	DisplayObject::StringValue1,"%2.1f", _FValue);
   }
   else
   {
      _Value = FValue1.GetValue() / _Divider;
      sprintf(	DisplayObject::StringValue1,"%d", _Value);
   }
   return((UBYTE* ) DisplayObject::StringValue1);
#else
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	return((UBYTE* )"");
#endif
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetColSep(UWORD16 _ColSep)
{
	TextField* Sep = GetFSep();
	Sep->SetCol(_ColSep);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValue::GetColSep()
{
	return FSep.GetCol();
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetColValue1(UWORD16 _ColValue1)
{
   FValue1.SetCol(_ColValue1);
	Format();
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValue::GetColValue1()
{
	return FValue1.GetCol();
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetColUnit1(UWORD16 _ColUnit1)
{
   FUnit1.SetCol(_ColUnit1);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValue::GetColUnit1()
{
	return FUnit1.GetCol();
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetFontValue1(UWORD16 _FontValue1)
{
   FValue1.SetFont(_FontValue1);
	Format();
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValue::GetFontValue1()
{
	return FValue1.GetFont();
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetFloatValue1(e_BOOL _Float)
{
	FValue1.Hide();
	FValue1.SetFloat(_Float);
	Format();
	FValue1.Show();
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelOneValue::GetFloatValue1()
{
	return FValue1.GetFloat();
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetNbDigitValue1(UWORD16 _NbDigitValue1)
{
	FValue1.SetNbDigit(_NbDigitValue1);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValue::GetNbDigitValue1()
{
	return FValue1.GetNbDigit();
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetDisplayZeroValue1(e_BOOL _DisplayZero)
{
   FValue1.SetDisplayZero(_DisplayZero);
	Format();
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelOneValue::GetDisplayZeroValue1()
{
	return FValue1.GetDisplayZero();
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelOneValue::IsLabelOnly()
{
	return (e_BOOL)(LabelOnly == TRUE);
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetLabelOnly(e_BOOL _LabelOnly)
{
	LabelOnly = _LabelOnly;
	if(!LabelOnly)
   {
		FUnit1.Show();
		FValue1.Show();
		FSep.Show();
	}
	else
   {
		FUnit1.Hide();
		FValue1.Hide();
		FSep.Hide();
	}
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetValueIsString(e_BOOL _Flag)
{
	this->ValueIsString = _Flag;
	if(_Flag)
   {
		FUnit1.Hide();
	}
	else
   {
		FUnit1.Show();
	}
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelOneValue::IsValueIsString()
{
	return (e_BOOL)(ValueIsString == TRUE);
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetStopMonitoring(e_BOOL _Flag)
{
	StopMonitoring = _Flag;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelOneValue::IsStopMonitoring()
{
	return (e_BOOL)(StopMonitoring == TRUE);
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetSignValue(e_BOOL _SignValue)
{
	FValue1.SetSignValue(_SignValue);
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelOneValue::IsSignValue()
{
	return FValue1.IsSignValue();
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetDivider(UWORD16 _Divider)
{
   Divider = _Divider;
   FValue1.SetDivider(_Divider);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelOneValue::GetDivider()
{
	return Divider;
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetNbDigitsChanged(e_BOOL _NbDigitsChanged)
{
   NbDigitsChanged = _NbDigitsChanged;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelOneValue::GetNbDigitsChanged()
{
   return(NbDigitsChanged);
}
/*----------------------------------------------------------------------------*/
void LabelOneValue::SetInitNbDigits(e_BOOL _Init)
{
	InitNbDigits = _Init;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelOneValue::GetInitNbDigits()
{
	return(InitNbDigits);
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
/*%I		Line   : ligne 												              		*/
/*%I		Col    : colonne												            		*/
/*%I		Value  : Valeur								               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::Init(  e_SYMBOL _Icon,
                           UBYTE **_Name,
                           UWORD16 _Line,
                           UWORD16 _Col,
                           UWORD16 _Value,
                           UBYTE **_NameUnit)
{
	Label::Init(_Icon, _Name, _Line, _Col);

   SetValue1(_Value);
	SetNameUnit(_NameUnit);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Format de la position de l'unitée = f(value)										*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NewValue = nouvelle valeur					               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::Format(UWORD16 NewValue)
{
	UWORD16 Col = 0;
	SWORD16 ValueSign;

	//Gestion des negatifs
	if(IsSignValue())
   {
		ValueSign = (SWORD16)(NewValue * GetDivider());

		if(ValueSign<0)
      {
			Col += Tools::GetStringPixelSize((UBYTE *)"-", FValue1.GetFont());
		}
      ValueSign = ValueSign / GetDivider(); 
		NewValue = abs(ValueSign);
	}

	/*%C Si on affiche des 0 devant */
	if(GetDisplayZeroValue1())
		Col += 1 + Tools::GetNumberPixelSize(  0, 
															FValue1.GetFont(),
                                             GetFloatValue1()) * 
                                             GetNbDigitValue1();
	else
		Col += 1 + Tools::GetNumberPixelSize(  NewValue,
                                             FValue1.GetFont(),
                                             GetFloatValue1());

	Col += GetColValue1();
	SetColUnit1(Col);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Format de la position de l'unitée = f(value)										*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::Format()
{
   Format(GetValue1());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NewValue = nouvelle valeur					               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::StopMonitoringMode()
{
   SetStopMonitoring(TRUE);
	SetValueIsString(TRUE);
	FValue1.SetText((UBYTE *)"-");
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::StartMonitoringMode()
{
   SetStopMonitoring(FALSE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet						 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::RefreshLanguage()
{
	Label::RefreshLanguage();
   FUnit1.SetTextOnly(GetNameUnit());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Passage en invertion video													 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	InvertVideo   : invertion si TRUE		               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::SetInvertVideo(e_BOOL _InvertVideo)
{
	Label::SetInvertVideo(_InvertVideo);
	FUnit1.SetReverseVideo(_InvertVideo);
	FSep.SetReverseVideo(_InvertVideo);
	FValue1.SetReverseVideo(_InvertVideo);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'affichage														 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::Refresh()
{
	if(!IsStopMonitoring())
   	{
		if(GetIdParam() != NO_ID)
		{
			UWORD16 Value;

			DataBaseAccess::ReadValue(&Value, GetIdParam(), GetDbTarget());

			/*%C Saturation */
			SaturateValue(&Value);
			
			/*%C Gestion du Diviseur */
			Value = Value / Divider;

			SetValue1(Value);
		}
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet															 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::Show()
{
	Refresh();

	Label::Show();

	if(!IsLabelOnly())
   {
		FSep.Show();
		FValue1.Show();
		if(!IsValueIsString())
      {
			FUnit1.Show();
		}
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet															 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::Hide()
{
	FUnit1.Hide();
	FSep.Hide();
	FValue1.Hide();
	Label::Hide();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet															 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::HideAll()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */   
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet																 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::Blink(e_BOOL _Actif)
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
/*%C Increment de la valeur courante											 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::IncreaseValue()
{
	UWORD16 Value = GetValue1();

	/*%C Access to data base */
	if(IncreaseValueOk(&Value))
   {
      SetValue1(Value);
	}
	/*%C Access to data base */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decrement de la valeur courante											 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::DecreaseValue()
{
	UWORD16 Value = GetValue1();

	/*%C Access to data base*/
	if(DecreaseValueOk(&Value))
   {
		SetValue1(Value);
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation d'increment														 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Val : valeur a incrementer					               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé	  														*/
/******************************************************************************/
e_BOOL LabelOneValue::IncreaseValueOk(UWORD16* _Val)
{
   e_BOOL ValueOk;

	if(GetIdParam() != NO_ID)
   {
      *_Val = *_Val * Divider;
      ValueOk = DataBaseAccess::IncrementValue(_Val, GetIdParam(), GetDbTarget());
      *_Val = *_Val / Divider;
      return ValueOk;
	}
	return FALSE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation de decrement													 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Val : valeur a incrementer					               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé	  														*/
/******************************************************************************/
e_BOOL LabelOneValue::DecreaseValueOk(UWORD16* _Val)
{
   e_BOOL ValueOk;

	if(GetIdParam() != NO_ID)
   {
      *_Val = *_Val * Divider;
		ValueOk = DataBaseAccess::DecrementValue(_Val, GetIdParam(), GetDbTarget());
      *_Val = *_Val / Divider;
      return ValueOk;
	}
	return FALSE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification d'un Objet										 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::StartModifMode()
{
	UWORD16 Value;
   DataBaseAccess::ReadValue(&Value, GetIdParam(), GetDbTarget());
   Value = Value / Divider;

	Label::StartModifMode();
   SetValue1(Value);
	SetValueTemp(Value);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet						 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValue::ConfirmModifValue(e_BOOL _Confirm)
{
	if(_Confirm)
   {
		/*%C Acces DB */
		if(GetIdParam() != NO_ID)
      {
			UWORD16 Value = GetValue1();
         	Value = Value * Divider;
			DataBaseAccess::WriteValue(&Value, GetIdParam(), GetDbTarget());

			/*%C Request a short bip sound */
			Tools::ShortBipRequest();
		}
	}
	else
   {
		/*%C affiche l'ancienne valeur */
		SetValue1(GetValueTemp());
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
UWORD16 LabelOneValue::GetFullValue()
{
   return(GetValue1());
}

