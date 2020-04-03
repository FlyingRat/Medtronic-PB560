/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MessageDialog.hpp 	 		  			 		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_MessageDialog.cpp 					  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef MessageDialogH
#define MessageDialogH

								
/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "typedef.h"
#include "HMI_DisplayObject.hpp"
#include "HMI_TextField.hpp"
#include "HMI_SymbolField.hpp"
#include "HMI_GraphicBox.hpp"
#include "HMI_Tools.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class MessageDialog : public DisplayObject
{
private:

   /* Parametres */

   TextField FLine1;
   e_BOOL Line1Centered;

   TextField FLine2;
   e_BOOL Line2Centered;

	TextField FLine3;
   e_BOOL Line3Centered;

   SymbolField FSymbol;

	GraphicBox MonitorBox;

   UBYTE TextLine[cMAX_LINE][cMAX_CHARACTER];

   e_BOOL Line1Ok, Line2Ok, Line3Ok, SymbolOk;
   
   UWORD16 WBox;
   
   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   MessageDialog();

   void SetMessage(UBYTE* Text, e_SYMBOL Symbol);

	void Init(  UWORD16 Line,
               UWORD16  Col,
               UWORD16 Heigth,
               UWORD16  Width,
               e_BOOL Black);

   void InitGraphicBox( UWORD16 _Line,
                        UWORD16  _Col,
                        UWORD16 _Heigth,
                        UWORD16  _Width,
                        e_BOOL _RoundHigh,
                        e_BOOL _RoundLow,
                        e_BOOL _Black);

   TextField* GetFLine1();
   TextField* GetFLine2();
   TextField* GetFLine3();

   UWORD16 GetHeight();
   UWORD16 GetWidth();   

   void SetLine1Centered(e_BOOL _Centered);
   e_BOOL IsLine1Centered();

   void SetLine2Centered(e_BOOL _Centered);
   e_BOOL IsLine2Centered();

   void SetLine3Centered(e_BOOL _Centered);   
   e_BOOL IsLine3Centered();

   SymbolField* GetFSymbol();

   void SetColLine1(UWORD16 Col);
   void SetColSymbol(UWORD16 Col);
   void SetColLine2(UWORD16 Col);
   void SetColLine3(UWORD16 Col);

   void SetLineLine1(UWORD16 _Line);
   void SetLineLine2(UWORD16 _Line);
   void SetLineLine3(UWORD16 _Line);
   UWORD16 GetLineLine1();
   UWORD16 GetLineLine2();
   UWORD16 GetLineLine3();

   void SetSpaceBetweenLines(  UWORD16 _Space);   

   virtual void Show();
   virtual void Hide();
   virtual void Refresh();   

   void SetWhithBox(UWORD16 WBox);

};

#endif
