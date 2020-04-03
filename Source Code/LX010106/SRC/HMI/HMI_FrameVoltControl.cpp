/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameVoltControl.cpp    	  		                  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Fenetre Controle des tensions													      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_FrameVoltControl.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Message.hpp"
#include "HMI_DataBaseAccess.hpp"

extern "C"
{
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_PowerSupply.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
FrameVoltControl::FrameVoltControl():VFrame()
{

}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/

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
void FrameVoltControl::init()
{
   UWORD16  _line,
            _spacing,
            _colsep,
            _colvalue;

   _line = 45;
   _spacing = 21;
   _colsep = 165;
   _colvalue = 173;


	LVoltCtrl.SetParent			(this);

	LVoltCtrl.Init					(NO,
										(UBYTE**)cMSG_MenuVoltControl,
										18,
										0);

	LVoltCtrl.SetFontLabel		(FONT_4);

   LVoltCtrl.SetCentered(TRUE);

   /* 24V Check */
	LOVAlim24V.SetParent			(this);

	LOVAlim24V.InitDbAccess		(MEASURE_SUPPLY_24V_U16,
										COMPUTE);

	LOVAlim24V.Init				(LOCKS,
					               (UBYTE**)cMSG_SupplyTest,
					               _line,
					               8,
					               242,
               				   (UBYTE**)cMSG_TensionUnit);

	LOVAlim24V.SetFloatValue1	(TRUE);

	LOVAlim24V.SetColSep			(_colsep);

	LOVAlim24V.SetColValue1		(_colvalue);

   _line += _spacing;

   /* Watchdog */
	LOVWatchDog.SetParent		(this);

	LOVWatchDog.InitDbAccess	(MEASURE_PFI_VOLTAGE_U16,
										COMPUTE);

	LOVWatchDog.Init				(LOCKS,
										(UBYTE**)cMSG_WatchdogTest,
										_line,
										8,
										252,
										(UBYTE**)cMSG_TensionUnit);

	LOVWatchDog.SetFloatValue1	(TRUE);

	LOVWatchDog.SetColSep		(_colsep);

	LOVWatchDog.SetColValue1	(_colvalue);

   _line += _spacing;

   /* Pression absolue */
	LOVAbsPress.SetParent		(this);

	LOVAbsPress.InitDbAccess	(MEAS_ABS_PRESS_MMHG_U16,
										COMPUTE);

	LOVAbsPress.Init				(LOCKS,
										(UBYTE**)cMSG_AbsPress,
										_line,
										8,
										252,
										(UBYTE**)cMSG_AbsPressUnit);

	LOVAbsPress.SetFloatValue1 (TRUE);                              

	LOVAbsPress.SetColSep		(_colsep);

	LOVAbsPress.SetColValue1	(_colvalue);

   _line += _spacing;

   /* Temperature interne */
	LOVIntTemp.SetParent		   (this);

	LOVIntTemp.InitDbAccess	   (AMBIENT_TEMP_S16,
										POWER_SUPPLY);

	LOVIntTemp.Init				(LOCKS,
										(UBYTE**)cMSG_Temperature,
										_line,
										8,
										252,
										(UBYTE**)cMSG_TempUnit);

	LOVIntTemp.SetFloatValue1	(TRUE);

    LOVIntTemp.SetMaxDisplayValue      (999);

	LOVIntTemp.SetColSep		   (_colsep);

	LOVIntTemp.SetColValue1	   (_colvalue);

 	LOVIntTemp.SetSignValue	   (TRUE);

   _line += _spacing;

    /* Temperature Blower */
	LOVBlowTemp.SetParent		(this);

	LOVBlowTemp.InitDbAccess	(MEASURE_BLOWER_TEMPERATURE_S16,
										COMPUTE);

	LOVBlowTemp.Init				(LOCKS,
										(UBYTE**)cMSG_BlowerTemperature,
										_line,
										8,
										252,
										(UBYTE**)cMSG_TempUnit);

	LOVBlowTemp.SetColSep		(_colsep);

	LOVBlowTemp.SetColValue1	(_colvalue);

	LOVBlowTemp.SetSignValue	   (TRUE);

	LOVBlowTemp.SetFloatValue1	(TRUE);

	LOVBlowTemp.SetMaxDisplayValue(999);
   

	Bat.SetParent					(this);

	Bat.Init							(43,
										230,
										FONT_1,
										FALSE,
										BAT);


	/*%C Table de refresh */

	/*%C Alway */
	RefreshTable[0] = NULL;
	
	/*%C Insp */
	RefreshTable[1] = NULL;
	
	/*%C Exp */
	RefreshTable[2] = NULL;
	
	/*%C XAlway */
	RefreshTable[3] = &this->LOVAlim24V;
	RefreshTable[4] = &this->LOVWatchDog;
	RefreshTable[5] = &this->LOVAbsPress;
	RefreshTable[6] = &this->LOVIntTemp;
	RefreshTable[7] = &this->LOVWatchDog;
	RefreshTable[8] = &this->LOVTemp;
	RefreshTable[9] = &this->LOVBlowTemp;
	RefreshTable[10] = NULL;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne la table des Objets a rafraichir											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Objets a rafraichir																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
DisplayObject** FrameVoltControl::GetRefreshTable()
{
	return RefreshTable;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVoltControl::Show()
{
	VFrame::Show();
	LVoltCtrl.Show();
	LOVAlim24V.Show();
	LOVWatchDog.Show();
    LOVAbsPress.Show();
	LOVIntTemp.Show();
    LOVBlowTemp.Show();
	LOVTemp.Show();

	IsBatVisible();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVoltControl::RefreshLanguage()
{
	LVoltCtrl.RefreshLanguage();
    LVoltCtrl.SetCentered(LVoltCtrl.GetCentered());
	LOVAlim24V.RefreshLanguage();
	LOVWatchDog.RefreshLanguage();
	LOVAbsPress.RefreshLanguage();
	LOVIntTemp.RefreshLanguage();
  	LOVTemp.RefreshLanguage();
    LOVBlowTemp.RefreshLanguage();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVoltControl::Hide()
{
	LVoltCtrl.Hide();
	LOVAlim24V.Hide();
	LOVWatchDog.Hide();
	LOVAbsPress.Hide();
  	LOVIntTemp.Hide();
    LOVBlowTemp.Hide();
	VFrame::Hide();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage de la battery																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVoltControl::IsBatVisible()
{
	UWORD16 Value;
	DataBaseAccess::ReadValue(&Value, DISPLAY_BATTERY_U16, CONTROL);

	if (this->IsVisible())
   {
      if(Value)
      {
		   Bat.Show();
	   }
	   else
      {
	      Bat.Hide();
	   }
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Démarrage (affichage valeur) ou arret (affichage tiret) sur pb com carte */
/*%C alimentation                                                             */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Flag : TRUE si pb de communication avec la carte alim                */
/*%I	  	DisplayFlag : TRUE si répercuter sur affichage                       */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameVoltControl::SetSupplyBusFailure(e_BOOL Flag, e_BOOL DisplayFlag)
{
   e_BOOL _IsVisible = LOVIntTemp.IsVisible();

   if(!DisplayFlag)
      LOVIntTemp.SetVisible(FALSE);
   else
      LOVIntTemp.SetVisible(TRUE);

   if(Flag)
      LOVIntTemp.StopMonitoringMode();
   else
      LOVIntTemp.StartMonitoringMode();

   LOVIntTemp.SetVisible(_IsVisible);
}
