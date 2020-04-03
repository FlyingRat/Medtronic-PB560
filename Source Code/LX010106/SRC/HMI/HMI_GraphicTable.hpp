/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_GraphicTable.hpp	   		                             	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_GraphicTable.cpp  	      	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef GraphicTableH
#define GraphicTableH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_DisplayObject.hpp" 

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

 /*#define L_MAX 		208//204
#define L_MIN 		130//138
#define L_C1  		75//65
#define L_OTHER 	42//46
#define L_MIDDLE  48 */

#define TABLE_LINE_NB 5
#define TABLE_COL_NB  4
#define TABLE_MAX_COL_NB 6
#define TABLE_MAX_LINE_NB 10

#define TABLE_WIDTH   204
#define TABLE_HEIGHT  183
#define TABLE_FIRST_LINE_HEIGHT 23
#define TABLE_FIRST_COL_WIDTH 72

typedef struct
{
   e_BOOL CellConfig[TABLE_MAX_LINE_NB][TABLE_MAX_COL_NB];
   e_BOOL ColConfig[TABLE_MAX_COL_NB];
   e_BOOL LineConfig[TABLE_MAX_LINE_NB];

} tGraphTableConfig;

//---------------------------------------------------------------------------
class GraphicTable: public DisplayObject
{

private:

   /* Parametres */

   /* caractéristiques de la boite */
   /* Line et Col sont hérités de DisplayObject */
   UWORD16 Width;

   UWORD16 Height;

   /* les lignes dans la boite */
   UWORD16 LineNb; /* en comptant la première */

   UWORD16 FirstLineHeight;

   UWORD16 OtherLineHeight;

   UWORD32 BoldLines;   /* Masque comprenant l'info "gras" pour chaque ligne */

   /* les colonnes dans la boite */
   UWORD16 ColNb; /* en comptant la première */

   UWORD16 FirstColWidth;

   UWORD16 OtherColWidth;

   UBYTE** ColTitle[TABLE_MAX_COL_NB];

   /* Configuration des cellules (et notamment inverse video */

   tGraphTableConfig GraphTableConfig;

   /* Methodes */

protected:

	/* Parametres */

   /* Methodes */

public:

	/* Parametres */

   /* Methodes */
   void Init(UWORD16 _Line, UWORD16 _Col);
   
   void SetWidth(UWORD16 _Width);
   UWORD16 GetWidth(void);

   void SetHeight(UWORD16 _Heigth);
   UWORD16 GetHeight(void);

   void SetLineNb(UWORD16 _LineNb);
   UWORD16 GetLineNb(void);

   void SetFirstLineHeight(UWORD16 _FirstLineHeight);
   UWORD16 GetFirstLineHeight(void);

   void SetOtherLineHeight(UWORD16 _OtherLineHeight);
   UWORD16 GetOtherLineHeight(void);

   void SetColNb(UWORD16 _ColNb);
   UWORD16 GetColNb(void);

   void SetColTitle(UWORD16 _Col, UBYTE** _Msg);

   void SetFirstColWidth(UWORD16 _FirstColWidth);
   UWORD16 GetFirstColWidth(void);

   void SetOtherColWidth(UWORD16 _OtherColWidth);
   UWORD16 GetOtherColWidth(void);

   void SetConfigVideoForCell(UWORD16 _Line, UWORD16 _Col, e_BOOL _Video);
   e_BOOL GetConfigVideoForCell(UWORD16 _Line, UWORD16 _Col);

   void SetConfigVideoForCol(UWORD16 _Col, e_BOOL _Video);

   void MarkColConfigVideo(UWORD16 _Col, e_BOOL _Video);
   e_BOOL GetMarkColConfigVideo(UWORD16 _Col);

   void SetConfigVideoForLine(UWORD16 _Line, e_BOOL _Video);

   void MarkLineConfigVideo(UWORD16 _Line, e_BOOL _Video);   
   e_BOOL GetMarkLineConfigVideo(UWORD16 _Line);

   UWORD16 GetDisplayLineForCell(UWORD16 _Line, UWORD16 _Col);

   UWORD16 GetDisplayColForCell(UWORD16 _Line, UWORD16 _Col);

   UWORD16 GetFirstCellLineToWriteTo(void);

   UWORD16 GetSpacingBetweenCells(void);     

   GraphicTable();
   
   virtual void Show();

   virtual void Hide();

   void SetSize(UWORD16 LineNb);

   void SetBoldLine(UWORD16 _Line);

   void ClearBoldLines();

   e_BOOL IsBoldLine(UWORD16 _Line);   

};

#endif
