/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Pen.hpp 			 		 				 		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_Pen.cpp 	 							  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef PenH
#define PenH
								
/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

extern "C"
{
#include "typedef.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define DOTTED_LENGTH 2

class Pen
{

private:

   /* Parametres */

	/*%C LineThickness [ 0: ??? ] */
   static UWORD16 LineThickness;

	/*%C LocalCounter [ 0: ??? ] */
   UWORD16 LocalCounter;

	/*%C Dotted [ 0: ??? ] */
   e_BOOL 	Dotted;

	/*%C DottedState [ 0: ??? ] */
   e_BOOL	DottedState;
   
   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */ 

public:

   /* Parametres */

   /* Methodes */

   Pen();

   void SwapDottedState();
   
   void SetDotted(e_BOOL Dotted);
   e_BOOL IsDotted();
   
   void SetDottedState(e_BOOL DottedState);
   e_BOOL IsDottedState();
   
   static void SetLineThickness(UWORD16 LineThickness);
   static UWORD16 GetLineThickness();

};

#endif
