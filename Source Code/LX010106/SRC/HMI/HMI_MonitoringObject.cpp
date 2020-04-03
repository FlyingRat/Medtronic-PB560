/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MonitoringObject.cpp 	       			 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(border + text + value + unit)			 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_MonitoringObject.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"
#include "HMI_DisplayObject.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "HMI_Tools.hpp"
#include "HMI_Message.hpp"


/******************************************************************************/
/*                           CONSTANT DECLARATION		                			*/
/******************************************************************************/

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
MonitoringObject::MonitoringObject():DisplayObject()    
{
	CenteredDisplay = TRUE;
   IconIsPrefered = FALSE;   
   TextHeaderOn = FALSE;
   FloatDisplayOn = FALSE;
	ValueReady = FALSE;
   Trigger = FALSE;
   SignedValue = FALSE;

   FIcon.SetParent(this);
   FIcon.Init(NAME_HEIGHT+2,0,FONT_2,FALSE,(e_SYMBOL)NO);

   TFTitle.SetParent(this);
	TFTitle.Init(NAME_HEIGHT,0,FONT_1,FALSE,(UBYTE *)"-");
	VTFValue.SetParent(this);
	VTFValue.Init(MONITOR_HEIGHT, 0, FONT_4, FALSE,0, 0,FALSE, FALSE);
   TFUnit.SetParent(this);
	TFUnit.Init(UNIT_HEIGHT, 3, FONT_2, FALSE,(UBYTE *)"");

	FTrig.SetParent(this);
	FTrig.SetSymbol(TRIGGERINV);
   FTrig.SetLine(NAME_HEIGHT);
	FTrig.SetCol(35);
	FTrig.Hide();

	StopMonitoring = TRUE;
	SetDbTarget(ADJUST);
	SetIdParam(0);
   SetInvertVideo(FALSE);
	DivisionFactorOfValue = 1;

   MaxDisplayValueConfigured = FALSE;
   MaxDisplayValue = 0xFFFF;
}

/******************************************************************************/
/*                           ACCESSEURS				                				*/
/******************************************************************************/
void MonitoringObject::SetCoord(UWORD16 Line, UWORD16 Col)
{
	DisplayObject::Init(Line, Col);
}
/*----------------------------------------------------------------------------*/
void MonitoringObject::SetDivisionFactorOfValue(UWORD16 _DivisionFactorOfValue)
{
	if (_DivisionFactorOfValue != 0)
	{
		DivisionFactorOfValue = _DivisionFactorOfValue;
	}
}
/*----------------------------------------------------------------------------*/
UWORD16 MonitoringObject::GetDivisionFactorOfValue()
{
	return DivisionFactorOfValue;
}
/*----------------------------------------------------------------------------*/
void MonitoringObject::SetTrigger(e_BOOL _Trigger)
{
	Trigger = _Trigger;
}
/*----------------------------------------------------------------------------*/
e_BOOL MonitoringObject::GetTrigger()
{
	return Trigger;
}
/*----------------------------------------------------------------------------*/
void MonitoringObject::SetReverseVideo(e_BOOL _ReverseVideo)
{
	ReverseVideo = _ReverseVideo;
}
/*----------------------------------------------------------------------------*/
e_BOOL MonitoringObject::GetReverseVideo()
{
	return ReverseVideo;
}
/*----------------------------------------------------------------------------*/
void MonitoringObject::SetCenteredDisplay(e_BOOL _CenteredDisplay)
{
	CenteredDisplay = _CenteredDisplay;
}
/*----------------------------------------------------------------------------*/
e_BOOL MonitoringObject::GetCenteredDisplay()
{
	return CenteredDisplay;
}
/*----------------------------------------------------------------------------*/
void MonitoringObject::SetValueReady(e_BOOL _ValueReady)
{
	ValueReady = _ValueReady;
}
/*----------------------------------------------------------------------------*/
e_BOOL MonitoringObject::GetValueReady()
{
	return ValueReady;
}
/*----------------------------------------------------------------------------*/
void MonitoringObject::SetStopMonitoring(e_BOOL _StopMonitoring)
{
	StopMonitoring = _StopMonitoring;
}
/*----------------------------------------------------------------------------*/
e_BOOL MonitoringObject::GetStopMonitoring()
{
	return StopMonitoring;
}
/*----------------------------------------------------------------------------*/
void MonitoringObject::SetTextHeaderOn(e_BOOL _TextHeaderOn)
{
	TextHeaderOn = _TextHeaderOn;
}
/*----------------------------------------------------------------------------*/
e_BOOL MonitoringObject::GetTextHeaderOn()
{
	return TextHeaderOn;
}
/*----------------------------------------------------------------------------*/
void MonitoringObject::SetFloatDisplayOn(e_BOOL _FloatDisplayOn)
{
	FloatDisplayOn = _FloatDisplayOn;
}
/*----------------------------------------------------------------------------*/
e_BOOL MonitoringObject::GetFloatDisplayOn()
{
	return FloatDisplayOn;
}
/*----------------------------------------------------------------------------*/
void MonitoringObject::SetMaxDisplayValue(UWORD16 _MaxDisplayValue)
{
   MaxDisplayValue = _MaxDisplayValue;
   SetMaxDisplayValueConfigured(TRUE);
}
/*----------------------------------------------------------------------------*/
UWORD16 MonitoringObject::GetMaxDisplayValue()
{
   return(MaxDisplayValue);
}
/*----------------------------------------------------------------------------*/
void MonitoringObject::SetMaxDisplayValueConfigured(e_BOOL _MaxDisplayValueConfigured)
{
   MaxDisplayValueConfigured = _MaxDisplayValueConfigured;
}
/*----------------------------------------------------------------------------*/
e_BOOL MonitoringObject::IsMaxDisplayValueConfigured()
{
   return(MaxDisplayValueConfigured);
}
/*----------------------------------------------------------------------------*/
void MonitoringObject::SetSignedValue(e_BOOL _signed)
{
	SignedValue = _signed;
}
/*----------------------------------------------------------------------------*/
e_BOOL MonitoringObject::IsSignedValue()
{
	return SignedValue;
}
/*----------------------------------------------------------------------------*/
void MonitoringObject::SaturateValue(UWORD16* _Value)
{
	UWORD16 _max = GetMaxDisplayValue();
	UWORD16 _abs = 0;

	if (IsMaxDisplayValueConfigured())
	{
		if (*_Value > _max)
		{
			if (IsSignedValue() && (*_Value & 0x8000))
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

/******************************************************************************/
/*                           METHODES                									*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Icon   : icone																			*/
/*%I		Name   : Pointeur sur le tableau de nom						  				*/
/*%I		Line   : ligne 																		*/
/*%I		Col    : colonne																		*/
/*%I		Value1  : Valeur 1																	*/
/*%I		ValueRefresh : Valeur pour le champ de refresh							  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::Init(  e_SYMBOL _Icon,
                              UWORD16 _Line, 
										UWORD16 _Col, 
										UBYTE **_Name,
										UWORD16 _Value, 
										e_BOOL _ValueFloat,
                            	UBYTE ** _Unit, 
                            	e_BOOL _TextHeadOn, 
                            	e_BOOL _Centered)
{
	DisplayObject::Init(_Line, _Col);

   Name = _Name;
	TFTitle.SetText(Name[GetLanguage()]);

    if (_Icon != NO)
   {
      Icon = _Icon;
      IconInverseVideo = _Icon;      
      IconIsPrefered = TRUE;
   }

	CenteredDisplay = _Centered;

    if (_Centered)
	{

        if (IconIsPrefered)
         FIcon.SetCol(     (FRAME_WIDTH - 14) / 2);
      else
		   TFTitle.SetCol(   1 +
							      (FRAME_WIDTH -
								  Tools::GetStringPixelSize(Name[GetLanguage()], FONT_1))/
							      2);
	}
   else
	{
        if (IconIsPrefered)
         FIcon.SetCol(1 + LEFT_MARGIN_WIDTH);
      else
		   TFTitle.SetCol(1 + LEFT_MARGIN_WIDTH);
	}

   FloatDisplayOn = _ValueFloat;

	TextHeaderOn = _TextHeadOn;
   VTFValue.SetIEDisplay(TextHeaderOn);
   VTFValue.SetValue(_Value);
   VTFValue.SetFloat(FloatDisplayOn);
   VTFValue.SetCol(FRAME_WIDTH -
   					Tools::GetStringPixelSize(Name[GetLanguage()],
   					FONT_4));

	Unit = _Unit;
   TFUnit.SetText(this->Unit[GetLanguage()]);
	TFUnit.SetFont(FONT_2);
   TFUnit.SetCol(	FRAME_WIDTH - 
   					Tools::GetStringPixelSize(Name[GetLanguage()],
   					FONT_2));

	RefreshValueColumn();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Positionne l'unité             														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_Unit : unité de la valeur                                           */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::SetNameUnit(UBYTE** _Unit)
{
      Unit = _Unit;
      TFUnit.SetText(this->Unit[GetLanguage()]);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::StopMonitoringMode()
{
	StopMonitoring = TRUE;
	DisplayNoValue();
	ValueReady = FALSE;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_DisplayFlag : TRUE -> ne doit pas rafraichir la valeur du point de  */
/*%I     vue de l'affichage																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::StopMonitoringMode(e_BOOL _DisplayFlag)
{
   e_BOOL   IsVisible,
            IsVisibleValue,
            IsVisibleUnit,
            IsVisibleTitle,
            IsVisibleIcon;

    if (!_DisplayFlag)
   {
      IsVisible = this->IsVisible();
      IsVisibleValue = VTFValue.IsVisible();
      IsVisibleUnit = TFUnit.IsVisible();
      IsVisibleTitle = TFTitle.IsVisible();
      IsVisibleIcon = FIcon.IsVisible();

      /*%C  on rend les objets "non visibles" pour éviter que StopMonitoringMode ne fasse
            appel aux méthodes show et hide */
      this->SetVisible(FALSE);            
      VTFValue.SetVisible(FALSE);
      TFUnit.SetVisible(FALSE);
      TFTitle.SetVisible(FALSE);
      FIcon.SetVisible(FALSE);

	   StopMonitoringMode();

      this->SetVisible(IsVisible);
      VTFValue.SetVisible(IsVisibleValue);
      TFUnit.SetVisible(IsVisibleUnit);
      TFTitle.SetVisible(IsVisibleTitle);
      FIcon.SetVisible(IsVisibleIcon);
   }
   else
      StopMonitoringMode();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Freeze du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::FreezeMonitoringMode()
{
	this->StopMonitoring = TRUE;
	this->ValueReady = FALSE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::StartMonitoringMode()
{
	StopMonitoring = FALSE;
	ValueReady = FALSE;
   VTFValue.Hide();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::StartMonitoringModeImpactDisplay(e_BOOL _DisplayFlag)
{
   StopMonitoring = FALSE;
	ValueReady = FALSE;
    if (_DisplayFlag)
      VTFValue.Hide();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::StopMonitoringModeImpactDisplay(e_BOOL _DisplayFlag)
{
   this->StopMonitoringMode(_DisplayFlag);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Passage en invertion video																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		InvertVideo   : invertion si TRUE												*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::SetInvertVideo(e_BOOL _BlackBackground)
{
	ReverseVideo = _BlackBackground;
    if (IconIsPrefered)
   {
        if (!_BlackBackground)
      {
		   FIcon.SetSymbol(Icon);
      }
      else
	   {
		   FIcon.SetSymbol(IconInverseVideo);
	   }
   }
   else
	   TFTitle.SetReverseVideo(_BlackBackground);

	VTFValue.SetReverseVideo(_BlackBackground);
   TFUnit.SetReverseVideo(_BlackBackground);

   /*%C L'arrière-plan est blanc */
    if (!_BlackBackground)
   {
		FTrig.SetSymbol(TRIGGER);
   }
   else
	{
		FTrig.SetSymbol(TRIGGERINV);
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de la valeur monitoring														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::Refresh()
{
	RefreshObject(FALSE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de la valeur monitoring														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Refresh forcé ou non																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::ForceRefresh()
{
	this->RefreshObject(TRUE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Force le Refresh de la valeur monitoring											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::RefreshObject(e_BOOL _Forced)
{
    if (!StopMonitoring)
	{
		/*%C Backup current visibility */
		e_BOOL VisibleBackUp = VTFValue.IsVisible();

        if (GetIdParam() != NO_ID)
		{
			UWORD16 Value;

			DataBaseAccess::ReadValue(	&Value,
												GetIdParam(), 
												GetDbTarget());

            /*%C Saturation */
            SaturateValue(&Value);

			Value = Value / DivisionFactorOfValue;

			/*%C Clear previous value if different */
            if (VTFValue.GetValue() != Value)
   			{
			   	VTFValue.Clear();
		   	}

	        /*%C Set visibility to FALSE to unable next SetValue(), ForceValue()
	         and RefreshValueColumn() to call Hide() and Show() methods */
         	VTFValue.SetVisible(FALSE);

            if (_Forced)
			{
				VTFValue.ForceValue(Value);
			}
         	else
			{
            	VTFValue.SetValue(Value);
			}

		}

    	RefreshValueColumn();

      	/*%C Restore visibility */
      	VTFValue.SetVisible(VisibleBackUp);

        if (IsVisible())
		{
			VTFValue.Show();
			TFUnit.Show();
      }

      ValueReady = TRUE;
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::Show()
{
	DisplayObject::Show();

	/*%C Affiche le cadre puis le symbole */
    if (ReverseVideo)
    {
		InterfaceCppC::DisBox(			GetLine(),
												GetCol(),
												FRAME_HEIGHT-1,
												FRAME_WIDTH-1,
												TRUE,
												1,
												GetPage());

		InterfaceCppC::DisplaySymbol(	CADRE_WHITE_BGw,


												GetLine()+FRAME_HEIGHT-4,
												GetCol(),
												GetPage());

		InterfaceCppC::DisplaySymbol(	CADRE_WHITE_BDw,
												GetLine()+FRAME_HEIGHT-4,
												GetCol()+FRAME_WIDTH-1-3, 
												GetPage());

		InterfaceCppC::DisplaySymbol(	CADRE_WHITE_HGw,
												GetLine(),
												GetCol(),
												GetPage());

		InterfaceCppC::DisplaySymbol(	CADRE_WHITE_HDw,
												GetLine(),
												GetCol()+FRAME_WIDTH-1-3, 
												GetPage());
   }
	else
	{
		InterfaceCppC::DisBox(			GetLine(),
												GetCol(),
												FRAME_HEIGHT-1,
												FRAME_WIDTH-1,
												TRUE,
												0,
												GetPage());

		InterfaceCppC::DisplaySymbol(	CADRE_WHITE_BG,
												GetLine()+FRAME_HEIGHT-4, 
												GetCol(), 
												GetPage());

		InterfaceCppC::DisplaySymbol(	CADRE_WHITE_BD,
												GetLine()+FRAME_HEIGHT-4, 
												GetCol()+FRAME_WIDTH-1-3, 
												GetPage());

		InterfaceCppC::DisplaySymbol(	CADRE_WHITE_HG,
												GetLine(), 
												GetCol(),
												GetPage());

      InterfaceCppC::DisplaySymbol(CADRE_WHITE_HD,
        										GetLine(), 
        										GetCol()+FRAME_WIDTH-1-3, 
        										GetPage());
	}

    if (IconIsPrefered)
      FIcon.Show();
   else
	   TFTitle.Show();

    if (ValueReady)
	{
   	VTFValue.Show();
		TFUnit.Show();
        if (Trigger)
		{
		    this->FTrig.Show();
   	}
	}
   else
	{
		DisplayNoValue();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::Hide()
{
    if (IconIsPrefered)
        FIcon.Hide();
    else
        TFTitle.Hide();
	VTFValue.Hide();
	TFUnit.Hide();
    FTrig.Hide();
	DisplayObject::Hide();
    InterfaceCppC::EraseZone(   GetLine(),
								GetCol(),
								FRAME_HEIGHT-1,
								FRAME_WIDTH-1,
								0,
								GetPage());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Rafraichit les abscisses des 2 valeurs												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::RefreshValueColumn()
{
	/*%C  +1 realigne le texte vers la droite en compensation du */
   /*%C décalage à gauche ajouté par le driver de bas niveau */

    if (CenteredDisplay)
   {
    	VTFValue.SetCol(	2 + (FRAME_WIDTH -
    							VTFValue.GetPixelSize())
                        / 2);

		TFUnit.SetCol(		2 + (FRAME_WIDTH -
    							TFUnit.GetPixelSize())
                        / 2);
   }
   else
	{
    	VTFValue.SetCol(	1 +
    							LEFT_MARGIN_WIDTH);

		TFUnit.SetCol(		1 + 
								FRAME_WIDTH - 
								RIGHT_MARGIN_WIDTH - 
								TFUnit.GetPixelSize());
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affiche "-" à la place d'une valeur													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::DisplayNoValue()
{
	UWORD16 Col;

    if (CenteredDisplay)
	{
		TFUnit.Hide();
	}

	FTrig.Hide();

    if (CenteredDisplay)
	{
		Col = 1 + (FRAME_WIDTH-Tools::GetStringPixelSize((UBYTE *)"-", FONT_4))/2;
	}
	else
	{
		Col = 1 + LEFT_MARGIN_WIDTH;
	}

	VTFValue.SetCol(Col);
  	VTFValue.SetText((UBYTE *)"-");
   VTFValue.Show();

    if (!CenteredDisplay)
	{
		TFUnit.Show();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet								  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::RefreshLanguage()
{
    if (!IconIsPrefered)
   	TFTitle.SetTextOnly(Name[GetLanguage()]);
   TFUnit.SetTextOnly(Unit[GetLanguage()]);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affiche le trigger																		  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::ShowTrigger()
{
	Trigger = TRUE;

    if (CenteredDisplay)
	{
		FTrig.SetLine(FTrig.GetLine());
		FTrig.SetCol(FTrig.GetCol());
   }
   else
	{
		FTrig.SetLine(MONITOR_HEIGHT);
        if (TextHeaderOn)
		{
			FTrig.SetCol(	FRAME_WIDTH - 
								RIGHT_MARGIN_WIDTH - 
								6 - 
								Tools::GetStringPixelSize((UBYTE *)"  ", FONT_2));
		}

		else
		{
	    	FTrig.SetCol(FRAME_WIDTH/2 - 3);
		}
	}
    if (IsVisible())
	{
    	FTrig.Show();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Efface le trigger																		  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObject::HideTrigger()
{
	Trigger = FALSE;
   FTrig.Hide();
}

