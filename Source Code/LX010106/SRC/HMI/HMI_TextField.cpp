/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_TextField.cpp   									 						*/
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

#include "HMI_TextField.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

#include "HMI_InterfaceCppC.hpp"

#include "HMI_Tools.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
TextField::TextField():FieldObject()
{
	Text = (UBYTE *)"???";
}
/*----------------------------------------------------------------------------*/
TextField::TextField(DisplayObject *_Parent)
{
	TextField();
   SetParent(_Parent);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void TextField::SetText(UBYTE* _Text)
{
	/*%C effacement de la valeur precedante */
	Clear();

	/*%C affectation */
	Text = _Text;

	/*%C affichage */
	if(IsVisible())
   {
      Show();
	}
}
/*----------------------------------------------------------------------------*/
void TextField::SetTextOnly(UBYTE* _Text)
{
	/*%C effacement de la valeur précédente */
	Clear();
	Text = _Text;
}
/*----------------------------------------------------------------------------*/
UBYTE* TextField::GetText()
{
	if(Text != NULL)
   {
		return (Text);
	}
	else
      return (UBYTE *)"???";
}
/*----------------------------------------------------------------------------*/
UBYTE TextField::GetPixelSize()
{
	return Tools::GetStringPixelSize(Text, GetFont());
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
void TextField::Init(SWORD16 _Line,
                     UWORD16 _Col,
                     UWORD16 _Font,
                     e_BOOL _ReverseVideo,
                     UBYTE *_Text)
{
	FieldObject::Init(_Line, _Col, _Font, _ReverseVideo);
   SetText(_Text);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet			 																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void TextField::Blink(e_BOOL _Actif)
{
	if(_Actif)
   {
		Hide();
	}
	else
   {
		Show();
	}
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
void TextField::Show()
{
	if(!HaveParent() || GetParent()->IsVisible())
   {
      FieldObject::Show();
		
		UWORD16 ColTmp, LineTmp;
		LineTmp = GetLine();
		ColTmp = GetCol();

		if(HaveParent())
      {
			LineTmp = LineTmp+ GetParent()->GetLine();
			ColTmp  = ColTmp + GetParent()->GetCol();
		}
		
		InterfaceCppC::DisplayString( GetText(),
								         	GetFont(),
									         GetReverseVideo(),
									         LineTmp,
         									ColTmp,
			         						1,
						         			GetPage());
	}
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
void TextField::Hide()
{
    if(!HaveParent() || GetParent()->IsVisible())
    {
	    if(IsVisible())
        {
		    /*%C Clear before hide !! */
		    Clear();
		    FieldObject::Hide();
	    }
    }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Efface la valeur courante 																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void TextField::Clear()
{
     if(!HaveParent() || GetParent()->IsVisible())
     {
	    if(IsVisible())
        {
		    UWORD16 ColTmp, LineTmp;
		    LineTmp = GetLine();
		    ColTmp = GetCol();

		    if(HaveParent())
            {
		    	LineTmp = LineTmp+ GetParent()->GetLine();
			    ColTmp  = ColTmp + GetParent()->GetCol();
		    }

		    InterfaceCppC::DisplayString(   GetText(),
									        GetFont(),
   			      						    GetReverseVideo(),
	         								LineTmp,
			         						ColTmp,
         									0,
						         			GetPage());
	    }
     }
}
