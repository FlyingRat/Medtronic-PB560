/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTwoValueLock.cpp 		   	      	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + Text + sep + value					 					*/
/*%C   + unit + value + unit 																	*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelTwoValueLock.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelTwoValueLock::LabelTwoValueLock():LabelTwoValue()
{

}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/


/******************************************************************************/
/*                           METHODES                					    		  */
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des paramettres d'acce a DB											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdParam2 : Id DB de la valeur2								            	*/
/*%I		DbTarget2 : Target DB	de la valeur2											*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValueLock::InitDbAccess(UWORD16 _IdParam1,
												 e_TYPE_OF_DB_TARGET _DbTarget1,
												 UWORD16 _IdParam2,
                                     e_TYPE_OF_DB_TARGET _DbTarget2)
{
   LabelOneValue::InitDbAccess(_IdParam1,_DbTarget1);
   SetIdParam2(_IdParam2);
   SetDbTarget2(_DbTarget2);
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
void LabelTwoValueLock::Refresh()
{
   if(!IsStopMonitoring())
   {
      if(GetIdParam() != NO_ID)
      {
         UWORD16 Value1;
         DataBaseAccess::ReadValue(	&Value1,
         									GetIdParam(), 
         									GetDbTarget());
         Value1 = Value1 / GetDivider();
         SetValue1(Value1);
      }
      if(GetIdParam2() != NO_ID)
      {
         UWORD16 Value2;
         DataBaseAccess::ReadValue(	&Value2,
         									GetIdParam2(), 
         									GetDbTarget2());
         Value2 = Value2 / GetDivider();
         SetValue2(Value2);
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification d'un Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValueLock::StartModifMode()
{
   Label::StartModifMode();
   SetValueState(2);
   ModifNextValue();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTwoValueLock::ConfirmModifValue(e_BOOL _Confirm)
{
	e_BOOL ValidParam = FALSE;

   if(_Confirm)
   {
      if(GetIdParam() != NO_ID)
      {
         /*%C Acces DB */
         UWORD16 Value1 = GetValue1();
         Value1 = Value1 * GetDivider();
         DataBaseAccess::WriteValue(&Value1,
         									GetIdParam(), 
         									GetDbTarget());
		 ValidParam = TRUE;
      }
      if(GetIdParam2() != NO_ID)
      {
         /*%C Acces DB */
         UWORD16 Value2 = GetValue2();
         Value2 = Value2 * GetDivider();
         DataBaseAccess::WriteValue(&Value2,
         									GetIdParam2(), 
         									GetDbTarget2());
		 ValidParam = TRUE;
      }

	  if(ValidParam)
	  {
	  	/*%C Request a short bip sound */
		Tools::ShortBipRequest();
	  }
   }
   else
   {
		/*%C affiche l'ancienne valeur */
		switch(GetValueState())
      {
         case 1:  SetValue1(GetValueTemp());
                  break;
         case 2:  SetValue2(GetValueTemp());
                  break;
         default : break;                  
      }
   }
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
void LabelTwoValueLock::StartMonitoringMode()
{
	LabelTwoValue::StartMonitoringMode();
}


