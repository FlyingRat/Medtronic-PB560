/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameWelcome.hpp  			  		                       	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  						   */
/*%C Classe declaration for HMI_FrameWelcome.cpp    				               */
/*%C			                                                                  */
/******************************************************************************/

#ifndef FrameWelcomeH
#define FrameWelcomeH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"
#include "HMI_LabelVersion.hpp"
#include "HMI_LabelOneValue.hpp"
#include "HMI_LabelTwoValue.hpp"
#include "HMI_SymbolField.hpp"
#include "HMI_VDate.hpp"
#include "HMI_VTime.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class FrameWelcome : public VFrame

{

private:

	/* Parametres */
	
	Label LWelcome;
	Label LCopyRight;   

	VDate Date1;

	VTime Time1;
	
	SymbolField SFLogo, SFLogo2, SFLogo3;

	SymbolField SFCompanyName;
	
	LabelOneValue LOVMachine;
	
   LabelTwoValue LTVPatient;

	LabelVersion LVSVersion, LVSSupplyVersionSoft;
	
	DisplayObject *RefreshTable[6];

	/* Methodes */

protected:

	/* Parametres */

	/* Methodes */

public:

	/* Parametres */

	/* Methodes */

	FrameWelcome();

	void init();

	virtual void Show();
	virtual void Hide();
	virtual void RefreshLanguage();

	virtual DisplayObject** GetRefreshTable();

};

#endif
