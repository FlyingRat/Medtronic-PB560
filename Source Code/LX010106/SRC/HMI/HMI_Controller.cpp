/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Controller.cpp                                      			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Classe de gestion de l'application		 f									      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/


#include "HMI_Controller.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Config.hpp"
#include "HMI_GlobalEventNode.hpp"
#include "HMI_Tools.hpp"
#include "HMI_Message.hpp"
#include "HMI_DataBaseAccess.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "HMI_MonitoringObject.hpp"
#include "HMI_DisplayObject.hpp"
#include "DB_KeyboardEvent.h"
#include "DRV_VarEeprom.h"
#include "System_Datas.h"
#include "define.h"
#include "HMI_Controller_Data.hpp"

#ifdef _BORLAND
    #include "Proto_Config.hpp"
    #include "EventRecorder.hpp"
#endif

extern "C"
{
#include "stdfile.h"
#include "DB_Usb.h"
#include "DB_IhmAccessParaDataBase.h"
#include <intrins.h>
    void DB_ComputeBreathTimingRatios(void);
}


/* Local define */

#define LOCAL_BLOWER_STEP_FACTOR 5

/******************************************************************************/
/*                        VARIABLE DECLARATION		                	   		*/
/******************************************************************************/

/* !!!!!!!!!!!!!        This is for KEIL compiler :     !!!!!!!!!!!!!!!!!!!!!!*/
/* The array "Controller_ArrayNode" is cut in 2 other arrays("Controller_ArrayNode1" */
/* and "Controller_ArrayNode2", and they are defined in 2 separate files.            */
/* In fact, "Controller_ArrayNode" array was too big , upper  65536 bytes            */
/* which is the limit of KEIL compiler.                               */

//MenuControlNode Controller_ArrayNode1[NB_NODE/NB_NODE];

bool EraseFlag = false;
static bool FirstCall = true;

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
Controller::Controller()
    : FCircuitCheck(FrameCircuitCheck::GetInstance())
{
    EraseFlag = false;
    FirstCall = true;
    SetHighPressAlarmToBeRemoved(FALSE);

    IESelected = I_E;
    ValveDetected = TRUE; /* A garder cohérent avec les infos de cInfoNode[]*/
    TrigEPosSelected = FALSE;
    UsbProcessingNode = NULL;
    UsbCmdInProgress = FALSE;
    SetUsbLock(FALSE);
    SetImpactDisplay(FALSE);
    PreviousErrorCode = 0;
    OnWait = FALSE;

    this->SegmentNumber = 1;
    this->StartCalib = FALSE;
    this->StartVerif = FALSE;
    this->DifferMonitoringStart = FALSE;
    this->MonitoringMode = FALSE;
    this->ExhalFlowUsed = FALSE;
    this->VentButtonOn = FALSE;
    this->BuzzerVoltRefreshReq = FALSE;
    this->IsDoubleMessageTimerStarted = FALSE;

    SetLongUpKeyDetected(FALSE);
    SetLongDownKeyDetected(FALSE);
    StepLevel = eSTEP_LEVEL_LOW;

    LeakTestRunning = FALSE;
}

/******************************************************************************/
/*                           ACCESSEURS				                				*/
/******************************************************************************/
void Controller::SetCurrentFrame(UWORD16 _CurrentFrame)
{
    CurrentFrame = _CurrentFrame;
    ShowFrame(_CurrentFrame);
}
/*----------------------------------------------------------------------------*/
UWORD16 Controller::GetCurrentFrame()
{
    return CurrentFrame;
}
/*----------------------------------------------------------------------------*/
UWORD16 Controller::GetLanguage()
{
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
    return(DisplayObject::Language);
}
/*----------------------------------------------------------------------------*/
void Controller::SetLanguage(UWORD16 _Lang)
{
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */  
    DisplayObject::Language = _Lang;
    Tools::SetFontConfigForLang(_Lang);
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::GetEndOfInit()
{
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    return(DisplayObject::EndOfInit);
}
/*----------------------------------------------------------------------------*/
void Controller::SetEndOfInit(e_BOOL _EndOfInit)
{
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    DisplayObject::EndOfInit = _EndOfInit;
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::GetLongUpKeyDetected()
{
    return(LongUpKeyDetected);
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::GetLongDownKeyDetected()
{
    return(LongDownKeyDetected);
}
/*----------------------------------------------------------------------------*/
void Controller::SetLongUpKeyDetected(e_BOOL _LongUpDetected)
{
    LongUpKeyDetected = _LongUpDetected;
}
/*----------------------------------------------------------------------------*/
void Controller::SetLongDownKeyDetected(e_BOOL _LongDownDetected)
{
    LongDownKeyDetected = _LongDownDetected;
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::GetImpactDisplay()
{
    return(ImpactDisplay);
}
/*----------------------------------------------------------------------------*/
void Controller::SetImpactDisplay(e_BOOL _ImpactDisplay)
{
    ImpactDisplay = _ImpactDisplay;
}
/*----------------------------------------------------------------------------*/
void Controller::SetLState(LegendState _State)
{
    LState  = _State;
}
/*----------------------------------------------------------------------------*/
Controller::LegendState Controller::GetLState()
{
    return LState;
}
/*----------------------------------------------------------------------------*/
void Controller::InsertDoubleMessage()
{
    UWORD16 Val = ALARM_TRUE;

    DataBaseAccess::WriteValue(&Val,ALARM_DELAYED_MESSAGE_U16,ALARMS);
}
/*----------------------------------------------------------------------------*/
void Controller::RemoveDoubleMessage()
{
    UWORD16 Val = ALARM_FALSE;

    DataBaseAccess::WriteValue(&Val,ALARM_DELAYED_MESSAGE_U16,ALARMS);
}
/*----------------------------------------------------------------------------*/
void Controller::SetBrightness(UWORD16 _Value)
{
    /*%C ecriture en base */
    UWORD16 Val = _Value;

    DataBaseAccess::WriteValue(&Val,ADJUST_BRIGHTNESS_U16,CONFIG);

    InterfaceCppC::DisplayBrithness(_Value);

    LastBrightness = _Value;
}
/*----------------------------------------------------------------------------*/
UWORD16 Controller::GetBrightness()
{
    UWORD16 Val;
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    DataBaseAccess::ReadValue(&Val,ADJUST_BRIGHTNESS_U16,CONFIG);

    return Val;
}
/*----------------------------------------------------------------------------*/
void Controller::SetLockOn(e_BOOL _Flag)
{
    LockOn = _Flag;

    UWORD16 _Val = _Flag;
    UWORD16 _FrameId = GetCurrentFrame();

    DataBaseAccess::WriteValue(&_Val,ADJUST_KEYLOCK_U16,CONFIG);

    if ((_Flag) && (_FrameId != 0))
        DataBaseAccess::WriteValue(&_FrameId,IHM_LOCKED_FRAME_ID,CONFIG);
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsLockOn()
{
    return(e_BOOL)(LockOn == TRUE);
}
/*----------------------------------------------------------------------------*/
void Controller::SetUsbLock(e_BOOL _UsbLock)
{
    UsbLock = _UsbLock;
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::GetUsbLock()
{
    return(UsbLock);
}
/*----------------------------------------------------------------------------*/
void Controller::SetUsbKeyDetected(e_BOOL _UsbKeyDetected)
{
    UsbKeyDetected = _UsbKeyDetected;
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::GetUsbKeyDetected()
{
    return(UsbKeyDetected);
}
/*----------------------------------------------------------------------------*/
void Controller::SetUsbProcessingNode(MenuControlNode* _Node)
{
    UsbProcessingNode = _Node;
}
/*----------------------------------------------------------------------------*/
MenuControlNode* Controller::GetUsbProcessingNode()
{
    return(UsbProcessingNode);
}
/*----------------------------------------------------------------------------*/
void Controller::SetUsbCmdInProgress(e_BOOL _UsbCmdInProgress)
{
    this->UsbCmdInProgress = _UsbCmdInProgress;
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsUsbCmdInProgress()
{
    return(this->UsbCmdInProgress);
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsFSecuEnable()
{
    e_BOOL rc = FALSE;
    /* Noeud Apnée toujours visible en mode CPAP, VSIMV et PSIMV car il ne dépend pas
       de la Freq de sécurité */
    if (CurrentMode == CPAP)
        rc = FALSE;
    else if ((CurrentMode == VSIMV) || (CurrentMode == PSIMV))
        rc = TRUE;
    else
    {
        UWORD16 Val;

        DataBaseAccess::ReadValue(&Val,BACKUP_R_NO_SELECT_U16,ADJUST);

        rc = (e_BOOL)(!Val);
    }
    return(rc);
}
/*----------------------------------------------------------------------------*/
void Controller::SetFSecuEnable()
{
    this->ManageLineMenuVentil(this->GetNodeAt(NodeFsecu));
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsSoupirEnable()
{
    UWORD16 Val;
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    DataBaseAccess::ReadValue(&Val,ADJUST_SIGH_SELECT_U16,ADJUST);
    return(e_BOOL)Val;
}
/*----------------------------------------------------------------------------*/
void Controller::SetSoupirEnable()
{
    this->ManageLineMenuVentil(this->GetNodeAt(NodeSoupirSelect));
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsVtCibleEnable()
{
    UWORD16 Val;
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    DataBaseAccess::ReadValue(&Val,TARGET_VT_SELECT_U16,ADJUST);
    return(e_BOOL) (Val);
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsInhibApneaEnable()
{
    UWORD16 Val;
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    DataBaseAccess::ReadValue(&Val,APNEA_ALARM_ACTIVATION,CONFIG);
    return(e_BOOL) (Val);
}
/*----------------------------------------------------------------------------*/
void Controller::SetVtCibleEnable()
{
    this->ManageLineMenuVentil(this->GetNodeAt(NodeVtCible));
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsModeChange()
{
    return(e_BOOL)(ModeChangeOn == TRUE);
}
/*----------------------------------------------------------------------------*/
void Controller::SetModeChange(e_BOOL _Flag)
{
    ModeChangeOn = _Flag;
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsLastShutDownError()
{
    /*%C Lecture du flag Ventil request */
    UWORD16 Value = 0;
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    DataBaseAccess::ReadValue(&Value, VENTIL_REQ_U16, CONFIG);

    return(e_BOOL)(Value);
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsFio2Sensor()
{
    /*%C Lecture du flag de présence capteur FiO2 */
    UWORD16 Value = 0;
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    DataBaseAccess::ReadValue(&Value, DETECTED_FIO2_SENSOR, CONTROL);
    return(e_BOOL)(Value);
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsSpo2Sensor()
{
    /*%C Lecture du flag de présence capteur SpO2 */
    UWORD16 Value = 0;
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    DataBaseAccess::ReadValue(&Value, ERROR_SPO2_SENSOR_DETECTED, CONTROL);
    return(e_BOOL)(!Value);
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsModifNodeOn()
{
    return(e_BOOL)(ModifNodeOn == TRUE);
}
/*----------------------------------------------------------------------------*/
void Controller::SetModifNodeOn(e_BOOL _Flag)
{
    ModifNodeOn = _Flag;

    /* Mise à jour du flag de "modif paramètre en cours"  dans la base control */
    /*%C ecriture en base */
    UWORD16 Val = (UWORD16) _Flag;

    DataBaseAccess::WriteValue(&Val,ADJUSTMENT_IN_PROGRESS_U16,CONTROL);

    if (DifferMonitoringStart)
    {
        SetDifferMonitoring(FALSE);
        SetMonitoringMode(TRUE);
    }

}
/*----------------------------------------------------------------------------*/
void Controller::SetDifferMonitoring(e_BOOL _differ)
{
    DifferMonitoringStart = _differ;
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsDifferMonitoring()
{
    return(DifferMonitoringStart);
}
void Controller::SetBuzzerVoltRefreshReq(e_BOOL _refresh_request)
{
    BuzzerVoltRefreshReq = _refresh_request;
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsBuzzerVoltRefreshReq()
{
    return(BuzzerVoltRefreshReq);
}
/*----------------------------------------------------------------------------*/
void Controller::StartBuzzerVoltRefresh()
{
    SaveBuzzerVoltParamId = LOVBuzzerVoltage.GetIdParam();
    SaveBuzzerVoltDbId = LOVBuzzerVoltage.GetDbTarget();

    LOVBuzzerVoltage.SetDbTarget(COMPUTE);
    LOVBuzzerVoltage.SetIdParam(MEASURE_BUZZER_VOLTAGE_U16);

    SetBuzzerVoltRefreshReq(TRUE);
}
/*----------------------------------------------------------------------------*/
void Controller::StopBuzzerVoltRefresh()
{
    LOVBuzzerVoltage.SetDbTarget(SaveBuzzerVoltDbId);
    LOVBuzzerVoltage.SetIdParam(SaveBuzzerVoltParamId);

    SetBuzzerVoltRefreshReq(FALSE);
}
/*----------------------------------------------------------------------------*/
void Controller::BuzzerVoltRefresh()
{
    UWORD16 Val;
    if (IsBuzzerVoltRefreshReq())
    {
        DataBaseAccess::ReadValue(&Val,BIP_RUNNING_U16,CONTROL);
        if (!Val)
            StopBuzzerVoltRefresh();
    }
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsVentButtonOn()
{
    return(VentButtonOn);
}
/*----------------------------------------------------------------------------*/
void Controller::SetVentButtonOn(e_BOOL _VentButtonOn)
{
    VentButtonOn = _VentButtonOn;       
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsPSupportNull()
{
    return(e_BOOL)(PSupportNull == TRUE);
}
/*----------------------------------------------------------------------------*/
void Controller::SetPSupportNull(e_BOOL _Flag)
{
    PSupportNull = _Flag;
}
/*----------------------------------------------------------------------------*/
void Controller::SetHighPressAlarmToBeRemoved(e_BOOL _ToBeRemoved)
{
    HighPressAlarmToBeRemoved = _ToBeRemoved;
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::HasHighPressAlarmToBeRemoved()
{
    return(HighPressAlarmToBeRemoved);
}
/*----------------------------------------------------------------------------*/
void Controller::UpdateMode(void)
{
    UWORD16 Val;

    /* Reset du flag de detection de nouveau mode */
    Val = FALSE;
    DataBaseAccess::WriteValue(&Val,USB_NEW_MODE_DETECTED,USB);

    /* Lecture du nouveau mode */
    DataBaseAccess::ReadValue(&Val,USB_NEW_MODE,USB);

    if (IsVentilOn())
    {
        if (this->GetCurrentMode() != Val)
        {
            /* Mise à jour du mode modifié */
            LModeVent.SetModifMode((e_MODE_TYPES) Val);
            MoveCurrentNode(GetNodeAt(NodeVentil));
            /* Proposition de changement de mode */
            ManageModeChange();

        }
        else
            SetCurrentMode((e_MODE_TYPES) Val);
    }
    else
        /* on passe au nouveau mode */
        SetCurrentMode((e_MODE_TYPES) Val);
}
/*----------------------------------------------------------------------------*/
void Controller::SetCurrentMode(e_MODE_TYPES _CurrentMode)
{
    /*%C ecriture en base */
    UWORD16 Val = (UWORD16)_CurrentMode;

    DataBaseAccess::WriteValue(&Val,ADJUST_MODE_U16,CONFIG);

    /*%C Memorisation du mode */
    CurrentMode = _CurrentMode;

    /*%C Mise a jour des fenetres Ventil et alarme */
    ((LabelMode*)GetNodeAt(NodeVentil)->GetObject())->SetActifMode(CurrentMode);
    ((LabelMode*)GetNodeAt(NodeVentil)->GetObject())->ShowNominalView();
    ((LabelMode*)GetNodeAt(NodeAlarm)->GetObject())->SetActifMode(CurrentMode);
    ((LabelMode*)GetNodeAt(NodeAlarm)->GetObject())->ShowNominalView();

    /*%C Cache les noeuds de Changement du Mode */
    GetNodeAt(NodeModeChange)->SetVisible(FALSE);
    GetNodeAt(NodeAlModeChange)->SetVisible(FALSE);

    /*%C Affiche le noeud Préférence et Histo Alarme */
    GetNodeAt(NodePreference)->SetVisible(TRUE);
    GetNodeAt(NodeAlHisto)->SetVisible(TRUE);

    /* Mise à jour du label du noeud LOVPe suivant le mode */
    if ((CurrentMode == CPAP) &&
        ((GetLanguage() == HMI_LANG_FRENCH) ||
         (GetLanguage() == HMI_LANG_GERMAN)))
        LOVPe.SetName((UBYTE**)cMSG_CpapPressure);
    else
        LOVPe.SetName((UBYTE**)cMSG_ExhalationPressure);

    /*%C Gestion des Menus */
    ChangeMenuWithMode(CurrentMode);

    /*%C determination du nom du nvx mode + Sous Menu */
    switch (CurrentMode)
    {
    case VOL  :    SendNodeModify(NodeFrMini,TRUE);
        SendNodeModify(NodeInspTime,TRUE);
        SendNodeModify(NodeTriggerI,TRUE);
        break;
    case PRES :    SendNodeModify(NodeFrMini,TRUE);
        SendNodeModify(NodeInspTime,TRUE);
        SendNodeModify(NodeTriggerI,TRUE);
        break;
    case PSVT :    SendNodeModify(NodeFrMini,TRUE);
        SendNodeModify(NodeInspTime,TRUE);
        SendNodeModify(NodeFsecu,TRUE);
        SendNodeModify(NodeVtCible,TRUE);
        break;
    case VSIMV :   SendNodeModify(NodeFrMini,TRUE);
        SendNodeModify(NodeInspTime,TRUE);
        break;
    case CPAP :    SendNodeModify(NodeFrMini,TRUE);
        SendNodeModify(NodeInspTime,TRUE);
        break;
    default :      SendNodeModify(NodeFrMini,TRUE);
        SendNodeModify(NodeInspTime,TRUE);
        break;
    }

    /*%C fin du blink */
    BTable.RemoveElement(GetNodeAt(NodeVentil)->GetObject());
    BTable.RemoveElement(GetNodeAt(NodeAlarm)->GetObject());
    BTable.RemoveElement(GetNodeAt(NodeModeChange)->GetObject());
    BTable.RemoveElement(GetNodeAt(NodeAlModeChange)->GetObject());

    /*%C Mise a jour des fenetres */
    FVentilation.SetMode(CurrentMode);
    FAlarme.SetMode(CurrentMode);
    FGraph.SetMode(CurrentMode);   
}
/*----------------------------------------------------------------------------*/
e_MODE_TYPES Controller::GetCurrentMode()
{
    return CurrentMode;
}
/*----------------------------------------------------------------------------*/
void Controller::SetConsultMode(e_MODE_TYPES _ConsultMode)
{
    /*%C ecriture en base */
    UWORD16 Val = (UWORD16)_ConsultMode;
    DataBaseAccess::WriteValue(&Val,ADJUST_MODE_U16,CONFIG);

    ConsultMode = _ConsultMode;
    ChangeMenuWithMode(ConsultMode);

    /*%C Modification des noeud de Mode */
    ((LabelMode*)GetNodeAt(NodeVentil)->GetObject())->SetActifMode(this->GetCurrentMode());
    ((LabelMode*)GetNodeAt(NodeVentil)->GetObject())->SetModifMode(ConsultMode);
    ((LabelMode*)GetNodeAt(NodeVentil)->GetObject())->ShowMultiModeView();
    ((LabelMode*)GetNodeAt(NodeAlarm)->GetObject())->SetActifMode(this->GetCurrentMode());
    ((LabelMode*)GetNodeAt(NodeAlarm)->GetObject())->SetModifMode(ConsultMode);
    ((LabelMode*)GetNodeAt(NodeAlarm)->GetObject())->ShowMultiModeView();

    /*%C Cache le noeud Préférence et Histo Alarme */
    GetNodeAt(NodePreference)->SetVisible(FALSE);
    GetNodeAt(NodeAlHisto)->SetVisible(FALSE);

    /*%C Affichage des noeuds de Changement du Mode */
    GetNodeAt(NodeModeChange)->SetVisible(TRUE);
    GetNodeAt(NodeAlModeChange)->SetVisible(TRUE);

    /*%C Mise A OUI de ChangerMode */
    ((LabelValueString*)GetNodeAt(NodeModeChange)->GetObject())->SetIntValue1(1);
    ((LabelValueString*)GetNodeAt(NodeAlModeChange)->GetObject())->SetIntValue1(1);

    /*%c debut du blink */
    BTable.AddElement(GetNodeAt(NodeVentil)->GetObject());
    BTable.AddElement(GetNodeAt(NodeAlarm)->GetObject());
    BTable.AddElement(GetNodeAt(NodeModeChange)->GetObject());
    BTable.AddElement(GetNodeAt(NodeAlModeChange)->GetObject());

    /*%C Mise a jour des fenetres */
    FAlarme.SetMode(ConsultMode);
    FVentilation.SetMode(ConsultMode);
}
/*----------------------------------------------------------------------------*/
e_MODE_TYPES Controller::GetConsultMode()
{
    return ConsultMode;
}
/*----------------------------------------------------------------------------*/
e_BOOL Controller::IsVentilOn()
{
    UWORD16 VentilOn;
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    DataBaseAccess::ReadValue(&VentilOn, VENTIL_REQ_U16, CONFIG);

    return(e_BOOL)(VentilOn == TRUE);
}
/*----------------------------------------------------------------------------*/
MenuControlNode* Controller::GetCurrentNode()
{
    return CurrentNode;
}
/*----------------------------------------------------------------------------*/
void Controller::SetCurrentNode(MenuControlNode *_CurrentNode)
{
    CurrentNode = _CurrentNode;
}
/*----------------------------------------------------------------------------*/
void Controller::SetPressureUnit(UWORD16 _Val)
{
    e_BOOL _IsVisible;
    UWORD16 _SizeName, _SizeName2;

    /*%C Mise à jour et récupération du nom de l'unité de pression */
    LVSPressureUnit.SetIntValue1(_Val);
    UBYTE** _PressureUnit = LVSPressureUnit.GetItem(_Val);

    /*%C Mise à jour de l'unité de pression pour tous les paramètres concernés */
    LOVPi.SetNameUnit(_PressureUnit);
    LOVPSupport.SetNameUnit(_PressureUnit);
    LOVPControl.SetNameUnit(_PressureUnit);
    LOVPi2.SetNameUnit(_PressureUnit);
    LOVPe.SetNameUnit(_PressureUnit);
    LOVPiMax.SetNameUnit(_PressureUnit);

    _IsVisible = LOVPatientPressure.IsVisible();
    LOVPatientPressure.SetVisible(FALSE);
    LOVPatientPressure.SetNameUnit(_PressureUnit);
    LOVPatientPressure.SetNameUnit2(_PressureUnit);
    LOVPatientPressure.SetVisible(_IsVisible);

    _IsVisible = LOVValvePressure.IsVisible();
    LOVValvePressure.SetVisible(FALSE);
    LOVValvePressure.SetNameUnit(_PressureUnit);
    LOVValvePressure.SetVisible(_IsVisible);

    LOVPMax.SetNameUnit(_PressureUnit);

    LOVPiMbar.SetNameLabel2(_PressureUnit);
    _SizeName = Tools::GetStringPixelSize(LOVPiMbar.GetName(), LOVPiMbar.GetFontLabel());
    _SizeName2 = Tools::GetStringPixelSize(LOVPiMbar.GetNameLabel2(), LOVPiMbar.GetFontLabel());
    if (_SizeName + _SizeName2 >= FIRST_VALUE_COLUMN - 19)
    {
        /* L'unité ne passe pas, on la décale dessous */
        LOVPiMbar.SetLabel2LineOffset    (12);
        LOVPiMbar.SetLabel2ColOffset     (12);
    }
    else
    {
        /* L'unité passe, on la laisse sur la même ligne */
        LOVPiMbar.SetLabel2LineOffset    (0);
        LOVPiMbar.SetLabel2ColOffset     (_SizeName + 2);
    }


    /*%C Mise à jour de l'unité de pression pour les autres fenêtres */
    FVentilation.SetPressureUnit(_PressureUnit);
    FGraph.SetPressureUnit(_PressureUnit);
    FAlarme.SetPressureUnit(_PressureUnit);
    FTendance.SetPressureUnit(_PressureUnit);         

}
/*----------------------------------------------------------------------------*/
void Controller::SetMCycl(e_BOOL _ModeCycl)
{
    /*%C Envoi du signal aux fenêtres de monitoring */
    FVentilation.SetIESelected(_ModeCycl);
    FAlarme.SetIESelected(_ModeCycl);
    FGraph.SetIESelected(_ModeCycl);
}
/*----------------------------------------------------------------------------*/
void Controller::SetConvTrigE(e_BOOL _ConvTrigE)
{
    /*%C  Envoi du signal au controller lui-même
          pour mise à jour des paramètres et des alarmes */
    this->SetTrigEPosSelected(_ConvTrigE);
}
/*----------------------------------------------------------------------------*/
void Controller::SetInhibApneaOk(e_BOOL _ApneaAlarm)
{
    /*%C  Envoi du signal aux fenêtres Ventilation, Alarme et Graph */
    FVentilation.SetInhibApneaOk(_ApneaAlarm);
    FAlarme.SetInhibApneaOk(_ApneaAlarm);
    FGraph.IsInhibApneaAlarmVisible();

    /* Mise à jour des fenêtres ventil et alarme */
    ChangeMenuWithMode(CurrentMode);
}
/*----------------------------------------------------------------------------*/
void Controller::SetValve(e_BOOL _ValveDetected)
{
#ifndef HMI_CONFIG_S2
    e_MODE_TYPES Mode;
    UWORD16 Val,i;

    UWORD16 FuiteNodeId, VteNodeId;
#endif

    if (ValveDetected != _ValveDetected)
    {
        /* Timeout sur le noeud pour sortir de modification */
        (this->*(this->GetCurrentNode()->GetEventNode()->OnTimeOut))();

#ifndef HMI_CONFIG_S2
        /*%C Récupération du Mode */
        DataBaseAccess::ReadValue(&Val,ADJUST_MODE_U16,CONFIG);
        Mode = (e_MODE_TYPES) Val;

        FuiteNodeId = GetNodeAt(NodeAlFuite)->GetEventNode()->GetId();
        VteNodeId = GetNodeAt(NodeAlVte)->GetEventNode()->GetId();

        /*%C Effacement du menu Alarme */
        HideAlarm(Mode, FuiteNodeId);
        HideAlarm(Mode, VteNodeId);

        /*%C Changement de configuration Fuite -> Vte */
        for (i=0;i<cMAX_MODE;i++)
        {
            /*%C  Pas de fonctionnement avec fuite pour les modes volume
                  et pas de fonctionnement avec valve (vte) pour le mode CPAP */
            if ((i != VOL) && (i != VSIMV) && (i !=PSIMV) && (i != CPAP))
                Tools::SwitchDisplayConfigForOneMode(  FuiteNodeId, VteNodeId,(e_MODE_TYPES)i);
        }

        /*%C Reconstruction de l'arbre d'affichage des alarmes */
        RebuildEventNodeTree(Mode, NodeAlarm, cAlarmEndNode);

        /*%C Affichage du menu Alarme */
        ShowAlarm(Mode, FuiteNodeId);
        ShowAlarm(Mode, VteNodeId);

        /*%C Move to the valid node */
        if (GetCurrentFrame() == FRAME_ALARME)
        {
            if (GetNodeAt(FuiteNodeId)->IsValid())
                MoveCurrentNode(this->GetNodeAt(FuiteNodeId));
            if (GetNodeAt(VteNodeId)->IsValid())
                MoveCurrentNode(this->GetNodeAt(VteNodeId));
        }
#endif
        ValveDetected = _ValveDetected;

        if (MonitoringMode)
        {
            /* Si l'info Valve a changé et qu'on est en monitoring alors, mettre à jour ce monitoring */
            SetMonitoringMode(TRUE);
        }
    }
}
/*----------------------------------------------------------------------------*/
void Controller::Fio2MonitorEnabled(e_BOOL _IsOk)
{
    if (_IsOk)
    {
        LTTVFiO2.StartMonitoringMode();
        if (GetCurrentFrame() == FRAME_MAINTENANCE)
            LOVFiO2Concent.StartMonitoringMode();
    }
    else
    {
        LTTVFiO2.StopMonitoringMode();
        if (GetCurrentFrame() == FRAME_MAINTENANCE)
            LOVFiO2Concent.StopMonitoringMode();
    }

    if (IsNodeInTree( CurrentMode, NodeAlFiO2, NodeAlarm, cAlarmEndNode))
    {
        LTTVFiO2.Hide();
        LTTVFiO2.Show();
    }
}
/*----------------------------------------------------------------------------*/
void Controller::Spo2MonitorEnabled(e_BOOL _IsOk)
{
    if (_IsOk)
        LTTVSpO2.StartMonitoringMode();
    else
        LTTVSpO2.StopMonitoringMode();
}
/*----------------------------------------------------------------------------*/
void Controller::SendInfoValve(e_BOOL _ValveDetected)
{
    FVentilation.SetValve(_ValveDetected, (e_BOOL) !this->IsModeChange());
    FAlarme.SetValve(_ValveDetected, (e_BOOL) !this->IsModeChange());
    FGraph.SetValve(_ValveDetected,(e_BOOL) (CurrentVirtualFrame == FRAME_GRAPH));
    this->SetValve(_ValveDetected);
}
/*----------------------------------------------------------------------------*/
void Controller::SetPressConvention(e_BOOL _Conv)
{
    /* install handlers */
    if (_Conv)
    {
        /* for Pi...*/
        GetNodeAt(NodeModifPi)->GetEventNode()->SetOnButtonUp(&Controller::ModifyUpNodePlusPeep);
        GetNodeAt(NodeModifPi)->GetEventNode()->SetOnButtonDown(&Controller::ModifyDownNodePlusPeep);

        /* for Pi2...*/
        GetNodeAt(NodeModifPi2)->GetEventNode()->SetOnButtonUp(&Controller::ModifyUpNodePlusPeep);
        GetNodeAt(NodeModifPi2)->GetEventNode()->SetOnButtonDown(&Controller::ModifyDownNodePlusPeep);

        /* for P Max... */
        GetNodeAt(NodeModifPiMax)->GetEventNode()->SetOnButtonUp(&Controller::ModifyUpNodePlusPeep);
        GetNodeAt(NodeModifPiMax)->GetEventNode()->SetOnButtonDown(&Controller::ModifyDownNodePlusPeep);

        /* for P Control... */
        GetNodeAt(NodeModifPControl)->GetEventNode()->SetOnButtonUp(&Controller::ModifyUpNodePlusPeep);
        GetNodeAt(NodeModifPControl)->GetEventNode()->SetOnButtonDown(&Controller::ModifyDownNodePlusPeep);

        /* for P Support... */
        GetNodeAt(NodeModifPSupport)->GetEventNode()->SetOnButtonUp(&Controller::ModifyUpNodePlusPeep);
        GetNodeAt(NodeModifPSupport)->GetEventNode()->SetOnButtonDown(&Controller::ModifyDownNodePlusPeep);

        /* for Pe... */
        GetNodeAt(NodeModifPe)->GetEventNode()->SetOnButtonUp(&Controller::ModifyUpPeepNodePlusPeep);
        GetNodeAt(NodeModifPe)->GetEventNode()->SetOnButtonDown(&Controller::ModifyDownPeepNodePlusPeep);
    }

    FVentilation.SetPressConvention(_Conv);
}
/*----------------------------------------------------------------------------*/
void Controller::SendInfoBlocExpi(e_BOOL _BlocExpiDetected)
{
    FGraph.SetBlocExpi(_BlocExpiDetected,(e_BOOL) (CurrentVirtualFrame == FRAME_GRAPH));
}
/*----------------------------------------------------------------------------*/
void Controller::SendInfoFio2Sensor(e_BOOL _IsOk)
{
    if (IsVentilOn() || (GetCurrentFrame() == FRAME_MAINTENANCE))
    {
        FVentilation.Fio2MonitorEnabled(_IsOk);
        FAlarme.Fio2MonitorEnabled(_IsOk);
        FGraph.Fio2MonitorEnabled(_IsOk, (e_BOOL) !(GetCurrentFrame() == FRAME_GRAPH));
        this->Fio2MonitorEnabled(_IsOk);
    }
    else
    {
        FVentilation.Fio2MonitorEnabled(FALSE);
        FAlarme.Fio2MonitorEnabled(FALSE);
        FGraph.Fio2MonitorEnabled(FALSE, (e_BOOL) !(GetCurrentFrame() == FRAME_GRAPH));
        this->Fio2MonitorEnabled(FALSE);
    }
}
/*----------------------------------------------------------------------------*/
void Controller::SendInfoSpo2Sensor(e_BOOL _IsOk)
{
    if (_IsOk)
    {
        if (IsVentilOn())
        {
            FVentilation.Spo2MonitorEnabled(_IsOk);
            FAlarme.Spo2MonitorEnabled(_IsOk);
            FGraph.Spo2MonitorEnabled(  _IsOk, 
                                        (e_BOOL) !(GetCurrentFrame() == FRAME_GRAPH));
            this->Spo2MonitorEnabled(_IsOk);
        }
    }
    else
    {
        FVentilation.Spo2MonitorEnabled(_IsOk);
        FAlarme.Spo2MonitorEnabled(_IsOk);
        FGraph.Spo2MonitorEnabled(    _IsOk, 
                                      (e_BOOL) !(GetCurrentFrame() == FRAME_GRAPH));
        this->Spo2MonitorEnabled(_IsOk);
    }
}
/*----------------------------------------------------------------------------*/
void Controller::SendInfoBadSupplyCheck(e_BOOL _IsBad)
{
    FBatteryMenu.BadSupplyCheck(_IsBad);
}
/*----------------------------------------------------------------------------*/
void Controller::SendInfoUsbErrorCodeReady(e_BOOL _ErrorCodeReady)
{

#ifdef HMI_CONFIG_USB

    UWORD16 _ErrorCode, _NodeId, Val;
    MenuControlNode * _ProcessingNode;
    UBYTE* _StringToDisplay;
    e_BOOL _Lock;

    if (_ErrorCodeReady)
    {
        /*%C Lecture du code d'erreur */
        DataBaseAccess::ReadValue(&_ErrorCode,USB_ERROR_CODE_IHM_U16,USB);

        /*%C Prise en compte du code d'erreur par la fenêtre USB */
        _Lock = FUsb.ManageErrorCode(_ErrorCode, &_StringToDisplay);

        /*%C Ajout du message à la queue de messages */
        if (    (_ErrorCode != E_USB_READY_ACCESS)
                ||  ((_ErrorCode == E_USB_READY_ACCESS)
                     &&  ((this->PreviousErrorCode == E_USB_OK)
                          ||  (this->PreviousErrorCode == E_USB_COMMAND_STOPPED)
                          ||  (this->PreviousErrorCode == E_USB_ONE_KEY_CONNECTED))))
        {
            UsbDelayed.AddMessageToQueue(   _StringToDisplay,
                                            TIME_USB_ERROR_CODE_MESSAGE,
                                            (e_BOOL)(GetCurrentFrame() == FRAME_USB));

    #ifdef HMI_CONFIG_USB_PROCESSING
            Timer.StopTimer(TimerUsbProcessing);
    #endif
        }
        else
        {
            /*%C No dislpay message */
        }

        /*% Reset du flag de signalisation d'un code d'erreur prêt... */
        Val = (UWORD16)FLAG_ERROR_CODE_NOT_READY;
        DataBaseAccess::WriteValue(&Val,USB_ERROR_CODE_READY_IHM_U16,USB);

        /*% ... et du code d'erreur lui-même */
        Val = (UWORD16)E_USB_OK;
        DataBaseAccess::WriteValue(&Val,USB_ERROR_CODE_IHM_U16,USB);

        _ProcessingNode = GetUsbProcessingNode();

        if (_ProcessingNode != NULL)
        {
            /*%C Le driver USB a mis jour les valeurs, on peut donc faire un
                  refresh de l'affichage */
            (_ProcessingNode->GetObject())->Refresh();
        }
        if (_Lock)
        {
            /*%C  Le code d'erreur demande le lock du menu, on se place donc sur le noeud
                  ghost  et on locke le menu USB */
            if (_ErrorCode == E_USB_KEY_DISCONNECTED)
            {
                SetUsbProcessingNode(NULL);
                UsbUpdateNavigNodes(NodeVentil);        
                if (!UsbDelayed.GetNbOfMessagesInQueue() || (this->PreviousErrorCode == E_USB_READY_ACCESS))
                    UsbMoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeVentil), eGoDown), (e_BOOL)(GetCurrentFrame() == FRAME_USB));
            }
            else
            {
                UsbUpdateNavigNodes(NodeUsbGhost);
                UsbMoveCurrentNode(GetNodeAt(NodeUsbGhost), (e_BOOL)(GetCurrentFrame() == FRAME_USB));
                ManageUsbLock(TRUE);
            }
        }
        else
        {
            /*%C  Le code d'erreur demande le délock du menu, on se place donc sur le noeud
                  de la commande envoyée ou sur le premier noeud usb si pas de commande en cours */
            ManageUsbLock(FALSE);
            if (GetUsbProcessingNode())
            {
                /*%C  C'est un code d'erreur issu d'une commande et qui n'a _pas_ renvoyé Lock.
                      _ProcessingNode = noeud de modif, il faut repartir sur le noeud normal */
                _NodeId = _ProcessingNode->GetEventNode()->GetIdNodeOnTimeOut();
                UsbMoveCurrentNode(GetNodeAt(_NodeId), (e_BOOL)(GetCurrentFrame() == FRAME_USB));
                UsbUpdateNavigNodes(_NodeId);
            }
            else
            {
                /*%C  C'est un code d'erreur spontané qui n'est pas issu d'une commande
                      et qui n'a _pas_ renvoyé Lock.
                      NodeUsbStop est invisible et lors du retour à cet écran il ne faut
                      pas afficher cUsbStartNode puisque menu locké d'où le NodeUsbGhost */
                UsbUpdateNavigNodes(cUsbStartNode);
                UsbMoveCurrentNode(GetNodeAt(cUsbStartNode), (e_BOOL)(GetCurrentFrame() == FRAME_USB));         
            }
            /*%C Dé-lock du menu, on bippe */
            Tools::ShortBipRequest();
        }
        this->PreviousErrorCode = _ErrorCode ;

        /*%C On cache le noeud stop */
        GetNodeAt(NodeUsbStop)->SetVisible(FALSE);

        /*%C Pas de commande USB en cours */
        SetUsbCmdInProgress(FALSE);             
    }
#endif /* HMI_CONFIG_USB */
}
/*----------------------------------------------------------------------------*/
void Controller::UsbMoveCurrentNode(MenuControlNode *_CurrentNode, e_BOOL _forced)
{
    UWORD16 Val1, Val2;
    e_BOOL active;
    /*%C  On n'affiche le menu USB que si la détection de clé se fait après le Power On
          Sur clé déjà présente au moment du power on, on ne change pas de noeud et on accède
          au menu USB par la touche de navigation */
    DataBaseAccess::ReadValue(&Val1,USB_KEY1_DETECTED_AFTER_POWER_ON_U16,USB);
    DataBaseAccess::ReadValue(&Val2,USB_KEY2_DETECTED_AFTER_POWER_ON_U16,USB);
    active = InterfaceCppC::IsOneAlarmActive();

    if (   ((Val1 == TRUE) &&
            (Val2 == TRUE) &&
            !IsModeChange() &&
            !active)
           || (_forced))
    {
        UWORD16 _IdNode = GetCurrentNode()->GetEventNode()->GetId();
        if (Tools::IsModifyNode(_IdNode))
        {
            /* Si c'est un noeud de modif alors on appelle sa fonction de timeout avant de
               partir vers le noeud USB */
            (this->*(this->GetCurrentNode()->GetEventNode()->OnTimeOut))();
            StopTimer(TimeOutModifEvent);
        }
        MoveCurrentNode(_CurrentNode);
    }
}
/*----------------------------------------------------------------------------*/
void Controller::UsbUpdateNavigNodes(UWORD16 _NodeId)
{
    GetNodeAt(NodeGraphGhost)->GetEventNode()->SetIdNodeOnMonitor(_NodeId);
    GetNodeAt(NodeAlGhost)->GetEventNode()->SetIdNodeOnMonitor(_NodeId);
    GetNodeAt(NodeAlGhost)->GetEventNode()->SetIdNodeOnDown(_NodeId);
    GetNodeAt(NodeAlGhost)->GetEventNode()->SetIdNodeOnUp(_NodeId);
}
/*----------------------------------------------------------------------------*/
void Controller::SetTrigEPosSelected(e_BOOL _TrigEPosSelected)
{
    e_MODE_TYPES Mode;
    UWORD16 Val;

    UWORD16 TrigEPosNodeId, TrigENegNodeId;

    if (TrigEPosSelected != _TrigEPosSelected)
    {
        /*%C Récupération du Mode */
        DataBaseAccess::ReadValue(&Val,ADJUST_MODE_U16,CONFIG);
        Mode = (e_MODE_TYPES) Val;

        TrigEPosNodeId = GetNodeAt(NodeTriggerE)->GetEventNode()->GetId();
        TrigENegNodeId = GetNodeAt(NodeTriggerEsigned)->GetEventNode()->GetId();

        /*%C Effacement du menu Ventil */
        HideVentil(Mode, TrigEPosNodeId);
        HideVentil(Mode, TrigENegNodeId);

        /*%C Changement de configuration TriggE -> TriggE négatif */
        Tools::SwitchDisplayConfigForAllModes(TrigEPosNodeId, TrigENegNodeId);

        /*%C Reconstruction de l'arbre d'affichage de la ventilation */
        RebuildEventNodeTree(Mode, NodeVentil, cVentilEndNode);

        /*%C Affichage du nvx menu Ventil */
        ShowVentil(Mode, TrigEPosNodeId);
        ShowVentil(Mode, TrigENegNodeId);

        TrigEPosSelected = _TrigEPosSelected;
    }
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne une instance unique du controller											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
Controller* Controller::GetInstance()
{
#ifndef _BORLAND
    static Controller Control;

    if (FirstCall == true)
    {
        Control.Init();
        FirstCall = false;
    }
    return &Control;
#else
    static Controller* Control;

    if (FirstCall == true)
    {
        Control = new Controller();
        Control->Init();
        FirstCall = false;
    }
    return Control;
#endif
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Détruit une instance unique du controller											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::RemoveInstance()
{
#ifndef _BORLAND
#else
    Controller* pControl = GetInstance();
    if (pControl != NULL)
    {
        delete pControl;
        FirstCall = true;
        InterfaceCppC::ErazePage(VIRTUAL_PAGE);
        InterfaceCppC::ErazePage(VIDEO_PAGE1);
        InterfaceCppC::ErazePage(VIDEO_PAGE2);
    }
#endif
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Change le noeud courant																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		CurrentNode : nvx noeud													 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::MoveCurrentNode(MenuControlNode *_CurrentNode)
{
    /*%C Quitte le noeud courant */
    if (CurrentNode != NULL)
    {
        CurrentNode->GetObject()->LoseFocus();
    }

    /*%C affectation */
    SetCurrentNode(_CurrentNode);

    /*%C Verification si changement de page */
    UWORD16 Temp = Tools::GetNumFrame(_CurrentNode->GetEventNode()->GetId());
    if (GetCurrentFrame() != Temp)
    {
        SetCurrentFrame(Temp);
    }

    /*% C Donne le focus */
    _CurrentNode->GetObject()->WinFocus();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Change le mode directement après Valid sur	ChangeMode							*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ChangeModeSimplify()
{
    /*%C Récupère le Node courant pour la modif de Node */
    SendNodeModify(CurrentNode->GetEventNode()->GetId(), TRUE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Deplace le noeud courant vers le noeud de modification associe				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::MoveToModifNode()
{
    SetModifNodeOn(TRUE);

    /*%C Quitte le noeud courant */
    if (CurrentNode != NULL)
    {
        CurrentNode->GetObject()->Refresh();
        CurrentNode->GetObject()->StartModifMode();

        /*%C debut du blink */
        BTable.AddElement(CurrentNode->GetObject());

        /*%C affectation */
        SetCurrentNode(GetNodeAt(   CurrentNode->
                                    GetEventNode()->
                                    GetIdNodeOnValid()));

        /*%C lancement du timer du noeud */
        Timer.StartTimer(TIME_OUT_MODIF_EVENT,TimeOutModifEvent,FALSE);

        /*%C fin du timer sur le changement de Mode si actif */
        if (IsModeChange())
        {
            Timer.StopTimer(TimerStopModifMode);
        }
    }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Deplace le noeud courant vers le prochain noeud de modification	(valid)	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::MoveToNextModifNode()
{
    /* Traitement des affichages d'interdépendance */
    SettingBlockDetect();

    MoveToNextModifNodeOnKey(eGoValid);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Deplace le noeud courant vers le prochain noeud de modification				*/
/*%C  suivant le type de touche																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::MoveToNextModifNodeOnKey(WayId _Key)
{
    /*%C fin du blink sur la valeur courante */
    BTable.RemoveElement(CurrentNode->GetObject());

    /*%C Change de Valeur de modification */
    if (CurrentNode != NULL)
    {
        CurrentNode->GetObject()->ModifNextValue();
    }

    /*%C affectation */
    switch (_Key)
    {
    case eGoMonitor   :     SetCurrentNode(GetNodeAt(   CurrentNode->
                                                        GetEventNode()->
                                                        GetIdNodeOnMonitor()));
        break;

    case eGoValid     :     SetCurrentNode(GetNodeAt(   CurrentNode->
                                                        GetEventNode()->
                                                        GetIdNodeOnValid()));
        break;

    case eGoLongValid :     SetCurrentNode(GetNodeAt(   CurrentNode->
                                                        GetEventNode()->
                                                        GetIdNodeOnLongValid()));
        break;
    default :
        break;                           
    }

    /*%C debut du blink sur la valeur courante */
    BTable.AddElement(CurrentNode->GetObject());

    /*%C lancement du timer */
    if (_Key == eGoValid)
    {
        /*%C Arret du timer pour la calibration */
        Timer.StartTimer(TIME_OUT_MODIF_EVENT,TimeOutModifEvent,FALSE);
    }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Deplace le noeud courant vers le prochain noeud de base						*/
/*%C  (sens = valid) _ touche																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ReturnToNode()
{
    ReturnToNodeOnKey(eGoValid);

    /*%C Notification de modification du noeud */
    SendNodeModify(CurrentNode->GetEventNode()->GetId(),TRUE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Deplace le noeud courant vers le prochain noeud de base  depuis un noeud */
/*%C USB	(sens = valid) _ touche																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ReturnToNodeUsb()
{
    /*%C On passe au nouveau noeud */
    ReturnToNodeOnKeyUsb(eGoValid);

    /*%C Notification de modification du noeud */
    SendNodeModify(CurrentNode->GetEventNode()->GetId(),TRUE);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Deplace le noeud courant vers le prochain noeud de base						*/
/*%C  dans le cas d'un Time Out sur noeud USB											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ReturnToNodeUsbTO()
{
    /* routine de gestion de time out */
    ReturnToNodeTO();

    /* suppression du message par ajout d'un message vide à afficher */
    UsbDelayed.AddMessageToQueue(    (UBYTE*) "",
                                     TIME_USB_ERROR_CODE_MESSAGE,
                                     (e_BOOL)(GetCurrentFrame() == FRAME_USB));
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Deplace le noeud courant vers le prochain noeud de base						*/
/*%C  suivant le type de touche																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Key : sens du deplacement												 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ReturnToNodeOnKeyUsb(WayId _Key)
{
    UBYTE* _StringToDisplay;

    MenuControlNode * _PreviousNode = NULL;
    /*%C Arret de la modification */
    EndModifToNode();

    /*%C Quitte le noeud de modif */
    if (CurrentNode != NULL)
    {
        CurrentNode->GetObject()->StopModifMode();
        _PreviousNode = CurrentNode;
    }

    /*%C affectation du nouveau noeud */
    switch (_Key)
    {
    case eGoMonitor   :     SetCurrentNode(GetNodeAt(   CurrentNode->
                                                        GetEventNode()->
                                                        GetIdNodeOnMonitor()));
        break;

    case eGoValid     :     SetCurrentNode(GetNodeAt(   CurrentNode->
                                                        GetEventNode()->
                                                        GetIdNodeOnValid()));
        break;

    case eGoLongValid :     SetCurrentNode(GetNodeAt(   CurrentNode->
                                                        GetEventNode()->
                                                        GetIdNodeOnLongValid()));
        break;
    default :
        break;                           
    }


    if ((_PreviousNode != NULL) && (_Key == eGoValid))
    {
        UWORD16 _Val;
        e_BOOL _EraseFlag;

        _Val = (_PreviousNode->GetObject())->GetFullValue();

        if (_Val)
        {
            /*%C  On positionne le flag de commande pour indiquer au driver bas niveau
                  qu'une commande doit être traitée */

            _Val = (UWORD16) TRUE;
            DataBaseAccess::WriteValue(&_Val,USB_COMMAND_SENT_U16,USB);

            if (_PreviousNode->GetEventNode()->GetId() == NodeModifUsbEraseKey)
                _EraseFlag = TRUE;
            else
                _EraseFlag = FALSE;

            /*%C Envoi de l'information à la fenêtre USB */
            FUsb.GetUsbProcessingMessage(_EraseFlag, &_StringToDisplay);

            UsbDelayed.AddMessageToQueue(  _StringToDisplay,
                                           TIME_USB_MESSAGE,
                                           (e_BOOL)(GetCurrentFrame() == FRAME_USB));
#ifdef HMI_CONFIG_USB_PROCESSING
            Timer.StartTimer(TIME_USB_PROCESSING,TimerUsbProcessing,TRUE);
#endif         

            /*%C Sauvegarde du noeud en cours de traitement */
            SetUsbProcessingNode(_PreviousNode);

            /*%C Commande USB en cours */
            SetUsbCmdInProgress(TRUE);

            /*%C On rafraîchit la navigation et on se place sur le noeud stop*/
            GetNodeAt(NodeGraphGhost)->GetEventNode()->SetIdNodeOnMonitor(NodeUsbStop);
            GetNodeAt(NodeAlGhost)->GetEventNode()->SetIdNodeOnMonitor(NodeUsbStop);
            GetNodeAt(NodeAlGhost)->GetEventNode()->SetIdNodeOnDown(NodeUsbStop);
            GetNodeAt(NodeAlGhost)->GetEventNode()->SetIdNodeOnUp(NodeUsbStop);
            GetNodeAt(NodeUsbStop)->SetVisible(TRUE);
            MoveCurrentNode(GetNodeAt(NodeUsbStop));

            /*%C Si on a lancé une opération alors on bloque l'affichage USB */
            ManageUsbLock(TRUE);
        }
        else
        {
            /* La commande n'a pas été lancée alors on n'affiche rien en envoyant
            un message vide */
            UsbDelayed.AddMessageToQueue(  (UBYTE*) "",
                                           TIME_USB_ERROR_CODE_MESSAGE,
                                           (e_BOOL)(GetCurrentFrame() == FRAME_USB));
        }
    }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Stoppe toute commande USB en cours                                       */
/*%I Input Parameter : 																			*/
/*%I 		NONE                    												 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ValidUsbStop()
{
    /*%C on envoie l'info au driver */
    UWORD16 _Val = (UWORD16) TRUE;
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    DataBaseAccess::WriteValue(&_Val,USB_STOP_COMMAND_SENT_U16,USB);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Routine appelée lors de la modification du noeud de sauvegarde des       */
/*%C paramètres                                                               */
/*%I Input Parameter : 																			*/
/*%I 		NONE                    												 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::StartSavingUsbSettings()
{
    Controller* Cont = Controller::GetInstance();

    UWORD16 _Val = E_USB_NOERROR_SETTINGS_OVERWRITE;
    UBYTE* _StringToDisplay;

    /*%C Prise en compte du code d'erreur par la fenêtre USB */
    Cont->FUsb.ManageErrorCode(_Val, &_StringToDisplay);

    /*%C Ajout du message à la queue de messages */
    Cont->UsbDelayed.AddMessageToQueue(  _StringToDisplay,
                                         TIME_USB_ERROR_CODE_MESSAGE,
                                         (e_BOOL)(Cont->GetCurrentFrame() == FRAME_USB));

}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Deplace le noeud courant vers le prochain noeud de base						*/
/*%C  suivant le type de touche																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Key : sens du deplacement												 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ReturnToNodeOnKey(WayId _Key)
{
    /*%C Arret de la modification */
    EndModifToNode();

    /*%C Quitte le noeud de modif */
    if (CurrentNode != NULL)
    {
        CurrentNode->GetObject()->StopModifMode();
    }

    /*%C affectation du nouveau noeud */
    switch (_Key)
    {
    case eGoMonitor   :     SetCurrentNode(GetNodeAt(   CurrentNode->
                                                        GetEventNode()->
                                                        GetIdNodeOnMonitor()));
        break;

    case eGoValid     :     SetCurrentNode(GetNodeAt(   CurrentNode->
                                                        GetEventNode()->
                                                        GetIdNodeOnValid()));
        break;

    case eGoLongValid :     SetCurrentNode(GetNodeAt(   CurrentNode->
                                                        GetEventNode()->
                                                        GetIdNodeOnLongValid()));
        break;
    }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Deplace le noeud courant vers le prochain noeud de base						*/
/*%C  dans le cas d'un Time Out																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ReturnToNodeTO()
{
    /*%C Arret de la modification */
    EndModifToNode();

    /*%C Quitte le noeud de modif */
    if (CurrentNode != NULL)
    {
        CurrentNode->GetObject()->CancelModifMode();
    }

    /*%C affectation du nouveau noeud */
    SetCurrentNode(GetNodeAt(   CurrentNode->
                                GetEventNode()->
                                GetIdNodeOnTimeOut()));

    /*%C Notification de modification du noeud */
    SendNodeModify(CurrentNode->GetEventNode()->GetId(), FALSE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Fin de modification sur un noeud de modif											*/
/*%C End of change on an edit node                                                                      	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::EndModifToNode()
{
    /* Effacement du message d'interdépendance */
    // Erasing the message of interdependence
    // When the setting completes its modification
    // hide the helper text for that setting.
    if (CurrentLoupe != NULL)
    {
        CurrentLoupe->DisplayMessage(FALSE);
        TopMessage.Hide();
		BottomMessage.Hide();
    }

    /*%C Arret du timer pour permettre reenregistrer l'objet dans le blinker */
    Timer.StopTimer(TimerAddToBlinkEvent);

    BTable.RemoveElement(CurrentNode->GetObject());

    /*%C fin du timer sur le noeud */
    Timer.StopTimer(TimeOutModifEvent);

    /*%C Arret modif sur le noeud */
    SetModifNodeOn(FALSE);

    /*%c debut du timer sur le changement de Mode si actif */
    if (IsModeChange())
    {
        Timer.StartTimer(TIME_STOP_MODIF_MODE,TimerStopModifMode,FALSE);
    }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Deplace le noeud courant vers le noeud de	modification						*/
/*%C 	  associe avec affichage de la loupe												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE											 											*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::MoveToModifNodeLoupe()
{
    VFrame* CFrame = GetFrameObject(CurrentFrame);

    DisplayObject* Object = CurrentNode->GetObject();

    Label*  EditableObject = (Label*)Object;

    /*%C arret d'uun precedant effacement de la loupe */
    Timer.StopTimer(TimerHideLoupe);

    /*%C affichage de la loupe */
    if (!IsVentilOn())
    {
        HideMessageFrame();
    }
    else
    {
        /*%C Arret d'un timer d'effacement de la fenetre d'arret de la ventil */
        // stop the timer that clears the stop ventilation message
        Timer.StopTimer(TimerHideStopVentMess);
        /*%C Arret du refresh */
        // stop patient data monitoring refresh in the loupe
        CFrame->HideMonitoring();
    }
    CFrame->ShowLoupe();

    /*%C affectation de la loupe a l'objet */
    EditableObject->SetLoupe(CFrame->GetLoupeObject());

    /*%C Memorisation de la loupe dans le controleur */
    CurrentLoupe = CFrame->GetLoupeObject();

    MoveToModifNode();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Deplace le noeud courant vers le noeud de base									*/
/*%C 	  (sens = valid) avec effacement de la loupe touche							*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ReturnToNodeLoupe()
{
    /*%C reprend l'execution normale */
    ReturnToNode();

    //Efface de la loupe dans l'objet courant
    DisplayObject* Object = CurrentNode->GetObject();

    Label*  EditableObject = (Label*)Object;

    EditableObject->SetLoupe(NULL);

    /*%C Efface la loupe */
    Timer.StartTimer(TIME_HIDE_LOUPE,TimerHideLoupe,FALSE);

    /*%C Effacement de la loupe dans le controleur */
    CurrentLoupe = NULL;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Deplace le noeud courant vers le noeud de base									*/
/*%C 	  dans le cas d'un Time Out avec effacement de la loupe						*/
/*%C Moves the current node to the base node */
/*%C in the case of a Time Out with deletion of loupe */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ReturnToNodeTOLoupe()
{
    VFrame* CFrame = GetFrameObject(CurrentFrame);

    /*%C Efface de la loupe dans l'objet courant */
    DisplayObject* Object = CurrentNode->GetObject();
    Label*  EditableObject = (Label*)Object;
    EditableObject->SetLoupe(NULL);

    /*%C Arret de la modification */
    ReturnToNodeTO();

    /*%C reaffiche le message de lancement de la ventil */
    if (!IsVentilOn())
    {
        ShowMessageFrame(   TRUE,
                            (UBYTE*)cMSG_StartVentil[GetLanguage()],
                            VENTIL);
    }
    else
    {
        /*%C reaffiche le monitoring */
        CFrame->ShowMonitoring();
    }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne l'instance d'une fenetre														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		id : numero de la fenetre												 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		instance d'une fenetre						  							  			*/
/******************************************************************************/
VFrame* Controller::GetFrameObject(UWORD16 _id)
{
    switch (_id)
    {
    case FRAME_WELCOME :       return &FWelcome;
    case FRAME_VENTILATION :   return &FVentilation;
    case FRAME_ALARME :        return &FAlarme;
    case FRAME_HISTO_ALARME :  return &FHistoAlarme;
    case FRAME_CONFIGURATION : return &FConfiguration;
	case FRAME_CONFIGURATION1 : return &HMI_Setup1::GetInstance().FConfiguration1;
    case FRAME_PREFERENCE :    return &FPreference;
    case FRAME_MAINTENANCE :   return &FMaintenance;
    case FRAME_HISTO_ANOMALIE : return &FHistoAno;
    case FRAME_VOLTAGE_CHECK : return &FVoltControl;
    case FRAME_GRAPH :         return &FGraph;
    case FRAME_CONFIG_GRAPH:   return &FGraphConfig;
    case FRAME_BATTERIE:       return &FBatteryMenu;
    case FRAME_USB:            return &FUsb;
    case FRAME_TENDANCE:       return &FTendance;
    case FRAME_CIRCUIT_CHECK:  return &FCircuitCheck;
    default :
        break;
    }
    return NULL;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut du test maximal du blower														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::StartBlowerBurnTest()
{
    /*%C Affichage de la valeur de PWM */
    LOVPwmBlower.StartMonitoringMode();
    LOVPwmBlower.RefreshEnable(TRUE);

    // Consigne de vitesse turbine maximum
    const UWORD16 MAX_SPEED_BLOWER = 50000;

    /*%c Demmarage  de la turbine */
    UWORD16 Value = MAX_SPEED_BLOWER;
    DataBaseAccess::WriteValue(&Value, CALIB_ADJUST_CMD_U16 , CONTROL);

    /*%c O2 Valve Open during this test only */ 
    Value = 1; 
    DataBaseAccess::WriteValue(&Value, VALVE_O2_CMD_U16 , CONTROL);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C FIn du test maximal du blower															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::StopBlowerBurnTest()
{
    /*%C Arret de la turbine */
    UWORD16 Value = 0;
    DataBaseAccess::WriteValue(&Value, CALIB_ADJUST_CMD_U16 , CONTROL);

    /*%c O2 Valve CLose after this test */ 
    DataBaseAccess::WriteValue(&Value, VALVE_O2_CMD_U16 , CONTROL);

    /*%C Arret du refresh de PWD */
    LOVPwmBlower.RefreshEnable(FALSE);
}

//*****************************************************************************
//                         Functional description
//                  
//   Start the Circuit Leak Test
//                     
//   Input Parameter : 
//   	  	NONE			
//    Input/Output : 	
//   		NONE			
//   Output Parameter : 
//   		NONE		
//*****************************************************************************
void Controller::StartCircuitLeakTest()
{
    if (LeakTestRunning)
    {
        AbortCircuitLeakTest();
    }
    else
    {
        LeakTestRunning = TRUE;
        FCircuitCheck.HideInstructions();

        LeakTestTimerCount = 0;

        UWORD16 Value = BIP_SHORT;
        DataBaseAccess::WriteValue( &Value,
                                    VALIDATION_BIP_U16,
                                    CONTROL);

        Timer.StartTimer(TIME_LEAK_TEST, TimerLeakTest, FALSE);

        // RPM value to generate approximately 30 mbar 
        const UWORD16 BLOWER_SPEED_RPM = 30000;

        // command the turbine
        Value = BLOWER_SPEED_RPM;
        DataBaseAccess::WriteValue(&Value, CALIB_ADJUST_CMD_U16, CONTROL);

        // close the exhalation valve
        Value = NO_CALIB; 
        DataBaseAccess::WriteValue(&Value, CALIB_FAS_VALVE_REQ_U16, CONTROL);

        Value = 1; 
        DataBaseAccess::WriteValue(&Value, CALIB_PATIENT_PRESS_REQ_U16, CONTROL);

        Value = TEST_STATE_RUNNING;
        DataBaseAccess::WriteValue(&Value, LEAK_TEST_RESULT_U16, COMPUTE);
    }

    FCircuitCheck.Refresh();
}
//*****************************************************************************
//                         Functional description 
//                                               
//   Stop the Circuit Leak Test
//                             
//   Input Parameter : 			
//   	  	NONE			
//   Input/Output : 	
//   		NONE		
//   Output Parameter : 
//   		NONE		
//*****************************************************************************
void Controller::StopCircuitLeakTest()
{
    // stop the turbine
    UWORD16 Value = 0;
    DataBaseAccess::WriteValue(&Value, CALIB_ADJUST_CMD_U16, CONTROL);

    // open the exhalation valve
    Value = NO_CALIB; 
    DataBaseAccess::WriteValue(&Value, CALIB_FAS_VALVE_REQ_U16, CONTROL);

    Value = NO_CALIB; 
    DataBaseAccess::WriteValue(&Value, CALIB_PATIENT_PRESS_REQ_U16, CONTROL);

    LeakTestRunning = FALSE;
    FCircuitCheck.Show();
}
//*****************************************************************************
//                         Functional description 
//                                               
//   Stop the Circuit Leak Test
//                             
//   Input Parameter : 			
//   	  	NONE			
//   Input/Output : 	
//   		NONE		
//   Output Parameter : 
//   		NONE		
//*****************************************************************************
void Controller::AbortCircuitLeakTest()
{
    if (LeakTestRunning == TRUE)
    {
        StopCircuitLeakTest();

        UWORD16 TestResult = TEST_STATE_ABORTED;
        DataBaseAccess::WriteValue(&TestResult, LEAK_TEST_RESULT_U16, COMPUTE);

        FCircuitCheck.Refresh();
    }
}
//*****************************************************************************
//                         Functional description 
//                                               
//   Leak Test Timer Callback
//                             
//   Input Parameter : 			
//   	  	NONE			
//   Input/Output : 	
//   		NONE		
//   Output Parameter : 
//   		NONE		
//*****************************************************************************
void Controller::CircuitLeakTestTimerCallback()
{
    if (LeakTestRunning == TRUE)
    {
        // read the filtered flow and store it as the leak test result
        UWORD16 Value;
        UWORD16 FilterQi;
        DataBaseAccess::ReadValue(&FilterQi, FILTER_QI_S16, COMPUTE);

        // clip negative flows, not of clinical utility
        if ((SWORD16)FilterQi < 0)
        {
            FilterQi = 0;
        }
        DataBaseAccess::WriteValue(&FilterQi, LEAK_TEST_QI_S16, COMPUTE);

        LeakTestTimerCount++;

        if (LeakTestTimerCount < 5)
        {
            // short beep for intermediate results
            Value = BIP_SHORT;
            DataBaseAccess::WriteValue( &Value,
                                        VALIDATION_BIP_U16,
                                        CONTROL);
            // restart the timer
            Timer.StartTimer(TIME_LEAK_TEST, TimerLeakTest, FALSE);
        }
        else
        {
            // long beep to end test
            Value = BIP_LONG;
            DataBaseAccess::WriteValue( &Value,
                                        VALIDATION_BIP_U16,
                                        CONTROL);
            UWORD16 TestResult;

            if ((SWORD16)FilterQi > 10)
            {
                TestResult = TEST_STATE_FAIL;
            }
            else
            {
                TestResult = TEST_STATE_PASS;
            }
            DataBaseAccess::WriteValue(&TestResult, LEAK_TEST_RESULT_U16, COMPUTE);

            StopCircuitLeakTest();
        }

        FCircuitCheck.Refresh();
    }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne une instance d'un noeud										 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	index : numero du noeud													 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
MenuControlNode* Controller::GetNodeAt(UWORD16 _index)
{
    if (_index>NB_NODE)
    {
        return NULL;
    }
    else
    {
        return &this->ArrayNode[_index];
    }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Pas d'action																 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::NoAction()
{
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet le deplacement vers le bas									 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::MoveDown()
{
    /*%C debut du timer sur le changement de Mode si actif */
    if (IsModeChange())
    {
        Timer.StartTimer(TIME_STOP_MODIF_MODE,TimerStopModifMode,FALSE);
    }
    MoveToOtherNode(eGoDown);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet le deplacement vers le haut									 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::MoveUp()
{
    /*%C debut du timer sur le changement de Mode si actif */
    if (IsModeChange())
    {
        Timer.StartTimer(TIME_STOP_MODIF_MODE,TimerStopModifMode,FALSE);
    }
    MoveToOtherNode(eGoUp);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet la modification de valeur vers le bas						 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ModifyDown()
{
    /*%C lancement du timer du Noeud */
    Timer.StartTimer(TIME_OUT_MODIF_EVENT,TimeOutModifEvent,FALSE);

    /*%C Arret du blink */
    BTable.RemoveElement(CurrentNode->GetObject());
    Timer.StartTimer(TIME_ADD_TO_BLINK_EVENT,TimerAddToBlinkEvent,FALSE);

    /*%C Traitement de la valeur */
    CurrentNode->GetObject()->DecreaseValue();

    /* Traitement des affichages d'interdépendance */
    SettingBlockDetect();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet la modification de valeur vers le haut					 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ModifyUp()
{
    /*%C lancement du timer du Noeud */
    Timer.StartTimer(TIME_OUT_MODIF_EVENT,TimeOutModifEvent,FALSE);

    /*%C Arret du blink */
    BTable.RemoveElement(CurrentNode->GetObject());
    Timer.StartTimer(TIME_ADD_TO_BLINK_EVENT,TimerAddToBlinkEvent,FALSE);

    /*%C Traitement de la valeur */
    CurrentNode->GetObject()->IncreaseValue();

    /* Traitement des affichages d'interdépendance */
    SettingBlockDetect();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet la modification de valeur vers le bas	avec refresh de la vitesse */
/*%C  Turbine                                                                 */
/*%C                                                                          */
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ModifyDownRefreshBlower()
{
    if (LOVPwmBlower.IsStopMonitoring() == TRUE)
    {
        LOVPwmBlower.StartMonitoringMode();
        LOVPwmBlower.RefreshEnable(TRUE);
    }

    ModifyDown();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet la modification de valeur vers le haut avec refresh de la vitesse*/
/*%C  Turbine                                                                 */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ModifyUpRefreshBlower()
{
    if (LOVPwmBlower.IsStopMonitoring() == TRUE)
    {
        LOVPwmBlower.StartMonitoringMode();
        LOVPwmBlower.RefreshEnable(TRUE);
    }

    ModifyUp();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet de traiter un deplacement sur valid						 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::MoveValid()
{
    /*%C Permet le deplacement la validation */
    MoveToOtherNode(eGoValid);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet de traiter un deplacement sur monit						 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::MoveMonitor()
{
    /*%C Permet le deplacement par Monitor */
    MoveToOtherNode(eGoMonitor);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet de se deplacer vers le prochain noeud	valide			 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	way : sens de deplacement												 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::MoveToOtherNode(WayId _way)
{
    MenuControlNode* PtrNode = GetCurrentNode();
    MenuControlNode* PtrNodeTarget=0;

    /*%C recherche du noeud suivant valide si il existe */
    switch (_way)
    {
    case eGoValid   : PtrNodeTarget = GetNodeAt(    PtrNode->
                                                    GetEventNode()->
                                                    GetIdNodeOnValid());

        PtrNodeTarget = FindFirstValidNode( PtrNodeTarget,
                                            eGoDown);
        break;

    case eGoMonitor : PtrNodeTarget = GetNodeAt(    PtrNode->
                                                    GetEventNode()->
                                                    GetIdNodeOnMonitor());

        PtrNodeTarget = FindFirstValidNode( PtrNodeTarget,
                                            eGoDown);
        break;

    case eGoUp      :

    case eGoDown    : PtrNodeTarget = GetNextValidNode(PtrNode,_way);
        break;
    default :
        break;
    }

    /*%C Verifie si le noeud d'arrivée est valide */
    if (!PtrNodeTarget->IsValid())
    {
        PtrNodeTarget = PtrNode;
    }

    /*%C arrive sur le noeud suivant */
    MoveCurrentNode(PtrNodeTarget);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet de trouver le prochain noeud valide, si la recherche suivant		*/
/*%C 		le sens initial est vide, on recherche suivant le sens oppose  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	StartNode : noeud de depart inclu dans la recherche			      	*/
/*%I		Beginway  : sens de deplacement 								         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		noeud valide									  							  			*/
/******************************************************************************/
MenuControlNode* Controller::FindFirstValidNode(MenuControlNode* _StartNode,
                                                WayId _Beginway)
{
    MenuControlNode *NextValidNode;

    if (_StartNode->IsValid())
    {
        return _StartNode;
    }
    NextValidNode = GetNextValidNode(_StartNode,_Beginway);
    if (NextValidNode == _StartNode)
    {
        /*%C recherche infructueuse, on cherche dans l'autre sens */
        WayId Way = eGoUp;
        if (Way == _Beginway)
        {
            Way = eGoDown;
        }
        NextValidNode = GetNextValidNode(_StartNode,Way);
    }
    return NextValidNode;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet de trouver le prochain noeud valide suivant un sens unique			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	StartNode : noeud de depart inclu dans la recherche			      	*/
/*%I		Beginway  : sens de deplacement 								         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		noeud valide									  							  			*/
/******************************************************************************/
MenuControlNode* Controller::GetNextValidNode(  MenuControlNode* _StartNode,
                                                WayId _way)
{
    typedef UWORD16 (EventNode::* PtrFunct)(void) const;

    PtrFunct MoveFunction;

    MenuControlNode *NextValidNode, *CurrentNode, *NextNode;

    e_BOOL Stop = FALSE;

    /*%C initialisation de la fonction de deplacement */
    switch (_way)
    {
    case eGoUp     :    MoveFunction = &EventNode::GetIdNodeOnUp;
        break;

    case eGoDown   :    MoveFunction = &EventNode::GetIdNodeOnDown;
        break;

    default         :   MoveFunction = &EventNode::GetIdNodeOnUp;
        break;
    }

    /*%C recherche du pointeur suivant */
    NextValidNode = _StartNode;
    CurrentNode = _StartNode;
    NextNode = GetNodeAt((CurrentNode->GetEventNode()->*(MoveFunction))());

    do
    {
        /*%C On avance d'un noeud */
        CurrentNode = NextNode;
        NextNode = GetNodeAt((CurrentNode->GetEventNode()->*(MoveFunction))());

        /*%C On teste */
        if (CurrentNode->IsValid())
        {
            NextValidNode = CurrentNode;
            Stop = TRUE;
        }
    }
    while ((_StartNode != NextNode) && !Stop);

    return NextValidNode;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Affichage d'une fenetre													 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	FrameId : numero de la fenetre										 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ShowFrame(UWORD16 _NewFrameId)
{
    UWORD16 Val1, Val2;

    /*%C Gestion des pages video */
    VFrame *Frame = GetFrameObject(_NewFrameId);

    if (Frame == NULL)
        return;

    if (
       (Frame->GetPage() == VIRTUAL_PAGE && _NewFrameId != FRAME_GRAPH) ||
       ((_NewFrameId == FRAME_GRAPH) && (CurrentVirtualFrame != FRAME_GRAPH))
       )
    {
        /*%C Bloque l'affichage de FGraph */
        FGraph.Hide();

        /*%C Effacement de la page; */
        InterfaceCppC::ErazePage(VIRTUAL_PAGE);
    }
    InterfaceCppC::DisplayPage(Frame->GetPage());

    /*%C Prise en charge du refresh */
    RTable.ResetTable();

    /*%C Changement de page */
    switch (_NewFrameId)
    {
    case FRAME_WELCOME :
        FWelcome.Show();
        RTable.SetTable(FWelcome.GetRefreshTable());
        break;

    case FRAME_VENTILATION :
        RTable.SetTable(FVentilation.GetRefreshTable());
        RTable.MakeRefreshInsp();
        RTable.MakeRefreshExp();
        /*%C Si on vient de Histo Alarm */
        /*%C Fin du timer de la page histo alarmes */
        this->Timer.StopTimer(TimerQuitHistoAlarme);
        /*%C Si on vient de Préférence */
        /*%C Fin du timer de la page préférences */
        this->Timer.StopTimer(TimerQuitPreferences);
        break;

    case FRAME_ALARME :
        RTable.SetTable(RefreshTableAlarm);
        RTable.SetTable(FAlarme.GetRefreshTable());
        RTable.MakeRefreshInsp();
        RTable.MakeRefreshExp();
        if (!this->IsModeChange())
            LHistoAlarm.Show();
        break;

    case FRAME_HISTO_ALARME :
        ManageHistoAlarmSeek();
        FHistoAlarme.Show();
        ShowMenu(NodeHistAlBack);
        RTable.SetTable(FHistoAlarme.GetRefreshTable());
        break;

    case FRAME_CIRCUIT_CHECK :
        FCircuitCheck.Show();
        ShowMenu(NodeTestCircuitLeak);
        RTable.SetTable(FCircuitCheck.GetRefreshTable());
        break;

    case FRAME_CONFIGURATION :
        FConfiguration.Show();
        ShowMenu(NodeConfLang);
        RTable.SetTable(RefreshTableConfig);
        RTable.SetTable(FConfiguration.GetRefreshTable());
        break;
    case FRAME_CONFIGURATION1 :
        HMI_Setup1::GetInstance().FConfiguration1.Show();
		ShowMenu(NodeConfModeCycl);
		RTable.SetTable(HMI_Setup1::GetInstance().FConfiguration1.GetRefreshTable());
		break;
    case FRAME_PREFERENCE :
        FPreference.Show();
        ShowMenu(NodePrefScreenSave);
        RTable.SetTable(FPreference.GetRefreshTable());
        break;

    case FRAME_MAINTENANCE :
        FMaintenance.Show();
        ShowMenu(NodeMaintHistAno);
        ShowMaintCalib();
        Fio2MonitorEnabled(IsFio2Sensor());
        RTable.SetTable(RefreshTableMaintenance);
        RTable.SetTable(FMaintenance.GetRefreshTable());
        break;

    case FRAME_HISTO_ANOMALIE :
        ManageHistoAnoSeek();
        FHistoAno.Show();
        ShowMenu(NodeHistAnoBackMaint);
        RTable.SetTable(FHistoAno.GetRefreshTable());
        break;

    case FRAME_VOLTAGE_CHECK :
        FVoltControl.Show();
        LRMaintTension.Show();
        LOVBuzzerVoltage.Show();
        LBackupBuzzer.Show();
        LBatteryMenu.Show();
        ShowMenu(NodeSupplyBuzVolt);
        LOVTempBat.Show();
        LOVBuzzSec.Show();
        RTable.SetTable(RefreshTableVolt);
        RTable.SetTable(FVoltControl.GetRefreshTable());
        break;

    case FRAME_GRAPH :
        if (CurrentVirtualFrame != FRAME_GRAPH)
        {
            FGraph.Show();
        }
        else
        {
            /*%C Rafraichit l'affichage sur changement de */
            /*%C mode et switch de page */
            FGraph.RefreshMode();
        }
        RTable.SetTable(FGraph.GetRefreshTable());
        RTable.MakeRefreshInsp();
        RTable.MakeRefreshExp();
        break;

    case FRAME_CONFIG_GRAPH:
        FGraphConfig.Show();
        ShowMenu(NodeCfgGraphVisu);
        RTable.SetTable(FGraphConfig.GetRefreshTable());
        break;

    case FRAME_BATTERIE:
        FBatteryMenu.Show();
        LRMaintBattery.Show();
        ShowMenu(NodeBatteryBackToMaint);
        RTable.SetTable(FBatteryMenu.GetRefreshTable());
        break;

    case FRAME_USB:
        Val1 = TRUE;
        Val2 = TRUE;
        DataBaseAccess::WriteValue(&Val1,USB_KEY1_DETECTED_AFTER_POWER_ON_U16,USB);
        DataBaseAccess::WriteValue(&Val2,USB_KEY2_DETECTED_AFTER_POWER_ON_U16,USB);
        FUsb.Show();
        ShowMenu(cUsbStartNode);
        if (!IsUsbCmdInProgress())
            GetNodeAt(NodeUsbStop)->SetVisible(FALSE);
        RTable.SetTable(FUsb.GetRefreshTable());
        break;

    case FRAME_TENDANCE:
        FTendance.Show();
        ShowMenu(NodeTrendBack);
        RTable.SetTable(FTendance.GetRefreshTable());
        break;
    default :
        break;                        
    }

    /*%C Gestion des alarmes */
    switch (_NewFrameId)
    {
    case FRAME_VENTILATION :
    case FRAME_ALARME :
    case FRAME_PREFERENCE :
    case FRAME_GRAPH :
    case FRAME_CONFIG_GRAPH:
        Timer.StartTimer(   TIME_SWAP_ALARM,
                            TimerSwapAlarm,
                            TRUE);
        break;

    case FRAME_HISTO_ALARME :
        break;

    default         :
        if (_NewFrameId != 999)
        {
            Timer.StopTimer(TimerSwapAlarm);
            ShowAlarm(FALSE,0,0);
        }
        break;
    }


    /*%C Gestion de la recherche d'Historique Alarme, arret si */
    /*%C changement de page */
    if (_NewFrameId == FRAME_ALARME)
    {
        Timer.StopTimer(TimerHistoAlarmSeek);
    }
    /*%C Gestion de la recherche d'Historique Anomalie, arret si */
    /*%Cchangement de page */
    if (_NewFrameId == FRAME_MAINTENANCE)
    {
        Timer.StopTimer(TimerHistoAnoSeek);
    }

    if (Frame->GetPage() == VIRTUAL_PAGE)
        CurrentVirtualFrame = _NewFrameId;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Traitement des evenements(touches, timer...)						 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	event : evenement a traiter											 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ManageSpyEvent(EventId _Spy)
{
    Controller *Cont;


    Cont = Controller::GetInstance();

    /*%C Traitement de l'evenement */
    switch (_Spy)
    {
    //------------- Program Event -------------
    

    case ProgInspControlEvent:
        Cont->RTable.MakeRefreshInsp();
        break;

    case ProgInspTrigEvent  :
        Cont->ManageTrigger(_Spy);
        Cont->RTable.MakeRefreshInsp();
        break;

    case ProgExhEvent         :
        Cont->ManageTrigger(_Spy);
        Cont->RTable.MakeRefreshExp();
        break;

    case ProgHideBatEvent   :
        Cont->ShowBattery(FALSE);
        Cont->ShowTempBattery(TRUE);
        break;

    case ProgShowBatEvent   :
        Cont->ShowBattery(TRUE);
        Cont->ShowTempBattery(FALSE);
        break;

    case ProgStartVentilOk  :
        /*%C demarrage de la ventil */
        Cont->ManageLegendState(eStartVentil);
        /*%C Mise à jour affichage Valve */
        Cont->SendInfoValve(Cont->ValveDetected);
        break;

    case ProgStartVentilKo  :
        /*%C Mise à jour affichage Valve */
        Cont->SendInfoValve(Cont->ValveDetected);
        break;

    case ProgInibAlarmOK    :
        Cont->FVentilation.SetInibOk(TRUE, (e_BOOL) !Cont->IsModeChange());
        Cont->FAlarme.SetInibOk(TRUE, (e_BOOL)!Cont->IsModeChange());
        Cont->FGraph.IsInibAlarmVisible();
        break;

    case ProgInibAlarmNOK :
        Cont->FVentilation.SetInibOk(FALSE, (e_BOOL)!Cont->IsModeChange());
        Cont->FAlarme.SetInibOk(FALSE, (e_BOOL)!Cont->IsModeChange());
        Cont->FGraph.IsInibAlarmVisible();
        break;

    case ProgCancelAlarmOK :
        Cont->FVentilation.SetCancelOk(TRUE, (e_BOOL) !Cont->IsModeChange());
        Cont->FAlarme.SetCancelOk(TRUE, (e_BOOL) !Cont->IsModeChange());
        Cont->FGraph.IsCancelAlarmVisible();
        break;

    case ProgCancelAlarmNOK :
        Cont->FVentilation.SetCancelOk(FALSE, (e_BOOL) !Cont->IsModeChange());
        Cont->FAlarme.SetCancelOk(FALSE, (e_BOOL) !Cont->IsModeChange());
        Cont->FGraph.IsCancelAlarmVisible();
        break;

    case ProgValveMissing   :
        Cont->SendInfoValve(FALSE);
        break;

    case ProgValveDetected :
        Cont->SendInfoValve(TRUE);
        break;

    case ProgBlocExpiMissing :
        Cont->SendInfoBlocExpi(FALSE);
        break;

    case ProgBlocExpiDetected :
        Cont->SendInfoBlocExpi(TRUE);
        break;

    case ProgFio2SensorOK  :
        //									   if(Cont->IsVentilOn())
        {
            Cont->SendInfoFio2Sensor(TRUE);
        }
        break;

    case ProgFio2SensorNOK  :
        Cont->SendInfoFio2Sensor(FALSE);
        break;

    case ProgSpo2SensorNoError:
        if (Cont->IsVentilOn())
        {
            Cont->SendInfoSpo2Sensor(TRUE);
        }
        break;

    case ProgSpo2SensorError:
        Cont->SendInfoSpo2Sensor(FALSE);
        break;

    case ProgCheckSupplyNoError:
        Cont->SendInfoBadSupplyCheck(FALSE);
        break;

    case ProgCheckSupplyError:
        Cont->SendInfoBadSupplyCheck(TRUE);
        break;

    case ProgUsbErrorCodeReady:
        Cont->SendInfoUsbErrorCodeReady(TRUE);
        break;

    case ProgUsbNewModeDetected:
        Cont->UpdateMode();
        break;

    case ProgRemoveHighPressureAlarm  :
        UWORD16 Val;
        AlarmEvent* HighPressAlarmPtr;
        HighPressAlarmPtr = Cont->ATable.GetAlarmFromId((UWORD16)ALARM_HIGH_PRESSURE_U16);
        if (HighPressAlarmPtr)
        {
            Cont->SetHighPressAlarmToBeRemoved(TRUE);
            DataBaseAccess::ReadValue(&Val,ALARM_HIGH_PRESSURE_U16,ALARMS);
            AlarmEvent HighPressAlarm;
            HighPressAlarm.id = HighPressAlarmPtr->id;
            HighPressAlarm.action = HighPressAlarmPtr->action;
            HighPressAlarm.day = HighPressAlarmPtr->day;
            HighPressAlarm.month = HighPressAlarmPtr->month;
            HighPressAlarm.year = HighPressAlarmPtr->year;
            HighPressAlarm.hour = HighPressAlarmPtr->hour;
            HighPressAlarm.min = HighPressAlarmPtr->min;
            Cont->AlarmDetect(FALSE,&HighPressAlarm);
            Cont->SetHighPressAlarmToBeRemoved(FALSE);
        }
        break;

    case ProgStartMonitoring :
        /* If we are currently modifying a setting or pressing the vent button
         so we differ monitoring start */
        if (Cont->IsModifNodeOn() || Cont->IsVentButtonOn())
            Cont->SetDifferMonitoring(TRUE);
        else
            Cont->SetDifferMonitoring(FALSE);

        Cont->SetMonitoringMode(TRUE);
        break;

    case ProgSupplyBusFailure :
        Cont->SetSupplyBusFailure(TRUE);
        break;
    case ProgSupplyBusOK :
        Cont->SetSupplyBusFailure(FALSE);
        break;
    case ProgExhalFlowUsed :
        Cont->SetExhalFlowUsed(TRUE);
        break;
    case ProgExhalFlowUnused :
        Cont->SetExhalFlowUsed(FALSE);
        break;

    default :
        break;
    }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Traitement des evenements timer										 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	event : Timer a traiter											 					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ManageTimerEvent(UWORD16 _Timer)
{
    Controller *Cont;

    Cont = Controller::GetInstance();

    /*%C Traitement de l'evenement */
    switch (_Timer)
    {
    //------------- Timer Event ---------------
    case TimerTriggerOk              :  Cont->ManageTrigger(_Timer); break;
    case TimerBlinkEvent             :  Cont->BTable.Blink();break;
    case TimeOutModifEvent           :  (Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnTimeOut))(); break;
    case TimerRefresh                :  Cont->RTable.MakeRefresh();
        Cont->BuzzerVoltRefresh();
        break;
    case TimerAddToBlinkEvent        :  Cont->BTable.AddElement(Cont->GetCurrentNode()->GetObject());break;
    case TimerWelcomeEvent           :  Cont->ManageLegendState(eOnWait);break;
    case TimerSpyPraram              :  Cont->PSpy.Refresh(); break;
    case TimerStopModifMode          :  Cont->StopModifMode(Cont->GetCurrentMode());break;
    case TimerAutoCalibTest          :  Cont->VerifAndManageCalibAuto();break;
    case TimerRefreshAlarm           :  Cont->AManager.CallRefresh();
        if (Cont->AManager.IsDoubleAlarmActive())
        {
            if (!Cont->IsDoubleMessageTimerStarted)
            {
                Cont->IsDoubleMessageTimerStarted = TRUE;
                Cont->Timer.StartTimer(TIME_DOUBLE_MESSAGE, TimerDoubleAlarm, FALSE);
            }
        }
        else
        {
            Cont->IsDoubleMessageTimerStarted = FALSE;
            Cont->Timer.StopTimer(TimerDoubleAlarm);
            Cont->RemoveDoubleMessage();
        }
        break;
    case TimerDoubleAlarm            :  Cont->InsertDoubleMessage();
        break;
    case TimerSwapAlarm              :  Cont->ATable.Refresh(); break;
    case TimerQuitHistoAlarme        :  if (Cont->GetCurrentFrame() == FRAME_HISTO_ALARME) (Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnTimeOut))();break;
    case TimerQuitPreferences        :  if (Cont->GetCurrentFrame() == FRAME_PREFERENCE) (Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnTimeOut))();break;
    case TimerQuitGraphConfig        :  if (Cont->GetCurrentFrame() == FRAME_CONFIG_GRAPH) (Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnTimeOut))();break;
    case TimerQuitVentilReport       :  if (Cont->GetCurrentFrame() == FRAME_TENDANCE) (Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnTimeOut))();break;
    case TimerHistoAlarmSeek           :  Cont->ManageHistoAlarmSeek();break;
    case TimerHistoAnoSeek             :  Cont->ManageHistoAnoSeek();break;
    case TimerWaitCalibVerif         :  Cont->ManageVerifPointCalib(NULL); break;
    case TimerWaitCalibQExp             :  Cont->MoveToCalibAuto(); break;
    case TimerWaitCalibFiO2             :  Cont->MoveToCalibAutoFiO2(); break;      
    case TimerHideStopVentMess       :  if (Cont->IsVentilOn())
        {
            // switch from the STOP VENT message to monitored data
            Cont->HideMessageFrame();
            /*%C Affichage du monitoring */
            Cont->FVentilation.ShowMonitoring();
            Cont->FAlarme.ShowMonitoring();
            break;
        }
        break;

    case TimerHideAlarmMessage       :  // clear the alarm message
        Cont->FVentilation.ShowCurrentAlarme(FALSE, 0);
        Cont->FAlarme.ShowCurrentAlarme(FALSE, 0);
        break;

    case TimerHideLoupe              :  /*%C reaffiche le message de lancement de la ventil */
        if (!Cont->IsVentilOn())
        {
            Cont->ShowMessageFrame(TRUE,(UBYTE*)cMSG_StartVentil[Cont->GetLanguage()],VENTIL);
        }
        else
        {
            /*%C reaffiche le monitoring */
            Cont->FAlarme.ShowMonitoring();
            Cont->FVentilation.ShowMonitoring();
        }
        break;
    case TimerUsbMessage             :  Cont->UsbDelayed.TimerHandler((e_BOOL)(Cont->GetCurrentFrame() == FRAME_USB));
        break;
    case TimerUsbProcessing          :  Cont->FUsb.AnimateProcessingDots((e_BOOL)(Cont->GetCurrentFrame() == FRAME_USB));
        break;
    case Timer100PrCentO2            :  Cont->Stop100FiO2();
        break;
    case TimerEndLongDownKey         :  Cont->SetLongDownKeyDetected(FALSE);
        Cont->DecreaseBlowerStep();
        break;
    case TimerEndLongUpKey         :    Cont->SetLongUpKeyDetected(FALSE);
        Cont->DecreaseBlowerStep();      
        break;
    case TimerLeakTest               :  Cont->CircuitLeakTestTimerCallback();
        break;

    default :
        break;
    }
#ifdef _BORLAND
    Controller::ProtoManageTimerEvent(_Timer);
#endif
}
#ifdef _BORLAND
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Traitement des evenements timer coté prototype             	 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	_Timer : evenement Timer à traiter											   */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ProtoManageTimerEvent(UWORD16 _Timer)
{
    _Timer = _Timer;  /* to avoid warning */

    #ifdef PROTO_CFG_WANT_RECORDER
    EventRecorder* EvtRecorder = EventRecorder::GetInstance();

    switch (_Timer)
    {
    case TimerHideAlarmMessage:
    case TimerHideStopVentMess:
    case TimerHideLoupe:
    case TimerBlinkEvent :
        /* Pas d'enregistrement d'évenement pour ces timers !*/
        break;

    default:
        TEvent Evt;
        Evt.Type = EVT_TYPE_TIMER;
        Evt.Params[EVT_PARAM_0] = _Timer;
        EvtRecorder->AddEvent(&Evt);
        break;
    }
    #endif /* PROTO_CFG_WANT_RECORDER */
}
#endif /* _BORLAND */

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Traitement des evenements touches									 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	event : evenement Keyboard à traiter											*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ManageKeyboardEvent(UWORD16 _Key)
{
    UWORD16 CFrame;
    Controller *Cont;
    UWORD16 val = 0;
    val = val; /* to avoid warning */

    Cont = Controller::GetInstance();

    UWORD16 Id = Cont->GetCurrentNode()->GetEventNode()->GetId();

    if (    (Id == NodeMaintHistAno) &&
            (Cont->EraseFlag == true) &&
            (DRV_EVENT_TransStateFlash() == DRV_EVENT_FREE))
    {
        Cont->EraseFlag = false;
    }

    if (Cont->EraseFlag == true) return;

    /*%C Traitement de l'evenement */
    switch (_Key)
    {
    //------------- Key Event -----------------
    case KEYBOARD_UP_EVENT_U16:

        (Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnButtonUp))();
        if (Cont->GetLongUpKeyDetected())
        {
            /* Restart Long Down Timer */
            Cont->Timer.StartTimer(TIME_END_LONG_UP_KEY,TimerEndLongUpKey,FALSE);
        }

        break;

    case KEYBOARD_DOWN_EVENT_U16:
        (Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnButtonDown))();
        if (Cont->GetLongDownKeyDetected())
        {
            /* Restart Long Down Timer */
            Cont->Timer.StartTimer(TIME_END_LONG_DOWN_KEY,TimerEndLongDownKey,FALSE);
        }
        break;

    case KEYBOARD_LONG_DOWN_EVENT_U16:
        Cont->GoToTopBottomFrame(Cont->GetCurrentFrame(),eGoDown);
        Cont->SetLongDownKeyDetected(TRUE);
        Cont->IncreaseBlowerStep();
        break;

    case KEYBOARD_LONG_UP_EVENT_U16:
        Cont->GoToTopBottomFrame(Cont->GetCurrentFrame(),eGoUp);
        Cont->SetLongUpKeyDetected(TRUE);
        Cont->IncreaseBlowerStep();
        break;

    case KEYBOARD_VALID_EVENT_U16:
        (Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnButtonValid))();
        break;

    case KEYBOARD_IT_GEN_EVENT_U16:
        Cont->ManageLegendState(eOnStart);
        break;

    case KEYBOARD_IT_OFF_EVENT_U16:
        break;

    case KEYBOARD_LONG_INHIB_EVENT_U16:
        Cont->ManageInhibKey(TRUE);
        break;

    case KEYBOARD_INHIB_EVENT_U16:
        Cont->ManageInhibKey(FALSE);
        break;

    case KEYBOARD_LONG_VALID_EVENT_U16:
        (Cont->*(Cont->GetCurrentNode()->
                 GetEventNode()->
                 OnButtonLongValid))();
        break;

    case KEYBOARD_CONFIRM_STOP_VENTIL_EVENT_U16:
        Cont->SetVentButtonOn(TRUE); 
        CFrame = Cont->GetCurrentFrame();
        /*%C Stop timer TimeOut */
        Cont->Timer.StopTimer(TimeOutModifEvent);
        /*%C Stop the parameter setting */
        (Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnTimeOut))();
        if ( (CFrame == FRAME_HISTO_ALARME) ||
             (CFrame == FRAME_PREFERENCE) ||
             (CFrame == FRAME_USB) ||
             (CFrame == FRAME_GRAPH))
        {
            Cont->SetCurrentFrame(FRAME_VENTILATION);
            Cont->MoveCurrentNode(  Cont->
                                    FindFirstValidNode(Cont->
                                                       GetNodeAt(NodeVentil),
                                                       eGoDown));

            CFrame = Cont->GetCurrentFrame();
        }

        if ( (CFrame == FRAME_VENTILATION) ||
             (CFrame == FRAME_ALARME))
        {
            // display the "press button again to confirm stop" message
            Cont->ShowMessageFrame(TRUE,(UBYTE*)cMSG_StopConfirmVentil[Cont->GetLanguage()],VENTIL);
        }
        // stop the timer that clears the "press start for 3 sec" message
        Cont->Timer.StopTimer(TimerHideStopVentMess);
        break;

    case KEYBOARD_STOP_VENTIL_EVENT_U16:
        Cont->SetVentButtonOn(FALSE); 
        Cont->SetDifferMonitoring(FALSE); 
        /*%C Stop timer TimeOut */
        Cont->Timer.StopTimer(TimeOutModifEvent);
        /*%C Stop the parameter setting */
        (Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnTimeOut))();
        CFrame = Cont->GetCurrentFrame();
        if ( (CFrame == FRAME_HISTO_ALARME) ||
             (CFrame == FRAME_PREFERENCE) ||
             (CFrame == FRAME_GRAPH))
        {
            Cont->SetCurrentFrame(FRAME_VENTILATION);
            Cont->MoveCurrentNode(  Cont->
                                    FindFirstValidNode(Cont->
                                                       GetNodeAt(NodeVentil),
                                                       eGoDown));

            CFrame = Cont->GetCurrentFrame();
        }

        if ( (CFrame == FRAME_VENTILATION) ||
             (CFrame == FRAME_ALARME))
        {
            Cont->ManageLegendState(eStopVentil);
        }
        break;

    case KEYBOARD_NAVIG_IT_GEN_EVENT_U16:
        Cont->ManageLegendState(eOnWait);
        Cont->SetCurrentFrame(FRAME_CIRCUIT_CHECK);
        Cont->MoveCurrentNode(  Cont->
                                FindFirstValidNode(
                                                  Cont->
                                                  GetNodeAt(NodeTestCircuitLeak),
                                                  eGoDown));
        break;

    case KEYBOARD_INHIB_IT_GEN_EVENT_ARRAY_U16:
        Cont->ManageLegendState(eOnWait);
        Cont->SetCurrentFrame(FRAME_CONFIGURATION);
        Cont->MoveCurrentNode(  Cont->
                                FindFirstValidNode(
                                                  Cont->
                                                  GetNodeAt(NodeConfLang),
                                                  eGoDown));
        break;

    case KEYBOARD_START_VENTIL_DOWN_EVENT_U16:
        /*%C Stop timer TimeOut */
        Cont->Timer.StopTimer(TimeOutModifEvent);
        /*%C Stop the parameter setting */
        (Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnTimeOut))();
        CFrame = Cont->GetCurrentFrame();
        if ((    (CFrame == FRAME_HISTO_ALARME) ||
                 (CFrame == FRAME_PREFERENCE) ||
                 (CFrame == FRAME_GRAPH)) &&
            Cont->IsVentilOn())
        {
            Cont->SetCurrentFrame(FRAME_VENTILATION);
            Cont->MoveCurrentNode(  Cont->
                                    FindFirstValidNode(Cont->
                                                       GetNodeAt(NodeVentil),
                                                       eGoDown));
            CFrame = Cont->GetCurrentFrame();
        }
        if ((    (CFrame == FRAME_VENTILATION) ||
                 (CFrame == FRAME_ALARME)) &&
            Cont->IsVentilOn())
        {
            /*%C Affichage du message d'arret */
            // show the Stop Ventilation message
            Cont->
                ShowMessageFrame(
                                TRUE,
                                (UBYTE*)cMSG_StopVentil[Cont->GetLanguage()],
                                VENTIL);
        }

        /*%C Arret effacement du message d'arret */
        // stop the timer to clear the Stop Ventilation message
        Cont->Timer.StopTimer(TimerHideStopVentMess);
        break;

    case KEYBOARD_START_VENTIL_UP_EVENT_U16:
        /*%C Stop timer TimeOut */
        Cont->Timer.StopTimer(TimeOutModifEvent);
        /*%C Stop the parameter setting */
        (Cont->*(Cont->GetCurrentNode()->GetEventNode()->OnTimeOut))();
        if (Cont->IsVentilOn())
        {
            /*%C Effacement du message de d'arret */
            // start the timer to hide the Stop Ventilation message
            Cont->Timer.StartTimer( TIME_HIDE_STOP_VENT_MESS,
                                    TimerHideStopVentMess,FALSE);
        }
        break;

    case KEYBOARD_LOCK_EVENT_U16 :
        CFrame = Cont->GetCurrentFrame();
        if ((CFrame == FRAME_VENTILATION) || (CFrame == FRAME_ALARME) || (CFrame == FRAME_GRAPH))
        {
            Cont->ManageLock((e_BOOL)(!Cont->IsLockOn()));
        }
        break;

    case KEYBOARD_BRIGHTNESS_UP_EVENT_U16:
        if (!Cont->IsVentilOn())
        {
            Cont->ChangeBrightness(eGoUp);
        }
        break;

    case KEYBOARD_BRIGHTNESS_DOWN_EVENT_U16:
        if (!Cont->IsVentilOn())
        {
            Cont->ChangeBrightness(eGoDown);
        }
        break;

#ifdef HMI_CONFIG_100_FIO2
    case KEYBOARD_100_FIO2 :
        /* Pas de lancement de 100% FiO2 si modif de noeud ou de mode en cours */
        if (!Cont->IsModifNodeOn() && !Cont->IsModeChange() && !Cont->IsLockOn())
        {
            if (Cont->IsVentilOn())
            {
                DataBaseAccess::ReadValue(&val,FIO2_100_ACTIVE,CONTROL);
                if (!val)
                {
                    val = TRUE;
                    Cont->BTable.AddElement(&Cont->LOVFiO2);
                    Cont->LOVFiO2.Set100FiO2();
                    InterfaceCppC::ActiveLed(LED_WHITE, CONTINU_LED);
                    DataBaseAccess::WriteValue(&val,FIO2_100_ACTIVE,CONTROL);
                    Cont->Timer.StartTimer(TIME_100_PR_CENT_O2,Timer100PrCentO2,FALSE);
                }
            }
        }
        break;

    case KEYBOARD_LONG_100_FIO2 :
        /* Arrêt de 100% FiO2 sur appui long de FiO2 */
        DataBaseAccess::ReadValue(&val,FIO2_100_ACTIVE,CONTROL);
        if (val)
            Cont->Stop100FiO2();
        break;
#endif

    case KEYBOARD_NAVIG_EVENT_U16:
        Cont->ChangePages(); break;

    default :
        break;
    }
#ifdef _BORLAND
    Controller::ProtoManageKeyboardEvent(_Key);
#endif

}
#ifdef _BORLAND
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Traitement des evenements touches coté prototype         	 				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	_Key : evenement Keyboard à traiter											   */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::ProtoManageKeyboardEvent(UWORD16 _Key)
{
    _Key = _Key;  /* to avoid warning */

    #ifdef PROTO_CFG_WANT_RECORDER
    EventRecorder* EvtRecorder = EventRecorder::GetInstance();
    Controller* Cont = Controller::GetInstance();
    UWORD16 _CurrentNodeId = Cont->GetCurrentNode()->GetEventNode()->GetId();

    TEvent Evt;
    Evt.Type = EVT_TYPE_CLICK;
    Evt.Params[EVT_PARAM_0] = _Key;
    Evt.Params[EVT_PARAM_1] = _CurrentNodeId;

    EvtRecorder->AddEvent(&Evt);

    #endif /* PROTO_CFG_WANT_RECORDER */
}
#endif /* _BORLAND */
/************************************************************************/
/* Description          : configuration de l'IHM en fonction de l'etat	*/
/*						  de la machine									            */
/* Parametres en entree : 		                                          */
/*		- State : etat de la machine							  	               */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ManageLegendState(LegendState State)
{
    UWORD16 CFrame;

    switch (State)
    {
    case eOnStart : /*%C determination du demarage d'urgence */
        if (!this->IsLastShutDownError())
        {
            this->SetCurrentFrame(FRAME_WELCOME);
            this->Timer.StartTimer(TIME_WELCOME_EVENT,TimerWelcomeEvent,FALSE);
            this->SetLState(eOnStart);
        }
        else
        {
            /*%C Arret anormal, lancement de la ventil */
            this->SetCurrentFrame(FRAME_VENTILATION);
            this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeVt),eGoDown));
            this->SetLState(eOnWait);
        }
        this->SetMonitoringMode(FALSE);
        break;

    case eOnWait :          /*%C positionne en page de ventil */
        if (this->GetCurrentFrame() == FRAME_WELCOME)
        {
            if (this->IsLockOn())
            {
                UWORD16 _FrameId;
                DataBaseAccess::ReadValue(&_FrameId,IHM_LOCKED_FRAME_ID,CONFIG);
                if (_FrameId == FRAME_ALARME)
                    this->MoveCurrentNode(this->GetNodeAt(NodeAlHisto));
                else
                    this->MoveCurrentNode(this->GetNodeAt(NodeGhost));
            }
            else
                this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeVt),eGoDown));
        }
        else
            this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeVt),eGoDown));

        this->ShowMessageFrame(TRUE,(UBYTE*)cMSG_StartVentil[GetLanguage()],VENTIL);
        this->SetMonitoringMode(FALSE);
        this->SetLState(eOnWait);
        /*%C Effacement de la page virtuelle */
        InterfaceCppC::ErazePage(VIRTUAL_PAGE);
        break;

    case eStartVentil:  if (this->GetLState() == eOnStart)
        {
            this->ManageTimerEvent(TimerWelcomeEvent);
        }
        this->Timer.StopTimer(TimerWelcomeEvent);

        /*%C Force l'arret de calibration QExp */
        this->ForceQExpCalibrationStop();
        /*%C Force l'arret de calibration QExp */
        this->ForceFiO2CalibrationStop();

        /*%C Effacement message de lancement de la ventil */
        this->HideMessageFrame();

        CFrame = this->GetCurrentFrame();
        if (CFrame == FRAME_PREFERENCE)
            this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeVt),eGoDown));

        this->ShowMonitoring();
        this->SetLState(eStartVentil);

        break;

    case eStopVentil:       //arret de Ventilation
        this->StopAllMenuAction();
        this->ShowMessageFrame(TRUE,(UBYTE*)cMSG_StartVentil[GetLanguage()],VENTIL);

        this->SetMonitoringMode(FALSE);
        this->SetLState(eStopVentil);

        CFrame = this->GetCurrentFrame();
        if (CFrame == FRAME_GRAPH)
            this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeVentil),eGoDown));

#ifdef HMI_CONFIG_100_FIO2
        UWORD16 Val;
        DataBaseAccess::ReadValue(&Val,FIO2_100_ACTIVE,CONTROL);
        if (Val)
            Stop100FiO2();
#endif

        break;
    default :
        break;                           

    }
}

/************************************************************************/
/* Description          : affichage du menu de deplacement sur une      */
/*						  fenetre								                     */
/* Parametres en entree : 		                                          */
/*		- FirstNodeId : premier noeud à afficher				  	            */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ShowMenu(UWORD16 FirstNodeId)
{
    UWORD16 Id,TempNodeId,NumFrame;

    MenuControlNode* PtrNode = this->GetNodeAt(FirstNodeId);
    Id = PtrNode->GetEventNode()->GetId();
    NumFrame = Tools::GetNumFrame(Id);
    TempNodeId = FirstNodeId;

    if ((NumFrame == FRAME_VENTILATION) || (NumFrame == FRAME_ALARME))
    {
        while ((Tools::GetNumFrame(Id) == NumFrame))
        {
            if (!Tools::IsModifyNode(Id) && PtrNode->IsVisible())
            {
                PtrNode->GetObject()->Show();
            }

            /*%C noeud suivant */
            TempNodeId++;
            PtrNode = this->GetNodeAt(TempNodeId);
            Id = PtrNode->GetEventNode()->GetId();
        }
    }
    else if (NumFrame == FRAME_MAINTENANCE)
    {
        while ((Tools::GetNumFrame(Id) == NumFrame))
        {
            if (!Tools::IsModifyNode(Id))
            {
                /* On n'affiche pas les noeuds de calibration, il seront affichés après
                   car la configuration de leur affichage est dynamique */
                if ((Id < cMaintCalibStartNode) || (Id > cMaintCalibEndNode))
                    PtrNode->SetVisible(TRUE);
            }

            /*%C noeud suivant */
            TempNodeId++;
            PtrNode = this->GetNodeAt(TempNodeId);
            Id = PtrNode->GetEventNode()->GetId();
        }

    }
    else
    {
        while ((Tools::GetNumFrame(Id) == NumFrame))
        {
            if (!Tools::IsModifyNode(Id))
            {
                PtrNode->SetVisible(TRUE);
            }

            /*%C noeud suivant */
            TempNodeId++;
            PtrNode = this->GetNodeAt(TempNodeId);
            Id = PtrNode->GetEventNode()->GetId();
        }
    }
}
/************************************************************************/
/* Description :  Affiche les paramètres de monitoring	sans           */
/*                afficher les valeurs (ce qui sera fait par un appel à */
/*                SetMonitoringMode(TRUE)                               */
/* Parametres en entree : aucun                                         */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ShowMonitoring(void)
{
    this->FVentilation.ShowMonitoring();
    this->FAlarme.ShowMonitoring();
    this->FGraph.ShowMonitoring();
}
/************************************************************************/
/* Description          : Debut ou Fin du monitoring de l'IHM		      */
/* Parametres en entree : 		                                          */
/*		- Flag : Debut si TRUE									  	               */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::SetMonitoringMode(e_BOOL Flag)
{

    if (Flag)
    {

        if (!this->DifferMonitoringStart)
        {
            FVentilation.StartMonitoringMode(IsFio2Sensor(),IsSpo2Sensor());
            FAlarme.StartMonitoringMode(IsFio2Sensor(),IsSpo2Sensor());
        }
        FGraph.StartMonitoringModeImpactDisp(  IsFio2Sensor(),
                                               IsSpo2Sensor(),
                                               (e_BOOL) (CurrentVirtualFrame == FRAME_GRAPH));

        if ( this->ExhalFlowUsed)
            LOVVteMl.StartMonitoringMode();
        LOVFrCMin.StartMonitoringMode();
        LOVVtiMl.StartMonitoringMode();
        LOVPiMbar.StartMonitoringMode();

        if (ValveDetected)
        {
            LTOVFuiteLMin.StopMonitoringMode();
            GetNodeAt(NodeAlFuite)->GetEventNode()->SetOnButtonValid(&Controller::NoAction);
        }
        else
        {
            LTOVFuiteLMin.StartMonitoringMode();
            GetNodeAt(NodeAlFuite)->GetEventNode()->SetOnButtonValid(&Controller::MoveToModifNodeLoupe);
        }

        LTTVTiS.StartMonitoringMode();

        if (IsFio2Sensor())
            LTTVFiO2.StartMonitoringMode();

        if (IsSpo2Sensor())
            LTTVSpO2.StartMonitoringMode();
    }
    else
    {
        /*%C Stop monitoring table Alarme */
        FVentilation.StopMonitoringMode();
        FAlarme.StopMonitoringMode();
        FGraph.StopMonitoringMode();

        LOVVteMl.StopMonitoringMode();
        LOVFrCMin.StopMonitoringMode();
        LOVVtiMl.StopMonitoringMode();
        LOVPiMbar.StopMonitoringMode();
        LTOVFuiteLMin.StopMonitoringMode();
        LTTVTiS.StopMonitoringMode();
        LTTVFiO2.StopMonitoringMode();
        LTTVSpO2.StopMonitoringMode();

        /* Restore handler when monitoring is stopped */
        GetNodeAt(NodeAlFuite)->GetEventNode()->SetOnButtonValid(&Controller::MoveToModifNodeLoupe);
    }

    MonitoringMode = Flag;
}
/************************************************************************/
/* Description          : Debut ou Fin de pb de communication avec la   */
/*                        carte alimentation                            */
/* Parametres en entree : 		                                          */
/*		- Flag : Debut si TRUE									  	               */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::SetSupplyBusFailure(e_BOOL Flag)
{
    FVoltControl.SetSupplyBusFailure(Flag, (e_BOOL)(FRAME_VOLTAGE_CHECK == GetCurrentFrame()));
    FBatteryMenu.SetSupplyBusFailure(Flag, (e_BOOL)(FRAME_BATTERIE == GetCurrentFrame()));
}
/************************************************************************/
/* Description          : Exhalation flow used set or unset				*/
/* Parametres en entree : 		                                        */
/*		- Flag : TRUE if used else FALSE								*/
/* Parametres en sortie : aucun											*/
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::SetExhalFlowUsed(e_BOOL Flag)
{
    FVentilation.SetExhalFlowUsed(Flag, (e_BOOL) (FRAME_VENTILATION == GetCurrentFrame()));
    FGraph.SetExhalFlowUsed(Flag, (e_BOOL) (FRAME_GRAPH == CurrentVirtualFrame));

    this->ExhalFlowUsed = Flag;

    /* VTE monitoring in the table of the alarm Frame */
    if (LOVVteMl.IsRefreshObject())
    {
        if (Flag)
            LOVVteMl.StartMonitoringMode();
        else
            LOVVteMl.StopMonitoringMode();
    }
}
/************************************************************************/
/* Description          : Gestion Brithness			                     */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ChangeBrightness(WayId Sens)
{
    MenuControlNode* pSavedNode = this->GetCurrentNode();
    e_BOOL isVisible = GetNodeAt(NodePrefBrightness)->GetObject()->IsVisible();
    e_BOOL isModifVisible = GetNodeAt(NodeModifPrefBrightness)->GetObject()->IsVisible();
    LabelProgressBar* ptBar = (LabelProgressBar*) GetNodeAt(NodePrefBrightness)->GetObject(); 
    e_BOOL savedBipRequest = ptBar->GetBipRequest();
    ptBar->SetBipRequest(FALSE);

    /* If a setting change's in progress just time out */ 
    if (this->IsModifNodeOn())
    {
        (this->*(pSavedNode->GetEventNode()->OnTimeOut))(); 
        pSavedNode = this->GetCurrentNode(); 
    }

    if (this->GetCurrentFrame() != FRAME_PREFERENCE)
    {
        this->SetCurrentNode(this->GetNodeAt(NodeModifPrefBrightness));
        GetNodeAt(NodePrefBrightness)->GetObject()->SetVisible(FALSE);
        GetNodeAt(NodeModifPrefBrightness)->GetObject()->SetVisible(FALSE);
    }
    else
    {
        this->MoveCurrentNode(this->GetNodeAt(NodePrefBrightness));
        this->MoveToModifNode();
    }

    switch (Sens)
    {
    case eGoUp:
        DataBaseAccess::IncrementValue(&this->LastBrightness, ADJUST_BRIGHTNESS_U16, CONFIG);
        InterfaceCppC::DisplayBrithness(this->LastBrightness);
        this->ModifyUp();
        break;
    case eGoDown:
        DataBaseAccess::DecrementValue(&this->LastBrightness, ADJUST_BRIGHTNESS_U16, CONFIG);
        InterfaceCppC::DisplayBrithness(this->LastBrightness);
        this->ModifyDown();
        break;
    default:
        break;
    }
    this->SetBrightness(this->LastBrightness);
    this->ReturnToNode();

    if (this->GetCurrentFrame() != FRAME_PREFERENCE)
    {
        this->MoveCurrentNode(pSavedNode);
        GetNodeAt(NodePrefBrightness)->GetObject()->SetVisible(isVisible);
        GetNodeAt(NodeModifPrefBrightness)->GetObject()->SetVisible(isModifVisible);
    }
    ptBar->SetBipRequest(savedBipRequest);
}
/************************************************************************/
/* Description          : Gestion de la touche inhibition			      */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ManageInhibKey(e_BOOL IsLongKey)
{
    if (IsLongKey)
    {
        // Si sur le noeud histoAno
        UWORD16 Id = this->GetCurrentNode()->GetEventNode()->GetId();
        if ((Id == NodeMaintHistAno))
        {
            // Effacement de la flash
            InterfaceCppC::MaintEraseFlashMngt();
            InterfaceCppC::EraseNANDFlashMngt();
            EraseFlag = true;
        }
    }
}

/************************************************************************/
/* Description          : Changement de la pages HMI                    */
/* Parametres en entree : aucun                                         */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/

void Controller::ChangePages()
{
    UWORD16 CFrame = this->GetCurrentFrame();

    UWORD16 _WaveDisplay;
    UWORD16 _MonitorNode;

    /*%C Read Value */
    DataBaseAccess::ReadValue(  &_WaveDisplay,
                                ADJUST_WAVEFORM_DISPLAY_U16,
                                CONFIG);
#ifndef HMI_CONFIG_CURVES
    _WaveDisplay =  FALSE;
#endif

    /*%C Gestion du saut de page */
    if (((CFrame == FRAME_VENTILATION) || (CFrame == FRAME_ALARME)) && !this->IsModifNodeOn())
    {
        if (CFrame == FRAME_VENTILATION)
        {
            this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeAlPi),eGoDown));
        }
        else if (CFrame == FRAME_ALARME && !this->IsModeChange())
        {
            if (!this->IsVentilOn() || (!_WaveDisplay))
            {
                _MonitorNode = (this->GetNodeAt(NodeAlGhost)->GetEventNode())->GetIdNodeOnMonitor();
                if ((_MonitorNode == NodeUsbGhost)||(_MonitorNode == NodeUsbStop))
                    this->MoveCurrentNode(this->GetNodeAt(_MonitorNode));
                else
                    this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(_MonitorNode),eGoDown));
            }
            else
            {
                this->MoveCurrentNode(this->GetNodeAt(NodeGraphGhost));
            }
        }
        else if (CFrame == FRAME_ALARME)
            this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeVt),eGoDown));
        return;
    }

    /*%C Pas d'acces au Menu config en ventilation */
    UWORD16 Id = this->GetCurrentNode()->GetEventNode()->GetId();
    if (this->IsVentilOn() && ((Id == NodeModifVentil) || (Id == NodeModifAlarm)))
    {
        return;
    }
    /*%C Appel dans l'arbre */
    _MonitorNode = (this->GetCurrentNode()->GetEventNode())->GetIdNodeOnMonitor();
    if ((_MonitorNode == NodeUsbGhost)||(_MonitorNode == NodeUsbStop))
        this->MoveCurrentNode(this->GetNodeAt(_MonitorNode));
    else
        (this->*(this->GetCurrentNode()->GetEventNode()->OnButtonMonitor))();

}


/************************************************************************/
/* Description       : communique au controleur une detection d'alarme  */
/* Parametres en entree : 		                                          */
/*		- Actif : TRUE si l'alarme est active							         */
/*		- AlarmId : Id de l'alarme										            */
/*		- Action : Action de l'alarme									            */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::AlarmDetect(e_BOOL Actif, AlarmEvent* Alarm)
{
    UWORD16 NewAlarmHighPrio;
    AlarmEvent* Last;

    if (Actif)
    {
        this->ATable.AddElement(Alarm, this->AManager.IsAlarmValid(Alarm));

        DataBaseAccess::ReadValue(&NewAlarmHighPrio,NEW_ALARM_HP_DETECTED_U16,CONTROL);

        /*%C Changement ede page uniquement sur apparition nouvelle Alarme Haute Priorite */
        if ((e_BOOL) NewAlarmHighPrio == TRUE)
        {
            NewAlarmHighPrio = FALSE;
            DataBaseAccess::WriteValue(&NewAlarmHighPrio,NEW_ALARM_HP_DETECTED_U16,CONTROL);         

            /*%C Retour en alarme si en page Historique alarme */
            if (this->CurrentFrame == FRAME_HISTO_ALARME)
            {
                /*%C Fin du timer de la page histo alarmes */
                this->Timer.StopTimer(TimerQuitHistoAlarme);
                this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeAlPi),eGoDown));
            }
            else if (this->CurrentFrame == FRAME_PREFERENCE && !this->IsModifNodeOn())
            {
                /*%C Fin du timer de la page préférences */
                this->Timer.StopTimer(TimerQuitPreferences);
                this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeVt),eGoDown));
            }
            else if (this->CurrentFrame == FRAME_TENDANCE)
            {
                /*%C Fin du timer de la page tendance */
                this->Timer.StopTimer(TimerQuitVentilReport);
                this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeAlPi),eGoDown));
            }
            else if (this->CurrentFrame == FRAME_GRAPH && !this->IsModifNodeOn())
            {
                this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeAlPi),eGoDown));
            }
            else if (this->CurrentFrame == FRAME_USB && !this->IsModifNodeOn())
            {
                this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeAlPi),eGoDown));
            }
        }
    }
    else
    {
        if (this->ATable.GetNbAlarm() != 0)
        {
            /*%C on stoppe l'affichage de l'alarme sauf pour l'alarme ALARM_HIGH_PRESSURE
            dont l'affichage est controllé par un SPY */
            if (Alarm->id == ALARM_HIGH_PRESSURE_U16)
            {
                if (HasHighPressAlarmToBeRemoved())
                {
                    this->FVentilation.RemoveAlarm(Alarm->id);
                    this->FAlarme.RemoveAlarm(Alarm->id);
                    this->ATable.RemoveElement(Alarm, this->AManager.IsAlarmValid(Alarm));
                }
            }
            else
            {
                this->FVentilation.RemoveAlarm(Alarm->id);
                this->FAlarme.RemoveAlarm(Alarm->id);
                this->ATable.RemoveElement(Alarm, this->AManager.IsAlarmValid(Alarm));
            }

            if (this->ATable.GetNbAlarm() == 0)
            {
                /*%C Arrêt du timer d'effacement de l'alarme */
                this->Timer.StopTimer(TimerHideAlarmMessage);
                /*%C Arrêt des alarmes */
                this->ShowAlarm(FALSE,Alarm->id,Alarm->action);
                /*%C Affichage derniere Alarme */
                Last = ATable.GetLastAlarm();
                this->FAlarme.ShowLastAlarme(Last);

                this->FVentilation.RemoveAllAlarms();
                this->FAlarme.RemoveAllAlarms();
            }
        }
    }
}
/************************************************************************/
/* Description          : Affichage d'une alarme						      */
/* Parametres en entree : 		                                          */
/*		- Actif : TRUE si l'alarme est active							         */
/*		- AlarmId : Id de l'alarme										            */
/*		- Action : Action de l'alarme									            */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ShowAlarm(e_BOOL Actif,UWORD16 AlarmId, UWORD16 Action)
{
    Action = Action; /* pour éviter le warning */
    if (Actif)
    {
        /*%C Lancement du timer d'effacement de l'alarme */
        this->Timer.StartTimer(TIME_HIDE_ALARM_MESSAGE,TimerHideAlarmMessage,FALSE);

        /*%C Affichage du message dans les fenetres Ventil et alarme */
        this->FVentilation.ShowCurrentAlarme(TRUE, AlarmId);
        this->FAlarme.ShowCurrentAlarme(TRUE, AlarmId);
    }
    else
    {
        /*%C Effacement des messages d'alarme */
        this->FVentilation.HideCurrentAlarme();
        this->FAlarme.HideCurrentAlarme();
    }
}

/************************************************************************/
/* Description       : Traitement d'un bloquage de paramètre				*/
/* Parametres en entree : 		                                          */
/*		- Actif : TRUE si le bloquage est actif						         */
/*		- AlarmId : Id du bloquage										            */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::SettingBlockDetect()
{
    UBYTE* Limit1 = 0;
    UBYTE* Limit2 = 0;

    UBYTE MessageString[60];

    UWORD16 Nb_Block = 0;

    /* Scan de DataBase pour visualiser les interdépendances */
    for (UWORD16 i = Start_Limit_Setting+1; i < End_Limit_Setting; i++)
    {
        UWORD16 Value;
        DataBaseAccess::ReadValue(&Value,i,CONTROL);

        if (Value == TRUE)
        {
            Nb_Block++;
            if (Nb_Block == 1)
            {
                /* Mémorisation de la 1ere limite */
                Limit1 = (UBYTE*)cMSG_BlockedSetting[i - Start_Limit_Setting - 1][GetLanguage()];
            }
            else
            {
                /* Mémorisation de la 2eme limite */
                Limit2 = (UBYTE*)cMSG_BlockedSetting[i - Start_Limit_Setting - 1][GetLanguage()];
                break;
            }
        }
    }

    /* Si on n'a pas de blocage */
    if (Nb_Block == 0)
    {
        /* Affichage du message */
        if (CurrentLoupe != NULL)
        {
            this->CurrentLoupe->DisplayMessage(FALSE);
        }
    }
    /* Si on a des bloquages */
    else if (Nb_Block > 0)
    {
        /* Si on n'a qu'un seul blocage */
        if (Nb_Block == 1)
        {
            /* Formatage du message */
            sprintf(    (char *)MessageString,
                        "%s|%s",
                        (char *)cMSG_SettingBlock[GetLanguage()],
                        Limit1);
        }
        /* Si on a plus d'un blocage (deux maxi)*/
        else
        {
            /* Formatage du message */
            sprintf(    (char *)MessageString,
                        "%s|%s / %s",
                        (char *)cMSG_SettingBlock[GetLanguage()],
                        Limit1,
                        Limit2);
        }
        /* Affichage du message */
        if (CurrentLoupe != NULL)
        {
            this->CurrentLoupe->SetMessage(MessageString);
            this->CurrentLoupe->DisplayMessage(TRUE);
        }
    }
}


/************************************************************************/
/* Description          : Affichage|Effacement du symbole batterie		*/
/* Parametres en entree : 		                                          */
/*		- Visible : TRUE si affichage									            */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ShowBattery(e_BOOL Visible)
{
    this->FVentilation.SetBatVisible(Visible, (e_BOOL) !this->IsModeChange());
    this->FAlarme.SetBatVisible(Visible, (e_BOOL) !this->IsModeChange());
    if (GetCurrentFrame() == FRAME_VOLTAGE_CHECK)
        this->FVoltControl.IsBatVisible();
    this->FGraph.IsBatVisible();
}

/************************************************************************/
/* Description          : Permet un saut vers le debut ou la fin d'une  */
/*						  fenetre (menu)								               */
/* Parametres en entree : 		                                          */
/*		- Frame : numero de la fenetre									         */
/*		- Way   : sens de deplacement									            */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::GoToTopBottomFrame(UWORD16 Frame,WayId Way)
{
    if (!this->IsModifNodeOn())
    {
        switch (Way)
        {
        case eGoUp   :
            switch (Frame)
            {
            case FRAME_VENTILATION  : this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeVentil),eGoDown)); break;
            case FRAME_ALARME      : this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeAlarm),eGoDown)); break;
            case FRAME_PREFERENCE   : this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodePrefScreenSave),eGoDown)); break;
            case FRAME_CONFIG_GRAPH : this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeCfgGraphVisu),eGoDown)); break;
            case FRAME_USB           : if (!IsUsbCmdInProgress()) this->MoveCurrentNode(this->FindFirstValidNode(this->GetCurrentNode(),eGoDown));break;
            default : break;
            }
            break;
        case eGoDown :
            switch (Frame)
            {
            case FRAME_VENTILATION  : this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeModeChange),eGoUp)); break;
            case FRAME_ALARME      : this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeAlModeChange),eGoUp)); break;
            case FRAME_PREFERENCE   : this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodePrefBackVentil),eGoDown)); break;
            case FRAME_CONFIG_GRAPH : this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeCfgGraphBackPref),eGoDown)); break;
            case FRAME_USB           : if (!IsUsbCmdInProgress()) this->MoveCurrentNode(this->FindFirstValidNode(this->GetCurrentNode(),eGoUp));break;
            default : break;
            }
            break;
        default :
            break;            
        }
    }
}
/************************************************************************/
/* Description          : Arret de toutes modification sur un menu et	*/
/*						  retour vers le noeud de base du noeud courant       */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::StopAllMenuAction()
{
    if (this->IsModifNodeOn())
    {
        this->ManageTimerEvent(TimeOutModifEvent);
    }
    if (this->IsModeChange())
    {
        this->StopModifMode(this->GetCurrentMode());
    }
}
/************************************************************************/
/* Description          : Affichage d'un message					         */
/* Parametres en entree : 		                                          */
/*		- Visible : TRUE si affichage									            */
/*		- Message : message a afficher 									         */
/*		- Symbol  : symbole a afficher									         */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ShowMessageFrame(e_BOOL Visible, UBYTE* Message, e_SYMBOL Symbol)
{
    this->FVentilation.ShowMessage(Visible,Message,Symbol);
    this->FAlarme.ShowMessage(Visible,Message,Symbol);
}
/************************************************************************/
/* Description          : effacement d'un message					         */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::HideMessageFrame()
{
    this->FVentilation.ShowMessage(FALSE,NULL,NO);
    this->FAlarme.ShowMessage(FALSE,NULL,NO);
}
/************************************************************************/
/* Description          : Action sur la carte buzzer							*/
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::PlayBuzzer()
{
    UWORD16 _Val = TRUE;
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    DataBaseAccess::WriteValue(&_Val, TEST_BUZ_CARD_U16, CONTROL);

    StartBuzzerVoltRefresh();
}
/************************************************************************/
/* Description          : Action sur le buzzer sécurité						*/
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::PlayBuzzerSec()
{
    UWORD16 _Val = TRUE;
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

    DataBaseAccess::WriteValue(&_Val, TEST_BUZ_SEC_U16, CONTROL);
}
/************************************************************************/
/* Description          : Opperation de changement de la langue         */
/*						  de l'IHM									                  */
/* Parametres en entree : 		                                          */
/*		- NumLanguage : numero de la langue								         */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ChangeLanguage(UWORD16 NumLanguage)
{
    MenuControlNode* Node;

    /*%C Ecriture dans la base du language */
    UWORD16 Val = NumLanguage;
    DataBaseAccess::WriteValue(&Val,ADJUST_LANGUAGE_U16,CONFIG);

    SetLanguage(NumLanguage);

    /*%C refresh des fenetres */
    this->FVentilation.RefreshLanguage();
    this->FAlarme.RefreshLanguage();
    this->FHistoAlarme.RefreshLanguage();
    this->FConfiguration.RefreshLanguage();
    this->FPreference.RefreshLanguage();
    this->FMaintenance.RefreshLanguage();
    this->FHistoAno.RefreshLanguage();
    this->FVoltControl.RefreshLanguage();
    this->FWelcome.RefreshLanguage();
    this->FGraph.RefreshLanguage();
    this->FGraphConfig.RefreshLanguage();
    this->FBatteryMenu.RefreshLanguage();
    this->FUsb.RefreshLanguage();
    this->FTendance.RefreshLanguage();
    this->FCircuitCheck.RefreshLanguage();
    HMI_Setup1::GetInstance().FConfiguration1.RefreshLanguage();

    /*%C Refresh du menu */
    for (int i = NodeVentil; i<=cMenuLastNode; i++)
    {
        Node = this->GetNodeAt(i);
        /*%C Pas refresh sur le noeud PI mbar car sinon efface le tableau */
        /* A VERIFER A VERIFER A VERIFER A VERIFER A VERIFER A VERIFER */
        if (!Tools::IsModifyNode(Node->GetEventNode()->GetId()) && (i!=NodeAlPi))
        {
            Node->GetObject()->RefreshLanguage();
        }
    }

    InterfaceCppC::ErazePage(VIRTUAL_PAGE);

    /*%CAffichage des fenetres */
    this->FAlarme.Show();
    this->FVentilation.Show();

    /*%C Affichage des Menus */
    this->ShowMenu(NodeVentil);
    this->ShowMenu(NodeAlarm);

    this->FConfiguration.Show();
    this->ShowMenu(NodeConfLang);

    /*%C refresh messages loupe demarage ventilation */
    if (!this->IsVentilOn())
    {
        this->ShowMessageFrame(TRUE,(UBYTE*)cMSG_StartVentil[GetLanguage()],VENTIL);
    }
}
/************************************************************************/
/* Description   : Reconstruit l'arbre des noeuds pour un mode donné    */
/* Parametres en entree : 		                                          */
/*		- Mode : mode pour lequel l'arbre doit être reconstruit           */
/*    - FirstNode :  Premier noeud à partir duquel doit être faire la   */
/*                   reconstruction                                     */
/*    - LastNode :  Dernier noeud de l'arbre à reconstruire             */
/* Parametres en sortie :                                               */
/*    - Nombre de noeuds visibles                                       */   
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
UWORD16 Controller::RebuildEventNodeTree( e_MODE_TYPES Mode,
                                          UWORD16 FirstNode,
                                          UWORD16 LastNode)
{
    MenuControlNode* Node;
    MenuControlNode* BackUpNode;
    UWORD16 NodeId, Order, PreviousId, NextId;
    UWORD16 FirstNodeId, LastNodeId;
    UWORD16 count = 0;

    /* on sauvegarde les Ids du premier et dernier noeud */
    FirstNodeId = GetNodeAt(FirstNode)->GetEventNode()->GetId();
    LastNodeId = GetNodeAt(LastNode)->GetEventNode()->GetId();

    /* le premier noeud*/
    Node = this->GetNodeAt(FirstNode);
    BackUpNode = Node; /* pour éviter le warning */
    NodeId = Node->GetEventNode()->GetId();
    Order = Tools::GetOrderWithMode(NodeId,Mode);

    do
    {
        if (!Tools::IsModifyNode(NodeId))
        {
            if (Order >= 1)
            {
                PreviousId = Tools::GetIdFromOrder(Order-1,Mode,FirstNodeId,LastNodeId);
                Node->GetEventNode()->SetIdNodeOnUp(GetNodeIdFromEventId(PreviousId));
            }

            NextId = Tools::GetIdFromOrder(Order+1,Mode,FirstNodeId,LastNodeId);
            Node->GetEventNode()->SetIdNodeOnDown(GetNodeIdFromEventId(NextId));
            BackUpNode = Node;
            count++;
        }

        Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());
        NodeId = Node->GetEventNode()->GetId();
        Order = Tools::GetOrderWithMode(NodeId,Mode);
    }
    while (Node != GetNodeAt(LastNode));

    /*%C Branchement du dernier noeud */
    Node->GetEventNode()->SetIdNodeOnUp(GetNodeIdFromEventId(BackUpNode->GetEventNode()->GetId()));

    return(count);
}
/************************************************************************/
/* Description   : Reconstruit l'arbre des noeuds pour tous les modes   */
/* Parametres en entree : 		                                          */
/*    - FirstNode :  Premier noeud à partir duquel doit être faire la   */
/*                   reconstruction                                     */
/*    - LastNode :  Dernier noeud de l'arbre à reconstruire             */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::RebuildEventNodeTreeForAllModes(  UWORD16 FirstNode,
                                                   UWORD16 LastNode)
{
    UWORD16 i;

    for (i=0;i<cMAX_MODE;i++)
    {
        RebuildEventNodeTree( (e_MODE_TYPES)i, FirstNode, LastNode);
    }
}
/************************************************************************/
/* Description   : Retrouve (ou pas) un noeud dans l'arbre des noeuds   */
/*                 pour un mode donné                                   */
/* Parametres en entree : 		                                          */
/*		- Mode : mode pour lequel l'arbre doit être parcouru              */
/*    - NodeToFind : Noeud à chercher dans l'arbre spécifié             */
/*    - FirstNode :  Premier noeud à partir duquel doit être faire le   */
/*                   parcours                                           */
/*    - LastNode :  Dernier noeud de l'arbre à parcourir                */
/* Parametres en sortie : Néant                                         */
/*    - Un masque comprenant :                                          */
/*          - bit31 : la présence ou non du noeud                       */
/*          - bit15 à bit0 : l'ordre d'affichage du noeud               */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
UWORD32 Controller::IsNodeInTree( e_MODE_TYPES Mode,
                                  UWORD16 NodeToFind,
                                  UWORD16 FirstNode,
                                  UWORD16 LastNode)
{
    MenuControlNode* Node;
    UWORD16 NodeId, Order;

    /* le premier noeud*/
    Node = this->GetNodeAt(FirstNode);
    NodeId = Node->GetEventNode()->GetId();

    do
    {
        if (!Tools::IsModifyNode(NodeId))
        {
            if (NodeId == NodeToFind)
            {
                Order = Tools::GetOrderWithMode(NodeId,Mode);
                return(0x80000000 | (Order));
            }
        }

        Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());
        NodeId = Node->GetEventNode()->GetId();
    }
    while (Node != GetNodeAt(LastNode));

    return(0);
}
/************************************************************************/
/* Description   : récupère l'Id d'un Noeud à partir de l'Id de son     */
/*                 noeud d'événement associé                            */
/*						  de l'IHM									                  */
/* Parametres en entree : 		                                          */
/*		- _Id : Id du noeud d'événement											   */
/* Parametres en sortie :                                               */
/*		- _Id : Id du noeud de controle											   */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
UWORD16 Controller::GetNodeIdFromEventId(UWORD16 _Id)
{
    UWORD16 i;
    for (i=0;i<NB_NODE;i++)
    {
        if (GetNodeAt(i)->GetEventNode()->GetId() == _Id)
            return GetNodeAt(i)->GetEventNode()->GetLinkedMenuControlNodeId();
    }
    return(0);
}
/************************************************************************/
/* Description : Masque tous les objets de type alarme                  */
/* Parametres en entree :                                               */
/*    Mode : mode de ventilation                                        */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::HideAlarm(e_MODE_TYPES Mode)
{
    MenuControlNode* Node;
    UWORD16 NodeId;
    Mode = Mode; /* pour éviter le warning */

    if (GetImpactDisplay() && GetEndOfInit())
    {
        Node = this->GetNodeAt(NodeAlarm);
        do
        {
            NodeId = Node->GetEventNode()->GetId();
            if (!Tools::IsModifyNode(NodeId) && (NodeId>cAlarmStartNode) && (NodeId<cAlarmEndNode))
            {
                Node->SetVisible(FALSE);
            }
            Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());
        }
        while (Node != this->GetNodeAt(cAlarmEndNode));
    }
}
/************************************************************************/
/* Description : Masque l'objet de type Alarme passé en paramètre       */
/* Parametres en entree :                                               */
/*    Mode : mode de ventilation                                        */
/*    NodeId : noeud à masquer                                          */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::HideAlarm(e_MODE_TYPES Mode, UWORD16 NodeId)
{
    MenuControlNode* Node;
    Mode = Mode; /* pour éviter le warning */

    if (GetImpactDisplay() && GetEndOfInit())
    {
        Node = this->GetNodeAt(NodeId);
        if (!Tools::IsModifyNode(NodeId) && (NodeId>cAlarmStartNode) && (NodeId<cAlarmEndNode))
        {
            Node->SetVisible(FALSE);
        }
    }
}
/************************************************************************/
/* Description : Masque tous les objets de type Ventil                  */
/* Parametres en entree :                                               */
/*    Mode : mode de ventilation                                        */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::HideVentil(e_MODE_TYPES Mode)
{
    MenuControlNode* Node;
    UWORD16 NodeId;
    Mode = Mode; /* pour éviter le warning */

    if (GetImpactDisplay() && GetEndOfInit())
    {
        Node = this->GetNodeAt(NodeVentil);
        Node->SetVisible(TRUE);
        do
        {
            NodeId = Node->GetEventNode()->GetId();
            if (!Tools::IsModifyNode(NodeId) && (NodeId>cVentilStartNode) && (NodeId<cVentilEndNode))
            {
                Node->SetVisible(FALSE);
            }
            Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());
        }
        while (Node != this->GetNodeAt(cVentilEndNode));
    }
}
/************************************************************************/
/* Description : Masque l'objet de type Ventil passé en paramètre       */
/* Parametres en entree :                                               */
/*    Mode : mode de ventilation                                        */
/*    NodeId : noeud à masquer                                         */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::HideVentil(e_MODE_TYPES Mode, UWORD16 NodeId)
{
    MenuControlNode* Node;
    Mode = Mode; /* pour éviter le warning */

    Node = GetNodeAt(NodeId);

    if (GetImpactDisplay() && GetEndOfInit())
    {
        if (!Tools::IsModifyNode(NodeId) && (NodeId>cVentilStartNode) && (NodeId<cVentilEndNode))
        {
            Node->SetVisible(FALSE);
        }
    }
}
/************************************************************************/
/* Description : Affiche tous les objets de type Ventil                 */
/* Parametres en entree :                                               */
/*    FirstLine : première ligne d'affichage                            */
/*    Increment : incrément d'affichage entre chaque ligne              */
/*    Mode : mode de ventilation                                        */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ShowVentil(  UWORD16 FirstLine,
                              UWORD16 Increment,
                              e_MODE_TYPES Mode)
{
    MenuControlNode* Node;
    UWORD16 NodeId;
    UWORD16 LineVentil = FirstLine;
    UWORD16 IncVentil = Increment;
    e_BOOL NodeVisible = FALSE;

    if (GetImpactDisplay())
    {
        Node = this->GetNodeAt(NodeVentil);
        Node->SetVisible(TRUE);
        do
        {
            /*%C maj de la liste */
            NodeVisible = FALSE;
            Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());
            NodeId = Node->GetEventNode()->GetId();

            if (!Tools::IsModifyNode(NodeId) && (NodeId>cVentilStartNode) && (NodeId<cVentilEndNode) && Tools::IsVisibleWhithMode(NodeId,Mode))
            {
                switch (NodeId)
                {
                case NodeApnee : NodeVisible = (e_BOOL) ((this->IsFSecuEnable()) || (this->IsInhibApneaEnable())); break;
                case NodePiMax : NodeVisible = this->IsVtCibleEnable(); break;
                case NodeSoupirCpt :
                case NodeSoupirVtCoeff : NodeVisible = this->IsSoupirEnable(); break;
                case NodeTriggerE :
                    GetNodeAt(NodeTriggerEsigned)->GetObject()->SetLine(LineVentil);
                    NodeVisible = TRUE;
                    break;
                case NodeTriggerEsigned :
                    GetNodeAt(NodeTriggerE)->GetObject()->SetLine(LineVentil);
                    NodeVisible = TRUE;
                    break;

                default   : NodeVisible = TRUE; break;
                }
                if (NodeVisible)
                {
                    Node->GetObject()->SetLine(LineVentil);
                    Node->SetVisible(TRUE);
                    LineVentil += IncVentil;
                }
            }
        }
        while (Node != this->GetNodeAt(cVentilEndNode));
    }
}
/************************************************************************/
/* Description : Affiche l'objet de type Ventil passé en paramètre      */
/* Parametres en entree :                                               */
/*    Mode : mode de ventilation                                        */
/*    NodeId : noeud à afficher                                         */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ShowVentil( e_MODE_TYPES Mode, UWORD16 NodeId)
{
    MenuControlNode* Node;

    if (GetImpactDisplay())
    {
        Node = this->GetNodeAt(NodeId);
        if (!Tools::IsModifyNode(NodeId) && (NodeId>cVentilStartNode) && (NodeId<cVentilEndNode) && Tools::IsVisibleWhithMode(NodeId,Mode))
        {
            Node->SetVisible(TRUE);
        }
    }
}
/************************************************************************/
/* Description : Affiche tous les objets de type Alarme                 */
/* Parametres en entree :                                               */
/*    FirstLine : première ligne d'affichage                            */
/*    Increment : incrément d'affichage entre chaque ligne              */
/*    Mode : mode de ventilation                                        */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ShowAlarm(   UWORD16 FirstLine,
                              UWORD16 Increment,
                              e_MODE_TYPES Mode)
{
    MenuControlNode* Node;
    UWORD16 NodeId;
    UWORD16 LineVentil = FirstLine;
    UWORD16 IncVentil = Increment;
    e_BOOL NodeVisible = FALSE;

    if (GetImpactDisplay())
    {
        Node = this->GetNodeAt(NodeAlarm);
        do
        {
            /*%C maj de la liste */
            NodeVisible = FALSE;
            Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());
            NodeId = Node->GetEventNode()->GetId();

            if (!Tools::IsModifyNode(NodeId) && (NodeId>cAlarmStartNode) && (NodeId<cAlarmEndNode) && Tools::IsVisibleWhithMode(NodeId,Mode))
            {
                switch (NodeId)
                {
                case NodeAlTi : // Ti s
                    LineVentil++;
                    NodeVisible = TRUE;
                    break;
                case NodeAlVte :
                    GetNodeAt(NodeAlFuite)->GetObject()->SetLine(LineVentil);
                    NodeVisible = TRUE;
                    break;
                case NodeAlFuite :
                    GetNodeAt(NodeAlVte)->GetObject()->SetLine(LineVentil);
                    NodeVisible = TRUE;
                    break;

                default   : NodeVisible = TRUE; break;
                }
                if (NodeVisible)
                {
                    Node->GetObject()->SetLine(LineVentil);
                    Node->SetVisible(TRUE);
                    LineVentil += IncVentil;
                }
            }

        }
        while (Node != this->GetNodeAt(cAlarmEndNode));

        Node = this->GetNodeAt(NodeAlarm);
        Node->SetVisible(TRUE);
    }
}
/************************************************************************/
/* Description : Affiche l'objet de type Alarme passé en paramètre      */
/* Parametres en entree :                                               */
/*    Mode : mode de ventilation                                        */
/*    NodeId : noeud à afficher                                         */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ShowAlarm( e_MODE_TYPES Mode, UWORD16 NodeId)
{
    MenuControlNode* Node;

    if (GetImpactDisplay())
    {
        Node = this->GetNodeAt(NodeId);

        if (!Tools::IsModifyNode(NodeId) && (NodeId>cAlarmStartNode) && (NodeId<cAlarmEndNode) && Tools::IsVisibleWhithMode(NodeId,Mode))
        {
            Node->SetVisible(TRUE);
        }
    }
}
/************************************************************************/
/* Description     : Affiche le tableau d'alarme         		         */
/*                                                                      */
/* Parametres en entree : 		                                          */
/*		- _Mode : mode courant											            */
/*    - _NbParam : Nombre de paramètres = de lignes du tableau          */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::DisplayAlarmTable(UWORD16 _NbParam, e_MODE_TYPES _Mode)
{
    UWORD32 _PresentAndOrder;
    UWORD16 Order = 0;

    if (GetImpactDisplay())
    {
        if (GetEndOfInit())
            FAlarme.HideTable();
        FAlarme.SetTableSize(_NbParam);
        _PresentAndOrder = IsNodeInTree( _Mode, NodeAlTi, NodeAlarm, cAlarmEndNode);
        if ( _PresentAndOrder)
        {
            Order =  _PresentAndOrder & 0x7FFFFFFF;
            FAlarme.ClearBoldLinesOfTable();
            FAlarme.SetBoldLineOfTable(Order -1);
        }
        FAlarme.ShowTable();
    }
}
/************************************************************************/
/* Description : Affiche tous les objets de calibration dans Maintenance*/
/* Parametres en entree :                                               */
/*    FirstLine : première ligne d'affichage                            */
/*    Increment : incrément d'affichage entre chaque ligne              */
/*    Mode : mode de ventilation                                        */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ShowMaintCalib(void)
{
    MenuControlNode* Node;
    UWORD16 NodeId, NodeLimitId;
    UWORD16 DisplayLine;
    UWORD16 DisplayInc = 17;

    /* On récupère la ligne du noeud précédent */
    NodeId = GetNodeAt(cMaintCalibStartNode)->GetEventNode()->GetIdNodeOnUp();
    DisplayLine = GetNodeAt(NodeId)->GetObject()->GetLine() + DisplayInc;

    /* On récupère le noeud limite */
    NodeLimitId = GetNodeAt(cMaintCalibEndNode)->GetEventNode()->GetIdNodeOnDown();

    Node = this->GetNodeAt(cMaintCalibStartNode);
    do
    {
        /*%C maj de la liste */
        Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());
        NodeId = Node->GetEventNode()->GetId();

        if (!Tools::IsModifyNode(NodeId)  &&
            (NodeId>cMaintCalibStartNode) &&
            (NodeId<cMaintCalibEndNode)   &&
            Tools::IsVisibleWhithMode(NodeId,CurrentMode))
        {
            Node->GetObject()->SetLine(DisplayLine);
            Node->SetVisible(TRUE);
            DisplayLine += DisplayInc;
        }
    }
    while (Node != this->GetNodeAt(NodeLimitId));
}
/************************************************************************/
/* Description          : changent des menus en fct du mode		         */
/*						  de l'IHM									                  */
/* Parametres en entree : 		                                          */
/*		- Mode : mode courant											            */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ChangeMenuWithMode(e_MODE_TYPES Mode)
{
    UWORD16 CurrentMode;
    UWORD16 LineVentil = VENTIL_FIRST_NODE_LINE;
    UWORD16 IncVentil = VENTIL_NODE_SPACING;
    UWORD16 NbParam;

    DataBaseAccess::ReadValue(&CurrentMode,ADJUST_MODE_U16,CONFIG);

    if (GetImpactDisplay())
    {
        /*%C Effacement du menu Ventil */
        HideVentil(Mode);

        /*%C Effacement du menu Alarme */
        HideAlarm(Mode);
    }

    /*%C Reconstruction de l'arbre des noeuds Ventil pour ce mode */
    RebuildEventNodeTree(Mode, NodeVentil, cVentilEndNode);

    /*%C Reconstruction de l'arbre des noeuds Alarm pour ce mode */
    NbParam = RebuildEventNodeTree(Mode, NodeAlarm, cAlarmEndNode);

    if (GetImpactDisplay())
    {
        /*%C Redessine le tableau des alarmes */
        DisplayAlarmTable(NbParam, Mode);

        /*%C Affichage du nvx menu Ventil */
        ShowVentil(LineVentil, IncVentil, Mode);

        /*%C Récupération de la première ligne du tableau des alarmes */
        LineVentil = this->FAlarme.GetFirstLineOfTable();

        /*%C Récupération de l'espace entre les lignes du tableau des alarmes */
        IncVentil = this->FAlarme.GetSpacingOfTable();

        /*%C Affichage du nvx menu Alarme */
        ShowAlarm(LineVentil, IncVentil, Mode);
    }
}
/************************************************************************/
/* Description          : teste si il y a un changement de mode et      */
/*						  traite l'IHM en fonction						            */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ManageModeChange()
{
    /*%C Teste si modification du Mode */
    LabelMode* NodeObject = (LabelMode*)this->CurrentNode->GetObject();
    e_MODE_TYPES ModifMode = NodeObject->GetModifMode();

    if (this->GetCurrentMode() != ModifMode)
    {
        /*%C en Ventil */
        if (this->IsVentilOn())
        {
            /*%C Affichage de bat et des symboles d'alarme */
            this->FVentilation.ShowBatAndValve(FALSE);
            this->FAlarme.ShowBatAndValve(FALSE);
            this->FVentilation.ShowPressConvention(FALSE);
            this->FVentilation.ShowInhibApneaOk(FALSE);
            this->FVentilation.ShowInibOk(FALSE);
            this->FVentilation.ShowCancelOk(FALSE);
            this->FAlarme.ShowInhibApneaOk(FALSE);
            this->FAlarme.ShowInibOk(FALSE);
            this->FAlarme.ShowCancelOk(FALSE);
            this->SetModeChange(TRUE);
            /*%C Prise en compte du mode */
            this->SetConsultMode(ModifMode);
            /*%C lancement du timer de fin de Modif du mode */
            this->Timer.StartTimer(TIME_STOP_MODIF_MODE,TimerStopModifMode,FALSE);
        }
        else
        {
            this->StopModifMode(ModifMode);
        }
    }
    else
    {
        if (this->IsVentilOn())
        {
            this->StopModifMode(this->GetCurrentMode());
        }
    }
}
/************************************************************************/
/* Description          : Arreet d'une modification de mode				   */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::StopModifMode(e_MODE_TYPES NewMode)
{

    /*%C Arret du timer */
    this->Timer.StopTimer(TimerStopModifMode);

    this->SetModeChange(FALSE);

    /*%C retour au mode courant */
    this->SetCurrentMode(NewMode);

    /*%C Positionnement du curseur courant */
    if (!this->IsModifNodeOn())
    {
        if (this->CurrentFrame == FRAME_VENTILATION)
        {
            this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeVentil),eGoDown));
        }

        if (this->CurrentFrame == FRAME_ALARME)
        {
            this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeAlarm),eGoUp));
        }
    }

    /*%C Affichage de bat et des symboles d'alarme */
    this->FVentilation.ShowBatAndValve(TRUE);
    this->FAlarme.ShowBatAndValve(TRUE);
    this->FVentilation.ShowPressConvention(TRUE);
    this->FVentilation.ShowInibOk(TRUE);
    this->FVentilation.ShowInhibApneaOk(TRUE);   
    this->FVentilation.ShowCancelOk(TRUE);
    this->FAlarme.ShowInibOk(TRUE);
    this->FAlarme.ShowInhibApneaOk(TRUE);
    this->FAlarme.ShowCancelOk(TRUE);
}
/************************************************************************/
/* Description          : Gestion du lock du menu				            */
/* Parametres en entree : 		                                          */
/*		- Actif : TRUE si Lock actif									            */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ManageLock(e_BOOL Actif)
{
    MenuControlNode* Node = this->GetNodeAt(NodeVentil);
    UWORD16 NodeId;
    e_BOOL _HasToLock = FALSE;

    if ( (this->GetCurrentFrame() == FRAME_VENTILATION) ||
         (this->GetCurrentFrame() == FRAME_ALARME) ||
         (this->GetCurrentFrame() == 0))  /* On reset, CurrentFrame id is 0 */
    {
        _HasToLock = TRUE;
    }

    if (_HasToLock)
    {
        this->SetLockOn(Actif);

        /*%C Arret des Modifs */
        this->StopAllMenuAction();

        /*%C On active le noeud fantome de la page Ventil et de la fenêtre graph */
        this->GetNodeAt(NodeGhost)->SetVisible(Actif);
        this->GetNodeAt(NodeGhost)->SetLock((e_BOOL)!Actif);
        this->GetNodeAt(NodeGraphGhost)->SetVisible(Actif);
        this->GetNodeAt(NodeGraphGhost)->SetLock((e_BOOL)!Actif);

        /*%C On bouge le noeud courant */
        if (Actif)
        {
            switch (this->GetCurrentFrame())
            {
            case FRAME_VENTILATION : this->MoveCurrentNode(this->GetNodeAt(NodeGhost)); break;
            case FRAME_ALARME : this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeAlHisto),eGoUp)); break;
            case FRAME_GRAPH : this->MoveCurrentNode(this->GetNodeAt(NodeGraphGhost)); break;
            default : break;
            }
        }

        /*%C maj des noeuds Mode */
        Node->SetLock(Actif);
        Node = this->GetNodeAt(NodeAlarm);
        Node->SetLock(Actif);

        /*%C Maj du menu Ventil */
        Node = this->GetNodeAt(NodeVentil);
        do
        {
            /*%C maj de la liste */
            Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());
            NodeId = Node->GetEventNode()->GetId();
            switch (NodeId)
            {
            case cVentilStartNode : break;
            default   : if (Actif)
                {
                    Node->SetLock(Tools::IsLockWhithLock(NodeId));
                }
                else
                {
                    Node->SetLock(FALSE);
                }
            }
        }
        while (Node != this->GetNodeAt(cVentilEndNode));
        /*%C Noeud Final a modifier en cas d'ajout de noeuds */

        /*%C Maj du menu Alarme */
        Node = this->GetNodeAt(NodeAlarm);
        do
        {
            /*%C maj de la liste */
            Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());
            NodeId = Node->GetEventNode()->GetId();
            switch (NodeId)
            {
            case cAlarmStartNode : break;
            case NodeAlModeChange : break;
            case NodeAlHisto : break;
            default   : if (Actif)
                {
                    Node->SetLock(Tools::IsLockWhithLock(NodeId));
                }
                else
                {
                    Node->SetLock(FALSE);
                }
                break;
            }
        }
        while (Node != this->GetNodeAt(cAlarmEndNode));
        /*%C Noeud Final a modifier en cas d'ajout de noeuds */

        /*%C Quitte le noeud fantome si pas de lock et on se positionne sur la ligne de mode */
        if (!Actif)
        {
            switch (this->GetCurrentFrame())
            {
            case FRAME_VENTILATION : this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeVt),eGoDown)); break;
            case FRAME_ALARME : this->MoveCurrentNode(this->FindFirstValidNode(this->GetNodeAt(NodeAlPi),eGoDown)); break;
            case FRAME_GRAPH : this->MoveCurrentNode(this->GetNodeAt(NodeGraphGhost)); break;
            default : break;
            }
        }
    }
}
/************************************************************************/
/* Description          : Gestion du lock du menu USB 		            */
/* Parametres en entree : 		                                          */
/*		- Actif : TRUE si Lock actif									            */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ManageUsbLock(e_BOOL Actif)
{
    MenuControlNode* Node;

    if (GetUsbLock() != Actif)
    {
        SetUsbLock(Actif);

        /*%C Arret des Modifs */
        //StopAllMenuAction();

        /*%C Maj du menu Usb */
        Node = this->GetNodeAt(NodeUsbGhost);
        do
        {
            Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());

            if (Actif)
                Node->SetLock(TRUE);
            else
                Node->SetLock(FALSE);
        }
        while (Node != this->GetNodeAt(cUsbEndNode));
    }
}
/************************************************************************/
/* Description          : deplacement des objet du menu en fonction de  */
/*						  la presence de sous menu						            */
/* Parametres en entree : 		                                          */
/*		- MasterNode : noeud pere du sous menu							         */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ManageLineMenuVentil(MenuControlNode* MasterNode)
{
    MenuControlNode* Node = MasterNode;
    UWORD16 LineVentil = MasterNode->GetObject()->GetLine() + VENTIL_NODE_SPACING;
    UWORD16 NodeId;
    e_BOOL NodeVisible;

    if (MasterNode->IsVisible())
    {
        /*%C effacement des noeuds */
        Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());
        do
        {
            NodeId = Node->GetEventNode()->GetId();
            if (!Tools::IsModifyNode(NodeId))
            {
                Node->SetVisible(FALSE);
            }
            Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());
        }
        while (Node != this->GetNodeAt(cVentilEndNode));
        /*%C Noeud Final a modifier en cas d'ajout de noeuds */

        /*%C affichage */
        Node = this->GetNodeAt(MasterNode->GetEventNode()->GetIdNodeOnDown());
        do
        {
            NodeVisible = FALSE;
            NodeId = Node->GetEventNode()->GetId();
            if (!Tools::IsModifyNode(NodeId))
            {
                switch (NodeId)
                {
                case NodeApnee : NodeVisible = (e_BOOL)(this->GetNodeAt(NodeFsecu)->IsVisible() && (this->IsFSecuEnable()) || (this->IsInhibApneaEnable())); break;

                case NodePiMax : NodeVisible = (e_BOOL)(this->GetNodeAt(NodeVtCible)->IsVisible() && (this->IsVtCibleEnable())); break;

                case NodeSoupirCpt :
                case NodeSoupirVtCoeff : NodeVisible = (e_BOOL)(this->GetNodeAt(NodeSoupirSelect)->IsVisible() && (this->IsSoupirEnable())); break;

                default   : if (!this->IsModeChange())
                    {
                        NodeVisible = Tools::IsVisibleWhithMode(NodeId,this->GetCurrentMode());
                    }
                    else
                    {
                        NodeVisible = Tools::IsVisibleWhithMode(NodeId,this->GetConsultMode());
                    }
                    break;
                }

                if (NodeVisible)
                {
                    Node->GetObject()->SetLine(LineVentil);
                    Node->SetVisible(TRUE);
                    LineVentil += VENTIL_NODE_SPACING;
                }
            }
            Node = this->GetNodeAt(Node->GetEventNode()->GetIdNodeOnDown());
        }
        while (Node != this->GetNodeAt(cVentilEndNode));
        /*%C Noeud Final a modifier en cas d'ajout de noeuds */
    }
}
/************************************************************************/
/* Description          : gestion de la calibration automatique avec    */
/*  					  Verif											               */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::VerifAndManageCalibAuto()
{
    this->ManageVerifPointCalib(&Controller::ManageCalibAuto);
}
/************************************************************************/
/* Description          : gestion de la calibration automatique			*/              
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ManageCalibAuto()
{
    /*%C On code la suite des noeuds sur le time out pour la calib auto */
    this->Timer.StartTimer(TIME_AUTO_CALIB_TEST,TimerAutoCalibTest,FALSE);
    (this->*(this->GetCurrentNode()->GetEventNode()->OnTimeOut))();
}
/************************************************************************/
/* Description          : gestion de la recherche d'Histo Alarm			*/
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun														*/
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ManageHistoAlarmSeek()
{
    if (this->FHistoAlarme.SeekEnd() == FALSE)
        this->Timer.StartTimer(TIME_HISTO_ALARM_SEEK,TimerHistoAlarmSeek,FALSE);
}

/************************************************************************/
/* Description          : gestion de la recherche d'Histo Anomalie		*/              
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun														*/
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ManageHistoAnoSeek()
{
    if (this->FHistoAno.SeekEnd() == FALSE)
        this->Timer.StartTimer(TIME_HISTO_ANO_SEEK,TimerHistoAnoSeek,FALSE);
}

/************************************************************************/
/* Description          : gestion du trigger							         */
/* Parametres en entree : 		                                          */
/*		- Event : type d'evenement de respiration						         */
/* Parametres en sortie : aucun										         	*/
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ManageTrigger(UWORD16 Event)
{
    static e_BOOL HideTriggerEnable = FALSE ;
    static e_BOOL MustHideTrigger = TRUE ;
    static e_BOOL IsInsTrigger = FALSE ;

    switch (Event)
    {
    case ProgInspTrigEvent :
        if (MustHideTrigger == TRUE)
        {
            /*%C Debut inspiration trigger */
            HideTriggerEnable = FALSE ;
            MustHideTrigger = FALSE ;
            IsInsTrigger = TRUE;
            this->Timer.StartTimer(TIME_TRIGGER_OK,TimerTriggerOk,FALSE);
            /*%C Affichage des triggers */
            this->SetVisibleTrigger(TRUE);
        }
        break;
    case ProgExhEvent      :
        if (IsInsTrigger == TRUE)
        {
            MustHideTrigger = TRUE;
            IsInsTrigger = FALSE;
            if (HideTriggerEnable)
            {
                /*%C Effacement des triggers */
                this->SetVisibleTrigger(FALSE);
            }
        }
        break;
    case TimerTriggerOk    :
        HideTriggerEnable = TRUE;
        if (MustHideTrigger)
        {
            /*%C Effacement des triggers */
            this->SetVisibleTrigger(FALSE);
            HideTriggerEnable = FALSE;
        }
        break;
    default : break;         
    }
}

/************************************************************************/
/* Description          : Affichage du trigger							      */
/* Parametres en entree : 		                                          */
/*		- Flag : TRUE si visible									            	*/
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::SetVisibleTrigger(e_BOOL Flag)
{
    if (Flag)
    {
        this->FVentilation.ShowTrigger();
        this->FAlarme.ShowTrigger();
        this->FGraph.ShowTrigger();
    }
    else
    {
        this->FVentilation.HideTrigger();
        this->FAlarme.HideTrigger();
        this->FGraph.HideTrigger();
    }
}

/************************************************************************/
/* Description          : Permet la gestion d'interdepandance a la fin  */
/*						de la modification d'un noeud					            */
/* Parametres en entree : 		                                          */
/*		- Flag : TRUE si visible										            */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::SendNodeModify(UWORD16 IdNode,e_BOOL IsNotTO)
{
    UWORD16 Val;

    switch (IdNode)
    {
    /*C% Ventil menu Interdependence */
    case cVentilStartNode :
        this->ManageModeChange();
        break;


    case NodeVt :
        if (IsNotTO)
        {
            this->LOVVteMl.RefreshValue1();
            this->LOVVtiMl.RefreshValue1();
            this->LOVVtiMl.RefreshValue2();
            this->LOVVteMl.RefreshValue1();
            this->LOVVteMl.RefreshValue2();
        }
        break;

    case NodeFVaci :
        if (IsNotTO)
        {
            this->LOVPiMbar.RefreshValue1();
            this->LOVPiMbar.RefreshValue2();
            this->LOVFrCMin.RefreshValue1();
        }
        break;
    case NodeInspTime:
        if (IsNotTO)
        {
            this->LOVApnee.Refresh();
        }
        break;
    case NodePi :
    case NodePi2 :
        if (IsNotTO)
        {
            /* rafraîchissement Pi Max */
            this->LOVPiMax.Refresh();

            if (IdNode == NodePi2)
            {
                this->LOVPiMbar.RefreshValue1();
                this->LOVPiMbar.RefreshValue2();
            }
        }
        break;
    case NodePControl :
    case NodePSupport :
        if (IsNotTO)
        {
            /* rafraîchissement Pi Max */
            this->LOVPiMax.Refresh();

            if (IdNode == NodePSupport)
            {
                this->LOVPiMbar.RefreshValue1();
                this->LOVPiMbar.RefreshValue2();
            }
        }
        break;
    case NodePente :
        if (IsNotTO)
        {
            this->LOVFrCMin.RefreshValue1();
            this->LTTVTiS.RefreshValue1();
            this->LTTVTiS.RefreshValue2();
        }
        break;
    case NodePe :
        if (IsNotTO)
        {
            this->LOVPiMbar.RefreshValue1();
            this->LOVPiMbar.RefreshValue2();
        }
        break;

    case NodeFrMini :
        if (IsNotTO)
        {
            this->LOVFrCMin.RefreshValue1();
        }
        break;

    case NodeTriggerI :
        if (IsNotTO)
        {

            UWORD16 Value = this->LOVTrigI.GetIntValue1();

            this->LOVFRMini.RefreshLanguage();
            if (this->LOVFRMini.IsVisible()) this->LOVFRMini.Show();
            /* changement du nom du mode VOL + PRES */
            if ((this->GetCurrentMode() == VOL) || (this->GetCurrentMode() == PRES))
            {
                ChangeNameMode((e_BOOL)Value);
            }

            if (IsNodeInTree( CurrentMode, NodeAlFr, NodeAlarm, cAlarmEndNode))
            {
                /* rafraichissement du High R */
                this->LOVFrCMin.RefreshValue1();
            }
        }
        break;

    case NodeFsecu :        if (IsNotTO)
        {
            this->LOVFrCMin.RefreshValue1();
            this->LTTVTiS.RefreshValue1();
            UWORD16 Value;
            DataBaseAccess::ReadValue(&Value, this->LOVFSecu.GetIdFlag(), this->LOVFSecu.GetDbIdFlag());

            /*+changement du nom du mode  PSVT*/
            if (this->GetCurrentMode() == PSVT)
            {
                this->ChangeNameMode((e_BOOL)!Value);
            }
            this->SetFSecuEnable();
        }
        break;


    case NodeVtCible :
        if (IsNotTO)
        {
            this->LOVVtiMl.RefreshValue1();
            this->LOVVtiMl.RefreshValue2();
            this->LOVVteMl.RefreshValue1();
            this->LOVVteMl.RefreshValue2();                        

            this->SetVtCibleEnable();
        }
        break;

    case NodeSoupirSelect :
        if (IsNotTO)
        {

            this->SetSoupirEnable();
        }
        break;

    case NodeModeChange :
        if (IsNotTO)
        {
            e_BOOL ChangeMode;
            /*%C RAZ du Flag de changement de Mode en cours */
            /*%C Teste le choix utilisateur */
            ChangeMode = (e_BOOL)this->LSTVChgtModeV.GetIntValue1();
            if (ChangeMode)
            {
                this->StopModifMode(this->GetConsultMode());
                //ecriture en base
                Val = TRUE;
                DataBaseAccess::WriteValue(&Val,CHANGE_MODE_U16,CONTROL);
            }
            else
            {
                this->StopModifMode(this->GetCurrentMode());
            }
        }
        else
        {
            this->StopModifMode(this->GetCurrentMode());
        }
        break;

        /*C% Alarm menu Interdependence */
    case cAlarmStartNode :
        this->ManageModeChange();
        break;

    case NodeAlModeChange :
        if (IsNotTO)
        {
            e_BOOL ChangeMode;
            /*%C Teste le choix utilisateur */
            ChangeMode = (e_BOOL)this->LOVChgtModeA.GetIntValue1();
            if (ChangeMode)
            {
                this->StopModifMode(this->GetConsultMode());
                /*%C ecriture en base */
                UWORD16 Val = (UWORD16)TRUE;
                DataBaseAccess::WriteValue(&Val,CHANGE_MODE_U16,CONTROL);

            }
            else
            {
                this->StopModifMode(this->GetCurrentMode());
            }

        }
        else
        {
            /*%C Bascule en mode courant */
            this->StopModifMode(this->GetCurrentMode());
        }
        break;

        /*C% Config menu Interdependence */
    case NodeConfLang :
        if (IsNotTO)
        {
            UWORD16 Language;
            /*%C Teste le choix utilisateur */
            Language = this->LVSLanguage.GetIntValue1();
            if (Language != GetLanguage())
            {
                this->ChangeLanguage(Language);
            }
        }
        break;

    case NodeConfDate :
        if (IsNotTO)
        {
            /*%C Demande de modification de RTC Date */
            UWORD16 Value = ADJUST_DATE;
            DataBaseAccess::WriteValue(&Value, ADJUST_RTC_REQ_U16, RTC);
        }
        break;

    case NodeConfTime :
        if (IsNotTO)
        {
            /*%C Demande de modification de RTC Heure */
            UWORD16 Value = ADJUST_HOUR;
            DataBaseAccess::WriteValue(&Value, ADJUST_RTC_REQ_U16, RTC);
        }
        break;

    case NodeConfModeCycl :
        if (IsNotTO)
        {
            /*%C Demande de modification de I/E ou I/T */
								e_BOOL _ModeCycl = (e_BOOL)HMI_Setup1::GetInstance().LVSModeCycl.GetIntValue1();
            SetMCycl(_ModeCycl);
        }
        break;

    case NodeConfPressureUnit :
        if (IsNotTO)
        {
            /*%C Demande de modification de l'unité de pression */
            UWORD16 _Val = LVSPressureUnit.GetIntValue1();
            SetPressureUnit(_Val);
        }
        break;

    case NodeConfConvTrigE :
        if (IsNotTO)
        {
            /*%C Demande de modification de convention de trigger E */
								e_BOOL _ConvTrigE = (e_BOOL)HMI_Setup1::GetInstance().LVSConvTrigE.GetIntValue1();
            SetConvTrigE(_ConvTrigE);
        }
        break;


        /*C% Preference menu Interdependence */
    case NodePrefBrightness :
        if (IsNotTO)
        {
            this->SetBrightness(this->LastBrightness);
        }
        break;

    case NodePrefApneaAlarm :
        if (IsNotTO)
        {
            e_BOOL _ApneaAlarm = (e_BOOL)LVSApneaAlarm.GetIntValue1();
            SetInhibApneaOk((e_BOOL)(!(_ApneaAlarm == TRUE)));
        }
        break;

    default : break;
    }
}
/************************************************************************/
/* Description          : Permet le changement du nom du mode(cour|long)*/
/* Parametres en entree : 		                                          */
/*		- IsLongNameMode : TRUE nom long								            */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ChangeNameMode(e_BOOL IsLongNameMode)
{
    e_BOOL Refresh = FALSE;
    if (!IsModeChange())
    {
        if (IsLongNameMode)
        {
            Refresh = (e_BOOL)this->LModeVent.IsNameMode2Display();
            LModeAlarm.SetNameMode2Display(FALSE);
            LModeVent.SetNameMode2Display(FALSE);
            FGraph.SetNameMode2Display(FALSE);
        }
        else
        {
            Refresh = (e_BOOL)!this->LModeVent.IsNameMode2Display();
            LModeAlarm.SetNameMode2Display(TRUE);
            LModeVent.SetNameMode2Display(TRUE);
            FGraph.SetNameMode2Display(TRUE);
        }

        if (Refresh)
        {
            LModeAlarm.RefreshLanguage();
            LModeVent.RefreshLanguage();
            LModeAlarm.Show();
            LModeVent.Show();
        }
    }
}


//---------------------------------------------------------------------------
//        FONCTIONS PARTICULIERES DE NOEUD
//---------------------------------------------------------------------------
/************************************************************************/
/* Description          : MoveToModifNode pour le noeud                 */
/*                        de calib concentration FiO2                   */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun										         	*/
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToModifNodeFiO2Concent()
{
    if (IsFio2Sensor())
        MoveToModifNode();
}
/************************************************************************/
/* Description          : MoveToModifNodeConsultCalib pour le noeud     */
/*                        de calib concentration FiO2                   */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun										         	*/
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToModifNodeConsultCalibFiO2Concent()
{
    if (IsFio2Sensor())
        MoveToModifNodeConsultCalib();
}
/************************************************************************/
/* Description          : MoveToModifNode pour les noeuds de calib auto */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun										         	*/
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToModifNodeCalibAuto()
{
    this->Timer.StartTimer(TIME_AUTO_CALIB_TEST,TimerAutoCalibTest,FALSE);
    this->MoveToModifNodeBlowerAction();
    this->Timer.StopTimer(TimeOutModifEvent);
}

/************************************************************************/
/* Description          : MoveToModifNode pour le noeud                 */
/*                        NodeMaintPwmBlower			                     */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToModifNodeMaintPwmBlower()
{
    this->LOVPwmBlower.StartMonitoringMode();
    this->LOVPwmBlower.Refresh();
    this->MoveToModifNode();
}
/************************************************************************/
/* Description          : ReturnToNodeTO pour le noeud                 */
/*                        NodeMaintPwmBlower			                     */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeMaintPwmBlowerTO()
{
    this->ReturnToNodeTO();
}
/************************************************************************/
/* Description          : Décrémente le pas de la turbine si le noeud   */
/*                        courant est dans la plage de noeuds de        */
/*                        calibration                                   */
/* Parametres en entree : aucun                                         */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::DecreaseBlowerStep()
{

    UWORD16 _CurrentNodeId = GetCurrentNode()->GetEventNode()->GetId();

    if (   ((_CurrentNodeId >= cMaintCalibStartNode) &&
            (_CurrentNodeId <= cMaintCalibEndNode)) ||
           _CurrentNodeId == NodeMaintPwmBlower ||
           _CurrentNodeId == NodeModifMaintPwmBlower )
    {
        if (StepLevel == eSTEP_LEVEL_HIGH)
        {
            StepLevel = eSTEP_LEVEL_LOW;
            cDB_TEST_CONTROL_DB[CALIB_ADJUST_CMD_U16].step /= LOCAL_BLOWER_STEP_FACTOR;
        }
    }
}
/************************************************************************/
/* Description          : Incrémente le pas de la turbine si le noeud   */
/*                        courant est dans la plage de noeuds de        */
/*                        calibration                                   */
/* Parametres en entree : aucun                                         */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::IncreaseBlowerStep()
{

    UWORD16 _CurrentNodeId = GetCurrentNode()->GetEventNode()->GetId();

    if (   ((_CurrentNodeId >= cMaintCalibStartNode) &&
            (_CurrentNodeId <= cMaintCalibEndNode)) ||
           _CurrentNodeId == NodeMaintPwmBlower ||
           _CurrentNodeId == NodeModifMaintPwmBlower )
    {
        if (StepLevel == eSTEP_LEVEL_LOW)
        {
            StepLevel = eSTEP_LEVEL_HIGH;
            cDB_TEST_CONTROL_DB[CALIB_ADJUST_CMD_U16].step *= LOCAL_BLOWER_STEP_FACTOR;
        }
    }
}
/************************************************************************/
/* Description          : ReturnToNode pour le noeud                    */
/*                        NodeMaintPwmBlower			                     */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeMaintPwmBlower()
{
    this->ReturnToNode();
}
/************************************************************************/
/* Description          : MoveToModifNode avec lancement du blower		*/
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToModifNodeBlowerAction()
{
    /*%C Lancement du refresh du blower */
    this->LOVPwmBlower.StartMonitoringMode();
    this->LOVPwmBlower.RefreshEnable(TRUE);
    this->MoveToModifNode();
}

/************************************************************************/
/* Description          : MoveToNextModifNode pour les noeuds de calib  */
/*						  avec verif de la valeur	                           */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::VerifAndMoveToNextModifNodeCalib()
{
    ManageVerifPointCalib(&Controller::MoveToNextModifNodeCalib);
}

/************************************************************************/
/* Description          : MoveToNextModifNode pour les noeuds de calib  */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToNextModifNodeCalib()
{
    MoveToNextModifNodeOnKey(eGoLongValid);
}

/************************************************************************/
/* Description          : ReturnToNode pour les noeuds de calib  avec   */
/*						  verif de la valeur							               */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::VerifAndReturnToNodeCalib()
{
    ManageVerifPointCalib(&Controller::ReturnToNodeCalib);
}

/************************************************************************/
/* Description          : ReturnToNode pour les noeuds de calib         */              
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeCalib()
{
    this->ReturnToNodeOnKey(eGoValid);

    /*%C Arret de la calibration automatique dans tous les cas */
    this->Timer.StopTimer(TimerAutoCalibTest);
    OnWait = FALSE;

    /*%C Arret monitoring blower */
    this->LOVPwmBlower.RefreshEnable(FALSE);
    this->LOVPwmBlower.StopMonitoringMode();
}
/************************************************************************/
/* Description          : Force l'arret de la calibration Exp Auto en   */
/*                         cours              			                  */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ForceQExpCalibrationStop(void)
{
    UWORD16 Val;
    UWORD16 Id = this->CurrentNode->GetEventNode()->GetId();

    if (Id == NodeAlCalibVte2)
    {
        /* End of calibration */
        Val = NO_CALIB;
        DataBaseAccess::WriteValue(  &Val,
                                     CALIB_FLOW_EXH_REQ_U16,
                                     CONTROL);
        this->SegmentNumber = 1;

        Timer.StopTimer(TimerWaitCalibQExp);

        /* on positionne l'alarme pour bien montrer qu'on a coupé une calibration en cours */
        Val = ALARM_DETECTED;
        DataBaseAccess::WriteValue( &Val,
                                    TECH_ALARM_EXHAL_FLOW_OFFSET_DEFAULT_U16,
                                    ALARMS);

        /*%C Gestion de la loupe */
        if (CurrentLoupe != NULL)
            this->CurrentLoupe->DisplayMessage(FALSE);

        /*%C reaffiche le message de lancement de la ventil */
        MoveToNextModifNode();

        LSTICalibQExp.Hide();
        this->CurrentNode->GetObject()->RefreshEnable(TRUE);
        LOVVteMl.ForceRefresh();

        ReturnToNodeTOLoupe();
    }
}
/************************************************************************/
/* Description          : Force l'arret de la calibration FiO2 Auto en  */
/*                         cours              			                  */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ForceFiO2CalibrationStop(void)
{
    UWORD16 Val;
    UWORD16 Id = this->CurrentNode->GetEventNode()->GetId();

    if ((Id == NodeAlCalibFiO2_2) && (!this->IsVentilOn()))
    {
        /* End of calibration */
        Val = NO_CALIB;
        DataBaseAccess::WriteValue(  &Val,
                                     CALIB_FIO2_REQ_U16,
                                     CONTROL);
        this->SegmentNumber = 1;
        this->StartCalib = FALSE;
        this->StartVerif = FALSE;

        Timer.StopTimer(TimerWaitCalibFiO2);

        /* on positionne l'alarme pour bien montrer qu'on a coupé une calibration en cours */
        Val = ALARM_DETECTED;
        DataBaseAccess::WriteValue( &Val,
                                    TECH_ALARM_FIO2_OFFSET_DEFAULT,
                                    ALARMS);

        /*%C Gestion de la loupe */
        if (CurrentLoupe != NULL)
            this->CurrentLoupe->DisplayMessage(FALSE);

        LSTICalibFiO2.Hide();
        this->CurrentNode->GetObject()->RefreshEnable(TRUE);
        LTTVFiO2.ForceRefresh();
        /* on passe sur le neud suivant et on appelle la routine de timeout
           pour revenir sur un noeud qui n'est pas de modif */
        ReturnToNodeToCalibNodeAlCalibFiO2();
        ReturnToNodeTOLoupe();
    }
}
/************************************************************************/
/* Description          : Verification des points de calibration        */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ManageVerifPointCalib(PController CallFct)
{
    static PController CallFctReff;

    if (!OnWait)
    {
        CallFctReff = CallFct;
    }
    ManualCalibTwoValue* AutoCalibVal = (ManualCalibTwoValue*)this->CurrentNode->GetObject();
    /*%C Verification de la calibration */
    if (AutoCalibVal->VerificationCalibCheck())
    {
        OnWait = FALSE;
        if (AutoCalibVal->CalibSegmentOK())
        {
            (this->*CallFctReff)();
        }
        else
        {
            if (!AutoCalibVal->StopIfErrorCalib())
            {
                (this->*CallFctReff)();
            }
            else
            {
                this->ReturnToNodeCalib();
            }
        }
    }
    else
    {
        /*%C attente de la reponse */
        OnWait = TRUE;
        this->Timer.StartTimer(TIME_WAIT_CALIB_VERIF,TimerWaitCalibVerif,FALSE);
    }
}

/************************************************************************/
/* Description          : MoveUp pour le noeud NodePreference    		   */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveDownNodePreference()
{
    if ( GetNodeAt(NodeVentil)->IsValid() )
    {
        MoveCurrentNode(GetNodeAt(NodeVentil));
    }
}

/************************************************************************/
/* Description          : MoveMonitor pour le noeud NodeModifVentil     */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveMonitorNodeModifVentil()
{
    /*%C arret de la modif sur le noeud du mode */
    this->StopAllMenuAction();

    /*%C reprise normale */
    this->MoveToOtherNode(eGoMonitor);
}

/************************************************************************/
/* Description          : MoveValid pour le noeud NodeAlHisto	         */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveValidNodeAlHisto()
{
    /*%C Debut du timer de la page histo alarmes */
    this->Timer.StartTimer(TIME_QUIT_HISTO_ALARME,TimerQuitHistoAlarme,FALSE);
    this->MoveValid();
}


/************************************************************************/
/* Description          : MoveValid pour le noeud NodePreference        */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveValidNodePreference()
{
    /*%C Debut du timer de la page histo alarmes */
    this->Timer.StartTimer(TIME_QUIT_PREFERENCES,TimerQuitPreferences,FALSE);
    this->MoveValid();
}

/************************************************************************/
/* Description          : MoveValid pour le noeud NodeHistAlBack        */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveValidNodeHistAlBack()
{
    /*%C fin du timer de la page histo alarmes */
    this->Timer.StopTimer(TimerQuitHistoAlarme);
    this->MoveValid();
}

/************************************************************************/
/* Description          : MoveValid pour le noeud NodeHistAlCancelled   */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveValidNodeHistAlCancelled()
{
    UWORD16 _Value;

    /*%C Do a Short Valid Bip */
    _Value = BIP_SHORT;
    DataBaseAccess::WriteValue( &_Value,
                                VALIDATION_BIP_U16,
                                CONTROL);

    /*%C UNCANCELLED all alarms */
    _Value = TRUE;
    DataBaseAccess::WriteValue( &_Value,
                                UNCANCEL_CMD_U16,
                                CONTROL);

    /*%C End of Node */
    this->MoveValid();
}

/************************************************************************/
/* Description          : MoveValid pour le noeud NodePrefBackVentil    */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveValidNodePrefBackVentil()
{
    /*%C fin du timer de la page histo alarmes */
    this->Timer.StopTimer(TimerQuitPreferences);
    this->MoveValid();
}

/************************************************************************/
/* Description          : MoveUp, MoveDown, ModifyUp, ModifyDown,		   */
/*						  MoveToModifNode, ReturnToNode pour le		         */
/*						  noeud NodePrefScreenSave	et suivants                */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveUpNodePrefScreenSave()
{
    /*%C Relance le timer de la page préférences */
    this->Timer.StartTimer(TIME_QUIT_PREFERENCES,TimerQuitPreferences,FALSE);
    this->MoveUp();
}
void Controller::MoveDownNodePrefScreenSave()
{
    /*%C Relance le timer de la page préférences */
    this->Timer.StartTimer(TIME_QUIT_PREFERENCES,TimerQuitPreferences,FALSE);
    this->MoveDown();
}
void Controller::ModifyUpNodePrefScreenSave()
{
    UWORD16 Id = this->GetCurrentNode()->GetEventNode()->GetId();
    if (Id == NodeModifPrefBrightness)
    {
        DataBaseAccess::IncrementValue(&this->LastBrightness, ADJUST_BRIGHTNESS_U16, CONFIG);
        InterfaceCppC::DisplayBrithness(this->LastBrightness);
    }
    else if (Id == NodeModifPrefSoundLevel)
    {
        DataBaseAccess::IncrementValue(&this->LastSoundLevel, SOUND_LEVEL_SELECT_U16, CONFIG);
        DataBaseAccess::WriteValue(&this->LastSoundLevel, SOUND_LEVEL_SELECT_U16, CONFIG);
    }
    /*%C Relance le timer de la page préférences */
    this->Timer.StartTimer(TIME_QUIT_PREFERENCES,TimerQuitPreferences,FALSE);
    this->ModifyUp();
}
void Controller::ModifyDownNodePrefScreenSave()
{
    UWORD16 Id = this->GetCurrentNode()->GetEventNode()->GetId();
    if (Id == NodeModifPrefBrightness)
    {
        DataBaseAccess::DecrementValue(&this->LastBrightness, ADJUST_BRIGHTNESS_U16, CONFIG);
        InterfaceCppC::DisplayBrithness(this->LastBrightness);
    }
    else if (Id == NodeModifPrefSoundLevel)
    {
        DataBaseAccess::DecrementValue(&this->LastSoundLevel, SOUND_LEVEL_SELECT_U16, CONFIG);
        DataBaseAccess::WriteValue(&this->LastSoundLevel, SOUND_LEVEL_SELECT_U16, CONFIG);
    }
    /*%C Relance le timer de la page préférences */
    this->Timer.StartTimer(TIME_QUIT_PREFERENCES,TimerQuitPreferences,FALSE);
    this->ModifyDown();
}
void Controller::ReturnToNodeTONodePrefScreenSave()
{
    this->ReturnToNodeTO();
    UWORD16 Id = this->GetCurrentNode()->GetEventNode()->GetId();
    if (Id == NodePrefBrightness)
        this->SetBrightness(this->GetBrightness());
    if (Id == NodePrefSoundLevel)    /*%C Reglage Volume */
    {
        DataBaseAccess::WriteValue(&this->MemoSoundLevel , SOUND_LEVEL_SELECT_U16, CONFIG);
        UWORD16 _Val = FALSE;
        DataBaseAccess::WriteValue(&_Val, TEST_VOLUME_U16, CONTROL);
    }
}
void Controller::MoveToModifNodePrefScreenSave()
{
    /*%C Relance le timer de la page préférences */
    this->Timer.StartTimer(TIME_QUIT_PREFERENCES,TimerQuitPreferences,FALSE);

    UWORD16 Id = this->GetCurrentNode()->GetEventNode()->GetId();
    if (Id == NodePrefSoundLevel)    /*%C Reglage Volume */
    {
        DataBaseAccess::ReadValue(&this->MemoSoundLevel , SOUND_LEVEL_SELECT_U16, CONFIG);
        this->LastSoundLevel = this->MemoSoundLevel;
        UWORD16 _Val = TRUE;
        DataBaseAccess::WriteValue(&_Val, TEST_VOLUME_U16, CONTROL);
    }

    this->MoveToModifNode();
}
void Controller::ReturnToNodePrefScreenSave()
{
    UWORD16 Id = this->GetCurrentNode()->GetEventNode()->GetId();
    if (Id == NodeModifPrefSoundLevel)   /*%C Reglage Volume */
    {
        UWORD16 _Val = FALSE;
        DataBaseAccess::WriteValue(&_Val, TEST_VOLUME_U16, CONTROL);
    }

    /*%C Relance le timer de la page préférences */
    this->Timer.StartTimer(TIME_QUIT_PREFERENCES,TimerQuitPreferences,FALSE);
    this->ReturnToNode();
}
/************************************************************************/
/* Description          : MoveTimeOut pour le noeud NodePrefScreenSave	*/
/*                        et suivants                                   */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveTimeOutNodePrefScreenSave()
{
    /*%C fin du timer de la page Préférences */
    this->Timer.StopTimer(TimerQuitPreferences);

    MenuControlNode* PtrNode = this->GetCurrentNode();
    MenuControlNode* PtrNodeTarget;

    PtrNodeTarget = this->GetNodeAt(PtrNode->GetEventNode()->GetIdNodeOnTimeOut());
    PtrNodeTarget = this->FindFirstValidNode(PtrNodeTarget,eGoDown);

    /*%C Verifie si le noeud d'arrivée est valide */
    if (!PtrNodeTarget->IsValid())
    {
        PtrNodeTarget = PtrNode;
    }

    /*%C arrive sur le noeud suivant */
    this->MoveCurrentNode(PtrNodeTarget);
}
/************************************************************************/
/* Description          : MoveTimeOut pour le noeud NodeHistAlBack	   */
/*                        et suivants                                   */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveTimeOutNodeHistAlBack()
{
    /*%C fin du timer de la page histo alarmes */
    this->Timer.StopTimer(TimerQuitHistoAlarme);

    MenuControlNode* PtrNode = this->GetCurrentNode();
    MenuControlNode* PtrNodeTarget;

    PtrNodeTarget = this->GetNodeAt(PtrNode->GetEventNode()->GetIdNodeOnTimeOut());
    PtrNodeTarget = this->FindFirstValidNode(PtrNodeTarget,eGoDown);

    /*%C Verifie si le noeud d'arrivée est valide */
    if (!PtrNodeTarget->IsValid())
    {
        PtrNodeTarget = PtrNode;
    }

    /*%C arrive sur le noeud suivant */
    this->MoveCurrentNode(PtrNodeTarget);
}

void Controller::MoveUpNodeHistAlBack()
{
    /*%C relance du timer de la page histo alarmes */
    this->Timer.StartTimer(TIME_QUIT_HISTO_ALARME,TimerQuitHistoAlarme,FALSE);

    this->MoveUp();
}
void Controller::MoveDownNodeHistAlBack()
{
    /*%C relance du timer de la page histo alarmes */
    this->Timer.StartTimer(TIME_QUIT_HISTO_ALARME,TimerQuitHistoAlarme,FALSE);

    this->MoveDown();
}

/************************************************************************/
/* Description          : MoveTimeOut pour les noeuds USB               */
/*                        et suivants                                   */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveTimeOutUSB()
{
    MenuControlNode* PtrNode = this->GetCurrentNode();
    MenuControlNode* PtrNodeTarget;

    PtrNodeTarget = this->GetNodeAt(PtrNode->GetEventNode()->GetIdNodeOnTimeOut());
    PtrNodeTarget = this->FindFirstValidNode(PtrNodeTarget,eGoDown);

    /*%C Verifie si le noeud d'arrivée est valide */
    if (!PtrNodeTarget->IsValid())
    {
        PtrNodeTarget = PtrNode;
    }

    /*%C arrive sur le noeud suivant */
    this->MoveCurrentNode(PtrNodeTarget);
}
/************************************************************************/
/* Description          : MoveUp & MoveDown pour le noeud NodeGraphGhost*/
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveUpNodeGraphGhost()
{
    this->FGraph.FreezeMonitoring(FALSE, TRUE);
}
void Controller::MoveDownNodeGraphGhost()
{
    this->FGraph.FreezeMonitoring(TRUE, TRUE);
}

/************************************************************************/
/* Description          :  MoveValid pour le noeud                      */
/*                         NodeCfgGraphBackPref			                  */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveValidNodeCfgGraphBackPref()
{
    /*%C Fin du timer de la page Config Graph */
    this->Timer.StopTimer(TimerQuitGraphConfig);
#ifdef HMI_CONFIG_CURVE_CFG
    this->MoveCurrentNode(this->GetNodeAt(NodePrefCurveConfig));
#endif   
}
/************************************************************************/
/* Description          : MoveValid pour le noeud NodePrefCurveConfig   */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveValidNodePrefCurveConfig()
{
    Timer.StartTimer(TIME_QUIT_GRAPH_CONFIG,TimerQuitGraphConfig,FALSE);

    MoveValid();
}

/************************************************************************/
/* Description          : MoveValid pour le noeud NodePrefTrend         */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveValidNodePrefTrend()
{
    /*%C Fin du timer de la page Préférence */
    this->Timer.StopTimer(TimerQuitPreferences);

    /*%C Lancement du timer de la page tendance (ventil report) */
    this->Timer.StartTimer(TIME_QUIT_VENTIL_REPORT,TimerQuitVentilReport,FALSE);

    MoveValid();
}

/************************************************************************/
/* Description          : MoveUp, MoveDown, ModifyUp, ModifyDown,		   */
/*						  MoveToModifNode, ReturnToNode pour les		         */
/*						  noeuds NodeCfgGraphVisu et suivants                 */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveUpNodeCfgGraphVisu()
{
    /*%C Relance le timer de la page Graph config */
    this->Timer.StartTimer(TIME_QUIT_GRAPH_CONFIG,TimerQuitGraphConfig,FALSE);
    this->MoveUp();
}
void Controller::MoveDownNodeCfgGraphVisu()
{
    /*%C Relance le timer de la page Graph config */
    this->Timer.StartTimer(TIME_QUIT_GRAPH_CONFIG,TimerQuitGraphConfig,FALSE);
    this->MoveDown();
}
void Controller::ModifyUpNodeCfgGraphVisu()
{
    /*%C Relance le timer de la page Graph config */
    this->Timer.StartTimer(TIME_QUIT_GRAPH_CONFIG,TimerQuitGraphConfig,FALSE);
    this->ModifyUp();
}
void Controller::ModifyDownNodeCfgGraphVisu()
{
    /*%C Relance le timer de la page Graph config */
    this->Timer.StartTimer(TIME_QUIT_GRAPH_CONFIG,TimerQuitGraphConfig,FALSE);
    this->ModifyDown();
}
void Controller::MoveToModifNodeCfgGraphVisu()
{
    /*%C Relance le timer de la page Graph config */
    this->Timer.StartTimer(TIME_QUIT_GRAPH_CONFIG,TimerQuitGraphConfig,FALSE);
    this->MoveToModifNode();
}
void Controller::ReturnToNodeCfgGraphVisu()
{
    /*%C Relance le timer de la page Graph config */
    this->Timer.StartTimer(TIME_QUIT_GRAPH_CONFIG,TimerQuitGraphConfig,FALSE);
    this->ReturnToNode();
}
void Controller::ReturnToNodeCfgGraphVisuVisu()
{
    UWORD16 Val;
    this->ReturnToNodeCfgGraphVisu();
    DataBaseAccess::ReadValue(&Val,CURVE_DISPLAY_TYPE_MODE_U16,CONFIG);
    /*%C Refresh Histo */
    if (Val == 1) this->LVSRepresentation.SetIntValue1(0);
}

/************************************************************************/
/* Description          : MoveTimeOut pour les noeuds NodeCfgGraphVisu  */
/*                        et suivants                     			      */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveTimeOutNodeCfgGraphVisu()
{
    Timer.StopTimer(TimerQuitGraphConfig);
#ifdef HMI_CONFIG_CURVE_CFG
    /* On sort de la fenetre config courbes : on relance le timer de la
     fenetre preferences */
    this->Timer.StartTimer(TIME_QUIT_PREFERENCES,TimerQuitPreferences,FALSE);

    MoveCurrentNode(this->GetNodeAt(NodePrefCurveConfig));
#endif   
}
/************************************************************************/
/* Description          : MoveUp, MoveDown pour le noeud NodeTrendBack  */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveUpNodeTrendBack()
{
    /*%C Relance le timer de la page ventil report */
    this->Timer.StartTimer(TIME_QUIT_VENTIL_REPORT,TimerQuitVentilReport,FALSE);
}
void Controller::MoveDownNodeTrendBack()
{
    /*%C Relance le timer de la page ventil report */
    this->Timer.StartTimer(TIME_QUIT_VENTIL_REPORT,TimerQuitVentilReport,FALSE);
}
void Controller::MoveValidNodeTrendBack()
{
    /*%C Stoppe le timer de la page ventil report */
    this->Timer.StopTimer(TimerQuitVentilReport);

    /*%C Relance le timer de la page préférence */
    this->Timer.StartTimer(TIME_QUIT_PREFERENCES,TimerQuitPreferences,FALSE);

    MoveValid();
}
void Controller::MoveTimeOutNodeTrendBack()
{
    /*%C Stoppe le timer de la page ventil report */
    this->Timer.StopTimer(TimerQuitVentilReport);

    /*%C Relance le timer de la page préférence */
    this->Timer.StartTimer(TIME_QUIT_PREFERENCES,TimerQuitPreferences,FALSE);

    MoveCurrentNode(GetNodeAt(NodePrefTrend));
}
/************************************************************************/
/* Description          : ReturnToNodeLoupe pour le noeud 1191        	*/
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeLoupe1191()
{
    this->ReturnToNodeLoupe();
}

/************************************************************************/
/* Description          : MoveDown pour le noeud NodeMaintPwmBlower     */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveDownNodeMaintPwmBlower()
{
    this->StopBlowerBurnTest();
    /*%C Effacement de la valeur de PWM */
    this->LOVPwmBlower.StopMonitoringMode();
    this->MoveDown();
}

/************************************************************************/
/* Description          : MoveUp pour le noeud NodeMaintPwmBlower       */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveUpNodeMaintPwmBlower()
{
    this->StopBlowerBurnTest();
    /*%C Effacement de la valeur de PWM */
    this->LOVPwmBlower.StopMonitoringMode();
    this->MoveUp();
}

/************************************************************************/
/* Description          : deplace le noeud courant vers le noeud de 	   */
/*						         calibration associe							      */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToModifNodeConsultCalib()
{
    if (this->CurrentNode != NULL)
    {
        ((AutoCalibValue*)this->CurrentNode->GetObject())->StartModifModeConsult();
    }

    /*%C affectation */
    this->SetCurrentNode(this->GetNodeAt(this->CurrentNode->GetEventNode()->GetIdNodeOnMonitor()));
}

/************************************************************************/
/* Description          : deplace le noeud courant vers le noeud de 	   */
/*						         calibration associe 									*/
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */ 
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToModifNodeConsultCalib2Value()
{
    if (this->CurrentNode != NULL)
    {
        ((ManualCalibTwoValue*)this->CurrentNode->GetObject())->StartModifModeConsult();
    }

    /*%C affectation */
    this->SetCurrentNode(this->GetNodeAt(this->CurrentNode->GetEventNode()->GetIdNodeOnMonitor()));
}

/************************************************************************/
/* Description          : deplace le noeud courant vers le noeud de base*/
/*						        suivant le type de touche						   */
/* Parametres en entree : 		                                          */
/*                                   								 	         */
/* Parametres en sortie : aucun											         */ 
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeOnConsultCalib()
{
    /*%C Quitte le noeud de modif */
    if (this->CurrentNode != NULL)
    {
        ((AutoCalibValue*)this->CurrentNode->GetObject())->StopModifModeConsult();
    }
    /*%C affectation du nouveau noeud*/
    this->SetCurrentNode(this->GetNodeAt(this->CurrentNode->GetEventNode()->GetIdNodeOnMonitor()));
}

/************************************************************************/
/* Description          : deplace le noeud courant vers le noeud de base*/
/*						        suivant le type de touche 						   */
/* Parametres en entree : 		                                          */
/*                                   								 	         */
/* Parametres en sortie : aucun											         */ 
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeOnConsultCalib2Value()
{
    /*%C Quitte le noeud de modif */
    if (this->CurrentNode != NULL)
    {
        ((ManualCalibTwoValue*)this->CurrentNode->GetObject())->StopModifModeConsult();
    }

    /*%C affectation du nouveau noeud */
    this->SetCurrentNode(this->GetNodeAt(this->CurrentNode->GetEventNode()->GetIdNodeOnMonitor()));
}

/************************************************************************/
/* Description          : deplace le noeud courant vers le prochain     */
/*						        noeud de consultation suivant le type de 		*/
/*						        touche										            */
/* Parametres en entree : 		                                          */
/*	                                                                  	*/
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToNextModifConsultCalib()
{
    /*%C Change de Valeur de modification */
    if (this->CurrentNode != NULL)
    {
        if (!((AutoCalibValue*)this->CurrentNode->GetObject())->ModifNextValueConsult())
        {
            ReturnToNodeOnConsultCalib();
        }
    }
}

/************************************************************************/
/* Description          : deplace le noeud courant vers le prochain     */
/*						        noeud de consultation suivant le type de 		*/
/*						        touche										            */
/* Parametres en entree : 		                                          */
/*	                                                                  	*/
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToNextModifConsultCalib2Value()
{
    /*%C Change de Valeur de modification */
    if (this->CurrentNode != NULL)
    {
        if (!((ManualCalibTwoValue*)this->CurrentNode->GetObject())->ModifNextValueConsult())
        {
            ReturnToNodeOnConsultCalib2Value();
        }
    }
}

/************************************************************************/
/* Description          : deplace le noeud courant vers le prochain     */
/*						        noeud afin de sauter un noeud de calibration  */
/* Parametres en entree : 		                                          */
/*	                                                                  	*/
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToNextNodeJumpCalib()
{
    MoveToNextModifNodeOnKey(eGoMonitor);
}

/************************************************************************/
/* Description          : Repart au noeud principal si appuis sur Monit	*/
/*								  pendant l'Auto Calibration						   */
/* Parametres en entree : 		                                          */
/*	                                                                  	*/
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeCalibAuto()
{       
    ReturnToNodeOnKey(eGoMonitor);

    /*%C  Arret de la calibration automatique dans tous les cas */
    this->Timer.StopTimer(TimerAutoCalibTest);
    this->Timer.StopTimer(TimerWaitCalibVerif);
    OnWait = FALSE;

    /*%C Arret monitoring blower */
    LOVPwmBlower.RefreshEnable(FALSE);
    LOVPwmBlower.StopMonitoringMode();
}

/************************************************************************/
/* Description          : ReturnToNodeLoupe pour le noeud NodeModifFsecu*/
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeLoupeNodeModifFsecu()
{
    LOVFrCMin.Refresh();
    ReturnToNodeLoupe();

}

/************************************************************************/
/* Description          : deplace le noeud courant vers le noeud de base*/
/*						  (sens = valid) avec effacement de la loupe	         */
/*						  touche										                  */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeLoupe1151()
{
    UWORD16 Val1, Val2, Mode;

    ReturnToNodeLoupe();

    DataBaseAccess::ReadValue(&Val1,ADJUST_TI_MIN_U16,ADJUST);
    DataBaseAccess::ReadValue(&Val2,ADJUST_TI_MAX_U16,ADJUST);
    DataBaseAccess::ReadValue(&Mode,ADJUST_MODE_U16,CONFIG);
    /*%C Mise à jour Timin & Timax */
    if (Mode == PSVT)
    {
        LTTVTiS.SetValue1(Val1);
        LTTVTiS.SetValue2(Val2);
    }
}

/************************************************************************/
/* Description          : Noeud de Transfer USB                        */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToNextModifNodeUsbTransferSetOn()
{
    /*%C On se déplace sur le prochain noeud de Modif*/
    MoveToNextModifNode();
}
/************************************************************************/
/* Description          : Noeud de calibration Exp sur modif VTE        */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToNextModifNodeAlVteMin()
{
    UWORD16 VentilOn;
    UWORD16 CurrentMode;
    UWORD16 _Line, _Spacing, _Order;
    UWORD32 _PresentAndOrder;

    DataBaseAccess::ReadValue(&CurrentMode,ADJUST_MODE_U16,CONFIG);
    DataBaseAccess::ReadValue(&VentilOn, VENTIL_AUTHORIZATION_U16, CONTROL);

    if (!VentilOn)
    {
        /*%C debut de la demande de calibration */
        this->CurrentNode->GetObject()->RefreshEnable(FALSE);
        LSTICalibQExp.SetIntValue1(0);

        /*%C Récupération de l'order d'affichage du noeud NodeAlVte */
        _PresentAndOrder = IsNodeInTree((e_MODE_TYPES)CurrentMode, NodeAlVte, NodeAlarm, cAlarmEndNode);
        if ( _PresentAndOrder)
            _Order =  _PresentAndOrder & 0x7FFFFFFF;
        else
            _Order = 0;

        /*%C Récupération de la première ligne du tableau des alarmes */
        _Line = FAlarme.GetFirstLineOfTable();

        /*%C Récupération de l'espace entre les lignes du tableau des alarmes */
        _Spacing = FAlarme.GetSpacingOfTable();

        /*%C Réajustement de la ligne d'affichage */
        _Line += _Spacing * (_Order - 1);
        LSTICalibQExp.SetLine(_Line);

        /* Mise à jour de la colonne d'affichage */
        this->UpdateColNodeAlCalibVte();

        LSTICalibQExp.Show();

        /*%C Gestion de la loupe */
        Label*  EditableObject1 = (Label*)&this->LSTICalibQExp;
        EditableObject1->SetLoupe(this->CurrentLoupe);
        if (CurrentLoupe != NULL)
        {
            this->CurrentLoupe->DisplayMessage(FALSE);
            this->CurrentLoupe->SetMessage((UBYTE*)cMSG_CalibQExpTab[GetLanguage()]);
            this->CurrentLoupe->DisplayMessage(TRUE);
        }

        /*%C Retour traitements normaux */
        MoveToNextModifNode();

        /*%C initialisation de la valeur de la loupe */
        if (CurrentLoupe != NULL)
            this->CurrentLoupe->SetValue(this->LSTICalibQExp.GetValue1());
    }
    else
    {
        /*%C saut de la calibration (On se place sur le noeud de */
        /*%C calib sans traitement) */
        MoveToNextModifNode();
        /*%C force le besoin de calibration à false */
        LSTICalibQExp.SetIntValue1(0);
        /*%C On demande passe le noeud de calibration */
        MoveToNextModifNodeAlCalibVte();
    }
}
/************************************************************************/
/* Description          : Noeud d'attente de fin de calibration Exp     */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToNextModifNodeAlCalibVte()
{
    e_BOOL _IsVisible = FALSE;

    /*%C Test du choix de calibration */
    if (LSTICalibQExp.GetIntValue1() == 1)
    {
        /* Change Node -> Move to the calib Node */
        SetCurrentNode(this->GetNodeAt(NodeAlCalibVte2));
        /* Display Message Calib processing */
        if (CurrentLoupe != NULL)
        {
            this->CurrentLoupe->DisplayMessage(FALSE);
            this->CurrentLoupe->SetMessage((UBYTE*)cMSG_CalibQExpProcessing[GetLanguage()]);
            this->CurrentLoupe->DisplayMessage(TRUE);
        }
        _IsVisible = LSTICalibQExp.IsVisible();
        LSTICalibQExp.Hide(); 
        LSTICalibQExp.SetVisible(FALSE);
        LSTICalibQExp.SetValue1((char*)"...");
        /* Mise à jour de la colonne d'affichage */
        this->UpdateColNodeAlCalibVte();
        LSTICalibQExp.SetVisible(_IsVisible);
        LSTICalibQExp.Show();

        /* AutoReload Timer Calib */
        this->Timer.StartTimer(TIME_WAIT_CALIB_VERIF,TimerWaitCalibQExp,TRUE);
        /* Lauch AutoCalibration */
        UWORD16 Val = SEGMENT_1;
        DataBaseAccess::WriteValue( &Val,
                                    CALIB_FLOW_EXH_REQ_U16,
                                    CONTROL);
        /* Calibration State */
        MoveToCalibAuto();
    }
    else
    {
        /*%C Fin de la demande de calibration */
        ReturnToNodeToCalibNodeAlCalibVte();
    }
}

/************************************************************************/
/* Description          : Noeud de calibration Exp               			*/
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToCalibAuto()
{
    UWORD16 Val;
    UWORD16 MaxPoints;

    MaxPoints = UpdateCalibrationPoints();

    /*%C  Determine if the checking of the calibration is made  */
    DataBaseAccess::ReadValue(  &Val,
                                CALIB_FLOW_EXH_REQ_U16,
                                CONTROL);

    switch (Val)
    {
    case TEST_LIMITES_OK :
    case TEST_LIMITES_FALSE :
        /* Is it the last point */
        if (this->SegmentNumber < MaxPoints)
        {
            /* Calib the next point */
            this->SegmentNumber = this->SegmentNumber + 1;
            DataBaseAccess::WriteValue( &this->SegmentNumber,
                                        CALIB_FLOW_EXH_REQ_U16,
                                        CONTROL);
        }
        else
        {
            /* End of calibration */
            Val = NO_CALIB;
            DataBaseAccess::WriteValue( &Val,
                                        CALIB_FLOW_EXH_REQ_U16,
                                        CONTROL);
            this->SegmentNumber = 1;
            ReturnToNodeToCalibNodeAlCalibVte();
        }
        break;

    default :
        /* Nothing */
        break;
    }
}

/************************************************************************/
/* Description          : Noeud de fin de calibration Exp               */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeTOLoupeNodeAlCalibVte()
{
    //fin du blink
    this->BTable.RemoveElement(this->CurrentNode->GetObject());

    //affectation
    this->SetCurrentNode(this->GetNodeAt(this->CurrentNode->GetEventNode()->GetIdNodeOnValid()));

    /*%C Gestion de la loupe */
    if (CurrentLoupe != NULL)
        this->CurrentLoupe->DisplayMessage(FALSE);

    //Effacement du noeud de calib
    LSTICalibQExp.Hide();

    //Affichage du noeud courant
    this->CurrentNode->GetObject()->RefreshEnable(TRUE);
    LOVVteMl.ForceRefresh();

    ReturnToNodeTOLoupe();
}

/************************************************************************/
/* Description          : Noeud de fin de calibration Exp               */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeToCalibNodeAlCalibVte()
{

    /* Stop Timer Calib */
    this->Timer.StopTimer(TimerWaitCalibQExp);

    /*%C Fin de la demande de calibration */
    MoveToNextModifNode();

    /*%C Gestion de la loupe */
    if (CurrentLoupe != NULL)
        this->CurrentLoupe->DisplayMessage(FALSE);

    /*%C Rafraichissement de la valeur afin de resynchroniser la loupe */
    /*%C et donc d'afficher la valeur */
    LOVVteMl.RefreshValue2();

    LSTICalibQExp.Hide();
    this->CurrentNode->GetObject()->RefreshEnable(TRUE);
    LOVVteMl.ForceRefresh();
}

/************************************************************************/
/* Description          : Noeud de Modif demande de calib Q Exp         */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ModifyUpNodeAlCalibVte()
{
    e_BOOL _IsVisible = LSTICalibQExp.IsVisible();
    LSTICalibQExp.Hide();
    LSTICalibQExp.SetVisible(FALSE);

    /*%C Execute the controller Modify Up fonction */
    ModifyUp();

    /* Mise à jour de la colonne d'affichage */
    UpdateColNodeAlCalibVte();
    LSTICalibQExp.SetVisible(_IsVisible);
    LSTICalibQExp.Show();   

    /*%C Display the calibration message */
    if (CurrentLoupe != NULL)
    {
        this->CurrentLoupe->SetMessage((UBYTE*)cMSG_CalibQExpTab[GetLanguage()]);
        this->CurrentLoupe->DisplayMessage(TRUE);
    }
}

/************************************************************************/
/* Description          : Noeud de Modif demande de calib Q Exp         */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ModifyDownNodeAlCalibVte()
{
    e_BOOL _IsVisible = LSTICalibQExp.IsVisible();
    LSTICalibQExp.Hide();
    LSTICalibQExp.SetVisible(FALSE);

    /*%C Execute the controller Modify Down fonction */
    ModifyDown();

    /* Mise à jour de la colonne d'affichage */
    UpdateColNodeAlCalibVte();
    LSTICalibQExp.SetVisible(_IsVisible);
    LSTICalibQExp.Show();   

    /*%C Display the calibration message */
    if (CurrentLoupe != NULL)
    {
        this->CurrentLoupe->SetMessage((UBYTE*)cMSG_CalibQExpTab[GetLanguage()]);
        this->CurrentLoupe->DisplayMessage(TRUE);
    }
}
/************************************************************************/
/* Description          : Noeud de Modif demande de calib Q Exp         */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::UpdateColNodeAlCalibVte()
{
    UWORD16 _Size, _Width, _Col;

    _Size = Tools::GetStringPixelSize(LSTICalibQExp.GetValue1(),LSTICalibQExp.GetFontValue1());
    _Width = FAlarme.GetPatientWidthOfTable();
    _Col = FAlarme.GetPatientColOfTable();
    LSTICalibQExp.SetCol(_Col + (_Width - _Size)/2 + 1);
}
/************************************************************************/
/* Description          : Noeud de Modif demande de calib Q Exp         */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::UpdateColNodeAlCalibFiO2()
{
    UWORD16 _Size, _Width, _Col;

    _Size = Tools::GetStringPixelSize(LSTICalibFiO2.GetValue1(),LSTICalibFiO2.GetFontValue1());
    _Width = FAlarme.GetPatientWidthOfTable();
    _Col = FAlarme.GetPatientColOfTable();
    LSTICalibFiO2.SetCol(_Col + (_Width - _Size)/2 + 1);
}

/************************************************************************/
/* Description          : Noeud de calibration FiO2                     */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToNextModifNodeAlFiO2Min()
{
    UWORD16 VentilOn;
    UWORD16 CurrentMode;
    UWORD16 _Line, _Spacing, _Order;
    UWORD32 _PresentAndOrder;

    DataBaseAccess::ReadValue(&CurrentMode,ADJUST_MODE_U16,CONFIG);
    DataBaseAccess::ReadValue(&VentilOn, VENTIL_AUTHORIZATION_U16, CONTROL);

    if (this->IsFio2Sensor())
    {
        /*%C debut de la demande de calibration */
        this->CurrentNode->GetObject()->RefreshEnable(FALSE);
        LSTICalibFiO2.SetIntValue1(0);

        /*%C Récupération de l'order d'affichage du noeud NodeAlFiO2 */
        _PresentAndOrder = IsNodeInTree((e_MODE_TYPES)CurrentMode, NodeAlFiO2, NodeAlarm, cAlarmEndNode);
        if ( _PresentAndOrder)
            _Order =  _PresentAndOrder & 0x7FFFFFFF;
        else
            _Order = 0;

        /*%C Récupération de la première ligne du tableau des alarmes */
        _Line = FAlarme.GetFirstLineOfTable();
        /*%C Récupération de l'espace entre les lignes du tableau des alarmes */
        _Spacing = FAlarme.GetSpacingOfTable();

        /*%C Réajustement de la ligne d'affichage */
        _Line += _Spacing * (_Order - 1);
        LSTICalibFiO2.SetLine(_Line);

        /* Mise à jour de la colonne d'affichage */
        this->UpdateColNodeAlCalibFiO2();

        LSTICalibFiO2.Show();

        /*%C Gestion de la loupe */
        Label*  EditableObject1 = (Label*)&this->LSTICalibFiO2;
        EditableObject1->SetLoupe(this->CurrentLoupe);

        if (CurrentLoupe != NULL)
        {
            this->CurrentLoupe->DisplayMessage(FALSE);
            this->CurrentLoupe->SetMessage((UBYTE*)cMSG_CalibFiO2Tab[GetLanguage()]);
            this->CurrentLoupe->DisplayMessage(TRUE);
        }

        /*%C Retour traitements normaux */
        MoveToNextModifNode();

        /*%C initialisation de la valeur de la loupe */
        if (CurrentLoupe != NULL)
            this->CurrentLoupe->SetValue(this->LSTICalibFiO2.GetValue1());
    }
    else
    {
        /*%C saut de la calibration (On se place sur le noeud de */
        /*%C calib sans traitement) */
        MoveToNextModifNode();
        /*%C force le besoin de calibration à false */
        LSTICalibFiO2.SetIntValue1(0);
        /*%C On demande passe le noeud de calibration */
        MoveToNextModifNodeAlCalibFiO2();
    }
}
/************************************************************************/
/* Description          : Noeud d'attente de fin de calibration FiO2    */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToNextModifNodeAlCalibFiO2()
{
    e_BOOL _IsVisible = FALSE;

    /*%C Test du choix de calibration */
    if (LSTICalibFiO2.GetIntValue1() == 1)
    {
        /* Change Node -> Move to the calib Node */
        SetCurrentNode(this->GetNodeAt(NodeAlCalibFiO2_2));

        /* Display Message Calib processing */
        if (CurrentLoupe != NULL)
        {
            this->CurrentLoupe->DisplayMessage(FALSE);
            this->CurrentLoupe->SetMessage((UBYTE*)cMSG_CalibFiO2Processing[GetLanguage()]);
            this->CurrentLoupe->DisplayMessage(TRUE);
        }

        _IsVisible = LSTICalibFiO2.IsVisible();
        LSTICalibFiO2.Hide();
        LSTICalibFiO2.SetVisible(FALSE);
        LSTICalibFiO2.SetValue1((char*)"...");
        /* Mise à jour de la colonne d'affichage */
        this->UpdateColNodeAlCalibFiO2();
        LSTICalibFiO2.SetVisible(_IsVisible);
        LSTICalibFiO2.Show();

        /* Launch AutoCalibration */
        this->StartCalib = TRUE;
        MoveToCalibAutoFiO2();
    }
    else
    {
        /*%C Fin de la demande de calibration */
        ReturnToNodeToCalibNodeAlCalibFiO2();
    }
}

/************************************************************************/
/* Description          : Noeud de calibration Exp               			*/
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToCalibAutoFiO2()
{
    UWORD16 Val;

    if (this->StartCalib == TRUE)
    {
        /* Démarrage calibration du segment */
        this->StartCalib = FALSE;
        this->StartVerif = TRUE;
        this->Timer.StartTimer(TIME_WAIT_FIO2_DETECT,TimerWaitCalibFiO2,FALSE);
        UWORD16 Val = this->SegmentNumber;
        DataBaseAccess::WriteValue( &Val, CALIB_FIO2_REQ_U16, CONTROL);
    }
    else
    {
        if (this->StartVerif)
        {
            this->StartVerif = FALSE;
            /* Demande d'un test aux limites */
            Val = TEST_LIMITES_REQUEST;
            DataBaseAccess::WriteValue(&Val, CALIB_FIO2_REQ_U16, CONTROL);
        }

        /* Controle du test aux limites  */
        DataBaseAccess::ReadValue(    &Val, CALIB_FIO2_REQ_U16, CONTROL);

        switch (Val)
        {
        case TEST_LIMITES_OK :
        case TEST_LIMITES_FALSE :
            /* Is it the last point */
            if (this->SegmentNumber < FIO2_CALIB_POINTS_NUMBER)
            {
                /* Calib the next point */
                this->SegmentNumber = this->SegmentNumber + 1;
                this->StartCalib = TRUE;
                this->Timer.StartTimer(TIME_WAIT_CALIB_VERIF,TimerWaitCalibFiO2,FALSE);
            }
            else
            {
                /* End of calibration */
                Val = NO_CALIB;
                DataBaseAccess::WriteValue(   &Val,
                                              CALIB_FIO2_REQ_U16,
                                              CONTROL);
                this->SegmentNumber = 1;
                this->StartCalib = TRUE;
                this->StartVerif = FALSE;
                this->Timer.StopTimer(TimerWaitCalibFiO2);
                ReturnToNodeToCalibNodeAlCalibFiO2();
            }
            break;
        default :
            this->Timer.StartTimer(TIME_WAIT_CALIB_VERIF,TimerWaitCalibFiO2,FALSE);
            break;
        }
    }
}

/************************************************************************/
/* Description          : Noeud de fin de calibration FiO2              */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeTOLoupeNodeAlCalibFiO2()
{
    //fin du blink
    this->BTable.RemoveElement(this->CurrentNode->GetObject());

    //affectation
    this->SetCurrentNode(this->GetNodeAt(this->CurrentNode->GetEventNode()->GetIdNodeOnValid()));

    /*%C Gestion de la loupe */
    if (CurrentLoupe != NULL)
        this->CurrentLoupe->DisplayMessage(FALSE);

    //Effacement du noeud de calib
    LSTICalibFiO2.Hide();

    //Affichage du noeud courant
    this->CurrentNode->GetObject()->RefreshEnable(TRUE);
    LTTVFiO2.ForceRefresh();

    ReturnToNodeTOLoupe();
}

/************************************************************************/
/* Description          : Noeud de fin de calibration FiO2              */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ReturnToNodeToCalibNodeAlCalibFiO2()
{

    /* Stop Timer Calib */
    this->Timer.StopTimer(TimerWaitCalibFiO2);

    /*%C Fin de la demande de calibration */
    MoveToNextModifNode();

    /*%C Gestion de la loupe */
    if (CurrentLoupe != NULL)
        this->CurrentLoupe->DisplayMessage(FALSE);

    /*%C Rafraichissement de la valeur afin de resynchroniser la loupe */
    /*%C et donc d'afficher la valeur */
    LTTVFiO2.RefreshValue2();

    LSTICalibFiO2.Hide();
    this->CurrentNode->GetObject()->RefreshEnable(TRUE);
    LTTVFiO2.ForceRefresh();
}

/************************************************************************/
/* Description          : Noeud de Modif demande de calib FiO2          */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ModifyUpNodeAlCalibFiO2()
{
    e_BOOL _IsVisible = LSTICalibFiO2.IsVisible();
    LSTICalibFiO2.Hide();   
    LSTICalibFiO2.SetVisible(FALSE);

    /*%C Execute the controller Modify Up fonction */
    ModifyUp();

    /* Mise à jour de la colonne d'affichage */
    UpdateColNodeAlCalibFiO2();
    LSTICalibFiO2.SetVisible(_IsVisible);
    LSTICalibFiO2.Show();

    /*%C Display the calibration message */
    if (CurrentLoupe != NULL)
    {
        this->CurrentLoupe->SetMessage((UBYTE*)cMSG_CalibFiO2Tab[GetLanguage()]);
        this->CurrentLoupe->DisplayMessage(TRUE);
    }
}

/************************************************************************/
/* Description          : Noeud de Modif demande de calib Q Exp         */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ModifyDownNodeAlCalibFiO2()
{
    e_BOOL _IsVisible = LSTICalibFiO2.IsVisible();
    LSTICalibFiO2.Hide();
    LSTICalibFiO2.SetVisible(FALSE);

    /*%C Execute the controller Modify Down fonction */
    ModifyDown();

    /* Mise à jour de la colonne d'affichage */
    UpdateColNodeAlCalibFiO2();
    LSTICalibFiO2.SetVisible(_IsVisible);
    LSTICalibFiO2.Show();

    /*%C Display the calibration message */
    if (CurrentLoupe != NULL)
    {
        this->CurrentLoupe->SetMessage((UBYTE*)cMSG_CalibFiO2Tab[GetLanguage()]);
        this->CurrentLoupe->DisplayMessage(TRUE);
    }
}
/************************************************************************/
/* Description          : Noeud de Reset Compteur Patient              	*/
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveValidNodeModifConfPatientReset()
{
    UWORD16 _Value;
    UWORD16 _Id;

    /*%C End of Node */
    ReturnToNode();

    if (LVSSResetPatientHrs.GetIntValue1() == TRUE)
    {
        /*%C Do a Long Valid Bip */
        _Value = BIP_LONG;
        DataBaseAccess::WriteValue( &_Value,
                                    VALIDATION_BIP_U16,
                                    CONTROL);

        _Value = 0;

        DataBaseAccess::WriteValue(&_Value,CURRENT_PATIENT_COUNTER_HOUR_U16,CONTROL);
        DataBaseAccess::WriteValue(&_Value,CURRENT_PATIENT_COUNTER_MIN_U16,CONTROL);
        DataBaseAccess::WriteValue(&_Value,SAVED_PATIENT_COUNTER_HOUR_U16,CONFIG);
        DataBaseAccess::WriteValue(&_Value,SAVED_PATIENT_COUNTER_MIN_U16,CONFIG);

        /*%C Refresh Value */
        LOVPatientHrs.Refresh();

        /*%C Re-Initialize the TrendEvent and the DB_Trend */
        for (_Id = DB_TREND_VENTIL_HOUR ; _Id < end_of_db_trend_table ; _Id ++)
        {
            DataBaseAccess::WriteValue(&_Value,_Id,TREND);
        }

        /*%C At the end, go back to OFF value */
        LVSSResetPatientHrs.SetIntValue1((UWORD16)FALSE);
        LVSSResetPatientHrs.Refresh();
        /* erase NAND Flash Memory */
        InterfaceCppC::EraseNANDFlashMngt();

        InterfaceCppC::FlashWriteEvent(EVENT_RESET_PATIENT_COUNTER);
    }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet le deplacement vers le haut du noeud NodeConfPatientReset			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::MoveUpNodeConfPatientReset()
{
    /*%C Change Node */
    MoveUp();
    /*%C Refresh the value at OFF */
    LVSSResetPatientHrs.SetIntValue1(0);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Permet le deplacement vers le bas du noeud NodeConfPatientReset			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	  	NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::MoveDownNodeConfPatientReset()
{
    /*%C Change Node */
    MoveDown();
    /*%C Refresh the value at OFF */
    LVSSResetPatientHrs.SetIntValue1(0);
}

/************************************************************************/
/* Description          : Affiche la temperature batterie dans le       */
/*                        menu Control des mesures			               */
/* Parametres en entree : Flag : TRUE si capteur                        */
/* Parametres en sortie : aucun										         	*/
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ShowTempBattery(e_BOOL Flag)
{
    if (Flag)
    {
        LOVTempBat.StartMonitoringMode();
    }
    else
    {
        LOVTempBat.StopMonitoringMode();
    }
}
/************************************************************************/
/* Description          : Show the breath timing as I:E or I/T          */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::DisplayBreathTiming()
{
    // Display the I:E or I/T in the setting loupe
    UBYTE MessageString[60];
    UWORD16 Value;
    UWORD16 DisplayMode;

    DataBaseAccess::ReadValue(&DisplayMode, ADJUST_CYCLING_MODE_U16, CONFIG);

    if (DisplayMode == I_T)
    {
        DataBaseAccess::ReadValue(&Value, COMPUTED_I_T_U16, COMPUTE);

        UWORD16 IValue =  Value / 10;
        UWORD16 DValue =  Value - (IValue * 10);

        sprintf(    (char *)MessageString,
                    "%s = %2d.%01d %s",
                    LOVIT.GetName(),
                    IValue,
                    DValue,
                    LOVIT.GetNameUnit());
    }
    else
    {
        // display I:E
        UWORD16 NumValue;
        UWORD16 DenValue;

        DataBaseAccess::ReadValue(&NumValue, COMPUTED_IE_NUMERATOR_U16, COMPUTE);
        DataBaseAccess::ReadValue(&DenValue, COMPUTED_IE_DENOMINATOR_U16, COMPUTE);

        UWORD16 IDenValue =  DenValue / 10;
        UWORD16 FDenValue =  DenValue - (IDenValue * 10);

        if ( (IDenValue >= 100)
             || ((IDenValue <= 1) && (FDenValue == 0)) )
        {
            sprintf(    (char *)MessageString,
                        "%s = %d:%d",
                        LIE.GetName(),
                        NumValue / 10,
                        IDenValue);
        }
        else
        {
            sprintf(    (char *)MessageString,
                        "%s = %d:%d.%01d",
                        LIE.GetName(),
                        NumValue / 10,
                        IDenValue,
                        FDenValue);
        }
    }

    TopMessage.SetMessage(MessageString, NO);
    TopMessage.Show();
}
/************************************************************************/
/* Description          : Modif Up de NodeInspTime                     */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ModifyUpNodeInspTime()
{
    ModifyUp();
    DisplayBreathTiming();
}
/************************************************************************/
/* Description          : Modif Down de NodeInspTime                    */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ModifyDownNodeInspTime()
{
    ModifyDown();
    DisplayBreathTiming();
}
/************************************************************************/
/* Description          : Arrivée sur le noeud de modif de NodeInspTime */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::MoveToModifNodeLoupeNodeInspTime()
{
    UWORD16 Value;
    // update the compute variables used to display I:E and I/T values in
    // the Inspiratory-Time setting loupe

    DataBaseAccess::ReadValue(&Value, ADJUST_TI_CONTROL_U16, ADJUST);
    DataBaseAccess::WriteValue(&Value, COMPUTED_TI_CONTROL_U16, COMPUTE);

    DataBaseAccess::ReadValue(&Value, ADJUST_CONTROL_R_U16, ADJUST);
    DataBaseAccess::WriteValue(&Value, COMPUTED_RATE_U16, COMPUTE);

    DB_ComputeBreathTimingRatios();

    // pass control to the actual modifcation node
    MoveToModifNodeLoupe();
    DisplayBreathTiming();
}
/************************************************************************/
/* Description          : Modif Up en pression relative                 */
/* Parametres en entree : aucun	                                        */
/* Parametres en sortie : aucun							     	        */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ModifyUpNodePlusPeep()
{
    UBYTE MessageString[150];

    this->ModifyUp();

    BuildPressureMessage(this->CurrentNode, this->GetNodeAt(NodePe), MessageString);

    this->TopMessage.SetMessage(MessageString, NO);
    this->TopMessage.Show();
}
/************************************************************************/
/* Description          : Modif Down en pression relative                 */
/* Parametres en entree : aucun	                                        */
/* Parametres en sortie : aucun							     	        */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ModifyDownNodePlusPeep()
{
    UBYTE MessageString[150];

    this->ModifyDown();

    BuildPressureMessage(this->CurrentNode, this->GetNodeAt(NodePe), MessageString);

    this->TopMessage.SetMessage(MessageString, NO);
    this->TopMessage.Show();
}
/************************************************************************/
/* Description: Modif Down en pression relative sur le noeud peep       */
/*                                                                      */
/* Parametres en entree : aucun	                                        */
/* Parametres en sortie : aucun							     	        */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ModifyDownPeepNodePlusPeep()
{
    UBYTE MessageString[150];
    MenuControlNode* pressure_node;

    this->ModifyDown();

    pressure_node = GetPressureNode();

    BuildPressureMessage(pressure_node, this->CurrentNode, MessageString);

    this->TopMessage.SetMessage(MessageString, NO);
    this->TopMessage.Show();
}
/************************************************************************/
/* Description: Modif Up en pression relative sur le noeud peep         */
/*                                                                      */
/* Parametres en entree : aucun	                                        */
/* Parametres en sortie : aucun							     	        */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::ModifyUpPeepNodePlusPeep()
{
    UBYTE MessageString[150];
    MenuControlNode* pressure_node;

    this->ModifyUp();

    pressure_node = GetPressureNode();

    BuildPressureMessage(pressure_node, this->CurrentNode, MessageString);

    this->TopMessage.SetMessage(MessageString, NO);
    this->TopMessage.Show();
}
/************************************************************************/
/* Description: csontruction du message (equation PEEP + pression)      */
/*                                                                      */
/* Parametres en entree : aucun	                                        */
/* Parametres en sortie : aucun							     	        */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::BuildPressureMessage(  MenuControlNode* node1,
                                        MenuControlNode* node2,
                                        UBYTE* buffer)
{
    UWORD16 Value;
    if (node1 && node2)
    {
        Value = ((LabelOneValue*) node1->GetObject())->GetFullValue();
        Value += ((LabelOneValue*) node2->GetObject())->GetFullValue();
        sprintf( (char *)buffer,
                 "%s + %s|= %2d %s",
                 ((LabelOneValue*)node1->GetObject())->GetName(),
                 ((LabelOneValue*)node2->GetObject())->GetName(),
                 Value,
                 ((LabelOneValue*)node2->GetObject())->GetNameUnit());
    }
    else
    {
        buffer[0] = 0;
    }

}
/************************************************************************/
/* Description          : Retrouve le noeud de pression du mode en cours*/
/* Parametres en entree : aucun	                                        */
/* Parametres en sortie : aucun							     	        */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
MenuControlNode* Controller::GetPressureNode()
{
    e_BOOL found = FALSE;
    e_BOOL found_pcontrol = FALSE;
    UWORD16 value1, value2;
    MenuControlNode* node = NULL;

    if ((!found) && GetNodeAt(NodePi)->IsValid())
    {
        node = GetNodeAt(NodePi);
        found = TRUE;
    }
    if ((!found) && GetNodeAt(NodePi2)->IsValid())
    {
        node = GetNodeAt(NodePi2);
        found = TRUE;
    }
    if ((!found) && GetNodeAt(NodePControl)->IsValid())
    {
        node = GetNodeAt(NodePControl);
        found = TRUE;
        found_pcontrol = TRUE;
    }
    if ((!found) && GetNodeAt(NodePSupport)->IsValid())
    {
        node = GetNodeAt(NodePSupport);
        found = TRUE;
    }
    if (found_pcontrol && GetNodeAt(NodePSupport)->IsValid())
    {
        value1 = ((LabelOneValue*) GetNodeAt(NodePSupport)->GetObject())->GetFullValue();
        value2 = ((LabelOneValue*) GetNodeAt(NodePControl)->GetObject())->GetFullValue();
        node = value1 >= value2?GetNodeAt(NodePSupport):GetNodeAt(NodePControl);
    }

    return node;
}
/************************************************************************/
/* Description          : Arrete un timer                               */
/* Parametres en entree :                                               */
/*    _Timer : numéro de timer                                          */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::StopTimer(UWORD16 _Timer)
{
    Timer.StopTimer(_Timer);
}
/************************************************************************/
/* Description          : Arrête tous les affichages 100% O2 et         */
/*                        commande l'arrêt auprès du système.           */
/* Parametres en entree : aucun	                                       */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Controller::Stop100FiO2()
{
    (void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
#ifdef HMI_CONFIG_100_FIO2
    UWORD16 Val;

    BTable.RemoveElement(&this->LOVFiO2);
    DataBaseAccess::ReadValue(&Val,ADJUST_FIO2,CONFIG);
    LOVFiO2.SetValue1(Val);
    Val = FALSE;
    InterfaceCppC::ActiveLed(LED_WHITE, NO_LED);
    DataBaseAccess::WriteValue(&Val,FIO2_100_ACTIVE,CONTROL);
    Timer.StopTimer(Timer100PrCentO2);
#endif
}
/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C                                                                          */
/*%C                                                                          */
/*%I Input Parameter :                                                        */
/*%I 		NONE                                                              */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O Output Parameter :                                                       */
/*%O 		NONE                                                              */
/******************************************************************************/
UWORD16 Controller::UpdateCalibrationPoints()
{
    UWORD16 Val;
    UWORD16 PointsNb;
    DataBaseAccess::ReadValue(&Val,ADJUST_PEDIATRIC_CIRCUIT_U16,CONFIG);
    if (Val)
    {
        PointsNb = FLOW_CALIB_POINTS_NUMBER_4_PEDIATRIC_EXHAL;
        EventNodeMaintFlowExp7.SetOnTimeOut(&Controller::VerifAndReturnToNodeCalib);
    }
    else
    {
        PointsNb = FLOW_CALIB_POINTS_NUMBER;
        EventNodeMaintFlowExp7.SetOnTimeOut(&Controller::VerifAndMoveToNextModifNodeCalib);
    }

    LOVFlowExp.SetNbSegment(PointsNb);
    return PointsNb;
}
/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C                                                                          */
/*%C                                                                          */
/*%I Input Parameter :                                                        */
/*%I 		NONE                                                              */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O Output Parameter :                                                       */
/*%O 		NONE                                                              */
/******************************************************************************/
void Controller::ReturnToNodePediatric()
{
    /*%C Updating calibration points number */
    UpdateCalibrationPoints();

    /*%C Relance le timer de la page préférences */
    this->Timer.StartTimer(TIME_QUIT_PREFERENCES,TimerQuitPreferences,FALSE);

    ReturnToNode();
}


/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C                                                                          */
/*%C  Called when user press up on the Restore Default Setting.         	  */
/*%C                                                                          */
/*%I Input Parameter : 														  */
/*%I 	  	NONE														  	  */
/*%IO Input/Output : 														  */
/*%IO		NONE															  */
/*%O Output Parameter : 													  */
/*%O 		NONE												  			  */
/******************************************************************************/
void Controller::MoveUpNodeConfRestoreDefaultSetting()
{
    /*%C Change Node */
    MoveUp();
}

/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C                                                                          */
/*%C  Called when user press down on the Restore Default Setting.			  */
/*%C                                                                          */
/*%I Input Parameter : 														  */
/*%I 	  	NONE															  */
/*%IO Input/Output : 														  */
/*%IO		NONE															  */
/*%O Output Parameter : 													  */
/*%O 		NONE												  			  */
/******************************************************************************/
void Controller::MoveDownNodeConfRestoreDefaultSetting()
{
    /*%C Change Node */
    MoveDown();
}


/************************************************************************/
/* Description : Restores All Settings to Manufactoring defualts        */
/*                                                                      */
/*%I Input Parameter :                                                  */                                                                      
/*%I 	  	NONE	                                                    */                                                                              
/*%IO Input/Output :                                                    */                                                                       
/*%IO		NONE		                                                */                                                                         
/*%O Output Parameter :                                                 */                                                                     
/*%O 		NONE	                                                    */
/************************************************************************/
void Controller::MoveValidNodeModifConfRestoreDefaultSetting()
{
	UWORD16 Id = 0;
   
	// Validate that the Restore Default is set to YES before the ventilator
	// Restores all default settings except Language, Date and Time.
	if (LVSSRestoreDefaultSettings.GetIntValue1() == TRUE)
	{
		// Ping the watch dog so that the vent doesn't reset.
		It_watchdog();

		// Restore manufactoring defaults for all Patient settings
		for (Id=0;Id<end_of_adjust_table;Id++)
		{
			// Write Default Settings for VOL 
			do
			{
				DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[Id],
										cDB_VOL_TEST_ADJUST_DB[Id].defvalue); 
				// Ping the watch dog so that the vent doesn't reset.
				It_watchdog();

				EEP_FIFO_PushOneData(&EEP_DB_VOL_Adjust[Id],
									 READ_EEP);
				// Ping the watch dog so that the vent doesn't reset.
				It_watchdog();
			}  
			while (EEP_DB_VOL_Adjust[Id] != cDB_VOL_TEST_ADJUST_DB[Id].defvalue);

			// Ping the watch dog so that the vent doesn't reset.
			It_watchdog();

			// Write Default Settings for PSV
			do
			{
				DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[Id],
										cDB_PSV_TEST_ADJUST_DB[Id].defvalue);

				// Ping the watch dog so that the vent doesn't reset.
				It_watchdog();

				EEP_FIFO_PushOneData(&EEP_DB_PSV_Adjust[Id],
									 READ_EEP);
				// Ping the watch dog so that the vent doesn't reset.
				It_watchdog();
			}   
			while (EEP_DB_PSV_Adjust[Id] != cDB_PSV_TEST_ADJUST_DB[Id].defvalue);

			// Ping the watch dog so that the vent doesn't reset.
			It_watchdog();

			// Write Default Settings for CPAP 
			do
			{
				DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[Id],
										cDB_CPAP_TEST_ADJUST_DB[Id].defvalue);

				// Ping the watch dog so that the vent doesn't reset.
				It_watchdog();

				EEP_FIFO_PushOneData(&EEP_DB_CPAP_Adjust[Id],
									 READ_EEP);

				// Ping the watch dog so that the vent doesn't reset.
				It_watchdog();
			}   
			while (EEP_DB_CPAP_Adjust[Id] != cDB_CPAP_TEST_ADJUST_DB[Id].defvalue);

			// Ping the watch dog so that the vent doesn't reset.
			It_watchdog();

			// Write Default Settings for VSIMV 
			do
			{
				DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[Id],
										cDB_VSIMV_TEST_ADJUST_DB[Id].defvalue);

				// Ping the watch dog so that the vent doesn't reset.
				It_watchdog();

				EEP_FIFO_PushOneData(&EEP_DB_VSIMV_Adjust[Id],
									 READ_EEP);

				// Ping the watch dog so that the vent doesn't reset.
				It_watchdog();
			}   
			while (EEP_DB_VSIMV_Adjust[Id] != 
				   cDB_VSIMV_TEST_ADJUST_DB[Id].defvalue);

			// Ping the watch dog so that the vent doesn't reset.
			It_watchdog();

			// Write Default Settings for PRES 
			do
			{
				DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[Id],
										cDB_PRES_TEST_ADJUST_DB[Id].defvalue);
				// Ping the watch dog so that the vent doesn't reset.
				It_watchdog();

				EEP_FIFO_PushOneData(&EEP_DB_PRES_Adjust[Id],
									 READ_EEP);

			    // Ping the watch dog so that the vent doesn't reset.
				It_watchdog();
			}   
			while (EEP_DB_PRES_Adjust[Id] != cDB_PRES_TEST_ADJUST_DB[Id].defvalue);

			// Ping the watch dog so that the vent doesn't reset.
			It_watchdog();

			// Write Default Settings for PSIMV 
			do
			{
				DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[Id],
										cDB_PSIMV_TEST_ADJUST_DB[Id].defvalue);

				// Ping the watch dog so that the vent doesn't reset.
				It_watchdog();

				EEP_FIFO_PushOneData(&EEP_DB_PSIMV_Adjust[Id],
									 READ_EEP);

				// Ping the watch dog so that the vent doesn't reset.
				It_watchdog();
			}
			while (EEP_DB_PSIMV_Adjust[Id] !=
				   cDB_PSIMV_TEST_ADJUST_DB[Id].defvalue);
		}

		// Ping the watch dog so that the vent doesn't reset.
		It_watchdog();

        // Reset most configuration settings back to manufactoring defaults
		for (Id=0;Id<end_of_db_config_table;Id++)
		{
            // Skip the Offset values and Machine Hours
			if (    (Id < OFFSET_INSP_FLOW_1_U16)
					|| ( (Id > OFFSET_VALVE_PRESS_2_U16)
						 &&(Id < SAVED_MACHINE_COUNTER_HOUR_U16) )
					|| (Id > SAVED_MACHINE_COUNTER_MIN_U16)
			   )
			{
				// Skip, Bad_erase, Language, Date and Time
				if (  (Id != BAD_ERASE_U16)
					  && (Id != ADJUST_LANGUAGE_U16) 
					  && (Id != RAZ_COUNTER_PAT_DATE_U16) 
					  && (Id != RAZ_COUNTER_PAT_MONTH_U16) 
					  && (Id != RAZ_COUNTER_PAT_YEAR_U16) 
					  && (Id != RAZ_COUNTER_PAT_HOUR_U16) 
					  && (Id != RAZ_COUNTER_PAT_MIN_U16) )
				{
					do
					{
						DB_WriteDataInEepAndRam(&EEP_DB_Config[Id],
												cDB_TEST_CONFIG_DB[Id].defvalue);

						// Ping the watch dog so that the vent doesn't reset.
						It_watchdog();

						EEP_FIFO_PushOneData(&EEP_DB_Config[Id],
											 READ_EEP);

						// Ping the watch dog so that the vent doesn't reset.
						It_watchdog();
					}
					while (EEP_DB_Config[Id] != cDB_TEST_CONFIG_DB[Id].defvalue);
				}

			}
			// Ping the watch dog so that the vent doesn't reset.
			It_watchdog();
		}

		// Ping the watch dog so that the vent doesn't reset.
		It_watchdog();

		/*%C At the end, go back to OFF value */
		LVSSRestoreDefaultSettings.SetIntValue1((UWORD16)FALSE);
		LVSSRestoreDefaultSettings.Refresh();

		// Refresh the Setup Screen.
		this->ShowMenu(NodeConfResetDefaultSetting);
		this->ShowFrame(FRAME_CONFIGURATION);
	}

	// Ping the watch dog so that the vent doesn't reset.
	It_watchdog();

	ReturnToNode();
}



/************************************************************************/
/* Description:  This function displays the helper message for          */
/*                   I sens setting.                                    */
/* Input parameters: 	none                                            */
/* Output parameters: 	none                                            */
/* Constraint                                                           */
/* 		Pre-conditions: 	None                                        */
/* 		Post-condition: 	None                                        */
/*		Exceptions: 		None                                        */
/************************************************************************/
void Controller::DisplayIsensHelperText()
{
   UWORD16 IsInspSensOFF;

    DataBaseAccess::ReadValue(&IsInspSensOFF, INSP_SENS_NO_SELECT_U16, ADJUST);

	BottomMessage.SetMessage((UBYTE *)cMSG_IsensHelperTxt[GetLanguage()], NO);

    // Only display INSP SENS helper text when changing INSP SENS between 0P to 5.
	if (IsInspSensOFF == FALSE)
	{
		BottomMessage.Show();
	}
	else
	{
        BottomMessage.Hide();
    }
}



/************************************************************************/
/* Description:  This function handles I sens setting increase changes. */
/*                   Specifically, when the user press the up           */
/*                   key, this function gets called.                    */
/* Input parameters: 	none                                            */
/* Output parameters: 	none                                            */
/* Constraint                                                           */
/* 		Pre-conditions: 	None                                        */
/* 		Post-condition: 	None                                        */
/*		Exceptions: 		None                                        */
/************************************************************************/
void Controller::ModifyUpNodeIsens()
{
    ModifyUp();
    DisplayIsensHelperText();
}

/************************************************************************/
/* Description:  This function handles I sens setting decrease changes. */
/*                   Specifically, when the user press the down         */
/*                   key, this function gets called.                    */
/* Input parameters: 	none                                            */
/* Output parameters: 	none                                            */
/* Constraint                                                           */
/* 		Pre-conditions: 	None                                        */
/* 		Post-condition: 	None                                        */
/*		Exceptions: 		None                                        */
/************************************************************************/
void Controller::ModifyDownNodeIsens()
{
    ModifyDown();
    DisplayIsensHelperText();
}




/************************************************************************/
/* Description          : This function handles I sens setting changes. */
/*                          Specifically, when the user press accept on */
/*                          the I sens node, this function gets called. */
/* Input parameters: 	none                                            */
/* Output parameters: 	none                                            */
/* Constraint                                                           */
/* 		Pre-conditions: 	None                                        */
/* 		Post-condition: 	None                                        */
/*		Exceptions: 		None                                        */
/************************************************************************/
void Controller::MoveToModifNodeLoupeNodeIsens()
{
    // pass control to the actual modifcation node
    MoveToModifNodeLoupe();
    DisplayIsensHelperText();
}


