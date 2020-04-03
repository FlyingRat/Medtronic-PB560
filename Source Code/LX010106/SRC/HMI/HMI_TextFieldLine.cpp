/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_TextFieldLine.cpp   									 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage d'un texte											 			  	*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_TextFieldLine.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

#include "HMI_InterfaceCppC.hpp"

#include "HMI_Tools.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
TextFieldLine::TextFieldLine():TextField()
{

}
/*----------------------------------------------------------------------------*/
TextFieldLine::TextFieldLine(DisplayObject *_Parent)
{
	TextFieldLine();
	SetParent(_Parent);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void TextFieldLine::SetUpperLined(e_BOOL _UpperLined)
{
    UpperLined = _UpperLined;
}
/******************************************************************************/
e_BOOL TextFieldLine::GetUpperLined()
{
    return(UpperLined);
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation				 																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Line         : ligne 											            	*/
/*%I		Col          : colonne 										            		*/
/*%I		ReverseVideo : TRUE si en reverse video			     		         	*/
/*%I		Text		   : texte a afficher													*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void TextFieldLine::Init(SWORD16 _Line,
                     UWORD16 _Col,
                     UWORD16 _Font,
                     e_BOOL _ReverseVideo,
                     UBYTE *_Text,
                     e_BOOL _UpperLined)
{
	TextField::Init(_Line, _Col, _Font, _ReverseVideo, _Text);
    SetUpperLined(_UpperLined);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet		 																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void TextFieldLine::Show()
{
	TextField::Show();
    if(GetUpperLined())
        InterfaceCppC::DisplayLine( GetLine() - 11,
                                    GetCol(),
                                    0,
						    		GetPixelSize() - 2,
								    1,
								    GetPage());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet		 																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void TextFieldLine::Hide()
{
    if(GetUpperLined())
        InterfaceCppC::DisplayLine( GetLine() - 11,
                                    GetCol(),
                                    0,
						    		GetPixelSize() - 2,
								    0,
								    GetPage());
	TextField::Hide();
}
