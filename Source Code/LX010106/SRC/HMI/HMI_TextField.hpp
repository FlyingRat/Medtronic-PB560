/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_TextField.hpp 	 						 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_TextField.cpp 	 								     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef TextFieldH
#define TextFieldH					

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_FieldObject.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class TextField: public FieldObject
{

private:

	/* Parametres */

	UBYTE *Text;

	/* Methodes */

protected:

	/* Parametres */

	/* Methodes */

public:

	/* Parametres */

	/* Methodes */

	TextField();

	TextField(DisplayObject *Parent);

	void Init(	SWORD16 Line, 
					UWORD16 Col, 
					UWORD16 Font, 
					e_BOOL ReverseVideo, 
					UBYTE *Text);

	void SetText(UBYTE* Text);
	UBYTE* GetText();

	void SetTextOnly(UBYTE* Text);

	UBYTE GetPixelSize();
	
	virtual void Blink(e_BOOL Actif);
	virtual void Show();
	virtual void Hide();
	virtual void Clear();

};

#endif
