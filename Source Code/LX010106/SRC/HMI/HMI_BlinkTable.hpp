/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_BlinkTable.hpp		                                      	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_BlinkTable.cpp	                         		*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef BlinkTableH
#define BlinkTableH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_DisplayObject.hpp"
extern "C"
{
#include "typedef.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define cMAX_BLINK 5

class BlinkTable
{
private:

   /* Parametres */
   
   DisplayObject *Table[cMAX_BLINK];

   e_BOOL BlinkState;

   /* Methodes */

protected:
   
   /* Parametres */
   
   /* Methodes */ 

public:

	/* Parametres */
   
   /* Methodes */ 

   BlinkTable();

   void AddElement(DisplayObject *Object);
   void RemoveElement(DisplayObject *Object);
   void RemoveAll(void);
   void Blink();

};

#endif
