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

#ifndef TextFieldLineH
#define TextFieldLineH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_TextField.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class TextFieldLine: public TextField
{

private:

	/* Parametres */
    e_BOOL UpperLined;
	

	/* Methodes */

protected:

	/* Parametres */

	/* Methodes */

public:

	/* Parametres */

	/* Methodes */
    void SetUpperLined(e_BOOL _UpperLined);
    e_BOOL GetUpperLined();

	TextFieldLine();

	TextFieldLine(DisplayObject *Parent);

    void Init(	SWORD16 Line,
					UWORD16 Col,
					UWORD16 Font,
					e_BOOL ReverseVideo,
					UBYTE *Text,
                    e_BOOL _UpperLined);
                    
	virtual void Show();
	virtual void Hide();

};

#endif
