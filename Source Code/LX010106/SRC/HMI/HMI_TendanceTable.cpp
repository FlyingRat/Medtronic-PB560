/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_TendanceTable.cpp                                 	 		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Affichage d'un tableau de tendance											      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_TendanceTable.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_InterfaceCppC.hpp"

#define DEFAULT_TREND_TABLE_FIRST_LINE      67
#define DEFAULT_TREND_TABLE_FIRST_COL       0
#define DEFAULT_TREND_TABLE_LINE_NB         6
#define DEFAULT_TREND_TABLE_COL_NB          4
#define DEFAULT_TREND_TABLE_HEIGHT          150
#define DEFAULT_TREND_TABLE_WIDTH           318
#define DEFAULT_TREND_TABLE_ODD_COL_WIDTH   67
#define DEFAULT_TREND_TABLE_EVEN_COL_WIDTH  93

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
TendanceTable::TendanceTable():DisplayObject()
{
   SetFirstDisplayLine(DEFAULT_TREND_TABLE_FIRST_LINE);
   SetFirstDisplayCol(DEFAULT_TREND_TABLE_FIRST_COL);
   SetNbOfLines(DEFAULT_TREND_TABLE_LINE_NB);
   SetNbOfCols(DEFAULT_TREND_TABLE_COL_NB);
   SetHeight(DEFAULT_TREND_TABLE_HEIGHT);
   SetWidth(DEFAULT_TREND_TABLE_WIDTH);
   SetOddColWidth(DEFAULT_TREND_TABLE_ODD_COL_WIDTH);
   SetEvenColWidth(DEFAULT_TREND_TABLE_EVEN_COL_WIDTH);
   SetLineHeight(GetHeight() / GetNbOfLines());
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void TendanceTable::SetFirstDisplayLine(UWORD16 _FirstDisplayLine)
{
   FirstDisplayLine = _FirstDisplayLine;
}
/*----------------------------------------------------------------------------*/
UWORD16 TendanceTable::GetFirstDisplayLine()
{
   return(FirstDisplayLine);
}
/*----------------------------------------------------------------------------*/
void TendanceTable::SetFirstDisplayCol(UWORD16 _FirstDisplayCol)
{
   FirstDisplayCol = _FirstDisplayCol;
}
/*----------------------------------------------------------------------------*/
UWORD16 TendanceTable::GetFirstDisplayCol()
{
   return(FirstDisplayCol);
}
/*----------------------------------------------------------------------------*/
void TendanceTable::SetNbOfLines(UWORD16 _NbOfLines)
{
   if(_NbOfLines != 0)
      NbOfLines = _NbOfLines;
   else
      NbOfLines = 1;
}
/*----------------------------------------------------------------------------*/
UWORD16 TendanceTable::GetNbOfLines()
{
   return(NbOfLines);
}
/*----------------------------------------------------------------------------*/
void TendanceTable::SetNbOfCols(UWORD16 _NbOfCols)
{
   if(_NbOfCols != 0)
      NbOfCols = _NbOfCols;
   else
      NbOfCols = 1;      
}
/*----------------------------------------------------------------------------*/
UWORD16 TendanceTable::GetNbOfCols()
{
   return(NbOfCols);
}
/*----------------------------------------------------------------------------*/
void TendanceTable::SetHeight(UWORD16 _Height)
{
   Height = _Height;
}
/*----------------------------------------------------------------------------*/
UWORD16 TendanceTable::GetHeight()
{
   return(Height);
}
/*----------------------------------------------------------------------------*/
void TendanceTable::SetLineHeight(UWORD16 _LineHeight)
{
   LineHeight = _LineHeight;
}
/*----------------------------------------------------------------------------*/
UWORD16 TendanceTable::GetLineHeight()
{
   return(LineHeight);
}
/*----------------------------------------------------------------------------*/
void TendanceTable::SetWidth(UWORD16 _Width)
{
   Width = _Width;
}
/*----------------------------------------------------------------------------*/
UWORD16 TendanceTable::GetWidth()
{
   return(Width);
}
/*----------------------------------------------------------------------------*/
void TendanceTable::SetOddColWidth(UWORD16 _OddColWidth)
{
   OddColWidth = _OddColWidth;
}
/*----------------------------------------------------------------------------*/
UWORD16 TendanceTable::GetOddColWidth()
{
   return(OddColWidth);
}
/*----------------------------------------------------------------------------*/
void TendanceTable::SetEvenColWidth(UWORD16 _EvenColWidth)
{
   EvenColWidth = _EvenColWidth;
}
/*----------------------------------------------------------------------------*/
UWORD16 TendanceTable::GetEvenColWidth()
{
   return(EvenColWidth);
}
/*----------------------------------------------------------------------------*/
UWORD16 TendanceTable::GetLineOfCell(UWORD16 _CellLine, UWORD16 _CellCol)
{
   UWORD16 Value = 0 ;
   if(_CellLine <= NbOfLines)
   {
      Value = GetFirstDisplayLine() + _CellLine * GetLineHeight() + GetLineHeight() - 5;
   }

   return(Value);
}
/*----------------------------------------------------------------------------*/
UWORD16 TendanceTable::GetLeftJustifiedColOfCell(UWORD16 _CellLine, UWORD16 _CellCol)
{
   UWORD16 Value = 0 ;
   if(_CellCol <= NbOfCols)
   {
      /* Colonne paire */
      if((_CellCol%2) == 0)
      {
         Value = (_CellCol/2) * (GetEvenColWidth() + GetOddColWidth());
      }
      /* Colonne impaire */
      else
      {
         Value = GetEvenColWidth() + (_CellCol/2) * (GetEvenColWidth() + GetOddColWidth());
      }
      Value += GetFirstDisplayCol();
      Value += 3; /* Pour ne pas être "collé" à la colonne */
   }
   return(Value);
}
/*----------------------------------------------------------------------------*/
UWORD16 TendanceTable::GetWidthOfCell(UWORD16 _CellLine, UWORD16 _CellCol)
{
   UWORD16 Value = 0 ;
   if((_CellCol <= NbOfCols) && (_CellLine <= NbOfLines))
   {
      /* Colonne paire */
      if((_CellCol%2) == 0)
         Value = GetEvenColWidth();
      /* Colonne impaire */
      else
         Value = GetOddColWidth();
   }
   return(Value);
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation par défaut de l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void TendanceTable::InitDefault()
{

}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation  de l'Objet													         */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I     _Line : ligne de début d'affichage                                   */
/*%I     _Col : colonne de début d'affichage                                  */
/*%I     _NbLine : nombre d'entrées horizontales de la table                  */
/*%I     _NbCol : nombre d'entrées verticales de la table                     */
/*%I     _Height : hauteur totale de la table                                 */
/*%I     _Width : largeur totale de la table                                  */
/*%I     _OddColWidth : largeur des colonnes impaires                         */
/*%I     _EvenColWidth : largeur des colonnes paires                          */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void TendanceTable::Init(  UWORD16 _Line,
                           UWORD16 _Col,
                           UWORD16 _NbLine,
                           UWORD16 _NbCol,
                           UWORD16 _Height,
                           UWORD16 _Width,
                           UWORD16 _OddColWidth,
                           UWORD16 _EvenColWidth)
{
   SetFirstDisplayLine(_Line);
   SetFirstDisplayCol(_Col);
   SetNbOfLines(_NbLine);
   SetNbOfCols(_NbCol);
   SetHeight(_Height);
   SetWidth(_Width);
   SetOddColWidth(_OddColWidth);
   SetEvenColWidth(_EvenColWidth);

   LineHeight = GetHeight() / GetNbOfLines();   
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
void TendanceTable::Show()
{
   UWORD16 i;
   UWORD16 _firstLine = GetFirstDisplayLine();
   UWORD16 _line;
   UWORD16 _spacing = GetHeight() / GetNbOfLines();
   UWORD16 _totalWidth = GetWidth();
   UWORD16 _col;
   UWORD16 _firstCol = GetFirstDisplayCol();

   _line = _firstLine;
   _col = _firstCol;

	/*%C Efface le tableau précédent */
	InterfaceCppC::EraseZone(	_line,
										_col,
										GetHeight(),
										GetWidth()-1,
										0,
										GetPage());

	/*%C Dessine toutes les lignes (de haut en bas) */
   InterfaceCppC::DisplayLine(_line,
										_col,
										0,
										_totalWidth,
										1,
										GetPage());

   for(i=0; i< GetNbOfLines(); i++)
   {
      _line += _spacing;

	   InterfaceCppC::DisplayLine(_line,
		   								_col,
			   							0,
				   						_totalWidth,
					   					1,
						   				GetPage());
   }

	/*%C Dessine toutes les colonnes (de gauche à droite) */
   InterfaceCppC::DisplayLine(_firstLine,
										_firstCol,
										GetHeight(),
										0,
										1,
										GetPage());

   for(i=0; i< GetNbOfCols(); i++)
   {

      /* Colonne paire */
      if((i%2) == 0)
      {
         _col = GetFirstDisplayCol() + GetEvenColWidth() + (i/2) * (GetEvenColWidth() + GetOddColWidth());
      }
      /* Colonne impaire */
      else
      {
         _col = GetFirstDisplayCol() + GetOddColWidth() + GetEvenColWidth() + (i/2) * (GetEvenColWidth() + GetOddColWidth());
      }
      /* Attention au max de l'afficheur */
      if(_col >= 320)
         _col = 319;
      
  	   InterfaceCppC::DisplayLine(_firstLine,
      									_col,
		      							GetHeight(),
   			      					0,
						      			1,
								      	GetPage());

   }

	/*%C Rajoute les angles arrondis */
	InterfaceCppC::DisplaySymbol(	CADRE_BLACK_HGw,
											_firstLine,
											_firstCol,
											GetPage());

	InterfaceCppC::DisplaySymbol(	CADRE_BLACK_HDw,
											_firstLine,
											_firstCol + GetWidth()-2,
											GetPage());

	InterfaceCppC::DisplaySymbol(	CADRE_BLACK_BGw,
											_line-2,
											_firstCol,
											GetPage());

	InterfaceCppC::DisplaySymbol(	CADRE_BLACK_BDw,
											_line-2,
											_firstCol + GetWidth()-2,
											GetPage());
}
