/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MonitoringObject.hpp 	 	  			 		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_MonitoringObject.cpp 				  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef MonitoringObjectH
#define MonitoringObjectH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_ValueTextField.hpp"
#include "HMI_ValueField.hpp"
#include "HMI_TextField.hpp"
#include "HMI_SymbolField.hpp"

#define FRAME_HEIGHT				43
#define FRAME_WIDTH				52
#define NAME_HEIGHT				10
#define MONITOR_HEIGHT			28
#define UNIT_HEIGHT			   39
#define LEFT_MARGIN_WIDTH		1
#define RIGHT_MARGIN_WIDTH		2

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class MonitoringObject: public DisplayObject
{

private:

	/* Parametres */

	UBYTE **Name;

	UBYTE **Unit;


	UWORD16 DivisionFactorOfValue;

	e_BOOL Trigger;

	e_BOOL ReverseVideo;

	e_BOOL CenteredDisplay;

   e_BOOL IconIsPrefered;   

	e_BOOL ValueReady;

	e_BOOL StopMonitoring;

	e_BOOL TextHeaderOn;

	e_BOOL FloatDisplayOn;

   	e_BOOL MaxDisplayValueConfigured;

   	UWORD16 MaxDisplayValue;

	e_BOOL SignedValue;

	/* Méthodes */

	void SetSignedValue(e_BOOL _signed);
	e_BOOL IsSignedValue();

protected:

	/* Parametres */

   e_SYMBOL Icon, IconInverseVideo;

   SymbolField FIcon;

	SymbolField FTrig;

	TextField TFTitle;

	TextField TFUnit;

	ValueTextField VTFValue;

	/* Méthodes */

   void SetMaxDisplayValueConfigured(e_BOOL _MaxDisplayValueConfigured);

   e_BOOL IsMaxDisplayValueConfigured();

   void SaturateValue(UWORD16* _Value);

public:

	/* Parametres */

   /* Méthodes */

	MonitoringObject();

	void Init(	e_SYMBOL _Icon,
               UWORD16 Line,
					UWORD16 Col, 
					UBYTE **Name, 
					UWORD16 Value, 
					e_BOOL ValueFloat, 
					UBYTE ** Text, 
					e_BOOL TextHeadOn, 
					e_BOOL Centered);

   void SetNameUnit(UBYTE** _Unit);               

   void SetCoord(UWORD16 Line, UWORD16 Col);

   void SetMaxDisplayValue(UWORD16 _MaxDisplayValue);
   UWORD16 GetMaxDisplayValue();

	void ForceRefresh();

    virtual void ShowTrigger();
   void HideTrigger();

	void RefreshObject(e_BOOL Forced);

   virtual void DisplayNoValue();

	void RefreshValueColumn();

	virtual void StopMonitoringMode();
   virtual void StopMonitoringMode(e_BOOL _DisplayFlag);   
	virtual void FreezeMonitoringMode();
	virtual void StartMonitoringMode();
 	virtual void StartMonitoringModeImpactDisplay(e_BOOL _DisplayFlag);
 	virtual void StopMonitoringModeImpactDisplay(e_BOOL _DisplayFlag);   
	virtual void SetInvertVideo(e_BOOL InvertVideo);
	virtual void Refresh();
	virtual void Show();
	virtual void Hide();
	virtual void RefreshLanguage();

	void SetDivisionFactorOfValue(UWORD16 _DivisionFactorOfValue);
	UWORD16 GetDivisionFactorOfValue();

	void SetTrigger(e_BOOL _Trigger);
	e_BOOL GetTrigger();

	void SetReverseVideo(e_BOOL _ReverseVideo);
	e_BOOL GetReverseVideo();

	void SetCenteredDisplay(e_BOOL _CenteredDisplay);
	e_BOOL GetCenteredDisplay();

	void SetValueReady(e_BOOL _ValueReady);
	e_BOOL GetValueReady();

	void SetStopMonitoring(e_BOOL _StopMonitoring);
	e_BOOL GetStopMonitoring();

	void SetTextHeaderOn(e_BOOL _TextHeaderOn);
	e_BOOL GetTextHeaderOn();

	void SetFloatDisplayOn(e_BOOL _FloatDisplayOn);
	e_BOOL GetFloatDisplayOn();

};

#endif
