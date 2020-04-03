/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameBatteryMenu.cpp    	  		                  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Fenetre menu batterie       													      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_FrameBatteryMenu.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Message.hpp"
#include "HMI_DataBaseAccess.hpp"

extern "C"
{
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_Rtc.h"
#include "DB_PowerSupply.h"
}

#define AGEING_LOW_LIMIT    50
#define AGEING_HIGH_LIMIT    110
/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
FrameBatteryMenu::FrameBatteryMenu():VFrame()
{
   SetForcedStoppedMonitoring(FALSE);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void FrameBatteryMenu::SetForcedStoppedMonitoring(e_BOOL _forced)
{
   ForcedStoppedMonitoring = _forced;
}
/*----------------------------------------------------------------------------*/
e_BOOL FrameBatteryMenu::GetForcedStoppedMonitoring()
{
   return(ForcedStoppedMonitoring);
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
void FrameBatteryMenu::init()
{

   	UWORD16 _ColSep, _ColValue, _Line, _Spacing;

   	_ColSep = 135;
   	_ColValue = 140;
   
	LInternalBatteryMenu.SetParent				(this);

	LInternalBatteryMenu.Init					(NO,
										        (UBYTE**)cMSG_InternalBatteryMenu,
                                          		18,
										        0);

	LInternalBatteryMenu.SetFontLabel			(FONT_4);

   LInternalBatteryMenu.SetCentered(TRUE);

   	_Line = 38;
   	_Spacing = 21;
	
   	LVSSupplier.SetParent        				(this);

	LVSSupplier.InitDbAccess     				(SUPPLIER_U16, POWER_SUPPLY);

   	LVSSupplier.Init             				(LOCKS,
                                				(UBYTE**)cMSG_BatSupplier,
                                				_Line,
                               					 8);

   	LVSSupplier.SetColSep        				(_ColSep);

   	LVSSupplier.SetColValue1     				(_ColValue);

   	LVSSupplier.SetSize          				(3);

    // show approved if Totex, Accutronics, and Saft batteries are used otherwise unknown
    // Totex batteries will show up with Accutronic batteries IDs.
   	LVSSupplier.SetItem          				(0,(UBYTE**)cMSG_BatSupplierUnknown);
   	LVSSupplier.SetItem          				(1,(UBYTE**)cMSG_BatSupplier3);
   	LVSSupplier.SetItem          				(2,(UBYTE**)cMSG_BatSupplier3);


   	/*%C Pas de Batterie */
   LNoBat.SetParent			(this);

	LNoBat.Init					                  (NO,
                                             (UBYTE**)cMSG_NoBat,
					                           	_Line,
					                           	8);

	LNoBat.SetFontLabel							(FONT_4);

   LNoBat.SetCentered               (TRUE);


   _Line += _Spacing;

   	/*%C Première date d'utilisation */
	VDDate.SetParent							(this);

	VDDate.InitDbAccess							(FIRST_DATE_MONTH_U16,
												POWER_SUPPLY,
												FIRST_DATE_DAY_U16,
												FIRST_DATE_YEAR_U16,
												NO_ID,
												NO_ID,
												NO_ID,
												POWER_SUPPLY);

	VDDate.Init									(LOCKS,
												(UBYTE**)cMSG_FirstUseDate,
												_Line,
												8);

	VDDate.SetColSep							(_ColSep);

	VDDate.SetColDate							(_ColValue);

	VDDate.SetFontDate							(FONT_4);

	VDDate.SetNameMonth							((UBYTE**)cMSG_Month);


  	LOVUnknownBat.SetParent						(this);

	LOVUnknownBat.InitDbAccess			(NO_ID,
												POWER_SUPPLY);

	LOVUnknownBat.Init					(LOCKS,
					                     (UBYTE**)cMSG_NoneUnit,
					                           	_Line,
					                           	8,
					                           	242,
               				               		(UBYTE**)cMSG_NoneUnit);

	LOVUnknownBat.SetColSep			   (_ColSep);

	LOVUnknownBat.SetColValue1			(_ColValue);


   	/* Première heure d'utilisation */
   	_Line += _Spacing;

	VTTime.SetParent							(this);

	VTTime.InitDbAccess							(FIRST_DATE_HOUR_U16,
												POWER_SUPPLY,
                                    			FIRST_DATE_MINUTE_U16,
												FIRST_DATE_SECOND_U16,
												NO_ID,
												NO_ID,
												NO_ID);

	VTTime.Init									(NO,
												(UBYTE**)cMSG_NoneUnit,
												_Line,
												8);

	VTTime.SetSep((UBYTE *)"");

	VTTime.SetColSep							(_ColSep);

	VTTime.SetColHours							(_ColValue);

   _Line += _Spacing;

   	/*%C Theoretical  Capacity */
	LOVTheoreticalCapacity.SetParent			(this);

	LOVTheoreticalCapacity.InitDbAccess			(CAPACITY_THEORICAL_U16,
												POWER_SUPPLY);

	LOVTheoreticalCapacity.Init					(LOCKS,
					                           	(UBYTE**)cMSG_BatTheoreticalCapacity,
					                           	_Line,
					                           	8,
					                           	242,
               				               		(UBYTE**)cMSG_PowerUnit);

	LOVTheoreticalCapacity.SetColSep			(_ColSep);

	LOVTheoreticalCapacity.SetColValue1			(_ColValue);


   _Line += _Spacing;
      
   	/* Battery Capacity Therocical * AGEING	*/

   	LOVAgeing.SetParent			      			(this);

	LOVAgeing.InitDbAccess		      			(CAPACITY_U16,
												POWER_SUPPLY);

	LOVAgeing.Init				         		(LOCKS,
					                     		(UBYTE**)cMSG_BatAgeing,
					                     		_Line,
					                     		8,
					                     		242,
               				         			(UBYTE**)cMSG_PowerUnit);

	LOVAgeing.SetColSep			      			(_ColSep);

	LOVAgeing.SetColValue1		      			(_ColValue);

   	_Line += _Spacing;

	/*%C Cycles effectués */
	LOVCyclesDone.SetParent			      		(this);

	LOVCyclesDone.InitDbAccess		      		(BAT_CYCLES_U16,
												POWER_SUPPLY);

	LOVCyclesDone.Init				      		(LOCKS,
					                        	(UBYTE**)cMSG_CyclesDone,
					                        	_Line,
					                        	8,
					                        	242,
												(UBYTE**)cMSG_NoneUnit);

	LOVCyclesDone.SetColSep			      		(_ColSep);

	LOVCyclesDone.SetColValue1		      		(_ColValue);

  	LOVCyclesDone.SetDivider		      		(100);

   	_Line += _Spacing;

	/*%C Tension batterie */
	LOVBatteryVoltage.SetParent					(this);

	LOVBatteryVoltage.InitDbAccess				(V_BAT_U16,
												POWER_SUPPLY);

	LOVBatteryVoltage.Init				   		(LOCKS,
					                        	(UBYTE**)cMSG_BatteryVoltage,
					                        	_Line,
					                        	8,
					                        	242,
               				            		(UBYTE**)cMSG_TensionUnit);

	LOVBatteryVoltage.SetFloatValue1	   		(TRUE);

	LOVBatteryVoltage.SetColSep					(_ColSep);

	LOVBatteryVoltage.SetColValue1				(_ColValue);

   	LOVBatteryVoltage.SetDivider		   		(10);

   	_Line += _Spacing;

	/*%C Température batterie */
	LOVBatteryTemperature.SetParent				(this);

	LOVBatteryTemperature.InitDbAccess			(TEMP_BAT_S16,
												POWER_SUPPLY);

	LOVBatteryTemperature.Init				   	(LOCKS,
					                           	(UBYTE**)cMSG_BatteryTemperature,
												_Line,
					                           	8,
					                           	242,
               				               		(UBYTE**)cMSG_TempUnit);

	LOVBatteryTemperature.SetFloatValue1		(TRUE);

	LOVBatteryTemperature.SetColSep				(_ColSep);

	LOVBatteryTemperature.SetColValue1			(_ColValue);
   
    LOVBatteryTemperature.SetMaxDisplayValue             (999); 

    LOVBatteryTemperature.SetSignValue	      (TRUE);

   _Line += _Spacing;

	
	/*%C Table de refresh */
	SetRefreshTable();
}
/******************************************************************************/
/*%C                       Functional description :                           */
/*%C                                                                          */
/*%C Installation de la table de refresh     								  */
/*%C                                                                          */
/*%I Input Parameter : 														  */
/*%I	  	NONE															  */
/*%IO Input/Output : 														  */
/*%IO		NONE															  */
/*%O Output Parameter : 													  */
/*%O 		NONE  							  								  */
/******************************************************************************/
void FrameBatteryMenu::SetRefreshTable()
{
	/*%C Alway */
	RefreshTable[0] = NULL;

	/*%C Insp */
	RefreshTable[1] = NULL;

	/*%C Exp */
	RefreshTable[2] = NULL;

	/*%C XAlway */
	RefreshTable[3] = &this->LOVBatteryVoltage;
	RefreshTable[4] = &this->LOVBatteryTemperature;
	RefreshTable[5] = NULL;
}
/******************************************************************************/
/*%C                       Functional description :                           */
/*%C                                                                          */
/*%C Désinstallation de la table de refresh     							   */
/*%C                                                                          */
/*%I Input Parameter : 														  */
/*%I	  	NONE															  */
/*%IO Input/Output : 														  */
/*%IO		NONE															  */
/*%O Output Parameter : 													  */
/*%O 		NONE  							  								  */
/******************************************************************************/
void FrameBatteryMenu::UnsetRefreshTable()
{
	/*%C Alway */
	RefreshTable[0] = NULL;

	/*%C Insp */
	RefreshTable[1] = NULL;

	/*%C Exp */
	RefreshTable[2] = NULL;

	/*%C XAlway */
	RefreshTable[3] = NULL;
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
DisplayObject** FrameBatteryMenu::GetRefreshTable()
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
void FrameBatteryMenu::Show()
{
	UWORD16 _UnknowBat, _NoBat, _Ageing;

	/*%C Unknown Battery flag reading */
	DataBaseAccess::ReadValue(&_UnknowBat, UNKNOWN_BATTERY_U16, POWER_SUPPLY);

  	/*%C No Battery flag reading */
	DataBaseAccess::ReadValue(&_NoBat, NO_PRESENCE_BAT_U16, POWER_SUPPLY);

   /*%C Ageing value */
   DataBaseAccess::ReadValue(&_Ageing, AGING_U16, POWER_SUPPLY);

	VFrame::Show();
   LInternalBatteryMenu.Show();
   LOVUnknownBat.Hide();
   LNoBat.Hide();
   if(_NoBat)
   {
      UnsetRefreshTable();   
      LNoBat.Show();
   }
   else
   {
    SetRefreshTable();
    
   	if(_UnknowBat)
   	{
         VDDate.StopMonitoringMode();
         VTTime.StopMonitoringMode();
		   VDDate.Hide();
     		VTTime.Hide();
         LOVUnknownBat.StopMonitoringMode();
         LOVUnknownBat.Show();
   		LOVCyclesDone.StopMonitoringMode();
      	LOVTheoreticalCapacity.StopMonitoringMode();
      	LOVAgeing.StopMonitoringMode();
	   }
   	else
	   {
         if(!GetForcedStoppedMonitoring())
         {
	   	   LOVBatteryVoltage.StartMonitoringMode();
      		LOVBatteryTemperature.StartMonitoringMode();
	   	   VDDate.StartMonitoringMode();
         	VTTime.StartMonitoringMode();
         }
        	VDDate.Show();
     	   VTTime.Show();
       	VDDate.Refresh();
        	VTTime.Refresh();
         if(!GetForcedStoppedMonitoring())
         {
		      LOVCyclesDone.StartMonitoringMode();
            LOVTheoreticalCapacity.StartMonitoringMode();
         }            
         if((AGEING_LOW_LIMIT <= _Ageing) && (AGEING_HIGH_LIMIT >= _Ageing) && !GetForcedStoppedMonitoring())
      	   LOVAgeing.StartMonitoringMode();
         else
      	   LOVAgeing.StopMonitoringMode();
	   }
	   LOVBatteryVoltage.Show();
	   LOVBatteryTemperature.Show();
	   LOVCyclesDone.Show();
  	   LVSSupplier.Show();
  	   LOVTheoreticalCapacity.Show();
  	   LOVAgeing.Show();
   }
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
void FrameBatteryMenu::RefreshLanguage()
{
	LInternalBatteryMenu.RefreshLanguage();
  	LInternalBatteryMenu.SetCentered(LInternalBatteryMenu.GetCentered());
	LOVBatteryVoltage.RefreshLanguage();
	LOVBatteryTemperature.RefreshLanguage();
   VDDate.RefreshLanguage();
	LOVCyclesDone.RefreshLanguage();
	LVSSupplier.RefreshLanguage();
   	LOVTheoreticalCapacity.RefreshLanguage();
   	VTTime.RefreshLanguage();
   	LOVAgeing.RefreshLanguage();
      LNoBat.RefreshLanguage();
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
void FrameBatteryMenu::Hide()
{
	UWORD16 _UnknowBat, _NoBat;

	/*%C Unknown Battery flag reading */
	DataBaseAccess::ReadValue(&_UnknowBat, UNKNOWN_BATTERY_U16, POWER_SUPPLY);

  	/*%C No Battery flag reading */
	DataBaseAccess::ReadValue(&_NoBat, NO_PRESENCE_BAT_U16, POWER_SUPPLY);

  	LInternalBatteryMenu.Hide();
   if(_NoBat)
   {
      LNoBat.Hide();
   }
   else
   {
	   LOVBatteryVoltage.Hide();
   	LOVBatteryTemperature.Hide();
      if(_UnknowBat)
         LOVUnknownBat.Hide();
      else
      {
	      VDDate.Hide();
   	   VTTime.Hide();
      }
	   LOVCyclesDone.Hide();
   	LVSSupplier.Hide();
   	LOVTheoreticalCapacity.Hide();
   	LOVAgeing.Hide();
   }
    VFrame::Hide();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	_Flag : TRUE indique qu'il y a un problème   								*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameBatteryMenu::BadSupplyCheck(e_BOOL _Flag)
{
	if(_Flag)
   {
      LOVCyclesDone.StopMonitoringMode();
      LOVBatteryVoltage.StopMonitoringMode();
      LOVBatteryTemperature.StopMonitoringMode();
   }
	else
   {
      LOVCyclesDone.StartMonitoringMode();
      LOVBatteryVoltage.StartMonitoringMode();
      LOVBatteryTemperature.StartMonitoringMode();
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
void FrameBatteryMenu::SetSupplyBusFailure(e_BOOL Flag, e_BOOL DisplayFlag)
{
   e_BOOL   _IsVisibleBatteryVoltage,
            _IsVisibleBatteryTemperature,
            _IsVisibleDate,
            _IsVisibleCyclesDone,
            _IsVisibleSupplier,
            _IsVisibleTheoreticalCapacity,
            _IsVisibleTime,
            _IsVisibleAgeing;

   /* sauvegarde des valeurs */
   _IsVisibleBatteryVoltage =  LOVBatteryVoltage.IsVisible();
   _IsVisibleBatteryTemperature =  LOVBatteryTemperature.IsVisible();
   _IsVisibleDate = VDDate.IsVisible();
   _IsVisibleCyclesDone = LOVCyclesDone.IsVisible();
   _IsVisibleSupplier = LVSSupplier.IsVisible();
   _IsVisibleTheoreticalCapacity = LOVTheoreticalCapacity.IsVisible();
   _IsVisibleTime = VTTime.IsVisible();
   _IsVisibleAgeing = LOVAgeing.IsVisible();

   if(!DisplayFlag)
   {
      LOVBatteryVoltage.SetVisible(FALSE);
      LOVBatteryTemperature.SetVisible(FALSE);
      VDDate.SetVisible(FALSE);
      LOVCyclesDone.SetVisible(FALSE);
      LVSSupplier.SetVisible(FALSE);
      LOVTheoreticalCapacity.SetVisible(FALSE);
      VTTime.SetVisible(FALSE);
      LOVAgeing.SetVisible(FALSE);
   }
   else
   {
      LOVBatteryVoltage.SetVisible(TRUE);
      LOVBatteryTemperature.SetVisible(TRUE);
      VDDate.SetVisible(TRUE);
      LOVCyclesDone.SetVisible(TRUE);
      LVSSupplier.SetVisible(TRUE);
      LOVTheoreticalCapacity.SetVisible(TRUE);
      VTTime.SetVisible(TRUE);
      LOVAgeing.SetVisible(TRUE);
   }

   /* mise à jour du flag interne */
   SetForcedStoppedMonitoring(Flag);
      
   if(Flag)
   {
      LOVBatteryVoltage.StopMonitoringMode();
   	LOVBatteryTemperature.StopMonitoringMode();
      VDDate.StopMonitoringMode();
   	LOVCyclesDone.StopMonitoringMode();
	   LVSSupplier.StopMonitoringMode();
   	LOVTheoreticalCapacity.StopMonitoringMode();
   	VTTime.StopMonitoringMode();
   	LOVAgeing.StopMonitoringMode();
   }
   else
   {
      LOVBatteryVoltage.StartMonitoringMode();
   	LOVBatteryTemperature.StartMonitoringMode();
      VDDate.StartMonitoringMode();
   	LOVCyclesDone.StartMonitoringMode();
	   LVSSupplier.StartMonitoringMode();
   	LOVTheoreticalCapacity.StartMonitoringMode();
   	VTTime.StartMonitoringMode();
   	LOVAgeing.StartMonitoringMode();
   }

   /* restauration des valeurs */
   LOVBatteryVoltage.SetVisible(_IsVisibleBatteryVoltage);
   LOVBatteryTemperature.SetVisible(_IsVisibleBatteryTemperature);
   VDDate.SetVisible(_IsVisibleDate);
   LOVCyclesDone.SetVisible(_IsVisibleCyclesDone);
   LVSSupplier.SetVisible(_IsVisibleSupplier);
   LOVTheoreticalCapacity.SetVisible(_IsVisibleTheoreticalCapacity);
   VTTime.SetVisible(_IsVisibleTime);
   LOVAgeing.SetVisible(_IsVisibleAgeing);
}
