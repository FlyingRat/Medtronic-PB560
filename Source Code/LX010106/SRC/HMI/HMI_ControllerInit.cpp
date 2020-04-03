/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ControllerInit.cpp                                  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Classe de gestion de l'initialisation de  l'application					   */
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
#include "HMI_Controller_Data.hpp"
#include "HMI_Setup1.hpp"

extern "C"
{
#include "enum.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Usb.h"
#include "DB_Rtc.h"
#include "DB_Current.h"

#ifdef _BORLAND
    #define DECLARATION_SYSTEM_DATAS
#endif
#include "System_Datas.h"

#ifdef _BORLAND
    #define DECLARATION_SETUP_DATAS
#endif
}


extern bool EraseFlag;


/******************************************************************************/
/*                           METHODES                									*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation du controler																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::Init() 
{
    UWORD16 Val,NodeId;

    ArrayNode = Controller_ArrayNode;

    /*%C Init de la langue */
    DataBaseAccess::ReadValue(&Val,ADJUST_LANGUAGE_U16,CONFIG);
    SetLanguage(Val);

    /*%C Init du MENU */
    InitGloblaEventNode();

    /*%CInit des fenetres */

    FVentilation.SetPage(VIDEO_PAGE1);
    FVentilation.init();

    FAlarme.SetPage(VIDEO_PAGE2);
    FAlarme.init();

    FHistoAlarme.SetPage(VIRTUAL_PAGE);
    FHistoAlarme.init();

    FConfiguration.SetPage(VIRTUAL_PAGE);
    FConfiguration.init();

    HMI_Setup1::GetInstance().Init();

    FPreference.SetPage(VIRTUAL_PAGE);
    FPreference.init();

    FMaintenance.SetPage(VIRTUAL_PAGE);
    FMaintenance.init();

    FHistoAno.SetPage(VIRTUAL_PAGE);
    FHistoAno.init();

    FVoltControl.SetPage(VIRTUAL_PAGE);
    FVoltControl.init();

    FWelcome.SetPage(VIRTUAL_PAGE);
    FWelcome.init();

    FGraph.SetPage(VIRTUAL_PAGE);
    FGraph.init();

    FGraphConfig.SetPage(VIRTUAL_PAGE);
    FGraphConfig.init();

    FBatteryMenu.SetPage(VIRTUAL_PAGE);
    FBatteryMenu.init();

    FUsb.SetPage(VIRTUAL_PAGE);
    FUsb.init();

    UsbDelayed.Init( &Timer, FUsb.GetMessageDialog(),  TimerUsbMessage);

    FTendance.SetPage(VIRTUAL_PAGE);
    FTendance.init();

    FCircuitCheck.SetPage(VIRTUAL_PAGE);
    FCircuitCheck.init();

    /*init de la zone au dessud e la loupe */
    TopMessage.SetParent(&FVentilation);

    TopMessage.SetWhithBox          (WHITH_VENTILBOX);
    TopMessage.InitGraphicBox       (40,
                                     195,
                                     35,
                                     WHITH_VENTILBOX,
                                     FALSE,
                                     FALSE,
                                     TRUE);
    TopMessage.SetLineLine1         (14);
    TopMessage.SetLineLine2         (29);
    TopMessage.SetLineLine3         (44);


    // Add text to the bottom of the Status/monitored data window
    // This is used to put a helper text for any setting diplayed 
    // in the Ventilation menu.
    BottomMessage.SetParent(&FVentilation);

    BottomMessage.SetWhithBox          (WHITH_VENTILBOX);
    BottomMessage.InitGraphicBox       (40,
                                     195,
                                     50,
                                     WHITH_VENTILBOX,
                                     FALSE,
                                     FALSE,
                                     TRUE);
    BottomMessage.SetLineLine1         (100);
    BottomMessage.SetLineLine2         (115);
    BottomMessage.SetLineLine3         (130);


    /*%C maj des noeuds */
    InitConfiguration();
    BuildTree();

    /*%C Construction des menus dynamiques */
    /*... les noeuds de calibration */
    RebuildEventNodeTreeForAllModes(cMaintCalibStartNode, cMaintCalibEndNode);

    /*... mise à jour des liens entre noeuds */
    NodeId = GetNodeAt(cMaintCalibStartNode)->GetEventNode()->GetIdNodeOnDown();
    /*... pour le premier noeud de calibration */
    GetNodeAt(NodeMaintSensorCal)->GetEventNode()->SetIdNodeOnValid(NodeId);
    GetNodeAt(NodeId)->GetEventNode()->SetIdNodeOnUp(NodeMaintSensorCal);
    GetNodeAt(cMaintCalibStartNode)->GetEventNode()->SetIdNodeOnUp(NodeMaintSensorCal);

    /*... pour le dernier noeud de calibration */
    NodeId = GetNodeAt(cMaintCalibEndNode)->GetEventNode()->GetIdNodeOnUp();
    GetNodeAt(NodeId)->GetEventNode()->SetIdNodeOnDown(NodeMaintPwmBlower);
    GetNodeAt(cMaintCalibEndNode)->GetEventNode()->SetIdNodeOnDown(NodeMaintPwmBlower);

    /*%C Initialisation des table de refresh du menu */

    /*%C Alway */
    RefreshTableAlarm[0] = NULL;

    /*%C Inspiration */
    RefreshTableAlarm[1] = &this->LOVVteMl;
    RefreshTableAlarm[2] = &this->LTOVFuiteLMin;
    RefreshTableAlarm[3] = &this->LOVFrCMin;
    RefreshTableAlarm[4] = &this->LTTVTiS;
    RefreshTableAlarm[5] = NULL;

    /*%C Expiration */
    RefreshTableAlarm[6] = &this->LOVVtiMl;
    RefreshTableAlarm[7] = &this->LOVPiMbar;
    RefreshTableAlarm[8] = NULL;

    /*%C XAlway */
    RefreshTableAlarm[9] = &this->LTTVSpO2;
    RefreshTableAlarm[10] = &this->LTTVFiO2;
    RefreshTableAlarm[11] = NULL;

    /*%C Initialisation des table de refresh du menu */
    /*%C Alway */
    RefreshTableMaintenance[0] = NULL;

    /*%C Insp */
    RefreshTableMaintenance[1] = NULL;

    /*%C Expiration */
    RefreshTableMaintenance[2] = NULL;

    /*%C Alway */
    RefreshTableMaintenance[3] = &this->LOVPatientPressure;
    RefreshTableMaintenance[4] = &this->LOVValvePressure;
    RefreshTableMaintenance[5] = &this->LOVFlowIns;
    RefreshTableMaintenance[6] = &this->LOVFlowExp;
    RefreshTableMaintenance[7] = &this->LOVFlowO2;
    RefreshTableMaintenance[8] = &this->LOVPressO2;
    RefreshTableMaintenance[9] = &this->LOVPwmBlower;
    RefreshTableMaintenance[10] = &this->LOVFiO2Concent;
    RefreshTableMaintenance[11] = NULL;

    /*%C Initialisation des table de refresh du menu */

    /*%C Alway */
    RefreshTableConfig[0] = &this->VTConf;
    RefreshTableConfig[1] = NULL;

    /*%C Inspiration */
    RefreshTableConfig[2] = NULL;

    /*%C Expiration */
    RefreshTableConfig[3] = NULL;

    /*%C XAlway */
    RefreshTableConfig[4] = &this->VDConf;
    RefreshTableConfig[5] = NULL;

    /*%C Initialisation des table de refresh du menu controle des tensions*/

    /*%C Alway */
    RefreshTableVolt[0] = NULL;

    /*%C Inspiration */
    RefreshTableVolt[1] = NULL;

    /*%C Expiration */
    RefreshTableVolt[2] = NULL;

    /*%C XAlway */
    RefreshTableVolt[3] = &this->LOVBuzzerVoltage;
    RefreshTableVolt[4] = NULL;

    /*%C Init du Buzzer */
    //BManager.Init(&Timer);

    /*%C Init des parametres ecouter */
    PSpy.AddElement( VENTIL_STATE_U16,
                     CONTROL,
                     VEN_INSPIRATION_TRIGGERED,
                     ProgInspTrigEvent);

    PSpy.AddElement(    VENTIL_STATE_U16,
                        CONTROL,
                        VEN_INSPIRATION_CONTROLED,
                        ProgInspControlEvent);

    PSpy.AddElement(    VENTIL_STATE_U16,
                        CONTROL,
                        VEN_EXHALATION,
                        ProgExhEvent);

    PSpy.AddElement( DISPLAY_BATTERY_U16,
                     CONTROL,
                     0,
                     ProgHideBatEvent);

    PSpy.AddElement( DISPLAY_BATTERY_U16,
                     CONTROL,
                     1,
                     ProgShowBatEvent);

    PSpy.AddElement(    VENTIL_REQ_U16,
                        CONFIG,
                        1,
                        ProgStartVentilOk);

    PSpy.AddElement(    VENTIL_REQ_U16,
                        CONFIG,
                        0,
                        ProgStartVentilKo);

    PSpy.AddElement( INHIBITED_BUZZER_U16,
                     CONTROL,
                     1,
                     ProgInibAlarmOK);

    PSpy.AddElement( INHIBITED_BUZZER_U16,
                     CONTROL,
                     0,
                     ProgInibAlarmNOK);

    PSpy.AddElement( CANCELLED_ALARM_U16,
                     CONTROL,
                     1,
                     ProgCancelAlarmOK);

    PSpy.AddElement( CANCELLED_ALARM_U16,
                     CONTROL,
                     0,
                     ProgCancelAlarmNOK);

    PSpy.AddElement( HIGH_PRESSURE_LED_REMINDER_U16,
                     CONTROL,
                     0,
                     ProgRemoveHighPressureAlarm);

    PSpy.AddElement(  VALVE_DETECTED_U16,
                      CONTROL,
                      FALSE,
                      ProgValveMissing);

    PSpy.AddElement(  VALVE_DETECTED_U16,
                      CONTROL,
                      TRUE,
                      ProgValveDetected);

    PSpy.AddElement(  BLOC_EXPI_DETECTED_U16,
                      CONTROL,
                      FALSE,
                      ProgBlocExpiMissing);

    PSpy.AddElement(  BLOC_EXPI_DETECTED_U16,
                      CONTROL,
                      TRUE,
                      ProgBlocExpiDetected);

    PSpy.AddElement(  DETECTED_FIO2_SENSOR,
                      CONTROL,
                      TRUE,
                      ProgFio2SensorOK);

    PSpy.AddElement(  DETECTED_FIO2_SENSOR,
                      CONTROL,
                      FALSE,
                      ProgFio2SensorNOK);

    PSpy.AddElement(  ERROR_SPO2_SENSOR_DETECTED,
                      CONTROL,
                      FALSE,
                      ProgSpo2SensorNoError);

    PSpy.AddElement(  ERROR_SPO2_SENSOR_DETECTED,
                      CONTROL,
                      TRUE,
                      ProgSpo2SensorError);

    PSpy.AddElement(  ALARM_CHECK_SUPPLY_U16,
                      ALARMS,
                      ALARM_FALSE,
                      ProgCheckSupplyNoError);

    PSpy.AddElement(  ALARM_CHECK_SUPPLY_U16,
                      ALARMS,
                      ALARM_TRUE,
                      ProgCheckSupplyError);

    PSpy.AddElement(  USB_ERROR_CODE_READY_IHM_U16,
                      USB,
                      TRUE,
                      ProgUsbErrorCodeReady);

    PSpy.AddElement(  USB_NEW_MODE_DETECTED,
                      USB,
                      TRUE,
                      ProgUsbNewModeDetected);

    PSpy.AddElement( START_MONITORING_U16,
                     CONTROL,
                     1,
                     ProgStartMonitoring);

    PSpy.AddElement( SUPPLY_BUS_FAILURE_U16,
                     CONTROL,
                     1,
                     ProgSupplyBusFailure);

    PSpy.AddElement( SUPPLY_BUS_FAILURE_U16,
                     CONTROL,
                     0,
                     ProgSupplyBusOK);

    PSpy.AddElement( EXHAL_FLOW_USE_U16,
                     CONTROL,
                     TRUE,
                     ProgExhalFlowUsed);

    PSpy.AddElement( EXHAL_FLOW_USE_U16,
                     CONTROL,
                     FALSE,
                     ProgExhalFlowUnused);

    /* Initialisation de l'affichage */
    Reset();

    SetEndOfInit(TRUE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                           */
/*%C Initialisation de l'affichage															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::Reset()
{
    UWORD16 Val;

    CurrentFrame = 0;
    CurrentVirtualFrame = 0;
    CurrentNode = GetNodeAt(NodeGhostEnd);

    /*%C Init Brithness */
    SetBrightness(GetBrightness());

    /*%C init du mode */
    DataBaseAccess::ReadValue(&Val,ADJUST_MODE_U16,CONFIG);
    switch (Val)
    {
    default:
    case VOL   : CurrentMode = VOL;
        break;
    case PSVT   : CurrentMode = PSVT;
        break;
    case PRES  : CurrentMode = PRES;
        break;
    case VSIMV : CurrentMode = VSIMV;
        break;
    case PSIMV : CurrentMode = PSIMV;
        break;
    case CPAP  : CurrentMode = CPAP;
        break;
    }
    ConsultMode = CurrentMode;

    /*%C init du changement de Mode */
    SetModeChange(FALSE);

    /*%C init du mode cyclage */
    DataBaseAccess::ReadValue(&Val,ADJUST_CYCLING_MODE_U16,CONFIG);
    SetMCycl((e_BOOL)Val);

    /*%C init de la convention trigger */
    DataBaseAccess::ReadValue(&Val,TRIGG_E_POSITIVE,CONFIG);
    SetTrigEPosSelected((e_BOOL)Val);

    /*%C init de la valve */
    DataBaseAccess::ReadValue(&Val,VALVE_DETECTED_U16,CONTROL);
    SendInfoValve((e_BOOL)Val);

    /*%C init de la convention de pression */
    DataBaseAccess::ReadValue(&Val,PRESSURE_SUPPORT_RELATIVE_U16,CONFIG);
    SetPressConvention((e_BOOL)Val);

    /*%C init des noeuds USB*/
    UsbUpdateNavigNodes(NodeVentil);

    /*%C init de l'unité de pression */
    DataBaseAccess::ReadValue(&Val,PRESSURE_UNIT_U16,CONFIG);
    SetPressureUnit(Val);

    /*%C init de l'activation/désactivation de l'alarme apnée */
    DataBaseAccess::ReadValue(&Val,APNEA_ALARM_ACTIVATION,CONFIG);
    SetInhibApneaOk((e_BOOL)(!(Val == TRUE)));

    /*%C init du Lock */
    DataBaseAccess::ReadValue(&Val,ADJUST_KEYLOCK_U16,CONFIG);
    ManageLock((e_BOOL)Val);

    /*%C Init de la loupe */
    CurrentLoupe = NULL;

    /*%C Init des pointeur courants */
    CurrentFrame = FRAME_VENTILATION;
    CurrentVirtualFrame = FRAME_WELCOME;

    /*%C init du flag de modif de noeud */
    SetModifNodeOn(FALSE);

    /*%C Init des parametres ecouter */
    PSpy.Reset();

    /*%C Lancement du spy */
    Timer.StartTimer(TIME_SPY_PARAM,TimerSpyPraram,TRUE);

    /*%C Preparation des pages Video */
    FVentilation.Show();
    FAlarme.Show();

    /*%C Initialisation effectuée (construction des noeuds),
        on peut maintenant impacter l'affichage */
    FVentilation.SetImpactDisplay(TRUE);
    FAlarme.SetImpactDisplay(TRUE);
    FGraph.SetImpactDisplay(TRUE);
    SetImpactDisplay(TRUE);

    /*%C Affichage du menu en fct du Mode */
    SetCurrentMode(GetCurrentMode());

    /*%C Affichage du noeud Préférence */
    GetNodeAt(NodePreference)->SetVisible(TRUE);

    /*%C lancement du timer de blink ,refresh  et Alarme */
    /*%C Temps minimum de scrutation < Temps d'expiration minimum */
    Timer.StartTimer(TIME_REFRESH_ALARM,TimerRefreshAlarm,TRUE);
    Timer.StartTimer(TIME_SWAP_ALARM,TimerSwapAlarm,TRUE);
    Timer.StartTimer(TIME_BLINK_EVENT,TimerBlinkEvent,TRUE);
    Timer.StartTimer(TIME_REFRESH,TimerRefresh,TRUE);

    /*C% P support setting Initialization */
    DataBaseAccess::ReadValue(&Val,P_SUPPORT_NO_SELECT_U16,ADJUST);
    SetPSupportNull((e_BOOL)Val);

    /*C% Gestion des noeuds de calib Q Exp et FiO2 menu Alarme */
    LSTICalibQExp.Hide();
    LSTICalibFiO2.Hide();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des Objets graphiques													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::InitConfiguration()
{
    UWORD16 LowLimit;
    UWORD16 HighLimit;

    UWORD16 _line;
    UWORD16 _col;
    UWORD16 _spacing;
    UWORD16 _colsep = 79;
    UWORD16 _colvalue = 83;
    UWORD16 Val, i;

    UWORD16 _CurrentLang ;
    DataBaseAccess::ReadValue(&_CurrentLang,ADJUST_LANGUAGE_U16,CONFIG);

    /*------------------------ fenetre Ventilation -------------------------------*/

    LModeVent.SetParent                 (&this->FVentilation);

    LModeVent.InitDbAccess              (ADJUST_MODE_U16,CONFIG);

    LModeVent.Init                          (FREE_SQUARE,
                                             NULL,
                                             18,
                                             4);

    LModeVent.SetNameMode               ((UBYTE**)cMSG_Mode,
                                         (UBYTE**)cMSG_Mode2,
                                         (UBYTE**)cMSG_Mode3,
                                         (UBYTE**)cMSG_EnableMode,
                                         (UBYTE**)cMSG_DisableMode);

    LOVVT.SetParent                     (&this->FVentilation);

    LOVVT.InitDbAccess                  ( ADJUST_VOL_CONTROL_U16,ADJUST);

    LOVVT.Init                              (FREE_SQUARE,
                                             (UBYTE**)cMSG_CurrantVolume,
                                             360,
                                             4 ,
                                             1000,
                                             (UBYTE**)cMSG_VolumeUnit);

    LOVVT.SetColSep                  (_colsep);

    LOVVT.SetColValue1               (_colvalue);


    /* Pi */                                    
    LOVPi.SetParent                  (&this->FVentilation);

    LOVPi.InitDbAccess               (ADJUST_P_CONTROL_U16,ADJUST);

    LOVPi.Init                       (FREE_SQUARE,
                                      (UBYTE**)cMSG_InsuflationPressureControl,
                                      50,
                                      4 ,
                                      14, (UBYTE**)cMSG_PressureUnit);

    LOVPi.SetColSep                  (_colsep);

    LOVPi.SetColValue1               (_colvalue);

    LOVPi.SetDivider                       (10);


    /*  P Support                */
    LOVPSupport.SetParent               (&this->FVentilation);

    LOVPSupport.InitDbAccess            (ADJUST_P_SUPPORT_U16,ADJUST);

    LOVPSupport.Init                        (FREE_SQUARE,
                                             (UBYTE**)cMSG_InsuflationPressureSupport,
                                             50,
                                             4 ,
                                             14,
                                             (UBYTE**)cMSG_PressureUnit);
    LOVPSupport.SetColSep                  (_colsep);

    LOVPSupport.SetColValue1               (_colvalue);

    LOVPSupport.SetDivider              (10);


    /* P Control   */
    LOVPControl.SetParent               (&this->FVentilation);

    LOVPControl.InitDbAccess            (ADJUST_P_CONTROL_U16,ADJUST);

    LOVPControl.Init                        (FREE_SQUARE,
                                             (UBYTE**)cMSG_InsuflationPressureControl2,
                                             50,
                                             4 ,
                                             14,
                                             (UBYTE**)cMSG_PressureUnit);
    LOVPControl.SetColSep                  (_colsep);

    LOVPControl.SetColValue1               (_colvalue);

    LOVPControl.SetDivider              (10);

    /* Pi2 (autre parametre de Database) */
    LOVPi2.SetParent                  (&this->FVentilation);

    LOVPi2.InitDbAccess               (ADJUST_P_SUPPORT_U16,ADJUST);

    LOVPi2.Init                       (FREE_SQUARE,
                                       (UBYTE**)cMSG_InsuflationPressureSupport,
                                       50,
                                       4 ,
                                       14, (UBYTE**)cMSG_PressureUnit);

    LOVPi2.SetColSep                  (_colsep);

    LOVPi2.SetColValue1               (_colvalue);

    LOVPi2.SetDivider                      (10);

    /* Fréquence VACI */
    LOVFVaci.SetParent               (&this->FVentilation);

    LOVFVaci.InitDbAccess            (ADJUST_CONTROL_R_U16,ADJUST);

    LOVFVaci.Init                    (FREE_SQUARE,
                                      (UBYTE**)cMSG_ControlRate,
                                      360,
                                      4,
                                      10,
                                      (UBYTE**)cMSG_FrequencyUnit);

    LOVFVaci.SetColSep               (_colsep);

    LOVFVaci.SetColValue1            (_colvalue);


    // I/E - not displayed but used to store/retrieve I/E label and units

    LIE.SetParent                  (&this->FVentilation);

    LIE.Init                       (NO,
                                    (UBYTE**)cMSG_IERation,
                                    0,
                                    0);

    /* Pe */
    LOVPe.SetParent                  (&this->FVentilation);

    LOVPe.InitDbAccess               (ADJUST_PEEP_U16,ADJUST);

    LOVPe.Init                       (FREE_SQUARE,
                                      (UBYTE**)cMSG_ExhalationPressure,
                                      70,
                                      4,
                                      6,
                                      (UBYTE**)cMSG_PressureUnit);

    LOVPe.InitDefaultFlag             ((UBYTE**)cMSG_No,
                                       PEEP_NO_SELECT_U16,
                                       ADJUST,
                                       TRUE);

    LOVPe.SetColSep                  (_colsep);

    LOVPe.SetColValue1               (_colvalue);

    LOVPe.SetDivider                       (10);


    /* Pente */
    LOVPente.SetParent               (&this->FVentilation);

    LOVPente.InitDbAccess            (ADJUST_RISE_TIME_U16,ADJUST);

    LOVPente.Init                    (FREE_SQUARE,
                                      (UBYTE**)cMSG_PressureSlope,
                                      90,
                                      4,
                                      RISETIME1);

    if (_CurrentLang == HMI_LANG_CHINESE)
    {

        LOVPente.SetColSep               (_colsep + 9);

        LOVPente.SetColSymbol            (_colvalue + 9);
    }
    else
    {

        LOVPente.SetColSep               (_colsep);

        LOVPente.SetColSymbol            (_colvalue);
    }

    /* Rampe */
    LOVRampe.SetParent                  (&this->FVentilation);

    LOVRampe.InitDbAccess               (ADJUST_RAMP_U16,ADJUST);

    LOVRampe.Init                           (FREE_SQUARE,
                                             (UBYTE**)cMSG_Rampe,
                                             360,
                                             4 ,
                                             RAMPE1);

    LOVRampe.SetColSep               (_colsep);

    LOVRampe.SetColSymbol            (_colvalue);

    /* Fréquence Mini */
    LOVFRMini.SetParent              (&this->FVentilation);

    LOVFRMini.InitDbAccess           (ADJUST_CONTROL_R_U16,ADJUST);

    LOVFRMini.Init                   (FREE_SQUARE,
                                      (UBYTE**)cMSG_ControlRate,
                                      110,
                                      4,
                                      10,
                                      (UBYTE**)cMSG_FrequencyUnit);

    if (_CurrentLang == HMI_LANG_CHINESE)
    {
        LOVFRMini.SetColSep              (_colsep + 11);

        LOVFRMini.SetColValue1           (_colvalue + 11);
    }
    else
    {
        LOVFRMini.SetColSep              (_colsep);

        LOVFRMini.SetColValue1           (_colvalue);
    }

    // I/T - not displayed but used to store/retrieve I/T% labeling and units
    LOVIT.SetParent                  (&this->FVentilation);

    LOVIT.Init                       (FREE_SQUARE,
                                      (UBYTE**)cMSG_ITRation,
                                      0,
                                      0,
                                      0,
                                      (UBYTE**)cMSG_PerCentUnit);

    /* Insp Time */
    LOVInspTime.SetParent                  (&this->FVentilation);

    LOVInspTime.InitDbAccess               (ADJUST_TI_CONTROL_U16,ADJUST);

    LOVInspTime.Init                       (FREE_SQUARE,
                                            (UBYTE**)cMSG_TiControl,
                                            130,
                                            4,
                                            25,
                                            (UBYTE**)cMSG_SecondUnit);
    LOVInspTime.SetDivider                     (100);

    LOVInspTime.SetFloatValue1              (TRUE);

    LOVInspTime.SetColSep                  (_colsep);

    LOVInspTime.SetColValue1               (_colvalue);

    /* Trig I */
    LOVTrigI.SetParent                  (&this->FVentilation);

    LOVTrigI.InitDbAccess               ( ADJUST_INSP_SENS_U16,
                                          ADJUST);

    LOVTrigI.Init                           (FREE_SQUARE,
                                             (UBYTE**)cMSG_InspirationTrigger,
                                             150,
                                             4);


    LOVTrigI.SetColSep               (_colsep);

    LOVTrigI.SetColValue1            (_colvalue);

    LOVTrigI.SetSize                 (7);


    for (i=0; i<nb_of_trigger_levels; i++)
    {
        LOVTrigI.SetItem(i,(UBYTE**) &cMSG_InspTrigger[i][0]);
    }


    /* Soupir Select */
    LSTVSoupir.SetParent             (&this->FVentilation);

    LSTVSoupir.SetColSep             (83);

    LSTVSoupir.SetColValue1          (88);

    LSTVSoupir.InitDbAccess          (ADJUST_SIGH_SELECT_U16,
                                      ADJUST);

    LSTVSoupir.Init                  (FREE_SQUARE,
                                      (UBYTE**)cMSG_Soupir,
                                      360,
                                      4);

    LSTVSoupir.SetItem1Name          ((UBYTE**)cMSG_No);

    LSTVSoupir.SetItem2Name          ((UBYTE**)cMSG_Yes);

    LSTVSoupir.SetColSep             (_colsep);

    LSTVSoupir.SetColValue1          (_colvalue);


    /* Soupir Vt coeff */
    LOVSVtSoupir.SetParent           (&this->FVentilation);

    LOVSVtSoupir.InitDbAccess        (ADJUST_SIGH_VT_COEF_U16,
                                      ADJUST);

    LOVSVtSoupir.Init                (LOS,
                                      (UBYTE**)cMSG_VtSoupir,
                                      360,
                                      13,
                                      11,
                                      (UBYTE**)cMSG_NoneUnit, (UBYTE*)"X");

    LOVSVtSoupir.SetFloatValue1      (TRUE);

    LOVSVtSoupir.SetColSep           (100);

    LOVSVtSoupir.SetColSign          (105);

    LOVSVtSoupir.SetColValue1        (118);


    /* Soupir Compteur */
    LOVCptSoupir.SetParent           (&this->FVentilation);

    LOVCptSoupir.SetColSep           (100);

    LOVCptSoupir.SetColValue1        (105);

    LOVCptSoupir.InitDbAccess        (ADJUST_SIGH_CPT_U16,
                                      ADJUST);

    LOVCptSoupir.Init                (LOS,
                                      (UBYTE**)cMSG_CptSoupir,
                                      360,
                                      13,
                                      50,
                                      (UBYTE**)cMSG_NoneUnit);

    /* Trigger E (valeur positive) */
    LOVTrigE.SetParent                  (&this->FVentilation);

    LOVTrigE.InitDbAccess               ( ADJUST_EXH_SENS_U16,ADJUST);

    LOVTrigE.InitDefaultFlag        ((UBYTE**)cMSG_Auto,
                                     AUTO_EXH_SENS_SELECT_U16,
                                     ADJUST,
                                     TRUE);

    LOVTrigE.Init                           (FREE_SQUARE,
                                             (UBYTE**)cMSG_ExhalationTrigger,
                                             170,
                                             4 ,
                                             15,
                                             (UBYTE**)cMSG_PerCentUnit);

    LOVTrigE.SetColSep               (_colsep);

    LOVTrigE.SetColValue1            (_colvalue);


    /* Trigger E (valeur négative) */
    LOVSTrigE.SetParent              (&this->FVentilation);

    LOVSTrigE.InitDbAccess           (ADJUST_EXH_SENS_NEGATIVE_U16,ADJUST);

    LOVSTrigE.InitDefaultFlag           ((UBYTE**)cMSG_Auto,
                                         AUTO_EXH_SENS_NEG_SELECT_U16,
                                         ADJUST,
                                         TRUE);

    LOVSTrigE.Init                   (FREE_SQUARE,
                                      (UBYTE**)cMSG_ExhalationTrigger,
                                      360,
                                      4,
                                      15,
                                      (UBYTE**)cMSG_PerCentUnit, (UBYTE*)"-");

    LOVSTrigE.SetColSep              (_colsep);

    LOVSTrigE.SetColSign             (_colsep + 5 );

    LOVSTrigE.SetColValue1           (_colvalue + 15);

    LOVSTrigE.SetColUnit1            (_colvalue + 30);   

    /* Fréquence de sécurité */
    LOVFSecu.SetParent               (&this->FVentilation);

    LOVFSecu.InitDbAccess            (ADJUST_BACKUP_R_U16,ADJUST);

    LOVFSecu.Init                    (FREE_SQUARE,
                                      (UBYTE**)cMSG_BackupRate,
                                      360,
                                      4,
                                      10,
                                      (UBYTE**)cMSG_FrequencyUnit);

    LOVFSecu.InitDefaultFlag         ((UBYTE**)cMSG_No,
                                      BACKUP_R_NO_SELECT_U16,ADJUST,TRUE);

    if (_CurrentLang == HMI_LANG_CHINESE)
    {

        LOVFSecu.SetColSep               (_colsep + 17);

        LOVFSecu.SetColValue1            (_colvalue + 17);
    }
    else
    {

        LOVFSecu.SetColSep               (_colsep);

        LOVFSecu.SetColValue1            (_colvalue);
    }



    /* Apnée */
    LOVApnee.SetParent                  (&this->FVentilation);

    LOVApnee.SetColSep               (_colsep);

    LOVApnee.SetColValue1            (_colvalue);

    LOVApnee.InitDbAccess               ( ADJUST_APNEA_U16 ,
                                          ADJUST);

    LOVApnee.Init                           (FREE_SQUARE,
                                             (UBYTE**)cMSG_Apnee,
                                             360,
                                             4 ,
                                             10,
                                             (UBYTE**)cMSG_SecondUnit);

    LOVApnee.InitDefaultFlag            ((UBYTE**)cMSG_Auto,
                                         AUTO_APNEA_SELECT_U16,
                                         ADJUST,
                                         TRUE);

    LOVApnee.SetDivider                 (1000);

    /* FiO2 */
    LOVFiO2.SetParent                (&this->FVentilation);

    LOVFiO2.InitDbAccess             (ADJUST_FIO2,CONFIG);

    LOVFiO2.Init                     (FREE_SQUARE,
                                      (UBYTE**)cMSG_FiO2,
                                      110,
                                      4,
                                      10,
                                      (UBYTE**)cMSG_PerCentUnit);

    LOVFiO2.SetColSep                (_colsep);

    LOVFiO2.SetColValue1             (_colvalue);


    /* Target VT */
    LOVVTCible.SetParent                 (&this->FVentilation);

    LOVVTCible.InitDbAccess             ( ADJUST_TARGET_VT_U16 ,
                                          ADJUST);

    LOVVTCible.Init                     (FREE_SQUARE,
                                         (UBYTE**)cMSG_VTCible,
                                         190,
                                         4 ,
                                         1000,
                                         (UBYTE**)cMSG_VolumeUnit);

    LOVVTCible.InitDefaultFlag          ((UBYTE**)cMSG_No,
                                         TARGET_VT_SELECT_U16,
                                         ADJUST,
                                         FALSE);

    LOVVTCible.SetColSep             (_colsep);

    LOVVTCible.SetColValue1          (_colvalue);


    /* Pi Max */
    LOVPiMax.SetParent                   (&this->FVentilation);

    LOVPiMax.InitDbAccess               ( ADJUST_MAX_PRESSURE_U16,ADJUST);

    LOVPiMax.Init                           (LOS,
                                             (UBYTE**)cMSG_PiMax,
                                             210,
                                             12,
                                             15,
                                             (UBYTE**)cMSG_PressureUnit);

    LOVPiMax.SetDivider                  (10);

    LOVPiMax.SetColSep(84);

    LOVPiMax.SetColValue1(87);


    LSTVChgtModeV.SetParent             (&this->FVentilation);

    LSTVChgtModeV.Init                  (FREE_SQUARE,
                                         (UBYTE**)cMSG_switchMode,
                                         224,
                                         4);

    LSTVChgtModeV.SetColSep             (109);

    LSTVChgtModeV.SetSep                    ((UBYTE *)":");

    LSTVChgtModeV.SetColValue1          (113);

    LSTVChgtModeV.SetItem1Name          ((UBYTE**)cMSG_NoneUnit);

    LSTVChgtModeV.SetItem2Name          ((UBYTE**)cMSG_Yes);

    LPreferences.SetParent              (&this->FVentilation);

    LPreferences.Init                       (FREE_SQUARE,
                                             (UBYTE**)cMSG_VPreferences,
                                             230, 
                                             4);

    /*--------------------------- fenetre Alarme ---------------------------------*/

    LModeAlarm.SetParent                    (&this->FAlarme);

    LModeAlarm.InitDbAccess             (ADJUST_MODE_U16,
                                         CONFIG);

    LModeAlarm.Init                     (FREE_SQUARE, 
                                         NULL,
                                         18,
                                         4);

    LModeAlarm.SetNameMode              ((UBYTE**)cMSG_Mode,
                                         (UBYTE**)cMSG_Mode2,
                                         (UBYTE**)cMSG_Mode3,
                                         (UBYTE**)cMSG_EnableMode,
                                         (UBYTE**)cMSG_DisableMode);


    LOVPiMbar.SetParent                 (&this->FAlarme);

    LOVPiMbar.InitDbAccess              ( ADJUST_LOW_PIP_U16,
                                          ADJUST,
                                          COMPUTED_LPF_PIP_U16,
                                          COMPUTE,
                                          ADJUST_HIGH_PIP_U16,
                                          ADJUST);

    LOVPiMbar.Init                          (FREE_SQUARE,
                                             (UBYTE**)cMSG_PiMbar,
                                             (UBYTE**)cMSG_PressureUnit[0],                                    
                                             360,
                                             4 ,
                                             5,
                                             25,
                                             35);

    LOVPiMbar.SetColLabel               (10);

    LOVPiMbar.SetDivider                   (10);

    LOVPiMbar.SetLabel2LineOffset    (15);
    LOVPiMbar.SetLabel2ColOffset     (12);

    LOVPiMbar.SetMaxDisplayValue      (999);


    LOVVtiMl.SetParent                  (&this->FAlarme);

    LOVVtiMl.InitDbAccess               (ADJUST_LOW_VTI_U16,
                                         ADJUST,
                                         COMPUTED_VTI_U16,
                                         COMPUTE,
                                         ADJUST_HIGH_VTI_U16,
                                         ADJUST);

    LOVVtiMl.Init                           (FREE_SQUARE,
                                             (UBYTE**)cMSG_VtiMl,
                                             66,
                                             4 ,
                                             500,
                                             750,
                                             1500);

    LOVVtiMl.InitDefaultFlag            ((UBYTE**)cMSG_No,
                                         LOW_VTI_NO_SELECT_U16,
                                         ADJUST,
                                         TRUE,
                                         (UBYTE**)cMSG_No,
                                         HIGH_VTI_NO_SELECT_U16,
                                         ADJUST,TRUE);

    LOVVtiMl.SetColLabel                    (12);

    LOVVtiMl.SetMaxDisplayValue             (9999);

    LOVVteMl.SetParent                  (&this->FAlarme);

    LOVVteMl.InitDbAccess               (ADJUST_LOW_VTE_U16,
                                         ADJUST,
                                         COMPUTED_VTE_U16,
                                         COMPUTE,
                                         ADJUST_HIGH_VTE_U16,
                                         ADJUST);

    LOVVteMl.Init                           (FREE_SQUARE,
                                             (UBYTE**)cMSG_VteMl,
                                             93,
                                             4 ,
                                             30,
                                             500,
                                             2000);

    LOVVteMl.InitDefaultFlag            ((UBYTE**)cMSG_No,
                                         LOW_VTE_NO_SELECT_U16,
                                         ADJUST,
                                         TRUE,
                                         (UBYTE**)cMSG_No,
                                         HIGH_VTE_NO_SELECT_U16,
                                         ADJUST,
                                         TRUE);

    LOVVteMl.SetColLabel                    (12);

    LOVVteMl.SetMaxDisplayValue         (9999);

    LOVFrCMin.SetParent                 (&this->FAlarme);

    LOVFrCMin.InitDbAccess              (ADJUST_HIGH_R_U16,
                                         ADJUST,
                                         MEASURE_R_U16,
                                         COMPUTE);

    LOVFrCMin.Init                          (FREE_SQUARE,
                                             (UBYTE**)cMSG_FrCMin,
                                             117, 
                                             4 ,
                                             20, 
                                             10);

    LOVFrCMin.InitDefaultFlag           ((UBYTE**)cMSG_No,
                                         HIGH_R_NO_SELECT_U16,
                                         ADJUST,
                                         TRUE);

    LOVFrCMin.SetValue1Maxi             (TRUE);

    LOVFrCMin.SetColValue1              (THIRD_VALUE_COLUMN);

    LOVFrCMin.SetColLabel               (11);

    LOVFrCMin.SetMaxDisplayValue    (99);

    LTTVSpO2.SetParent               (&this->FAlarme);

    LTTVSpO2.InitDbAccess            (ADJUST_LOW_SPO2,
                                      CONFIG,
                                      MEASURE_SPO2_U16,
                                      COMPUTE,
                                      ADJUST_HIGH_SPO2,
                                      CONFIG);

    LTTVSpO2.Init                    (FREE_SQUARE,
                                      (UBYTE**)cMSG_SpO2Pc,
                                      167,
                                      4,
                                      500,
                                      750,
                                      1500);

    LTTVSpO2.InitDefaultFlag         ((UBYTE**)cMSG_No,
                                      SPO2_LOW_SELECT,
                                      CONFIG,
                                      FALSE,
                                      (UBYTE**)cMSG_No,
                                      SPO2_HIGH_SELECT,
                                      CONFIG,
                                      FALSE);
    LTTVSpO2.SetColLabel             (11);

    LTTVSpO2.SetMaxDisplayValue (999);



    LTTVFiO2.SetParent               (&this->FAlarme);

    LTTVFiO2.InitDbAccess            (ADJUST_LOW_FIO2,
                                      CONFIG,
                                      COMPUTED_FIO2,
                                      COMPUTE,
                                      ADJUST_HIGH_FIO2,
                                      CONFIG);

    LTTVFiO2.Init                    (FREE_SQUARE,
                                      (UBYTE**)cMSG_FiO2Pc,
                                      167,
                                      4,
                                      500,
                                      750,
                                      1500);

    LTTVFiO2.InitDefaultFlag         ((UBYTE**)cMSG_No,
                                      FIO2_LOW_SELECT,
                                      CONFIG,
                                      FALSE,
                                      (UBYTE**)cMSG_No,
                                      FIO2_HIGH_SELECT,
                                      CONFIG,
                                      FALSE);
    LTTVFiO2.SetColLabel             (11);

    LTTVFiO2.SetMaxDisplayValue (999);


    LTTVTiS.SetParent                       (&this->FAlarme);

    LTTVTiS.InitDbAccess                    (ADJUST_TI_MIN_U16,
                                             ADJUST,
                                             MEASURE_TI_HMI_U16,
                                             COMPUTE,
                                             ADJUST_TI_MAX_U16,
                                             ADJUST);

    LTTVTiS.Init                            (FREE_SQUARE,
                                             (UBYTE**)cMSG_TiS,
                                             192,
                                             4 ,
                                             500,
                                             750,
                                             1500);

    LTTVTiS.InitDefaultFlag             ((UBYTE**)cMSG_Auto,
                                         TI_MIN_AUTO_SELECT_U16,
                                         ADJUST,
                                         TRUE,
                                         (UBYTE**)cMSG_Auto,
                                         TI_MAX_AUTO_SELECT_U16,
                                         ADJUST,TRUE);

    LTTVTiS.SetFloatValueRefresh        (TRUE);

    LTTVTiS.SetFloatValue1              (TRUE);

    LTTVTiS.SetFloatValue2              (TRUE);

    LTTVTiS.SetColLabel                 (12);

    LTTVTiS.SetDivider                  (100);


    LTOVFuiteLMin.SetParent          (&this->FAlarme);

    LTOVFuiteLMin.InitDbAccess       (ADJUST_HIGH_LEAK_U16,ADJUST,COMPUTED_LEAK_HMI_U16,COMPUTE);

    LTOVFuiteLMin.Init               (FREE_SQUARE,
                                      (UBYTE**)cMSG_FuiteParam,
                                      93,
                                      4,
                                      400,
                                      700);

    LTOVFuiteLMin.InitDefaultFlag    ((UBYTE**)cMSG_No,HIGH_LEAK_SELECT_U16,ADJUST,FALSE);

    LTOVFuiteLMin.SetValue1Maxi      (TRUE);

    LTOVFuiteLMin.SetColValue1       (THIRD_VALUE_COLUMN);

    LTOVFuiteLMin.SetColLabel        (11);

    LTOVFuiteLMin.SetMaxDisplayValue (200);


    /* Calibration expiration */
    LSTICalibQExp.SetParent          (&this->FAlarme);

    LSTICalibQExp.Init               (NO,
                                      (UBYTE**)cMSG_NoneUnit,
                                      118,
                                      122);

    LSTICalibQExp.SetInvertVideo     (TRUE);

    LSTICalibQExp.SetColLabel        (0);

    LSTICalibQExp.SetColSep          (0);

    LSTICalibQExp.SetColValue1       (0);

    LSTICalibQExp.SetSep             ((UBYTE*)"");

    LSTICalibQExp.SetItem1Name       ((UBYTE**)cMSG_No);

    LSTICalibQExp.SetItem2Name       ((UBYTE**)cMSG_Yes);

    /* Calibration FiO2 */
    LSTICalibFiO2.SetParent          (&this->FAlarme);

    LSTICalibFiO2.Init               (NO,
                                      (UBYTE**)cMSG_NoneUnit,
                                      118,
                                      122);

    LSTICalibFiO2.SetInvertVideo     (TRUE);

    LSTICalibFiO2.SetColLabel        (0);

    LSTICalibFiO2.SetColValue1       (0);

    LSTICalibFiO2.SetSep             ((UBYTE*)"");

    LSTICalibFiO2.SetItem1Name       ((UBYTE**)cMSG_No);

    LSTICalibFiO2.SetItem2Name       ((UBYTE**)cMSG_Yes);



    LHistoAlarm.SetParent               (&this->FAlarme);

    LHistoAlarm.Init                        (FREE_SQUARE,
                                             (UBYTE**)cMSG_HistoAlarm,
                                             233,
                                             4);

    LOVChgtModeA.SetParent              (&this->FAlarme);

    LOVChgtModeA.Init                       (FREE_SQUARE,
                                             (UBYTE**)cMSG_switchMode,
                                             233,
                                             4);

    LOVChgtModeA.SetColSep              (108);

    LOVChgtModeA.SetSep                 ((UBYTE *)":");

    LOVChgtModeA.SetColValue1           (115);

    LOVChgtModeA.SetItem1Name           ((UBYTE**)cMSG_NoneUnit);

    LOVChgtModeA.SetItem2Name           ((UBYTE**)cMSG_Yes);

    /*------------------------- fenetre HistAlarme -------------------------------*/

    LCancelledAlarm.SetParent           (&this->FHistoAlarme);

    LCancelledAlarm.Init                    (FREE_SQUARE,
                                             (UBYTE**)cMSG_CancelledAlarm,
                                             206,
                                             8);

    LRAlarmeA.SetParent                 (&this->FHistoAlarme);

    LRAlarmeA.Init                          (FREE_SQUARE,
                                             (UBYTE**)cMSG_Back,
                                             226,
                                             8);

    /*----------------------- fenetre configuration ------------------------------*/
    _line = 35;
    _spacing = 18;
    _colsep = 139;
    _colvalue = 146;


    /* Compteur Machine */

    LOVMachineHrs.SetParent           (&this->FConfiguration);

    LOVMachineHrs.InitDbAccess        (CURRENT_MACHINE_COUNTER_HOUR_U16,
                                       CONTROL);

    LOVMachineHrs.Init                (NO,
                                       (UBYTE**)cMSG_CounterMachine,
                                       _line,
                                       0,
                                       24,
                                       (UBYTE**)cMSG_HourUnit);

    LOVMachineHrs.SetColLabel           (8);

    LOVMachineHrs.SetColSep           (_colsep+8);

    LOVMachineHrs.SetColValue1        (_colvalue+8);

    LOVMachineHrs.SetNbDigitValue1   (5);

    LOVMachineHrs.SetDisplayZeroValue1(TRUE);

    /* Langue */
    _line += _spacing;

    LVSLanguage.SetParent               (&this->FConfiguration);

    LVSLanguage.InitDbAccess            (ADJUST_LANGUAGE_U16,
                                         CONFIG);

    LVSLanguage.Init                        (FREE_SQUARE,
                                             (UBYTE**)cMSG_Language,
                                             _line,
                                             8);

    LVSLanguage.SetColSep               (_colsep);

    LVSLanguage.SetColValue1            (_colvalue);

    LVSLanguage.SetValue1Name           ((UBYTE**)cMSG_CountryLanguage);

    /* Date */
    _line += _spacing;

    VDConf.SetParent                     (&this->FConfiguration);

    VDConf.InitDbAccess                 (DB_RTC_MONTH_U16,
                                         RTC,
                                         DB_RTC_DAY_U16,
                                         DB_RTC_YEAR_U16,
                                         ADJUST_RTC_MONTH_U16,
                                         ADJUST_RTC_DAY_U16,
                                         ADJUST_RTC_YEAR_U16,
                                         RTC);

    VDConf.Init                             (FREE_SQUARE,
                                             (UBYTE**)cMSG_Date,
                                             _line,
                                             8);

    VDConf.SetColSep                        (_colsep);

    VDConf.SetColDate                       (_colvalue);

    VDConf.SetNameMonth                 ((UBYTE**)cMSG_Month);

    /* Heure */
    _line += _spacing;

    VTConf.SetParent                        (&this->FConfiguration);

    VTConf.InitDbAccess                 (DB_RTC_HOUR_U16,
                                         RTC, DB_RTC_MINUTE_U16,
                                         DB_RTC_SECOND_U16,
                                         ADJUST_RTC_HOUR_U16,
                                         ADJUST_RTC_MINUTE_U16,
                                         ADJUST_RTC_SECOND_U16);

    VTConf.Init                             (FREE_SQUARE,
                                             (UBYTE**)cMSG_Time,
                                             _line,
                                             8);

    VTConf.SetColSep                        (_colsep);

    VTConf.SetColHours                  (_colvalue);

    /* Alarme Voluntary stop */
    _line += _spacing;

    LVSVoluntaryStopAlarm.SetParent                   (&this->FConfiguration);

    LVSVoluntaryStopAlarm.InitDbAccess                (VOLUNTARY_STOP_ALARM_ACTIVATION,
                                                       CONFIG);

    LVSVoluntaryStopAlarm.Init                        (FREE_SQUARE,
                                                       (UBYTE**)cMSG_VoluntaryStopAlarm,
                                                       _line,
                                                       8);

    LVSVoluntaryStopAlarm.SetColSep                   (_colsep);

    LVSVoluntaryStopAlarm.SetColValue1                (_colvalue);

    LVSVoluntaryStopAlarm.SetItem1Name                ((UBYTE**)cMSG_No);

    LVSVoluntaryStopAlarm.SetItem2Name                ((UBYTE**)cMSG_Yes);

    /* Unité de Pression */
    _line += _spacing;

    LVSPressureUnit.SetParent        (&this->FConfiguration);

    LVSPressureUnit.InitDbAccess     (PRESSURE_UNIT_U16, CONFIG);

    LVSPressureUnit.Init             (FREE_SQUARE,
                                      (UBYTE**)cMSG_PressureUnitType,
                                      _line,
                                      8);

    LVSPressureUnit.SetColSep        (_colsep);

    LVSPressureUnit.SetColValue1     (_colvalue);

    LVSPressureUnit.SetSize          (3);

    LVSPressureUnit.SetItem          (0,(UBYTE**)cMSG_PressureUnit[0]);

    LVSPressureUnit.SetItem          (1,(UBYTE**)cMSG_PressureUnit[1]);

    LVSPressureUnit.SetItem          (2,(UBYTE**)cMSG_PressureUnit[2]);

   /* Alarm Tone */
    _line += _spacing;

   LVSAlarmTone.SetParent        (&this->FConfiguration);

   LVSAlarmTone.InitDbAccess     (SOUND_TYPE_SELECT_U16, CONFIG);

   LVSAlarmTone.Init             (FREE_SQUARE,
                                    (UBYTE**)cMSG_Alarm_Tone,
                                             _line,
                                             8);

   LVSAlarmTone.SetColSep        (_colsep);

   LVSAlarmTone.SetColValue1     (_colvalue);

   LVSAlarmTone.SetItem1Name          ((UBYTE**)cMSG_Original);

   LVSAlarmTone.SetItem2Name          ((UBYTE**)cMSG_Compliant);

    /* Compteur Patient */
    _line += _spacing;

    LOVPatientHrs.SetParent     (&this->FConfiguration);

    LOVPatientHrs.InitDbAccess  (CURRENT_PATIENT_COUNTER_HOUR_U16,
                                 CONTROL,
                                 CURRENT_PATIENT_COUNTER_MIN_U16,
                                 CONTROL);

    LOVPatientHrs.Init          (FREE_SQUARE,
                                 (UBYTE**)cMSG_CounterPatient,
                                 _line,
                                 8,
                                 24,
                                 (UBYTE**)cMSG_HourUnit,
                                 34,
                                 (UBYTE**)cMSG_MinuteUnit);

    LOVPatientHrs.SetColSep     (_colsep);

    LOVPatientHrs.SetColValue1  (_colvalue);

    LOVPatientHrs.SetColValue2  (_colvalue + 68);

    LOVPatientHrs.SetColUnit2   (_colvalue + 88);

    LOVPatientHrs.SetNbDigitValue1(5);

    LOVPatientHrs.SetDisplayZeroValue1(TRUE);

    LOVPatientHrs.SetNbDigitValue2(2);

    LOVPatientHrs.SetDisplayZeroValue2(TRUE);

    /* Reset Compteur Patient */
    _line += _spacing;

    LVSSResetPatientHrs.SetParent       (&this->FConfiguration);

    LVSSResetPatientHrs.Init               (LOS,
                                            (UBYTE**)cMSG_ResetPatientHrs,
                                            _line,
                                            20);

    LVSSResetPatientHrs.SetItem1Name            ((UBYTE**)cMSG_No);

    LVSSResetPatientHrs.SetItem2Name            ((UBYTE**)cMSG_Yes);

    LVSSResetPatientHrs.SetColSep       (_colsep);

    LVSSResetPatientHrs.SetColValue1    (_colvalue);


	//  Restore Default Settings Button.
	_line += _spacing;

	LVSSRestoreDefaultSettings.SetParent        (&this->FConfiguration);

	LVSSRestoreDefaultSettings.Init             (FREE_SQUARE,
									 (UBYTE**)cMSG_RestoreDefaultSetting,
											  _line,
											  8);

	LVSSRestoreDefaultSettings.SetColSep        (_colsep);

	LVSSRestoreDefaultSettings.SetColValue1     (_colvalue);

	LVSSRestoreDefaultSettings.SetItem1Name          ((UBYTE**)cMSG_No);

	LVSSRestoreDefaultSettings.SetItem2Name          ((UBYTE**)cMSG_Yes);
	


    /* Vers la Maintenance */
    _line += _spacing;

    LMaintenance.SetParent              (&this->FConfiguration);

    LMaintenance.Init                       (FREE_SQUARE,
                                             (UBYTE**)cMSG_Maintenance,
                                             _line,
                                             8);


	/* Next Page */
	_line += _spacing;

	 LNextPage.SetParent				(&this->FConfiguration);

	 LNextPage.Init						(FREE_SQUARE,
										(UBYTE**)cMSG_NextPage,
										_line,
										8);

/*----------------------- Configuration/Setup 2 Window ------------------------------*/
   _line = 35;
   _spacing = 18;
   _colsep = 139;
   _colvalue = 146;

   (HMI_Setup1::GetInstance()).InitConfiguration();

    /*----------------------- fenetre Preference ---------------------------------*/

    _line = 32;
    _spacing = 20;
    _colsep = 143;
    _colvalue = 153;

    LVSScreenSave.SetParent             (&this->FPreference);

    LVSScreenSave.InitDbAccess          (ADJUST_BACKLIGHT_U16,
                                         CONFIG);

    LVSScreenSave.Init                  (FREE_SQUARE,
                                         (UBYTE**)cMSG_ScreenSave,
                                         _line,
                                         8);

    LVSScreenSave.SetColSep             (_colsep);

    LVSScreenSave.SetColValue1          (_colvalue);

    LVSScreenSave.SetItem1Name          ((UBYTE**)cMSG_No);

    LVSScreenSave.SetItem2Name          ((UBYTE**)cMSG_Yes);


    _line += _spacing;

    LPBBrightness.SetParent              (&this->FPreference);

    LPBBrightness.InitDbAccess          (ADJUST_BRIGHTNESS_U16,
                                         CONFIG);

    LPBBrightness.Init                  (FREE_SQUARE,
                                         (UBYTE**)cMSG_Brightness,
                                         _line,
                                         8,
                                         34000);

    LPBBrightness.SetColSep             (_colsep);

    LPBBrightness.SetColValue           (_colvalue);

    InterfaceCppC::DB_Request           (&LowLimit,
                                         ADJUST_BRIGHTNESS_U16,
                                         CONFIG, MIN);

    InterfaceCppC::DB_Request           (&HighLimit,
                                         ADJUST_BRIGHTNESS_U16,
                                         CONFIG, MAX);

    LPBBrightness.SetLimits             (LowLimit,
                                         HighLimit);


    _line += _spacing;

    LPBSoundLevel.SetParent             (&this->FPreference);

    LPBSoundLevel.InitDbAccess          (SOUND_LEVEL_SELECT_U16,
                                         CONFIG);

    LPBSoundLevel.Init                  (FREE_SQUARE,
                                         (UBYTE**)cMSG_SoundLevel,
                                         _line,
                                         8,
                                         34000);

    LPBSoundLevel.SetColSep             (_colsep);

    LPBSoundLevel.SetColValue           (_colvalue);

    InterfaceCppC::DB_Request           (&LowLimit,
                                         SOUND_LEVEL_SELECT_U16,
                                         CONFIG, MIN);

    InterfaceCppC::DB_Request           (&HighLimit,
                                         SOUND_LEVEL_SELECT_U16,
                                         CONFIG, MAX);

    LPBSoundLevel.SetLimits             (LowLimit,
                                         HighLimit);

    _line += _spacing + 2;

    LOVFDAjustKeyTone.SetParent     (&this->FPreference);

    LOVFDAjustKeyTone.InitDbAccess  (ADJUST_KEY_TONE_U16,
                                     CONFIG);

    LOVFDAjustKeyTone.Init              (FREE_SQUARE,
                                         (UBYTE**)cMSG_KeySound,
                                         _line,
                                         8,
                                         24,
                                         (UBYTE**)cMSG_NoneUnit);

    LOVFDAjustKeyTone.SetColSep     (_colsep);

    LOVFDAjustKeyTone.SetColValue1  (_colvalue);




    LOVFDAjustKeyTone.InitDefaultValue      ((UBYTE**)cMSG_Off,
                                             0,
                                             (UBYTE**)cMSG_Key,
                                             1,
                                             (UBYTE**)cMSG_Bip,
                                             2,
                                             (UBYTE**)cMSG_BipAndKey,
                                             3);

    /* Alarme Apnée */
    _line += _spacing;

    LVSApneaAlarm.SetParent                    (&this->FPreference);

    LVSApneaAlarm.InitDbAccess                (APNEA_ALARM_ACTIVATION,
                                               CONFIG);

    LVSApneaAlarm.Init                        (FREE_SQUARE,
                                               (UBYTE**)cMSG_ApneaAlarm,
                                               _line,
                                               8);

    LVSApneaAlarm.SetColSep                   (_colsep);

    LVSApneaAlarm.SetColValue1                (_colvalue);

    LVSApneaAlarm.SetItem1Name                ((UBYTE**)cMSG_No);

    LVSApneaAlarm.SetItem2Name                ((UBYTE**)cMSG_Yes);


    /* Alarme Déconnexion */
    _line += _spacing;

    LOVFDisconnectionAlarm.SetParent         (&this->FPreference);

    LOVFDisconnectionAlarm.InitDbAccess     (ADJUST_DISCONNECTION_DELAY_U16 ,
                                             ADJUST);

    LOVFDisconnectionAlarm.Init             (FREE_SQUARE,
                                             (UBYTE**)cMSG_DisconnectionAlarm,
                                             _line,
                                             8 ,
                                             1000,
                                             (UBYTE**)cMSG_SecondUnit);

    LOVFDisconnectionAlarm.SetDivider      (1000);

    LOVFDisconnectionAlarm.SetColSep           (_colsep);

    LOVFDisconnectionAlarm.SetColValue1    (_colvalue);


    LOVFDisconnectionAlarm.InitDefaultFlag  ((UBYTE**)cMSG_Auto,
                                             DISCONNECTION_DELAY_AUTO_U16,
                                             ADJUST,
                                             TRUE);


#ifdef HMI_CONFIG_CURVES

    #ifdef HMI_CONFIG_CURVE_CFG
    _line += _spacing;

    LCurveConfiguration.SetParent    (&this->FPreference);

    LCurveConfiguration.Init         (FREE_SQUARE,
                                      (UBYTE**)cMSG_CurveConfiguration,
                                      _line,
                                      8);
    #else

    _line += _spacing;

    LVSWaveformDisplay.SetParent        (&this->FPreference);

    LVSWaveformDisplay.InitDbAccess (ADJUST_WAVEFORM_DISPLAY_U16,
                                     CONFIG);

    LVSWaveformDisplay.Init             (FREE_SQUARE,
                                         (UBYTE**)cMSG_WaveformDisplay,
                                         _line,
                                         8);

    LVSWaveformDisplay.SetColSep        (_colsep);

    LVSWaveformDisplay.SetColValue1  (_colvalue);

    LVSWaveformDisplay.SetItem1Name  ((UBYTE**)cMSG_No);

    LVSWaveformDisplay.SetItem2Name  ((UBYTE**)cMSG_Yes);
    #endif // HMI_CONFIG_CURVE_CFG
#else //not  HMI_CONFIG_CURVES

    // No curves so forcing setting to FALSE
    Val = FALSE;
    DataBaseAccess::WriteValue(&Val,ADJUST_WAVEFORM_DISPLAY_U16,CONFIG);

#endif // HMI_CONFIG_CURVES

    _line += _spacing;

    LVSPediatricCircuit.SetParent       (&this->FPreference);

    LVSPediatricCircuit.InitDbAccess    (ADJUST_PEDIATRIC_CIRCUIT_U16,
                                         CONFIG);

    LVSPediatricCircuit.Init                (FREE_SQUARE,
                                             (UBYTE**)cMSG_PediatricCircuit,
                                             _line,
                                             8);

    LVSPediatricCircuit.SetColSep       (_colsep);

    LVSPediatricCircuit.SetColValue1     (_colvalue);

    LVSPediatricCircuit.SetItem1Name     ((UBYTE**)cMSG_No);

    LVSPediatricCircuit.SetItem2Name     ((UBYTE**)cMSG_Yes);


    _line += _spacing;

    LTrendMenu.SetParent                   (&this->FPreference);

    LTrendMenu.Init                     (FREE_SQUARE,
                                         (UBYTE**)cMSG_RapportVentil,
                                         _line,
                                         8);

    LRVentilMenu.SetParent              (&this->FPreference);

    LRVentilMenu.Init                       (FREE_SQUARE,
                                             (UBYTE**)cMSG_BackVentil,
                                             230,
                                             8);
    /*--------------------------- Circuit Check Window --------------------------*/

    _line = 40;

    LCircuitLeak.SetParent           (&FCircuitCheck);

    LCircuitLeak.Init                (FREE_SQUARE,
                                      (UBYTE**)cMSG_CircuitLeak,
                                      _line,
                                      8);

    /*--------------------------- fenetre Maintenance ----------------------------*/

    _line = 63;
    _spacing = 16;

    LHistoAnom.SetParent                 (&this->FMaintenance);

    LHistoAnom.Init                     (FREE_SQUARE, 
                                         (UBYTE**)cMSG_HistoAnom, 
                                         _line,
                                         8);

    _line += _spacing;

    LVoltCtrl.SetParent                 (&this->FMaintenance);

    LVoltCtrl.Init                          (FREE_SQUARE,
                                             (UBYTE**)cMSG_VoltCtrl,
                                             _line,
                                             8);

    _line += _spacing;

    LSensorCal.SetParent                    (&this->FMaintenance);

    LSensorCal.Init                     (FREE_SQUARE,
                                         (UBYTE**)cMSG_SensorCal,
                                         _line,
                                         8);

    /* Pression Patient */
    _spacing = 17;
    _line += _spacing;
    _col = 19;
    _colsep = 128;
    _colvalue = 136;


    LOVPatientPressure.SetParent     (&this->FMaintenance);

    LOVPatientPressure.InitDbAccess (FILTER_INTERNAL_PRESSURE_S16,
                                     COMPUTE);

    LOVPatientPressure.SetSignValue (TRUE);

    LOVPatientPressure.Init             (LOS,
                                         (UBYTE**)cMSG_PatientPressure,
                                         _line,
                                         _col,
                                         96,
                                         (UBYTE**)cMSG_PressureUnit);

    LOVPatientPressure.SetColSep        (_colsep);

    LOVPatientPressure.SetColValue1 (_colvalue);

    LOVPatientPressure.SetFloatValue1(TRUE);

    LOVPatientPressure.InitCalibProperties(CALIB_PATIENT_PRESS_REQ_U16,
                                           CONTROL,
                                           PATIENT_PRESSURE_CALIB_POINTS,
                                           PatientPressureFloatSegmentList,
                                           PATIENT_PRESSURE_CALIB_POINTS_NUMBER,
                                           CALIB_ADJUST_CMD_U16,
                                           CONTROL,
                                           MEASURE_SPEED_BLOWER_U16,COMPUTE);

    LOVPatientPressure.InitValue2        (FILTER_PATIENT_PRESSURE_PROXI_S16,
                                          COMPUTE,
                                          (UBYTE**)cMSG_NoneUnit,
                                          _line,
                                          235,
                                          (UBYTE**)cMSG_PressureUnit,
                                          (UBYTE**)cMSG_Slash,
                                          1);

    LOVPatientPressure.SetMaxDisplayValue(999);

    LOVPatientPressure.SetMaxDisplayValue2(999);

    /* Pression Valve */
    _line += _spacing;

    LOVValvePressure.SetParent           (&this->FMaintenance);

    LOVValvePressure.InitDbAccess       (FILTER_VALVE_PRESSURE_S16,
                                         COMPUTE);

    LOVValvePressure.SetSignValue       (TRUE);

    LOVValvePressure.Init               (LOS,
                                         (UBYTE**)cMSG_ValvePressure,
                                         _line,
                                         _col,
                                         102,
                                         (UBYTE**)cMSG_PressureUnit);

    LOVValvePressure.SetColSep          (_colsep);

    LOVValvePressure.SetColValue1       (_colvalue);

    LOVValvePressure.SetFloatValue1 (TRUE);

    LOVValvePressure.InitCalibProperties    (CALIB_FAS_VALVE_REQ_U16,
                                             CONTROL,
                                             VALVE_FAS_PWM_CALIB_POINTS,
                                             ValvePressureFloatSegmentList,
                                             0);

    LOVValvePressure.SetMaxDisplayValue(999);                                         

    /* Débit inspiré */
    _line += _spacing;

    LOVFlowIns.SetParent                    (&this->FMaintenance);

    LOVFlowIns.InitDbAccess             (FILTER_QI_S16, COMPUTE);

    LOVFlowIns.SetSignValue             (TRUE);

    LOVFlowIns.Init                     (LOS,
                                         (UBYTE**)cMSG_FlowIns, 
                                         _line,
                                         _col,
                                         1253, 
                                         (UBYTE**)cMSG_StandardFlowUnit);

    LOVFlowIns.SetColSep                    (_colsep);

    LOVFlowIns.SetColValue1             (_colvalue);

    LOVFlowIns.SetFloatValue1           (TRUE);

    LOVFlowIns.InitCalibProperties  (CALIB_FLOW_INSP_REQ_U16,
                                     CONTROL,
                                     FLOW_CALIB_POINTS,
                                     FlowFloatSegmentList,
                                     FLOW_CALIB_POINTS_NUMBER,
                                     CALIB_ADJUST_CMD_U16,
                                     CONTROL,
                                     MEASURE_SPEED_BLOWER_U16,
                                     COMPUTE);

    /* Débit expiré */
    _line += _spacing;

    LOVFlowExp.SetParent                    (&this->FMaintenance);

    LOVFlowExp.InitDbAccess             (FILTER_QE_S16, COMPUTE);

    LOVFlowExp.SetSignValue             (TRUE);

    LOVFlowExp.Init                     (LOS,
                                         (UBYTE**)cMSG_FlowExp,
                                         _line,
                                         _col,
                                         126,
                                         (UBYTE**)cMSG_StandardFlowUnit);

    LOVFlowExp.SetColSep                    (_colsep);

    LOVFlowExp.SetColValue1             (_colvalue);

    LOVFlowExp.SetFloatValue1           (TRUE);

    LOVFlowExp.InitCalibProperties  (CALIB_FLOW_EXH_REQ_U16,
                                     CONTROL,
                                     FLOW_CALIB_POINTS,
                                     FlowFloatSegmentList,
                                     FLOW_CALIB_POINTS_NUMBER);

    this->UpdateCalibrationPoints();

    /* Capteur FiO2 */
    _line += _spacing;

    LOVFiO2Concent.SetParent           (&this->FMaintenance);

    LOVFiO2Concent.InitDbAccess         (MEASURE_FIO2, COMPUTE);

    LOVFiO2Concent.SetFloatValue1           (TRUE);

    LOVFiO2Concent.Init                     (LOS,
                                             (UBYTE**)cMSG_CalibFiO2,
                                             _line,
                                             _col,
                                             126,
                                             (UBYTE**)cMSG_PerCentUnit);

    LOVFiO2Concent.SetColSep                (_colsep);

    LOVFiO2Concent.SetColValue1        (_colvalue);


    LOVFiO2Concent.InitCalibProperties  (CALIB_FIO2_REQ_U16,
                                         CONTROL,
                                         FIO2_CALIB_POINTS,
                                         FiO2FloatSegmentList,
                                         FIO2_CALIB_POINTS_NUMBER,
                                         CALIB_ADJUST_CMD_U16,
                                         CONTROL,
                                         MEASURE_SPEED_BLOWER_U16,
                                         COMPUTE);


    /* Débit O2 */
    _line += _spacing;

    LOVFlowO2.SetParent                 (&this->FMaintenance);

    LOVFlowO2.InitDbAccess              (FILTER_QO2_S16, COMPUTE);

    LOVFlowO2.SetSignValue              (TRUE);

    LOVFlowO2.Init                      (LOS,
                                         (UBYTE**)cMSG_FlowO2,
                                         _line,
                                         _col,
                                         25,
                                         (UBYTE**)cMSG_FlowUnit);

    LOVFlowO2.SetColSep                 (_colsep);

    LOVFlowO2.SetColValue1              (_colvalue);

    LOVFlowO2.SetFloatValue1            (TRUE);

    LOVFlowO2.InitCalibProperties       (CALIB_FLOW_O2_REQ_U16,
                                         CONTROL,
                                         FLOW_O2_CALIB_POINTS,
                                         FlowO2FloatSegmentList,
                                         FLOW_O2_CALIB_POINTS_NUMBER,
                                         CALIB_ADJUST_VANNE_FIO2_CMD,
                                         CONTROL,
                                         MEMO_CMD_VANNE_FIO2_TO_CALIB,
                                         CONTROL);

    /* Pression O2 */
    _line += _spacing;

    LOVPressO2.SetParent                (&this->FMaintenance);

    LOVPressO2.InitDbAccess             (FILTER_PRESSURE_O2_S16, COMPUTE);

    LOVPressO2.SetSignValue             (TRUE);

    LOVPressO2.SetDivider               (100);   

    LOVPressO2.Init                     (LOS,
                                         (UBYTE**)cMSG_O2Pressure,
                                         _line,
                                         _col,
                                         25,
                                         (UBYTE**)cMSG_PressBarUnit);

    LOVPressO2.SetColSep                (_colsep);

    LOVPressO2.SetColValue1             (_colvalue);

    LOVPressO2.SetFloatValue1           (TRUE);

    LOVPressO2.InitCalibProperties      (CALIB_PRESS_O2_REQ_U16,
                                         CONTROL,
                                         O2_PRESSURE_CALIB_POINTS,
                                         O2PressureFloatSegmentList,
                                         O2_PRESSURE_CALIB_POINTS_NUMBER,
                                         CALIB_ADJUST_VANNE_FIO2_CMD,
                                         CONTROL,
                                         MEMO_CMD_VANNE_FIO2_TO_CALIB,
                                         CONTROL);


    /* Blower */
    _line = 215;
    _spacing = 16;

    LOVPwmBlower.SetParent              (&this->FMaintenance);

    LOVPwmBlower.InitDbAccess           (CALIB_ADJUST_CMD_U16,
                                         CONTROL);

    LOVPwmBlower.Init                       (FREE_SQUARE, 
                                             (UBYTE**)cMSG_PwmBlower, 
                                             _line,
                                             8, 
                                             4000, 
                                             (UBYTE**)cMSG_NoneUnit);

    LOVPwmBlower.SetColSep              (130);

    LOVPwmBlower.SetColValue1           (138);

    LOVPwmBlower.SetColUnit1            (178);

    LOVPwmBlower.StopMonitoringMode ();

    LOVPwmBlower.RefreshEnable          (FALSE);

    FMaintenance.SetBlowerSpeedLine  (_line);

    _line += _spacing;

    LRConfMaint.SetParent               (&this->FMaintenance);

    LRConfMaint.Init                        (FREE_SQUARE, 
                                             (UBYTE**)cMSG_Back,
                                             _line, 
                                             8);


    /*--------------------- fenetre Histo Anomalies ------------------------------*/

    LRMaintAno.SetParent                    (&this->FHistoAno);

    LRMaintAno.Init                     (FREE_SQUARE, 
                                         (UBYTE**)cMSG_Back,
                                         226, 
                                         8);


    /*--------------------- fenetre Controle des tensions ------------------------*/
    _line = 149;
    _spacing = 21;
    _colsep = 165;
    _colvalue = 173;

    LRMaintTension.SetParent            (&this->FVoltControl);

    LRMaintTension.Init                 (FREE_SQUARE,
                                         (UBYTE**)cMSG_Back,
                                         231, 
                                         8);

    /* Tension Buzzer  */
    Val = 0;
    DataBaseAccess::WriteValue(&Val,MEASURE_ZERO_VALUE_U16,COMPUTE);

    LOVBuzzerVoltage.SetParent         (&this->FVoltControl);

    LOVBuzzerVoltage.InitDbAccess      (MEASURE_ZERO_VALUE_U16,
                                        COMPUTE);

    LOVBuzzerVoltage.Init             (LOCKS,
                                       (UBYTE**)cMSG_Buzzer,
                                       _line,
                                       8,
                                       252,
                                       (UBYTE**)cMSG_TensionUnit);

    LOVBuzzerVoltage.SetFloatValue1 (TRUE);

    LOVBuzzerVoltage.SetColSep         (_colsep);

    LOVBuzzerVoltage.SetDivider        (100);

    LOVBuzzerVoltage.SetColValue1      (_colvalue);

    LOVBuzzerVoltage.SetMaxDisplayValue     (9999);     

    _line += _spacing;

    /* Backup Buzzer  */
    LBackupBuzzer.SetParent           (&this->FVoltControl);

    LBackupBuzzer.Init               (FREE_SQUARE,
                                      (UBYTE**)cMSG_BuzzerSec,
                                      _line,
                                      8);
    _line += _spacing;

    /* Internal Battery menu  */
    LBatteryMenu.SetParent            (&this->FVoltControl);

    LBatteryMenu.Init                   (FREE_SQUARE,
                                         (UBYTE**)cMSG_BatteryMenu,
                                         _line,
                                         8);

    /* Correcteur d'altitude */
    _line += _spacing;

    LVSBaroCorrector.SetParent          (&this->FConfiguration);

    LVSBaroCorrector.InitDbAccess       (ADJUST_BAROMETRIC_CORRECTOR_U16,
                                         CONFIG);

    LVSBaroCorrector.Init               (FREE_SQUARE,
                                         (UBYTE**)cMSG_BaroCorrect,
                                         _line,
                                         8);

    LVSBaroCorrector.SetColSep          (_colsep);

    LVSBaroCorrector.SetColValue1       (_colvalue);

    LVSBaroCorrector.SetItem1Name       ((UBYTE**)cMSG_No);

    LVSBaroCorrector.SetItem2Name       ((UBYTE**)cMSG_Yes);



    /*--------------------- fenetre Menu batterie ------------------------*/

    LRMaintBattery.SetParent            (&this->FBatteryMenu);

    LRMaintBattery.Init                 (FREE_SQUARE,
                                         (UBYTE**)cMSG_Back,
                                         226,
                                         8);


    /*-------------------------- fenetre Graph -----------------------------------*/

    /* Vide */


    /*------------------------- fenetre Configuration Courbe----------------------*/

    _colsep = 127;
    _colvalue = 133;


    LVSVisu.SetParent                       (&this->FGraphConfig);

    LVSVisu.InitDbAccess                    (CURVE_DISPLAY_TYPE_MODE_U16, 
                                             CONFIG);

    LVSVisu.Init                            (FREE_SQUARE,
                                             (UBYTE**)cMSG_Visualisation, 
                                             50, 
                                             8);

    LVSVisu.SetColSep                       (_colsep);

    LVSVisu.SetColValue1                    (_colvalue);

    LVSVisu.SetItem1Name                    ((UBYTE**)cMSG_CurveVisualisation1);

    LVSVisu.SetItem2Name                    ((UBYTE**)cMSG_CurveVisualisation2);

    LOVPMax.SetParent                        (&this->FGraphConfig);

    LOVPMax.InitDbAccess                    (CURVE_MAX_PRESSURE_U16,
                                             CONFIG);

    LOVPMax.SetColSep                       (_colsep);

    LOVPMax.SetColValue1                    (_colvalue);

    LOVPMax.Init                            (FREE_SQUARE, 
                                             (UBYTE**)cMSG_PressionMax, 
                                             78, 
                                             8 ,
                                             1, 
                                             (UBYTE**)cMSG_PressureUnit);

    LOVPMax.InitDefaultValue            ((UBYTE**)cMSG_Auto, 
                                         0);

    LOVQMax.SetParent                       (&this->FGraphConfig);

    LOVQMax.InitDbAccess                    (CURVE_MAX_FLOW_U16,
                                             CONFIG);

    LOVQMax.SetColSep                       (_colsep);

    LOVQMax.SetColValue1                    (_colvalue);

    LOVQMax.Init                            (FREE_SQUARE, 
                                             (UBYTE**)cMSG_DebitMax, 
                                             106, 
                                             8 , 
                                             1, 
                                             (UBYTE**)cMSG_FlowUnit);

    LOVQMax.InitDefaultValue            ((UBYTE**)cMSG_Auto, 0);

    LOVVtMax.SetParent                  (&this->FGraphConfig);

    LOVVtMax.InitDbAccess               (CURVE_MAX_VT_U16,
                                         CONFIG);

    LOVVtMax.SetColSep                  (_colsep);

    LOVVtMax.SetColValue1               (_colvalue);

    LOVVtMax.Init                           (FREE_SQUARE, 
                                             (UBYTE**)cMSG_VtMax, 
                                             132, 
                                             8 , 
                                             1,
                                             (UBYTE**)cMSG_VolumeUnit);

    LOVVtMax.InitDefaultValue           ((UBYTE**)cMSG_Auto, 
                                         0);

    LOVTMax.SetParent                       (&this->FGraphConfig);

    LOVTMax.InitDbAccess                    (CURVE_MAX_TIME_U16,
                                             CONFIG);

    LOVTMax.SetColSep                       (_colsep);

    LOVTMax.SetColValue1                    (_colvalue);

    LOVTMax.Init                            (FREE_SQUARE, 
                                             (UBYTE**)cMSG_TempsMax, 
                                             160, 
                                             8 , 
                                             1, 
                                             (UBYTE**)cMSG_SecondUnit);

    LOVTMax.InitDefaultValue            ((UBYTE**)cMSG_Auto, 
                                         0);

    LVSRepresentation.SetParent     (&this->FGraphConfig);

    LVSRepresentation.InitDbAccess  (CURVE_DRAW_MODE_U16,
                                     CONFIG);

    LVSRepresentation.Init              (FREE_SQUARE, 
                                         (UBYTE**)cMSG_Representation,
                                         188, 
                                         8);

    LVSRepresentation.SetColSep     (_colsep);

    LVSRepresentation.SetColValue1  (_colvalue);

    LVSRepresentation.SetItem1Name  ((UBYTE**)cMSG_CurveRepresentation1);

    LVSRepresentation.SetItem2Name  ((UBYTE**)cMSG_CurveRepresentation2);

    LRGraphPref.SetParent             (&this->FGraphConfig);

    LRGraphPref.Init                      (FREE_SQUARE,
                                           (UBYTE**)cMSG_Back,
                                           226, 
                                           8);

    /*-------------------------- fenetre USB -------------------------------------*/

    _line = 60;
    _spacing = 20;
    _colsep = 175;


    LVSContRecord.SetParent              (&this->FUsb);

    LVSContRecord.InitDbAccess          (USB_CONTINUOUS_RECORDING_U16,
                                         USB);

    LVSContRecord.Init                  (FREE_SQUARE,
                                         (UBYTE**)cMSG_ContRecordUSB,
                                         _line,
                                         8);

    LVSContRecord.SetColSep             (_colsep);

    LVSContRecord.SetColValue1          (_colsep + 8);

    LVSContRecord.SetItem1Name          ((UBYTE**)cMSG_No);

    LVSContRecord.SetItem2Name          ((UBYTE**)cMSG_Yes);


    /* Transférer Tendance */
    _line += _spacing;

    LOVFTransfTrend.SetParent        (&this->FUsb);

    LOVFTransfTrend.InitDbAccess     (USB_TREND_TRANSFER_U16,
                                      USB);

    LOVFTransfTrend.Init             (FREE_SQUARE,
                                      (UBYTE**)cMSG_TransferTrendUSB,
                                      _line,
                                      8,
                                      1,
                                      (UBYTE**)cMSG_MonthUnit);

    LOVFTransfTrend.InitDefaultFlag  ((UBYTE**)cMSG_No,
                                      USB_TREND_TRANSFER_SELECT_U16,USB,FALSE);

    LOVFTransfTrend.SetColSep        (_colsep);

    LOVFTransfTrend.SetColValue1     (_colsep + 8);

    /* Effacer clé */
    _line += 2*_spacing;

    LVSEraseKey.SetParent               (&this->FUsb);

    LVSEraseKey.InitDbAccess            (USB_ERASE_KEY_U16,
                                         USB);

    LVSEraseKey.Init                        (FREE_SQUARE,
                                             (UBYTE**)cMSG_EraseKey,
                                             _line,
                                             8);

    LVSEraseKey.SetColSep               (_colsep);

    LVSEraseKey.SetColValue1            (_colsep + 8);

    LVSEraseKey.SetItem1Name            ((UBYTE**)cMSG_No);

    LVSEraseKey.SetItem2Name            ((UBYTE**)cMSG_Yes);





#ifdef HMI_CONFIG_USB_MONIT_TRANSFER
    /* Transférer Monitorage */
    _line += _spacing;

    LOVFTransfMonit.SetParent        (&this->FUsb);

    LOVFTransfMonit.InitDbAccess     (USB_MONITOR_TRANSFER_U16,
                                      USB);

    LOVFTransfMonit.Init             (FREE_SQUARE,
                                      (UBYTE**)cMSG_TransferMonitUSB,
                                      _line,
                                      8,
                                      4,
                                      (UBYTE**)cMSG_HourUnit);

    LOVFTransfMonit.InitDefaultFlag  ((UBYTE**)cMSG_No,
                                      USB_MONITOR_TRANSFER_SELECT_U16,USB,FALSE);

    LOVFTransfMonit.SetColSep        (_colsep);

    LOVFTransfMonit.SetColValue1     (_colsep + 8);

    LOVFTransfMonit.SetForcedVisible(FALSE);
#endif	

#ifdef HMI_CONFIG_USB_EVENTS_TRANSFER
    /* Enregistrement en continu */
    _line += _spacing;

    LVSFTransfEvents.SetParent           (&this->FUsb);

    LVSFTransfEvents.InitDbAccess       (USB_EVENTS_TRANSFER_U16,
                                         USB);

    LVSFTransfEvents.Init               (FREE_SQUARE,
                                         (UBYTE**)cMSG_TransferEventsUSB,
                                         _line,
                                         8);

    LVSFTransfEvents.SetColSep          (_colsep);

    LVSFTransfEvents.SetColValue1       (_colsep + 8);

    LVSFTransfEvents.SetItem1Name       ((UBYTE**)cMSG_No);

    LVSFTransfEvents.SetItem2Name       ((UBYTE**)cMSG_Yes);
#endif

#ifdef HMI_CONFIG_USB_SETTINGS_TRANSFER
    /* Transférer vers (clé ou legendair) */   
    _line += _spacing;

    LVSTransferSetOn.SetParent           (&this->FUsb);

    LVSTransferSetOn.InitDbAccess       (USB_TRANSFER_ON_U16,
                                         USB,
                                         USB_TRANSFER_APPLY_U16,
                                         USB);

    LVSTransferSetOn.Init               (FREE_SQUARE,
                                         (UBYTE**)cMSG_TransferOnUSB,
                                         _line,
                                         8,
                                         0,
                                         0);

    LVSTransferSetOn.SetColSep          (_colsep);

    LVSTransferSetOn.SetColValue1       (_colsep + 8);

    LVSTransferSetOn.SetColSep2     (_colsep + 60);

    LVSTransferSetOn.SetColValue2       (_colsep + 70);

    LVSTransferSetOn.SetItem1Name       ((UBYTE**)cMSG_TransferToKey);

    LVSTransferSetOn.SetItem2Name       ((UBYTE**)cMSG_TransferToVentil);

    LVSTransferSetOn.SetValue2Item1Name((UBYTE**) cMSG_No);

    LVSTransferSetOn.SetValue2Item2Name((UBYTE**) cMSG_Yes);

    LVSTransferSetOn.SetCallBackPtr(&StartSavingUsbSettings);
#endif	

    /* Stop */

    LStopUsb.SetParent                   (&this->FUsb);

    LStopUsb.Init                           (FREE_SQUARE,
                                             (UBYTE**)cMSG_Stop,
                                             234,
                                             8);


    /*-------------------------- fenetre Tendance --------------------------------*/

    LRTendance.SetParent                    (&this->FTendance);

    LRTendance.Init                     (FREE_SQUARE,
                                         (UBYTE**)cMSG_Back,
                                         232,
                                         8);

}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Creation de l'arbre d'etat																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																			 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE												  							  			*/
/******************************************************************************/
void Controller::BuildTree()
{

    /*----------------- Noeud Ventilation -------------------------------*/

    /*%C Noeud Mode Ventilation */
    GetNodeAt(NodeVentil)->Init (FALSE,
                                 FALSE,   
                                 &this->LModeVent,            
                                 &EventNodeVentil);

    /*%C Noeud Mode Ventilation */
    GetNodeAt(NodeModifVentil)->Init    (FALSE,
                                         FALSE,   
                                         &this->LModeVent,            
                                         &EventNodeModifVentil);

    /*%C Noeud Vt */
    GetNodeAt(NodeVt)->Init (FALSE,
                             FALSE,   
                             &this->LOVVT,
                             &EventNodeVt);

    /*%C Noeud Vt */
    GetNodeAt(NodeModifVt)->Init    (FALSE,
                                     FALSE,
                                     &this->LOVVT,                
                                     &EventNodeModifVt);

    /*%C Noeud LOVPi */
    GetNodeAt(NodePi)->Init (FALSE,
                             FALSE,
                             &this->LOVPi,
                             &EventNodePi);

    /*%C Noeud LOVPi */
    GetNodeAt(NodeModifPi)->Init    (FALSE,
                                     FALSE,
                                     &this->LOVPi,
                                     &EventNodeModifPi);

    /*%C Noeud LOVPi2 */
    GetNodeAt(NodePi2)->Init    (FALSE,
                                 FALSE,
                                 &this->LOVPi2,
                                 &EventNodePi2);

    /*%C Noeud LOVPi2 */
    GetNodeAt(NodeModifPi2)->Init   (FALSE,
                                     FALSE,
                                     &this->LOVPi2,
                                     &EventNodeModifPi2);


    /*%C Noeud LOVPControl */
    GetNodeAt(NodePControl)->Init   (FALSE,
                                     FALSE,
                                     &this->LOVPControl,
                                     &EventNodePControl);

    /*%C Noeud LOVPControl */
    GetNodeAt(NodeModifPControl)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVPControl,
                                         &EventNodeModifPControl);

    /*%C Noeud LOVPSupport */
    GetNodeAt(NodePSupport)->Init   (FALSE,
                                     FALSE,
                                     &this->LOVPSupport,
                                     &EventNodePSupport);

    /*%C Noeud LOVPSupport */
    GetNodeAt(NodeModifPSupport)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVPSupport,
                                         &EventNodeModifPSupport);
    /*%C Noeud LOVFVaci */
    GetNodeAt(NodeFVaci)->Init  (FALSE,
                                 FALSE,
                                 &this->LOVFVaci,
                                 &EventNodeFVaci);

    /*%C Noeud LOVFVaci */
    GetNodeAt(NodeModifFVaci)->Init (FALSE,
                                     FALSE,
                                     &this->LOVFVaci,
                                     &EventNodeModifFVaci);

    /*%C Noeud LOVPe */
    GetNodeAt(NodePe)->Init (FALSE,
                             FALSE,
                             &this->LOVPe,
                             &EventNodePe);

    /*%C Noeud LOVPe */
    GetNodeAt(NodeModifPe)->Init    (FALSE,
                                     FALSE,
                                     &this->LOVPe,
                                     &EventNodeModifPe);


    /*%C Noeud LOVPente */
    GetNodeAt(NodePente)->Init  (FALSE,
                                 FALSE,
                                 &this->LOVPente,
                                 &EventNodePente);

    /*%C Noeud LOVPente */
    GetNodeAt(NodeModifPente)->Init (FALSE,
                                     FALSE,
                                     &this->LOVPente,
                                     &EventNodeModifPente);


    /*%C Noeud LOVRampe */
    GetNodeAt(NodeRampe)->Init  (FALSE,
                                 FALSE,
                                 &this->LOVRampe,
                                 &EventNodeRampe);

    /*%C Noeud LOVRampe */
    GetNodeAt(NodeModifRampe)->Init (FALSE,
                                     FALSE,
                                     &this->LOVRampe,
                                     &EventNodeModifRampe);



    /*%C Noeud LOVFRMini */
    GetNodeAt(NodeFrMini)->Init (FALSE,
                                 FALSE,
                                 &this->LOVFRMini,
                                 &EventNodeFrMini);

    /*%C Noeud LOVFRMini */
    GetNodeAt(NodeModifFrMini)->Init    (FALSE,
                                         FALSE,
                                         &this->LOVFRMini,
                                         &EventNodeModifFrMini);

    /*%C Noeud LOVInspTime */
    GetNodeAt(NodeInspTime)->Init   (FALSE,
                                     FALSE,
                                     &this->LOVInspTime,
                                     &EventNodeInspTime);

    /*%C Noeud LOVInspTime */
    GetNodeAt(NodeModifInspTime)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVInspTime,
                                         &EventNodeModifInspTime);

    /*%C Noeud Trigger I */
    GetNodeAt(NodeTriggerI)->Init   (FALSE,
                                     FALSE,
                                     &this->LOVTrigI,
                                     &EventNodeTriggerI);

    /*%C Noeud Trigger I */
    GetNodeAt(NodeModifTriggerI)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVTrigI,
                                         &EventNodeModifTriggerI);

    /*%C Noeud Soupir Select */
    GetNodeAt(NodeSoupirSelect)->Init   (FALSE,
                                         FALSE,
                                         &this->LSTVSoupir,
                                         &EventNodeSoupirSelect);

    /*%C Noeud Soupir Select */
    GetNodeAt(NodeModifSoupirSelect)->Init  (FALSE,
                                             FALSE,
                                             &this->LSTVSoupir,
                                             &EventNodeModifSoupirSelect);

    /*%C Noeud Soupir Vt Coeff */
    GetNodeAt(NodeSoupirVtCoeff)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVSVtSoupir,
                                         &EventNodeSoupirVtCoeff);

    /*%C Noeud Soupir Vt Coeff */
    GetNodeAt(NodeModifSoupirVtCoeff)->Init (FALSE,
                                             FALSE,
                                             &this->LOVSVtSoupir,
                                             &EventNodeModifSoupirVtCoeff);

    /*%C Noeud Soupir Compteur */
    GetNodeAt(NodeSoupirCpt)->Init  (FALSE,
                                     FALSE,
                                     &this->LOVCptSoupir,
                                     &EventNodeSoupirCpt);

    /*%C Noeud Soupir Compteur */
    GetNodeAt(NodeModifSoupirCpt)->Init (FALSE,
                                         FALSE,
                                         &this->LOVCptSoupir,
                                         &EventNodeModifSoupirCpt);

    /*%C Noeud Trigger E */
    GetNodeAt(NodeTriggerE)->Init   (FALSE,
                                     FALSE,
                                     &this->LOVTrigE,
                                     &EventNodeTriggerE);

    /*%C Noeud Trigger E */
    GetNodeAt(NodeModifTriggerE)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVTrigE,
                                         &EventNodeModifTriggerE);

    /*%C Noeud LOVFSecu */
    GetNodeAt(NodeFsecu)->Init  (FALSE,
                                 FALSE,
                                 &this->LOVFSecu,
                                 &EventNodeFsecu);

    /*%C Noeud LOVFSecu */
    GetNodeAt(NodeModifFsecu)->Init (FALSE,
                                     FALSE,
                                     &this->LOVFSecu,
                                     &EventNodeModifFsecu);


    /*%C Noeud FiO2 */
    GetNodeAt(NodeFiO2)->Init   (FALSE,
                                 FALSE,
                                 &this->LOVFiO2,
                                 &EventNodeFiO2);
    /*%C Noeud FiO2 */
    GetNodeAt(NodeModifFiO2)->Init  (FALSE,
                                     FALSE,
                                     &this->LOVFiO2,
                                     &EventNodeModifFiO2);


    /*%C Noeud Apnee */
    GetNodeAt(NodeApnee)->Init  (FALSE,
                                 FALSE,
                                 &this->LOVApnee,
                                 &EventNodeApnee);

    /*%C Noeud Apnee */
    GetNodeAt(NodeModifApnee)->Init (FALSE,
                                     FALSE,
                                     &this->LOVApnee,
                                     &EventNodeModifApnee);

    /*%C Noeud Vt Cible */
    GetNodeAt(NodeVtCible)->Init    (FALSE,
                                     FALSE,   
                                     &this->LOVVTCible,           
                                     &EventNodeVtCible);

    /*%C Noeud Vt Cible */
    GetNodeAt(NodeModifVtCible)->Init   (FALSE,
                                         FALSE,   
                                         &this->LOVVTCible,
                                         &EventNodeModifVtCible);

    /*%C Noeud Pression Maxi */
    GetNodeAt(NodePiMax)->Init  (FALSE,
                                 FALSE,
                                 &this->LOVPiMax,             
                                 &EventNodePiMax);

    /*%C Noeud Pression Maxi */
    GetNodeAt(NodeModifPiMax)->Init (FALSE,
                                     FALSE,
                                     &this->LOVPiMax,             
                                     &EventNodeModifPiMax);

    /*%C Noeud Trigger E (signé) */
    GetNodeAt(NodeTriggerEsigned)->Init (FALSE,
                                         FALSE,
                                         &this->LOVSTrigE,
                                         &EventNodeTriggerEsigned);

    /*%C Noeud Trigger E (signé) */
    GetNodeAt(NodeModifTriggerEsigned)->Init    (FALSE,
                                                 FALSE,
                                                 &this->LOVSTrigE,
                                                 &EventNodeModifTriggerEsigned);


    /*%C Noeud Préférences */
    GetNodeAt(NodePreference)->Init (FALSE,
                                     FALSE,   
                                     &this->LPreferences,
                                     &EventNodePreference);

    /*%C Noeud Changement de Mode */
    GetNodeAt(NodeModeChange)->Init (FALSE,
                                     FALSE,   
                                     &this->LSTVChgtModeV,
                                     &EventNodeModeChange);

    /*%C Noeud Changement de Mode */
    GetNodeAt(NodeModifModeChange)->Init    (FALSE,
                                             FALSE,   
                                             &this->LSTVChgtModeV,        
                                             &EventNodeModifModeChange);

    GetNodeAt(NodeGhost)->Init  (FALSE,
                                 FALSE,
                                 &this->GhostObject,            
                                 &EventNodeGhost);


    /*------------------------- Noeud Alarme -------------------------------------*/

    /*%C Noeud Mode Alarme */
    GetNodeAt(NodeAlarm)->Init  (FALSE,
                                 FALSE,   
                                 &this->LModeAlarm,           
                                 &EventNodeAlarm);

    /*%C Noeud Mode Alarme */
    GetNodeAt(NodeModifAlarm)->Init (FALSE,
                                     FALSE,
                                     &this->LModeAlarm,           
                                     &EventNodeModifAlarm);

    /*%C Noeud Pi max */
    GetNodeAt(NodeAlPi)->Init   (FALSE,
                                 FALSE,
                                 &this->LOVPiMbar,
                                 &EventNodeAlPi);

    /*%C Noeud Pi max */
    GetNodeAt(NodeAlPiMin)->Init    (FALSE,
                                     FALSE,   
                                     &this->LOVPiMbar,
                                     &EventNodeAlPiMin);

    /*%C Noeud Pi max */
    GetNodeAt(NodeAlPiMax)->Init    (FALSE,
                                     FALSE,   
                                     &this->LOVPiMbar,
                                     &EventNodeAlPiMax);

    /*%C Noeud Vti */
    GetNodeAt(NodeAlVti)->Init  (FALSE,
                                 FALSE,   
                                 &this->LOVVtiMl,             
                                 &EventNodeAlVti);

    /*%C Noeud Vti */
    GetNodeAt(NodeAlVtiMin)->Init   (FALSE,
                                     FALSE,   
                                     &this->LOVVtiMl,
                                     &EventNodeAlVtiMin);

    /*%C Noeud Vti */
    GetNodeAt(NodeAlVtiMax)->Init   (FALSE,
                                     FALSE,   
                                     &this->LOVVtiMl,             
                                     &EventNodeAlVtiMax);

    /*%C Noeud Vte */
    GetNodeAt(NodeAlVte)->Init  (FALSE,
                                 FALSE,   
                                 &this->LOVVteMl,
                                 &EventNodeAlVte);

    /*%C Noeud Vte */
    GetNodeAt(NodeAlVteMin)->Init   (FALSE,
                                     FALSE,   
                                     &this->LOVVteMl,
                                     &EventNodeAlVteMin);

    /*%C Noeud Vte */
    GetNodeAt(NodeAlVteMax)->Init   (FALSE,
                                     FALSE,   
                                     &this->LOVVteMl,
                                     &EventNodeAlVteMax);

    /*%C Noeud Calib Vte */
    GetNodeAt(NodeAlCalibVte)->Init (FALSE,
                                     FALSE,
                                     &this->LSTICalibQExp,
                                     &EventNodeAlCalibVte);

    /*%C Noeud Calib Vte */
    GetNodeAt(NodeAlCalibVte2)->Init    (FALSE,
                                         FALSE,
                                         &this->LSTICalibQExp,
                                         &EventNodeAlCalibVte2);

    /*%C Noeud Fuite */
    GetNodeAt(NodeAlFuite)->Init    (FALSE,
                                     FALSE,
                                     &this->LTOVFuiteLMin,
                                     &EventNodeAlFuite);

    /*%C Noeud Fuite */
    GetNodeAt(NodeAlFuiteMax)->Init (FALSE,
                                     FALSE,
                                     &this->LTOVFuiteLMin,
                                     &EventNodeAlFuiteMax);


    /*%C Noeud Fi02 */
    GetNodeAt(NodeAlFiO2)->Init (FALSE,
                                 FALSE,
                                 &this->LTTVFiO2,
                                 &EventNodeAlFiO2);

    /*%C Noeud Fi02 */
    GetNodeAt(NodeAlFiO2Min)->Init  (FALSE,
                                     FALSE,
                                     &this->LTTVFiO2,
                                     &EventNodeAlFiO2Min);

    /*%C Noeud Fi02 */
    GetNodeAt(NodeAlFiO2Max)->Init  (FALSE,
                                     FALSE,
                                     &this->LTTVFiO2,
                                     &EventNodeAlFiO2Max);

    /*%C Noeud Calib Fi02 */
    GetNodeAt(NodeAlCalibFiO2)->Init    (FALSE,
                                         FALSE,
                                         &this->LSTICalibFiO2,
                                         &EventNodeAlCalibFiO2);

    /*%C Noeud Calib FiO2 */
    GetNodeAt(NodeAlCalibFiO2_2)->Init  (FALSE,
                                         FALSE,
                                         &this->LSTICalibFiO2,
                                         &EventNodeAlCalibFiO2_2);

    /*%C Noeud Fr */
    GetNodeAt(NodeAlFr)->Init   (FALSE,
                                 FALSE,
                                 &this->LOVFrCMin,
                                 &EventNodeAlFr);

    /*%C Noeud Fr */
    GetNodeAt(NodeAlFrMax)->Init    (FALSE,
                                     FALSE,
                                     &this->LOVFrCMin,
                                     &EventNodeAlFrMax);

    /*%C Noeud SpO2 */
    GetNodeAt(NodeAlSpO2)->Init  (FALSE,
                                  FALSE,
                                  &this->LTTVSpO2,
                                  &EventNodeAlSpO2);
    /*%C Noeud SpO2 */
    GetNodeAt(NodeAlSpO2Min)->Init  (FALSE,
                                     FALSE,
                                     &this->LTTVSpO2,
                                     &EventNodeAlSpO2Min);
    /*%C Noeud SpO2 */
    GetNodeAt(NodeAlSpO2Max)->Init  (FALSE,
                                     FALSE,
                                     &this->LTTVSpO2,
                                     &EventNodeAlSpO2Max);
    /*%C Noeud Ti */
    GetNodeAt(NodeAlTi)->Init   (FALSE,
                                 FALSE,
                                 &this->LTTVTiS,              
                                 &EventNodeAlTi);

    /*%C Noeud Ti */
    GetNodeAt(NodeAlTiMin)->Init    (FALSE,
                                     FALSE,   
                                     &this->LTTVTiS,              
                                     &EventNodeAlTiMin);

    /*%C Noeud Ti */
    GetNodeAt(NodeAlTiMax)->Init    (FALSE,
                                     FALSE,
                                     &this->LTTVTiS,              
                                     &EventNodeAlTiMax);




    /*%C Noeud Historique Alarme */
    GetNodeAt(NodeAlHisto)->Init    (FALSE,
                                     FALSE,   
                                     &this->LHistoAlarm,
                                     &EventNodeAlHisto);

    /*%C Noeud Changement de Mode */
    GetNodeAt(NodeAlModeChange)->Init   (FALSE,
                                         FALSE,   
                                         &this->LOVChgtModeA,
                                         &EventNodeAlModeChange);

    /*%C Noeud Changement de Mode */
    GetNodeAt(NodeModifAlModeChange)->Init  (FALSE,
                                             FALSE,
                                             &this->LOVChgtModeA,         
                                             &EventNodeModifAlModeChange);

    /*%C Noeud fantôme des alarmes */
    GetNodeAt(NodeAlGhost)->Init    (FALSE,
                                     FALSE,
                                     &this->GhostObject,
                                     &EventNodeAlGhost);


    /*------------------------- Noeud Historique Alarme --------------------------*/

    /*%C Noeud Retour */
    GetNodeAt(NodeHistAlBack)->Init (TRUE,
                                     FALSE,
                                     &this->LRAlarmeA,
                                     &EventNodeHistAlBack);

    /*%C Noeud Alarmes Annulées */
    GetNodeAt(NodeHistAlCancelled)->Init    (TRUE,
                                             FALSE,   
                                             &this->LCancelledAlarm,
                                             &EventNodeHistAlCancelled);

    /*------------------------- Menu Configuration -------------------------------*/

    /*%C Noeud Compteur Machine */
    GetNodeAt(NodeConfMachineHour)->Init    (FALSE,
                                             FALSE,
                                             &this->LOVMachineHrs,
                                             &EventNodeConfMachineHour);

    /*%C Noeud Langue */
    GetNodeAt(NodeConfLang)->Init   (TRUE,
                                     FALSE,
                                     &this->LVSLanguage,
                                     &EventNodeConfLang);

    /*%C Noeud Langue */
    GetNodeAt(NodeModifConfLang)->Init  (FALSE,
                                         FALSE,    
                                         &this->LVSLanguage,
                                         &EventNodeModifConfLang);

    /*%C Noeud Date */
    GetNodeAt(NodeConfDate)->Init   (FALSE,
                                     FALSE,
                                     &this->VDConf,
                                     &EventNodeConfDate);

    /*%C Noeud Date */
    GetNodeAt(NodeConfMonth)->Init  (FALSE,
                                     FALSE,
                                     &this->VDConf,
                                     &EventNodeConfMonth);

    /*%C Noeud Date */
    GetNodeAt(NodeConfDay)->Init    (FALSE,
                                     FALSE,    
                                     &this->VDConf,              
                                     &EventNodeConfDay);

    /*%C Noeud Date */
    GetNodeAt(NodeConfYear)->Init   (FALSE,
                                     FALSE,   
                                     &this->VDConf,              
                                     &EventNodeConfYear);

    /*%C Noeud Heure */
    GetNodeAt(NodeConfTime)->Init   (FALSE,
                                     FALSE,    
                                     &this->VTConf,
                                     &EventNodeConfTime);

    /*%C Noeud Heure */
    GetNodeAt(NodeConfHour)->Init   (FALSE,
                                     FALSE,    
                                     &this->VTConf,
                                     &EventNodeConfHour);

    /*%C Noeud Minute */
    GetNodeAt(NodeConfMinute)->Init (FALSE,
                                     FALSE,    
                                     &this->VTConf,
                                     &EventNodeConfMinute);

    /*%C Noeud Second */
    GetNodeAt(NodeConfSecond)->Init (FALSE,
                                     FALSE,    
                                     &this->VTConf,
                                     &EventNodeConfSecond);

    /*%C Noeud Alarme Voluntary Stop */
    GetNodeAt(NodePrefVoluntaryStopAlarm)->Init (FALSE,
                                                 FALSE,
                                                 &this->LVSVoluntaryStopAlarm,
                                                 &EventNodePrefVoluntaryStopAlarm);

    /*%C Noeud Alarme Voluntary Stop */
    GetNodeAt(NodeModifPrefVoluntaryStopAlarm)->Init    (FALSE,
                                                         FALSE,
                                                         &this->LVSVoluntaryStopAlarm,
                                                         &EventNodeModifPrefVoluntaryStopAlarm);
    /*%C Noeud Unité Pression */
    GetNodeAt(NodeConfPressureUnit)->Init   (FALSE,
                                             FALSE,
                                             &this->LVSPressureUnit,
                                             &EventNodeConfPressureUnit);

    /*%C Noeud Unité Pression */
    GetNodeAt(NodeModifConfPressureUnit)->Init  (FALSE,
                                                 FALSE,
                                                 &this->LVSPressureUnit,
                                                 &EventNodeModifConfPressureUnit);
	/*%C Alarm Tone */

	GetNodeAt(NodeConfAlarmTone)->Init	(FALSE,
                                         FALSE,
										&this->LVSAlarmTone,
										&EventNodeConfAlarmTone);

	GetNodeAt(NodeModifConfAlarmTone)->Init	(FALSE,
                                             FALSE,
										&this->LVSAlarmTone,
										&EventNodeModifConfAlarmTone);

    /*%C Noeud compteur patient */
    GetNodeAt(NodeConfPatientCount)->Init   (FALSE,
                                             FALSE,
                                             &this->LOVPatientHrs,
                                             &EventNodeConfPatientCount);

    /*%C Noeud compteur patient */
    GetNodeAt(NodeModifConfPatientCount)->Init  (FALSE,
                                                 FALSE,
                                                 &this->LOVPatientHrs,
                                                 &EventNodeModifConfPatientCount);


    /*%C Noeud Reset compteur patient */
    GetNodeAt(NodeConfPatientReset)->Init   (FALSE,
                                             FALSE,
                                             &this->LVSSResetPatientHrs,
                                             &EventNodeConfPatientReset);

    /*%C Noeud Reset compteur patient */
    GetNodeAt(NodeModifConfPatientReset)->Init  (FALSE,
                                                 FALSE,
                                                 &this->LVSSResetPatientHrs,
                                                 &EventNodeModifConfPatientReset);

    
	/*%C Reset Default Settings */
	GetNodeAt(NodeConfResetDefaultSetting)->Init	(FALSE,
                                         FALSE,
										&this->LVSSRestoreDefaultSettings,
										&EventNodeConfResetDefaultSetting);

	GetNodeAt(NodeModifConfResetDefaultSetting)->Init	(FALSE,
                                             FALSE,
										&this->LVSSRestoreDefaultSettings,
										&EventNodeModifConfResetDefaultSetting);

	

    /*%C Noeud maintenance */
    GetNodeAt(NodeConfMaint)->Init  (FALSE,
                                     FALSE,
                                     &this->LMaintenance,
                                     &EventNodeConfMaint);

	/*%C Next Page of Configuration/Setup */
	GetNodeAt(NodeConfNextPage)->Init	(FALSE,
										FALSE,
										&this->LNextPage,
										&EventNodeConfNextPage);

/*--------------------- Menu Configuration Page 2 ----------------------------*/


	/*%C Noeud Mode Cyclage */
	GetNodeAt(NodeConfModeCycl)->Init(TRUE,
										FALSE,
										&HMI_Setup1::GetInstance().LVSModeCycl,
										&EventNodeConfModeCycl);

	/*%C Noeud Mode Cyclage */
	GetNodeAt(NodeModifConfModeCycl)->Init	(FALSE,
										FALSE,
										&HMI_Setup1::GetInstance().LVSModeCycl,
										&EventNodeModifConfModeCycl);

    /*%C Noeud Convention de Pression */
	GetNodeAt(NodeConfRelativePress)->Init	(FALSE,
										FALSE,
										&HMI_Setup1::GetInstance().LVSRelativePressure,
										&EventNodeConfRelativePress);

	/*%C Noeud Convention de Pression */
	GetNodeAt(NodeModifConfRelativePress)->Init	(FALSE,
										FALSE,
										&HMI_Setup1::GetInstance().LVSRelativePressure,
										&EventNodeModifConfRelativePress);


	/*%C Noeud Convention Trigger E */
	GetNodeAt(NodeConfConvTrigE)->Init	(FALSE,
										FALSE,
										&HMI_Setup1::GetInstance().LVSConvTrigE,
										&EventNodeConfConvTrigE);

	/*%C Noeud Convention Trigger E */
	GetNodeAt(NodeModifConfConvTrigE)->Init	(FALSE,
										FALSE,
										&HMI_Setup1::GetInstance().LVSConvTrigE,
										&EventNodeModifConfConvTrigE);
	/*%C Noeud retour configuration */
	GetNodeAt(NodeConfig1BackToConfig)->Init(FALSE,
										FALSE,    
										&HMI_Setup1::GetInstance().LVSBack,
										&EventNodeConfig1BackToConfig);

    /*------------------------- Circuit Check nodes ------------------------------*/

    /*%C Node Circuit Leak Check */
    GetNodeAt(NodeTestCircuitLeak)->Init   (TRUE,
                                            FALSE,
                                            &this->LCircuitLeak,
                                            &EventNodeCircuitLeak);

    /*------------------------- Noeud Preference  --------------------------------*/

    /*%C Noeud Veille ecran */
    GetNodeAt(NodePrefScreenSave)->Init (FALSE,
                                         FALSE,    
                                         &this->LVSScreenSave,
                                         &EventNodePrefScreenSave);

    /*%C Noeud Veille ecran */
    GetNodeAt(NodeModifPrefScreenSave)->Init    (FALSE,
                                                 FALSE,    
                                                 &this->LVSScreenSave,       
                                                 &EventNodeModifPrefScreenSave);


    /*%C Noeud Contraste */

    GetNodeAt(NodePrefBrightness)->Init (FALSE,
                                         FALSE,
                                         &this->LPBBrightness,
                                         &EventNodePrefBrightness);

    /*%C Noeud Contraste */
    GetNodeAt(NodeModifPrefBrightness)->Init    (FALSE,
                                                 FALSE,
                                                 &this->LPBBrightness,
                                                 &EventNodeModifPrefBrightness);
    /*%C Noeud Niveau sonore */
    GetNodeAt(NodePrefSoundLevel)->Init (FALSE,
                                         FALSE,
                                         &this->LPBSoundLevel,
                                         &EventNodePrefSoundLevel);

    /*%C Noeud Niveau sonore */
    GetNodeAt(NodeModifPrefSoundLevel)->Init    (FALSE,
                                                 FALSE,
                                                 &this->LPBSoundLevel,
                                                 &EventNodeModifPrefSoundLevel);


    /*%C Noeud Tonalite clavier */
    GetNodeAt(NodePrefKeyTone)->Init    (FALSE,
                                         FALSE,
                                         &this->LOVFDAjustKeyTone,
                                         &EventNodePrefKeyTone);

    /*%C Noeud Tonalite clavier */
    GetNodeAt(NodeModifPrefKeyTone)->Init   (FALSE,
                                             FALSE,
                                             &this->LOVFDAjustKeyTone,
                                             &EventNodeModifPrefKeyTone);

    /*%C Noeud Alarme Apnée */
    GetNodeAt(NodePrefApneaAlarm)->Init (FALSE,
                                         FALSE,
                                         &this->LVSApneaAlarm,
                                         &EventNodePrefApneaAlarm);

    /*%C Noeud Alarme Apnée */
    GetNodeAt(NodeModifPrefApneaAlarm)->Init    (FALSE,
                                                 FALSE,
                                                 &this->LVSApneaAlarm,
                                                 &EventNodeModifPrefApneaAlarm);

    /*%C Noeud Alarme Déconnexion */
    GetNodeAt(NodePrefDisconnectionAlarm)->Init (FALSE,
                                                 FALSE,
                                                 &this->LOVFDisconnectionAlarm,
                                                 &EventNodePrefDisconnectionAlarm);

    /*%C Noeud Alarme Déconnexion */
    GetNodeAt(NodeModifPrefDisconnectionAlarm)->Init    (FALSE,
                                                         FALSE,
                                                         &this->LOVFDisconnectionAlarm,
                                                         &EventNodeModifPrefDisconnectionAlarm);


#ifdef HMI_CONFIG_CURVES
    #ifdef HMI_CONFIG_CURVE_CFG

    /*%C Menu config courbes */
    GetNodeAt(NodePrefCurveConfig)->Init    (FALSE,
                                             FALSE,
                                             &this->LCurveConfiguration,
                                             &EventNodePrefCurveConfig);
    #else

    /*%C Choix affichage courbes */
    GetNodeAt(NodePrefWaveDisplay)->Init    (FALSE,
                                             FALSE,
                                             &this->LVSWaveformDisplay,
                                             &EventNodePrefWaveDisplay);

    /*%C Choix affichage courbes */
    GetNodeAt(NodeModifPrefWaveDisplay)->Init   (FALSE,
                                                 FALSE,
                                                 &this->LVSWaveformDisplay,
                                                 &EventNodeModifPrefWaveDisplay);

    #endif
#endif

    /*%C Choix circuit pediatrique */
    GetNodeAt(NodePrefPediatricCircuit)->Init   (FALSE,
                                                 FALSE,
                                                 &this->LVSPediatricCircuit,
                                                 &EventNodePrefPediatricCircuit);

    /*%C Choix circuit pediatrique */
    GetNodeAt(NodeModifPrefPediatricCircuit)->Init  (FALSE,
                                                     FALSE,
                                                     &this->LVSPediatricCircuit,
                                                     &EventNodeModifPrefPediatricCircuit);

    /*%C Noeud Rapport Ventilation */
    GetNodeAt(NodePrefTrend)->Init  (TRUE,
                                     FALSE,
                                     &this->LTrendMenu,
                                     &EventNodePrefTrend);

    /*%C Noeud Retour Ventilation */
    GetNodeAt(NodePrefBackVentil)->Init (TRUE,
                                         FALSE,
                                         &this->LRVentilMenu,
                                         &EventNodePrefBackVentil);


    /*------------------------- Noeud Maintenance --------------------------------*/

    /*%C Noeud Historique anomalie */
    GetNodeAt(NodeMaintHistAno)->Init   (TRUE,
                                         FALSE,    
                                         &this->LHistoAnom,            
                                         &EventNodeMaintHistAno);

    /*%C Noeud Controle des tensions */
    GetNodeAt(NodeMaintVoltCtrl)->Init  (FALSE,
                                         FALSE,    
                                         &this->LVoltCtrl,
                                         &EventNodeMaintVoltCtrl);

    /*%C Noeud Calibration des capteurs */
    GetNodeAt(NodeMaintSensorCal)->Init (FALSE,
                                         FALSE,    
                                         &this->LSensorCal,
                                         &EventNodeMaintSensorCal);

    /*%C Noeud Pression patient */
    GetNodeAt(NodeMaintPatientPressure)->Init   (FALSE,
                                                 FALSE,    
                                                 &this->LOVPatientPressure,
                                                 &EventNodeMaintPatientPressure);

    /*%C Noeud Pression patient */
    GetNodeAt(NodeMaintPatientPressure1)->Init  (FALSE,
                                                 FALSE,    
                                                 &this->LOVPatientPressure,   
                                                 &EventNodeMaintPatientPressure1);

    /*%C Noeud Pression patient */
    GetNodeAt(NodeMaintPatientPressure2)->Init  (FALSE,
                                                 FALSE,    
                                                 &this->LOVPatientPressure,
                                                 &EventNodeMaintPatientPressure2);

    /*%C Noeud Pression patient */
    GetNodeAt(NodeMaintPatientPressure3)->Init  (FALSE,
                                                 FALSE,    
                                                 &this->LOVPatientPressure,   
                                                 &EventNodeMaintPatientPressure3);

    /*%C Noeud FAS valve Calibration */
    GetNodeAt(NoteMaintValvePressure)->Init (FALSE,
                                             FALSE,    
                                             &this->LOVValvePressure,     
                                             &EventNoteMaintValvePressure);

    /*%C Noeud FAS valve Calibration */
    GetNodeAt(NoteMaintValvePressure1)->Init    (FALSE,
                                                 FALSE,    
                                                 &this->LOVValvePressure,     
                                                 &EventNoteMaintValvePressure1);

    /*%C Noeud FAS valve Calibration */
    GetNodeAt(NoteMaintValvePressure2)->Init    (FALSE,
                                                 FALSE,
                                                 &this->LOVValvePressure,     
                                                 &EventNoteMaintValvePressure2);

    /*%C Noeud FAS valve Calibration */
    GetNodeAt(NoteMaintValvePressure3)->Init    (FALSE,
                                                 FALSE,
                                                 &this->LOVValvePressure,     
                                                 &EventNoteMaintValvePressure3);

    /*%C Noeud Debit inspire */
    GetNodeAt(NodeMaintFlowIns)->Init   (FALSE,
                                         FALSE,
                                         &this->LOVFlowIns,
                                         &EventNodeMaintFlowIns);

    /*%C Noeud Debit inspire */
    GetNodeAt(NodeMaintFlowIns1)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowIns,
                                         &EventNodeMaintFlowIns1);

    /*%C Noeud Debit inspire */
    GetNodeAt(NodeMaintFlowIns2)->Init  (FALSE,
                                         FALSE,    
                                         &this->LOVFlowIns,           
                                         &EventNodeMaintFlowIns2);

    /*%C Noeud Debit inspire */
    GetNodeAt(NodeMaintFlowIns3)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowIns,           
                                         &EventNodeMaintFlowIns3);

    /*%C Noeud Debit inspire */
    GetNodeAt(NodeMaintFlowIns4)->Init  (FALSE,
                                         FALSE,    
                                         &this->LOVFlowIns,           
                                         &EventNodeMaintFlowIns4);

    /*%C Noeud Debit inspire */
    GetNodeAt(NodeMaintFlowIns5)->Init  (FALSE,
                                         FALSE,    
                                         &this->LOVFlowIns,
                                         &EventNodeMaintFlowIns5);

    /*%C Noeud Debit inspire */
    GetNodeAt(NodeMaintFlowIns6)->Init  (FALSE,
                                         FALSE,   
                                         &this->LOVFlowIns,           
                                         &EventNodeMaintFlowIns6);

    /*%C Noeud Debit inspire */
    GetNodeAt(NodeMaintFlowIns7)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowIns,
                                         &EventNodeMaintFlowIns7);

    /*%C Noeud Debit inspire */
    GetNodeAt(NodeMaintFlowIns8)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowIns,
                                         &EventNodeMaintFlowIns8);

    /*%C Noeud Debit inspire */
    GetNodeAt(NodeMaintFlowIns9)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowIns,
                                         &EventNodeMaintFlowIns9);


    /*%C Noeud Debit expire */
    GetNodeAt(NodeMaintFlowExp)->Init   (FALSE,
                                         FALSE,
                                         &this->LOVFlowExp,
                                         &EventNodeMaintFlowExp);

    /*%C Noeud Debit expire */
    GetNodeAt(NodeMaintFlowExp1)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowExp,
                                         &EventNodeMaintFlowExp1);

    /*%C Noeud Debit expire */
    GetNodeAt(NodeMaintFlowExp2)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowExp,
                                         &EventNodeMaintFlowExp2);

    /*%C Noeud Debit expire */
    GetNodeAt(NodeMaintFlowExp3)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowExp,           
                                         &EventNodeMaintFlowExp3);

    /*%C Noeud Debit expire */
    GetNodeAt(NodeMaintFlowExp4)->Init  (FALSE,
                                         FALSE,    
                                         &this->LOVFlowExp,
                                         &EventNodeMaintFlowExp4);

    /*%C Noeud Debit expire */
    GetNodeAt(NodeMaintFlowExp5)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowExp,           
                                         &EventNodeMaintFlowExp5);

    /*%C Noeud Debit expire */
    GetNodeAt(NodeMaintFlowExp6)->Init  (FALSE,
                                         FALSE,    
                                         &this->LOVFlowExp,           
                                         &EventNodeMaintFlowExp6);

    /*%C Noeud Debit expire */
    GetNodeAt(NodeMaintFlowExp7)->Init  (FALSE,
                                         FALSE,    
                                         &this->LOVFlowExp,           
                                         &EventNodeMaintFlowExp7);

    /*%C Noeud Debit expire */
    GetNodeAt(NodeMaintFlowExp8)->Init  (FALSE,
                                         FALSE,    
                                         &this->LOVFlowExp,           
                                         &EventNodeMaintFlowExp8);

    /*%C Noeud Debit expire */
    GetNodeAt(NodeMaintFlowExp9)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowExp,
                                         &EventNodeMaintFlowExp9);

    /*%C Noeud FiO2 */
    GetNodeAt(NodeMaintFiO2Concent)->Init    (FALSE,
                                              FALSE,
                                              &this->LOVFiO2Concent,
                                              &EventNodeMaintFiO2Concent);

    /*%C Noeud FiO2 */
    GetNodeAt(NodeMaintFiO2Concent1)->Init  (FALSE,
                                             FALSE,
                                             &this->LOVFiO2Concent,
                                             &EventNodeMaintFiO2Concent1);

    /*%C Noeud FiO2 */
    GetNodeAt(NodeMaintFiO2Concent2)->Init  (FALSE,
                                             FALSE,
                                             &this->LOVFiO2Concent,
                                             &EventNodeMaintFiO2Concent2);


    /*%C Noeud Debit O2 */
    GetNodeAt(NodeMaintFlowO2)->Init    (FALSE,
                                         FALSE,
                                         &this->LOVFlowO2,
                                         &EventNodeMaintFlowO2);

    /*%C Noeud Debit O2 */
    GetNodeAt(NodeMaintFlowO2_1)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowO2,
                                         &EventNodeMaintFlowO2_1);

    /*%C Noeud Debit O2 */
    GetNodeAt(NodeMaintFlowO2_2)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowO2,
                                         &EventNodeMaintFlowO2_2);

    /*%C Noeud Debit O2 */
    GetNodeAt(NodeMaintFlowO2_3)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowO2,
                                         &EventNodeMaintFlowO2_3);

    /*%C Noeud Debit O2 */
    GetNodeAt(NodeMaintFlowO2_4)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowO2,
                                         &EventNodeMaintFlowO2_4);

    /*%C Noeud Debit O2 */
    GetNodeAt(NodeMaintFlowO2_5)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowO2,
                                         &EventNodeMaintFlowO2_5);

    /*%C Noeud Debit O2 */
    GetNodeAt(NodeMaintFlowO2_6)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowO2,
                                         &EventNodeMaintFlowO2_6);

    /*%C Noeud Debit O2 */
    GetNodeAt(NodeMaintFlowO2_7)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowO2,
                                         &EventNodeMaintFlowO2_7);

    /*%C Noeud Debit O2 */
    GetNodeAt(NodeMaintFlowO2_8)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowO2,
                                         &EventNodeMaintFlowO2_8);

    /*%C Noeud Debit O2 */
    GetNodeAt(NodeMaintFlowO2_9)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVFlowO2,
                                         &EventNodeMaintFlowO2_9);

    /*%C Noeud Pression O2 */
    GetNodeAt(NodeMaintPressO2)->Init   (FALSE,
                                         FALSE,
                                         &this->LOVPressO2,
                                         &EventNodeMaintPressO2);

    /*%C Noeud Pression O2 */
    GetNodeAt(NodeMaintPressO2_1)->Init (FALSE,
                                         FALSE,
                                         &this->LOVPressO2,
                                         &EventNodeMaintPressO2_1);

    /*%C Noeud Pression O2 */
    GetNodeAt(NodeMaintPressO2_2)->Init (FALSE,
                                         FALSE,
                                         &this->LOVPressO2,
                                         &EventNodeMaintPressO2_2);


    /*%C Noeud Pwm Turbine */
    GetNodeAt(NodeMaintPwmBlower)->Init (FALSE,
                                         FALSE,    
                                         &this->LOVPwmBlower,         
                                         &EventNodeMaintPwmBlower);

    /*%C Noeud Pwm Turbine */
    GetNodeAt(NodeModifMaintPwmBlower)->Init    (FALSE,
                                                 FALSE,    
                                                 &this->LOVPwmBlower,         
                                                 &EventNodeModifMaintPwmBlower);

    /*%C Noeud retour configuration */
    GetNodeAt(NodeMaintBackToConfig)->Init  (FALSE,
                                             FALSE,    
                                             &this->LRConfMaint,
                                             &EventNodeMaintBackToConfig);


    /*%C Premier noeud fantôme des calibrations */
    GetNodeAt(NodeMaintGhostStart)->Init    (FALSE,
                                             FALSE,
                                             &this->GhostObject,
                                             &EventNodeMaintGhostStart);

    /*%C Dernier noeud fantôme des calibrations */
    GetNodeAt(NodeMaintGhostEnd)->Init  (FALSE,
                                         FALSE,
                                         &this->GhostObject,
                                         &EventNodeMaintGhostEnd);


    /*------------------------- Noeud Histo Anomalies ----------------------------*/

    /*%C Noeud retour Maintenance */
    GetNodeAt(NodeHistAnoBackMaint)->Init   (TRUE,
                                             FALSE,    
                                             &this->LRMaintAno,           
                                             &EventNodeHistAnoBackMaint);


    /*------------------------- Noeud Controle des tensions ----------------------*/

    /*%C Noeud Buzzer Voltage */
    GetNodeAt(NodeSupplyBuzVolt)->Init  (TRUE,
                                         FALSE,
                                         &this->LOVBuzzerVoltage,
                                         &EventNodeSupplyBuzVolt);

    /*%C Noeud Back-up Buzzer */
    GetNodeAt(NodeSupplyBackUpBuz)->Init    (FALSE,
                                             FALSE,
                                             &this->LBackupBuzzer,
                                             &EventNodeSupplyBackUpBuz);

    /*%C Noeud Battery Menu */
    GetNodeAt(NodeSupplyBatteryMenu)->Init  (FALSE,
                                             FALSE,
                                             &this->LBatteryMenu,
                                             &EventNodeSupplyBatteryMenu);

    /*%C Noeud Barometric Corrector */
    GetNodeAt(NodeSupplyAltCompens)->Init   (FALSE,
                                             FALSE,
                                             &this->LVSBaroCorrector,
                                             &EventNodeSupplyAltCompens);

    /*%C Noeud Barometric Corrector */
    GetNodeAt(NodeModifSupplyAltCompens)->Init  (FALSE,
                                                 FALSE,
                                                 &this->LVSBaroCorrector,
                                                 &EventNodeModifSupplyAltCompens);

    /*%C Noeud retour Maintenance depuis menu controle des tensions*/
    GetNodeAt(NodeSupplyBackToMaint)->Init  (FALSE,
                                             FALSE,
                                             &this->LRMaintTension,
                                             &EventNodeSupplyBackToMaint);

    /*------------------------- Noeud Graph --------------------------------------*/

    /*%C Noeud Famtôme du menu graphique */
    GetNodeAt(NodeGraphGhost)->Init (FALSE,
                                     FALSE,
                                     &this->GhostObject,
                                     &EventNodeGraphGhost);

    /*----------------------- Noeud Config Graph  --------------------------------*/

    /*%C Noeud Visualisation */
    GetNodeAt(NodeCfgGraphVisu)->Init   (FALSE,
                                         FALSE,
                                         &this->LVSVisu,             
                                         &EventNodeCfgGraphVisu);

    /*%C Noeud Visualisation */
    GetNodeAt(NodeModifCfgGraphVisu)->Init  (FALSE,
                                             FALSE,
                                             &this->LVSVisu,             
                                             &EventNodeModifCfgGraphVisu);

    /*%C Noeud Pression Max */
    GetNodeAt(NodeCfgGraphPMax)->Init   (FALSE,
                                         FALSE,
                                         &this->LOVPMax,             
                                         &EventNodeCfgGraphPMax);

    /*%C Noeud Pression Max */
    GetNodeAt(NodeModifCfgGraphPMax)->Init  (FALSE,
                                             FALSE,
                                             &this->LOVPMax,             
                                             &EventNodeModifCfgGraphPMax);

    /*%C Noeud Débit Max */
    GetNodeAt(NodeCfgGraphQMax)->Init   (FALSE,
                                         FALSE,
                                         &this->LOVQMax,              
                                         &EventNodeCfgGraphQMax);

    /*%C Noeud Débit Max */
    GetNodeAt(NodeModifCfgGraphQMax)->Init  (FALSE,
                                             FALSE,
                                             &this->LOVQMax,             
                                             &EventNodeModifCfgGraphQMax);

    /*%C Noeud Vt MAx */
    GetNodeAt(NodeCfgGraphVtMax)->Init  (FALSE,
                                         FALSE,
                                         &this->LOVVtMax,
                                         &EventNodeCfgGraphVtMax);

    /*%C Noeud Vt MAx */
    GetNodeAt(NodeModifCfgGraphVtMax)->Init (FALSE,
                                             FALSE,
                                             &this->LOVVtMax,            
                                             &EventNodeModifCfgGraphVtMax);

    /*%C Noeud Temps Max */
    GetNodeAt(NodeCfgGraphTMax)->Init   (FALSE,
                                         FALSE,
                                         &this->LOVTMax,             
                                         &EventNodeCfgGraphTMax);

    /*%C Noeud Temps Max */
    GetNodeAt(NodeModifCfgGraphTMax)->Init  (FALSE,
                                             FALSE,
                                             &this->LOVTMax,             
                                             &EventNodeModifCfgGraphTMax);

    /*%C Noeud Représentation */
    GetNodeAt(NodeCfgGraphRepresent)->Init  (TRUE,
                                             FALSE, 
                                             &this->LVSRepresentation,    
                                             &EventNodeCfgGraphRepresent);

    /*%C Noeud Représentation */
    GetNodeAt(NodeModifCfgGraphRepresent)->Init (TRUE,
                                                 FALSE, 
                                                 &this->LVSRepresentation,    
                                                 &EventNodeModifCfgGraphRepresent);

    /*%C Noeud Retour Pref */
    GetNodeAt(NodeCfgGraphBackPref)->Init   (TRUE,
                                             FALSE, 
                                             &this->LRGraphPref,
                                             &EventNodeCfgGraphBackPref);

    /*------------------------ Noeud Menu batterie -------------------------------*/

    /*%C Noeud retour Maintenance depuis menu batterie interne*/
    GetNodeAt(NodeBatteryBackToMaint)->Init (TRUE,
                                             FALSE,
                                             &this->LRMaintBattery,
                                             &EventNodeBatteryBackToMaint);

    /*------------------------ Noeud Menu USB ------------------------------------*/

    GetNodeAt(NodeUsbGhost)->Init   (FALSE,
                                     FALSE,
                                     &this->GhostObject,
                                     &EventNodeUsbGhost);

    GetNodeAt(NodeUsbEraseKey)->Init    (TRUE,
                                         FALSE,
                                         &this->LVSEraseKey,
                                         &EventNodeUsbEraseKey);

    GetNodeAt(NodeModifUsbEraseKey)->Init   (TRUE,
                                             FALSE,
                                             &this->LVSEraseKey,
                                             &EventNodeModifUsbEraseKey);

#ifdef HMI_CONFIG_USB_SETTINGS_TRANSFER
    GetNodeAt(NodeUsbTransferSetOn)->Init   (TRUE,
                                             FALSE,
                                             &this->LVSTransferSetOn,
                                             &EventNodeUsbTransferSetOn);

    GetNodeAt(NodeModifUsbTransferSetOn)->Init  (TRUE,
                                                 FALSE,
                                                 &this->LVSTransferSetOn,
                                                 &EventNodeModifUsbTransferSetOn);

    GetNodeAt(NodeUsbApplySet)->Init    (TRUE,
                                         FALSE,
                                         &this->LVSTransferSetOn,
                                         &EventNodeUsbApplySet);
#endif

    GetNodeAt(NodeUsbContRecord)->Init  (TRUE,
                                         FALSE,
                                         &this->LVSContRecord,
                                         &EventNodeUsbContRecord);

    GetNodeAt(NodeModifUsbContRecord)->Init (TRUE,
                                             FALSE,
                                             &this->LVSContRecord,
                                             &EventNodeModifUsbContRecord);

#ifdef HMI_CONFIG_USB_MONIT_TRANSFER										
    GetNodeAt(NodeUsbTransferMonit)->Init   (TRUE,
                                             FALSE,
                                             &this->LOVFTransfMonit,
                                             &EventNodeUsbTransferMonit);

    GetNodeAt(NodeModifUsbTransferMonit)->Init  (TRUE,
                                                 FALSE,
                                                 &this->LOVFTransfMonit,
                                                 &EventNodeModifUsbTransferMonit);
#endif										

    GetNodeAt(NodeUsbTransferTrend)->Init   (TRUE,
                                             FALSE,
                                             &this->LOVFTransfTrend,
                                             &EventNodeUsbTransferTrend);

    GetNodeAt(NodeModifUsbTransferTrend)->Init  (TRUE,
                                                 FALSE,
                                                 &this->LOVFTransfTrend,
                                                 &EventNodeModifUsbTransferTrend);

#ifdef HMI_CONFIG_USB_EVENTS_TRANSFER
    GetNodeAt(NodeUsbTransferEvents)->Init  (TRUE,
                                             FALSE,
                                             &this->LVSFTransfEvents,
                                             &EventNodeUsbTransferEvents);

    GetNodeAt(NodeModifUsbTransferEvents)->Init (TRUE,
                                                 FALSE,
                                                 &this->LVSFTransfEvents,
                                                 &EventNodeModifUsbTransferEvents);
#endif										

    GetNodeAt(NodeUsbStop)->Init    (TRUE,
                                     FALSE,
                                     &this->LStopUsb,
                                     &EventNodeUsbStop);

    /*------------------------ Noeud Menu Tendance -------------------------------*/

    GetNodeAt(NodeTrendBack)->Init  (TRUE,
                                     FALSE,
                                     &this->LRTendance,
                                     &EventNodeTrendBack);


    /*------------------------- Noeud fantome ------------------------------------*/

    GetNodeAt(NodeGhostEnd)->Init   (FALSE,
                                     FALSE,
                                     &this->GhostObject,
                                     &EventNodeGhostEnd);

}
