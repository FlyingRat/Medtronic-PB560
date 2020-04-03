/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueFiO2Flag.cpp		                        	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Objet d'affichage pour la FiO2                                           */
/*%C			                                                                  */
/******************************************************************************/

/************************************************************************/
/*                           HEADER INCLUDE FILE		                */
/************************************************************************/

#include "HMI_LabelOneValueFiO2Flag.hpp"

/************************************************************************/
/*                           OTHER INCLUDE FILE		                	*/
/************************************************************************/

#include "HMI_DataBaseAccess.hpp"

extern "C"
{
#include "DB_Control.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValueFiO2Flag::LabelOneValueFiO2Flag():LabelOneValueFlag()
{
   //LabelOneValue::LabelOneValue();
   ModifyOn = FALSE;
   ChangeModeOn = FALSE;
}
/******************************************************************************/
/*                           ACCESSEURS						                	   */
/******************************************************************************/
void LabelOneValueFiO2Flag::Set100FiO2()
{
	if(!ModifyOn)
		LabelOneValue::SetValue1(100);
}
/*----------------------------------------------------------------------------*/
void LabelOneValueFiO2Flag::SetChangeMode(e_BOOL _ChangeModeOn)
{
	ChangeModeOn = _ChangeModeOn;
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'affichage																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueFiO2Flag::Refresh()
{
   UWORD16 Active;
   UWORD16 Value;

   if(!IsStopMonitoring())
   {
	   if(GetIdParam() != NO_ID)
      {
         DataBaseAccess::ReadValue(&Value, GetIdParam(), GetDbTarget());
   		DataBaseAccess::ReadValue(&Active, FIO2_100_ACTIVE, CONTROL);
         
		   if(Active && !ModifyOn && !ChangeModeOn)
	         SetValue1(100);
         else
	         SetValue1(Value);
	   }
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification de l'Objet  												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueFiO2Flag::StartModifMode()
{
	UWORD16 val;

	ModifyOn = TRUE;

   LabelOneValueFlag::StartModifMode();

	DataBaseAccess::ReadValue(&val, FIO2_100_ACTIVE, CONTROL);
   if(val)
   {
      DataBaseAccess::ReadValue(&val, GetIdParam(), GetDbTarget());
      SetValue1(val);
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirmation de la valeur moodifiée     											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_Confirm																					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueFiO2Flag::ConfirmModifValue(e_BOOL _Confirm)
{
    LabelOneValueFlag::ConfirmModifValue(_Confirm);
    ModifyOn = FALSE;
}
