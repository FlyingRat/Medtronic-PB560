/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueSymbol.cpp  			                          	 	   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + Text + sep + value+ unit)					      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelOneValueLine.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "HMI_Tools.hpp"
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelOneValueLine::LabelOneValueLine()
{
    LineToBeDisplayed = FALSE;
}

/******************************************************************************/
/*                           ACCESSEURS						                	   */
/******************************************************************************/
e_BOOL LabelOneValueLine::GetLineToBeDisplayed()
{
	return(LineToBeDisplayed);
}
/******************************************************************************/
void LabelOneValueLine::SetLineToBeDisplayed(e_BOOL _ToBeDisplayed)
{
	LineToBeDisplayed = _ToBeDisplayed;
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
/*%I	  	Icon   : icone												               		*/
/*%I		Name   : Pointeur sur le tableau de nom						         	*/
/*%I		Line   : ligne 												              		*/
/*%I		Col    : colonne												            		*/
/*%I		Value  : Valeur								               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueLine::Init(  e_SYMBOL _Icon,
                           UBYTE **_Name,
                           UWORD16 _Line,
                           UWORD16 _Col,
                           UWORD16 _Value,
                           UBYTE **_NameUnit)
{
	LabelOneValue::Init(_Icon, _Name, _Line, _Col, _Value, _NameUnit);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet															 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueLine::Show()
{
	LabelOneValue::Show();

    if(GetLineToBeDisplayed())
        InterfaceCppC::DisplayLine( GetLine() - 11,
                                    GetColLabel() + 3,
                                    0,
						    		Tools::GetStringPixelSize(GetName(),GetFontLabel()),
								    1,
								    GetPage());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet															 			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE												               					*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelOneValueLine::Hide()
{
    if(GetLineToBeDisplayed())
        InterfaceCppC::DisplayLine( GetLine() - 11,
                                    GetColLabel() + 3,
                                    0,
				    				Tools::GetStringPixelSize(GetName(),GetFontLabel()),
					    			0,
						    		GetPage());
	LabelOneValue::Hide();
}