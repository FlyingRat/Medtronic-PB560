/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_BatteryObject.hpp	   	                             	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_GraphTitle.cpp  	      	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef BatteryObjectH
#define BatteryObjectH


/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_TextField.hpp"
#include "HMI_LabelTwoValue.hpp"
#include "HMI_SymbolField.hpp"
#include "HMI_LabelOneValue.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class BatteryObject: public DisplayObject
{

private:

	/* Parametres */
   LabelOneValue  LOVPercent;

   LabelTwoValue  LTVJauge;

   SymbolField SFEqual;

   e_BOOL   JaugeAvailable,
            BusFailure,
            UnknownBattery,
            CheckSupply,
            CheckBattery,
            ForcedDisplay;

   UWORD16 CurrentDisplay;            

   /* Méthodes */

protected:

	/* Parametres */

   /* Methodes */

public:

	/* Parametres */

   /* Methodes */

	BatteryObject();

	void Init(  UWORD16 Line, 
					UWORD16 Col);

  	void SetJaugeAvailable(e_BOOL _JaugeAvailable);
   e_BOOL GetJaugeAvailable();

  	void SetBusFailure(e_BOOL _BusFailure);
   e_BOOL GetBusFailure();

   e_BOOL GetForcedDisplay();
   void SetForcedDisplay(e_BOOL _ForceDisplay);

   virtual void Refresh();
	virtual void Show();
	virtual void Hide();
	virtual void RefreshLanguage();

};

#endif
