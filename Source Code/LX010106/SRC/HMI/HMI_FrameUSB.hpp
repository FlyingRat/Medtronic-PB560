/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameUSB.hpp	  	                             	  				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_FrameUSB.cpp                       				*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef FrameUSBH
#define FrameUSBH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"
#include "HMI_LabelValueString.hpp"
#include "HMI_LabelSerial.hpp"
#include "HMI_LabelOneValue.hpp"
#include "HMI_LabelTwoValue.hpp"
#include "HMI_LabelTwoValueCentered.hpp"
#include "HMI_ShiftingDots.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
#define WHITH_USBBOX 304
#define LINE_UBSBOX 168
#define COL_USBBOX 8
#define HEIGH_USBBOX 53

class FrameUSB: public VFrame

{

private:

   /* Parametres */

	Label LUsb;

	LabelSerial LVSSerieNumber;

	MessageDialog Message;

   UBYTE MessageString[60];

//   LabelTwoValue LOVRemainingTime;
   LabelTwoValueCentered LOVRemainingTime;

   Label LWait;

 	DisplayObject *RefreshTable[5];
   
#ifdef HMI_CONFIG_USB_PROCESSING
   ShiftingDots ProcessingDots;
#endif   

   UBYTE MessageStorage[100];

	/* Methodes */

protected:

   /* Paramettres */

   /* Methodes */

public:
   /* Paramettres */

   /* Methodes */

	FrameUSB();
   
   void init();

   virtual void Show();
   virtual void Hide();
   virtual void RefreshLanguage();

 	virtual DisplayObject** GetRefreshTable();

   void SendInfoUsbKeyDetected(e_BOOL _KeyDetected, UBYTE** _MessageToBeDisplayed);
   e_BOOL ManageErrorCode(UWORD16 _ErrorCode, UBYTE** _MessageToBeDisplayed);
   void GetUsbProcessingMessage(e_BOOL _EraseFlag, UBYTE** _MessageToBeDisplayed);
   MessageDialog* GetMessageDialog();

   void NoUsbMessage(UBYTE** _MessageToBeDisplayed);

   void AnimateProcessingDots(e_BOOL _DisplayFlag);

   void ResetDisplay();

};

#endif

