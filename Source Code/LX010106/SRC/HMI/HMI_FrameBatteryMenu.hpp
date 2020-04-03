/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameBatteryMenu.hpp  		  		                       	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_FrameBatteryMenu.cpp    			             	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef FrameBatteryMenuH
#define FrameBatteryMenuH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_VDate.hpp"
#include "HMI_VTime.hpp"
#include "HMI_Label.hpp"
#include "HMI_LabelOneValue.hpp"
#include "HMI_LabelStringTwoItems.hpp"
#include "HMI_LabelStringNItems.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class FrameBatteryMenu : public VFrame

{

private:

   /* Parametres */

   Label LInternalBatteryMenu;

   LabelOneValue 	LOVBatteryVoltage,
					LOVBatteryTemperature,
					LOVCyclesDone,
               LOVTheoreticalCapacity,
                  	LOVAgeing,
                     LOVUnknownBat;
   Label    LNoBat;                     

   LabelStringNItems   LVSSupplier;                         

   VDate VDDate;
   VTime VTTime;

   e_BOOL ForcedStoppedMonitoring;

   DisplayObject *RefreshTable[6];

	/* Methodes */
   void SetForcedStoppedMonitoring(e_BOOL _forced);
   e_BOOL GetForcedStoppedMonitoring();

protected:

   /* Parametres */

   /* Methodes */
    void UnsetRefreshTable(); 
   	void SetRefreshTable();

public:
   
   /* Parametres */
   
   /* Methodes */
	
	FrameBatteryMenu();
   void BadSupplyCheck(e_BOOL _Flag);
   void SetSupplyBusFailure(e_BOOL Flag, e_BOOL DisplayFlag);    

   void init();
   virtual void Show();
   virtual void Hide();
   virtual void RefreshLanguage();
   
   virtual DisplayObject** GetRefreshTable();

};

#endif
