/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameCircuitCheck.hpp	   		                    	  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  */
/*%C Classe declaration for HMI_FrameCircuitCheck.cpp    			          */
/*%C			                                                              */
/******************************************************************************/

#ifndef FrameCircuitCheckH
#define FrameCircuitCheckH


/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"
#include "HMI_LabelOneValue.hpp"
#include "HMI_LabelStringNItems.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class FrameCircuitCheck : public VFrame

{
#ifdef _BORLAND
    friend class SettingFile;
    friend class BinarySettingFile;   
#endif

private:

    /* Parametres */

    Label LCircuitCheck;
    LabelOneValue LOVLeakTestQi;
    LabelStringNItems LVSLeakTestResult;
    Label LInstrLine1;
    Label LInstrLine2;
    Label LInstrLine3;

    /* Methodes */

protected:

    /* Parametres */

    /* Methodes */

public:

    /* Parametres */

    /* Methodes */

    FrameCircuitCheck();

    static FrameCircuitCheck& FrameCircuitCheck::GetInstance();

    void init();

    virtual void Hide();
    virtual void HideInstructions();
    virtual void Show();
    virtual void RefreshLanguage();
    virtual void Refresh();

};

#endif
