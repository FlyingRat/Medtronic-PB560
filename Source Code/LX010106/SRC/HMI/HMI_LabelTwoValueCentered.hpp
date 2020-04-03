/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTwoValueCentered.hpp 						   	         */
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelTwoValueCentered.cpp  				      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelTwoValueCenteredH
#define LabelTwoValueCenteredH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelTwoValue.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelTwoValueCentered: public LabelTwoValue
{

private:

	/* Parametres */

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelTwoValueCentered();

   void SetValue2(UWORD16 _Value2);   
   virtual void Refresh();

};

#endif
