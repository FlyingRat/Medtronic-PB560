/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueDbRT.hpp 	 	                             	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelOneValueDbRT.cpp    	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelOneValueDbRTH
#define LabelOneValueDbRTH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelOneValue.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelOneValueDbRT: public LabelOneValue
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

   LabelOneValueDbRT();

	virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void IncreaseValue();
   virtual void DecreaseValue();

};

#endif

