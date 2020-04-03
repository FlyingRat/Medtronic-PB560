/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValue.hpp  	     		                        	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/



/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelOneValue.cpp     		               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelOneValueH
#define LabelOneValueH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Label.hpp"
#include "HMI_EditableObject.hpp"
#include "HMI_ValueField.hpp"
#include "HMI_ValueTextField.hpp"
#include "HMI_TextField.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelOneValue: public EditableObject
{

private:

   /* Parametres */

   TextField   FUnit1,
               FSep;
   
   ValueTextField FValue1;
   
   e_BOOL   LabelOnly,
            ValueIsString,
			StopMonitoring;

   UBYTE **NameUnit;

   UWORD16  Divider;

   e_BOOL NbDigitsChanged;
   e_BOOL InitNbDigits;

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

   LabelOneValue();

   void Format();

   virtual void Format(UWORD16 NewValue);

   virtual void SetVisible(e_BOOL V);

   void Init(	e_SYMBOL Icon, 
   				UBYTE **Name,
   				UWORD16 Line,
   				UWORD16 Col,
   				UWORD16 Value, 
   				UBYTE **NameUnit);

   void SetSep(UBYTE *Sep);
   UBYTE* GetSep();

   void SetNbDigitsChanged(e_BOOL _NbDigitsChanged);
   e_BOOL GetNbDigitsChanged();

   void SetInitNbDigits(e_BOOL _Init);
   e_BOOL GetInitNbDigits();

   void SetMaxDisplayValue(UWORD16 _MaxDisplayValue);
   UWORD16 GetMaxDisplayValue();

   void SetUnit1(UBYTE *Unit1);
   UBYTE* GetUnit1();

   virtual void SetValue1(UWORD16 Value1);
   UWORD16 GetValue1();

   virtual UWORD16 GetFullValue();   

   void SetColSep(UWORD16 ColSep);
   UWORD16 GetColSep();

   void SetColValue1(UWORD16 ColValue1);
   UWORD16 GetColValue1();

   void SetColUnit1(UWORD16 ColUnit1);
   UWORD16 GetColUnit1();

   UWORD16 GetEndColValue1();   

   void SetFontValue1(UWORD16 FontValue1);
   UWORD16 GetFontValue1();

   void SetFontUnit1(UWORD16 FontUnit1);
   UWORD16 GetFontUnit1();

   void SetFloatValue1(e_BOOL Float);
   e_BOOL GetFloatValue1();

   void SetNbDigitValue1(UWORD16 NbDigitValue1);
   UWORD16 GetNbDigitValue1();

   void SetDisplayZeroValue1(e_BOOL DisplayZero);
   e_BOOL GetDisplayZeroValue1();

   void SetDivider(UWORD16 _Divider);
   UWORD16 GetDivider();

   void SetNameUnit(UBYTE** NameUnit);
   UBYTE* GetNameUnit();
   
   void SetLabelOnly(e_BOOL LabelOnly);
	e_BOOL IsLabelOnly();
   
   void SetSignValue(e_BOOL SignValue);
   e_BOOL IsSignValue();

   virtual void SetValueIsString(e_BOOL Flag);
   e_BOOL IsValueIsString();

   void SetStopMonitoring(e_BOOL Flag);
   e_BOOL IsStopMonitoring();

   TextField* GetFUnit1();
   TextField* GetFSep();
   ValueTextField* GetFValue1();

   virtual void StopMonitoringMode();
   virtual void StartMonitoringMode();
   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void SetInvertVideo(e_BOOL InvertVideo);
   virtual void Refresh();
   virtual void Show();
   virtual void Hide();
   virtual void HideAll();
   virtual void Blink(e_BOOL Actif);
   virtual void IncreaseValue();
   virtual void DecreaseValue();
	virtual void StartModifMode();
   virtual void RefreshLanguage();

   virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);
   virtual UBYTE* GetStringValue1();

 
};

#endif
