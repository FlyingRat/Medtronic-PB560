/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameAlarme.cpp                                     			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Fenetre Alarme																		      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_FrameAlarme.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Config.hpp"
#include "HMI_Message.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "HMI_DatabaseAccess.hpp"
#include "HMI_Tools.hpp"
extern "C"
{
#include "stdio.h"
#include "DB_Config.h"
}
#define MONITORING_HEIGHT 117
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

UBYTE StringDate[20];

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/

FrameAlarme::FrameAlarme():VFrame()
{
   IESelected = TRUE;
   ValveDetected = TRUE;
   FiO2Enabled = FALSE;
	SpO2Enabled = FALSE;
   IsInhibApneaAlarm = TRUE;
   BatVisible = FALSE;

#ifdef HMI_CONFIG_TIME_24H_FORMAT
   SetTimeFormat(ALARM_24H_FORMAT);
#elif defined HMI_CONFIG_TIME_12H_FORMAT
   SetTimeFormat(ALARM_12H_FORMAT);
#else
   SetTimeFormat(ALARM_12H_FORMAT);
#endif

#ifdef HMI_CONFIG_DATE_US_FORMAT
   SetDateFormat(ALARM_US_FORMAT);
#elif defined HMI_CONFIG_DATE_EUR_FORMAT
   SetDateFormat(ALARM_EUR_FORMAT);
#else
   SetDateFormat(ALARM_EUR_FORMAT);
#endif
   SetImpactDisplay(FALSE);

   ValveVisible = FALSE;
   
   Mode = VOL;
}

/******************************************************************************/
/*                           ACCESSEURS						                	   */
/******************************************************************************/
e_BOOL FrameAlarme::IsBatVisible()
{
	 return (e_BOOL)(BatVisible == TRUE);
}
/*----------------------------------------------------------------------------*/
e_BOOL FrameAlarme::IsValveVisible()
{
	return (e_BOOL)(ValveVisible == TRUE);
}
/*----------------------------------------------------------------------------*/
e_BOOL FrameAlarme::IsInhibAlarmVisible()
{
	 return (e_BOOL)(IsInhibAlarm == TRUE);
}
/*----------------------------------------------------------------------------*/
e_BOOL FrameAlarme::IsInhibApneaAlarmVisible()
{
	 return (e_BOOL)(IsInhibApneaAlarm == TRUE);
}
/*----------------------------------------------------------------------------*/
e_BOOL FrameAlarme::IsCancelAlarmVisible()
{
	 return (e_BOOL)(IsCancelAlarm == TRUE);
}
/*----------------------------------------------------------------------------*/
DisplayObject* FrameAlarme::GetAlarmField()
{
   return &this->LAlarme;
}
/*----------------------------------------------------------------------------*/
void FrameAlarme::SetDateFormat(e_ALARM_DATE_FORMAT _format)
{
   AlarmDateFormat = _format;
}
/*----------------------------------------------------------------------------*/
e_ALARM_DATE_FORMAT FrameAlarme::GetDateFormat(void)
{
   return(AlarmDateFormat);
}
/*----------------------------------------------------------------------------*/
void FrameAlarme::SetTimeFormat(e_ALARM_TIME_FORMAT _format)
{
   AlarmTimeFormat = _format;
}
/*----------------------------------------------------------------------------*/
e_ALARM_TIME_FORMAT FrameAlarme::GetTimeFormat(void)
{
   return(AlarmTimeFormat);
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
void FrameAlarme::init()
{
   UWORD16 _col;
   
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

   SFValve.SetParent          (this);

	SFValve.Init               (15,
                              231,
                              0,
                              FALSE,
                              VALVE_BLACK);

	BOBat.SetParent				(this);

	BOBat.Init			         (15,
										161);


	GTable.SetParent				(this);

	GTable.Init						(32,
										1);
   /*%C Titre de la deuxième colonne (min) */
   GTable.SetColTitle(1,(UBYTE**)cMSG_MiniTab);

   /*%C Titre de la troisième colonne (patient)*/
   GTable.SetColTitle(2,(UBYTE**)cMSG_PatientTab);

   /*%C Titre de la quatrième colonne (max)*/
   GTable.SetColTitle(3,(UBYTE**)cMSG_MaxiTab);

	MonitorBox.SetParent			(this);

	MonitorBox.Init				(cALARM_FIRST_LINE,
										COL_ALARMEBOX,
										MONITORING_HEIGHT,
										WHITH_ALARMEBOX,
										TRUE,
										TRUE,
										TRUE);

	AlarmBox.SetParent			(this);

	AlarmBox.Init					(LINE_ALARMEBOX,
										COL_ALARMEBOX,
										HEIGH_ALARMEBOX,
				                  WHITH_ALARMEBOX,
				                  TRUE,
				                  TRUE,
				                  FALSE);

	LAlarme.SetParent				(this);

	LAlarme.Init					(NO,
										(UBYTE**)cMSG_Alarm,
										165,
//										COL_ALARMEBOX + 2);
										COL_ALARMEBOX + 4);

   LastAlarmDate.SetParent		(this);

   LastAlarmDate.Init			(210,
   									COL_ALARMEBOX + 4,
   									FONT_1,
   									FALSE,
   									(UBYTE *)"");

   LOVPip.SetParent				(this);

	LOVPip.InitDbAccess			(COMPUTED_LPF_PIP_U16,
										COMPUTE);

	LOVPip.Init						(NO,
										(UBYTE**)cMSG_InsuflationPressurePeakMon,
										50,
										COL_ALARMEBOX + 4,
										14,
               					(UBYTE**)cMSG_PressureUnit);

	LOVPip.SetColLabel				(0);

	LOVPip.SetColSep				(33);

	LOVPip.SetColValue1			(38);

	LOVPip.SetInvertVideo			(TRUE);

	LOVPip.SetDivider				(10);

	LOVPip.SetMaxDisplayValue	(999);


	LOVVti.SetParent				(this);

	LOVVti.InitDbAccess			(COMPUTED_VTI_U16,
										COMPUTE);

	LOVVti.Init						(NO,
										(UBYTE**)cMSG_Vti,
										50,
										COL_ALARMEBOX + 4,
										1400,
										(UBYTE**)cMSG_VolumeUnit);

	LOVVti.SetColLabel			(0);

	LOVVti.SetColSep				(33);

	LOVVti.SetColValue1			(38);

	LOVVti.SetInvertVideo		(TRUE);

	LOVVti.SetMaxDisplayValue	(9999);


   LOVMap.SetParent				(this);

	LOVMap.InitDbAccess			(AVERAGE_PRESSURE_U16,
										COMPUTE);

	LOVMap.Init						(NO,
										(UBYTE**)cMSG_MeanAirwayPressureMon,
										80,
										COL_ALARMEBOX + 4,
										1400,
										(UBYTE**)cMSG_PressureUnit);

	LOVMap.SetColLabel			(0);

	LOVMap.SetColSep				(33);

	LOVMap.SetColValue1			(38);

	LOVMap.SetInvertVideo		(TRUE);

	LOVMap.SetDivider				(10);

	LOVPeep.SetParent				(this);

	LOVPeep.InitDbAccess			(COMPUTED_PEEP_U16,
										COMPUTE);

	LOVPeep.Init  					(NO,
										(UBYTE**)cMSG_ExhalationPressureMon,
										110,
										COL_ALARMEBOX + 4,
										4,
					               (UBYTE**)cMSG_PressureUnit);

	LOVPeep.SetColLabel				(0);

	LOVPeep.SetColSep				(33);

	LOVPeep.SetColValue1			(38);

 	LOVPeep.SetDivider			(10);

	LOVPeep.SetInvertVideo		(TRUE);

	LOVPeep.SetMaxDisplayValue	(999);

	LTVIE.SetParent				(this);

	LTVIE.InitDbAccess         (MEASURE_IE_NUMERATOR_U16,
                              COMPUTE,
                              MEASURE_IE_DENOMINATOR_U16,
                              COMPUTE);

	LTVIE.Init  					(NO,
										(UBYTE**)cMSG_IERation,
										140,
										COL_ALARMEBOX + 4,
										22,
										(UBYTE**)cMSG_Colon,
										20,
					               (UBYTE**)cMSG_NoneUnit);


	LTVIE.SetColLabel				(0);

	LTVIE.SetFontUnit1			(FONT_4);

	LTVIE.SetInvertVideo			(TRUE);

	LTVIE.SetColSep				(33);

   LTVIE.SetColValue1			(38);

	LTVIE.SetColValue2			(71);

	LTVIE.SetFloatValues			(TRUE);

   _col = LTVIE.GetPixelSize() + 6;

	LTVIE.SetColTrigger			(_col);

	LTVIE.SetMaxDisplayValue	(1990);


   LOVR.SetParent				   (this);

	LOVR.InitDbAccess			   (COMPUTED_PULSE_U16,
										COMPUTE);

	LOVR.Init  					   (HEART_INVERSE_VIDEO,
										(UBYTE**)cMSG_NoneUnit,
										138,
										COL_ALARMEBOX + 4,
										10,
										(UBYTE**)cMSG_FrequencyUnit);

	LOVR.SetColLabel				(20);

	LOVR.SetColSep				   (33);

	LOVR.SetColValue1			   (38);

	LOVR.SetInvertVideo			(TRUE);

	LOVR.SetMaxDisplayValue	(99);


	LOVIT.SetParent            (this);

	LOVIT.InitDbAccess         (MEASURE_IT_U16,COMPUTE);

	LOVIT.Init                 (NO,
                              (UBYTE**)cMSG_ITRation,
                              138,
                              COL_ALARMEBOX + 4,
                              1000, (UBYTE**)cMSG_PerCentUnit);

	LOVIT.SetColLabel          (0);

	LOVIT.SetColSep            (33);

	LOVIT.SetColValue1         (38);

   LOVIT.SetInvertVideo       (TRUE);

   LOVIT.SetTrigger           (TRUE);

   _col = LOVIT.GetPixelSize() + 3;

	LOVIT.SetColTrigger			(_col);

	LOVIT.SetMaxDisplayValue	(100);


   LOVM.SetParent				   (this);

	LOVM.InitDbAccess			   (COMPUTED_VMI_U16,
										COMPUTE);

	LOVM.Init  					   (NO,
										(UBYTE**)cMSG_Vm,
										138,
										COL_ALARMEBOX + 4,
										10,
										(UBYTE**)cMSG_VolumeLiterUnit);

	LOVM.SetColLabel				(0);

	LOVM.SetColSep				   (33);

	LOVM.SetColValue1			   (38);

	LOVM.SetInvertVideo			(TRUE);

	LOVM.SetFloatValue1		   (TRUE);

	LOVM.SetMaxDisplayValue	(999);	
   
   
	Message.SetParent				(this);

	Message.Init					(32,
										COL_ALARMEBOX,
										117,
										WHITH_ALARMEBOX, 
										TRUE);

	Message.SetColLine1			(8);

	Message.SetColLine2			(8);

	Message.SetColLine3			(8);

	/*%C Choix de la loupe */
	SelectLoupeAlarm();

	GetLoupeObject()->SetParent(this);

	GetLoupeObject()->Init		(32,
										COL_ALARMEBOX);

   InitInfoAlarmTable();

	/*%C Table de refresh */

	/*%C Alway */
	RefreshTable[0] = NULL;

	/*%C Insp */
	RefreshTable[1] = &this->LOVPeep;
	RefreshTable[2] = &this->LTVIE;
   RefreshTable[3] = &this->LOVIT;
	RefreshTable[4] = NULL;

	/*%C Exp */
	RefreshTable[5] = &this->LOVPip;
	RefreshTable[6] = &this->LOVVti;
	RefreshTable[7] = &this->LOVMap;
	RefreshTable[8] = &this->LOVR;
	RefreshTable[9] = &this->LOVM;
	RefreshTable[10] = NULL;

	/*%C XAlway */
	RefreshTable[11] = &this->BOBat;
	RefreshTable[12] = NULL;

	/*%C initialisation de la loupe */
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
/*                 monitoring de la fenêtre alarme permettant de gérer  */
/*                 l'ordre d'affichage et la visibilité pour chaque mode*/
/*                 de ventilation                                       */
/* Parametres en entree : Néant                                         */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameAlarme::InitInfoAlarmTable(void)
{
   UWORD16 i,j;

   /* initialisation du tableau en ram avec le tableau de constantes */
   for(i=0; i<OBJECT_ALARM_OBJECT_MAX+1; i++)
   {
      for(j=0; j<cALARM_MAX_MODE; j++)
      {
         InfoAlarm[i].InfoByMode[j].Visible = cInfoAlarm[i].InfoByMode[j].Visible;
         InfoAlarm[i].InfoByMode[j].Order = cInfoAlarm[i].InfoByMode[j].Order;
      }
   }
   InfoAlarm[OBJECT_ALARM_LOVPIP].pObject = &LOVPip;
   InfoAlarm[OBJECT_ALARM_LOVVTI].pObject = &LOVVti;
   InfoAlarm[OBJECT_ALARM_LOVMAP].pObject = &LOVMap;
   InfoAlarm[OBJECT_ALARM_LOVPEEP].pObject = &LOVPeep;
   InfoAlarm[OBJECT_ALARM_LTVIE].pObject = &LTVIE;
   InfoAlarm[OBJECT_ALARM_LOVIT].pObject = &LOVIT;
   InfoAlarm[OBJECT_ALARM_LOVR].pObject = &LOVR;
   InfoAlarm[OBJECT_ALARM_LOVM].pObject = &LOVM;
   InfoAlarm[OBJECT_ALARM_OBJECT_MAX].pObject = NULL;

   SetInfoTable(  InfoAlarm,
                  OBJECT_ALARM_OBJECT_MAX,
                  MONITORING_HEIGHT,
                  cALARM_FIRST_LINE);

   if(!CheckInfoTable())
      Tools::Panic(PANIC_MODULE_ALARM);

   RebuildFrameTree(Mode);
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
void FrameAlarme::ShowTrigger()
{
   if(IESelected)
   	LTVIE.ShowTrigger();
   else
	   LOVIT.ShowTrigger();
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
void FrameAlarme::HideTrigger()
{
   if(IESelected)
   	LTVIE.HideTrigger();
   else
      LOVIT.HideTrigger();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Affichage de la batterie 																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	BatVisible : TRUE si visible														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::SetBatVisible(e_BOOL _BatVisible, e_BOOL _ImpactDisplay)
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
/*%C Affichage	des objets Batterie et Valve           								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::ShowBatAndValve(e_BOOL _Visible)
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
/*%C Affichage	de l'objet Valve								                        */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::DisplayValve()
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
/*%C  Affichage d'une alarme 																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Actif : TRUE si visible 									            		*/
/*%I	   Id : Id de l'alarmesi visible														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::ShowCurrentAlarme(e_BOOL Actif, UWORD16 Id)
{
	if(MutexAlarm)
   {
		LastAlarmDate.Hide();
    	LAlarme.Hide();
		MutexAlarm = FALSE;
	}

	if(Actif)
	{
		HideCurrentAlarme();
		LAlarme.SetWhithBox(AlarmBox.GetWidth());
		LAlarme.SetAlarmId(Id);

		AlarmBox.RefreshBoxRound(Actif);

		LAlarme.SetInvertVideo(FALSE);

		LAlarme.Show();
	}
	else
	{
		HideCurrentAlarme();

		AlarmBox.RefreshBoxRound(Actif);

		LAlarme.SetInvertVideo(TRUE);

		LAlarme.Show();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Effacement d'une alarme  																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Actif : TRUE si visible 									            		*/
/*%I	   Id : Id de l'alarmesi visible														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::HideCurrentAlarme()
{
   /*%C Affichage rectangle Blanc */
   InterfaceCppC::EraseZone				(LINE_ALARMEBOX+2, 
   												COL_ALARMEBOX+2,
                              			HEIGH_ALARMEBOX-4, 
                              			WHITH_ALARMEBOX-4, 0,
                              			GetPage());

   LAlarme.SetInvertVideo					(FALSE);

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
void FrameAlarme::RemoveAlarm(UWORD16 _AlarmId)
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
void FrameAlarme::RemoveAllAlarms(void)
{
      LAlarme.RemoveAllAlarms();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage de la derniere alarme														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::ShowLastAlarme(AlarmEvent* Alarm)
{
   UWORD16 Hours = 0;
   UBYTE AlarmSuffixe[5];
   UWORD16 _ColOffSet;

   Tools::StrCpy(AlarmSuffixe,(UBYTE *)"");

	if(Alarm->id<Mark_Begin_Technical_Alarm)
	{
      MutexAlarm = TRUE;

		/*%C Affiche la dernière alarme */
		LAlarme.SetWhithBox					(AlarmBox.GetWidth());

        LAlarme.SetAlarmId                  (Alarm->id);

 		InterfaceCppC::EraseZone			(LINE_ALARMEBOX+2, 
 													COL_ALARMEBOX+2,
                                 		HEIGH_ALARMEBOX-4, 
                                 		WHITH_ALARMEBOX-4,
                                 		0, 
                                 		GetPage());

      LAlarme.SetInvertVideo				(FALSE);
		LAlarme.Show();
      InterfaceCppC::DisplayLine			(LINE_ALARMEBOX+4, 
      											COL_ALARMEBOX+1,
                                 		HEIGH_ALARMEBOX-8, 
                                 		0, 
                                 		0, 
                                 		GetPage());

      InterfaceCppC::DisplayLine			(LINE_ALARMEBOX+4,
		                                 COL_ALARMEBOX+WHITH_ALARMEBOX-1,
		                                 HEIGH_ALARMEBOX-8, 
		                                 0, 
		                                 0, 
		                                 GetPage());


		/*%C Affiche la date et l'heure de la dernière alarme */
      Hours = Alarm->hour;

      if(GetTimeFormat() == ALARM_12H_FORMAT)
      {
        /* AM or PM*/
        if(Hours >= 12)
            Tools::StrCpy(AlarmSuffixe,(UBYTE *)"pm");
        else
            Tools::StrCpy(AlarmSuffixe,(UBYTE *)"am");
      }
      
      if(GetTimeFormat() == ALARM_12H_FORMAT)
      {
         if(Hours > 12)
         {
            Hours = Hours - 12;
         }
         else if(Hours == 0)
         {
            Hours = Hours + 12;
         }
      }

      if(GetDateFormat() == ALARM_US_FORMAT)
      {
       	sprintf(	(char *)StringDate,
       				"%02d/%02d/%02d %02d:%02d %s",
		   			Alarm->month,Alarm->day,Alarm->year,
			   		Hours,Alarm->min,AlarmSuffixe);
      }
      else
      {
       	sprintf(	(char *)StringDate,
       				"%02d/%02d/%02d %02d:%02d %s",
		   			Alarm->day,Alarm->month,Alarm->year,
			   		Hours,Alarm->min,AlarmSuffixe);
      }

      /* On centre l'affichage */
      _ColOffSet = WHITH_ALARMEBOX -  Tools::GetStringPixelSize(StringDate, LastAlarmDate.GetFont());
      if(_ColOffSet)
         LastAlarmDate.SetCol(COL_ALARMEBOX + _ColOffSet/2);

      LastAlarmDate.SetText				(StringDate);

		LastAlarmDate.Show();
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne la table des Objets a rafraichir											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
DisplayObject** FrameAlarme::GetRefreshTable()
{
	return RefreshTable;
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
void FrameAlarme::Show()
{
	VFrame::Show();

   if(GetImpactDisplay())
    	GTable.Show();

	ShowBatAndValve(TRUE);

   ShowInhibApneaOk(IsInhibApneaAlarmVisible());

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
/*%C Operation de changement de la langue	de l'Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/

void FrameAlarme::RefreshLanguage()
{

   ObjectsRefreshLanguage(Mode);
   
	BOBat.RefreshLanguage();

	LAlarme.RefreshLanguage();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/

void FrameAlarme::Hide()
{
	VFrame::Hide();

   ObjectsHide(Mode);

   ShowBatAndValve(FALSE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Changement du mode courant																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Mode : mode courant																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::SetMode(e_MODE_TYPES ModeTmp)
{
   if(!IsMessageOn())
   {
      ObjectsHide(Mode);
   }
   Mode = ModeTmp;
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
void FrameAlarme::SetIESelected(e_BOOL _IESelected)
{
   if(IESelected != _IESelected)
   {
      if(!IsMessageOn())
      {
         ObjectsHide(Mode,OBJECT_ALARM_LTVIE);
         ObjectsHide(Mode,OBJECT_ALARM_LOVIT);
      }

      /*%C Changement de configuration I/T -> I/E */
      SwitchDisplayConfigForAllModes(OBJECT_ALARM_LTVIE, OBJECT_ALARM_LOVIT);

      /*%C Reconstruction de l'arbre d'affichage de la ventilation */
      RebuildFrameTree(Mode);

      if(!IsMessageOn())
      {
         ObjectsShow(Mode,OBJECT_ALARM_LTVIE);
         ObjectsShow(Mode,OBJECT_ALARM_LOVIT);
      }
      IESelected = _IESelected;
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de la zone de monitoring													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::ShowMonitoring()
{
	/*%C Activation du refresh */
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
/*%C Effacement de la zone de monitoring													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::HideMonitoring()
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
/*%C Affichage d'un Message																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Visible : TRUE si Affichage									            	*/
/*%I		Message : Message a afficher									         		*/
/*%I		Symbol  : Symbole a afficher														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::ShowMessage(e_BOOL _Visible,
										UBYTE* _Message,
                              e_SYMBOL _Symbol)

{
	if(_Visible)
   {
		Message.Hide();

		SetMessageOn(TRUE);

		SetMonitorOn(FALSE);

		HideMonitoring();

		Message.SetWhithBox(this->MonitorBox.GetWidth());

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
/*%C Arret du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::StopMonitoringMode()
{
	/*%C Efface du monitoring */
	HideMonitoring();
   
   ObjectsStopMonitoringMode();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::StartMonitoringMode()
{
   this->StartMonitoringMode(FALSE, FALSE);
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
void FrameAlarme::ObjectsStartMonitoringMode(void)
{
   UWORD16 i;

   if(GetImpactDisplay())
   {
      for(i=0;i<OBJECT_ALARM_OBJECT_MAX;i++)
      {
         if(InfoAlarm[i].pObject != NULL)
            InfoAlarm[i].pObject->StartMonitoringMode();
      }
   }      
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
void FrameAlarme::StartMonitoringMode(e_BOOL IsFio2Sensor, e_BOOL IsSpO2Sensor)
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
/*%C Determine si les valeurs de la zone refresh acceptent le refresh			*/
/*%C 	(!= StartMonitoringMode)  qui affiche "-" a la place de la valeur			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::EnableMonitZoneRefresh(e_BOOL _Enable)
{
   ObjectsRefreshEnable(_Enable);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Configure la taille du tableau															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::SetTableSize(UBYTE _LineNb)
{
	GTable.SetSize(_LineNb);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affiche la table            															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::DisplayTable(void)
{
   GTable.Hide();
   GTable.Show();   
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Efface la table             															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::HideTable(void)
{
	GTable.Hide();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affiche la table            															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::ShowTable(void)
{
	GTable.Show();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Récupère la ligne de la première ligne inscriptible                      */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
UWORD16 FrameAlarme::GetFirstLineOfTable(void)
{
	return(GTable.GetFirstCellLineToWriteTo());
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Configure la ligne de séparation du paramètre en gras dans la table      */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Line : ligne qui doit être en gras        				            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::SetBoldLineOfTable(UWORD16 Line)
{
   GTable.SetBoldLine(Line);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Positionne toutes les lignes de la table à "non gras"                    */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Line : ligne qui doit être en gras        				            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameAlarme::ClearBoldLinesOfTable(void)
{
   GTable.ClearBoldLines();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Récupère la ligne de la première ligne inscriptible                      */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
UWORD16 FrameAlarme::GetSpacingOfTable(void)
{
	return(GTable.GetSpacingBetweenCells());
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Récupère l'indice de colonne de la colonne patient                       */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
UWORD16 FrameAlarme::GetPatientColOfTable(void)
{
   return(GTable.GetDisplayColForCell(0,2));
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Récupère la largeur de la colonne patient                                */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	            	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
UWORD16 FrameAlarme::GetPatientWidthOfTable()
{
   return(GTable.GetOtherColWidth());
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
void FrameAlarme::SetInibOk(e_BOOL _InibOk, e_BOOL _ImpactDisplay)
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
void FrameAlarme::ShowInibOk(e_BOOL _Visible)
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
void FrameAlarme::SetInhibApneaOk(e_BOOL _InhibOk)
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
void FrameAlarme::ShowInhibApneaOk(e_BOOL _Visible)
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
void FrameAlarme::SetCancelOk(e_BOOL _CancelOk, e_BOOL _ImpactDisplay)
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
void FrameAlarme::ShowCancelOk(e_BOOL _Visible)
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
/* Parametres en entree : aucun	                                       */
/*		- _ValveDetected : presence de la valve						         */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameAlarme::SetValve(e_BOOL _ValveDetected, e_BOOL _ImpactDisplay)
{
   UWORD16 Val;
   DataBaseAccess::ReadValue(&Val,VENTIL_REQ_U16,CONFIG);
   ValveVisible = (e_BOOL)Val;

   ValveDetected = _ValveDetected;

   if(_ImpactDisplay)
      DisplayValve();
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
void FrameAlarme::Fio2MonitorEnabled(e_BOOL _Flag)
{
   FiO2Enabled = _Flag;
   /* Pas de monitoring du FiO2 en fenêtre Alarme pour le moment */
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
void FrameAlarme::Spo2MonitorEnabled(e_BOOL _Flag)
{
   SpO2Enabled = _Flag;
   /* Pas de monitoring du SpO2 en fenêtre Alarme pour le moment */
}
/************************************************************************/
/* Description          : Positionne l'unité de pression                */
/* Parametres en entree : aucun	                                       */
/*		- _PressureUnit : Unité de pression                               */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameAlarme::SetPressureUnit(UBYTE** _PressureUnit)
{
   e_BOOL _VisibleBackup;

   ObjectsHide(Mode);

   _VisibleBackup = LOVPip.IsVisible();
   LOVPip.SetVisible(FALSE);
   LOVPip.SetNameUnit(_PressureUnit);
   LOVPip.SetVisible(_VisibleBackup);

   _VisibleBackup = LOVPeep.IsVisible();
   LOVPeep.SetVisible(FALSE);
   LOVPeep.SetNameUnit(_PressureUnit);
   LOVPeep.SetVisible(_VisibleBackup);

   _VisibleBackup = LOVMap.IsVisible();
   LOVMap.SetVisible(FALSE);
   LOVMap.SetNameUnit(_PressureUnit);
   LOVMap.SetVisible(_VisibleBackup);

   ObjectsShow(Mode);
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
void FrameAlarme::ShowInhibApneaAlarm()
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
void FrameAlarme::HideInhibApneaAlarm()
{
	/* Hiding the symbol */
	InhibApneaAlarm.Hide();

	/* Do not need to hide the cross since the previous call erase a zone*/
}
