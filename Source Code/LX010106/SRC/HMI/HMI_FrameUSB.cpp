/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameUSB.cpp                              						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Fenetre Menu USB																	      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_FrameUSB.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"
#include "HMI_Message.hpp"
#include "HMI_Config.hpp"

extern "C"
{
#include "stdfile.h"
#include "DB_Usb.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
FrameUSB::FrameUSB():VFrame()
{

}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
MessageDialog* FrameUSB::GetMessageDialog()
{
   return(&Message);
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
void FrameUSB::init()
{
   UWORD16 _Col;

	LUsb.SetParent							(this);

	LUsb.Init								(NO,
												(UBYTE**)cMSG_TitleUSB,
												18,
												0);

	LUsb.SetFontLabel						(FONT_4);

   LUsb.SetCentered                 (TRUE);


	LVSSerieNumber.SetParent			(this);

	LVSSerieNumber.InitDbAccess		(VERSION);

	LVSSerieNumber.Init					(NO,
												(UBYTE**)cMSG_ShortSerial,
												40,
												8);

  	LVSSerieNumber.SetColAdjust		(TRUE);

	LVSSerieNumber.SetColLabel			(0);

	LVSSerieNumber.SetColSep			(0);

	LVSSerieNumber.SetColValue1		(0);


	Message.SetParent						(this);

	Message.Init							(LINE_UBSBOX,
												COL_USBBOX,
												HEIGH_USBBOX,
												WHITH_USBBOX,
												TRUE);
                                    
   Message.SetLineLine1             (14);

	Message.SetColLine1					(100);

	Message.SetWhithBox					(WHITH_USBBOX);

   Message.SetSpaceBetweenLines     (15);

	Message.SetMessage               ((UBYTE*)"",NO);



   /* Temps restant avant la fin de la commande en cours */
   LOVRemainingTime.SetParent		   (this);

   LOVRemainingTime.InitDbAccess		(USB_PROGRESS_HOURS_U16,
   									      USB,
                                    USB_PROGRESS_MINUTES_U16,
   									      USB);
   //_Col = COL_USBBOX+15;
   _Col = 0;
   LOVRemainingTime.Init  		      (NO,
   									      (UBYTE**)cMSG_NoneUnit,
   									      LINE_UBSBOX+48,
   									      _Col,
   									      65535,
					                     (UBYTE**)cMSG_HourUnit,
                                    65535,
                                    (UBYTE**)cMSG_MinuteUnit);

	LOVRemainingTime.SetSep          ((UBYTE*) "");

   _Col = LOVRemainingTime.GetColUnit1();

   LOVRemainingTime.SetColValue2    (_Col + 40);

   LOVRemainingTime.SetColUnit2     (_Col + 60);

	LOVRemainingTime.SetInvertVideo  (TRUE);

   LOVRemainingTime.SetColAdjust    (TRUE);


   LWait.SetParent		   (this);

   LWait.Init  		      (NO,
   								(UBYTE**)cMSG_ShortWait,
                           LINE_UBSBOX+48,
   								0);

   LWait.SetInvertVideo  (TRUE);

   LWait.SetCentered     (TRUE);

#ifdef HMI_CONFIG_USB_PROCESSING
   ProcessingDots.SetParent		   (this);

   ProcessingDots.Init              (FREE_SQUARE,
                                    BLACK_SQUARES,
                                    FALSE,
                                    40,
                                    250);
#endif

   /*%C Table de refresh */

	/*%C Alway */
	RefreshTable[0] = NULL;

	/*%C Insp */
	RefreshTable[1] 	= NULL;

	/*%C Exp */
	RefreshTable[2] 	= NULL;

	/*%C XAlway */
	RefreshTable[3] = &this->LOVRemainingTime;
	RefreshTable[4]	= NULL;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Affichage de l'Objet																	 	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameUSB::Show()
{
   VFrame::Show();
	LUsb.Show();
	LVSSerieNumber.Show();
	Message.Show();
   if(LOVRemainingTime.IsVisible())
   {
      LOVRemainingTime.SetNbDigitsChanged(TRUE);
      LOVRemainingTime.Show();
#ifdef HMI_CONFIG_USB_PROCESSING
      ProcessingDots.Show();
#endif
   }
   if(LWait.IsVisible())
   {
     LWait.Show();
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Animation du processing par pointillés												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	_DisplayFlag : TRUE si les pointillés doivetn etre affichés          */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameUSB::AnimateProcessingDots(e_BOOL _DisplayFlag)
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
	_DisplayFlag = _DisplayFlag;
#ifdef HMI_CONFIG_USB_PROCESSING
   	if(_DisplayFlag)
      	ProcessingDots.Animate();
#endif
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet								 	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameUSB::RefreshLanguage()
{
	LUsb.RefreshLanguage();
  	LUsb.SetCentered(LUsb.GetCentered());
	LVSSerieNumber.RefreshLanguage();
	Message.RefreshLanguage();
  	LOVRemainingTime.RefreshLanguage();
   LWait.RefreshLanguage();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne la table des Objets a rafraichir											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
DisplayObject** FrameUSB::GetRefreshTable()
{
	return RefreshTable;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																	 	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameUSB::Hide()
{
	LUsb.Hide();
	LVSSerieNumber.Hide();
	Message.Hide();
   LOVRemainingTime.Hide();
#ifdef HMI_CONFIG_USB_PROCESSING
   ProcessingDots.Hide();
#endif
   LWait.Hide();
   VFrame::Hide();   
}
/************************************************************************/
/* Description          : Determine la presence ou l'absence de la      */
/*                         clé usb                 	                  */
/* Parametres en entree :     	                                       */
/*		 _KeyDetected : presence de la clé						               */
/*     _MessageToBeDisplayed : Pointeur vers le message à afficher      */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameUSB::SendInfoUsbKeyDetected(e_BOOL _KeyDetected, UBYTE** _MessageToBeDisplayed)
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	_KeyDetected = _KeyDetected;
	
   	*_MessageToBeDisplayed = (UBYTE*)"";
}
/************************************************************************/
/* Description          : Aucun message Usb dans la Dialog Box          */
/* Parametres en entree :     	                                       */
/*     _DisplayFlag : TRUE si l'affichage doit etre impacté             */
/*     _MessageToBeDisplayed : Pointeur vers le message à afficher      */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameUSB::NoUsbMessage(UBYTE** _MessageToBeDisplayed)
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	*_MessageToBeDisplayed = (UBYTE*)"";
}
/************************************************************************/
/* Description          : Opération en cours sur le driver USB          */
/* Parametres en entree :     	                                       */
/*     _EraseFlag : TRUE, opération d'effacement en cours,              */
/*                  FALSE opération de transfert en cours               */
/*     _MessageToBeDisplayed : Pointeur vers le message à afficher      */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameUSB::GetUsbProcessingMessage(e_BOOL _EraseFlag,
                                       UBYTE** _MessageToBeDisplayed)
{
   if(_EraseFlag)
      *_MessageToBeDisplayed = (UBYTE*)cMSG_UsbErrEraseProcessing[GetLanguage()];
   else
      *_MessageToBeDisplayed = (UBYTE*)cMSG_UsbErrTransfProcessing[GetLanguage()];

	/* Quick and Dirty solution : USB driver should reset these values on the
	   following conditions :
	    - when a USB command is stopped manually
		- or when the USB command has ended (error or not)
		As it can't do for architectural reasons, it is done here */
	UWORD16 Val = 0;
	DataBaseAccess::WriteValue(&Val,USB_PROGRESS_HOURS_U16,USB);
	DataBaseAccess::WriteValue(&Val,USB_PROGRESS_MINUTES_U16,USB);

   LOVRemainingTime.SetNbDigitsChanged(TRUE);
   LOVRemainingTime.Show();
#ifdef HMI_CONFIG_USB_PROCESSING
   ProcessingDots.Show();
#endif   
}
/************************************************************************/
/* Description          : Gestion du code d'erreur renvoyé par le driver*/
/* Parametres en entree :     	                                       */
/*       _ErrorCode : code d'erreur à traiter                           */
/*       _MessageToBeDisplayed : Pointeur vers le message à afficher    */
/* Parametres en sortie : 											               */
/*       TRUE si le code d'erreur traité doit engendrer un lock du menu */
/*       FALSE sinon                                                    */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
e_BOOL FrameUSB::ManageErrorCode(UWORD16 _ErrorCode, UBYTE** _MessageToBeDisplayed)
{
   e_BOOL _Lock = FALSE;

   UWORD16 Value = TRUE;
   DataBaseAccess::WriteValue(&Value, END_OF_OPERATION_U16 , CONTROL);

   switch(_ErrorCode)
   {
		case E_USB_READY_ACCESS :
				*_MessageToBeDisplayed = (UBYTE*)"";
		break;

      case E_USB_OK:
      case E_USB_ONE_KEY_CONNECTED:
      case E_USB_COMMAND_STOPPED:
            *_MessageToBeDisplayed = (UBYTE*)cMSG_Wait[GetLanguage()];
				_Lock = TRUE;
      break;	  

      case E_USB_NOERROR_COMPATIBLE_M2XL2S2 :
         sprintf( (char*)MessageStorage,
                  "%s %s",
                  (char*) cMSG_VentilCompatible[GetLanguage()],
				  "PB640, PB560, PB520");
		 *_MessageToBeDisplayed = MessageStorage;
			_Lock = TRUE;
	  break;

	  case E_USB_NOERROR_COMPATIBLE_M2XL2 :
		 sprintf( (char*)MessageStorage,
				  "%s %s",
				  (char*) cMSG_VentilCompatible[GetLanguage()],
				  "PB640, PB560");
         *_MessageToBeDisplayed = MessageStorage;
			_Lock = TRUE;
      break;

      case E_USB_NOERROR_COMPATIBLE_XL2 :
         sprintf( (char*)MessageStorage,
                  "%s %s",
                  (char*) cMSG_VentilCompatible[GetLanguage()],
                  "PB560");
         *_MessageToBeDisplayed = MessageStorage;
			_Lock = TRUE;
      break;

      case E_USB_NOERROR_COMPATIBLE_S2 :
         sprintf( (char*)MessageStorage,
                  "%s %s",
                  (char*) cMSG_VentilCompatible[GetLanguage()],
                  "PB520");
         *_MessageToBeDisplayed = MessageStorage;
			_Lock = TRUE;
      break;

      case E_USB_CREATE_FAILED:
      case E_USB_FILE_OPEN_FAILED:
      case E_USB_FILE_CLOSE_FAILED:
      case E_USB_FILE_WRITE_FAILED:
      case E_USB_FILE_READ_FAILED:
      case E_USB_FILE_SYSTEM_FAILED:
      case E_USB_EXPLORE_FAILED:
            *_MessageToBeDisplayed = (UBYTE*)cMSG_UsbErrTransfer[GetLanguage()];
				_Lock = TRUE;
      break;

      case E_USB_INCOMPATIBLE_SETTINGS:
            *_MessageToBeDisplayed = (UBYTE*)cMSG_UsbErrPortability[GetLanguage()];
				_Lock = TRUE;
      break;
		/*On ne vérouille pas la page pour laisser la possibilité d'effacer la clé */
      case E_USB_NO_FREE_SPACE:
            *_MessageToBeDisplayed = (UBYTE*)cMSG_UsbErrFullKey[GetLanguage()];
      break;

      case E_USB_ENTIRE_ERASE_FAILED:
            *_MessageToBeDisplayed = (UBYTE*)cMSG_UsbErrErase[GetLanguage()];
				_Lock = TRUE;
      break;

      case E_USB_TOO_MANY_KEY_CONNECTED:
            *_MessageToBeDisplayed = (UBYTE*)cMSG_UsbErrTooManyKeys[GetLanguage()];
            _Lock = TRUE;
      break;

      case E_USB_SETTING_FILE_NOT_FOUND:
      case E_USB_SETTING_FILE_CORRUPTED:
            *_MessageToBeDisplayed = (UBYTE*)cMSG_UsbErrFile[GetLanguage()];
			_Lock = TRUE;
      break;

      case E_USB_NOERROR_SETTINGS_OVERWRITE :
            *_MessageToBeDisplayed = (UBYTE*)cMSG_SettingsOverWrite[GetLanguage()];      
			_Lock = TRUE;
      break;

		case E_USB_DISCONNECTION_KEY_DURING_OPERATION:
			*_MessageToBeDisplayed = (UBYTE*)cMSG_UsbErrDisconnect[GetLanguage()];      
			_Lock = TRUE;
		break ;
		case E_USB_NOT_ENOUGH_KEY_SPACE :
			 *_MessageToBeDisplayed = (UBYTE*)cMSG_NotEnoughKeySpace[GetLanguage()];      
		break ;
		case E_USB_KEY_DISCONNECTED :
              *_MessageToBeDisplayed = NULL;
			  _Lock = TRUE;
		break;					

      default:
              *_MessageToBeDisplayed = (UBYTE*)"UNKNOWN ERROR CODE";
			  _Lock = TRUE;
      break;
   }
   LOVRemainingTime.Hide();
#ifdef HMI_CONFIG_USB_PROCESSING
   ProcessingDots.Hide();
#endif

   if(_Lock == TRUE)
   {
      if(   (_ErrorCode == E_USB_NOERROR_COMPATIBLE_M2XL2S2) ||
            (_ErrorCode == E_USB_NOERROR_COMPATIBLE_M2XL2) ||
            (_ErrorCode == E_USB_NOERROR_COMPATIBLE_XL2) ||
            (_ErrorCode == E_USB_NOERROR_COMPATIBLE_S2)  )
      {
             LWait.Show();
      }
   }
   else
   {
      LWait.Hide();
   }

   return(_Lock);
}
/************************************************************************/
/* Description          : Resete l'affichage de la frame USB            */
/* Parametres en entree : Néant	                                       */
/* Parametres en sortie : Néant  								               */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameUSB::ResetDisplay()
{
   LWait.Hide();
   LOVRemainingTime.Hide();
#ifdef HMI_CONFIG_USB_PROCESSING
   ProcessingDots.Hide();
#endif
}
