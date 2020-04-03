/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Setup1.hpp		                                      	  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  */
/*%C Classe declaration for HMI_Setup1.cpp		                              */
/*%C                                                                          */
/******************************************************************************/

#ifndef HMI_Setup1H
#define HMI_Setup1H

/******************************************************************************/
/*                           	INCLUDE                    	      			  */
/******************************************************************************/

#include "HMI_Label.hpp"
#include "HMI_LabelOneValue.hpp"
#include "HMI_LabelOneValueSign.hpp"
#include "HMI_LabelOneValueDbRT.hpp"
#include "HMI_LabelOneValueSignFlag.hpp"
#include "HMI_LabelOneValueDefault.hpp"
#include "HMI_LabelOneValueThreeDefault.hpp"
#include "HMI_LabelOneValueFourDefault.hpp"
#include "HMI_LabelOneValueFlag.hpp"
#include "HMI_LabelOneValueFiO2Flag.hpp"
#include "HMI_LabelOneValueTrig.hpp"
#include "HMI_LabelProgressBar.hpp"
#include "HMI_LabelTwoValueLock.hpp"
#include "HMI_LabelTabOneValue.hpp"
#include "HMI_LabelTabOneValueFlag.hpp"
#include "HMI_LabelTabTwoValue.hpp"
#include "HMI_LabelTabTwoValueTwoLabels.hpp"
#include "HMI_LabelRatio.hpp"
#include "HMI_LabelRatioTrunk.hpp"
#include "HMI_LabelTabTwoValueFlag.hpp"
#include "HMI_LabelValueString.hpp"
#include "HMI_LabelStringTwoItems.hpp"
#include "HMI_LabelTwoStringsTwoItems.hpp"
#include "HMI_LabelStringNItems.hpp"
#include "HMI_LabelLanguage.hpp"
#include "HMI_LabelMode.hpp"
#include "HMI_Rampe.hpp"
#include "HMI_RiseTime.hpp"

#include "HMI_AutoCalibValue.hpp"
#include "HMI_ManualCalibValue.hpp"
#include "HMI_ManualCalibTwoValue.hpp"
#include "HMI_VDate.hpp"
#include "HMI_VTime.hpp"
#include "typedef.h"
#include "HMI_IhmType.hpp"
#include "HMI_BlinkTable.hpp"
#include "HMI_RefreshTable.hpp"
#include "HMI_ParameterSpy.hpp"
#include "HMI_VTimer.hpp"

#include "HMI_Loupe.hpp"
#include "HMI_AlarmTable.hpp"
#include "HMI_AlarmManager.hpp"

#include "HMI_FrameWelcome.hpp"
#include "HMI_FrameConfiguration.hpp"
#include "HMI_FramePreference.hpp"
#include "HMI_FrameMaintenance.hpp"
#include "HMI_FrameHistoAno.hpp"
#include "HMI_FrameVoltControl.hpp"
#include "HMI_FrameVentilation.hpp"
#include "HMI_FrameAlarme.hpp"
#include "HMI_FrameHistoAlarme.hpp"
#include "HMI_FrameGraph.hpp"
#include "HMI_FrameGraphConfig.hpp"
#include "HMI_FrameBatteryMenu.hpp"
#include "HMI_FrameUSB.hpp"
#include "HMI_FrameTendance.hpp"
#include "HMI_MessageDelayed.hpp"
#include "HMI_MessageDialog.hpp"

extern "C"
{
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_Current.h"
#include "DB_Usb.h"
}


/******************************************************************************/
/*                           	DEFINES                    	      			  */
/******************************************************************************/
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class MenuControlNode;

class HMI_Setup1
{

#ifdef _BORLAND
    friend class SettingFile;
    friend class BinarySettingFile;
    friend class TForm1;      
#endif

private:

    /* Parametres */
    static bool FirstCall;
    /* Methodes */

protected:

    /* Parametres */

    /* Methodes */

public:

    /* Parametres */

    /* Configuration/Setup 2 window */
    FrameConfiguration      FConfiguration1;
    LabelStringTwoItems     LVSModeCycl,
    LVSConvTrigE,
    LVSRelativePressure;
    Label                   LVSBack;

    /* Methodes */
    HMI_Setup1();
    void Init();
    void InitConfiguration();
    static HMI_Setup1& GetInstance();

};


#endif
