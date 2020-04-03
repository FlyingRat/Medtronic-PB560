/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueTrig.cpp  	    	           	 	  				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	d'une valeur avec trigger 										*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelOneValueTrig.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_InterfaceCppC.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValueTrig::LabelOneValueTrig():LabelOneValue()
{
	FTrig.SetParent(this);
	FTrig.SetSymbol(TRIGGER);
	HideTrigger();
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelOneValueTrig::SetTrigger(e_BOOL _Flag)
{
   Trigger = _Flag;
}
/*----------------------------------------------------------------------------*/
e_BOOL LabelOneValueTrig::IsTrigger()
{
	return (e_BOOL)(Trigger == TRUE);
}
/*----------------------------------------------------------------------------*/
void LabelOneValueTrig::SetColTrigger(UWORD16 _Col)
{
   FTrig.SetCol(_Col);
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Formate l'affichage																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																			        	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueTrig::Format(UWORD16 _NewValue)
{
	LabelOneValue::Format(_NewValue);
	//FTrig.SetCol(GetPixelSize()+ 10);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affiche le trigger																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																			        	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueTrig::ShowTrigger()
{
	FTrig.Hide();
	//FTrig.SetCol(GetPixelSize()+ 10);
	SetTrigger(TRUE);
	FTrig.Show();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Efface le trigger																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																			        	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueTrig::HideTrigger()
{
	SetTrigger(FALSE);
	FTrig.Hide();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Passage en invertion video																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	InvertVideo   : invertion si TRUE									        	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueTrig::SetInvertVideo(e_BOOL _InvertVideo)
{
	LabelOneValue::SetInvertVideo(_InvertVideo);
	FTrig.SetReverseVideo(_InvertVideo);

	if(_InvertVideo)
   {
		FTrig.SetSymbol(TRIGGERINV);
	}
	else
   {
		FTrig.SetSymbol(TRIGGER);
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																			        	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueTrig::Show()
{
	LabelOneValue::Show();

	if(IsTrigger())
   {
		ShowTrigger();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement	de l'Objet 																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																			        	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueTrig::Hide()
{
	HideTrigger();
	LabelOneValue::Hide();    
}

