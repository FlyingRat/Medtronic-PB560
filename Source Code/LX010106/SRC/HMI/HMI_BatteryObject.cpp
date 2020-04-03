/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_BatteryObject.cpp	                                 	 	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(text + white background)								      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_BatteryObject.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DisplayObject.hpp"
#include "HMI_DataBaseAccess.hpp"
#include "HMI_Message.hpp"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_PowerSupply.h"
#include "DB_AlarmStatus.h"

/* local defines */
#define CURRENT_DISPLAY_PERCENT 0
#define CURRENT_DISPLAY_GAUGE 1
#define CURRENT_DISPLAY_NEUTRAL 2
/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
BatteryObject::BatteryObject():DisplayObject()
{

   JaugeAvailable = FALSE;

   BusFailure = FALSE;

   UnknownBattery = FALSE;

   CheckSupply = FALSE;

   CheckBattery = FALSE;

	LOVPercent.SetParent	      (this);

	LOVPercent.InitDbAccess		(PER_CENT_BAT_U16,
										POWER_SUPPLY);

	LOVPercent.Init				(BAT,
										NULL,
					               18,
					               160,
					               60,
					               (UBYTE**)cMSG_PerCentUnit);

	LOVPercent.SetColValue1		(16);

	LOVPercent.SetFontValue1	(FONT_1);

	LOVPercent.SetSep				((UBYTE *)"");

	LOVPercent.SetMaxDisplayValue(100);


	LTVJauge.SetParent         (this);

   LTVJauge.InitDbAccess      (JAUGE_HOUR_DISPLAY_U16,
                              POWER_SUPPLY,
                              JAUGE_MINUTE_DISPLAY_U16,
                              POWER_SUPPLY);

   LTVJauge.Init              (BAT,
                              NULL,
                              18,
                              160,
                              1,
                              (UBYTE**)cMSG_HourUnit,
                              15,
                              (UBYTE**)cMSG_NoneUnit);

   LTVJauge.SetColValue1      (25);

   LTVJauge.SetColValue2      (48);

   LTVJauge.SetSep            ((UBYTE*)"");

   LTVJauge.SetFontValue1     (FONT_1);

   LTVJauge.SetFontValue2     (FONT_1);

   LTVJauge.SetNbDigitValue1  (2);

   LTVJauge.SetDisplayZeroValue1(TRUE);

   LTVJauge.SetNbDigitValue2  (2);

   LTVJauge.SetDisplayZeroValue2(TRUE);


	SFEqual.SetParent	         (this);

	SFEqual.Init					(0,
										15,
										0,
										FALSE,
										EQUAL);
                              
   SetForcedDisplay            (TRUE);

   CurrentDisplay = CURRENT_DISPLAY_NEUTRAL;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void BatteryObject::SetForcedDisplay(e_BOOL _ForceDisplay)
{
   this->ForcedDisplay = _ForceDisplay;
}
/*----------------------------------------------------------------------------*/
e_BOOL BatteryObject::GetForcedDisplay()
{
   return(this->ForcedDisplay);
}
/*----------------------------------------------------------------------------*/
void BatteryObject::SetJaugeAvailable(e_BOOL _JaugeAvailable)
{
	JaugeAvailable = _JaugeAvailable;
}
/*----------------------------------------------------------------------------*/
e_BOOL BatteryObject::GetJaugeAvailable()
{
	return JaugeAvailable;
}
/*----------------------------------------------------------------------------*/
void BatteryObject::SetBusFailure(e_BOOL _BusFailure)
{
	BusFailure = _BusFailure;
}
/*----------------------------------------------------------------------------*/
e_BOOL BatteryObject::GetBusFailure()
{
	return BusFailure;
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
/*%I		Icon : icone												               		*/
/*%I		Name : Pointeur sur le tableau de nom						         		*/
/*%I		Line : ligne 												               		*/
/*%I		Col : colonne												            			*/
/*%I		Value1 : Valeur 1											               		*/
/*%I		ValueRefresh : Valeur pour le champ de refresh								*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BatteryObject::Init(  UWORD16 _Line,
                        UWORD16 _Col)
{
	DisplayObject::Init(_Line, _Col);

	LOVPercent.Init				(BAT,
										NULL,
					               _Line,
					               _Col,
					               60,
					               (UBYTE**)cMSG_PerCentUnit);

   LTVJauge.Init              (BAT,
                              NULL,
                              _Line,
                              _Col,
                              1,
                              (UBYTE**)cMSG_HourUnit,
                              15,
                              (UBYTE**)cMSG_NoneUnit);

}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'état du paramètre VT														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BatteryObject::Refresh()
{
   e_BOOL   _JaugeAvailable,
            _BusFailure,
            _UnknownBattery,
            _CheckSupply,
            _CheckBattery;

   UWORD16 _Val;

   /*%C Get values first */
	DataBaseAccess::ReadValue(&_Val,JAUGE_AVALAIBLE_U16,POWER_SUPPLY);
   _JaugeAvailable = (e_BOOL)_Val;

	DataBaseAccess::ReadValue(&_Val,SUPPLY_BUS_FAILURE_U16,CONTROL);
   _BusFailure = (e_BOOL)_Val;

	DataBaseAccess::ReadValue(&_Val,UNKNOWN_BATTERY_U16,POWER_SUPPLY);
   _UnknownBattery = (e_BOOL)_Val;

	DataBaseAccess::ReadValue(&_Val,ALARM_CHECK_SUPPLY_U16,ALARMS);
   _CheckSupply = _Val == ALARM_FALSE ? FALSE : TRUE;

	DataBaseAccess::ReadValue(&_Val,ALARM_CHECK_BATTERY_U16,ALARMS);
   _CheckBattery = _Val == ALARM_FALSE ? FALSE : TRUE;


   if((_BusFailure) ||
      (_UnknownBattery) ||
      (_CheckSupply) ||
      (_CheckBattery) )
   {
      if((_BusFailure != BusFailure) ||
         (_UnknownBattery != UnknownBattery) ||
         (_CheckSupply != CheckSupply) ||
         (_CheckBattery != CheckBattery) ||
         GetForcedDisplay() ||
         (CurrentDisplay != CURRENT_DISPLAY_NEUTRAL))
         {
            LTVJauge.Hide();
            SFEqual.Hide();
	         LOVPercent.Show();
	         LOVPercent.StopMonitoringMode();
            CurrentDisplay = CURRENT_DISPLAY_NEUTRAL;
         }
   }
   else if(_JaugeAvailable)
   {
	   if((JaugeAvailable != _JaugeAvailable) ||
         GetForcedDisplay() ||
         (CurrentDisplay != CURRENT_DISPLAY_GAUGE))
      {
	      LOVPercent.Hide();
	      LTVJauge.Show();
         SFEqual.Show();
         CurrentDisplay = CURRENT_DISPLAY_GAUGE;
      }
      LTVJauge.Refresh();
   }
   else
   {
      if( GetForcedDisplay() ||
         (CurrentDisplay != CURRENT_DISPLAY_PERCENT))
      {
	      LTVJauge.Hide();
         SFEqual.Hide();
	      LOVPercent.StartMonitoringMode();
	      LOVPercent.Show();
         CurrentDisplay = CURRENT_DISPLAY_PERCENT;
      }
	   LOVPercent.Refresh();
   }

   /*C% Storage old value */
   JaugeAvailable = _JaugeAvailable;
   BusFailure = _BusFailure;
   UnknownBattery = _UnknownBattery;
   CheckSupply = _CheckSupply;
   CheckBattery = _CheckBattery;
   SetForcedDisplay(FALSE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BatteryObject::Show()
{
   DisplayObject::Show();
   SetForcedDisplay(TRUE); /* Flag will be reset in Refresh() method */
   Refresh();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BatteryObject::Hide()
{
   LOVPercent.Hide();
   LTVJauge.Hide();
   SFEqual.Hide();
   DisplayObject::Hide();   
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Opperation de changement de la langue de l'Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BatteryObject::RefreshLanguage()
{
   LOVPercent.RefreshLanguage();
   LTVJauge.RefreshLanguage();
}
