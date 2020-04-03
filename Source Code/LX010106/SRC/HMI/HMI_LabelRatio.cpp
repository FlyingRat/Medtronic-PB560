/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelRatio.cpp 	  		   	         	 	  					*/
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

#include "HMI_LabelRatio.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelRatio::LabelRatio():LabelTwoValue()
{

}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelRatio::SetValue2Temp(UWORD16 _Value2Temp)
{
   Value2Temp = _Value2Temp;
}
UWORD16 LabelRatio::GetValue2Temp()
{
   return(Value2Temp);
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
void LabelRatio::Init(  e_SYMBOL _Icon,
                           UBYTE **_Name,
                           UWORD16 _Line,
                           UWORD16 _Col,
                           UWORD16 _Value1,
                           UBYTE **_NameUnit1,
                           UWORD16 _Value2,
                           UBYTE **_NameUnit2)
{
   LabelTwoValue::Init( _Icon,
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
/*%C Arret du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelRatio::StopMonitoringMode()
{
   LabelTwoValue::StopMonitoringMode();
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
void LabelRatio::StartMonitoringMode()
{
   LabelTwoValue::StartMonitoringMode();
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
void LabelRatio::Blink(e_BOOL _Actif)
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
         case 2 : GetFValue2()->Blink(_Actif);
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
void LabelRatio::StartModifMode()
{

   UWORD16 Value1;
   DataBaseAccess::ReadValue(&Value1, GetIdParam(), GetDbTarget());
   Value1 = Value1 / GetDivider();

   UWORD16 Value2;
   DataBaseAccess::ReadValue(&Value2, GetIdParam2(), GetDbTarget2());
   Value2 = Value2 / GetDivider();

	Label::StartModifMode();

   if(   ((LabelOneValue::GetFloatValue1() == TRUE)&&(LabelOneValue::GetValue1() == 10)) ||
         ((LabelOneValue::GetFloatValue1() == FALSE)&&(LabelOneValue::GetValue1() == 1)))
   {
      SetValue2(Value2);
	   SetValueTemp(Value1);
	   SetValue2Temp(Value2);
      SetValueState(2);
   }
   else
   {
      SetValue1(Value1);
	   SetValueTemp(Value1);
	   SetValue2Temp(Value2);      
      SetValueState(1);
   }
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
void LabelRatio::IncreaseValue()
{
   UWORD16 Value;

   if(GetValueState() == 1)
   {
      /* Numérateur */
      LabelOneValue::IncreaseValue();
   }
   else
   {
      /* Dénominateur */
      Value = GetValue2();
      if(DecreaseValueOk(&Value))
      {
         SetValue2(Value);

         if(   ((GetFloatValue2() == TRUE)&&(GetValue2() == 10)) ||
               ((GetFloatValue2() == FALSE)&&(GetValue2() == 1)))
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
void LabelRatio::DecreaseValue()
{
   UWORD16 Value;

   if(GetValueState() == 1)
   {
      /* Numérateur */   
      Value = LabelOneValue::GetValue1();
      if(LabelOneValue::DecreaseValueOk(&Value))
      {
         LabelOneValue::SetValue1(Value);
         if(   ((LabelOneValue::GetFloatValue1() == TRUE)&&(LabelOneValue::GetValue1() == 10)) ||
               ((LabelOneValue::GetFloatValue1() == FALSE)&&(LabelOneValue::GetValue1() == 1)))
            SetValueState(2);
      }
   }
   else
   {
      /* Dénominateur */
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
/*%C Autorisation d'increment																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Val : valeur a incrementer												 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé	  														*/
/******************************************************************************/
e_BOOL LabelRatio::IncreaseValueOk(UWORD16* _Val)
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
e_BOOL LabelRatio::DecreaseValueOk(UWORD16* _Val)
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
void LabelRatio::ConfirmModifValue(e_BOOL _Confirm)
{
   UWORD16 Value;
   e_BOOL ValidParam = FALSE;
   
   if(_Confirm)
   {
      if(GetIdParam2() != NO_ID)
      {
         /*%C Acces DB */
         Value = GetValue2();
         Value = Value * GetDivider();
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
      SetValue1(GetValueTemp());
      SetValue2(GetValue2Temp());
   }
}
