/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_VDate.cpp											 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage de la date											 			  	*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_VDate.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"
#include "HMI_Config.hpp"


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR	                	   	*/
/******************************************************************************/
VDate::VDate():EditableObject()
{
   FSep.SetParent(this);
	FMonth.SetParent(this);
   FDay.SetParent(this);
	FYears.SetParent(this);

   NameMonth = NULL;
   Month = 1;
   ValueState = 1;

#ifdef HMI_CONFIG_DATE_US_FORMAT
   SetVDateFormat(VDATE_US_FORMAT);
#elif defined HMI_CONFIG_DATE_EUR_FORMAT
   SetVDateFormat(VDATE_EUR_FORMAT);
#else
   SetVDateFormat(VDATE_EUR_FORMAT);
#endif
   SetColSep(40);
   SetSep((UBYTE *)":");

   if(GetVDateFormat() == VDATE_US_FORMAT)
   {
      FDay.Init(0,GetColDate()+48,FONT_4,FALSE,1,2,TRUE,FALSE);
      FMonth.Init(0,48,FONT_4,FALSE,(UBYTE *)" ");
	   FYears.Init(0,GetColDate()+80,FONT_4,FALSE,2002,4,TRUE,FALSE);
   }
   else
   {
      FDay.Init(0,53,FONT_4,FALSE,1,2,TRUE,FALSE);
      FMonth.Init(0,GetColDate()+5,FONT_4,FALSE,(UBYTE *)" ");
	   FYears.Init(0,GetColDate()+80,FONT_4,FALSE,2002,4,TRUE,FALSE);
   }
   Format();

   SetDbTarget(ADJUST);
   SetIdParam2(NO_ID);
   SetIdParam3(NO_ID);
   SetIdParamReg1(NO_ID);
   SetIdParamReg2(NO_ID);
   SetIdParamReg3(NO_ID);

   StopMonitoring = FALSE;   

}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void VDate::SetVisible(e_BOOL V)
{
   DisplayObject::SetVisible(V);
   FSep.SetVisible(V);
   FMonth.SetVisible(V);
   FDay.SetVisible(V);
   FYears.SetVisible(V);
}
/*----------------------------------------------------------------------------*/
void VDate::SetIdParam2(UWORD16 _IdParam2)
{
   IdParam2 = _IdParam2;
}
/*----------------------------------------------------------------------------*/
UWORD16 VDate::GetIdParam2()
{
   return IdParam2;
}
/*----------------------------------------------------------------------------*/
void VDate::SetVDateFormat(e_VDATE_FORMAT _format)
{
   VDateFormat = _format;
}
/*----------------------------------------------------------------------------*/
e_VDATE_FORMAT VDate::GetVDateFormat()
{
   return(VDateFormat);
}
/*----------------------------------------------------------------------------*/
void VDate::SetIdParam3(UWORD16 _IdParam3)
{
   IdParam3 = _IdParam3;
}
/*----------------------------------------------------------------------------*/
UWORD16 VDate::GetIdParam3()
{
   return IdParam3;
}
/*----------------------------------------------------------------------------*/
void VDate::SetIdParamReg1(UWORD16 _IdParamReg1)
{
   IdParamReg1 = _IdParamReg1;
}
/*----------------------------------------------------------------------------*/
UWORD16 VDate::GetIdParamReg1()
{
   return IdParamReg1;
}
/*----------------------------------------------------------------------------*/
void VDate::SetIdParamReg2(UWORD16 _IdParamReg2)
{
   IdParamReg2 = _IdParamReg2;
}
/*----------------------------------------------------------------------------*/
UWORD16 VDate::GetIdParamReg2()
{
   return IdParamReg2;
}
/*----------------------------------------------------------------------------*/
void VDate::SetIdParamReg3(UWORD16 _IdParamReg3)
{
   IdParamReg3 = _IdParamReg3;
}
/*----------------------------------------------------------------------------*/
UWORD16 VDate::GetIdParamReg3()
{
   return IdParamReg3;
}
/*----------------------------------------------------------------------------*/
void VDate::SetSep(UBYTE *_Sep)
{
   FSep.SetText(_Sep);
}
/*----------------------------------------------------------------------------*/
UBYTE* VDate::GetSep()
{
   return FSep.GetText();
}

/*----------------------------------------------------------------------------*/
void VDate::SetNameMonth(UBYTE** _NameMonth)
{
   NameMonth = _NameMonth;

   FMonth.SetText(GetNameMonth());
}
/*----------------------------------------------------------------------------*/

UWORD16 VDate::GetDay(void)
{
   return FDay.GetValue();
}
/*----------------------------------------------------------------------------*/
void VDate::SetDay(UWORD16 _Day)
{
	if ((_Day < 1) || (_Day > 31))
		_Day = 1;
	FDay.SetValue(_Day);
}
/*----------------------------------------------------------------------------*/
UWORD16 VDate::GetYear(void)
{
   return FYears.GetValue();
}
/*----------------------------------------------------------------------------*/
void VDate::SetYear(UWORD16 _Year)
{
	_Year += 2000;
	if ((_Year < 2004) || (_Year > 2099))
		_Year = 2099;
	FYears.SetValue(_Year);
}
/*----------------------------------------------------------------------------*/
UWORD16 VDate::GetMonth(void)
{
   return Month;
}
/*----------------------------------------------------------------------------*/
void VDate::SetMonth(UWORD16 _Month)
{
	if((_Month<1)||(_Month>12))
   {
      _Month = 1;
   }
   if(Month != _Month)
   {
      Month = _Month;
      FMonth.SetText(GetNameMonth());
   }
}
/*----------------------------------------------------------------------------*/
UWORD16 VDate::GetColSep()
{
   return FSep.GetCol();
}
/*----------------------------------------------------------------------------*/
void VDate::SetColSep(UWORD16 ColSep)
{
	FSep.SetCol(ColSep);
}
/*----------------------------------------------------------------------------*/
UWORD16 VDate::GetColDate()
{
   if(GetVDateFormat() == VDATE_US_FORMAT)
   {
      return FMonth.GetCol();
   }
   else
   {
      return FDay.GetCol();
   }
}
/*----------------------------------------------------------------------------*/
void VDate::SetColDate(UWORD16 _ColDate)
{
   if(GetVDateFormat() == VDATE_US_FORMAT)
   {
      FMonth.SetCol(_ColDate);
   }
   else
   {
      FDay.SetCol(_ColDate);
   }
   Format();
}
/*----------------------------------------------------------------------------*/
void VDate::SetFontDate(UWORD16 _Font)
{
   FDay.SetFont(_Font);
   FMonth.SetFont(_Font);
   FYears.SetFont(_Font);

   Format();
}
/*----------------------------------------------------------------------------*/
UWORD16 VDate::GetValueState()
{
   return ValueState;
}
/*----------------------------------------------------------------------------*/
void VDate::SetValueState(UWORD16 _ValueState)
{
   ValueState = _ValueState;
}
/*----------------------------------------------------------------------------*/
void VDate::SetIdDbParamReg(e_TYPE_OF_DB_TARGET _IdDbParamReg)
{
   IdDbParamReg = _IdDbParamReg;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET VDate::GetIdDbParamReg()
{
   return IdDbParamReg;
}
/*----------------------------------------------------------------------------*/
void VDate::SetDate(int _Day,int _Month,int _Year)
{
   SetDay(_Day);
   SetMonth(_Month);
   SetYear(_Year);
}
/*----------------------------------------------------------------------------*/
void VDate::SetStopMonitoring(e_BOOL Flag)
{
   StopMonitoring = Flag;
}
/*----------------------------------------------------------------------------*/
e_BOOL VDate::IsStopMonitoring()
{
   return (e_BOOL)(StopMonitoring == TRUE);
}
/*----------------------------------------------------------------------------*/
void VDate::SetColBackup(UWORD16 _colbackup)
{
   ColBackup = _colbackup;
}
/*----------------------------------------------------------------------------*/
UWORD16 VDate::GetColBackup()
{
   return(ColBackup);
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
void VDate::StopMonitoringMode()
{
   SetStopMonitoring(TRUE);
#ifdef HMI_CONFIG_DATE_US_FORMAT
   FMonth.SetText((UBYTE *)"-");
   FDay.Hide();
#elif defined HMI_CONFIG_DATE_EUR_FORMAT
   FDay.Hide();
   SetColBackup(FMonth.GetCol());
   FMonth.SetText((UBYTE *)"-");
   FMonth.SetCol(FDay.GetCol());
#else
   FDay.Hide();
   SetColBackup(FMonth.GetCol());
   FMonth.SetText((UBYTE *)"-");
   FMonth.SetCol(FDay.GetCol());
#endif

   FYears.Hide();
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
void VDate::StartMonitoringMode()
{
   e_BOOL _IsVisible = FMonth.IsVisible();

   SetStopMonitoring(FALSE);
   FMonth.SetVisible(FALSE);
   FMonth.SetCol(GetColBackup());
   Month = 13; /* pour forcer le show */
   FMonth.SetVisible(_IsVisible);
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des acces DB																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdParamDay      : Id du jour en lecture						         	*/
/*%I		DbTarget        : bd Target	 								            	*/
/*%I		IdParamMonth    : Id du mois en lecture	  	 	    		         	*/
/*%I		IdParamYears	  : Id de l'année en lecture		     		         	*/
/*%I		IdParamRegDay	  : Id du jour en ecriture			     		      		*/
/*%I		IdParamRegMonth : Id du mois en ecriture			     		      		*/
/*%I		IdParamRegYears : Id dd l'année en ecriture								  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::InitDbAccess(  UWORD16 _IdParamMonth,
                           e_TYPE_OF_DB_TARGET _DbTarget,
                           UWORD16  _IdParamDay,
                           UWORD16 _IdParamYears,
                           UWORD16 _IdParamRegMonth ,
                           UWORD16 _IdParamRegDay,
                           UWORD16 _IdParamRegYears,
                           e_TYPE_OF_DB_TARGET _IdDbParamReg)
{
   SetIdParam(_IdParamMonth);
   SetDbTarget(_DbTarget);
   SetIdParam2(_IdParamDay);
   SetIdParam3(_IdParamYears);
   SetIdParamReg1(_IdParamRegMonth);
	SetIdParamReg2(_IdParamRegDay);
   SetIdParamReg3(_IdParamRegYears);
   SetIdDbParamReg(_IdDbParamReg);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des acces DB																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Nom de la date					  														*/
/******************************************************************************/
UBYTE* VDate::GetNameMonth(void)
{
   if(NameMonth != NULL)
   {
      UBYTE **tmp;
      tmp = NameMonth;
     
      /*%C positionnement de la ligne (ici NB_LANGUAGE = nb de langues) */
      tmp = &tmp[GetNbLanguage()*(Month)];
     
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
/*%C Formate l'affichage de la date															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::Format()
{
	if(FMonth.GetFont() == FONT_1)
   {
      if(VDateFormat == VDATE_US_FORMAT)
      {
         FMonth.SetCol(GetColDate());
         SetColBackup(GetColDate());
         FDay.SetCol(GetColDate()+30);
      }
      else
      {
         FDay.SetCol(GetColDate());
         FMonth.SetCol(GetColDate()+20);
         SetColBackup(GetColDate()+20);
      }
      FYears.SetCol(GetColDate()+50);
   }
   else
   {
      if(VDateFormat == VDATE_US_FORMAT)
      {
         FMonth.SetCol(GetColDate());
         SetColBackup(GetColDate());
         FDay.SetCol(GetColDate()+45);
      }
      else
      {
         FDay.SetCol(GetColDate());
         FMonth.SetCol(this->GetColDate()+25);
         SetColBackup(GetColDate()+25);
      }
      FYears.SetCol(GetColDate()+68);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue	de l'Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::RefreshLanguage()
{
   Label::RefreshLanguage();
   FMonth.SetTextOnly(GetNameMonth());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Inversion video de l'objet																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo : Invertion si TRUE												  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::SetInvertVideo(e_BOOL _InvertVideo)
{
   Label::SetInvertVideo(_InvertVideo);
   FSep.SetReverseVideo(_InvertVideo);
   FMonth.SetReverseVideo(_InvertVideo);
   FDay.SetReverseVideo(_InvertVideo);
   FYears.SetReverseVideo(_InvertVideo);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'affichage																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::Refresh()
{
   if(!IsStopMonitoring())
   {   
      if(GetIdParam() != NO_ID)
      {
         UWORD16 Value;

   		DataBaseAccess::ReadValue(&Value, GetIdParam(), GetDbTarget());
	   	SetMonth(Value);
		   DataBaseAccess::ReadValue(&Value, GetIdParam2(), GetDbTarget());
   		SetDay(Value);
	   	DataBaseAccess::ReadValue(&Value, GetIdParam3(), GetDbTarget());
		   SetYear(Value);
   	}
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::Show()
{
   Refresh();
   Label::Show();
   FSep.Show();

   FMonth.Show();
   if(!IsStopMonitoring())
   {
      FDay.Show();
      FYears.Show();
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::Hide()
{
	Label::Show();
	FSep.Hide();
	FMonth.Hide();
	FDay.Hide();
	FYears.Hide();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::Blink(e_BOOL _Actif)
{
   if(GetVDateFormat() == VDATE_US_FORMAT)
   {
      switch(GetValueState())
      {
         case 1 : FMonth.Blink(_Actif);
                  break;
         case 2 : FDay.Blink(_Actif);
                  break;
         case 3 : FYears.Blink(_Actif);
                  break;
         default : break;                  
      }
   }
   else
   {
      switch(GetValueState())
      {
         case 1 : FDay.Blink(_Actif);
                  break;
         case 2 : FMonth.Blink(_Actif);
                  break;
         case 3 : FYears.Blink(_Actif);
                  break;
         default : break;                  
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Increment de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::IncreaseValue()
{
   UWORD16 Value;
   if(GetVDateFormat() == VDATE_US_FORMAT)
   {
      switch(GetValueState())
      {
         case 1 : Value = GetMonth();
                  break;

         case 2 : Value = GetDay();
                  break;

         case 3 : Value = GetYear();
	   				Value = Value%100;
		   			break;

         default: Value = 0;
                  break;
      }

      /*%C Access to data base */
      if(IncreaseValueOk(&Value))
      {
         switch(GetValueState())
         {
            case 1 : SetMonth(Value);
                     break;
            case 2 : SetDay(Value);
                     break;
            case 3 : SetYear(Value);
                     break;
            default : break;                     
         }
      }
   }
   else
   {
      switch(GetValueState())
      {
         case 1 : Value = GetDay();
                  break;

         case 2 : Value = GetMonth();
                  break;

         case 3 : Value = GetYear();
	   				Value = Value%100;
		   			break;

         default: Value = 0;
                  break;
      }

      /*%C Access to data base */
      if(IncreaseValueOk(&Value))
      {
         switch(GetValueState())
         {
            case 1 : SetDay(Value);
                     break;
            case 2 : SetMonth(Value);
                     break;
            case 3 : SetYear(Value);
                     break;
            default : break;                     
         }
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decrement de la valeur courante														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::DecreaseValue()
{
   UWORD16 Value;

   if(GetVDateFormat() == VDATE_US_FORMAT)
   {
      switch(GetValueState())
      {
         case 1 : Value = GetMonth();
                  break;

         case 2 : Value = GetDay();
                  break;

   		case 3 : Value = GetYear();
	   				Value = Value%100;
		   			break;

         default: Value = 0;
                  break;
      }

      /*%C Access to data base */
      if(DecreaseValueOk(&Value))
      {
         switch(GetValueState())
         {
            case 1 : SetMonth(Value);
                     break;
            case 2 : SetDay(Value);
                     break;
            case 3 : SetYear(Value);
                     break;
            default : break;
         }
      }
   }
   else
   {
      switch(GetValueState())
      {
         case 1 : Value = GetDay();
                  break;

         case 2 : Value = GetMonth();
                  break;

   		case 3 : Value = GetYear();
	   				Value = Value%100;
		   			break;

         default: Value = 0;
                  break;
      }

      /*%C Access to data base */
      if(DecreaseValueOk(&Value))
      {
         switch(GetValueState())
         {
            case 1 : SetDay(Value);
                     break;
            case 2 : SetMonth(Value);
                     break;
            case 3 : SetYear(Value);
                     break;
            default : break;
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
/*%I		Val : valeur a incrementer														  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé	  														*/
/******************************************************************************/
e_BOOL VDate::IncreaseValueOk(UWORD16* _Val)
{
   if(GetVDateFormat() == VDATE_US_FORMAT)
   {
      switch(GetValueState())
      {
         case 1 : return DataBaseAccess::IncrementValue( _Val,
                                                         GetIdParamReg1(),
                                                         GetIdDbParamReg());

         case 2 : return DataBaseAccess::IncrementValue( _Val,
                                                         GetIdParamReg2(),
                                                         GetIdDbParamReg());

         case 3 : return DataBaseAccess::IncrementValue( _Val,
                                                         GetIdParamReg3(),
					   													GetIdDbParamReg());

         default: return FALSE;
	   }
   }
   else
   {
      switch(GetValueState())
      {
         case 1 : return DataBaseAccess::IncrementValue( _Val,
                                                         GetIdParamReg2(),
                                                         GetIdDbParamReg());

         case 2 : return DataBaseAccess::IncrementValue( _Val,
                                                         GetIdParamReg1(),
                                                         GetIdDbParamReg());

         case 3 : return DataBaseAccess::IncrementValue( _Val,
                                                         GetIdParamReg3(),
					   													GetIdDbParamReg());

         default: return FALSE;
	   }

   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation de decrement																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Val : valeur a incrementer														  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé	  														*/
/******************************************************************************/
e_BOOL VDate::DecreaseValueOk(UWORD16* _Val)
{
   if(GetVDateFormat() == VDATE_US_FORMAT)
   {
      switch(GetValueState())
      {
         case 1 : return DataBaseAccess::DecrementValue( _Val,
                                                         GetIdParamReg1(),
                                                         GetIdDbParamReg());

         case 2 : return DataBaseAccess::DecrementValue( _Val,
	   																	GetIdParamReg2(),
                                                         GetIdDbParamReg());

         case 3 : return DataBaseAccess::DecrementValue( _Val,
                                                         GetIdParamReg3(),
                                                         GetIdDbParamReg());
   		default: return FALSE;
	   }
   }
   else
   {
      switch(GetValueState())
      {
         case 1 : return DataBaseAccess::DecrementValue( _Val,
                                                         GetIdParamReg2(),
                                                         GetIdDbParamReg());

         case 2 : return DataBaseAccess::DecrementValue( _Val,
	   																	GetIdParamReg1(),
                                                         GetIdDbParamReg());

         case 3 : return DataBaseAccess::DecrementValue( _Val,
                                                         GetIdParamReg3(),
                                                         GetIdDbParamReg());
   		default: return FALSE;
	   }

   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Demarage de la modification d'un Objet											  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::StartModifMode()
{
   RefreshEnable(FALSE);
   Label::StartModifMode();
   SetValueState(1);
   if(GetVDateFormat() == VDATE_US_FORMAT) 
        SetValueTemp(GetMonth());
   else
        SetValueTemp(GetDay());    

   /*%C MAJ des param adjust */
   UWORD16 Value;

   Value = GetMonth();
   DataBaseAccess::WriteValue(&Value, GetIdParamReg1(), GetIdDbParamReg());

   Value = GetDay();
   DataBaseAccess::WriteValue(&Value, GetIdParamReg2(), GetIdDbParamReg());

   Value = GetYear();
   DataBaseAccess::WriteValue(&Value, GetIdParamReg3(), GetIdDbParamReg());
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret de la modification d'un Objet											  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::StopModifMode()
{
   RefreshEnable(TRUE);
   EditableObject::StopModifMode();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet								  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::ConfirmModifValue(e_BOOL _Confirm)
{
   e_BOOL ValidState = TRUE;
   UWORD16  Value;

   if(GetVDateFormat() == VDATE_US_FORMAT)
   {
   	    if(_Confirm)
        {
            switch(GetValueState())
            {
                case 1 : 	Value = GetMonth();
				   		    DataBaseAccess::WriteValue(&Value,
                        	                            GetIdParamReg1(),
						   		    					GetIdDbParamReg());
						    break;

   			    case 2 : 	Value = GetDay();
	   					    DataBaseAccess::WriteValue(&Value,
		   					    						GetIdParamReg2(),
                        		                        GetIdDbParamReg());
				   		    break;

                case 3 : 	Value = GetYear();
		   				    Value = Value%100;
	   					    DataBaseAccess::WriteValue(&Value,
                        	                            GetIdParamReg3(),
                            	                        GetIdDbParamReg());
                            break;

                default : 	Value = 0;
					  	    ValidState = FALSE;
						    break;
            }
            /*%C Update display */
            UpdateValues();

		    if (ValidState)
	  	    {
	  	 	    /*%C Request a short bip sound */
			    Tools::ShortBipRequest();
	  	    }
        }
        else
        {
            /*%C affiche l'ancienne valeur */
            switch(this->GetValueState())
	   	    {
                case 1 :    SetMonth(GetValueTemp());
			   			    break;

                case 2 :    SetDay(GetValueTemp());
                            break;

			    case 3 :    Value = GetValueTemp()%100;
                            SetYear(Value);
                            break;

                default :   break;
            }
            /*%C Permet le refresh */
            RefreshEnable(TRUE);
        }
    }
    else
    {
   	    if(_Confirm)
        {
            switch(GetValueState())
            {
                case 1 :    Value = GetDay();
				   		    DataBaseAccess::WriteValue(&Value,
                                                        GetIdParamReg2(),
						   								GetIdDbParamReg());
                            break;

   			    case 2 :    Value = GetMonth();
	   					    DataBaseAccess::WriteValue(&Value,
		   												GetIdParamReg1(),
                                                        GetIdDbParamReg());
                            break;

                case 3 :    Value = GetYear();
		   				    Value = Value%100;
	   					    DataBaseAccess::WriteValue(&Value,
                                                        GetIdParamReg3(),
                                                        GetIdDbParamReg());
                            break;

                default :   Value = 0;
                            ValidState = FALSE;
                            break;
            }
            /*%C Update display */
            UpdateValues();
            
            if (ValidState)
	  	    {
	  	 	    /*%C Request a short bip sound */
			    Tools::ShortBipRequest();
	  	    }
	    }
        else
        {
            /*%C affiche l'ancienne valeur */
            switch(this->GetValueState())
	   	    {
                case 1 :    SetDay(GetValueTemp());
			   			    break;

                case 2 :    SetMonth(GetValueTemp());
                            break;

			    case 3 :    Value = GetValueTemp()%100;
                            SetYear(Value);
                            break;
                     
                default : break;
            }
            /*%C Permet le refresh */
            RefreshEnable(TRUE);
        }
    }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Changement de la valeur en modification								  				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::ModifNextValue()
{
	UWORD16 Value;

	ConfirmModifValue(TRUE);
	UWORD16 State = GetValueState();
	if(State<3)
	{
		SetValueState(++State);
   }
   if(GetVDateFormat() == VDATE_US_FORMAT)
   {
   	switch(GetValueState())
	   {
   		case 1 : SetValueTemp(GetMonth());
	   				break;

   		case 2 : DataBaseAccess::ReadValue(&Value, GetIdParam2(), GetDbTarget());
	   				SetDay(Value);
		   			SetValueTemp(GetDay());
			   		break;

   		case 3 : SetValueTemp(GetYear());
                  break;
      }
   }
   else
   {
   	switch(GetValueState())
	   {

   		case 1 : DataBaseAccess::ReadValue(&Value, GetIdParam2(), GetDbTarget());
	   				SetDay(Value);
		   			SetValueTemp(GetDay());
			   		break;
                  
   		case 2 : SetValueTemp(GetMonth());
	   				break;

   		case 3 : SetValueTemp(GetYear());
                  break;
      }
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Update values      								  				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void VDate::UpdateValues()
{
	UWORD16 Value;

    DataBaseAccess::ReadValue(&Value, GetIdParamReg1(), GetIdDbParamReg());
    SetMonth(Value);

    DataBaseAccess::ReadValue(&Value, GetIdParamReg2(), GetIdDbParamReg());
    SetDay(Value);

    DataBaseAccess::ReadValue(&Value, GetIdParamReg3(), GetIdDbParamReg());
    SetYear(Value%100);
}
