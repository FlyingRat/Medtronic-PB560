/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTwoStringsTwoItems.cpp  	    	          	  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage (icon + text + String + String) avec 2 valeurs         */
/*%C possibles	pour les strings		                                          */
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelTwoStringsTwoItems.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelTwoStringsTwoItems::LabelTwoStringsTwoItems():LabelStringTwoItems()
{
   Value2Item1Name = NULL;
   Value2Item2Name = NULL;      
   SetFontValue2(FONT_4);
   FValue2.SetParent(this);
   FSep2.SetParent(this);
   FSep2.SetText((UBYTE *)"-");
   SetCallBackPtr(NULL);
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
T_CallBackPtr LabelTwoStringsTwoItems::GetCallBackPtr()
{
   return(CallBackPtr);
}
/*----------------------------------------------------------------------------*/
void LabelTwoStringsTwoItems::SetCallBackPtr(T_CallBackPtr _CallBackPtr)
{
   CallBackPtr = (T_CallBackPtr) _CallBackPtr;
}
/*----------------------------------------------------------------------------*/
void LabelTwoStringsTwoItems::SetIdParam2(UWORD16 _IdParam2)
{
	IdParam2 = _IdParam2;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoStringsTwoItems::GetIdParam2()
{
	return IdParam2;
}                
/*----------------------------------------------------------------------------*/
void LabelTwoStringsTwoItems::SetDbTarget2(e_TYPE_OF_DB_TARGET _DbTarget2)
{
	DbTarget2 = _DbTarget2;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET LabelTwoStringsTwoItems::GetDbTarget2()
{
	return DbTarget2;
}
/*----------------------------------------------------------------------------*/
void LabelTwoStringsTwoItems::SetIntValue2(UWORD16 _IntValue2)
{
   IntValue2 = _IntValue2;
   SetValue2(GetValue2Name());
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoStringsTwoItems::GetIntValue2()
{
   return IntValue2;
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoStringsTwoItems::GetValueState()
{
	return ValueState;
}
/*----------------------------------------------------------------------------*/
void LabelTwoStringsTwoItems::SetValueState(UWORD16 _ValueState)
{
	ValueState = _ValueState;
}
/*----------------------------------------------------------------------------*/
void LabelTwoStringsTwoItems::SetValue2Item1Name(UBYTE** _Value2Item1Name)
{
   Value2Item1Name = _Value2Item1Name;
   SetValue2(GetValue2Name());
}
/*----------------------------------------------------------------------------*/
void LabelTwoStringsTwoItems::SetValue2Item2Name(UBYTE** _Value2Item2Name)
{
   Value2Item2Name = _Value2Item2Name;
   SetValue2(GetValue2Name());
}
/*----------------------------------------------------------------------------*/
void LabelTwoStringsTwoItems::SetValue2(UBYTE* _Value2)
{
   FValue2.SetText(_Value2);
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTwoStringsTwoItems::GetValue2()
{
   return FValue2.GetText();
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTwoStringsTwoItems::GetValue2Item1Name()
{
   if(Value2Item1Name != NULL)
   {
      return (Value2Item1Name[GetLanguage()]);
   }
   else
	{
      return (UBYTE *)"???";
	}
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTwoStringsTwoItems::GetValue2Item2Name()
{
   if(Value2Item2Name != NULL)
   {
      return (Value2Item2Name[GetLanguage()]);
   }
   else
	{
      return (UBYTE *)"???";
	}
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTwoStringsTwoItems::GetValue2Name()
{
   UWORD16 Value = GetIntValue2();

   switch(Value)
   {
      case 0  : return GetValue2Item1Name();
      case 1  : return GetValue2Item2Name();
      default : return (UBYTE *)"???";
   }
}
/*----------------------------------------------------------------------------*/
void LabelTwoStringsTwoItems::SetFontValue2(UWORD16 _FontValue2)
{
	FValue2.SetFont(_FontValue2);
   FSep2.SetFont(_FontValue2);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTwoStringsTwoItems::GetFontValue2()
{
   return FValue2.GetFont();
}
/*----------------------------------------------------------------------------*/
void LabelTwoStringsTwoItems::SetColValue2(UWORD16 _Col)
{
   FValue2.SetCol(_Col);
}
/*----------------------------------------------------------------------------*/
void LabelTwoStringsTwoItems::SetColSep2(UWORD16 _Col)
{
   FSep2.SetCol(_Col);
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 	 																		*/
/*%I		Icon   : icone												               		*/
/*%I		Name   : Pointeur sur le tableau de nom						         	*/
/*%I		Line   : ligne 												               	*/
/*%I		Col    : colonne												         			*/
/*%I		Value1  : Valeur 1											     		         */
/*%I		Value2  : Valeur 2																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoStringsTwoItems::Init(	e_SYMBOL _Icon,
										UBYTE **_Name,
										UWORD16 _Line,
										UWORD16 _Col,
										UWORD16 _Value1,
										UWORD16 _Value2)

{
	LabelStringTwoItems::Init(_Icon, _Name, _Line, _Col);
   SetIntValue1(_Value1);
   SetIntValue2(_Value2);
   FValue2.SetCol(220);
   FSep2.SetCol(210);
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
void LabelTwoStringsTwoItems::SetInvertVideo(e_BOOL _InvertVideo)
{
	LabelStringTwoItems::SetInvertVideo(_InvertVideo);
	FValue2.SetReverseVideo(_InvertVideo);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des paramettres d'acce a DB											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdParam : Id DB												               	*/
/*%I		DbTarget : Target DB											            		*/
/*%I		IdParam2 : Id DB de la valeur2													*/
/*%I		DbTarget2 : Target DB de la valeur2												*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoStringsTwoItems::InitDbAccess(UWORD16 _IdParam,
												e_TYPE_OF_DB_TARGET _DbTarget,
												UWORD16 _IdParam2,
												e_TYPE_OF_DB_TARGET _DbTarget2)
{
	LabelStringTwoItems::InitDbAccess(	_IdParam, _DbTarget);

   SetIdParam2(_IdParam2);
   SetDbTarget2(_DbTarget2);
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
void LabelTwoStringsTwoItems::IncreaseValue()
{
	UWORD16 Value;

	switch(GetValueState())
	{
		case 1 : Value = this->GetIntValue1(); break;
      case 2 : Value = this->GetIntValue2(); break;
      default : break;      
	}

	if(IncreaseValueOk(&Value))
	{
		switch(GetValueState())
		{
			case 1 : SetIntValue1(Value);
						break;
			case 2 : SetIntValue2(Value);
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
void LabelTwoStringsTwoItems::DecreaseValue()
{
	UWORD16 Value;

	switch(GetValueState())
	{
		case 1 : Value = GetIntValue1(); 	break;
		case 2 : Value = GetIntValue2();		break;
      default : break;
	}

	if(DecreaseValueOk(&Value))
	{
		switch(GetValueState())
		{
			case 1 : SetIntValue1(Value); break;
         case 2 : SetIntValue2(Value); break;
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
void LabelTwoStringsTwoItems::ModifNextValue()
{
	if(this->GetIdParam() != NO_ID)
	{
		/*%C sauvegarde de la valeur 1 */
		UWORD16 Value = GetIntValue1();
		DataBaseAccess::WriteValue(&Value,
											GetIdParam(),
											GetDbTarget());
	}
	UWORD16 State = GetValueState();
	if(State<2)
	{
		SetValueState(++State);
	}
	RefreshValue2();
	SetValueTemp(GetIntValue2());
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
void LabelTwoStringsTwoItems::StartModifMode()
{
	Label::StartModifMode();
   SetIntValue1(GetIntValue1());
   SetValueState(1);
   SetValueTemp(GetIntValue1());

   if(GetCallBackPtr())
   {
      (*CallBackPtr) ();
   }
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
void LabelTwoStringsTwoItems::ConfirmModifValue(e_BOOL _Confirm)
{
	if(_Confirm)
	{
		/*%C Acces DB */
		if(GetIdParam2() != NO_ID)
		{
			UWORD16 Value = GetIntValue2();
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
			case 1: 	SetIntValue1(GetValueTemp());
						break;
         case 2: 	SetIntValue2(GetValueTemp());
         			break;
         default : break;                  
		}
	}
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de la première valeur															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoStringsTwoItems::RefreshValue1()
{
	if(GetIdParam() != NO_ID)
	{
		UWORD16 Value;
      DataBaseAccess::ReadValue(	&Value,
      									GetIdParam(),
      									GetDbTarget());

		SetIntValue1(Value);
	}
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
void LabelTwoStringsTwoItems::RefreshValue2()
{
	if(GetIdParam2() != NO_ID)
	{
		UWORD16 Value;
      DataBaseAccess::ReadValue(	&Value,
      									GetIdParam2(),
      									GetDbTarget2());

		SetIntValue2(Value);
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
e_BOOL LabelTwoStringsTwoItems::DecreaseValueOk(UWORD16* _Val)
{
   e_BOOL ValueOk;

	if(GetValueState() == 1)
	{
		return LabelStringTwoItems::DecreaseValueOk(_Val);
	}
	else
	{
		if(GetIdParam2() != NO_ID)
		{
			ValueOk = DataBaseAccess::DecrementValue(	_Val,
														GetIdParam2(),
                                          GetDbTarget2());
         return ValueOk;
		}
		return FALSE;
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
e_BOOL LabelTwoStringsTwoItems::IncreaseValueOk(UWORD16* _Val)
{
   e_BOOL ValueOk;

	if(GetValueState() == 1)
	{
 		return LabelStringTwoItems::IncreaseValueOk(_Val);
	}
	else
	{
		if(GetIdParam2() != NO_ID)
		{
			ValueOk = DataBaseAccess::IncrementValue(	_Val,
                                          GetIdParam2(),
                                          GetDbTarget2());
         return ValueOk;
		}
		return FALSE;
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
void LabelTwoStringsTwoItems::Show()
{
	RefreshValue2();
   LabelStringTwoItems::Show();
   FValue2.Show();
   FSep2.Show();
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
void LabelTwoStringsTwoItems::Hide()
{
	LabelStringTwoItems::Hide();
   FValue2.Hide();
   FSep2.Hide();   
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
void LabelTwoStringsTwoItems::Blink(e_BOOL _Actif)
{
	switch(GetValueState())
	{
		case 1 : GetFValue1()->Blink(_Actif); 
					break;
		case 2 : FValue2.Blink(_Actif); 
					break;
      default : break;               
	}
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
void LabelTwoStringsTwoItems::Refresh()
{
   if(this->GetIdParam() != NO_ID)
   {
      UWORD16 Value;
      DataBaseAccess::ReadValue(&Value, GetIdParam(), GetDbTarget());
      SetIntValue1(Value);
   }
   if(this->GetIdParam2() != NO_ID)
   {
      UWORD16 Value;
      DataBaseAccess::ReadValue(&Value, GetIdParam2(), GetDbTarget2());
      SetIntValue2(Value);
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
UWORD16 LabelTwoStringsTwoItems::GetFullValue()
{
   return(GetIntValue2());
}

