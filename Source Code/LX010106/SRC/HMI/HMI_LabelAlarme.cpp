/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelAlarme.cpp	  			                          	 		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	d'une alarme												      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelAlarme.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/



/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelAlarme::LabelAlarme():Label()
{
   AlarmId = 0;
   SetIcon(NO);
   SetColLabel(0);
   SetFontLabel(FONT_1);
}

/******************************************************************************/
/*                           ACCESSEURS				                  			*/
/******************************************************************************/
void LabelAlarme::SetAlarmId(UWORD16 _AlarmId)
{
   AlarmId = _AlarmId;
   GetFLabel()->SetText(GetName());
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelAlarme::GetAlarmId()
{
   return AlarmId;
}
/*----------------------------------------------------------------------------*/
void LabelAlarme::RemoveAlarmId(UWORD16 AlarmId)
{
   AlarmId  = AlarmId; /* To Avoid warning */ 
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne le nom d'une alarme															*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Nom de l'alarme				  														*/
/******************************************************************************/
UBYTE* LabelAlarme::GetName()
{
   if(GetPtrName() != NULL)
   {
      UBYTE **tmp;
      tmp = GetPtrName();
     
		/*%C positionnement de la ligne (ici NB_LANGUAGE = nb de langues) */
      tmp = &tmp[GetNbLanguage()*(GetAlarmId())];
      
      /*%C lecture de la colonne */
      return tmp[GetLanguage()];
   }
   else
	{
      return (UBYTE *)"";
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelAlarme::RefreshLanguage()
{
   GetFLabel()->SetTextOnly(GetName());
}
