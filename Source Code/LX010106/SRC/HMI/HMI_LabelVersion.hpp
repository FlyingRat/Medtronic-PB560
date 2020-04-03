/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelVersion.hpp 		  				   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelVersion.cpp  					  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelVersionH
#define LabelVersionH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelValueString.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelVersion : public LabelValueString
{
private:
   
   /* Parametres */
   e_TYPE_OF_DB_TARGET DbTarget;


   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

	LabelVersion();
   virtual UBYTE* GetValue1Name();
   void InitDbAccess(e_TYPE_OF_DB_TARGET _DbTarget);

};

#endif
