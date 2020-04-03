/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MessageDialog.cpp     	      			 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage d'un message										 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_MessageDialog.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

#include "HMI_Tools.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "HMI_FrameVentilation.hpp"
#include "HMI_FrameAlarme.hpp"
#include "DB_IHMAccessParaDatabase.h"
/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
MessageDialog::MessageDialog():DisplayObject()
{
   FLine1.SetParent(this);
	FLine2.SetParent(this);
	FLine3.SetParent(this);
   FSymbol.SetParent(this);
	MonitorBox.SetParent(this);

   Line1Ok = FALSE;
   Line2Ok = FALSE;
   Line3Ok = FALSE;
   SymbolOk = FALSE;
   FLine1.Init(15,16,FONT_1,TRUE,(UBYTE *)"");
   FLine2.Init(91,16,FONT_1,TRUE,(UBYTE *)"");
   FLine3.Init(111,16,FONT_1,TRUE,(UBYTE *)"");
   FSymbol.Init(33,40,FONT_1,TRUE,NO);
	MonitorBox.Init(32,192,152,120,TRUE,TRUE,TRUE);

   SetLine1Centered(TRUE);
   SetLine2Centered(TRUE);
   SetLine3Centered(TRUE);   
}

/*----------------------------------------------------------------------------*/
void MessageDialog::SetWhithBox(UWORD16 _WBox)
{
   WBox = _WBox;
}

/******************************************************************************/
/*                           ACCESSEURS				                    			*/
/******************************************************************************/
void MessageDialog::SetLine1Centered(e_BOOL _Centered)
{
   Line1Centered = _Centered;
}
/*----------------------------------------------------------------------------*/
void MessageDialog::SetLine2Centered(e_BOOL _Centered)
{
   Line2Centered = _Centered;
}
/*----------------------------------------------------------------------------*/
void MessageDialog::SetLine3Centered(e_BOOL _Centered)
{
   Line3Centered = _Centered;
}
/*----------------------------------------------------------------------------*/
e_BOOL MessageDialog::IsLine1Centered()
{
   return(Line1Centered);
}
/*----------------------------------------------------------------------------*/
e_BOOL MessageDialog::IsLine2Centered()
{
   return(Line2Centered);
}
/*----------------------------------------------------------------------------*/
e_BOOL MessageDialog::IsLine3Centered()
{
   return(Line3Centered);
}
/*----------------------------------------------------------------------------*/
void MessageDialog::SetColLine1(UWORD16 _Col)
{
   FLine1.SetCol(_Col);
}
/*----------------------------------------------------------------------------*/
void MessageDialog::SetColSymbol(UWORD16 _Col)
{
   FSymbol.SetCol(_Col);
}
/*----------------------------------------------------------------------------*/
void MessageDialog::SetColLine2(UWORD16 _Col)
{
   FLine2.SetCol(_Col);
}
/*----------------------------------------------------------------------------*/
void MessageDialog::SetColLine3(UWORD16 _Col)
{
   FLine3.SetCol(_Col);
}
/*----------------------------------------------------------------------------*/
void MessageDialog::SetLineLine1(UWORD16 _Line)
{
   FLine1.SetLine(_Line);
}
/*----------------------------------------------------------------------------*/
void MessageDialog::SetLineLine2(UWORD16 _Line)
{
   FLine2.SetLine(_Line);
}
/*----------------------------------------------------------------------------*/
void MessageDialog::SetLineLine3(UWORD16 _Line)
{
   FLine3.SetLine(_Line);
}
/*----------------------------------------------------------------------------*/
UWORD16 MessageDialog::GetLineLine1()
{
   return(FLine1.GetLine());
}
/*----------------------------------------------------------------------------*/
UWORD16 MessageDialog::GetLineLine2()
{
   return(FLine2.GetLine());
}
/*----------------------------------------------------------------------------*/
UWORD16 MessageDialog::GetLineLine3()
{
   return(FLine3.GetLine());
}
/*----------------------------------------------------------------------------*/
TextField* MessageDialog::GetFLine1()
{
   return &this->FLine1;
}
/*----------------------------------------------------------------------------*/
TextField* MessageDialog::GetFLine2()
{
   return &this->FLine2;
}
/*----------------------------------------------------------------------------*/
TextField* MessageDialog::GetFLine3()
{
   return &this->FLine3;
}
/*----------------------------------------------------------------------------*/
UWORD16 MessageDialog::GetHeight()
{
   return(MonitorBox.GetHeight());
}
/*----------------------------------------------------------------------------*/
UWORD16 MessageDialog::GetWidth()
{
   return(MonitorBox.GetWidth());
}
/*----------------------------------------------------------------------------*/
SymbolField* MessageDialog::GetFSymbol()
{
   return &this->FSymbol;
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des paramettres d'acces a DB										*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Line   : ligne											               			*/
/*%I		Col    : colonne											            			*/
/*%I		Heigth : Hauteur											            			*/
/*%I		Width  : Largeur											            			*/
/*%I		Black  : en noir																 		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MessageDialog::Init(  UWORD16 _Line,
                           UWORD16  _Col,
                           UWORD16 _Heigth,
                           UWORD16  _Width,
                           e_BOOL _Black)
{
   DisplayObject::Init(_Line,_Col);
	MonitorBox.Init(_Line,_Col,_Heigth,_Width,TRUE,TRUE,_Black);

   /*%C On calcule l'espace entre les lignes à partir de ces données : */
   /*%C 2 bords + 3 lignes + 1 symbole => 2*5px + 3*9px + 31px = 68px */
   UWORD16 space = 0;

   if(_Heigth > 68) space = (_Heigth - 68) / 3;

   /*%C  Limite l'écart à 20px */
   if(space > 20) space =20;

   /*%C 5px + 9px => 1ère ligne à 5px du bord */
	FLine1.Init(14,16,FONT_1,TRUE,(UBYTE *)"");

   /*%C 5px + 9px + space (-1 recalage Symbole) */
	FSymbol.Init(14+space-1,(_Width-37)/2,FONT_1,TRUE,NO);

   /*%C 5px + 9px + space + 31px + space + 9px */
	FLine2.Init(54+2*space,16,FONT_1,TRUE,(UBYTE *)"");

   /*%C 5px + 9px + space + 31px + space + 9px + space + 9px */
	FLine3.Init(63+3*space,16,FONT_1,TRUE,(UBYTE *)"");
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Postionne l'espacement entre les lignes                                  */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_Space   : Espacement entre chaque ligne  	               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MessageDialog::SetSpaceBetweenLines(  UWORD16 _Space)
{
   UWORD16 _FirstLine =  FLine1.GetLine();

	FLine2.SetLine(_FirstLine + _Space);

	FLine3.SetLine(_FirstLine + _Space);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des paramettres d'affichage du fond du message   			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Line        : ligne											               	*/
/*%I		Col         : colonne											            	*/
/*%I		Heigth      : Hauteur											            	*/
/*%I		Width       : Largeur											            	*/
/*%I		RoundHigh   : Bord Supérieur rond ?												*/
/*%I		RoundLow    : Bord Inférieur rond ?												*/
/*%I		Black       : en noir																*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MessageDialog::InitGraphicBox( UWORD16 _Line,
                                    UWORD16  _Col,
                                    UWORD16 _Heigth,
                                    UWORD16  _Width,
                                    e_BOOL _RoundHigh,
                                    e_BOOL _RoundLow,
                                    e_BOOL _Black)
{
   DisplayObject::Init(_Line,_Col);
	MonitorBox.Init(_Line,_Col,_Heigth,_Width,_RoundHigh,_RoundLow,_Black);

   /*%C On calcule l'espace entre les lignes à partir de ces données : */
   /*%C 2 bords + 3 lignes + 1 symbole => 2*5px + 3*9px + 31px = 68px */
   UWORD16 space = 0;

   if(_Heigth > 68) space = (_Heigth - 68) / 3;

   /*%C  Limite l'écart à 20px */
   if(space > 20) space =20;

   /*%C 5px + 9px => 1ère ligne à 5px du bord */
	FLine1.Init(14,16,FONT_1,TRUE,(UBYTE *)"");

   /*%C 5px + 9px + space (-1 recalage Symbole) */
	FSymbol.Init(14+space-1,(_Width-37)/2,FONT_1,TRUE,NO);

   /*%C 5px + 9px + space + 31px + space + 9px */
	FLine2.Init(54+2*space,16,FONT_1,TRUE,(UBYTE *)"");

   /*%C 5px + 9px + space + 31px + space + 9px + space + 9px */
	FLine3.Init(63+3*space,16,FONT_1,TRUE,(UBYTE *)"");
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage d'un Message																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Text   : texte a afficher										         		*/
/*%I		Symbol : symbole a afficher													 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MessageDialog::SetMessage( UBYTE* Text, e_SYMBOL Symbol)
{
   /*%C Déclaration du Texte tampon */
   UBYTE* TextTemp;
   e_BOOL _IsVisible[3];

   /*%C Variables locales */
   UWORD16 SizeBox = 0 ;
   UWORD16 BoxFont = 0;
   UWORD16 i = 0 , j = 0 , k = 0, x1 = 0,  x2 = 0;

   /*%C Init du tableau de Ligne */
   for (i=0; i<cMAX_LINE; i++)
   {
		for (j=0; j<cMAX_CHARACTER; j++)
      {
			/*%C Protection pour le dépasement */
         i = i % cMAX_LINE;
         j = j % cMAX_CHARACTER;
         TextLine[i][j] = 0;
      }
   }

   /*%C Receuil de la longueur de la fenetre + 2 afin d'intégrer */
   /* le cadre Noir */
	SizeBox = WBox - 2;

	/*%C Receuil de la police de la police */
   BoxFont = FLine1.GetFont();

   /*%C Appel de la fonction de traitement de message */
   TextTemp = Tools::BuildMessage(Text , SizeBox , BoxFont);

   /*%C Mis en forme des différentes lignes */
   for(i = 0 ; i < 100 ; i ++)
   {
      if(TextTemp[i] == '\0')
		{
			break;
		}
      else if(TextTemp[i] == '|')
      {
         j = j + 1;
         i = i + 1;
         k = 0; 
      }
	   /*%C Protection pour le dépasement */
	   x1 = j;
		x1 = x1 % cMAX_LINE;
	   /*%C Protection pour le dépasement */
	   x2 = k;
		x2 = x2 % cMAX_CHARACTER;
	   TextLine[x1][x2] = TextTemp [i];
      k ++;
   }

   _IsVisible[1] = FLine2.IsVisible();
   _IsVisible[2] = FLine2.IsVisible();
   /*%C Centrer les messages en fonction de la fenêtre */
   if(IsLine1Centered())
   {
      _IsVisible[0] = FLine1.IsVisible();
      FLine1.SetVisible(FALSE);
      FLine1.SetCol(	(SizeBox -
	   					((Tools::GetStringPixelSize(TextLine[0], BoxFont))-1)) /
		   				2);
      FLine1.SetVisible(_IsVisible[0]);
   }

   if(IsLine2Centered())
   {
      _IsVisible[1] = FLine2.IsVisible();
      FLine2.SetVisible(FALSE);
   	FLine2.SetCol(	(SizeBox -
	   					((Tools::GetStringPixelSize(TextLine[1], BoxFont))-1)) /
   	   				2);
      FLine2.SetVisible(_IsVisible[1]);
   }


   if(IsLine3Centered())
   {
      _IsVisible[2] = FLine2.IsVisible();
      FLine3.SetVisible(FALSE);      
      FLine3.SetCol(	(SizeBox -
	   					((Tools::GetStringPixelSize(TextLine[2], BoxFont))-1)) /
   	   				2);
      FLine3.SetVisible(_IsVisible[2]);
   }

	FLine1.SetText(TextLine[0]);
	FLine2.SetText(TextLine[1]);
	FLine3.SetText(TextLine[2]);


	/*%C Affichage du Symbol */
	if((Symbol != NONE) && (Symbol != NO))
   {
		SymbolOk = TRUE;
		FSymbol.SetSymbol(Symbol);
   }

   /* Affichage d'une ligne blanche et une ligne sur le cadre Alarme */
	/* ou Ventil afin d'éviter son effacement */
   	if(WBox == WHITH_ALARMEBOX)
   {
        InterfaceCppC::DisplayLine( 36,
                                    COL_ALARMEBOX + WHITH_ALARMEBOX,
												109,
                                    0,
												1,
												this->GetPage());
		  InterfaceCppC::DisplayLine( 35,
                                    COL_ALARMEBOX + WHITH_ALARMEBOX + 1,
												111,
                                    0,
												0,
												this->GetPage());
	}
	else if (WBox == WHITH_VENTILBOX)
	{
        InterfaceCppC::DisplayLine( 37,
												COL_VENTILBOX + WHITH_VENTILBOX,
												143,
												0,
												1,
												this->GetPage());
		  InterfaceCppC::DisplayLine( 36,
                                    COL_VENTILBOX + WHITH_VENTILBOX + 1,
												145,
												0,
												0,
                                    this->GetPage());
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MessageDialog::Show()
{
   DisplayObject::Show();
	MonitorBox.Show();
   FLine1.Show();
   FSymbol.Show();
   FLine2.Show();
	FLine3.Show();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MessageDialog::Hide()
{
	FLine1.Hide();
	FSymbol.Hide();
	FLine2.Hide();
	FLine3.Hide();
	DisplayObject::Hide();    
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Rafraîchissement de l'Objet																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MessageDialog::Refresh()
{
	DisplayObject::Show();
 	FLine1.Hide();
	FLine1.Show();
 	FLine2.Hide();   
	FLine2.Show();   
}

