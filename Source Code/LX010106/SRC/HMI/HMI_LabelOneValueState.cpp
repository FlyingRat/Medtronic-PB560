/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueState.cpp  	  		    	           	 	  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage d'une valeur mais qui passe a "Non"	 						*/
/*%C ou autre pour un certain flag de la BD												*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelOneValueState.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValueState::LabelOneValueState():LabelOneValue()
{
   SetValueState(0);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
UWORD16 LabelOneValueState::GetValueState()
{
   return ValueState;
}
/*----------------------------------------------------------------------------*/
void LabelOneValueState::SetValueState(UWORD16 _ValueState)
{
   ValueState = _ValueState;
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Debut de la modification d'un Objet			  										*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																  		         	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueState::StartModifMode()
{
   LabelOneValue::StartModifMode();
   SetValue1(GetValue1());
   SetValueState(1);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Confirme la modification de la valeur de Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																  		         	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueState::StopModifMode()
{
   LabelOneValue::StopModifMode();
   SetValueState(1);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C modification de la valeur suivante													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																  		         	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueState::ModifNextValue()
{
   UWORD16 State = GetValueState();
	/*%C  modification of the following value */ 
   SetValueState(++State);
}
