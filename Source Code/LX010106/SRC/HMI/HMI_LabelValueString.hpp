/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelValueString.hpp 		  			   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelValueString.cpp  			  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelValueStringH
#define LabelValueStringH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_EditableObject.hpp"
#include "HMI_TextField.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelValueString : public EditableObject
{
private:

   /* Parametres */

   TextField FValue1;

   TextField FSep;

   UWORD16 IntValue1;

   e_BOOL ColAdjust;
   
   e_BOOL StopMonitoring;

   /* Methodes */
  
protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelValueString();

   void SetSep(UBYTE *Sep);
   UBYTE* GetSep();

   void SetValue1(UBYTE* Value1);
   UBYTE* GetValue1();

   void SetIntValue1(UWORD16 IntValue1);
   UWORD16 GetIntValue1();

   virtual UWORD16 GetFullValue();   

   virtual UBYTE* GetValue1Name();
   void SetColSep(UWORD16 ColSep);
   UWORD16 GetColSep();
   virtual UWORD16 GetEndCol();   

   void SetColValue1(UWORD16 ColValue1);
   UWORD16 GetColValue1();

   void SetColAdjust(e_BOOL _Adjust);
   e_BOOL GetColAdjust();

   void SetFontValue1(UWORD16 FontValue1);
   UWORD16 GetFontValue1();

   virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);

   TextField* GetFSep();
   TextField* GetFValue1();

   void SetStopMonitoring(e_BOOL Flag);
   e_BOOL IsStopMonitoring();

   /* virtual */
   virtual void StopMonitoringMode();
   virtual void StartMonitoringMode();
   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void SetInvertVideo(e_BOOL InvertVideo);
   virtual void Refresh();
   virtual void Show();
   virtual void Hide();
   virtual void Blink(e_BOOL Actif);
   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void StartModifMode();
   virtual void RefreshLanguage();
   virtual void SetVisible(e_BOOL V);
};

#endif
