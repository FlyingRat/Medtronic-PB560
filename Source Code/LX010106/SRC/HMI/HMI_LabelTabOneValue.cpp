/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabOneValue.cpp  	  		  	           	 	  				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + text + value + Value)									*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelTabOneValue.hpp"

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
LabelTabOneValue::LabelTabOneValue():EditableObject()
{
   Value1IsMaxi = FALSE;

	SetColValue1(FIRST_VALUE_COLUMN);
	SetFontValue1(FONT_4);
	
	FValue1.SetParent(this);
	FValueRefresh.SetParent(this);
	FValueRefresh.Init( 	0, 
								SECOND_VALUE_COLUMN, 
								FONT_4, 
								TRUE,
								0, 
								0,
								FALSE, 
								FALSE);

	Value1IsString = FALSE;
	StopMonitoring = TRUE;
	DbTargetMonitor = ADJUST;
	IdParamMonitor = 0;

	TFNoValue.SetParent(this);
	TFNoValue.Init(0,THIRD_VALUE_COLUMN,FONT_4,FALSE,(UBYTE *)"    -");

   Divider = 1;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
ValueTextField* LabelTabOneValue::GetFValue1()
{
	return &this->FValue1;
}
/*----------------------------------------------------------------------------*/
ValueTextField* LabelTabOneValue::GetFValueRefresh()
{
	return &this->FValueRefresh;
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetValue1(UWORD16 _Value1)
{
	UWORD16 col = Value1IsMaxi ? THIRD_VALUE_COLUMN : FIRST_VALUE_COLUMN;

   FValue1.Hide();

   FValue1.SetCol(col+
   					(COLUMN_WIDTH-
   					Tools::GetNumberPixelSize(	_Value1,
 									                 	FValue1.GetFont(),
									                  FValue1.GetFloat()))/2);

	FValue1.SetValue(_Value1);
   FValue1.Show();

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
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabOneValue::GetValue1()
{
	return FValue1.GetValue();
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTabOneValue::GetStringValue1()
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
void LabelTabOneValue::SetValueRefresh(UWORD16 _ValueRefresh)
{
	UWORD16 NewCol =  SECOND_VALUE_COLUMN+
                     (COLUMN_WIDTH-
                     Tools::GetNumberPixelSize(	_ValueRefresh,
                                          		FValueRefresh.GetFont(),
                                          		FValueRefresh.GetFloat()))/2;

	/*%C Inverse l'ordre d'appel des fcts selon les nouvelles coordonnées */
	FValueRefresh.Hide();
	FValueRefresh.SetCol(NewCol);
	FValueRefresh.SetValue(_ValueRefresh);
	FValueRefresh.Show();
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabOneValue::GetValueRefresh()
{
	return FValueRefresh.GetValue();
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetColValue1(UWORD16 _ColValue1)
{
	FValue1.SetCol(_ColValue1);
	if(Value1IsMaxi)
	{
		TFNoValue.SetCol(FIRST_VALUE_COLUMN);
	}
	else
	{
		TFNoValue.SetCol(THIRD_VALUE_COLUMN);
	}
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabOneValue::GetColValue1()
{
	return FValue1.GetCol();
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetFontValue1(UWORD16 _FontValue1)
{
	FValue1.SetFont(_FontValue1);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabOneValue::GetFontValue1()
{
	return FValue1.GetFont();
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetFloatValue1(e_BOOL _Float)
{
	FValue1.SetFloat(_Float);
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabOneValue::GetFloatValue1()
{
	return FValue1.GetFloat();
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetFloatValueRefresh(e_BOOL _Float)
{
	FValueRefresh.SetFloat(_Float);
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabOneValue::GetFloatValueRefresh()
{
	return FValueRefresh.GetFloat();
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetValue1Maxi(e_BOOL _Maxi)
{
	Value1IsMaxi = _Maxi;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabOneValue::IsValue1Maxi()
{
	return Value1IsMaxi;
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetNbDigitValue1(UWORD16 _NbDigitValue1)
{
	FValue1.SetNbDigit(_NbDigitValue1);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabOneValue::GetNbDigitValue1()
{
	return FValue1.GetNbDigit();
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetDisplayZeroValue1(e_BOOL _DisplayZero)
{
	FValue1.SetDisplayZero(_DisplayZero);
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabOneValue::GetDisplayZeroValue1()
{
	return FValue1.GetDisplayZero();
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetValue1IsString(e_BOOL _Flag)
{
	Value1IsString = _Flag;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabOneValue::IsValue1IsString()
{
	return (e_BOOL)(Value1IsString == TRUE);
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetIdParamMonitor(UWORD16 _IdParamMonitor)
{
	IdParamMonitor = _IdParamMonitor;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabOneValue::GetIdParamMonitor()
{
	return IdParamMonitor;
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetDivider(UWORD16 _Divider)
{
	Divider = _Divider;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabOneValue::GetDivider()
{
	return Divider;
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetDbTargetMonitor(e_TYPE_OF_DB_TARGET _DbTargetMonitor)
{
	DbTargetMonitor = _DbTargetMonitor;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET LabelTabOneValue::GetDbTargetMonitor()
{
	return DbTargetMonitor;
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetStopMonitoring(e_BOOL _Flag)
{
	StopMonitoring = _Flag;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabOneValue::IsStopMonitoring()
{
	return (e_BOOL)(StopMonitoring == TRUE);
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetMaxDisplayValue(UWORD16 _MaxDisplayValue)
{
   MaxDisplayValue = _MaxDisplayValue;
   SetMaxDisplayValueConfigured(TRUE);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabOneValue::GetMaxDisplayValue()
{
   return(MaxDisplayValue);
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SetMaxDisplayValueConfigured(e_BOOL _MaxDisplayValueConfigured)
{
   MaxDisplayValueConfigured = _MaxDisplayValueConfigured;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelTabOneValue::IsMaxDisplayValueConfigured()
{
   return(MaxDisplayValueConfigured);
}
/*----------------------------------------------------------------------------*/
void LabelTabOneValue::SaturateValue(UWORD16* _Value)
{
	UWORD16 _max = GetMaxDisplayValue();

	if (IsMaxDisplayValueConfigured())	{
		if (*_Value > _max) {
				*_Value = _max;
        }
	}
}
/******************************************************************************/
/*                           METHODES                					     			*/
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
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::Init(  e_SYMBOL _Icon,
                              UBYTE **_Name,
                              UWORD16 _Line,
                              UWORD16 _Col,
                              UWORD16 _Value1,
                              UWORD16 _ValueRefresh)
{
	Label::Init(_Icon, _Name, _Line, _Col);
	SetValue1(_Value1);
	SetValueRefresh(_ValueRefresh);
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
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::InitDbAccess(UWORD16 _IdParam,
                                    e_TYPE_OF_DB_TARGET _DbTarget,
                                    UWORD16 _IdParamMonitor,
                                    e_TYPE_OF_DB_TARGET _DbTargetMonitor)
{
	MenuObject::InitDbAccess(_IdParam,_DbTarget);
	SetIdParamMonitor(_IdParamMonitor);
	SetDbTargetMonitor(_DbTargetMonitor);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::StopMonitoringMode()
{
   SetStopMonitoring(TRUE);
   FValueRefresh.Hide();
   FValueRefresh.SetCol(SECOND_VALUE_COLUMN+
                        (COLUMN_WIDTH-
                        Tools::GetStringPixelSize
                        ((UBYTE *)"-",
                        FValueRefresh.GetFont()))/2);

   FValueRefresh.SetText((UBYTE *)"-");
   FValueRefresh.Show();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret du monitorage pour _tout_ l'Objet												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::StopAllMonitoringMode()
{
	UWORD16 _col = Value1IsMaxi ? THIRD_VALUE_COLUMN : FIRST_VALUE_COLUMN;
	
   /* Stop du monitoring de la valeur FValueRefresh */
   StopMonitoringMode();

   /* Stop du monitoring pour la valeur FValue1 */
   FValue1.Hide();
   FValue1.SetCol(_col+	(COLUMN_WIDTH -
						Tools::GetStringPixelSize((UBYTE *)"-",
						FValue1.GetFont()))/2);

   FValue1.SetText((UBYTE *)"-");
   FValue1.Show();
   
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::StartMonitoringMode()
{
	SetStopMonitoring(FALSE);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour _tout_ l'Objet											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::StartAllMonitoringMode()
{
	StartMonitoringMode();

	RefreshValue1();

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
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::ConfirmModifValue(e_BOOL _Confirm)
{
	if(_Confirm)
   {
		/*%C Acces DB */
		if(GetIdParam() != NO_ID)
      {
			UWORD16 Value = GetValue1();
         	Value = Value * GetDivider();
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
/*%C Passage en invertion video																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE								  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::SetInvertVideo(e_BOOL _InvertVideo)
{
	Label::SetInvertVideo(_InvertVideo);
	FValue1.SetReverseVideo(_InvertVideo);
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
void LabelTabOneValue::Refresh()
{
	if(!IsStopMonitoring())
   {
    	if(GetIdParamMonitor() != NO_ID)
      {
         UWORD16 Value;
         DataBaseAccess::ReadValue( &Value,
                                    GetIdParamMonitor(),
                                    GetDbTargetMonitor());
		 Value = Value / Divider;

		 /*%C Saturation */
		 SaturateValue(&Value);

         SetValueRefresh(Value);
      }
    }
    else
   {
      FValueRefresh.Hide();
		FValueRefresh.SetCol(SECOND_VALUE_COLUMN+
                           (COLUMN_WIDTH-Tools::GetStringPixelSize
                           ((UBYTE *)"-",FValueRefresh.GetFont()))/2);

      FValueRefresh.SetText((UBYTE *)"-");
      FValueRefresh.Show();
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Force le Refresh de la valeur monitoring											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::ForceRefresh()
{
	if(!IsStopMonitoring())
   {
		if(GetIdParamMonitor() != NO_ID)
      {
			UWORD16 Value;
         DataBaseAccess::ReadValue( &Value,
                                    GetIdParamMonitor(),
                                    GetDbTargetMonitor());

         Value = Value / Divider;
         FValueRefresh.ForceValue(Value);
		}
	}
	else
   {
		FValueRefresh.Hide();
		FValueRefresh.SetCol (SECOND_VALUE_COLUMN+
                           (COLUMN_WIDTH-
                           Tools::GetStringPixelSize
                           ((UBYTE *)"-",
                           FValueRefresh.GetFont()))/2);

		FValueRefresh.SetText((UBYTE *)"-");
		FValueRefresh.Show();
	}
}        

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de la premiere valeur															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::RefreshValue1()
{

   if(GetIdParam() != NO_ID)
   {
		UWORD16 Value;
		DataBaseAccess::ReadValue(	&Value,
											GetIdParam(),
											GetDbTarget());
		Value = Value / Divider;
		SetValue1(Value);
	}
#if 0
   if(IsStopMonitoring())
   {
	  UWORD16 _col = Value1IsMaxi ? THIRD_VALUE_COLUMN : FIRST_VALUE_COLUMN;
	  FValue1.Hide();
	  FValue1.SetCol( _col +
						(COLUMN_WIDTH-
						Tools::GetStringPixelSize
						((UBYTE *)"-",
						FValue1.GetFont()))/2);

	  FValue1.SetText((UBYTE *)"-");
	  FValue1.Show();
   }
#endif   
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
void LabelTabOneValue::Show()
{
	RefreshValue1();

	Label::Show();
	TFNoValue.Show();
	FValue1.Show();
	FValueRefresh.Show();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet 																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::Hide()
{
	FValue1.Hide();
	FValueRefresh.Hide();
	Label::Hide();    
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet 																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::Blink(e_BOOL _Actif)
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
/*%C Increment de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabOneValue::IncreaseValue()
{
	UWORD16 Value = GetValue1();

	if(IncreaseValueOk(&Value))
   {
		SetValue1(Value);
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
void LabelTabOneValue::DecreaseValue()
{
	UWORD16 Value = GetValue1();

	if(DecreaseValueOk(&Value))
   {
		SetValue1(Value);
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
e_BOOL LabelTabOneValue::IncreaseValueOk(UWORD16* _Val)
{
   e_BOOL ValueOk;

	if(GetIdParam() != NO_ID)
   {
      *_Val = *_Val * Divider;
      ValueOk = DataBaseAccess::IncrementValue(	_Val,
													GetIdParam(),
                                       GetDbTarget());
      *_Val = *_Val / Divider;
      return ValueOk;
	}
	return FALSE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation de decrement																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Val : valeur a decrementer											  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si decrement autorisé	  														*/
/******************************************************************************/
e_BOOL LabelTabOneValue::DecreaseValueOk(UWORD16* _Val)
{
   e_BOOL ValueOk;

	if(GetIdParam() != NO_ID)
   {
      *_Val = *_Val * Divider;
		ValueOk = DataBaseAccess::DecrementValue(	_Val,
													GetIdParam(),
                                       GetDbTarget());
      *_Val = *_Val / Divider;
      return ValueOk;
	}
	return FALSE;
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
/*%O 		NONE								  														*/
/******************************************************************************/

void LabelTabOneValue::StartModifMode()
{
	Label::StartModifMode();
	SetValue1(GetValue1());
	SetValueTemp(GetValue1());
}

