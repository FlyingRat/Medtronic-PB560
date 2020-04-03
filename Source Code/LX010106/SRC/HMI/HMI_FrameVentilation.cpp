/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameVentilation.cpp    	  		                  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Fenetre Ventilation																      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_FrameVentilation.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Message.hpp"
#include "HMI_DataBaseAccess.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "HMI_Tools.hpp"
extern "C"
{
#include "DB_Config.h"
}

#define MONITORING_HEIGHT 151
/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
FrameVentilation::FrameVentilation():VFrame()
{
   IESelected = TRUE;
   ValveDetected = TRUE;
   BatVisible = FALSE;
   FiO2Enabled = FALSE;
   SpO2Enabled = FALSE;
   IsInhibApneaAlarm = TRUE;
   SetImpactDisplay(FALSE);
   ValveVisible = FALSE;
   Mode = VOL;
   this->ExhalFlowUsed = FALSE;
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
e_BOOL FrameVentilation::IsBatVisible()
{
	return (e_BOOL)(BatVisible == TRUE);
}
/*----------------------------------------------------------------------------*/
e_BOOL FrameVentilation::IsValveVisible()
{
	return (e_BOOL)(ValveVisible == TRUE);
}
/*----------------------------------------------------------------------------*/
e_BOOL FrameVentilation::IsInhibAlarmVisible()
{
	 return (e_BOOL)(IsInhibAlarm == TRUE);
}
/*----------------------------------------------------------------------------*/
e_BOOL FrameVentilation::IsInhibApneaAlarmVisible()
{
	 return (e_BOOL)(IsInhibApneaAlarm == TRUE);
}
/*----------------------------------------------------------------------------*/
e_BOOL FrameVentilation::IsCancelAlarmVisible()
{
	 return (e_BOOL)(IsCancelAlarm == TRUE);
}
/*----------------------------------------------------------------------------*/
DisplayObject* FrameVentilation::GetAlarmField()
{
	return &this->LAlarme;
}
/*----------------------------------------------------------------------------*/
DisplayObject** FrameVentilation::GetRefreshTable()
{
	return RefreshTable;
}
/*----------------------------------------------------------------------------*/
void FrameVentilation::SetPressConvention(e_BOOL _Conv)
{
	if(_Conv)
        PressConvention.SetName((UBYTE**)cMSG_RelativePressureRel);
    else
        PressConvention.SetName((UBYTE**)cMSG_RelativePressureAbs);
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
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::init()
{

   UWORD16 _col;
   UWORD16 _colLabel = 6;


   	PressConvention.SetParent				(this);



	PressConvention.Init  					(NO,
   									(UBYTE**)cMSG_RelativePressureRel,
   									17,
   									115);


    PressConvention.SetFontLabel(FONT_1);


	InhibApneaAlarm.SetParent	(this);

	InhibApneaAlarm.Init			(19,
										251,
										0,
										FALSE,
										ALARM_TRIANGLE_BLACK_DOT);

	InhibAlarm.SetParent			(this);

	InhibAlarm.Init				(19,
										274,
										0,
										FALSE,
										BELL_BLACK);

	CancelAlarm.SetParent		(this);

	CancelAlarm.Init				(19,
										297,
										0,
										FALSE,
										ALARM_TRIANGLE_BLACK);

   BarVentil.SetParent			(this);

	BarVentil.InitDbAccess		(LPF_PATIENT_PRESSURE_S16,
	                           COMPUTE,
   		                     COMPUTED_PEEP_U16,
         	                  COMPUTED_LPF_PIP_U16);

	BarVentil.Init					(38,
										168,
										VERT,
										0,
                              (UBYTE**)cMSG_PressureUnit);

   BarVentil.SetDivider			(10);

	MonitorBox.SetParent			(this);

	MonitorBox.Init				(cVENTIL_FIRST_LINE,
										COL_VENTILBOX,
                              MONITORING_HEIGHT,
			                     WHITH_VENTILBOX,
         			            TRUE,
			                     TRUE,
         			            TRUE);

	AlarmBox.SetParent			(this);

	AlarmBox.Init					(184,
										COL_VENTILBOX,
										41,
				                  WHITH_VENTILBOX,
				                  TRUE,
				                  TRUE,
				                  FALSE);


	LOVPip.SetParent				(this);

   LOVPip.InitDbAccess			(COMPUTED_LPF_PIP_U16,
   									COMPUTE);

   LOVPip.Init  					(NO,
   									(UBYTE**)cMSG_InsuflationPressurePeakMon,
   									54,
   									COL_VENTILBOX,
   									17,
					               (UBYTE**)cMSG_PressureUnit);

   LOVPip.SetColLabel			(_colLabel);

   LOVPip.SetColSep				(40);

	LOVPip.SetColValue1			(48);

	LOVPip.SetInvertVideo		(TRUE);

	LOVPip.SetDivider				(10);


	LOVVti.SetParent				(this);

	LOVVti.InitDbAccess			(COMPUTED_VTI_U16,
										COMPUTE);

	LOVVti.Init 					(NO,
										(UBYTE**)cMSG_Vti,
										77,
										COL_VENTILBOX,
										1400,
										(UBYTE**)cMSG_VolumeUnit);

	LOVVti.SetColLabel			(_colLabel);

	LOVVti.SetColSep				(40);

	LOVVti.SetColValue1			(48);

	LOVVti.SetInvertVideo		(TRUE);

	LOVVti.SetMaxDisplayValue	(9999);


	LOVVte.SetParent				(this);

	LOVVte.InitDbAccess			(COMPUTED_VTE_U16,
										COMPUTE);

	LOVVte.Init 					(NO,
										(UBYTE**)cMSG_Vte,
										100,
										COL_VENTILBOX,
										1000,
										(UBYTE**)cMSG_VolumeUnit);

	LOVVte.SetColLabel			(_colLabel);

	LOVVte.SetColSep				(40);

	LOVVte.SetColValue1			(48);

	LOVVte.SetInvertVideo		(TRUE);

	LOVVte.SetMaxDisplayValue	(9999);	

   LOVVm.SetParent				(this);

	LOVVm.InitDbAccess			(COMPUTED_VMI_U16,
										COMPUTE);

	LOVVm.Init 						(NO,
										(UBYTE**)cMSG_Vm,
										123,
										COL_VENTILBOX,
										1000,
										(UBYTE**)cMSG_VolumeLiterUnit);

	LOVVm.SetColLabel				(_colLabel);

	LOVVm.SetColSep				(40);

	LOVVm.SetColValue1			(48);

	LOVVm.SetInvertVideo			(TRUE);

	LOVVm.SetFloatValue1			(TRUE);

	LOVVm.SetMaxDisplayValue	(999);


   LOVR.SetParent				   (this);

	LOVR.InitDbAccess			   (MEASURE_R_U16,
										COMPUTE);

	LOVR.Init  					   (NO,
										(UBYTE**)cMSG_RateMon,
										146,
										COL_VENTILBOX,
										10,
										(UBYTE**)cMSG_FrequencyUnit);

	LOVR.SetColLabel				(_colLabel);

	LOVR.SetColSep				   (40);

	LOVR.SetColValue1			   (48);

	LOVR.SetInvertVideo			(TRUE);

	LOVR.SetMaxDisplayValue	(99);	


	LTVIE.SetParent				(this);

	LTVIE.InitDbAccess			(MEASURE_IE_NUMERATOR_U16,
										COMPUTE,
										MEASURE_IE_DENOMINATOR_U16,
										COMPUTE);	  

	LTVIE.Init  					(NO,
					               (UBYTE**)cMSG_IERation,
					               169,
					               COL_VENTILBOX,
					               1,
					               (UBYTE**)cMSG_Colon,
					               20,
					               (UBYTE**)cMSG_NoneUnit);

	LTVIE.SetColLabel				(_colLabel);

   LTVIE.SetColSep				(40);

   LTVIE.SetColValue1			(48);

	LTVIE.SetColValue2			(82);

	LTVIE.SetFontUnit1			(FONT_4);

	LTVIE.SetFloatValues			(TRUE);

	LTVIE.SetInvertVideo			(TRUE);

   _col = LTVIE.GetPixelSize() + 12;

	LTVIE.SetColTrigger			(_col);

	LTVIE.SetMaxDisplayValue	(99);
	LTVIE.SetMaxDisplayValue2	(1990);


	LOVIT.SetParent            (this);

	LOVIT.InitDbAccess         (MEASURE_IT_U16,COMPUTE);

	LOVIT.Init                 (NO,
                              (UBYTE**)cMSG_ITRation,
                              138,
                              COL_VENTILBOX,
                              1000, (UBYTE**)cMSG_PerCentUnit);

	LOVIT.SetColLabel          (_colLabel);

	LOVIT.SetColSep            (40);

	LOVIT.SetColValue1         (48);

   LOVIT.SetInvertVideo       (TRUE);

   LOVIT.SetTrigger           (TRUE);

   _col = LOVIT.GetPixelSize() + 12;

	LOVIT.SetColTrigger			(_col);

	LOVIT.SetMaxDisplayValue	(100);

      

   LOVFIO2.SetParent(this);

	LOVFIO2.InitDbAccess       (COMPUTED_FIO2,COMPUTE);

	LOVFIO2.Init               (NO,
                              (UBYTE**)cMSG_FiO2,
                              168,
                              COL_VENTILBOX,
                              21,
                              (UBYTE**)cMSG_PerCentUnit);

	LOVFIO2.SetColLabel        (_colLabel);

	LOVFIO2.SetColSep          (40);

	LOVFIO2.SetColValue1       (48);

	LOVFIO2.SetInvertVideo     (TRUE);

	LOVFIO2.SetMaxDisplayValue	(999);

   LOVSPO2.SetParent(this);

	LOVSPO2.InitDbAccess       (MEASURE_SPO2_U16,COMPUTE);

	LOVSPO2.Init               (NO,
                              (UBYTE**)cMSG_SpO2,
                              168,
                              COL_VENTILBOX,
                              21,
                              (UBYTE**)cMSG_PerCentUnit);

	LOVSPO2.SetColLabel        (_colLabel);

	LOVSPO2.SetColSep          (40);

	LOVSPO2.SetColValue1       (48);

	LOVSPO2.SetInvertVideo     (TRUE);


   LOVFuite.SetParent(this);

	LOVFuite.InitDbAccess      (COMPUTED_LEAK_HMI_U16,COMPUTE);

	LOVFuite.Init              (NO,
                              (UBYTE**)cMSG_FuiteMon,
                              168,
                              COL_VENTILBOX,
                              1000,
                              (UBYTE**)cMSG_FlowUnit);


	LOVFuite.SetColLabel       (_colLabel);

  	LOVFuite.SetColSep         (40);

   LOVFuite.SetColValue1      (48);

	LOVFuite.SetInvertVideo    (TRUE);

	LOVFuite.SetMaxDisplayValue	(200);

	BOBat.SetParent				(this);

	BOBat.Init			         (15,
										161);

	SFValve.SetParent          (this);

	SFValve.Init               (15,
                              231,
                              0,
                              FALSE,
                              VALVE_BLACK);

   Message.SetParent				(this);

	Message.Init					(33,
										COL_VENTILBOX,
										151,
				                  WHITH_VENTILBOX,
				                  TRUE);

	LAlarme.SetParent				(this);

	LAlarme.Init					(NO,
					               (UBYTE**)cMSG_Alarm,
					               200,
					               202);

	GetLoupeObject()->SetParent(this);

	GetLoupeObject()->Init		(32,
										COL_VENTILBOX);
                              
   InitInfoVentilTable();

	/*%C Table de refresh */

	/*%C Alway */
	RefreshTable[0] = &this->BarVentil;
	RefreshTable[1] = NULL;

	/*%C Insp */
	RefreshTable[2] 	= &this->LOVVte;
    RefreshTable[3] 	= &this->LOVR;
	RefreshTable[4] 	= &this->LTVIE;
	RefreshTable[5]     = &this->LOVFuite;
	RefreshTable[6]     = &this->LOVIT;
	RefreshTable[7] 	= NULL;

	/*%C Exp */
	RefreshTable[8] 	= &this->LOVPip;
	RefreshTable[9] 	= &this->LOVVti;
	RefreshTable[10] 	= &this->LOVVm;
    RefreshTable[11]    = &this->LOVFIO2;
    RefreshTable[12]    = &this->LOVSPO2;
	RefreshTable[13] 	= NULL;

	/*%C XAlway */
	RefreshTable[14] 	= &this->BOBat;
	RefreshTable[15]	= NULL;

	HideLoupe();

	/*%C Affichage du monitoring */
	//ShowMonitoring();

	/*%C Affichage de la batterie */
	SetBatVisible(TRUE, TRUE);

	/*%C Effacement des alarmes */
   HideCurrentAlarme();

}
/************************************************************************/
/* Description   : Initilalise la table de configuration des objets de  */
/*                 ventilation permettant de gérer l'ordre d'affichage  */
/*                 et la visibilité pour chaque mode de ventilation     */
/* Parametres en entree : Néant                                         */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameVentilation::InitInfoVentilTable(void)
{
   UWORD16 i,j;

   /* initialisation du tableau en ram avec le tableau de constantes */
   for(i=0; i<OBJECT_VENTIL_OBJECT_MAX+1; i++)
   {
      for(j=0; j<cVENTIL_MAX_MODE; j++)
      {
         InfoVentil[i].InfoByMode[j].Visible = cInfoVentil[i].InfoByMode[j].Visible;
         InfoVentil[i].InfoByMode[j].Order = cInfoVentil[i].InfoByMode[j].Order;
      }
   }

   InfoVentil[OBJECT_VENTIL_LOVPIP].pObject = &LOVPip;
   InfoVentil[OBJECT_VENTIL_LOVVTI].pObject = &LOVVti;
   InfoVentil[OBJECT_VENTIL_LOVVTE].pObject = &LOVVte;
   InfoVentil[OBJECT_VENTIL_LOVVM].pObject = &LOVVm;
   InfoVentil[OBJECT_VENTIL_LOVR].pObject = &LOVR;
   InfoVentil[OBJECT_VENTIL_LOVFUITE].pObject = &LOVFuite;
   InfoVentil[OBJECT_VENTIL_LOVFIO2].pObject = &LOVFIO2;
   InfoVentil[OBJECT_VENTIL_LOVSPO2].pObject = &LOVSPO2;
   InfoVentil[OBJECT_VENTIL_LTVIE].pObject = &LTVIE;
   InfoVentil[OBJECT_VENTIL_LTVIT].pObject = &LOVIT;
   InfoVentil[OBJECT_VENTIL_OBJECT_MAX].pObject = NULL;

   SetInfoTable(  InfoVentil,
                  OBJECT_VENTIL_OBJECT_MAX,
                  MONITORING_HEIGHT,
                  cVENTIL_FIRST_LINE);

   if(!CheckInfoTable())
      Tools::Panic(PANIC_MODULE_VENTIL);

   RebuildFrameTree(Mode);
}
/************************************************************************/
/* Description   : Démarre le monitoring des objets                     */
/* Parametres en entree : Néant                                         */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameVentilation::ObjectsStartMonitoringMode(void)
{
   UWORD16 i;
   for(i=0;i<OBJECT_VENTIL_OBJECT_MAX;i++)
   {
      if(InfoVentil[i].pObject != NULL)
      {
         /*%C On ne lance le Monitoring de FiO2 que si le capteur est présent */
         if(i == OBJECT_VENTIL_LOVFIO2)
         {
            if(FiO2Enabled)
               InfoVentil[i].pObject->StartMonitoringMode();
         }
         /*%C On ne lance le Monitoring de SpO2 que si le capteur est présent */
         else if(i == OBJECT_VENTIL_LOVSPO2)
         {
            if(SpO2Enabled)
               InfoVentil[i].pObject->StartMonitoringMode();
         }
         else if(i == OBJECT_VENTIL_LOVFUITE)
         {
            if(ValveDetected)
               InfoVentil[i].pObject->StopMonitoringMode();
            else
			   InfoVentil[i].pObject->StartMonitoringMode();
		 }
		 else if(i == OBJECT_VENTIL_LOVVTE)
		 {
			if(this->ExhalFlowUsed)
				InfoVentil[i].pObject->StartMonitoringMode();
		 }
         else
            InfoVentil[i].pObject->StartMonitoringMode();
      }
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage du trigger																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::ShowTrigger()
{
	if(!IsMessageOn())
	{
      if(IESelected)
		   LTVIE.ShowTrigger();
      else
         LOVIT.ShowTrigger();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement du trigger																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::HideTrigger()
{
	if(!IsMessageOn())
   {
		if(IESelected)
		   LTVIE.HideTrigger();
      else
         LOVIT.HideTrigger();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage de la batterie																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	BatVisible : TRUE si visible														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::SetBatVisible(e_BOOL _BatVisible, e_BOOL _ImpactDisplay)
{
	BatVisible = _BatVisible;

   if(_ImpactDisplay)
   {
   	if(BatVisible)
      {
		   BOBat.Show();
   	}
	   else
      {
	   	BOBat.Hide();
   	}
   }      
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	des objets Batterie et Valve								            */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::ShowBatAndValve(e_BOOL _Visible)
{
	if(_Visible)
   {
		if(IsBatVisible())
      {
			BOBat.Show();
		}
		if(IsValveVisible())
      {
         DisplayValve();
      }
	}
	else
   {
		BOBat.Hide();
      SFValve.Hide();
	}
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	des objets Batterie et Valve								            */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::ShowPressConvention(e_BOOL _Visible)
{
	if(_Visible)
        PressConvention.Show();
	else
        PressConvention.Hide();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'objet Valve								                        */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::DisplayValve()
{
   UWORD16 Val;

 	DataBaseAccess::ReadValue(&Val,VENTIL_REQ_U16,CONFIG);

	if(ValveDetected)
		SFValve.SetBarredSymbol(FALSE);
	else
		SFValve.SetBarredSymbol(TRUE);

   if(Val)
      SFValve.Show();
   else
      SFValve.Hide();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage d'une alarme																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Actif : TRUE si visible 											            */
/*%I		Id : Id de l'alarme si visible													*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::ShowCurrentAlarme(e_BOOL _Actif, UWORD16 _Id)
{
   if(_Actif)
   {
		HideCurrentAlarme();
		LAlarme.SetWhithBox(AlarmBox.GetWidth());
		LAlarme.SetAlarmId(_Id);

		AlarmBox.RefreshBoxRound(_Actif);

		LAlarme.SetInvertVideo(FALSE);

		LAlarme.Show();

	}
	else
   {
		HideCurrentAlarme();

		AlarmBox.RefreshBoxRound(_Actif);

		LAlarme.SetInvertVideo(TRUE);

		LAlarme.Show();
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement d'une alarme																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Actif : TRUE si visible 											            */
/*%I		Id : Id de l'alarme si visible													*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::HideCurrentAlarme()
{
   /*%C Affichage rectangle Blanc */
   InterfaceCppC::EraseZone	(LINE_VENTILBOX+2,
   									COL_VENTILBOX+2,
                              HEIGH_VENTILBOX-4,
                              WHITH_VENTILBOX-4,
                              0,
                              GetPage());

   LAlarme.SetInvertVideo		(FALSE);

   LAlarme.Hide();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Suppression d'une alarme	de la liste des alarmes actives                 */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_AlarmId : Id de l'alarme													      */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::RemoveAlarm(UWORD16 _AlarmId)
{
      LAlarme.RemoveAlarmId(_AlarmId);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Suppression de toutes les alarmes                                        */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::RemoveAllAlarms(void)
{
      LAlarme.RemoveAllAlarms();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::Show()
{
	VFrame::Show();

   ShowInhibApneaOk(IsInhibApneaAlarmVisible());

   InhibAlarm.Show();
   
   CancelAlarm.Show();

	BarVentil.Show();

	ShowBatAndValve(TRUE);

    ShowPressConvention(TRUE);

	/*%C Affichage des messages OU du monitoring */
	if(IsMessageOn())
   {
		Message.Show();
	}
	else
   {
		ShowMonitoring();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement	de l'Objet																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::Hide()
{
    BarVentil.Hide();
    ShowBatAndValve(FALSE);
    ShowPressConvention(FALSE);    

    ObjectsHide(Mode);
    VFrame::Hide();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet							  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::RefreshLanguage()
{
	BarVentil.RefreshLanguage();
	LAlarme.RefreshLanguage();
	BOBat.RefreshLanguage();

   ObjectsRefreshLanguage(Mode);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Changement du mode courant														  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Mode : mode courantMode : mode courant											*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::SetMode(e_MODE_TYPES _ModeTmp)
{
 	if(!IsMessageOn())
   {
      ObjectsHide(Mode);
   }
   
   Mode = _ModeTmp;
   RebuildFrameTree(Mode);

 	if(!IsMessageOn())
   {
      ObjectsShow(Mode);
	}
}
/************************************************************************/
/* Description          : Determine la presence de IE ou de IT			   */
/* Parametres en entree : aucun	                                       */
/*		- IESelected : presence de IE									            */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameVentilation::SetIESelected(e_BOOL _IESelected)
{
   if(IESelected != _IESelected)
   {
      if(!IsMessageOn())
      {
         ObjectsHide(Mode,OBJECT_VENTIL_LTVIE);
         ObjectsHide(Mode,OBJECT_VENTIL_LTVIT);
      }

      /*%C Changement de configuration I/T -> I/E */
      SwitchDisplayConfigForAllModes(OBJECT_VENTIL_LTVIE, OBJECT_VENTIL_LTVIT);

      /*%C Reconstruction de l'arbre d'affichage de la ventilation */
      RebuildFrameTree(Mode);

      if(!IsMessageOn())
      {
         ObjectsShow(Mode,OBJECT_VENTIL_LTVIE);
         ObjectsShow(Mode,OBJECT_VENTIL_LTVIT);
      }
      IESelected = _IESelected;
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de la zone de monitoring											  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::ShowMonitoring()
{
	/*%C Desactivation du refresh */
   EnableMonitZoneRefresh(TRUE);

   SetMessageOn(FALSE);
	SetMonitorOn(TRUE);
	MonitorBox.Show();
	AlarmBox.Show();
	SetMode(Mode);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de la zone de monitoring											  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::HideMonitoring()
{
	/*%C Desactivation du refresh */
	EnableMonitZoneRefresh(FALSE);

	SetMessageOn(TRUE);
	SetMonitorOn(FALSE);

   ObjectsHide(Mode);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Affichage d'un Message															  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Visible : TRUE si Affichage									            	*/
/*%I		Message : Message a afficher								         			*/
/*%I		Symbol  : Symbole a afficher														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::ShowMessage( e_BOOL _Visible,
												UBYTE* _Message,
                                    e_SYMBOL _Symbol)
{
	if(_Visible)
   {
		Message.Hide();
      SetMessageOn(TRUE);
		SetMonitorOn(FALSE);
		HideMonitoring();
		Message.SetWhithBox(MonitorBox.GetWidth() - 5);
      Message.SetMessage(_Message,_Symbol);
      Message.Show();
	}
	else
   {
		SetMessageOn(FALSE);
		SetMonitorOn(TRUE);
		Message.Hide();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Arret du monitorage pour l'Objet												  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE									            									*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::StopMonitoringMode()
{
   /*%C Efface du monitoring */
   HideMonitoring();

   ObjectsStopMonitoringMode();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Reprise du monitorage pour l'Objet											  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE									            									*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::StartMonitoringMode()
{
   this->StartMonitoringMode(FALSE, FALSE);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	IsFio2Sensor = presence ou non du capteur Fio2								*/
/*%I	  	IsSpo2Sensor = presence ou non du capteur Spo2								*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::StartMonitoringMode(e_BOOL IsFio2Sensor, e_BOOL IsSpO2Sensor)
{
	/*%C Affichage du monitoring */
   ShowMonitoring();

   if(IsFio2Sensor)
      FiO2Enabled = TRUE;

   if(IsSpO2Sensor)
      SpO2Enabled = TRUE;

   ObjectsStartMonitoringMode();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C determine si les valeurs de la zone refresh acceptent le refresh 			*/
/*%I  (!= StartMonitoringMode) qui affiche "-" a la place de la valeur			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::EnableMonitZoneRefresh(e_BOOL _Enable)
{
   ObjectsRefreshEnable(_Enable);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage du symbole Inib Alarm														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	_InibOk																	            */
/*%I	  	_ImpactDisplay															            */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::SetInibOk(e_BOOL _InibOk, e_BOOL _ImpactDisplay)
{

	IsInhibAlarm = _InibOk;
   if(_ImpactDisplay)
   {
	   if(_InibOk)
      {
		   ShowInibOk(TRUE);
      }
	   else
      {
		   ShowInibOk(FALSE);
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	du symbole Inib Alarm														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	_Visible																					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::ShowInibOk(e_BOOL _Visible)
{
	if(_Visible)
	{
		if(IsInhibAlarmVisible())
		{
			InhibAlarm.Show();
		}
	}
	else
	{
		InhibAlarm.Hide();
	}
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage du symbole Inhib Apnea Alarm  											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	InibOk																	            */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::SetInhibApneaOk(e_BOOL _InhibOk)
{

	IsInhibApneaAlarm = _InhibOk;

	if(_InhibOk)
   {
		ShowInhibApneaAlarm();
   }
	else
   {
		HideInhibApneaAlarm();
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	du symbole Inhib Apnea Alarm												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	_Visible																					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::ShowInhibApneaOk(e_BOOL _Visible)
{
	if(_Visible)
	{
		if(IsInhibApneaAlarmVisible())
		{
			ShowInhibApneaAlarm();
		}
	}
	else
	{
		HideInhibApneaAlarm();
	}
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage du symbole Cancel Alarm														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	CancelOk																	            */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::SetCancelOk(e_BOOL _CancelOk, e_BOOL _ImpactDisplay)
{

	IsCancelAlarm = _CancelOk;

   if(_ImpactDisplay)
   {
   	if(_CancelOk)
	   {
		   CancelAlarm.Show();
      }
	   else
      {
	   	CancelAlarm.Hide();
      }
   }      
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	du symbole Cancel Alarm														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	_Visible																					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVentilation::ShowCancelOk(e_BOOL _Visible)
{
	if(_Visible)
	{
		if(IsCancelAlarmVisible())
		{
			CancelAlarm.Show();
		}
	}
	else
	{
		CancelAlarm.Hide();
	}
}
/************************************************************************/
/* Description          : Determine la presence ou l'absence de la      */
/*                         valve d'expiration			                  */
/* Parametres en entree :     	                                       */
/*		- _ValveDetected : presence de la valve						         */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameVentilation::SetValve(e_BOOL _ValveDetected, e_BOOL _ImpactDisplay)
{
#ifndef HMI_CONFIG_S2
   UWORD16 i;
#endif
   UWORD16 Val;
   DataBaseAccess::ReadValue(&Val,VENTIL_REQ_U16,CONFIG);
   ValveVisible = (e_BOOL)Val;

   if(ValveDetected != _ValveDetected)
   {
#ifndef HMI_CONFIG_S2
      if((!IsMessageOn())&&
         (Mode != VOL)&&
		 (Mode != VSIMV)&&
		 (Mode != PSIMV))
      {
         ObjectsHide(Mode,OBJECT_VENTIL_LOVFUITE);
         ObjectsHide(Mode,OBJECT_VENTIL_LOVVTE);
      }

      /*%C Pas de fonctionnement avec fuite pour les modes volume */
	  for(i=0; i<cVENTIL_MAX_MODE; i++)
      {
		 if ((i != VOL) && (i!= VSIMV) && (i!= PSIMV))
		 {
			/*%C Changement de configuration Fuite -> Vte */
			SwitchDisplayConfigForOneMode(OBJECT_VENTIL_LOVFUITE, OBJECT_VENTIL_LOVVTE, (e_MODE_TYPES)i);
		 }
	  }

	  /*%C Reconstruction de l'arbre d'affichage de la ventilation */
	  RebuildFrameTree(Mode);

	  if((!IsMessageOn())&&
		 (Mode != VOL)&&
		 (Mode != VSIMV)&&
		 (Mode != PSIMV))
	  {
         ObjectsShow(Mode,OBJECT_VENTIL_LOVFUITE);
         ObjectsShow(Mode,OBJECT_VENTIL_LOVVTE);
      }
#endif      
   }
   ValveDetected = _ValveDetected;
   
   if(_ImpactDisplay)
      DisplayValve();
}
/************************************************************************/
/* Description          : Positionne l'unité de pression                */
/* Parametres en entree :     	                                       */
/*		- _PressureUnit : Unité de pression                               */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameVentilation::SetPressureUnit(UBYTE** _PressureUnit)
{
   if(GetImpactDisplay())
   {
      ObjectsHide(Mode);
      BarVentil.Hide();
   }
   LOVPip.SetNameUnit(_PressureUnit);
   BarVentil.SetNameUnit(_PressureUnit);
   if(GetImpactDisplay())
   {
      BarVentil.Show();
      ObjectsShow(Mode);
   }      
}
/************************************************************************/
/* Description          : Active le monitoring de Fio2					   */
/* Parametres en entree :                                               */
/*       _Flag : TRUE si capteur                                        */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameVentilation::Fio2MonitorEnabled(e_BOOL _Flag)
{
   FiO2Enabled = _Flag;

	if(_Flag)
      LOVFIO2.StartMonitoringMode();
	else
      LOVFIO2.StopMonitoringMode();
}
/************************************************************************/
/* Description          : Active le monitoring de Spo2					   */
/* Parametres en entree :                                               */
/*       _Flag : TRUE si capteur                                        */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameVentilation::Spo2MonitorEnabled(e_BOOL _Flag)
{
   SpO2Enabled = _Flag;

	if(_Flag)
      LOVSPO2.StartMonitoringMode();
	else
      LOVSPO2.StopMonitoringMode();
}
/************************************************************************/
/* Description          : Exhalation flow used set or unset				*/
/* Parametres en entree : 		                                        */
/*		- _Flag : TRUE if used else FALSE								*/
/*		- _ImpactDisplay : TRUE if display has to be impacted			*/
/* Parametres en sortie : aucun											*/
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameVentilation::SetExhalFlowUsed(e_BOOL _Flag, e_BOOL _ImpactDisplay)
{
	_ImpactDisplay = _ImpactDisplay;

	this->ExhalFlowUsed = _Flag;

	if (LOVVte.IsRefreshObject())
	{
		if (_Flag)
			InfoVentil[OBJECT_VENTIL_LOVVTE].pObject->StartMonitoringMode();
		else
			InfoVentil[OBJECT_VENTIL_LOVVTE].pObject->StopMonitoringMode();
	}
}
/************************************************************************/
/* Description          : Shows the Apnea Inhibition symbol				*/
/* Parametres en entree : aucun	                                        */
/* Parametres en sortie : aucun											*/
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameVentilation::ShowInhibApneaAlarm()
{
#define CROSS_LINE1_SIZE 17
#define CROSS_LINE2_SIZE 16

	/* Displaying the Apnea Inhibition symbol */
	InhibApneaAlarm.Show();

	/* Writing a cross on top of it */
	InterfaceCppC::DisplayCross( 	InhibApneaAlarm.GetLine(),
									InhibApneaAlarm.GetCol(),
									CROSS_LINE1_SIZE,
									CROSS_LINE2_SIZE,
									1,
									GetPage());
}
/************************************************************************/
/* Description          : Hides the Apnea Inhibition symbol				*/
/* Parametres en entree : aucun	                                        */
/* Parametres en sortie : aucun											*/
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameVentilation::HideInhibApneaAlarm()
{
	/* Hiding the symbol */
	InhibApneaAlarm.Hide();

	/* Do not need to hide the cross since the previous call erase a zone*/
}
