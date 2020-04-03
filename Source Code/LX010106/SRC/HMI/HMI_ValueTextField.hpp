/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ValueTextField.hpp 						 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_ValueTextField.cpp								     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef ValueTextFieldH
#define ValueTextFieldH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_ValueField.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class ValueTextField: public ValueField
{

private:

	/* Parametres */

	UBYTE *Text;

	e_BOOL IsString;

	/* Methodes */

protected:
	
	/* Parametres */

	/* Methodes */

public:
	
	/* Parametres */

	/* Methodes */

	ValueTextField();

	ValueTextField(DisplayObject *Parent);

	virtual void SetValue(UWORD16 Value);

	void SetTextOnly(UBYTE* Text);
	void SetText(UBYTE* Text);

	UBYTE* GetText();
	UBYTE GetPixelSize();

	virtual void Show();
	virtual void Hide();
	virtual void Clear();

};

#endif
