/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTwoValue.cpp 	  		   	      	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + Text + sep + value					 					*/
/*%C   + unit + value + unit 																	*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelTwoValue.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"

extern "C"
{
#include "stdfile.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelTwoValue::LabelTwoValue():LabelOneValue()
{
   /*%C Init Parent */

   FUnit2.SetParent(this);
   FValue2.SetParent(this);

   SetColValue2(104);
   SetColUnit2(128);
   SetFontValue2(FONT_4);
   SetLabelOnly(FALSE);
   ValueState = 1;
   SetIdParam2(NO_ID);
   SetDbTarget2(ADJUST);
   SetColAdjust(FALSE);
   SetDivider2(1);
   MaxDisplayValue2Configured = FALSE;
   MaxDisplayValue2 = 0xFFFF;
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelTwoValue::SetIdParam2(UWORD16 _IdParam2)
{
   IdParam2 = _IdParam2;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoValue::GetIdParam2()
{
   return IdParam2;
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetDbTarget2(e_TYPE_OF_DB_TARGET _DbTarget2)
{
   DbTarget2 = _DbTarget2;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET LabelTwoValue::GetDbTarget2()
{
   return DbTarget2;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoValue::GetValueState()
{
   return ValueState;
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetValueState(UWORD16 _ValueState)
{
   ValueState = _ValueState;
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetNameUnit2(UBYTE** _NameUnit2)
{
   NameUnit2 = _NameUnit2;

   SetUnit2(GetNameUnit2());
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetTextValue2(UBYTE* _TextValue2)
{
	FValue2.SetText((UBYTE*) _TextValue2);
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTwoValue::GetNameUnit2()
{
   if(NameUnit2 != NULL)
   {
      return (NameUnit2[GetLanguage()]);
   }
   else
	{
      return (UBYTE *)"???";
	}
}
/*----------------------------------------------------------------------------*/
TextField* LabelTwoValue::GetFUnit2()
{
   return &this->FUnit2;
}
/*----------------------------------------------------------------------------*/
ValueTextField* LabelTwoValue::GetFValue2()
{
	return &this->FValue2;
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetUnit2(UBYTE *_Unit2)
{
   FUnit2.SetText(_Unit2);
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTwoValue::GetUnit2()
{
   return FUnit2.GetText();
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetMaxDisplayValue2(UWORD16 _MaxDisplayValue2)
{
   MaxDisplayValue2 = _MaxDisplayValue2;
   SetMaxDisplayValue2Configured(TRUE);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoValue::GetMaxDisplayValue2()
{
   return(MaxDisplayValue2);
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetMaxDisplayValue2Configured(e_BOOL _MaxDisplayValue2Configured)
{
   MaxDisplayValue2Configured = _MaxDisplayValue2Configured;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTwoValue::IsMaxDisplayValue2Configured()
{
   return(MaxDisplayValue2Configured);
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SaturateValue2(UWORD16* _Value)
{
	UWORD16 _max = GetMaxDisplayValue2();
	UWORD16 _abs = 0;

	if (IsMaxDisplayValue2Configured())
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
void LabelTwoValue::SetValue2(UWORD16 _Value2)
{
//   _Value2 = _Value2 / GetDivider();

   /*%C Gestion du deplacement de l'unite */
	if(Tools::FindNbDigit(_Value2) != Tools::FindNbDigit(FValue2.GetValue()))
   {
	  FUnit2.Hide();
	  if(GetColAdjust() && GetNbDigitsChanged())
	  {
		 FValue2.SetCol(GetEndColValue1());
	  }

		FValue2.SetValue(_Value2);
		Format2(_Value2);
		FUnit2.Show();
	}
	else
   {
	  if(GetColAdjust() && GetNbDigitsChanged())
	  {
		 FUnit2.Hide();
		 FValue2.SetCol(GetEndColValue1());
		 FValue2.SetValue(_Value2);
		 FValue2.Show();
		Format2(_Value2);
		FUnit2.Show();
	  }
	  else
		 FValue2.SetValue(_Value2);
	}

   FValue2.SetValue(_Value2);

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
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoValue::GetValue2()
{
   return FValue2.GetValue();
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTwoValue::GetStringValue2()
{
#ifdef  _BORLAND
   UWORD16 _Value, _Divider;
   FLOAT32 _FValue;
   _Divider = GetDivider();

   if(GetFloatValue1())
   {
	  _FValue = ((FLOAT32) FValue2.GetValue()) / _Divider / 10;
	  sprintf(	DisplayObject::StringValue2,"%2.1f", _FValue);
   }
   else
   {
	  _Value = FValue2.GetValue() / _Divider;
	  sprintf(	DisplayObject::StringValue2,"%d", _Value);
   }
   return((UBYTE* ) DisplayObject::StringValue2);
#else
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
	return((UBYTE* )"");
#endif
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetColValue2(UWORD16 _ColValue2)
{
   FValue2.SetCol(_ColValue2);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoValue::GetColValue2()
{
   return FValue2.GetCol();
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetColUnit2(UWORD16 _ColUnit2)
{
   FUnit2.SetCol(_ColUnit2);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoValue::GetColUnit2()
{
   return FUnit2.GetCol();
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetFontValue2(UWORD16 _FontValue2)
{
   FValue2.SetFont(_FontValue2);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoValue::GetFontValue2()
{
   return FValue2.GetFont();
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetFloatValue2(e_BOOL _Float)
{
   FValue2.SetFloat(_Float);
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTwoValue::GetFloatValue2()
{
   return  FValue2.GetFloat();
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetNbDigitValue2(UWORD16 _NbDigitValue2)
{
   FValue2.SetNbDigit(_NbDigitValue2);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoValue::GetNbDigitValue2()
{
   return FValue2.GetNbDigit();
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetDisplayZeroValue2(e_BOOL _DisplayZero)
{
   FValue2.SetDisplayZero(_DisplayZero);
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTwoValue::GetDisplayZeroValue2()
{
   return FValue2.GetDisplayZero();
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetLabelOnly(e_BOOL _LabelOnly)
{
   LabelOneValue::SetLabelOnly(_LabelOnly);
   if(!_LabelOnly)
   {
	  FUnit2.Show();
	  FValue2.Show();
   }
   else
   {
	  FUnit2.Hide();
	  FValue2.Hide();
   }
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetColAdjust(e_BOOL _Adjust)
{
   ColAdjust =  _Adjust;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTwoValue::GetColAdjust()
{
   return(ColAdjust);
}
/*----------------------------------------------------------------------------*/
void LabelTwoValue::SetDivider2(UWORD16 _Divider2)
{
   Divider2 = _Divider2;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoValue::GetDivider2()
{
   return(Divider2);
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
/*%I		Icon   : icone												               		*/
/*%I		Name   : Pointeur sur le tableau de nom						         	*/
/*%I		Line   : ligne 												               	*/
/*%I		Col    : colonne												            		*/
/*%I		Value1  : Valeur1												            		*/
/*%I		NameUnit1    : nom unit 1										         		*/
/*%I		Value2  : Valeur2												            		*/
/*%I		NameUnit2    : nom du unit2														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::Init(  e_SYMBOL _Icon,
                           UBYTE **_Name,
                           UWORD16 _Line,
                           UWORD16 _Col,
                           UWORD16 _Value1,
                           UBYTE **_NameUnit1,
                           UWORD16 _Value2,
                           UBYTE **_NameUnit2)
{
   LabelOneValue::Init(_Icon, _Name, _Line, _Col, _Value1, _NameUnit1);
   SetValue2(_Value2);
   SetNameUnit2(_NameUnit2);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des paramettres d'acce a DB											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdParam : Id DB													               */
/*%I		DbTarget : Target DB											            		*/
/*%I		IdParam2 : Id DB de la valeur2								            	*/
/*%I		DbTarget2 : Target DB	de la valeur2								 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::InitDbAccess(UWORD16 _IdParam,
                                 e_TYPE_OF_DB_TARGET _DbTarget,
                                 UWORD16 _IdParam2,
                                 e_TYPE_OF_DB_TARGET _DbTarget2)
{
   LabelOneValue::InitDbAccess(_IdParam,_DbTarget);
   SetIdParam2(_IdParam2);
   SetDbTarget2(_DbTarget2);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::StopMonitoringMode()
{
   LabelOneValue::StopMonitoringMode();
   FValue2.SetText((UBYTE *)"-");
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::StartMonitoringMode()
{
   LabelOneValue::StartMonitoringMode();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::RefreshLanguage()
{
   LabelOneValue::RefreshLanguage();
	FUnit2.SetTextOnly(GetNameUnit2());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Passage en invertion video																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE									 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::SetInvertVideo(e_BOOL _InvertVideo)
{
   LabelOneValue::SetInvertVideo(_InvertVideo);
   FUnit2.SetReverseVideo(_InvertVideo);
   FValue2.SetReverseVideo(_InvertVideo);
}

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
void LabelTwoValue::Refresh()
{
   LabelOneValue::Refresh();
   if(!IsStopMonitoring())
   {
	  if(GetIdParam2() != NO_ID)
	  {
		 UWORD16 Value;
		 DataBaseAccess::ReadValue(	&Value,
											GetIdParam2(),
											GetDbTarget2());

		 /*%C Saturation */
		 SaturateValue2(&Value);

		 Value = Value / GetDivider();
		 SetValue2(Value);
	  }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE									 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::Show()
{
   Refresh();
   LabelOneValue::Show();
   if(!IsLabelOnly())
   {
      FUnit2.Show();
      FValue2.Show();
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE									 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::Hide()
{
   FUnit2.Hide();
   FValue2.Hide();
   LabelOneValue::Hide();   
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
void LabelTwoValue::HideAll()
{
   FUnit2.Hide();
   FValue2.Hide();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE									 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::Blink(e_BOOL _Actif)
{
   if(IsLabelOnly())
   {
      Label::Blink(_Actif);
   }
   else
   {
      switch(GetValueState())
      {
         case 1 : GetFValue1()->Blink(_Actif);
                  break;
         case 2 : FValue2.Blink(_Actif);
                  break;
         default : break;                  
      }

      if(GetLoupe() != NULL)
      {
         GetLoupe()->Blink(_Actif);
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE									 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::StartModifMode()
{
   LabelOneValue::StartModifMode();
   SetValueState(1);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Increment de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE									 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::IncreaseValue()
{
   UWORD16 Value;

   if(GetValueState() == 1)
   {
      LabelOneValue::IncreaseValue();
   }
   else
   {
      Value = GetValue2();
      if(IncreaseValueOk(&Value))
      {
         SetValue2(Value);
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decrement de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE									 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::DecreaseValue()
{
   UWORD16 Value;

   if(GetValueState() == 1)
   {
      LabelOneValue::DecreaseValue();
   }
   else
   {
      Value = GetValue2();
      if(DecreaseValueOk(&Value))
      {
         SetValue2(Value);
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation d'increment																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Val : valeur a incrementer												 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé	  														*/
/******************************************************************************/
e_BOOL LabelTwoValue::IncreaseValueOk(UWORD16* _Val)
{
   e_BOOL ValueOk;

   if(GetValueState() == 1)
   {
      *_Val = *_Val * GetDivider();
      return LabelOneValue::IncreaseValueOk(_Val);
   }
   else
   {
      if(GetIdParam2() != NO_ID)
      {
         *_Val = *_Val * GetDivider();
         ValueOk = DataBaseAccess::IncrementValue( _Val,
                                                GetIdParam2(),
                                                GetDbTarget2());
         *_Val = *_Val / GetDivider();
         return ValueOk;
      }
      return FALSE;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation de decrement																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Val : valeur a incrementer												 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé	  														*/
/******************************************************************************/
e_BOOL LabelTwoValue::DecreaseValueOk(UWORD16* _Val)
{
   e_BOOL ValueOk;

   if(GetValueState() == 1)
   {
      *_Val = *_Val * GetDivider();
      return LabelOneValue::DecreaseValueOk(_Val);
   }
   else
   {
      if(GetIdParam2() != NO_ID)
      {
      *_Val = *_Val * GetDivider();
      ValueOk = DataBaseAccess::DecrementValue( _Val,
                                             GetIdParam2(),
                                             GetDbTarget2());
      *_Val = *_Val / GetDivider();
      return ValueOk;
      }
      return FALSE;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::ConfirmModifValue(e_BOOL _Confirm)
{
   if(_Confirm)
   {
      if(GetIdParam2() != NO_ID)
      {
         /*%C Acces DB */
         UWORD16 Value = GetValue2();
         Value = Value * GetDivider();
         DataBaseAccess::WriteValue(&Value,
         									GetIdParam2(), 
         									GetDbTarget2());
		 /*%C Request a short bip sound */
		 Tools::ShortBipRequest();

         LabelOneValue::Refresh();
      }
   }
   else
   {
      /*%C affiche l'ancienne valeur */
      switch(GetValueState())
      {
         case 1:  SetValue1(GetValueTemp());
                  break;
         case 2:  SetValue2(GetValueTemp());
                  break;
         default : break;                  
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Changement de la valeur en modification												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValue::ModifNextValue()
{
   UWORD16 State = GetValueState();
   if(State<2)
   {
      SetValueState(++State);
   }
   SetValueTemp(GetValue2());
   SetValue2(GetValue2());

   /*%C sauvegarde de la valeur 1 */
   if(GetIdParam() != NO_ID)
   {
      UWORD16 Value = GetValue1();
      Value = Value * GetDivider();
      DataBaseAccess::WriteValue(&Value, GetIdParam(), GetDbTarget());
   }
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
void LabelTwoValue::Format2(UWORD16 NewValue)
{
	UWORD16 Col = 0;
	SWORD16 ValueSign;

	//Gestion des negatifs
	if(IsSignValue())
   {
		ValueSign = (SWORD16)NewValue;
		if(ValueSign<0)
      {
			Col += Tools::GetStringPixelSize((UBYTE *)"-", FValue2.GetFont());
		}
		NewValue = abs(ValueSign);
	}

	/*%C Si on affiche des 0 devant */
	if(GetDisplayZeroValue2())
		Col += 1 + Tools::GetNumberPixelSize(  0,
															FValue2.GetFont(),
                                             GetFloatValue2()) *
                                             GetNbDigitValue2();
	else
		Col += 1 + Tools::GetNumberPixelSize(  NewValue,
                                             FValue2.GetFont(),
                                             GetFloatValue2());

	Col += GetColValue2();
	SetColUnit2(Col);
}

