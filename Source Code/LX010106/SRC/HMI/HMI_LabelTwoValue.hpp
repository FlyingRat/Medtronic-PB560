/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTwoValue.hpp 						   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelTwoValue.cpp  				  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelTwoValueH
#define LabelTwoValueH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelOneValue.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelTwoValue: public LabelOneValue
{

private:
   
	/* Parametres */

   /* Methodes */

   TextField FUnit2;
   
   ValueTextField FValue2;
   
   UBYTE **NameUnit2;
   
   UWORD16  ValueState,
            IdParam2,
            Divider2;
   
   e_TYPE_OF_DB_TARGET DbTarget2;

   e_BOOL ColAdjust;

   e_BOOL MaxDisplayValue2Configured;
   UWORD16 MaxDisplayValue2;

   /* Methodes */
   void SetMaxDisplayValue2Configured(e_BOOL _MaxDisplayValue2Configured);
   e_BOOL IsMaxDisplayValue2Configured();

   void SaturateValue2(UWORD16* _Value);


protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelTwoValue();

   void Init(  e_SYMBOL Icon,
               UBYTE **Name,
               UWORD16 Line,
               UWORD16 Col,
               UWORD16 Value1,
               UBYTE **NameUnit1,
               UWORD16 Value2,
               UBYTE **NameUnit2);

   void InitDbAccess(UWORD16 IdParam,
                     e_TYPE_OF_DB_TARGET DbTarget,
                     UWORD16 IdParam2,
                     e_TYPE_OF_DB_TARGET DbTarget2);

	void SetTextValue2(UBYTE* _TextValue2);

	void SetNameUnit2(UBYTE** NameUnit2);
   UBYTE* GetNameUnit2();

   void SetUnit2(UBYTE *Unit1);
   UBYTE* GetUnit2();
   
   void SetValue2(UWORD16 Value2);
   UWORD16 GetValue2();

   void SetMaxDisplayValue2(UWORD16 _MaxDisplayValue2);
   UWORD16 GetMaxDisplayValue2();

   void SetColValue2(UWORD16 ColValue2);
   UWORD16 GetColValue2();
   
   void SetColUnit2(UWORD16 ColUnit1);
   UWORD16 GetColUnit2();
   
   void SetFontValue2(UWORD16 FontValue2);
   UWORD16 GetFontValue2();
   
   void SetFloatValue2(e_BOOL FloatValue2);
   e_BOOL GetFloatValue2();
   
   void SetNbDigitValue2(UWORD16 NbDigitValue2);
   UWORD16 GetNbDigitValue2();
   
   void SetDisplayZeroValue2(e_BOOL DisplayZero);
   e_BOOL GetDisplayZeroValue2();
   
   virtual void SetValueState(UWORD16 ValueState);
   UWORD16 GetValueState();

	void SetDbTarget2(e_TYPE_OF_DB_TARGET DbTarget2);
   e_TYPE_OF_DB_TARGET GetDbTarget2();
 		 
   void SetIdParam2(UWORD16 IdParam2);
   UWORD16 GetIdParam2();

   void SetDivider2(UWORD16 _Divider2);
   UWORD16 GetDivider2();

   void SetLabelOnly(e_BOOL LabelOnly);
   TextField* GetFUnit2();
   ValueTextField* GetFValue2();

   void SetColAdjust(e_BOOL _Adjust);
   e_BOOL GetColAdjust();

   virtual void StopMonitoringMode();
   virtual void StartMonitoringMode();

   virtual void SetInvertVideo(e_BOOL InvertVideo);
   virtual void Refresh();
   virtual void Show();
   virtual void Hide();
   virtual void HideAll();   
   virtual void Blink(e_BOOL Actif);
   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void StartModifMode();
   virtual void ModifNextValue();
   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void RefreshLanguage();
   virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);
   virtual UBYTE* GetStringValue2();

   void Format2(UWORD16 NewValue);   
   
};

#endif
