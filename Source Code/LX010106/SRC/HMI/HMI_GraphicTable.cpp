/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_GraphicTable.cpp	                                 	 		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Affichage d'un tableau															      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_GraphicTable.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Tools.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "enum.h"
#include "DB_Config.h"
#include "HMI_DataBaseAccess.hpp"
#include "HMI_Message.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
GraphicTable::GraphicTable():DisplayObject()
{
   LineNb = TABLE_LINE_NB;
   ColNb = TABLE_COL_NB;
   SetWidth(TABLE_WIDTH);
   SetHeight(TABLE_HEIGHT);
   SetFirstLineHeight(TABLE_FIRST_LINE_HEIGHT);
   SetFirstColWidth(TABLE_FIRST_COL_WIDTH);

   /*%C Initialisation de l'inverse video des cellules */
   UWORD16 i,j;
   for(i=0; i<TABLE_MAX_LINE_NB; i++)
   {
         for(j=0; j<TABLE_MAX_COL_NB; j++)
         {
            GraphTableConfig.CellConfig[i][j] = FALSE;
         }
   }
   /*%C Toute la colonne est en inverse video, sauf la première case mais
      SetConfigVideoForCol() ne l'impacte pas */
   SetConfigVideoForCol(TABLE_COL_NB-2, TRUE);

   /*%C Aucune ligne n'est gras par défaut */
   BoldLines = 0x0;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void GraphicTable::SetBoldLine(UWORD16 _Line)
{
   if(_Line <= LineNb)
      BoldLines |= (0x1 << _Line);

}
/*----------------------------------------------------------------------------*/
void GraphicTable::ClearBoldLines()
{
   BoldLines = 0x0;
}
/*----------------------------------------------------------------------------*/
e_BOOL GraphicTable::IsBoldLine(UWORD16 _Line)
{
   if(_Line <= LineNb)
   {
      if(BoldLines & (0x1 << _Line))
         return TRUE;
   }
   return FALSE;
}
/*----------------------------------------------------------------------------*/
void GraphicTable::SetWidth(UWORD16 _Width)
{
   Width = _Width;
}
/*----------------------------------------------------------------------------*/
UWORD16 GraphicTable::GetWidth(void)
{
   return(Width);
}
/*----------------------------------------------------------------------------*/
void GraphicTable::SetHeight(UWORD16 _Height)
{
   Height = _Height;
}
/*----------------------------------------------------------------------------*/
UWORD16 GraphicTable::GetHeight(void)
{
   return(Height);
}
/*----------------------------------------------------------------------------*/
void GraphicTable::SetLineNb(UWORD16 _LineNb)
{
   UWORD16 i,j;
   e_BOOL video;
   if(( _LineNb != 0)&&(_LineNb < TABLE_MAX_LINE_NB))
   {
      /*%C Si on a ajouté des lignes */
      if( _LineNb > LineNb)
      {
         /*%C Pour chaque ligne ajoutée */
         for(i=LineNb; i<_LineNb; i++)
         {
            /*%C Pour chaque colonne, on vérifie si elle est configurée en inverse video */
            for(j=0; j<ColNb; j++)
            {
               video = GetMarkColConfigVideo(j);
               SetConfigVideoForCell(i, j, video);
            }
         }
      }
      LineNb = _LineNb;
   }
   else
      LineNb = 2;
}
/*----------------------------------------------------------------------------*/
UWORD16 GraphicTable::GetLineNb(void)
{
   return(LineNb);
}
/*----------------------------------------------------------------------------*/
void GraphicTable::SetFirstLineHeight(UWORD16 _FirstLineHeight)
{
   FirstLineHeight = _FirstLineHeight;
}
/*----------------------------------------------------------------------------*/
UWORD16 GraphicTable::GetFirstLineHeight(void)
{
   return(FirstLineHeight);
}
/*----------------------------------------------------------------------------*/
void GraphicTable::SetOtherLineHeight(UWORD16 _OtherLineHeight)
{
   OtherLineHeight = _OtherLineHeight;
}
/*----------------------------------------------------------------------------*/
UWORD16 GraphicTable::GetOtherLineHeight(void)
{
   return(OtherLineHeight);
}
/*----------------------------------------------------------------------------*/
void GraphicTable::SetColNb(UWORD16 _ColNb)
{
   UWORD16 i,j;
   e_BOOL video;
   if(( _ColNb != 0)&&(_ColNb < TABLE_MAX_COL_NB))
   {
      /*%C Si on a ajouté des colonnes */
      if( _ColNb > ColNb)
      {
         /*%C Pour chaque colonne ajoutée */
         for(i=ColNb; i<_ColNb; i++)
         {
            /*%C Pour chaque ligne, on vérifie si elle est configurée en inverse video */
            for(j=0; j<LineNb; j++)
            {
               video = GetMarkLineConfigVideo(j);
               SetConfigVideoForCell(j, i, video);
            }
         }
      }
      ColNb = _ColNb;
   }
   else
      ColNb = 2;
}
/*----------------------------------------------------------------------------*/
void GraphicTable::SetColTitle(UWORD16 _Col, UBYTE** _Msg)
{
   if((_Col < ColNb) && (_Msg != NULL))
      ColTitle[_Col] = _Msg;
}
/*----------------------------------------------------------------------------*/
UWORD16 GraphicTable::GetColNb(void)
{
   return(ColNb);
}
/*----------------------------------------------------------------------------*/
void GraphicTable::SetFirstColWidth(UWORD16 _FirstColWidth)
{
   FirstColWidth = _FirstColWidth;
}
/*----------------------------------------------------------------------------*/
UWORD16 GraphicTable::GetFirstColWidth(void)
{
   return(FirstColWidth);
}
/*----------------------------------------------------------------------------*/
void GraphicTable::SetOtherColWidth(UWORD16 _OtherColWidth)
{
   OtherColWidth = _OtherColWidth;
}
/*----------------------------------------------------------------------------*/
UWORD16 GraphicTable::GetOtherColWidth(void)
{
   return(OtherColWidth);
}
/*----------------------------------------------------------------------------*/
void GraphicTable::SetSize(UWORD16 _LineNb)
{
	SetLineNb(_LineNb);
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
/*%I 		Line : Ligne objet 																	*/
/*%I		Col : Colonne objet																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphicTable::Init(UWORD16 _Line, UWORD16 _Col)
{
   UWORD16 i;
   
   /*%C appel de l'init de la classe parente */
   DisplayObject::Init(_Line, _Col);

   for(i=0; i<TABLE_MAX_COL_NB; i++)
   {
      ColTitle[i] = NULL;
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Récupère la ligne d'affichage pour une cellule donnée                    */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		UWORD16 _Line : ligne définissant la cellule									*/
/*%I		UWORD16 _Col : colonne définissant la cellule            				*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Ligne d'affichage sur l'écran graphique   									*/
/******************************************************************************/
UWORD16 GraphicTable::GetDisplayLineForCell(UWORD16 _Line, UWORD16 _Col)
{
   if((_Line <= LineNb) && (_Col <= ColNb))
   {
      if(_Line == 0)
         return (GetLine());
      else
         return (GetLine()+FirstLineHeight + (_Line - 1)*OtherLineHeight);
   }
   return 0;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Récupère la colonne d'affichage pour une cellule donnée                  */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		UWORD16 _Line : ligne définissant la cellule									*/
/*%I		UWORD16 _Col : colonne définissant la cellule            				*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Colonne d'affichage sur l'écran graphique   									*/
/******************************************************************************/
UWORD16 GraphicTable::GetDisplayColForCell(UWORD16 _Line, UWORD16 _Col)
{
   if((_Line <= LineNb) && (_Col <= ColNb))
   {
      if(_Col == 0 )
         return (GetCol());
      else
         return (GetCol()+FirstColWidth + (_Col - 1)*OtherColWidth);
   }
   return 0;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Configuration de l'inverse video pour une cellule donnée     				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		UWORD16 _Line : ligne définissant la cellule									*/
/*%I		UWORD16 _Col : colonne définissant la cellule            				*/
/*%I		e_BOOL _Video : inverse video ou non                                 */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphicTable::SetConfigVideoForCell(UWORD16 _Line, UWORD16 _Col, e_BOOL _Video)
{
   if((_Line <= LineNb) && (_Col <= ColNb))
   {
      GraphTableConfig.CellConfig[_Line][_Col] = _Video;
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Récupération de la configuration de l'inverse video pour une cellule  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		UWORD16 _Line : ligne définissant la cellule									*/
/*%I		UWORD16 _Col : colonne définissant la cellule            				*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O		e_BOOL _Video : inverse video ou non                                 */
/******************************************************************************/
e_BOOL GraphicTable::GetConfigVideoForCell(UWORD16 _Line, UWORD16 _Col)
{
   if((_Line <= LineNb) && (_Col <= ColNb))
      return(GraphTableConfig.CellConfig[_Line][_Col]);
   else
      return(FALSE);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Configuration de l'inverse video pour une colonne donnée     				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		UWORD16 _Col : colonne                                   				*/
/*%I		e_BOOL _Video : inverse video ou non                                 */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphicTable::SetConfigVideoForCol(UWORD16 _Col, e_BOOL _Video)
{
   UWORD16 i ;
   if(_Col <= ColNb)
   {
      for(i=1; i<LineNb; i++)
      {
         SetConfigVideoForCell(i, _Col, _Video);
      }
   MarkColConfigVideo(_Col, _Video);
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Configuration de l'inverse video pour une ligne donnée        				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		UWORD16 _Line : ligne                                   				*/
/*%I		e_BOOL _Video : inverse video ou non                                 */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphicTable::SetConfigVideoForLine(UWORD16 _Line, e_BOOL _Video)
{
   UWORD16 i ;
   if(_Line <= LineNb)
   {
      for(i=1; i<ColNb; i++)
      {
         SetConfigVideoForCell(_Line, i, _Video);
      }
   MarkLineConfigVideo(_Line, _Video);
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Marquage de la colonne selon son type d'inverse video       				   */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		UWORD16 _Col : colonne                                   				*/
/*%I		e_BOOL _Video : inverse video ou non                                 */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphicTable::MarkColConfigVideo(UWORD16 _Col, e_BOOL _Video)
{
   if(_Col <= ColNb)
   {
      GraphTableConfig.ColConfig[_Col] = _Video;
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Récupération du marquage de la colonne selon son type d'inverse video    */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		UWORD16 _Col : colonne                                   				*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		e_BOOL _Video : inverse video ou non  							  				*/
/******************************************************************************/
e_BOOL GraphicTable::GetMarkColConfigVideo(UWORD16 _Col)
{
   if(_Col <= ColNb)
   {
      return(GraphTableConfig.ColConfig[_Col]);
   }
   else
      return(FALSE);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Récupération du marquage de la ligne selon son type d'inverse video      */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		UWORD16 _Col : colonne                                   				*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O		e_BOOL _Video : inverse video ou non                                 */
/******************************************************************************/
e_BOOL GraphicTable::GetMarkLineConfigVideo(UWORD16 _Line)
{
   if(_Line <= LineNb)
   {
      return(GraphTableConfig.LineConfig[_Line]);
   }
   else
      return(FALSE);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Marquage de la ligne selon son type d'inverse video       				   */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		UWORD16 _Line : ligne                                     				*/
/*%I		e_BOOL _Video : inverse video ou non                                 */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphicTable::MarkLineConfigVideo(UWORD16 _Line, e_BOOL _Video)
{
   if(_Line <= LineNb)
   {
      GraphTableConfig.LineConfig[_Line] = _Video;
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Renvoie la ligne d'affichage de la première cellule sur laquelle on peut */
/*%C écrire                                                                   */
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
UWORD16 GraphicTable::GetFirstCellLineToWriteTo(void)
{
   UWORD16 FirstLineCell;

   FirstLineCell = GetDisplayLineForCell(1, 0);
   if(OtherLineHeight != 0)
      FirstLineCell += OtherLineHeight/2;
   FirstLineCell += 4; /* réajustement */
   return(FirstLineCell);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Renvoie l'espace entre deux cellules                                     */
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
UWORD16 GraphicTable::GetSpacingBetweenCells(void)
{
   return(OtherLineHeight);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphicTable::Hide()
{
   /*%C Efface la boite précédente */
	InterfaceCppC::EraseZone(	GetLine(),
										GetCol(),
										Height,
										Width,
										0,
										GetPage());
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphicTable::Show()
{
   UWORD16 i,j;
   UWORD16 BaseLine = GetLine();
   UWORD16 BaseCol = GetCol();
   UWORD16 LastLineOffset;

   /*%C  Calcul de la hauteur des lignes (autres que la première)
         en prenant en compte :
               - la hauteur totale de la graphic table
               - la hauteur de la première ligne
               - le nombre de lignes (autres que la première) */
   OtherLineHeight = (Height - FirstLineHeight) / (LineNb - 1);

   /* Si la taille du tableau n'est pas divisible par le nombre de ligne,
      alors on corrige sur la dernière ligne */
   LastLineOffset = (Height - FirstLineHeight) % (LineNb - 1);

   /*%C Même calcul pour largeur des colonnes (autres que la première) */
   OtherColWidth = (Width - FirstColWidth) / (ColNb -1);

   /*%C Dessin de la boite... */
   /*%C... première ligne horizontale */
   InterfaceCppC::DisplayLine(   BaseLine,
                                 BaseCol+FirstColWidth,
										   0,
										   Width-FirstColWidth,
										   1,
										   GetPage());
   /*%C... dernière ligne horizontale */
   InterfaceCppC::DisplayLine(   BaseLine+Height,
                                 BaseCol,
										   0,
										   Width,
										   1,
										   GetPage());
   /*%C... première ligne verticale */
   InterfaceCppC::DisplayLine(   BaseLine+FirstLineHeight,
                                 BaseCol,
										   Height-FirstLineHeight,
										   0,
										   1,
										   GetPage());

   /*%C... dernière ligne verticale */
   InterfaceCppC::DisplayLine(   BaseLine,
                                 BaseCol+Width,
										   Height,
										   0,
										   1,
										   GetPage());


   /*%C Dessin des lignes horizontales */
   for(i=0; i<(LineNb-1); i++)
   {
      InterfaceCppC::DisplayLine(BaseLine+FirstLineHeight+i*OtherLineHeight,
										   BaseCol,
										   0,
										   Width,
										   1,
										   GetPage());
      /*%C si la ligne est en gras alors on affiche une seconde ligne */                                 
      if(IsBoldLine(i))
            InterfaceCppC::DisplayLine(BaseLine+FirstLineHeight+i*OtherLineHeight+1,
										   BaseCol,
										   0,
										   Width,
										   1,
										   GetPage());
   }

   /*%C Dessin des lignes verticales */
   for(i=0; i<(ColNb-1); i++)
   {
      InterfaceCppC::DisplayLine(BaseLine,
										   BaseCol+FirstColWidth+i*OtherColWidth,
										   Height,
										   0,
										   1,
										   GetPage());
   }

   /*%C Arrondi les angles */
	InterfaceCppC::DisplaySymbol(	CADRE_BLACK_HGw,
											BaseLine,
											BaseCol+FirstColWidth,
											GetPage());

	InterfaceCppC::DisplaySymbol(	CADRE_BLACK_HDw,
											BaseLine,
											BaseCol+Width-3,
											GetPage());

 	InterfaceCppC::DisplaySymbol(	CADRE_BLACK_HGw,
 											BaseLine+FirstLineHeight,
 											BaseCol,
 											GetPage());

 	InterfaceCppC::DisplaySymbol(	CADRE_BLACK_BGw,
 											BaseLine+Height-3,
 											BaseCol,
 											GetPage());

 	InterfaceCppC::DisplaySymbol(	CADRE_BLACK_BDw,
 											BaseLine+Height-3,
 											BaseCol+Width-3,
 											GetPage());

   UWORD16 DisplayLine, DisplayCol;
   UWORD16 DisplayWidth, DisplayHeight;   

   for(i=0; i<LineNb; i++)
   {
      for(j=0; j<ColNb; j++)
      {
         if(GetConfigVideoForCell(i,j))
         {
            DisplayLine = GetDisplayLineForCell(i,j);
            DisplayCol = GetDisplayColForCell(i,j);
            if(i==0)
               DisplayHeight = FirstLineHeight;
            else
               DisplayHeight = OtherLineHeight;

            if(j==0)
               DisplayWidth = FirstColWidth;
            else
               DisplayWidth = OtherColWidth;

            if(i != (LineNb-1))
            {
               /*%C La cellule en inverse video */
            	InterfaceCppC::DisBox(  DisplayLine+1,
                                       DisplayCol,
                                       DisplayHeight-2,
                                       DisplayWidth-1,
						   			         TRUE,
							   		         1,
                                       GetPage());
            }
            else
            {
               /*%C La dernière cellule en inverse video */
            	InterfaceCppC::DisBox(  DisplayLine+1,
                                       DisplayCol,
                                       DisplayHeight+LastLineOffset-2,
                                       DisplayWidth-1,
						   			         TRUE,
							   		         1,
                                       GetPage());
            }

            if(i != (LineNb-1))
            {
               /*%C Le trait de séparation au bas de la cellule sauf pour la
                  dernière cellule */
	            InterfaceCppC::DisplayLine(DisplayLine+DisplayHeight,
			   							         DisplayCol,
				   						         0,
					   					         DisplayWidth,
						   				         0,
                                          GetPage());
            }

            /*%C si la ligne précédente est en gras alors on affiche une seconde ligne */
            if((i != 0) && (IsBoldLine(i-1)))
               InterfaceCppC::DisplayLine(DisplayLine+1,
			   							         DisplayCol,
				   						         0,
					   					         DisplayWidth,
						   				         0,
                                          GetPage());


         }
      }
   }

   /*%C Dessine les titres des colonnes du tableau */
   UWORD16 Val;
   UWORD16 StringPixelSize;
   DataBaseAccess::ReadValue(&Val,ADJUST_LANGUAGE_U16,CONFIG);
	for(i=1; i<ColNb; i++)
   {
      if (ColTitle[i][Val] != NULL)
      {
         StringPixelSize = Tools::GetStringPixelSize((UBYTE*) ColTitle[i][Val], FONT_1);
         /*%C Si le texte à afficher est inférieur en taille pixel à la largeur
            de la colonne qui va le contenir */
         if( OtherColWidth > StringPixelSize)
         {
   	      InterfaceCppC::DisplayString(	(UBYTE*)ColTitle[i][Val],
											FONT_1,
											FALSE,
											BaseLine+(FirstLineHeight/2)+4,  /* +4 car on ne connait pas hauteur des caractères ! */
											BaseCol+FirstColWidth+(i-1)*OtherColWidth + (OtherColWidth - StringPixelSize)/2 + 1,
											1,
											GetPage());
         }
         else
         {
   	      InterfaceCppC::DisplayString(	(UBYTE *)"Err",
											FONT_1,
											FALSE,
											BaseLine+(FirstLineHeight/2),
											BaseCol+FirstColWidth+(i-1)*OtherColWidth,
											1,
											GetPage());
         }
      }
   }      
}
