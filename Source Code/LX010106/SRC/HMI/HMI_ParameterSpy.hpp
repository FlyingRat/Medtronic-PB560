/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ParameterSpy.hpp 			  			 		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_ParameterSpy.cpp 	 				  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef ParameterSpyH
#define ParameterSpyH
								
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

#define MAX_SPY   31
#define NO_PARAM  9999

class ParameterSpy

{

private:
   
   /* Parametres */

	/*%C TableId [ 0: MAX_SPY ] */
   UWORD16 TableId[MAX_SPY];

	/*%C TableBd [ 0: MAX_SPY ] */
   e_TYPE_OF_DB_TARGET TableBd[MAX_SPY];
   
	/*%C TableValue [ 0: MAX_SPY ] */
   UWORD16 TableValue[MAX_SPY];
   
	/*%C TableEvent [ 0: MAX_SPY ] */
   EventId TableEvent[MAX_SPY];

	/*%C TableEventOk [ 0: MAX_SPY ] */
   e_BOOL TableEventOk[MAX_SPY];
   
   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:
 	
 	/* Parametres */

   /* Methodes */

   ParameterSpy();
   
   void AddElement(  UWORD16 Id,
                     e_TYPE_OF_DB_TARGET Bd,
                     UWORD16 Value,
                     EventId Event);

   UWORD16 FindParam(UWORD16 Id,
                     e_TYPE_OF_DB_TARGET Bd,
                     UWORD16 Value);

   UWORD16 FindFreeIndex();
   
   void RemoveElement(  UWORD16 Id,
                        e_TYPE_OF_DB_TARGET Bd,
                        UWORD16 Value);

   void RemoveAll(void);
   void Refresh();
	void Reset();

};

#endif
