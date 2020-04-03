/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ManualCalibValue.cpp 	   	      	 	  						*/
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

#include "HMI_ManualCalibValue.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                     	   */
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
ManualCalibValue::ManualCalibValue():AutoCalibValue()
{
firstRequest = TRUE;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
UWORD16 ManualCalibValue::GetIdBlow()
{
   return IdBlow;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET ManualCalibValue::GetBdBlow()
{
   return BdBlow;
}
/*----------------------------------------------------------------------------*/
void ManualCalibValue::SetIdBlow(UWORD16 _IdBlow)
{
   IdBlow = _IdBlow;
}
/*----------------------------------------------------------------------------*/
void ManualCalibValue::SetBdBlow(e_TYPE_OF_DB_TARGET _BdBlow)
{
   BdBlow = _BdBlow;
}
/*----------------------------------------------------------------------------*/
UWORD16 ManualCalibValue::GetIdMesBlow()
{
   return IdMesBlow;
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET ManualCalibValue::GetBdMesBlow()
{
   return BdMesBlow;
}
/*----------------------------------------------------------------------------*/
void ManualCalibValue::SetIdMesBlow(UWORD16 _IdMesBlow)
{
   IdMesBlow = _IdMesBlow;
}
/*----------------------------------------------------------------------------*/
void ManualCalibValue::SetBdMesBlow(e_TYPE_OF_DB_TARGET _BdMesBlow)
{
   BdMesBlow = _BdMesBlow;
}
/*----------------------------------------------------------------------------*/
void ManualCalibValue::SetFirstModifOnCalibPoint(e_BOOL _Flag)
{
   FirstModifOnCalibPoint = _Flag;
}
/*----------------------------------------------------------------------------*/
e_BOOL ManualCalibValue::IsFirstModifOnCalibPoint()
{
	return (e_BOOL)(FirstModifOnCalibPoint == TRUE);
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
void ManualCalibValue::InitCalibProperties(  UWORD16 _IdCalibParam,
                                             e_TYPE_OF_DB_TARGET _BdCalibParam,
                                             const UWORD16* _SegmentList,
                                             const e_BOOL* _FloatList,
                                             UWORD16 _NbSegment,
                                             UWORD16 _IdBlow,
                                             e_TYPE_OF_DB_TARGET _BdBlow,
                                             UWORD16 _IdMesBlow,
                                             e_TYPE_OF_DB_TARGET _BdMesBlow)
{
	AutoCalibValue::InitCalibProperties(_IdCalibParam,
                                       _BdCalibParam,
   												_SegmentList,
                                       _FloatList,
                                       _NbSegment);
	SetIdBlow(_IdBlow);
   SetBdBlow(_BdBlow);
   SetIdMesBlow(_IdMesBlow);
   SetBdMesBlow(_BdMesBlow);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Incrementation de la valeur courante													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibValue::IncreaseValue()
{
	UWORD16 Val;

	if(GetIdCalibParam()!= NO_ID)
   {
      if(IsFirstModifOnCalibPoint())
      {
			if(GetIdMesBlow() != NO_ID)
			{
				/*%C Copie de la valeur blower dans adjust */
				DataBaseAccess::ReadValue(&Val, GetIdMesBlow(), GetBdMesBlow());
				DataBaseAccess::WriteValue(&Val, GetIdBlow(), GetBdBlow());
         }
      SetFirstModifOnCalibPoint(FALSE);
      }

		DataBaseAccess::ReadValue(&Val, GetIdBlow(), GetBdBlow());
      /*%C Access to data base */
      if(IncreaseValueOk(&Val))
      {
      	DataBaseAccess::WriteValue(&Val, GetIdBlow(), GetBdBlow());
      }
      /*%C Access to data base */
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Decrementation de la valeur courante													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ManualCalibValue::DecreaseValue()
{
	UWORD16 Val;

	if(GetIdCalibParam()!= NO_ID)
   {
		if(IsFirstModifOnCalibPoint())
      {
			if(GetIdMesBlow() != NO_ID)
			{
		    	/*%C Copie de la valeur blower dans adjust */
				DataBaseAccess::ReadValue(&Val, GetIdMesBlow(), GetBdMesBlow());
				DataBaseAccess::WriteValue(&Val, GetIdBlow(), GetBdBlow());
         }
			SetFirstModifOnCalibPoint(FALSE);
		}

		DataBaseAccess::ReadValue(&Val, GetIdBlow(), GetBdBlow());
		/*%C Access to data base */
		if(DecreaseValueOk(&Val))
      {
		   DataBaseAccess::WriteValue(&Val, GetIdBlow(), GetBdBlow());
		}
		/*%C Access to data base */
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation d'increment																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Val : valeur a incrementer															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé  														*/
/******************************************************************************/
e_BOOL ManualCalibValue::IncreaseValueOk(UWORD16* _Val)
{
   if(GetIdBlow() != NO_ID)
   {
      return DataBaseAccess::IncrementValue(_Val, GetIdBlow(), GetBdBlow());
   }
   return FALSE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation de decrement																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Val : valeur a decrementer															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si decrement autorisé  														*/
/******************************************************************************/
e_BOOL ManualCalibValue::DecreaseValueOk(UWORD16* _Val)
{
	if(GetIdBlow() != NO_ID)
   {
		return DataBaseAccess::DecrementValue(_Val, GetIdBlow(), GetBdBlow());
	}
	return FALSE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine if faut stopper la calib si erreur						  				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	TRUE ou FALSE	 																		*/
/******************************************************************************/
e_BOOL ManualCalibValue::StopIfErrorCalib()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
	return TRUE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine si la verification de la calibration courante est realisée		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	TRUE ou FALSE	 																		*/
/******************************************************************************/
e_BOOL ManualCalibValue::VerificationCalibCheck()
{
	UWORD16 Val;

	if(firstRequest)
   {
      /*%C demande de verification */
	   Val = TEST_LIMITES_REQUEST;
      DataBaseAccess::WriteValue(&Val, GetIdCalibParam(), GetBdCalibParam());
      firstRequest = FALSE;
      return FALSE;
   }
   else
   {
      /*%C test de la reponse */
      DataBaseAccess::ReadValue(&Val, GetIdCalibParam(), GetBdCalibParam());
    	if((Val == TEST_LIMITES_OK) || (Val == TEST_LIMITES_FALSE))
      {
         firstRequest = TRUE;
			return TRUE;
      }
      else
      {
         return FALSE;
      }
   }
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
/*%O 	  	NONE				 																		*/
/******************************************************************************/
void ManualCalibValue::StartModifMode()
{
   AutoCalibValue::StartModifMode();

   /*%C Mise a Zero de la commande blower */
   UWORD16 Val = 0;
   DataBaseAccess::WriteValue(&Val, GetIdBlow(), GetBdBlow());

   /*%C Init du flag de modif */
   SetFirstModifOnCalibPoint(TRUE);
	firstRequest = TRUE;
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
/*%O 	  	NONE				 																		*/
/******************************************************************************/
void ManualCalibValue::StopModifMode()
{
   AutoCalibValue::StopModifMode();
 
   /*%C Mise a Zero de la commande blower */
   UWORD16 Val = 0;
 
   DataBaseAccess::WriteValue(&Val, GetIdBlow(), GetBdBlow());

   /*%C Init du flag de modif */
	SetFirstModifOnCalibPoint(TRUE);
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
/*%O 	  	NONE				 																		*/
/******************************************************************************/
void ManualCalibValue::ModifNextValue()
{
   AutoCalibValue::ModifNextValue();

   /*%C Mise a Zero de la commande blower */
   UWORD16 Val = 0;
   DataBaseAccess::WriteValue(&Val, GetIdBlow(), GetBdBlow());

   /*%C Init du flag de modif */
   SetFirstModifOnCalibPoint(TRUE);
}
