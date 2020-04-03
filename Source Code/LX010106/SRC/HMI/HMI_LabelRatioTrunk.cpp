/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelRatioTrunk.cpp 	   	         	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + Text + sep + value					 					*/
/*%C   + unit + value + unit)																	*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelRatioTrunk.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelRatioTrunk::LabelRatioTrunk():LabelRatio()
{
 Threshold = FALSE;
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelRatioTrunk::SetAllVisible(e_BOOL _Visible)
{
   SetVisible(_Visible);
   GetFValue1()->SetVisible(_Visible);
   GetFUnit1()->SetVisible(_Visible);
   GetFValue2()->SetVisible(_Visible);
}
/*-----------------------------------------------------------------------------*/
void LabelRatioTrunk::SetValueState(UWORD16 ValueState)
{
	/* ValueState is forced to 2 to avoid modifying the numerator */
	LabelTwoValue::SetValueState(2);
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
void LabelRatioTrunk::Init(  e_SYMBOL _Icon,
                           UBYTE **_Name,
                           UWORD16 _Line,
                           UWORD16 _Col,
                           UWORD16 _Value1,
                           UBYTE **_NameUnit1,
                           UWORD16 _Value2,
                           UBYTE **_NameUnit2)
{
   LabelRatio::Init( _Icon,
                        _Name,
                        _Line,
                        _Col,
                        _Value1,
                        _NameUnit1,
                        _Value2,
                        _NameUnit2);
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
void LabelRatioTrunk::StartModifMode()
{

   UWORD16 Value1;

   SetAllVisible(FALSE);

   DataBaseAccess::ReadValue(&Value1, GetIdParam(), GetDbTarget());
   Value1 = Value1 / GetDivider();
   if(Value1 == 10)
      SetFloatValue1(FALSE);

   UWORD16 Value2;
   DataBaseAccess::ReadValue(&Value2, GetIdParam2(), GetDbTarget2());
   Value2 = Value2 / GetDivider2();

   if(Value2 == 10)
      SetFloatValue2(FALSE);

   SetAllVisible(TRUE);

	Label::StartModifMode();

   if((Value1 == 10))
   {
      SetValue1(1);

      if(Value2 == 10)
      {
         SetValue2(1);
         SetFloatValue2(FALSE);
         Threshold = TRUE;
      }
      else
      {
         SetValue2(Value2);
         SetFloatValue2(TRUE);
      }
      SetValueState(2);
   }
   else
   {
      if(Value2 == 10)
      {
         SetValue2(1);
         SetFloatValue2(FALSE);
      }
      else
      {
         SetValue2(Value2);
         SetFloatValue2(TRUE);
      }
      SetValue1(Value1);
      SetValueState(1);
   }
   SetValueTemp(Value1);
   SetValue2Temp(Value2);
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
void LabelRatioTrunk::IncreaseValue()
{
   UWORD16 Value2;

   if(GetValueState() == 1)
   {
      /* Numérateur */
      if(Threshold)
      {
         /* Si on est au seuil */
         HideAll();
         SetAllVisible(FALSE);
		 SetValue1(1);
         SetFloatValue1(FALSE);
		 Threshold = FALSE;
		 SetVisible(TRUE);
		 LabelOneValue::IncreaseValue();
		 RefreshValueColumn();
		 SetAllVisible(TRUE);
		 ShowAll();
	  }
	  else
	  {
		 /* hors seuil : comportement normal */
		 LabelOneValue::IncreaseValue();
	  }
   }
   else
   {
	  /* Dénominateur */
	  Value2 = GetValue2();
	  if(DecreaseValueOk(&Value2) && (Value2 != 1))
	  {
		 if(Value2 == 10)
         {
            Threshold = TRUE;
            HideAll();
            SetAllVisible(FALSE);
            SetFloatValue2(FALSE);
            SetValue1(1);
            SetFloatValue1(FALSE);
            SetValueState(1);
            RefreshValueColumn();
            SetAllVisible(TRUE);
            SetValue2(1);
            ShowAll();
         }
         else
         {
            SetValue2(Value2);
         }
      }
      else
      {
         /* On ne peut pas incrémenter le dénominateur, on passe donc au numérateur */
         SetValueState(1);
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
void LabelRatioTrunk::DecreaseValue()
{
   UWORD16 Value1;
   UWORD16 Value2;   

   if(GetValueState() == 1)
   {
      /* Numérateur */
      Value1 = LabelOneValue::GetValue1();
      if(LabelOneValue::DecreaseValueOk(&Value1) && (Value1 != 1))
      {
         if(Value1 == 10)
         {
            Threshold = TRUE;         
            HideAll();
            SetAllVisible(FALSE);
            SetFloatValue1(FALSE);
            SetValue2(1);
            SetFloatValue2(FALSE);
            SetValueState(2);
            SetValue1(1);
            RefreshValueColumn();
            SetAllVisible(TRUE);
            ShowAll();
         }
         else
         {
            SetValue1(Value1);
         }
      }
      else
      {
         /* On ne peut pas décrémenter le numérateur, on passe donc au dénominateur */
         SetValueState(2);         
      }
   }
   else
   {
      if(Threshold)
      {
         /* Si on est au seuil */
         SetVisible(FALSE);
         SetValue2(10);
         SetFloatValue2(TRUE);
         Threshold = FALSE;
         SetVisible(TRUE);
         Value2 = GetValue2();
         if(IncreaseValueOk(&Value2))
         {
            SetValue2(Value2);
         }
         RefreshValueColumn();
         ShowAll();
      }
      else
      {
         /* hors seuil : comportement normal */
         /* Dénominateur */
         Value2 = GetValue2();
         if(IncreaseValueOk(&Value2))
         {
            SetValue2(Value2);
         }
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
e_BOOL LabelRatioTrunk::IncreaseValueOk(UWORD16* _Val)
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
e_BOOL LabelRatioTrunk::DecreaseValueOk(UWORD16* _Val)
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
void LabelRatioTrunk::ConfirmModifValue(e_BOOL _Confirm)
{
   UWORD16 Value;
   e_BOOL ValidParam = FALSE;
   
   if(_Confirm)
   {
      if(GetIdParam2() != NO_ID)
      {
         /*%C Acces DB */
         Value = GetValue2();
         Value = Value * GetDivider2();
         if(Value == 1)
            Value = 10;
         DataBaseAccess::WriteValue(&Value,
         									GetIdParam2(), 
         									GetDbTarget2());
		 ValidParam = TRUE;
      }

      if(LabelOneValue::GetIdParam() != NO_ID)
      {
         /*%C Acces DB */
         Value = LabelOneValue::GetValue1();
         Value = Value * LabelOneValue::GetDivider();
         if(Value == 1)
            Value = 10;
         DataBaseAccess::WriteValue(&Value,
         									LabelOneValue::GetIdParam(),
         									LabelOneValue::GetDbTarget());
		 ValidParam = TRUE;
      }
	  if(ValidParam)
	  {
	  	/*%C Request a short bip sound */
		Tools::ShortBipRequest();
	  }
   }
   else
   {
      /*%C affiche l'ancienne valeur */
      if((GetValueTemp() == 10) ||(GetValueTemp() == 1)) 
      {
         SetFloatValue1(FALSE);
         SetValue1(1);
         
         if((GetValue2Temp() == 10) ||(GetValue2Temp() == 1))
         {
            SetFloatValue2(FALSE);
            SetValue2(1);
         }
         else
         {
            SetFloatValue2(TRUE);
            SetValue2(GetValue2Temp());
         }
      }
      else
      {
         SetFloatValue1(TRUE);
         SetValue1(GetValueTemp());

         if((GetValue2Temp() == 10) ||(GetValue2Temp() == 1))
         {
            SetFloatValue2(FALSE);
            SetValue2(1);
         }
         else
         {
            SetFloatValue2(TRUE);
            SetValue2(GetValue2Temp());
         }
      }
      HideAll();
      SetAllVisible(FALSE);
      RefreshValueColumn();
      SetAllVisible(TRUE);
      ShowAll();
   }
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
void LabelRatioTrunk::Refresh()
{
   UWORD16 Value1;
   UWORD16 Value2;

   if(!IsStopMonitoring())
   {
      SetAllVisible(FALSE); /* Pour ne pas impacter l'affichage */

      if(GetIdParam() != NO_ID)
      {
         DataBaseAccess::ReadValue(	&Value1,
         								   GetIdParam(),
         								   GetDbTarget());
         Value1 = Value1 / GetDivider();
         SetFloatValue1(TRUE);
         if(Value1 == 10)
         {
            Value1 = 1;
            SetFloatValue1(FALSE);
         }
         SetValue1(Value1);
      }

      if(GetIdParam2() != NO_ID)
      {
         DataBaseAccess::ReadValue(	&Value2,
         									GetIdParam2(),
         									GetDbTarget2());
         Value2 = Value2 / GetDivider2();
         SetFloatValue2(TRUE);
         if(Value2 == 10)
         {
            Value2 = 1;
            SetFloatValue2(FALSE);
         }               
         SetValue2(Value2);
      }
      RefreshValueColumn();
      SetAllVisible(TRUE); /* On ré-impacte l'affichage */
      ShowAll();
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Met à jour les colonnes suivants les valeurs du numérateur et du denomi. */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	   NONE                             									 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelRatioTrunk::RefreshValueColumn()
{

   UWORD16 _ColValue2 = GetEndColValue1();

   UWORD16 _ColUnit2 = 2 + _ColValue2 + Tools::GetNumberPixelSize( GetValue2(),
                                                               GetFValue2()->GetFont(),
                                                               GetFloatValue2());

   GetFValue2()->SetCol(_ColValue2);
   GetFUnit2()->SetCol(_ColUnit2);  

}
/******************************************************************************/
/*%C                                                                          */
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affiche tous les objets du ratiotrunk                                    */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	   NONE                             									 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelRatioTrunk::ShowAll()
{
   GetFValue1()->Show();
   GetFUnit1()->Show();
   GetFValue2()->Show();
   GetFUnit2()->Show();
}
/******************************************************************************/
/*%C                                                                          */
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Efface tous les objets du ratiotrunk                                     */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	   NONE                             									 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelRatioTrunk::HideAll()
{
   GetFValue1()->Hide();
   GetFUnit1()->Hide();
   GetFValue2()->Hide();
   GetFUnit2()->Hide();
}

