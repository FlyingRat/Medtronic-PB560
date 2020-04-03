/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameWelcome.cpp    		  		                  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  Fenetre Welcome																	      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_FrameWelcome.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Message.hpp"
#include "HMI_Config.hpp"

extern "C"
{
#include "DB_Control.h"
#include "DB_Rtc.h"
}


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
FrameWelcome::FrameWelcome():VFrame()
{

}

/******************************************************************************/
/*                           ACCESSEURS						                	   */
/******************************************************************************/


/******************************************************************************/
/*                           METHODES               		 				      	*/
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
void FrameWelcome::init()
{
   UWORD16 _Col, _Col2, _Col3;
   UWORD16 _Line;
   e_SYMBOL _Logo, _Logo2, _Logo3;

	LWelcome.SetParent			(this);

	LWelcome.Init					(NO, 
										(UBYTE**)cMSG_Welcome,
										22,
										0);

	LWelcome.SetFontLabel		(FONT_4);

   LWelcome.SetCentered		   (TRUE);

	Date1.SetParent				(this);

	Date1.InitDbAccess			(DB_RTC_MONTH_U16, 
										RTC, 
										DB_RTC_DAY_U16, 
										DB_RTC_YEAR_U16,
                        		ADJUST_RTC_MONTH_U16, 
                        		ADJUST_RTC_DAY_U16, 
                        		ADJUST_RTC_YEAR_U16,RTC);

	Date1.Init						(NO,
									    NULL,  
									    22,     
									    8);

	Date1.SetColDate				(0);

	Date1.SetFontDate				(FONT_1);

	Date1.SetNameMonth			((UBYTE**)cMSG_Month);

	Date1.SetMonth					(12);

	Date1.SetSep					((UBYTE *)" ");

	Time1.SetParent				(this);

	Time1.InitDbAccess			(DB_RTC_HOUR_U16, 
										RTC, 
										DB_RTC_MINUTE_U16, 
										DB_RTC_SECOND_U16,
                        		ADJUST_RTC_HOUR_U16, 
                        		ADJUST_RTC_MINUTE_U16, 
                        		ADJUST_RTC_SECOND_U16);

	Time1.Init						(NO, 
										NULL, 
										22,
										238);

	Time1.SetColHours				(0);

	Time1.SetFontHours			(FONT_1);

	LOVMachine.SetParent			(this);

	LOVMachine.InitDbAccess		(CURRENT_MACHINE_COUNTER_HOUR_U16,
										CONTROL);

	LOVMachine.Init				(NO,
										(UBYTE**)cMSG_Machine, 
										59,
										8, 
										123,
				                  (UBYTE**)cMSG_HourUnit);

	LOVMachine.SetColLabel		(0);

	LOVMachine.SetColSep			(55);

	LOVMachine.SetColValue1		(59);

	LOVMachine.SetNbDigitValue1(5);

	LOVMachine.SetDisplayZeroValue1(TRUE);


	LTVPatient.SetParent       (this);

   LTVPatient.InitDbAccess    (CURRENT_PATIENT_COUNTER_HOUR_U16,
                              CONTROL,
                              CURRENT_PATIENT_COUNTER_MIN_U16,
                              CONTROL);

   LTVPatient.Init            (NO,
                              (UBYTE**)cMSG_PatWelcome,
							  59,
                              122,
                              10,
                              (UBYTE**)cMSG_HourUnit,
                              34,
                              (UBYTE**)cMSG_MinuteUnit);

   LTVPatient.SetColSep       (72);

   LTVPatient.SetColValue1    (77);

   LTVPatient.SetColValue2    (148);

   LTVPatient.SetColUnit2     (168);

   LTVPatient.SetNbDigitValue1(5);

   LTVPatient.SetDisplayZeroValue1(TRUE);

   LTVPatient.SetNbDigitValue2(2);

   LTVPatient.SetDisplayZeroValue2(TRUE);

   _Col = 10;
	LVSVersion.SetParent			(this);

	LVSVersion.Init				(NO,
										(UBYTE**)cMSG_VSoft,
										95,
										_Col);

   LVSVersion.InitDbAccess    (VERSION);

   LVSVersion.SetColAdjust     (TRUE);

   LVSVersion.SetColLabel        (0);

   LVSVersion.SetColSep          (0);

   LVSVersion.SetColValue1       (0);

   _Col = LVSVersion.GetEndCol() + 10 ;

   /* Version soft Carte Alim */
	LVSSupplyVersionSoft.SetParent	(this);

	LVSSupplyVersionSoft.Init			(NO,
										      (UBYTE**)cMSG_Slash,
										      95,
										      _Col);

   LVSSupplyVersionSoft.InitDbAccess(POWER_SUPPLY);

   LVSSupplyVersionSoft.SetSep      ((UBYTE*)"");

	LVSSupplyVersionSoft.SetColLabel(2);

	LVSSupplyVersionSoft.SetColSep	(5);

	LVSSupplyVersionSoft.SetColValue1(7);


	LCopyRight.SetParent		   (this);

	LCopyRight.Init					(NO,
									(UBYTE**)cMSG_CopyrightWelcome,
									230,
									55);



	SFCompanyName.SetParent				(this);

	_Line = 214;
	_Col = 155;
	_Logo = COMPANY;

	SFCompanyName.Init					(_Line,
										_Col,
										0,
										FALSE,
										_Logo);



   SFLogo.SetParent					(this);
   SFLogo2.SetParent				(this);
   SFLogo3.SetParent				(this);

#ifdef HMI_CONFIG_M2
   _Col = 30;
   _Col2 = 218;
   _Col3 = 242;
   _Logo = LOGO_LEGENDAIR;
   _Logo2 = TRADEMARK;
   _Logo3 = LOGO_M2;

#elif defined HMI_CONFIG_XL2
   _Col = 30;
   _Col2 = 218;
   _Col3 = 242;
   _Logo = LOGO_LEGENDAIR;
   _Logo2 = TRADEMARK;
   _Logo3 = LOGO_XL2;

#elif defined HMI_CONFIG_S2
   _Col = 30;
   _Col2 = 218;
   _Col3 = 242;   
   _Logo = LOGO_LEGENDAIR;
   _Logo2 = TRADEMARK;
   _Logo3 = LOGO_S2;

#else
   _Col = 0;
   _Col2 = 0;
   _Logo = NO;
   _Logo2 = NO;
   _Logo3 = NO;

#endif
	_Line = 150;

	SFLogo.Init						(_Line,
										_Col,
										0,
										FALSE,
										_Logo);

	SFLogo2.Init					(_Line,
										_Col2,
										0,
										FALSE,
										_Logo2);

	SFLogo3.Init					(_Line,
										_Col3,
										0,
										FALSE,
										_Logo3);


   /*%C Table de refresh */

	/*%C Alway */
	RefreshTable[0] = &this->Time1;
	RefreshTable[1] = NULL;

	/*%C Insp */
	RefreshTable[2] = NULL;

	/*%C Exp */
	RefreshTable[3] = NULL;

	/*%C XAlway */
	RefreshTable[4] = &this->Date1;
	RefreshTable[5] = NULL;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne la table des Objets a rafraichir									  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Objets a rafraichir																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
DisplayObject** FrameWelcome::GetRefreshTable()
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
void FrameWelcome::Show()
{
	VFrame::Show();
	LWelcome.Show();
	Date1.Refresh();
	Date1.Show();
	Time1.Refresh();
	Time1.Show();
	LOVMachine.Show();
	LTVPatient.Show();
   LVSVersion.Show();
   LVSSupplyVersionSoft.Show();
	SFCompanyName.Show();
   LCopyRight.Show();
	SFLogo.Show();
	SFLogo2.Show();
	SFLogo3.Show();   
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
void FrameWelcome::RefreshLanguage()
{
	LWelcome.RefreshLanguage();
   LWelcome.SetCentered(LWelcome.GetCentered());
	Date1.RefreshLanguage();
	Date1.RefreshLanguage();
	Time1.RefreshLanguage();
	LOVMachine.RefreshLanguage();
   LTVPatient.RefreshLanguage();
	LVSVersion.RefreshLanguage();
   LVSSupplyVersionSoft.RefreshLanguage();
   LCopyRight.RefreshLanguage();
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
void FrameWelcome::Hide()
{
	LWelcome.Hide();
	Date1.Hide();
	Date1.Hide();
	Time1.Hide();
	LOVMachine.Hide();
   LTVPatient.Hide();
	LVSVersion.Hide();
   LVSSupplyVersionSoft.Hide();
	SFCompanyName.Hide();
   LCopyRight.Hide();
	SFLogo.Hide();
	SFLogo2.Hide();
	SFLogo3.Hide();
	VFrame::Hide();    
}

