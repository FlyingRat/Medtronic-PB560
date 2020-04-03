/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_TendanceTable.hpp	   		                             	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_TendanceTable.cpp        	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef TendanceTableH
#define TendanceTableH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_DisplayObject.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/


//---------------------------------------------------------------------------
class TendanceTable: public DisplayObject
{

private:

   /* Parametres */
   UWORD16 FirstDisplayLine;
   UWORD16 FirstDisplayCol;

   UWORD16 NbOfLines;
   UWORD16 NbOfCols;

   UWORD16 Height;
   UWORD16 Width;
   UWORD16 LineHeight;

   UWORD16 OddColWidth;
   UWORD16 EvenColWidth;

   /* Methodes */
   void SetFirstDisplayLine(UWORD16 _FirstDisplayLine);
   UWORD16 GetFirstDisplayLine();

   void SetFirstDisplayCol(UWORD16 _FirstDisplayCol);
   UWORD16 GetFirstDisplayCol();

   void SetNbOfLines(UWORD16 _NbOfLines);
   UWORD16 GetNbOfLines();

   void SetNbOfCols(UWORD16 _NbOfCols);
   UWORD16 GetNbOfCols();

   void SetHeight(UWORD16 _Height);
   UWORD16 GetHeight();

   void SetLineHeight(UWORD16 _LineHeight);
   UWORD16 GetLineHeight();

   void SetWidth(UWORD16 _Width);
   UWORD16 GetWidth();

   void SetOddColWidth(UWORD16 _OddColWidth);
   UWORD16 GetOddColWidth();

   void SetEvenColWidth(UWORD16 _EvenColWidth);
   UWORD16 GetEvenColWidth();

protected:
	
	/* Parametres */

   /* Methodes */

public:
	
	/* Parametres */

   /* Methodes */
   void InitDefault();

   void Init(  UWORD16 _Line,
               UWORD16 _Col,
               UWORD16 _NbLine,
               UWORD16 _NbCol,
               UWORD16 _Height,
               UWORD16 _Width,
               UWORD16 _OddColWidth,
               UWORD16 _EvenColWidth);

	TendanceTable();

   UWORD16 GetLineOfCell(UWORD16 _CellLine, UWORD16 _CellCol);
   UWORD16 GetLeftJustifiedColOfCell(UWORD16 _CellLine, UWORD16 _CellCol);
   UWORD16 GetWidthOfCell(UWORD16 _CellLine, UWORD16 _CellCol);   

   virtual void Show();
   
};

#endif
