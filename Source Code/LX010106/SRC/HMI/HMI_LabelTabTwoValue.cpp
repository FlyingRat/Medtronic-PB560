/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabTwoValue.cpp 	  		           	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + text + value + Value) 								*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelTabTwoValue.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Tools.hpp"
#include "HMI_DataBaseAccess.hpp"

extern "C"
{
#include "stdfile.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelTabTwoValue::LabelTabTwoValue():LabelTabOneValue()
{
	SetColValue2(THIRD_VALUE_COLUMN);
   SetFontValue2(FONT_4);
   FValue2.SetParent(this);
}

/******************************************************************************/
/*                           ACCESSEURS				                				*/
/******************************************************************************/
UWORD16 LabelTabTwoValue::GetValueState()
{
	return ValueState;
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValue::SetValueState(UWORD16 _ValueState)
{
	ValueState = _ValueState;
}
/*----------------------------------------------------------------------------*/
ValueTextField* LabelTabTwoValue::GetFValue2()
{
	return &this->FValue2;
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValue::SetValue2(UWORD16 _Value2)
{
	FValue2.Hide();
	FValue2.SetCol(THIRD_VALUE_COLUMN+
						(COLUMN_WIDTH-
						Tools::GetNumberPixelSize(	_Value2,
															FValue2.GetFont(),
															FValue2.GetFloat()))/2);

	FValue2.SetValue(_Value2);
	FValue2.Show();

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
UWORD16 LabelTabTwoValue::GetValue2()
{
   return FValue2.GetValue();
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTabTwoValue::GetStringValue2()
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
void LabelTabTwoValue::SetColValue2(UWORD16 _ColValue2)
{
	FValue2.SetCol(_ColValue2);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabTwoValue::GetColValue2()
{
	return FValue2.GetCol();
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValue::SetFontValue2(UWORD16 _FontValue2)
{
	FValue2.SetFont(_FontValue2);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabTwoValue::GetFontValue2()
{
   return FValue2.GetFont();
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValue::SetFloatValue2(e_BOOL _Float)
{
	FValue2.SetFloat(_Float);
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabTwoValue::GetFloatValue2()
{
	return FValue2.GetFloat();
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValue::SetNbDigitValue2(UWORD16 _NbDigitValue2)
{
	FValue2.SetNbDigit(_NbDigitValue2);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabTwoValue::GetNbDigitValue2()
{
	return FValue2.GetNbDigit();
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValue::SetDisplayZeroValue2(e_BOOL _DisplayZero)
{
   FValue2.SetDisplayZero(_DisplayZero);
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabTwoValue::GetDisplayZeroValue2()
{
	return FValue2.GetDisplayZero();
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValue::SetValue2IsString(e_BOOL _Flag)
{
   Value2IsString = _Flag;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabTwoValue::IsValue2IsString()
{
	return (e_BOOL)(Value2IsString == TRUE);
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValue::SetIdParam2(UWORD16 _IdParam2)
{
	IdParam2 = _IdParam2;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabTwoValue::GetIdParam2()
{
	return IdParam2;
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValue::SetDbTarget2(e_TYPE_OF_DB_TARGET _DbTarget2)
{
	DbTarget2 = _DbTarget2;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET LabelTabTwoValue::GetDbTarget2()
{
	return DbTarget2;
}

/******************************************************************************/
/*                           METHODES                									*/
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
/*%I		Col    : colonne												         			*/
/*%I		Value1  : Valeur 1											     		         */
/*%I		ValueRefresh : Valeur pour le champ de refresh			  		        	*/
/*%I		Value2  : Valeur 2																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValue::Init(	e_SYMBOL _Icon, 
										UBYTE **_Name,
										UWORD16 _Line,
										UWORD16 _Col,
                         		UWORD16 _Value1, 
                         		UWORD16 _ValueRefresh, 
                         		UWORD16 _Value2)
{
	LabelTabOneValue::Init(_Icon, _Name, _Line, _Col,_Value1,_ValueRefresh);
   SetValue2(_Value2);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des paramettres d'acce a DB											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdParam : Id DB												               	*/
/*%I		DbTarget : Target DB											            		*/
/*%I		IdParamMonitor : Id DB de la valeur monitor					      		*/
/*%I		DbTargetMonitor : Target DB de la valeur monitor			  		    	*/
/*%I		IdParam2 : Id DB de la valeur2													*/
/*%I		DbTarget2 : Target DB de la valeur2												*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValue::InitDbAccess(UWORD16 _IdParam, 
												e_TYPE_OF_DB_TARGET _DbTarget, 
												UWORD16 _IdParamMonitor, 
												e_TYPE_OF_DB_TARGET _DbTargetMonitor,
												UWORD16 _IdParam2, 
												e_TYPE_OF_DB_TARGET _DbTarget2)
{
	LabelTabOneValue::InitDbAccess(	_IdParam,
        										_DbTarget,
        										_IdParamMonitor,
        										_DbTargetMonitor);

	SetIdParamMonitor(_IdParamMonitor);
   SetDbTargetMonitor(_DbTargetMonitor);
   SetIdParam2(_IdParam2);
   SetDbTarget2(_DbTarget2);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Passage en invertion video																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE								  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValue::SetInvertVideo(e_BOOL _InvertVideo)
{
	LabelTabOneValue::SetInvertVideo(_InvertVideo);
	FValue2.SetReverseVideo(_InvertVideo);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de la valeur monitoring														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValue::Refresh()
{
	LabelTabOneValue::Refresh();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de la deuxieme valeur															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValue::RefreshValue2()
{
	if(GetIdParam2() != NO_ID)
	{
		UWORD16 Value;
      DataBaseAccess::ReadValue(	&Value, 
      									GetIdParam2(), 
      									GetDbTarget2());

      Value = Value / GetDivider();
		SetValue2(Value);
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValue::Show()
{
	RefreshValue2();
   LabelTabOneValue::Show();
   FValue2.Show();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValue::Hide()
{
    FValue2.Hide();
    LabelTabOneValue::Hide();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValue::Blink(e_BOOL _Actif)
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

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Increment de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValue::IncreaseValue()
{
	UWORD16 Value;

	switch(GetValueState())
	{
		case 1 : Value = this->GetValue1(); break;
      case 2 : Value = this->GetValue2(); break;
      default : break;      
	}

	if(IncreaseValueOk(&Value))
	{
		switch(GetValueState())
		{
			case 1 : SetValue1(Value); 
						break;
			case 2 : SetValue2(Value); 
						break;
         default : break;                  
		}
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decrement de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValue::DecreaseValue()
{
	UWORD16 Value;

	switch(GetValueState())
	{
		case 1 : Value = GetValue1(); 
					break;
		case 2 : Value = GetValue2(); 
					break;
      default : break;               
	}

	if(DecreaseValueOk(&Value))
	{
		switch(GetValueState())
		{
			case 1 : SetValue1(Value); break;
         case 2 : SetValue2(Value); break;
         default : break;
		}
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation d'increment																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Val : valeur a incrementer											  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé	  														*/
/******************************************************************************/
e_BOOL LabelTabTwoValue::IncreaseValueOk(UWORD16* _Val)
{
   e_BOOL ValueOk;

	if(GetValueState() == 1)
	{
 		return LabelTabOneValue::IncreaseValueOk(_Val);
	}
	else
	{
		if(GetIdParam2() != NO_ID)
		{
         *_Val = *_Val * GetDivider();
			ValueOk = DataBaseAccess::IncrementValue(	_Val,
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
/*%I		Val : valeur a incrementer											  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé	  														*/
/******************************************************************************/
e_BOOL LabelTabTwoValue::DecreaseValueOk(UWORD16* _Val)
{
   e_BOOL ValueOk;

	if(GetValueState() == 1)
	{
		return LabelTabOneValue::DecreaseValueOk(_Val);
	}
	else
	{
		if(GetIdParam2() != NO_ID)
		{
         *_Val = *_Val * GetDivider();
			ValueOk = DataBaseAccess::DecrementValue(	_Val,
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
/*%C Debut de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE	  																					*/
/******************************************************************************/
void LabelTabTwoValue::StartModifMode()
{
	Label::StartModifMode();
   SetValue1(GetValue1());
   SetValueState(1);
   SetValueTemp(GetValue1());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE	  																					*/
/******************************************************************************/
void LabelTabTwoValue::ConfirmModifValue(e_BOOL _Confirm)
{
	if(_Confirm)
	{
		/*%C Acces DB */
		if(GetIdParam2() != NO_ID)
		{
			UWORD16 Value = GetValue2();
         	Value = Value * GetDivider();
			DataBaseAccess::WriteValue(&Value,
												GetIdParam2(),
												GetDbTarget2());
			/*%C Request a short bip sound */
			Tools::ShortBipRequest();

			RefreshValue1();
			RefreshValue2();
		}
	}
	else
	{
		/*%C affiche l'ancienne valeur */
		switch(this->GetValueState())
		{
			case 1: 	SetValue1(GetValueTemp());
						break;
         case 2: 	SetValue2(GetValueTemp());
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
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE	  																					*/
/******************************************************************************/
void LabelTabTwoValue::ModifNextValue()
{
	if(this->GetIdParam() != NO_ID)
	{
		/*%C sauvegarde de la valeur 1 */
		UWORD16 Value = GetValue1();
        Value = Value * GetDivider();
		DataBaseAccess::WriteValue(&Value,
									GetIdParam(),
									GetDbTarget());
											
        /*%C Request a short bip sound */ 
        Tools::ShortBipRequest(); 											
	}
	UWORD16 State = GetValueState();
	if(State<2)
	{
		SetValueState(++State);
	}
	RefreshValue2();
	SetValueTemp(GetValue2());
}


