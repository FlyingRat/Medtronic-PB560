/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameMaintenance.hpp	   		                       	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*   Date        |  Programmer    | Modification                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_FrameMaintenance.cpp    			             	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef FrameMaintenanceH
#define FrameMaintenanceH


/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_LabelVersion.hpp"
#include "HMI_LabelSerial.hpp"
#include "HMI_LabelValueString.hpp"
#include "HMI_LabelOneValue.hpp"
#include "HMI_TextField.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class FrameMaintenance : public VFrame

{
#ifdef _BORLAND
   friend class SettingFile;
   friend class BinarySettingFile;   
#endif

private:

   /* Parametres */

   Label LMaintenance;

   LabelSerial    LVSSerieNumber;

   TextField TFSup;

   LabelVersion   LVSVersionSoft,
                  LVSSupplyVersionSoft;

	LabelOneValue  LOVSpeed;

   DisplayObject     *RefreshTable[5];

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

	FrameMaintenance();

   void SetBlowerSpeedLine(UWORD16 _Line);   

   void init();

   virtual DisplayObject** GetRefreshTable();

   virtual void Hide();
	virtual void Show();
   virtual void RefreshLanguage();

};

#endif
