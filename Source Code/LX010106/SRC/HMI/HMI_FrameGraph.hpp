/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameGraph.hpp	  	      		                       	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  */
/*%C Classe declaration for HMI_FrameGraph.cpp          			          */
/*%C			                                                              */
/******************************************************************************/

#ifndef FrameGraphH
#define FrameGraphH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"
#include "HMI_LabelOneValue.hpp"
#include "HMI_SymbolField.hpp"
#include "HMI_MonitoringObject.hpp"
#include "HMI_MonitoringObjectWithRecall.hpp"
#include "HMI_MonitoringObjectTwoValue.hpp"
#include "HMI_GraphTitle.hpp"
#include "HMI_Graph.hpp"
#include "HMI_Scale.hpp"
#include "HMI_PerformanceGraphControl.hpp"
#include "HMI_WobGraphControl.hpp"
#include "HMI_BatteryObject.hpp"
#include "HMI_Config.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define REFRESH_OBJ_NB  23
#define MONIT_OBJ_NB	   11

#define cGRAPH_FIRST_LINE 196
#define cGRAPH_FIRST_COL 1
#define cGRAPH_MAX_MODE  (nb_of_mode)


typedef struct
{
   CurveData* Curv;
   Scale* ScaleX;
   Scale* ScaleY;
   UWORD16 IdParamY;
   e_TYPE_OF_DB_TARGET IdDbY;
   e_BOOL Dotted;
}  tCurvInfo;

class FrameGraph : public VFrame

{

private:

	/* Parametres */

	BatteryObject BOBat;
	SymbolField SFValve;   

	SymbolField SFPause;

  	Label LGraph;

	GraphTitle GTMode;

	Graph GSmallFlow;
	Graph GSmallPressure;
	Graph GSmallFlowV;
	Graph GSmallPressureV;


	PerformanceGraphControl PGCSmallFlow;
	PerformanceGraphControl PGCSmallPressure;

	CurveData CDFlow;
	CurveData CDPressure;
	CurveData CDFlowV;
	CurveData CDPressureV;

	WobGraphControl WGCSmallFlowV;
	WobGraphControl WGCSmallPressureV;

  	MonitoringObject MoSpO2;
  	MonitoringObject MoFiO2;
  	MonitoringObject MoRate;
	MonitoringObjectTwoValue MoTVIE;
	MonitoringObject MoIT;
	MonitoringObject MoVmi;   
	MonitoringObject MoFuite;
	MonitoringObject MoVti;
	MonitoringObject MoVte;
	MonitoringObject MoPe;
   MonitoringObject MoPip;
   MonitoringObject MoPulse;
   MonitoringObject MoTi;
   MonitoringObject MoTe;

	e_MODE_TYPES Mode;
  	e_MODE_TYPES PreviousMode;

   e_BOOL ModeChange;   

   e_BOOL   TriggerOn,
            Freezed,
            IESelected,
            ValveDetected,
            FiO2Enabled,
			SpO2Enabled,
			ExhalFlowUsed;

   e_BOOL BlocExpiDetected;            

   e_BOOL FirstInitOk;            

	DisplayObject* RefreshTable[REFRESH_OBJ_NB];

	SymbolField InhibAlarm, CancelAlarm, InhibApneaAlarm;

  	/* Methodes */

   e_BOOL GetModeChange();
   void SetModeChange(e_BOOL _ModeChange);   

   e_MODE_TYPES GetPreviousMode();
   void SetPreviousMode(e_MODE_TYPES _PreviousMode);

   void InitInfoGraphTable(void);

   void GraphReInit(e_BOOL _PositiveCurves, e_BOOL _DisplayFlag);

   void GraphRefresh();

   void HideInhibApneaAlarm(void);
   void ShowInhibApneaAlarm(void);   

protected:

	/* Parametres */

	/* Methodes */

public:

	/* Paramettres */

	/* Methodes */

	FrameGraph();
	void init();
	virtual void SetMode(e_MODE_TYPES Mode);
   void ShowTrigger();
   void HideTrigger();
  	void FreezeMonitoring(e_BOOL Freeze, e_BOOL _DisplayFlag);
   void RefreshMode();
	void IsBatVisible();
   void IsInibAlarmVisible();
   void IsCancelAlarmVisible();
   void IsInhibApneaAlarmVisible();   

   virtual void StopMonitoringMode();
	virtual void StartMonitoringMode();
	virtual void StartMonitoringModeImpactDisp(  e_BOOL IsFio2Sensor,
                                                   e_BOOL IsSpO2Sensor,
                                                   e_BOOL _DisplayFlag);   
 	virtual void Show();
	virtual void Hide();
	virtual void RefreshLanguage();

	virtual DisplayObject** GetRefreshTable();

   void SetIESelected(e_BOOL _IESelected);

   void SetValve(e_BOOL _ValveDetected, e_BOOL _DisplayFlag);

   void SetBlocExpi(e_BOOL _BlocExpiDetected, e_BOOL _DisplayFlag);
   e_BOOL IsBlocExpiDetected();

   void Fio2MonitorEnabled(e_BOOL _Flag, e_BOOL _DisplayFlag);

   void Spo2MonitorEnabled(e_BOOL _Flag, e_BOOL _DisplayFlag);

   void SetPressureUnit(UBYTE** _PressureUnit);

   void SetNameMode2Display(e_BOOL _NameMode2Display);

   void ObjectsFreezeMonitoringMode(void);

   virtual void RebuildFrameTree(e_MODE_TYPES Mode);
   virtual void ObjectsHide(e_MODE_TYPES _Mode);
   virtual void ObjectsHide(e_MODE_TYPES _Mode, e_OBJECT _ObjectId);
   void ObjectsStartMonitoringModeImpactDisplay(e_BOOL _DisplayFlag);
   void SetExhalFlowUsed(e_BOOL _Flag, e_BOOL _ImpactDisplay);
};

#endif
