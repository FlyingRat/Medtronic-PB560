/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameAlarme.hpp	     		                        	  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  */
/*%C Classe declaration for HMI_FrameAlarme.cpp	    	                      */
/*%C			                                                              */
/******************************************************************************/

#ifndef FrameAlarmeH
#define FrameAlarmeH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"
#include "HMI_LabelOneValue.hpp"
#include "HMI_LabelTwoValueTrig.hpp"
#include "HMI_LabelOneValueTrig.hpp"
#include "HMI_LabelAlarmeTwoLine.hpp"
#include "HMI_BarGraph.hpp"
#include "HMI_LoupeAlarm.hpp"
#include "HMI_Loupe.hpp"
#include "HMI_MessageDialog.hpp"
#include "HMI_GraphicBox.hpp"
#include "HMI_GraphicTable.hpp"
#include "HMI_TextField.hpp"
#include "HMI_BatteryObject.hpp"
#include "HMI_Config.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define WHITH_ALARMEBOX 111
#define LINE_ALARMEBOX 149
#define COL_ALARMEBOX 207
#define HEIGH_ALARMEBOX 66

#define cALARM_FIRST_LINE 32

typedef enum {
   ALARM_EUR_FORMAT = 0,
   ALARM_US_FORMAT
} e_ALARM_DATE_FORMAT;

typedef enum {
   ALARM_24H_FORMAT = 0,
   ALARM_12H_FORMAT
} e_ALARM_TIME_FORMAT;


class FrameAlarme : public VFrame

{

private:

	/* Parametres */


	BatteryObject BOBat;
	SymbolField SFValve;   

	GraphicBox 	MonitorBox;
	GraphicBox	AlarmBox;
	
	LabelAlarmeTwoLine LAlarme;
   
   TextField LastAlarmDate;
	
	GraphicTable GTable;

	LabelOneValue LOVPip;

   LabelOneValue LOVMap;
	
	LabelOneValue LOVVti;
	
	LabelOneValue LOVPeep;

	LabelOneValue LOVR;

	LabelOneValue LOVM;

   LabelOneValueTrig LOVIT;

	LabelTwoValueTrig LTVIE;
	
	e_MODE_TYPES Mode;

	e_BOOL 	BatVisible,
            ValveVisible,
            IsInhibApneaAlarm,
				IsInhibAlarm,
				IsCancelAlarm,
            IESelected,
            ValveDetected,
            FiO2Enabled,
            SpO2Enabled;            

	e_BOOL MutexAlarm;

	MessageDialog Message;

	DisplayObject *RefreshTable[13];

	SymbolField InhibAlarm, CancelAlarm, InhibApneaAlarm;

   e_ALARM_DATE_FORMAT AlarmDateFormat;

   e_ALARM_TIME_FORMAT AlarmTimeFormat;

	/* Methodes */
   
   void InitInfoAlarmTable(void);

   void SetDateFormat(e_ALARM_DATE_FORMAT _format);
   e_ALARM_DATE_FORMAT GetDateFormat(void);
   
   void SetTimeFormat(e_ALARM_TIME_FORMAT _format);
   e_ALARM_TIME_FORMAT GetTimeFormat(void);

   void HideInhibApneaAlarm(void);
   void ShowInhibApneaAlarm(void);



protected:

	/* Parametres */

	/* Methodes */

public:
	
	/* Parametres */

	/* Methodes */
	
	FrameAlarme();
	
	void init();
	
	void ShowTrigger();
	void HideTrigger();
	void EnableMonitZoneRefresh(e_BOOL Enable);
	void ShowBatAndValve(e_BOOL Visible);
   void DisplayValve();   
   void SetTableSize(UBYTE LineNb);
   void SetBoldLineOfTable(UWORD16 Line);
   void ClearBoldLinesOfTable(void);      
   void DisplayTable(void);
   void ShowTable(void);
   void HideTable(void);
   UWORD16 GetSpacingOfTable(void);
   UWORD16 GetFirstLineOfTable(void);
   UWORD16 GetPatientColOfTable(void);
   UWORD16 GetPatientWidthOfTable();
	void ShowCurrentAlarme(e_BOOL Actif, UWORD16 Id);
   void HideCurrentAlarme();
   void RemoveAlarm(UWORD16 _AlarmId);
   void RemoveAllAlarms(void);     
	void ShowLastAlarme(AlarmEvent* Alarm);
	void ShowMessage(e_BOOL Visible, UBYTE* Message, e_SYMBOL Symbol);
   void SetInibOk(e_BOOL _InibOk, e_BOOL _ImpactDisplay);
	void ShowInibOk(e_BOOL _Visible);
   void SetInhibApneaOk(e_BOOL _InhibOk);
   void ShowInhibApneaOk(e_BOOL _Visible);
	void SetCancelOk(e_BOOL _CancelOk, e_BOOL _ImpactDisplay);
	void ShowCancelOk(e_BOOL _Visible);
	e_BOOL IsInhibAlarmVisible();
   e_BOOL IsInhibApneaAlarmVisible();   
	e_BOOL IsCancelAlarmVisible();

	virtual void Show();
	virtual void Hide();
	virtual void StopMonitoringMode();
	virtual void StartMonitoringMode();
   virtual void StartMonitoringMode(e_BOOL IsFio2Sensor, e_BOOL IsSpO2Sensor);   
	virtual void ShowMonitoring();
	virtual void HideMonitoring();
	virtual void RefreshLanguage();

	
	virtual void SetMode(e_MODE_TYPES Mode);
	
	virtual DisplayObject** GetRefreshTable();
	
	void SetBatVisible(e_BOOL BatVisible, e_BOOL _ImpactDisplay);
	e_BOOL IsBatVisible();

   e_BOOL IsValveVisible();

	DisplayObject* GetAlarmField();

   void SetIESelected(e_BOOL _IESelected);

   void SetValve(e_BOOL _ValveDetected, e_BOOL _ImpactDisplay);

   void Fio2MonitorEnabled(e_BOOL _Flag);

   void Spo2MonitorEnabled(e_BOOL _Flag);      

   void SetPressureUnit(UBYTE** _PressureUnit);
   virtual void ObjectsStartMonitoringMode(void);
};

#endif
