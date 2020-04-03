/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Setup1.cpp                                      			  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Classe de gestion de l'application		 f							      */
/*		                                                                      */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                   	  */
/******************************************************************************/


#include "HMI_Setup1.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  		  */
/******************************************************************************/

#include "HMI_Config.hpp"
#include "HMI_GlobalEventNode.hpp"
#include "HMI_Tools.hpp"
#include "HMI_Message.hpp"
#include "HMI_DataBaseAccess.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "HMI_MonitoringObject.hpp"
#include "HMI_DisplayObject.hpp"
#include "DB_KeyboardEvent.h"
#include "DRV_VarEeprom.h"
#include "System_Datas.h"
#include "define.h"

#include "HMI_Controller_Data.hpp"

#ifdef _BORLAND
    #include "Proto_Config.hpp"
    #include "EventRecorder.hpp"
#endif

extern "C"
{
#include "stdfile.h"
#include "DB_Usb.h"
#include "DB_IhmAccessParaDataBase.h"
}


/******************************************************************************/
/*                        VARIABLE DECLARATION		                	   	  */
/******************************************************************************/

bool HMI_Setup1::FirstCall = true;

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                		  */
/******************************************************************************/
HMI_Setup1::HMI_Setup1()
{

    FirstCall = true;
}

/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C                                                                          */
/*%C Initailization of the Frame Configuration								  */
/*%C                                                                          */
/*%I Input Parameter : 														  */
/*%I	  	NONE															  */
/*%IO Input/Output : 														  */
/*%IO		NONE														 	  */
/*%O Output Parameter : 													  */
/*%O 		NONE  							  								  */
/******************************************************************************/
void HMI_Setup1::Init()
{
    FConfiguration1.SetPage(VIRTUAL_PAGE);
    FConfiguration1.init();
    FConfiguration1.SetLabel((UBYTE**)cMSG_Configuration2);
}


/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C                                                                          */
/*%C Initailize all label strings objects for the Frame.   				      */
/*%C                                                                          */
/*%I Input Parameter : 														  */
/*%I	  	NONE															  */
/*%IO Input/Output : 														  */
/*%IO		NONE														 	  */
/*%O Output Parameter : 													  */
/*%O 		NONE  							  								  */
/******************************************************************************/
void HMI_Setup1::InitConfiguration()
{

    UWORD16 _line =35;
    UWORD16 _spacing = 18;
    UWORD16 _colsep = 139;
    UWORD16 _colvalue = 146;

/*----------------------- Configuration/Setup 2 Window -----------------------*/

    /* Mode Cyclage */
    /* Cycling Mode setting (I:E I/T) */
    _line += _spacing;

    LVSModeCycl.SetParent            (&this->FConfiguration1);
    LVSModeCycl.InitDbAccess         (ADJUST_CYCLING_MODE_U16, CONFIG);
    LVSModeCycl.Init                 (FREE_SQUARE,
                                      (UBYTE**)cMSG_ModeCycle,
                                      _line,
                                      8);
    LVSModeCycl.SetColSep            (_colsep);
    LVSModeCycl.SetColValue1         (_colvalue);
    LVSModeCycl.SetItem1Name         ((UBYTE**)cMSG_ITRation);
    LVSModeCycl.SetItem2Name         ((UBYTE**)cMSG_IERation);

    /* Convention Pression (absolute/relative) */
    /* Relative Pressure Setting (OFF/YES) */
    _line += _spacing;

    LVSRelativePressure.SetParent            (&this->FConfiguration1);
    LVSRelativePressure.InitDbAccess         (PRESSURE_SUPPORT_RELATIVE_U16, CONFIG);
    LVSRelativePressure.Init                 (FREE_SQUARE,
                                              (UBYTE**)cMSG_RelativePressure,
                                              _line,
                                              8);

    LVSRelativePressure.SetColSep            (_colsep);
    LVSRelativePressure.SetColValue1         (_colvalue);
    LVSRelativePressure.SetItem1Name         ((UBYTE**)cMSG_Off);
    LVSRelativePressure.SetItem2Name         ((UBYTE**)cMSG_Yes);

    /* Convention Trigger E (positif ou négatif) */
    _line += _spacing;
    LVSConvTrigE.SetParent               (&this->FConfiguration1);
    LVSConvTrigE.InitDbAccess           (TRIGG_E_POSITIVE,
                                         CONFIG);
    LVSConvTrigE.Init                       (FREE_SQUARE,
                                             (UBYTE**)cMSG_TriggerEConv,
                                             _line,
                                             8);

    LVSConvTrigE.SetColSep               (_colsep);
    LVSConvTrigE.SetColValue1           (_colvalue);
    LVSConvTrigE.SetItem1Name         ((UBYTE**)cMSG_Positive);
    LVSConvTrigE.SetItem2Name         ((UBYTE**)cMSG_Negative);

    // Back key
    _line += _spacing;
    LVSBack.SetParent               (&this->FConfiguration1);
    LVSBack.Init                        (FREE_SQUARE, 
                                         (UBYTE**)cMSG_Back,
                                         _line, 
                                         8);
}



/******************************************************************************/
/*%C                       Functionnal description :                          */
/*%C                                                                          */
/*%C Retourne une instance unique du controller								  */
/*%C                                                                          */
/*%I Input Parameter : 														  */
/*%I 		NONE															  */
/*%IO Input/Output : 													   	  */
/*%IO		NONE															  */
/*%O Output Parameter : 													  */
/*%O 		NONE												  			  */
/******************************************************************************/
HMI_Setup1& HMI_Setup1::GetInstance()
{

    static HMI_Setup1 Control;

    return Control;

}
