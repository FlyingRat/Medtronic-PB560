/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MonitoringObjectTwoValue.cpp   			 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(border + text + value1 + sep + value2) 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_MonitoringObjectTwoValue.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/
#include "HMI_Config.hpp"
#include "HMI_DataBaseAccess.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "HMI_Tools.hpp"
#include "HMI_Message.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION		                			*/
/******************************************************************************/


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
MonitoringObjectTwoValue::MonitoringObjectTwoValue():MonitoringObject()    
{
	VTFValue2.SetParent(this);
	VTFValue2.Init(MONITOR_HEIGHT, 0, FONT_4, FALSE, 0, 0,FALSE, FALSE);

	TFSep.SetParent(this);
	TFSep.Init(MONITOR_HEIGHT, 3, FONT_2, FALSE,(UBYTE *)"");

   MaxDisplayValue2Configured = FALSE;
   MaxDisplayValue2 = 0xFFFF;
}

/******************************************************************************/
/*                           ACCESSEURS				                				*/
/******************************************************************************/
void MonitoringObjectTwoValue::SetIdParam2(UWORD16 _IdParam2)
{
	IdParam2 = _IdParam2;
}
/*----------------------------------------------------------------------------*/
UWORD16 MonitoringObjectTwoValue::GetIdParam2()
{
	return IdParam2;
}
/*----------------------------------------------------------------------------*/
void MonitoringObjectTwoValue::SetDbTarget2(e_TYPE_OF_DB_TARGET _DbTarget2)
{
	DbTarget2 = _DbTarget2;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET MonitoringObjectTwoValue::GetDbTarget2()
{
	return DbTarget2;
}
/*----------------------------------------------------------------------------*/
void MonitoringObjectTwoValue::SetMaxDisplayValue2(UWORD16 _MaxDisplayValue2)
{
   MaxDisplayValue2 = _MaxDisplayValue2;
   SetMaxDisplayValue2Configured(TRUE);
}
/*----------------------------------------------------------------------------*/
UWORD16 MonitoringObjectTwoValue::GetMaxDisplayValue2()
{
   return(MaxDisplayValue2);
}
/*----------------------------------------------------------------------------*/
void MonitoringObjectTwoValue::SetMaxDisplayValue2Configured(e_BOOL _MaxDisplayValue2Configured)
{
   MaxDisplayValue2Configured = _MaxDisplayValue2Configured;
}
/*----------------------------------------------------------------------------*/
e_BOOL MonitoringObjectTwoValue::IsMaxDisplayValue2Configured()
{
   return(MaxDisplayValue2Configured);
}
/*----------------------------------------------------------------------------*/
void MonitoringObjectTwoValue::SaturateValue2(UWORD16* _Value)
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
void MonitoringObjectTwoValue::Init(	   e_SYMBOL _Icon,
                                          UWORD16 _Line,
														UWORD16 _Col,
														UBYTE **_Name,
														UWORD16 _Value,
														e_BOOL _ValueFloat,
														UWORD16 _Value2,
														e_BOOL _Value2Float,
														UBYTE ** _Sep,
														e_BOOL _TextHeadOn,
														e_BOOL _Centered)
{
	MonitoringObject::Init(	_Icon,
                           _Line,
									_Col,
									_Name,
									_Value,
									_ValueFloat,
									(UBYTE**)cMSG_NoneUnit,
									_TextHeadOn,
									_Centered);

#ifdef HMI_CONFIG_TRUNCATED_I_E
	/*%C If decimal is asked and if decimal value = 0 */
	/*%C then the value is set whith Integer attribut */
    if ((GetFloatDisplayOn()) && (_Value % 10 == 0))
	{
		VTFValue.SetFloat(FALSE);
		_Value = _Value * 10;
	}
#endif

	FloatDisplayOn2 = _Value2Float;
	VTFValue2.SetIEDisplay(_TextHeadOn);

#ifdef HMI_CONFIG_TRUNCATED_I_E
	/*%C If decimal is asked and if decimal value = 0 */
	/*%C then the value is set whith Integer attribut */
    if ((FloatDisplayOn2) && (_Value2 % 10 == 0))
	{
		VTFValue2.SetFloat(FALSE);
		_Value2 = _Value2 * 10;
	}
#endif   

	VTFValue2.SetValue(_Value2);
	VTFValue2.SetFloat(_Value2Float);
	VTFValue2.SetCol(	7 + (FRAME_WIDTH -
							VTFValue2.GetPixelSize())
							/ 2);

	TFSep.SetText(_Sep[MonitoringObject::GetLanguage()]);
	TFSep.SetFont(FONT_4);
	TFSep.SetCol(	2 + (FRAME_WIDTH -
						TFSep.GetPixelSize())
						/ 2);

	RefreshValueColumn();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des paramettres d'acce a DB											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdParam2 : Id DB de la valeur2								            	*/
/*%I		DbTarget2 : Target DB	de la valeur2											*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MonitoringObjectTwoValue::InitDbAccess2(UWORD16 _IdParam2,
															e_TYPE_OF_DB_TARGET _DbTarget2)
{
	SetIdParam2(_IdParam2);
   SetDbTarget2(_DbTarget2);
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
void MonitoringObjectTwoValue::SetInvertVideo(e_BOOL _BlackBackground)
{
	VTFValue2.SetReverseVideo(_BlackBackground);

	MonitoringObject::SetInvertVideo(_BlackBackground);

	TFSep.SetReverseVideo(_BlackBackground);
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
void MonitoringObjectTwoValue::Refresh()
{
	RefreshObject(FALSE);
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
void MonitoringObjectTwoValue::RefreshObject(e_BOOL _Forced)
{

    if (!GetStopMonitoring())
	{
		/*%C Backup current visibility */
		e_BOOL VisibleBackUp2 = VTFValue2.IsVisible();

		/*%C Refresh the 1st value */
        if (GetIdParam2() != NO_ID)
		{
			UWORD16 Value2;
			/*%C Read Value */
			DataBaseAccess::ReadValue(	&Value2,
												GetIdParam2(),
												GetDbTarget2());

            /*%C Saturation */
            SaturateValue2(&Value2);

			/*%C Apply the divisor */
			Value2 = Value2 / GetDivisionFactorOfValue();

			/*%C Clear previous value if different */
            if (VTFValue2.GetValue() != Value2)
   			{
			   	VTFValue2.Clear();
		   	}
         	/*%C Set visibility to FALSE to unable next SetFloat(), ForceValue()
	         SetFloat() and RefreshValueColumn() to call Hide() and Show() methods */
        	VTFValue2.SetVisible(FALSE);

#ifdef HMI_CONFIG_TRUNCATED_I_E
			/*%C If decimal is asked */
            if (FloatDisplayOn2)
			{
                //   if value >= 100 or value == 1.0
                //   then the value is set with Integer attribute to
                //   force three significant digits
                if ( (Value2 >= 1000) || (Value2 == 10) )
				{
					VTFValue2.SetFloat(FALSE);
					Value2 = Value2 / 10;
				}
				/*%C else Value stay decimal */
				else
				{
					VTFValue2.SetFloat(TRUE);
				}
			}
#endif /* HMI_CONFIG_TRUNCATED_I_E */

            if (_Forced)
			{
				VTFValue2.ForceValue(Value2);
			}
         	else
			{
				VTFValue2.SetValue(Value2);
			}
		}

		/*%C Backup current visibility */
		e_BOOL VisibleBackUp = VTFValue.IsVisible();

		/*%C Refresh the 2nd Value */
        if (GetIdParam() != NO_ID)
		{
			UWORD16 Value;

			/*%C Read Value */
			DataBaseAccess::ReadValue(	&Value,
												GetIdParam(),
												GetDbTarget());

            /*%C Saturation */
            SaturateValue(&Value);

			/*%C Apply the divisor */
			Value = Value / GetDivisionFactorOfValue();

			/*%C Clear previous value if different */
            if (VTFValue.GetValue() != Value)
   			{
			   	VTFValue.Clear();
		   	}

         	/*%C Set visibility to FALSE to unable next SetValue(), ForceValue()
	         SetFloat() and RefreshValueColumn() to call Hide() and Show() methods */
         	VTFValue.SetVisible(FALSE);

#ifdef HMI_CONFIG_TRUNCATED_I_E
			/*%C If decimal is asked */
            if (GetFloatDisplayOn())
			{
                //   if value >= 100 or value == 1.0
                //   then the value is set with Integer attribute to
                //   force three significant digits
                if ( (Value >= 1000) || (Value == 10) )
				{
					VTFValue.SetFloat(FALSE);
					Value = Value / 10;
				}
				else
				{
					VTFValue.SetFloat(TRUE);
				}
			}
#endif /*  HMI_CONFIG_TRUNCATED_I_E */

            if (_Forced)
			{
				VTFValue.ForceValue(Value);
			}
			else
			{
				VTFValue.SetValue(Value);
			}

		}

		/*%C check the colum value */
		RefreshValueColumn();

		/*%C Restore visibility */
      	VTFValue.SetVisible(VisibleBackUp);
      	VTFValue2.SetVisible(VisibleBackUp2);

		/*%C Display the valuie */
        if (IsVisible())
		{
			VTFValue2.Show();
			VTFValue.Show();
			TFUnit.Show();
			TFSep.Show();
		}

		SetValueReady(TRUE);
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
void MonitoringObjectTwoValue::Show()
{
	DisplayObject::Show();

	/*%C Display the table symbol */
    if (GetReverseVideo())
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

	/*%C Display the title */
	TFTitle.Show();

	/*%C Display the value if it is disponible */
    if (GetValueReady())
	{
		VTFValue2.Show();
		VTFValue.Show();
		TFUnit.Show();
		TFSep.Show();
        if (GetTrigger())
		{
            FTrig.Show();
		}
	}
	/*%C Else display "-" */
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
void MonitoringObjectTwoValue::Hide()
{
	VTFValue2.Hide();
	TFSep.Hide();
	MonitoringObject::Hide();    
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
void MonitoringObjectTwoValue::RefreshValueColumn()
{
    UWORD16 StartCol = LEFT_MARGIN_WIDTH + ( FRAME_WIDTH - 
                                             VTFValue.GetPixelSize() -
                                             TFSep.GetPixelSize() -
                                             VTFValue2.GetPixelSize() ) / 2;

    VTFValue.SetCol(    StartCol );
    TFSep.SetCol(       VTFValue.GetCol() + VTFValue.GetPixelSize() );
    VTFValue2.SetCol(   TFSep.GetCol() + TFSep.GetPixelSize() );
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
void MonitoringObjectTwoValue::DisplayNoValue()
{
	/*%C Display String "-" : which means there's no value to display */
    VTFValue.SetText((UBYTE *)" - ");
    VTFValue2.SetText((UBYTE *)" - ");

    RefreshValueColumn();

	VTFValue2.Show();
	VTFValue.Show();
	TFSep.Show();
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
void MonitoringObjectTwoValue::StartMonitoringMode()
{
	MonitoringObject::StartMonitoringMode();   
}
/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C                                                                          */
/*%C Stop object monitoring		   											  */
/*%C                                                                          */
/*%I Input Parameter : 														  */
/*%I		NONE															  */
/*%IO Input/Output : 														  */
/*%IO		NONE															  */
/*%O Output Parameter : 													  */
/*%O 		NONE								  							  */
/******************************************************************************/
void MonitoringObjectTwoValue::StopMonitoringMode()
{
	MonitoringObject::StopMonitoringMode();
	DisplayNoValue();
}
/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C                                                                          */
/*%C Stop object monitoring		   											  */
/*%C    - virtual method forwards call to base class for processing           */
/*%C                                                                          */
/*%I Input Parameter : 														  */
/*%I		e_BOOL _DisplayFlag                                               */
/*%IO Input/Output : 														  */
/*%IO		NONE															  */
/*%O Output Parameter : 													  */
/*%O 		NONE								  							  */
/******************************************************************************/
void MonitoringObjectTwoValue::StopMonitoringMode(e_BOOL _DisplayFlag)
{
	MonitoringObject::StopMonitoringMode(_DisplayFlag);
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
void MonitoringObjectTwoValue::ShowTrigger()
{
    MonitoringObject::SetTrigger(TRUE);

    FTrig.SetLine(10);
    FTrig.SetCol(35);
    FTrig.Show();
}


