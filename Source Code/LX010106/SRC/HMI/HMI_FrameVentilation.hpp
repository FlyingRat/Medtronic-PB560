/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameVentilation.hpp	 	  		                       	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_FrameVentilation.cpp    			             	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef FrameVentilationH
#define FrameVentilationH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/
#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"
#include "HMI_LabelOneValue.hpp"
#include "HMI_LabelTwoValueTrig.hpp"
#include "HMI_LabelOneValueTrig.hpp"
#include "HMI_LabelAlarme.hpp"
#include "HMI_BarGraph.hpp"
#include "HMI_GraphicBox.hpp"
#include "HMI_Loupe.hpp"
#include "HMI_MessageDialog.hpp"
#include "HMI_LabelAlarmeTwoLine.hpp"
#include "HMI_MonitoringObject.hpp"
#include "HMI_BatteryObject.hpp"
#include "HMI_Config.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define WHITH_VENTILBOX 123
#define LINE_VENTILBOX 184
#define COL_VENTILBOX 195
#define HEIGH_VENTILBOX 41

#define cVENTIL_FIRST_LINE 33

class FrameVentilation : public VFrame
{
private:

	/* Parametres */

	BarGraph BarVentil;
	SymbolField SFValve;   

	LabelOneValue LOVPip;
	LabelOneValue LOVVti;
	LabelOneValue LOVVte;
	LabelOneValue LOVVm;
	LabelOneValue LOVR;
   LabelOneValue LOVFIO2;
   LabelOneValue LOVSPO2;   
   LabelOneValue LOVFuite;
   LabelTwoValueTrig LTVIE;
   LabelOneValueTrig LOVIT;

	BatteryObject BOBat;

	e_MODE_TYPES Mode;

	e_BOOL 	BatVisible,
			ValveVisible,
			IsInhibApneaAlarm,
			IsInhibAlarm,
			IsCancelAlarm,
			IESelected,
			ValveDetected,
			FiO2Enabled,
			SpO2Enabled,
			ExhalFlowUsed;

	MessageDialog Message;

	LabelAlarmeTwoLine LAlarme;

	GraphicBox MonitorBox,AlarmBox;

	DisplayObject *RefreshTable[16];

	SymbolField InhibAlarm, CancelAlarm, InhibApneaAlarm;

    Label PressConvention;

	/* Methodes */

   void InitInfoVentilTable(void);
   void HideInhibApneaAlarm(void);
   void ShowInhibApneaAlarm(void);

protected:

	/* Parametres */

	/* Methodes */

public:

	/* Parametres */

	/* Methodes */

	FrameVentilation();

	void init();
	void ShowTrigger();
	void HideTrigger();

	virtual void StopMonitoringMode();
	virtual void StartMonitoringMode();
	virtual void StartMonitoringMode(e_BOOL IsFio2Sensor, e_BOOL IsSpO2Sensor);

	virtual DisplayObject** GetRefreshTable();

	virtual void Show();
	virtual void Hide();
	virtual void SetMode(e_MODE_TYPES Mode);

	void SetBatVisible(e_BOOL _BatVisible, e_BOOL _ImpactDisplay);
	e_BOOL IsBatVisible();

	e_BOOL IsValveVisible();

	void ShowBatAndValve(e_BOOL Visible);
    void ShowPressConvention(e_BOOL _Visible);
    void SetPressConvention(e_BOOL _Conv);    
	void DisplayValve();

	void SetInibOk(e_BOOL _InibOk, e_BOOL _ImpactDisplay);
	void ShowInibOk(e_BOOL _Visible);
	void SetInhibApneaOk(e_BOOL _InhibOk);
	void ShowInhibApneaOk(e_BOOL _Visible);
	void SetCancelOk(e_BOOL _CancelOk, e_BOOL _ImpactDisplay);
	void ShowCancelOk(e_BOOL _Visible);
	void SetExhalFlowUsed(e_BOOL _Flag, e_BOOL _ImpactDisplay);
	e_BOOL IsInhibAlarmVisible();
	e_BOOL IsInhibApneaAlarmVisible();   
	e_BOOL IsCancelAlarmVisible();

	virtual void ShowMonitoring();
	virtual void HideMonitoring();

	void ShowMessage(e_BOOL Visible, UBYTE* Message, e_SYMBOL Symbol);

	virtual void RefreshLanguage();

	void ShowCurrentAlarme(e_BOOL Actif, UWORD16 Id);

	void HideCurrentAlarme();

	void RemoveAlarm(UWORD16 _AlarmId);

	void RemoveAllAlarms(void);

	DisplayObject* GetAlarmField();

	void EnableMonitZoneRefresh(e_BOOL Enable);

	void SetIESelected(e_BOOL _IESelected);

	void SetValve(e_BOOL _ValveDetected, e_BOOL _ImpactDisplay);

	void Fio2MonitorEnabled(e_BOOL _Flag);

	void Spo2MonitorEnabled(e_BOOL _Flag);

	void SetPressureUnit(UBYTE** _PressureUnit);

	virtual void ObjectsStartMonitoringMode(void);
};

#endif
