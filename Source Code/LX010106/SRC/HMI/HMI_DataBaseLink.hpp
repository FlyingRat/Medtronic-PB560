/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_DataBaseLink.hpp	                                   	    	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_DataBaseLink.cpp	                 	      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef DataBaseLinkH
#define DataBaseLinkH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_IhmType.hpp"
extern "C"
{
#include "typedef.h"
#include "enum.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class DataBaseLink
{
private:

   /* Parametres */

	/*%C IdParam [ 0 : ???] */
   UWORD16 IdParam;

   e_TYPE_OF_DB_TARGET DbTarget;

   /* Methodes */

protected:
   
   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   DataBaseLink();

   void Init(UWORD16 IdParam, e_TYPE_OF_DB_TARGET DbTarget);
  
   void SetIdParam(SWORD16 IdParam);
	UWORD16 GetIdParam();

   void SetDbTarget(e_TYPE_OF_DB_TARGET DbTarget);
   e_TYPE_OF_DB_TARGET GetDbTarget();

};

#endif
