/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ShiftingDots.hpp		  		                             	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_ShiftingDots.cpp 		   	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef ShiftingDotsH
#define ShiftingDotsH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_DisplayObject.hpp"      
#include "HMI_SymbolField.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define MAX_SYMBOLS 5

class ShiftingDots: public DisplayObject
{

private:

   /* Parametres */

   e_SYMBOL PreviousSymbols[MAX_SYMBOLS];

   SymbolField Symbols[MAX_SYMBOLS];

   UWORD16 Current;

   e_BOOL Vertical;
   /* Methodes */

   void SetVertical(e_BOOL _Vertical);
   e_BOOL IsVertical();

protected:
   
   /* Parametres */
   
   /* Methodes */

public:
   
   /* Parametres */
   
   /* Methodes */

   ShiftingDots();

   void Init(  e_SYMBOL _FirstSymbol,
               e_SYMBOL _SecondSymbol,
               e_BOOL _Vertical,
               UWORD16 _Line,
               UWORD16 _Col);

   void SetPreviousSymbol(e_SYMBOL _PreviousSymbol, UWORD16 _Index);
   e_SYMBOL GetPreviousSymbol(UWORD16 _Index);
   void ChangeSymbol(UWORD16 _Index);
   void Animate();   

   virtual void Show();
   virtual void Hide();
};

#endif
