/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameVoltControl.hpp  		  		                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  */
/*%C Classe declaration for HMI_FrameVoltControl.cpp    			          */
/*%C			                                                              */
/******************************************************************************/

#ifndef FrameVoltControlH
#define FrameVoltControlH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"
#include "HMI_LabelOneValue.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class FrameVoltControl : public VFrame

{

private:

   /* Parametres */

   Label LVoltCtrl;

   LabelOneValue LOVAlim24V;
   LabelOneValue LOVWatchDog;
   LabelOneValue LOVAbsPress;
	LabelOneValue LOVIntTemp;
	LabelOneValue LOVTemp;
	LabelOneValue LOVTempBat;
    LabelOneValue LOVBlowTemp;
	SymbolField Bat;

	DisplayObject *RefreshTable[11];

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:
   
   /* Parametres */
   
   /* Methodes */
	
	FrameVoltControl();

   void init();
   void IsBatVisible();
   void SetSupplyBusFailure(e_BOOL Flag, e_BOOL DisplayFlag);   

   virtual void Show();
   virtual void Hide();
   virtual void RefreshLanguage();
   
   virtual DisplayObject** GetRefreshTable();

};

#endif
