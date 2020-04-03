/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_VTime.cpp                            	 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C   Objet d'affichage de l'heure			   					  						*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/
#include "HMI_VTime.hpp"


/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/
#include "HMI_Config.hpp"
#include "HMI_DataBaseAccess.hpp"
#include "HMI_Message.hpp"
extern "C"
{
#include "DB_Config.h"
#include "DB_Rtc.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
VTime::VTime():EditableObject()
{   
   Suffixe = AM;

   FSep.SetParent(this);
	FSepHours.SetParent(this);
	FSepMin.SetParent(this);
   FHours.SetParent(this);
   FMin.SetParent(this);
	FSec.SetParent(this);
   FSuffixe.SetParent(this);

#ifdef HMI_CONFIG_TIME_24H_FORMAT
   SetVTimeFormat(VTIME_24H_FORMAT);
#elif defined HMI_CONFIG_TIME_12H_FORMAT
   SetVTimeFormat(VTIME_12H_FORMAT);
#else
   SetVTimeFormat(VTIME_12H_FORMAT);
#endif

   SetSep((UBYTE *)":");
   SetSepHours((UBYTE *)":");
   SetTextSuffixe((UBYTE *)cMSG_Am[0]);
   SetSecVisible (TRUE);
   SetColSep(40);

   FHours.Init(0,48,FONT_4,FALSE,0,2,TRUE,FALSE);
   FSepHours.Init(0,this->getColHours()+24,FONT_4,FALSE,(UBYTE *)":");
   FMin.Init(0,this->getColHours()+32,FONT_4,FALSE,0,2,TRUE,FALSE);
   FSepMin.Init(0,this->getColHours()+56,FONT_4,FALSE,(UBYTE *)":");
   FSec.Init(0,this->getColHours()+64,FONT_4,FALSE,0,2,TRUE,FALSE);
   if(GetVTimeFormat() == VTIME_12H_FORMAT)
      FSuffixe.Init(0,this->getColHours()+88,FONT_1,FALSE,(UBYTE *)cMSG_Am[0]);

   Format();

   SetDbTarget(ADJUST);
   SetIdParam2(NO_ID);
   SetIdParam3(NO_ID);
   SetIdParamReg1(NO_ID);
   SetIdParamReg2(NO_ID);
   SetIdParamReg3(NO_ID);
   
   StopMonitoring = FALSE;
   
   ForcedSuffixUpdate = TRUE;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void VTime::SetVisible(e_BOOL V)
{
   DisplayObject::SetVisible(V);
   FSep.SetVisible(V);
   FSepHours.SetVisible(V);
   FSepMin.SetVisible(V);
   FSuffixe.SetVisible(V);
   FHours.SetVisible(V);
   FMin.SetVisible(V);
   FSec.SetVisible(V);
}
/*----------------------------------------------------------------------------*/
void VTime::SetVTimeFormat(e_VTIME_FORMAT _format)
{
   VTimeFormat = _format;
}
/*----------------------------------------------------------------------------*/
e_VTIME_FORMAT VTime::GetVTimeFormat()
{
   return(VTimeFormat);
}
/*----------------------------------------------------------------------------*/
void VTime::SetIdParam2(UWORD16 _IdParam2)
{
   IdParam2 = _IdParam2;
}
/*----------------------------------------------------------------------------*/
UWORD16 VTime::GetIdParam2()
{
   return IdParam2;
}
/*----------------------------------------------------------------------------*/
void VTime::SetIdParam3(UWORD16 _IdParam3)
{
   IdParam3 = _IdParam3;
}
/*----------------------------------------------------------------------------*/
UWORD16 VTime::GetIdParam3()
{
   return IdParam3;
}
/*----------------------------------------------------------------------------*/
void VTime::SetIdParamReg1(UWORD16 _IdParamReg1)
{
   IdParamReg1 = _IdParamReg1;
}
/*----------------------------------------------------------------------------*/
UWORD16 VTime::GetIdParamReg1()
{
   return IdParamReg1;
}
/*----------------------------------------------------------------------------*/
void VTime::SetIdParamReg2(UWORD16 _IdParamReg2)
{
   IdParamReg2 = _IdParamReg2;
}
/*----------------------------------------------------------------------------*/
UWORD16 VTime::GetIdParamReg2()
{
   return IdParamReg2;
}
/*----------------------------------------------------------------------------*/
void VTime::SetIdParamReg3(UWORD16 _IdParamReg3)
{
   IdParamReg3 = _IdParamReg3;
}
/*----------------------------------------------------------------------------*/
UWORD16 VTime::GetIdParamReg3()
{
   return IdParamReg3;
}
/*----------------------------------------------------------------------------*/
UBYTE* VTime::GetSep(void)
{
   return FSep.GetText();
}
/*----------------------------------------------------------------------------*/
void VTime::SetSep(UBYTE* _Sep)
{
   FSep.SetText(_Sep);
}
/*----------------------------------------------------------------------------*/
UBYTE* VTime::GetSepHours(void)
{
   return FSepHours.GetText();
}
/*----------------------------------------------------------------------------*/
void VTime::SetSepHours(UBYTE* _SepHours)
{
   FSepHours.SetText(_SepHours);
   FSepMin.SetText(_SepHours);
}
/*----------------------------------------------------------------------------*/
e_BOOL VTime::GetSecVisible()
{
   return SecVisible;
}
/*----------------------------------------------------------------------------*/
UBYTE* VTime::GetTextSuffixe(void)
{
   return FSuffixe.GetText();
}
/*----------------------------------------------------------------------------*/
void VTime::SetTextSuffixe(UBYTE* _Suffixe)
{
   FSuffixe.SetText(_Suffixe);
}
/*----------------------------------------------------------------------------*/
UWORD16 VTime::GetHours(void)
{
    UWORD16 _Hours;
    _Hours = FHours.GetValue();

    if(GetVTimeFormat() == VTIME_12H_FORMAT) {
    
        if(Suffixe == PM) {
            if(_Hours != 12 ) {
		        _Hours = _Hours + 12;
            }
	    }
	    else {
            if(_Hours == 12 ) {
		        _Hours = 0;
    	    }
	    }
    }

	return _Hours;
}
/*----------------------------------------------------------------------------*/
void VTime::SetHours(UWORD16 _Hours)
{
	UWORD16 Val;
	DataBaseAccess::ReadValue(&Val,ADJUST_LANGUAGE_U16,CONFIG);
	e_PERIOD TempSuffixe;

   if(GetVTimeFormat() == VTIME_12H_FORMAT)
   {
	if (_Hours >= 12)
   	{
		if (_Hours != 12)
			_Hours = _Hours - 12;

		TempSuffixe = PM;

		if ((TempSuffixe != Suffixe) || (ForcedSuffixUpdate))
		{
			SetTextSuffixe((UBYTE *)cMSG_Pm[Val]);
			Suffixe = TempSuffixe;
		}
   }
   else /* _Hours < 12 */
   {
		if(_Hours == 0)
			_Hours = _Hours + 12;

		TempSuffixe = AM;

		if ((TempSuffixe != Suffixe) || (ForcedSuffixUpdate))
		{
			SetTextSuffixe((UBYTE *)cMSG_Am[Val]);
			Suffixe = TempSuffixe;
		}
   }

   if (ForcedSuffixUpdate)
    	ForcedSuffixUpdate = FALSE;
   }
   FHours.SetValue(_Hours);

}
/*----------------------------------------------------------------------------*/
UWORD16 VTime::GetMin(void)
{
   return FMin.GetValue();
}
/*----------------------------------------------------------------------------*/
void VTime::SetMin(UWORD16 _Min)
{
   FMin.SetValue(_Min);
}
/*----------------------------------------------------------------------------*/
UWORD16 VTime::GetSec(void)
{
   return FSec.GetValue();
}
/*----------------------------------------------------------------------------*/
void VTime::SetSec(UWORD16 _Sec)
{
   FSec.SetValue(_Sec);
}
/*----------------------------------------------------------------------------*/
UWORD16 VTime::getColSep()
{
   return FSep.GetCol();
}
/*----------------------------------------------------------------------------*/
void VTime::SetColSep(UWORD16 _ColSep)
{
   FSep.SetCol(_ColSep);
}
/*----------------------------------------------------------------------------*/
UWORD16 VTime::getColHours()
{
   return FHours.GetCol();
}
/*----------------------------------------------------------------------------*/
void VTime::SetColHours(UWORD16 _ColHours)
{
   FHours.SetCol(_ColHours);
   Format();
}
/*----------------------------------------------------------------------------*/
void VTime::SetFontHours(UWORD16 _Font)
{
   FHours.SetFont(_Font);
   FSepHours.SetFont(_Font);
   FMin.SetFont(_Font);
   FSepMin.SetFont(_Font);
   FSec.SetFont(_Font);
	if (_Font > FONT_2)
	{
   	FSuffixe.SetFont(FONT_1);
	}
	else
	{
   	FSuffixe.SetFont(_Font);
	}
}
/*----------------------------------------------------------------------------*/
e_BOOL VTime::IsSecVisible()
{
	if (SecVisible == TRUE)
	{
   	return (TRUE);
	}
	else
	{
		return (FALSE);
	}		  
}
/*----------------------------------------------------------------------------*/
UWORD16 VTime::GetValueState()
{
   return ValueState;
}
/*----------------------------------------------------------------------------*/
void VTime::SetValueState(UWORD16 _ValueState)
{
   ValueState = _ValueState;
}
/*----------------------------------------------------------------------------*/
void VTime::SetStopMonitoring(e_BOOL Flag)
{
   StopMonitoring = Flag;
}
/*----------------------------------------------------------------------------*/
e_BOOL VTime::IsStopMonitoring()
{
   return (e_BOOL)(StopMonitoring == TRUE);
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des accés de DataBase													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdParamHours : ID de la lecture de l'heure dans la DB						*/
/*%I		DbTarget : Nom de la DB				            								*/
/*%I		IdParamMin : ID de la lecture des minutes dans la DB						*/
/*%I		IdParamSec : ID de la lecture des secpndes dans DB							*/
/*%I		IdParamRegHours : ID du réglage de l'heure dans la DB		      		*/
/*%I		IdParamRegMin : ID du réglage des minutes dans la DB 		      		*/
/*%I		IdParamRegSec : ID du réglage des secondes dans la DB		      		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTime::InitDbAccess(  UWORD16 _IdParamHours,
                           e_TYPE_OF_DB_TARGET _DbTarget,
                           UWORD16 _IdParamMin ,
                           UWORD16 _IdParamSec,
                           UWORD16 _IdParamRegHours ,
                           UWORD16 _IdParamRegMin,
                           UWORD16 _IdParamRegSec)
{
   SetIdParam(_IdParamHours);
   SetDbTarget(_DbTarget);
   SetIdParam2(_IdParamMin);
   SetIdParam3(_IdParamSec);
   SetIdParamReg1(_IdParamRegHours);
   SetIdParamReg2(_IdParamRegMin);
   SetIdParamReg3(_IdParamRegSec);
}
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
void VTime::StopMonitoringMode()
{
   SetStopMonitoring(TRUE);
	FHours.Hide();
   FSepHours.Hide();
   FSepMin.Hide();
   FSuffixe.Hide();
   FHours.Hide();
   FMin.Hide();
   FSec.Hide();
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
void VTime::StartMonitoringMode()
{
   SetStopMonitoring(FALSE);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Formate l'affichage de l'heure en fonction de la police						*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTime::Format()
{
	/*%C Change the space between the different fields according to the police */ 
   if(FHours.GetFont() == FONT_1)
   {
      FSep.SetCol(getColHours()+16);
      FSepHours.SetCol(getColHours()+16);
      FMin.SetCol(getColHours()+21);
      FSepMin.SetCol(getColHours()+37);
      FSec.SetCol(getColHours()+42);
      FSuffixe.SetCol(getColHours()+58);
   }
   else
   {
      FSepHours.SetCol(getColHours()+24);
      FMin.SetCol(getColHours()+32);
      FSepMin.SetCol(getColHours()+56);
      FSec.SetCol(getColHours()+64);
      FSuffixe.SetCol(getColHours()+88);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affiche ou non les secondes																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		SecVisible : Si TRUE, Affiche la secondes									  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTime::SetSecVisible (e_BOOL _SecVisible)
{
   SecVisible = _SecVisible;

   /*%C If SecVisible = TRUE, the second ans his separator are displayed else */
	/*%C they are erased */
   if(SecVisible)
   {
      FSepMin.Show();
      FSec.Show();
   }
   else
   {
      FSepMin.Hide();
      FSec.Hide();
   }
   if(GetVTimeFormat() == VTIME_12H_FORMAT)
   {
   	/*%C Refresh of time information : AM or PM */
      FSuffixe.Show();
   }      
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Raffraichissement de l'heure, des minutes et des secondes						*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTime::Refresh()
{
   if(!IsStopMonitoring())
   {
   	/*%C Do a refresh only if parameter is selected */
      if(GetIdParam() != NO_ID)
      {
         UWORD16 Value;
         /*%C Reading hours in DataBase and display it */
         DataBaseAccess::ReadValue(&Value, GetIdParam(), GetDbTarget());
         SetHours(Value);

         /*%C Reading minutes in DataBase and display it */
         DataBaseAccess::ReadValue(&Value, GetIdParam2(), GetDbTarget());
         SetMin(Value);

         /*%C Reading secondes in DataBase and display it */
         DataBaseAccess::ReadValue(&Value, GetIdParam3(), GetDbTarget());
         SetSec(Value);
      }
   }      
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage de l'objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTime::Show()
{
	/*%C Choose the display format according to the police */
   Format();
	/*%C Display Label of the Object */
   Label::Show();

   if(!IsStopMonitoring())
   {
      /*%C Display the separator situated in front of hours */
      FSep.Show();
      /*%C Display hours */
      FHours.Show();
      /*%C Display the separator situated in front of minutes */
      FSepHours.Show();
      /*%C Display minutes */
      FMin.Show();

   	/*%C Display minute's separator and secondes only if they are visibles */
      if(IsSecVisible())
      {
         FSepMin.Show();
         FSec.Show();
      }
      if(GetVTimeFormat() == VTIME_12H_FORMAT)
      {
      	/*%C Display the time information : AM or PM */
         FSuffixe.Show();
      }
   }      
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTime::Hide()
{
	/*%C Object's erasing */
   Label::Hide();
   FSep.Hide();
   FSepHours.Hide();
   FSepMin.Hide();
   FHours.Hide();
   FMin.Hide();
   FSec.Hide();

   if(GetVTimeFormat() == VTIME_12H_FORMAT)
   {
      FSuffixe.Hide();
   }      
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Clignottement des objets																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTime::Blink(e_BOOL _Actif)
{
	/*%C Blink the object selected */
   switch(GetValueState())
   {
      case 1 : FHours.Blink(_Actif);
               if(GetVTimeFormat() == VTIME_12H_FORMAT)
                  FSuffixe.Blink(_Actif);
               break;
      case 2 : FMin.Blink(_Actif);
               break;
      case 3 : FSec.Blink(_Actif);
               break;
      default : break;               
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Incrément de la valeur sélectionnée													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTime::IncreaseValue()
{
   UWORD16 Value;

	/*%C Reading selected value in DataBase*/
   switch(GetValueState())
   {
      case 1 : Value =  GetHours();
                        break;
      case 2 : Value =  GetMin();
                        break;
      case 3 : Value =  GetSec();
                        break;
      default: Value =  0;
                        break;
   }

   /*%C If an IncreaseValueOk = TRUE is return by the Increase function of */
   /*%C dataBase then display object selected  */
   if(IncreaseValueOk(&Value))
   {
      switch(GetValueState())
      {
         case 1 : SetHours(Value);
                  break;
         case 2 : SetMin(Value);
                  break;
         case 3 : SetSec(Value);
                  break;
         default : break;                  
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Décrément de la valeur sélectionnée													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTime::DecreaseValue()
{
   UWORD16 Value;

	/*%C Reading selected value in DataBase*/
   switch(GetValueState())
   {
      case 1 : Value = GetHours();
               break;
      case 2 : Value = GetMin();
               break;
      case 3 : Value = GetSec();
               break;
      default: Value = 0;
               break;
   }

   /*%C If an DecreaseValueOk = TRUE is return by the Increase function of */ 
   /*%C dataBase then display object selected  */
   if(DecreaseValueOk(&Value))
   {
      switch(this->GetValueState())
      {
         case 1 : SetHours(Value);
                  break;
         case 2 : SetMin(Value);
                  break;
         case 3 : SetSec(Value);
                  break;
         default : break;
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Vérifie l'autorisation d'incrémentation de la valeur en conformité avec	*/
/*%C DataBase																						*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Val : valeur a incrémenter														  	*/
/*%IO Input/Output : 																			*/
/*%IO		Return TRUE si incrément autorisé												*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
e_BOOL VTime::IncreaseValueOk(UWORD16* _Val)
{
	/*%C Selected object incrementation test */ 
   switch(GetValueState())
   {
      case 1 : return DataBaseAccess::IncrementValue( _Val,
                                                      GetIdParamReg1(),
                                                      GetDbTarget());
      case 2 : return DataBaseAccess::IncrementValue( _Val,
                                                      GetIdParamReg2(),
                                                      GetDbTarget());
      case 3 : return DataBaseAccess::IncrementValue( _Val,
                                                      GetIdParamReg3(),
                                                      GetDbTarget());
      default: return FALSE;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Vérifie l'autorisation de décrémentation de la valeur en conformité avec	*/
/*%C DataBase																						*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Val : valeur a décrémenter														  	*/
/*%IO Input/Output : 																			*/
/*%IO		Return TRUE si décrément autorisé												*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
e_BOOL VTime::DecreaseValueOk(UWORD16* _Val)
{
	/*%C Selected object decrementation test */ 
   switch(GetValueState())
   {
      case 1 : return DataBaseAccess::DecrementValue( _Val,
                                                      GetIdParamReg1(),
                                                      GetDbTarget());

      case 2 : return DataBaseAccess::DecrementValue( _Val,
                                                      GetIdParamReg2(),
                                                      GetDbTarget());

      case 3 : return DataBaseAccess::DecrementValue( _Val,
                                                      GetIdParamReg3(),
                                                      GetDbTarget());
      default: return FALSE;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Démarrage d'une opération de modification des champs de l'objet				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE  							  														*/
/*%IO Input/Output : 																			*/
/*%IO 	NONE  							  														*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTime::StartModifMode()
{
   /*%C Stop the Refresh during the modification */
   RefreshEnable(FALSE);
   /*%C Run the modification's operation of Label object */
   Label::StartModifMode();
   /*%C Set the first field for the modification */
   SetValueState(1);
	/*%C Store hours in a temp value */
   SetValueTemp(GetHours());

   /*%C Parameters update according DataBased */
   UWORD16 Value;
   Value = GetSec();
   DataBaseAccess::WriteValue(&Value, ADJUST_RTC_SECOND_U16, RTC);
   Value = GetMin();
   DataBaseAccess::WriteValue(&Value, ADJUST_RTC_MINUTE_U16, RTC);
   Value = GetHours();
   DataBaseAccess::WriteValue(&Value, ADJUST_RTC_HOUR_U16, RTC);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification des champs de l'objet ou annule sa modification	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Confirm : Valide ou annule la modidification									*/
/*%IO Input/Output : 																			*/
/*%IO 	NONE  							  														*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTime::ConfirmModifValue(e_BOOL _Confirm)
{
	e_BOOL ValidState = TRUE;

	/*%C If Confirm is asked then store the parameters selected in DataBase */
   if(_Confirm)
   {
      UWORD16  Value;
      switch(this->GetValueState())
      {
         case 1 : Value = GetHours();
                  DataBaseAccess::WriteValue(&Value,
                                             GetIdParamReg1(),
                                             GetDbTarget());				  
                  break;

         case 2 : Value = GetMin();
                  DataBaseAccess::WriteValue(&Value,
                                             GetIdParamReg2(),
                                             GetDbTarget());                  
				  break;

         case 3 : Value = GetSec();
                  DataBaseAccess::WriteValue(&Value,
                                             GetIdParamReg3(),
                                             GetDbTarget());
                  /*%C Permet le refresh */
                  RefreshEnable(TRUE);				  
                  break;

         default : Value = 0; 
				   ValidState = FALSE;
		 		   break;
      }
	  if(ValidState)
	  {
	  	/*%C Request a short bip sound */
		Tools::ShortBipRequest();
	  }
   }
	/*%C Else display the old (temp) value */
  else
   {
      switch(GetValueState())
      {
         case 1 : SetHours(GetValueTemp());
                  break;
         case 2 : SetMin(GetValueTemp());
                  break;
         case 3 : SetSec(GetValueTemp());
                  break;
         default : break;                  
      }
   	/*%C Authorize values refresh */
      RefreshEnable(TRUE);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Permet d'activer la modification de la prochaine valeur						*/
/*%C Heures -> Minutes -> Secondes                                           	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Confirm : Valide ou annule la modidification									*/
/*%IO Input/Output : 																			*/
/*%IO 	NONE  							  														*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void VTime::ModifNextValue()
{
	/* Confirm the modification of the next value */
   ConfirmModifValue(TRUE);
	/* Read the state */
   UWORD16 State = GetValueState();
	/* If the state is < 3 modify and store the state */
   if(State<3)
   {
      SetValueState(++State);
   }
	/*%C Store parameters in a temp value */
   switch(GetValueState())
   {
      case 2 : SetValueTemp(GetMin());
               break;
      case 3 : SetValueTemp(GetSec());
               break;
      default : break;               
   }
}

