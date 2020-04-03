/******************************************************************************/
/*                                                                            */
/* Project Number :  RB0505                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameCircuitCheck.cpp    	  		                  	  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C CircuitCheck Window													  */
/*		                                                                      */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  	  */
/******************************************************************************/

#include "HMI_FrameCircuitCheck.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  		  */
/******************************************************************************/

#include "HMI_Message.hpp"

extern "C"
{
#include "DB_Compute.h"
}

/******************************************************************************/
/*                           CONSTRUCTOR/DESTRUCTOR                  		  */
/******************************************************************************/
FrameCircuitCheck::FrameCircuitCheck():VFrame()    
{

}

/******************************************************************************/
/*                           ACCESSORS                                        */
/******************************************************************************/
/******************************************************************************/
//%C                       Functional description                       		
//%C                                                                        
//%C Return the singleton object of this class
//%C
//%I Input Parameter :
//%I	  	NONE
//%IO Input/Output :
//%IO		NONE
//%O Output Parameter :
//%O 		Reference to the singleton object
/******************************************************************************/
FrameCircuitCheck& FrameCircuitCheck::GetInstance()
{
    static FrameCircuitCheck FCircuitCheck;

    return FCircuitCheck;
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameCircuitCheck::init()
{
    UWORD16  _line = 18;
    UWORD16  _spacing = 20;
    UWORD16  _col = 19;
    UWORD16  _colsep = 128;
    UWORD16  _colvalue = 136;

    LCircuitCheck.SetParent         (this);

    LCircuitCheck.Init              (NO,
                                     (UBYTE**)cMSG_CircuitCheck,
                                     _line,
                                     0);

    LCircuitCheck.SetFontLabel      (FONT_4);

    LCircuitCheck.SetCentered       (TRUE);

    _line = 40;
    // "Circuit Leak" test node inserted here by HMI_Controller 

    _line += _spacing;

    // Leak Test End Flow
    LOVLeakTestQi.SetParent           (this);

    LOVLeakTestQi.InitDbAccess        (LEAK_TEST_QI_S16,
                                       COMPUTE);

    LOVLeakTestQi.SetSignValue        (TRUE);

    LOVLeakTestQi.Init                (LOCKS,
                                       (UBYTE**)cMSG_FuiteMon,
                                       _line,
                                       _col,
                                       255,
                                       (UBYTE**)cMSG_FlowUnit);

    LOVLeakTestQi.SetFloatValue1      (TRUE);

    LOVLeakTestQi.SetColSep           (_colsep);

    LOVLeakTestQi.SetColValue1        (_colvalue);

    _line += _spacing;

    // Leak Test Result
    LVSLeakTestResult.SetParent       (this);

    LVSLeakTestResult.InitDbAccess    (LEAK_TEST_RESULT_U16,
                                       COMPUTE);

    LVSLeakTestResult.Init            (LOCKS,
                                       (UBYTE**)cMSG_TestStatus,
                                       _line,
                                       _col);

    LVSLeakTestResult.SetColSep       (_colsep);

    LVSLeakTestResult.SetColValue1    (_colvalue);

    LVSLeakTestResult.SetSize         (7);

    for (int i=0;i<nb_of_test_states;i++)
    {
        LVSLeakTestResult.SetItem(i,(UBYTE**) &cMSG_TestStates[i][0]);
    }

    _line += _spacing;

    _line += _spacing;

    _col   = 2;

    // instructions for use
    LInstrLine1.SetParent         (this);

    LInstrLine1.Init              (NO,
                                   (UBYTE**)cMSG_LeakTestInstr1,
                                   _line,
                                   _col);

    LInstrLine1.SetFontLabel      (FONT_1);

    LInstrLine2.SetParent         (this);

    _line += _spacing;

    LInstrLine2.Init              (NO,
                                   (UBYTE**)cMSG_LeakTestInstr2,
                                   _line,
                                   _col);

    LInstrLine2.SetFontLabel      (FONT_1);

    _line += _spacing;

    LInstrLine3.SetParent         (this);

    LInstrLine3.Init              (NO,
                                   (UBYTE**)cMSG_LeakTestInstr3,
                                   _line,
                                   _col);

    LInstrLine3.SetFontLabel      (FONT_1);

}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Show all contained objects												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameCircuitCheck::Show()
{
    VFrame::Show();
    LCircuitCheck.Show();
    LOVLeakTestQi.Show();
    LVSLeakTestResult.Show();
    LInstrLine1.Show();
    LInstrLine2.Show();
    LInstrLine3.Show();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Change the language for all contained objects  						*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameCircuitCheck::RefreshLanguage()
{
    LCircuitCheck.RefreshLanguage();
    LOVLeakTestQi.RefreshLanguage();
    LVSLeakTestResult.RefreshLanguage();
    LInstrLine1.RefreshLanguage();
    LInstrLine2.RefreshLanguage();
    LInstrLine3.RefreshLanguage();
    LCircuitCheck.SetCentered(LCircuitCheck.GetCentered());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Hide all display objects															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameCircuitCheck::Hide()
{
    LCircuitCheck.Hide();
    LOVLeakTestQi.Hide();
    LVSLeakTestResult.Hide();
    LInstrLine1.Hide();
    LInstrLine2.Hide();
    LInstrLine3.Hide();
    VFrame::Hide();    
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Hide the patient instructions										*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameCircuitCheck::HideInstructions()
{
    LInstrLine1.Hide();
    LInstrLine2.Hide();
    LInstrLine3.Hide();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh the contained objects										*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameCircuitCheck::Refresh()
{
    LOVLeakTestQi.Refresh();
    LVSLeakTestResult.Refresh();
}

