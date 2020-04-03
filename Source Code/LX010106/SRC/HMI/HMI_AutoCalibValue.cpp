/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_AutoCalibValue.cpp                                       	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Champ de calibration automatique        											*/
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_AutoCalibValue.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
AutoCalibValue::AutoCalibValue():LabelOneValue()
{
   SetIdCalibParam(0);
   SetBdCalibParam(ADJUST);
   SetSegmentList(NULL);
   SetNbSegment(0);
   SetCurrentSegment(0);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
UWORD16 AutoCalibValue::GetIdCalibParam()
{
   return IdCalibParam;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET AutoCalibValue::GetBdCalibParam()
{
   return BdCalibParam;
}
/*----------------------------------------------------------------------------*/
UWORD16 AutoCalibValue::GetNbSegment()
{
   return NbSegment;
}
/*----------------------------------------------------------------------------*/
UWORD16 AutoCalibValue::GetCurrentSegment()
{
   return CurrentSegment;
}
/*----------------------------------------------------------------------------*/
void AutoCalibValue::SetIdCalibParam(UWORD16 _IdCalibParam)
{
   IdCalibParam = _IdCalibParam;
}
/*----------------------------------------------------------------------------*/
void AutoCalibValue::SetBdCalibParam(e_TYPE_OF_DB_TARGET _BdCalibParam)
{
   BdCalibParam = _BdCalibParam;
}
/*----------------------------------------------------------------------------*/
void AutoCalibValue::SetSegmentList(const UWORD16* _SegmentList)
{
   SegmentList = _SegmentList;
}
/*----------------------------------------------------------------------------*/
void AutoCalibValue::SetFloatList(const e_BOOL* _FloatList)
{
   FloatList = _FloatList;
}
/*----------------------------------------------------------------------------*/
void AutoCalibValue::SetNbSegment(UWORD16 _NbSegment)
{
   NbSegment = _NbSegment;
}
/*----------------------------------------------------------------------------*/
void AutoCalibValue::SetCurrentSegment(UWORD16 _CurrentSegment)
{
   CurrentSegment = _CurrentSegment;
}

/******************************************************************************/
/*                          	 	METHODES                				     		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		IdCalibParam : Id DB											           		   */
/*%I		BdCalibParam : Target DB										            	*/
/*%I		SegmentList  : Tableau definissant les valeurs a calibrer       		*/
/*%I 		FloatList    : Tableau le type des valeurs a calibrer			   		*/
/*%I		NbSegment    : Nb de valeur a calibrer						         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void AutoCalibValue::InitCalibProperties( UWORD16 _IdCalibParam,
                                          e_TYPE_OF_DB_TARGET _BdCalibParam,
                                          const UWORD16* _SegmentList,
                                          const e_BOOL* _FloatList,
                                          UWORD16 _NbSegment)
{

	/*%C Initialisation */
   SetIdCalibParam(_IdCalibParam);
   SetBdCalibParam(_BdCalibParam);
   SetSegmentList(_SegmentList);
   SetFloatList(_FloatList);
   SetNbSegment(_NbSegment);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne la valeur a calibrer															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Index : Indice de la valeur									         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Valeur a calibrer				  														*/
/******************************************************************************/
UWORD16 AutoCalibValue::GetSegmentListAt(UWORD16 _Index)
{
   /*%C Turn over the value has to gauge else return 0 */
   if(SegmentList != NULL)
   {
      if(_Index >= GetNbSegment())
      {
         _Index = GetNbSegment();
      }
      return SegmentList[_Index];
   }
   else
   {
   	return 0;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne le type de la valeur a calibrer										 	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Index : Indice de la valeur									         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	Type de la valeur a calibrer 														*/
/******************************************************************************/
e_BOOL AutoCalibValue::GetFloatListAt(UWORD16 _Index)
{
   /*%C Turn over the type of the value to gauge else false */
   if(FloatList != NULL)
   {
      if(_Index >= GetNbSegment())
      {
         _Index = GetNbSegment();
      }
      return FloatList[_Index];
   }
   else
   {
   	return FALSE;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine si la verification de la calibration courante est realisée	 	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	TRUE ou FALSE					 														*/
/******************************************************************************/
e_BOOL AutoCalibValue::VerificationCalibCheck()
{
   UWORD16 Val;

	/*%C  Determine if the checking of the calibration is made  */
   DataBaseAccess::ReadValue(	&Val, 
   									GetIdCalibParam(), 
   									GetBdCalibParam());

   if((Val == TEST_LIMITES_OK) || (Val == TEST_LIMITES_FALSE))
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine si la calibration de la valeur courante est correcte	 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	TRUE ou FALSE					 														*/
/******************************************************************************/
e_BOOL AutoCalibValue::CalibSegmentOK()
{
   UWORD16 Val;

	/*%C  Determine if the calibration is correct */
	DataBaseAccess::ReadValue(	&Val, 
										GetIdCalibParam(),
										GetBdCalibParam());
   switch(Val)
   {
      case TEST_LIMITES_OK    : return TRUE;
      case TEST_LIMITES_FALSE : return FALSE;
		default 						: return FALSE;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la phase de modification du champ								 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	NONE								 														*/
/******************************************************************************/
void AutoCalibValue::StartModifMode()
{
   Label::StartModifMode();
   RefreshEnable(FALSE);
   SetCurrentSegment(0);
   SetFloatValue1(GetFloatListAt(GetCurrentSegment()));
   SetValue1(GetSegmentListAt(GetCurrentSegment()));

   /*%C  Beginning of the calibration */
   UWORD16 Val = SEGMENT_1; 
   DataBaseAccess::WriteValue(&Val, 
   									GetIdCalibParam(), 
   									GetBdCalibParam());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine di il faut stopper la calibration si erreur 						 	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	TRUE ou FALSE					 														*/
/******************************************************************************/
e_BOOL AutoCalibValue::StopIfErrorCalib()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
	return FALSE;
}				 

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret de la phase de modification du champ										 	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	NONE								 														*/
/******************************************************************************/
void AutoCalibValue::StopModifMode()
{
   LabelOneValue::StopModifMode();

   /*%C Refresh */
   SetFloatValue1(TRUE);

	/*%C Refresh value */
   SetValue1(0);
  	GetFValue1()->StoreValue(10);
   RefreshEnable(TRUE);

	/*%C Dtop of the calibration */
   UWORD16 Val = END_AUTOCALIB;
   DataBaseAccess::WriteValue(&Val, 
   									GetIdCalibParam(), 
   									GetBdCalibParam());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Changement de la valeur en modification									 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	NONE								 														*/
/******************************************************************************/
void AutoCalibValue::ModifNextValue()
{
   Label::ModifNextValue();
   SetCurrentSegment(GetCurrentSegment()+1);
   SetFloatValue1(GetFloatListAt(GetCurrentSegment()));
   SetValue1(GetSegmentListAt(GetCurrentSegment()));

   /*%C  Continuation of the calibration */
   UWORD16 Val = GetCurrentSegment()+1; 
   DataBaseAccess::WriteValue(&Val, 
   									GetIdCalibParam(), 
   									GetBdCalibParam());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la phase de modification du champ								 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	NONE								 														*/
/******************************************************************************/
void AutoCalibValue::StartModifModeConsult()
{
   Label::StartModifMode();

	/*%C Beginning of the checking of the calibration */
   RefreshEnable(FALSE);
   SetCurrentSegment(AUTOCALIB_SEG_1);
	SetFloatValue1(GetFloatListAt(GetCurrentSegment()-AUTOCALIB_SEG_1));
   SetValue1(GetSegmentListAt(GetCurrentSegment()-AUTOCALIB_SEG_1));

   UWORD16 Val = AUTOCALIB_SEG_1;
   DataBaseAccess::WriteValue(&Val, 
   									GetIdCalibParam(), 
   									GetBdCalibParam());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret de la phase de modification du champ								 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	NONE								 														*/
/******************************************************************************/
void AutoCalibValue::StopModifModeConsult()
{
   LabelOneValue::StopModifMode();

  	/*%C Refresh value */
   SetFloatValue1(TRUE);
 	SetValue1(0);
 	GetFValue1()->StoreValue(10);
 	RefreshEnable(TRUE);

	/*%C Stop the cheking of the calibration */
   UWORD16 Val = END_AUTOCALIB;
   DataBaseAccess::WriteValue(&Val, 
   									GetIdCalibParam(), 
   									GetBdCalibParam());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Changement de la valeur en consultation									 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	FALSE si plus de points		 														*/
/******************************************************************************/
e_BOOL AutoCalibValue::ModifNextValueConsult()
{
   if(((GetCurrentSegment()+1)-AUTOCALIB_SEG_1) < GetNbSegment())
   {
      /*%C Check the next point */
  		UWORD16 Val = GetCurrentSegment()+1; 
      DataBaseAccess::WriteValue(&Val, 
      									GetIdCalibParam(), 
      									GetBdCalibParam());

      SetCurrentSegment(GetCurrentSegment()+1);

      /*%C  posting of the point of calibration */
      SetFloatValue1(GetFloatListAt(GetCurrentSegment()-AUTOCALIB_SEG_1));
      SetValue1(GetSegmentListAt(GetCurrentSegment()-AUTOCALIB_SEG_1));

      return TRUE;
   }
   else
   {
      /*%C End of check */
      return FALSE;
   }
}
