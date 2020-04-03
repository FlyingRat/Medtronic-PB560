/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameMaintenance.cpp    	  		                  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Fenetre Maintenance																      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_FrameMaintenance.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Message.hpp"

extern "C"
{
#include "DB_Control.h"
#include "DB_Compute.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
FrameMaintenance::FrameMaintenance():VFrame()
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
void FrameMaintenance::init()
{
   LMaintenance.SetParent		(this);

	LMaintenance.Init				(NO,
										(UBYTE**)cMSG_MenuMaintenance,
										18,
										0);

	LMaintenance.SetFontLabel	(FONT_4);

   LMaintenance.SetCentered   (TRUE);

   /* Version soft CPU */
	LVSVersionSoft.SetParent	(this);

	LVSVersionSoft.Init			(NO,
										(UBYTE**)cMSG_SoftwareVersion,
										36,
										8);

   LVSVersionSoft.InitDbAccess(VERSION);

   LVSVersionSoft.SetColAdjust(TRUE);

	LVSVersionSoft.SetColLabel	(0);

   LVSVersionSoft.SetColSep	(0);    /* param = 0 -> on ajuste la colonne au mieux */

	LVSVersionSoft.SetColValue1(0);    /* param = 0 -> on ajuste la colonne au mieux */

   /* Version soft Carte Alim */
	LVSSupplyVersionSoft.SetParent	(this);

	LVSSupplyVersionSoft.Init			(NO,
										      (UBYTE**)cMSG_SupplySoftwareVersion,
										      36,
										      150);

   LVSSupplyVersionSoft.InitDbAccess(POWER_SUPPLY);

   LVSSupplyVersionSoft.SetColAdjust(TRUE);

	LVSSupplyVersionSoft.SetColLabel	(0);

	LVSSupplyVersionSoft.SetColSep	(0);     /* param = 0 -> on ajuste la colonne au mieux */

	LVSSupplyVersionSoft.SetColValue1(0);     /* param = 0 -> on ajuste la colonne au mieux */

   /* Numéro de série */
   LVSSerieNumber.SetParent			(this);

	LVSSerieNumber.InitDbAccess		(VERSION);

	LVSSerieNumber.Init					(NO,
												(UBYTE**)cMSG_ShortSerial,
												54,
												150);
                                    
	LVSSerieNumber.SetColAdjust      (TRUE);

   LVSSerieNumber.SetColLabel	      (0);

	LVSSerieNumber.SetColSep			(0);

	LVSSerieNumber.SetColValue1		(0);



   LOVSpeed.SetParent			(this);

	LOVSpeed.InitDbAccess		(MEASURE_SPEED_BLOWER_U16,
										COMPUTE);

	LOVSpeed.Init					(NO,
										(UBYTE**)cMSG_NoneUnit,
										196,
										218, 
										25000, 
										(UBYTE**)cMSG_SpeedUnit);

	LOVSpeed.SetColLabel			(0);

	LOVSpeed.SetColSep			(0);

	LOVSpeed.SetSep				((UBYTE *)"");

	LOVSpeed.SetColValue1		(8);

	TFSup.SetParent				(this);

	TFSup.Init						(196,
										189,
										FONT_1,
										FALSE,
										(UBYTE *)">>");

   /*%C Table de refresh */

	/*%C Alway */
	RefreshTable[0] = NULL;

	/*%C Insp */
	RefreshTable[1] = NULL;

	/*%CEXp */
	RefreshTable[2] = NULL;

	/*%C XAlway */
	RefreshTable[3] = &this->LOVSpeed;
	RefreshTable[4] = NULL;
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
DisplayObject** FrameMaintenance::GetRefreshTable()
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
void FrameMaintenance::Show()
{
	VFrame::Show();
	LMaintenance.Show();
	LVSVersionSoft.Show();
   LVSSupplyVersionSoft.Show();   
   LVSSerieNumber.Show();
	LOVSpeed.Show();
	TFSup.Show();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Positionne la ligne d'affichage de l'objet blower speed            		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	_Line : line number to be set														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameMaintenance::SetBlowerSpeedLine(UWORD16 _Line)
{
	LOVSpeed.SetLine(_Line);
	TFSup.SetLine(_Line);
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
void FrameMaintenance::RefreshLanguage()
{
	LMaintenance.RefreshLanguage();
   LMaintenance.SetCentered(LMaintenance.GetCentered());
	LVSVersionSoft.RefreshLanguage();
   LVSSupplyVersionSoft.RefreshLanguage();
	LVSSerieNumber.RefreshLanguage();
	LOVSpeed.RefreshLanguage();
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
void FrameMaintenance::Hide()
{
	LMaintenance.Hide();
	LVSVersionSoft.Hide();
   LVSSupplyVersionSoft.Hide();
   LVSSerieNumber.Hide();
	LOVSpeed.Hide();
	TFSup.Hide();
	VFrame::Hide();    
}


