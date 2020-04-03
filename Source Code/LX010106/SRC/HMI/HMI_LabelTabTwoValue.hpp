/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabTwoValue.hpp 	   			   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelTabTwoValue.cpp    	  			  	      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelTabTwoValueH
#define LabelTabTwoValueH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Label.hpp"
#include "HMI_ValueField.hpp"
#include "HMI_LabelTabOneValue.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelTabTwoValue: public LabelTabOneValue
{

private:
   
   /* Parametres */
   
   ValueTextField FValue2;
   
   UBYTE **NameUnit;
   
   UWORD16  ValueState,
            IdParam2;

   e_BOOL Value2IsString;
   
   e_TYPE_OF_DB_TARGET DbTarget2;
   
   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelTabTwoValue();

   void Init(  e_SYMBOL Icon,
               UBYTE **Name,
               UWORD16 Line,
               UWORD16 Col,
               UWORD16 Value1,
               UWORD16 ValueRefresh,
               UWORD16 Value2);

   void InitDbAccess(UWORD16 IdParam,
                     e_TYPE_OF_DB_TARGET DbTarget,
                     UWORD16 IdParamMonitor,
                     e_TYPE_OF_DB_TARGET DbTargetMonitor,
                     UWORD16 IdParam2,
                     e_TYPE_OF_DB_TARGET DbTarget2);

   virtual void SetValue2(UWORD16 Value2);
   UWORD16 GetValue2();
  
   void SetColValue2(UWORD16 ColValue2);
   UWORD16 GetColValue2();
  
   void SetFontValue2(UWORD16 FontValue2);
   UWORD16 GetFontValue2();
  
   void SetFloatValue2(e_BOOL Float);
   e_BOOL GetFloatValue2();
  
   void SetNbDigitValue2(UWORD16 NbDigitValue2);
   UWORD16 GetNbDigitValue2();
  
   void SetDisplayZeroValue2(e_BOOL DisplayZero);
   e_BOOL GetDisplayZeroValue2();

   void SetIdParam2(UWORD16 IdParam2);
   UWORD16 GetIdParam2();
  
   void SetDbTarget2(e_TYPE_OF_DB_TARGET DbTarget2);
   e_TYPE_OF_DB_TARGET GetDbTarget2();

   void SetValue2IsString(e_BOOL Flag);
   e_BOOL IsValue2IsString();

   UWORD16 GetValueState();
   void SetValueState(UWORD16 ValueState);

   virtual void SetInvertVideo(e_BOOL InvertVideo);
   ValueTextField* GetFValue2();

   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void Refresh();
   virtual void Show();
   virtual void RefreshValue2();
   virtual void Hide();
   virtual void Blink(e_BOOL Actif);
   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void StartModifMode();
   virtual void ModifNextValue();

   virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);
   virtual UBYTE* GetStringValue2();   

};

#endif
