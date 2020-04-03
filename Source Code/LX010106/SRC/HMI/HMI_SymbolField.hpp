/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_SymbolField.hpp 		 					 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_SymbolField.cpp 	  							     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef SymbolFieldH
#define SymbolFieldH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_FieldObject.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class SymbolField: public FieldObject
{
private:

	/* Parametres */

	e_SYMBOL Symbol;

	e_BOOL BarredSymbol;

	/* Methodes */

protected:

	/* Parametres */

	/* Methodes */

public:

	/* Parametres */

	/* Methodes */

	SymbolField();

	SymbolField(DisplayObject *Parent);

	void Init(  UWORD16 Line,
               UWORD16 Col,
               UWORD16 Font,
               e_BOOL ReverseVideo,
               e_SYMBOL Symbol);

	void SetSymbol(e_SYMBOL Symbol);
	e_SYMBOL GetSymbol();

	void SetBarredSymbol(e_BOOL Barred);
	e_BOOL GetBarredSymbol();

	virtual void Blink(e_BOOL Actif);
	virtual void Show();
	virtual void Hide();
	virtual void Clear();	  

};

#endif
