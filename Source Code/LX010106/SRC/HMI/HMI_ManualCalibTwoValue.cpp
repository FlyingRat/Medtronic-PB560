/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ManualCalibTwoValue.cpp 	   	      	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet de calibration manuelle										 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_ManualCalibTwoValue.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                     	   */
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
ManualCalibTwoValue::ManualCalibTwoValue():ManualCalibValue()
{

}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void ManualCalibTwoValue::SetNameUnit2(UBYTE** _NameUnit2)
{
   if(_NameUnit2 != NULL)
      Value2.SetNameUnit(_NameUnit2);
}
/*----------------------------------------------------------------------------*/
void ManualCalibTwoValue::SetVisible(e_BOOL V)
{
   LabelOneValue::SetVisible(V);
   Value2.SetVisible(V);
}
/*----------------------------------------------------------------------------*/
void ManualCalibTwoValue::SetLine(UWORD16 Line)
{
   ManualCalibValue::SetLine(Line);
   Value2.SetLine(Line);
}
/*----------------------------------------------------------------------------*/
void ManualCalibTwoValue::SetMaxDisplayValue2(UWORD16 _MaxDisplayValue) 
{
	Value2.SetMaxDisplayValue(_MaxDisplayValue);
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
/*%I		IdCalibParam : Id DB											            		*/
/*%I 		BdCalibParam : Target DB										            	*/
/*%I 		SegmentList  : Tableau definissant les valeurs a calibrer       		*/
/*%I		FloatList    : Tableau le type des valeurs a calibrer			   		*/
/*%I		NbSegment    : Nb de valeur a calibrer						      		   */
/*%I		IdBlow       : Id du blower									   	         */
/*%I		BdBlow       : Bd Target du blower												*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::InitValue2(  UWORD16 _IdCalibParam,
                                       e_TYPE_OF_DB_TARGET _BdCalibParam,
                                       UBYTE **_Name,
                                       UWORD16 _Line,
                                       UWORD16 _Col,
                                       UBYTE **_NameUnit,
                                       UBYTE **_Sep,
                                       UWORD16 _ColSep)
{
   Value2.SetParent(GetParent());
   Value2.SetColValue1(8);
	Value2.SetFloatValue1(TRUE);
	Value2.SetSignValue(TRUE);
	Value2.InitDbAccess(_IdCalibParam, _BdCalibParam);
   Value2.Init(NO, _Name, _Line, _Col, 0, _NameUnit);
   Value2.SetSep(*_Sep);
	Value2.SetColSep(_ColSep);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la phase de modification du champ											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::StartModifMode()
{
   ManualCalibValue::StartModifMode();
   Value2.RefreshEnable(FALSE);
   Value2.SetFloatValue1(GetFloatListAt(GetCurrentSegment()));
   Value2.SetValue1(GetSegmentListAt(GetCurrentSegment()));
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret de la phase de modification du champ											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::StopModifMode()
{
   ManualCalibValue::StopModifMode();
  	
  	/*%C reprise du refresh */
   Value2.SetFloatValue1(TRUE);
   
   /*%C Pb de refresh de la valeur */
   Value2.SetValue1(0);
   Value2.GetFValue1()->StoreValue(10);
   Value2.RefreshEnable(TRUE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Changement de la valeur en modification												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::ModifNextValue()
{
   ManualCalibValue::ModifNextValue();

   Value2.SetFloatValue1(GetFloatListAt(GetCurrentSegment()));
   Value2.SetValue1(GetSegmentListAt(GetCurrentSegment()));
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::StopMonitoringMode()
{
   ManualCalibValue::StopMonitoringMode();
   Value2.StopMonitoringMode();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::StartMonitoringMode()
{
   ManualCalibValue::StartMonitoringMode();
   Value2.StartMonitoringMode();
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
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::RefreshLanguage()
{
   ManualCalibValue::RefreshLanguage();
   Value2.RefreshLanguage();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'affichage																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::Refresh()
{
   ManualCalibValue::Refresh();
   Value2.Refresh();
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
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::Show()
{
   ManualCalibValue::Show();
   Value2.Show();
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
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::Hide()
{
   Value2.Hide();
   ManualCalibValue::Hide();   
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::Blink(e_BOOL _Actif)
{
   ManualCalibValue::Blink(_Actif);
   Value2.Blink(_Actif);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la phase de modification du champ											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::StartModifModeConsult()
{
   /*%C Debut de la verification de la calibration */
   AutoCalibValue::StartModifModeConsult();

   Value2.SetFloatValue1(GetFloatListAt(GetCurrentSegment()-AUTOCALIB_SEG_1));
   Value2.SetValue1(GetSegmentListAt(GetCurrentSegment()-AUTOCALIB_SEG_1));

}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret de la phase de modification du champ											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibTwoValue::StopModifModeConsult()
{
   AutoCalibValue::StopModifModeConsult();
  
   /*%C reprise du refresh */
   Value2.SetFloatValue1(TRUE);
 	Value2.SetValue1(0);
 	Value2.GetFValue1()->StoreValue(10);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Changement de la valeur en consultation												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		FALSE si plus de points		  														*/
/******************************************************************************/
e_BOOL ManualCalibTwoValue::ModifNextValueConsult()
{
   e_BOOL Val;

	Val = AutoCalibValue::ModifNextValueConsult();
   
   /*%C suite de la calibration */
   if(Val == TRUE)
   {
      /*%C affichage du point de calib */
      Value2.SetFloatValue1(GetFloatListAt(	GetCurrentSegment()-
      													AUTOCALIB_SEG_1));

      Value2.SetValue1(GetSegmentListAt(	GetCurrentSegment()-
      												AUTOCALIB_SEG_1));
   }
   return (Val);
}

