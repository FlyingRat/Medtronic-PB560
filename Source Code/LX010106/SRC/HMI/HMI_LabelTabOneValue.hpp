/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabOneValue.hpp 	     			   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelTabOneValue.cpp    	  				      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelTabOneValueH
#define LabelTabOneValueH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Label.hpp"
#include "HMI_EditableObject.hpp"
#include "HMI_ValueTextField.hpp"
#include "HMI_ValueField.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define FIRST_VALUE_COLUMN		   73
#define SECOND_VALUE_COLUMN		114
#define THIRD_VALUE_COLUMN		   161
#define COLUMN_WIDTH			      40

class LabelTabOneValue: public EditableObject
{

private:
   
   /* Parametres */

   TextField	TFNoValue;
   
   ValueTextField FValue1,
                  FValueRefresh;

   UWORD16  ValueTemp,
            IdParamMonitor,
            Divider;

   e_BOOL   Value1IsString,
            StopMonitoring,
            Value1IsMaxi;

   e_TYPE_OF_DB_TARGET DbTargetMonitor;
   
   e_BOOL MaxDisplayValueConfigured;
   UWORD16 MaxDisplayValue;

   /* Methodes */
   void SetMaxDisplayValueConfigured(e_BOOL _MaxDisplayValueConfigured);
   e_BOOL IsMaxDisplayValueConfigured();

   void SaturateValue(UWORD16* _Value);


protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */
 
   LabelTabOneValue();

   void Init(  e_SYMBOL Icon,
               UBYTE **Name,
               UWORD16 Line,
               UWORD16 Col,
               UWORD16 Value1,
               UWORD16 ValueRefresh);

   void InitDbAccess(UWORD16 IdParam,
                     e_TYPE_OF_DB_TARGET DbTarget,
                     UWORD16 IdParamMonitor,
					 e_TYPE_OF_DB_TARGET DbTargetMonitor);

   void SetMaxDisplayValue(UWORD16 _MaxDisplayValue);
   UWORD16 GetMaxDisplayValue();

   virtual void SetValue1(UWORD16 Value1);
   UWORD16 GetValue1();
   
   void SetValueRefresh(UWORD16 ValueRefresh);
   UWORD16 GetValueRefresh();
   
   void SetColValue1(UWORD16 ColValue1);
   UWORD16 GetColValue1();
   
   void SetFontValue1(UWORD16 FontValue1);
   UWORD16 GetFontValue1();
   
   void SetFloatValue1(e_BOOL Float);
   e_BOOL GetFloatValue1();
   
   void SetNbDigitValue1(UWORD16 NbDigitValue1);
   UWORD16 GetNbDigitValue1();
   
   void SetDisplayZeroValue1(e_BOOL DisplayZero);
   e_BOOL GetDisplayZeroValue1();

   void SetValue1Maxi(e_BOOL Maxi);
   e_BOOL IsValue1Maxi();
   
   void SetFloatValueRefresh(e_BOOL Float);
   e_BOOL GetFloatValueRefresh();

   void SetValue1IsString(e_BOOL Flag);
   e_BOOL IsValue1IsString();
   
   void SetStopMonitoring(e_BOOL Flag);
   e_BOOL IsStopMonitoring();

   void SetIdParamMonitor(UWORD16 IdParamMonitor);
   UWORD16 GetIdParamMonitor();
   
   void SetDbTargetMonitor(e_TYPE_OF_DB_TARGET DbTargetMonitor);
   e_TYPE_OF_DB_TARGET GetDbTargetMonitor();

   void SetValueState(UWORD16 ValueState);
   UWORD16 GetValueState();

   void SetDivider(UWORD16 _Divider);
   UWORD16 GetDivider();

   ValueTextField* GetFValue1();
   ValueTextField* GetFValueRefresh();

   void ForceRefresh();
   void StopAllMonitoringMode();
   void StartAllMonitoringMode();   
   virtual void StopMonitoringMode();
   virtual void StartMonitoringMode();
   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void SetInvertVideo(e_BOOL InvertVideo);
   virtual void Refresh();
   virtual void RefreshValue1();
   virtual void Show();
   virtual void Hide();
   virtual void Blink(e_BOOL Actif);
   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void StartModifMode();

   virtual e_BOOL IncreaseValueOk(UWORD16* _Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* _Val);
   virtual UBYTE* GetStringValue1();   

};

#endif
