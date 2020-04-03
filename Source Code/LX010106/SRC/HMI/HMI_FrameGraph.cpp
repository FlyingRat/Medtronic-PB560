/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameGraph.cpp            		                  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Fenetre Courbes																		      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_FrameGraph.hpp"
#define CURVE_INFO_MAX 5
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Message.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "HMI_DisplayObject.hpp"
#include "HMI_IhmType.hpp"
//#include "HMI_Controller.hpp"
#include "HMI_Tools.hpp"
extern "C"
{
#include "DB_Config.h"
#include "DB_Current.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
FrameGraph::FrameGraph():VFrame()    
{
	Mode = VOL;
	TriggerOn = FALSE;
	Freezed = FALSE;
   IESelected = TRUE;
   ValveDetected = TRUE; /* être cohérent avec le tableau de
                           configuration de l'affichage InfoGraph[] */
	FiO2Enabled = FALSE;
	SpO2Enabled = FALSE;

   FirstInitOk = FALSE;

   SetModeChange(FALSE);

   BlocExpiDetected =  TRUE;

   Mode = VOL;

   this->ExhalFlowUsed = FALSE;
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
DisplayObject** FrameGraph::GetRefreshTable()
{
	return RefreshTable;
}
/*----------------------------------------------------------------------------*/
e_BOOL FrameGraph::GetModeChange()
{
   return(ModeChange);
}
/*----------------------------------------------------------------------------*/
void FrameGraph::SetModeChange(e_BOOL _ModeChange)
{
   ModeChange = _ModeChange;
}
/*----------------------------------------------------------------------------*/
e_MODE_TYPES FrameGraph::GetPreviousMode()
{
   return(PreviousMode);
}
/*----------------------------------------------------------------------------*/
void FrameGraph::SetPreviousMode(e_MODE_TYPES _PreviousMode)
{
    PreviousMode = _PreviousMode;
}
/*----------------------------------------------------------------------------*/
void FrameGraph::SetBlocExpi(e_BOOL _BlocExpiDetected, e_BOOL _DisplayFlag)
{
   this->BlocExpiDetected = _BlocExpiDetected;

   this->GraphReInit( (e_BOOL)(!IsBlocExpiDetected() || !ValveDetected), _DisplayFlag);
}
/*----------------------------------------------------------------------------*/
e_BOOL FrameGraph::IsBlocExpiDetected()
{
   return(this->BlocExpiDetected);
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
void FrameGraph::init()
{

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

	BOBat.SetParent				(this);

	BOBat.Init			         (15,
										161);

	SFValve.SetParent          (this);

	SFValve.Init               (15,
                              231,
                              0,
                              FALSE,
                              VALVE_BLACK);

	SFPause.SetParent				(this);

	SFPause.Init					(14,
										117,
										0,
										FALSE,
										PAUSE);


   GTMode.SetParent				(this);

	GTMode.Init						(1,
										1,
										(UBYTE**)cMSG_Mode, 
										(UBYTE**)cMSG_Mode2,
					               (UBYTE**)cMSG_Mode3);


	/*%C Gestion Graph flow */
	PGCSmallFlow.InitRefreshTime	(TIME_REFRESH);

	CDFlow.Init						(GSmallFlow.GetScaleX(),
										GSmallFlow.GetScaleY());

	CDFlow.InitDbAccess			(CURVE_CORRECTED_FLOW_S16, 
										COMPUTE);


	/*%C Graph small flow */
	GSmallFlow.SetParent			(this);

	GSmallFlow.Init				(196,
										1,
										84,
										266,
										0,
										50,
										0,
										44,
                     			DataBaseAccess::GetMin(CURVE_MAX_FLOW_U16, CONFIG)*
                     			10,
                     			DataBaseAccess::GetMax(CURVE_MAX_FLOW_U16, CONFIG)*
                     			10,30,15,
                     			FONT_2,
                     			(UBYTE **)cMSG_SecondUnit,
                     			(UBYTE **)cMSG_FlowUnit,
			                     (UBYTE **)cMSG_OutOfLimit);

	GSmallFlow.SetGControl		(&PGCSmallFlow);

	GSmallFlow.AddCurve			(&CDFlow);

	GSmallFlow.GetScaleX()->InitDbAccess(CURVE_MAX_TIME_U16, CONFIG);
	GSmallFlow.GetScaleY()->InitDbAccess(CURVE_MAX_FLOW_U16, CONFIG);
	GSmallFlow.GetScaleY()->SetSymetric(TRUE);


	/*%C Gestion Graph Pressure */
	PGCSmallPressure.InitRefreshTime	(TIME_REFRESH);

	CDPressure.Init				(GSmallPressure.GetScaleX(),
										GSmallPressure.GetScaleY());

	CDPressure.InitDbAccess		(LPF_PATIENT_PRESSURE_S16,
										COMPUTE);

	CDPressure.GetPen()->SetDotted(FALSE);


	/*%C Graph small Pressure */
	GSmallPressure.SetParent	(this);

	GSmallPressure.Init			(112,
										1,
										84,
										266,
										0,
										50,
										0,
										44,
                        		DataBaseAccess::GetMin(CURVE_MAX_PRESSURE_U16, 
                        		CONFIG)*10,
		                        DataBaseAccess::GetMax(CURVE_MAX_PRESSURE_U16, 
		                        CONFIG)*10,
		                        0,
		                        15,
		                        FONT_2,
		                        (UBYTE **)cMSG_SecondUnit,
                        		(UBYTE **)cMSG_PressureUnit,
                        		(UBYTE **)cMSG_OutOfLimit);

	GSmallPressure.SetGControl	(&PGCSmallPressure);

	GSmallPressure.AddCurve		(&CDPressure);

	GSmallPressure.GetScaleX()->InitDbAccess(CURVE_MAX_TIME_U16, CONFIG);
	GSmallPressure.GetScaleY()->InitDbAccess(CURVE_MAX_PRESSURE_U16, CONFIG);


	/*%C Gestion Graph flow */
	WGCSmallFlowV.Init();
	CDFlowV.Init					(GSmallFlowV.GetScaleX(),
										GSmallFlowV.GetScaleY());

	CDFlowV.InitDbAccess			(CURVE_CORRECTED_VT_WOB_U16, 
										COMPUTE,CURVE_CORRECTED_FLOW_S16, 
										COMPUTE);


	/*%C Graph small flow */
	GSmallFlowV.SetParent		(this);

	GSmallFlowV.Init				(197,
										1,
										84,
										266,
										0,
										6000,
										0,
										44,
										DataBaseAccess::GetMin(CURVE_MAX_FLOW_U16, 
										CONFIG)*10,
										DataBaseAccess::GetMax(CURVE_MAX_FLOW_U16, 
										CONFIG)*10,
										30,
										15,
										FONT_2, 
										(UBYTE **)cMSG_VolumeUnit, 
										(UBYTE **)cMSG_FlowUnit,
										(UBYTE **)cMSG_OutOfLimit);

	GSmallFlowV.SetGControl		(&WGCSmallFlowV);

	GSmallFlowV.AddCurve			(&CDFlowV);

	GSmallFlowV.GetScaleX()->InitDbAccess(CURVE_MAX_VT_U16, CONFIG);
	GSmallFlowV.GetScaleY()->InitDbAccess(CURVE_MAX_FLOW_U16, CONFIG);
	GSmallFlowV.GetScaleY()->SetSymetric(TRUE);


	/*%C Gestion Graph Pressure */
	WGCSmallPressureV.Init();

	CDPressureV.Init				(GSmallPressureV.GetScaleX(),
										GSmallPressureV.GetScaleY());

	CDPressureV.InitDbAccess	(CURVE_CORRECTED_VT_WOB_U16,
                              COMPUTE,
                              FILTER_PATIENT_PRESSURE_S16, 
                              COMPUTE);

	CDPressureV.GetPen()->SetDotted(FALSE);


	/*%C Graph small Pressure */
	GSmallPressureV.SetParent	(this);

	GSmallPressureV.Init			(112,
										1,
										84,
										266,
										0,
										6000,
										0,
										44,
                        		DataBaseAccess::GetMin(CURVE_MAX_PRESSURE_U16,
                        		CONFIG)*10,
		                        DataBaseAccess::GetMax(CURVE_MAX_PRESSURE_U16, 
		                        CONFIG)*10,
		                        0,
		                        15,
		                        FONT_2,
		                        (UBYTE **)cMSG_VolumeUnit,
		                        (UBYTE **)cMSG_PressureUnit,
		                        (UBYTE **)cMSG_OutOfLimit);

	GSmallPressureV.SetGControl(&WGCSmallPressureV);

	GSmallPressureV.AddCurve(&CDPressureV);

	GSmallPressureV.GetScaleX()->InitDbAccess(CURVE_MAX_VT_U16, CONFIG);
	GSmallPressureV.GetScaleY()->InitDbAccess(CURVE_MAX_PRESSURE_U16, CONFIG);


	/*%C Graph Rate */
   MoRate.SetParent				(this);
	MoRate.Init					   (NO,
                              196,
										108,
										(UBYTE**)cMSG_RateMon,
										10,
										FALSE,
										(UBYTE**)cMSG_FrequencyUnit,
										FALSE,
										TRUE);

	MoRate.InitDbAccess		   (MEASURE_R_U16,
										COMPUTE);

	MoRate.SetInvertVideo		(TRUE);

   MoRate.SetMaxDisplayValue  (99);


   /*%C Graph FiO2 */
   MoFiO2.SetParent				(this);
	MoFiO2.Init						(NO,
                              196,
										161,
										(UBYTE**)cMSG_FiO2,
										10,
										FALSE,
										(UBYTE**)cMSG_PerCentUnit,
					               FALSE,
					               TRUE);

	MoFiO2.InitDbAccess        (COMPUTED_FIO2,
										COMPUTE);

	MoFiO2.SetInvertVideo			(TRUE);

   MoFiO2.SetMaxDisplayValue  (999);

   /*%C Graph SpO2 */
   MoSpO2.SetParent				(this);
	MoSpO2.Init						(NO,
                              196,
										161,
										(UBYTE**)cMSG_SpO2,
										10,
										TRUE,
										(UBYTE**)cMSG_PerCentUnit,
					               FALSE,
					               TRUE);

	MoSpO2.InitDbAccess        (MEASURE_SPO2_U16,
										COMPUTE);

	MoSpO2.SetInvertVideo      (TRUE);

   MoSpO2.SetMaxDisplayValue  (9999);

	/*%C Graph Pulse */
	MoPulse.SetParent				(this);

	MoPulse.Init					(HEART_INVERSE_VIDEO,
                              108,
										267,
										(UBYTE**)cMSG_Pulse,
										10, 
										FALSE, 
										(UBYTE**)cMSG_FrequencyUnit,
					               FALSE, 
					               TRUE);

	MoPulse.InitDbAccess			(COMPUTED_PULSE_U16,
										COMPUTE);

	MoPulse.SetInvertVideo	   (TRUE);

   MoPulse.SetMaxDisplayValue  (9999);

	/*%C Graph Fuite */
	MoFuite.SetParent				(this);

	MoFuite.Init				   (NO,
                              108,
										267,
										(UBYTE**)cMSG_FuiteMon,
										10,
										FALSE,
										(UBYTE**)cMSG_FlowUnit,
					               FALSE,
					               TRUE);

	MoFuite.InitDbAccess			(COMPUTED_LEAK_HMI_U16,
										COMPUTE);

	MoFuite.SetInvertVideo	   (TRUE);
	MoFuite.SetMaxDisplayValue  (200);

	/*%C Graph I/E */
   MoTVIE.SetParent			   (this);

	MoTVIE.Init						(NO,
                              196,
										267,
										(UBYTE**)cMSG_IERation,
										10,
										TRUE,
										10,
										TRUE,
										(UBYTE**)cMSG_Colon,
					               FALSE,
					               TRUE);

	MoTVIE.InitDbAccess			(MEASURE_IE_NUMERATOR_U16,
										COMPUTE);

	MoTVIE.InitDbAccess2			(MEASURE_IE_DENOMINATOR_U16,
                              COMPUTE);

	MoTVIE.SetInvertVideo		(TRUE);

   MoTVIE.SetMaxDisplayValue  (99);
    MoTVIE.SetMaxDisplayValue2 (1990);

    MoTVIE.SetCenteredDisplay(FALSE);

	/*%C Graph I/T */
   MoIT.SetParent				   (this);

	MoIT.Init						(NO,
                              152,
										267,
										(UBYTE**)cMSG_ITRation,
										10,
										FALSE,
										(UBYTE**)cMSG_PerCentUnit,
					               FALSE,
					               TRUE);

	MoIT.InitDbAccess			   (MEASURE_IT_U16,
										COMPUTE);

	MoIT.SetInvertVideo		   (TRUE);

	MoIT.SetTrigger            (TRUE);

   MoIT.SetMaxDisplayValue    (100);

	/*%C Graph VMI */
   MoVmi.SetParent				(this);
	MoVmi.Init					   (NO,
                              196,
										2,
										(UBYTE**)cMSG_Vmi,
										10,
										TRUE,
										(UBYTE**)cMSG_VolumeLiterUnit,
										FALSE,
										TRUE);

	MoVmi.InitDbAccess		   (COMPUTED_VMI_U16,
										COMPUTE);

	MoVmi.SetInvertVideo		   (TRUE);

   MoVmi.SetMaxDisplayValue   (999);


	/*%C Graph Vte */
   MoVte.SetParent				(this);

	MoVte.Init						(NO,
                              152,
										267,
										(UBYTE**)cMSG_Vte,
										10,
										FALSE,
										(UBYTE**)cMSG_VolumeUnit,
					               FALSE,
					               TRUE);

	MoVte.InitDbAccess			(COMPUTED_VTE_U16,
										COMPUTE);

	MoVte.SetInvertVideo		   (TRUE);

   MoVte.SetMaxDisplayValue    (9999);


	/*%C Graph VTI */
	MoVti.SetParent				(this);

	MoVti.Init						(NO,
                              108,
										267,
										(UBYTE**)cMSG_Vti,
										10, 
										FALSE, 
										(UBYTE**)cMSG_VolumeUnit,
					               FALSE, 
					               TRUE);

	MoVti.InitDbAccess			(COMPUTED_VTI_U16,
										COMPUTE);

	MoVti.SetInvertVideo		   (TRUE);

   MoVti.SetMaxDisplayValue   (9999);

	/*%C Graph Pe */
	MoPe.SetParent				   (this);

	MoPe.Init						(NO,
                              64,
										267,
										(UBYTE**)cMSG_ExhalationPressureMon,
										10,
										FALSE,
					               (UBYTE**)cMSG_PressureUnit,
					               FALSE,
					               TRUE);

	MoPe.InitDbAccess			   (COMPUTED_PEEP_U16,
										COMPUTE);

	MoPe.SetInvertVideo			(TRUE);

	MoPe.SetDivisionFactorOfValue	(10);

   MoPe.SetMaxDisplayValue    (999);

	/*%C Graph PIP */
	MoPip.SetParent				   (this);

	MoPip.Init						(NO,
                              20,
										267,
										(UBYTE**)cMSG_InsuflationPressurePeakMon,
										10,
										FALSE,
					               (UBYTE**)cMSG_PressureUnit,
					               FALSE,
					               TRUE);

	MoPip.InitDbAccess			(COMPUTED_LPF_PIP_U16,
										COMPUTE);

	MoPip.SetInvertVideo			(TRUE);

	MoPip.SetDivisionFactorOfValue	(10);

   MoPip.SetMaxDisplayValue    (999);

	/*%C Graph Ti */
   MoTi.SetParent             (this);

  	MoTi.Init						(NO,
                              20,
										267,
										(UBYTE**)cMSG_TiMon,
										10,
										TRUE,
					               (UBYTE**)cMSG_SecondUnit,
					               FALSE,
					               TRUE);


   MoTi.InitDbAccess          (MEASURE_TI_U16, COMPUTE);

   MoTi.SetInvertVideo        (TRUE);

   MoTi.SetMaxDisplayValue    (99);

	/*%C Graph Te */
   MoTe.SetParent             (this);

  	MoTe.Init						(NO,
                              20,
										267,
										(UBYTE**)cMSG_TeMon,
										10,
										TRUE,
					               (UBYTE**)cMSG_SecondUnit,
					               FALSE,
					               TRUE);


   MoTe.InitDbAccess          (MEASURE_TE_U16, COMPUTE);

   MoTe.SetInvertVideo        (TRUE);

   MoTe.SetMaxDisplayValue    (599);

   /*%C Initialisation et contrôle de la table de configuration de l'affichage
   des Monitoring Objects */
   InitInfoGraphTable();

   /*%C Table de refresh */
	/*% CAlway */
   RefreshTable[0] 	= &this->GSmallFlow;
   RefreshTable[1] 	= &this->GSmallPressure;
   RefreshTable[2] 	= &this->GSmallFlowV;
   RefreshTable[3] 	= &this->GSmallPressureV;
	RefreshTable[4] 	= NULL;

	/*%C Insp*/
	RefreshTable[5]	= &this->MoRate;
 	RefreshTable[6]   = &this->MoIT;
	RefreshTable[7] 	= &this->MoTVIE;
   RefreshTable[8] 	= &this->MoVte;
   RefreshTable[9] 	= &this->MoPe;
   RefreshTable[10] 	= &this->MoFuite;
   RefreshTable[11] 	= &this->MoTe;
   RefreshTable[12] 	= &this->MoTi;
	RefreshTable[13] 	= NULL;

	/*%C Exp */
	RefreshTable[14] = &this->MoFiO2;
	RefreshTable[15] = &this->MoSpO2;
	RefreshTable[16] 	= &this->MoVti;
	RefreshTable[17] 	= &this->MoPip;
	RefreshTable[18] 	= &this->MoPulse;
	RefreshTable[19] 	= &this->MoVmi;
	RefreshTable[20] 	= NULL;

	/*%C XAlway */
	RefreshTable[21] = &this->BOBat;
	RefreshTable[22] = NULL;

   FirstInitOk = TRUE;

}
/************************************************************************/
/* Description   : Initilalise la table de configuration des objets de  */
/*                 Monitoring permettant de gérer l'ordre d'affichage   */
/*                 et la visibilité pour chaque mode de ventilation     */
/* Parametres en entree : Néant                                         */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameGraph::InitInfoGraphTable(void)
{
   UWORD16 i,j;

   /* initialisation du tableau en ram avec le tableau de constantes */
    for (i=0; i<OBJECT_GRAPH_OBJECT_MAX+1; i++)
   {
        for (j=0; j<cGRAPH_MAX_MODE; j++)
      {
         InfoGraph[i].InfoByMode[j].Visible = cInfoGraph[i].InfoByMode[j].Visible;
         InfoGraph[i].InfoByMode[j].Order = cInfoGraph[i].InfoByMode[j].Order;
      }
   }

   InfoGraph[OBJECT_GRAPH_MOFIO2].pObject = &MoFiO2;
   InfoGraph[OBJECT_GRAPH_MOSPO2].pObject = &MoSpO2;
   InfoGraph[OBJECT_GRAPH_MOPULSE].pObject = &MoPulse;
   InfoGraph[OBJECT_GRAPH_MOIE].pObject = &MoTVIE;
   InfoGraph[OBJECT_GRAPH_MOIT].pObject = &MoIT;
   InfoGraph[OBJECT_GRAPH_MOFR].pObject = &MoRate;
   InfoGraph[OBJECT_GRAPH_MOVM].pObject = &MoVmi;
   InfoGraph[OBJECT_GRAPH_MOVTE].pObject = &MoVte;
   InfoGraph[OBJECT_GRAPH_MOVTI].pObject = &MoVti;
   InfoGraph[OBJECT_GRAPH_MOPE].pObject = &MoPe;
   InfoGraph[OBJECT_GRAPH_MOPI].pObject = &MoPip;
   InfoGraph[OBJECT_GRAPH_MOFUITE].pObject = &MoFuite;
   InfoGraph[OBJECT_GRAPH_MOTE].pObject = &MoTe;
   InfoGraph[OBJECT_GRAPH_MOTI].pObject = &MoTi;
   InfoGraph[OBJECT_GRAPH_OBJECT_MAX].pObject = NULL;

   SetInfoTable(  InfoGraph,
                  OBJECT_GRAPH_OBJECT_MAX,
                  0,
                  0);


    if (!CheckInfoTable())
      Tools::Panic(PANIC_MODULE_GRAPH);

   RebuildFrameTree(Mode);
}
/************************************************************************/
/*%C Description   : Reconstruit l'ordre d'affichage pur un mode donné  */
/*%C Parametres en entree : 		                                       */
/*		- Mode : mode pour lequel l'arbre doit être reconstruit           */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameGraph::RebuildFrameTree(e_MODE_TYPES Mode)
{
   UWORD16 Cnt, Order;
   e_BOOL IsVisible;
   UWORD16 ObjectTotalCount = 0;
   UWORD16 ObjectLineCount = 0;
   UWORD16 _Line, _Col;

   tInfo* ptrInfo = InfoGraph;
   _Col = 0;
   _Line = 0; 

   /*%C Premier parcours pour savoir combien de MO sont visibles dans ce Mode */
   ptrInfo = GetPtrFromOrder(0,Mode);
   do
   {
      Order = GetOrderFromPtr(ptrInfo, Mode);

      /*%C On passe au noeud suivant dans l'ordre*/
      ptrInfo = GetPtrFromOrder(++Order,Mode);
      ObjectTotalCount++;

   } while (ptrInfo != NULL);

   /*%C Calcul du nombre d'objets qui peuvent être contenus dans la ligne du bas */
   ObjectLineCount = (320 - RIGHT_MARGIN_WIDTH - LEFT_MARGIN_WIDTH) / (FRAME_WIDTH);

   /*%C reconstruction effective de l'arbre d'affichage */
   Cnt = 0;
   ptrInfo = GetPtrFromOrder(0,Mode);
   do
   {
      Order = GetOrderFromPtr(ptrInfo, Mode);

      /*%C On rend l'objet invisible pour éviter que SetLine() ne fasse appel
        à Show() */
      IsVisible = ptrInfo->pObject->IsVisible();
      ptrInfo->pObject->SetVisible(FALSE);

        if (Cnt < ObjectLineCount)
      {
         /*%C les objets de la ligne du bas */
         ptrInfo->pObject->SetLine(cGRAPH_FIRST_LINE);
         _Col = cGRAPH_FIRST_COL + Cnt*(FRAME_WIDTH+1);
         ptrInfo->pObject->SetCol(_Col);
      }
      else
      {
         /*%C les objets de la colonne de droite */
         ptrInfo->pObject->SetCol(_Col);
         _Line = cGRAPH_FIRST_LINE - (Cnt - ObjectLineCount + 1)*(FRAME_HEIGHT+1);
         ptrInfo->pObject->SetLine(_Line);
      }
      Cnt++;

      /*%C On restaure la visibilité pour cet objet */
      ptrInfo->pObject->SetVisible(IsVisible);

      /*%C On passe au noeud suivant dans l'ordre*/
      ptrInfo = GetPtrFromOrder(++Order,Mode);

   } while (ptrInfo != NULL);
}
/************************************************************************/
/* Description   : Cache les objets qui sont visibles dans ce mode      */
/* Parametres en entree :                                               */
/*		- Mode : mode pour lequel on doit faire l'opération               */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameGraph::ObjectsHide(e_MODE_TYPES _Mode)
{
   UWORD16 i;

    if (GetImpactDisplay() && GetEndOfInit())
   {
        for (i=0;i<OBJECT_GRAPH_OBJECT_MAX;i++)
      {
            if ((InfoGraph[i].pObject != NULL)&&
            (InfoGraph[i].InfoByMode[_Mode].Visible))
            InfoGraph[i].pObject->Hide();
      }
   }
}
/************************************************************************/
/* Description   : Cache l'objet s'il est visible dans ce mode          */
/* Parametres en entree :                                               */
/*		- _Mode : mode pour lequel on doit faire l'opération              */
/*		- _ObjectId : Objet à cacher                                      */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameGraph::ObjectsHide(e_MODE_TYPES _Mode, e_OBJECT _ObjectId)
{
    if (GetImpactDisplay() && GetEndOfInit())
   {
        if (_ObjectId<OBJECT_GRAPH_OBJECT_MAX)
      {
            if ((InfoGraph[_ObjectId].pObject != NULL)&&
         (InfoGraph[_ObjectId].InfoByMode[_Mode].Visible))
         InfoGraph[_ObjectId].pObject->Hide();
      }
   }
}
/************************************************************************/
/* Description   : Démarre le monitoring des objets                     */
/* Parametres en entree :                                               */
/*    _DisplayFlag : impacte ou non l'affichage                         */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameGraph::ObjectsStartMonitoringModeImpactDisplay(e_BOOL _DisplayFlag)
{
   UWORD16 i;

    for (i=0;i<OBJECT_GRAPH_OBJECT_MAX;i++)
   {
        if (InfoGraph[i].pObject != NULL)
      {
         /*%C On ne lance le Monitoring de FiO2 que si le capteur est présent */
            if (i == OBJECT_GRAPH_MOFIO2)
         {
                if (FiO2Enabled)
               InfoGraph[i].pObject->StartMonitoringModeImpactDisplay(_DisplayFlag);
         }
         /*%C On ne lance le Monitoring de SpO2 que si le capteur est présent */
            else if (i == OBJECT_GRAPH_MOSPO2)
         {
                if (SpO2Enabled)
               InfoGraph[i].pObject->StartMonitoringModeImpactDisplay(_DisplayFlag);
         }
            else if (i == OBJECT_GRAPH_MOFUITE)
		 {
                if (ValveDetected)
			   InfoGraph[i].pObject->StopMonitoringModeImpactDisplay(_DisplayFlag);
			else
			   InfoGraph[i].pObject->StartMonitoringModeImpactDisplay(_DisplayFlag);
		 }
            else if (i == OBJECT_GRAPH_MOVTE)
		 {
                if (this->ExhalFlowUsed)
				InfoGraph[i].pObject->StartMonitoringModeImpactDisplay(_DisplayFlag);
         }
         else
            InfoGraph[i].pObject->StartMonitoringModeImpactDisplay(_DisplayFlag);
      }
   }
}
/************************************************************************/
/* Description   : Freeze le monitoring des objets                      */
/* Parametres en entree : Néant                                         */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameGraph::ObjectsFreezeMonitoringMode(void)
{
   UWORD16 i;
   (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    for (i=0;i<OBJECT_GRAPH_OBJECT_MAX;i++)
   {
        if (InfoGraph[i].pObject != NULL)
         InfoGraph[i].pObject->FreezeMonitoringMode();
   }
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
void FrameGraph::SetMode(e_MODE_TYPES _ModeTmp)
{
    if (IsVisible())
   {
      ObjectsHide(Mode);
   }

   SetPreviousMode(Mode);
   Mode = _ModeTmp;
   RebuildFrameTree(Mode);

    if (IsVisible())
   {
      ObjectsShow(Mode);
	}
   SetModeChange(TRUE);
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
void FrameGraph::SetIESelected(e_BOOL _IESelected)
{
    if (IESelected != _IESelected)
   {
      /*%C Changement de configuration I/T -> I/E */
      SwitchDisplayConfigForAllModes(OBJECT_GRAPH_MOIE, OBJECT_GRAPH_MOIT);

      /*%C Reconstruction de l'arbre d'affichage des Monitoring Objects */
      RebuildFrameTree(Mode);

      IESelected = _IESelected;
   }
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
void FrameGraph::Show()
{
	UWORD16 WobDisplayMode;
   VFrame::Show();

	InterfaceCppC::EraseZone	(0,
										0,
										240,
										320,
										0,
										GetPage());

   InhibAlarm.Show();
   CancelAlarm.Show();
   ShowInhibApneaAlarm();

	GTMode.Show();
	IsBatVisible();
   IsInibAlarmVisible();
   IsCancelAlarmVisible();
   IsInhibApneaAlarmVisible();   

	DataBaseAccess::ReadValue	(&WobDisplayMode, 
										CURVE_DISPLAY_TYPE_MODE_U16, 
										CONFIG);

    if (WobDisplayMode)
	{
		GSmallPressure.Hide();
		GSmallFlow.Hide();
      CDPressureV.SetScale		(GSmallPressureV.GetScaleX(),
                           	GSmallPressureV.GetScaleY());

		GSmallPressureV.Show();
		CDFlowV.SetScale			(GSmallFlowV.GetScaleX(),
										GSmallFlowV.GetScaleY());

		GSmallFlowV.Show();
   }
   else
   {
	   GSmallPressureV.Hide();
		GSmallFlowV.Hide();

		CDPressure.SetScale		(GSmallPressure.GetScaleX(),
										GSmallPressure.GetScaleY());

		GSmallPressure.Show();
		CDFlow.SetScale			(GSmallFlow.GetScaleX(),
										GSmallFlow.GetScaleY());

		GSmallFlow.Show();
   }

	SetMode(Mode);
   SetModeChange(FALSE);

   /*%C Si le graph est gelé, on le réactive */
    if (Freezed)
	{
      FreezeMonitoring(FALSE, TRUE);
	}

	/*%C Si le trigger est actif */
    if (TriggerOn)
	{
    	ShowTrigger();
	}
   else
	{
	   HideTrigger();
	}
   /*%C Pour afficher la présence ou non de la valve */
   SetValve(ValveDetected, TRUE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Effacement de l'Objet																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameGraph::Hide()
{
	VFrame::Hide();
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
void FrameGraph::RefreshLanguage()
{
	GTMode.RefreshLanguage();
	GSmallFlowV.RefreshLanguage();
 	GSmallPressureV.RefreshLanguage();
	GSmallFlow.RefreshLanguage();
 	GSmallPressure.RefreshLanguage();

   BOBat.RefreshLanguage();

   ObjectsRefreshLanguage(Mode);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameGraph::StopMonitoringMode()
{
    if (!Freezed)
   {
      BOBat.StopMonitoringMode();

      ObjectsStopMonitoringMode();
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
/*%I	  	DisplayFlag = impacte ou non l'affichage                             */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameGraph::StartMonitoringModeImpactDisp( e_BOOL IsFio2Sensor,
                                                e_BOOL IsSpO2Sensor,
                                                e_BOOL _DisplayFlag)
{
    if (!Freezed)
   {
      BOBat.StartMonitoringMode();

        if (IsFio2Sensor)
         FiO2Enabled = TRUE;

        if (IsSpO2Sensor)
         SpO2Enabled = TRUE;

      ObjectsStartMonitoringModeImpactDisplay(_DisplayFlag);
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameGraph::StartMonitoringMode(void)
{
   this->StartMonitoringModeImpactDisp(FALSE, FALSE, TRUE);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affiche le trigger																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameGraph::ShowTrigger()
{
	TriggerOn = TRUE;

    if (!Freezed &&
		IsVisible())
   {
        if (IESelected)
         MoTVIE.ShowTrigger();
      else
         MoIT.ShowTrigger();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Efface le trigger																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameGraph::HideTrigger()
{
	TriggerOn = FALSE;

    if (!Freezed && 
		IsVisible())
   {
        if (IESelected)
         MoTVIE.HideTrigger();
      else
         MoIT.HideTrigger();
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gel de la courbe      																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameGraph::FreezeMonitoring(e_BOOL Freeze, e_BOOL _DisplayFlag)
{
	UWORD16 CurrentMode;

   static e_BOOL RefreshScreen = FALSE;

   /*%C Store flag */
   Freezed = Freeze;

   /*%C Si on freeze l'affichage */
    if (Freeze)
   {
      RefreshScreen = FALSE;

      ObjectsFreezeMonitoringMode();

      /*%C Affichage du symbole Pause */
	   SFPause.Show();

   }
   /*%C Si on relance l'affichage */
    else if (RefreshScreen == FALSE)
	{
      RefreshScreen = TRUE;
    	DataBaseAccess::ReadValue(&CurrentMode,ADJUST_MODE_U16,CONFIG);
    	FrameGraph::SetMode((e_MODE_TYPES)CurrentMode);
   	GTMode.Show();

      /*%C Effacement du symbole Pause*/
		SFPause.Hide();

      ObjectsStartMonitoringModeImpactDisplay(_DisplayFlag);

      /*%C Si le trigger est actif */
        if (TriggerOn)
		{
        	ShowTrigger();
		}
      else
		{
        	HideTrigger();
		}
	}

   /*%C Passe la commande de Freeze aux courbes */
	GSmallFlow.FreezeGraph(Freeze);
   GSmallPressure.FreezeGraph(Freeze);
   GSmallFlowV.FreezeGraph(Freeze);
   GSmallPressureV.FreezeGraph(Freeze);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Rafraichit l'affichage sur changement de mode										*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameGraph::RefreshMode()
{
	UWORD16 CurrentMode, Style;

   IsBatVisible();
   IsInibAlarmVisible();
   IsCancelAlarmVisible();
   IsInhibApneaAlarmVisible();   

   /*%C Reset des courbes */
    if (!Freezed)
   {
	   DataBaseAccess::ReadValue(&CurrentMode,ADJUST_MODE_U16,CONFIG);

      /*%C Lecture du Style (Boucle / Pression-Débit) dans la DataBase */
      DataBaseAccess::ReadValue(&Style, CURVE_DISPLAY_TYPE_MODE_U16,CONFIG);
	   GTMode.Show();

      /*%C Si on est en courbe WOB on rafraichit totalement le graph */
      if (Style == 1)
      {
         GSmallFlowV.Raz();
         GSmallPressureV.Raz();
      }
      else
      {
         GSmallFlow.Raz();
         GSmallPressure.Raz();
      }
   }
    if (GetModeChange())
   {
      SetModeChange(FALSE);
        if (GetPreviousMode() != Mode)
      {
            if (IsVisible())
         {
            ObjectsHide(GetPreviousMode());
            ObjectsShow(Mode);
         }
      }
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
void FrameGraph::IsBatVisible()
{
	UWORD16 Value;

	DataBaseAccess::ReadValue(&Value, DISPLAY_BATTERY_U16, CONTROL);

	if (this->IsVisible())
   {
        if (Value)
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
/*%C Affichage du symbole Inib Alarm														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	               */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameGraph::IsInibAlarmVisible()
{
	UWORD16 Value;

	DataBaseAccess::ReadValue(&Value, INHIBITED_BUZZER_U16, CONTROL);

	if (this->IsVisible())
   {
        if (Value)
      {
		   InhibAlarm.Show();
      }
   	else
      {
		   InhibAlarm.Hide();
      }
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage du symbole Cancel Alarm														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	               */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameGraph::IsCancelAlarmVisible()
{
	UWORD16 Value;

	DataBaseAccess::ReadValue(&Value, CANCELLED_ALARM_U16, CONTROL);

	if (this->IsVisible())
   {
        if (Value)
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
/*%C Affichage du symbole Inhib Apnea Alarm											   */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																	               */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameGraph::IsInhibApneaAlarmVisible()
{
	UWORD16 Value;

	DataBaseAccess::ReadValue(&Value, APNEA_ALARM_ACTIVATION, CONFIG);

	if (this->IsVisible())
   {
        if (!Value)
      {
		   ShowInhibApneaAlarm();
	  }
	else
	  {
		   HideInhibApneaAlarm();
      }
   }
}
/************************************************************************/
/* Description          : Determine la presence ou l'absence de la      */
/*                         valve d'expiration			                  */
/* Parametres en entree : aucun	                                       */
/*		 _ValveDetected : presence de la valve						            */
/*     _DisplayFlag : TRUE si l'affichage doit etre impacté             */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameGraph::SetValve(e_BOOL _ValveDetected, e_BOOL _DisplayFlag)
{
#ifndef HMI_CONFIG_S2
   UWORD16 i;
#endif      
   e_BOOL _IsVisible = FALSE;

    if (!_DisplayFlag)
   {
      /* sauvegarde de la visibilité */
      _IsVisible = SFValve.IsVisible();
      SFValve.SetVisible(FALSE);
   }

    if (_ValveDetected)
   {
      SFValve.SetBarredSymbol(FALSE);
   }
   else
   {
      SFValve.SetBarredSymbol(TRUE);
   }

   SFValve.Show();

    if (ValveDetected != _ValveDetected)
   {
      ValveDetected = _ValveDetected;

#ifndef HMI_CONFIG_S2
        if (_DisplayFlag)
      {
         ObjectsHide(Mode, OBJECT_GRAPH_MOVTE);
         ObjectsHide(Mode, OBJECT_GRAPH_MOFUITE);
      }

      /*%C Pas de fonctionnement avec fuite pour les modes volume */
        for (i=0; i<cGRAPH_MAX_MODE; i++)
      {
         if ((i != VOL) && (i!= VSIMV))
         {
            /*%C Changement de configuration Fuite -> Vte */
            SwitchDisplayConfigForOneMode(OBJECT_GRAPH_MOVTE, OBJECT_GRAPH_MOFUITE, (e_MODE_TYPES)i);

            /*%C Reconstruction de l'arbre d'affichage de la ventilation */
            RebuildFrameTree((e_MODE_TYPES)i);
         }
      }
        if (_DisplayFlag)
      {
         ObjectsShow(Mode, OBJECT_GRAPH_MOVTE);
         ObjectsShow(Mode, OBJECT_GRAPH_MOFUITE);
      }

        if (FirstInitOk)
      {
         /* Mise à jour de l'affichage des graphes */
         GraphReInit( (e_BOOL)(!IsBlocExpiDetected() || !_ValveDetected),
          _DisplayFlag);
      }
#endif      
   }

    if (!_DisplayFlag)
   {
      /* restauration de la visibilité */
      SFValve.SetVisible(_IsVisible);
   }
}
/************************************************************************/
/* Description          : Active le monitoring de Fio2					   */
/* Parametres en entree :                                               */
/*                _Flag : TRUE si capteur                               */
/*                _DisplayFlag : TRUE si l'affichage doit etre impacté  */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameGraph::Fio2MonitorEnabled(e_BOOL _Flag, e_BOOL _DisplayFlag)
{
   FiO2Enabled = _Flag;

    if (!Freezed)
   {
        if (_Flag)
	  	   MoFiO2.StartMonitoringMode();
      else
	  	   MoFiO2.StopMonitoringMode(_DisplayFlag);
	}
}
/************************************************************************/
/* Description          : Active le monitoring de Spo2					   */
/* Parametres en entree :                                               */
/*                _Flag : TRUE si capteur                               */
/*                _DisplayFlag : TRUE si l'affichage doit etre impacté  */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameGraph::Spo2MonitorEnabled(e_BOOL _Flag, e_BOOL _DisplayFlag)
{
   SpO2Enabled = _Flag;

    if (!Freezed)
   {
        if (_Flag)
	  	   MoSpO2.StartMonitoringMode();
      else
	  	   MoSpO2.StopMonitoringMode(_DisplayFlag);
    }
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
void FrameGraph::SetPressureUnit(UBYTE** _PressureUnit)
{
   e_BOOL _VisibleBackup;

   _VisibleBackup = MoPe.IsVisible();
   MoPe.SetVisible(FALSE);
   MoPe.SetNameUnit(_PressureUnit);
   MoPe.SetVisible(_VisibleBackup);

   _VisibleBackup = MoPip.IsVisible();
   MoPip.SetVisible(FALSE);
   MoPip.SetNameUnit(_PressureUnit);
   MoPip.SetVisible(_VisibleBackup);

   _VisibleBackup = GSmallPressure.IsVisible();
   GSmallPressure.SetVisible(FALSE);
   GSmallPressure.SetTUnit2(_PressureUnit);
   GSmallPressure.SetVisible(_VisibleBackup);

   _VisibleBackup = GSmallPressureV.IsVisible();
   GSmallPressureV.SetVisible(FALSE);
   GSmallPressureV.SetTUnit2(_PressureUnit);
   GSmallPressureV.SetVisible(_VisibleBackup);
}
/************************************************************************/
/* Description          : Positionne flag pour deuxième mode d'affichage*/
/*                        des noms de modes                             */
/* Parametres en entree : aucun	                                       */
/*		- _NameMode2Display : Flag                                        */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameGraph::SetNameMode2Display(e_BOOL _NameMode2Display)
{
     GTMode.SetNameMode2Display(_NameMode2Display);
}
/************************************************************************/
/* Description          : Réinitialise le graph passé en paramètre      */
/* Parametres en entree : aucun	                                       */
/*       _PositiveCurves :  = 1 <=> afficher uniquement partie positive */
/*       _DisplayFlag : TRUE si l'affichage doit etre impacté           */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameGraph::GraphReInit(e_BOOL _PositiveCurves, e_BOOL _DisplayFlag)
{
   Graph*  _GraphPtr;
   Graph* _GraphTable[4];
   UWORD16 i, cpt;

   /* Init de la table des graphes à réinitialiser */
   i = 0;
   _GraphTable[i++] = &GSmallFlow;
   _GraphTable[i++] = &GSmallPressure;
   _GraphTable[i] = NULL;

   UWORD16 _Line, _Col, _Height, _Width;

   SWORD16 _MinX, _MaxX;
   UWORD16 _ZeroPosX, _MajorTickSpacingX;

   SWORD16 _MinY, _MaxY;
   UWORD16 _ZeroPosY, _MajorTickSpacingY;

   UWORD16 _Font;
   UBYTE **_Unit1;
   UBYTE **_Unit2;
   UBYTE **_OutOfLimit;
   UWORD16 _IdMaxX, _IdMaxY;
   e_TYPE_OF_DB_TARGET _DbMaxX, _DbMaxY;

   GraphControl * _GraphControlPtr;
   UWORD16 _GraphControlRefreshTime;

   tCurvInfo _CurveInfoTable[CURVE_INFO_MAX]={
		{NULL, NULL, NULL, 0, (e_TYPE_OF_DB_TARGET)0, (e_BOOL)0},
		{NULL, NULL, NULL, 0, (e_TYPE_OF_DB_TARGET)0, (e_BOOL)0},
		{NULL, NULL, NULL, 0, (e_TYPE_OF_DB_TARGET)0, (e_BOOL)0},
		{NULL, NULL, NULL, 0, (e_TYPE_OF_DB_TARGET)0, (e_BOOL)0},
		{NULL, NULL, NULL, 0, (e_TYPE_OF_DB_TARGET)0, (e_BOOL)0}};

   CurveData** _CurveTable;
   UWORD16 _CurveNumber;

   e_BOOL _Symetric;

   cpt = 0;
    while (_GraphTable[cpt] !=  NULL)
   {
      /* Init de varaibles de parcours */
      _GraphPtr = _GraphTable[cpt];

        for (i=0; i<CURVE_INFO_MAX; i++)
      {
         _CurveInfoTable[i].Curv = NULL;
     	}

      /*%C Sauvegarde des valeurs précédentes... */

      /* ... pour le graph */
      _Line             =  _GraphPtr->GetLine();
      _Col              =  _GraphPtr->GetCol();
      _Height           =  _GraphPtr->GetHeight();
      _Width            =  _GraphPtr->GetWidth();
      _MinX             =  _GraphPtr->GetScaleX()->GetMin();
      _MaxX             =  _GraphPtr->GetScaleX()->GetMax();
      _ZeroPosX         =  _GraphPtr->GetScaleX()->GetZeroPos();
      _MajorTickSpacingX = _GraphPtr->GetScaleX()->GetMajorTickSpacing();
      _MinY              = _GraphPtr->GetScaleY()->GetMin();
	   _MaxY					 = _GraphPtr->GetScaleY()->GetMax();
      _ZeroPosY          = _GraphPtr->GetScaleY()->GetZeroPos();
      _MajorTickSpacingY = _GraphPtr->GetScaleY()->GetMajorTickSpacing();
      _Font              =	_GraphPtr->GetScaleY()->GetFont();
      _Unit1             = _GraphPtr->GetTUnit1Ptr();
      _Unit2             = _GraphPtr->GetTUnit2Ptr();
      _OutOfLimit        = _GraphPtr->GetTOutOfLimitPtr();
      _IdMaxX            = _GraphPtr->GetScaleX()->GetIdMax();
      _DbMaxX            = _GraphPtr->GetScaleX()->GetDbMax();
      _IdMaxY            = _GraphPtr->GetScaleY()->GetIdMax();
      _DbMaxY            = _GraphPtr->GetScaleY()->GetDbMax();
      _Symetric          = _GraphPtr->GetScaleY()->GetSymetric();

      /* ... pour le graph control */
      _GraphControlPtr = _GraphPtr->GetGControl();
      _GraphControlRefreshTime = (_GraphControlPtr != NULL)? _GraphControlPtr->GetRefreshTime():0;

      /* ... pour les courbes */
      _CurveTable = _GraphPtr->GetCurveTable();
      _CurveNumber = _GraphPtr->GetCurveNumber();

      /* remplissage de _CurveInfoTable avec les informations de tout les courbes du graphe */
        if (_CurveTable)
      {
            for (i=0; i<_CurveNumber; i++)
         {
#ifdef _BORLAND
            /* Controle du nombre courbes par graphe
               Non effectué sur cible (#ifdef _BORLAND) car la seule routine appelant
               la fonction Panic est celle qui controle les tables de configuration de
               l'affichage appelée uniquement à l'init */
                if (i >= CURVE_INFO_MAX)
               Tools::Panic(PANIC_MODULE_FRAME_GRAPH);
#endif
            _CurveInfoTable[i].Curv = _CurveTable[i];
            _CurveInfoTable[i].ScaleX = _CurveTable[i]->GetScaleX();
            _CurveInfoTable[i].ScaleY = _CurveTable[i]->GetScaleY();
            _CurveInfoTable[i].IdParamY = _CurveTable[i]->GetIdParamY();
            _CurveInfoTable[i].IdDbY = _CurveTable[i]->GetDbTargetY();
            _CurveInfoTable[i].Dotted = _CurveTable[i]->GetPen()->IsDotted();
         }
      }

        if (_GraphPtr == &GSmallFlow)
      {
         /* RéInit des objets */
            if (!_PositiveCurves)
         {
            _ZeroPosY = 30;
            _Symetric = TRUE;
         }
         else
         {
            _ZeroPosY = 0;
            _Symetric = FALSE;
         }
      }

      /* Réinit de l'objet dans ses valeurs après constructeur */
      e_BOOL _IsVisibleGraph = _GraphPtr->IsVisible();
      e_BOOL _IsVisibleScaleX = _GraphPtr->GetScaleX()->IsVisible();
      e_BOOL _IsVisibleScaleY = _GraphPtr->GetScaleY()->IsVisible();
      _GraphPtr->SetVisible(FALSE);
      _GraphPtr->GetScaleX()->SetVisible(FALSE);
      _GraphPtr->GetScaleY()->SetVisible(FALSE);
      _GraphPtr->Construct();
      _GraphControlPtr->Construct();
      i = 0;
        while ((_CurveInfoTable[i].Curv != NULL)&& (i<CURVE_INFO_MAX))
      {
         _CurveInfoTable[i].Curv->Construct();
         i++;
      }

      /* Initialisation du Graph Control */
      _GraphControlPtr->InitRefreshTime   (_GraphControlRefreshTime);

      /* Initialisation des courbes */
      i = 0;
        while ((_CurveInfoTable[i].Curv != NULL)&& (i<CURVE_INFO_MAX))
      {
         /* Init */
         _CurveInfoTable[i].Curv->Init(_CurveInfoTable[i].ScaleX, _CurveInfoTable[i].ScaleY);

         /* InitDbAccess */
         _CurveInfoTable[i].Curv->InitDbAccess(_CurveInfoTable[i].IdParamY, _CurveInfoTable[i].IdDbY);

         /* SetDotted */
         _CurveInfoTable[i].Curv->GetPen()->SetDotted(_CurveInfoTable[i].Dotted);

         i++;
      }

      _GraphPtr->SetParent		   (this);

  	   _GraphPtr->Init			   (  _Line,
                                    _Col,
		      					         _Height,
		   						         _Width,
                                    _MinX,
		   	 					         _MaxX,
				   				         _ZeroPosX,
					   			         _MajorTickSpacingX,
                 	   		         _MinY,
                 		   	         _MaxY,
                                    _ZeroPosY,
                                    _MajorTickSpacingY,
                 			            _Font,
                                    _Unit1,
                                    _Unit2,
                                    _OutOfLimit);

      _GraphPtr->SetGControl (_GraphControlPtr);

      /* Ajout des courbes */
      i = 0;
        while ((_CurveInfoTable[i].Curv != NULL) && (i<CURVE_INFO_MAX))
      {
         _GraphPtr->AddCurve	  (_CurveInfoTable[i].Curv);
         i++;
      }

      _GraphPtr->GetScaleX()->InitDbAccess(_IdMaxX, _DbMaxX);
      _GraphPtr->GetScaleY()->InitDbAccess(_IdMaxY, _DbMaxY);
      _GraphPtr->GetScaleY()->SetSymetric(_Symetric);

      /* On restaure la visibilité */
      _GraphPtr->SetVisible(_IsVisibleGraph);
      _GraphPtr->GetScaleX()->SetVisible(_IsVisibleScaleX);
      _GraphPtr->GetScaleY()->SetVisible(_IsVisibleScaleY);

      cpt++;
   } /* while(_GraphTable[cpt] !=  NULL) */

   /* Refresh de l'écran */
    if (_DisplayFlag)
   {
     GraphRefresh();
    }
}
/************************************************************************/
/* Description          : Rafraichi la partie graphe de la fenetre      */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameGraph::GraphRefresh()
{
   UWORD16 WobDisplayMode;

    /*	InterfaceCppC::EraseZone	(0,
										0,
										240,
										320,
										0,
										GetPage());*/

	DataBaseAccess::ReadValue	(&WobDisplayMode,
										CURVE_DISPLAY_TYPE_MODE_U16,
										CONFIG);

    if (WobDisplayMode)
	{
		GSmallPressure.Hide();
		GSmallFlow.Hide();
      CDPressureV.SetScale		(GSmallPressureV.GetScaleX(),
                           	GSmallPressureV.GetScaleY());

		GSmallPressureV.Show();
		CDFlowV.SetScale			(GSmallFlowV.GetScaleX(),
										GSmallFlowV.GetScaleY());

		GSmallFlowV.Show();
   }
   else
   {
	   GSmallPressureV.Hide();
		GSmallFlowV.Hide();

		CDPressure.SetScale		(GSmallPressure.GetScaleX(),
										GSmallPressure.GetScaleY());

		GSmallPressure.Show();
		CDFlow.SetScale			(GSmallFlow.GetScaleX(),
										GSmallFlow.GetScaleY());

		GSmallFlow.Show();
   }
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
void FrameGraph::SetExhalFlowUsed(e_BOOL _Flag, e_BOOL _ImpactDisplay)
{
	e_BOOL is_movte_visible = InfoGraph[OBJECT_GRAPH_MOVTE].pObject->IsVisible(); 

    this->ExhalFlowUsed = _Flag; 

    if (_ImpactDisplay)
        InfoGraph[OBJECT_GRAPH_MOVTE].pObject->SetVisible(TRUE);
    else
        InfoGraph[OBJECT_GRAPH_MOVTE].pObject->SetVisible(FALSE);  	

	if (InfoGraph[OBJECT_GRAPH_MOVTE].pObject->IsRefreshObject())
	{
		if (_Flag)
			InfoGraph[OBJECT_GRAPH_MOVTE].pObject->StartMonitoringMode();
		else
			InfoGraph[OBJECT_GRAPH_MOVTE].pObject->StopMonitoringMode();
	}
    if (_ImpactDisplay)
        InfoGraph[OBJECT_GRAPH_MOVTE].pObject->SetVisible(is_movte_visible);
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
void FrameGraph::ShowInhibApneaAlarm()
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
void FrameGraph::HideInhibApneaAlarm()
{
	/* Hiding the symbol */
	InhibApneaAlarm.Hide();

	/* Do not need to hide the cross since the previous call erase a zone*/
}
